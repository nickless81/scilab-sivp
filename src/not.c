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

int int_not(char *fname)
{
  IplImage* img2 = NULL;

  // check nbre et nature param entre sortie
  Rhs=Max(Lhs,Rhs);

  CheckRhs(1,1);
  CheckLhs(1,1);

  //load the input image
  IplImage* img1 = NULL ;
  img1=Mat2IplImg(1);

  // check if input image is correctly loaded
  if(img1==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
  // check if the output image is correctly loaded
  if(img2==NULL)
    {
      sciprint("Error: can't create the output matrix\r\n");
      return 0;
    }

  //use the opencv function
  cvNot(img1,img2);

  //transform the result of opencv canny in a matrice
  IplImg2Mat(img2, 3);

  //send the result
  LhsVar(1)=3;

  //let's free the memory
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );

  return 0;
}

