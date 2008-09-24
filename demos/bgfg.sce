filename = SIVP_PATH + '/images/video.avi';
if MSDOS then filename=strsubst(filename,'/','\'),end   
n = aviopen(filename);
im = avireadframe(n);
fg = detectforeground(im, 'LI');//create background model
while ~isempty(im),
      fg = detectforeground(im);//get the foreground mask 
      imshow(fg);   
      im = avireadframe(n);
end;
aviclose(n);
