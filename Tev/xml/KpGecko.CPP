// ---------------------------------------
// KpGecko.cpp
// dialogas su tux_gecko langu
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr!=Mingw
#error CompilerGr!=Mingw
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "tvxml.h"
#include "tvmain.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11t.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "xmln.h"
#include "kpstap.h"
#include "iBsh.h"
#include "iBshl.h"
#include "lzdsh.h"
#include "lzdsho.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// --------------------------------------------------
KpGeckoDialog *KpGeckoDialogPtr = NULL; // reikia dël KpGeckoStreamFactory(), neiðeina padaryt nestatiðkai – reiðkia tik vienas KpGecko per aplikacijà


// --------------------------------------------------
KpGeckoDialog::KpGeckoDialog(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers, UC_Modes iEncMode,
      const unsigned char *lpszCaption,
      int iWndDXmin, int iWndDXmax, int iWndDYmin, int iWndDYmax,
      int iWndSoftBorderWdt, int iWndSoftCaptHgt, int iWndHardBorderWdt, int iWndHardCaptHgt,
      int iScrX, int iScrY, int iScrDX, int iScrDY,
      int iResDXenl, int iResDYenl,
      DWORD dwStyle, int iInitWndX, int iInitWndY, int iInitWndDX, int iInitWndDY)
: KpPubDlg(pKpFileSys,
   iXmlVers, iEncMode, lpszCaption, iWndDXmin, iWndDXmax, iWndDYmin, iWndDYmax,
   iWndSoftBorderWdt, iWndSoftCaptHgt, iWndHardBorderWdt, iWndHardCaptHgt,
   iScrX, iScrY, iScrDX, iScrDY, iResDXenl, iResDYenl,
   dwStyle, iInitWndX, iInitWndY, iInitWndDX, iInitWndDY)
{
   m_pResCtrl = NULL;
   m_pGeckoInit = NULL;
}


// --------------------------------------------------
KpGeckoDialog::~KpGeckoDialog()
{
// PutLogMessage_("---------------- KpGeckoDialog::~KpGeckoDialog()");
   FinitGecko();
}


// --------------------------------------------------
HRESULT KpGeckoDialog::InitGecko(void)
{
HRESULT retc = S_OK;

// TODO: jei bus keli KpGeckoDialog objektai, ar nesusipjaus pakartotinë inicializacija?
   if((m_pResCtrl == NULL) && SUCCEEDED(retc)) // vienkartinë inicializacija
      KP_NEW(m_pResCtrl, XKpGecko);

   if((m_pGeckoInit == NULL) && (KpGeckoDialogPtr != NULL) && SUCCEEDED(retc))
   {
// jei jau buvo inicializuota, tik perkeliam nuorodà ið ankstesnio objekto
      m_pGeckoInit = KpGeckoDialogPtr->m_pGeckoInit;
   }
   if((m_pGeckoInit == NULL) && SUCCEEDED(retc))
      KP_NEW(m_pGeckoInit, XGeckoInit);

   KpGeckoDialogPtr = this; // TODO: reikia steko, atsimenant visus buvusius

   if(SUCCEEDED(retc)) m_pGeckoInit->setProtocolIStreamFactory(KpGeckoStreamFactory);

return(retc);
}


// --------------------------------------------------
void KpGeckoDialog::FinitGecko(void)
{
HRESULT retc = S_OK;

// TODO: kai bus keli, kol nëra steko, susipjaus
// naikinam tik paskutiná, visi vëlesni – tik nuorodos á tà patá objektà
/* if(KpGeckoDialogPtr != NULL) */ // if(m_pGeckoInit != NULL)
      KP_DELETE(m_pGeckoInit);

   KP_DELETE(m_pResCtrl);

   KpGeckoDialogPtr = NULL; // TODO: reikia steko, atstatyt prieð tai buvusá
}


// ----------------------------------
HRESULT KpGeckoDialog::OpenWindowLocal(void)
{
HRESULT retc=S_OK;

   KP_ASSERT(m_hScreen != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc)) retc = InitGecko();

   if(SUCCEEDED(retc)) retc = CreateResCtrl(
      0, 0, // nestumiam á kairæ/virðø – ðitas paraðtes tvarkom HTML-e
      m_iScrCurDX + IBSH_RES_DX_ENL, m_iScrCurDY + IBSH_RES_DY_ENL,
      m_hScreen);

return(retc);
}


// ----------------------------------
HRESULT KpGeckoDialog::CreateResCtrl(int iXpos, int iYpos, int iWdt, int iHgt, HWND hParent)
{
HRESULT retc=S_OK;

   KP_ASSERT(hParent != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(m_pResCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);

// !!!! gràþinti kaþkokius klaidos kodus
   if(SUCCEEDED(retc))
      m_pResCtrl->create("LzdshXGecko",
#  ifdef TEST_GECKO_OVERLAPPED_WINDOW
         WS_OVERLAPPEDWINDOW
#  else
         WS_CHILD // WS_VISIBLE
#  endif
         |ES_DISABLENOSCROLL,
         iXpos, iYpos, iWdt, iHgt,
#  ifdef TEST_GECKO_OVERLAPPED_WINDOW
         0);
#  else
         hParent);
#  endif

   if(SUCCEEDED(retc))
      m_pResCtrl->setClipboardFilter(clipboardFilter);

// KpMsgOut("CreateResCtrl", IDI_ASTERISK, KP_MB_TESTI);

// if(SUCCEEDED(retc)) m_pResCtrl->setVisible(true);

return(retc);
}


// ----------------------------------
HRESULT KpGeckoDialog::RedrawWindowLocal(void)
{
HRESULT retc = S_OK;

#ifdef IBSH_RES_MODE_XGECKO
#  if Compiler != Watcom
   KP_ASSERT(m_pResCtrl, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) m_pResCtrl->setGeometry(m_iResX, m_iResY, m_iScrCurDX + m_iResDXenl, m_iScrCurDY + m_iResDYenl);
#  endif
#endif

return(retc);
}


// ----------------------------------
IInputStream *KpGeckoStreamFactory(const char *a_URL)
{
HRESULT retc = S_OK;
IInputStream *ret_p = NULL;
XmlVersions vers = XM_NO_VERS;
const unsigned char *entry_fname = NULL;
unsigned char *fname_ptr = NULL;
unsigned char *pntd = NULL;
bool cont = True;
const unsigned char *test_str;
int answ_no = -1;
unsigned char url[KP_MAX_FNAME_LEN + 7 + 1]; // kad dar tilptø "tux:///"
wchar_t *url_buf = NULL;
int prod_ver = 0;

// PutLogMessage_("KpGeckoStreamFactory() %s", a_URL);

   KP_ASSERT(a_URL != NULL, E_INVALIDARG, null, True);

// ----------------------- url
   KP_ASSERT(strlen(a_URL) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, a_URL, False);
   if(SUCCEEDED(retc))
   {
      KpStApp::DecodePostMsg(url, (const unsigned char *)a_URL, False); // iš xGecko ateina su perkoduotais %20 etc.
      url[KP_MAX_FNAME_LEN] = Nul;
   }

   KP_ASSERT(strstr(url, TV_XL_TUX_PATH_PREFIX) == url, E_INVALIDARG, url, True); // "tux:///"

   KP_ASSERT(KpGeckoDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(KpGeckoDialogPtr->m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);

// ----------------------- entry_fname
   if(SUCCEEDED(retc)) retc = KpGeckoDialogPtr->GetXmlVersion(&vers);

   if(SUCCEEDED(retc))
   {
      if(XM_IS_VERS_PURE_HTML(vers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_HTML;
      else if(XM_IS_VERS_XHTML(vers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_XHTML;
      else if(XM_IS_VERS_XML(vers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_XML;

      if(entry_fname == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

// ----------------------- fname_ptr
#if KP_XGECKO_VER == 124 // "1.2.4"
   fname_ptr = &url[4]; // Imam nuo 5 simbolio, nes pirmi 4 yra "tux:"
// #endif
#else // #if KP_XGECKO_VER == 130 // "1.3.0"
   fname_ptr = &url[7]; // Imam nuo 8 simbolio, nes pirmi 7 yra "tux:///"
#endif
// PutLogMessage_(">>>> KpGeckoStreamFactory() 3: [%s]", fname_ptr);

// ------------------------------------
// if(SUCCEEDED(retc))
// {
// printf("ATIDAROMAS FAILAS: %s\n", url);
// KP_TRACE_1("KpGeckoStreamFactory(%s);", url);
// KP_TRACE_2("KpGeckoStreamFactory(%s); %s", url, KPGECKO_TUX_EXIT_URL);
// PutLogMessage_2("KpGeckoStreamFactory(%s); m_lpszCurSearchKwd: %s", url, KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd);
// }

#if FALSE
static unsigned char dir_name[KP_MAX_FNAME_LEN + 1];
GetLocalPath(dir_name, KP_LocalDir, True);
PutLogMessage_(">>>> KpGeckoStreamFactory() 1: [%s] [%s]", url, dir_name);
PutLogMessage_(">>>> KpGeckoStreamFactory() 1: [%s] [%s]", url, entry_fname);
#endif

// ------------------------------------
   if(SUCCEEDED(retc))
   {
      if(strstr(url, KPST_GRP_PATH_PREFIX) == url) // "tux:///KpStart:"
      {
// PutLogMessage_("KpGeckoStreamFactory(%s)", a_URL);      
         pntd = url + strlen(KPST_GRP_PATH_PREFIX);

StartSelKwdIxs kwd_ix = NoStartSelIx;
         retc = GetKwrdIndex((int *)(&kwd_ix), pntd, lpszaStartSelKwds, -1, False, False);
         if(retc == KP_E_KWD_NOT_FOUND) KP_ERROR(retc, pntd);

         if(SUCCEEDED(retc))
         {
            pntd += strlen(lpszaStartSelKwds[kwd_ix]);
            KP_ASSERT(*pntd++ == ':', KP_E_FILE_FORMAT, url, True);
         }

         if(SUCCEEDED(retc)) switch(kwd_ix)
         {
// --------------------------------------
         case StartAdminActionIx:
//          retc = TestAdmin(&bAdminFl);
            if(!bAdminFl)
            {
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN /* STARTSEL_MSG_NOT_ADMIN */, IDI_WARNING, KP_MB_GERAI);
               break;
            }
         case StartActionIx:
         case StartAndCloseActionIx:

// ieðkom darbinio katalogo
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];
static unsigned char wrk_dir[KP_MAX_FTYPE_LEN * 2 + 1];
            if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, pntd);
            if(SUCCEEDED(retc))
            {
               strcpy(wrk_dir, disk);
               strcat(wrk_dir, path);
            }

// vykdom dos komandà
            if(SUCCEEDED(retc))
            {
               retc = StartCmdProcess(pntd, wrk_dir /* KP_CUR_DIR */, NULL, NULL, True, SW_SHOWNORMAL, SW_SHOWMINIMIZED,
                                          True, (const unsigned char *)"", True, False);
               if(retc == KP_E_FILE_NOT_FOUND)
               {
                  KpMsgOut(KP_MSG_NOTINST_DELETE, IDI_ERROR, KP_MB_TESTI);
                  retc = S_OK;
               }
            }

// baigiam meniu valdymo programà
            if(kwd_ix == StartAndCloseActionIx)
            {
// praneðimai á iBshDlg::DoEdit() kaþko nenueina
// PutLogMessage_("KpGeckoStreamFactory() 2: WM_QUIT %d %d", GetCurrentThreadId(), iKpMainThread);
//             PostQuitMessage(SUCCEEDED(retc)?IDOK:IDABORT);
//             PostThreadMessage(iKpMainThread, WM_QUIT, SUCCEEDED(retc)?IDOK:IDABORT, 0L);
               KpGeckoDialogPtr->m_bClose = True;
            }
            break;

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case OptionsIx:
            KP_ASSERT(pOptDialog != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) if(!theOptDialog.m_bWindowOpen)
            {
               theOptDialog.m_bWindowOpen = True;
               if(SUCCEEDED(retc)) retc = theOptDialog.OpenWindow(hKpInstance);
//             if(SUCCEEDED(retc)) retc = theOptDialog.DoEdit();
            }

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case LogoffIx:
            KpGeckoDialogPtr->m_bClose = True;
         case LoginIx:
//          PostThreadMessage(iKpMainThread, WM_COMMAND, 0L, KP_ID_LOGOFF); // á iBshDlg::DoEdit() kaþko nenueina
            KpGeckoDialogPtr->m_bLogoff = True;
PutLogMessage_("KpGeckoStreamFactory()  m_bClose %d  m_bLogoff %d", KpGeckoDialogPtr->m_bClose, KpGeckoDialogPtr->m_bLogoff);

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
         case DoLoginIx:
// url: "tux:///KpStart:DoLogin:?cmd=1&user=vardas&pwd=slaptazodis"
// pntd: "?cmd=1&user=vardas&pwd=slaptazodis"
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->ProcDoLogin(pntd);
            KpGeckoDialogPtr->m_bClose = True;
            if(FAILED(retc)) KpGeckoDialogPtr->m_bLogoff = True; // KP_E_CANCEL

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case RefreshIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->RefreshGrpMenu(True);

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
         case StopRefreshIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SwitchGrpMenuRefreshing(False);

//          KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
            ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
            KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
         case StartRefreshIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SwitchGrpMenuRefreshing(True);

//          KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
            ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
            KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case BrowseIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(theKpStAppPtr->m_pGrpKpPubDlg != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(theKpStAppPtr->m_pGrpKpPubDlg->m_pResCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);

            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SwitchGrpMenuRefreshing(False);

            KP_NEWA(url_buf, wchar_t, strlen(pntd) + 1);

            if(SUCCEEDED(retc)) KptStrToUnicode(url_buf, pntd, TV_MAIN_CTBL);
            if(SUCCEEDED(retc)) theKpStAppPtr->m_pGrpKpPubDlg->m_pResCtrl->loadURI(url_buf);

            KP_DELETEA(url_buf);

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case ReturnIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            
            if(SUCCEEDED(retc))
            {
               if(theKpStAppPtr->m_bLogin)
                  retc = theKpStAppPtr->GenLoginDlg();
               else
               {
                  retc = theKpStAppPtr->SwitchGrpMenuRefreshing(True);
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->RefreshGrpMenu(True);
               }
            }

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case DownLoadIx:
// PutLogMessage_("KpGeckoStreamFactory() %s", a_URL);
// PutLogMessage_("KpGeckoStreamFactory() %s", url);
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->StartGrpDownloadThread(pntd);

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case UninstIx:
// PutLogMessage_("KpGeckoStreamFactory() UninstIx: [%s]", a_URL);
// PutLogMessage_("KpGeckoStreamFactory() UninstIx: [%s]", pntd);
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->StartUninstThread(pntd);

// //       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
//          ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
//          KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case SetVarIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveVar(pntd);
// duodam atsakymà, kad OK

//          KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True)); // registruoti nereikia, trins tux_gecko
            ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)(SUCCEEDED(retc)?"1":"0"), True);
            KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            break;

         case GetVarIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

unsigned char val_buf[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 100];
            if(SUCCEEDED(retc))
            {
               if(strcmp(pntd, "user") == 0)
                  retc = theKpStAppPtr->GetIniUserData(val_buf);
               else
               {
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);
                  if(SUCCEEDED(retc))
                  {
                     if(FAILED(theKpStAppPtr->GetProdVerRegVariableStr(val_buf, prod_ver, pntd)))
                        val_buf[0] = Nul;
                  }
               }
// PutLogMessage_("KpGeckoStreamFactory() user: [%s]", val_buf);               
//             KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, val_buf, True)); // registruoti nereikia, trins tux_gecko
               ret_p = new XKpGeckoStream((FILE *)NULL, val_buf, True);
               KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
            }
            break;
#endif

// --------------------------------------
#if IBSH_PROJ == IBSH_PROJ_START_GRP
         case DiagMsgIx:
            KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->GrpSendDiagMsg(pntd);
            break;
#endif

// --------------------------------------
         default: KP_ERROR(E_NOTIMPL, lpszaStartSelKwds[kwd_ix]);
         }

// PutLogMessage_("KpGeckoStreamFactory(): %s %s", a_URL, lpszaStartSelKwds[kwd_ix]);

      } //  // if(strstr(url, KPST_GRP_PATH_PREFIX) == url)

      else if(strcmp(url, entry_fname) == 0) // "tux:///entry.html"
      {
#if FALSE
char str_buf[400];
sprintf(str_buf, ">>>> KpGeckoStreamFactory(): %s", url);
PutLogMessage((const unsigned char *)str_buf, NULL);
#endif
//       KP_NEW(ret_p, XKpGeckoStream((FILE *)NULL, (const unsigned char *)url)); // registruoti nereikia, trins tux_gecko
         ret_p = new XKpGeckoStream((FILE *)NULL, (const unsigned char *)url); // skaitysim ið m_lpszResultFormatted[] // pirmas failas ArkSh arba þodyno lizdas LzdSh
         KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
      }

// -----------------------
      else if(strcmp(url, KPGECKO_TUX_EXIT_URL) == 0) // "tux:///exit"
      {
         retc = KpGeckoDialogPtr->m_pKpFileSys->SendAnswers(0);
         PostQuitMessage(IDCANCEL); // iki iBshDialogProc() ar iBshDlg::DoEdit() nenueina
KP_TRACE_("KpGeckoStreamFactory(): IDCANCEL: GetCurrentThreadId(): %d %d", GetCurrentThreadId(), iKpMainThread);
         KP_ASSERT(iKpMainThread, KP_E_SYSTEM_ERROR, null, True);
//       if(SUCCEEDED(retc)) PostThreadMessage(iKpMainThread, WM_QUIT, IDCANCEL, 0L);
         if(SUCCEEDED(retc)) PostThreadMessage(iKpMainThread, WM_CLOSE, IDCANCEL, 0L);
      }

// ----------------
      else
      {
         if(strcmp(url, KPGECKO_TUX_PROC_URL) == 0) // "tux:///proc"
         {
            KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniCmdStr(fname_ptr);
         }

// ----------------
         if((strstr(fname_ptr, ".htm") == NULL) || (fname_ptr[0] != 'p') || (!isdigit(fname_ptr[1]))) // iðorinis failas
         {
// PutLogMessage_("KpGeckoStreamFactory(): ext. file: [%s] [%s]", fname_ptr, url);          
            retc = KpGeckoDialogPtr->m_pKpFileSys->CreateGeckoStream(fname_ptr, url, &ret_p);
         }
// tux:///p21.htm
// tux:///p21.htm?answ=a3 - atsakymas nr. 3
         else // naujas vidinis ArkSh failas
         {
            if(KpGeckoDialogPtr != NULL) if(KpGeckoDialogPtr->m_pKpFileSys != NULL)
               KpGeckoDialogPtr->m_pKpFileSys->BlockSemaphore();

            if(SUCCEEDED(retc)) retc = KpGeckoDialogPtr->m_pKpFileSys->CloseFiles(True);

            KP_ASSERT(strlen(fname_ptr) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)) strcpy(KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd, fname_ptr);

// PutLogMessage_(">>>> KpGeckoStreamFactory() 4: [%s]", KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd);

// uzduoties nr.
            if(SUCCEEDED(retc))
            {
               retc = KpGeckoDialogPtr->m_pKpFileSys->CalcTaskNo();
               cont = (KpGeckoDialogPtr->m_pKpFileSys->m_iTaskNo >= 0);
            }
// PutLogMessage_(">>>> KpGeckoStreamFactory() 5: m_iTaskNo: %d cont: %d [%s]", KpGeckoDialogPtr->m_pKpFileSys->m_iTaskNo, cont, KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd);

            if(cont && SUCCEEDED(retc))
            {
               pntd = strchr(KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd, '?');
               cont = (pntd != NULL);
            }

// analizuojam atsakymus
            if(cont && SUCCEEDED(retc))
            {
               *pntd++ = Nul;
               test_str = (const unsigned char *)"answ=a";
               cont = (strstr(pntd, test_str) == pntd); KP_ASSERT(cont, E_INVALIDARG, null, False);
            }

            if(cont && SUCCEEDED(retc))
            {
               pntd += 6; // strlen(test_str);
               cont = (sscanf((const char *)pntd, "%d", &answ_no) == 1);
               KP_ASSERT(cont, E_INVALIDARG, null, False);
            }

            if(cont && SUCCEEDED(retc)) retc = KpGeckoDialogPtr->m_pKpFileSys->ProcessAnswer(answ_no);

// keièiam failà
            if(SUCCEEDED(retc)) retc = KpGeckoDialogPtr->m_pKpFileSys->OpenFiles();

            KpGeckoDialogPtr->m_pKpFileSys->m_lCurEntryId = (-1L);

            if(SUCCEEDED(retc)) if(KpGeckoDialogPtr->m_pKpFileSys->m_lThreadId == 0)
                retc = KpGeckoDialogPtr->m_pKpFileSys->SearchForEntry(KpGeckoDialogPtr);

            if(KpGeckoDialogPtr != NULL) if(KpGeckoDialogPtr->m_pKpFileSys != NULL)
               KpGeckoDialogPtr->m_pKpFileSys->ReleaseSemaphore();

         } // else // if((strstr(fname_ptr, ".htm") == NULL) || (fname_ptr[0] != 'p') || (!isdigit(fname_ptr[1]))) // iðorinis failas

      } // else

   } // if(SUCCEEDED(retc))

return(ret_p);
}


// ----------------------------------
XKpGeckoStream::XKpGeckoStream(FILE *a_file, const unsigned char *lpszURI, bool bInline)
{
HRESULT retc = S_OK;

// PutLogMessage_("XKpGeckoStream::XKpGeckoStream() 1 [%s]", lpszURI);

   m_lResultPtr = 0L;
   m_bInline = bInline;

   m_lpszURI[0] = Nul;

   if(lpszURI == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strncpy(m_lpszURI, lpszURI, KP_MAX_FNAME_LEN);
      m_lpszURI[KP_MAX_FNAME_LEN] = Nul;
   }

   m_file = a_file;
// PutLogMessage_("XKpGeckoStream::XKpGeckoStream(): m_file: %x", m_file);

   m_XmlO1_file = NULL;
   m_lpszFileBuf = null;
   m_lBufSize = 0L;

#if FALSE
char str_buf[400];
sprintf(str_buf, ">>>> XKpGeckoStream::XKpGeckoStream(): %lx", this);
PutLogMessage(str_buf, NULL);
#endif

#ifdef Debug
fstream out_file("arksh.htm", ios::out | ios::binary);
out_file.write((const char *)KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf, strlen((const char *)KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf));
out_file.close();
#endif
}


// ----------------------------------
XKpGeckoStream::XKpGeckoStream(XmlO1 *XmlO1_file, const unsigned char *lpszURI, unsigned char *lpszFileBuf)
{
HRESULT retc = S_OK;

// PutLogMessage_("XKpGeckoStream::XKpGeckoStream() 2 [%s]", lpszURI);

   m_lResultPtr = 0L;
   m_bInline = False;

   m_lpszURI[0] = Nul;

   if(lpszURI == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strncpy(m_lpszURI, lpszURI, KP_MAX_FNAME_LEN);
      m_lpszURI[KP_MAX_FNAME_LEN] = Nul;
   }

   m_file = NULL;
   m_XmlO1_file = XmlO1_file;
// PutLogMessage_("XKpGeckoStream::XKpGeckoStream(): m_XmlO1_file: %x  m_XmlO1_file->m_lpszFName: %s", m_XmlO1_file, m_XmlO1_file->m_lpszFName);
   m_lpszFileBuf = lpszFileBuf;
   m_lBufSize = 0L;
}


// ----------------------------------
XKpGeckoStream::XKpGeckoStream(unsigned char *lpszFileBuf, const unsigned char *lpszURI, long lFileBufSize)
{
HRESULT retc = S_OK;

PutLogMessage_("XKpGeckoStream::XKpGeckoStream() 3 [%s] %ld", lpszURI, lFileBufSize);
// fstream out_file("kpn1.dat", ios::out);
// out_file.write((const char *)lpszFileBuf, lFileBufSize);
// out_file.close();

   m_lResultPtr = 0L;
   m_bInline = False;

   m_lpszURI[0] = Nul;

   if(lpszURI == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strncpy(m_lpszURI, lpszURI, KP_MAX_FNAME_LEN);
      m_lpszURI[KP_MAX_FNAME_LEN] = Nul;
   }

   m_file = NULL;
   m_XmlO1_file = NULL;
   m_lpszFileBuf = lpszFileBuf;
   m_lBufSize = lFileBufSize;
}


// ----------------------------------
XKpGeckoStream::~XKpGeckoStream(void)
{
HRESULT retc = S_OK;

// PutLogMessage_("XKpGeckoStream::~XKpGeckoStream(): m_file: %x  m_XmlO1_file: %x", m_file, m_XmlO1_file);

   if(m_file != NULL) fclose(m_file);
   m_file = NULL;

   KP_DELETE(m_XmlO1_file);
   KP_DELETEA(m_lpszFileBuf);

#if FALSE
char str_buf[400];
sprintf(str_buf, ">>>> XKpGeckoStream::~XKpGeckoStream(): %lx", this);
PutLogMessage(str_buf, NULL);
#endif
}


// ----------------------------------
int XKpGeckoStream::read(char *a_buffer, int size)
{
HRESULT retc = S_OK;
long num_bytes = 0;
long num_chars = 0;
UC_Modes enc = UC_No_Mode;

   KP_ASSERT(KpGeckoDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(KpGeckoDialogPtr->m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = KpGeckoDialogPtr->GetEncoding(&enc);

// -------------------------------
   if(m_file != NULL) // atidarytas realus FILE failas - skaitom ið jo
   {
      if(SUCCEEDED(retc))
      {
         num_bytes = fread((void*)a_buffer, 1, size, m_file);
// PutLogMessage_("XKpGeckoStream::read() 1 %s", a_buffer);
         num_chars = num_bytes;
         if(enc >= UC_Unicode16) num_chars /= 2; // sizeof(UniChar);
      }

// KP_TRACE_1("XKpGeckoStream::read: external: %d:", num_bytes);

   }

// -------------------------------
   else if(m_XmlO1_file != NULL) // atidarytas realus m_XmlO1_file failas
   {
// !!! TODO: padaryt ir parsinamus XML-inius, dabar kol kas tik binary
      KP_ASSERT(m_XmlO1_file->m_fFiles != NULL, KP_E_NO_FILE, null, True);
      while((num_bytes < size) && SUCCEEDED(retc))
      {
KpChar in_ch;
         retc = m_XmlO1_file->m_fFiles[XL_IX_DefDataFile]->GetChar(&in_ch, False);
         if(SUCCEEDED(retc)) a_buffer[num_bytes++] = in_ch;
      }
// PutLogMessage_("XKpGeckoStream::read() 2 %s", a_buffer);

// KP_TRACE_1("XKpGeckoStream::read: external: %d:", num_bytes);
// PutLogMessage_("XKpGeckoStream::read(): m_file: %x  m_XmlO1_file: %x  num_bytes: %d  retc: %x", m_file, m_XmlO1_file, num_bytes, retc);
      if(retc == KP_E_EOF) retc = S_OK;
      num_chars = num_bytes;
      if(enc >= UC_Unicode16) num_chars /= 2; // sizeof(UniChar);
   }

// -------------------------------
   else if(m_lpszFileBuf != null) // skaitom tiesiai ið m_lpszFileBuf[]
   {
      num_bytes = m_lBufSize - m_lResultPtr;
      if(size < num_bytes) num_bytes = size;
#if FALSE
PutLogMessage_("XKpGeckoStream::read() [%s] %d", m_lpszURI, num_bytes);
unsigned char fname[400];
strcpy(fname, m_lpszURI + strlen("tux:///"));
strcat(fname, ".copy");
FILE *out_file = fopen((const char *)fname, "ab");
fwrite(m_lpszFileBuf + m_lResultPtr, num_bytes, 1, out_file);
fclose(out_file);
#endif
      memcpy(a_buffer, m_lpszFileBuf + m_lResultPtr, num_bytes);
      m_lResultPtr += num_bytes;
   }

// -------------------------------
   else if(m_bInline) // skaitom ið m_lpszURI[]
   {
      num_bytes = strlen(m_lpszURI + m_lResultPtr);
      if(size < num_bytes) num_bytes = size;
      memcpy(a_buffer, m_lpszURI + m_lResultPtr, num_bytes);
      m_lResultPtr += num_bytes;
   }

// -------------------------------
   else // failø nëra – srautas atidarytas URI uþklausa "tux:///entry.html", skaitom ið buferio m_lpszResultFormatted[]
   {

int bytes_left = 0;

      if(((a_buffer == NULL) || (size < 0)) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

//    if((pLzdSearch == NULL) && SUCCEEDED(retc))
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      KP_ASSERT(KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf != NULL, KP_E_SYSTEM_ERROR, null, True);

#ifdef Debug
// unsigned char str_buf[100];
// strncpy(str_buf, theSearchThread.m_lpszResultFormatted + m_lResultPtr, 20);
// str_buf[20] = Nul;
// KP_TRACE_2("XKpGeckoStream::read: %d: %s", m_lResultPtr, str_buf);
// KP_TRACE_1("XKpGeckoStream::read: internal: %d:", m_iResultPtr);
#endif


      if(SUCCEEDED(retc))
      {
//       num_bytes = (size / sizeof(theSearchThread.m_lpszResultFormatted[0])) * sizeof(theSearchThread.m_lpszResultFormatted[0]);
         num_bytes = size;
         if(enc >= UC_Unicode16) num_bytes = (num_bytes / sizeof(UniChar)) * sizeof(UniChar);

//       bytes_left = LzdshtResLen(theSearchThread.m_lpszResultFormatted) * sizeof(theSearchThread.m_lpszResultFormatted[0]) - m_lResultPtr;
         if(enc >= UC_Unicode16) bytes_left = wcslen(KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf) * sizeof(UniChar) - m_lResultPtr;
         else bytes_left = strlen((unsigned char *)KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf) - m_lResultPtr;

         if(bytes_left < num_bytes) num_bytes = bytes_left;

//       if(bytes_left == 0)
//       {
//           KpGeckoDialogPtr->m_iDoRedraw = 1; // 2; // True; // kad pakeistø langelio dydá, bet tik po iðvedimo

// PutLogMessage_1("XKpGeckoStream::read m_lpszCurSearchKwd: %s", KpGeckoDialogPtr->m_pKpFileSys->m_lpszCurSearchKwd);

//       }

//       num_chars = num_bytes / sizeof(theSearchThread.m_lpszResultFormatted[0]);
         num_chars = num_bytes;
         if(enc >= UC_Unicode16) num_chars = num_bytes / sizeof(UniChar);

//       if(m_lResultPtr == 0) num_bytes -= 2; // nepadeda

#ifdef TEST_GECKO_CONVERT_TO_8BIT
unsigned char *buf_ptr = null;
         KP_NEWA(buf_ptr, unsigned char, num_chars + 1);

UniChar *uni_ptr = NULL;
         KP_NEWA(uni_ptr, UniChar, num_chars + 1);

         if(((buf_ptr == NULL) || (uni_ptr == NULL)) && SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
         {
            memcpy(uni_ptr, (const char *)(&(theSearchThread.m_lpszResultFormatted)) + m_lResultPtr, num_bytes);
            uni_ptr[num_chars] = C_Nul;
         }

#else
#   if FALSE // nepadeda
         if(m_lResultPtr == 0)
         {
            a_buffer[0] = 0xFF;
            a_buffer[1] = 0xFE;
            memcpy(a_buffer+2, (const char *)(&(theSearchThread.m_lpszResultFormatted)) + m_lResultPtr, num_bytes);
         }
         else
#   endif
         {
//          memcpy(a_buffer, (const char *)(&(theSearchThread.m_lpszResultFormatted)) + m_lResultPtr, num_bytes);
            memcpy(a_buffer, (const char *)KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf + m_lResultPtr, num_bytes);
         }
#endif

// PutLogMessage_("XKpGeckoStream::read() 3 %s", a_buffer);

         m_lResultPtr +=  num_bytes;

#ifdef TEST_GECKO_CONVERT_TO_8BIT
         KptUnicodeToStr(buf_ptr, uni_ptr, 71);

         num_bytes /= sizeof(theSearchThread.m_lpszResultFormatted[0]);

         memcpy(a_buffer, buf_ptr, num_bytes);

         KP_DELETEA(uni_ptr);
         KP_DELETEA(buf_ptr);
#endif

// PutLogMessage_("XKpGeckoStream::read(): internal: total_bytes: %d  num_bytes: %d", num_bytes, strlen((unsigned char *)KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf));

// valom buferá kai jau perduotas, kad sunkiau grabintøsi
         if(SUCCEEDED(retc)) if(num_bytes == bytes_left) // if(m_lResultPtr >= strlen(KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf))
         {
            memset(KpGeckoDialogPtr->m_pKpFileSys->m_pResBuf, Nul, m_lResultPtr);
            m_lResultPtr = 0;
         }

      } // if(SUCCEEDED(retc))

   } // else // if(m_file)

// TODO !!!! po paskutinio skaitymo nuresetint buferá
//    if(SUCCEEDED(retc)) retc=theSearchThread.m_lpOutFileObj->Reset();
//    if(SUCCEEDED(retc)) memset(m_lpszResultFormatted, Nul, KPGECKO_RESULT_BUF_LEN);

// ---------------------------------- treisinam failo turini
#if FALSE // #  ifdef Debug
if(strstr(m_lpszURI, ".htm") /* || strstr(m_lpszURI, ".css") */)
{
unsigned char *buf_ptr = null;
   KP_NEWA(buf_ptr, unsigned char, num_chars + 1);

   if(SUCCEEDED(retc))
   {
      buf_ptr[0] = Nul;

      if(num_bytes == num_chars)
      {
         memcpy(buf_ptr, a_buffer, num_chars); // num_bytes);
         buf_ptr[num_chars] = Nul;
      }
      else
      {
UniChar *uni_ptr = NULL;
         KP_NEWA(uni_ptr, UniChar, num_chars + 1);

         if(SUCCEEDED(retc))
         {
            memcpy(uni_ptr, a_buffer, num_bytes);
            uni_ptr[num_chars] = C_Nul;

            KptUnicodeToStr(buf_ptr, uni_ptr, 71);
         }

         KP_DELETEA(uni_ptr);
      }

      KP_TRACE(buf_ptr);
   }

   KP_DELETEA(buf_ptr);
}
#endif

#if FALSE // #  ifdef Debug
char str_buf[100];
sprintf(str_buf, "XKpGeckoStream::read(%x, %d) %d %d %s", a_buffer, size, num_bytes, num_chars, m_lpszURI);
KP_TRACE(str_buf);
#endif

// -------------------------- iðlaisvinam semaforà, kurá turëjo uþstatyti prieð iðkvieèiant m_pKpFileSys->SearchForEntry() (KpGeckoDialog::DisplayResult())
// taip neveikia
//    if(num_bytes == 0)
//       if(KpGeckoDialogPtr != NULL) if(KpGeckoDialogPtr->m_pKpFileSys != NULL)
//          KpGeckoDialogPtr->m_pKpFileSys->ReleaseSemaphore();
   if(KpGeckoDialogPtr != NULL) KpGeckoDialogPtr->m_bXGeckoPending = False;

// PutLogMessage_("XKpGeckoStream::read() [%s]", a_buffer);

return(num_bytes);
}


// --------------------------------------------------
HRESULT KpGeckoDialog::DisplayResult(void)
{
HRESULT retc=S_OK;
const wchar_t *entry_fname = NULL;

   KP_ASSERT(m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True)
   KP_ASSERT(m_pResCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(m_pKpFileSys != NULL) m_pKpFileSys->BlockSemaphore();
   m_bXGeckoPending = True;

   if(SUCCEEDED(retc))
   {
#ifdef TEST_GECKO_FROM_FILE
// KP_TRACE("m_pResCtrl->loadURI(L\"tux:index.html\")");
// KP_TRACE("m_pResCtrl->loadURI(L\"tux:///index.html\")");

#  if KP_XGECKO_VER == 124 // "1.2.4"
      if(XM_IS_VERS_PURE_HTML(m_iXmlVers)) entry_fname = (L"tux:index.html"); // tux_gecko_1.2.4
      else if(XM_IS_VERS_XHTML(m_iXmlVers)) entry_fname = (L"tux:index.xhtml"); // tux_gecko_1.2.4
      else if(XM_IS_VERS_XML(m_iXmlVers)) entry_fname = (L"tux:index.xml"); // tux_gecko_1.2.4
#  endif
#  if KP_XGECKO_VER == 130 // "1.3.0"
      if(XM_IS_VERS_PURE_HTML(m_iXmlVers)) entry_fname = (L"tux:///index.html");
      else if(XM_IS_VERS_XHTML(m_iXmlVers)) entry_fname = (L"tux:///index.xhtml");
      else if(XM_IS_VERS_XML(m_iXmlVers)) entry_fname = (L"tux:///index.xml");
#  endif

#else
// KP_TRACE("m_pResCtrl->loadURI(L\"tux:entry.html\")");
// KP_TRACE("m_pResCtrl->loadURI(L\"tux:///entry.html\")");

      if(XM_IS_VERS_PURE_HTML(m_iXmlVers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_HTML;
      else if(XM_IS_VERS_XHTML(m_iXmlVers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XHTML;
      else if(XM_IS_VERS_XML(m_iXmlVers)) entry_fname = KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XML;
#endif
   }

   if((entry_fname == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// PutLogMessage((const unsigned char *)">>>> KpGeckoDialog::Load()", NULL);

   if(SUCCEEDED(retc)) m_pResCtrl->loadURI(entry_fname);

// ----------------------------
#ifndef IBSH_NOZOOM
   if(SUCCEEDED(retc)) m_pResCtrl->setZoom((float)m_iFact / 1000.);
#endif

// -----------------------
   if(SUCCEEDED(retc)) m_pResCtrl->setVisible(true);

// -----------------------
   if(SUCCEEDED(retc)) retc = DisplayResultCommon();

// -----------------------
   if(m_pKpFileSys != NULL) m_pKpFileSys->ReleaseSemaphore();

return(retc);
}
