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
libdir=@TOOLBOXDIR@/lib

lib_LTLIBRARIES = libsivp.la

AM_CPPFLAGS = @LIBRARY_EXTRA_CPPFLAGS@

#vdrw.c goodfeaturestotrack.c 
#
IMG_IO_SRC=imread.c imwrite.c test.c mat2utfimg.c
AVI_IO_SRC=aviinfo.c aviopen.c aviclose.c avicloseall.c avilistopened.c avireadframe.c camopen.c
IMG_TRAN_SRC=imresize.c
IMG_PROC_MAN= canny.c sobel.c    convert.c laplace.c precornerdetec.c imsmooth.c threshold.c adaptativethreshold.c erode.c dilate.c pyrdown.c pyrup.c xor.c not.c cmp.c hough.c

libsivp_la_SOURCES = libsivp.c common.c sivp_init.c $(IMG_IO_SRC)  $(AVI_IO_SRC) $(IMG_TRAN_SRC) $(IMG_PROC_MAN)

libsivp_la_LDFLAGS = -no-undefined -version-info 0:0:0 -release @PACKAGE_VERSION@

libsivp_la_LIBADD = @LIBRARY_EXTRA_LIBS@

EXTRA_DIST = common.h

libsivp.c: ilib_gen_gateway.sce
	$(SCIDIR)/bin/scilab -nw -nb -f ilib_gen_gateway.sce


