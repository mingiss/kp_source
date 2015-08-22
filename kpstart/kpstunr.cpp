// ---------------------------
// kpstun.cpp
// licenzijos panaikinimas
// includinamas gabalas, naudojamas kpstun.cpp ir kpsttrg.cpp
//
// jei apibrezta STAND_ALONE - atskiras .exe (unreg.exe)
// jei ne - ilinkuojamas KpsUnReg() (kpsttrg.cpp)
//

// -----------------------------------------
#ifdef STAND_ALONE
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "kpstmsg.h"


// -----------------------------------------
#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif
#if IBSH_SKIN != IBSH_SKIN_SPLASH // ShowBmp() langas – nestandartinis lokaliai apdorojamas
#error IBSH_SKIN != IBSH_SKIN_SPLASH
#endif

// -----------------------------------------
int iProdVerGlob=0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
KpStApp theApp;
bool bServiceFl=False;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 + 1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,
   ResetRestDays_RC,

   RegSert_RC,
   UnRegSert_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#else // #ifdef STAND_ALONE
#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
HRESULT KpsUnReg(void)
#endif
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
HANDLE cmd_proc=NULL;
bool silent = False;
const unsigned char *par_ptr = null;

#ifdef STAND_ALONE
   if(StackTop == NULL) StackTop = &nCmdShow;
#else
   if(StackTop == NULL) StackTop = &retc;
#endif

#ifndef STAND_ALONE
HINSTANCE hInstance = GetModuleHandle(NULL);
#endif

#ifdef STAND_ALONE // Audrius pirma iškviečia registravimo patikrinimą, tada KpStApp ir inicializuojama
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);

   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

   if(SUCCEEDED(retc)) retc = theApp.InitStApp(hInstance, ini_fname,
#ifdef STAND_ALONE
      lpCmdLine,
      KpStRegMode);
#else
      "",
      KpStarterMode); // TUX IPA kažko neveikia registravimasis on-the-fly - iškviečiam kaip paprastą paleidėją
#endif
#endif

#ifdef STAND_ALONE
   if((theApp.m_plCmdLineArgs != NULL) && (theApp.m_iKpStMode == KpStRegMode))
   {
      par_ptr = (const unsigned char *)(theApp.m_plCmdLineArgs->GetValue());
      KP_ASSERT(par_ptr != null, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc)) silent = (strstr(par_ptr, "/SILENT") != null);
   }
#endif

   if (SUCCEEDED(retc)) if (theApp.m_lpszProjDir[0])
      SetCurrentDirectory((const char *)theApp.m_lpszProjDir);

   if(SUCCEEDED(retc))
   {
      theApp.UnRegSert();
      retc = theApp.RemoveReg(retc, hInstance);
   }

#ifdef STAND_ALONE
   if((theApp.m_plCmdLineArgs != NULL) && (!silent) && SUCCEEDED(retc))
   {
      retc = StartProcess((const unsigned char *)theApp.m_plCmdLineArgs->GetValue(), null, NULL, &cmd_proc, SW_SHOWNORMAL); // SW_SHOWDEFAULT);
      if(SUCCEEDED(retc)) retc = WaitForProcessEnd(cmd_proc, NULL);
   }
#endif

#ifdef STAND_ALONE  // reikia, kad kphp11 threadas liktų gyvas, CloseStApp() KpStRegMode'je faktiškai nieko daugiau ir nedaro
   /* if(SUCCEEDED(retc)) */ retc0 = theApp.CloseStApp(retc, KP_My_Documents);
   if(SUCCEEDED(retc)) retc = retc0;
#endif

return(/* RET_CODE_WIN */(retc));
}
