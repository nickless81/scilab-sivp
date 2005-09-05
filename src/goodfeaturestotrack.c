/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

#include "common.h"

int int_goodfeaturestotrack(char *fname)
{
static int l2, m2, n2, l3, m3, n3, l4, m4, n4;

//create variable for parameters
int * param1 = NULL;
double * param2=NULL;
double * param3=NULL;

int flag=0;
//check the number of in/out parametres
Rhs=Max(Lhs,Rhs);

CheckRhs(4,4);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "i", &m2, &n2, &l2);
GetRhsVar(3, "d", &m3, &n3, &l3);
GetRhsVar(4, "d", &m4, &n4, &l4);

// check if arg are scalaire
if (m2*n2 != 1 || m3*n3 != 1 || m4*n4 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }

//receive the data
param1 =  istk(l2);
param2 =  stk(l3);
param3 =  stk(l4);

//load the input image for cvcanny
IplImage* img1 = NULL ;
img1=Mat2IplImg(1);

// check if input image is correctly loaded
if(img1==NULL)
  {
  sciprint("Error: can't read the input image\r\n");
  cvReleaseImage( &img1 );
  return 0;
  }
  
if(img1->nChannels !=1)
  {
  sciprint("Error:wrong number of channel for input matrice\r\n");
  cvReleaseImage( &img1 );
  return 0;
  }

//create the output image
IplImage* img2 = NULL;
img2=cvCreateImage(cvGetSize(img1),IPL_DEPTH_32F,1);

IplImage* img3 = NULL;
img3=cvCreateImage(cvGetSize(img1),IPL_DEPTH_32F,1);

IplImage* imgout = NULL;
imgout=cvCreateImage(cvGetSize(img1),IPL_DEPTH_8U,3);

cvCvtColor(img1,imgout,CV_GRAY2BGR);

// check if the output image is correctly loaded
if(img2==NULL || img3==NULL)
  {
  sciprint("Error: can't create the output matrix\r\n");
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );
  cvReleaseImage( &img3 );
  return 0;
  }
       
CvPoint2D32f corners[1000];
  
cvGoodFeaturesToTrack(img1,img2,img3,corners,param1,param2[0],param3[0],NULL);

int i=1;
for (i=1;i<=param1[0];i++)
    {
    cvCircle(imgout,cvPoint(corners[i-1].x,corners[i-1].y),10,CV_RGB(255,0,0),2,8,0);
    sciprint("number of corner :%i\n",param1[0]);
    sciprint("point number %i x=%f y=%f\n",i,corners[i].x,corners[i].y);
    }

IplImg2Mat(imgout,5);

//send the result
LhsVar(1)=5;
  
//let's free the memory
cvReleaseImage( &img1 );
cvReleaseImage( &img2 );
cvReleaseImage( &img3 );
cvReleaseImage( &imgout );

return 0;
}

/* ©2005 LIAMA */