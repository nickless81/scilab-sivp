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

function [imdiff] = imabsdiff(im1, im2)

    //check the image width and height
    if( or( size(im1)<>size(im2) )) then
	error("The two images do not have the same size or the same channel number.");
	//return;
    end
  
    if (size(size(im1),2)>3) then
	error("The two inputs are not images");
	return;
    end
    if (size(size(im1),2)==3) then
        if (size(im1, 3)<>1) & (size(im1,3)<>3) then
	    error("The two inputs are not images");
	    //return;
        end	    
    end

    //actruely abs(im1-im2) will be more efficient,
    //but if the two image are all unsigned integer
    // abs(uint8(8)-uint(9)) will give error result
    //so we have to use OpenCV cvAbsDiff function for the same type at this situation

    tt = str2code(typeof(im1(1)));
    tt = code2str( tt( 1:min(length(tt),4)));

    //if the same data type and isn't uint32
    if (type(im1(1))==type(im2(1)) & typeof(im1(1))==typeof(im2(1)) & typeof(im1(1))<>'uint32') then
       imdiff = int_imabsdiff(im1, im2);
       //imdiff = abs(im1 - im2);
    else //convert to the same type first
       //imdiff = int_imabsdiff(double(im1), double(im2));
       imdiff = abs(double(im1)-double(im2));
    end

endfunction
