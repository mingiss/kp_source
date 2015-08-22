// ---------------------------
// unlock.cpp 
// 8cd atmintuko perregistravimas i CD-ROM
// veikia priklausomai nuo pavadinimo
//    unlock.exe  
//    restore.exe
//    restoreall.exe
//
   
// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <richedit.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpcapp.h"
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "unlock"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
bool bServiceFl=False;   


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
static unsigned char exe_fname[KP_MAX_FNAME_LEN+1];
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];

// ------------------------------- 
   if(SUCCEEDED(retc)) retc=KpInitWindows(hInstance);
   
// ------------------------------- 
   if(SUCCEEDED(retc)) retc=GetAppName(exe_fname);
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, exe_fname);

   if(SUCCEEDED(retc)) retc = LockFlashStr(name);

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}
