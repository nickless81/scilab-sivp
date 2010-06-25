// Allan CORNET - DIGITEO - 2010

function p = getSIVPpath()
  p = [];
  if isdef('sivplib') then
    [m, mp] = libraryinfo('sivplib');
    p = fullpath(mp + '../');
  end
endfunction