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

/**********************************************************************
 * imout=filter2(F, imin);
 * the difference between filter2 and imfilter is:
 * the returned matrix of filter2 is double,
 * but the returned matrix of imfilter is as the same as input image
 **********************************************************************/
int int_filter2(char * fname)
{

  int mR1, nR1, lR1;
  int mR2, nR2, lR2;

  IplImage* src_image = NULL;
  IplImage* f32_src_image = NULL;
  IplImage* f32_filtered_image = NULL;
  IplImage* f64_filtered_image = NULL;

  IplImage* src_filter = NULL;
  CvMat* f32_filter = NULL;


  CheckRhs(2, 2);
  CheckLhs(1, 1);

  //load the input src_filter
  src_filter = Mat2IplImg(1);
  //load the input image
  src_image = Mat2IplImg(2);

  if(src_image == NULL)
    {
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);
      return -1;
    }
  if(src_filter == NULL)
    {
      Scierror(999, "%s: Internal error for getting the src_filter data.\r\n", fname);
      cvReleaseImage(&src_image);
      return -1;
    }
  if(src_filter->nChannels != 1)
    {
      Scierror(999, "%s: The kernel must be 2D matrix.\r\n", fname);
      cvReleaseImage(&src_image);
      cvReleaseImage(&src_filter);
      return -1;
    }

  //the src_filter must be a 32F matrix
  //because scilab has no single float data type
  //src_filter must be converted to 32F
  f32_filter = cvCreateMat(src_filter->height,
			    src_filter->width,
			    CV_32FC1);
  if(f32_filter == NULL)
    {
      Scierror(999, "%s: Internal error for allocating memory for the kernel.\r\n", fname);
      cvReleaseImage(&src_image);
      cvReleaseImage(&src_filter);
      return -1;
    }
  cvConvert(src_filter, f32_filter);

  f32_src_image = cvCreateImage(cvSize(src_image->width, src_image->height), 
				IPL_DEPTH_32F, src_image->nChannels);
  f32_filtered_image = cvCloneImage(f32_src_image);
  f64_filtered_image = cvCreateImage(cvSize(src_image->width, src_image->height), 
				IPL_DEPTH_64F, src_image->nChannels);
  
  if( !f32_src_image || !f32_filtered_image || !f64_filtered_image)
    {
      Scierror(999, "%s: Internal error for allocating memory for images.\r\n", fname);
      cvReleaseImage(&f64_filtered_image);
      cvReleaseImage(&f32_filtered_image);
      cvReleaseImage(&f32_src_image);
      cvReleaseImage(&src_filter);
      cvReleaseMat(&f32_filter);
      return -1;
    }
  cvConvert(src_image, f32_src_image);
  cvFilter2D(f32_src_image, f32_filtered_image, f32_filter, cvPoint(-1,-1));
  cvConvert(f32_filtered_image, f64_filtered_image);
  

  IplImg2Mat(f64_filtered_image, Rhs+1);
  LhsVar(1) = Rhs+1;
  
  cvReleaseImage(&src_image);
  cvReleaseImage(&f32_src_image);

  cvReleaseImage(&src_filter);
  cvReleaseMat(&f32_filter);

  cvReleaseImage(&f32_filtered_image);
  cvReleaseImage(&f64_filtered_image);

  return 0;
}
