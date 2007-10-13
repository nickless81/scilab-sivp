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

//create video file

#include "common.h"

int int_avifile(char *fname)
{
  int mL, nL;
  int mR1, nR1, lR1;
  int mR2, nR2, lR2;
  int mR3, nR3, lR3;
  int nPos = 0;

  int nCurrFile = 0;
  int *pret = &nCurrFile;
  int nWidth, nHeight;
  int nFPS = 25;

  CheckRhs(2,3);
  CheckLhs(1,1);

  //get file name
  GetRhsVar(++nPos, "c", &mR1, &nR1, &lR1);

  //get dims
  GetRhsVar(++nPos, "i", &mR2, &nR2, &lR2);
  CheckDims(nPos, mR2, nR2, 2, 1);
  nWidth = *((int *)(istk(lR2)));
  nHeight = *(( (int *)(istk(lR2)) )+1);

  //get fps
  if(Rhs == 3)
    {
      GetRhsVar(++nPos, "i", &mR3, &nR3, &lR3);
      CheckDims(nPos, mR3, nR3, 1, 1);
      nFPS = *((int *)(istk(lR3)));
    }

  //find empty pointer
  for (nCurrFile = 0; nCurrFile < MAX_AVI_FILE_NUM; nCurrFile++)
    {
      if( !(OpenedAviCap[nCurrFile].video.writer))
	break;
    }

  if( nCurrFile ==  MAX_AVI_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files (or cameras) opened. Use aviclose or avicloseall to close some files (cameras).\r\n", fname);
      return -1;
    }


  OpenedAviCap[nCurrFile].video.writer = cvCreateVideoWriter(cstk(lR1), 
							     CV_FOURCC('X','V','I','D'),
							     (double)nFPS, 
							     cvSize(nWidth, nHeight),
							     1);
  if(OpenedAviCap[nCurrFile].video.writer == 0)
    {
      Scierror(999, "%s: Can not create video file %s.\r\n", fname, cstk(lR1));
      return -1;
    }

  strcpy(OpenedAviCap[nCurrFile].filename, cstk(lR1));
  OpenedAviCap[nCurrFile].iswriter = 1;
  OpenedAviCap[nCurrFile].width = nWidth;
  OpenedAviCap[nCurrFile].height = nHeight;

  //the output is the opened index
  nCurrFile += 1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(++nPos, "i", &mL, &nL, &pret);
  
  LhsVar(1) =nPos ;
  return 0;
}
