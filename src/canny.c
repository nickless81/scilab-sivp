//donner comme parrametre a scilab "path de l'image a traiter"
//                                 "path ou on veut ecrire l'image traité"
//                                 "seuil 1" 
//                                 "seuil 2"   

#include "common.h"

extern int toto_canny __PARAMS((char *ch,char *che,double *a,double *b));

int int_canny(char *fname)
{
static int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4;
char *chaine1=NULL;
char *chaine2=NULL;
double *param1=NULL;
double *param2=NULL;

// check nbre et nature param entre sortie
Rhs=Max(0,Rhs);

CheckRhs(4,4);
CheckLhs(0,1);

//definie le param charactere d entre
GetRhsVar(1, "c", &m1, &n1, &l1);
GetRhsVar(2, "c", &m2, &n2, &l2);
GetRhsVar(3, "d", &m3, &n3, &l3);
GetRhsVar(4, "d", &m4, &n4, &l4);

chaine1 = cstk(l1);
chaine2 = cstk(l2);
param1 =  stk(l3);
param2 =  stk(l4);

toto_canny(chaine1,chaine2,param1,param2);

/*
LhsVar(1)=0;
C2F(putlhsvar)();
*/
return 0;
}


int toto_canny(char *ch , char *che ,double *a ,double *b)

{
double lowThresh=0 ;
double highThresh=0;
int apertureSize=3 ;

lowThresh=a[0] ;
highThresh=b[0];

IplImage* img0 = NULL ;
char name0[strlen(ch)];
strcpy(name0,ch)      ;
img0 = cvLoadImage( name0, -1 );
 
IplImage* img1 = NULL;
img1=cvCreateImage(cvGetSize(img0),img0->depth,img0->nChannels);

//petit coup de canny
cvCanny( img0, img1 ,lowThresh,highThresh,apertureSize);

//on sauve
cvSaveImage(che,img1);
//fwrite en binaire de data image

// memory release for img0 before exiting the application 
cvReleaseImage( &img0 );
cvReleaseImage( &img1 );

return(0); 
}
