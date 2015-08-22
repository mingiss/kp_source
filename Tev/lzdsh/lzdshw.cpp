// ---------------------------
// lzdshw.cpp
// WinLED zodyno paleidejas
// lzdshd.exe - WinLED Demo, zodynas vlzd2.xdb
// lzdshl.exe - WinLED Lengvai
// lzdshp.exe - WinLED Pro, zodynai vlz2.xdb, lvz2.xdb
// kopijuojant i distributyva pervadinti i WinLED.exe
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <string>
#include <time.h>

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpfonts.h"
#include "kptt.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "KpPubDlg.h"
#include "KpRtfDlg.h"
#include "lzdsh.h"
#include "lzdshl.h"
#include "lzdshr.h"
#include "lzdsht.h"
#include "lzdsho.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "lzdsh"; 
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl = False;

KpErrorProcClass KpErrorProc(True, 71);
KpStApp theApp;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs; // + LZDSH_RC_NumOfRcIxs;

KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 /* +LZDSH_RC_NumOfRcIxs_1 */ +1]=
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

// #ifdef LZDSHT_ENCODED
//    WriteRtfFromImg,
//    GetHwFromImg,
// #endif

   NULL
};

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
DWORD retw;
HCURSOR cur_sav=NULL;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
long skin;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey=0;
DWORD dwBufLen;
DWORD dwValType;
unsigned char cmd[KP_MAX_FNAME_LEN+1];
bool ver_98 = False;


//-----------------
   theKpStAppPtr = &theApp;

//-----------------
   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
   if(SUCCEEDED(retc))
      retc=theApp.InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode);

//-----------------
   ver_98 = False;
// if(SUCCEEDED(retc)) retc = GetAppName(app_fname);
   if(SUCCEEDED(retc)) if(strstr(/* app_fname */ ini_fname, "98")) ver_98 = True;

// ---------------- get current skin
   if(SUCCEEDED(retc)) retc = theApp.GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc = theApp.GetIniProdVer(&prod_ver);

   skin=LzdshSkinMahd;
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );
      if(RegOpenKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS)
      {
         dwBufLen=sizeof(skin);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "Skin", NULL, 
               &dwValType, (LPBYTE)&skin, &dwBufLen)==ERROR_SUCCESS)
         {
            if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }
      }
   }
   
   
   cmd[0] = Nul;
   if(SUCCEEDED(retc)) switch(prod_ver)
   {
      case 1012: strcpy(cmd, "lzdshd"); break; // WinLED Demo
      case 2012: strcpy(cmd, "lzdshl"); break; // WinLED Lengvai
      case 3012: strcpy(cmd, "lzdshp"); break; // WinLED Pro
      case 11012: /* 5012: */ strcpy(cmd, "lzdshpf"); break; // WinLED Pro atmintuke
      case 9012: strcpy(cmd, "lzdshpn"); break; // WinLED Pro tinklinis
      case 10012: strcpy(cmd, "lzdshdn"); break; // WinLED Demo tinklinis
   }

   if(SUCCEEDED(retc)) switch(skin)
   { 
      case LzdshSkinSta: strcat(cmd, "_cla"); break;
      case LzdshSkinMahd: strcat(cmd, "_mahd"); break;
   }

   if(ver_98 && SUCCEEDED(retc)) strcat(cmd, "_98");
   
   if(SUCCEEDED(retc)) strcat(cmd, ".exe");
   
FILE *in_file = fopen((const char *)cmd, "rb");
   if(in_file == NULL) strcpy(cmd + strlen(cmd) - 4, ".bin");
   else fclose(in_file);   

   if((cmd[0]==Nul) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc))   
      retc=StartCmdProcess(cmd, KPST_CUR_DIR, NULL, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
            
   retw=RET_CODE_WIN(retc);

return(retw);
}
