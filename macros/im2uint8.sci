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

function [im2] = im2uint8(im)
	 imtype = typeof(im);
	 
	 select imtype
	 	case 'boolean' then
		     im2 = uint8(im*255);
		case 'uint8' then
		     im2 = im;
		case 'int8' then
		     im2 = uint8(im)+128;
		case 'uint16' then
		     im2 = uint8(double(im)*(2^8-1)/(2^16-1)+0.5);
		case 'int16' then
		     im2 = uint8((double(im) + 2^15)*(2^8-1)/(2^16-1)+0.5);
		case 'int32' then
		     im2 = uint8((double(im)+2^31) * (2^8-1)/(2^32-1)+0.5);
	 	case 'constant' then
		     im2 = uint8(im * 255);
		else
		     error("Data type " + imtype + " is not supported.");
		end
endfunction
