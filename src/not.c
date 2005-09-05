/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

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

/* ©2005 LIAMA */