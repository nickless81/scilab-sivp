////////////////////////////////////////////////////////////
// SIVP - Scilab Image and Video Processing toolbox
// Copyright (C) 2005-2006  Shiqi Yu
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


function imshow(im)
	//get dim of image
	width =size(im,2);
	height=size(im,1);
	channel = 0;

	//check whether it is an image
	if(size(size(im),2)==3) then
		if( size(im,3) == 3 | size(im,3) == 1) then
			channel = size(im,3);
		end
	end
	if(size(size(im),2)==2) then
		channel=1;
	end

	if(channel==0)
		error("The input should be an image.");
		return;
	end

	//imc=mat2utfimg(uint8(im));
	imc=mat2utfimg(im2uint8(im));

	if (channel==1)
		imc='P5'+char(10)+msprintf("%d %d",width,height)+char(10)+'255'+char(10)+char(imc); 
	else
		imc='P6'+char(10)+msprintf("%d %d",width,height)+char(10)+'255'+char(10)+char(imc); 
	end

	TCL_SetVar('imagewidth',msprintf("%d",width));
	TCL_SetVar('imageheight',msprintf("%d",height));
	TCL_SetVar('imagechannel',msprintf("%d",channel));
	TCL_SetVar('imagedata', imc);

	TCL_EvalFile(SIVP_PATH +'/macros/imshow.tcl');
endfunction
