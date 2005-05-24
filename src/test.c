#include "common.h"

int int_test(char * fname)
{
  CheckRhs(0,0);
  CheckLhs(0,4);

  sciprint("%s: This is a test.\n", fname);

  double x1[]={10.0,20.0,30.0, 40.0, 50.0, 60.0, 70.0, 80.0}; int m1=2, n1=2, c1=2; double *y1 = x1;
  float x2[]={100.0,200.0,300.0, 400.0, 500.0, 600.0};int m2=1, n2=2, c2=3; double *y2 = x2;
  int    x3[]={1,2,3,4,5,6,7,8,9,10,11,12};       int m3=2, n3=2, c3=3; int    *y3 = x3;
  uchar  x4[]={5,6,7,8,9,10,11,12,13,14,15,16};       int m4=2, n4=3, c4=2; uchar *y4=x4;

  Create3DDoubleMat(1, m1, n1,c1, y1);
  Create3DFloatMat(2, m2, n2,c2, y2);
  Create3DIntMat(3, m3, n3,c3, y3, I_INT32);
  Create3DIntMat(4, m4, n4,c4, y4, I_UCHAR);

  LhsVar(1) = 1;
  LhsVar(2) = 2;
  LhsVar(3) = 3;
  LhsVar(4) = 4;

}
