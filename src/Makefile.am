##
## -------------------------------------------------------------------------
## SIVP - Scilab Image and Video Processing toolbox
## Copyright (C) 2005-2006  Shiqi Yu, Shulin Shang
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

ALL_SRC=addframe.c avicloseall.c aviclose.c avifile.c aviinfo.c avilistopened.c aviopen.c avireadframe.c camopen.c camshift.c canny.c common.c cvtcolor.c detectforeground.c detectobjects.c filter2.c imabsdiff.c imadd.c imdivide.c imfilter.c imfinfo.c immultiply.c impyramid.c imread.c imresize.c imsubtract.c imwrite.c ind2rgb.c mat2utfimg.c meanshift.c sivp_init.c sobel.c test.c 

libsivpdir=@TOOLBOXDIR@/lib

libsivp_DATA = libsivp.so
EXTRA_DIST = $(ALL_SRC) common.h

all: libsivp.so

libsivp.so: builder.sce
	$(SCIEXE) -nwni -nb -f builder.sce
	rm -f loader.sce
	rm -f libsivp.c

clean:
	rm -f *.a *.o *.lo *.so stamp-h1 Makelib libsivp.c loader.sce

distclean:
	rm -fr *.a *.o *.lo *.so stamp-h1 Makelib Makefile Makefile.win builder.sce .libs


