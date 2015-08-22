// ---------------------------
// StartGrp.cpp
// tolesnis StartSel.exe vystymas
// grupin�s aplikacijos starteris/selektorius, prenumeratos grupinis registratorius
// paprastai registruoja ir pat� save, tod�l leid�iamas kaip KpStRegMode, tik nereikalauti admino,
//    nes prenumeruojami produktai diegiami � %ALLUSERSPROFILE% � darbo metu eiliniam useriui reikia
//    nusikraut, �diegt ir u�registruot leidinio komponentus, atnaujint ir i�sisaugot paleidimo meniu.
//

// -----------------------------------------
#define KPSTEDI_MODE 48 // OWNER_MODE | LOGIN_MODE logino �vedimui

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
#include "kpmsg.h"
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
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlg.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstedi.h"
#include "kpstart.h"
#include "lzdsh.h"
#include "lzdsho.h"


// ----------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#if Envir != MSWin32
#error Envir != MSWin32
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif
#if IBSH_SKIN != IBSH_SKIN_START_GRP // ShowBmp() langas � nestandartinis lokaliai apdorojamas
#error IBSH_SKIN != IBSH_SKIN_START_GRP
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "StartGrp";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;

// KpStartApp theApp;
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


// ----------------------------------
// LzdShOptDlg theOptDialog;
LzdShOptDlg *pOptDialog = NULL;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
HRESULT KpStApp::GetGrpLocalDir(unsigned char *lpszLocalDir)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszLocalDir != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetLocalPath(lpszLocalDir, KP_LocalDir);

   KP_ASSERT(strlen(lpszLocalDir) + strlen(STARTSEL_MNG_DIR) + 1 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcat(lpszLocalDir, STARTSEL_MNG_DIR);
      strcat(lpszLocalDir, "\\");
   }

return(retc);
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
HRESULT retc = S_OK;

try
{
   if(StackTop == NULL) StackTop = &nCmdShow;

// -------------------------------
KpStartApp *app_ptr = NULL; // (&theApp); //
   KP_NEW(app_ptr, KpStartApp);
   theKpStAppPtr = app_ptr; // static_cast<KpStApp *> (&theApp);
   KP_ASSERT(app_ptr != NULL, E_POINTER, null, True);
   if(SUCCEEDED(retc)) retc = app_ptr->GetOpenResult();

// -------------------------------
static unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

// -------------------------------
// nustatom einam�j� katalog�, i� InitCommonApp() i�mestas d�l TUX_XFS
static unsigned char full_path[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);
   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      KP_WARNING(KP_E_SYSTEM_ERROR, full_path);
      KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
   }

// -------------------------------
// ka�kod�l netinka KpStarterMode
// KpStRegMode irgi nelabai � CheckReg() bando forsuotai ie�kot terminuotos licencijos ir pusei minut�s pakabina WinXP be ineto
   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStEditMode); // KpStRegMode); // KpStarterMode); // ??

   if(SUCCEEDED(retc))
   {
      retc = app_ptr->LoadIniFile(app_ptr->m_lpszIniFName, True, False); // forsuojam i�orinio .ini failo skaitym� � ten i�saugotas logino slapta�odis
      if(FAILED(retc)) retc = app_ptr->LoadIni(); // .ini neradom (ar radom sugadint�) � inicializuojam atgal i� InternalIniData[]
   }

// PutLogMessage_("WinMain() %d %x %x", sizeof(&WinMain), &WinMain);

// ------------------------------- registruojam pat� starter�
// TODO: dar gal reikt� ir TestFlash(). Arba ir CheckReg() nereikia � free aplikacija
// bool lic_entered = False;
// if(SUCCEEDED(retc)) retc = app_ptr->CheckReg(hInstance, &lic_entered);

// ---------------------------------------------------------------
// sukuriam Gecko dialogo objektus, pana�u, kad vienkartiniai
   if(SUCCEEDED(retc)) retc = app_ptr->OpenShowHtml();

// ------------------------------------- kuriam parink�i� dialog�
   KP_NEWO(pOptDialog, LzdShOptDlg(app_ptr->m_pGrpKpPubDlg));

// ------------------------------- paleid�iam meniu parsiuntimo thread�
   KP_ASSERT(app_ptr->m_pGrpKpPubDlg != NULL, E_POINTER, null, True);
   KP_ASSERT(app_ptr->m_pGrpKpPubDlg->m_pKpFileSys != NULL, E_POINTER, null, True);
   if(SUCCEEDED(retc)) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore(); // bus loginimosi proced�ra; suspenduojam StartProcessGrpThread()

#if TRUE // #ifndef Debug
   app_ptr->m_bForceGrpCfg = True; // pirm� kart� krausim forsuotai � dabar paleidimo metu meniu nebeatnaujinam, kad WinXP nepakibt� pusei minut�s, kai n�ra ineto; visi atnaujinimai � tik fone 
   if(SUCCEEDED(retc)) retc = app_ptr->StartProcessGrpThread();
#endif

// ------------------------------- loginam�s
   if(SUCCEEDED(retc)) app_ptr->m_bGrpRefreshFlg = False;

   if(SUCCEEDED(retc)) retc = app_ptr->m_pGrpKpPubDlg->ShowDialog();

   if(SUCCEEDED(retc)) do
   {
      retc = S_OK; // valom KP_S_LOGOFF ir KP_E_ACCESS_DENIED

unsigned char prev_user[KP_MAX_FILE_LIN_WDT + 1];
unsigned char pwd[TV_TAG_LEN + 1];
      if(SUCCEEDED(retc)) retc = app_ptr->GetIniUserData(prev_user);
      if(SUCCEEDED(retc)) retc = app_ptr->GetIniUserPwd(pwd);
      
      if(SUCCEEDED(retc))
      {
// jei slapta�odis i�valytas, reikia logintis      
         if(pwd[0] == Nul)
         {
int ii = 0;
            while((pwd[0] == Nul) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

PutLogMessage_("WinMain() 01: m_bClose: %d  m_bLogoff: %d  retc: %x  KP_E_CANCEL: %x  KP_S_LOGOFF: %x", app_ptr->m_pGrpKpPubDlg->m_bClose, app_ptr->m_pGrpKpPubDlg->m_bLogoff, retc, KP_E_CANCEL, KP_S_LOGOFF);       
               if(SUCCEEDED(retc)) retc = app_ptr->Login();
PutLogMessage_("WinMain() 02: m_bClose: %d  m_bLogoff: %d  retc: %x  KP_E_CANCEL: %x  KP_S_LOGOFF: %x", app_ptr->m_pGrpKpPubDlg->m_bClose, app_ptr->m_pGrpKpPubDlg->m_bLogoff, retc, KP_E_CANCEL, KP_S_LOGOFF);       

               if(SUCCEEDED(retc)) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();

               if(SUCCEEDED(retc)) retc = app_ptr->GetIniUserPwd(pwd);
               if((pwd[0] == Nul) && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_BAD_PWD, IDI_ERROR, KP_MB_TESTI);

               if((retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
               {
HRESULT retc0 = S_OK;
unsigned char new_user[KP_MAX_FILE_LIN_WDT + 1];
                  if(SUCCEEDED(retc0)) retc0 = app_ptr->GetIniUserData(new_user);
int prod_ver = 0;
                  if(SUCCEEDED(retc0)) retc0 = app_ptr->GetIniProdVer(&prod_ver);
unsigned char prev_pwd_enc[2 * TV_TAG_LEN + KP_MAX_FNAME_LEN + 1];
                  if(SUCCEEDED(retc0)) retc0 = app_ptr->GetProdVerRegVariableStr(prev_pwd_enc, prod_ver, KPST_PRODVER_REG_KEY_LastUser);
unsigned char new_pwd_enc[2 * TV_TAG_LEN + 1];
                  if(SUCCEEDED(retc0)) retc0 = app_ptr->GetIniUserPwdEnc(KPST_GRP_PWD_CRYPT_CODE, new_pwd_enc);

                  if(SUCCEEDED(retc0))
                  {
                     if(strcmp(new_user, prev_user) == 0)
                     {
                        if(strcmp(new_pwd_enc, prev_pwd_enc) != 0)
                        {
                           KpMsgOut(KPST_MSG_BAD_PWD, IDI_ERROR, KP_MB_TESTI);
                           retc = S_OK;
                           pwd[0] = Nul;
                           if(SUCCEEDED(retc0)) retc0 = app_ptr->SetIniUserPwd(pwd);
                           if(SUCCEEDED(retc0)) retc0 = app_ptr->SaveIni();
                        }
                     }
                     else
                     {
                        if(ii++ < 1)
                        {
                           PutMsgFirewall(KPST_MSG_CHECK_CONN);
                           retc = S_OK;
                        }
                        else
                        {
                           KpMsgOut(KP_MSG_NO_CONN, IDI_ERROR, KP_MB_TESTI);
                           retc = KP_E_CANCEL; // jeigu paliksim ry�io klaid�, u�kraus paskutinio userio meniu
                        }

                        pwd[0] = Nul;
                        if(SUCCEEDED(retc0)) retc0 = app_ptr->SetIniUserData(prev_user);
                        if(SUCCEEDED(retc0)) retc0 = app_ptr->SetIniUserPwd(pwd);
                        if(SUCCEEDED(retc0)) retc0 = app_ptr->SaveIni();
                     }
                  }
               }

            } // while((pwd[0] == Nul) && SUCCEEDED(retc))

// ------------------------------- atnaujinam cfg � kreipiam�s � prodreg server�, kraunam, diegiam, registruojam komponentus
// #if FALSE // meniu nusikrauti reikia ne �ia, o �emiau, kiekvien� kart� paleid�iant, kad nusiresetint� galimi parsi�sto meniu l��imai
#if TRUE // negerai � jei WinXP ir n�ra ineto � pakibs pusei minut�s, nusikraunam tik �ia, i�kart po logino 
// pirm� kart� po logino meniu u�kraunam pagrindiniam threade
            if(SUCCEEDED(retc))
            {
               retc = app_ptr->ProcessGrp(True);
               if(retc == KP_E_CANCEL) retc = S_OK;
            }
#endif
         } // if((pwd[0] == Nul) && SUCCEEDED(retc))
#if FALSE // meniu nusikrauti reikia kiekvien� kart� paleid�iant, kad nusiresetint� galimi parsi�sto meniu l��imai
         else
         {
// u�logintam useriui kol kas pakraunam offlinin� meniu
            if(SUCCEEDED(retc)) retc = app_ptr->LoadGrpCfg(); // skaitom fail� StartGrp.cfg � m_lpszGrpCfgBuf[]
            if(SUCCEEDED(retc)) retc = app_ptr->ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode
         }
#endif
      }

// pirm� kart� po paleidimo nusikraunam meniu forsuotai, kad nusiresetint� galimi parsi�sto meniu l��imai
// negerai � jei WinXP ir n�ra ineto � pakibs pusei minut�s
// TODO: parsi�sto meniu l��imus per j�g� resetint parsiun�iant nauj� meniu kur nors kitur � gal pajutus, kad meniu blogas; patyrin�t, kokie gali b�t l��imai
#if FALSE
      if(SUCCEEDED(retc) || (retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
      {
         retc = app_ptr->ProcessGrp(True);
         if(retc == KP_E_CANCEL) retc = S_OK;
      }
#else
      if(SUCCEEDED(retc)) retc = app_ptr->LoadGrpCfg(); // skaitom fail� StartGrp.cfg � m_lpszGrpCfgBuf[]
      if(SUCCEEDED(retc)) retc = app_ptr->ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode
#endif

// ------------------------------- i� cfg generuojam meniu
      if(SUCCEEDED(retc)) retc = app_ptr->GenStartMenu(True);

// -------------------------------
bool skip_menu = False;
      if(
         (retc == KP_E_ACCESS_DENIED) || // (retc == KP_E_REFUSED) || // registracija atmesta i� serverio � meniu praleid�iam ir gr��tam atgal � login�
         (retc == KP_E_CANCEL) || // KP_E_CANCEL i� Login() � dabar einam lauk; reik�t� ka�kaip pereit � offline, nesiregistruot ir nedownloadint
         (retc == KP_S_LOGOFF)
        )
         skip_menu = True;

      if(app_ptr != NULL) if(app_ptr->m_pGrpKpPubDlg != NULL)
         if(app_ptr->m_pGrpKpPubDlg->m_bLogoff) skip_menu = True;

#if FALSE // nulinio failo nebegeneruojam
      if(FAILED(retc) && (!skip_menu))
      {
// failo pakraut nepavyko (pvz., failas nesiparsina) � generuojam nulin�
         retc = S_OK;
         if(SUCCEEDED(retc)) retc = app_ptr->InitGrpCfg();
         if(SUCCEEDED(retc)) retc = app_ptr->SaveGrpCfg();
         if(SUCCEEDED(retc)) retc = app_ptr->ParseGrpCfgBuf(); // m_lpszGrpCfgBuf[] --> m_pGrpCfgNode
         if(SUCCEEDED(retc)) retc = app_ptr->GenStartMenu(True);
      }
#endif

// ------------------------------- vykdom meniu
      if(!skip_menu)
      {
// pakartojam �ia, nes atidarant lang� paleidimo meniu konfig�racinis failas dar nesuparsintas
         if(SUCCEEDED(retc)) if(app_ptr->m_pGrpKpPubDlg != NULL) retc = app_ptr->m_pGrpKpPubDlg->CreateBackground();

         if(app_ptr != NULL) if(app_ptr->m_pGrpKpPubDlg != NULL) if(app_ptr->m_pGrpKpPubDlg->m_pKpFileSys != NULL) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();
//       if(SUCCEEDED(retc)) app_ptr->m_bGrpRefreshFlg = True;
         if(SUCCEEDED(retc)) retc = app_ptr->SwitchGrpMenuRefreshing(True);

         if(SUCCEEDED(retc)) retc = app_ptr->ProcStartMenu();

//       if(SUCCEEDED(retc)) app_ptr->m_bGrpRefreshFlg = False;
      /* if(SUCCEEDED(retc)) retc = */ app_ptr->SwitchGrpMenuRefreshing(False);
         if(app_ptr != NULL) if(app_ptr->m_pGrpKpPubDlg != NULL) if(app_ptr->m_pGrpKpPubDlg->m_pKpFileSys != NULL) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->BlockSemaphore();
      }

      if(app_ptr != NULL) if(app_ptr->m_pGrpKpPubDlg != NULL)
      {
// PutLogMessage_("WinMain() retc %x  KP_S_LOGOFF %x  m_bLogoff %d  m_bClose %d", retc, KP_S_LOGOFF, app_ptr->m_pGrpKpPubDlg->m_bLogoff, app_ptr->m_pGrpKpPubDlg->m_bClose);
         if(((retc == KP_S_LOGOFF) || app_ptr->m_pGrpKpPubDlg->m_bLogoff) && app_ptr->m_pGrpKpPubDlg->m_bClose)
            retc = S_OK; // valom KP_S_LOGOF, eisim lauk, buvo komanda Logoff, ne Login
      }

   } while((retc == KP_S_LOGOFF) || (retc == KP_E_ACCESS_DENIED)); // jei logoff ar netiko slapta�odis � gr��tam nuo prad�i�

   if(retc == KP_E_CANCEL) retc = S_OK;

// KpMsgOutF("WinMain() 1 %x", retc);

   if(SUCCEEDED(retc)) retc = app_ptr->m_pGrpKpPubDlg->HideDialog();
   if(SUCCEEDED(retc)) retc = app_ptr->m_pGrpKpPubDlg->CloseWindow(); // �ia m_hDialogWindow jau NULL

// -----------------
   if(app_ptr != NULL) if(app_ptr->m_pGrpKpPubDlg != NULL) if(app_ptr->m_pGrpKpPubDlg->m_pKpFileSys != NULL) app_ptr->m_pGrpKpPubDlg->m_pKpFileSys->ReleaseSemaphore();

// -----------------
// if(SUCCEEDED(retc))
   if(app_ptr != NULL)
   {
HRESULT retc0 = app_ptr->StopProcessGrpThread();
      if(SUCCEEDED(retc)) retc = retc0;
   }

// palaukiam, kol pasibaigs galimai buvus suspenduota ProcessGrpThreadProc()
// TODO: !!! �iaip reik�t� tiesiog nu�udyti ProcessGrpThreadProc()
// if(SUCCEEDED(retc)) KpSleep(1000);

// ---------------------------------------------------------------
// naikinam Gecko dialogo objektus, pana�u, kad vienkartiniai
// l��ta lyg ir �ia
// if(SUCCEEDED(retc)) retc = app_ptr->CloseShowHtml();

// ------------------------------- naikinam parink�i� dialog�
   KP_DELETE(pOptDialog);

// -------------------------------
// if(SUCCEEDED(retc))
   if(app_ptr != NULL)
   {
HRESULT retc0 = app_ptr->CloseStApp(retc, KP_My_Documents);
      if(SUCCEEDED(retc)) retc = retc0;
   }

// theKpStAppPtr = NULL;
// KP_DELETE(app_ptr); // l��ta?

}
catch(const char *msg) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)msg)
catch(int sig){ unsigned char out_str[100]; sprintf((char *)out_str, "sig: %d", sig); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::bad_alloc& ba){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::bad_alloc&: %s", ba.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception& ex){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::exception&: %s", ex.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::exception*")
// catch(const Exception& ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception&")
// catch(const Exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception*")
catch(const EXCEPTION_DEBUG_INFO& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO&")
catch(const EXCEPTION_DEBUG_INFO *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO*")
catch(const EXCEPTION_RECORD& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD&")
catch(const EXCEPTION_RECORD *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD*")
catch(...) KP_ERROR(KP_E_SYSTEM_ERROR, null);

return(RET_CODE_WIN(retc));
}
