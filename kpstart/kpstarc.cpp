// ---------------------------
// kpstarc.cpp
// katalogo files_obj failus suraðo á pirmàjá .tev objekto raðymo blokà 
// parametras – .tev failo vardas <obj_name> be prievardþio kataloge Output (>kpstarc matau10)
// naudoja failà files_obj\<obj_name>.ini
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
#include "kpstapa.h"
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kpstarc"; 
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
fstream out_file;
KpStArc *arc1 = NULL;
KpStArc *arc2 = NULL;

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
   KP_NEWO(arc1, KpStArc(fname, KpStAppObj.m_lKpStArcStart[0], KpStAppObj.m_lKpStArcLen[0]));  

   if(SUCCEEDED(retc)) retc = arc1->FormatArc();

   KP_NEWO(arc2, KpStArc(fname, KpStAppObj.m_lKpStArcStart[1], KpStAppObj.m_lKpStArcLen[1]));  

   if(SUCCEEDED(retc)) retc = arc2->FormatArc();

// ------------------------------- ciklas per katalogo files_obj failus
   if(SUCCEEDED(retc)) retc = arc1->AppendFolder(KPSTAPA_GRP_PATH, KPSTAPA_GRP_PATH);   // prideda pakatalogio lpszSrcPath failus prie archyvo, 

// ------------------------------- 
   KP_DELETE(arc1);

   KP_DELETE(arc2);

   retc0 = KpStAppObj.CloseStApp(retc, KP_My_Documents);
   if(SUCCEEDED(retc)) retc = retc0;

return(RET_CODE_MAIN(retc));
}
