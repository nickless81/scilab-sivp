filename = getSIVPpath() + 'images/video.mpg';
if getos() == 'Windows' then 
  filename=strsubst(filename,'/','\');
end
n = aviopen(filename);
for idx=1:100,
    im=avireadframe(n);
    imshow(im);
end;
aviclose(n);
