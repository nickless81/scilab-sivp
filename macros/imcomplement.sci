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

function [im2] = imcomplement(im)
	 imtype = typeof(im(1));

//// because hypermat can not +-*/ with an integer scalar
//// so we have to convert the data to double first
//// After the bug is fixed, we can reuse the following code.

//	 select imtype
//	  case 'boolean' then
//	   im2 = ~im;
//	  case 'uint8' then
//	   im2 = uint8(- int16(im) + int16(255));
//	  case 'int8' then
//	   im2 = int8(-int16(im)-int16(1));
//	  case 'uint16' then
//	   im2 = uint16(-int32(im) + int32(2^16-1));
//	  case 'int16' then
//	   im2 = int16(-int32(im)-int32(1));
//	  case 'int32' then
//	   im2 = int32(-double(im)-1);
//	  case 'constant' then
//	   im2 = 1.0 - im;
//	 else
//	   error("Data type " + imtype + " is not supported.");
//	 end

// convert im to double is not efficient enough
	 select imtype
	  case 'boolean' then
	   im2 = ~im;
	  case 'uint8' then
	   im2 = uint8(- double(im) + 255);
	  case 'int8' then
	   im2 = int8(-double(im)-double(1));
	  case 'uint16' then
	   im2 = uint16(-double(im) + double(2^16-1));
	  case 'int16' then
	   im2 = int16(-double(im)-double(1));
	  case 'int32' then
	   im2 = int32(-double(im)-1);
	  case 'constant' then
	   im2 = 1.0 - im;
	 else
	   error("Data type " + imtype + " is not supported.");
	 end
endfunction
