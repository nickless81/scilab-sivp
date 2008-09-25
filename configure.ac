##
## -------------------------------------------------------------------------
## SIVP - Scilab Image and Video Processing toolbox
## Copyright (C) 2005  Shiqi Yu, Shulin Shang
## Some inspiration came from sip's configure.ac (thx Ricardo Fabbri)
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


AC_PREREQ(2.59)
AC_INIT([sivp], [svn-trunk], [https://sourceforge.net/tracker/?group_id=134898&atid=731349])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/test.c)
AM_CONFIG_HEADER(src/config.h)
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
#AC_PROG_CXX
#AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

if test x"$ac_cv_prog_cc_stdc" = x'no'; then
   AC_MSG_WARN([[found the $CC compiler but it is not ANSI-C 
                compliant.]])
fi

#AC_LIBTOOL_WIN32_DLL
#AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Check to see if building shared libraries
libtool_build_shared_libs='no'
if ./libtool --config | grep 'build_libtool_libs=yes' > /dev/null
then
  libtool_build_shared_libs='yes'
fi


###
### Tests for windows
###
##native_win32_build='no'
##cygwin_build='no'
##win32_build='no'
##case $host_os in
##   cygwin*) 
##       cygwin_build='yes'
##       win32_build='yes' 
##       ;;
##   mingw* )
##       native_win32_build='yes' 
##       win32_build='yes' 
##       ;;
##esac


# checks for xsltproc (to buld HTML help pages)
AC_CHECK_PROG([has_xsltproc],[xsltproc],[yes],[no], , )
if test x$has_xsltproc = xno; then
   # checks for sabcmd as an alternative
   AC_CHECK_PROG([has_sablotron],[sabcmd],[yes],[no], , )
   if test x$has_sablotron = xno; then
      AC_MSG_ERROR([[xsltproc or sabcmd programs were not found but \
at least one of them is required to build the SIVP manual pages.
Download xslproc (from libxml) at:
   http://www.xmlsoft.org 
or sabcmd (from sablotron) at:
   http://www.gingerall.com/charlie/ga/xml/p_sab.xml]])
   fi
fi

# test if SCI is defined. If not, test if scilab is in path,
# then get SCI from scilab -nw.
if test -z "$SCI"; then
   AC_CHECK_PROG([has_scilab],[scilab],[yes],[no], , )
   if test x$has_scilab = xno; then
      AC_MSG_ERROR([[neither Scilab was found in your PATH nor a SCI variable has been defined]])
   else
      cmd='F=mopen("path.incl","w");
           mfprintf(F,SCI);
           mclose(F);'
      echo "$cmd" | scilab -nw >/dev/null
      SCIDIR=`cat path.incl`
	 # TODO 
	 #SCIEXE="${SCIDIR}/bin/scilex"
	 SCIEXE="${SCIDIR}/bin/scilab"
   fi
else
   SCIDIR="$SCI"
   if test $win32_build = yes; then
      SCIEXE="${SCI}/bin/Scilex.exe"
   else
      #SCIEXE="${SCI}/bin/scilex"
      SCIEXE="${SCI}/bin/scilab"
   fi
fi

#CFLAGS="$CFLAGS -I${SCIDIR}/routines"

AC_PREFIX_DEFAULT([SCI/contrib/${PACKAGE_NAME}-${PACKAGE_VERSION}])

if test "x$prefix"  = xNONE; then 
   prefix="${SCIDIR}/contrib/${PACKAGE_NAME}-${PACKAGE_VERSION}"
else
   prefix="${prefix}/${PACKAGE_NAME}-${PACKAGE_VERSION}"
fi

TOOLBOXDIR=$prefix

# Set the default installation
AC_PREFIX_DEFAULT([$TOOLBOXDIR])
AC_SUBST(TOOLBOXDIR)
AC_SUBST(SCIDIR)
AC_SUBST(SCIEXE)

# check for OpenCV >= 0.9.6
have_opencv=no
PKG_CHECK_MODULES(OPENCV, 
		[opencv >= 0.9.6],
		[CFLAGS="$CFLAGS $OPENCV_CFLAGS"
		 LDFLAGS="$LDFLAGS $OPENCV_LIBS"
		 have_opencv=yes
		 AC_DEFINE(HAVE_OPENCV,[], [define HAVE_OPENCV if you have opencv])],
		[AC_MSG_ERROR([[ OpenCV version >= 0.9.6 was not found. ]])])

# Checks for header files. 
AC_HEADER_STDC
if test x"$ac_cv_header_stdc" = x'no'; then
   AC_MSG_WARN([[this package uses ANSI-C headers but none were found.]])
fi
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_HEADER_STDBOOL


# Checks for library functions.
##AC_FUNC_MALLOC
AC_CHECK_FUNCS([malloc])


TOOLBOX_TABLE="	'sivptest', 'int_test'; \
		'sivp_init','int_sivp_init'; \
		'imread', 'int_imread';\
		'int_imwrite', 'int_imwrite';\
		'imfinfo', 'int_imfinfo';\
		'aviinfo', 'int_aviinfo';\
		'aviopen', 'int_aviopen';\
		'camopen', 'int_camopen';\
		'avifile', 'int_avifile';\
		'aviclose','int_aviclose';\
		'avicloseall','int_avicloseall';\
		'avilistopened', 'int_avilistopened';\
		'avireadframe', 'int_avireadframe';\
		'addframe', 'int_addframe';\ 
		'int_imresize', 'int_imresize';\
		'int_imabsdiff', 'int_imabsdiff';\
		'int_imadd', 'int_imadd'; \
		'int_imsubtract', 'int_imsubtract'; \
		'int_immultiply', 'int_immultiply'; \
		'int_imdivide', 'int_imdivide'; \
		'imfilter', 'int_imfilter'; \
		'filter2', 'int_filter2'; \
		'mat2utfimg', 'int_mat2utfimg';\
		'int_canny', 'int_canny'; \
		'int_sobel', 'int_sobel'; \
		'int_cvtcolor', 'int_cvtcolor'; \
		'ind2rgb', 'int_ind2rgb'; \
		'detectobjects', 'int_detectobjects'; \
		'camshift', 'int_camshift'; \
		'meanshift', 'int_meanshift';\
		'detectforeground', 'int_detectforeground';\
		'impyramid', 'int_impyramid';\
		"

TOOLBOX_FUNCTIONS="    'sivptest'; \
		       'sivp_init'; \
		       'imread';\
		       'int_imwrite';\
		       'imfinfo'; \
		       'aviinfo';\
		       'aviopen';\
		       'camopen';\
		       'avifile';\
		       'aviclose';\
		       'avicloseall';\
		       'avilistopened';\
		       'avireadframe';\
		       'addframe';\
		       'int_imresize';\
		       'int_imabsdiff';\
		       'int_imadd'; \
		       'int_imsubtract'; \
		       'int_immultiply'; \
		       'int_imdivide'; \
		       'imfilter'; \
		       'filter2'; \
		       'mat2utfimg'; \
		       'int_canny'; \
		       'int_sobel'; \
		       'int_cvtcolor'; \
		       'ind2rgb'; \
		       'detectobjects'; \
		       'camshift'; \
		       'meanshift';\
		       'detectforeground';\
		       'impyramid';\
		   "

AC_SUBST(TOOLBOX_TABLE)
AC_SUBST(TOOLBOX_FUNCTIONS)

AC_CONFIG_FILES([Makefile 
		 etc/Makefile
		 macros/Makefile
		 man/Makefile
		 images/Makefile
		 demos/Makefile
		 src/Makefile
		 src/builder.sce
		 src/Makefile.win
		 loader.sce])

AC_OUTPUT


AC_MSG_RESULT([
=====================================================
Configuration:
	CFLAGS   = $CFLAGS
	LDFLAGS  = $LDFLAGS
=====================================================
This toolbox will be installed in $TOOLBOXDIR
Please run 'make' and 'make install' to compile and install the toolbox. 
]) 
