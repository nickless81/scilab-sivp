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

int int_sobel(char *fname)
{
static int l2, m2, n2, l3, m3, n3, l4, m4, n4 ;

//create variable for parameters
int *param1=NULL;
int *param2=NULL;
int *param3=NULL;

IplImage* img2 = NULL;

// check nbre et nature param entre sortie
Rhs=Max(Lhs,Rhs);

CheckRhs(4,4);
CheckLhs(1,1);

//definie le param charactere d entre
GetRhsVar(2, "i", &m2, &n2, &l2);
GetRhsVar(3, "i", &m3, &n3, &l3);
GetRhsVar(4, "i", &m4, &n4, &l4);

// check if arg are scalaire
if (m2*n2 != 1 || m3*n3 != 1 || m4*n4 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

//receive the data
param1 =  istk(l2);
param2 =  istk(l3);
param3 =  istk(l4);

//verifications des valeurs
if ( (param3[0]%2 != 1) || (param3[0]<3) )
{
sciprint("Error: The size of sobel kernel must be 3,5,7, ...\r\n");
return 0;
}

if ( (param1[0]>2) || (param1[0]<0) || (param2[0]>2)|| (param2[0]<0))
{
sciprint("Error: wrong dx or dy ...\r\n");
return 0;
}


//load the input image for cvsobel
IplImage* img1 = NULL ;
img1=Mat2IplImg(1);

// check if input image is correctly loaded
if(img1==NULL)
  {
   sciprint("Error: can't read the input image\r\n");
   return 0;
  }

  if(   (img1->depth==IPL_DEPTH_8U)  &&  (img1->nChannels==1)   )
  {
   //create the output image for cv canny 
   
   img2 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_16S, 1);
   
   // check if the output image is correctly loaded
   if(img2==NULL)
     {
     sciprint("Error: can't create the output matrix\r\n");
     return 0;
     }
   
   //use the opencv function
   cvSobel( img1, img2 ,param1[0],param2[0],param3[0]);
   
   //transform the result of opencv canny in a matrice
   IplImg2Mat(img2, 5);
   
   //send the result
   LhsVar(1)=5;
  }
 else
 {
  sciprint("Error: wrong input matrice\r\n");
  return 0;
 }  
 
//let's free the memory
cvReleaseImage( &img1 );
cvReleaseImage( &img2 );

return 0;
}
