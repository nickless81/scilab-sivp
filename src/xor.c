/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

#include "common.h"

int int_xor(char *fname)
{
//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(2,2);
CheckLhs(1,1);

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
  
 if(img1->nChannels != img2->nChannels || img1->depth != img2->depth || size1.width != size2.width || size1.height != size2.height) 
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

cvXor(img1,img2,img3,NULL);
  
IplImg2Mat(img3,3);

//send the result
LhsVar(1)=3;

//let's free the memory
cvReleaseImage( &img1 );
cvReleaseImage( &img2 );
cvReleaseImage( &img3 );

return 0;
}

/* ©2005 LIAMA */