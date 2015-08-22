// ---------------------------
// kpstisvr.cpp
// lokalus IP komandø apdorojimo serveriukas
//

// -----------------------------------------
#define KPSTEDI_MODE 6 // (USER_MODE | STARTER_MODE)

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
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
#include "kpstmsg.h"
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
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstedi.h"
#include "kpstart.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstisvr"; // "lzdsh"; //
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;

KpStartApp theApp;
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
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
KpStartApp *app_ptr = NULL;
static unsigned char full_path[KP_MAX_FNAME_LEN + 1];
MSG msg;
int retp;
bool endfl = False;

   app_ptr = (&theApp);
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);
   KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);
   if(SUCCEEDED(retc)) retc = app_ptr->GetOpenResult();

PutLogMessage_("------------ WinMain() 1 %x", retc);
// -------------------------------
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStIpSvrMode);

PutLogMessage_("------------ WinMain() 2 %x", retc);
// KpErrorProc.OutputErrorMessage(retc, "Kpstisvr initiated", False, __FILE__, __LINE__, (long)hKpInstance);

// nustatom einamàjá katalogà, ið InitCommonApp() iðmestas dël TUX_XFS
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);

// pirmas parametras – darbinio katalogo vardas. kpstisvr.bin paleidþiamas ið temp katalogo, o visa aplinka pasilikus atmintuke
   if(SUCCEEDED(retc)) if(app_ptr->m_plCmdLineArgs) strcpy(full_path, (const unsigned char *)(app_ptr->m_plCmdLineArgs->GetValue()));

   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, full_path, False, __FILE__, __LINE__, 0L);
   }

PutLogMessage_("----------------- WinMain() 3");

// ---------------------- main message loop
   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp = LOWORD(msg.wParam);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
// atëjo IP POST praneðimas "CD=" – vartotojo aplikacija kpstart.exe vis dar gyva – atnaujinam lockinimo nusiëmimo taimerá
      case KPST_WM_BLOCK_SES:
PutLogMessage_("WinMain() KPST_WM_BLOCK_SES");
         if(theKpStAppPtr->m_iSesCtrlTimer) KillTimer(HWND_DESKTOP, theKpStAppPtr->m_iSesCtrlTimer);
         theKpStAppPtr->m_iSesCtrlTimer = SetTimer(HWND_DESKTOP, KPST_SES_CTRL_TIMER, KPST_SES_RELEASE_TIMEOUT, NULL);
         KP_ASSERT(theKpStAppPtr->m_iSesCtrlTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
         break;

      case WM_TIMER:
// kpstisvr.exe – kliento kpstart.exe numirë, nuresetinam sesijos blokavimà
         if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iSesCtrlTimer)
         {
PutLogMessage_("WinMain() WM_TIMER %d %x", theKpStAppPtr->m_bCheckUpdPending, retc);
            KP_WARNING(KP_E_TIMEOUT, "Klientas neatsiliepia");
            theKpStAppPtr->m_bInstanceLocked = False;

            if(!theKpStAppPtr->m_bCheckUpdPending) endfl = True; // einam lauk; Vistos laikais kaþko èia likdavom laukt naujo "CD=", dabar gal jau nebereikia – juk "RD=" irgi sustabdo kpstisvr.exe
         }
         break;

    case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
PutLogMessage_("------------ WinMain() WM_QUIT %x", retc);
         }
         endfl = True;
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDCANCEL:
            endfl = True;
            retc = KP_E_CANCEL;
PutLogMessage_("------------ WinMain() IDCANCEL %x", retc);
            break;
         }
         break;

      } // if(SUCCEEDED(retc)) switch(msg.message)


// --------------------------------
//    if((exit_code==STILL_ACTIVE) && SUCCEEDED(retc)) KpSleep(KPST_PROC_CMD_TIMEOUT, HWND_DESKTOP);

   } while((!endfl) && SUCCEEDED(retc));

PutLogMessage_("--------------- WinMain() out %x", retc);

// ---------------------------------
   /* if(SUCCEEDED(retc)) */ retc0 = app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0;

// KpErrorProc.OutputErrorMessage(retc, "Kpstisvr closed", False, __FILE__, __LINE__, (long)hKpInstance);

return(RET_CODE_WIN(retc));
}
