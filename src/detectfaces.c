/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2008  Shiqi Yu
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

/**********************************************************************
 * this function only supports UINT8
 * [faces]=detectfaces(im);
 * faces is a Nx4 matrix.
 * each row of faces is a face location [x,y,w,h]
 **********************************************************************/

int int_detectfaces(char * fname)
{
  static CvHaarClassifierCascade* pCascade = NULL;

  CvMemStorage* pStorage = NULL;
  IplImage * pSrcImg = NULL;
  IplImage * pGray = NULL;
  CvSeq    * pFaces = NULL;
  double     tmp;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  //load haar cascade xml file
  if(!pCascade)
    pCascade = (CvHaarClassifierCascade*)cvLoad( "/home/yushiqi/sivp/sivp/etc/haarcascade_frontalface_alt2.xml", 0, 0, 0 );
  
  if( !pCascade )
    {
      Scierror(999, "%s: Failed to load face haar cascade file.\r\n", fname);
      return -1;
    }

  //load the input image
  pSrcImg = Mat2IplImg(1);
  if(pSrcImg == NULL)
    {
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);
      return -1;
    }
  if(pSrcImg->depth != IPL_DEPTH_8U)
    {
      cvReleaseImage(&pSrcImg);
      Scierror(999, "%s: Only 8-bit unsigned image is supported.\r\n", fname);
      return -1;
    }

  //create memory storage needed by face detector
  pStorage = cvCreateMemStorage(0);
  if(!pStorage)
    {
      cvReleaseImage(&pSrcImg);
      Scierror(999, "%s: Can not create memory storage for detector.\r\n", fname);
      return -1;
    }

  //convert the input image to gray
  pGray = cvCreateImage( cvSize(pSrcImg->width,pSrcImg->height), pSrcImg->depth, 1 );
  if( pGray == NULL )
    {
      cvReleaseImage(&pSrcImg);
      cvReleaseMemStorage(&pStorage);
      Scierror(999, "%s: Can not create image for detection.\r\n", fname);
      return -1;
    }
  if( pSrcImg->nChannels == 1)
    {
      cvCopy(pSrcImg, pGray, NULL);
    }
  else
    {
      cvCvtColor(pSrcImg, pGray, CV_BGR2GRAY);
    }


  pFaces = cvHaarDetectObjects( pGray, pCascade, pStorage,
                                            1.1, 3, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );

  //copy face locations to output matrix
  if(pFaces == NULL)
    {
      Create2DDoubleMat(Rhs+1, 0, 0, &tmp); //return []
    }
  else
    {
      if(pFaces->total == 0)
	{
	  Create2DDoubleMat(Rhs+1, 0, 0, &tmp); //return []
	}
      else
	{
	  int idx;
	  
	  IplImage * pLocations = cvCreateImage(cvSize(4, pFaces->total),
						IPL_DEPTH_64F, 1);

	  for( idx = 0; idx < (pFaces ? pFaces->total : 0); idx++ )
	    {
	      CvRect* r = (CvRect*)cvGetSeqElem( pFaces, idx );
	      CV_IMAGE_ELEM(pLocations, double, idx, 0) = r->x;
	      CV_IMAGE_ELEM(pLocations, double, idx, 1) = r->y;
	      CV_IMAGE_ELEM(pLocations, double, idx, 2) = r->width;
	      CV_IMAGE_ELEM(pLocations, double, idx, 3) = r->height;
	    }
	  IplImg2Mat(pLocations, Rhs+1);
	  cvReleaseImage(&pLocations);
	}
    }

  
  LhsVar(1) = Rhs+1;


  cvReleaseMemStorage(&pStorage);
  cvReleaseImage(&pSrcImg);
  cvReleaseImage(&pGray);
}
