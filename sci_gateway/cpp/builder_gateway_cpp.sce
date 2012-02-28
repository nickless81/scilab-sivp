// -------------------------------------------------------------------------
// SIVP - Scilab Image Processing toolbox
// Copyright (C) 2005-2010  Shiqi Yu
// Copyright (C) 2012 - DIGITEO - Allan CORNET
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// -------------------------------------------------------------------------
//
function builder_gateway_cpp()

  gw_cpp_table = ['sivptest', 'int_test'; ..
                  'sivp_init','int_sivp_init'; ..
                  'imread', 'int_imread'; ..
                  'int_imwrite', 'int_imwrite'; ..
                  'imfinfo', 'int_imfinfo'; ..
                  'aviinfo', 'int_aviinfo'; ..
                  'aviopen', 'int_aviopen'; ..
                  'camopen', 'int_camopen'; ..
                  'avifile', 'int_avifile'; ..
                  'aviclose','int_aviclose'; ..
                  'avicloseall','int_avicloseall'; ..
                  'avilistopened', 'int_avilistopened'; ..
                  'avireadframe', 'int_avireadframe'; ..
                  'addframe', 'int_addframe'; ..
                  'int_imresize', 'int_imresize'; ..
                  'int_imabsdiff', 'int_imabsdiff'; ..
                  'int_imadd', 'int_imadd'; ..
                  'int_imsubtract', 'int_imsubtract'; ..
                  'int_immultiply', 'int_immultiply'; ..
                  'int_imdivide', 'int_imdivide'; ..
                  'imfilter', 'int_imfilter'; ..
                  'filter2', 'int_filter2'; ..
                  'mat2utfimg', 'int_mat2utfimg'; ..
                  'int_canny', 'int_canny'; ..
                  'int_sobel', 'int_sobel'; ..
                  'int_cvtcolor', 'int_cvtcolor'; ..
                  'ind2rgb', 'int_ind2rgb'; ..
                  'detectobjects', 'int_detectobjects'; ..
                  'camshift', 'int_camshift'; ..
                  'meanshift', 'int_meanshift'; ..
                  'detectforeground', 'int_detectforeground'; ..
                  'impyramid', 'int_impyramid'];


  gw_cpp_files = ["common.cpp", ..
                  "camshift.cpp", ..
                  "canny.cpp", ..
                  "cvtcolor.cpp", ..
                  "detectforeground.cpp", ..
                  "detectobjects.cpp", ..
                  "filter2.cpp", ..
                  "imabsdiff.cpp", ..
                  "imadd.cpp", ..
                  "imdivide.cpp", ..
                  "imfilter.cpp", ..
                  "imfinfo.cpp", ..
                  "immultiply.cpp", ..
                  "impyramid.cpp", ..
                  "imread.cpp", ..
                  "imresize.cpp", ..
                  "imsubtract.cpp", ..
                  "imwrite.cpp", ..
                  "ind2rgb.cpp", ..
                  "mat2utfimg.cpp", ..
                  "meanshift.cpp", ..
                  "sivp_init.cpp", ..
                  "sobel.cpp", ..
                  "test.cpp", ..
                  "videoio.cpp"];


  gw_cpp_path = get_absolute_file_path('builder_gateway_cpp.sce');

  opencv_libs = [];

  if getos() <> 'Windows' then  //linux, Darwin
    gw_cpp_files = [gw_cpp_files, "common.h", "gw_sivp.h"];
    if getos() == 'Darwin' then
      if ~isdir("/usr/local/include/opencv") then
        error("Can not find OpenCV. Compiling SIVP needs OpenCV");
      end
      inter_cflags = "-DOPENCV_V2 -I/usr/local/include/opencv ";
      inter_ldflags = "-lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy";
    else
      opencv_version = unix_g('pkg-config --modversion opencv');
      if( length(opencv_version) == 0 | ( strtod( strsubst(opencv_version, '.', '')) <= 99.9 ) )
        error(gettext("OpenCV (version >= 1.0.0) is needed for compiling SIVP."));
      end;

      if ( strtod( strsubst(opencv_version, '.', '')) < 111 ) then //if opencv version <1.1.1
        inter_cflags = "-DOPENCV_V1 ";
      else
        inter_cflags = "-DOPENCV_V2 ";
      end;
      inter_cflags = inter_cflags + unix_g('pkg-config --cflags opencv');
      inter_ldflags = unix_g('pkg-config --libs opencv');
      if( (length(inter_cflags)==0) | (length(inter_ldflags)==0))
        error("Can not find OpenCV. Compiling SIVP needs OpenCV");
      end    
    end
  else
    gw_cpp_files = [gw_cpp_files, "dllSIVP.cpp"];
    OPENCV_INCLUDE_ROOT_PATH = fullpath(gw_cpp_path + "../../thirdparty/opencv/windows/include");
    OPENCV_INCLUDE = fullpath(OPENCV_INCLUDE_ROOT_PATH + "/opencv");
    OPENCV2_INCLUDE = fullpath(OPENCV_INCLUDE_ROOT_PATH + "/opencv2");
    inter_cflags = ilib_include_flag([OPENCV_INCLUDE_ROOT_PATH, OPENCV_INCLUDE, OPENCV2_INCLUDE]);
    inter_ldflags = "";
    opencv_libs = [];
  end


  tbx_build_gateway('gw_sivp', ..
                    gw_cpp_table, ..
                    gw_cpp_files, ..
                    gw_cpp_path, ..
                    opencv_libs, ..
                    inter_ldflags, ..
                    inter_cflags);

endfunction
// ====================================================================
builder_gateway_cpp();
clear builder_gateway_cpp;
// ====================================================================
