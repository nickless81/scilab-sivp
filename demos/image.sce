filename = getSIVPpath() + 'images/lena.png';
if getos() == 'Windows' then 
  filename=strsubst(filename,'/','\');
end
im = imread(filename);
imshow(im);