////////////////////////////////////////////////////////////
// SIVP - Scilab Image and Video Processing toolbox
// Copyright (C) 2006  Shiqi Yu
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////

//send graphics to an image matrix
//this function call xs2ppm() save the image to disk
//and then load it to scilab
//a better solution should be considered as soon as possible
function im =  xs2im(win_num, varargin)
  if length(varargin)==1 then
    iscolor = varargin(1);
  else
    iscolor = 1;
  end
  imfile = TMPDIR + "/sivp-tmp-" + strcat(string(getdate())) + ".ppm";
  xs2ppm(win_num, imfile, iscolor);
  im = imread(imfile);
  mdelete(imfile);
endfunction 
