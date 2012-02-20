//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test imresize
//==============================================================================
im = imread(fullpath(getSIVPpath() + "/images/lena.png"));
ima = imresize(im, 1.5);
assert_checkequal(size(ima), [768 768 3]);
imb = imresize(im, 1.5, 'bilinear');
assert_checkequal(size(imb), [768 768 3]);
imc = imresize(im, [100,200], 'bicubic');
assert_checkequal(size(imc), [100 200 3]);
//==============================================================================
