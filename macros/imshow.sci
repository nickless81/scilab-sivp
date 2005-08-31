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

	imc=mat2utfimg(uint8(im));

	if (channel==1)
		imc='P5'+char(10)+msprintf('%d %d",width,height)+char(10)+'255'+char(10)+char(imc); 
	else
		imc='P6'+char(10)+msprintf('%d %d",width,height)+char(10)+'255'+char(10)+char(imc); 
	end

	TCL_SetVar('imagewidth',msprintf('%d',width));
	TCL_SetVar('imageheight',msprintf('%d',height));
	TCL_SetVar('imagechannel',msprintf('%d',channel));
	TCL_SetVar('imagedata', imc);

	TCL_EvalFile(SCI + '/contrib/sivp/macros/imshow.tcl');
endfunction
