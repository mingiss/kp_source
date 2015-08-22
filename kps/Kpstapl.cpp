// ---------------------------
// kpstapl.cpp
// common application for program starters
// licence input dialog KPSTLIC
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <ctype.h>
#include <stdio.h>
#include <string>
// #include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <mmsystem.h>

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

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
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
#include "kpmsg.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
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

#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
// #error Envir!=MSWin32
#if (Envir!=MSWin32Con)
#error Envir!=MSWin32
#endif
#endif


// ==============================
// ----------------------------------
HRESULT KpStApp::OpenLicWindow(bool bUnReg, bool bEntered)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;
HDC dc;
int wnd_x=0;
int wnd_y=0;
KpStLicPars *lic_pars_ptr=NULL;
int hint2_fl = 0;
int persp_fl = 0;
int lic_cod1=0;
int lic_cod2=0;
int lic_cod3=0;
int lic_id;
int prod_ver;
int prod_ver_saved;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
bool obj_fl = False;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int prod_name_2_fl = 0;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR)) obj_fl = True;

   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdName(prod_name);

   if((m_hInstance==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "KPSTLIC",
      wcx.lpfnWndProc   = (WNDPROC)KpStLicDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hIconSm       = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hCursor       = ::LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      dc=GetDC(HWND_DESKTOP);
      if(dc==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   KP_DELETE(lic_pars_ptr);

   KP_NEW(lic_pars_ptr, KpStLicPars);

   if(SUCCEEDED(retc))
   {
      prod_name_2_fl = 0;
      if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;

      lic_pars_ptr->m_lpszEnterLicPrompt = (obj_fl?KPST_MSG_OBJ_REG:KPST_MSG_PROD_REG);
      lic_pars_ptr->m_lpszEnterLicExpl = (obj_fl?KPST_MSG_OBJ_REG_INFO:KPST_MSG_REG_INFO);
      lic_pars_ptr->m_lpszPrompt=KPST_MSG_IVESK_LIC;

      lic_pars_ptr->m_lpszHint = (obj_fl?KPST_MSG_OBJ_REG_PERSPEJ:KPST_MSG_REG_PERSPEJ);
      lic_pars_ptr->m_lpszButAkt = KPST_MSG_BUT_REG;
      lic_pars_ptr->m_lpszAtsaukt = KPST_MSG_CANCEL_REG;
      persp_fl = 1;

      if(bUnReg)
      {
         lic_pars_ptr->m_lpszEnterLicPrompt=KPST_MSG_UNREG;
         lic_pars_ptr->m_lpszEnterLicExpl = (obj_fl?KPST_MSG_OBJ_UNREG_INFO:KPST_MSG_UNREG_INFO);
         lic_pars_ptr->m_lpszPrompt=KPST_MSG_UNREG_IVESK_LIC;
         lic_pars_ptr->m_lpszHint=(const unsigned char *)"";
         lic_pars_ptr->m_lpszButAkt=KPST_MSG_BUT_UNREG;
         lic_pars_ptr->m_lpszAtsaukt=KPST_MSG_CANCEL_UNREG;
         persp_fl=0;
      }

      hint2_fl=1;
      lic_pars_ptr->m_lpszLic1[0] = Nul;
      lic_pars_ptr->m_lpszLic2[0] = Nul;
      lic_pars_ptr->m_lpszLic3[0] = Nul;

      lic_pars_ptr->m_bEntered = bEntered;
      lic_pars_ptr->m_bUnReg = bUnReg;

      if(bEntered)
      {
         lic_pars_ptr->m_lpszPrompt=(const unsigned char *)"";
         hint2_fl=0;

         if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_cod1, KP11_LIC_CODE1);
         if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_cod2, KP11_LIC_CODE2);
         if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_cod3, KP11_LIC_CODE3);

         if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

// KpMsgOutF_4("OpenLicWindow lic_id: %d prod_ver: %d rem_lic_id: %d rem_prod_ver: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
// KpMsgOutF_3("OpenLicWindow lic_code: %d-%d-%d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
// KpMsgOutF_4("OpenLicWindow inst_code: %d-%d-%d-%d", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
// KpMsgOutF_4("OpenLicWindow inst_key: %d-%d-%d-%d", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);

//       if(SUCCEEDED(retc)) retc = UnpackInstCode(); // èia jau vëlu – sugadintas KP11_INST_CODE1234 – perskaièiuotas su aktyviu lic. code, ne su ið data.dat perskaitytu

         if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&prod_ver_saved, KP11_REM_PRODVER); // nustatytas su UnpackInstCode() per CheckReg() (kpstreg.exe) ar RemoveReg() (kpstun.exe)

#if FALSE
unsigned char str_buf[100];
sprintf((char *)str_buf, "%d", lic_id);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// --------------------------------
// nustatom lic. laukø reikðmes, jei jau buvo ávestos á data.dat
// ðito tikrinimo ðiaip jau nereikëtø, nes bEntered jau buvo nustatytas pagal ðituos paèius poþymius
//       if((lic_id != m_iKpstRand0) && (prod_ver_saved == prod_ver) && SUCCEEDED(retc)) // KpstRand(0)
         {
            if(SUCCEEDED(retc)) retc=FormatKeyHex(lic_pars_ptr->m_lpszLic1, lic_cod1 /* m_iLicCode1 */);
            if(SUCCEEDED(retc)) retc=FormatKeyHex(lic_pars_ptr->m_lpszLic2, lic_cod2 /* m_iLicCode2 */);
            if(SUCCEEDED(retc)) retc=FormatKeyHex(lic_pars_ptr->m_lpszLic3, lic_cod3 /* m_iLicCode3 */);
         }
      }

   }

// ------------------------------

   if(SUCCEEDED(retc))
   {
      wnd_x=(GetDeviceCaps(dc, HORZRES)-KPSTLIC_WND_DX)/2;
      wnd_y=(GetDeviceCaps(dc, VERTRES)-KPSTLIC_WND_DY)/2;

      lic_pars_ptr->m_iWndWdt = bUnReg?KPSTLICREM_WND_DX:KPSTLIC_WND_DX;
      lic_pars_ptr->m_iWndHgt = KPSTLIC_WND_DY;

      m_hLicDialogWindow=CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSTLIC",
         (char *)KPST_MSG_LIC,       // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         wnd_x,  // CW_USEDEFAULT, // int x,               // horizontal position of window
         wnd_y,  // CW_USEDEFAULT, // int y,               // vertical position of window
         lic_pars_ptr->m_iWndWdt,          // int nWidth,           // window width
         lic_pars_ptr->m_iWndHgt,          // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         lic_pars_ptr            // LPVOID lpParam        // pointer to window-creation data
      );

      if(m_hLicDialogWindow==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// nereikia naikint - sunaikins lango callback programa KpStLicDialogProc()
// KP_DELETE(lic_pars_ptr);

return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpStLicDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
int retp;
bool endfl=False;
const unsigned char *enter_prompt;
const unsigned char *expl;
const unsigned char *prompt;
const unsigned char *hint;
const unsigned char *act;
const unsigned char *atsaukt;
int lic_id = 0;
int lic_id_sav = 0;
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT+100];
const unsigned char *pnts;
unsigned char *pntd;
bool entered;
LPCREATESTRUCT cst_ptr=NULL;
KpStLicPars *lic_pars_ptr=NULL;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int prod_name_2_fl = 0;
int hint2_fl = 0;
int persp_fl = 0;
unsigned char code_buf[KP_KWD_LEN + 1];
HDC hdc = NULL;
PAINTSTRUCT ps;
KpWnd *cur_wnd = NULL;
int wnd_dx, wnd_dy;
unsigned char *prod_name_2_ptr = null;
unsigned char *lic_buf_ptr;
const unsigned char *lic_buf_1 = (const unsigned char *)"";
const unsigned char *lic_buf_2 = (const unsigned char *)"";
const unsigned char *lic_buf_3 = (const unsigned char *)"";
int lic_high = 0;

   retp=LOWORD(wParam);
   endfl=False;

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

// istraukiam parametrus
   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// case WM_PAINT:
      enter_prompt=(unsigned char *)"";
      expl=(unsigned char *)"";
      prompt=(unsigned char *)"";
      hint=(unsigned char *)"";
      act=(unsigned char *)"";
      atsaukt=(unsigned char *)"";

      lic_buf[0] = Nul;
      entered=False;

      cst_ptr=(LPCREATESTRUCT)lParam;
      if(cst_ptr!=NULL) lic_pars_ptr=(KpStLicPars *)cst_ptr->lpCreateParams;
      if(lic_pars_ptr!=NULL)
      {
         enter_prompt=lic_pars_ptr->m_lpszEnterLicPrompt;
         expl=lic_pars_ptr->m_lpszEnterLicExpl;
         prompt=lic_pars_ptr->m_lpszPrompt;
         hint=lic_pars_ptr->m_lpszHint;
         act=lic_pars_ptr->m_lpszButAkt;
         atsaukt=lic_pars_ptr->m_lpszAtsaukt;

         entered=lic_pars_ptr->m_bEntered;

// ---------------------
         strcpy(lic_buf, lic_pars_ptr->m_lpszLic1);
         strcat(lic_buf, "-");
         strcat(lic_buf, lic_pars_ptr->m_lpszLic2);
         strcat(lic_buf, "-");
         strcat(lic_buf, lic_pars_ptr->m_lpszLic3);

//       if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetLicHighHp11(&lic_high);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->AddHigh(lic_buf, lic_high, 12);

         if(SUCCEEDED(retc))
         {
            lic_buf_1 = (const unsigned char *)"";
            lic_buf_2 = (const unsigned char *)"";
            lic_buf_3 = (const unsigned char *)"";

            lic_buf_ptr = lic_buf;
            lic_buf_1 = lic_buf_ptr;

            lic_buf_ptr = strchr(lic_buf_ptr, '-');
            if(lic_buf_ptr != null)
            {
               *lic_buf_ptr++ = Nul;
               lic_buf_2 = lic_buf_ptr;

               lic_buf_ptr = strchr(lic_buf_ptr, '-');
               if(lic_buf_3 != null)
               {
                  *lic_buf_ptr++ = Nul;
                  lic_buf_3 = lic_buf_ptr;
               }
            }
         }
      }

      hint2_fl=1; if(prompt[0]==Nul) hint2_fl=0;
      persp_fl=1; if(hint[0]==Nul) persp_fl=0;

      break;
   }

// vykdom
   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// ------
      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);

// ------
      KP_NEWO(cur_wnd, KpWnd(hwndDlg, TYP_KpDialog, null, NULL,
            hKpInstance, NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
            lic_pars_ptr->m_iWndWdt, lic_pars_ptr->m_iWndHgt, 1, 1, 0L, 0L,
            NULL));

      if(SUCCEEDED(retc)) retc = WndPreg(cur_wnd, TYP_KpDialog, hKpInstance, null, False);

// ------
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdNameDec(prod_name);

      if(SUCCEEDED(retc))
      {
         prod_name_2_fl = 0;
         if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;

         prod_name_2_ptr = prod_name;
         if(prod_name_2_fl)
         {
            prod_name_2_ptr = prod_name + KPSTLIC_MAX_PROD_NAME_LEN;
            while((*prod_name_2_ptr != Spc) && (prod_name_2_ptr > prod_name)) --prod_name_2_ptr;
            if(*prod_name_2_ptr == Spc) *prod_name_2_ptr++ = Nul;
            else
            {
               while((*prod_name_2_ptr != Spc) && (*prod_name_2_ptr != Nul)) prod_name_2_ptr++;
               if(*prod_name_2_ptr == Spc) *prod_name_2_ptr++ = Nul;
            }
         }
      }

// ------
      if(SUCCEEDED(retc)) retc = KpCreateIcon(hKpInstance, hwndDlg, NULL, KP_IDI_SETUP_ICON, KPST_SETUP_ICON_X, KPST_SETUP_ICON_Y, KPST_SETUP_ICON_WDT, KPST_SETUP_ICON_WDT, 0);
//    if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, NULL, IDCANCEL, IDI_SETUP_ICON, KPST_SETUP_ICON_X, KPST_SETUP_ICON_Y, KPST_SETUP_ICON_WDT, KPST_SETUP_ICON_WDT);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name, KPSTLIC_HEAD_X, KPSTLIC_HEAD_Y, 1,
                                    KPW_CONTROL_STYLE_BOLD /* KPW_CONTROL_STYLE_HEADING_3 */, 0, 0, NULL);
      if(prod_name_2_fl && SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name_2_ptr, KPSTLIC_HEAD_X, KPSTLIC_HEAD2_Y, 1,
                                    KPW_CONTROL_STYLE_BOLD /* KPW_CONTROL_STYLE_HEADING_3 */, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, enter_prompt, KPSTLIC_SUBHEAD_X, KPSTLIC_SUBHEAD_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, expl, KPSTLIC_HINT_X, KPSTLIC_HINT1_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(hint2_fl && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prompt, KPSTLIC_HINT_X, KPSTLIC_HINT2_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
//       if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_REG_CARD, KPSTLIC_HINT_X, KPSTLIC_HINT2_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
         if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_IVESK_LIC_1, KPSTLIC_HINT_X, KPSTLIC_HINT21_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      }

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_LIC_KOD, KPSTLIC_CODE_PROMPT_X, KPSTLIC_CODE_CTRL_Y, KPSTLIC_CODE_PROMPT_DX, 1,
                                    KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicCodeEdit1), lic_buf_1, KPST_KEY_SEGM_EDIT_DX, KPSTLIC_CODE1_EDIT_X, KPSTLIC_CODE_CTRL_Y,
                                    KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hLicCodeEdit1 == NULL) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"-", KPSTLIC_CODE_EDIT_DASH1_X, KPSTLIC_CODE_CTRL_Y, KPST_DASH_DX, 1,
                                    KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicCodeEdit2), lic_buf_2, KPST_KEY_SEGM_EDIT_DX, KPSTLIC_CODE2_EDIT_X, KPSTLIC_CODE_CTRL_Y,
                                    KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hLicCodeEdit2 == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"-", KPSTLIC_CODE_EDIT_DASH2_X, KPSTLIC_CODE_CTRL_Y, KPST_DASH_DX, 1,
                                    KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicCodeEdit3), lic_buf_3, KPST_KEY_SEGM_EDIT_DX, KPSTLIC_CODE3_EDIT_X, KPSTLIC_CODE_CTRL_Y,
                                    KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hLicCodeEdit3 == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ----------------------------------------------------------
// nustatom defaultines m_hLicCodeEdit* lauku reiksmes
// èia tik licencijuotiems updeitams - nafig reikia?
// ðiaip anksèiau ávestai licencijai per defaultinæ reikðmæ nustatyta jau KpCreateEdit()
      if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniIniLicID(&lic_id);

      if((lic_id != KpstRand(0)) && SUCCEEDED(retc))
      {
// issaugojam buvusius LicCode, etc.
//       if(SUCCEEDED(retc))  lic_id_sav = theKpStAppPtr->m_iLicID;
         if(SUCCEEDED(retc))
         {
            retc = EmuTv.GetHp11Variable(&lic_id_sav, KP11_LICID);
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

// nustatom default reiksmes is m_Ini
//       if(SUCCEEDED(retc)) theKpStAppPtr->m_iLicID = lic_id;
         if(SUCCEEDED(retc))
         {
            retc = EmuTv.SetHp11Variable(lic_id, KP11_LICID);
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            retc = theKpStAppPtr->CalcLicCode();
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

         lic_buf[0] = Nul;
         if(SUCCEEDED(retc))
         {
            retc = theKpStAppPtr->FormatLicCodeFull(lic_buf);
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

//       if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetLicHighHp11(&lic_high);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->AddHigh(lic_buf, lic_high, 12);

         if(SUCCEEDED(retc))
         {
            pnts = lic_buf;

            pntd = strchr(pnts, '-');
            if(pntd)
            {
               *pntd++ = Nul;
               SendMessage(theKpStAppPtr->m_hLicCodeEdit1, WM_SETTEXT, 0, (LPARAM)pnts);
               pnts = pntd;
            }

            pntd = strchr(pnts, '-');
            if(pntd)
            {
               *pntd++ = Nul;
               SendMessage(theKpStAppPtr->m_hLicCodeEdit2, WM_SETTEXT, 0, (LPARAM)pnts);
               pnts = pntd;
            }

//          pntd = strchr(pnts, '-');
//          if(pntd)
            {
//             *pntd++ = Nul;
               SendMessage(theKpStAppPtr->m_hLicCodeEdit3, WM_SETTEXT, 0, (LPARAM)pnts);
//             pnts = pntd;
            }
         }

// atstatom buvusius LicCod, etc.
//       if(SUCCEEDED(retc)) theKpStAppPtr->m_iLicID = lic_id_sav;
         if(SUCCEEDED(retc))
         {
            retc = EmuTv.SetHp11Variable(lic_id_sav, KP11_LICID);
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            retc = theKpStAppPtr->CalcLicCode();
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }
      }

// ----------------------------------------------------------

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, hint, KPSTLIC_PERSPEJ_X, KPSTLIC_PERSPEJ_Y, 1, KPW_CONTROL_STYLE_BOLD /* KPW_CONTROL_STYLE_HEADING_3 */, 0, 0, NULL);
//    if(SUCCEEDED(retc)) retc=KpCreateRichEdit(hKpInstance, hwndDlg, NULL, hint, KPSTLIC_HINT_DX, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL], KPSTLIC_HINT_X, KPSTLIC_PERSPEJ_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0);

//    if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, act, KPSTLIC_HINT_X, KPSTLIC_HINT3_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicOkButton), IDOK, KP_MSG_TESTI /* KPST_MSG_INTERNETU */,
         KPSTLIC_OK_BUT_X, KPSTLIC_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hLicOkButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicSkipButton), KPST_ID_SKIP, KPST_MSG_TELEFONU, KPSTLIC_SKIP_BUT_X, KPSTLIC_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hLicSkipButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hLicCancelButton), IDCANCEL, atsaukt, KPSTLIC_CANCEL_BUT_X, KPSTLIC_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hLicCancelButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!SetFocus(entered?theKpStAppPtr->m_hLicOkButton:theKpStAppPtr->m_hLicCodeEdit1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      KP_DELETE(lic_pars_ptr);

      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      wnd_dx = KPSTLIC_WND_DX;
      wnd_dy = KPSTLIC_WND_DY;

      if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, hwndDlg);
      if(cur_wnd && SUCCEEDED(retc))
      {
         wnd_dx = cur_wnd->m_iWdtDots;
         wnd_dy = cur_wnd->m_iHgtDots;
      }

      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdName(prod_name);
      prod_name_2_fl = 0;
      if(SUCCEEDED(retc))
         if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

//    if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTLIC_LINE_X1, KPSTLIC_LINE1_Y, /* lic_pars_ptr->m_bUnReg? */ KPSTLICREM_LINE_X2 /* :KPSTLIC_LINE_X2 */, KPSTLIC_LINE1_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTLIC_LINE_X1, KPSTLIC_LINE1_Y, wnd_dx - (iWndBorderWdt * 2), KPSTLIC_LINE1_Y, KP_WND_SUNKEN, NULL);

//    if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTLIC_LINE_X1, KPSTLIC_LINE2_Y, /* lic_pars_ptr->m_bUnReg? */ KPSTLICREM_LINE_X2 /* :KPSTLIC_LINE_X2 */, KPSTLIC_LINE2_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTLIC_LINE_X1, KPSTLIC_LINE2_Y + (wnd_dy - KPSTLIC_WND_DY_0), wnd_dx - (iWndBorderWdt * 2), KPSTLIC_LINE2_Y + (wnd_dy - KPSTLIC_WND_DY_0), KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

// case WM_PASTE: // èia neateina
// KpMsgOutF_0("WM_PASTE");
//    break;

   case WM_CLOSE:
      endfl=True;
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl=True;
      break;

   case WM_COMMAND:
      switch(HIWORD(wParam))
      {
      case EN_UPDATE:
// iðskaidom theKpStAppPtr->m_hLicCodeEdit1 á likusius po Paste
// KP_TRACE("KpStLicDialogProc(): EN_UPDATE");
         KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if((HWND)lParam == theKpStAppPtr->m_hLicCodeEdit1)
         {
            SendMessage(theKpStAppPtr->m_hLicCodeEdit1, WM_GETTEXT, KP_KWD_LEN + 1, (LPARAM)code_buf);
            code_buf[KP_KWD_LEN] = Nul;
            retc = RemoveSpaces(code_buf);
            if(SUCCEEDED(retc))
            {
               pnts = code_buf;
               pntd = strchr(pnts, '-');
               if(pntd)
               {
                  *pntd++ = Nul;
                  SendMessage(theKpStAppPtr->m_hLicCodeEdit1, WM_SETTEXT, 0, (LPARAM)pnts);

                  pnts = pntd;
                  pntd = strchr(pnts, '-');

                  if(pntd) *pntd++ = Nul;

                  SendMessage(theKpStAppPtr->m_hLicCodeEdit2, WM_SETTEXT, 0, (LPARAM)pnts);

                  if(pntd)
                  {
                     pnts = pntd;
// atkandam pirmus 4 simbolius - tam atvejui, jeigu lauke theKpStAppPtr->m_hLicCodeEdit1 jau kaþkas buvo (anksèiau suvestas kodas)
                     while(*pntd && ((pntd - pnts) < 4)) pntd++;
                     if(pntd) *pntd++ = Nul;

                     SendMessage(theKpStAppPtr->m_hLicCodeEdit3, WM_SETTEXT, 0, (LPARAM)pnts);
                  }
               }
            }
         }
         break;

//    case EN_CHANGE:
// KP_TRACE("KpStLicDialogProc(): EN_CHANGE");
//       break;
      }

      switch(LOWORD(wParam))
      {
      case IDCANCEL:
      case IDOK:
      case KPST_ID_SKIP:
         endfl=True;
         break;

//    default:
// KP_TRACE_4("%d %d %lx %lx", HIWORD(wParam), retp, lParam, theKpStAppPtr->m_hLicCodeEdit1);
//       break;
      }
      break;

   default:
// KP_TRACE_1("%d", uMsg);
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// -------------------------------------------
HRESULT KpStApp::EnterLicence(HINSTANCE hInst, bool bUnReg, bool bEntered)
{
HRESULT retc=S_OK;
MSG msg;
int retp;
bool endfl=False;
// unsigned char code_buf[KPST_NUM_OF_KEY_SEGM_CHARS+1+1];
unsigned char code_buf[KPST_NUM_OF_LIC_CHARS + 1];
HWND cur_wnd;
int prod_ver = 0;

   if(hInst == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_hInstance = hInst;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = OpenLicWindow(bUnReg, bEntered);

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      retp=LOWORD(msg.wParam);

      if(SUCCEEDED(retc)) switch(msg.message)
      {
//    case WM_PASTE: // èia neateina
// KpMsgOutF_0("WM_PASTE");
//       break;

      case WM_CHAR:
#if FALSE // #ifdef Debug
{
unsigned char str_buf[100];
sprintf((char *)str_buf, "WM_CHAR %d %c", retp, retp);
KP_TRACE(str_buf);
}
#endif
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId!=0L)
               if(!::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;

         case Tab:
            cur_wnd=GetFocus();

            if(cur_wnd==m_hLicCodeEdit1) SetFocus(m_bShiftFl?m_hLicCancelButton:m_hLicCodeEdit2);
            else if(cur_wnd==m_hLicCodeEdit2) SetFocus(m_bShiftFl?m_hLicCodeEdit1:m_hLicCodeEdit3);
            else if(cur_wnd==m_hLicCodeEdit3) SetFocus(m_bShiftFl?m_hLicCodeEdit2:m_hLicOkButton);
            else if(cur_wnd==m_hLicOkButton) SetFocus(m_bShiftFl?m_hLicCodeEdit2:m_hLicSkipButton);
            else if(cur_wnd==m_hLicSkipButton) SetFocus(m_bShiftFl?m_hLicOkButton:m_hLicCancelButton);
            else if(cur_wnd==m_hLicCancelButton) SetFocus(m_bShiftFl?m_hLicSkipButton:m_hLicCodeEdit1);
            else SetFocus(m_hLicOkButton);
            break;

         case Enter:
//          PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
            PostMessage(NULL, WM_COMMAND, IDCANCEL, 0L);
            break;

         default:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hLicCodeEdit1)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS <= SendMessage(m_hLicCodeEdit1, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)code_buf))
                  SetFocus(m_hLicCodeEdit2);
            }
            else if(cur_wnd==m_hLicCodeEdit2)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS <= SendMessage(m_hLicCodeEdit2, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)code_buf))
                  SetFocus(m_hLicCodeEdit3);
            }
            else if(cur_wnd==m_hLicCodeEdit3)
            {
//             if(KPST_NUM_OF_KEY_SEGM_CHARS <= SendMessage(m_hLicCodeEdit3, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)code_buf))
//                PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            }
            break;
         }
         break;

//    case WM_KEYFIRST:
      case WM_KEYDOWN:

#if FALSE // TRUE // #ifdef Debug
{
unsigned char str_buf[100];
sprintf((char *)str_buf, "WM_KEYDOWN %d %c", retp, retp);
KP_TRACE(str_buf);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
}
#endif
         switch(retp)
         {
         case Shift:
            m_bShiftFl=True;
            break;

         case Dn:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hLicCodeEdit1) SetFocus(m_hLicOkButton);
            else if(cur_wnd==m_hLicCodeEdit2) SetFocus(m_hLicCancelButton);
            else if(cur_wnd==m_hLicCodeEdit3) SetFocus(m_hLicCancelButton);
            else if(cur_wnd==m_hLicCancelButton);
            else SetFocus(m_hLicOkButton);
            break;

         case Up:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hLicOkButton) SetFocus(m_hLicCodeEdit1);
            else if(cur_wnd==m_hLicCancelButton) SetFocus(m_hLicCodeEdit2);
            else if(cur_wnd==m_hLicCodeEdit1);
            else if(cur_wnd==m_hLicCodeEdit2);
            else if(cur_wnd==m_hLicCodeEdit3);
            else SetFocus(m_hLicOkButton);
            break;
         }
         break;

      case WM_KEYUP:
#if FALSE // #ifdef Debug
{
unsigned char str_buf[100];
sprintf((char *)str_buf, "WM_KEYDUP %d %c", retp, retp);
KP_TRACE(str_buf);
}
#endif
         if(retp==Shift)
         {
            m_bShiftFl=False;
         }
         break;

      case WM_COMMAND:
//       switch(HIWORD(msg.wParam))
//       {
//       case EN_UPDATE: // èia neateina
// KP_TRACE("KpStApp::EnterLicence(): EN_UPDATE");
//          break;
//
//       case EN_CHANGE: // èia neateina
// KP_TRACE("KpStApp::EnterLicence(): EN_CHANGE");
//          break;
//       }

         switch(retp)
         {
         case KPST_ID_SKIP:
         case IDOK:

//          m_iLicCode1=0;
//          m_iLicCode2=0;
//          m_iLicCode3=0;
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE1);
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE2);
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE3);

            KP_ASSERT((m_hLicCodeEdit1 != NULL) && (m_hLicCodeEdit2 != NULL) && (m_hLicCodeEdit3 != NULL), KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc))
            {
               SendMessage(m_hLicCodeEdit1, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)code_buf);
               code_buf[KPST_NUM_OF_KEY_SEGM_CHARS] = Nul;
               strcat(code_buf, "-");
               SendMessage(m_hLicCodeEdit2, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)(code_buf + strlen(code_buf)));
               code_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 2 + 1] = Nul;
               strcat(code_buf, "-");
               SendMessage(m_hLicCodeEdit3, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)(code_buf + strlen(code_buf)));
               code_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 3 + 2] = Nul;
            }

            if(SUCCEEDED(retc)) retc = ParseLicCodeHigh(code_buf);

            if(SUCCEEDED(retc)) endfl = True;
            else
            {
               KpMsgOut(KPST_MSG_BLOGAS_LIC_KODAS, IDI_ERROR, KP_MB_TESTI);
               SetFocus(m_hLicCodeEdit3);
               retc = S_OK;
            }
            break;

         case IDCANCEL:
            endfl=True;
            retc=KP_E_CANCEL;
            break;

//       default:
// KP_TRACE_1("%d", retp);
//          break;
         }
         break;

      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
         endfl=True;
         retc=KP_E_CANCEL;
         break;

//    case WM_PAINT:
//    case WM_TIMER:
//       break;
//    default:
// KP_TRACE_1("%d", msg.message);
//       break;
      }

   } while((!endfl) && SUCCEEDED(retc));

   if(m_hLicDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hLicDialogWindow)))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }
   m_hLicDialogWindow=NULL;

   if((msg.message==WM_COMMAND) && (retp==KPST_ID_SKIP) && SUCCEEDED(retc))
      retc=KP_E_SKIP;

return(retc);
}
