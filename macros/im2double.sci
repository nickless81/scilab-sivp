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

function [im2] = im2double(im)
	 imtype = typeof(im(1));
	 
	 select imtype
	 	case 'boolean' then
		     im2 = double(im);
		case 'uint8' then
		     im2 = double(im) / 255.0;
		case 'int8' then
		     im2 = (double(im) + 128) / 255.0;
		case 'uint16' then
		     im2 = double(im) / (2^16-1);
		case 'int16' then
		     im2 = (double(im) + 2^15) / (2^16-1);
		case 'int32' then
		     im2 = (double(im) + 2^31) / (2^32-1);
	 	case 'constant' then
		     im(im>1.0) = 1.0;
		     im(im<0.0) = 0.0;
		     im2 = im;
		else
		     error("Data type " + imtype + " is not supported.");
		end
endfunction
