// ====================================================================
function demo_image()
  filename = fullpath(getSIVPpath() + 'images/lena.png');
  im = imread(filename);
  imshow(im);
endfunction
// ====================================================================
demo_image();
clear demo_image;
// ====================================================================
