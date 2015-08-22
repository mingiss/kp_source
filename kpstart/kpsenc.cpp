// ---------------------------
// kpsenc.cpp, 
// failo uzkodavimas/atkodavimas
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"

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
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "xmlg.h"
#include "xml8.h"
#include "kpstap.h"
#include "kpsenc.h"


#if Envir!=MSWin32
// #error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
const unsigned char lpszProdName[] = "kpsenc";
int iProdVerGlob=0;
int iUpdNumGlob = -1;
bool bServiceFl=False;

KpErrorProcClass KpErrorProc(True, 71);
KpsEncApp theApp;

// -----------------------------------------
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
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int main(int argc, char** argv)
// int APIENTRY WinMain(HINSTANCE hInstance,
//                      HINSTANCE /* hPrevInstance */,
//                      LPSTR     lpCmdLine,
//                      int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK; 
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
KpsEncApp *app_ptr=NULL;
const unsigned char *file_name=NULL;
FILE *out_file;
long file_len;
unsigned char *file_buf = NULL;

   app_ptr = (&theApp);
   theKpStAppPtr = static_cast <KpStApp *> (&theApp);
   
// ------------------------------- 
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

   KP_ASSERT(argc >= 2, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hKpInstance /* hInstance */, NULL /* ini_fname */, argv[1] /* lpCmdLine */, KpStarterMode);
   
   if(SUCCEEDED(retc)) if(app_ptr->m_plCmdLineArgs==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc))
   {    
      file_name=(const unsigned char *)app_ptr->m_plCmdLineArgs->GetValue();
      if(file_name==NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      retc=ReadFileContents(file_name, &file_buf, &file_len, True, True);
      
   if((file_buf==NULL) && SUCCEEDED(retc))   
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(argc > 2)
      {
long entry_id = 0L;
int prod_ver = 0;
         sscanf(argv[2], "%d", &prod_ver);      
PutLogMessage_("main(): %x %d %d %ld", file_buf, file_len, prod_ver, entry_id);
         retc = EnctBufInc(file_buf, file_len, prod_ver, entry_id, True);
      }
      else retc = /* app_ptr-> */ EnctBufSimpl(file_buf, file_len);
   }

   if(SUCCEEDED(retc))
   {
      out_file=fopen((const char *)file_name, "wb");
      if(out_file==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, file_name, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fwrite(file_buf, 1, file_len, out_file)!=file_len)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, file_name, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(feof(out_file) || ferror(out_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, file_name, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(fclose(out_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, file_name, True, __FILE__, __LINE__, 0L);

   KP_DELETEA(file_buf);
   
// KpMsgOut((const unsigned char *)"Kodavimas baigtas", IDI_ASTERISK, KP_MB_TESTI);

// return(RET_CODE_WIN(retc));
return(RET_CODE_MAIN(retc));
}
