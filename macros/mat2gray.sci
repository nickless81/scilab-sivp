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

function [G] = mat2gray(M, mm)

	 //check input
	 if(size(size(M),2)>2)
		error("The input matrix M should be 2D matrix.");
	 end

	 //get rhs
	 rhs=argn(2);
	 //convert to double
	 M = double(M);
	 if (rhs==1)  then
	    mmin = min(M);
	    mmax = max(M);
	 elseif (rhs==2)
	    if(length(mm)<>2)
		error("The second argument should be a 2-element vector.");
	    end
	    mmin = mm(1);
	    mmax = mm(2);
	 end
 
	 if (mmax < mmin)
	    error("Parameter mmax should be greater than mmin");
	 end 
	 
	 //map M from [mmin, mmax] to [0,1]
	 if (mmax == mmin)
	    G=zeros(size(M,1), size(M,2));
	 else	       
	    G = (M-mmin)/(mmax-mmin);
	    G(G>1) = 1;
	    G(G<0) = 0;
	 end
endfunction
