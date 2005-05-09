ilib_name="sivp";

files=[	"sivp_common.o";
	"vdofinfo.o"; 
	"sivp_formats.o";
	"imgread.o";
	"int_imgwrite.o";
	"vdoread.o"];


libs = [];


table = ["vdofinfo", "int_vdofinfo"; 
	"sivp_formats", "int_sivp_formats";
	"imgread", "int_imgread";
	"int_imgwrite", "int_imgwrite";
	"vdoopen", "int_vdoopen";
	"vdoclose", "int_vdoclose";
	"vdocloseall", "int_vdocloseall";
	"vdoshowopened", "int_vdoshowopened";
	"vdogetframe", "int_vdogetframe" ];


ldflags = "-lavformat -lavcodec -lz";
cflags ="-I/usr/local/include/ffmpeg/";
fflags ="";

// do not modify below
//---------------------------------------
ilib_build(ilib_name, table, files, libs, "Makelib", ldflags,cflags,fflags)
