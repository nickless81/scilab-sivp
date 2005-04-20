#include "sivp_common.h"

BOOL
conver_image(AVImageInfo * pSrc, AVImageInfo * pDst)
{
  
}

int int_imgwrite(char *fname)
{
  char **Str;
  char * filename;
  int mR1, nR1, lR1;
  int mR2, nR2, lR2;
  int mR11, nR11, lR11;
  int mR12, nR12, lR12;
  int mR13, nR13, lR13;
  int nBytes;

  AVImageInfo Info, * pInfo=&Info;
  AVImageInfo OutInfo;
  void * pOutBuf;

  AVImageFormat *pOutImgFmt;
  int nWidth, nHeight, nCh;
  SciIntMat Dims;
  SciIntMat ImgData;

  void * pImgData;

  ByteIOContext bi, *f=&bi;

  av_register_all();
  
  CheckRhs(2,2);
  CheckLhs(0,1);
/*   the first argument is a 2D matrix or 3D matrix */
  switch (  VarType(1) ) 
    {
    case 8:
      GetRhsVar(1, "I", &mR1, &nR1, &ImgData);
      nHeight = mR1;
      nWidth = nR1;
      nCh = 1;
      break;
    case  17: /* hmat */
      GetRhsVar(1,"m",&mR1,&nR1,&lR1);
      CheckLength(1, mR1, 3);
      GetListRhsVar(1,1,"S",&mR11,&nR11,&Str);
      if ( strcmp(Str[0],"hm") != 0)
	{
	  Scierror(999,"Argument 1 is not an hypermatrix\r\n");
	  return 0;
	}
      GetListRhsVar(1,2,"I",&mR12,&nR12,&Dims);
      GetListRhsVar(1,3,"I",&mR13,&nR13,&ImgData);

      nHeight = IC_INT32(Dims.D)[0];
      nWidth = IC_INT32(Dims.D)[1];
      if(Dims.n >= 3)
	nCh = IC_INT32(Dims.D)[2];
      else
	nCh = 1;

      /* we must free Str memory */
      FreeRhsSVar(Str);

      break;
    default:
      Scierror(999,"%s: The first argument must be a uint8 matrix\r\n", fname );
      break;
    }

  GetRhsVar(2, "c", &mR2, &nR2, &lR2);
  filename = cstk(lR2);
  
  /*Find the right AVImageFormat*/
  pOutImgFmt = guess_image_format(filename);
  if(!pOutImgFmt)
    {
      Scierror(999, "%s: Unsurpported image format.\r\n ", fname);
      return 0;
    }
  if(!pOutImgFmt->img_write)
    {
      Scierror(999, "%s: Unsurpported image format.\r\n ", fname);
      return 0;
    }

  pImgData = malloc(nWidth * nHeight * nCh);
  if(!pImgData)
    {
      Scierror(999, "%s, Can not alloc memory for image data", fname);
      return 0;
    }

  mat2img(ImgData.D, pImgData, nWidth, nHeight, nCh);

  /*   fill image info to a AVImageInfo stucture */
  if(nCh == 1)
    pInfo->pix_fmt = PIX_FMT_GRAY8;
  else
    pInfo->pix_fmt = PIX_FMT_RGB24;
  pInfo->width = nWidth;
  pInfo->height = nHeight;
  pInfo->interleaved = 0;
 
  avpicture_fill(&(pInfo->pict),pImgData, pInfo->pix_fmt, nWidth, nHeight);

  /*   pix_fmt convert */
  if (!(pOutImgFmt->supported_pixel_formats & (1 << pInfo->pix_fmt)))
    {
      int fmt;
      /*       find a supported pixel formats */
      for (fmt=0; fmt<PIX_FMT_NB; fmt++)
	{
	  if(pOutImgFmt->supported_pixel_formats & (1 << fmt))
	    break;
	}
      /* if can not find one */
      if(fmt == PIX_FMT_NB)
	{
	  Scierror(999, "%s: Can not find a supported pixel format for this file.", fname);
	  goto EXIT_TAG;
	}
      /*alloc memory for new format*/
      memcpy(&OutInfo, pInfo, sizeof(OutInfo));
      OutInfo.pix_fmt = fmt;
      pOutBuf = malloc( avpicture_get_size(OutInfo.pix_fmt, OutInfo.width, OutInfo.height) );
      if(!pOutBuf)
	{
	  Scierror(999, "%s: Can not alloc memory.", fname);
	  goto EXIT_TAG;
	}
      avpicture_fill(&(OutInfo.pict),pOutBuf, OutInfo.pix_fmt, OutInfo.width, OutInfo.height );
      
      if(img_convert( &(OutInfo.pict), OutInfo.pix_fmt, &(pInfo->pict), pInfo->pix_fmt, pInfo->width, pInfo->height ) < 0)
	{
	  Scierror(999, "%s: Can not convert the pixel format to a supported one.", fname);
	  goto EXIT_TAG2;
	}
      
      pInfo = &OutInfo;
    }

  /*   open a file for the image */
  if (url_fopen(f, filename, URL_WRONLY) < 0)
    {
      Scierror(999, "%s: Open file %s error.\r\n", fname, filename);
      goto EXIT_TAG;
    }

  av_write_image(f, pOutImgFmt, pInfo);

  url_fclose(f);
  

 EXIT_TAG2:
  avpicture_free(&(OutInfo.pict));

 EXIT_TAG:
  avpicture_free(&(Info.pict));

  return 0;

}

