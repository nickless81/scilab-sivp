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

function [hsv] = rgb2hsv(rgb)
  rgb=im2double(rgb);
  tmp=int_cvtcolor(rgb, 'rgb2hsv');
  hsv=zeros(tmp);

  hsv(:,:,1) = tmp(:,:,3)/360;
  hsv(:,:,2) = tmp(:,:,2);
  hsv(:,:,3) = tmp(:,:,1);
  clear tmp;
endfunction
