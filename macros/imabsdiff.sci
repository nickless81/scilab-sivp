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

    //must be the same class, and not be uint32
    if (type(im1(1))<>type(im2(1)) | ...
      typeof(im1(1))<>typeof(im2(1)) | ...
      typeof(im1(1))=='uint32'   ) then
      error("The two input images must be of the same class and not be"+...
	     " uint32.");
    end

    //actruely abs(im1-im2) will be more efficient,
    //but abs(uint8(8)-uint8(9)) 
    //and abs(int16(2^15-1)-int16(-1))  will give error results 
    //(255 and -32768 respectively)
    //so we have to use OpenCV cvAbsDiff function for the same type at
    //these situations

    //int8 is not supported by OpenCV function cvAbsDiff
    //convert to int16 first when int8 class
    if ( typeof(im1(1))=='constant') then //double
       imdiff = abs(im1 - im2); 
    elseif ( typeof(im1(1))=='int8') then //int8
       imdiff = abs(int16(im1) - int16(im2));
       imdiff(imdiff > 127) = int16(127);
       imdiff = int8(imdiff);
    else 
       imdiff = int_imabsdiff(im1, im2);
    end

endfunction
