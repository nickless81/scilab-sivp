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

int int_laplace(char *fname)
{
static int l2, m2, n2;
int *param1=NULL;
IplImage* img2 = NULL;

// check nbre et nature param entre sortie
Rhs=Max(Lhs,Rhs);

CheckRhs(2,2);
CheckLhs(1,1);

//definie le param charactere d entre
GetRhsVar(2, "i", &m2, &n2, &l2);

// check if arg are scalaire
if (m2*n2 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

param1 =  istk(l2);

//verifications des valeurs
if ( (param1[0]%2 != 1) || (param1[0]<3) )
{
sciprint("Error: The size of laplace kernel must be 3,5,7, ...\r\n");
return 0;
}


//load the input image
IplImage* img1 = NULL ;
img1=Mat2IplImg(1);

// check if input image is correctly loaded
if(img1==NULL)
  {
   sciprint("Error: can't read the input image\r\n");
   return 0;
  }
  
 if ((img1->depth==IPL_DEPTH_8U) && (img1->nChannels==1))
 	{
   	//create the output image for the function 
	img2=cvCreateImage(cvGetSize(img1),IPL_DEPTH_16S ,img1->nChannels);
	// check if the output image is correctly loaded
	if(img2==NULL)
  		{
   		sciprint("Error: can't create the output matrix\r\n");
   		return 0;
  		}
   	//use the opencv function
   	cvLaplace( img1, img2 ,param1[0]);
       
   	//transform the result of opencv canny in a matrice
   	IplImg2Mat(img2, 3);

   	//send the result
   	LhsVar(1)=3;
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

