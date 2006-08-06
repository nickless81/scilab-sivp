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

//
// salt & pepper (drop-out noise): 
//    d: density, from 0 to 1
//
// gaussian
//    m: mean (from 0 to 1)
//    v: variance (from 0 to 1)
//
// imnoise(img, 'localvar',V);
//    Additive gaussian noise where the variance at Img(i,j) is
//    V(i,j).
// imnoise(img, 'localvar',x, y);
//    
//
// speckle (multiplicative noise)
//    Image = Image + prob*Image
//    where "prob" is a gaussian(0-1) distributed noise
//    v: variance
//

function imn = imnoise(im, noise_type, param1, param2)
//function imn = imnoise(im, noise_type, param1, param2, param3)
  
  //source image type
  imtype = typeof(im(1));
  //convert image to double
  im=im2double(im);

  // directly im+rand(im) will cause "inconsistent addition".
  // so firstly reshape the input matrix
  // what causes the problem? SIVP hypermat creation code?
  im=matrix(im(:), size(im));
  
  //Gaussian noise
  if (noise_type == 'gaussian' | noise_type == 'Gaussian') then
    if ~exists('param1','local')
      m=0
    else
      m=param1
    end
    if ~exists('param2','local')
      v=0.01
    else
      v=param2
    end
    
    // Set the current random generator 
    // to a Gaussian (with mean 0 and variance 1) random number
    // generator. 
    //
    // rand(4,5,3, 'normal') will return a matrix sized 4x5x3x1
    // but rand('normal');rand(4,5,3) will return a matrix sized 4x5x3x1
    // besides, rand(im, 'normal') will return error,
    // so here we have to use rand('normal') set to a Gassian generator.
    old_rand_gen=rand('info');
    rand('normal');
    
    imn = im + sqrt(v)*rand(im) + m;
    
    rand(old_rand_gen);
    
    
  elseif noise_type == 'localvar'
    if argn(2) < 3 then
      error('Too few arguments for noise type ''localvar''.');
      
    //only one parameter
    elseif argn(2) == 3 then
      if( or(size(im)<>size(param1))) then
	error("The first parameter for ''localvar'' should have the same"+...
	      " size with the input image.");
      end
      
      old_rand_gen=rand('info');
      rand('normal');
      imn = matrix(im(:), size(im)) + sqrt(param1).*rand(im);
      rand(old_rand_gen);
      
    //two parameters  
    elseif argn(2) == 4 then
      if( or(size(param1)<>size(param2))) then
	error("The two parameters for ''localvar'' should have the same size.");
      end
      
      minp1 = min(param1);
      maxp1 = max(param1);
      imn = min(max(im(:),minp1),maxp1); //max(im,minp1) can't work
                                         //because im is a hypermat.
      imn = matrix(interp1(param1(:),param2(:),imn),size(im));
      
      old_rand_gen=rand('info');
      rand('normal');
      imn = im + sqrt(imn).*rand(im);
      rand(old_rand_gen);
    end
    
  //salt & pepper noise
  elseif noise_type == 'salt & pepper' | noise_type == 'salt and pepper'
    if ~exists('param1','local')
      d=0.05 
    else
      d=param1
      
      if( d < 0 | d > 1) then
	error("The parameter for ''salt & pepper'' noise should in range [0,1].");
      end
    end
    
    // logic:
    //
    // If prob <= d, then modify pix value like this:
    //    if prob <= d/2
    //       put salt
    //    else
    //       put pepper.
    //
    old_rand_gen=rand('info');
    rand('uniform');
    prob=rand(im);
    rand(old_rand_gen);
    
    imn=im;
    imn(prob < d/2) = 0;
    imn(prob >=d/2 & prob < d) = 1;
    
  elseif noise_type=='speckle'
    if ~exists('param1','local')
      v=0.04
    else
      v=param1
      if( d < 0) then
	error("The parameter for ''speckle'' noise should >=0.");
      end
   end

   old_rand_gen=rand('info');
   rand('uniform');
   imn = im + im .* (sqrt(v) * (rand(im)-0.5) );   
   rand(old_rand_gen);
   
  elseif noise_type == 'poisson'
    error('Not yet implemented');
  else
    error('Invalid noise type.');
  end

  //conver the output image to the same type as the input image
  
  select imtype
   case 'uint8' then
    imn = im2uint8(imn);
   case 'int8' then
    imn = im2int8(imn);
   case 'uint16' then
    imn = im2uint16(imn);
   case 'int16' then
    imn = im2int16(imn);
   case 'int32' then
    imn = im2int32(imn);
   case 'constant' then
    imn = im2double(imn);
   else 
    error("Data type " + imtype + " is not supported.");
  end

endfunction
