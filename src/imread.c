#include "common.h"

int int_imread(char * fname)
{


  int mR, nR, lR;

  IplImage * pImage;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  pImage = cvLoadImage(cstk(lR), -1);

  /* if load image failed */
  if(pImage == NULL)
    {
      Scierror(999, "%s: Can not open file %s.\r\n", fname, cstk(lR));
      return -1;
    }

  IplImg2Mat(pImage, 2);

  LhsVar(1) = 2;
  
  cvReleaseImage(&pImage);
}

