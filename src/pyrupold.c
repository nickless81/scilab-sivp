/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

#include "common.h"

int int_pyrup(char *fname)
{
static int l2, m2, n2;
int flag ;
//create variable for parameters
char * nom=NULL;

//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(1,2);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "c", &m2, &n2, &l2);

//receive the data
nom =  cstk(l2);

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
img2=cvCreateImage(cvGetSize(img1),img1->depth,img1->nChannels);

// check if the output image is correctly loaded
if(img2==NULL)
  {
   sciprint("Error: can't create the output matrix\r\n");
   return 0;
  }
   
flag=strcmp(nom,"GAUSSIAN_5x5");
if (flag==0)
  {
  //use the opencv function
  cvPyrUp( img1, img2 ,CV_GAUSSIAN_5x5);
  }
     
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