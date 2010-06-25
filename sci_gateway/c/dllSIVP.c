/*
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
 */

#include <windows.h> 
/*--------------------------------------------------------------------------*/ 
#if _WIN64
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/cv210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/cvaux210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/cvhaartraining.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/cxcore210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/cxts210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/highgui210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/ml210.lib")
#else
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/cv210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/cvaux210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/cvhaartraining.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/cxcore210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/cxts210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/highgui210.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/ml210.lib")
#endif
/*--------------------------------------------------------------------------*/ 
int WINAPI DllMain (HINSTANCE hInstance , DWORD reason, PVOID pvReserved)
{
  switch (reason) 
    {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    }
  return 1;
}
/*--------------------------------------------------------------------------*/ 

