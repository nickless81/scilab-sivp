#include "sivp_common.h"

typedef struct OpenedVDOfFile{
  char filename[FILENAME_MAX];
  AVFormatContext *pFormatCtx;
  AVCodecContext  *pCodecCtx;
  AVCodec         *pCodec;
  int nVdoStream; //video stream index
  unsigned long  nCurFrame;
  BOOL bOpened;
} OpenedVdoFile;
  
static OpenedVdoFile VdoFiles[MAX_VDO_FILE_NUM];


int
vdoopen(char * filename, char * fname)
{
  int nCurrFile;
  int i;
  static int inited = 0;
  
  /* init  */
  if(!inited)
    {
      memset(&VdoFiles, 0, sizeof(VdoFiles));
      inited = 1;
    }

  for (nCurrFile = 0; nCurrFile < MAX_VDO_FILE_NUM; nCurrFile++)
    {
      if( !VdoFiles[nCurrFile].bOpened)
	break;
    }

  if( nCurrFile ==  MAX_VDO_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files opened. Use vdoclose or vdocloseall to close some file.\r\n", fname);
      return -1;
    }

  // Register all formats and codecs
  av_register_all ();

  strcpy(VdoFiles[nCurrFile].filename, filename);

  // Open video file
  if (av_open_input_file (&(VdoFiles[nCurrFile].pFormatCtx), filename, NULL, 0, NULL) != 0)
    {
      Scierror(999, "%s: Couldn't open file %s. Maybe this file does not exist.\r\n", fname, filename);
      return -1;		// Couldn't open file
    }
  

  // Retrieve stream information
  if (av_find_stream_info( VdoFiles[nCurrFile].pFormatCtx ) < 0)
    {
      av_close_input_file(VdoFiles[nCurrFile].pFormatCtx);
      Scierror(999, "%s: Couldn't find steam information.\r\n", fname);
      return -1;		// Couldn't find stream information
    }
  dump_format(VdoFiles[nCurrFile].pFormatCtx, 0, filename, FALSE);


  // Find the first video stream
  VdoFiles[nCurrFile].nVdoStream = -1;
  for (i = 0; i < VdoFiles[nCurrFile].pFormatCtx->nb_streams; i++)
    if (VdoFiles[nCurrFile].pFormatCtx->streams[i]->codec.codec_type == CODEC_TYPE_VIDEO)
      {
	 VdoFiles[nCurrFile].nVdoStream = i;
	break;
      }
  
  // Can't find a video stream
  if ( VdoFiles[nCurrFile].nVdoStream == -1)
    {
      av_close_input_file(VdoFiles[nCurrFile].pFormatCtx);
      Scierror (999, "%s: No video stream in this file.\r\n", fname);
      return -1;
    }

  // Get a pointer to the codec context for the video stream
  VdoFiles[nCurrFile].pCodecCtx = &(VdoFiles[nCurrFile].pFormatCtx->streams[VdoFiles[nCurrFile].nVdoStream]->codec);
				    
  // Find the decoder for the video stream
  VdoFiles[nCurrFile].pCodec = avcodec_find_decoder (VdoFiles[nCurrFile].pCodecCtx->codec_id);
  if (VdoFiles[nCurrFile].pCodec == NULL)
    {
      av_close_input_file(VdoFiles[nCurrFile].pFormatCtx );
      Scierror(999, "%s: No codec for this video file.\r\n", fname);
      return -1;
    }

  // Open the codec
  if(avcodec_open(VdoFiles[nCurrFile].pCodecCtx, VdoFiles[nCurrFile].pCodec)<0)
    {
      av_close_input_file(VdoFiles[nCurrFile].pFormatCtx );
      Scierror(999, "%s: Can not open the codec for this video file.\r\n", fname);
      return -1; 
    }

				    
  if( VdoFiles[nCurrFile].pCodecCtx->frame_rate > 1000 
      && VdoFiles[nCurrFile].pCodecCtx->frame_rate_base == 1 )
    {
      VdoFiles[nCurrFile].pCodecCtx->frame_rate_base = 1000;
    }

  VdoFiles[nCurrFile].bOpened = TRUE;
  
  return nCurrFile;

}

AVFrame *
vdogetframe(int nFile, char *fname)
{
  AVFrame         *pFrame; 
  AVFrame         *pFrameRGB;
  AVPacket        packet;
  
  int nMemSize;
  int nFinished;
  unsigned char * pBuffer;
  int nRet;

  // Allocate memory for video frame
  pFrame=avcodec_alloc_frame();

  // Allocate memory for an RGB image
  pFrameRGB=avcodec_alloc_frame();

  if(pFrame == NULL || pFrameRGB==NULL)
    {
      Scierror (999, "%s: Can not allocate memory for video frame.\r\n", fname);
      return NULL;
    }    

  // Determine required buffer size and allocate buffer

  nMemSize=avpicture_get_size(PIX_FMT_RGB24, VdoFiles[nFile].pCodecCtx->width, VdoFiles[nFile].pCodecCtx->height);
  pBuffer=(unsigned char *) malloc(nMemSize);
  if(pBuffer == NULL)
    {
      Scierror (999, "%s: Can not allocate memory for video frame.\r\n", fname);
      return NULL;
    }    

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  avpicture_fill((AVPicture *)pFrameRGB, pBuffer, 
		 PIX_FMT_RGB24, 
		 VdoFiles[nFile].pCodecCtx->width, 
		 VdoFiles[nFile].pCodecCtx->height);

  //read the next frame
  while(1){
    nRet = av_read_frame(VdoFiles[nFile].pFormatCtx, &packet);
    if(nRet < 0) 
      goto NO_FRAME;


    // if it's a packet from the video stream
    if(packet.stream_index== VdoFiles[nFile].nVdoStream)
      {
	// Decode video frame
	avcodec_decode_video(VdoFiles[nFile].pCodecCtx, pFrame, &nFinished, packet.data, packet.size);
	
	// if we get a video frame
	if(nFinished)
	  {
	    // Convert the image format to RGB
	    img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, 
			(AVPicture*)pFrame, 
			VdoFiles[nFile].pCodecCtx->pix_fmt, 
			VdoFiles[nFile].pCodecCtx->width, 
			VdoFiles[nFile].pCodecCtx->height);

	    VdoFiles[nFile].nCurFrame++;

	    // Free the packet
	    av_free_packet(&packet);

	    break; //break the while loop
	  }
      }
    
  }


    // Free the frame
    av_free(pFrame);
    //the RGB image should be free out of this function

    return pFrameRGB;

 NO_FRAME:
    // Free the frame
    av_free(pFrame);
    // Free the RGB image
    free(pBuffer);
    av_free(pFrameRGB);

    return NULL;
}

int
int_vdoopen(char *fname)
{
  int mL, nL;
  int mR, nR, lR;
  int ret, *pret = &ret;
  
  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  ret = vdoopen(cstk(lR), fname);
  if(ret < 0)
    return -1;

  ret = ret+1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(2, "i", &mL, &nL, &pret);
  
  LhsVar(1) =2 ;
  return 0;
}

int
int_vdogetframe(char *fname)
{
  AVFrame * pFrameRGB;
  int mR, nR, lR;
  int nFile;

  unsigned char * pMatData;  

  CheckRhs(1,1);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR, &nR, &lR);
  CheckDims(1, mR, nR, 1, 1);

  nFile = *((int *)(istk(lR)));
  nFile = nFile - 1;

  if (!(nFile >= 0 && nFile < MAX_VDO_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_VDO_FILE_NUM);
      return -1;
    }
  if(! VdoFiles[nFile].bOpened)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use vdoshowopened command to show opened files.\r\n",
	       fname, nFile+1);
      return -1;
    }


  pFrameRGB = vdogetframe(nFile, fname);
  //if this is the last frame, or can not get a frame
  if(pFrameRGB == NULL)
    {
      return -2;
    }

  pMatData = (unsigned char *)malloc(VdoFiles[nFile].pCodecCtx->width * VdoFiles[nFile].pCodecCtx->height * 3);
  if(pMatData == NULL)
    {
      Scierror(999, "%s: Can not allocate memory for image matrix.\r\n", fname);
      return -1;
    }

  img2mat(pFrameRGB->data[0], pMatData, VdoFiles[nFile].pCodecCtx->width, VdoFiles[nFile].pCodecCtx->height, 3);

  if(Create3DIntMat(2, VdoFiles[nFile].pCodecCtx->height,  VdoFiles[nFile].pCodecCtx->width, 3, pMatData, I_UCHAR))
    {
      /*  Return variables  */
      LhsVar(1) = 2;
    }
  else
    {
      Scierror(999, "%s: Can not convert the image to a matrix.\r\n",fname);
    }


  // Free the RGB image
  free(pFrameRGB->data[0]);
  av_free(pFrameRGB);
  
  return 0;
}

int 
int_vdoshowopened(char * fname)
{
  int i;

  CheckRhs(0, 0);
  CheckLhs(0, 1);

  sciprint("Opened files:\r\n");
  for (i = 0; i < MAX_VDO_FILE_NUM; i++)
    {
      if(VdoFiles[i].bOpened==TRUE)
	{
	  sciprint("%d: %s\r\n", i+1, VdoFiles[i].filename);
	}
    }


}


int 
int_vdoclose(char *fname)
{
  int mR, nR, lR;
  int nFile;
  
  CheckRhs(1,1);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR, &nR, &lR);
  CheckDims(1, mR, nR, 1, 1);

  nFile = *((int *)(istk(lR)));
  nFile = nFile - 1;

  if (nFile >= 0 && nFile < MAX_VDO_FILE_NUM)
    {
      if(VdoFiles[nFile].bOpened)
	{
	  avcodec_close(VdoFiles[nFile].pCodecCtx);
	  av_close_input_file(VdoFiles[nFile].pFormatCtx);
	}
      
      memset(&(VdoFiles[nFile]), 0, sizeof(OpenedVdoFile));
    }
  else
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_VDO_FILE_NUM);
    }

}


int 
int_vdocloseall(char *fname)
{
  int i;

  CheckRhs(0, 0);
  CheckLhs(0, 1);

  for (i = 0; i < MAX_VDO_FILE_NUM; i++)
    {
      if(VdoFiles[i].bOpened)
	{
	  avcodec_close(VdoFiles[i].pCodecCtx);
	  av_close_input_file(VdoFiles[i].pFormatCtx);
	}
    }

  memset( &VdoFiles, 0, sizeof(OpenedVdoFile) * MAX_VDO_FILE_NUM);
}


