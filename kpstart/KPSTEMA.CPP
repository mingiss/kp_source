// ---------------------------
// kpstema.cpp
// apsimetinetojas AcroRead32.exe, kad nustatytu defaultini Save As folderi
//
// kpstema.exe kopijuojamas i AcroRd32.exe // anksciau buvo i ema.exe
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"
#include "res_com.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpstap.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
KpCommonApp theApp;
int SortMode=KP_LNG_LIT;
                 

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     
#ifndef Debug
                               lpCmdLine
#endif                               
                               ,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
OPENFILENAME op_fn_str;
unsigned char filters[100];
unsigned char *pntd;
const unsigned char *pnts;
int par_cnt;
HCURSOR cur_sav=NULL;
static unsigned char out_file[KP_MAX_FNAME_LEN + 1];

//-----------------
   if(SUCCEEDED(retc)) retc=theApp.InitCommonApp(hInstance,
#ifdef Debug
      "c:\\arkim\\rezultatai"
#else      
      lpCmdLine
#endif      
      );

   if(SUCCEEDED(retc)) par_cnt=CountRecListEntries(theApp.m_plCmdLineArgs);
   if((par_cnt!=1) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      op_fn_str.lStructSize=sizeof(op_fn_str);
      op_fn_str.hwndOwner=HWND_DESKTOP;
      op_fn_str.hInstance=hInstance;

      pntd=filters;
            
      strcpy(pntd, KPSTEDI_REZ_FILES); // "Text (Accessible) (*.txt)" // "Rezultat¸ failai"
      pntd+=strlen(pntd)+1;
      strcpy(pntd, KPST_REZ_FILE_FILTER);
      pntd+=strlen(pntd)+1;
      
      strcpy(pntd, KP_MSG_ALL_FILES);
      pntd+=strlen(pntd)+1;
      strcpy(pntd, "*.*");
      pntd+=strlen(pntd)+1;
      
      *(pntd++)=Nul;
      *(pntd++)=Nul;
      op_fn_str.lpstrFilter=(const char *)filters; 

      op_fn_str.lpstrCustomFilter=NULL;
      op_fn_str.nMaxCustFilter=0; 
      op_fn_str.nFilterIndex=1; 

      strncpy(out_file, KPST_REZ_FILE_NAME /* "rezultatai.txt" */ /* KPST_REZ_FILE_FILTER */, KP_MAX_FNAME_LEN);
      out_file[KP_MAX_FNAME_LEN] = Nul;
      op_fn_str.lpstrFile = out_file;
      op_fn_str.nMaxFile = KP_MAX_FNAME_LEN; 

      op_fn_str.lpstrFileTitle=NULL; 
      op_fn_str.nMaxFileTitle=0; 

// programos parametras - pradinis aplankas
      op_fn_str.lpstrInitialDir=(const char *)theApp.m_plCmdLineArgs->GetValue(); // "c:\\arkim\\rezultatai";

      op_fn_str.lpstrTitle=(const char *)KPST_EMA_WNAME; // "Save As"; // "Pasirinkite rezultatø failà"; 
      op_fn_str.Flags=0;        

      op_fn_str.nFileOffset=(WORD)strlen(op_fn_str.lpstrInitialDir); 

      pnts=(const unsigned char *)strchr(op_fn_str.lpstrFile, '.');
      if(pnts!=NULL) op_fn_str.nFileExtension=pnts-(const unsigned char *)op_fn_str.lpstrFile+1; 
      else op_fn_str.nFileExtension=(int)strlen(op_fn_str.lpstrFile);

      op_fn_str.lpstrDefExt=(const char *)KPST_REZ_FILE_FILTER+2; // "txt"
      op_fn_str.lCustData=NULL; 
      op_fn_str.lpfnHook=NULL; 
      op_fn_str.lpTemplateName=NULL; 


      if(!GetSaveFileName(&op_fn_str))
      {
         retc=KP_E_CANCEL;
//       retc=KpErrorProc.OutputErrorMessage(retc, CommDlgExtendedError(), True, __FILE__, __LINE__, 0L);
      }
      
   } // if(SUCCEEDED(retc))  

return(RET_CODE(retc));
}
