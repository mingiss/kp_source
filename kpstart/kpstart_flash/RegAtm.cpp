// ---------------------------
// RegAtm.cpp
// Nupirkto atmintuko susiejimas su pirkusiu vartotoju prieð iðsiunèiant
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
// #include "lzdshn.h"

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

#include "md5.h"

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
#include "iBsht.h"
#include "iBshl.h"
#include "xmln.h"
#include "kpstap.h"


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
#if IBSH_PROJ != IBSH_PROJ_REG_ATM
#error IBSH_PROJ != IBSH_PROJ_REG_ATM
#endif
#if IBSH_SKIN != IBSH_SKIN_MIKO
#error IBSH_SKIN != IBSH_SKIN_MIKO
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "RegAtm";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;

KpStApp theApp;
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_5 + 1]=
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

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
// TODO: perdaryt á dinaminá
#define KPST_REGATM_HTM_BUF_SIZE 100000 // KP_MAX_FILE_LIN_LEN

/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
KpString AI_val_str;

// -------------------------------
   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

// ---------------------------------------------------------------
// sukuriam Gecko dialogo objektus
// ------------------------
iBshFileSys *file_sys = NULL;
   if(SUCCEEDED(retc)) file_sys = new iBshFileSys();
   KP_ASSERT(file_sys != NULL, KP_E_OUTOFMEM, null, True);
   if(SUCCEEDED(retc)) retc = file_sys->GetOpenResult();

   if(SUCCEEDED(retc)) retc = file_sys->OpenFiles(null, XM_VERS_XHTML, CreateNewUniFile);

iBshDlg *dlg_ptr = NULL;
   if(SUCCEEDED(retc)) dlg_ptr = new iBshDlg(file_sys, IBSH_OUT_VERS, UC_PlainText, lpszProdName);
   KP_ASSERT(dlg_ptr != NULL, KP_E_OUTOFMEM, null, True);
   if(SUCCEEDED(retc)) retc = dlg_ptr->GetOpenResult();

// ------------------------
   if(SUCCEEDED(retc)) retc = dlg_ptr->OpenWindow(hKpInstance, False);

// ------------------------------- ieðkom atmintuko
bool found = False;
   if(SUCCEEDED(retc)) do
   {
unsigned char drive_path[10];
      strcpy(drive_path, "A:");
UINT drive_type;

      for(int ii = 'B' /* 'A'*/; (ii <= 'Z') && (!found) && SUCCEEDED(retc); ii++)
      {
         drive_path[0] = ii;
         drive_type = GetDriveType((const char *)drive_path);

         if((drive_type == DRIVE_REMOVABLE) /* || (drive_type == DRIVE_CDROM) */) // DRIVE_CDROM - cd8 formatuotiems atmintukams
         {
            if(GetVolumeInformation((const char *)drive_path, NULL, 0, NULL, NULL, NULL, NULL, 0L))
            {
static unsigned char src_fmask[KP_MAX_FNAME_LEN + 100];
               if(SUCCEEDED(retc))
               {
                  strcpy(src_fmask, drive_path);
                  strcat(src_fmask, "\\*");
               }

// --------------- atidarom aplankø sàraðà
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
               if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)src_fmask, &file_data);
               if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
               {
                  retw = GetLastError();
                  if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
                     KP_ERROR(KP_E_SYSTEM_ERROR, retw);
               }

               if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
               {
// ------- ar aplankas?
                  if((file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && SUCCEEDED(retc))
                  {
KpString data_dat_fname_str;
                     data_dat_fname_str = drive_path;
                     data_dat_fname_str += "\\";
                     data_dat_fname_str += file_data.cFileName;
                     data_dat_fname_str += "\\";
                     data_dat_fname_str += KPST_FDF_DATA_FNAME;
                     retc = KpStApp::GetDataDatVariable(&data_dat_fname_str, (const unsigned char *)"AI", &AI_val_str, False);
                     if(FAILED(retc) && (retc != KP_E_FILE_NOT_FOUND)) KP_ERROR(retc, null);
                     if(SUCCEEDED(retc)) found = True;
                     if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;
                  }

// ---------------- kitas aplankas
                  retw = ERROR_SUCCESS;
                  if(SUCCEEDED(retc))
                     if(!FindNextFile(enumeration, &file_data))
                     {
                        retw = GetLastError();
                        if(retw == ERROR_NO_MORE_FILES)
                        {
                           // retc = KP_E_FILE_NOT_FOUND;
                        }
                        else KP_ERROR(KP_E_SYSTEM_ERROR, retw);
                     }

               } while((!found) && (retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));
            }
         }

      } // for(int ii = 'B' /* 'A'*/; (ii <= 'Z') && (!found) && SUCCEEDED(retc); ii++)


      if(!found) retc = KpMsgOut("Ákiðkite atmintukà", IDI_ASTERISK, KP_MB_GERAI_ATSAUKTI);

   } while((!found) && SUCCEEDED(retc));

// ------------------------------------------ siunèiam uþklausà
   if(SUCCEEDED(retc))
   {
unsigned char get_cmd[KP_MAX_FNAME_LEN + 1];
      strcpy(get_cmd, KPST_USBPIRK_FILE);

      strcat(get_cmd, KPST_USBRAKTAI_RAKTAS); // "?raktas="
      strcat(get_cmd, AI_val_str.ExtractUnsignedValueA());

      strcat(get_cmd, KPST_USBRAKTAI_ID); // "&id="
unsigned char atm_cod_md5[MD5_RES_WDT + TV_TAG_LEN + 1];
      strcpy(atm_cod_md5, AI_val_str.ExtractUnsignedValueA());
      strcat(atm_cod_md5, KPST_USBRAKTAI_ID_TAIL); // "w0r1UkazZ"
unsigned char *hash_ptr = null;
      hash_ptr = (unsigned char *)MD5String((char *)atm_cod_md5);
      KP_ASSERT(hash_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(strlen(hash_ptr) == MD5_RES_WDT, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) strcat(get_cmd, hash_ptr);
      if(hash_ptr != null) free(hash_ptr);
      hash_ptr = null;

KpSocket *sock_ptr = NULL;
      if(SUCCEEDED(retc))
      {
         sock_ptr = new KpSocket();
         KP_ASSERTE(sock_ptr != NULL, KP_E_OUTOFMEM, null, True);
      }
      if(SUCCEEDED(retc)) retc = sock_ptr->GetOpenResult();

      if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_USBPIRK_URL, True);
      if(SUCCEEDED(retc)) retc = sock_ptr->Connect(True);

      if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, get_cmd, True);

PutLogMessage_("WinMain() 1: %s", get_cmd);
PutLogMessage_("WinMain() 2: %s", KPST_USBPIRK_URL);

unsigned char *rcv_buf = null;
long read = KPST_REGATM_HTM_BUF_SIZE;
      if(SUCCEEDED(retc))
      {
         rcv_buf = new unsigned char[KPST_REGATM_HTM_BUF_SIZE + 100];
         KP_ASSERTE(rcv_buf != null, KP_E_OUTOFMEM, null, True);
      }

      if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, True);
      KP_ASSERT(read < KPST_REGATM_HTM_BUF_SIZE, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) rcv_buf[read] = Nul;

fstream out_file((const char *)KPST_USBRAKTAI_FNAME, ios::out);
out_file << rcv_buf;
out_file.close();

      KP_DELETE(sock_ptr);

      KP_DELETEA(rcv_buf);
   }


// ------------------------------- rodom parsiøstà failà
   KP_ASSERT(dlg_ptr != NULL, E_POINTER, null, True);
   KP_ASSERT(dlg_ptr->m_pKpFileSys != NULL, E_POINTER, null, True);
   if(SUCCEEDED(retc)) retc = dlg_ptr->m_pKpFileSys->SearchForEntry(dlg_ptr, KPST_USBRAKTAI_FNAME);

// --------------------
   if(SUCCEEDED(retc)) retc = dlg_ptr->ShowDialog();

   if(SUCCEEDED(retc)) retc = dlg_ptr->DoEdit();

   if(SUCCEEDED(retc)) retc = dlg_ptr->HideDialog();


// ---------------------------------------------------------------
// naikinam Gecko dialogo objektus
   KP_DELETE(dlg_ptr);

   KP_DELETE(file_sys);

// -------------------------------
// if(SUCCEEDED(retc))
   {
HRESULT retc0 = KpFinitWindows();
      if(SUCCEEDED(retc)) retc = retc0;
   }

return(RET_CODE_WIN(retc));
}
