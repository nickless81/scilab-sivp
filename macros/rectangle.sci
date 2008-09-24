function [imr]=rectangle(im, position, rgb)

	 //get the image width and height
	 [imh,imw] = size(im);

	 //check the rectangle position
	 if (position(1)<1 | position(2)<1 | position(1)+position(3)-1>imw | position(2)+position(4)-1>imh) then
	    error("The rectangle is out of the image range.");
	    return;   
	 end

      //check color value
      for i=1:3,
          if (rgb(i)>255 | rgb(i)<0) then
             error("The value of R,G,B should be in [0,255].")
             return;
          end
      end

	 if (size(size(im),2) == 2)  //gray image
          im(position(2):(position(4)-1):(position(2)+position(4)-1), position(1):(position(1)+position(3)-1))=rgb(1);
          im(position(2):(position(2)+position(4)-1), position(1):(position(3)-1):(position(1)+position(3)-1))=rgb(1);  
	 elseif (size(size(im),2) == 3)  //RGB image
          for i=1:3,
          im(position(2):(position(4)-1):(position(2)+position(4)-1), position(1):(position(1)+position(3)-1), i)=rgb(i);
          im(position(2):(position(2)+position(4)-1), position(1):(position(3)-1):(position(1)+position(3)-1), i)=rgb(i);
          end       
	 else
	    error("Is the imput an image?");
	    return;
	 end

       imr=im;

endfunction
