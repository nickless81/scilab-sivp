# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /usr/lib/scilab-3.1-rc1/contrib/sivp
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/sivp
pkglibdir = $(libdir)/sivp
pkgincludedir = $(includedir)/sivp

top_builddir = ..

ACLOCAL = aclocal-1.4
AUTOCONF = autoconf
AUTOMAKE = automake-1.4
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i686-pc-linux-gnu
AR = ar
AS = @AS@
CC = gcc
CXX = g++
CXXCPP = g++ -E
DLLTOOL = @DLLTOOL@
ECHO = echo
EGREP = grep -E
EXEEXT = 
F77 = g77
GCJ = @GCJ@
GCJFLAGS = @GCJFLAGS@
HAVE_LIB = @HAVE_LIB@
LIB = @LIB@
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIB = @LTLIB@
MAKEINFO = makeinfo
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = sivp
PACKAGE_NAME = sivp
PKG_CONFIG = /usr/bin/pkg-config
RANLIB = ranlib
RC = @RC@
SCIDIR = /usr/lib/scilab-3.1-rc1
STRIP = strip
TOOLBOXDIR = /usr/lib/scilab-3.1-rc1/contrib/sivp
TOOLBOX_FUNCTIONS =     'sivptest'; 		       'canny'; 		       'imread';		       'imwrite';		   
TOOLBOX_SRC = 
TOOLBOX_TABLE = 	'sivptest', 'int_test'; 		'canny', 'int_canny'; 		'imread', 'int_imread';		'imwrite', 'int_imwrite';		
VERSION = cvs
has_scilab = yes

macros_sci = imshow.sci char2double.sci short2double.sci long2double.sci sip_approx_true_cmap.sci sip_index_true_cmap.sci

macros_bin = $(macros_sci:.sci=.bin)

macrodir = /usr/lib/scilab-3.1-rc1/contrib/sivp/macros
macro_DATA = $(macros_bin) genlib names lib
mkinstalldirs = $(SHELL) $(top_srcdir)/config/mkinstalldirs
CONFIG_HEADER = ../src/config.h
CONFIG_CLEAN_FILES = 
DATA =  $(macro_DATA)

DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.ac $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu macros/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status $(BUILT_SOURCES)
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


install-macroDATA: $(macro_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(macrodir)
	@list='$(macro_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(macrodir)/$$p"; \
	    $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(macrodir)/$$p; \
	  else if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(macrodir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(macrodir)/$$p; \
	  fi; fi; \
	done

uninstall-macroDATA:
	@$(NORMAL_UNINSTALL)
	list='$(macro_DATA)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(macrodir)/$$p; \
	done
tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = macros

distdir: $(DISTFILES)
	here=`cd $(top_builddir) && pwd`; \
	top_distdir=`cd $(top_distdir) && pwd`; \
	distdir=`cd $(distdir) && pwd`; \
	cd $(top_srcdir) \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here --srcdir-name=$(top_srcdir) --output-dir=$$top_distdir --gnu macros/Makefile
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am: install-macroDATA
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-macroDATA
uninstall: uninstall-am
all-am: Makefile $(DATA)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(macrodir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am clean-local

clean: clean-am

distclean-am:  distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: uninstall-macroDATA install-macroDATA tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


#
# The following code is an adaptation to Automake from /usr/lib/scilab-3.1-rc1/macros/Make.lib
#
%.bin : %.sci
	@SCI=$(SCIDIR);export SCI;$(SCIDIR)/bin/scilab -comp  $<

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

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
