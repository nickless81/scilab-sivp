
// ====================================================================

inter_names=[	'sivptest', 'int_test';
		'sivp_init','int_sivp_init';
		'imread', 'int_imread';
		'int_imwrite', 'int_imwrite';
		'imfinfo', 'int_imfinfo';
		'aviinfo', 'int_aviinfo';
		'aviopen', 'int_aviopen';
		'camopen', 'int_camopen';
		'avifile', 'int_avifile';
		'aviclose','int_aviclose';
		'avicloseall','int_avicloseall';
		'avilistopened', 'int_avilistopened';
		'avireadframe', 'int_avireadframe';
		'addframe', 'int_addframe'; 
		'int_imresize', 'int_imresize';
		'int_imabsdiff', 'int_imabsdiff';
		'int_imadd', 'int_imadd';
		'int_imsubtract', 'int_imsubtract';
		'int_immultiply', 'int_immultiply';
		'int_imdivide', 'int_imdivide';
		'imfilter', 'int_imfilter';
		'filter2', 'int_filter2';
		'mat2utfimg', 'int_mat2utfimg';
		'int_canny', 'int_canny';
		'int_sobel', 'int_sobel';
		'int_cvtcolor', 'int_cvtcolor';
		'ind2rgb', 'int_ind2rgb';
		'detectobjects', 'int_detectobjects';
		'camshift', 'int_camshift';
		'meanshift', 'int_meanshift';
		'detectforeground', 'int_detectforeground';
		'impyramid', 'int_impyramid';];

inter_files=["common.c",
"camshift.c", 
"canny.c", 
"cvtcolor.c", 
"detectforeground.c", 
"detectobjects.c", 
"filter2.c", 
"imabsdiff.c", 
"imadd.c", 
"imdivide.c", 
"imfilter.c", 
"imfinfo.c", 
"immultiply.c", 
"impyramid.c", 
"imread.c", 
"imresize.c", 
"imsubtract.c", 
"imwrite.c", 
"ind2rgb.c", 
"mat2utfimg.c", 
"meanshift.c", 
"sivp_init.c", 
"sobel.c", 
"test.c",
"videoio.c"];

curr_path=get_absolute_file_path('builder_gateway_c.sce');

opencv_libs="";

if ~MSDOS then  //linux
	inter_files=["common.h", inter_files];
	inter_cflags = unix_g('pkg-config --cflags opencv');
	inter_ldflags = unix_g('pkg-config --libs opencv');
else
	inter_cflags = "-I"""+SCI+"/contrib/sivp/opencv/include"" ";
	inter_ldflags = "-LIBPATH:"""+SCI+"/contrib/sivp/opencv/lib"" ";
	opencv_libs = ["cxcore200", "cv200", "cvaux200", "highgui200"];
end

if( (length(inter_cflags)==0) | (length(inter_ldflags)==0))
	error("Can not find OpenCV. Compiling SIVP needs OpenCV");
end

tbx_build_gateway('sivp', inter_names, inter_files, ..
                  curr_path, ..
                     opencv_libs, inter_ldflags, inter_cflags);

clear tbx_build_gateway inter_names inter_files inter_cflags inter_libs;
