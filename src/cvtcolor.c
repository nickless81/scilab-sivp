/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2006  Shiqi Yu
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
/************************************************************
 * im2=int_cvtcolor(im, cvt_code);
 * cvt_code = 'rgb2hsv', 'hsv2rgb', 'rgb2ycrcb', 'ycrcb2rgb'
 ************************************************************/

int int_cvtcolor(char *fname) 
{
  char * cvt_str_code = NULL; //input string code
  int cvt_code; //opencv cvt_color code

  IplImage * src_image = NULL;
  IplImage * src_f32_image = NULL;
  IplImage * dst_f32_image = NULL;
  IplImage * dst_f64_image = NULL;

  int m2, n2, l2;

  //check the number of input and output parameters
  CheckRhs(2,2);
  CheckLhs(1,1);

  GetRhsVar(2, "c", &m2, &n2, &l2);
  cvt_str_code = cstk(l2);

  //load the input image
  src_image = Mat2IplImg(1);

  // check if input image is correctly loaded
  if(src_image == NULL)
    {
      sciprint("%s error: can't load the input image.\r\n", fname);
      return -1;
    }
  //check the number of channels
  if(src_image->nChannels != 3)
    {
      sciprint("%s error: The input image must be 3-channel image.\r\n", fname);
      cvReleaseImage(&src_image);
      return -1;
    }
  //this function is called 
  //from scilab macros rgb2hsv/hsv2rgb/...
  //the input image can only be double float.
  if(src_image->depth != IPL_DEPTH_64F)
    {
      sciprint("%s error: The input image must be double type.\r\n", fname);
      cvReleaseImage(&src_image);
      return -1;
    }
  
  if( strcmp(cvt_str_code, "rgb2hsv") == 0)
    cvt_code = CV_BGR2HSV; //the channel order of IplImage in SIVP is BGR
  else if( strcmp(cvt_str_code, "hsv2rgb") == 0)
    cvt_code = CV_HSV2BGR;
  else if( strcmp(cvt_str_code, "rgb2ycrcb") == 0)
    cvt_code = CV_BGR2YCrCb;
  else if( strcmp(cvt_str_code, "ycrcb2rgb") == 0)
    cvt_code = CV_YCrCb2BGR;
  else
    {
      sciprint("%s error: unsupport convertion code %s.\r\n", fname, cvt_str_code);
      cvReleaseImage(&src_image);
      return -1;
    }
  //create images needed
  src_f32_image = cvCreateImage(cvGetSize(src_image), 
				IPL_DEPTH_32F,
				3);
  dst_f32_image = cvCreateImage(cvGetSize(src_image), 
				IPL_DEPTH_32F,
				3);
  dst_f64_image = cvCreateImage(cvGetSize(src_image), 
				IPL_DEPTH_64F,
				3);

  if(src_f32_image == NULL ||
     dst_f32_image == NULL ||
     dst_f64_image == NULL)
    {
      sciprint("Error: create image error.\r\n");
      cvReleaseImage(&src_image);
      cvReleaseImage(&src_f32_image);
      cvReleaseImage(&dst_f32_image);
      cvReleaseImage(&dst_f64_image);
      return -1;
    }

  cvConvert(src_image, src_f32_image);
 
  cvCvtColor(src_f32_image, dst_f32_image, cvt_code);
  
  cvConvert(dst_f32_image, dst_f64_image);

  IplImg2Mat(dst_f64_image, 3);
  //send the result
  LhsVar(1)=3;

  cvReleaseImage(&src_image);
  cvReleaseImage(&src_f32_image);
  cvReleaseImage(&dst_f32_image);
  cvReleaseImage(&dst_f64_image);
  
  return 0;
}



/*
int int_convert(char *fname)
{
  static int l2, m2, n2;

  //create variable for parameters
  char * nom = NULL;
  int flag=0;
  //check the number of in/out parametres
  Rhs=Max(Lhs,Rhs);

  CheckRhs(0,2);
  CheckLhs(1,1);

  //check the nature of parametres
  GetRhsVar(2, "c", &m2, &n2, &l2);

  nom = cstk(l2);

  //load the input image for cvcanny
  IplImage* img1 = NULL ;
  img1=Mat2IplImg(1);

  IplImage* img2 = NULL;

  // check if input image is correctly loaded
  if(img1==NULL)
    {
      sciprint("Error: can't read the input image\r\n");
      return 0;
    }

  flag=strcmp(nom,"GRAY2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_GRAY2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"GRAY2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_GRAY2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"RGB2GRAY");
  if (flag==0)
    {
      if (img1->nChannels==3)
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,1);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_RGB2GRAY);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BGR2GRAY");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,1);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BGR2GRAY);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"XYZ2BGR");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_XYZ2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BGR2XYZ");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BGR2XYZ);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }


  flag=strcmp(nom,"XYZ2RGB");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_XYZ2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"RGB2XYZ");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_RGB2XYZ);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"YCrCb2RGB");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_YCrCb2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }


  flag=strcmp(nom,"YCrCb2BGR");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_YCrCb2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"RGB2YCrCb");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_RGB2YCrCb);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }


  flag=strcmp(nom,"BGR2YCrCb");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BGR2YCrCb);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }


  flag=strcmp(nom,"BGR2HSV");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BGR2HSV);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }	

  flag=strcmp(nom,"RGB2HSV");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,"CV_RGB2HSV");
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }	


  flag=strcmp(nom,"BGR2Lab");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BGR2Lab);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"RGB2Lab");
  if (flag==0)
    {
      if (img1->nChannels==3) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_RGB2Lab);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerBG2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerBG2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }	


  flag=strcmp(nom,"BayerGB2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGB2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerRG2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerRG2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerGR2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGR2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerBG2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,"CV_BayerBG2RGB");
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerRG2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,"CV_BayerRG2BGR");
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerGB2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGB2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerGR2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGR2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerRG2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerRG2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerBG2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerBG2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerGR2RGB");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGR2RGB);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  flag=strcmp(nom,"BayerGB2BGR");
  if (flag==0)
    {
      if (img1->nChannels==1) 
	{
	  img2=cvCreateImage(cvGetSize(img1),img1->depth,3);
	  if(img2==NULL)
	    {
	      sciprint("Error: can't create the output matrix\r\n");
	      return 0;
	    }
	  cvCvtColor(img1, img2,CV_BayerGB2BGR);
	  IplImg2Mat(img2, 3);
	  //send the result
	  LhsVar(1)=3;
	  //let's free the memory
	  cvReleaseImage( &img1 );
	  cvReleaseImage( &img2 );
	  return 0;
	}	
      else
	{
	  sciprint("Error: Wrong depth for input matrix\r\n");
	  return 0;
	}
    }

  //let's free the memory
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );

  return 0;
}

*/
