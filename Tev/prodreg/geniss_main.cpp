// ===================================================
// geniss.cpp
// Inno Setup scriptu generatorius
// main()
//

// ------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
// #include <iostream.h>
#include <iostream>
// #include <fstream.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
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
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "geniss.h"
#include "geniss_en.h"
#include "geniss_lt.h"
#include "geniss_pl_1250.h"
#include "geniss_pl_1257.h"
#include "geniss_ru.h"


#if Compiler != Watcom
using namespace std;
#endif


// --------------------------
const unsigned char lpszProdName[] = "geniss";
int iProdVerGlob=0;
int iUpdNumGlob = -1;
bool bServiceFl = False;

int KpHp11NumOfExtFun = KP_RC_CBIX_NumOfCommonIxs;
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

KpErrorProcClass KpErrorProc(True, 43);
// KpStApp theApp;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ------------------------------------
int main(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

try
{
   KP_NEWO(theKpStAppPtr, KpStApp()); // &theApp;

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(NULL, (const unsigned char *)"geniss_0.ini", "geniss.exe", KpStEditMode);

// ------------------------
   if(SUCCEEDED(retc)) retc = InitVars();

   if(SUCCEEDED(retc)) retc = ReadIniFile();

   if(SUCCEEDED(retc))
   {
cout << "ProdName:     " << ProdName << endl;
cout << "ProdNameRaw:  " << ProdNameRaw << endl;
cout << "ProdDir:      " << ProdDir << endl;
cout << "ProdGroup:    " << ProdGroup << endl;
cout << "ProdFNameRaw: " << ProdFNameRaw << endl;
cout << "ProdFName:    " << ProdFName << endl;
cout << "VerName:      " << VerName << endl;
cout << "Ver:          " << Ver << endl;
cout << "ProdVer:      " << ProdVer << endl;
cout << "ProdVerFlash: " << ProdVerFlash << endl;
cout << "ProdVerNet:   " << ProdVerNet << endl;
cout << "UpdVerName:   " << UpdVerName << endl;
cout << "UpdNum:       " << UpdNum << endl;
cout << "PrevVerName:  " << PrevVerName << endl;
cout << "PrevVer:      " << PrevVer << endl;
cout << "PrevUpdNum:   " << PrevUpdNum << endl;
cout << "BuildNum:     " << BuildNum << endl;
cout << "FirstVerName: " << FirstVerName << endl;
cout << "FirstVer:     " << FirstVer << endl;
cout << "IconFName:    " << IconFName << endl;
cout << "SetupFName:   " << SetupFName << endl;
cout << "ExeFName:     " << ExeFName << endl;
cout << "SvrFName:     " << SvrFName << endl;
cout << "AutoRun:      " << YesNoKwds[AutoRun] << endl;
cout << "RequireAdmin: " << YesNoKwds[RequireAdmin] << endl;
cout << "PartialInstallIx: " << YesNoKwds[PartialInstall] << endl;
cout << "PartialDirIx: " << YesNoKwds[PartialDir] << endl;
cout << "ProdTypeIx:   " << lpszaProdTypeKwds[iProdType] << endl;
cout << "ChkUpdIx:     " << YesNoKwds[ChkUpd] << endl;
cout << "Publisher:    " << Publisher << endl;
cout << "SplashBMP:    " << SplashBMP << endl;
cout << "StartPDF:     " << StartPDF << endl;
cout << "Password:     " << Password << endl;
cout << "ProjID:       " << ProjID << endl;
cout << "Kalba:        " << Kalba << " " << iMsgLangOff << endl;
cout << "CidMode:      " << " 0x" << hex << CidMode << endl;
   }

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIssBat();

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFiles);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssCd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssSh);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssUpdWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssGrp);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFlash);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFlashUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFlashUpdWhole);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFlashStart);
// /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFlashStartUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssChkVol);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssNet);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssSvr);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssCli);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssRez);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFonts);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssDel);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssDelWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesPl(GenIssFinst);

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFiles);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssCd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssSh);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssUpdWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssGrp);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFlash);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFlashUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFlashUpdWhole);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFlashStart);
// /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFlashStartUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssChkVol);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssNet);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssSvr);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssCli);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssRez);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFonts);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssDel);
   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssDelWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputFilesBat(GenIssFinst);

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssCd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssSh);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssCert);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssUpdWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssGrp);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFlash);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFinst);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFlashUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFlashUpdWhole);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFlashStart);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssFlashStartUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssChkVol);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssNet);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssSvr);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenBat(GenIssCli);

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssCd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssSh);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssCert);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssUpdWhole);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssGrp);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFlash);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFinst);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFlashUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFlashUpdWhole);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFlashStart);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssFlashStartUpd);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssChkVol);

   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssNet);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssSvr);
   /* if(SUCCEEDED(retc)) retc = */ OutputGenIss(GenIssCli);

// ------------------------
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_cd.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_cd_sh.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_cd_tux.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_cd_tux_sh.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_cd_free.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_flash.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_flash_tux.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_net.ini");
   /* if(SUCCEEDED(retc)) retc = */ OutputKpstartIni((const unsigned char *)"kpstart_finst.ini");

// -------------------------
   /* if(SUCCEEDED(retc)) retc = */ GenXFS_XFS_hh();
   /* if(SUCCEEDED(retc)) retc = */ GenXFS_tux_core_hh();
   /* if(SUCCEEDED(retc)) retc = */ GenXFS_Xipa_hh();
   /* if(SUCCEEDED(retc)) retc = */ GenXFS_XipaResource_rc();

   /* if(SUCCEEDED(retc)) retc = */ GenXFSTool_cfg();

// -------------------------
// /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"copy_ico");
// /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"copy_XFS_pries_exe");
// /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"copy_XFS_po_exe");
   /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"make_cd");
   /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"make_free");
   /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"make_XFS_exe");
   /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"make_creg");
   /* if(SUCCEEDED(retc)) retc = */ OutputGenLocalBat((const unsigned char *)"make_KURK");
   
// ------------------------
/* if(SUCCEEDED(retc)) */ if(theKpStAppPtr != NULL){ retc0 = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0; }
}
catch(const char *msg) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)msg)
catch(int sig){ unsigned char out_str[100]; sprintf((char *)out_str, "sig: %d", sig); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::bad_alloc& ba){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::bad_alloc&: %s", ba.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception& ex){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::exception&: %s", ex.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::exception*")
// catch(const Exception& ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception&")
// catch(const Exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception*")
catch(const EXCEPTION_DEBUG_INFO& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO&")
catch(const EXCEPTION_DEBUG_INFO *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO*")
catch(const EXCEPTION_RECORD& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD&")
catch(const EXCEPTION_RECORD *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD*")
catch(...) KP_ERROR(KP_E_SYSTEM_ERROR, null);

return(RET_CODE_MAIN(retc));
}
