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

int int_pyrup(char *fname)
{
static int l2, m2, n2;

//create variable for parameters
char * nom = NULL;


int flag=0;
//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(2,2);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "c", &m2, &n2, &l2);

nom = cstk(l2);

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
img2=cvCreateImage(cvSize(img1->width*2,img1->height*2),img1->depth,img1->nChannels);
// check if the output image is correctly loaded
if(img2==NULL)
  {
   sciprint("Error: can't create the output matrix\r\n");
   return 0;
  }

  flag=strcmp(nom,"GAUSSIAN_5x5");
  if (flag==0)
  	{
  	cvPyrUp( img1, img2 ,CV_GAUSSIAN_5x5);
	IplImg2Mat(img2, 3);

 	//send the result
 	LhsVar(1)=3;
  
 	//let's free the memory
	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );

	return 0;
	}
  
sciprint("Error: wrong argument\r\n");
 
 //let's free the memory
cvReleaseImage( &img1 );
cvReleaseImage( &img2 );

return 0;
}

