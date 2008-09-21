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

ALL_SRC=$(wildcard *.c *.h)

libsivpdir=@TOOLBOXDIR@/lib

libsivp_DATA = libsivp.so
EXTRA_DIST = $(ALL_SRC)

all: libsivp.so

libsivp.so: builder.sce
	$(SCIEXE) -nwni -nb -f builder.sce
	rm -f loader.sce
	rm -f libsivp.c

clean:
	rm -f *.a *.o *.lo *.so stamp-h1 Makelib

distclean:
	rm -fr *.a *.o *.lo *.so stamp-h1 Makelib Makefile.in Makefile Makefile.win builder.sce .libs


