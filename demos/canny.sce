filename = SCI + '/contrib/sivp/images/lena.png';

if MSDOS then filename=strsubst(filename,'/','\'),end

im=imread(filename);               

imc=canny(im, 50, 150, 3);                  

imshow(imc);
