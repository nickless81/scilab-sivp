/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2005  Shiqi Yu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***********************************************************************/


#include"common.h"

/**************************************************
 * nRow: the first dim
 * nCol: the second dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 * nType: I_CHAR, I_INT16, I_INT32, I_UCHAR,  I_UINT16,  I_UINT32
 **************************************************/
BOOL
Create2DIntMat(int nPos, int nRow, int nCol, void * pData, int nType)
{
  SciIntMat IntMat;

  //create SciIntMat for the image data
  IntMat.m = nRow;
  IntMat.n = nCol;
  IntMat.l = -1; /* dimensions matrix not in scilab stack */
  IntMat.it = nType;
  IntMat.D = pData;

  CreateVarFromPtr(nPos,"I",&(IntMat.m), &(IntMat.n), &IntMat ); 
  return TRUE;
}


/**************************************************
 * Create a 2D nRow * nCol float matrix(single precision, 4bytes)
 * nRow: the first dim
 * nCol: the second dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 **************************************************/
BOOL
Create2DFloatMat(int nPos, int nRow, int nCol, float * pData)
{
  CreateVarFromPtr(nPos,"r",&nRow, &nCol, &pData); 
  return TRUE;
}

/**************************************************
 * Create a 2D nRow * nCol double matrix(double precision, 8bytes)
 * nRow: the first dim
 * nCol: the second dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 **************************************************/
BOOL
Create2DDoubleMat(int nPos, int nRow, int nCol, double * pData)
{
  CreateVarFromPtr(nPos,"d",&nRow, &nCol, &pData); 
  return TRUE;
}

/**************************************************
 * Create a 3D nRow * nCol * nCh integer matrix
 * nRow: the first dim
 * nCol: the second dim
 * nCh:  the third dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 * nType: I_CHAR, I_INT16, I_INT32, I_UCHAR,  I_UINT16,  I_UINT32
 **************************************************/
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
  Dims.n = 3;
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
  IC_INT32(Dims.D)[2] = nCh;

  //create SciIntMat for the image data
  IntData.m = nRow ;
  IntData.n = nCol * nCh;
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

/**************************************************
 * Create a 3D nRow * nCol * nCh float matrix (single precision, 4 bytes)
 * nRow: the first dim
 * nCol: the second dim
 * nCh:  the third dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 **************************************************/
BOOL 
Create3DFloatMat(int nPos, int nRow, int nCol, int nCh, float* pData)
{
  static char *Str[]= { "hm","dims","entries"}; 
  int m1=1,n1=3;
  int mL=3,nL=1,lL;
  int un=1;
  int nSize = nRow * nCol * nCh;

  SciIntMat Dims;

  //create SciIntMat for dimentional information
  Dims.m = 1;
  Dims.n = 3;
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
  IC_INT32(Dims.D)[2] = nCh;


  CreateVar(nPos,"m", &mL, &nL, &lL);
  CreateListVarFromPtr(nPos,1,"S", &m1, &n1, Str);
  CreateListVarFromPtr(nPos,2,"I",&(Dims.m), &(Dims.n), &Dims); 
  CreateListVarFromPtr(nPos,3,"r", &nSize, &un, &pData );

/*   free memory */
  free(Dims.D);

  return TRUE;
}

/**************************************************
 * Create a 3D nRow * nCol * nCh double matrix (double precision, 8 bytes)
 * nRow: the first dim
 * nCol: the second dim
 * nCh:  the third dim
 * pData: pData is the data for matrix, and it can be freed after this function is called.
 **************************************************/
BOOL 
Create3DDoubleMat(int nPos, int nRow, int nCol, int nCh, double* pData)
{
  static char *Str[]= { "hm","dims","entries"}; 
  int m1=1,n1=3;
  int mL=3,nL=1,lL;
  int un=1;
  int nSize = nRow * nCol * nCh;

  SciIntMat Dims;

  //create SciIntMat for dimentional information
  Dims.m = 1;
  Dims.n = 3;
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
  IC_INT32(Dims.D)[2] = nCh;


  CreateVar(nPos,"m", &mL, &nL, &lL);
  CreateListVarFromPtr(nPos,1,"S", &m1, &n1, Str);
  CreateListVarFromPtr(nPos,2,"I",&(Dims.m), &(Dims.n), &Dims); 
  CreateListVarFromPtr(nPos,3,"d", &nSize, &un, &pData );

/*   free memory */
  free(Dims.D);

  return TRUE;
}



void iplimg2mat(IplImage * pImage, void * pMat)
{

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

/* convert data from columnwise to row-wise */
void mat2img(unsigned char * pMat, unsigned char *pImg, int nWidth, int nHeight, int nCh)
{
  int row, col, ch;
  long offset;
  long nCount = 0;

  for(row=0; row < nHeight; row++)
    for(col=0; col < nWidth; col++)
      for (ch=0; ch < nCh; ch++)
	{
	  offset = ch*(nWidth*nHeight) + col * nHeight + row;
	  pImg[nCount] = pMat[offset];
	  nCount++;
	}
}
