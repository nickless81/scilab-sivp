filename = SIVP_PATH + '/images/red_car_video.avi';
if MSDOS then filename=strsubst(filename,'/','\'),end
n = aviopen(filename);
im = avireadframe(n); //get a frame
obj_win = camshift(im, [12, 6, 39, 13]); //initialize tracker
while ~isempty(im),
      obj_win = camshift(im); //camshift tracking          
      im = rectangle(im, obj_win, [0,255,0]);
      imshow(im);
      im = avireadframe(n);
end;
aviclose(n);
