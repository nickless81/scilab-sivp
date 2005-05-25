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


/************************************************************
 * convert IplImage to SCI matrix
************************************************************/
BOOL IplImg2Mat(IplImage * pImage, int nPos)
{
  void * pMatData;
  int nBytes;
  int nType;
  
  if(pImage == NULL)
    return FALSE;

  /*how many bytes per pixel per channel*/
  nBytes = pImage->depth;
  if (nBytes > IPL_DEPTH_SIGN)
    nBytes -= IPL_DEPTH_SIGN;
  nBytes = nBytes >> 3;
  
  /*alloc memory for matrix data*/
  pMatData = malloc(pImage->width * pImage->height * pImage->nChannels * nBytes);
  if(pMatData == NULL)
    return FALSE;

  ImgData2MatData(pImage, pMatData);

  /*convert IplImage data type to scilab data type*/
  nType = IplType2SciType(pImage->depth);
  if (nType <= 0)
    {
      free(pMatData);
      return FALSE;
    }
  /*create matrix for scilab*/
  if(pImage->nChannels == 1)
    {
      switch(nType){
      case I_CHAR:
      case I_UCHAR:
      case I_INT16:
      case I_UINT16:
      case I_INT32:
	Create2DIntMat(nPos, pImage->height, pImage->width, pMatData, nType);
	break;
      case SIVP_FLOAT:
	Create2DFloatMat(nPos,pImage->height, pImage->width, pMatData);
	break;
      case SIVP_DOUBLE:
	Create2DDoubleMat(nPos,pImage->height, pImage->width, pMatData);
	break;
      }
    }
  else
    {
      switch(nType){
      case I_CHAR:
      case I_UCHAR:
      case I_INT16:
      case I_UINT16:
      case I_INT32:
	Create3DIntMat(nPos, pImage->height, pImage->width, pImage->nChannels, pMatData, nType);
	break;
      case SIVP_FLOAT:
	Create3DFloatMat(nPos,pImage->height, pImage->width, pImage->nChannels, pMatData);
	break;
      case SIVP_DOUBLE:
	Create3DDoubleMat(nPos,pImage->height, pImage->width, pImage->nChannels, pMatData);
	break;
      }
    }

  /*free matrix data*/
  free(pMatData);
  return TRUE;
}

/************************************************************
 * change the data order from row-wise to column-wise
 ************************************************************/
BOOL ImgData2MatData(IplImage * pImage, void * pMatData)
{
  if (pImage == NULL || pMatData == NULL)
    return FALSE;
  //  IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16U,
  //IPL_DEPTH_16S, IPL_DEPTH_32S, IPL_DEPTH_32F and IPL_DEPTH_64F 
  int row, col, ch;
  long nCount = 0;
  int nBytes;

  char * pSrc = (char*)(pImage->imageData);
  char * pDst = (char*)pMatData;

  /*how many bytes per pixel per channel*/
  nBytes = pImage->depth;
  if (nBytes > IPL_DEPTH_SIGN)
    nBytes -= IPL_DEPTH_SIGN;
  nBytes = nBytes >> 3;

  for(ch = 0; ch < pImage->nChannels ; ch++) //the order of IplImage is BGR
    for(col =0; col < pImage->width; col++)
      for(row = 0; row < pImage->height; row++)
	{
	  memcpy(pDst+nCount, pSrc + pImage->widthStep*row + col*pImage->nChannels*nBytes + (pImage->nChannels-ch-1), nBytes );
	  nCount += nBytes;
	}


  return TRUE;
}

/************************************************************
 * unsigned int32 is not supported (no this type in OpenCV)
 ************************************************************/
int IplType2SciType(int IplType)
{
  switch(IplType)    {
  case IPL_DEPTH_8U:  return I_UCHAR;
  case IPL_DEPTH_8S:  return I_CHAR;
  case IPL_DEPTH_16U: return I_UINT16;
  case IPL_DEPTH_16S: return I_INT16;
  case IPL_DEPTH_32S: return I_INT32;
  case IPL_DEPTH_32F: return SIVP_FLOAT;
  case IPL_DEPTH_64F: return SIVP_DOUBLE;
  default: return 0;
  }
}

/************************************************************
 * unsigned int32 is not supported (no this type in OpenCV)
 ************************************************************/
int SciType2IplType(int SciType)
{
  switch(SciType)    {
  case I_UCHAR:  return IPL_DEPTH_8U;
  case I_CHAR:   return IPL_DEPTH_8S;
  case I_UINT16: return IPL_DEPTH_16U;
  case I_INT16:  return IPL_DEPTH_16S;
  case I_INT32:  return IPL_DEPTH_32S;
  case SIVP_FLOAT:  return IPL_DEPTH_32F;
  case SIVP_DOUBLE: return IPL_DEPTH_64F;
  default: return 0;
  }
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
