/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2006  Shiqi Yu
 * Copyright (C) 2005  Vincent Etienne
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
 * BW = sobel(im, dx, dy, thresh)
 * [BW,thresh] = sobel(im, ...)
 **********************************************************************/
int int_sobel(char *fname)
{
  static int One=1;
  static int l2, m2, n2, l3, m3, n3, l4, m4, n4 ;

  //create variable for parameters
  double *pfThresh=NULL;
  double fThresh = -1.0;
  int *pnDx=NULL;
  int *pnDy=NULL;
  
  IplImage* pSrcImg = NULL;
  IplImage* pSobelImg = NULL;
  IplImage* pEdgeImg = NULL;

  CheckRhs(3,4);
  CheckLhs(1,2);


  GetRhsVar(2, "i", &m2, &n2, &l2);
  GetRhsVar(3, "i", &m3, &n3, &l3);
  // check if arg are scalaire
  if (m2*n2 != 1 || m3*n3 != 1) 
    {
      Scierror(999, "Internal eroror: %s: arguments must be scalars.\r\n", fname);
      return 0;
    }
  //receive the data
  pnDx =  istk(l2);
  pnDy =  istk(l3);

  if( Rhs == 4)
    {
      GetRhsVar(4, "d", &m4, &n4, &l4);
      // check if arg are scalaire
      if ( m4*n4 != 1) 
	{
	  Scierror(999, "Internal eroror: %s: arguments must be scalars.\r\n", fname);
	  return 0;
	}
      pfThresh = stk(l4);
      //check the values
      if(pfThresh[0]< 0)
	{
	  Scierror(999, "Internal eroror: %s: thresh should greater than zero. \r\n", fname);
	  return 0;
	}
    }
  else
    {
      pfThresh = &fThresh; //the value is -1 to indicate 
                           //that the thresh should be choosen in this function
    }



  if ( (pnDx[0]>2) || (pnDx[0]<0) || (pnDy[0]>2)|| (pnDy[0]<0))
    {
      Scierror(999, "Internal eroror: %s: The direction should be 0 or 1.\r\n", fname);
      return 0;
    }


  //load the input image
  pSrcImg = Mat2IplImg(1);
  
  // check if input image is correctly loaded
  if(pSrcImg == NULL)
    {
      Scierror(999, "%s: Can not get the image.\r\n", fname);
      return 0;
    }

  //the image must be gray image
  if(! ((pSrcImg->depth==IPL_DEPTH_8U)  &&  (pSrcImg->nChannels==1)) )
    {
      cvReleaseImage(&pSrcImg);
      Scierror(999, "%s: The input image must be gray image.\r\n", fname);
      return 0;
    }

  
  //create the output image for cvSobel
  pSobelImg = cvCreateImage(cvGetSize(pSrcImg), IPL_DEPTH_16S, 1);
  // check if the output image is correctly created
  if(pSobelImg == NULL)
    {
      cvReleaseImage(&pSrcImg);
      Scierror(999, "%s: Can't create images.\r\n", fname);
      return 0;
    }
   
  //Sobel operate
  cvSobel( pSrcImg, pSobelImg , pnDx[0], pnDy[0], 3);
  
  pEdgeImg = cvCreateImage(cvGetSize(pSrcImg), IPL_DEPTH_8U, 1);
  // check if the output image is correctly created
  if(pEdgeImg == NULL)
    {
      cvReleaseImage(&pSrcImg);
      cvReleaseImage(&pSobelImg);
      Scierror(999, "%s: Can't create images.\r\n", fname);
      return 0;
    }

  //convert the sobel image to [0,255] 8bits image
  //the range of the sobel image is[-4x255, 4x255]
  cvConvertScaleAbs(pSobelImg, pEdgeImg, 0.25, 0);

  //choose the thresh value if the user does not specified the value
  if(pfThresh[0] < 0)
    {
      double fMin, fMax;
      cvMinMaxLoc(pEdgeImg, &fMin, &fMax, NULL, NULL, NULL);
      pfThresh[0] = cvRound(( 3*fMin/4.0 + fMax/4.0)*4) ;
    }

  //threshold
  cvThreshold(pEdgeImg, pEdgeImg, pfThresh[0]/4.0, 255, CV_THRESH_BINARY);

  
  //translate IplImage to Matrix
  IplImg2Mat(pEdgeImg, 5);
  CreateVarFromPtr( 6, "d", &One, &One, &pfThresh);

  //send the result
  LhsVar(1)=5;
  LhsVar(2)=6;

  //release all images
  cvReleaseImage(&pSrcImg);
  cvReleaseImage(&pSobelImg);
  cvReleaseImage(&pEdgeImg);

  return 0;

}
