/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2006  Shiqi Yu
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

/************************************************************
 * imout = imabsdiff(im1, im2)
 ************************************************************/

int int_imabsdiff(char * fname)
{


  IplImage * pImage1 = NULL;
  IplImage * pImage2 = NULL;
  IplImage * pImageOut = NULL; //output

  CheckRhs(2, 2);
  CheckLhs(1, 1);

  /*convert the matrix to IplImage*/
  pImage1 = Mat2IplImg(1);
  pImage2 = Mat2IplImg(2);

  if( !pImage1 || !pImage2)
    {
      return -1;
    }

  if((pImage1->width != pImage2->width) || (pImage1->height != pImage2->height))
    {
      cvReleaseImage(&pImage1);
      cvReleaseImage(&pImage2);
      Scierror(999, "%s: The two input images do not have same image size.\r\n",fname);
      return -1;
    }


  if(pImage1->nChannels != pImage2->nChannels)
    {
      cvReleaseImage(&pImage1);
      cvReleaseImage(&pImage2);
      Scierror(999, "%s: The two input images do not have same channel number.\r\n",fname);
      return -1;
    }

  if(pImage1->depth != pImage2->depth)
    {
      cvReleaseImage(&pImage1);
      cvReleaseImage(&pImage2);
      Scierror(999, "%s: The two input images do not have same depth.\r\n",fname);
      return -1;
    }

  pImageOut = cvCreateImage(cvGetSize(pImage1), pImage1->depth, pImage1->nChannels);

  if(!pImageOut)
    {
      Scierror(998, "%s: Can not alloc memeory for image.\r\n", fname);
      cvReleaseImage(&pImage1);
      cvReleaseImage(&pImage2);
      return -1;
    }
  cvAbsDiff(pImage1, pImage2, pImageOut);
  
  IplImg2Mat(pImageOut, 3);

  LhsVar(1) = 3;
  
  cvReleaseImage(&pImage1);
  cvReleaseImage(&pImage2);
  cvReleaseImage(&pImageOut);

  return 0;

}
