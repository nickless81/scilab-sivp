filename = getSIVPpath() + 'images/lena.png';
if getos() == 'Windows' then 
  filename=strsubst(filename,'/','\');
end
im=imread(filename);               
imc=edge(rgb2gray(im),'canny');
imshow(imc);
