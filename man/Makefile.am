## Makefile.am -- Process this file with automake to produce Makefile.in
## Copyright (C) 2005 Shiqi Yu
## Copyright (C) 2003 Ricardo Fabbri
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

IMG_IO_MAN=imread.xml imwrite.xml
AVI_IO_MAN= #aviinfo.xml aviopen.xml aviclose.xml avicloseall.xml avilistopened.xml avireadframe.xml camopen.xml
IMG_GUI_MAN=imshow.xml
IMG_TRAN_MAN=imresize.xml
IMG_PROC_MAN= 

manpages_xml = $(IMG_IO_MAN) $(AVI_IO_MAN) $(IMG_GUI_MAN) $(IMG_TRAN_MAN) $(IMG_PROC_MAN)

manpages_cat  = $(manpages_xml:.xml=.cat)

manpages_html = $(manpages_xml:.xml=.htm)

SCIDIR=@SCIDIR@

helpdir=@TOOLBOXDIR@/man
help_DATA = $(manpages_html) whatis.htm 

EXTRA_DIST = $(manpages_xml) html-sivp.xsl mansivp.dtd Makefile.am.input 

%.htm: %.xml
	@echo "Creating html help files"
	@$(SCIDIR)/bin/scilab -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','whatis');quit"
	@$(SCIDIR)/bin/scilab -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','html');quit"

Makefile.am: Makefile.am.input
	$(top_srcdir)/config/subst_input_files.sh

clean-local:
	rm -f *.htm
