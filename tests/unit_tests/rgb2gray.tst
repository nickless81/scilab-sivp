//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test rgb2gray
//==============================================================================
RGB = imread(fullpath(getSIVPpath() + "/images/lena.png"));
G = rgb2gray(RGB);
imshow(G);
//==============================================================================