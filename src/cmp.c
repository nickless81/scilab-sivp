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

int int_cmp(char *fname)
{
  static int l3, m3, n3;
  //create variable for parameters
  char * nom = NULL;
  //check the number of in/out parametres
  Rhs=Max(Lhs,Rhs);

  CheckRhs(3,3);
  CheckLhs(1,1);

  GetRhsVar(3, "c", &m3, &n3, &l3);

  nom = cstk(l3);
  //load the input image for cvcanny
  IplImage* img1 = NULL ;
  img1=Mat2IplImg(1);

  // check if input image is correctly loaded
  if(img1==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  //load the input image for cvcanny
  IplImage* img2 = NULL ;
  img2=Mat2IplImg(2);

  // check if input image is correctly loaded
  if(img2==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  CvSize size1,size2;
  size1=cvGetSize(img1);
  size2=cvGetSize(img2);

  if(img1->nChannels != img2->nChannels|| img1->depth != img2->depth || size1.width != size2.width || size1.height != size2.height) 
    {
      sciprint("Error:wrong depth or wrong size of picture\r\n");
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      return 0;
    }

  //create the output image for cv canny 
  IplImage* img3 = NULL;
  img3=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);

  // check if the output image is correctly loaded
  if(img3==NULL)
    {
      sciprint("Error: can't create the output matrix\r\n");
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      return 0;
    }

  int flag=0; 

  flag=strcmp(nom,"CMP_EQ");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_EQ);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }

  flag=strcmp(nom,"CMP_GT");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_GT);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }

  flag=strcmp(nom,"CMP_GE");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_GE);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }	

  flag=strcmp(nom,"CMP_LT");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_LT);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }	

  flag=strcmp(nom,"CMP_LE");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_LE);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }	

  flag=strcmp(nom,"CMP_NE");
  if (flag==0)
    {
      cvCmp(img1,img2,img3,CV_CMP_NE);
      IplImg2Mat(img3, 4);

      //send the result
      LhsVar(1)=4;

      //let's free the memory
      cvReleaseImage( &img1 );
      cvReleaseImage( &img2 );
      cvReleaseImage( &img3 );
      return 0;
    }	

  sciprint("Error: wrong argument\r\n");

  //let's free the memory
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );
  cvReleaseImage( &img3 );

  return 0;
}
