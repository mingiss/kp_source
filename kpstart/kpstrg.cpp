// ---------------------------
// kpstrg.cpp
// aplikacijos lic. kodo registravimas
// includinamas gabalas, naudojamas kpstreg.cpp ir kpsttrg.cpp
//
// jei apibrezta STAND_ALONE - atskiras .exe (registr.exe)
// jei ne - ilinkuojamas KpsTestReg() (kpsttrg.cpp)
//
// pirmas parametras –  lic. kodas, kurá reikia tyliai uþregistruot, tik jei KpStRegMode
//    jei KpStarterMode – tada paleidimo katalogas, kurá reikia nusistatyti aktyviu
//

// -----------------------------------------
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
#include "xmlg.h"
#include "kpstap.h"
#include "kpstart.h"

#ifndef STAND_ALONE
#include "kpsttrg.h"
#endif

// ----------------------------------
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

// #define DebugStop

// -----------------------------------------
int iProdVerGlob=0;
int iUpdNumGlob = -1;

#ifdef KPSTTRG_DLL
// extern "C"
__declspec(dllexport)
#endif
KpErrorProcClass KpErrorProc(True, 71);

bool bServiceFl=False;

KpStartApp theApp;
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[]={"c:\\arkim\\rezultatai\\kpstart.log"};
#endif

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
#ifdef STAND_ALONE
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#else
#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
HRESULT KpsTestReg(void)
#endif
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
KpStartApp *app_ptr = NULL;
bool lic_entered = False;
bool bound=False;
static int lic_id = 0;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

#ifdef STAND_ALONE
   if(StackTop == NULL) StackTop = &nCmdShow;
#else
   if(StackTop == NULL) StackTop = &retc;
#endif

#if FALSE
if(!SetCurrentDirectory("\\")) KpMsgOutF_0("KpsTestReg(): SetCurrentDirectory() nepavyko");
char dir_buf[KP_MAX_FNAME_LEN + 1];
GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf);
KpMsgOutF_1("KpsTestReg() 1: %s", dir_buf);
#endif

// KpMsgOutF_0("KpsTestReg() 1");

#ifndef STAND_ALONE
HINSTANCE hInstance = GetModuleHandle(NULL);
#endif

// KpMsgOutF_0("KpsTestReg() 2");

   theKpStAppPtr = static_cast<KpStApp *> (&theApp);
   app_ptr=(&theApp);

// KpMsgOutF_0("KpsTestReg() 3");

#ifdef Debug
#ifdef DebugStop
KpMsgOut("0. WinMain", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// -------------------------------
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

// KpMsgOutF_0("KpsTestReg() 4");

#ifdef Debug
#ifdef DebugStop
KpMsgOut("1. InitStApp", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname,
#ifdef STAND_ALONE
      lpCmdLine,
      KpStRegMode,
#else
      "",
      KpStarterMode, // TUX IPA kaþko neveikia registravimasis on-the-fly - iðkvieèiam kaip paprastà paleidëjà
#endif
      False, &lic_entered);

   if(SUCCEEDED(retc)) GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)app_ptr->m_lpszProjDir);

// bus sukurti ið naujo WatchExecProc() threade
// nepadeda – taimerio praneðimai vis tiek eina á pagrindiná threadà
// if(app_ptr->m_iLicManagTimer) KillTimer(HWND_DESKTOP, app_ptr->m_iLicManagTimer);
// app_ptr->m_iLicManagTimer = 0;
//
// if(app_ptr->m_iProcCmdTimer) KillTimer(HWND_DESKTOP, app_ptr->m_iProcCmdTimer);
// app_ptr->m_iProcCmdTimer = 0;
//
// if(app_ptr->m_iFlashCheckTimer) KillTimer(HWND_DESKTOP, app_ptr->m_iFlashCheckTimer);
// app_ptr->m_iFlashCheckTimer = 0;

// ---------------------------------
// stabdom ip komandø procesinimà, kad tux_ipa.bin galëtø dar kartà já pasileisti
// nepadeda – socketas Accept()-e
// paprasèiausiai antrà k. inicializuojant neiðvedam klaidos praneðimo ir soketo su threadu neatidarom
// if(SUCCEEDED(retc)) if(app_ptr->m_lListThreadId)
// {
//    PostThreadMessage(app_ptr->m_lListThreadId, WM_CLOSE, 0L, 0L);
//    PostThreadMessage(app_ptr->m_lListThreadId, WM_QUIT, IDCANCEL, 0L);
//    app_ptr->m_lListThreadId = 0L;
// }

// KpMsgOutF_0("KpsTestReg() 5");

// ---------------------------------
   if(SUCCEEDED(retc)) retc = theApp.GetIniProdNameDec(prod_name);
   if(SUCCEEDED(retc)) retc = theApp.GetIniBound(&bound);

// KpMsgOutF_0("KpsTestReg() 6");

// reikia, kad papildymu pririsimas prie lic. kodo cia neveiktu
// istrinam kphp11 lauka m_iIni.m_iIniLicID
// lokalus theKpStAppPtr->m_Ini.m_iIniLicID lieka nepakites - kad atsirastu defaultiniai laukai
   lic_id = KpstRand(0);
   if(SUCCEEDED(retc)) retc=theApp.SetIniElement(&lic_id, (unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf, sizeof(int));

// KpMsgOutF_0("KpsTestReg() 7");

   if(SUCCEEDED(retc)) retc = app_ptr->CheckReg(hInstance, lic_entered?NULL:&lic_entered);

// -------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4. CloseStApp", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#if FALSE // #ifndef STAND_ALONE
HANDLE hh;
   if(SUCCEEDED(retc))
   {
      hh = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         WatchExecProc,      // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         NULL // &m_lListThreadId     // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      if(hh==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

// KpMsgOutF_0("KpsTestReg() 8");
// PutLogMessage_("WatchExecProc() started theKpStAppPtr: %lx", theKpStAppPtr);

#ifdef STAND_ALONE  // reikia, kad kphp11 threadas liktø gyvas, CloseStApp() KpStRegMode'je faktiðkai nieko daugiau ir nedaro
   /* if(SUCCEEDED(retc)) */ retc0=app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;
#endif

// KpMsgOutF_0("KpsTestReg() 9");

#ifndef STAND_ALONE
#ifndef LAUNCHER_REGMODE
   if(lic_entered)
#endif
#endif
      if(bound && SUCCEEDED(retc))
      {
unsigned char *out_msg = null;
         KP_NEWA(out_msg, unsigned char, strlen(KPST_MSG_REG_SUCC) + strlen(KPST_MSG_ALLREADY_REG) + strlen(prod_name) + 100);
         if(SUCCEEDED(retc))
         {
            sprintf((char *)out_msg, (const char *)(lic_entered?KPST_MSG_REG_SUCC:KPST_MSG_ALLREADY_REG), prod_name);
            if(app_ptr->m_plCmdLineArgs && (app_ptr->m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
            {
               /* retc = */ SpcEolToSpc(out_msg);
               KP_WARNING(retc, out_msg);
            }
            else
               KpMsgOutF(out_msg);
         }

         KP_DELETEA(out_msg);
      }

// KpMsgOutF_0("KpsTestReg() 10");

#if FALSE
GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf);
KpMsgOutF_1("KpsTestReg() 7: %s", dir_buf);
#endif

// KpMsgOutF_0("KpsTestReg() 11");

return(/* RET_CODE_WIN */(retc));
}


// su threadu neiðeina – taimerio praneðimai neateina, paprasèiau su KpStaWindowProc()
#if FALSE // #ifndef STAND_ALONE
// ------------------- command socket listening idle loop
DWORD WINAPI WatchExecProc(LPVOID /* lpParameter */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];

   KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);

// turëtø u_tekt ankstesnio iðkvietimo ið KpsTestReg()
// if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
// if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(hKpInstance, ini_fname, "", KpStarterMode);

// nepadeda – taimerio praneðimai vis tiek eina á pagrindiná threadà
// if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetTimers();

// KpMsgOutF_0("WatchExecProc(): entering WatchExec()");
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->WatchExec();

   /* if(SUCCEEDED(retc)) */ retc0 = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE_MAIN(retc));
}
#endif // #ifndef STAND_ALONE
