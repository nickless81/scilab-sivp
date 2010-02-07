
r=messagebox("Do you really have a camera?", "modal", "info", ["Yes" "No"])

if r==1
	n = camopen();
  
	if( isdef('n') )
	if(n>0)
		for idx=1:100,
			im=avireadframe(n);
			imshow(im);
		end;
		aviclose(n);
	end;
	end;
end
