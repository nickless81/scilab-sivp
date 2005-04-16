#include"sivp_common.h"


BOOL 
Create3DIntMat(int nPos, int nRow, int nCol, int nCh, void* pData, int nType)
{
  static char *Str[]= { "hm","dims","entries"}; 
  int m1=1,n1=3;
  int mL=3,nL=1,lL, un=1;

  SciIntMat Dims;
  SciIntMat IntData;

  //create SciIntMat for dimentional information
  Dims.m = 1;
  Dims.n = (nCh==1 ? 2 : 3);
  Dims.l = -1; /* dimensions matrix not in scilab stack */
  Dims.it = I_INT32;
  Dims.D = malloc(Dims.n * sizeof(int)); //dim data
  if (!Dims.D)
  {
    Scierror(999,"Unable to alloc memory for the image\n");
    return FALSE;
  }

  IC_INT32(Dims.D)[0] = nRow;
  IC_INT32(Dims.D)[1] = nCol;
  if(Dims.n == 3)
    IC_INT32(Dims.D)[2] = nCh;

  //create SciIntMat for the image data
  IntData.m = nRow * nCol *nCh;
  IntData.n = 1;
  IntData.l = -1; /* dimensions matrix not in scilab stack */
  IntData.it = nType;
  IntData.D = pData;


  CreateVar(nPos,"m", &mL, &nL, &lL);
  CreateListVarFromPtr(nPos,1,"S", &m1, &n1, Str);
  CreateListVarFromPtr(nPos,2,"I",&(Dims.m), &(Dims.n), &Dims); 
  CreateListVarFromPtr(nPos,3,"I",&(IntData.m), &(IntData.n), &IntData ); 


/*   free memory */
  free(Dims.D);

  return TRUE;
}

void rgbimg2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight)
{
  img2mat(pSrc, pDst, nWidth, nHeight, 3);
}


void grayimg2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight)
{
  img2mat(pSrc, pDst, nWidth, nHeight, 1);
}

void img2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight, int nCh)
{
  int row, col, ch;
  long nCount = 0;

  for(ch =0; ch < nCh; ch++)
    for(col =0; col < nWidth; col++)
      for(row = 0; row < nHeight; row++)
	{
	  *(pDst+nCount) = *(pSrc+(nWidth*nCh)*row+col*nCh+ch);
	  nCount++;
	}
}
