// ====================================================================
stacksize('max');
// ====================================================================
function demo_face()
  filename = fullpath(getSIVPpath() + 'images/people.jpg');
  im = imread(filename);
  face = detectfaces(im);
  [m, n] = size(face);
  for i = 1:m,
    im = rectangle(im, face(i,:), [0,255,0]);
  end
  imshow(im);
endfunction
// ====================================================================
demo_face();
clear demo_face;
// ====================================================================
