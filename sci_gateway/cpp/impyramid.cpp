/*******************************************************************************
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
 *******************************************************************************/

#include "common.h"

int int_impyramid(char *fname)
{
   int mR, nR, lR;

   IplImage *pSrcImg = NULL;
   IplImage *pDstImg = NULL;

   CheckRhs(2, 2);
   CheckLhs(1, 1);

   //load the input image
   pSrcImg = Mat2IplImg(1);
   if(pSrcImg == NULL)
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);

   GetRhsVar(2, "c", &mR, &nR, &lR);
   if(strcmp(cstk(lR), "reduce") == 0)
    {
      pDstImg = cvCreateImage(cvSize(ceil(pSrcImg->width/2), ceil(pSrcImg->height/2)), pSrcImg->depth, pSrcImg->nChannels);
      cvPyrDown(pSrcImg, pDstImg, CV_GAUSSIAN_5x5);
    }
   else if(strcmp(cstk(lR), "expand") == 0)
    {
      pDstImg = cvCreateImage(cvSize(2*pSrcImg->width, 2*pSrcImg->height), pSrcImg->depth, pSrcImg->nChannels);
      cvPyrUp(pSrcImg, pDstImg, CV_GAUSSIAN_5x5); 
    }
   else
   {
      cvReleaseImage(&pSrcImg);
      Scierror(999, "%s, undefined method.\r\n", cstk(lR));
    }

   IplImg2Mat(pDstImg, Rhs+1);
   LhsVar(1) = Rhs+1;

   cvReleaseImage(&pSrcImg);
   cvReleaseImage(&pDstImg);

   return 0;
}

