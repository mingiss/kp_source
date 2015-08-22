// ----------------------------
// kpstedn.cpp
// kpstart.ini failo lic. kodų perkėlimas į kitą kpstart.ini
// kpstart.ini versijos atnaujinimas
//


// ------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
using namespace std;
#endif

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
#include "xmlg.h"
#include "kpstap.h"


// ------------------------------------
const unsigned char lpszProdName[] = "kpstedn";
KpErrorProcClass KpErrorProc(True, 43);
int iProdVerGlob = 0;
bool bServiceFl = False;
int iUpdNumGlob = -1;

KpStApp theApp;

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


// -----------------------------------------
int main(int argc, char** argv)
{
HRESULT retc = S_OK;

// ------------------------------------
   theKpStAppPtr = &theApp;
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(NULL, NULL, NULL, KpStEditMode);

   KP_ASSERT(argc == 3, E_INVALIDARG, "Sintaksė:\n    kpstedn.exe foo.ini bar.ini\nFailo foo.ini licenciniai duomenys perkeliami į failą bar.ini, atnaujinama failo bar.ini versija\n", True);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile((const unsigned char *)argv[1], True, False);
   
long flash_id = 0;
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniFlashId(&flash_id);
// HRESULT GetIniCheckFlash(bool *pbCheckFlash); // gets value of m_Ini.m_bCheckFlash
// HRESULT GetIniBound(bool *pbBound); // gets value of m_Ini.m_bBound;
// HRESULT GetIniIniLicID(int *piIniLicID); // gets value of m_Ini.m_iIniLicID
// HRESULT GetIniCompIdMode(int *piCompIdMode); // gets value of m_Ini.m_iCompIdMode
unsigned char atm_kod[TV_TAG_LEN + 1];
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniAdminPwd(atm_kod);
   
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile((const unsigned char *)argv[2], True, False);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniFlashId(flash_id);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniAdminPwd(atm_kod);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile((const unsigned char *)argv[2]);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);

return(RET_CODE_MAIN(retc));
}

