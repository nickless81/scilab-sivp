stacksize('max');
filename = getSIVPpath() + 'images/lena.png';
if getos() == 'Windows' then 
  filename=strsubst(filename,'/','\');
end
im=imread(filename);               
imn = imnoise(im, 'gaussian');
imshow(imn);
