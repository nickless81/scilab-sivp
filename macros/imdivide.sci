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

function [imout] = imdivide(im1, im2)

    if ( typeof(im1(1))=='constant') then //double
       imout = im1 ./ im2; 
    elseif ( typeof(im1(1))=='int8') then //int8
       imout = double(im1) ./ double(im2);
       imout(imout > 127) = 127;
       imout(imout < -128) = -128;
       imout = int8(imout);
    else 
       imout = int_imdivide(im1, im2);
    end

endfunction
