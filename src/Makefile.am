libdir=@TOOLBOXDIR@/lib

lib_LTLIBRARIES = libsivp.la

# AM_CPPFLAGS = @LIBRARY_EXTRA_CPPFLAGS@

libsivp_la_SOURCES = libsivp.c common.c imread.c test.c canny.c

libsivp_la_LDFLAGS = -no-undefined -version-info 0:0:0 -release @PACKAGE_VERSION@

# libsivp_la_LIBADD = @LIBRARY_EXTRA_LIBS@


libsivp.c: ilib_gen_gateway.sce
	${SCIDIR}/scilab -nw -f ilib_gen_gateway.sce

