/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2005-2008  Shiqi Yu
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
int int_avireadframe(char * fname)
{
  int mR1, nR1, lR1;
  int mR2, nR2, lR2;

  int nFile;
  int nFrameIdx = -1;

  IplImage * pImage;

  double tmp;

  CheckRhs(1,2);
  CheckLhs(0,1);

  GetRhsVar(1, "i", &mR1, &nR1, &lR1);
  CheckDims(1, mR1, nR1, 1, 1);
  if(Rhs == 2)
    {
      GetRhsVar(2, "i", &mR2, &nR2, &lR2);
      CheckDims(2, mR2, nR2, 1, 1);

      nFrameIdx = *((int *)(istk(lR2)));
      nFrameIdx -= 1;
    }

  nFile = *((int *)(istk(lR1)));
  nFile -= 1;

  if (!(nFile >= 0 && nFile < MAX_AVI_FILE_NUM))
    {
      Scierror(999, "%s: The argument should >=1 and <= %d.\r\n", fname, MAX_AVI_FILE_NUM);
      return -1;
    }

  if ( OpenedAviCap[nFile].iswriter )
    {
      Scierror(999, "%s: The opened file is for writing.\r\n", fname);
      return -1;
    }


  if(! OpenedAviCap[nFile].video.cap)
    {
      Scierror(999, "%s: The %d'th file is not opened.\r\n Please use avilistopened command to show opened files.\r\n",
	       fname, nFile+1);
      return -1;
    }
  if(Rhs ==2 && nFrameIdx < 0)
    {
      Scierror(999, "%s: The frame index should >=1, but your input is %d.\r\n", fname, nFrameIdx+1);
      return -1;
    }


  if(nFrameIdx >=0)
    cvSetCaptureProperty( OpenedAviCap[nFile].video.cap, CV_CAP_PROP_POS_FRAMES, nFrameIdx);

  pImage = cvQueryFrame(OpenedAviCap[nFile].video.cap);

  if (! pImage)
  {
      Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
      sciprint("Warning: No frame.\r\n", fname);
  }
  else if(! IplImg2Mat(pImage, Rhs+1))
    {
      Scierror(999, "%s: SIVP interal error.\r\n", fname);
      return -1;
    }

  LhsVar(1) = Rhs+1;

  //pImage can not be released!!

  return 0;
}
