// ---------------------------
// ListLic.cpp
// Visø ádiegtø licencijø kodø iðvedimas
// Naudojam Lentynos kpstart.ini
//

// -----------------------------------------
// #define LIST_LIC_CONSOLE

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
#if IBSH_SKIN != IBSH_SKIN_SPLASH
#error IBSH_SKIN != IBSH_SKIN_SPLASH
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "ListLic";
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


// -----------------------------------------
#ifdef LIST_LIC_CONSOLE
KpConsole ListLicConsole;
#endif
int line_cnt = 0;
unsigned char log_fname[KP_MAX_FNAME_LEN + 100] = { Nul };
#ifndef LIST_LIC_CONSOLE
KpFStream *log_file = NULL;
#endif

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
#ifdef LIST_LIC_CONSOLE
#define enc_fprintf(...) \
   { \
   static unsigned char str_buf[2000]; \
      sprintf((char *)str_buf, (const char *)__VA_ARGS__); \
      line_cnt++; \
      if(SUCCEEDED(retc)) retc = ListLicConsole.AddString(str_buf); \
   }
#else
#define enc_fprintf(...) \
   { \
   static unsigned char str_buf[2000]; \
      sprintf((char *)str_buf, (const char *)__VA_ARGS__); \
      line_cnt++; \
      *log_file << (const char *)str_buf; \
   }
#endif


void enum_key(HKEY hQueryKey, const char *lpszKeyName, const char *lpszSubKeyName)
{
HRESULT retc = S_OK;
HKEY hKey = NULL;
char key_name[200 + 1];
char sub_key_name[400 + 1];
char class_name[200 + 1];
DWORD key_ix;
DWORD name_len;
DWORD class_len;
LONG retw = ERROR_SUCCESS;
unsigned char prod_name[KP_KWD_LEN + 1];

   prod_name[0] = Nul;
int sub_key_len = strlen(lpszSubKeyName);
   KP_ASSERT(sub_key_len <= KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(prod_name, lpszSubKeyName);

unsigned char *pntd = strstr(prod_name, "_is1");
bool out_fl = (pntd == prod_name + sub_key_len - strlen("_is1"));
   if(out_fl) *pntd = Nul;

   retw = RegOpenKeyEx(hQueryKey, lpszKeyName, 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hKey);
   if(retw != ERROR_SUCCESS)
   {
//    enc_fprintf(out_file, "------------ neatsidaro retw=%ld\n", retw);
   }
   else
   {
// ---------------------------------- enum values
      if(out_fl)
      {
#if FALSE
union
{
   char text[200 + 1];
   DWORD num;
} val_buf;
DWORD dwBufLen;
DWORD dwValType;

         key_ix = 0;
         do
         {
            name_len = 200;
            dwBufLen = 200;

//          retw = RegQueryValueEx(hKey, key_name, NULL, &dwValType,
            retw = RegEnumValue(hKey, key_ix++, key_name, &name_len, NULL, &dwValType, (LPBYTE)&val_buf, &dwBufLen);
            if(retw == ERROR_NO_MORE_ITEMS) break;
            else if(retw != ERROR_SUCCESS)
            {
  //           enc_fprintf(out_file, "--------- neskaito retw=%ld %ld\n", retw, key_ix - 1);
            }
            else switch(dwValType)
            {
//          case REG_DWORD: enc_fprintf("%s: 0x%lx\n", key_name, val_buf.num); break;
            case REG_SZ: enc_fprintf("%s: %s\n", key_name, val_buf.text); break;
//          default: enc_fprintf("%s: ------------- dwValType=%ld\n", key_name, dwValType);
            }

         } while(TRUE); // (retw == ERROR_SUCCESS);
#endif

DWORD val_type;
unsigned char kwd_buf[KP_KWD_LEN + 100];
DWORD kwd_len = KP_KWD_LEN;

#if FALSE
// --------------- produkto versijos pavadinimas – netinka, kai kuriø be prod. pavadinimo
         kwd_len = KP_KWD_LEN;
         retw = RegQueryValueEx(hKey, "DisplayName", NULL, &val_type, kwd_buf, &kwd_len);
         if((retw == ERROR_SUCCESS) && (val_type == REG_SZ)) enc_fprintf(kwd_buf);
#endif

// ---------------- produkto diegimo kelias
         kwd_len = KP_KWD_LEN;
         retw = RegQueryValueEx(hKey, "Inno Setup: App Path", NULL, &val_type, kwd_buf, &kwd_len);
         if((retw == ERROR_SUCCESS) && (val_type == REG_SZ))
         {
// --------------- ieðkom data.dat
unsigned char data_path[KP_KWD_LEN + 100];
            strcpy(data_path, kwd_buf);
            strcat(data_path, "\\data.dat");
FILE *in_file = fopen((const char *)data_path, "r");
            if(in_file != NULL)
            {
// ------------ radom data.dat
               fclose(in_file);

// ------------ skanuojam data.dat
               KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);
#if FALSE
filebuf fb;
KpInStream *in_file_ptr = NULL;

               KP_ASSERT(fb.open((const char *)data_path, ios::in), KP_E_FILE_NOT_FOUND, null, True);
               KP_NEW(in_file_ptr, KpInStream(&fb));
XmlTagPars *dat_rec = NULL;
               if(SUCCEEDED(retc))
               {
                  dat_rec = NULL;
                  retc = theKpStAppPtr->GetKpstFdfDataRec(&dat_rec, in_file_ptr, FdfInputFdf, True);
               }

unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
#if FALSE
XmlTagPars *dat_rec_ptr = NULL;
               dat_rec_ptr = dat_rec;
               while((dat_rec_ptr != NULL) && SUCCEEDED(retc))
               {
unsigned char par_nam[TV_TAG_LEN + 1];
                  retc = dat_rec_ptr->GetCurTextPar(par_nam, par_val);
                  enc_fprintf("%s: %s", par_nam, par_val);

                  if(SUCCEEDED(retc)) retc = dat_rec_ptr->GetNextBrother((KpTreeEntry **)&dat_rec_ptr);
               }
#endif

               if((dat_rec != NULL) && SUCCEEDED(retc))
               { 
                  retc = dat_rec->SeekTextPar("PI", par_val, NULL);
                  if(SUCCEEDED(retc))
                  {
                     enc_fprintf("%s: %s\n", prod_name, par_val);
                  } // if(SUCCEEDED(retc))

               } // if((dat_rec != NULL) && SUCCEEDED(retc))
#endif

               if(SUCCEEDED(retc)) if(SetCurrentDirectory((const char *)kwd_buf))
               {
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetSavedKeyDat(NULL);
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->UnpackInstCode();
int rem_lic_id = 0;
int rem_prod_ver = 0;
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&rem_lic_id, KP11_REM_LICID);
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&rem_prod_ver, KP11_REM_PRODVER);
                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(rem_lic_id, KP11_LICID);
                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(rem_prod_ver, KP11_PRODVER);
                  
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->ReCalcLicCode();
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->UnpackInstCode();
                  
int lic_cod1 = 0;
int lic_cod2 = 0;
int lic_cod3 = 0;
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_cod1, KP11_LIC_CODE1);
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_cod2, KP11_LIC_CODE2);
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_cod3, KP11_LIC_CODE3);

KpStLicPars lic_pars;
                  if(SUCCEEDED(retc)) retc = FormatKeyHex(lic_pars.m_lpszLic1, lic_cod1 /* m_iLicCode1 */);
                  if(SUCCEEDED(retc)) retc = FormatKeyHex(lic_pars.m_lpszLic2, lic_cod2 /* m_iLicCode2 */);
                  if(SUCCEEDED(retc)) retc = FormatKeyHex(lic_pars.m_lpszLic3, lic_cod3 /* m_iLicCode3 */);
                  
                  if(SUCCEEDED(retc)) enc_fprintf("%s: %s-%s-%s\n", prod_name, lic_pars.m_lpszLic1, lic_pars.m_lpszLic2, lic_pars.m_lpszLic3);
               }
               
// ---------
               retc = S_OK;
               
            } // if(in_file != NULL)

         } // if((retw == ERROR_SUCCESS) && (val_type == REG_SZ))

//       enc_fprintf("");

      } // if(out_fl)

// ---------------------------------- enum subkeys
      key_ix = 0;
      do
      {
         name_len = 200;
         class_len = 200;
         retw = RegEnumKeyEx(hKey, key_ix++, key_name, &name_len, NULL, class_name, &class_len, NULL);
         if(retw == ERROR_NO_MORE_ITEMS) break;
         else if(retw != ERROR_SUCCESS)
         {
//          enc_fprintf(out_file, "--------- nesinumeruoja retw=%ld %ld\n", retw, key_ix - 1);
         }
         else
         {
            strcpy(sub_key_name, lpszKeyName);
            strcat(sub_key_name, "\\");
            strcat(sub_key_name, key_name);

            enum_key(hQueryKey, sub_key_name, key_name);
         }

      } while(TRUE); // (retw == ERROR_SUCCESS);
   }

   if(hKey) RegCloseKey(hKey);
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
// -------------------------------
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   if(StackTop == NULL) StackTop = &nCmdShow;

unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];
   GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir);

// -------------------------------
KpStartApp *app_ptr = NULL; // (&theApp); //
   KP_NEW(app_ptr, KpStartApp);
   theKpStAppPtr = app_ptr; // static_cast<KpStApp *> (&theApp);
   KP_ASSERT(app_ptr != NULL, E_POINTER, null, True);
   if(SUCCEEDED(retc)) retc = app_ptr->GetOpenResult();

#if TRUE // FALSE
static unsigned char ini_fname[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStEditMode);
#else
   if(SUCCEEDED(retc)) retc = app_ptr->InitCommonApp(hInstance, lpCmdLine);
#endif
if(FAILED(retc)) KP_ERROR(retc, null);
// KpMsgOutF("%x", retc);


// -------------------------------
   if(SUCCEEDED(retc)) 
   {
#ifdef LIST_LIC_CONSOLE
      log_fname[0] = Nul;
#else      
      strcpy(log_fname, cur_dir);
      strcat(log_fname, "\\");
#endif     
      strcat(log_fname, "ListLic.log");
      
#ifndef LIST_LIC_CONSOLE
      KP_NEW(log_file, KpFStream((const char *)log_fname, ios::out));
#endif
   }
   
const unsigned char *kepure = (const unsigned char *)"Kompiuteryje ádiegti produktai";
#ifdef LIST_LIC_CONSOLE
   if(SUCCEEDED(retc)) retc = ListLicConsole.Init(hInstance, log_fname, kepure);
#endif   
   if(SUCCEEDED(retc)) enc_fprintf("%s:\n\n", kepure);


// -------------------------- skanuojam registrà ir iðvedinëjam
unsigned char str_buf[KP_MAX_FNAME_LEN + 1];

#if FALSE
   if(SUCCEEDED(retc)) for(line_cnt = 0; (line_cnt < 23) && SUCCEEDED(retc); line_cnt++)
   {
      sprintf((char *)str_buf, "Produktas %d", line_cnt);
#  ifdef LIST_LIC_CONSOLE
      if(SUCCEEDED(retc)) retc = ListLicConsole.AddString(str_buf);
#  endif      
   }
#endif

   if(SUCCEEDED(retc)) enum_key(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", "");
   if(SUCCEEDED(retc)) if(app_ptr ->m_plCmdLineArgs != NULL) 
      if(strcmp((unsigned char *)(app_ptr ->m_plCmdLineArgs->GetValue()), "all") == 0)
         enum_key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", ""); // lentyniniø reikia nerodyt

#ifdef LIST_LIC_CONSOLE
   if(SUCCEEDED(retc)) retc = ListLicConsole.DoRefresh();
#endif   

// ------------------------------- laukiam pabaigos
#ifdef LIST_LIC_CONSOLE
   if(SUCCEEDED(retc))
   {
      retc = KpSleep(0L);
      if(retc == KP_E_CANCEL) retc = S_OK;
   }
#endif

/* if(SUCCEEDED(retc)) retc = */ if(app_ptr != NULL){ retc0 = app_ptr->CloseStApp(retc, KP_My_Documents); if(SUCCEEDED(retc)) retc = retc0; }

#ifdef LIST_LIC_CONSOLE
   /* if(SUCCEEDED(retc)) retc = */ retc0 = ListLicConsole.KpConsoleDestructor(); if(SUCCEEDED(retc)) retc = retc0;
#endif

#ifndef LIST_LIC_CONSOLE
   if(SUCCEEDED(retc)) log_file->close();
   KP_DELETE(log_file);
#endif
   
// ------------------------------- á ekranà netilpo – kraunam logo failà á notepadà
   SetCurrentDirectory((const char *)cur_dir);
   if(/* (line_cnt > 24) && */ SUCCEEDED(retc))
   {
      KP_ASSERT(strlen(log_fname) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(str_buf, log_fname);
         retc = StartCmdProcess(str_buf, KPST_CUR_DIR, NULL, NULL, True, SW_SHOWNORMAL);
      }
   }

return(RET_CODE_WIN(retc));
}
