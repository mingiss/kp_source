// ---------------------------
// iBsh.cpp
// el. knygø perþiûros programa
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#ifdef IBSH_RES_MODE_MSHTML
#if CompilerGr==Mingw
#include "HTMLWindow.h"
#endif
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "tvmain.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "xmlsty.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBshr.h"
#include "iBsht.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "iBsh";
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;
int iUpdNumGlob = -1;


int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs + IBSH_RC_NumOfRcIxs;

KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 + IBSH_RC_NumOfRcIxs_1 + 1]=
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

#if FALSE // #ifdef IBSHT_ENCODED
   WriteRtfFromImg,
   GetHwFromImg,
#endif

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -------------------------
#if FALSE // dubliuojasi su kpstapg.cpp
DWORD WINAPI CheckUpdateThreadProc(LPVOID /* lpParameter */)
{
HRESULT retc=S_OK;

   if((theKpStAppPtr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_UNEXPECTED, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->CheckUpdate(null, False, False);

return(RET_CODE_MAIN(retc));
}
#endif


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
DWORD retw = True;
HCURSOR cur_sav=NULL;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
DWORD chk_thread;
HANDLE h_chk_thread;
int num_of_lics=0;
static unsigned char full_path[KP_MAX_FNAME_LEN + 1];

iBshFileSys *file_sys = NULL;
KpPubDlg *pub_dlg = NULL;

//-----------------
   KP_NEWO(theKpStAppPtr, iBshApp());

   if(SUCCEEDED(retc))
   {
      cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

// -----------------------------------
#ifdef Debug
   if(SUCCEEDED(retc)) retc = KpTraceWindow.GetOpenResult();
#endif

#ifdef IBSH_RES_MODE_MSHTML
#if Compiler != Watcom
   HTMLWindow::InitOle();
#endif
#endif

   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
// ----- iðorinis iBshpn.ini dël lic. serverio adreso - pavojinga, galima nulauþt, pakiðant kità .ini
   if(SUCCEEDED(retc)) if(strstr(ini_fname, "iBshpn") || strstr(ini_fname, "iBshdn")) strcpy(ini_fname, "iBsh.ini");

// static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
// GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf);
// KpMsgOutF("WinMain() 1 [%s]", dir_buf);

// nustatom einamàjá katalogà, ið InitCommonApp() iðmestas dël TUX_XFS
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);
   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, full_path, False, __FILE__, __LINE__, 0L);
   }

// -------------------------------------
// if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitCommonApp(hInstance, lpCmdLine);

// ------------------------------ paleidziam automatinio lic. tikrinimo threadà
#ifndef TEST_NO_THREADS
   if(SUCCEEDED(retc))
   {
      h_chk_thread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         CheckUpdateThreadProc, // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         (LPDWORD)&chk_thread   // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      KP_ASSERT(h_chk_thread, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }
#endif

// --------------------
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode, True);

// -------------------------------------
   KP_NEWO(file_sys, iBshFileSys());

// --------------------
   if(SUCCEEDED(retc)) retc = file_sys->OpenFiles(null, XM_VERS_HTML401_TRANS, CreateNew8File, CreateNewBFile);

// --------------------
   KP_NEWO(pub_dlg, iBshDlg(file_sys));

// -------------------------------------
// if(SUCCEEDED(retc)) retc = pub_dlg->InitGecko();

// atkelta ið iBshDialogProc() WM_CREATE
// if(SUCCEEDED(retc)) if(file_sys->m_bGeckoShowFl) retc = pub_dlg->CreateResCtrl(IBSH_RES_X, IBSH_RES_Y, IBSH_RES_DX_DYN, IBSH_RES_DY_DYN, pDialogPtr->m_hScreen);

// --------------------
   if(SUCCEEDED(retc)) if(file_sys->m_bGeckoShowFl) retc = pub_dlg->OpenWindow(hKpInstance);

// --------------------
   if(SUCCEEDED(retc)) retc = file_sys->SearchForEntry(pub_dlg, null);

// --------------------
   if(cur_sav != NULL) SetCursor(cur_sav);
   cur_sav = NULL;

   if(SUCCEEDED(retc)) if(file_sys->m_bGeckoShowFl) retc = pub_dlg->ShowDialog();

   if(SUCCEEDED(retc)) if(file_sys->m_bGeckoShowFl) retc = pub_dlg->DoEdit();

//-----------------
   cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
   KP_ASSERT0(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), True);

#ifdef IBSH_RES_MODE_MSHTML
#if Compiler != Watcom
   HTMLWindow::CloseOle();
#endif
#endif

   if(theKpStAppPtr)
   {
      retc0 = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);
      if(SUCCEEDED(retc)) retc=retc0;
   }

   if(cur_sav != NULL) SetCursor(cur_sav);
   cur_sav = NULL;

// if(SUCCEEDED(retc)) pub_dlg->FinitGecko();

   KP_DELETE(pub_dlg);
   KpSleep(200); // kad uþsilikæ pub_dlg praneðimø procedûros nerastø tuðèio piBshFile

// KP_DELETE(file_sys); // iðtrina KP_DELETE(pub_dlg);  

   if(FAILED(retc)) retw = RET_CODE_WIN(retc);

return(retw);
}
