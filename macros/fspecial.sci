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

//Create 2-D special filters.
function [F] = fspecial(ftype, varargin)
  
  //check input
  if typeof(ftype)~='string' then
    error('The first argument must be a string.');
  end
  
  op1 = [];
  op2 = [];
  if length(varargin)>=1 then
    op1 = varargin(1);
    if ~isreal(op1) then, error("The second arguument should be real."); end
  end
  if length(varargin)>=2 then
    op2 = varargin(2);
    if ~isreal(op2) then, error("The third arguument should be real."); end
  end
  if length(varargin)>2 then
    error("Too many arguments.");
  end
  
  select ftype,
    
    //----------------------------------------------
    //sobel filter
   case 'sobel' then,
    if length(varargin)>0 then, 
      error("Too many arguments for this kind of filter");
    end
    F=[1 2 1; 0 0 0; -1 -2 -1];
    
    //----------------------------------------------
    //prewitt filter
   case 'prewitt' then,
    if length(varargin)>0 then, 
      error("Too many arguments for this kind of filter");
    end
    F=[1 1 1; 0 0 0; -1 -1 -1];
    
    //----------------------------------------------
    //average filter
   case 'average' then,
    if length(varargin)>1 then, 
      error("Too many arguments for this kind of filter");
    end
    if isempty(op1) then, 
      op1=3; 
    else
      if op1 ~= floor(op1) then, error('The second argument must be an integer.'); end;
    end
    F = ones(op1,op1)/op1/op1;

    //----------------------------------------------
    //gaussian low pass filter
    case 'gaussian' then,
     //set the size for the filter
     if isempty(op1) then
       siz = [3,3];
     else
       if length(op1)==1 then
	 siz = [op1, op1];
       elseif length(op1)==2 then
	 siz = op1;
       else
	 error("The second argument should have 1 or 2 elements for gaussian filter");
       end
     end
     //set std for the filter
     if isempty(op2) then
       g_std = 0.5;
     else
       if length(op2)>1 then
	 error("The third argument should have only 1 element for gaussian filter");
       else
	 g_std = op2;
       end
     end
     //
     sizx = (siz(2)-1)/2;
     sizy = (siz(1)-1)/2;
     x2 = ones(siz(1),1) * ([-sizx:sizx]^2);
     y2 = ([-sizy:sizy]^2)' * ones(1, siz(2));
     F = exp( -(x2+y2)/(2*g_std^2) );
     F(F<%eps*max(F)) = 0;
     sumF=sum(F);
     if sumF~=0 then
       F = F / sum(F);
     end
   //----------------------------------------------
   //laplacian filter
   case 'laplacian' then,
    if length(varargin)>1 then, 
      error("Too many arguments for this kind of filter");
    end
    if isempty(op1) then, 
      op1=0.2; 
    else
      if (op1 < 0 | op1 > 1) then, error("The second argument should be in range [0, 1]"); end,
    end
    op1d=1-op1;
    F = [op1, op1d, op1; op1d, -4, op1d; op1, op1d, op1]/(op1+1);
    
   //----------------------------------------------
   //log filter:a rotationally symmetric Laplacian of Gaussian filter 
   case 'log' then,
    //get faussian filter first
     if isempty(op1) then
       siz = [5,5];
     else
       if length(op1)==1 then
	 siz = [op1, op1];
       elseif length(op1)==2 then
	 siz = op1;
       else
	 error("The second argument should have 1 or 2 elements for log filter");
       end
     end
     //set std for the filter
     if isempty(op2) then
       g_std = 0.5;
     else
       if length(op2)>1 then
	 error("The third argument should have only 1 element for log filter");
       else
	 g_std = op2;
       end
     end
     //
     sizx = (siz(2)-1)/2;
     sizy = (siz(1)-1)/2;
     x2 = ones(siz(1),1) * ([-sizx:sizx]^2);
     y2 = ([-sizy:sizy]^2)' * ones(1, siz(2));
     F = exp( -(x2+y2)/(2*g_std^2) );
     F(F<%eps*max(F)) = 0;
     sumF=sum(F);
     if sumF~=0 then
       F = F / sum(F);
     end
    //now laplacian
    Ftmp = F.*(x2+y2-2*g_std^2)/(g_std^4);
    F = Ftmp - sum(Ftmp(:))/prod(siz);

   //----------------------------------------------
   //unsharp contrast enhancement filter
   case 'unsharp' then,
    if length(varargin)>1 then, 
      error("Too many arguments for this kind of filter");
    end
    if isempty(op1) then, 
      op1=0.2; 
    else
      if (op1 < 0 | op1 > 1) then, error("The second argument should be in range [0, 1]"); end,
    end
     F = [0, 0,0; 0, 1, 0; 0, 0, 0] - fspecial('laplacian',op1);

   else
    error('No such kind of filter: ' + ftype );
  end
  

endfunction
