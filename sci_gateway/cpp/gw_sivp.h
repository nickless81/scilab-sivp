/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2012 - DIGITEO - Allan CORNET
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
#ifndef __GW_SIVP_H__
#define __GW_SIVP_H__

#ifdef __cplusplus
extern "C" {
#endif

int int_impyramid(char *fname);
int int_detectforeground(char *fname);
int int_meanshift(char *fname);
int int_camshift(char *fname);
int int_detectobjects(char *fname);
int int_ind2rgb(char *fname);
int int_cvtcolor(char *fname);
int int_sobel(char *fname);
int int_canny(char *fname);
int int_mat2utfimg(char *fname);
int int_filter2(char *fname);
int int_imfilter(char *fname);
int int_imdivide(char *fname);
int int_immultiply(char *fname);
int int_imsubtract(char *fname);
int int_imadd(char *fname);
int int_imabsdiff(char *fname);
int int_imresize(char *fname);
int int_addframe(char *fname);
int int_avireadframe(char *fname);
int int_avilistopened(char *fname);
int int_avicloseall(char *fname);
int int_aviclose(char *fname);
int int_avifile(char *fname);
int int_camopen(char *fname);
int int_aviopen(char *fname);
int int_aviinfo(char *fname);
int int_imfinfo(char *fname);
int int_imwrite(char *fname);
int int_imread(char *fname);
int int_sivp_init(char *fname);
int int_test(char *fname);

#ifdef __cplusplus
};
#endif

#endif /* __GW_SIVP_H__ */
