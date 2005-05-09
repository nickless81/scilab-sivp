#include <mex.h> 
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc int_vdofinfo;
extern Gatefunc int_sivp_formats;
extern Gatefunc int_imgread;
extern Gatefunc int_imgwrite;
extern Gatefunc int_vdoopen;
extern Gatefunc int_vdoclose;
extern Gatefunc int_vdocloseall;
extern Gatefunc int_vdoshowopened;
extern Gatefunc int_vdogetframe;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway,int_vdofinfo,"vdofinfo"},
  {(Myinterfun)sci_gateway,int_sivp_formats,"sivp_formats"},
  {(Myinterfun)sci_gateway,int_imgread,"imgread"},
  {(Myinterfun)sci_gateway,int_imgwrite,"int_imgwrite"},
  {(Myinterfun)sci_gateway,int_vdoopen,"vdoopen"},
  {(Myinterfun)sci_gateway,int_vdoclose,"vdoclose"},
  {(Myinterfun)sci_gateway,int_vdocloseall,"vdocloseall"},
  {(Myinterfun)sci_gateway,int_vdoshowopened,"vdoshowopened"},
  {(Myinterfun)sci_gateway,int_vdogetframe,"vdogetframe"},
};
 
int C2F(sivp)()
{
  Rhs = Max(0, Rhs);
  (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  return 0;
}
