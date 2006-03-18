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

function [subim] = imcrop(im, rect)

	 //get the image width and height
	 [imh,imw] = size(im);

	 //check the rectangle
	 if (rect(1)<1 | rect(2)<1 | rect(1)+rect(3)-1>imw | rect(2)+rect(4)-1>imh ) then
	    error("The rectangle is out of the image range.");
	    return;   
	 end

	 if (size(size(im),2) ==2) //gray image
	    subim = im(rect(2):rect(2)+rect(4)-1, rect(1):rect(1)+rect(3)-1);
	 elseif (size(size(im),2) ==3)//RGB image
	    subim = im(rect(2):rect(2)+rect(4)-1, rect(1):rect(1)+rect(3)-1, :);
	 else
	    error("Is the imput an image?");
	    return;
	 end
endfunction