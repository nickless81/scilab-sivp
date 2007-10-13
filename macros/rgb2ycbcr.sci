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

function [ycc] = rgb2ycbcr(rgb)
  rgb=im2double(rgb);
  tmp=int_cvtcolor(rgb, 'rgb2ycrcb');
  ycc=zeros(tmp);

  ycc(:,:,1) = tmp(:,:,1);
  ycc(:,:,2) = tmp(:,:,3);
  ycc(:,:,3) = tmp(:,:,2);
  clear tmp;
endfunction
