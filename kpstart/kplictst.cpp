// ---------------------------
// kplictst.cpp
// tikrina, ar priregistruotas lic. kodas (is data.dat) sutampa su perduotu kaip parametru
// pries diegiant papildymus, priristus prie lic. kodo
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <windows.h>
#include <richedit.h>
#include <time.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpcolors.h"
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
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kplictst"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
bool bServiceFl=False;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,
   
   CheckResRequest_RC,
   CheckRelRequest_RC,

   NULL
};

// KpCommonApp theApp;
KpStApp theApp;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


//---------------------------------------------
// int main(int argc, char **argv)
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
bool retv = False;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT+1];
   
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);
   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
   
// if(SUCCEEDED(retc)) retc = theApp.InitCommonApp(hInstance, lpCmdLine);
   if(SUCCEEDED(retc)) retc = theApp.InitStApp(hInstance, ini_fname, lpCmdLine, KpStRegMode);

// if((argc<2) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if((theApp.m_plCmdLineArgs == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE
// if(SUCCEEDED(retc)) retc = KpMsgOut((unsigned char *)(theApp.m_plCmdLineArgs->GetValue()), IDI_ASTERISK, KP_MB_TESTI);
   if(SUCCEEDED(retc)) 
   if(SUCCEEDED(retc))
   {
      sscanf(/*argv[1] */ (char *)(theApp.m_plCmdLineArgs->GetValue()), "%d", &retv);
      if(!retv)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
#endif


   if(SUCCEEDED(retc))
   {
      retc = theApp.GetSavedKeyReg();
      if(FAILED(retc))
      {
         retc = theApp.GetSavedKeyDat();
         if(FAILED(retc))
         {
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            KpMsgOut(KPST_MSG_NOT_REG, IDI_INFORMATION, KP_MB_BAIGTI);
         }
      }
   }

         
#if FALSE
if(SUCCEEDED(retc))
{
retc = theApp.FormatLicCodeFull(lic_buf);
if(FAILED(retc)) KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
}
if(SUCCEEDED(retc)) KpMsgOut(lic_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
         
#if FALSE
   if(SUCCEEDED(retc))
   {
      retc = theApp.GetCommonCompID();
      if(FAILED(retc))
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
#endif

#if FALSE
   if(SUCCEEDED(retc))
   {
      retc = theApp.ReCalcLicCode();
      if(FAILED(retc))
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      retc = theApp.CalcLicCode();
      if(FAILED(retc))
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
#endif
   
   if(SUCCEEDED(retc))
   {
      retc = theApp.FormatLicCodeFull(lic_buf);
      if(FAILED(retc))
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
         
   if(SUCCEEDED(retc))
   {
// KpMsgOut(lic_buf, IDI_ASTERISK, KP_MB_TESTI);
// KpMsgOut((unsigned char *)(theApp.m_plCmdLineArgs->GetValue()), IDI_ASTERISK, KP_MB_TESTI);
      
      if(strcmp(lic_buf, (const unsigned char *)(theApp.m_plCmdLineArgs->GetValue()))!=0)
      {                
         retc = KP_E_REFUSED;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
      }
   }
   

return(RET_CODE_WIN(retc));
}

