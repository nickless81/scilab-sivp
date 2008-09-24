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

manpages_xml = addframe.xml avicloseall.xml aviclose.xml avifile.xml aviinfo.xml avilistopened.xml aviopen.xml avireadframe.xml camopen.xml camshift.xml corr2.xml detecteyes.xml detectfaces.xml detectforeground.xml edge.xml filter2.xml fspecial.xml hsv2rgb.xml im2bw.xml im2double.xml im2int16.xml im2int32.xml im2int8.xml im2uint16.xml im2uint8.xml imabsdiff.xml imadd.xml imcomplement.xml imcrop.xml imdivide.xml imfilter.xml imfinfo.xml imhist.xml imlincomb.xml immultiply.xml imnoise.xml impyramid.xml imread.xml imresize.xml imshow.xml imsubtract.xml imwrite.xml ind2rgb.xml mat2gray.xml mean2.xml meanshift.xml ntsc2rgb.xml rectangle.xml rgb2gray.xml rgb2hsv.xml rgb2ntsc.xml rgb2ycbcr.xml std2.xml xs2im.xml ycbcr2rgb.xml 

manpages_cat  = $(manpages_xml:.xml=.cat)

manpages_html = $(manpages_xml:.xml=.htm)

SCIDIR=@SCIDIR@

helpdir=@TOOLBOXDIR@/man
help_DATA = $(manpages_html) whatis.htm 

EXTRA_DIST = $(manpages_xml) html-sivp.xsl mansivp.dtd Makefile.am.input 

%.htm: %.xml
	@echo "Creating html help files"
	@$(SCIEXE) -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','whatis');quit"
	@$(SCIEXE) -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','html');quit"
#@$(SCIDIR)/bin/scilab -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','whatis');quit"
#@$(SCIDIR)/bin/scilab -nwni -nb -e "exec('$(top_srcdir)/config/sivp_xmltohtml.sci');%helps=[PWD,'SIVP';%helps];sivp_xmltohtml(PWD,'SIVP','html-sivp.xsl','html');quit"

Makefile.am: Makefile.am.input
	$(top_srcdir)/config/subst_input_files.sh

clean-local:
	rm -f *.htm
