// ---------------------------
// kpstreg.cpp
// aplikacijos lic. kodo registravimas
//
// kpstreg.exe kopijuojamas i:
//    registr_tev.exe   - #ifdef KPST_TEV
//   (registr_arkim.exe - #ifdef KPST_ARKIM)
//
// po to pervadinamas i registr.exe
// start.ini faila nukopijuoti i registr.ini ir uzdeti "CID tiesiogiai"
//
// pirmas parametras –  lic. kodas, kurį reikia tyliai užregistruot, tik jei KpStRegMode
//    jei KpStarterMode – tada paleidimo katalogas, kurį reikia nusistatyti aktyviu
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
const unsigned char lpszProdName[] = "kpstreg";
int iProdVerGlob = 0;
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
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
HRESULT retc = S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
bool lic_entered = False;
bool bound = False;
static int lic_id = 0;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

   if(StackTop == NULL) StackTop = &nCmdShow;

#if FALSE
if(!SetCurrentDirectory("\\")) KpMsgOutF_0("KpsTestReg(): SetCurrentDirectory() nepavyko");
char dir_buf[KP_MAX_FNAME_LEN + 1];
GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf);
KpMsgOutF_1("KpsTestReg() 1: %s", dir_buf);
#endif

// KpMsgOutF_0("KpsTestReg() 1");

   theKpStAppPtr = static_cast<KpStApp *> (&theApp);

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

   if(SUCCEEDED(retc)) retc = theApp.InitStApp(hInstance, ini_fname, lpCmdLine,
        KpStRegMode, False, &lic_entered);

   if(SUCCEEDED(retc)) GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)theApp.m_lpszProjDir);

// bus sukurti iš naujo WatchExecProc() threade
// nepadeda – taimerio pranešimai vis tiek eina į pagrindinį threadą
// if(theApp.m_iLicManagTimer) KillTimer(HWND_DESKTOP, theApp.m_iLicManagTimer);
// theApp.m_iLicManagTimer = 0;
//
// if(theApp.m_iProcCmdTimer) KillTimer(HWND_DESKTOP, theApp.m_iProcCmdTimer);
// theApp.m_iProcCmdTimer = 0;
//
// if(theApp.m_iFlashCheckTimer) KillTimer(HWND_DESKTOP, theApp.m_iFlashCheckTimer);
// theApp.m_iFlashCheckTimer = 0;

// ---------------------------------
// stabdom ip komandų procesinimą, kad tux_ipa.bin galėtų dar kartą jį pasileisti
// nepadeda – socketas Accept()-e
// paprasčiausiai antrą k. inicializuojant neišvedam klaidos pranešimo ir soketo su threadu neatidarom
// if(SUCCEEDED(retc)) if(theApp.m_lListThreadId)
// {
//    PostThreadMessage(theApp.m_lListThreadId, WM_CLOSE, 0L, 0L);
//    PostThreadMessage(theApp.m_lListThreadId, WM_QUIT, IDCANCEL, 0L);
//    theApp.m_lListThreadId = 0L;
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

   if(SUCCEEDED(retc)) retc = theApp.CheckReg(theApp.m_hInstance, lic_entered?NULL:&lic_entered);

// -------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4. CloseStApp", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

      if(bound && SUCCEEDED(retc))
      {
unsigned char *out_msg = null;
         KP_NEWA(out_msg, unsigned char, strlen(KPST_MSG_REG_SUCC) + strlen(KPST_MSG_ALLREADY_REG) + strlen(prod_name) + 100);
         if(SUCCEEDED(retc))
         {
            sprintf((char *)out_msg, (const char *)(lic_entered?KPST_MSG_REG_SUCC:KPST_MSG_ALLREADY_REG), prod_name);
            if(theApp.m_plCmdLineArgs && (theApp.m_iKpStMode == KpStRegMode)) // command line kpstreg.exe režimas – pranešimų neišvedinėjam
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

   HRESULT retc0 = theApp.CloseStApp(retc, KP_My_Documents);
   if(SUCCEEDED(retc)) retc = retc0;

// KpMsgOutF_0("KpsTestReg() 9");

return(/* RET_CODE_WIN */(retc));
}
