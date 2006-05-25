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

int int_dilate(char *fname)
{
  static int l2, m2, n2, l3, n3, m3, l4, m4, n4 ,m5, n5, l5, m6, n6, l6, m7, n7, l7;

  //create variable for parameters optionel
  int * a;
  int * b;
  int * c;
  int * d;

  //create variable for parameters
  int * nbr_it=NULL;  // variable pour le nombre d'itération
  IplImage* img1 = NULL ; //l'image source
  char * nom = NULL; // variable pour le texte a recuperer

  //variable system
  int flag ;

  Rhs=Max(Lhs,Rhs);

  CheckRhs(2,7);
  CheckLhs(1,1);

  IplConvKernel * truc; //variable pr creer la forme optionel du filtre d'érodage

  //load the input image for cvcanny
  img1=Mat2IplImg(1);
  // check if input image is correctly loaded
  if(img1==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  //create the output 
  IplImage* img2 = NULL;
  img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);
  // check if the output image is correctly loaded
  if(img2==NULL)
    {
      sciprint("Error: can't create the output matrix\r\n");
      return 0;
    }

  if (Rhs==2)
    {
      GetRhsVar(2, "i", &m2, &n2, &l2);
      // recupere les valeur des variable pas optionel
      nbr_it =  istk(l2);

      // check if arg are scalaire
      if (m2*n2 != 1) 
	{
	  sciprint("Error: arguments must be scalars\r\n");
	  return 0;
	}

      cvDilate(img1,img2 ,0,nbr_it[0]);

      //transform the result of opencv canny in a matrice
      IplImg2Mat(img2, 8);
      //send the result
      LhsVar(1)=8;

      return 0;
    }
  else
    if (Rhs==7)
      {
	GetRhsVar(2, "i", &m2, &n2, &l2);
	GetRhsVar(3, "c", &m3, &n3, &l3);

	GetRhsVar(4, "i", &m4, &n4, &l4);
	GetRhsVar(5, "i", &m5, &n5, &l5);
	GetRhsVar(6, "i", &m6, &n6, &l6);
	GetRhsVar(7, "i", &m7, &n7, &l7);

	// recupere les valeur des variable pas optionel
	nbr_it =  istk(l2);
	nom = cstk(l3);
	//recup var opti
	a = istk(l4);
	b = istk(l5);
	c = istk(l6);
	d = istk(l7);

	// check if arg are scalaire
	if (m2*n2 != 1) 
	  {
	    sciprint("Error: arguments must be scalars\r\n");
	    return 0;
	  }

	flag=strcmp(nom,"RECT");
	if (flag==0)
	  {
	    truc=cvCreateStructuringElementEx(a[0], b[0], c[0], d[0],
					      CV_SHAPE_RECT,NULL );
	  }
	flag=strcmp(nom,"CROSS");
	if (flag==0)
	  {
	    truc=cvCreateStructuringElementEx( a[0], b[0], c[0], d[0], CV_SHAPE_CROSS,NULL );
	  }	
	flag=strcmp(nom,"ELLIPSE");
	if (flag==0)
	  {
	    truc=cvCreateStructuringElementEx( a[0], b[0], c[0], d[0], CV_SHAPE_ELLIPSE,NULL );
	  }
	cvDilate(img1,img2 ,truc,nbr_it[0]);
	//transform the result of opencv canny in a matrice
	IplImg2Mat(img2, 8);
	//send the result
	LhsVar(1)=8;	

	cvReleaseImage( &img1 );
	cvReleaseImage( &img2 );	

	return 0;	
      }
    else
      {
	printf("mvs nbr param\n");
	sciprint(" Error : parameters number must be 3 or 7\r\n");
	return 0;
      }
}
