// ====================================================================
function demo_video()
  filename = fullpath(getSIVPpath() + 'images/red-car-video.avi');
  n = aviopen(filename);
  for idx = 1:100,
    im = avireadframe(n);
    imshow(im);
  end;
  aviclose(n);
endfunction
// ====================================================================
demo_video();
clear demo_video;
// ====================================================================
