// ====================================================================
function demo_canny()
  filename = fullpath(getSIVPpath() + 'images/lena.png');
  im = imread(filename);               
  imc = edge(rgb2gray(im), 'canny');
  imshow(imc);
endfunction
// ====================================================================
demo_canny();
clear demo_canny;
// ====================================================================
