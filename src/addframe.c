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

/* read a frame from an opened video file*/
int int_addframe(char * fname)
{
  int mR1, nR1, lR1;

  int nFile;
  IplImage * pImage;

  CheckRhs(2,2);
  CheckLhs(1,1);

  //get opened file index
  GetRhsVar(1, "i", &mR1, &nR1, &lR1);
  CheckDims(1, mR1, nR1, 1, 1);
  nFile = *((int *)(istk(lR1)));
  nFile -= 1;

  //check whether the nFile'th is a video writer
  if (!(nFile >= 0 && nFile < MAX_AVI_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
      return -1;
    }

  if (! OpenedAviCap[nFile].iswriter )
    {
      Scierror(999, "%s: The opened file is not for writing.\r\n", fname);
      return -1;
    }

  if(! OpenedAviCap[nFile].video.writer)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use avilistopened command to show opened files.\r\n",
	       fname, nFile+1);
      return -1;
    }

  //load the input image
  pImage = Mat2IplImg(2);

  if(pImage == NULL)
    {
      Scierror(999, "%s: Internal error for getting the image data.\r\n", fname);
      return -1;
    }

  if( cvWriteFrame(OpenedAviCap[nFile].video.writer, pImage) != 0)
    {
      Scierror(999, "%s: Write frame error, please check input image size and depth.\r\n", fname);
      return -1;
    }

  LhsVar(1) = 1;

  cvReleaseImage(&pImage);
  return 0;
}
