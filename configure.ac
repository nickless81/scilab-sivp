# Copyright (C) 2005 Shiqi Yu
# Some inspiration came from sip's configure.ac (thx Ricardo Fabbri)


AC_PREREQ(2.59)
AC_INIT([sivp], [cvs], [https://sourceforge.net/tracker/?group_id=134898&atid=731349])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/test.c)
AM_CONFIG_HEADER(src/config.h)
AM_INIT_AUTOMAKE([sivp], [cvs] )

# Checks for programs.
AC_PROG_CC

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
at least one of them is required to build the SIP manual pages.
Download xslproc (from libxml) at:
   http://http://www.xmlsoft.org 
or sabcmd (from sablotron) at:
   http://www.gingerall.com/charlie/ga/xml/p_sab.xml]])
   fi
fi

# test if SCI is defined. If not,
# test if scilab is in path, then get SCI from scilab -nw.
if test -z $SCI; then
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
else
   SCIDIR=$SCI
fi
CPPFLAGS="$CPPFLAGS -I${SCIDIR}/routines"

if test "x$prefix"  = xNONE; then 
   prefix="${SCIDIR}/contrib/sivp"
fi
TOOLBOXDIR=$prefix
# Set the default installation
AC_PREFIX_DEFAULT([$TOOLBOXDIR])
AC_SUBST(TOOLBOXDIR)
AC_SUBST(SCIDIR)

#
# Set defines required to build DLLs and modules using MinGW
# thx to Bob F.
#
# These options are set for DLL build
#  libanimal:           _DLL ANIMAL_LIB
# TODO:
#   - update from SIMPLE toolbox
#
LIBRARY_EXTRA_CPPFLAGS=''
LIBRARY_EXTRA_LIBS=''
if test "${native_win32_build}" = 'yes'
then
  if test "${libtool_build_shared_libs}" = 'yes'
  then
    CPPFLAGS="$CPPFLAGS -D_DLL"
    LIBRARY_EXTRA_CPPFLAGS="-DANIMAL_LIB"
    LIBRARY_EXTRA_LIBS="${SCIDIR}/bin/LibScilab.lib"
    # temporary:
#    LIBS="$LIBS ${SCIDIR}/bin/LibScilab.lib"
  else
    CPPFLAGS="$CPPFLAGS -D_LIB"
  fi
fi
AC_SUBST(LIBRARY_EXTRA_CPPFLAGS)dnl
AC_SUBST(LIBRARY_EXTRA_LIBS)dnl

# Checks for libs. 

# check for OpenCV >= 0.9.6
have_opencv=no
PKG_CHECK_MODULES(OPENCV, 
		[opencv >= 0.9.6],
		[CFLAGS="$CFLAGS $OPENCV_CFLAGS"
		 LIBS="$LIBS $OPENCV_LIBS"
		 have_opencv=yes],
		[AC_MSG_ERROR([[ OpenCV version >= 0.9.6 was not found. ]])])



#check for ffmpeg
have_ffmpeg=no
AC_CHECK_HEADER(ffmpeg/avcodec.h,
    AC_CHECK_LIB(avcodec, avcodec_decode_video,
        [AC_CHECK_LIB(avformat, av_read_frame,
			[have_ffmpeg=yes
			 LIBS="$LIBS -lavcodec -lavformat"],,
			[-lavcodec])]))

#echo $has_ffmpeg
#echo ":$FFMPEG_CFLGS:"
#echo ":$FFMPEG_LIBS:"
#AC_MSG_ERROR([stop])

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

# AC_CHECK_FUNC([strcasecmp],[],[AC_MSG_ERROR([[this package needs the strcasecmp function.]])])

# AC_SUBST(CFLAGS)
# AC_SUBST(CPPFLAGS)
# AC_SUBST(LDFLAGS)
# AC_SUBST(LIBS)
TOOLBOX_FUNCTIONS="'viptest'; \
		   "
			      
AC_SUBST(TOOLBOX_FUNCTIONS)

AC_CONFIG_FILES([Makefile 
		 src/Makefile
		 loader.sce])

AC_OUTPUT


AC_MSG_RESULT([
=====================================================
Configuration:
	CC       = $CC
	CFLAGS   = $CFLAGS
	CPPFLAGS = $CPPFLAGS
	LDFLAGS  = $LDFLAGS
	LIBS     = $LIBS
	LIBRARY_EXTRA_CPPFLAGS	= $LIBRARY_EXTRA_CPPFLAGS
	LIBRARY_EXTRA_LIBS	= $LIBRARY_EXTRA_LIBS

	use OpenCV = $have_opencv
	use ffmpeg = $have_ffmpeg
=====================================================
This toolbox will be installed in $TOOLBOXDIR.
]) 
