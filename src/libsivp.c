#include <mex.h> 
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc int_test;
extern Gatefunc int_sivp_init;
extern Gatefunc int_imread;
extern Gatefunc int_imwrite;
extern Gatefunc int_vdopen;
extern Gatefunc int_vdgetframe;
extern Gatefunc int_vdshowopened;
extern Gatefunc int_vdclose;
extern Gatefunc int_vdcloseall;
extern Gatefunc int_mat2utfimg;
extern Gatefunc int_canny;
extern Gatefunc int_convert;
extern Gatefunc int_laplace;
extern Gatefunc int_precornerdetec;
extern Gatefunc int_imsmooth;
extern Gatefunc int_sobel;
extern Gatefunc int_threshold;
extern Gatefunc int_adaptativethreshold;
extern Gatefunc int_erode;
extern Gatefunc int_dilate;
extern Gatefunc int_pyrdown;
extern Gatefunc int_pyrup;
extern Gatefunc int_goodfeaturestotrack;
extern Gatefunc int_xor;
extern Gatefunc int_not;
extern Gatefunc int_cmp;
extern Gatefunc int_hough;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway,int_test,"sivptest"},
  {(Myinterfun)sci_gateway,int_sivp_init,"sivp_init"},
  {(Myinterfun)sci_gateway,int_imread,"imread"},
  {(Myinterfun)sci_gateway,int_imwrite,"imwrite"},
  {(Myinterfun)sci_gateway,int_vdopen,"vdopen"},
  {(Myinterfun)sci_gateway,int_vdgetframe,"vdgetframe"},
  {(Myinterfun)sci_gateway,int_vdshowopened,"vdshowopened"},
  {(Myinterfun)sci_gateway,int_vdclose,"vdclose"},
  {(Myinterfun)sci_gateway,int_vdcloseall,"vdcloseall"},
  {(Myinterfun)sci_gateway,int_mat2utfimg,"mat2utfimg"},
  {(Myinterfun)sci_gateway,int_canny,"canny"},
  {(Myinterfun)sci_gateway,int_convert,"convert"},
  {(Myinterfun)sci_gateway,int_laplace,"laplace"},
  {(Myinterfun)sci_gateway,int_precornerdetec,"precornerdetec"},
  {(Myinterfun)sci_gateway,int_imsmooth,"imsmooth"},
  {(Myinterfun)sci_gateway,int_sobel,"sobel"},
  {(Myinterfun)sci_gateway,int_threshold,"threshold"},
  {(Myinterfun)sci_gateway,int_adaptativethreshold,"adaptativethreshold"},
  {(Myinterfun)sci_gateway,int_erode,"erode"},
  {(Myinterfun)sci_gateway,int_dilate,"dilate"},
  {(Myinterfun)sci_gateway,int_pyrdown,"pyrdown"},
  {(Myinterfun)sci_gateway,int_pyrup,"pyrup"},
  {(Myinterfun)sci_gateway,int_goodfeaturestotrack,"goodfeaturestotrack"},
  {(Myinterfun)sci_gateway,int_xor,"xor"},
  {(Myinterfun)sci_gateway,int_not,"not"},
  {(Myinterfun)sci_gateway,int_cmp,"cmp"},
  {(Myinterfun)sci_gateway,int_hough,"hough"},
};
 
int C2F(libsivp)()
{
  Rhs = Max(0, Rhs);
  (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  return 0;
}
