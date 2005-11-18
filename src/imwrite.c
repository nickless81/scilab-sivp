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

/************************************************************
 * write an image to a file
 * the first argument should be a matrix; only 8-bit single-channel or 3-channel can be saved.
 *    other formats will be converted to one of these formats
 * the second argument should be the file name 
 * the format of the file is decided by the file name
 * return 0 if succeed, -1 otherwise
 ************************************************************/

/*TODO: when the file type can not be gotten from the file name
 * an error will occur, 
 * and then scilab will exit
 */
int int_imwrite(char * fname)
{

  int mL=1, nL=1, lL;
  int mR, nR, lR;

  IplImage * pImage, *pDstImage;
  double dScale = 1.0;
  double dShift = 0.0;

  CheckRhs(2, 2);
  CheckLhs(1, 1);

  /*get file name*/
  GetRhsVar(2, "c", &mR, &nR, &lR);

  /*create return value*/
  CreateVar(3, "d", &mL, &nL, &lL);
  *stk(lL) = -1;

  /*convert the matrix to IplImage*/
  pImage = Mat2IplImg(1);
  
  if(pImage == NULL)
    goto EXIST_TAG;

  if(pImage->nChannels != 1 && pImage->nChannels != 3)
    {
      Scierror(999, "%s: Single-channel or 3-channel can be saved.\r\n", fname);
    }


  if(pImage->depth == IPL_DEPTH_8U)
    {
      *stk(lL) = cvSaveImage(cstk(lR), pImage);
    }
  else
    {
      /*only unsigned char image can be saved
	convert other type to unsigned char*/
      /*
      switch(pImage->depth){
      case IPL_DEPTH_8S:     dScale = 1.0;   dShift = 128.0 ; break;
      case IPL_DEPTH_16U:    dScale = (double)(2^8-1)/(double)(2^16-1);   dShift = 0.0 ; break;
      case IPL_DEPTH_16S:    dScale = 1.0/(double)(2^8); dShift = 128.0; break;
      case IPL_DEPTH_32S:    dScale = 1.0/(double)(2^24); dShift = (double)(2^23); break;
      case IPL_DEPTH_32F:
      case IPL_DEPTH_64F:    dScale = 255.0; dShift = 0.0; break;
      }
      */
      dScale = 1.0;
      dShift = 0.0;


      pDstImage = cvCreateImage(cvSize(pImage->width, pImage->height), IPL_DEPTH_8U, pImage->nChannels);
      if(!pDstImage)
	{
	  cvReleaseImage(&pImage);
	  Scierror(999, "%f: Create IplImage error.",fname);
	}
      cvConvertScale(pImage, pDstImage, dScale, dShift);
      *stk(lL) = cvSaveImage(cstk(lR), pDstImage);
      cvReleaseImage(&pDstImage);
    }
  

      //  *stk(lL) = 0;
 EXIST_TAG:
  LhsVar(1) = 3;
  
  cvReleaseImage(&pImage);

  return 0;
}

