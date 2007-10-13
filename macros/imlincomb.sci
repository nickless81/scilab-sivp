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

////////////////////////////////////////////////////////////
// imout = imlincomb(k1,im1, k2,im2, ..., kn,imn, [K]) 
//
// imout = k1*im1 + k2*im2 + ... + kn*imn
//   or
// imout = k1*im1 + k2*im2 + ... + kn*imn +K
////////////////////////////////////////////////////////////
function [imout] = imlincomb(varargin)
  
  imtype = 'undefined';
  totype = 'undefined';
  
  varlen = length(varargin);
  if(typeof(varargin(varlen))=='string') then
    totype = varargin(varlen);
    varlen = varlen-1;
  end
  
  if varlen < 2 then
    error("Too few arguments for function imlincomb.");
  end
  
  for ii = 1:2:varlen
    //K
    if(ii==varlen) then
      imout = imout + varargin(ii);
    elseif ii==1 then
      kn=varargin(ii);
      imn=varargin(ii+1);
      
      if(prod(size(kn))<>1) then
	error("The " + string(ii) +"''th argument should be a double scalar.");
      end
      
      imtype = typeof(imn(1));
      imout = double(imn)*kn;
    else
      kn=varargin(ii);
      imn=varargin(ii+1);
      
      if(prod(size(kn))<>1) then
	error("The " + string(ii) +"''th argument should be a double scalar.");
      end
      
      //check image size and class
      if(imtype <> typeof(imn(1)))
	error("The input images should has the same class.");
      end
      if and(size(imout) == size(imn))==%F then
	error("The input images should has the same size.");
      end
      
      imout = imout + double(imn)*kn;
    end //end if ii
  end //end for ii
  
  //convert the output image to the same type as the input images
  //or to the user specified type
  if(totype=='undefined') then
    totype=imtype;
  end
  
  select totype,
   case 'uint8' then
    imout = round(imout);
    imout(imout>255) = 255;
    imout(imout<0) = 0;
    imout = uint8(imout);
   
   case 'int8' then
    imout = round(imout);
    imout(imout>127) = 127;
    imout(imout<-128) = -128;
    imout = int8(imout);

   case 'uint16' then
    imout = round(imout);
    imout(imout>(2^16-1)) = 2^16-1;
    imout(imout<0) = 0;
    imout = uint16(imout);

   case 'int16' then
    imout = round(imout);
    imout(imout>(2^15-1)) = 2^15-1;
    imout(imout<(-2^15)) = -2^15;
    imout = int16(imout);

   case 'int32' then
    imout = round(imout);
    imout(imout>(2^31-1)) = 2^31-1;
    imout(imout<(-2^31)) = -2^31;
    imout = int16(imout);

   case 'constant' then
    ;
   else
    error("Data type " + totype + " is not supported.");
  end
  
endfunction
