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

function [c] = corr2(imA, imB)
	 if ( (size(size(imA), 2) >=3) | (size(size(imB), 2) >=3)) then
	    error("The input must be 2D matrix.");
	 end

	 //check the image width and height
	 if( or( size(imA)<>size(imB) )) then
	     error("The two inputs do not have the same size.");
         end

	 difA = double(imA) - mean2(imA);
	 difB = double(imB) - mean2(imB);

	 c = sum( difA.*difB ) / sqrt(sum(difA.^2) * sum(difB.^2));
endfunction
