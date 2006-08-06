/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2006  Shiqi Yu
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

int
int_imfinfo(char *fname)
{
  int mL, nL, lL;
  int mxL, nxL;

  int mR, nR, lR;
  int One = 1;
  int element = 0;
  static char *NameStr[]= { "V",
			"Filename",
			"FileSize",
			"Width",
			"Height",
			"BitDepth",
			"ColorType"  };
  char * pFilename;
  double fValue;
  double *pfValue = &fValue;
  char sValue[16];
  char **psValue = &sValue;
  
  IplImage * pImage = NULL;

  CheckRhs(1,1);
  CheckLhs(1,1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  pFilename = cstk(lR);
  //open image file
  pImage = cvLoadImage(pFilename, -1);

  //if failed to open the video file
  if(!pImage)
    {
      Scierror(999, "%s: Can not open image file %s.\r\n", fname, pFilename);
      return -1;
    }
  
  mL = 7;
  nL = 1;

  CreateVar(2,"m", &mL, &nL, &lL);
 
  CreateListVarFromPtr(2, ++element, "S", &mL, &nL, NameStr);
  //store file name
  //TODO: the path should be absolute path
  mxL = strlen(cstk(lR));
  CreateListVarFromPtr(2, ++element, "c", &mxL, &One, &pFilename);

  //get the file size
  struct stat fileStat;
  if( stat(pFilename, &fileStat) != 0)
    {
      Scierror(999, "%s: Can not get the information of file %s.\r\n", fname, pFilename);
      cvReleaseImage(&pImage);
      return -1;
    }
  fValue = (double)(fileStat.st_size);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  //Width
  fValue = (double)(pImage->width);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  //Height
  fValue = (double)(pImage->height);
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  //BitDepth
  fValue = (double)(pImage->depth & 0x0FFFFFFF );
  CreateListVarFromPtr(2, ++element, "d", &One, &One, &pfValue);

  //ColorType
  if( pImage->nChannels == 1 )
    {
      sprintf(sValue, "grayscale");
      mxL = 9;
    }
  else if( pImage->nChannels == 3 || pImage->nChannels == 4)
    {
      sprintf(sValue, "truecolor");
      mxL = 9;
    }
  else
    {
      mxL = 0;
    }
  CreateListVarFromPtr(2, ++element, "c", &mxL, &One, &psValue );
 
  cvReleaseImage(&pImage);

  LhsVar(1) =2 ;
  return 0;
}
