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
#include "gw_sivp.h"

int int_imread(char * fname)
{
  int mR, nR, lR;

  IplImage * pImage;

  CheckRhs(1, 1);
  CheckLhs(1, 1);

  GetRhsVar(1, "c", &mR, &nR, &lR);

  // fix default mode for compatibility with previous version of SIVP
  pImage = cvLoadImage(cstk(lR), 1);

  /* if load image failed */
  if(pImage == NULL)
    {
      Scierror(999, "%s: Can not open file %s.\r\n", fname, cstk(lR));
      return -1;
    }

  IplImg2Mat(pImage, 2);

  LhsVar(1) = 2;

  cvReleaseImage(&pImage);

  return 0;
}

