////////////////////////////////////////////////////////////
// SIVP - Scilab Image and Video Processing toolbox
// Copyright (C) 2006  Shiqi Yu
//
// SIP - Scilab Image Processing toolbox
// Copyright (C) 2002-2004  Ricardo Fabbri
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


function [border, thresh]=edge(Img, method, thresh, dir_or_sig, sig)
// 
// AUTHOR
//    Shiqi Yu
//
//    Ricardo Fabbri  <rfabbri@if.sc.usp.br>
//    Cybernetic Vision Research Group
//    Luciano da Fontoura Costa, supervisor.
//    http://cyvision.if.sc.usp.br
//
// REFERENCE
//    "Algorithms for Image Processing and Computer Vision", 
//    J.R. Parker, Wiley, chapter 1.
//

  

  if argn(2)==0 then
    error('Invalid number of arguments.')
  end
  
  //check image channel
  if size( size(Img),2) <> 2  then
    error('The input image should be a single channel image.');
  end
  
  if ~exists('method','local') then
    method='sobel'
  end

  if ~exists('thresh','local') then
    thresh=0.2;
  end

  direction='both'; //default value
  sigma = []; //default value

  if exists('dir_or_sig', 'local') then
    if( typeof(dir_or_sig) == 'string') then
      direction = dir_or_sig;
    elseif (typeof(dir_or_sig) == 'constant') then
      sigma = dir_or_sig;
    end
  end
  
  if exists('sig', 'local') then
    sigma = sig;
  end
  
  select method,
   case 'sobel' then
    //mask = fspecial('sobel');
    if(direction=='horizontal') then
      border=int_sobel(Img, 0, 1, thresh);
    elseif(direction=='vertical') then
      border=int_sobel(Img, 1, 0, thresh);
    elseif(direction=='both') then
      border=int_sobel(Img, 1, 1, thresh);
    else
      error('Invalid direction');
    end
    
    if (thresh > 0) then
      border=im2bw(border, 0.5);
    else
      border=double(border);
    end
    //End sobel
    return; 
   case 'prewitt' then
    mask = fspecial('prewitt');
   case 'log' then
    if isempty(sigma) then
      sigma=2;
    end
    direction = 'horizontal'; //to prevent filter two times

    mask = fspecial('log', ceil(sigma*3)*2+1, sigma);
   case 'canny' then
    //set default thresh value
    //negative value is invalid here
    if thresh < 0 then
      thresh = 0.3;
    end
    
    if(length(thresh)==1) then
      low_th=thresh*0.4;
      high_th=thresh;
    elseif (length(thresh)==2) then
      low_th=thresh(1);
      high_th=thresh(2);
    else
      error('Invalid threshold for Canny method: Can not be negative.');
    end
    
    if isempty(sigma) then
      sigma=3;
    end
    if and(sigma <> [1,3,5,7]) then
      error('sigma for canny must be 1, 3, 5 or 7.');
    end
      
    border = int_canny(Img, low_th*1024, high_th*1024, sigma);
    border = im2bw(border, 0.5);
    
    //END of CANNY
    return;
   case 'fftderiv' // fourier gradient
    if isempty(sigma) then
      sigma=1;
    end
    
    Img = double(Img);
    
    [r,c] = size(Img)
    fu = [0:c-1]*(1/c)
    fv = [0:r-1]*(1/r)
    fu(int(c/2):c) = fu(int(c/2):c) - 1;
    fv(int(r/2):r) = fv(int(r/2):r) - 1;
    
    if sigma == 0
      gf = ones(r,c)
    else
      gf = ones(r,1) * exp(-(sigma*%pi*fu)^2)
      gv = exp(-(sigma*%pi*fv')^2) * ones(1,c)
      gf = gf .* gv
    end

    select direction
     case 'horizontal'
      fvp = %i*2*%pi*fv' * ones(1,c)
      Dyf = fft(Img,-1) .* gf .* fvp
      border = abs(fft(Dyf,1))
     case 'vertical'
      fup = ones(r,1) * %i*2*%pi*fu
      Dxf = fft(Img,-1) .* gf .* fup
      border = abs(fft(Dxf,1))
     case 'both'
      fup = ones(r,1) * %i*2*%pi*fu
      fvp = %i*2*%pi*fv' * ones(1,c)
      Dxf = fft(Img,-1) .* gf .* fup
      Dyf = fft(Img,-1) .* gf .* fvp
      
      Dx = abs(fft(Dxf,1))
      Dy = abs(fft(Dyf,1))
      
      border = sqrt(Dx.^2 + Dy.^2)
     else
      error('Invalid direction.');
    end
    
    if thresh >=0 then
      scale_thresh = min(border) * (1-thresh) + max(border)*thresh;
      border=border > scale_thresh;
    end
   // END
   return
  else
    error('Invalid edge detection method.')
  end

  select direction
   case 'horizontal'
    mx=filter2(mask, Img);
    border=abs(mx)
   case 'vertical'
    my=filter2(mask', Img);
    border=abs(my)
   case 'both'
    mx=filter2(mask, Img);
    my=filter2(mask',Img);
    border=sqrt(mx.*mx + my.*my);
   else
    error('Invalid direction.');
  end

  if thresh >=0 then
    scale_thresh = min(border) * (1-thresh) + max(border)*thresh;
    border=border > scale_thresh;
  end

endfunction

