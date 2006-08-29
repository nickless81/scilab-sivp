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

/* close an opened file */
int int_aviclose(char *fname)
{
  int mR, nR, lR;
  int nFile;
  
  CheckRhs(1,1);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR, &nR, &lR);
  CheckDims(1, mR, nR, 1, 1);

  nFile = *((int *)(istk(lR)));
  nFile = nFile - 1;

  if (nFile >= 0 && nFile < MAX_AVI_FILE_NUM)
    {
      if(OpenedAviCap[nFile].video.cap)
	{
	  cvReleaseCapture(&(OpenedAviCap[nFile].video.cap));
	  memset(OpenedAviCap[nFile].filename, 0, sizeof(OpenedAviCap[nFile].filename) );
	}
      else
	{
	  Scierror(999, "%s: The %d'th file is not opened.\r\n", fname, nFile+1);
	}
    }
  else
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
    }

  return 0;
}
