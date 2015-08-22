// ---------------------------
// kpstrsvr.cpp; TevAutoRun.exe, tvarsvr.exe
// flash atmintuko autorun ir autounlock serveris
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>
#include <string>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kpstrsvr"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
#ifdef Debug
bool bServiceFl=False; // True; //    
#else
bool bServiceFl=False; // True; // 
#endif
int iKpstrSvrTimer = 0;


int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};


UINT bActiveDiscs[KP_NUM_OF_DISKS] = 
{
   DRIVE_UNKNOWN, // A:
   DRIVE_UNKNOWN, // B:
   DRIVE_UNKNOWN, // C:
   DRIVE_UNKNOWN, // D:
   DRIVE_UNKNOWN, // E:
   DRIVE_UNKNOWN, // F:
   DRIVE_UNKNOWN, // G:
   DRIVE_UNKNOWN, // H:
   DRIVE_UNKNOWN, // I:
   DRIVE_UNKNOWN, // J:
   DRIVE_UNKNOWN, // K:
   DRIVE_UNKNOWN, // L:
   DRIVE_UNKNOWN, // M:
   DRIVE_UNKNOWN, // N:
   DRIVE_UNKNOWN, // O:
   DRIVE_UNKNOWN, // P:
   DRIVE_UNKNOWN, // Q:
   DRIVE_UNKNOWN, // R:
   DRIVE_UNKNOWN, // S:
   DRIVE_UNKNOWN, // T:
   DRIVE_UNKNOWN, // U:
   DRIVE_UNKNOWN, // V:
   DRIVE_UNKNOWN, // W:
   DRIVE_UNKNOWN, // X:
   DRIVE_UNKNOWN, // Y:
   DRIVE_UNKNOWN, // Z:
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
bool endfl = False;
MSG msg;
int retp;
unsigned char drive_path[10];
UINT drive_type;
int dev;
unsigned char user_name[KP_MAX_FNAME_LEN+1];
DWORD ll;
bool system_user = False;
MSWin32Version vers;
HANDLE find_file;
WIN32_FIND_DATA find_file_data;
#if FALSE
fstream autorun_file;
unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];
unsigned char *val_ptr = NULL;
int kwd_ix;
#endif
unsigned char cmd_str[KP_MAX_FILE_LIN_LEN+100+1];
unsigned char start_in[KP_MAX_FILE_LIN_LEN+100+1];
unsigned char fname[KP_MAX_FILE_LIN_LEN+1];
TevAutorunPars autorun_pars;

// ------------------------------- 
   if(SUCCEEDED(retc)) retc=KpInitWindows(hInstance);
   
// --------------------------------
#ifndef Debug
   if(SUCCEEDED(retc)) bServiceFl=(iWindowsVersion>=WinNT);
#endif

   if(SUCCEEDED(retc))
   {
      vers=iWindowsVersion;
      strcpy(user_name, "Unknown");

      ll = KP_MAX_FNAME_LEN;
      if((vers >= WinNT40c) && SUCCEEDED(retc))
         if(!GetUserName((char *)user_name, &ll))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      user_name[KP_MAX_FNAME_LEN] = Nul;
   }
   if(SUCCEEDED(retc))
   {
      TvStrLwrLat(user_name);
      system_user = (strcmp(user_name, "system") == 0);
      if(system_user) bServiceFl = True;
   }

// --------------------------------
#ifdef Debug
   if(system_user && SUCCEEDED(retc))
      /* retc = */ StartProcess((const unsigned char *)"C:\\Temp\\tvarsvr.bat", KPST_CUR_DIR, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
#endif


// --------------------------------
   if(SUCCEEDED(retc))
   {
      iKpstrSvrTimer = SetTimer(HWND_DESKTOP, KPST_CHK_FLASH_TIMER, KPST_CHK_NEW_FLASH_TIMEOUT, NULL);
      if(iKpstrSvrTimer == 0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// --------------------------------
   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0)
      {
         retc=KP_E_SYSTEM_ERROR;
         KpErrorProc.OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp=LOWORD(msg.wParam);
      }
      
      if(SUCCEEDED(retc)) switch(msg.message)
      {
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
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
            break;
         case IDCANCEL:
//          if(msg.hwnd==m_hDialogWindow) 
               endfl=True;
            break;
         } // switch(retp)
         break;
      
      case WM_TIMER:

         if(retp == iKpstrSvrTimer) 
         {
            for(dev = 0; dev < KP_NUM_OF_DISKS; dev++)
            {
               sprintf((char *)drive_path, "%c:\\", dev+'A');
               drive_type=GetDriveType((const char *)drive_path);

//             if(drive_type != DRIVE_NO_ROOT_DIR)
//                if(!GetVolumeInformation((const char *)drive_path, vol_name, 20, &ser_no, &max_fn_len, &sys_fl, fs_name, 100))
//                   drive_type = DRIVE_NO_ROOT_DIR;

               switch(drive_type)
               {
               case DRIVE_NO_ROOT_DIR /* DRIVE_UNKNOWN */: bActiveDiscs[dev] = drive_type; break;
               
               case DRIVE_REMOVABLE:
               case DRIVE_CDROM:
//             default:
                  if(
                     (bActiveDiscs[dev] == DRIVE_NO_ROOT_DIR)
#ifdef Debug
                     || (dev=='G'-'A')
#endif                     
                    )
                  {
                     strcpy(fname, drive_path);
                     strcat(fname, TEV_AUTORUN_INF_FNAME);
char vol_name[20+1];
unsigned long ser_no;
unsigned long max_fn_len;
unsigned long sys_fl;
char fs_name[KP_MAX_FNAME_LEN+1];

#ifdef Debug
                     if(system_user && SUCCEEDED(retc)) retc = LockFlash(Fl_SetRegAccess);
#endif

                     if(!GetVolumeInformation((const char *)drive_path, vol_name, 20, &ser_no, &max_fn_len, &sys_fl, fs_name, 100))
                     {
#if FALSE // #ifdef Debug
                        KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
                        KpMsgOut(drive_path, IDI_ASTERISK, KP_MB_TESTI);
#endif
                     }
                     else
                     {
                        find_file = FindFirstFile((const char *)fname, &find_file_data);
                        if(find_file == INVALID_HANDLE_VALUE)
                        {
                           retc = KP_E_FILE_NOT_FOUND;
                           ll = GetLastError();
                           if(ll != ERROR_FILE_NOT_FOUND)
                              KpErrorProc.OutputErrorMessage(retc, ll, False, __FILE__, __LINE__, 0L);
                        }
                        else
                           if(!FindClose(find_file))
                              KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                        
                        if(FAILED(retc)) bActiveDiscs[dev] = drive_type;
                        else
                        {
// ----------------------------
// jei paleista "chkvol.exe" - nieko nedaryti, atmintukas tikrinamas
int found;
                           found = GetProcessIdByName((const unsigned char *)"chkvol.exe");
#if FALSE
                           autorun_file.open((const char *)fname, ios_base::in);
                           if(!autorun_file.fail())
                           {
                              if(!found) do
                              {
                                 autorun_file.getline(in_str, KP_MAX_FILE_LIN_LEN);
                                 if(autorun_file.eof() && SUCCEEDED(retc)) retc = KP_E_EOF;        
                                 if(SUCCEEDED(retc)) if(autorun_file.fail())
                                 {
                                    retc = KP_E_FERROR;
                                    KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                                 }

                                 if(SUCCEEDED(retc))
                                 {
                                    val_ptr = strchr(in_str, '=');
                                    if(val_ptr == NULL)
                                    {
                                       if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
                                       if(SUCCEEDED(retc)) retc = strlwr(in_str);
                                       if(SUCCEEDED(retc)) if((in_str[0] != ';') && (in_str[0] != Nul))
                                          if(strcmp(in_str, "[autorun]") != 0)
                                             KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, fname, False, __FILE__, __LINE__, 0L);
                                    }
                                    else
                                    {   
                                       *val_ptr++ = Nul;
                                       if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
                                       if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(val_ptr);
                              
                                       kwd_ix = NoAutoRunIx;
                                       if(SUCCEEDED(retc))
                                       {
                                          retc = GetKwrdIndex(&kwd_ix, in_str, lpszaAutoRunKwds, -1, False, True);
                                          if(retc == KP_E_KWD_NOT_FOUND)    
                                             retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, False, __FILE__, __LINE__, 0L);
                                          else if(SUCCEEDED(retc))
                                          {   

                                             switch(kwd_ix)
                                             {
                                             case OpenIx:
                                                if(!system_user)
                                                {
                                                   sprintf((char *)cmd_str, "%c:", dev+'A');
                                                   if(*val_ptr != '\\') strcat(cmd_str, "\\");
                                                   strcat(cmd_str, val_ptr);
                                                   retc=StartProcess(cmd_str, drive_path /* KPST_CUR_DIR */, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
                                                }
                                                break;
                                       
                                             case ActionIx:
                                                if(system_user) retc = LockFlashStr(val_ptr);
                                                break;
                                             }
                                    
                                          } // else // if(retc == KP_E_KWD_NOT_FOUND)

                                       } // if(SUCCEEDED(retc))

                                    } // else // if(val_ptr == NULL)
                           
                                 } // else // if(autorun_file.fail())

                              } while(SUCCEEDED(retc));
                           
                              retc = S_OK;
                     
                              autorun_file.close();
                  
                           } // if(!autorun_file.fail())
#endif
                           if((!found) && SUCCEEDED(retc))
                           {
                              if(SUCCEEDED(retc)) retc = ParseTevAutorun(drive_path, &autorun_pars);

                              if((autorun_pars.m_lpszOpen[0]) && SUCCEEDED(retc))
                              {
                                 sprintf((char *)cmd_str, "%c:", dev + 'A');
                                 if(autorun_pars.m_lpszOpen[0] != '\\') strcat(cmd_str, "\\");
                                 strcat(cmd_str, autorun_pars.m_lpszOpen);

                                 sprintf((char *)start_in, "%c:", dev + 'A');
                                 if(autorun_pars.m_lpszStartIn[0] != '\\') strcat(start_in, "\\");
                                 strcat(start_in, autorun_pars.m_lpszStartIn);

                                 retc = StartProcess(cmd_str, start_in, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
                              }
                              
                              if((autorun_pars.m_iAction >= 0) && system_user && SUCCEEDED(retc)) 
                                 retc = LockFlash(autorun_pars.m_iAction);
                           }
                     
//---------------
                           if(SUCCEEDED(retc)) bActiveDiscs[dev] = drive_type;

                        } // else // if(FAILED(retc)) // retc = KP_E_FILE_NOT_FOUND; 
                        
                     } // else // if(!GetVolumeInformation((const char *)drive_path, vol_name, 20, &ser_no, &max_fn_len, &sys_fl, fs_name, 100))
                  
                  } // if(bActiveDiscs[dev] == DRIVE_NO_ROOT_DIR)
                  
//                bActiveDiscs[dev] = drive_type;
                     
                  break; // case DRIVE_REMOVABLE:
               
               } // switch(drive_type) 
            
               retc = S_OK;

            } // for(dev = 0; dev < KP_NUM_OF_DISKS; dev++)
            
         } // if(retp==iKpstrSvrTimer)
         
         break; // case WM_TIMER:                                   
      
      }  // if(SUCCEEDED(retc)) switch(msg.message)
   
   } while((!endfl) && SUCCEEDED(retc));

   if(iKpstrSvrTimer) KillTimer(HWND_DESKTOP, iKpstrSvrTimer);
   iKpstrSvrTimer=0;

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}

