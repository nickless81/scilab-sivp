//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test impyramid
//==============================================================================
stacksize('max');

//Compute a four-level multiresolution pyramid of the 'lena' image.

im0 = imread(fullpath(getSIVPpath() + "/images/" + 'lena.png'));
im1 = impyramid(im0, 'reduce');
im2 = impyramid(im1, 'reduce');
im3 = impyramid(im2, 'reduce');

imshow(im0);
imshow(im1);
imshow(im2);
imshow(im3);
//==============================================================================
