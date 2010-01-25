// ====================================================================
// Allan CORNET
// DIGITEO 2008
// This file is released into the public domain
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

inter_files=["addframe.cpp", 
"avicloseall.cpp", 
"aviclose.cpp", 
"avifile.cpp", 
"aviinfo.cpp", 
"avilistopened.cpp", 
"aviopen.cpp", 
"avireadframe.cpp", 
"camopen.cpp", 
"camshift.cpp", 
"canny.cpp", 
"cvtcolor.cpp", 
"detectforeground.cpp", 
"detectobjects.cpp", 
"filter2.cpp", 
"imabsdiff.cpp", 
"imadd.cpp", 
"imdivide.cpp", 
"imfilter.cpp", 
"imfinfo.cpp", 
"immultiply.cpp", 
"impyramid.cpp", 
"imread.cpp", 
"imresize.cpp", 
"imsubtract.cpp", 
"imwrite.cpp", 
"ind2rgb.cpp", 
"mat2utfimg.cpp", 
"meanshift.cpp", 
"sivp_init.cpp", 
"sobel.cpp", 
"test.cpp"];

inter_cflags = unix_g('pkg-config --cflags opencv');
inter_ldflags = unix_g('pkg-config --libs opencv');

if( (length(inter_cflags)==0) | (length(inter_ldflags)==0))
	error("Can not find OpenCV. Compiling SIVP needs OpenCV");
end

tbx_build_gateway('sivp_cpp', inter_names, inter_files, ..
                  get_absolute_file_path('builder_gateway_cpp.sce'), ..
                     [], inter_ldflags, inter_cflags);

clear tbx_build_gateway inter_names inter_files inter_cflags inter_libs;
