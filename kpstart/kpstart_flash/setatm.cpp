// --------------------------------
// setatm.cpp atmintuko kodo ‘ra’ymas ‘ data.dat fail–
//

// --------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <windows.h>
// #include <iostream> 
#include <fstream> 
#include <string>
#include <richedit.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kperr.h"
#include "kpsock.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
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

#define MAX_COMP_DATA_POS 20

// using namespace std;

// --------------------------------
const unsigned char lpszProdName[] = "setatm"; 
KpErrorProcClass KpErrorProc(True, 43);
int iProdVerGlob=0;
KpStApp theApp;
bool bServiceFl=False;
int iUpdNumGlob = -1;
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_7 + 1]=
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

   RegSert_RC,
   UnRegSert_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------
int main(int argc, char **argv)
{
HRESULT retc = S_OK;
KpString file_name;
KpString par_str;
unsigned char *par_buf = null;
unsigned char *val_ptr = null;
KpString val_str;
int l_argc;
int cur_par;
char **l_argv_ptr;
#ifdef Debug
char *l_argv[3];
#endif

   theKpStAppPtr = &theApp;

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = KpInit();

   if(SUCCEEDED(retc))
   {
      if(argc < 3)
      {
#ifdef Debug
         l_argv[0] = argv[0];
         l_argv[1] = "data.dat";
         l_argv[2] = "AI=GG0-65062-1780";
         l_argv_ptr = l_argv; 
#else
         cout << endl;
         cout << "SetAtm.exe - data.dat failo papildymas atmintuko kodu" << endl;
         cout << endl;
         cout << "setatm.exe data.dat AI=GG0-65062-1780" << endl;
         cout << "                    ^   ^" << endl;
         cout << "                    |   +---- kintamojo reikmÎ" << endl;
         cout << "                    +-------- kintamojo vardas" << endl;
         cout << endl;
#endif
      }
      else // if(argc < 3)
      {
         l_argv_ptr = argv; 
         l_argc = argc;

      } // else // if(argc != 2)

   } // if(SUCCEEDED(retc))
   
   if(SUCCEEDED(retc))
   {
      file_name = l_argv_ptr[1]; 
      cur_par = 2;
   }
   while((cur_par < l_argc) && SUCCEEDED(retc))
   {
      par_str = l_argv_ptr[cur_par];

// ----------------------------- u˛koduojam atmintuko kod‡ (AI)
// !!! TODO

// -----------------------------
      KP_NEWA(par_buf, unsigned char, par_str.length() + 1);

      if(SUCCEEDED(retc))
      {
         strcpy(par_buf, par_str.ExtractUnsignedValueA());
         val_ptr = strchr(par_buf, '=');
         KP_ASSERT(val_ptr, E_INVALIDARG, null, True);
      }
      if(SUCCEEDED(retc))
      {
         *val_ptr++ = Nul;
         val_str = val_ptr;
      }

// --------------------- reikmÎ ioriniam faile
      if(SUCCEEDED(retc)) if(*val_ptr == '@')
      {
         val_ptr++;
         
unsigned char *file_contents = null;
         retc = ReadFileContents(val_ptr, &file_contents, NULL, True, False);
         KP_ASSERT(file_contents != null, KP_E_OUTOFMEM, null, True);

         if(SUCCEEDED(retc)) val_str = file_contents;
         
         KP_DELETEA(file_contents);
      }
      
// -------------------------------- ·raom · data.dat
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetDataDatVariable(&file_name, par_buf, &val_str, True);

// ----------------------------
      KP_DELETEA(par_buf);
   
// ----------------------------
      cur_par++;
      
   } // while((cur_par < l_argc) && SUCCEEDED(retc))
   
// ----------------------------
#ifdef Debug
system("pause");
#endif   
   
return(RET_CODE_MAIN(retc));
}

