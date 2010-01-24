/*****************************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2008  Jia Wu
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
 *****************************************************************************/

#include "common.h"

/*********************************************************************************************
 * this function only supports 3-channel image, and uses hue histogram to calc back projection
 * [object]=camshift(im) or [object]=camshift(im,window)
 * object is a 1x5 matrix of the object window and object orientation [x,y,w,h,theta]
 * window is a 1x4 matrix of the initial search window [x,y,w,h]
 *********************************************************************************************/

int int_camshift(char *fname)
{
  static CvHistogram *pHist = NULL;
  static CvRect object_window;

  IplImage *pSrcImage = NULL;
  IplImage *pHSVImage = NULL;
  IplImage *pHueImage = NULL;
  IplImage *pMask = NULL;

  IplImage *pObject = NULL;
  CvConnectedComp comp;
  CvBox2D box;

  CheckRhs(1, 2);
  CheckLhs(1, 1); 

  //load the input image
  pSrcImage = Mat2IplImg(1);
  if(pSrcImage == NULL)
   {
     Scierror(999, "%s: Can not get the image data.\r\n", fname);
     return -1;
   }
  if(pSrcImage->nChannels != 3)
  {
     cvReleaseImage(&pSrcImage);
     Scierror(999, "%s: Only 3-channel image is supported.\r\n", fname);
     return -1;
  }

  pHSVImage = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 3);
  if(pHSVImage == NULL)
   {
     cvReleaseImage(&pSrcImage);
     Scierror(999, "%s: Can not create hsv image.\r\n", fname);
     return -1;
   }
  pHueImage = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 1);
  if(pHueImage == NULL)
   {
     cvReleaseImage(&pSrcImage);
     cvReleaseImage(&pHSVImage);
     Scierror(999, "%s: Can not create hue image.\r\n", fname);
     return -1;
   }
  pMask = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 1);
  if(pMask == NULL)
   {
     cvReleaseImage(&pSrcImage);
     cvReleaseImage(&pHSVImage);
     cvReleaseImage(&pHueImage);
     Scierror(999, "%s: Can not create mask image.\r\n", fname);
     return -1;
   }

  //convert the input RGB image to HSV image
  cvCvtColor(pSrcImage, pHSVImage, CV_BGR2HSV);
  cvSplit(pHSVImage, pHueImage, 0, 0, 0);

  cvInRangeS(pHSVImage, cvScalar(0, 30, 10, 0), cvScalar(180, 256, 256, 0), pMask);

  pObject = cvCreateImage(cvSize(5, 1), IPL_DEPTH_64F, 1);
  if(pObject == NULL)
  {
     cvReleaseImage(&pSrcImage);
     cvReleaseImage(&pHSVImage);
     cvReleaseImage(&pHueImage);
     cvReleaseImage(&pMask);
     Scierror(999, "%s: Can not allocate memory.\r\n", fname);
     return -1;
  }

  //object tracking
  if(Rhs == 1)
   {
    IplImage *pBPImage = NULL;
    
    if(pHist == NULL)
     {
      cvReleaseImage(&pSrcImage);
      cvReleaseImage(&pHSVImage);
      cvReleaseImage(&pHueImage);
      cvReleaseImage(&pMask);
      cvReleaseImage(&pObject);
      Scierror(999, "%s: Object histogram not initialized. Please input a window to initialize the tracker.\r\n", fname);
      return -1;
     }

    pBPImage = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 1);
    if(pBPImage == NULL)
     {
      cvReleaseImage(&pSrcImage);
      cvReleaseImage(&pHSVImage);
      cvReleaseImage(&pHueImage);
      cvReleaseImage(&pMask);
      cvReleaseImage(&pObject);
      Scierror(999, "%s: Can not create backproject image.\r\n", fname);
      return -1;
     }
    //calculate backproject image
    cvCalcBackProject(&pHueImage, pBPImage, pHist);
    cvAnd(pBPImage, pMask, pBPImage, 0);

    //camshift tracking
    cvCamShift(pBPImage, object_window, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1), &comp, &box); 
    //object window
    object_window = comp.rect;
    cvReleaseImage(&pBPImage);
   }
  //object initialization
  else if(Rhs == 2)
  {
    IplImage *pWindow = Mat2IplImg(2);
    CvRect rect;

    int dimension = 1;
    int h_bins = 20;
    int hist_size[] = {h_bins};
    float h_range[] = {0, 180};
    float *range[] = {h_range};

    if(pWindow == NULL)
     {      
       cvReleaseImage(&pSrcImage);
       cvReleaseImage(&pHSVImage);
       cvReleaseImage(&pHueImage);
       cvReleaseImage(&pMask);
       cvReleaseImage(&pObject);        
       Scierror(999, "%s: Can not get the initial window data.\r\n", fname);
       return -1;
     }

    rect.x = CV_IMAGE_ELEM(pWindow, double, 0, 0)-1;
    rect.y = CV_IMAGE_ELEM(pWindow, double, 0, 1)-1;
    rect.width = CV_IMAGE_ELEM(pWindow, double, 0, 2);
    rect.height = CV_IMAGE_ELEM(pWindow, double, 0, 3);
    cvReleaseImage(&pWindow);

    if(rect.x<0 || rect.y<0 || rect.width<0 || rect.height<0 || rect.x+rect.width>pSrcImage->width ||
       rect.y+rect.height>pSrcImage->height)
     {
       cvReleaseImage(&pSrcImage);
       cvReleaseImage(&pHSVImage);
       cvReleaseImage(&pHueImage);
       cvReleaseImage(&pMask);
       cvReleaseImage(&pObject);        
       Scierror(999, "%s: Improper initial window. Please Input an initial window with right position and size.\r\n", fname);
       return -1;
      }

    //search window
    object_window = rect;
    box.angle = 0;

    //create histogram
    if(pHist == NULL)
       pHist = cvCreateHist(1, hist_size, CV_HIST_ARRAY, range, 1);     

    cvSetImageROI(pHueImage, rect);
    cvSetImageROI(pMask, rect);
    //calculate the hue histogram
    cvCalcHist(&pHueImage, pHist, 0, pMask);
    cvResetImageROI(pHueImage);   
    cvResetImageROI(pMask); 
   }  

  CV_IMAGE_ELEM(pObject, double, 0, 0) = object_window.x+1;
  CV_IMAGE_ELEM(pObject, double, 0, 1) = object_window.y+1;
  CV_IMAGE_ELEM(pObject, double, 0, 2) = object_window.width;
  CV_IMAGE_ELEM(pObject, double, 0, 3) = object_window.height;
  CV_IMAGE_ELEM(pObject, double, 0, 4) = box.angle;
  IplImg2Mat(pObject, Rhs+1); 

  LhsVar(1) = Rhs+1;  

  cvReleaseImage(&pSrcImage);
  cvReleaseImage(&pHSVImage);
  cvReleaseImage(&pHueImage);
  cvReleaseImage(&pMask);
  cvReleaseImage(&pObject);

  return 0; 
}
