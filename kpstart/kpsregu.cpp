// ---------------------------
// kpsregu.cpp
// kpstart.exe duomenu surinkimas
// vietoj surinkimas_xxx.bat
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>

#include "kpstdlib.h"
#include "kpstdio.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpsock.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kpwindow.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "kpstedi.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
KpStApp theApp;
KpStApp *theKpStAppPtr = static_cast<KpStApp *> (&theApp);


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}

                 
// -----------------------------------------
HRESULT AddFile(const unsigned char *lpszCurFileName, FILE *pOutFile, const unsigned char *lpszOutFileName, int *piFileCnt, int *piLineCnt)
{
unsigned char *file_buf=NULL;
HRESULT retc=S_OK;
int ii;
long file_len;

   if((lpszCurFileName==NULL) || (pOutFile==NULL) || (piFileCnt==NULL) || (piLineCnt==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      
   if(SUCCEEDED(retc))
   {   
      file_buf=NULL;
      retc=ReadFileContents(lpszCurFileName, &file_buf, &file_len, False, False);
      
      if(SUCCEEDED(retc))
      {     
         (*piFileCnt)++;
         ii=0;
// neskaiciuoja tusciu eiluciu, nereikalauja paskutines eilutes pabaigos
         retc=CountStrings(&ii, file_buf, lpszEols, False);
         if(SUCCEEDED(retc)) (*piLineCnt)+=ii-1;
      }
      
      if(SUCCEEDED(retc))
      {     
         fputs((const char *)file_buf, pOutFile);
         if(feof(pOutFile) || ferror(pOutFile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
      }
      else retc=S_OK;
   
      KP_DELETE(file_buf);
   }

return(retc);
}
   
                 
/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK; 
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
unsigned char dat_fname[KP_MAX_FNAME_LEN+1];
unsigned char *ini_fname_ptr;
unsigned char filters[100];
unsigned char cur_fname[KP_MAX_FNAME_LEN+1];
unsigned char my_docs_path[KP_MAX_FNAME_LEN+1];
WIN32_FIND_DATA find_data;
HANDLE fhandle;
OPENFILENAME op_fn_str;
unsigned char *pntd;
FILE *out_file=NULL;
int file_cnt=0;
int line_cnt=0;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
const unsigned char *rez_file_ptr;
int retv;
unsigned char str_buf[100];
int rep_count=0;


   if(((theKpStAppPtr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      
// ------------------------------- .ini ir bendras .dat failas
   if(SUCCEEDED(retc)) retc=GetAppName(ini_fname);

   if(SUCCEEDED(retc))
   {             
      strlwr(ini_fname);
      ini_fname_ptr=strstr(ini_fname, ".exe");
      if(ini_fname_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ini_fname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      *ini_fname_ptr=Nul;

      do
      {                       
         if(*(--ini_fname_ptr)=='\\') break;
      } while(ini_fname_ptr>ini_fname);
      if(*ini_fname_ptr=='\\') ini_fname_ptr++;

      strcpy(dat_fname, ini_fname_ptr);

      strcat(ini_fname_ptr, ".ini");
      strcat(dat_fname, ".dat");
   }


// --------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1. InitStApp", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname_ptr, lpCmdLine, KpStRegMode);

// ------------------------------- sukeiciam rez. file name su bendru dat. file name
   strcpy(rez_fname, theKpStAppPtr->m_Ini.lpszRezFName);
   strcpy(theKpStAppPtr->m_Ini.lpszRezFName, dat_fname);


// ----------------------------- .dat failo vardo rankinis patikslinimas
   if(SUCCEEDED(retc))
   {
      op_fn_str.lStructSize=sizeof(op_fn_str);
      op_fn_str.hwndOwner=HWND_DESKTOP;
      op_fn_str.hInstance=hInstance;

      strcpy(filters, "Rezultatø rinkmenos");
      pntd=filters+strlen(filters)+1;
      strcpy(pntd, "*.dat");
      pntd+=strlen(pntd)+1;
      *(pntd++)=Nul;
      *(pntd++)=Nul;
      op_fn_str.lpstrFilter=(const char *)filters; 

      op_fn_str.lpstrCustomFilter=NULL;
      op_fn_str.nMaxCustFilter=0; 
      op_fn_str.nFilterIndex=1; 
      op_fn_str.lpstrFile=(char *)theKpStAppPtr->m_Ini.lpszRezFName; 
      op_fn_str.nMaxFile=KP_MAX_FNAME_LEN; 
      op_fn_str.lpstrFileTitle=NULL; 
      op_fn_str.nMaxFileTitle=0; 
      
      op_fn_str.lpstrInitialDir=KPSTEDI_INIT_DIR; 
      
      op_fn_str.lpstrTitle="Pasirinkite rezultatø kaupimo rinkmenà"; 
      op_fn_str.Flags=0;        
      
      op_fn_str.nFileOffset=(WORD)strlen(KPSTEDI_INIT_DIR); 
      
      pntd=strchr(theKpStAppPtr->m_Ini.lpszRezFName, '.');
      if(pntd!=NULL) op_fn_str.nFileExtension=pntd-theKpStAppPtr->m_Ini.lpszRezFName+1; 
      else op_fn_str.nFileExtension=(int)strlen(theKpStAppPtr->m_Ini.lpszRezFName);

      op_fn_str.lpstrDefExt="dat"; 
      op_fn_str.lCustData=NULL; 
      op_fn_str.lpfnHook=NULL; 
      op_fn_str.lpTemplateName=NULL; 


      if(!GetOpenFileName(&op_fn_str))
      {
         retc=KP_E_CANCEL;
//       retc=KpErrorProc.OutputErrorMessage(retc, CommDlgExtendedError(), True, __FILE__, __LINE__, 0L);
      }
   }


// -------------------- collect data
   rep_count=0;
   do
   {
      out_file=fopen((const char *)theKpStAppPtr->m_Ini.lpszRezFName, "a");
      if(out_file==NULL)
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, theKpStAppPtr->m_Ini.lpszRezFName, True, __FILE__, __LINE__, 0L);
       
         if((++rep_count)<3) retc=KpSleep(1000, HWND_DESKTOP);
         else
         {
            retc=/* m_pRezFNameDialog-> */ KpstEdiDialog.OpenWindow((const unsigned char *)"Negaliu atverti rezultatø rinkmenos.");
            if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */KpstEdiDialog.DoEdit(1000);
         }
      }
   
   } while((out_file==NULL) && SUCCEEDED(retc));
   
   /* m_pRezFNameDialog-> */ KpstEdiDialog.CloseWindow();
    
// ---------------- C:\Bebras\rezX.dat    
   if(SUCCEEDED(retc))
   {
      if(strchr(rez_fname, '\\')==NULL)
      {
         strcpy(cur_fname, "C:\\Bebras\\");
         strcat(cur_fname, rez_fname);
      }
      else
         strcpy(cur_fname, rez_fname);

      retc=AddFile(cur_fname, out_file, theKpStAppPtr->m_Ini.lpszRezFName, &file_cnt, &line_cnt);
   }
                  
// ---------------- ...\My Documents\*\rezX.dat    
   if(SUCCEEDED(retc))
   {
      rez_file_ptr=rez_fname;
      do
      {
         pntd=strchr(rez_file_ptr, '\\');
         if(pntd) rez_file_ptr=pntd+1;
      } while(pntd);
      
      retc=GetLocalPath(my_docs_path, KP_My_Documents);
   }

   if(SUCCEEDED(retc))
   {
      if(iWindowsVersion<WinNT35c)
      {    
         strcpy(cur_fname, my_docs_path);
         strcat(cur_fname, rez_file_ptr);
         retc=AddFile(cur_fname, out_file, theKpStAppPtr->m_Ini.lpszRezFName, &file_cnt, &line_cnt);
      }
      else
      {                            
         pntd=my_docs_path+strlen(my_docs_path);
         while(pntd>my_docs_path) if(*(--pntd)=='\\') break;
         while(pntd>my_docs_path) if(*(--pntd)=='\\') break;
         while(pntd>my_docs_path) if(*(--pntd)=='\\') break;
         *pntd=Nul;
         
         strcpy(cur_fname, my_docs_path);
         strcat(cur_fname, "\\*");
         
         fhandle=FindFirstFile((const char *)cur_fname, &find_data);

         if(fhandle!=INVALID_HANDLE_VALUE) do
         {
            if(find_data.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
            {     
               strcpy(cur_fname, my_docs_path);
               strcat(cur_fname, "\\");
               strcat(cur_fname, find_data.cFileName);
               strcat(cur_fname, "\\");
               if(iWindowsVersion<Win2000c) strcat(cur_fname, MY_DOCS_PATH_NT_2);
               else strcat(cur_fname, MY_DOCS_PATH_2K_2);
               strcat(cur_fname, rez_file_ptr);
               
               retc=AddFile(cur_fname, out_file, theKpStAppPtr->m_Ini.lpszRezFName, &file_cnt, &line_cnt);
            }   
               
            if(SUCCEEDED(retc))
               if(!FindNextFile(fhandle, &find_data))
               {
                  retv=GetLastError();
                  if(retv!=ERROR_NO_MORE_FILES)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L);
                  fhandle=INVALID_HANDLE_VALUE;
               }
         
         } while((fhandle!=INVALID_HANDLE_VALUE) && SUCCEEDED(retc));
         
      } // else // if(iWindowsVersion<WinNT35c)
   
   } // if(SUCCEEDED(retc))

                 
   if(out_file!=NULL)
   {
      if(fclose(out_file)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, theKpStAppPtr->m_Ini.lpszRezFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=retc0;
      }       
      out_file=NULL;
   }


   sprintf((char *)str_buf, "Prijungta rinkmenø: %d, eiluèiø: %d", file_cnt, line_cnt);
   KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);


#ifdef Debug
#ifdef DebugStop
KpMsgOut("5. Exit", IDI_ASTERISK, KP_MB_BAIGTI);
#endif
#endif

return(RET_CODE(retc));
}

