/*
 * Copyright (C) 2010-2012 - DIGITEO - Allan CORNET
 */

#include <windows.h>
/*--------------------------------------------------------------------------*/
#if _WIN64
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_calib3d231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_calib3d231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_contrib231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_contrib231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_core231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_core231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_features2d231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_features2d231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_flann231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_flann231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_gpu231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_gpu231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_haartraining_engine.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_haartraining_engined.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_highgui231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_highgui231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_imgproc231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_imgproc231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_legacy231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_legacy231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_ml231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_ml231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_objdetect231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_objdetect231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_ts231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_ts231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_video231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x64/lib/opencv_video231d.lib")
#else
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_calib3d231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_calib3d231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_contrib231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_contrib231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_core231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_core231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_features2d231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_features2d231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_flann231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_flann231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_gpu231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_gpu231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_haartraining_engine.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_haartraining_engined.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_highgui231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_highgui231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_imgproc231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_imgproc231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_legacy231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_legacy231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_ml231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_ml231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_objdetect231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_objdetect231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_ts231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_ts231d.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_video231.lib")
#pragma comment(lib,"../../thirdparty/opencv/windows/x86/lib/opencv_video231d.lib")

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


