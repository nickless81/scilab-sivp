#include "sivp_common.h"
#include "stack-c.h"

/******************************************************
 * list all supported video formats and image formats
 ******************************************************/

int
int_sivp_formats(char *fname)
{
  int minlhs=1, maxlhs=1, minrhs=0, maxrhs=0;


  AVImageFormat *image_fmt;  

  CheckRhs(minrhs,maxrhs) ;
  CheckLhs(minlhs,maxlhs) ;

  //register all available formats
  av_register_all();

  //print all supported image formats
  //cracked from libavcodec/utils.c
  sciprint("Supported image and video formats. D: Decoding; E: Encoding\n\r\n\r");
  sciprint("Image formats:\n\r");
  for(image_fmt = first_image_format; image_fmt != NULL; image_fmt = image_fmt->next) 
    {
      sciprint(
             "\t%s%s    %-6s %s\n",
             image_fmt->img_read  ? "D":" ",
             image_fmt->img_write ? "E":" ",
             image_fmt->name,
             image_fmt->extensions ? image_fmt->extensions:" ");
    }


  sciprint("\n");
  //for video formats
  sciprint("Video codecs:\n\r");

  const char * last_name;
  last_name= "000";
  for(;;){
    int decode=0;
    int encode=0;

    
    AVCodec * p, *p2;    

    p2=NULL;
    for(p = first_avcodec; p != NULL; p = p->next) 
      {
	if((p2==NULL || strcmp(p->name, p2->name)<0) && strcmp(p->name, last_name)>0)
	  {
	    p2= p;
	    decode= encode=0;
	  }
	if(p2 && strcmp(p->name, p2->name)==0)
	  {
	    if(p->decode) decode=1;
	    if(p->encode) encode=1;
	  }
      }

    if(p2==NULL)
      break;
    
    last_name= p2->name;
 
    if(p2->type==CODEC_TYPE_VIDEO)
      {
	sciprint(
	       "\t%s%s   %s\n", 
	       decode ? "D":" ", 
	       encode ? "E":" ", 
	       p2->name);
      }
  }


  return 0;
}
