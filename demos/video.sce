filename = SCI + '/contrib/sivp/images/walking.avi';

if MSDOS then filename=strsubst(filename,'/','\'),end

n = vdopen(filename);

for idx=1:100,
	im=vdgetframe(n);
	imshow(im);
end;
vdclose(n);