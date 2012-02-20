// Allan CORNET - DIGITEO - 2010-2012
function p = getSIVPpath()
  p = [];
  if isdef('sivplib') then
    [m, mp] = libraryinfo('sivplib');
    p = pathconvert(fullpath(mp + "../"), %t, %t);
  end
endfunction