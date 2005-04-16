#include <mex.h> 
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc int_vdofinfo;
extern Gatefunc int_sivp_formats;
extern Gatefunc int_imgread;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway,int_vdofinfo,"vdofinfo"},
  {(Myinterfun)sci_gateway,int_sivp_formats,"sivp_formats"},
  {(Myinterfun)sci_gateway,int_imgread,"imgread"},
};
 
int C2F(sivp)()
{
  Rhs = Max(0, Rhs);
  (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  return 0;
}
