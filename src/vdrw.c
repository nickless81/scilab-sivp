#include "common.h"

#define MAX_VD_FILE_NUM 32

typedef struct OpenedVDfFile{
  char filename[FILENAME_MAX];
  AVFormatContext *pFormatCtx;
  AVCodecContext  *pCodecCtx;
  AVCodec         *pCodec;
  int nVdStream; //video stream index
  unsigned long  nCurFrame;
  BOOL bOpened;
} OpenedVdFile;
  
static OpenedVdFile VdFiles[MAX_VD_FILE_NUM];

int
vdopen(char * filename, char * fname)
{
  int nCurrFile;
  int i;
  static int inited = 0;
  
  /* init  */
  if(!inited)
    {
      memset(&VdFiles, 0, sizeof(VdFiles));
      inited = 1;
    }

  for (nCurrFile = 0; nCurrFile < MAX_VD_FILE_NUM; nCurrFile++)
    {
      if( !VdFiles[nCurrFile].bOpened)
	break;
    }

  if( nCurrFile ==  MAX_VD_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files opened. Use vdclose or vdcloseall to close some file.\r\n", fname);
      return -1;
    }

  // Register all formats and codecs
  av_register_all ();

  strcpy(VdFiles[nCurrFile].filename, filename);

  // Open video file
  if (av_open_input_file (&(VdFiles[nCurrFile].pFormatCtx), filename, NULL, 0, NULL) != 0)
    {
      Scierror(999, "%s: Couldn't open file %s. Maybe this file does not exist.\r\n", fname, filename);
      return -1;		// Couldn't open file
    }
  

  // Retrieve stream information
  if (av_find_stream_info( VdFiles[nCurrFile].pFormatCtx ) < 0)
    {
      av_close_input_file(VdFiles[nCurrFile].pFormatCtx);
      Scierror(999, "%s: Couldn't find steam information.\r\n", fname);
      return -1;		// Couldn't find stream information
    }
  

  // Find the first video stream
  VdFiles[nCurrFile].nVdStream = -1;
  for (i = 0; i < VdFiles[nCurrFile].pFormatCtx->nb_streams; i++)
    if (VdFiles[nCurrFile].pFormatCtx->streams[i]->codec.codec_type == CODEC_TYPE_VIDEO)
      {
	 VdFiles[nCurrFile].nVdStream = i;
	break;
      }
  
  // Can't find a video stream
  if ( VdFiles[nCurrFile].nVdStream == -1)
    {
      av_close_input_file(VdFiles[nCurrFile].pFormatCtx);
      Scierror (999, "%s: No video stream in this file.\r\n", fname);
      return -1;
    }

  // Get a pointer to the codec context for the video stream
  VdFiles[nCurrFile].pCodecCtx = &(VdFiles[nCurrFile].pFormatCtx->streams[VdFiles[nCurrFile].nVdStream]->codec);
				    
  // Find the decoder for the video stream
  VdFiles[nCurrFile].pCodec = avcodec_find_decoder (VdFiles[nCurrFile].pCodecCtx->codec_id);
  if (VdFiles[nCurrFile].pCodec == NULL)
    {
      av_close_input_file(VdFiles[nCurrFile].pFormatCtx );
      Scierror(999, "%s: No codec for this video file.\r\n", fname);
      return -1;
    }

  // Open the codec
  if(avcodec_open(VdFiles[nCurrFile].pCodecCtx, VdFiles[nCurrFile].pCodec)<0)
    {
      av_close_input_file(VdFiles[nCurrFile].pFormatCtx );
      Scierror(999, "%s: Can not open the codec for this video file.\r\n", fname);
      return -1; 
    }

				    
  if( VdFiles[nCurrFile].pCodecCtx->frame_rate > 1000 
      && VdFiles[nCurrFile].pCodecCtx->frame_rate_base == 1 )
    {
      VdFiles[nCurrFile].pCodecCtx->frame_rate_base = 1000;
    }

  VdFiles[nCurrFile].bOpened = TRUE;
  
  return nCurrFile;

}

AVFrame *
vdgetframe(int nFile, char *fname)
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

  nMemSize=avpicture_get_size(PIX_FMT_RGB24, VdFiles[nFile].pCodecCtx->width, VdFiles[nFile].pCodecCtx->height);
  pBuffer=(unsigned char *) malloc(nMemSize);
  if(pBuffer == NULL)
    {
      Scierror (999, "%s: Can not allocate memory for video frame.\r\n", fname);
      return NULL;
    }    

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  avpicture_fill((AVPicture *)pFrameRGB, pBuffer, 
		 PIX_FMT_RGB24, 
		 VdFiles[nFile].pCodecCtx->width, 
		 VdFiles[nFile].pCodecCtx->height);

  //read the next frame
  while(1){
    nRet = av_read_frame(VdFiles[nFile].pFormatCtx, &packet);
    if(nRet < 0) 
      goto NO_FRAME;


    // if it's a packet from the video stream
    if(packet.stream_index== VdFiles[nFile].nVdStream)
      {
	// Decode video frame
	avcodec_decode_video(VdFiles[nFile].pCodecCtx, pFrame, &nFinished, packet.data, packet.size);
	
	// if we get a video frame
	if(nFinished)
	  {
	    // Convert the image format to RGB
	    img_convert((AVPicture *)pFrameRGB, PIX_FMT_RGB24, 
			(AVPicture*)pFrame, 
			VdFiles[nFile].pCodecCtx->pix_fmt, 
			VdFiles[nFile].pCodecCtx->width, 
			VdFiles[nFile].pCodecCtx->height);

	    VdFiles[nFile].nCurFrame++;

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
int_vdopen(char *fname)
{
  int mL, nL;
  int mR, nR, lR;
  int ret, *pret = &ret;
  
  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  ret = vdopen(cstk(lR), fname);
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
int_vdgetframe(char *fname)
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

  if (!(nFile >= 0 && nFile < MAX_VD_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_VD_FILE_NUM);
      return -1;
    }
  if(! VdFiles[nFile].bOpened)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use vdshowopened command to show opened files.\r\n",
	       fname, nFile+1);
      return -1;
    }


  pFrameRGB = vdgetframe(nFile, fname);
  //if this is the last frame, or can not get a frame, return zero
  if(pFrameRGB == NULL)
    {
      int iOne=1;
      double dL =0.0, *pdL = &dL;
      double dZero=0.0;
      CreateVarFromPtr(2,"d", &iOne, &iOne, &pdL);
      LhsVar(1) = 2;
      return 2;
    }

  pMatData = (unsigned char *)malloc(VdFiles[nFile].pCodecCtx->width * VdFiles[nFile].pCodecCtx->height * 3);
  if(pMatData == NULL)
    {
      Scierror(999, "%s: Can not allocate memory for image matrix.\r\n", fname);
      return -1;
    }

  img2mat(pFrameRGB->data[0], pMatData, VdFiles[nFile].pCodecCtx->width, VdFiles[nFile].pCodecCtx->height, 3);

  if(Create3DIntMat(2, VdFiles[nFile].pCodecCtx->height,  VdFiles[nFile].pCodecCtx->width, 3, pMatData, I_UCHAR))
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
int_vdshowopened(char * fname)
{
  int i;

  CheckRhs(0, 0);
  CheckLhs(0, 1);

  sciprint("Opened files:\r\n");
  for (i = 0; i < MAX_VD_FILE_NUM; i++)
    {
      if(VdFiles[i].bOpened==TRUE)
	{
	  sciprint("%d: %s\r\n", i+1, VdFiles[i].filename);
	}
    }


}


int 
int_vdclose(char *fname)
{
  int mR, nR, lR;
  int nFile;
  
  CheckRhs(1,1);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR, &nR, &lR);
  CheckDims(1, mR, nR, 1, 1);

  nFile = *((int *)(istk(lR)));
  nFile = nFile - 1;

  if (nFile >= 0 && nFile < MAX_VD_FILE_NUM)
    {
      if(VdFiles[nFile].bOpened)
	{
	  avcodec_close(VdFiles[nFile].pCodecCtx);
	  av_close_input_file(VdFiles[nFile].pFormatCtx);
	}
      
      memset(&(VdFiles[nFile]), 0, sizeof(OpenedVdFile));
    }
  else
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_VD_FILE_NUM);
    }

}


int 
int_vdcloseall(char *fname)
{
  int i;

  CheckRhs(0, 0);
  CheckLhs(0, 1);

  for (i = 0; i < MAX_VD_FILE_NUM; i++)
    {
      if(VdFiles[i].bOpened)
	{
	  avcodec_close(VdFiles[i].pCodecCtx);
	  av_close_input_file(VdFiles[i].pFormatCtx);
	}
    }

  memset( &VdFiles, 0, sizeof(OpenedVdFile) * MAX_VD_FILE_NUM);
}
