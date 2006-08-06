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

//because OpenCV function cvResize can only
//handle UINT8, UINT16 and SINGLE FLOAT classes,
//convert image to these three classes first before resizing
function [imout] = imresize(imin, varargin)
  
    //if INT8, convert to UINT8 first
    if (typeof(imin(1))=='int8') then
      if length(varargin)==1 then
	imout = int_imresize(im2uint8(imin), varargin(1));
      elseif length(varargin)==2 then
	imout = int_imresize(im2uint8(imin), varargin(1),varargin(2));
      end
      
      imout = im2int8(imout);
      
    //if INT16, convert to UINT16 first
    elseif (typeof(imin(1))=='int16') then
      if length(varargin)==1 then
	imout = int_imresize(im2uint16(imin), varargin(1));
      elseif length(varargin)==2 then
	imout = int_imresize(im2uint16(imin), varargin(1),varargin(2));
      end
      
      imout = im2int16(imout);
      
//    //if INT32, convert to double first
//    elseif (typeof(imin(1))=='int32') then
//      if length(varargin)==1 then
//	imout = int_imresize(im2double(imin), varargin(1));
//      elseif length(varargin)==2 then
//	imout = int_imresize(im2double(imin), varargin(1),varargin(2));
//      end
//      
//      imout = im2int32(imout);
      
    //UINT8, UINT16, INT32 and DOUBLE will be handled by C interface int_imresize
    else
      if length(varargin)==1 then
	imout = int_imresize(imin, varargin(1));
      elseif length(varargin)==2 then
	imout = int_imresize(imin, varargin(1),varargin(2));
      end
    end
    

endfunction