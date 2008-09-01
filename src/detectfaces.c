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
  IplImage * pLocations = NULL;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  //load haar cascade xml file
  if(!pCascade)
    pCascade = (CvHaarClassifierCascade*)cvLoad( "haarcascade_frontalface_alt2.xml", 0, 0, 0 );
  
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

  

  cvReleaseStorage(&pStorage);
}
