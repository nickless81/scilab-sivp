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

function [im2] = im2bw(im, thresh)
	 if (thresh < 0 | thresh > 1)
	    error("thresh should be in the range [0,1]");
	 end

	 dims = size(im);
	 if (size(dims,2)== 3) then
	   if (dims(3)<>3) then
	     error("The input matrix im should be MxN or M x N x 3 matrix.");
	   end
	   //convert the RGB image to gray image first
	   im = rgb2gray(im);
	 elseif (size(size(im),2)>3) then
	   error("The input matrix im should be MxN or M x N x 3 matrix.");
	 end

	 imtype = typeof(im(1));
	 
	 select imtype
	 	case 'boolean' then
		     im2 = im;
		case 'uint8' then
		     im2 = im > uint8(round((2^8-1)*thresh));
		case 'int8' then
		     im2 = im > int8(round((2^8-1)*thresh-128));
		case 'uint16' then
		     im2 = im > uint16(round((2^16-1)*thresh)); 
		case 'int16' then
		     im2 = im > int16(round((2^16-1)*thresh-2^15)); 
		case 'int32' then
		     im2 = im > int32(round((2^32-1)*thresh-2^31)); 
	 	case 'constant' then
		     im2 = im > thresh;
		else
		     error("Data type " + imtype + " is not supported.");
	 end
endfunction
