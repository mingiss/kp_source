// ---------------------------
// kpsobex.cpp
// iðtraukia parametrus ið .tev objekto ir suraðo á 
//    files_obj\AcroRead602\Reader\Javascripts\A.js ir á
//    files_obj\<obj_name>.ini (m_iProdVer ir m_lpszPwd)
// parametras – .tev failo vardas <obj_name> be prievardþio kataloge Output (>kpsobex matau10)
//

// -----------------------------------------
#include "envir.h"

#include <string>
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpmsg.h"
#include "res_com.h"
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
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kpsobex"; 
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;    
KpStApp KpStAppObj;

// -----------------------------------------
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


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ---------------------------------------------------- main
int main(int argc, char **argv)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
int prod_ver;
fstream out_file;

// ------------------------------- 
   theKpStAppPtr = &KpStAppObj;

   KP_ASSERT(argc == 2, E_INVALIDARG, null, True); 
   
// -------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(fname, "files_obj/");
      strcat(fname, argv[1]);
      strcat(fname, ".ini");
   }    
   
   if(SUCCEEDED(retc)) retc = KpStAppObj.InitStApp(NULL, fname, (const char *)null, KpStEditMode);
   
// -------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(fname, "Output/");
      strcat(fname, argv[1]);
      strcat(fname, ".tev");
   }    
   
   if(SUCCEEDED(retc)) retc = KpStAppObj.IoRid(fname, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc = KpStAppObj.GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      strcpy(fname, "files_obj/AcroRead602/Reader/Javascripts/A.js");
      retc = CreatePath(fname, True);
   }
      
   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)fname, ios_base::out);
      KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, fname, True);

      if(SUCCEEDED(retc))
      {
         out_file << "global.ProdVer = " << setfill('0') << setw(5) << prod_ver << ";" << endl;
         out_file << "global.ProdVar = " << KpStAppObj.m_ProdVar << ";" << endl; 
         out_file << "global.ProductDate = " << KpStAppObj.m_ProdDate << ";" << endl;
         out_file << "global.ProductVersion = " << KpStAppObj.m_ProdVersion << ";" << endl;

         out_file.close();

         KP_ASSERT(!out_file.fail(), KP_E_FERROR, fname, True);
      }
   }   

   if(SUCCEEDED(retc)) retc = KpStAppObj.SaveIni();
   
// ------------------------------- 
   retc0 = KpStAppObj.CloseStApp(retc, KP_My_Documents);
   if(SUCCEEDED(retc)) retc = retc0;

return(RET_CODE_MAIN(retc));
}
