
filename = SCI + '/contrib/sivp/images/lena.png';

if MSDOS then filename=strsubst(filename,'/','\'),end

im = imread(filename);

imshow(im);