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

int int_adaptativethreshold(char *fname)
{
  static int l2, m2, n2, l3, m3, n3, l4, m4, n4,l5,m5,n5,l6,m6,n6;

  //create variable for parameters
  double * param1=NULL;
  char * nom1 = NULL;
  char * nom2 = NULL;
  int * param2=NULL;
  double * param3=NULL;

  int flag=0;
  //check the number of in/out parametres
  Rhs=Max(Lhs,Rhs);

  CheckRhs(6,6);
  CheckLhs(1,1);

  //check the nature of parametres
  GetRhsVar(2, "d", &m2, &n2, &l2);
  GetRhsVar(3, "c", &m3, &n3, &l3);
  GetRhsVar(4, "c", &m4, &n4, &l4);
  GetRhsVar(5, "i", &m5, &n5, &l5);
  GetRhsVar(6, "d", &m6, &n6, &l6);

  nom1 = cstk(l3);
  nom2 = cstk(l4);

  // check if arg are scalaire
  if (m2*n2 != 1 || m5*n5 != 1 || m6*n6 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

  //receive the data
  param1 =  stk(l2);
  param2 =  istk(l5);
  param3 =  stk(l6);

  //load the input image for cvcanny
  IplImage* img1 = NULL ;
  img1=Mat2IplImg(1);

  // check if input image is correctly loaded
  if(img1==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  //create the output image for cv canny 
  IplImage* img2 = NULL;
  img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);

  // check if the output image is correctly loaded
  if(img2==NULL)
    {
      sciprint("Error: can't create the output matrix\r\n");
      return 0;
    }

  flag=strcmp(nom1,"ADAPTIVE_THRESH_MEAN_C");
  if (flag==0)
    {
      flag=strcmp(nom2,"THRESH_BINARY");
      if (flag==0)
	{
	  cvAdaptiveThreshold( img1, img2,param1[0],CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,param2[0],param3[0]);
	  IplImg2Mat(img2, 7);
	  //send the result
	  LhsVar(1)=7;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}

      flag=strcmp(nom2,"THRESH_BINARY_INV");
      if (flag==0)
	{
	  cvAdaptiveThreshold(img1, img2,param1[0],CV_ADAPTIVE_THRESH_MEAN_C,
			      CV_THRESH_BINARY_INV,param2[0],param3[0]);
	  IplImg2Mat(img2, 7);

	  //send the result
	  LhsVar(1)=7;

	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );

	  return 0;
	}


    }

  flag=strcmp(nom1,"ADAPTIVE_THRESH_GAUSSIAN_C");
  if (flag==0)
    {
      flag=strcmp(nom2,"THRESH_BINARY");
      if (flag==0)
	{
	  cvAdaptiveThreshold( img1, img2,param1[0],CV_ADAPTIVE_THRESH_GAUSSIAN_C,
			       CV_THRESH_BINARY,param2[0],param3[0]);
	  IplImg2Mat(img2, 7);

	  //send the result
	  LhsVar(1)=7;

	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );

	  return 0;
	}

      flag=strcmp(nom2,"THRESH_BINARY_INV");
      if (flag==0)
	{
	  cvAdaptiveThreshold( img1, img2,param1[0],CV_ADAPTIVE_THRESH_GAUSSIAN_C,
			       CV_THRESH_BINARY_INV,param2[0],param3[0]);
	  IplImg2Mat(img2, 7);

	  //send the result
	  LhsVar(1)=7;

	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );

	  return 0;
	}
    }

  sciprint("Error: wrong argument\r\n");

  //let's free the memory
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );

  return 0;
}
