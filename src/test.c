/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2005  Vincent Etienne
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

int int_test(char * fname)
{
  CheckRhs(1,1);
  CheckLhs(0,1);

  IplImage * pImg;
  pImg = Mat2IplImg(1);
  if(pImg != NULL)
    {
      cvNamedWindow( "Image view", 1 );
      cvShowImage( "Image view", pImg );
      cvWaitKey(10); // very important, contains event processing loop inside
      //cvDestroyWindow( "Image view" );
      cvReleaseImage( &pImg );
    }
  else
    {
      sciprint("NULL image\r\n");
    }

  return 0;

}
