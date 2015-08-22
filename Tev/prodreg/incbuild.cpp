// ===================================================
// incbuild.cpp
// Jûros buildø inkrementorius
//    ið lokaliam aplanke esanèio geniss.ini iðsitraukia ProdVer 
//    ið tux_XFS\include\tux\fs\XFS.hh iðsitraukia XFS versijà
//    atnaujina geniss.ini lokaliam aplanke (nusiurbia ið Jûros)
//    komandinës eilutës parametras – buildo komentaras á Jûrà  
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

#if Compiler != Watcom
using namespace std;
#endif

// --------------------------
const unsigned char lpszProdName[] = "incbuild";
int iProdVerGlob = 0;
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


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ------------------------------------
int main(int argc, char** argv)
{
HRESULT retc = S_OK;

try
{
// -----------------------------
int prod_ver = 0; // 1072;
   if(SUCCEEDED(retc)) retc = ReadIniFile();
   if(SUCCEEDED(retc)) retc = DelHeadTailApost(ProdVer);
// printf("ProdVer: [%s]\n", ProdVer);   
   if(SUCCEEDED(retc)) sscanf((const char *)ProdVer, "%d", &prod_ver); 

int prev_build_num = BuildNum;
printf("BuildNum: %d\n", prev_build_num);   

// -----------------------------
static unsigned char comments[KP_MAX_FNAME_LEN + GEN_CSS_STR_PAR_LEN * 3 + KP_MAX_FILE_LIN_LEN + 100]; // = (const unsigned char *)"testuojam%20incbuild.exe";
static unsigned char comments_out[3 * (KP_MAX_FNAME_LEN + GEN_CSS_STR_PAR_LEN * 3 + KP_MAX_FILE_LIN_LEN + 100) + 1];
   comments[0] = Nul;
   comments_out[0] = Nul;

// ---- user
   if(SUCCEEDED(retc))
   {
DWORD ll = KP_MAX_FNAME_LEN;
      if(!GetUserName((char *)comments, &ll)) comments[0] = Nul;
      if(comments[0] != Nul) strcat(comments, ": ");
   }

// ---- versijos, datos 
   if(SUCCEEDED(retc)) retc = ScanXFS_XFS_hh(comments + strlen(comments));
   if(SUCCEEDED(retc)) strcat(comments, "; ");
   if(SUCCEEDED(retc)) retc = ScanKpCurDatCpp(comments + strlen(comments));
   if(SUCCEEDED(retc)) strcat(comments, "; ");
   if(SUCCEEDED(retc)) retc = GetGenIssExeDate(comments + strlen(comments));

   if((argc >= 2) && SUCCEEDED(retc))
   {
      KP_ASSERT(strlen(argv[1]) < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, False);
      if(SUCCEEDED(retc))
      {
         strcat(comments, "; ");
         strncpy(comments + strlen(comments), argv[1], KP_MAX_FILE_LIN_LEN);
         comments[GEN_CSS_STR_PAR_LEN + KP_MAX_FILE_LIN_LEN + 10] = Nul;  
      }
   }

   if(SUCCEEDED(retc)) retc = KpStApp::EncodePostMsg(comments_out, comments);

// -----------------------------
unsigned char reg_url[KP_MAX_FNAME_LEN + GEN_CSS_STR_PAR_LEN + KP_MAX_FILE_LIN_LEN + 1000];
   reg_url[0] = Nul;
   if(SUCCEEDED(retc)) sprintf((char *)reg_url, GENISS_INCBUILD_FMT, prod_ver, comments_out);

if(SUCCEEDED(retc)) printf("%s\n", reg_url);

// -----------------------------
KpSocket *sock_ptr = NULL;
   KP_NEWO(sock_ptr, KpSocket);

   if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(GENISS_INCBUILD_URL, True);
   if(SUCCEEDED(retc)) retc = sock_ptr->Connect(True);

   if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, reg_url, True);

unsigned char rcv_buf[GENISS_INI_BUF_SIZE + 1];
long read = GENISS_INI_BUF_SIZE;
   if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, True);
   
   if(SUCCEEDED(retc))
   {
      rcv_buf[read] = Nul;
      if(strstr(rcv_buf, GENISS_SVR_OK) == rcv_buf)
      {
fstream in_file;
         in_file.open(GEN_ISS_INI_SAV_FNAME, ios_base::in);
         if(in_file.fail()) CopyFile(GEN_ISS_INI_FNAME, GEN_ISS_INI_SAV_FNAME, True); 
         else in_file.close();

fstream out_file;
         out_file.open(GEN_ISS_INI_FNAME, ios_base::out | ios_base::binary);
         KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, GEN_ISS_INI_FNAME, True);
         
//       if(SUCCEEDED(retc)) retc = DoubleCrToSingle(rcv_buf);
         if(SUCCEEDED(retc)) out_file << rcv_buf + strlen(GENISS_SVR_OK);
         
         out_file.close();
      } 
      else
      {
         retc = KP_E_REFUSED;
         printf((const char *)rcv_buf); // serverio klaida
      }
   }

   KP_DELETE(sock_ptr);
   
// -----------------------------
   if(SUCCEEDED(retc)) retc = ReadIniFile();
   KP_ASSERT(BuildNum >= prev_build_num + 1, KP_E_SYSTEM_ERROR, "Buildo inkrementavimas nepavyko", True);
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
