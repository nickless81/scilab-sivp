EXTRA_DIST = ChangeLog COPYING INSTALL libtool Makefile.in NEWS README \
		builder.sce loader.sce \
		config/config.guess config/config.sub config/install-sh \
		config/ltmain.sh config/missing config/mkinstalldirs \
		src/ilib_gen_gateway.sce


SUBDIRS = src 

toolboxdir=@TOOLBOXDIR@


install-data-local:
	cp loader.sce ${toolboxdir}
	cp builder.sce ${toolboxdir}

uninstall:
	rm ${toolboxdir} -rf
