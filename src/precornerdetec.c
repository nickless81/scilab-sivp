/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

#include "common.h"

int int_precornerdetec(char *fname)
{
static int l2, m2, n2;

//create variable for parameters
int * param=NULL;

//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(2,2);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "i", &m2, &n2, &l2);

// check if arg are scalaire
if (m2*n2 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

//receive the data
param =  istk(l2);

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

if(img1->nChannels==1)
  {
  //create the output image for cv precornerdetec 
  img2=cvCreateImage(cvGetSize(img1),IPL_DEPTH_32F,img1->nChannels);

  // check if the output image is correctly loaded
  if(img2==NULL)
    {
    sciprint("Error: can't create the output matrix\r\n");
    return 0;
    }
  
  cvPreCornerDetect(img1 ,img2 ,param[0] );
  
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

/* ©2005 LIAMA */