#ifndef VDO_H
#define VDO_H


#ifdef __cplusplus
extern "C" {
#endif

#include <avcodec.h>
#include <avformat.h>
#include <stdio.h>
#include <stack-c.h>

#define TRUE 1
#define FALSE 0

  typedef int BOOL;

  /*video file information structure  */
  typedef struct VDOFINFO{
    char filename[FILENAME_MAX];
    int64_t file_size; //video file size, in byte
    int width; //image width
    int height; //image height
    char codec_name[16];
    char pixel_format[16];
    int bit_rate; //the average bitrate. in b/s
    int64_t duration; //in second
    int frame_number; //video frame number, reserved now
    char title [512];
    char author [512];
    char copyright [512];
    char comment [512];
    char log[512];// error message
  }VDOFInfo;


  BOOL Create3DIntMat(int nPos, int nRow, int nCol, int nCh, void* pData, int nType);
  //int vdofinfo(char * filename, VDOFInfo * finfo);
  void rgbimg2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight);
  void grayimg2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight);
  void img2mat(unsigned char* pSrc, unsigned char * pDst, int nWidth, int nHeight, int nCh);
  void mat2img(unsigned char * pMat, unsigned char *pImg, int nWidth, int nHeight, int nCh);
       

#ifdef __cplusplus
}
#endif
#endif
