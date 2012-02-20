/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
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
#include "gw_sivp.h"

/* convert data from columnwise to row-wise
 * intput: an image (M x N or M x N x 3) which must be uint8 type.
 * output: the utf-8 image data
 * if failed, output is 0.
 * this function is for showing a image in TK
 ************************************************************/

int int_mat2utfimg(char * fname)
{
  IplImage * pImg = NULL;
  int nOne=1, lL;

  unsigned char * pUTFData = NULL;
  int nCurr = 0;
  int isOK;

  int w,h,c;
  unsigned char Pixel;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  /*convert the matrix to IplImage*/
  pImg = Mat2IplImg(1);
  if(pImg == NULL)
    goto EXIT_TAG;


  pUTFData=(unsigned char*)malloc(pImg->width * pImg->height * pImg->nChannels * 2);

  for(h=0; h < pImg->height; h++)
    for(w=0; w < pImg->width; w++)
      for(c=pImg->nChannels-1; c>=0; c--)
  {
    Pixel = CV_IMAGE_ELEM(pImg, unsigned char, h, w*pImg->nChannels + c );
    if(Pixel <= 127 && Pixel > 0)
      {
        pUTFData[nCurr++] = Pixel;
      }
    else
      {
        pUTFData[nCurr++] = (Pixel >> 6) + 0xC0; //11000000 + highest 2 bits
        pUTFData[nCurr++] = (Pixel & 0x3F) + 0x80;//10000000 + lest 6 bits
      }
  }


  isOK = FALSE;
  isOK = Create2DIntMat(2, 1, nCurr, pUTFData, I_UCHAR);

  if(!isOK)
    {
      goto EXIT_TAG;
    }

  if(pUTFData)
    free(pUTFData);
  if(pImg)
    cvReleaseImage(&pImg);

  LhsVar(1) = 2;
  return 0;

      //  *stk(lL) = 0;
 EXIT_TAG:
  if(pUTFData)
    free(pUTFData);
  if(pImg)
    cvReleaseImage(&pImg);
  /*create return value*/
  CreateVar(2, "d", &nOne, &nOne, &lL);
  *stk(lL) = 0;
  LhsVar(1) = 2;


  return 0;
}

