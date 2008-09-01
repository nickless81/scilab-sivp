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

IMG_IO_SRC=imread.c imwrite.c imfinfo.c test.c mat2utfimg.c ind2rgb.c
AVI_IO_SRC=aviinfo.c aviopen.c avifile.c aviclose.c avicloseall.c avilistopened.c avireadframe.c camopen.c addframe.c
IMG_TRAN_SRC=imresize.c imabsdiff.c imadd.c imsubtract.c immultiply.c imdivide.c
IMG_FILTER_SRC=sobel.c imfilter.c filter2.c canny.c  
IMG_COLOR_SRC=cvtcolor.c
IMG_APP=detectfaces.c

ALL_SRC=libsivp.c common.c sivp_init.c $(IMG_IO_SRC)  $(AVI_IO_SRC) $(IMG_TRAN_SRC) $(IMG_FILTER_SRC) $(IMG_COLOR_SRC) $(IMG_APP)

libdir=@TOOLBOXDIR@/lib

lib_LTLIBRARIES = libsivp.la

AM_CPPFLAGS = @LIBRARY_EXTRA_CPPFLAGS@

libsivp_la_SOURCES = $(ALL_SRC)

libsivp_la_LDFLAGS = -no-undefined -version-info 0:0:0 -release @PACKAGE_VERSION@

libsivp_la_LIBADD = @LIBRARY_EXTRA_LIBS@

EXTRA_DIST = common.h 

libsivp.c: ilib_gen_gateway.sce
	rm -f libsivp.c
	$(SCIEXE) -nw -nb -f ilib_gen_gateway.sce


