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


#include "common.h"

int int_aviopen(char *fname)
{
  int mL, nL;
  int mR, nR, lR;
  int nCurrFile = 0;
  int *pret = &nCurrFile;

  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  for (nCurrFile = 0; nCurrFile < MAX_AVI_FILE_NUM; nCurrFile++)
    {
      if( !(OpenedCap[nCurrFile].cap))
	break;
    }

  if( nCurrFile ==  MAX_AVI_FILE_NUM)
    {
      Scierror(999, "%s: Too many video files (or cameras) opened. Use aviclose or avicloseall to close some files (cameras).\r\n", fname);
      return -1;
    }


  OpenedCap[nCurrFile].cap = cvCaptureFromFile(cstk(lR));
  if(OpenedCap[nCurrFile].cap == 0)
    {
      Scierror(999, "%s: Can not open video file %s. \nMaybe the codec of the video can not be handled or the file does not exist.\r\n", fname, cstk(lR));
      return -1;
    }

  strcpy(OpenedCap[nCurrFile].filename, cstk(lR));
  //the output is the opened index
  nCurrFile += 1;

  mL = 1;
  nL = 1;
  CreateVarFromPtr(2, "i", &mL, &nL, &pret);
  
  LhsVar(1) =2 ;
  return 0;
}
