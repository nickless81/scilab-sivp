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
AC_INIT([sivp], [0.2.6], [https://sourceforge.net/tracker/?group_id=134898&atid=731349])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/test.c)
AM_CONFIG_HEADER(src/config.h)
AM_INIT_AUTOMAKE([sivp],[0.2.6])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# ssl begin
if test x"$ac_cv_prog_cc_stdc" = x'no'; then
   AC_MSG_WARN([[found the $CC compiler but it is not ANSI-C 
                compliant.]])
fi
# ssl end

AC_LIBTOOL_WIN32_DLL
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Check to see if building shared libraries
libtool_build_shared_libs='no'
if ./libtool --config | grep 'build_libtool_libs=yes' > /dev/null
then
  libtool_build_shared_libs='yes'
fi


#
# Tests for windows
#
native_win32_build='no'
cygwin_build='no'
case $host_os in
   cygwin*) 
       cygwin_build='yes'
       ;;
   mingw* )
       native_win32_build='yes' 
       ;;
esac


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
   if test $native_win32_build = yes; then
      dnl TODO take SCIDIR from the registry
      AC_MSG_WARN([[hardcoding SCI to /c/scilab]])
      SCIDIR="/c/scilab"
   else
      AC_CHECK_PROG([has_scilab],[scilab],[yes],[no], , )
      if test x$has_scilab = xno; then
         AC_MSG_ERROR([[neither Scilab was found in your PATH nor a SCI variable has been defined]])
      else
         cmd='F=mopen("path.incl","w");
              mfprintf(F,SCI);
              mclose(F);'
         echo "$cmd" | scilab -nw >/dev/null
         SCIDIR=`cat path.incl`
      fi
   fi
else
   SCIDIR="$SCI"
fi

CPPFLAGS="$CPPFLAGS -I${SCIDIR}/routines"

AC_PREFIX_DEFAULT([SCI/contrib/sivp])

if test "x$prefix"  = xNONE; then 
   prefix="${SCIDIR}/contrib/sivp"
fi

TOOLBOXDIR=$prefix

# Set the default installation
AC_PREFIX_DEFAULT([$TOOLBOXDIR])
AC_SUBST(TOOLBOXDIR)
AC_SUBST(SCIDIR)


LIBRARY_EXTRA_CPPFLAGS=''
LIBRARY_EXTRA_LIBS=''
if test "${native_win32_build}" = 'yes'
then
  if test "${libtool_build_shared_libs}" = 'yes'
  then
    SHARED_LIB_SUFFIX=dll
    CPPFLAGS="$CPPFLAGS -DFORDLL"
    AC_MSG_WARN([[Don't forget to rename SCI/bin/LibScilab* to lowercase]])
    LDFLAGS="$LDFLAGS -L${SCIDIR}/bin"
    #LIBRARY_EXTRA_CPPFLAGS="-D_SIMPLELIB"
    LIBRARY_EXTRA_LIBS="-lscilab"
  else
    CPPFLAGS="$CPPFLAGS -D_LIB"
  fi
else
   SHARED_LIB_SUFFIX=so
fi
AC_SUBST(SHARED_LIB_SUFFIX)

AC_SUBST(LIBRARY_EXTRA_CPPFLAGS)
AC_SUBST(LIBRARY_EXTRA_LIBS)

# Checks for libs. 

# check for OpenCV >= 0.9.6
have_opencv=no
PKG_CHECK_MODULES(OPENCV, 
		[opencv >= 0.9.6],
		[CPPFLAGS="$CPPFLAGS $OPENCV_CFLAGS"
		 LDFLAGS="$LDFLAGS -L${SCIDIR}/bin"
		 LIBS="$LIBS $OPENCV_LIBS"
		 have_opencv=yes
		 AC_DEFINE(HAVE_OPENCV,[], [define HAVE_OPENCV if you have opencv])],
		[AC_MSG_ERROR([[ OpenCV version >= 0.9.6 was not found. ]])])



# check for ffmpeg
if test $native_win32_build = no; then
have_ffmpeg=no
AC_CHECK_HEADER(ffmpeg/avcodec.h,
    AC_CHECK_LIB(avcodec, avcodec_decode_video,
        [AC_CHECK_LIB(avformat, av_read_frame,
			[have_ffmpeg=yes
			 AC_DEFINE(HAVE_FFMPEG,[],[define HAVE_FFMPEG if you have ffmpeg])
			 LIBS="$LIBS -lavcodec -lavformat"],
			 AC_MSG_ERROR([[ libavformat (FFMPEG) was not found. ]]),
			[-lavcodec])]), 
			 AC_MSG_ERROR([[ libavcodec (FFMPEG) was not found. ]]))
fi



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
#AC_FUNC_MALLOC
AC_CHECK_FUNCS([malloc])

PACKAGE_NAME=sivp
## for src/Makefile
# TOOLBOX_SRC=" test.c"

# for src/ilib_gen_gateway.sce

TOOLBOX_TABLE="	'sivptest', 'int_test'; \
		'sivp_init','int_sivp_init'; \
		'imread', 'int_imread';\
		'imwrite', 'int_imwrite';\
		'vdopen', 'int_vdopen'; \
		'vdgetframe', 'int_vdgetframe'; \
		'vdshowopened', 'int_vdshowopened'; \
		'vdclose', 'int_vdclose'; \
		'vdcloseall', 'int_vdcloseall'; \
		'mat2utfimg', 'int_mat2utfimg';\
		'canny', 'int_canny'; \
		'convert', 'int_convert'; \
		'laplace', 'int_laplace'; \
		'precornerdetec', 'int_precornerdetec'; \
		'imsmooth', 'int_imsmooth'; \
		'sobel', 'int_sobel'; \
		'threshold', 'int_threshold'; \
		'adaptativethreshold', 'int_adaptativethreshold'; \
		'erode', 'int_erode';\
		'dilate', 'int_dilate';\
		'pyrdown', 'int_pyrdown';\
		'pyrup', 'int_pyrup';\
		'goodfeaturestotrack', 'int_goodfeaturestotrack';\
		'xor', 'int_xor';\
		'not', 'int_not';\
		'cmp', 'int_cmp';\
		'hough', 'int_hough';\
		"
# for loader.sce
# TOOLBOX_FUNCTIONS is the first colum of TOOLBOX_TABLE 
TOOLBOX_FUNCTIONS="    'sivptest'; \
		       'sivp_init'; \
		       'imread';\
		       'imwrite';\
		       'vdopen'; \
		       'vdgetframe'; \
		       'vdshowopened'; \
		       'vdclose'; \
		       'vdcloseall'; \
		       'mat2utfimg'; \
		       'canny'; \
		       'convert'; \
		       'laplace'; \
		       'precornerdetec'; \
		       'imsmooth'; \
		       'sobel'; \
		       'threshold'; \
		       'adaptativethreshold'; \
		       'erode';\
		       'dilate';\
		       'pyrdown';\
		       'pyrup';\
		       'goodfeaturestotrack';\
		       'xor';\
		       'not';\
		       'cmp';\
		       'hough';\
		   "

AC_SUBST(PACKAGE_NAME)
AC_SUBST(TOOLBOX_SRC)
AC_SUBST(TOOLBOX_TABLE)
AC_SUBST(TOOLBOX_FUNCTIONS)

AC_CONFIG_FILES([Makefile 
		 macros/Makefile
		 images/Makefile
		 man/Makefile
		 src/Makefile
		 demos/Makefile
		 src/ilib_gen_gateway.sce
		 loader.sce])

AC_OUTPUT


if test $native_win32_build = no; then
AC_MSG_RESULT([
=====================================================
Configuration:
	CC       = $CC
	CFLAGS   = $CFLAGS
	CPPFLAGS = $CPPFLAGS
	LDFLAGS  = $LDFLAGS
	LIBS     = $LIBS
        
	have OpenCV = $have_opencv
	have FFMPEG = $have_ffmpeg
=====================================================
This toolbox will be installed in $TOOLBOXDIR.
Please run 'make' and 'make install' to compile and install the toolbox. 
]) 
else
AC_MSG_RESULT([
=====================================================
Configuration:
	CC       = $CC
	CFLAGS   = $CFLAGS
	CPPFLAGS = $CPPFLAGS
	LDFLAGS  = $LDFLAGS
	LIBS     = $LIBS
        
	have OpenCV = $have_opencv
=====================================================
This toolbox will be installed in $TOOLBOXDIR.
Please run 'make' and 'make install' to compile and install the toolbox. 
]) 
fi
