// ---------------------------
// kpstedm.cpp
// aplikacijos paleidimo kpstart.exe .ini failo redagavimas
//

// -----------------------------------------
// #define KPSTEDI_EDITOR

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
#include "kphp11y.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
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


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = 
#if KPSTEDI_MODE & USER_MODE
"edini"; 
#else
"kpstedf";
#endif
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl=False;

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
KpErrorProcClass KpErrorProc(True, 71);
KpStApp theApp;
                 

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
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
DWORD retw;
unsigned char ini_file_name[KP_MAX_FNAME_LEN+1];
OPENFILENAME op_fn_str;
unsigned char filters[100];
unsigned char *pntd;
unsigned char *fname;
const unsigned char *pnts;
int par_cnt;
HCURSOR cur_sav=NULL;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
KpTreeEntry *next_entry;
bool check_flash = False;
const unsigned char *val_ptr = NULL;
long flash_id = 0L;         
int st_pos = 0;
int ii;
KpStEditActions action;
unsigned char num_buf[MAX_64BIT_HEX_DIGITS /* MAX_LONG_DIGITS */ + 1];
unsigned char flash_lic[KP_KWD_LEN + 1];
static unsigned char in_line[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char user_data[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char user_data_tmp[KP_MAX_FILE_LIN_WDT + 1];
fstream in_file;

   if(StackTop == NULL) StackTop = &nCmdShow;

   flash_lic[0] = Nul;
   
//-----------------
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

//-----------------
// siaip bus veliau - iskvies theApp.InitStApp, bet reikia dabar - lpCmdLine parsinimui
   if(SUCCEEDED(retc)) retc = theApp.InitCommonApp(hInstance, lpCmdLine);

   if(SUCCEEDED(retc))
   {
      cur_sav=SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      if(cur_sav==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
                             
   par_cnt=0;
   if((theApp.m_plCmdLineArgs) && SUCCEEDED(retc)) retc=theApp.m_plCmdLineArgs->CountEntries(&par_cnt, 0, NULL);
        
   if(SUCCEEDED(retc))
   {
      if(par_cnt>=1)
      {
         strncpy(ini_file_name, (const unsigned char *)(theApp.m_plCmdLineArgs->GetValue()),
            KP_MAX_FNAME_LEN);
         ini_file_name[KP_MAX_FNAME_LEN]=Nul;
      }
      else
      {
         if(SUCCEEDED(retc))
         {
            ini_file_name[0]=Nul;
//          strcpy(ini_file_name, KPSTEDI_INIT_DIR);
            strcat(ini_file_name, KPST_INI_FILE_FILTER);
         }
   
         if(SUCCEEDED(retc))
         {
            op_fn_str.lStructSize=sizeof(op_fn_str);
            op_fn_str.hwndOwner=HWND_DESKTOP;
            op_fn_str.hInstance=hInstance;

            strcpy(filters, KPSTEDI_INI_FILTER_NAME);
            pntd = filters + strlen(filters)+1;
            strcpy(pntd, KPST_INI_FILE_FILTER);
            pntd += strlen(pntd) + 1;
            *(pntd++) = Nul;
            *(pntd++) = Nul;
            op_fn_str.lpstrFilter = (const char *)filters; 

            op_fn_str.lpstrCustomFilter = NULL;
            op_fn_str.nMaxCustFilter = 0; 
            op_fn_str.nFilterIndex = 1; 
            op_fn_str.lpstrFile = (char *)ini_file_name; 
            op_fn_str.nMaxFile = KP_MAX_FNAME_LEN; 
            op_fn_str.lpstrFileTitle = NULL; 
            op_fn_str.nMaxFileTitle = 0; 
      
            op_fn_str.lpstrInitialDir = KPSTEDI_INIT_DIR; 
      
            op_fn_str.lpstrTitle = (const char *)KPSTEDI_INI_FILE_PROMPT; 
            op_fn_str.Flags = 0;        
      
            op_fn_str.nFileOffset = (WORD)strlen(op_fn_str.lpstrInitialDir); 
      
            pnts = (const unsigned char *)strchr(op_fn_str.lpstrFile, '.');
            if(pnts!=NULL) op_fn_str.nFileExtension=pnts-(const unsigned char *)op_fn_str.lpstrFile+1; 
            else op_fn_str.nFileExtension = (int)strlen(op_fn_str.lpstrFile);

            op_fn_str.lpstrDefExt = (const char *)KPST_INI_FILE_FILTER+2; // "ini"; 
            op_fn_str.lCustData = NULL; 
            op_fn_str.lpfnHook = NULL; 
            op_fn_str.lpTemplateName = NULL; 


            if(!GetOpenFileName(&op_fn_str))
            {
               retc=KP_E_CANCEL;
//             retc=KpErrorProc.OutputErrorMessage(retc, CommDlgExtendedError(), True, __FILE__, __LINE__, 0L);
            }
         }
      
      } // else // if(par_cnt>=1)
      
   } // if(SUCCEEDED(retc))  

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_file_name, lpCmdLine, KpStEditMode);
                   
   if(SUCCEEDED(retc)) retc=theApp.GetIniCheckFlash(&check_flash);
   
   if(SUCCEEDED(retc))
   {
      if(par_cnt>=2) 
      {
         next_entry = NULL;
         if(SUCCEEDED(retc)) next_entry = theApp.m_plCmdLineArgs->m_pFirstChild;
         for(ii = 1; (ii < par_cnt) && SUCCEEDED(retc); ii++)
         { 
            if((next_entry == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         
            if(SUCCEEDED(retc))
            {
               val_ptr = (const unsigned char *)(next_entry->GetValue());
               if(val_ptr == NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// KpMsgOut(val_ptr, IDI_ASTERISK, KP_MB_TESTI);

            }         

            if(SUCCEEDED(retc))
            {
               pnts = val_ptr;
            
               action = KpStEditRezFName; 
               if(check_flash) action = KpStEditFlashId; 

               if(*pnts == '-')
               {
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | BOUND_MODE)
                  pnts++;
                  switch(*pnts++)
                  {
#  if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
                  case 'r': action = KpStEditRezFName; break;
                  case 's': action = KpStEditRegURL; break;
#  endif                  
#  if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
                  case 'f': action = KpStEditFlashId; break;
                  case 'p': action = KpStEditFlashLic; break;
#  endif                  
#  if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | BOUND_MODE)
                  case 'u': action = KpStEditUserData; break;
#  endif                  
                  default:
#endif
                     retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | BOUND_MODE)
                     break;
                  }
#endif
               }
            }

            if(SUCCEEDED(retc)) switch(action)
            {
            case KpStEditRezFName:
               retc = theApp.SetIniRezFName(pnts);
               break;
               
            case KpStEditRegURL:
               retc = theApp.SetIniRegURL(pnts);
               break;
            
            case KpStEditFlashLic:
               strncpy(flash_lic, pnts, KP_KWD_LEN);
               flash_lic[KP_KWD_LEN] = Nul;
               retc = theApp.SetIniAdminPwd(pnts);
               break;
            
            case KpStEditFlashId:
               st_pos = strlen(pnts) - MAX_LONG_HEX_DIGITS;
               if(st_pos < 0) st_pos = 0;

               strcpy(num_buf, pnts + st_pos);
               if(strcmp(num_buf, "*") == 0) // -f* atmintuko flash id ištraukti iš failo atmintukai.txt pagal lic. kodą (parametro -p)
               {
                  flash_id = 0;
                  
                  KP_ASSERT(flash_lic[0], E_INVALIDARG, (const unsigned char *)KPSTEDI_NO_FLASH_LIC, True); // atmintuko lic. parametras -p turi eiti prieš -f*

#if FALSE // flash id. tiesiai iš lic. kodo be fizinio atmintuko pagamint neišeis, reikia pid, vid ir vol. size – trauksim iš atmintukai.txt
                  if(SUCCEEDED(retc)) pnts = strchr(flash_lic, '-');
                  KP_ASSERT(pnts, E_INVALIDARG, flash_lic, True);
                  if(SUCCEEDED(retc))
                  { 
                     pnts++;
                     pntd = strchr(pnts, '-');
                  }
                  KP_ASSERT(pntd, E_INVALIDARG, flash_lic, True);
                  if(SUCCEEDED(retc)) *pntd = Nul;
...
#else
                  in_file.open((const char *)KPST_FLASH_REG_FILE_NAME, ios::in);
                  KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, KPST_FLASH_REG_FILE_NAME, False);
                  if(SUCCEEDED(retc))
                  {
                     while(SUCCEEDED(retc))
                     {
                        in_file.getline(in_line, KP_MAX_FILE_LIN_WDT);
                        in_line[KP_MAX_FILE_LIN_WDT] = Nul;
                     
                        if(in_file.eof()) retc = KP_E_EOF;
                        KP_ASSERT(!in_file.fail(), KP_E_FERROR, KPST_FLASH_REG_FILE_NAME, False);
                        if(SUCCEEDED(retc))
                        {
                           pnts = strstr(in_line, flash_lic);
                           if(pnts)
                           { 
// 0M1-31944-3515	59188337[2032B657]	2010.12.08	MT10_v2.01.1 
                              pnts = strchr(pnts, '[');
                              KP_ASSERT(pnts, KP_E_FILE_FORMAT, in_line, True);
                              if(SUCCEEDED(retc))
                              {
                                 pnts++;
                                 sscanf((char *)pnts, "%lx", &flash_id);
                              }
                              break;                     
                           }
                        }
                     }  
                     if(retc == KP_E_EOF) retc = S_OK;
                     KP_ASSERT(flash_id, KP_E_KWD_NOT_FOUND, flash_lic, True);
                     
                     in_file.close();
                  }  
#endif                  
               }
               else
               {                
                  retc = ForceTextToHex(num_buf); // nereikia, čia jau ir taip turi būti teisingas hex, ne atmintukinis id tekstas
                  if(SUCCEEDED(retc)) sscanf((const char *)num_buf, "%lx", &flash_id);
               }

               if(SUCCEEDED(retc)) retc = theApp.SetIniFlashId(flash_id);
               break;
            
            case KpStEditUserData:
               KP_ASSERT(strlen(pnts) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, pnts, True);
               if(SUCCEEDED(retc)) strcpy(user_data, pnts);

// --------------------- keičiam makrokomandas {file:...} nurodyto failo paskutinės eilutės turiniu            
               while(SUCCEEDED(retc))
               {
                  fname = strstr(user_data, KPST_FNAME_SHORTCUT_FILE); // "{file:" 
                  if(fname == null) break;               
               
                  *fname = Nul;
                  fname += strlen(KPST_FNAME_SHORTCUT_FILE); // parametro pradžia – failo vardas
                  pntd = strchr(fname, '}'); // galas - parametro uodega
                  KP_ASSERT(pntd, E_INVALIDARG, fname, True);
                  if(SUCCEEDED(retc)) *pntd++ = Nul;
                  
                  if(SUCCEEDED(retc)) in_line[0] = Nul;
                  
// pagaminam pirmą nulinį varinatą, jeigu kartais failas būtų tuščias
                  KP_ASSERT(strlen(user_data) + strlen(in_line) + strlen(pntd) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
                  if(SUCCEEDED(retc))
                  {
                     strcpy(user_data_tmp, user_data);
                     strcat(user_data_tmp, in_line);                   
                     strcat(user_data_tmp, pntd);
                  }
// skaitom failą
                  if(SUCCEEDED(retc))
                  {
                     in_file.open((const char *)fname, ios::in);
                     KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, fname, False);
                     if(SUCCEEDED(retc))
                     {
                        while(SUCCEEDED(retc))
                        {
                           in_file.getline(in_line, KP_MAX_FILE_LIN_WDT);
                           in_line[KP_MAX_FILE_LIN_WDT] = Nul;
                     
                           if(in_file.eof()) retc = KP_E_EOF;
                           KP_ASSERT(!in_file.fail(), KP_E_FERROR, fname, False);
                           KP_ASSERT(strlen(user_data) + strlen(in_line) + strlen(pntd) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
                           if(SUCCEEDED(retc))
                           {
                              strcpy(user_data_tmp, user_data);
                              strcat(user_data_tmp, in_line);                   
                              strcat(user_data_tmp, pntd);
                           }
                        }
                        if(retc == KP_E_EOF) retc = S_OK;
                        
                        in_file.close();
                     }
                  }
                  
                  if(SUCCEEDED(retc)) strcpy(user_data, user_data_tmp);
               }
// ----
               if(SUCCEEDED(retc)) retc = theApp.SetIniUserData(user_data);
               break;
            
            default:
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               break;
            }
            
            if(SUCCEEDED(retc)) next_entry = next_entry->m_pFirstChild;

         } // for(ii = 1; ii < par_cnt; ii++)
         
         if(SUCCEEDED(retc)) retc=theApp.SaveIni();
         
      }
      else // if(par_cnt>=2)
      {
         if((!KpstEdiDialogPtr) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         
#if KPSTEDI_MODE & OWNER_MODE
// iškelta į KpStEdiDlg::DoEdit() WM_COMMAND IDOK
//       if(SUCCEEDED(retc)) retc = theApp.AskUserPwd();
//       if(SUCCEEDED(retc)) retc = theApp.AskUserPUK();
#endif         

         if(SUCCEEDED(retc)) retc = KpstEdiDialogPtr->OpenWindow((const unsigned char *)"");

         if(cur_sav != NULL) SetCursor(cur_sav);
         cur_sav = NULL;

         if(SUCCEEDED(retc))
         {
            retc = KpstEdiDialogPtr->DoEdit(0);
         /* if(SUCCEEDED(retc)) retc = */ KpstEdiDialogPtr->CloseWindow();
         }
      }
   
   } // if(SUCCEEDED(retc))             
                      
   if(SUCCEEDED(retc)) retc = theApp.GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT)) // po edini.exe
      retc = theApp.InitAcroSaveAs();

   if(cur_sav != NULL) SetCursor(cur_sav);
   cur_sav = NULL;

#if (KPSTEDI_MODE & OWNER_MODE)
// iškelta į KpStEdiDlg::DoEdit() WM_COMMAND IDOK
// if(SUCCEEDED(retc)) KpMsgOut(KPSTEDI_USER_DATA_CHANGED, IDI_ASTERISK, KP_MB_TESTI);
#endif

// /* if(SUCCEEDED(retc)) */ retc0=app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0;
   KP_DELETE(KpstEdiDialogPtr);

   retw = RET_CODE_WIN(retc);

return(retw);
}
