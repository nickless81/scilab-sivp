imgsrcdir="/mnt/store/refined-nonorm-silh/121/nm-01/090/";
imsrcdir="/mnt/store/refined-nonorm-silh/122/nm-01/090/";

imgfiles=listfiles(imgsrcdir + "*.png");
imfiles=listfiles(imsrcdir + "*.png");

imgdt1=getdate();
filenum=min(size(imgfiles,1), size(imfiles,1));

for ii=1:filenum
  img=imgread(imgfiles(ii));
end

imgdt2=getdate();



imdt1=getdate();


for ii=1:filenum
  im=imread(imfiles(ii));
end

imdt2=getdate();



imgdt=imgdt2-imgdt1;
imdt=imdt2-imdt1;


imgdt(9)*1000+imgdt(10)
imdt(9)*1000+imdt(10)

