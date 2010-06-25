stacksize('max');
filename = getSIVPpath() + 'images/people.jpg';
if getos() == 'Windows' then 
  filename=strsubst(filename,'/','\');
end
im = imread(filename);
face = detectfaces(im);
[m,n] = size(face);
for i=1:m,
    im = rectangle(im, face(i,:), [0,255,0]);
end;
imshow(im);    
