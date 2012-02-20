// ====================================================================
stacksize('max');
// ====================================================================
function demo_noise()
  filename = fullpath(getSIVPpath() + 'images/lena.png');
  im = imread(filename);
  imn = imnoise(im, 'gaussian');
  imshow(imn);
endfunction
// ====================================================================
demo_noise();
clear demo_noise;
// ====================================================================
