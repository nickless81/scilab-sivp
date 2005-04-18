#include "sivp_common.h"


static int read_image_data_alloc_cb(void *opaque, AVImageInfo *info)
{
  AVImageInfo * outinfo = (AVImageInfo*)opaque;
  long numBytes;
  uint8_t * buffer;
  int ret;

  //alloc memory for image data
  numBytes=avpicture_get_size(info->pix_fmt, info->width,info->height);
  buffer=(uint8_t*)malloc(numBytes);
  memset(buffer, 0 , numBytes);
  // Assign appropriate parts of buffer to image planes 
  ret = avpicture_fill(&(info->pict), buffer, info->pix_fmt,info->width, info->height);

  memcpy(outinfo, info, sizeof(AVImageInfo));
  
  return 0;

}


AVImageInfo* imgread(char *fname, char * filename)
{
  //  char buf[320*240*3+1024];
  AVPicture ImageRGBorGRAY, *pImageRGBorGRAY=&ImageRGBorGRAY;
  AVImageInfo *pinfo;

  ByteIOContext bi, *f=&bi;

  int ret;

  //register all available formats
  av_register_all();

  if (url_fopen(f, filename, URL_RDONLY) < 0)
    {
      return NULL;
    }

  pinfo = (AVImageInfo *)malloc(sizeof(AVImageInfo));
  if(!pinfo)
    {
      return NULL;
    }

  ret = av_read_image(f, filename, NULL , read_image_data_alloc_cb, pinfo);
  if (ret < 0)
    return NULL;

  //convert to PIX_FMT_RGB24 or PIX_FMT_GRAY8
  if( !(pinfo->pix_fmt == PIX_FMT_RGB24 || pinfo->pix_fmt == PIX_FMT_GRAY8))
    {
      if(pinfo->pix_fmt == PIX_FMT_NB)
	goto ERROR_TAG;
      
      uint8_t * s;
      int numBytes;
      enum PixelFormat dst_pix_fmt;

      if(pinfo->pix_fmt == PIX_FMT_PAL8 ||
	 pinfo->pix_fmt == PIX_FMT_MONOWHITE ||
	 pinfo->pix_fmt == PIX_FMT_MONOBLACK)
	{
	  dst_pix_fmt = PIX_FMT_GRAY8;
	}
      else
	{
	  dst_pix_fmt = PIX_FMT_RGB24;
	}

      numBytes=avpicture_get_size(dst_pix_fmt, pinfo->width,pinfo->height);
      s=(uint8_t*)malloc(numBytes);
      memset(s, 0 , numBytes);

      avpicture_fill(pImageRGBorGRAY, s, dst_pix_fmt, pinfo->width, pinfo->height); 
      ret = img_convert(pImageRGBorGRAY, dst_pix_fmt, &(pinfo->pict),  
		  pinfo->pix_fmt, pinfo->width, pinfo->height); 

      //free old image data
      avpicture_free(&(pinfo->pict));
      //copy AVPicture form pImageRGB to pinfo(pinfo will be returned)
      memcpy(&(pinfo->pict), pImageRGBorGRAY, sizeof(AVPicture));
      pinfo->pix_fmt =  dst_pix_fmt;
    }

  url_fclose(f);
  return pinfo;

 ERROR_TAG:
  
  url_fclose(f);
  avpicture_free(&(pinfo->pict));
  free(pinfo);
  return NULL;
}

int int_imgread(char *fname)
{
  int minlhs=1, minrhs=1, maxlhs=3, maxrhs=1;
  int mL, nL, lL;
  int mR, nR, lR;

  AVImageInfo * pInfo;
  unsigned char * pMatData;
  int nCh;

  CheckRhs(minrhs,maxrhs) ;
  CheckLhs(minlhs,maxlhs) ;

  GetRhsVar(1, "c", &mL, &nL, &lL);

  pInfo = imgread(fname, cstk(lL));

  if(!pInfo) //read file error
    {
       Scierror(999,"%s: Read image file %s error. Maybe this file does not exist.\r\n",fname, cstk(lL));
       return -1;
    }

  /*   convert the image data to matrix data (to columnwise) */
  nCh = (pInfo->pix_fmt==PIX_FMT_RGB24? 3 :1) ;

  pMatData = (unsigned char *)malloc(pInfo->width * pInfo->height * nCh);
  
  if(!pMatData)
    {
      Scierror(999, "%s: Can not alloc memory for image data.\n", fname);
      goto EXIT_TAG2;
    }


  img2mat(pInfo->pict.data[0], pMatData, pInfo->width, pInfo->height, nCh);

  if(Create3DIntMat(2, pInfo->height, pInfo->width, nCh, pMatData, I_UCHAR))
    {
      /*  Return variables  */
      LhsVar(1) = 2;
    }
  else
    {
      Scierror(999, "%s: Read image file %s error.\r\n",fname, cstk(lL));
    }



  /*   free memory */
 EXIT_TAG1:
  free(pMatData);
 EXIT_TAG2:
  avpicture_free(&(pInfo->pict));
  free(pInfo);
  return 0;

}

