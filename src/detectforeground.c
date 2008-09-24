/*****************************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2008  Jia Wu
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
 *****************************************************************************/


#include "common.h"


/**********************************************************************
 * [fg]=detectforeground(im,method) or [fg]=detectforeground(im)
 * fg is the foreground image.
 * method is different background modeling algorithms.
 **********************************************************************/

int int_detectforeground(char *fname)
{
   static CvBGStatModel *bg_model = NULL;
 
   double tmp;
   IplImage *pSrcImg = NULL;

   CheckRhs(1, 2);
   CheckLhs(1, 1);   

   //load input image
   pSrcImg = Mat2IplImg(1);
   if(pSrcImg == NULL)
    {
      Scierror(999, "%s: Internal error of getting image data.\r\n", fname);
      return -1;
    }

    //create background model
    if(Rhs == 2)  
     {
       int mR, nR, lR;
       GetRhsVar(2, "c", &mR, &nR, &lR);

       if(strncmp(cstk(lR), "LI", MAX_FILENAME_LENGTH) == 0)  //ACM MM2003
         {
          if(bg_model)
            cvReleaseBGStatModel(&bg_model);
          bg_model = cvCreateFGDStatModel(pSrcImg, NULL);
           
          Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
          }
        else if(strncmp(cstk(lR), "GMM", MAX_FILENAME_LENGTH) == 0)  //GMM  
          {
          if(bg_model)
            cvReleaseBGStatModel(&bg_model);
          bg_model = cvCreateGaussianBGModel(pSrcImg, NULL);
           
          Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
          }
        else
          {
          Scierror(999, "%s: The function now only supports 'LI' and 'GMM' background modeling. Please input the right background modeling method name.\r\n", fname);
          return -1;
          }
     }
    //foreground detection or initialize background model
    else if(Rhs == 1)
     {
       //initialize background model. "LI" is the default method
       if(bg_model == NULL)
         {
          bg_model = cvCreateFGDStatModel(pSrcImg, NULL);  
          
          Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
         }
       else if((bg_model->foreground->width != pSrcImg->width) || (bg_model->foreground->height != pSrcImg->height))
         {   
          cvReleaseBGStatModel(&bg_model);
          bg_model = cvCreateFGDStatModel(pSrcImg, NULL);  
          
          Create2DDoubleMat(Rhs+1, 0, 0, &tmp);
         }
       //foreground detection
       else
         {
           cvUpdateBGStatModel(pSrcImg, bg_model);

           IplImg2Mat(bg_model->foreground, Rhs+1);
         }   
     }

    LhsVar(1) = Rhs+1;

    return 0;
}


