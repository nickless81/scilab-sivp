//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test imhist
//==============================================================================
im = imread(fullpath(getSIVPpath() + "/images/lena.png"));
im = rgb2gray(im);
[count, cells]=imhist(im);
[count, cells]=imhist(im, 10);
scf(0);
imhist(im, 10, '');
scf(1);
imhist(im, 10, 0.5);
scf(2);
imhist(im, 10, 'green');
scf(3);
imhist(im, 10, 0.8, 'green');
//==============================================================================
