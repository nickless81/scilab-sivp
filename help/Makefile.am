##
## -------------------------------------------------------------------------
## SIVP - Scilab Image and Video Processing toolbox
## Copyright (C) 2008  Shiqi Yu
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

helppages_xml = en_US/addframe.xml en_US/avicloseall.xml en_US/aviclose.xml en_US/avifile.xml en_US/aviinfo.xml en_US/avilistopened.xml en_US/aviopen.xml en_US/avireadframe.xml en_US/camopen.xml en_US/camshift.xml en_US/corr2.xml en_US/detecteyes.xml en_US/detectfaces.xml en_US/detectforeground.xml en_US/edge.xml en_US/filter2.xml en_US/fspecial.xml en_US/hsv2rgb.xml en_US/im2bw.xml en_US/im2double.xml en_US/im2int16.xml en_US/im2int32.xml en_US/im2int8.xml en_US/im2uint16.xml en_US/im2uint8.xml en_US/imabsdiff.xml en_US/imadd.xml en_US/imcomplement.xml en_US/imcrop.xml en_US/imdivide.xml en_US/imfilter.xml en_US/imfinfo.xml en_US/imhist.xml en_US/imlincomb.xml en_US/immultiply.xml en_US/imnoise.xml en_US/impyramid.xml en_US/imread.xml en_US/imresize.xml en_US/imshow.xml en_US/imsubtract.xml en_US/imwrite.xml en_US/ind2rgb.xml en_US/mat2gray.xml en_US/mean2.xml en_US/meanshift.xml en_US/ntsc2rgb.xml en_US/rectangle.xml en_US/rgb2gray.xml en_US/rgb2hsv.xml en_US/rgb2ntsc.xml en_US/rgb2ycbcr.xml en_US/std2.xml en_US/xs2im.xml en_US/ycbcr2rgb.xml

helpdir=@TOOLBOXDIR@/jar
help_DATA = ../jar/scilab_en_US_help.jar

EXTRA_DIST = $(helppages_xml) en_US/build_help.sce buildhelp.sce 

all: $(help_DATA)

$(help_DATA): buildhelp.sce $(helppages_xm)
	$(SCIEXE) -nw -nb -f buildhelp.sce

clean:
	rm -rf en_US/scilab_en_US_help en_US/master_help.xml