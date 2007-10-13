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

//convert RGB image to gray scale image
//G = 0.299*R + 0.587*G + 0.114*B
//TODO: The algorithm should be optimized to improve performance.

function [G] = rgb2gray(RGB)
  dims = size(RGB);
  typeofrgb = typeof(RGB(1));
  
  //check whether RGB is a MxNx3 hypermat
  if (size(dims,2)== 3) then
    if (dims(3)<>3) then
      error('RGB image must have dimentions M x N x 3.');
    end
    //convert the image to double image first
    RGB = im2double(RGB);
    
    //convert to gray scale
    G =  0.299*RGB(:,:,1) + 0.587*RGB(:,:,2) + 0.114*RGB(:,:,3);
    
    select typeofrgb
     case 'uint8' then
      G = im2uint8(G);
     case 'int8' then
      G = im2int8(G);
     case 'uint16' then
      G = im2uint16(G);
     case 'int16' then
      G = im2int16(G);
     case 'int32' then
      G = im2int32(G);
     case 'constant' then
      G = im2double(G);
     else
      error("Data type " + imtype + " is not supported.");
    end //end select
    
  else //if not size(dims,'2') == 3
      error('RGB image must have dimentions M x N x 3.')
  end
endfunction
