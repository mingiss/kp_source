// -------------------------------------------
// KpWinVer.cpp
//

#include "envir.h"

#include <stdio.h>
#include <string>
#include <windows.h>
#include <richedit.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpstap.h"


//---------------------------------------------
KpErrorProc_tag KpErrorProc(True, 43);
bool bServiceFl=False;
int iProdVerGlob=0;
const unsigned char lpszProdName[] = "kpwinver"; 


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


//---------------------------------------------
int main(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc = KpInitWindows(GetModuleHandle(NULL));

   printf("iWindowsVersion:        %d %s\n", iWindowsVersion, (iWindowsVersion<WinNumOfCurrentWinVersions)?lpszaWindowsVerNames[iWindowsVersion]:(const unsigned char *)"Unknown");        
   printf("iWindowsSP:             %d\n", iWindowsSP);             
   printf("Osvi.dwMajorVersion:    %ld\n", Osvi.dwMajorVersion);    
   printf("Osvi.dwMinorVersion:    %ld\n", Osvi.dwMinorVersion);    
   printf("Osvi.dwBuildNumber:     %ld\n", Osvi.dwBuildNumber);     
   printf("Osvi.dwPlatformId:      %ld\n", Osvi.dwPlatformId);      
   printf("Osvi.szCSDVersion:      [%s]\n", Osvi.szCSDVersion);
   printf("Osvi.wServicePackMajor: %d\n", Osvi.wServicePackMajor); 
   printf("Osvi.wServicePackMinor: %d\n", Osvi.wServicePackMinor); 
   printf("Osvi.wSuiteMask:        0x%0x\n", Osvi.wSuiteMask);        
   printf("Osvi.wProductType:      %d\n", Osvi.wProductType);      

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_MAIN(retc));
}

