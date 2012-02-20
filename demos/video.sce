// ====================================================================
function demo_video()
  filename = fullpath(getSIVPpath() + 'images/video.mpg');
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
