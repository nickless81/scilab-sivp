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

/**********************************************************************
 * imout=imresize(imin, scale);
 * imout=imresize(imin, scale, interp);
 * imout=imresize(imin, [mrows ncols]);
 * imout=imresize(imin, [mrows ncols], interp);
 *
 * interp = 'nearest', 'bilinear', 'bicubic' or 'area'
 **********************************************************************/
int int_imresize(char * fname)
{

  int mR1, nR1, lR1;
  int mR2, nR2, lR2;
  int mR3, nR3, lR3;

  IplImage* pSrcImg = NULL;
  IplImage* pDstImg = NULL;
  int Interpolation = CV_INTER_NN; //Interpolation method, default method is nearest neigbor
  int nDestW = 0, nDestH = 0;

  CheckRhs(2, 3);
  CheckLhs(1, 1);

  //descided which interpolation method to use
  if( Rhs == 3)
    {
      GetRhsVar(3, "c",  &mR3, &nR3, &lR3);

      if( strcmp(cstk(lR3), "nearest") == 0)
	Interpolation = CV_INTER_NN;
      else if( strcmp(cstk(lR3), "bilinear") == 0)
	Interpolation = CV_INTER_LINEAR;
      else if( strcmp(cstk(lR3), "bicubic") == 0)
	Interpolation = CV_INTER_CUBIC;
      else if( strcmp(cstk(lR3), "area") == 0)
	Interpolation = CV_INTER_AREA;
      else
	{
	  Scierror(999, "%s: Interpolation method '%s' is not supported.\r\nSee the help page of %s for detailed information.\r\n", fname, cstk(lR3), fname);
	  return -1;
	}
    }

  //load the input image
  pSrcImg = Mat2IplImg(1);
  if(pSrcImg == NULL)
    {
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);
      return -1;
    }

  //descided the size for destination image
  GetRhsVar(2, "d", &mR2, &nR2, &lR2);
  if(mR2 == 1 && nR2 == 1)
    {
      nDestW = cvRound(pSrcImg->width * stk(lR2)[0]);
      nDestH = cvRound(pSrcImg->height * stk(lR2)[0]);
    }
  else if(mR2 * nR2 == 2)
    {
      nDestW = cvRound(stk(lR2)[1]);
      nDestH = cvRound(stk(lR2)[0]);
    }
  else
    {
      Scierror(999, "%s: The second parameter should be a double value or 1X2 vector.\r\n", fname);
      cvReleaseImage(&pSrcImg);
      return -1;
    }
  //check whether the width and height of destination image is valid.
  if(nDestW <=0 || nDestH <=0)
    {
      Scierror(999, "%s: The scaled image size is invalid.\r\n", fname);
      cvReleaseImage(&pSrcImg);
      return -1;
    }

  pDstImg = cvCreateImage(cvSize(nDestW, nDestH), pSrcImg->depth, pSrcImg->nChannels);

  if(pDstImg == NULL)
    {
      Scierror(999, "%s: Internal error for allocating memory.\r\n", fname);
      cvReleaseImage(&pSrcImg);
      return -1;
    }

  cvResize(pSrcImg, pDstImg, Interpolation);

  
  IplImg2Mat(pDstImg, Rhs+1);
  LhsVar(1) = Rhs+1;

  cvReleaseImage(&pSrcImg);
  cvReleaseImage(&pDstImg);
  return 0;
}
