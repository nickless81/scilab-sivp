#include <mex.h> 
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc int_test;
extern Gatefunc int_sivp_init;
extern Gatefunc int_imread;
extern Gatefunc int_imwrite;
extern Gatefunc int_imfinfo;
extern Gatefunc int_aviinfo;
extern Gatefunc int_aviopen;
extern Gatefunc int_camopen;
extern Gatefunc int_avifile;
extern Gatefunc int_aviclose;
extern Gatefunc int_avicloseall;
extern Gatefunc int_avilistopened;
extern Gatefunc int_avireadframe;
extern Gatefunc int_addframe;
extern Gatefunc int_imresize;
extern Gatefunc int_imabsdiff;
extern Gatefunc int_imadd;
extern Gatefunc int_imsubtract;
extern Gatefunc int_immultiply;
extern Gatefunc int_imdivide;
extern Gatefunc int_imfilter;
extern Gatefunc int_filter2;
extern Gatefunc int_mat2utfimg;
extern Gatefunc int_canny;
extern Gatefunc int_sobel;
extern Gatefunc int_cvtcolor;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway,int_test,"sivptest"},
  {(Myinterfun)sci_gateway,int_sivp_init,"sivp_init"},
  {(Myinterfun)sci_gateway,int_imread,"imread"},
  {(Myinterfun)sci_gateway,int_imwrite,"imwrite"},
  {(Myinterfun)sci_gateway,int_imfinfo,"imfinfo"},
  {(Myinterfun)sci_gateway,int_aviinfo,"aviinfo"},
  {(Myinterfun)sci_gateway,int_aviopen,"aviopen"},
  {(Myinterfun)sci_gateway,int_camopen,"camopen"},
  {(Myinterfun)sci_gateway,int_avifile,"avifile"},
  {(Myinterfun)sci_gateway,int_aviclose,"aviclose"},
  {(Myinterfun)sci_gateway,int_avicloseall,"avicloseall"},
  {(Myinterfun)sci_gateway,int_avilistopened,"avilistopened"},
  {(Myinterfun)sci_gateway,int_avireadframe,"avireadframe"},
  {(Myinterfun)sci_gateway,int_addframe,"addframe"},
  {(Myinterfun)sci_gateway,int_imresize,"int_imresize"},
  {(Myinterfun)sci_gateway,int_imabsdiff,"int_imabsdiff"},
  {(Myinterfun)sci_gateway,int_imadd,"int_imadd"},
  {(Myinterfun)sci_gateway,int_imsubtract,"int_imsubtract"},
  {(Myinterfun)sci_gateway,int_immultiply,"int_immultiply"},
  {(Myinterfun)sci_gateway,int_imdivide,"int_imdivide"},
  {(Myinterfun)sci_gateway,int_imfilter,"imfilter"},
  {(Myinterfun)sci_gateway,int_filter2,"filter2"},
  {(Myinterfun)sci_gateway,int_mat2utfimg,"mat2utfimg"},
  {(Myinterfun)sci_gateway,int_canny,"int_canny"},
  {(Myinterfun)sci_gateway,int_sobel,"int_sobel"},
  {(Myinterfun)sci_gateway,int_cvtcolor,"int_cvtcolor"},
};
 
int C2F(libsivp)()
{
  Rhs = Max(0, Rhs);
  (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  return 0;
}
