filename = SIVP_PATH + '/images/lena.png';
if MSDOS then filename=strsubst(filename,'/','\'),end
im = imread(filename);
face = detectfaces(im, 'haarcascade_frontalface_alt2.xml');
rect = face*diag([1,1,1,0.7]);
subface = imcrop(im, rect);
reyes = detectrighteyes(subface);
[m,n] = size(reyes);
for i=1:m,  
    im = rectangle(im, reyes(i,:)+rect*diag([1,1,0,0]), [0,255,0]);
end;
imshow(im);    
