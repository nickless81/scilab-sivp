##
## -------------------------------------------------------------------------
## SIVP - Scilab Image and Video Processing toolbox
## Copyright (C) 2005  Shiqi Yu
## Copyright (C) 2003 Ricardo Fabbri
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
## -------------------------------------------------------------------------
##
macros_sci = corr2.sci detectfaces.sci detectlefteyes.sci detectrighteyes.sci edge.sci fspecial.sci hsv2rgb.sci im2bw.sci im2double.sci im2int16.sci im2int32.sci im2int8.sci im2uint16.sci im2uint8.sci imabsdiff.sci imadd.sci imcomplement.sci imcrop.sci imdivide.sci imhist.sci imlincomb.sci immultiply.sci imnoise.sci imresize.sci imshow.sci imsubtract.sci imwrite.sci isbw.sci mat2gray.sci mean2.sci ntsc2rgb.sci rectangle.sci rgb2gray.sci rgb2hsv.sci rgb2ntsc.sci rgb2ycbcr.sci std2.sci stdev2.sci xs2im.sci ycbcr2rgb.sci 

macros_bin = $(macros_sci:.sci=.bin)

macrodir=@TOOLBOXDIR@/macros
macro_DATA = $(macros_bin) names lib imshow.tcl

EXTRA_DIST = $(macros_sci)  imshow.tcl buildmacros.sce



$(macros_bin) names lib: 	$(macros_sci) 
	$(SCIEXE) -nw -nb -f buildmacros.sce ;

clean-local:
	rm -f tmp_* *.bin lib names Lib.mak Macros.mak genlib Sci_Name Sci_Lib
