//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test meanshift
//==============================================================================
// <-- NO CHECK REF --> 
//==============================================================================
n = aviopen(fullpath(getSIVPpath() + "/images/" + 'red-car-video.avi'));
im = avireadframe(n); //get a frame
obj_win = meanshift(im, [12, 6, 39, 13]); //initialize tracker

while ~isempty(im),
  obj_win = meanshift(im); //meanshift tracking
  im = rectangle(im, obj_win, [0,255,0]);
  imshow(im);
  im = avireadframe(n);
end;
aviclose(n);
//==============================================================================
