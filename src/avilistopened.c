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

//TODL: list filenames
int int_avilistopened(char * fname)
{
  int element;
  int One = 1;
  int i;

  int count = 0;
  int offset = 0;

  double dIndices[MAX_AVI_FILE_NUM];
  double * dIdx = dIndices;
  char sFileNames[MAX_AVI_FILE_NUM * MAX_FILENAME_LENGTH];
  char * sFN = sFileNames;

  CheckRhs(0, 0);
  CheckLhs(1, 1);

  for (i = 0; i < MAX_AVI_FILE_NUM; i++)
    {
      if(OpenedAviCap[i].video.cap)
	{
	  dIndices[count]=i+1;

      //strcpy(sFileNames[count],  OpenedAviCap[i].filename, MAX_FILENAME_LENGTH);
      strncpy(sFileNames+offset, OpenedAviCap[i].filename, MAX_FILENAME_LENGTH);
	  offset += strlen(OpenedAviCap[i].filename)+1;
	  count++;
	}
    }


  CreateVarFromPtr(1, "d", &count, &One, &dIdx);
  //CreateVarFromPtr(2, "S", &count, &One, &sFN);

  LhsVar(1) =1;
  //  LhsVar(2) =2;

  return 0;
}
