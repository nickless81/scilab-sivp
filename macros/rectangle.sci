function [imr]=rectangle(im, position, rgb)

	 //get the image width and height
	 [imh,imw] = size(im);
     position=round(position);
     xx = position(1);
     yy = position(2)
     ww = position(3);
     hh = position(4);

	 //check the rectangle position
	 if (xx<1 | yy<1 | xx+ww-1>imw | yy+hh-1>imh) then
	    error("The rectangle is out of the image range.");
	    return;   
	 end

	 if (size(size(im),2) == 2)  //gray image
          im( [yy, (yy+hh-1)], xx:(xx+ww-1) )=rgb(1);
          im( [yy:(yy+hh-1)], [xx, (xx+ww-1)] )=rgb(1);  
	 elseif (size(size(im),2) == 3)  //RGB image
          for i=1:3,
          im([yy,(yy+hh-1)], xx:(xx+ww-1), i)=rgb(i);
          im(yy:(yy+hh-1), [xx,(xx+ww-1)], i)=rgb(i);
          end       
	 else
	    error("Is the imput an image?");
	    return;
	 end

       imr=im;

endfunction
