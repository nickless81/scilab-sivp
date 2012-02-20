//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test rgb2ycbcr
//==============================================================================
stacksize('max');
RGB = imread(fullpath(getSIVPpath() + "/images/lena.png"));
YCC = rgb2ycbcr(RGB);
RGB = ycbcr2rgb(YCC);
imshow(RGB);
//==============================================================================
