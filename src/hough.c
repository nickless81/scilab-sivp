/************************************************/
/*      NLPR & LIAMA                            */
/*      Projet SIVP                             */
/*      Scilab toolbox for a better world       */
/*      2005                                    */
/************************************************/

#include "common.h"

int int_hough(char *fname)

{
static int l2, m2, n2, l3, m3, n3, l4, m4, n4, l5, m5, n5, l6, m6, n6, l7, m7, n7  ;

//create variable for parameters
char * param2=NULL;
double * param3=NULL;
double * param4=NULL;
int * param5=NULL;
double * param6=NULL;
double * param7=NULL;

Rhs=Max(Lhs,Rhs);

CheckRhs(7,7);
CheckLhs(1,1);

//check the nature of parametres
GetRhsVar(2, "c", &m2, &n2, &l2);
GetRhsVar(3, "d", &m3, &n3, &l3);
GetRhsVar(4, "d", &m4, &n4, &l4);
GetRhsVar(5, "i", &m5, &n5, &l5);
GetRhsVar(6, "d", &m6, &n6, &l6);
GetRhsVar(7, "d", &m7, &n7, &l7);

// check if arg are scalaire
if (m3*n3 != 1 || m4*n4 != 1 || m5*n5 != 1 || m6*n6 != 1|| m7*n7 != 1) 
    {
      sciprint("Error: arguments must be scalars\r\n");
      return 0;
    }   
    
//receive the data
param2 =  cstk(l2);
param3 =  stk(l3);
param4 =  stk(l4);
param5 =  istk(l5);
param6 =  stk(l6);
param7 =  stk(l7);

IplImage* img1 = NULL ;
img1=Mat2IplImg(1);

// check if input image is correctly loaded
if(img1==NULL)
  {
   sciprint("Error: can't read the input image\r\n");
   return 0;
  }

IplImage* color_img2 = cvCreateImage( cvGetSize(img1), 8, 3 );

CvMemStorage* storage = cvCreateMemStorage(0);
CvSeq* lines = 0;
int i;

cvCvtColor( img1, color_img2, CV_GRAY2BGR );

int flag=0;

flag=strcmp(param2,"CV_HOUGH_PROBABILISTIC");
if (flag==0)
	{
	lines = cvHoughLines2(img1,storage,CV_HOUGH_PROBABILISTIC,param3[0],CV_PI/param4[0],param5[0],param6[0],param7[0]);
	for( i = 0; i < lines->total; i++ ) 
		{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		cvLine( color_img2, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA,0 );
		}
	}  	
	
flag=strcmp(param2,"CV_HOUGH_STANDARD");
if (flag==0)
	{
	lines = cvHoughLines2(img1,storage,CV_HOUGH_STANDARD,param3[0],CV_PI/param4[0],param5[0],param6[0],param7[0]);
	for( i = 0; i < lines->total; i++ )
        	{
            	float* line = (float*)cvGetSeqElem(lines,i);
            	float rho = line[0];
            	float theta = line[1];
            	CvPoint pt1, pt2;
            	double a = cos(theta);
		double b = sin(theta);
            	
		if( fabs(a) < 0.001 )
            		{
                	pt1.y = pt2.y = cvRound(rho);
                	pt1.x = 0;
                	pt2.x = color_img2->height;
            		}
            	else if( fabs(b) < 0.001 )
            		{
                	pt1.x = pt2.x = cvRound(rho);
                	pt1.y = 0;
                	pt2.y = color_img2->width;
            		}
            	else
            		{
                	pt1.y = 0;
                	pt1.x = cvRound(rho/b);
                	pt2.y = cvRound(rho/a);
                	pt2.x = 0;
            		//pt2.x = color_img2->width;
			//pt2.y = pt1.y - color_img2->width * a / b;			
			}
            	cvLine( color_img2, pt1, pt2, CV_RGB(255,0,0), 1, CV_AA,0 );
		}
	}
	
IplImg2Mat(color_img2, 8);

//send the result
LhsVar(1)=8;
//let's free the memory
cvReleaseImage( &img1 );
cvReleaseImage( &color_img2 );
return 0;    
}


















/* ©2005 LIAMA */