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

int int_imsmooth(char *fname)
{
static int l2, m2, n2, l3, m3, n3, l4, m4, n4, m5, n5, l5;

//create variable for parameters
char * nom = NULL;
int flag=0;

int * param2=NULL;
int * param3=NULL;
int * param4=NULL;

//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(5,5);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "c", &m2, &n2, &l2);
GetRhsVar(3, "i", &m3, &n3, &l3);
GetRhsVar(4, "i", &m4, &n4, &l4);
GetRhsVar(5, "i", &m5, &n5, &l5);

// check if arg are scalaire
if (m3*n3 != 1 || m4*n4 != 1 || m5*n5 != 1 ) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

//receive the data
nom = cstk(l2);
param2 =  istk(l3);
param3 =  istk(l4);
param4 =  istk(l5);

//load the input image for cvcanny
IplImage* img1 = NULL ;
img1=Mat2IplImg(1);

// check if input image is correctly loaded
if(img1==NULL)
  {
   sciprint("Error: can't read the input image\r\n");
   return 0;
  }

  flag=strcmp(nom,"BLUR");
  if (flag==0)
  	{
  	//create the output image for cv canny 
	IplImage* img2 = NULL;
	img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
	cvSmooth( img1, img2 ,CV_BLUR ,param2[0],param3[0],param4[0], 0);
	//transform the result of opencv canny in a matrice
 	IplImg2Mat(img2, 5);
	//send the result
 	LhsVar(1)=5;
  	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	return 0;
	}
  
  flag=strcmp(nom,"BLUR_NO_SCALE");
  if (flag==0)
  	{
  	//create the output image for cv canny 
	IplImage* img2 = NULL;
	img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
	cvSmooth( img1, img2 ,CV_BLUR ,param2[0],param3[0],param4[0],0);
	//transform the result of opencv canny in a matrice
 	IplImg2Mat(img2, 5);
	//send the result
 	LhsVar(1)=5;
  	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	return 0;
	}
	
	
  flag=strcmp(nom,"GAUSSIAN");
  if (flag==0)
  	{
  	//create the output image for cv canny 
	IplImage* img2 = NULL;
	img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
	cvSmooth( img1, img2 ,CV_GAUSSIAN ,param2[0],param3[0],param4[0], 0);
	//transform the result of opencv canny in a matrice
 	IplImg2Mat(img2, 5);
	//send the result
 	LhsVar(1)=5;
  	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	return 0;
	}
	
  flag=strcmp(nom,"BILATERAL");
  if (flag==0)
  	{
  	//create the output image for cv canny 
	IplImage* img2 = NULL;
	img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
	cvSmooth( img1, img2 ,CV_BILATERAL,param2[0],param3[0],param4[0], 0);
	//transform the result of opencv canny in a matrice
 	IplImg2Mat(img2, 5);
	//send the result
 	LhsVar(1)=5;
  	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	return 0;
	}
  
  flag=strcmp(nom,"MEDIAN");
  if (flag==0)
  	{
  	//create the output image for cv canny 
	IplImage* img2 = NULL;
	img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
	cvSmooth( img1, img2 ,CV_MEDIAN ,param2[0],param3[0],param4[0], 0);
	//transform the result of opencv canny in a matrice
 	IplImg2Mat(img2, 5);
	//send the result
 	LhsVar(1)=5;
  	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );
	return 0;
	}
 
sciprint("Error: Don't find the operation to do\r\n");
cvReleaseImage( &img1 );
return 0;
}

