// ---------------------------
// kpstart.cpp, atnaujintas kpsptiw.cpp
// aplikacijos paleidimas
// tikrinimas, ar paleidziama is kompakto
// paleidziama naujam thread'e
//
// kpstart.exe kopijuojamas i:
//    start_tev.exe   - #ifdef KPST_TEV
//    start_arkim.exe - #ifdef KPST_ARKIM
//
// po to pervadinamas i start.exe arba xxx.exe priklausomai nuo projekto
// Registruojamu licenciju projektams ir kitiems su rezultatu surinkimu start.ini (xxx.ini) faile
//    nuimti "CID tiesiogiai". Tada registracijai reikes admino.
//
// atskiri projektai:
//    kpstart.exe
//    kpstartd.exe    - #ifdef Debug
//    kpstartl.exe    - #ifdef Debug DebugStop Logging
//    kpstartc.exe    - #ifdef AllwaysCid (visada iesko realaus kompiuterio ID, jautrioms apsaugai aplikacijoms)
//    kpstartlc.exe   - #ifdef AllwaysCid Debug DebugStop Logging
//
// pirmas parametras – paleidimo katalogas, jei nurodytas – reikia já nusistatyti aktyviu, tik kai KpStarterMode
//    jei KpStRegMode – tada lic. kodas, kurá reikia tyliai uþregistruot
//

// -----------------------------------------
#define KPSTEDI_MODE 6 // (USER_MODE | STARTER_MODE)
// #define TEST_DIAG_MSG // SendDiagMsg() debuginimui – generuoja klaidà

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <commctrl.h>
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
#include "xmlg.h"
#include "kpstap.h"
#include "kpstedi.h"
#include "kpstart.h"
#include "iBshn.h"


// -------------------------------------
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
const unsigned char lpszProdName[] = "kpstart";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;

KpStartApp theApp;
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
// unsigned char lpszLogFileName[]={"c:\\arkim\\rezultatai\\kpstart.log"};
unsigned char lpszLogFileName[]={"ipaf.log"};
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
HRESULT retc0 = S_OK;
static unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
KpStartApp *app_ptr = NULL;
static unsigned char full_path[KP_MAX_FNAME_LEN + 1];
int ii;

   if(StackTop == NULL) StackTop = &nCmdShow;

   app_ptr = (&theApp);
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);

   if(SUCCEEDED(retc)) retc = app_ptr->GetOpenResult();

#ifdef Debug
#ifdef DebugStop
KpMsgOut("0. WinMain", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// -------------------------------
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

#ifdef Debug
#ifdef DebugStop
KpMsgOut("1. InitStApp", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// char dir_buf[KP_MAX_FNAME_LEN + 1];
// GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf);
// KpMsgOutF_1("WinMain(): %s", dir_buf);

// nustatom einamàjá katalogà, ið InitCommonApp() iðmestas dël TUX_XFS 
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);

// pirmas parametras – darbinio katalogo vardas. kpstisvr.bin paleidþiamas ið temp katalogo, o visa aplinka pasilikus atmintuke
// netinka ðitaip – lpCmdLine dar neiðparsinta á m_plCmdLineArgs
// if(SUCCEEDED(retc)) if(app_ptr->m_plCmdLineArgs) strcpy(full_path, (const unsigned char *)(app_ptr->m_plCmdLineArgs->GetValue()));
   if(lpCmdLine && SUCCEEDED(retc)) if(lpCmdLine[0])
   {
      if(lpCmdLine[0] == '\"')
      {
         strncpy(full_path, lpCmdLine + 1, KP_MAX_FNAME_LEN);
         full_path[KP_MAX_FNAME_LEN] = Nul;
         ii = strlen(full_path); if(ii > 0) ii--;
         if(full_path[ii] == '\"') full_path[ii] = Nul;
      }
      else
      {
         strncpy(full_path, lpCmdLine, KP_MAX_FNAME_LEN);
         full_path[KP_MAX_FNAME_LEN] = Nul;
      }

// tikrinam, gal parametras - .tev failo vardas, tada SetCurrendDirectory() nereikia
      if(SUCCEEDED(retc))
      {
         strlwr(full_path);
         if(strstr(full_path, KPST_TEV_OBJ_FILE_TYPE))
            retc = GetAppPath(full_path, False); // nereikia - gràþinam paleidimo katalogà
      }
   }      

   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, full_path, False, __FILE__, __LINE__, 0L);
   }
   
PutLogMessage_("WinMain() 1");
   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode);

// PutLogMessage_("WinMain() 2 [%s] [%s]", full_path, app_ptr->m_lpszFlashDevName);
PutLogMessage_("WinMain() 2");

// dar pakartojam, o gal nereikia?
// KP_ASSERT(SetCurrentDirectory((char *)full_path), KP_E_SYSTEM_ERROR, GetLastError());

#ifdef TEST_DIAG_MSG
KP_ERROR(KP_E_SYSTEM_ERROR, null);
#endif

#ifdef Debug
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniCmdStr(cmd_str);
KP_TRACE(cmd_str);
#endif

#if FALSE
char str_buf[100];
int lic_id_hp11 = 0;
int lic_id_ini = 0;
EmuTv.GetHp11Variable(&lic_id_hp11, HP11_RC_INI_BUF+(unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf);
theKpStAppPtr->GetIniIniLicID(&lic_id_ini);
sprintf(str_buf, "lic_id_hp11(%o): %d  lic_id_ini: %d   %d", HP11_RC_INI_BUF+(unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf,
lic_id_hp11, // cMemBank[(HP11_RC_INI_BUF+(unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf)/2],
lic_id_ini, KpstRand(0));
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif

#ifdef Debug
#ifdef DebugStop
KpMsgOut("2. StartCmdProcess", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// ---------------------- start main process

// GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf);
// KpMsgOutF_1("WinMain(): %s", dir_buf);

   if(SUCCEEDED(retc)) retc = app_ptr->StartCmd();
PutLogMessage_("WinMain() 3");

#ifdef Debug
#ifdef DebugStop
KpMsgOut("3. StartComplete", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc = app_ptr->StartComplete();

// #ifdef Debug
// Sleep(3000);
// KpMsgOut("Jau", IDI_ASTERISK, KP_MB_TESTI);
// #endif

// -------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("3.9 WatchExec", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc = app_ptr->WatchExec();

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4. CloseStApp", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

/* if(SUCCEEDED(retc)) */ if(app_ptr != NULL){ retc0 = app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0; }

#ifdef Debug
#ifdef DebugStop
KpMsgOut("5. Exit", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

#ifdef Logging
KP_ERROR(KP_S_DIAG_MSG, null);
#endif

return(RET_CODE_WIN(retc));
}
