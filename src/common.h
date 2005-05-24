#ifndef SIVP_COMMON_H
#define SIVP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#define CV_INLINE static

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

typedef int BOOL;

#include <stdio.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <stack-c.h>

  BOOL Create2DIntMat(int nPos, int nRow, int nCol, void * pData, int nType);
  BOOL Create2DFloatMat(int nPos, int nRow, int nCol, float * pData);
  BOOL Create2DDoubleMat(int nPos, int nRow, int nCol, double * pData);
  BOOL Create3DIntMat(int nPos, int nRow, int nCol, int nCh, void * pData, int nType);
  BOOL Create3DFloatMat(int nPos, int nRow, int nCol, int nCh, float* pData);
  BOOL Create3DDoubleMat(int nPos, int nRow, int nCol, int nCh, double* pData);


#ifdef __cplusplus
}
#endif


#endif
