#include "common.h"

int int_imread(char * fname)
{

  int mL, nL, lL;
  int mR, nR, lR;

  IplImage * pImage;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  GetRhsVar(1, "c", &mL, &nL, &lL);

  pImage = cvLoadImage(cstk(lL), -1);

  /* if load image failed */
  if(pImage == NULL)
    {
      Scierror("%s: Can not open file %s.\r\n", fname, cstk(lL));
      return -1;
    }

  IplImg2Mat(pImage, 2);

  LhsVar(1) = 2;
  
  cvReleaseImage(&pImage);
}

