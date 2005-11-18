/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2005  Shiqi Yu
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

int
int_aviinfo(char *fname)
{
  int mL, nL, lL;
  int mxL, nxL;

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
  mxL = strlen(cstk(lR));
  CreateListVarFromPtr(2, ++element, "c", &mxL, &One, &pFilename);

  //get the file size
  struct stat fileStat;
  if( stat(pFilename, &fileStat) != 0)
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
