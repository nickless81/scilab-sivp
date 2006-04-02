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
macros_sci = imshow.sci imcrop.sci imabsdiff.sci \
	mean2.sci corr2.sci std2.sci \
	im2bw.sci im2int8.sci im2uint8.sci im2int16.sci im2uint16.sci im2int32.sci im2double.sci \
	mat2gray.sci

macros_bin = $(macros_sci:.sci=.bin)

macrodir=@TOOLBOXDIR@/macros
macro_DATA = $(macros_bin) genlib names lib imshow.tcl

EXTRA_DIST = $(macros_sci)  imshow.tcl

## dist_macro_DATA = $(macros_sci) sip-intro.dem sipdemo_gui.dem interferometry_gui.dem mogrify.dem


#
# The following code is an adaptation to Automake from @SCIDIR@/macros/Make.lib
#

%.bin : %.sci
	@SCI=$(SCIDIR);export SCI;$(SCIDIR)/bin/scilab -comp  $<

##.sci.bin:
##	@SCI=$(SCIDIR);export SCI;$(SCIDIR)/bin/scilab -comp  $*.sci

lib: $(macros_sci)
	@echo $? > tmp_comp ;$(SCIDIR)/macros/Lib Xtmp_comp; rm -f tmp_comp
	@rm -f `cat tmp_Bin`
	@echo Starting Compilation 
	@if ( $(SCIDIR)/util/scibatch $(SCIDIR) tmp_Macros ) ;\
	then echo generating lib and names;\
	     $(SCIDIR)/util/scibatch $(SCIDIR) genlib;\
	else echo "Compilation failed"; rm -f `cat tmp_Bin` ;exit 1; \
	fi
	@echo End of compilation

names genlib: 	$(macros_sci) Makefile 
	@echo $(PWD) > tmp_comp ;
	@echo $(PACKAGE_NAME) >> tmp_comp ;
	@echo $(macros_sci) >> tmp_comp ;
	@$(SCIDIR)/macros/Name Xtmp_comp; rm -f tmp_comp

clean-local:
	rm -f tmp_* *.bin lib names Lib.mak Macros.mak genlib
