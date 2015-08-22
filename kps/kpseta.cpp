// ------------------------------------------
// kpseta.cpp  set file attributes
//
// kpseta.exe kopijuojamas i seta.exe
//


// ------------------------------------------
#include "envir.h"

#include <windows.h>
#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpcapp.h"
#include "kpwindow.h"
#include "kperr.h"


// --------------------------------------------
KpCommonApp theApp;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


//--------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
DWORD attribute=FILE_ATTRIBUTE_NORMAL;
const unsigned char *file_ptr=NULL;
const unsigned char *attr_ptr=NULL;
RecListEntry_tag *next_par;
FILE *mcl_file=NULL;
unsigned char fname_buf[KP_MAX_FNAME_LEN+1];
unsigned char *pnts;
unsigned char attr_ch;

   if(SUCCEEDED(retc)) retc=theApp.InitCommonApp(hInstance, lpCmdLine);
   
   if(SUCCEEDED(retc)) if(theApp.m_plCmdLineArgs==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) file_ptr=(const unsigned char *)theApp.m_plCmdLineArgs->GetValue();
   if((file_ptr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// KpMsgOut(file_ptr, IDI_ASTERISK, KP_MB_TESTI);

   if(SUCCEEDED(retc)) next_par=theApp.m_plCmdLineArgs->GetNextEntry();
   if((next_par==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) attr_ptr=(const unsigned char *)(next_par->GetValue());
   if((attr_ptr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(attr_ptr)!=1)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, attr_ptr, True, __FILE__, __LINE__, 0L);

// ((char *)attr_ptr)[0]=ctolower(attr_ptr[0]);
// KpMsgOut(attr_ptr, IDI_ASTERISK, KP_MB_TESTI);

   if(SUCCEEDED(retc)) attr_ch=ctolower(attr_ptr[0]);

#if FALSE
   if((iWindowsVersion>=WinNT35c) && SUCCEEDED(retc)) switch(attr_ch)
   {
      case 'a': attr_ch='h'; break; // arba attr_ch='r';
      case 'h': attr_ch='a'; break;
      case 'r': attr_ch='s'; break;
      case 's':
      default:
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         break;
   }
#endif

   if(SUCCEEDED(retc)) switch(attr_ch)
   {
      case 'a': attribute=FILE_ATTRIBUTE_ARCHIVE; break;
      case 'h': attribute=FILE_ATTRIBUTE_HIDDEN; break;
      case 'r': attribute=FILE_ATTRIBUTE_READONLY; break;
      case 's': attribute=FILE_ATTRIBUTE_SYSTEM; break;
      default:
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         break;
   }

   if(SUCCEEDED(retc))
   {
      if(file_ptr[0]!='@')
      {
         if(!SetFileAttributes((const char *)file_ptr, attribute))
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, file_ptr, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         mcl_file=fopen((const char *)file_ptr+1, "r");
         if(mcl_file==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, file_ptr, True, __FILE__, __LINE__, 0L);
         
         while(SUCCEEDED(retc))
         {
            fgets((char *)fname_buf, KP_MAX_FNAME_LEN, mcl_file);
            if(feof(mcl_file)) retc=KP_E_EOF;
            if(SUCCEEDED(retc)) if(ferror(mcl_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
            
            if(SUCCEEDED(retc))
            {
               pnts=strchr(fname_buf, '\n');
               if(pnts!=NULL) *pnts=Nul;
               if(!SetFileAttributes((const char *)fname_buf, attribute))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, fname_buf, False, __FILE__, __LINE__, 0L);
            }
         }         

         if(mcl_file!=NULL) fclose(mcl_file);
         mcl_file=NULL;
                  
         if(retc==KP_E_EOF) retc=S_OK;
      }
   }

return(RET_CODE(retc));
}
