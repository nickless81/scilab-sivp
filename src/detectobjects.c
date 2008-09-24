/*****************************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2008  Jia Wu
 * Copyright (C) 2008  Shiqi Yu (shiqi.yu@gmail.com)
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

/**********************************************************************
 * this function only supports UINT8
 * [objects]=detectobjects(im, xmlfile);
 * objects is a Nx4 matrix.
 * each row of objects is an object location [x,y,w,h]
 **********************************************************************/

int int_detectobjects(char * fname)
{
  static CvHaarClassifierCascade* pCascade = NULL;
  static char xmlname[MAX_FILENAME_LENGTH];

  int mR, nR, lR;

  CvMemStorage* pStorage = NULL;
  IplImage * pSrcImg = NULL;
  IplImage * pGray = NULL;
  CvSeq    * pObjects = NULL;
  char       sFileName[MAX_FILENAME_LENGTH];
  double     tmp;

  CheckRhs(2, 2);
  CheckLhs(1, 1);

  GetRhsVar(2, "c", &mR, &nR, &lR); 
  
  //load haar cascade xml file
  if( !pCascade )
   {
     sprintf(xmlname, "%s", cstk(lR));
     sprintf(sFileName,"%s/etc/%s", sSIVP_PATH, xmlname);
     pCascade = (CvHaarClassifierCascade*)cvLoad( sFileName, 0, 0, 0 );
   }
  else if(strncmp(xmlname, cstk(lR), MAX_FILENAME_LENGTH) != 0) 
  {
     cvReleaseHaarClassifierCascade(&pCascade);
     
     sprintf(xmlname, "%s", cstk(lR));
     sprintf(sFileName,"%s/etc/%s", sSIVP_PATH, xmlname);
     pCascade = (CvHaarClassifierCascade*)cvLoad( sFileName, 0, 0, 0 );
   } 

  if( !pCascade )
    {
      Scierror(999, "%s: Failed to load object haar cascade file %s.\r\n", fname, sFileName);
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

  //create memory storage needed by object detector
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


  pObjects = cvHaarDetectObjects( pGray, pCascade, pStorage,
                                            1.1, 3, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(20, 20) );

  //copy object locations to output matrix
  if(pObjects == NULL)
    {
      Create2DDoubleMat(Rhs+1, 0, 0, &tmp); //return []
    }
  else
    {
      if(pObjects->total == 0)
	{
	  Create2DDoubleMat(Rhs+1, 0, 0, &tmp); //return []
	}
      else
	{
	  int idx;
	  
	  IplImage * pLocations = cvCreateImage(cvSize(4, pObjects->total),
						IPL_DEPTH_64F, 1);

	  for( idx = 0; idx < (pObjects ? pObjects->total : 0); idx++ )
	    {
	      CvRect* r = (CvRect*)cvGetSeqElem( pObjects, idx );
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
