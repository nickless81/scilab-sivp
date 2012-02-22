/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2005,2010  Shiqi Yu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***********************************************************************/


#include "common.h"
#include "gw_sivp.h"

OpenedAvifileCap OpenedAviCap[MAX_AVI_FILE_NUM];


int int_aviinfo(char *fname)
{
  int mL, nL, lL;
  int mxL;

  int mR, nR, lR;
  int One = 1;
  int element = 0;
  static char *NameStr[]= { "V",
      "Filename",
      "FileSize",
      "FramesPerSecond",
      "Width",
      "Height",
      "NumFrames",
      "VideoCompression"  };
  char * pFilename;
  double fValue;
  double *pfValue = &fValue;
  int iValue;
  int *piValue = &iValue;

#ifdef WIN_SIVP
  struct _stat fileStat;
#else
  struct stat fileStat;
#endif

  CvCapture * pCapture = NULL;

  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  pFilename = cstk(lR);
  //open video file
  pCapture = cvCaptureFromFile(pFilename);

  //if failed to open the video file
  if(!pCapture)
    {
      Scierror(999, "%s: Can not open video file %s. Maybe the codec of the video can not be handled.\r\n", fname, pFilename);
      return -1;
    }
  /* This is a hack. If we don't call this first then getting capture
   * properties (below) won't work right. This is an OpenCV bug. We
   * ignore the return value here. But it's actually a video frame.
   */
  cvQueryFrame( pCapture );



  mL = 8;
  nL = 1;

  CreateVar(2,"m", &mL, &nL, &lL);

  CreateListVarFromPtr(2, ++element, "S", &mL, &nL, NameStr);
  //store file name
  //TODO: the path should be absolute path
  mxL = (int)strlen(cstk(lR));
  CreateListVarFromPtr(2, ++element, "c", &mxL, &One, &pFilename);

  //get the file size
#ifdef WIN_SIVP
  if( _stat(pFilename, &fileStat) != 0)
#else
  if( stat(pFilename, &fileStat) != 0)
#endif
    {
      Scierror(999, "%s: Can not get the information of file %s.\r\n", fname, pFilename);
      cvReleaseCapture(&pCapture);
      return -1;
    }
  fValue = (double)(fileStat.st_size);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  fValue = cvGetCaptureProperty(pCapture, CV_CAP_PROP_FPS);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  fValue = cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  fValue = cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  //go the last frame to determind the number of frames
  //sciprint("set position=%d", cvSetCaptureProperty( pCapture, CV_CAP_PROP_POS_AVI_RATIO, 1.0 )); #this lines sometimes do not works
  while(1)
    {
      if (cvGrabFrame(pCapture)==0)
  break;
    }
  fValue = cvGetCaptureProperty(pCapture, CV_CAP_PROP_POS_FRAMES);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  iValue = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FOURCC);
  mxL = 4;
  CreateListVarFromPtr(2, ++element, "c", &mxL, &One, (char**)(&piValue) );

  cvReleaseCapture(&pCapture);

  LhsVar(1) =2 ;
  return 0;
}


int int_camopen(char *fname)
{
  int mL, nL;
  int mR, nR, lR;
  int nCurrFile = 0;
  int *pret = &nCurrFile;

  int nCamIdx = -1;

  CheckRhs(0,1);
  CheckLhs(1,1);

  if(Rhs ==1)
    {
      GetRhsVar(1, "i", &mR, &nR, &lR);
      CheckDims(1, mR, nR, 1, 1);
      nCamIdx = *((int *)(istk(lR)));
    }


  for (nCurrFile = 0; nCurrFile < MAX_AVI_FILE_NUM; nCurrFile++)
    {
      if( !(OpenedAviCap[nCurrFile].video.cap))
  break;
    }

  if( nCurrFile ==  MAX_AVI_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files (or cameras) opened. Use aviclose or avicloseall to close some files (cameras).\r\n", fname);
      return -1;
    }


  OpenedAviCap[nCurrFile].video.cap = cvCaptureFromCAM(nCamIdx);
  if(OpenedAviCap[nCurrFile].video.cap == 0)
    {
      Scierror(999, "%s, Can not open the camera.\r\n", fname);
      return -1;
    }
  cvSetCaptureProperty(OpenedAviCap[nCurrFile].video.cap, CV_CAP_PROP_FRAME_WIDTH, 320);
  cvSetCaptureProperty(OpenedAviCap[nCurrFile].video.cap, CV_CAP_PROP_FRAME_HEIGHT, 240);
  cvSetCaptureProperty(OpenedAviCap[nCurrFile].video.cap, CV_CAP_PROP_FPS, 25);

  strncpy(OpenedAviCap[nCurrFile].filename, "camera", MAX_FILENAME_LENGTH);
  OpenedAviCap[nCurrFile].iswriter = 0;


  //the output is the opened index
  nCurrFile += 1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(2, "i", &mL, &nL, &pret);

  LhsVar(1) =2 ;
  return 0;
}

int int_aviopen(char *fname)
{
  int mL, nL;
  int mR, nR, lR;
  int nCurrFile = 0;
  int *pret = &nCurrFile;

  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  for (nCurrFile = 0; nCurrFile < MAX_AVI_FILE_NUM; nCurrFile++)
    {
      if( !(OpenedAviCap[nCurrFile].video.cap))
  break;
    }

  if( nCurrFile ==  MAX_AVI_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files (or cameras) opened. Use aviclose or avicloseall to close some files (cameras).\r\n", fname);
      return -1;
    }


  OpenedAviCap[nCurrFile].video.cap = cvCaptureFromFile(cstk(lR));
  if(OpenedAviCap[nCurrFile].video.cap == 0)
    {
      Scierror(999, "%s: Can not open video file %s. \nMaybe the codec of the video can not be handled or the file does not exist.\r\n", fname, cstk(lR));
      return -1;
    }

  OpenedAviCap[nCurrFile].iswriter = 0;
  strncpy(OpenedAviCap[nCurrFile].filename, cstk(lR), MAX_FILENAME_LENGTH);
  //the output is the opened index
  nCurrFile += 1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(2, "i", &mL, &nL, &pret);

  LhsVar(1) =2 ;
  return 0;
}

/* close an opened file */
int int_aviclose(char *fname)
{
  int mR, nR, lR;
  int nFile;

  CheckRhs(1,1);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR, &nR, &lR);
  CheckDims(1, mR, nR, 1, 1);

  nFile = *((int *)(istk(lR)));
  nFile = nFile - 1;

  if (nFile >= 0 && nFile < MAX_AVI_FILE_NUM)
    {
      if(OpenedAviCap[nFile].video.cap)
  {
    //if it is reader for video/camera
    if (! OpenedAviCap[nFile].iswriter)
      cvReleaseCapture(&(OpenedAviCap[nFile].video.cap));
    //if it is reader for video/camera
    else
      cvReleaseVideoWriter(&(OpenedAviCap[nFile].video.writer));

    memset(OpenedAviCap[nFile].filename, 0, sizeof(OpenedAviCap[nFile].filename) );
  }
      else
  {
    Scierror(999, "%s: The %d'th file is not opened.\r\n", fname, nFile+1);
  }
    }
  else
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
    }

  return 0;
}


/* close all opened files */
int int_avicloseall(char *fname)
{
  int i;

  CheckRhs(0, 0);
  CheckLhs(0, 1);

  for (i = 0; i < MAX_AVI_FILE_NUM; i++)
    {
      if(OpenedAviCap[i].video.cap)
  {
    //if it is reader for video/camera
    if (! OpenedAviCap[i].iswriter)
      cvReleaseCapture( &(OpenedAviCap[i].video.cap) );
    //if it is reader for video/camera
    else
      cvReleaseVideoWriter(&(OpenedAviCap[i].video.writer));

    memset(OpenedAviCap[i].filename, 0, sizeof(OpenedAviCap[i].filename) );
  }
    }

  return 0;
}



int int_avifile(char *fname)
{
  int mL, nL;
  int mR1, nR1, lR1;
  int mR2, nR2, lR2;
  int mR3, nR3, lR3;
  int nPos = 0;

  int nCurrFile = 0;
  int *pret = &nCurrFile;
  int nWidth, nHeight;
  int nFPS = 25;

  CheckRhs(2,3);
  CheckLhs(1,1);

  //get file name
  GetRhsVar(++nPos, "c", &mR1, &nR1, &lR1);

  //get dims
  GetRhsVar(++nPos, "i", &mR2, &nR2, &lR2);
  CheckDims(nPos, mR2, nR2, 2, 1);
  nWidth = *((int *)(istk(lR2)));
  nHeight = *(( (int *)(istk(lR2)) )+1);

  //get fps
  if(Rhs == 3)
    {
      GetRhsVar(++nPos, "i", &mR3, &nR3, &lR3);
      CheckDims(nPos, mR3, nR3, 1, 1);
      nFPS = *((int *)(istk(lR3)));
    }

  //find empty pointer
  for (nCurrFile = 0; nCurrFile < MAX_AVI_FILE_NUM; nCurrFile++)
    {
      if( !(OpenedAviCap[nCurrFile].video.writer))
  break;
    }

  if( nCurrFile ==  MAX_AVI_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files (or cameras) opened. Use aviclose or avicloseall to close some files (cameras).\r\n", fname);
      return -1;
    }


  OpenedAviCap[nCurrFile].video.writer = cvCreateVideoWriter(cstk(lR1),
                   CV_FOURCC('X','V','I','D'),
                   (double)nFPS,
                   cvSize(nWidth, nHeight),
                   1);
  if(OpenedAviCap[nCurrFile].video.writer == 0)
    {
      Scierror(999, "%s: Can not create video file %s.\r\n", fname, cstk(lR1));
      return -1;
    }

  strncpy(OpenedAviCap[nCurrFile].filename, cstk(lR1), MAX_FILENAME_LENGTH);
  OpenedAviCap[nCurrFile].iswriter = 1;
  OpenedAviCap[nCurrFile].width = nWidth;
  OpenedAviCap[nCurrFile].height = nHeight;

  //the output is the opened index
  nCurrFile += 1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(++nPos, "i", &mL, &nL, &pret);

  LhsVar(1) =nPos ;
  return 0;
}


/* read a frame from an opened video file*/
int int_addframe(char * fname)
{
  int mR1, nR1, lR1;

  int nFile;
  IplImage * pImage;

  CheckRhs(2,2);
  CheckLhs(1,1);

  //get opened file index
  GetRhsVar(1, "i", &mR1, &nR1, &lR1);
  CheckDims(1, mR1, nR1, 1, 1);
  nFile = *((int *)(istk(lR1)));
  nFile -= 1;

  //check whether the nFile'th is a video writer
  if (!(nFile >= 0 && nFile < MAX_AVI_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
      return -1;
    }

  if (! OpenedAviCap[nFile].iswriter )
    {
      Scierror(999, "%s: The opened file is not for writing.\r\n", fname);
      return -1;
    }

  if(! OpenedAviCap[nFile].video.writer)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use avilistopened command to show opened files.\r\n",
         fname, nFile+1);
      return -1;
    }

  //load the input image
  pImage = Mat2IplImg(2);

  if(pImage == NULL)
    {
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);
      return -1;
    }
  //only UINT8 images are supported by cvWriteFrame
  if(pImage->depth != IPL_DEPTH_8U)
    {
      cvReleaseImage(&pImage);
      Scierror(999, "%s: The input image must be UINT8.\r\n", fname);
      return -1;
    }

  //if the input frame is not the same size as pre-defined video writer
  //resize the input image
  if(pImage->width != OpenedAviCap[nFile].width
     ||pImage->height != OpenedAviCap[nFile].height)
    {
      IplImage * pTmp = cvCreateImage(cvSize(OpenedAviCap[nFile].width,
               OpenedAviCap[nFile].height),
              IPL_DEPTH_8U,
              pImage->nChannels);
      if(!pTmp)
  {
    cvReleaseImage(&pImage);
    Scierror(999, "%s: Can not alloc memory.\r\n", fname);
    return -1;
  }
      cvResize(pImage, pTmp, CV_INTER_LINEAR);

      cvReleaseImage(&pImage);
      pImage = pTmp;
    }

  if( cvWriteFrame(OpenedAviCap[nFile].video.writer, pImage) != 0)
    {
      Scierror(999, "%s: Write frame error, please check input image size and depth.\r\n", fname);
      return -1;
    }

  LhsVar(1) = 1;

  cvReleaseImage(&pImage);
  return 0;
}

/* read a frame from an opened video file*/
int int_avireadframe(char * fname)
{
  int mR1, nR1, lR1;
  int mR2, nR2, lR2;

  int nFile;
  int nFrameIdx = -1;

  IplImage * pImage;

  double tmp;

  CheckRhs(1,2);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR1, &nR1, &lR1);
  CheckDims(1, mR1, nR1, 1, 1);
  if(Rhs == 2)
    {
      GetRhsVar(2, "i", &mR2, &nR2, &lR2);
      CheckDims(2, mR2, nR2, 1, 1);

      nFrameIdx = *((int *)(istk(lR2)));
      nFrameIdx -= 1;
    }

  nFile = *((int *)(istk(lR1)));
  nFile -= 1;

  if (!(nFile >= 0 && nFile < MAX_AVI_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
      return -1;
    }

  if ( OpenedAviCap[nFile].iswriter )
    {
      Scierror(999, "%s: The opened file is for writing.\r\n", fname);
      return -1;
    }


  if(! OpenedAviCap[nFile].video.cap)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use avilistopened command to show opened files.\r\n",
         fname, nFile+1);
      return -1;
    }
  if(Rhs ==2 && nFrameIdx < 0)
    {
      Scierror(999, "%s: The frame index should >=1, but your input is %d.\r\n", fname, nFrameIdx+1);
      return -1;
    }


  if(nFrameIdx >=0)
    cvSetCaptureProperty( OpenedAviCap[nFile].video.cap, CV_CAP_PROP_POS_FRAMES, nFrameIdx);

  pImage = cvQueryFrame(OpenedAviCap[nFile].video.cap);

  if (! pImage)
  {
      Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
  }
  else if(! IplImg2Mat(pImage, Rhs+1))
    {
      Scierror(999, "%s: SIVP interal error.\r\n", fname);
      return -1;
    }

  LhsVar(1) = Rhs+1;

  //pImage can not be released!!

  return 0;
}


//TODL: list filenames
int int_avilistopened(char * fname)
{
  int One = 1;
  int i;

  int count = 0;
  int offset = 0;

  double dIndices[MAX_AVI_FILE_NUM];
  double * dIdx = dIndices;
  char sFileNames[MAX_AVI_FILE_NUM * MAX_FILENAME_LENGTH];
  char * sFN = sFileNames;

  CheckRhs(0, 0);
  CheckLhs(1, 1);

  for (i = 0; i < MAX_AVI_FILE_NUM; i++)
    {
      if(OpenedAviCap[i].video.cap)
  {
    dIndices[count]=i+1;

      //strcpy(sFileNames[count],  OpenedAviCap[i].filename, MAX_FILENAME_LENGTH);
      strncpy(sFileNames+offset, OpenedAviCap[i].filename, MAX_FILENAME_LENGTH);
    offset += (int)strlen(OpenedAviCap[i].filename)+1;
    count++;
  }
    }


  CreateVarFromPtr(1, "d", &count, &One, &dIdx);

  LhsVar(1) =1;

  return 0;
}
