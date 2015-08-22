// ---------------------------
// kpstapr.cpp
// common application for program starters
// install key & Co - secret part
//
// 2012.10.01  mp  pasilpnintas admino reikalavimas raðant á HKEY_CURRENT_USER SaveCompID()
// 2012.10.03  mp  bugas terminuotø lic. minuèiø sk. inicializavime
// 2012.10.26  mp  lic. termino dinaminis pailginimas kreipinio á serverá bûdu; iki ðiol galëjo tik patrumpëti
//

#define Logging

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <time.h>
#include <fstream>

#include <ctype.h>
#include <stdio.h>
#include <string>
// #if ((CompilerGr==Msvc) && (Envir!=MSWin32Mfc))
#if (CompilerGr==Msvc)
#include <WINSOCK2.H>
#endif
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <winsock.h>
#include <mmsystem.h>
#include <direct.h>

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpttucf.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
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
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"

#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
// #error Envir!=MSWin32
#if (Envir!=MSWin32Con)
#error (Envir!=MSWin32) && (Envir!=MSWin32Mfc) && (Envir!=MSWin32Con)
#endif
#endif


// ------------------------------
void KpStApp::InitKeyFmts(void)
{
// #define KPST_CNT_PKG_FMT "{75BCD15-DFB38D-149AA44-1B3A0C8-%d}"
   m_CntPkgFmt[ 0]='{';
   m_CntPkgFmt[ 1]='7';
   m_CntPkgFmt[ 2]='5';
   m_CntPkgFmt[ 3]='B';
   m_CntPkgFmt[ 4]='C';
   m_CntPkgFmt[ 5]='D';
   m_CntPkgFmt[ 6]='1';
   m_CntPkgFmt[ 7]='5';
   m_CntPkgFmt[ 8]='-';
   m_CntPkgFmt[ 9]='D';
   m_CntPkgFmt[10]='F';
   m_CntPkgFmt[11]='B';
   m_CntPkgFmt[12]='3';
   m_CntPkgFmt[13]='8';
   m_CntPkgFmt[14]='D';
   m_CntPkgFmt[15]='-';
   m_CntPkgFmt[16]='1';
   m_CntPkgFmt[17]='4';
   m_CntPkgFmt[18]='9';
   m_CntPkgFmt[19]='A';
   m_CntPkgFmt[20]='A';
   m_CntPkgFmt[21]='4';
   m_CntPkgFmt[22]='4';
   m_CntPkgFmt[23]='-';
   m_CntPkgFmt[24]='1';
   m_CntPkgFmt[25]='B';
   m_CntPkgFmt[26]='3';
   m_CntPkgFmt[27]='A';
   m_CntPkgFmt[28]='0';
   m_CntPkgFmt[29]='C';
   m_CntPkgFmt[30]='8';
   m_CntPkgFmt[31]='-';
   m_CntPkgFmt[32]='%';
   m_CntPkgFmt[33]='d';
   m_CntPkgFmt[34]='}';
   m_CntPkgFmt[35]=Nul;

// #define KPST_BOLT_PKG_FMT "{75BCD15-DFB38D-149AA44-1B3A0CA-123}"
   m_BoltPkgFmt[ 0]='{';
   m_BoltPkgFmt[ 1]='7';
   m_BoltPkgFmt[ 2]='5';
   m_BoltPkgFmt[ 3]='B';
   m_BoltPkgFmt[ 4]='C';
   m_BoltPkgFmt[ 5]='D';
   m_BoltPkgFmt[ 6]='1';
   m_BoltPkgFmt[ 7]='5';
   m_BoltPkgFmt[ 8]='-';
   m_BoltPkgFmt[ 9]='D';
   m_BoltPkgFmt[10]='F';
   m_BoltPkgFmt[11]='B';
   m_BoltPkgFmt[12]='3';
   m_BoltPkgFmt[13]='8';
   m_BoltPkgFmt[14]='D';
   m_BoltPkgFmt[15]='-';
   m_BoltPkgFmt[16]='1';
   m_BoltPkgFmt[17]='4';
   m_BoltPkgFmt[18]='9';
   m_BoltPkgFmt[19]='A';
   m_BoltPkgFmt[20]='A';
   m_BoltPkgFmt[21]='4';
   m_BoltPkgFmt[22]='4';
   m_BoltPkgFmt[23]='-';
   m_BoltPkgFmt[24]='1';
   m_BoltPkgFmt[25]='B';
   m_BoltPkgFmt[26]='3';
   m_BoltPkgFmt[27]='A';
   m_BoltPkgFmt[28]='0';
   m_BoltPkgFmt[29]='C';
   m_BoltPkgFmt[30]='A';
   m_BoltPkgFmt[31]='-';
   m_BoltPkgFmt[32]='1';
   m_BoltPkgFmt[33]='2';
   m_BoltPkgFmt[34]='3';
   m_BoltPkgFmt[35]='}';
   m_BoltPkgFmt[36]=Nul;

// #define KPST_LIC_PKG_FMT "{75BCD15-DFB38D-149AA44-1B3A0C9-%d}"
   m_LicPkgFmt[ 0]='{';
   m_LicPkgFmt[ 1]='7';
   m_LicPkgFmt[ 2]='5';
   m_LicPkgFmt[ 3]='B';
   m_LicPkgFmt[ 4]='C';
   m_LicPkgFmt[ 5]='D';
   m_LicPkgFmt[ 6]='1';
   m_LicPkgFmt[ 7]='5';
   m_LicPkgFmt[ 8]='-';
   m_LicPkgFmt[ 9]='D';
   m_LicPkgFmt[10]='F';
   m_LicPkgFmt[11]='B';
   m_LicPkgFmt[12]='3';
   m_LicPkgFmt[13]='8';
   m_LicPkgFmt[14]='D';
   m_LicPkgFmt[15]='-';
   m_LicPkgFmt[16]='1';
   m_LicPkgFmt[17]='4';
   m_LicPkgFmt[18]='9';
   m_LicPkgFmt[19]='A';
   m_LicPkgFmt[20]='A';
   m_LicPkgFmt[21]='4';
   m_LicPkgFmt[22]='4';
   m_LicPkgFmt[23]='-';
   m_LicPkgFmt[24]='1';
   m_LicPkgFmt[25]='B';
   m_LicPkgFmt[26]='3';
   m_LicPkgFmt[27]='A';
   m_LicPkgFmt[28]='0';
   m_LicPkgFmt[29]='C';
   m_LicPkgFmt[30]='9';
   m_LicPkgFmt[31]='-';
   m_LicPkgFmt[32]='%';
   m_LicPkgFmt[33]='d';
   m_LicPkgFmt[34]='}';
   m_LicPkgFmt[35]=Nul;

// #define KPST_CNT_REG_KEY_FMT "Software\\Adobe\\LocalData\\Descriptors\\%s" // "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s"
   m_CntRegKeyFmt[ 0]='S';
   m_CntRegKeyFmt[ 1]='o';
   m_CntRegKeyFmt[ 2]='f';
   m_CntRegKeyFmt[ 3]='t';
   m_CntRegKeyFmt[ 4]='w';
   m_CntRegKeyFmt[ 5]='a';
   m_CntRegKeyFmt[ 6]='r';
   m_CntRegKeyFmt[ 7]='e';
   m_CntRegKeyFmt[ 8]='\\';
   m_CntRegKeyFmt[ 9]='A';
   m_CntRegKeyFmt[10]='d';
   m_CntRegKeyFmt[11]='o';
   m_CntRegKeyFmt[12]='b';
   m_CntRegKeyFmt[13]='e';
   m_CntRegKeyFmt[14]='\\';
   m_CntRegKeyFmt[15]='L';
   m_CntRegKeyFmt[16]='o';
   m_CntRegKeyFmt[17]='c';
   m_CntRegKeyFmt[18]='a';
   m_CntRegKeyFmt[19]='l';
   m_CntRegKeyFmt[20]='D';
   m_CntRegKeyFmt[21]='a';
   m_CntRegKeyFmt[22]='t';
   m_CntRegKeyFmt[23]='a';
   m_CntRegKeyFmt[24]='\\';
   m_CntRegKeyFmt[25]='D';
   m_CntRegKeyFmt[26]='e';
   m_CntRegKeyFmt[27]='s';
   m_CntRegKeyFmt[28]='c';
   m_CntRegKeyFmt[29]='r';
   m_CntRegKeyFmt[30]='i';
   m_CntRegKeyFmt[31]='p';
   m_CntRegKeyFmt[32]='t';
   m_CntRegKeyFmt[33]='o';
   m_CntRegKeyFmt[34]='r';
   m_CntRegKeyFmt[35]='s';
   m_CntRegKeyFmt[36]='\\';
   m_CntRegKeyFmt[37]='%';
   m_CntRegKeyFmt[38]='s';
   m_CntRegKeyFmt[39]=Nul;

// #define KPST_CNT_REG_PATH_1 m_CntRegPath1 ("C:\\Program Files\\Common Files\\") // ("C:\\Program Files\\Common Files\\Adobe\\LocalData") // ("C:\\RegisteredPackages") // ("C:\\Temp") // ("C:\\Documents and Settings") // "C:\\WINNT" //
   m_CntRegPath1[ 0]='C';
   m_CntRegPath1[ 1]=':';
   m_CntRegPath1[ 2]='\\';
   m_CntRegPath1[ 3]='P';
   m_CntRegPath1[ 4]='r';
   m_CntRegPath1[ 5]='o';
   m_CntRegPath1[ 6]='g';
   m_CntRegPath1[ 7]='r';
   m_CntRegPath1[ 8]='a';
   m_CntRegPath1[ 9]='m';
   m_CntRegPath1[10]=' ';
   m_CntRegPath1[11]='F';
   m_CntRegPath1[12]='i';
   m_CntRegPath1[13]='l';
   m_CntRegPath1[14]='e';
   m_CntRegPath1[15]='s';
   m_CntRegPath1[16]='\\';
   m_CntRegPath1[17]='C';
   m_CntRegPath1[18]='o';
   m_CntRegPath1[19]='m';
   m_CntRegPath1[20]='m';
   m_CntRegPath1[21]='o';
   m_CntRegPath1[22]='n';
   m_CntRegPath1[23]=' ';
   m_CntRegPath1[24]='F';
   m_CntRegPath1[25]='i';
   m_CntRegPath1[26]='l';
   m_CntRegPath1[27]='e';
   m_CntRegPath1[28]='s';
   m_CntRegPath1[29]='\\';
   m_CntRegPath1[30]=Nul;

// #define KPST_CNT_REG_PATH_11 m_CntRegPath11 ("Adobe\\LocalData\\")
   m_CntRegPath11[ 0]='A';
   m_CntRegPath11[ 1]='d';
   m_CntRegPath11[ 2]='o';
   m_CntRegPath11[ 3]='b';
   m_CntRegPath11[ 4]='e';
   m_CntRegPath11[ 5]='\\';
   m_CntRegPath11[ 6]='L';
   m_CntRegPath11[ 7]='o';
   m_CntRegPath11[ 8]='c';
   m_CntRegPath11[ 9]='a';
   m_CntRegPath11[10]='l';
   m_CntRegPath11[11]='D';
   m_CntRegPath11[12]='a';
   m_CntRegPath11[13]='t';
   m_CntRegPath11[14]='a';
   m_CntRegPath11[15]='\\';
   m_CntRegPath11[16]=Nul;

// #define KPST_CNT_REG_PATH_2 ("Descriptors\\") // ("\\Descriptors") // ("") // ("\\Â") // ("\\All Users") //
   m_CntRegPath2[ 0]='D';
   m_CntRegPath2[ 1]='e';
   m_CntRegPath2[ 2]='s';
   m_CntRegPath2[ 3]='c';
   m_CntRegPath2[ 4]='r';
   m_CntRegPath2[ 5]='i';
   m_CntRegPath2[ 6]='p';
   m_CntRegPath2[ 7]='t';
   m_CntRegPath2[ 8]='o';
   m_CntRegPath2[ 9]='r';
   m_CntRegPath2[10]='s';
   m_CntRegPath2[11]='\\';
   m_CntRegPath2[12]=Nul;

#if FALSE
// #define KPST_CNT_REG_PATH_22 ("Incremental\\") //  ("\\Incremental")
   m_CntRegPath22[ 0]='I';
   m_CntRegPath22[ 1]='n';
   m_CntRegPath22[ 2]='c';
   m_CntRegPath22[ 3]='r';
   m_CntRegPath22[ 4]='e';
   m_CntRegPath22[ 5]='m';
   m_CntRegPath22[ 6]='e';
   m_CntRegPath22[ 7]='n';
   m_CntRegPath22[ 8]='t';
   m_CntRegPath22[ 9]='a';
   m_CntRegPath22[10]='l';
   m_CntRegPath22[11]='\\';
   m_CntRegPath22[12]=Nul;
#endif
}


// ------------------------------
int NormalizeCompId(long lValue)
{
int ret_val = 0;
long in_val = lValue;

// ---------------------------
// in_val=(in_val & 0xFFFF) + (in_val >> 16);

   in_val = (in_val % KPSTA_COMPID_SIGNIF) + (in_val / KPSTA_COMPID_SIGNIF);

// ret_val = ((in_val*10) /* + m_iInstCount */) & 0xFFFF;
   ret_val = ((in_val*10) /* + m_iInstCount */) % 65530;


// ---------------------------
#ifdef Debug
// ret_val=1;
// ret_val=60340;
// ret_val=52610;
// ret_val=4950+m_iInstCount;
// ret_val=4951;
// ret_val=4953;
#endif

// ---------------------------
#if FALSE // #ifdef Debug
unsigned char out_str[100];
sprintf((char *)out_str, "comp_id: %d", ret_val);
KP_TRACE(out_str);
#endif

   if(ret_val == 0) ret_val = 1;

#ifdef Debug
#ifdef DebugStop
unsigned char str_buf[100];
sprintf((char *)str_buf, "GetPhysCID galas cid:%d", ret_val);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

return(ret_val);
}


// ------------------------------
HRESULT KpStApp::GetPhysCompId(long *plPhysWithoutBolt)
{
HRESULT retc=S_OK;
bool ci_direct=False;
long cur_comp_id = 0;
long new_comp_id = 0; // cumulated
int comp_id = 0;
int comp_id_mode = 0;
bool lic_flash = False;
long flash_id = 0;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetPhysCID pradzia", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// KpMsgOut("###", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

// ------------------------
   if(SUCCEEDED(retc)) retc = GetIniCompIdMode(&comp_id_mode);
   if(SUCCEEDED(retc)) retc = GetIniLicFlash(&lic_flash);
   if(SUCCEEDED(retc)) retc = GetIniFlashId(&flash_id);

// ---------------------------
   if (lic_flash)
   {
      comp_id_mode = 0;
      new_comp_id = flash_id;
   }

// --------------------------- BIOS Date
   if((comp_id_mode & KPST_COMPID_BIOS_DATE) && SUCCEEDED(retc))
   {
#if TRUE // #if FALSE //
unsigned char dat_buf[BIOS_DAT_SIZE + 1];
unsigned char *pntd;

      if(SUCCEEDED(retc)) retc = GetBIOSDate(dat_buf);
#if FALSE // #ifdef Logging
static char str_buf[1000];
sprintf(str_buf, "[phys 1] %s", dat_buf);
KP_WARNING0(S_OK, str_buf);
#endif
      if(SUCCEEDED(retc))
      {
// KpMsgOut(dat_buf, KP_MB_TESTI);
#if FALSE // #ifdef Logging
char buf[100];
unsigned char buf1[50];
strcpy(buf1, dat_buf);
EncodeText(buf1);
sprintf(buf, "dcidd: %s", buf1);
KP_TRACE(buf);
#endif
         pntd=dat_buf;
         while(*pntd)
         {
            if(*pntd=='.') *pntd=Nul;
            pntd++;
         }
         cur_comp_id=(atoi((const char *)dat_buf)-1981)*12*31+
                     atoi((const char *)dat_buf+5)*31+
                     atoi((const char *)dat_buf+8);

         new_comp_id += cur_comp_id;
#if FALSE // #ifdef Logging
sprintf(str_buf, "[phys 2] %d %d", new_comp_id, cur_comp_id);
KP_WARNING0(S_OK, str_buf);
#endif
#if FALSE // #ifdef Logging
sprintf(buf, "dcid: %d", new_comp_id);
KP_TRACE(buf);
#endif
      }
#endif

   } // if((comp_id_mode & KPST_COMPID_BIOS_DATE) && SUCCEEDED(retc))


// --------------------------- Disk serial No.
   if((comp_id_mode & KPST_COMPID_DISK_ID) && SUCCEEDED(retc))
   {
#if TRUE // #if FALSE
unsigned char disk_label_buf[KP_MAX_FNAME_LEN+1];

      if(SUCCEEDED(retc)) retc = GetDiskInfo((unsigned char *)"C:\\", &cur_comp_id, disk_label_buf);

      if(SUCCEEDED(retc)) new_comp_id += cur_comp_id; // !!!! gali persipildyt
#else
//    new_comp_id = getHardDriveComputerID();
      new_comp_id += getHardDriveComputerID(); // !!!! gali persipildyt
#endif
   } // if((comp_id_mode & KPST_COMPID_DISK_ID) && SUCCEEDED(retc))


// --------------------------- Pentium proc. ID
   if((comp_id_mode & KPST_COMPID_PROC_ID) && SUCCEEDED(retc))
   {
      cur_comp_id = 0;

#if FALSE
// neduoda jokios unikalios informacijos - tiesiog proco parametrai ir tiek
      __asm
      {
         push eax
         push ebx
         push ecx
         push edx

         mov eax, 0
         cpuid
         mov cur_comp_id, eax

         pop edx
         pop ecx
         pop ebx
         pop eax
      }
#endif

#if FALSE
// valid for Pentium III only
int proc_id_low = 0;
int proc_id_high = 0;
      __asm
      {
         push eax
         push ebx
         push ecx
         push edx

         mov eax, 3
         mov ecx, 0
         mov edx, 0
         cpuid
         mov proc_id_low, ecx
         mov proc_id_high, edx

         pop edx
         pop ecx
         pop ebx
         pop eax
      }

      new_comp_id = proc_id_low; // +proc_id_high;
#endif

      if(SUCCEEDED(retc)) new_comp_id += cur_comp_id; // !!!! gali persipildyt

   } // if((comp_id_mode & KPST_COMPID_PROC_ID) && SUCCEEDED(retc))


// --------------------------- ProcName
   if((comp_id_mode & KPST_COMPID_PROC_NAME) && SUCCEEDED(retc))
   {
unsigned char proc_name_buf[KP_MAX_FNAME_LEN + 1];
unsigned char *pntd;

      if(SUCCEEDED(retc)) retc = GetProcName(proc_name_buf);

      if(SUCCEEDED(retc))
      {
         pntd = proc_name_buf;
         while(*pntd)
         {
            new_comp_id += *pntd;
            new_comp_id = new_comp_id % KPSTA_COMPID_SIGNIF;

            pntd++;
         }
      }

   } // if((comp_id_mode & KPST_COMPID_PROC_NAME) && SUCCEEDED(retc))


// -------------------------- suspaudþiam iki FizID
// if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID); // negalima - mes jau RC threade
   comp_id = cMemBank[KP11_COMPID/2];
#if FALSE // #ifdef Logging
static char str_buf[1000];
sprintf(str_buf, "[phys 3] %d %d", new_comp_id, comp_id);
KP_WARNING0(S_OK, str_buf);
#endif
   if(SUCCEEDED(retc)) new_comp_id = NormalizeCompId(new_comp_id);
#if FALSE // #ifdef Logging
sprintf(str_buf, "[phys 4] %d", new_comp_id);
KP_WARNING0(S_OK, str_buf);
#endif
#if FALSE // #ifdef Logging
char buf[50];
sprintf(buf, "dcidn: %d", new_comp_id);
KP_TRACE(buf);
#endif

// --------------------------- gràþinam FizID
   if((plPhysWithoutBolt != NULL) && SUCCEEDED(retc)) *plPhysWithoutBolt = new_comp_id;

// --------------------------- Varþtas
   if((comp_id_mode & KPST_COMPID_BOLT) && SUCCEEDED(retc)) retc = AddBolt(&new_comp_id);

// --------------------------- atnaujinam, tik jei pasikeitë (padidëjo)
   if(SUCCEEDED(retc))
   {
      if((new_comp_id > comp_id /* m_iCompId */) || ((new_comp_id / 10) < (comp_id / 10)) /* (new_comp_id <= comp_id - 10) */) // tik 10 ismetimu !!!
//    if((new_comp_id / 10) != (comp_id / 10))
      {
//       m_iCompId=new_comp_id;
//       retc=EmuTv.SetHp11Variable(new_comp_id, KP11_COMPID);
         cMemBank[KP11_COMPID/2] = (short)new_comp_id;
      }
   }
#if FALSE // #ifdef Logging
sprintf(str_buf, "[phys 5] %d", cMemBank[KP11_COMPID/2]);
KP_WARNING0(S_OK, str_buf);
#endif
#if FALSE // #ifdef Logging
char buf[50];
sprintf(buf, "cid: %d", cMemBank[KP11_COMPID/2]);
KP_TRACE(buf);
#endif

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetTimCompId(void)
{
HRESULT retc=S_OK;
time_t ltime;
int comp_id=0;

// m_iCompId=0;

   time(&ltime);

   comp_id /* m_iCompId */ = NormalizeCompId(ltime);

// if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(comp_id, KP11_COMPID);
   cMemBank[KP11_COMPID/2] = comp_id;

return(retc);
}


//----------------------------------------
void PackBIOSDate(unsigned char *lpszOutBuf,
                  const unsigned char *lpszInBuf)
{
unsigned char *pntd;

   pntd=lpszOutBuf;
   if(atoi((const char *)lpszInBuf+6)>81)
   {
      (*pntd++)='1';
      (*pntd++)='9';
   }
   else
   {
      (*pntd++)='2';
      (*pntd++)='0';
   }
   (*pntd++)=lpszInBuf[6];
   (*pntd++)=lpszInBuf[7];
   (*pntd++)='.';
   (*pntd++)=lpszInBuf[0];
   (*pntd++)=lpszInBuf[1];
   (*pntd++)='.';
   (*pntd++)=lpszInBuf[3];
   (*pntd++)=lpszInBuf[4];
   (*pntd++)=Nul;
}


HRESULT GetBIOSDate(unsigned char *lpszDatBuf)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
MSWin32Version win_ver;
unsigned char str_buf[BIOS_DAT_SIZE+1];
#if (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HKEY hKey=NULL;
char szBiosDate[BIOS_DAT_BUF_SIZE + 1];
DWORD dwBufLen;
DWORD dwValType;
#endif
unsigned char key_name[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszDatBuf, E_INVALIDARG, null, True);

   if (SUCCEEDED(retc)) strcpy(lpszDatBuf, "XXXX.XX.XX");

#if (Envir==MSDos) || (Envir==MSDosCon)
   if (SUCCEEDED(retc))
   {
      strncpy(str_buf, (char *)0xffff5, 8);
      str_buf[8]=0;
      PackBIOSDate(lpszDatBuf, str_buf);
   }
#elif (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)

   if (SUCCEEDED(retc)) win_ver=iWindowsVersion;

   if (SUCCEEDED(retc))
   {
      if (win_ver < WinNT)
      {
         strncpy(str_buf, (char *)0xffff5, 8);
         str_buf[8]=0;
         PackBIOSDate(lpszDatBuf, str_buf);
      }
      else
      {
//       strcpy(key_name, "HARDWARE\\DESCRIPTION\\System");
         key_name[ 0] = 'H';
         key_name[ 1] = 'A';
         key_name[ 2] = 'R';
         key_name[ 3] = 'D';
         key_name[ 4] = 'W';
         key_name[ 5] = 'A';
         key_name[ 6] = 'R';
         key_name[ 7] = 'E';
         key_name[ 8] = '\\';
         key_name[ 9] = 'D';
         key_name[10] = 'E';
         key_name[11] = 'S';
         key_name[12] = 'C';
         key_name[13] = 'R';
         key_name[14] = 'I';
         key_name[15] = 'P';
         key_name[16] = 'T';
         key_name[17] = 'I';
         key_name[18] = 'O';
         key_name[19] = 'N';
         key_name[20] = '\\';
         key_name[21] = 'S';
         key_name[22] = 'y';
         key_name[23] = 's';
         key_name[24] = 't';
         key_name[25] = 'e';
         key_name[26] = 'm';
         key_name[27] = Nul;

         retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
         if (retw != ERROR_SUCCESS)
         {
            hKey = NULL;
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }

         if (SUCCEEDED(retc))
         {
            dwBufLen = BIOS_DAT_BUF_SIZE;

//          strcpy(key_name, "SystemBiosDate");
            key_name[ 0] = 'S';
            key_name[ 1] = 'y';
            key_name[ 2] = 's';
            key_name[ 3] = 't';
            key_name[ 4] = 'e';
            key_name[ 5] = 'm';
            key_name[ 6] = 'B';
            key_name[ 7] = 'i';
            key_name[ 8] = 'o';
            key_name[ 9] = 's';
            key_name[10] = 'D';
            key_name[11] = 'a';
            key_name[12] = 't';
            key_name[13] = 'e';
            key_name[14] = Nul;

            retw=RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE) szBiosDate, &dwBufLen);
            if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
            {
               szBiosDate[0] = Nul;
//             if (iWindowsVersion < Win8)
//                retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
               retc = KP_E_SYSTEM_ERROR;
            }
            else szBiosDate[dwBufLen] = Nul;
         }

         if (FAILED(retc)) // if (iWindowsVersion >= Win8)
         {
            retc = S_OK;

            if (hKey)
            {
               retw = RegCloseKey(hKey);
//             if(retw != ERROR_SUCCESS) retc = KP_E_SYSTEM_ERROR;
#ifdef Debug
               if(retw != ERROR_SUCCESS)
                  KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
               hKey = NULL;
            }

//          strcpy(key_name, "HARDWARE\\DESCRIPTION\\System\\BIOS");
            key_name[ 0] = 'H';
            key_name[ 1] = 'A';
            key_name[ 2] = 'R';
            key_name[ 3] = 'D';
            key_name[ 4] = 'W';
            key_name[ 5] = 'A';
            key_name[ 6] = 'R';
            key_name[ 7] = 'E';
            key_name[ 8] = '\\';
            key_name[ 9] = 'D';
            key_name[10] = 'E';
            key_name[11] = 'S';
            key_name[12] = 'C';
            key_name[13] = 'R';
            key_name[14] = 'I';
            key_name[15] = 'P';
            key_name[16] = 'T';
            key_name[17] = 'I';
            key_name[18] = 'O';
            key_name[19] = 'N';
            key_name[20] = '\\';
            key_name[21] = 'S';
            key_name[22] = 'y';
            key_name[23] = 's';
            key_name[24] = 't';
            key_name[25] = 'e';
            key_name[26] = 'm';
            key_name[27] = '\\';
            key_name[28] = 'B';
            key_name[29] = 'I';
            key_name[30] = 'O';
            key_name[31] = 'S';
            key_name[32] = Nul;

            retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
            if(retw != ERROR_SUCCESS)
            {
               hKey = NULL;
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
            {
               dwBufLen = BIOS_DAT_BUF_SIZE;

//             strcpy(key_name, "BIOSReleaseDate");
               key_name[ 0] = 'B';
               key_name[ 1] = 'I';
               key_name[ 2] = 'O';
               key_name[ 3] = 'S';
               key_name[ 4] = 'R';
               key_name[ 5] = 'e';
               key_name[ 6] = 'l';
               key_name[ 7] = 'e';
               key_name[ 8] = 'a';
               key_name[ 9] = 's';
               key_name[10] = 'e';
               key_name[11] = 'D';
               key_name[12] = 'a';
               key_name[13] = 't';
               key_name[14] = 'e';
               key_name[15] = Nul;

               retw = RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE) szBiosDate, &dwBufLen);
               if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
               {
                  szBiosDate[0] = Nul;
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
               }
               else szBiosDate[dwBufLen] = Nul;
            }
         }

         if (hKey)
         {
            retw = RegCloseKey(hKey);
//          if(retw != ERROR_SUCCESS) retc = KP_E_SYSTEM_ERROR;
#ifdef Debug
            if(retw != ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            hKey = NULL;
         }

         if(SUCCEEDED(retc))
         {
            PackBIOSDate(lpszDatBuf, (const unsigned char *)szBiosDate);
         }

      } // else // if(win_ver < WinNT)

   } // if(SUCCEEDED(retc))

#else

   if(SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKNOWN_SYSTEM, null, True, __FILE__, __LINE__, 0L);

#endif

return(retc);
}


HRESULT GetProcName(unsigned char *lpszNameBuf)
{
HRESULT retc = S_OK;
LONG retw = ERROR_SUCCESS;
unsigned char key_name[KP_MAX_FNAME_LEN + 1];
HKEY hKey = NULL;
DWORD dwBufLen;
DWORD dwValType;

   KP_ASSERT(lpszNameBuf, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) *lpszNameBuf = Nul;

   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "HARDWARE\DESCRIPTION\System\CentralProcessor\0");
      key_name[0] = 'H';
      key_name[1] = 'A';
      key_name[2] = 'R';
      key_name[3] = 'D';
      key_name[4] = 'W';
      key_name[5] = 'A';
      key_name[6] = 'R';
      key_name[7] = 'E';
      key_name[8] = '\\';
      key_name[9] = 'D';
      key_name[10] = 'E';
      key_name[11] = 'S';
      key_name[12] = 'C';
      key_name[13] = 'R';
      key_name[14] = 'I';
      key_name[15] = 'P';
      key_name[16] = 'T';
      key_name[17] = 'I';
      key_name[18] = 'O';
      key_name[19] = 'N';
      key_name[20] = '\\';
      key_name[21] = 'S';
      key_name[22] = 'y';
      key_name[23] = 's';
      key_name[24] = 't';
      key_name[25] = 'e';
      key_name[26] = 'm';
      key_name[27] = '\\';
      key_name[28] = 'C';
      key_name[29] = 'e';
      key_name[30] = 'n';
      key_name[31] = 't';
      key_name[32] = 'r';
      key_name[33] = 'a';
      key_name[34] = 'l';
      key_name[35] = 'P';
      key_name[36] = 'r';
      key_name[37] = 'o';
      key_name[38] = 'c';
      key_name[39] = 'e';
      key_name[40] = 's';
      key_name[41] = 's';
      key_name[42] = 'o';
      key_name[43] = 'r';
      key_name[44] = '\\';
      key_name[45] = '0';
      key_name[46] = Nul;

      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
      KP_ASSERT(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, True);
   }

   if(SUCCEEDED(retc))
   {
      dwBufLen = KP_MAX_FNAME_LEN;

//    strcpy(key_name, "ProcessorNameString");
      key_name[0]='P';
      key_name[1]='r';
      key_name[2]='o';
      key_name[3]='c';
      key_name[4]='e';
      key_name[5]='s';
      key_name[6]='s';
      key_name[7]='o';
      key_name[8]='r';
      key_name[9]='N';
      key_name[10]='a';
      key_name[11]='m';
      key_name[12]='e';
      key_name[13]='S';
      key_name[14]='t';
      key_name[15]='r';
      key_name[16]='i';
      key_name[17]='n';
      key_name[18]='g';
      key_name[19]=Nul;

      retw = RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)lpszNameBuf, &dwBufLen);
//    KP_ASSERT((dwValType == REG_SZ) && (retw == ERROR_SUCCESS), KP_E_SYSTEM_ERROR, retw, True);
      if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS)){ dwBufLen = 0L; lpszNameBuf[0] = Nul; }
   }
   if(SUCCEEDED(retc)) lpszNameBuf[dwBufLen] = Nul;
   else lpszNameBuf[0] = Nul;

   if(hKey)
   {
      retw = RegCloseKey(hKey);
#ifdef Debug
      KP_ASSERT(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, null, False);
#endif
      hKey=NULL;
   }

return(retc);
}


//-------------------------------------------- get disk serial number and label
HRESULT GetDiskInfo(const unsigned char *lpszVolName, long *plSerNum, unsigned char *lpszLabel)
{
HRESULT retc=S_OK;

   lpszLabel[0]=Nul;
   *plSerNum=0L;

#if FALSE

unsigned char str_buf[100];
short disk_no;
union
{
   struct
   {
      short midInfoLevel;                // information level
      long midSerialNum;                 // serial number
      unsigned char midVolLabel[11];     // ASCII volume label
      unsigned char midFileSysType[8];   // file system type
   } main;
   short loc;
} MediaID;

long r_ebp=0;
short r_bp=0;
short r_ss=0;

   lpszLabel[0]=Nul;
   *plSerNum=0L;

   MediaID.main.midSerialNum=0;
   MediaID.main.midVolLabel[0]=Nul;

   disk_no=iDiskNo;
   MediaID.main.midInfoLevel=0;

   _asm
   {
      push  ax
      push  bx
      push  cx
      push  dx
      push  ds

      mov   bx, disk_no
      mov   ch, 08h              ;DeviceCat
      mov   cl, 66h              ;Get Media ID

;     mov   dx, seg MediaID
      mov   dx, ss
      mov   ds, dx

;     mov   dx, offset MediaID   ;ds:dx points to MID structure
      mov   dx, bp
      sub   dx, 88h              ; offset of MediaID !!!

      mov   ax, 440Dh            ;IOCTL for block device
      int   21h

      jnc   GetDiskInfo_success
      mov   retc, 80040306h     ; KP_E_SYSTEM_ERROR !!!

GetDiskInfo_success:
      pop   ds
      pop   dx
      pop   cx
      pop   bx
      pop   ax



      mov   r_ebp, ebp
      mov   r_bp, bp
      mov   r_ss, ss
   }

   if(FAILED(retc))
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);


BOOL SetVolumeLabel(
  LPCTSTR lpRootPathName,  // pointer to name of root directory for
                           // volume
  LPCTSTR lpVolumeName   // name for the volume
);



#if FALSE
   sprintf((char *)str_buf, "ebp: %x bp: %x ss: %x ss:bp: %x", r_ebp, r_bp, r_ss, (r_ss<<8)+r_bp);
   KpMsgOut(str_buf, KP_MB_TESTI);



   sprintf((char *)str_buf, "ser_no: %d", MediaID.main.midSerialNum);
   KpMsgOut(str_buf, KP_MB_TESTI);

   strncpy(str_buf, MediaID.main.midVolLabel, 11);
   str_buf[11]=Nul;
   KpMsgOut(str_buf, KP_MB_TESTI);
#endif


// ------------------------------------
char vol_name[20+1];
unsigned long ser_no;

   if(!GetVolumeInformation("e:\\", vol_name, 20, &ser_no, &max_fn_len, &sys_fl, fs_name, 100)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

#endif

unsigned long max_fn_len;
unsigned long sys_fl;
char fs_name[KP_MAX_FNAME_LEN+1];

   if(!GetVolumeInformation((const char *)lpszVolName, (char *)lpszLabel, KP_MAX_FNAME_LEN, (unsigned long *)plSerNum, &max_fn_len, &sys_fl, fs_name, KP_MAX_FNAME_LEN)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL  );

return(retc);
}


// ------------------------------
HRESULT KpStApp::IncCompID(void)
{
HRESULT retc=S_OK;

#if FALSE
int comp_id=0;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);

   if(SUCCEEDED(retc))
   {
//    m_iInstCount=(m_iInstCount+1) & 0xFFFF /* % 10 */;
      comp_id /* m_iCompId */ = (comp_id /* m_iCompId */ + 1) & 0xFFFF /* % 10 */;
   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(comp_id, KP11_COMPID);
#endif

static KpRcPars rc_pars;
   rc_pars.iOpCode = KP_RC_INC_COMPID;
   rc_pars.iParBlSize=sizeof(rc_pars);

// PutLogMessage_("KpStApp::ICI ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ResetSystemTime(SYSTEMTIME *p_TtPtr /* *p_StPtr */)
{
HRESULT retc=S_OK;
// MSWin32Version win_vers;
// int max_day;

   KP_ASSERT(p_TtPtr /* p_StPtr */, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
#if FALSE
// ------------------------- remember current system time
      GetSystemTime(p_StPtr);
//    GetLocalTime(p_StPtr);

      win_vers = iWindowsVersion;

      if((win_vers == Win98c) || (win_vers == Win98) || (win_vers == Win98SE))
      {
// ----------------------------------------------- increment hour - error of Win98 - only in summer time !!!!
         p_StPtr->wHour++;
         if(p_StPtr->wHour>23)
         {
            p_StPtr->wHour=0;
            p_StPtr->wDayOfWeek++; if(p_StPtr->wDayOfWeek>6) p_StPtr->wDayOfWeek=0;
            p_StPtr->wDay++;
            switch(p_StPtr->wMonth)
            {
            case 1: max_day=31; break;
            case 2: max_day=28; if((p_StPtr->wYear%4==0) && (p_StPtr->wYear%100!=0)) max_day=29; break;
            case 3: max_day=31; break;
            case 4: max_day=30; break;
            case 5: max_day=31; break;
            case 6: max_day=30; break;
            case 7: max_day=31; break;
            case 8: max_day=31; break;
            case 9: max_day=30; break;
            case 10: max_day=31; break;
            case 11: max_day=30; break;
            case 12: max_day=31; break;
            default: max_day=31; break;
            }
            if(p_StPtr->wDay>max_day)
            {
               p_StPtr->wDay=1;
               p_StPtr->wMonth++;
               if(p_StPtr->wMonth>12)
               {
                  p_StPtr->wMonth=1;
                  p_StPtr->wYear++;
               }
            }
         }
      }
#endif

// ---------------------------------------
      p_TtPtr->wYear  = 2002; // = 1998;
      p_TtPtr->wMonth = 2;
      p_TtPtr->wDay   = 28;
      p_TtPtr->wDayOfWeek = 0;
      p_TtPtr->wHour   = 17;
      p_TtPtr->wMinute = 18;
      p_TtPtr->wSecond = 19;
      p_TtPtr->wMilliseconds = 0;

//    SetSystemTime(p_TtPtr);

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
HRESULT KpStApp::CreateRegPath(const SYSTEMTIME *p_TtPtr, unsigned char *lpszPath)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
const unsigned char *sys_drive;

   KP_ASSERT(lpszPath, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      retc = CreatePath(lpszPath, False);
      if(retc == KP_E_DIR_ERROR)
      {
         retc = S_OK;
         sys_drive = (unsigned char *)getenv("SystemDrive");
         KP_ASSERT(sys_drive != NULL, KP_E_SYSTEM_ERROR, null, False);
         if(SUCCEEDED(retc))
         {
            lpszPath[0] = sys_drive[0];
            retc = CreatePath(lpszPath, False);
         }
      }
      else if(FAILED(retc)) KP_WARNING(retc, null);
   }

// if(SUCCEEDED(retcf))
// if(!_mkdir((const char *)lpszPath))
// {
      retc0 = ChFileTimeCrtd(lpszPath, p_TtPtr);
//    if(SUCCEEDED(retcf)) retcf = retc0;
//    if(SUCCEEDED(retc)) retc = retc0;
// }

#if FALSE
   if(bForceAdmin && SUCCEEDED(retc))
   {
//    !!!! TODO
      DWORD SetNamedSecurityInfo(
         (char *)key_name, // LPTSTR pObjectName,
         SE_FILE_OBJECT,   // SE_OBJECT_TYPE ObjectType,
         DACL_SECURITY_INFORMATION, // SECURITY_INFORMATION SecurityInfo,
         NULL,             // PSID psidOwner,
         NULL,             // PSID psidGroup,
         PACL pDacl,       // PACL pDacl,
         NULL              // PACL pSacl
         );

      KP_ASSERT(False, KP_E_DIR_ERROR, null, False);
      if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
   }
#endif

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetRegSecData(HKEY hQueryKey, const unsigned char *lpszSubKey, const unsigned char *lpszVariable, long *plValPtr)
{
HRESULT retc = S_OK;
LONG retw = ERROR_SUCCESS;
HKEY res_key = 0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwBufLen;
DWORD dwValType;

   KP_ASSERT(lpszSubKey, E_INVALIDARG, null, True);
   KP_ASSERT(plValPtr, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      retw=RegOpenKeyEx(hQueryKey,
         (LPCTSTR)lpszSubKey,
         0, KEY_QUERY_VALUE, &res_key);
      if(retw!=ERROR_SUCCESS)
      {
         retc = KP_E_KWD_NOT_FOUND;
#ifdef Debug
//       KP_ASSERT(KP_E_KWD_NOT_FOUND, null, False);
#endif
      }
   }

// --------------------
   if(SUCCEEDED(retc))
   {
      *plValPtr = 0L;

      key_buf[0] = Nul;

      dwBufLen = KP_MAX_FILE_LIN_WDT;
      retw = RegQueryValueEx(res_key, (const char *)lpszVariable, NULL, &dwValType, (LPBYTE)key_buf, &dwBufLen);
      if((dwValType != REG_SZ) || (retw!=ERROR_SUCCESS))
      {
         key_buf[0] = Nul;
         retc = KP_E_KWD_NOT_FOUND;
#ifdef Debug
         KP_WARNING(KP_E_KWD_NOT_FOUND, retw);
#endif
      }
      else key_buf[dwBufLen] = Nul;
   }

   if(SUCCEEDED(retc))
   {
#if FALSE // #ifdef Logging
char buf[100];
sprintf(buf, "rcid: %s", key_buf);
KP_TRACE(buf);
#endif
      sscanf((const char *)key_buf, "%lx", plValPtr);
   }

   if(res_key)
   {
      retw = RegCloseKey(res_key);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      KP_ASSERT(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, null, False);
#endif
      res_key = NULL;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetRegCompID(HKEY hQueryKey, const unsigned char *lpszSubKey, int iProdVer, int *piIdOut)
{
HRESULT retc = S_OK;
long id_val = 0L;

   KP_ASSERT(lpszSubKey, E_INVALIDARG, null, True);
   KP_ASSERT(piIdOut, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      *piIdOut = 0;

      retc = GetRegSecData(hQueryKey, lpszSubKey, (const unsigned char *)"EstDispl", &id_val);

      if(retc == KP_E_KWD_NOT_FOUND)
      {
         retc = S_OK;
         id_val = 0L;
      }

      if(SUCCEEDED(retc))
      {
         *piIdOut = (id_val ^ iProdVer) / 10;

#if FALSE // #ifdef Logging
sprintf(buf, "rcidn: %d", *piIdOut);
KP_TRACE(buf);
#endif
      }

   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedCompIDFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, int iProdVer, int *p_comp_id)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
#ifdef KPST_WINDOWS_INTERFACE
DWORD read;
HANDLE in_file = INVALID_HANDLE_VALUE;
#else
FILE *in_file = NULL;
#endif
int cnt1;

   KP_ASSERT(lpszPath != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPath[0] != Nul, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszPath) + 1 + strlen(KPST_CNT_REG_PATH_11) < KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
   KP_ASSERT(pkg_name != null, E_INVALIDARG, null, True);
   KP_ASSERT(p_comp_id != NULL, E_INVALIDARG, null, True);

   strcpy(key_name, lpszPath);
   if(key_name[strlen(key_name) - 1] != '\\') strcat(key_name, "\\");
   strcat(key_name, KPST_CNT_REG_PATH_11);
   strcat(key_name, KPST_CNT_REG_PATH_2);
   strcat(key_name, pkg_name);
// strcat((char *)key_name, "\\cbdata");
// strcat(key_name, " ");
#if FALSE // #ifdef Logging
strcpy(str_buf, key_name);
sprintf(str_buf_1, "[saved 7.1] %s", str_buf + 89);
KP_WARNING0(S_OK, str_buf_1);
#if FALSE
str_buf[20] = Nul;
sprintf(str_buf_1, "[saved 7.2] %s", str_buf + 10);
KP_WARNING0(S_OK, str_buf_1);
str_buf[10] = Nul;
sprintf(str_buf_1, "[saved 7.3] %s", str_buf);
KP_WARNING0(S_OK, str_buf_1);
#endif
#endif

#ifdef KPST_WINDOWS_INTERFACE
   in_file = CreateFile((const char *)key_name, GENERIC_READ, FILE_SHARE_READ,
         0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   if(in_file == INVALID_HANDLE_VALUE)
#else
   in_file = fopen((const char *)key_name, "rb");
   if(in_file == NULL)
#endif
   {
//    retc=KP_E_KWD_NOT_FOUND; // KP_E_FILE_NOT_FOUND
//    KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FILE_NOT_FOUND */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
   }
   else
   {
#ifdef KPST_WINDOWS_INTERFACE
      if(!ReadFile(in_file, &cnt1, sizeof(cnt1), &read, NULL))
#else
//    fscanf(in_file, "%x", &cnt1);
      fread(&cnt1, sizeof(cnt1), 1, in_file);
      if(ferror(in_file) || feof(in_file))
#endif
      {
//       retc=KP_E_KWD_NOT_FOUND; // KP_E_FERROR
//       KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FERROR */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
      }
      else
      {
         retc=S_OK;
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 8] %d", cnt1);
KP_WARNING0(S_OK, str_buf_1);
#endif
#if FALSE // #ifdef Debug // #ifdef Logging
char buf[100];
sprintf(buf, "%s fcid: %d %x", key_name, cnt1, cnt1);
KpMsgOut(buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KP_TRACE(buf);
#endif
         cnt1^=iProdVer;
         cnt1/=10;
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 9] %d", cnt1);
KP_WARNING0(S_OK, str_buf_1);
#endif
#if FALSE // #ifdef Debug // #ifdef Logging
sprintf(buf, "fcidn: %d", cnt1);
KpMsgOut(buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KP_TRACE(buf);
#endif
//       if(cnt1>m_iInstCount) m_iInstCount=cnt1;
         if(cnt1 > *p_comp_id /* m_iCompId */) *p_comp_id /* m_iCompId */ = cnt1;
                                                   // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                                                   // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 10] %d", *p_comp_id);
KP_WARNING0(S_OK, str_buf_1);
#endif
#ifdef Debug // #if TRUE //
#if FALSE // #if TRUE // #ifdef DebugStop
// KpMsgOutF("%s GetSavedCompIDFileSingle() retc:%x cnt1:%d cid:%d", key_name, retc, cnt1, *p_comp_id);
PutLogMessage_("GSCIFS(): %s %x %d %d", key_name, retc, cnt1, *p_comp_id);
#endif
#endif
      }

#ifdef KPST_WINDOWS_INTERFACE
      if(!CloseHandle(in_file))
#else
      if(fclose(in_file))
#endif
      {
         if(SUCCEEDED(retc))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//          retc=KP_E_SYSTEM_ERROR;
         }
      }

   } // else // if(in_file==NULL)

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedCompIDprodVer(int iProdVer, int *piCompId)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int comp_id = 0;
int cnt1;

   KP_ASSERT(piCompId, E_INVALIDARG, True, null);

// ------------------------------
   if(SUCCEEDED(retc))
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, iProdVer);
#if FALSE // #ifdef Logging
static unsigned char str_buf[1000];
static char str_buf_1[1000];
strcpy(str_buf, pkg_name);
sprintf(str_buf_1, "[saved 1.1] %s", str_buf + 31);
KP_WARNING0(S_OK, str_buf_1);
#if FALSE
str_buf[20] = Nul;
sprintf(str_buf_1, "[saved 1.2] %s", str_buf + 10);
KP_WARNING0(S_OK, str_buf_1);
str_buf[10] = Nul;
sprintf(str_buf_1, "[saved 1.3] %s", str_buf);
KP_WARNING0(S_OK, str_buf_1);
#endif
#endif

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);
#if FALSE // ifdef Logging
strcpy(str_buf, key_name);
sprintf(str_buf_1, "[saved 2.1] %s", str_buf + 89);
KP_WARNING0(S_OK, str_buf_1);
#if FALSE
str_buf[20] = Nul;
sprintf(str_buf_1, "[saved 2.2] %s", str_buf + 10);
KP_WARNING0(S_OK, str_buf_1);
str_buf[10] = Nul;
sprintf(str_buf_1, "[saved 2.3] %s", str_buf);
KP_WARNING0(S_OK, str_buf_1);
#endif
#endif
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "strlen(key_name): %d", strlen(key_name));
KP_TRACE(str_buf);
#endif

      retc0=GetRegCompID(HKEY_LOCAL_MACHINE, key_name, iProdVer, &cnt1);
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 3] %d", cnt1);
KP_WARNING0(S_OK, str_buf_1);
#endif
      if(SUCCEEDED(retc0)) if(cnt1 > comp_id /* m_iCompId */) comp_id /* m_iCompId */ = cnt1;
                // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 4] %d", comp_id);
KP_WARNING0(S_OK, str_buf_1);
#endif
#ifdef Debug // #if TRUE //
#if FALSE // #if TRUE // #ifdef DebugStop
// KpMsgOutF("%s GetSavedCID global retc:%x cnt1:%d cid:%d", key_name, retc, cnt1, comp_id);
PutLogMessage_("GSCIR() global: %s %x %d %d", key_name, retc, cnt1, comp_id);
#endif
#endif

      retc0=GetRegCompID(HKEY_CURRENT_USER, key_name, iProdVer, &cnt1);
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 5] %d", cnt1);
KP_WARNING0(S_OK, str_buf_1);
#endif
      if(SUCCEEDED(retc0)) if(cnt1 > comp_id /* m_iCompId */) comp_id /* m_iCompId */=cnt1;
                // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino
#if FALSE // #ifdef Logging
sprintf(str_buf_1, "[saved 6] %d", comp_id);
KP_WARNING0(S_OK, str_buf_1);
#endif
#ifdef Debug // #if TRUE //
#if FALSE // #if TRUE // #ifdef DebugStop
// KpMsgOutF("%s GetSavedCID local retc:%x cnt1:%d cid:%d", key_name, retc, cnt1, comp_id);
PutLogMessage_("GSCIR() local: %s %x %d %d", key_name, retc, cnt1, comp_id);
#endif
#endif

   }

// -------------------- files
   if(SUCCEEDED(retc) || (retc == KP_E_KWD_NOT_FOUND))
   {
      retc = GetSavedCompIDFileSingle(KPST_CNT_REG_PATH_1, pkg_name, iProdVer, &comp_id);

      retc0 = S_OK;

const unsigned char *all_users_profile = (unsigned char *)getenv("ALLUSERSPROFILE");
      KP_ASSERT0E(all_users_profile != NULL, KP_E_SYSTEM_ERROR, null, False);
      KP_ASSERT0E(all_users_profile[0] != Nul, KP_E_SYSTEM_ERROR, null, False);

      if(SUCCEEDED(retc0)) retc0 = GetSavedCompIDFileSingle(all_users_profile, pkg_name, iProdVer, &comp_id);
      KP_ASSERTE(SUCCEEDED(retc0), retc0, null, False);

      if(SUCCEEDED(retc)) retc = retc0;

   } // if(SUCCEEDED(retc) || (retc==KP_E_KWD_NOT_FOUND))

#ifdef Debug
#if FALSE // #if TRUE // #ifdef DebugStop
KpMsgOutF("GetSavedCID galas retc:%x cid:%d", retc, comp_id);
#endif
#endif

   if(SUCCEEDED(retc)) *piCompId = comp_id;

return(retc);
}



// ------------------------------
HRESULT KpStApp::GetSavedCompID(void)
{
HRESULT retc=S_OK;
int prod_ver=0;
int comp_id = 0;
int comp_id_1 = 0;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetSavedCID pradzia", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// m_iInstCount=0;
// m_iCompId=0;
// if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_COMPID);
   cMemBank[KP11_COMPID/2] = 0;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = GetSavedCompIDprodVer(prod_ver, &comp_id);

   if((prod_ver == 6010) && SUCCEEDED(retc))
   {
      retc = GetSavedCompIDprodVer(2010, &comp_id_1);
      if((comp_id_1 > comp_id) && SUCCEEDED(retc)) comp_id = comp_id_1;
   }

// if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(comp_id, KP11_COMPID);
   cMemBank[KP11_COMPID/2] = comp_id;

return(retc);
}


// ------------------------------
HRESULT GetCommonCompID_RC(void *pKpStAppObjPtr)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
bool ci_direct = False;
int num_of_lics = 0;
bool bound = False;
KpStApp *this_ptr = (KpStApp *)pKpStAppObjPtr;
#ifndef AllwaysCid
int comp_id = 0;
#endif

   if((pKpStAppObjPtr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = this_ptr->GetIniCiDirect(&ci_direct);
   if(SUCCEEDED(retc)) retc = this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = this_ptr->GetIniBound(&bound);

   if(SUCCEEDED(retc))
   {
      if(num_of_lics && (this_ptr->m_iKpStMode == KpStarterMode))
         retc = this_ptr->GetTimCompId();
      else
      {
#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetCommonCID pradzia", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#if FALSE
/*       retc0 = */ this_ptr->GetSavedCnt(); // if(SUCCEEDED(retc)) retc=retc0;
         retc0 = this_ptr->GetCompId(); if(SUCCEEDED(retc)) retc = retc0;
#else
//       this_ptr->m_iCompId=0;
//       if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_COMPID);
         cMemBank[KP11_COMPID/2] = 0;

         if(bound && SUCCEEDED(retc))
         {
            retc0 = this_ptr->GetSavedCompID(); if(SUCCEEDED(retc)) retc = retc0;
#if TRUE // #ifdef Logging // #if FALSE //
PutLogMessage_("[RC 1] saved %d", cMemBank[KP11_COMPID/2]);
#endif

#ifndef AllwaysCid
//          if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
            comp_id = cMemBank[KP11_COMPID/2];
            if(((comp_id /* this_ptr->m_iCompId */ == 0) || ci_direct) && SUCCEEDED(retc))
#endif
            {
               if(SUCCEEDED(retc))
               {
#ifndef AllwaysCid
                  if(ci_direct)
#endif
                  {
// atnaujina m_iCompID tik jei netelpa á ribas [comp_id - 10, comp_id] (comp_id – kol kas perskaitytas su GetSavedCompID())
                     retc0 = this_ptr->GetPhysCompId();
#if TRUE // #ifdef Logging // #if FALSE //
PutLogMessage_("[RC 2] phys %d", cMemBank[KP11_COMPID/2]);
#endif
                     if(SUCCEEDED(retc)) retc=retc0;
                  }
#ifndef AllwaysCid
                  else
                  {
                     KP_ASSERT(this_ptr->m_iKpStMode != KpStarterMode, KP_E_NOTINST, null, False);
                     retc = S_OK;
                  }
#endif
               }
            }
            if(ci_direct) retc0 = this_ptr->SaveCompID(False); if(SUCCEEDED(retc)) retc=retc0;

#endif // #else // #if FALSE

         } // if(bound && SUCCEEDED(retc))

      } // else // if(num_of_lics && (this_ptr->m_iKpStMode == KpStarterMode))

   } // if(SUCCEEDED(retc))

// #ifdef Debug
// if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
// #endif
   retc = S_OK;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetCommonCID galas", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#ifdef Debug
// cMemBank[KP11_COMPID/2]=1800;
#endif

#ifdef Logging
PutLogMessage_("[RC 3] %d", cMemBank[KP11_COMPID/2]);
#endif

return(retc);
}


// ------------------------------------------
HRESULT KpStApp::SaveRegSecData(HKEY hQueryKey, const unsigned char *lpszSubKey, const unsigned char *lpszVariable, long lValue)
{
HRESULT retc = S_OK;
LONG retw = ERROR_SUCCESS;
HKEY res_key = 0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT + 1];
DWORD dwDisposition;

   KP_ASSERT(lpszSubKey, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      retw = RegCreateKeyEx(hQueryKey, (LPCTSTR)lpszSubKey,
         0, NULL /* "" */, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw != ERROR_SUCCESS)
      {
         retc = KP_E_ACCESS_DENIED;
         KP_ERRORWE(retc, retw, False);
//       KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
      }
   }

// --------------------
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_buf, "%x", lValue);

      retw = RegSetValueEx(res_key, (const char *)lpszVariable, 0, REG_SZ, (BYTE *)key_buf, strlen(key_buf));
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

// -------------------- siuksles
   if(SUCCEEDED(retc))
   {
      RegSetValueEx(res_key, "ProductID", 0, REG_SZ, (const unsigned char *)"none", strlen("none"));
      RegSetValueEx(res_key, "AuthorizedCDFPrefix", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "Comments", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "Contact", 0, REG_SZ, (const unsigned char *)"Customer Support Department", strlen("Customer Support Department"));
      RegSetValueEx(res_key, "Size", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "DisplayVersion", 0, REG_SZ, (const unsigned char *)"007.003.015", strlen("007.003.015"));
      RegSetValueEx(res_key, "VersionMajor", 0, REG_SZ, (const unsigned char *)"00000007", strlen("00000007"));
      RegSetValueEx(res_key, "VersionMinor", 0, REG_SZ, (const unsigned char *)"00000003", strlen("00000003"));
      RegSetValueEx(res_key, "WindowsInstaller", 0, REG_SZ, (const unsigned char *)"00000015", strlen("00000015"));
      RegSetValueEx(res_key, "Version", 0, REG_SZ, (const unsigned char *)"07003015", strlen("07003015"));
   }

   if(res_key)
   {
      retw=RegCloseKey(res_key);
      if(retw!=ERROR_SUCCESS)
      {
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
      res_key = 0;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveCompIDFileSingle(const unsigned char *lpszPath, const SYSTEMTIME *p_tt,
   const unsigned char *pkg_name, bool bForceAdmin, int comp_id_calc, int /* comp_id */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int name_len;
#endif
HANDLE out_file=INVALID_HANDLE_VALUE;
DWORD written;
#else
FILE *out_file=NULL;
#endif

   KP_ASSERT(lpszPath != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPath[0] != Nul, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszPath) + 1 + strlen(KPST_CNT_REG_PATH_11) < KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
   KP_ASSERT(p_tt != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(pkg_name != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc0))
   {
      strcpy(key_name, lpszPath);
      if(key_name[strlen(key_name) - 1] != '\\') strcat(key_name, "\\");
      strcat(key_name, KPST_CNT_REG_PATH_11);

      retc0 = CreateRegPath(p_tt, key_name);
   }
   if(SUCCEEDED(retc0))
   {
      m_CntRegPath1[0] = key_name[0]; // pakeièiam disko raidæ, jeigu kartais CreateRegPath() nerado C: ir perðoko á %SystemDrive%

      strcat(key_name, KPST_CNT_REG_PATH_2);

      retc0 = CreateRegPath(p_tt, key_name);
   }
   if(SUCCEEDED(retc0))
   {
      m_CntRegPath1[0] = key_name[0];

      strcat(key_name, pkg_name);
#if FALSE
      retc0 = CreateRegPath(p_tt, key_name);
   }
   if(SUCCEEDED(retc0))
   {
      m_CntRegPath1[0] = key_name[0];

      strcat((char *)key_name, "\\cbdata");
      strcat(key_name, " ");
#endif
   }

#ifdef KPST_WINDOWS_INTERFACE
#  ifdef KPST_UNICODE_FNAMES
// if(SUCCEEDED(retcf))
// {
//    name_len = strlen(KP_WIN_UNICODE_FNAME_PREFIX);
//    retcf = KptStrEncode(key_name_i, KP_WIN_UNICODE_FNAME_PREFIX, &name_len, 1);
//    if(SUCCEEDED(retc)) retc = retcf;
// }
   if(SUCCEEDED(retc0))
   {
      name_len = strlen(key_name);
//    retcf = KptStrEncode(key_name_i+strlen(KP_WIN_UNICODE_FNAME_PREFIX), key_name, &name_len, 1);
//    retcf = KptStrEncode(key_name_i, key_name, &name_len, 1);
      retc0 = KptStrToUnicode(key_name_w, key_name, &name_len, 1);
//    if(FAILED(retcf))
//       retcf = KpErrorProc.OutputErrorMessage(retcf, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc = retc0;
   }
   if(SUCCEEDED(retc0))
   {
//    key_name_w[name_len++] = iaUniChars[C_A_Ogon];
      key_name_w[name_len] = C_Nul;

#     if FALSE

int *pnti;
int low_byte;
int high_byte;

      pnti = key_name_i;
      while(*pnti)
      {
         low_byte = (*pnti & 0xFF);
         high_byte = (((*pnti)>>16) & 0xFF);
         *pnti = (low_byte<<16 | high_byte);
         pnti++;
      }
#     endif
   }
#  endif
#endif

   if(SUCCEEDED(retc0))
   {
#ifdef KPST_WINDOWS_INTERFACE
      out_file =
#  ifdef KPST_UNICODE_FNAMES
         CreateFileW((WCHAR *)key_name_w,
#  else
         CreateFile((const char *)key_name,
#  endif
            GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
      if((out_file==INVALID_HANDLE_VALUE) || (out_file==NULL))
#else
      out_file = fopen((const char *)key_name, "wb");
      if(out_file == NULL)
#endif
      {
//       retc0 = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// !!!!  retc0 = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, key_name, True, __FILE__, __LINE__, 0L, NULL);
//       if(SUCCEEDED(retc)) retc=retc0;
         retc0 = KP_E_DIR_ERROR;
         KP_WARNING(retc0, null);
         if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
         if(SUCCEEDED(retc)) retc=retc0;
      }

      if(SUCCEEDED(retc0))
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!WriteFile(out_file, &comp_id_calc, sizeof(comp_id_calc), &written, NULL))
#else
//       fprintf(out_file, "%x\n", comp_id_calc);
         fwrite(&comp_id_calc, sizeof(comp_id_calc), 1, out_file);
         if(ferror(out_file) || feof(out_file))
#endif
         {
//          retcf=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//          if(SUCCEEDED(retc)) retc=retcf;
            retc0 = KP_E_FERROR;
         }

// PutLogMessage_("SCIFS(): %s %x %d", key_name, retc, comp_id);

#ifdef KPST_WINDOWS_INTERFACE
         if(!CloseHandle(out_file))
#else
         if(fclose(out_file))
#endif
         {
            if(SUCCEEDED(retc0))
            {
//             retc0 = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//             if(SUCCEEDED(retc)) retc=retc0;
               retc0 = KP_E_DIR_ERROR;
            }
         }

      } // if(SUCCEEDED(retc0))

// ------------------- reset file creation date
      if(SUCCEEDED(retc0))
      {
         retc0 = ChFileTimeCrtd(key_name, p_tt);
//       if(SUCCEEDED(retc)) retc = retc0;
      }

   }  // if(SUCCEEDED(retc0)

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveCompID(bool bForceAdmin)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
LONG retw = ERROR_SUCCESS;
HKEY hKey = 0;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int prod_ver = 0;
// SYSTEMTIME st;
SYSTEMTIME tt;
int comp_id = 0;
int comp_id_calc = 0;

// if((!bCiDirect) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
//    retc = EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
      comp_id = cMemBank[KP11_COMPID/2];

//    comp_id_calc = (m_iInstCount * 10) ^ prod_ver;
      comp_id_calc = (comp_id /* m_iCompId */ * 10) ^ prod_ver;
   }

   if(SUCCEEDED(retc)) sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      if(bForceAdmin || bAdminFl)
      {
         if(!bAdminFl) retc0 = KP_E_ACCESS_DENIED;
         else retc0 = SaveRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"EstDispl", comp_id_calc);
         if(FAILED(retc0))
         {
            KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin)
            {
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
               if(SUCCEEDED(retc)) retc = retc0;
            }
         }
      }

// PutLogMessage_("SCI(): system %s %x %d", key_name, retc, comp_id);

      retc0 = SaveRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"EstDispl", comp_id_calc);

      if(FAILED(retc0)) KpErrorProc.OutputErrorMessage(retc0, null, False /* True */, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc=retc0;

// PutLogMessage_("SCI(): local %s %x %d", key_name, retc, comp_id);
   }

// -------------------- files
/* if(SUCCEEDED(retc)) */ retc0 = ResetSystemTime(&tt /* &st */);

// C:\WINNT\RegisteredPackages\{A2F3B5A7-2D39-4A4E-96E6-BFADEBCBB27B}
// 319494 SQLODBC.CAB
//   7281 SQLODBC.CAT
//   1014 SQLODBC.INF

// --------------------------------------- Common Data
   if(SUCCEEDED(retc0))
   {
      if(bForceAdmin || bAdminFl)
      {
         retc0 = S_OK;

         if(!bAdminFl) retc0 = KP_E_ACCESS_DENIED;

         if(SUCCEEDED(retc0)) retc0 = SaveCompIDFileSingle(KPST_CNT_REG_PATH_1, &tt, pkg_name, bForceAdmin, comp_id_calc, comp_id);

      } // if(bForceAdmin || bAdminFl)

      if(FAILED(retc0) && SUCCEEDED(retc))
      {
         KP_ASSERTE(SUCCEEDED(retc0), retc0, null, False);
         if(bForceAdmin)
         {
            KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
            retc = retc0;
         }
      }

// -------------------------------- All Users – ne admino aplikacijoms
      retc0 = S_OK;

const unsigned char *all_users_profile = (unsigned char *)getenv("ALLUSERSPROFILE");
      KP_ASSERT0E(all_users_profile != NULL, KP_E_SYSTEM_ERROR, null, False);
      KP_ASSERT0E(all_users_profile[0] != Nul, KP_E_SYSTEM_ERROR, null, False);

      if(SUCCEEDED(retc0)) retc0 = SaveCompIDFileSingle(all_users_profile, &tt, pkg_name, bForceAdmin, comp_id_calc, comp_id);
      KP_ASSERTE(SUCCEEDED(retc0), retc0, null, False);

   } // if(SUCCEEDED(retcf))

// ----------------------- restore system time
//       SetSystemTime(&st);

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedBoltRegSingle(HKEY hQueryKey, const unsigned char *lpszSubKey, long *plBolt)
{
return(GetRegSecData(hQueryKey, lpszSubKey, (const unsigned char *)"EstDispl", plBolt));
}


// ------------------------------
HRESULT KpStApp::GetSavedBoltFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, long *plBolt)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
#ifdef KPST_WINDOWS_INTERFACE
DWORD read;
HANDLE in_file = INVALID_HANDLE_VALUE;
#else
FILE *in_file = NULL;
#endif

   KP_ASSERT(lpszPath != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPath[0] != Nul, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszPath) + 1 + strlen(KPST_CNT_REG_PATH_11) < KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
   KP_ASSERT(pkg_name != null, E_INVALIDARG, null, True);
   KP_ASSERT(plBolt != NULL, E_INVALIDARG, null, True);

   strcpy(key_name, lpszPath);
   if(key_name[strlen(key_name) - 1] != '\\') strcat(key_name, "\\");
   strcat(key_name, KPST_CNT_REG_PATH_11);
   strcat(key_name, KPST_CNT_REG_PATH_2);
   strcat(key_name, pkg_name);

#ifdef KPST_WINDOWS_INTERFACE
   in_file = CreateFile((const char *)key_name, GENERIC_READ, FILE_SHARE_READ,
         0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   if(in_file == INVALID_HANDLE_VALUE)
#else
   in_file = fopen((const char *)key_name, "rb");
   if(in_file == NULL)
#endif
   {
      retc = KP_E_KWD_NOT_FOUND; // KP_E_FILE_NOT_FOUND
//    KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FILE_NOT_FOUND */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
   }
   else
   {
#ifdef KPST_WINDOWS_INTERFACE
      if(!ReadFile(in_file, plBolt, sizeof(*plBolt), &read, NULL))
#else
      fread(plBolt, sizeof(*plBolt), 1, in_file);
      if(ferror(in_file) || feof(in_file))
#endif
      {
         retc = KP_E_KWD_NOT_FOUND; // KP_E_FERROR
//       KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FERROR */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
      }

#ifdef KPST_WINDOWS_INTERFACE
      if(!CloseHandle(in_file))
#else
      if(fclose(in_file))
#endif
      {
         if(SUCCEEDED(retc))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//          retc=KP_E_SYSTEM_ERROR;
         }
      }

   } // else // if(in_file == NULL)

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedBolt(long *plBolt)
{
HRESULT retc = S_OK;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];

// ------------------------------
   KP_ASSERT(plBolt, E_INVALIDARG, True, null);

// ------------------------------
   if(SUCCEEDED(retc)) strcpy((char *)pkg_name, (const char *)KPST_BOLT_PKG_FMT);
bool found = False;

// -------------------- registry
   if(SUCCEEDED(retc)) sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

   if((!found) && SUCCEEDED(retc)) if(SUCCEEDED(GetSavedBoltRegSingle(HKEY_LOCAL_MACHINE, key_name, plBolt))) found = True;
// PutLogMessage_("KpStApp::GetSavedBolt() HKLM [%s] %d %ld", key_name, found, *plBolt);
   if((!found) && SUCCEEDED(retc)) if(SUCCEEDED(GetSavedBoltRegSingle(HKEY_CURRENT_USER, key_name, plBolt))) found = True;
// PutLogMessage_("KpStApp::GetSavedBolt() HKCU [%s] %d %ld", key_name, found, *plBolt);

// -------------------- files
   if((!found) && SUCCEEDED(retc)) if(SUCCEEDED(GetSavedBoltFileSingle(KPST_CNT_REG_PATH_1, pkg_name, plBolt))) found = True;
// PutLogMessage_("KpStApp::GetSavedBolt() C: [%s] [%s] %d %ld", KPST_CNT_REG_PATH_1, pkg_name, found, *plBolt);
   if((!found) && SUCCEEDED(retc)) if(SUCCEEDED(GetSavedBoltFileSingle((const unsigned char *)getenv("ALLUSERSPROFILE"), pkg_name, plBolt))) found = True;
// PutLogMessage_("KpStApp::GetSavedBolt() all [%s] [%s] %d %ld", getenv("ALLUSERSPROFILE"), pkg_name, found, *plBolt);

   if((!found) && SUCCEEDED(retc)) retc = KP_E_KWD_NOT_FOUND;

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveBoltRegSingle(HKEY hQueryKey, const unsigned char *lpszSubKey, long lBolt)
{
return(SaveRegSecData(hQueryKey, lpszSubKey, (const unsigned char *)"EstDispl", lBolt));
}


// ------------------------------
HRESULT KpStApp::SaveBoltFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, long lBolt, const SYSTEMTIME *p_tt)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
#ifdef KPST_WINDOWS_INTERFACE
DWORD written;
HANDLE out_file = INVALID_HANDLE_VALUE;
#else
FILE *out_file = NULL;
#endif

   KP_ASSERT(lpszPath != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPath[0] != Nul, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszPath) + 1 + strlen(KPST_CNT_REG_PATH_11) < KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
   KP_ASSERT(pkg_name != null, E_INVALIDARG, null, True);
   KP_ASSERT(p_tt != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(key_name, lpszPath);
      if(key_name[strlen(key_name) - 1] != '\\') strcat(key_name, "\\");
      strcat(key_name, KPST_CNT_REG_PATH_11);

      retc = CreateRegPath(p_tt, key_name);
   }
   if(SUCCEEDED(retc))
   {
      m_CntRegPath1[0] = key_name[0]; // pakeièiam disko raidæ, jeigu kartais CreateRegPath() nerado C: ir perðoko á %SystemDrive%

      strcat(key_name, KPST_CNT_REG_PATH_2);

      retc = CreateRegPath(p_tt, key_name);
   }

   if(SUCCEEDED(retc))
   {
      m_CntRegPath1[0] = key_name[0];

      strcat(key_name, pkg_name);
   }

   if(SUCCEEDED(retc))
   {
#ifdef KPST_WINDOWS_INTERFACE
      out_file = CreateFile((const char *)key_name, GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
      if((out_file == INVALID_HANDLE_VALUE) || (out_file == NULL))
#else
      out_file = fopen((const char *)key_name, "wb");
      if(out_file == NULL)
#endif
      {
         retc = KP_E_DIR_ERROR;
         KP_ERRORWE(retc, null, False);
      }
      else
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!WriteFile(out_file, &lBolt, sizeof(lBolt), &written, NULL))
#else
         fwrite(&lBolt, sizeof(lBolt), 1, out_file);
         if(ferror(out_file) || feof(out_file))
#endif
         {
            retc = KP_E_FERROR;
         }

// PutLogMessage_("SCIFS(): %s %x %d", key_name, retc, comp_id);

#ifdef KPST_WINDOWS_INTERFACE
         if(!CloseHandle(out_file))
#else
         if(fclose(out_file))
#endif
         {
            if(SUCCEEDED(retc)) retc = KP_E_DIR_ERROR;
         }

// ------------------- reset file creation date
         if(SUCCEEDED(retc)) ChFileTimeCrtd(key_name, p_tt);

      } // else // if(out_file == NULL)

   }  // if(SUCCEEDED(retc)

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveBolt(long lBolt)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
SYSTEMTIME tt;

// ------------------------------
   strcpy((char *)pkg_name, (const char *)KPST_BOLT_PKG_FMT);

// -------------------- registry
   sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

   SaveBoltRegSingle(HKEY_LOCAL_MACHINE, key_name, lBolt);
   SaveBoltRegSingle(HKEY_CURRENT_USER, key_name, lBolt);

// -------------------- files
   ResetSystemTime(&tt);

// --------------------------------------- Common Data
   SaveBoltFileSingle(KPST_CNT_REG_PATH_1, pkg_name, lBolt, &tt);

// -------------------------------- All Users
   SaveBoltFileSingle((const unsigned char *)getenv("ALLUSERSPROFILE"), pkg_name, lBolt, &tt);

return(retc);
}


// ------------------------------
long KpStApp::AddBoltFormula(long lFizId, long lRemID)
{
return((((lFizId ^ lRemID) & 0x7FFF) / 10) * 10);
}


// ------------------------------
HRESULT KpStApp::RetrieveBolt(long *plBolt, long lFizId)
{
HRESULT retc = S_OK;
long compid_received = -1L;
long compid_calculated = 0L;

   KP_ASSERT(plBolt, E_INVALIDARG, True, null);

// ----------------------------- priëmimo buferis
unsigned char *rcv_buf = null;
long read = 1000;
   KP_NEWA(rcv_buf, unsigned char, read + 1);

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ----------------------------- socketo kûrimas
KpSocket *sock_ptr = NULL;
   KP_NEWO(sock_ptr, KpSocket);
#endif

// ----------------------------- URL
unsigned char reg_url[KP_MAX_FNAME_LEN + 1];
   KP_ASSERT(strlen(KPST_BOLT_FILE) + strlen(KPST_BOLT_FORMAT)
             + MAX_LONG_DIGITS + 10 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(reg_url, KPST_BOLT_FILE);
      sprintf((char *)reg_url + strlen(reg_url), KPST_BOLT_FORMAT, lFizId);
// PutLogMessage_("RetrieveBolt() 2: [%s]", reg_url);
   }

#ifndef KPST_PRODGRP_NO_SVR_REQUEST
// ------------------------------ jungiamës
   if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_BOLT_URL, False);
   if(SUCCEEDED(retc)) retc = sock_ptr->Connect(False);

// ------------------------------ siunèiam uþklausà
   if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, reg_url, False);
#endif

// ------------------------------ priimam varþtà
   if(SUCCEEDED(retc))
   {
#  ifndef KPST_PRODGRP_NO_SVR_REQUEST
      retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, False);
#  else // #  ifndef KPST_PRODGRP_NO_SVR_REQUEST
      read = 0;
      retc = KP_E_TRANS_ERR;
#  endif // #  ifndef KPST_PRODGRP_NO_SVR_REQUEST
   }
   if(SUCCEEDED(retc)) rcv_buf[read] = Nul;
// PutLogMessage_("RetrieveBolt() 3: [%s]", rcv_buf);

// ------------------------- skanuojam priimtà varþtà
   if(SUCCEEDED(retc)) sscanf((const char *)rcv_buf, "%ld", plBolt);

// ----------------------------- generuojam lokalø varþtà
   if(FAILED(retc))
   {
      retc = S_OK;
SYSTEMTIME sys_time;
      if(SUCCEEDED(retc)) GetSystemTime(&sys_time);
FILETIME file_time;
      if(SUCCEEDED(retc)) SystemTimeToFileTime(&sys_time, &file_time);
// KpstRand negalima – mes jau emuliatoriuje
//    *plBolt = (((KpstRand((file_time.dwLowDateTime >> 16) & 0xFFFF) & 0x7FFF) << 16) | (KpstRand(file_time.dwLowDateTime & 0xFFFF) & 0xFFFF));
long low_byte = (file_time.dwLowDateTime & 0x7F);
      *plBolt = (file_time.dwLowDateTime & 0x7FFFFFFF) ^ (low_byte << 8) ^ (low_byte << 16) ^ (low_byte << 24);
// PutLogMessage_("RetrieveBolt() 5: %ld %lx %lx", *plBolt, *plBolt, file_time.dwLowDateTime);
   }

PutLogMessage_("RetrieveBolt() 6: %ld", *plBolt);

   if(SUCCEEDED(retc)) retc = SaveBolt(*plBolt);

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetBolt(long *plBolt, long lFizId)
{
HRESULT retc = S_OK;

   KP_ASSERT(plBolt, E_INVALIDARG, True, null);

   if(SUCCEEDED(retc))
   {
      retc = GetSavedBolt(plBolt);
      if(FAILED(retc)) retc = RetrieveBolt(plBolt, lFizId);
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::AddBolt(long *plCompId)
{
HRESULT retc = S_OK;
long bolt = 0L;

   KP_ASSERT(plCompId, E_INVALIDARG, True, null);

   if(SUCCEEDED(retc)) retc = GetBolt(&bolt, *plCompId);

   if(SUCCEEDED(retc)) *plCompId = AddBoltFormula(*plCompId, bolt);

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetRegLicences(HKEY hQueryKey, const unsigned char *lpszSubKey)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY res_key=0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char val_name[KP_MAX_FNAME_LEN+1];
DWORD dwBufLen;
DWORD dwValType;
int num_of_lics=0;
int ii, jj;
static LicStatus lic_buf_one;
unsigned char *pntd=NULL; // pointer to lic_buf_one
unsigned char scan_buf[3];
int hex_val;

   if((lpszSubKey==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(m_pLicArray==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
   {
      retw=RegOpenKeyEx(hQueryKey,
         (LPCTSTR)lpszSubKey,
         0, KEY_QUERY_VALUE, &res_key);
      if(retw!=ERROR_SUCCESS)
      {
         retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }
   }

// --------------------
   for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
   {
      sprintf((char *)val_name, "Dat%d", ii);
      key_buf[0]=Nul;

      dwBufLen=KP_MAX_FILE_LIN_WDT;
      retw=RegQueryValueEx(res_key, (const char *)val_name, NULL, &dwValType, (LPBYTE)key_buf, &dwBufLen);
      if((dwValType!=REG_SZ) || (retw!=ERROR_SUCCESS))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         retc=S_OK;
      }
      else key_buf[dwBufLen]=Nul;

      if(SUCCEEDED(retc))
      {
         pntd=(unsigned char *)(&lic_buf_one);
         for(jj=0; jj<sizeof(LicStatus); jj++)
         {
            scan_buf[0]=key_buf[jj*2];
            scan_buf[1]=key_buf[jj*2+1];
            scan_buf[2]=Nul;
            hex_val=0;
            sscanf((const char *)scan_buf, "%x", &hex_val);
            *(pntd++)=(hex_val^ii)&Maxuchar;
         }
         retc=EnctBufSimpl(&lic_buf_one, sizeof(LicStatus));
      }
      if(
         (
            (lic_buf_one.m_iLicState>m_pLicArray[ii].m_iLicState) ||
            (
               (lic_buf_one.m_iLicState>=m_pLicArray[ii].m_iLicState) &&
               (lic_buf_one.m_iLicState>KpstLicFree) &&
               (lic_buf_one.m_iSecondsToKill>m_pLicArray[ii].m_iSecondsToKill)
            )
         ) &&
         SUCCEEDED(retc)
        )
      {
         m_pLicArray[ii].m_iLicState=lic_buf_one.m_iLicState;
         m_pLicArray[ii].m_Host.S_un.S_addr=lic_buf_one.m_Host.S_un.S_addr;
         m_pLicArray[ii].m_iSessionID=lic_buf_one.m_iSessionID;
         m_pLicArray[ii].m_iSecondsToKill=lic_buf_one.m_iSecondsToKill;
      }

   } // for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)

   if(res_key)
   {
      retw=RegCloseKey(res_key);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      res_key=NULL;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedLicences(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HRESULT retca=KP_E_KWD_NOT_FOUND;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int prod_ver=0;
#ifdef KPST_WINDOWS_INTERFACE
DWORD read;
HANDLE in_file=INVALID_HANDLE_VALUE;
#else
FILE *in_file=NULL;
#endif
LicStatus *lic_buf=NULL;
int num_of_lics=0;
int ii;

   if(m_pLicArray==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
      sprintf((char *)pkg_name, (const char *)KPST_LIC_PKG_FMT, prod_ver);

   KP_NEWA(lic_buf, LicStatus, num_of_lics);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      retc0=GetRegLicences(HKEY_LOCAL_MACHINE, key_name);
      if(SUCCEEDED(retc0)) retca=retc0;

      retc0=GetRegLicences(HKEY_CURRENT_USER, key_name);
      if(SUCCEEDED(retc0)) retca=retc0;
   }

// -------------------- file
   if(SUCCEEDED(retc))
   {
      strcpy(key_name, KPST_CNT_REG_PATH_1);
      strcat(key_name, KPST_CNT_REG_PATH_11);
      strcat(key_name, KPST_CNT_REG_PATH_2);
      strcat(key_name, pkg_name);

#ifdef KPST_WINDOWS_INTERFACE
      in_file = CreateFile((const char *)key_name, GENERIC_READ, FILE_SHARE_READ,
               0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      if(in_file == INVALID_HANDLE_VALUE)
#else
      in_file = fopen((const char *)key_name, "rb");
      if(in_file==NULL)
#endif
      {
//       retc=KP_E_KWD_NOT_FOUND; // KP_E_FILE_NOT_FOUND
//       KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FILE_NOT_FOUND */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
      }
      else
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!ReadFile(in_file, lic_buf, sizeof(LicStatus)*num_of_lics, &read, NULL))
#else
         fread(lic_buf, sizeof(LicStatus)*num_of_lics, 1, in_file);
         if(ferror(in_file) || feof(in_file))
#endif
         {
//          retc=KP_E_KWD_NOT_FOUND; // KP_E_FERROR
//          KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FERROR */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
         }
         else
         {
            retca=S_OK;
            retc = EnctBufSimpl(lic_buf, sizeof(LicStatus)*num_of_lics);

            if(SUCCEEDED(retc))
            {
               for(ii=0; ii<num_of_lics; ii++)
                  if(
                     (lic_buf[ii].m_iLicState>m_pLicArray[ii].m_iLicState) ||
                     (
                        (lic_buf[ii].m_iLicState>=m_pLicArray[ii].m_iLicState) &&
                        (lic_buf[ii].m_iLicState>KpstLicFree) &&
                        (lic_buf[ii].m_iSecondsToKill>m_pLicArray[ii].m_iSecondsToKill)
                     )
                    )
                  {
                     m_pLicArray[ii].m_iLicState=lic_buf[ii].m_iLicState;
                     m_pLicArray[ii].m_Host.S_un.S_addr=lic_buf[ii].m_Host.S_un.S_addr;
                     m_pLicArray[ii].m_iSessionID=lic_buf[ii].m_iSessionID;
                     m_pLicArray[ii].m_iSecondsToKill=lic_buf[ii].m_iSecondsToKill;
                  }
            }
         }

#ifdef KPST_WINDOWS_INTERFACE
         if(!CloseHandle(in_file))
#else
         if(fclose(in_file))
#endif
         {
            if(SUCCEEDED(retc))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//             retc=KP_E_SYSTEM_ERROR;
            }
         }
      }
   }

   if(FAILED(retca) && SUCCEEDED(retc))
   {
      for(ii=0; ii<num_of_lics; ii++)
      {
         m_pLicArray[ii].m_iLicState=KpstLicBusy;
         m_pLicArray[ii].m_Host.S_un.S_addr=INADDR_NONE;
         m_pLicArray[ii].m_iSessionID=0;
         m_pLicArray[ii].m_iSecondsToKill=KPST_INI_SECS_TO_KILL;
      }
   }

   KP_DELETEA(lic_buf);

return(retc);
}


// ------------------------------------------
HRESULT KpStApp::SaveRegLicences(HKEY hQueryKey, const unsigned char *lpszSubKey)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY res_key=0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwDisposition;
int num_of_lics=0;
const unsigned char *pnts;
int ii, jj;
unsigned char val_name[KP_MAX_FNAME_LEN+1];
LicStatus lic_buf_one;
unsigned char str_buf[20];

   if((lpszSubKey==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(m_pLicArray==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

// ---------------------------
   if(SUCCEEDED(retc))
   {
      retw=RegCreateKeyEx(hQueryKey, (LPCTSTR)lpszSubKey,
         0, NULL /* "" */, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw!=ERROR_SUCCESS)
      {
         retc = KP_E_ACCESS_DENIED;
//       KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
//       KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
      }
   }

// --------------------
   for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
   {
      memcpy(&lic_buf_one, &m_pLicArray[ii], sizeof(LicStatus));
      retc=EnctBufSimpl(&lic_buf_one, sizeof(LicStatus));
      if(SUCCEEDED(retc))
      {
         key_buf[0]=Nul;
         pnts=(const unsigned char *)(&lic_buf_one);
         for(jj=0; jj<sizeof(LicStatus); jj++)
         {
            sprintf((char *)str_buf, "%02x", ((*pnts++)^ii)&Maxuchar);
            strcat(key_buf, str_buf);
         }

         sprintf((char *)val_name, "Dat%d", ii);

         retw=RegSetValueEx(res_key, (const char *)val_name, 0, REG_SZ, key_buf, strlen(key_buf));
         if(retw!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// -------------------- siuksles
   if(SUCCEEDED(retc))
   {
      RegSetValueEx(res_key, "ProductID", 0, REG_SZ, (const unsigned char *)"none", strlen("none"));
      RegSetValueEx(res_key, "AuthorizedCDFPrefix", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "Comments", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "Contact", 0, REG_SZ, (const unsigned char *)"Customer Support Department", strlen("Customer Support Department"));
      RegSetValueEx(res_key, "Size", 0, REG_SZ, (const unsigned char *)" ", 1);
      RegSetValueEx(res_key, "DisplayVersion", 0, REG_SZ, (const unsigned char *)"007.003.015", strlen("007.003.015"));
      RegSetValueEx(res_key, "VersionMajor", 0, REG_SZ, (const unsigned char *)"00000007", strlen("00000007"));
      RegSetValueEx(res_key, "VersionMinor", 0, REG_SZ, (const unsigned char *)"00000003", strlen("00000003"));
      RegSetValueEx(res_key, "WindowsInstaller", 0, REG_SZ, (const unsigned char *)"00000015", strlen("00000015"));
      RegSetValueEx(res_key, "Version", 0, REG_SZ, (const unsigned char *)"07003015", strlen("07003015"));
   }

   if(res_key)
   {
      retw=RegCloseKey(res_key);
      if(retw!=ERROR_SUCCESS)
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
      res_key=0;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveLicences(bool bForceAdmin)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HRESULT retcf=S_OK;
long retw=ERROR_SUCCESS;
HKEY hKey=0;
SYSTEMTIME tt;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
LicStatus *lic_buf=NULL;
int num_of_lics=0;
int prod_ver=0;
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int name_len;
#endif
HANDLE out_file=INVALID_HANDLE_VALUE;
DWORD written;
#else
FILE *out_file=NULL;
#endif

   if(m_pLicArray==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
   else
   {
      if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
      if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

      if(SUCCEEDED(retc))
         sprintf((char *)pkg_name, (const char *)KPST_LIC_PKG_FMT, prod_ver);

      KP_NEWA(lic_buf, LicStatus, num_of_lics);

// -------------------- registry
      if(SUCCEEDED(retc))
      {
         sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

         retc0=SaveRegLicences(HKEY_LOCAL_MACHINE, key_name);
         if(FAILED(retc0))
         {
            KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin) retc=KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
            if(SUCCEEDED(retc)) retc=retc0;
         }

         retc0=SaveRegLicences(HKEY_CURRENT_USER, key_name);
         if(SUCCEEDED(retc)) retc=retc0;
      }

// -------------------- file
// TODO: atskirt SaveLicencesFileSingle() ir iraðinët dar ir á %ALLUSERSPROFILE%
/* if(SUCCEEDED(retc)) */ retcf = ResetSystemTime(&tt);

//    if(SUCCEEDED(retc))
      if(SUCCEEDED(retcf))
      {
         retcf = S_OK;

         strcpy(key_name, KPST_CNT_REG_PATH_1);
         strcat(key_name, KPST_CNT_REG_PATH_11);

         retcf = CreateRegPath(&tt, key_name);
      }
      if(SUCCEEDED(retcf))
      {
         m_CntRegPath1[0] = key_name[0];

         strcat(key_name, KPST_CNT_REG_PATH_2);

         retcf = CreateRegPath(&tt, key_name);
      }
      if(SUCCEEDED(retcf))
      {
         m_CntRegPath1[0] = key_name[0];

         strcat(key_name, pkg_name);
      }

// ---------------------------
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
      if(SUCCEEDED(retcf))
      {
         name_len = strlen(key_name);
         retcf = KptStrToUnicode(key_name_w, key_name, &name_len, 1);
//       if(FAILED(retcf))
//          retcf = KpErrorProc.OutputErrorMessage(retcf, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retcf;
      }
      if(SUCCEEDED(retcf))
      {
         key_name_w[name_len] = C_Nul;
      }
#endif
#endif

      if(SUCCEEDED(retcf))
      {
#ifdef KPST_WINDOWS_INTERFACE
         out_file =
#ifdef KPST_UNICODE_FNAMES
            CreateFileW((WCHAR *)key_name_w,
#else
            CreateFile((const char *)key_name,
#endif
               GENERIC_WRITE, FILE_SHARE_WRITE,
               0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
         if((out_file == INVALID_HANDLE_VALUE) || (out_file==NULL))
#else
         out_file = fopen((const char *)key_name, "wb");
         if(out_file == NULL)
#endif
         {
            retcf = KP_E_DIR_ERROR;
            KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
            if(SUCCEEDED(retc)) retc = retcf;
         }

         if(SUCCEEDED(retcf))
         {
            memcpy(lic_buf, m_pLicArray, sizeof(LicStatus)*num_of_lics);
            retc0 = EnctBufSimpl(lic_buf, sizeof(LicStatus)*num_of_lics);
            if(SUCCEEDED(retc)) retc = retc0;

#ifdef KPST_WINDOWS_INTERFACE
            if(!WriteFile(out_file, lic_buf, sizeof(LicStatus)*num_of_lics, &written, NULL))
#else
            fwrite(lic_buf, sizeof(LicStatus)*num_of_lics, 1, out_file);
            if(ferror(out_file) || feof(out_file))
#endif
            {
//             retcf = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//             if(SUCCEEDED(retc)) retc = retcf;
               retcf = KP_E_FERROR;
            }

// ------------------------
#ifdef KPST_WINDOWS_INTERFACE
            if(!CloseHandle(out_file))
#else
            if(fclose(out_file))
#endif
            {
               if(SUCCEEDED(retcf))
               {
//                retcf = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                if(SUCCEEDED(retc)) retc = retcf;
                  retcf = KP_E_DIR_ERROR;
               }
            }

         } // if(SUCCEEDED(retcf))

// ------------------- reset file creation date
         if(SUCCEEDED(retcf))
         {
            retcf = ChFileTimeCrtd(key_name, &tt);
//          if(SUCCEEDED(retc)) retc = retcf;
         }

      } // if(SUCCEEDED(retc))

   } // else // if(m_pLicArray==NULL)

   KP_DELETEA(lic_buf);

   if(SUCCEEDED(retc)) retc = retcf;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CountFreeLicences(int *iCnt)
{
HRESULT retc=S_OK;
int num_of_lics=0;
int cnt = 0;
int ii;

   if((iCnt == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics);

   if(SUCCEEDED(retc)) for(ii=0; ii<num_of_lics; ii++)
      if(m_pLicArray[ii].m_iLicState == KpstLicFree) cnt++;

   if(SUCCEEDED(retc)) *iCnt = cnt;

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveDatRestDaysInit(const unsigned char *lpszFileName, const RestTimeStruct *pOutData, bool bForceAdmin)
{
HRESULT retc = S_OK;
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int name_len;
#endif
HANDLE out_file = INVALID_HANDLE_VALUE;
DWORD written;
#else
FILE *out_file = NULL;
#endif

   KP_ASSERT(lpszFileName, E_INVALIDARG, null, True);
   KP_ASSERT(pOutData, E_INVALIDARG, null, True);

#ifdef KPST_WINDOWS_INTERFACE
#  ifdef KPST_UNICODE_FNAMES
   if(SUCCEEDED(retc))
   {
      name_len = strlen(lpszFileName);
      retc = KptStrToUnicode(key_name_w, lpszFileName, &name_len, 1);
   }
   if(SUCCEEDED(retc)) key_name_w[name_len] = C_Nul;
#  endif
#endif

   if(SUCCEEDED(retc))
   {
#ifdef KPST_WINDOWS_INTERFACE
      out_file =
#  ifdef KPST_UNICODE_FNAMES
         CreateFileW((WCHAR *)key_name_w,
#  else
         CreateFile((const char *)lpszFileName,
#  endif
            GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
      if((out_file == INVALID_HANDLE_VALUE) || (out_file == NULL))
#else
      out_file = fopen((const char *)lpszFileName, "wb");
      if(out_file == NULL)
#endif
      {
         retc = KP_E_DIR_ERROR;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         if(bForceAdmin) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
      }

      if(SUCCEEDED(retc))
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!WriteFile(out_file, pOutData, sizeof(*pOutData), &written, NULL))
#else
         fwrite(pOutData, sizeof(*pOutData), 1, out_file);
         if(ferror(out_file) || feof(out_file))
#endif
         {
            retc = KP_E_FERROR;
         }
#ifdef KPST_WINDOWS_INTERFACE
         if(!CloseHandle(out_file))
#else
         if(fclose(out_file))
#endif
         {
            if(SUCCEEDED(retc)) retc = KP_E_DIR_ERROR;
         }

      } // if(SUCCEEDED(retc)) // if(CreateFile(...))

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
HRESULT KpStApp::LoadDatRestDaysInit(const unsigned char *lpszFileName, RestTimeStruct *pInData)
{
HRESULT retc = S_OK;
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
int name_len;
#endif
HANDLE in_file = INVALID_HANDLE_VALUE;
DWORD read;
#else
FILE *in_file = NULL;
#endif

   KP_ASSERT(lpszFileName, E_INVALIDARG, null, True);
   KP_ASSERT(pInData, E_INVALIDARG, null, True);

#ifdef KPST_WINDOWS_INTERFACE
#  ifdef KPST_UNICODE_FNAMES
   if(SUCCEEDED(retc))
   {
      name_len = strlen(lpszFileName);
      retc = KptStrToUnicode(key_name_w, lpszFileName, &name_len, 1);
   }
   if(SUCCEEDED(retc)) key_name_w[name_len] = C_Nul;
#  endif
#endif

   if(SUCCEEDED(retc))
   {
#ifdef KPST_WINDOWS_INTERFACE
      in_file =
#  ifdef KPST_UNICODE_FNAMES
         CreateFileW((WCHAR *)key_name_w,
#  else
         CreateFile((const char *)lpszFileName,
#  endif
            GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      if((in_file == INVALID_HANDLE_VALUE) || (in_file == NULL))
#else
      out_file = fopen((const char *)lpszFileName, "rb");
      if(out_file == NULL)
#endif
      {
         retc = KP_E_DIR_ERROR;
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!ReadFile(in_file, pInData, sizeof(*pInData), &read, NULL))
#else
         fread(pInData, sizeof(*pInData), 1, in_file);
         if(ferror(in_file) || feof(in_file))
#endif
         {
            retc = KP_E_FERROR;
         }
#ifdef KPST_WINDOWS_INTERFACE
         if(!CloseHandle(in_file))
#else
         if(fclose(in_file))
#endif
         {
            if(SUCCEEDED(retc)) retc = KP_E_DIR_ERROR;
         }

      } // if(SUCCEEDED(retc)) // if(CreateFile(...))

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveRegDatRestDaysInit(bool bForceAdmin)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HRESULT retcf = S_OK;
int prod_ver = 0;
int rest_days_init = 0;
long rest_mins_init = 0L;
time_t ltime;
long cur_mins;
RestTimeStruct out_data;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
SYSTEMTIME tt;
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &m_lRestMinutes;

   KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
// KP_ASSERT(sizeof(short) == sizeof(MemBankType), KP_E_SYSTEM_ERROR, null, True);

// if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   prod_ver = cMemBank[KP11_PRODVER/2];

   if(SUCCEEDED(retc))
   {
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);
      sprintf((char *)pkg_name + strlen(pkg_name) - 1, "-%d}", (cMemBank[KP11_LIC_HIGH/2] << 16) | cMemBank[KP11_LICID/2]);
   }

   if(SUCCEEDED(retc))
   {
//    retc = EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT); // negalima – mes jau HP11 viduj
      rest_days_init = cMemBank[KP11_REST_DAYS_INIT/2]; // ((short *)&cMemBank)[KP11_REST_DAYS_INIT/2];
   }

   if((rest_days_init == 0) && SUCCEEDED(retc))
   {
//    retc = EmuTv.SetHp11Variable(0, KP11_BLOCK_TERM); // negalima – mes jau HP11 viduj
      cMemBank[KP11_BLOCK_TERM/2] = 0;
   }

   if(SUCCEEDED(retc))
   {
      out_data.m_lRestMinsInit = rest_mins_init = (long)rest_days_init * KPST_MINS_PER_DAY;

      out_data.m_lRestMinutes = *rest_mins_ptr;

      time(&ltime);
      out_data.m_lCurMins = cur_mins = ltime / KP_SECS_PER_MIN;
   }

// PutLogMessage_("SRDRDI r_m_i: %ld r_m: %ld c_m: %ld", rest_mins_init, *rest_mins_ptr, cur_mins);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      if(bForceAdmin || bAdminFl)
      {
         retc0 = S_OK;

         if(!bAdminFl) retc0 = KP_E_ACCESS_DENIED;
         else
         {
            if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"RelVal", rest_mins_init); // ðito saugoti nereikëtø – aktualus ið DiegRakto
            if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"IncVal", *rest_mins_ptr);
            if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"AbsVal", cur_mins);
         }
         if(FAILED(retc0))
         {
            KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin)
            {
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
               if(SUCCEEDED(retc)) retc = retc0;
            }
         }
      }

      retc0 = S_OK;

      if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"RelVal", rest_mins_init); // ðito saugoti nereikëtø – aktualus ið DiegRakto
      if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"IncVal", *rest_mins_ptr);
      if(SUCCEEDED(retc0)) retc0 = SaveRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"AbsVal", cur_mins);

      if(FAILED(retc0)) KpErrorProc.OutputErrorMessage(retc0, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc = retc0;
   }

// -------------------- file
/* if(SUCCEEDED(retc)) */ retcf = ResetSystemTime(&tt);

// if(SUCCEEDED(retc))
   if(SUCCEEDED(retcf))
   {
// -------------------- system file
      if(bForceAdmin || bAdminFl)
      {
         retcf = S_OK;

         if(!bAdminFl) retcf = KP_E_ACCESS_DENIED;

         if(SUCCEEDED(retcf))
         {
            strcpy(key_name, KPST_CNT_REG_PATH_1);
            strcat(key_name, KPST_CNT_REG_PATH_11);

            retcf = CreateRegPath(&tt, key_name);
         }
         if(SUCCEEDED(retcf))
         {
            m_CntRegPath1[0] = key_name[0];

            strcat(key_name, KPST_CNT_REG_PATH_2);

            retcf = CreateRegPath(&tt, key_name);
         }
#if FALSE
         if(SUCCEEDED(retcf))
         {
            m_CntRegPath1[0] = key_name[0];

            strcat(key_name, KPST_CNT_REG_PATH_22);

            retcf = CreateRegPath(&tt, key_name);
         }
#endif
         if(SUCCEEDED(retcf))
         {
            m_CntRegPath1[0] = key_name[0];

            strcat(key_name, pkg_name);
         }

         if(SUCCEEDED(retcf)) retcf = SaveDatRestDaysInit(key_name, &out_data, bForceAdmin);

// ------------------- reset file creation date
         if(SUCCEEDED(retcf)) retcf = ChFileTimeCrtd(key_name, &tt);

         if(FAILED(retcf) && SUCCEEDED(retc))
         {
            KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin)
            {
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
               retc = retcf;
            }
         }

      } // if(bForceAdmin || bAdminFl)


// -------------------- local file
//    if(SUCCEEDED(retc))
      {
         retcf = S_OK;

         if(SUCCEEDED(retcf)) retcf = GetLocalPath(key_name, KP_Temp_Dir, True);
         if(SUCCEEDED(retcf))
         {
            strcat(key_name, KPST_CNT_REG_PATH_11);
            strcat(key_name, KPST_CNT_REG_PATH_2);
//          strcat(key_name, KPST_CNT_REG_PATH_22);

            strcat(key_name, pkg_name);

            retcf = CreatePath(key_name, False); // gal naudoti retcf = CreateRegPath(&tt, key_name);
         }

         if(SUCCEEDED(retcf)) retcf = SaveDatRestDaysInit(key_name, &out_data, False);

// ------------------- reset file creation date
//       if(SUCCEEDED(retcf)) retcf = ChFileTimeCrtd(key_name, &tt);

         if(FAILED(retcf) && SUCCEEDED(retc))
            KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);

      } // if(SUCCEEDED(retc))

// --------------------
   } // if(SUCCEEDED(retcf))

// PutLogMessage_("SaveRegDatRestDaysInit() m_lRestMinutes: %lx %ld  lic_high: %d lic_low_hash: %d", *rest_mins_ptr, *rest_mins_ptr, cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_LICID/2]);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::LoadRegDatRestDaysInit(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HRESULT retcr = KP_E_KWD_NOT_FOUND;
int prod_ver = 0;
int rest_days_init = 0;
long rest_mins_init = 0L;
long rest_mins_init_tmp = 0L;
long rest_mins_tmp = 0L;
time_t ltime;
long cur_mins = 0L;
long cur_mins_tmp = 0L;
long cur_mins_read = 0L;
RestTimeStruct in_data;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
unsigned char file_key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &m_lRestMinutes;

   KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);

// if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   prod_ver = cMemBank[KP11_PRODVER/2];

   if(SUCCEEDED(retc))
   {
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);
      sprintf((char *)pkg_name + strlen(pkg_name) - 1, "-%d}", (cMemBank[KP11_LIC_HIGH/2] << 16) | cMemBank[KP11_LICID/2]);
   }

   if(SUCCEEDED(retc))
   {
//    retc = EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT); // negalima – mes jau HP11 viduj
      rest_days_init = cMemBank[KP11_REST_DAYS_INIT/2];
   }

   if(SUCCEEDED(retc))
   {
      rest_mins_init = (long)rest_days_init * KPST_MINS_PER_DAY;

      time(&ltime);
      cur_mins = ltime / KP_SECS_PER_MIN;
      cur_mins_read = 0L;
   }

PutLogMessage_("LRDRDI() 1 r_d_i: %d r_m_i: %ld r_m: %ld c_m: %ld", rest_days_init, rest_mins_init, *rest_mins_ptr, cur_mins);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      retc0 = S_OK;

      rest_mins_init_tmp = 0L;
      rest_mins_tmp = 0L;
      cur_mins_tmp = 0L;
   }

// -------------------- system registry
   if(SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"RelVal", &rest_mins_init_tmp);
      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"IncVal", &rest_mins_tmp);
      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_LOCAL_MACHINE, key_name, (const unsigned char *)"AbsVal", &cur_mins_tmp);

      if(SUCCEEDED(retc0))
      {
         if(/* (rest_mins_init_tmp < rest_mins_init) || */ (rest_mins_init == 0L)) rest_mins_init = rest_mins_init_tmp;
      /* if(rest_mins_tmp < *rest_mins_ptr) */ *rest_mins_ptr = rest_mins_tmp;
      /* if(cur_mins_tmp > cur_mins_read) */ cur_mins_read = cur_mins_tmp;

         retcr = S_OK;

PutLogMessage_("LRDRDI() SR: r_m_i: %ld r_m: %ld c_m: %ld   r_m_i_t: %ld r_m_t: %ld c_m_t: %ld", rest_mins_init, *rest_mins_ptr, cur_mins_read, rest_mins_init_tmp, rest_mins_tmp, cur_mins_tmp);
      }

   }

// -------------------- system file
   if(SUCCEEDED(retc))
   {
      strcpy(file_key_name, KPST_CNT_REG_PATH_1);
      strcat(file_key_name, KPST_CNT_REG_PATH_11);
      strcat(file_key_name, KPST_CNT_REG_PATH_2);
//    strcat(file_key_name, KPST_CNT_REG_PATH_22);
      strcat(file_key_name, pkg_name);

      retc0 = LoadDatRestDaysInit(file_key_name, &in_data);
      if(SUCCEEDED(retc0))
      {
         if(/* (in_data.m_lRestMinsInit < rest_mins_init) || */ (rest_mins_init == 0L)) rest_mins_init = in_data.m_lRestMinsInit;
      /* if(in_data.m_lRestMinutes < *rest_mins_ptr) */ *rest_mins_ptr = in_data.m_lRestMinutes;
      /* if(in_data.m_lCurMins > cur_mins_read) */ cur_mins_read = in_data.m_lCurMins;

         retcr = S_OK;

PutLogMessage_("LRDRDI() SF: r_m_i: %ld r_m: %ld c_m: %ld   r_m_i_t: %ld r_m_t: %ld c_m_t: %ld", rest_mins_init, *rest_mins_ptr, cur_mins_read, rest_mins_init_tmp, rest_mins_tmp, cur_mins_tmp);
      }
   }

// -------------------- local registry
   if(SUCCEEDED(retc))
   {
      retc0 = S_OK;

      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"RelVal", &rest_mins_init_tmp);
      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"IncVal", &rest_mins_tmp);
      if(SUCCEEDED(retc0)) retc0 = GetRegSecData(HKEY_CURRENT_USER, key_name, (const unsigned char *)"AbsVal", &cur_mins_tmp);

      if(SUCCEEDED(retc0))
      {
         if(/* (rest_mins_init_tmp < rest_mins_init) || */ (rest_mins_init == 0L)) rest_mins_init = rest_mins_init_tmp;
      /* if(rest_mins_tmp < *rest_mins_ptr) */ *rest_mins_ptr = rest_mins_tmp;
      /* if(cur_mins_tmp > cur_mins_read) */ cur_mins_read = cur_mins_tmp;

         retcr = S_OK;

PutLogMessage_("LRDRDI() LR: r_m_i: %ld r_m: %ld c_m: %ld   r_m_i_t: %ld r_m_t: %ld c_m_t: %ld", rest_mins_init, *rest_mins_ptr, cur_mins_read, rest_mins_init_tmp, rest_mins_tmp, cur_mins_tmp);
      }
   }

// -------------------- local file
   if(SUCCEEDED(retc))
   {
      retc0 = GetLocalPath(file_key_name, KP_Temp_Dir, True);
      if(SUCCEEDED(retc0))
      {
         strcat(file_key_name, KPST_CNT_REG_PATH_11);
         strcat(file_key_name, KPST_CNT_REG_PATH_2);
//       strcat(file_key_name, KPST_CNT_REG_PATH_22);
         strcat(file_key_name, pkg_name);

         retc0 = LoadDatRestDaysInit(file_key_name, &in_data);
      }
      if(SUCCEEDED(retc0))
      {
         if(/* (in_data.m_lRestMinsInit < rest_mins_init) || */ (rest_mins_init == 0L)) rest_mins_init = in_data.m_lRestMinsInit;
      /* if(in_data.m_lRestMinutes < *rest_mins_ptr) */ *rest_mins_ptr = in_data.m_lRestMinutes;
      /* if(in_data.m_lCurMins > cur_mins_read) */ cur_mins_read = in_data.m_lCurMins;

         retcr = S_OK;

PutLogMessage_("LRDRDI() LF: r_m_i: %ld r_m: %ld c_m: %ld   r_m_i_t: %ld r_m_t: %ld c_m_t: %ld", rest_mins_init, *rest_mins_ptr, cur_mins_read, rest_mins_init_tmp, rest_mins_tmp, cur_mins_tmp);
      }
   }

// --------------------------
   if(SUCCEEDED(retc)) retc = retcr;

   if(SUCCEEDED(retc)) if(cur_mins_read > cur_mins) cur_mins = cur_mins_read; // retc = KP_E_REFUSED; // á cheatinimà nereaguojam – tiesiog pastumiam skaitiklius, kad terminas liktø tas pats
   if(SUCCEEDED(retc))
   {
      if(rest_mins_init)
      {
         if(*rest_mins_ptr > rest_mins_init) *rest_mins_ptr = rest_mins_init;
// PutLogMessage_("LoadRegDatRestDaysInit() m_lRestMinutes: %lx %ld  cur_mins: %ld  cur_mins_read: %ld", *rest_mins_ptr, *rest_mins_ptr, cur_mins, cur_mins_read);
         *rest_mins_ptr -= cur_mins - cur_mins_read;
// PutLogMessage_("LoadRegDatRestDaysInit() m_lRestMinutes: %lx %ld", *rest_mins_ptr, *rest_mins_ptr);

         if(SUCCEEDED(retc))
         {
#if FALSE
            if(*rest_mins_ptr <= (long)KPST_MINS_PER_DAY * KPST_REST_DAYS_WARNING)
            {
               PostThreadMessage(iKpMainThread, WM_COMMAND, KPST_ID_REST_DAYS_EXCEEDED, *rest_mins_ptr / KPST_MINS_PER_DAY);
KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, KPST_ID_REST_DAYS_EXCEEDED);
            }
#endif
            if(*rest_mins_ptr <= 0L)
            {
//             retc = EmuTv.SetHp11Variable(1, KP11_BLOCK_TERM); // negalima – mes jau HP11 viduj
               cMemBank[KP11_BLOCK_TERM/2] = 1;

// KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, KPST_ID_REST_DAYS_EXCEEDED);
               retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
// nereikia – tada nespëja pagauti KPST_ID_REST_DAYS_EXCEEDED praneðimo – WM_QUIT suvalgo EmuTt::WaitForRemoteCallCompletion()
// //          PostQuitMessage(IDABORT);
//             PostThreadMessage(iKpMainThread, WM_QUIT, IDABORT, 0L);
            }
            else
            {
//             retc = EmuTv.SetHp11Variable(0, KP11_BLOCK_TERM); // negalima – mes jau HP11 viduj
               cMemBank[KP11_BLOCK_TERM/2] = 0;
            }
         }
      }
   }

PutLogMessage_("LRDRDI 6 r_m_i: %ld r_m: %ld c_m: %ld", rest_mins_init, *rest_mins_ptr, cur_mins_read);

// iðsaugotà rest_mins_init ignoruojam – aktualus ið DiegRakto

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetKpstFdfLine(KpString *psOutStr, KpInStream *pInStream)
{
HRESULT retc = S_OK;
unsigned char in_line[KP_MAX_FILE_LIN_LEN + 1];
// int ll;

   if(((psOutStr == NULL) || (pInStream == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
//    *pInStream >> in_str;

      pInStream->getline((char *)in_line, KP_MAX_FILE_LIN_LEN);
      in_line[KP_MAX_FILE_LIN_LEN] = Nul;
   }

   if(SUCCEEDED(retc)) if(pInStream->eof())
   {
//    retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      retc=KP_E_EOF;
//    KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) if(pInStream->fail())
      retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE
   if(SUCCEEDED(retc))
   {
      ll = strlen(in_line);
      while(ll > 0)
      {
         if(TvStrChr(lpszEols, in_line[ll - 1])) ll--;
         else break;
      }
      in_line[ll] = Nul;
   }
#endif

   if(SUCCEEDED(retc)) *psOutStr = (const char *)in_line;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetKpstFdfData(KpString *psOutStr, KpInStream *pInStream, FdfInputMode iInpMode, bool bOutMsg)
{
HRESULT retc=S_OK;
KpString in_str;
KpString a85_str;
int ii, jj;

   if(((psOutStr==NULL) || (pInStream == NULL) || (iInpMode < 0) || (iInpMode >= FdfInputMax)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) if(pInStream->fail() || pInStream->eof())
   {
      retc = KP_E_FILE_NOT_FOUND;
   /* retc = */ KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) switch(iInpMode)
   {
   case FdfInputFdf:

      if(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
#ifdef Logging
if(SUCCEEDED(retc)) PutLogMessage_("[GKFD 1] %s", in_str.ExtractUnsignedValueA());
#endif
         if(retc == KP_E_EOF)
         {
            retc = KP_E_FILE_FORMAT;
         /* retc = */ KpErrorProc.OutputErrorMessage(retc, null, bOutMsg, __FILE__, __LINE__, 0L, NULL);
         }
      }
      if(SUCCEEDED(retc)) if(in_str!="%FDF-1.2")
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);

      while(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
#ifdef Logging
if(SUCCEEDED(retc)) PutLogMessage_("[GKFD 2] %s", in_str.ExtractUnsignedValueA());
#endif
         if(retc == KP_E_EOF)
            retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) if(in_str=="<</Filter[/A85]>>") break;
      }

      if(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
#ifdef Logging
if(SUCCEEDED(retc)) PutLogMessage_("[GKFD 3] %s", in_str.ExtractUnsignedValueA());
#endif
         if(retc == KP_E_EOF)
            retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc)) if(in_str!="stream")
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
   case FdfInputRawA85:

      if(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
#ifdef Logging
if(SUCCEEDED(retc)) PutLogMessage_("[GKFD 4] %s", in_str.ExtractUnsignedValueA());
#endif
         if(retc == KP_E_EOF)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         ii = in_str.index("<~");
         if(ii < 0) ii = 0;
         else ii += 2;

         jj = in_str.index("~>");
         if(jj < 0) jj = in_str.length();

//       a85_str = "<~" + in_str.substr(ii, jj - ii) + "~>";
         a85_str = "<~";
         a85_str += in_str.substr(ii, jj - ii);
         a85_str += "~>";

      }

      if(SUCCEEDED(retc))
      {
         retc=A85toStr(psOutStr, a85_str);
         if(FAILED(retc))
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      break;

   case FdfInputRawAscii:
      if(SUCCEEDED(retc)) retc = GetKpstFdfLine(psOutStr, pInStream);
      break;

   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
      break;

   } // if(SUCCEEDED(retc)) switch(iInpMode)

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetKpstFdfDataRec(XmlTagPars **OutDataRec, KpInStream *pInStream, FdfInputMode iInpMode, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char delim;
KpString in_str;
const unsigned char *in_str_ptr = null;
KpString in_str_tmp;
bool found = False;
const unsigned char *pnts;
unsigned char *pntd;
XmlTagPars *dat_rec_ptr = NULL;
bool a85_fl = False;
int ii;
int jj;
KpString a85_str;
bool multiline = False;
// unsigned char dat_str[KP_MAX_FILE_LIN_WDT + 1];

   if(((OutDataRec==NULL) || (pInStream == NULL) || (iInpMode < 0) || (iInpMode >= FdfInputMax)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) if(*OutDataRec != NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) if(pInStream->fail())
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(iInpMode)
   {
   case FdfInputFdf:

      if(SUCCEEDED(retc)) retc = GetKpstFdfLine(&in_str, pInStream);
      if(SUCCEEDED(retc))
      {
//       if(in_str != "%FDF-1.2")
         in_str_ptr = in_str.ExtractUnsignedValueA();
         if(in_str_ptr == null) in_str_ptr = (const unsigned char *)"";
         if(strstr(in_str_ptr, "%FDF-1.2") != in_str_ptr)
         {
            PutLogMessage_("GKFDR: in_str: %s", in_str_ptr);
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
         }
      }

// skanuojam laukø vardus ir kuriam tu­Íius parametr° ßra­us
      found = False;
      while((!found) && SUCCEEDED(retc))
      {
         in_str = "";
         retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

         if(SUCCEEDED(retc))
         {
            if(strcmp(in_str.ExtractValueA(), "/Fields") == 0)
            {
               found = False;
               while((!found) && SUCCEEDED(retc))
               {
                  in_str = "";
                  retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

                  if(SUCCEEDED(retc))
                  {
                     pnts = in_str.ExtractUnsignedValueA();
                     if(strstr(pnts, "/T("))
                     {
                        if(strlen(pnts) >= KP_MAX_FILE_LIN_LEN)
                           retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

                        if(SUCCEEDED(retc))
                        {
                           pnts = strchr(pnts, '(');
                           if(pnts == NULL)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
                        }
                        if(SUCCEEDED(retc))
                        {
                           pnts++;
                           pntd = strchr(pnts, ')');
                           if(pntd == NULL)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
                        }
                        if(SUCCEEDED(retc))
                        {
                           *pntd = Nul;

                           if(*OutDataRec == NULL)
                              KP_NEW(*OutDataRec, XmlTagPars(pnts, (const unsigned char *)"", NULL, TV_MAIN_CTBL))
                           else retc = (*OutDataRec)->AddTextPar(pnts, "");
                        }

                     } // if(strstr(pnts, "/T("))
                     else
                        if((strcmp(pnts, "/Filter") == 0) || (strcmp(pnts, "stream") == 0)) found = True;

                  } // if(SUCCEEDED(retc))

               } // while((!found) && SUCCEEDED(retc))

            } // if(strcmp(in_str.ExtractValueA(), "/Fields") == 0)
            else
               if(strcmp(in_str.ExtractValueA(), "/JavaScript") == 0)
               {
                  found = True;
                  KP_NEW(*OutDataRec, XmlTagPars((const unsigned char *)"JavaScript", (const unsigned char *)"", NULL));
// nereikia
// !!! TODO iðsitraukti dokumento vardà ("mano_pdf") ið antro parametro á *OutDataRec laukà "Doc"
// /JavaScript<</Doc 2 0 R >> >> >>
// endobj
// 2 0 obj
// [ (mano_pdf) 3 0 R ]
// endobj
                  found = False;
                  while((!found) && SUCCEEDED(retc))
                  {
                     in_str = "";
                     retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

                     if(SUCCEEDED(retc))
                     {
                        pnts = in_str.ExtractUnsignedValueA();
                        if((strcmp(pnts, "/Filter") == 0) || (strcmp(pnts, "stream") == 0)) found = True;

                     } // if(SUCCEEDED(retc))

                  } // while((!found) && SUCCEEDED(retc))

               } // if(strcmp(in_str.ExtractValueA(), "/JavaScript") == 0)

         } // if(SUCCEEDED(retc))

      } // while((!found) && SUCCEEDED(retc))

// ---------------------------------- skanuojam reik­mes
      if(SUCCEEDED(retc)) dat_rec_ptr = *OutDataRec;

      while(dat_rec_ptr && SUCCEEDED(retc))
      {
         a85_fl = False;

         if(strcmp(pnts, "/Filter") == 0)
         {
            a85_fl = True;

            in_str = "";
            retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

            if(SUCCEEDED(retc))
            {
               pnts = in_str.ExtractUnsignedValueA();
               if(strcmp(pnts, "/A85") != 0)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
            }

            found = False;
            while((!found) && SUCCEEDED(retc))
            {
               in_str = "";
               retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

               if(SUCCEEDED(retc))
               {
                  pnts = in_str.ExtractUnsignedValueA();
                  if(strcmp(pnts, "stream") == 0) found = True;

               } // if(SUCCEEDED(retc))

            } // while((!found) && SUCCEEDED(retc))

         } // if(strcmp(pnts, "/Filter") == 0)

         if(SUCCEEDED(retc)) if(delim != '\n') retc = GetKpstFdfLine(&in_str, pInStream);

         in_str = "";
         multiline = False;
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = GetKpstFdfLine(&in_str_tmp, pInStream);
            if(SUCCEEDED(retc))
            {
               if(strcmp(in_str_tmp.ExtractValueA(), "endstream") == 0) break;
               else
               {
                  if(strcmp(in_str.ExtractValueA(), "") != 0)
                  {
                     in_str += "\n";
                     multiline = True;
                  }
                  in_str += in_str_tmp;
               }
            }
         }
         if(multiline && SUCCEEDED(retc)) in_str += "\n";

         if(a85_fl && SUCCEEDED(retc))
         {
            ii = in_str.index("<~");
            if(ii < 0) ii = 0;
            else ii += 2;

            jj = in_str.index("~>");
            if(jj < 0) jj = in_str.length();

//          a85_str = "<~" + in_str.substr(ii, jj - ii) + "~>";
            a85_str = "<~";
            a85_str += in_str.substr(ii, jj - ii);
            a85_str += "~>";

            retc = A85toStr(&in_str, a85_str);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);

         } // if(a85_fl && SUCCEEDED(retc))

         if(SUCCEEDED(retc))
         {
            pnts = in_str.ExtractUnsignedValueA();
//          KP_ASSERT(strlen(pnts) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
         }
//       if(SUCCEEDED(retc)) retc = DecodePdfParText(dat_str, pnts);

         if(SUCCEEDED(retc)) retc = dat_rec_ptr->SetTextPar(0, pnts); // dat_str);

         if(SUCCEEDED(retc)) retc = dat_rec_ptr->GetNextBrother((KpTreeEntry **)&dat_rec_ptr);

         if(dat_rec_ptr && SUCCEEDED(retc))
         {
            found = False;
            while((!found) && SUCCEEDED(retc))
            {
               in_str = "";
               retc = pInStream->GetWord(&in_str, (const unsigned char *)" \t\r\n<>[]", &delim);

               if(SUCCEEDED(retc))
               {
                  pnts = in_str.ExtractUnsignedValueA();
                  if((strcmp(pnts, "/Filter") == 0) || (strcmp(pnts, "stream") == 0)) found = True;

               } // if(SUCCEEDED(retc))

            } // while((!found) && SUCCEEDED(retc))

         } // if(dat_rec_ptr && SUCCEEDED(retc))

      } // while(dat_rec_ptr && SUCCEEDED(retc))

      break;

   case FdfInputRawA85:
   case FdfInputRawAscii:
      retc = GetKpstFdfData(&in_str, pInStream, iInpMode, bOutMsg);
      KP_NEW(*OutDataRec, XmlTagPars((const unsigned char *)"Data", in_str, NULL, TV_MAIN_CTBL));
      break;

   default:
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
      break;
   }


#if FALSE
KpString in_str;
KpString a85_str;
int ii, jj;

      while(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
         if(SUCCEEDED(retc)) if(in_str=="<</Filter[/A85]>>") break;
      }

      if(SUCCEEDED(retc))
      {
         retc = GetKpstFdfLine(&in_str, pInStream);
         if(in_str!="stream")
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) retc = GetKpstFdfLine(&in_str, pInStream);

      if(SUCCEEDED(retc))
      {
         ii=in_str.index("<~");
         if(ii<0) ii=0;
         else ii+=2;

         jj=in_str.index("~>");
         if(jj<0) jj=in_str.length();

//       a85_str = "<~" + in_str.substr(ii, jj - ii) + "~>";
         a85_str = "<~";
         a85_str += in_str.substr(ii, jj - ii);
         a85_str += "~>";

         if(SUCCEEDED(retc)) if(pInStream->fail())
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) if(pInStream->eof())
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         retc=A85toStr(psOutStr, a85_str);
         if(FAILED(retc))
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetDataDatParStr(KpString *psDatStr, bool bOutMsg)
{
HRESULT retc = S_OK;
static unsigned char dat_fname[KP_MAX_FNAME_LEN + 100];
KpInStream /* KpFStream */ *p_in_file=NULL;
filebuf fb;

   KP_ASSERTE(psDatStr != NULL, E_INVALIDARG, null, bOutMsg);

#if FALSE
// XFS-ui netinka – ten aplikacija pakatalogyje bin/xipa.bin
   if(SUCCEEDED(retc)) retc = GetAppPath(dat_fname, True);
#else
   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dat_fname), KP_E_SYSTEM_ERROR, GetLastError(), True);
   if(SUCCEEDED(retc)) strcat(dat_fname, "\\");
#endif

   if(SUCCEEDED(retc)) strcat(dat_fname, KPST_FDF_DATA_FNAME);

#ifdef Logging
if(SUCCEEDED(retc)) PutLogMessage_("[GSKD] %s", dat_fname);
#endif

// KP_NEW(p_in_file, KpInStream /* KpFStream */ ((const char *)dat_fname, ios::in));
   if(SUCCEEDED(retc)) fb.open((const char *)dat_fname, ios::in);
   KP_NEW(p_in_file, KpInStream(&fb));

   KP_ASSERTE(p_in_file != NULL, KP_E_FILE_NOT_FOUND, dat_fname, bOutMsg);
   KP_ASSERTE((!p_in_file->fail()) && (!p_in_file->eof()), KP_E_FERROR, dat_fname, bOutMsg);

   if(SUCCEEDED(retc)) retc = GetKpstFdfData(psDatStr, p_in_file, FdfInputFdf, bOutMsg);

   if(p_in_file != NULL)
   {
      KP_DELETE(p_in_file);
      fb.close();
   }

return(retc);
}


HRESULT KpStApp::GetDataDatParStr(unsigned char *lpszDatBuf, bool bOutMsg)
{
HRESULT retc = S_OK;
KpString dat_str;

   KP_ASSERTE(lpszDatBuf != null, E_INVALIDARG, null, bOutMsg);

   if(SUCCEEDED(retc)) retc = GetDataDatParStr(&dat_str, bOutMsg);

const unsigned char *dat_ptr = dat_str.ExtractUnsignedValueA();
   KP_ASSERTE(dat_ptr != null, KP_E_FILE_FORMAT, null, bOutMsg);
   KP_ASSERTE(strlen(dat_ptr) < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, dat_ptr, bOutMsg);

   if(SUCCEEDED(retc)) strcpy(lpszDatBuf, dat_ptr);

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveKpstFdfDataRec(const XmlTagPars *pDataRec, KpOutStream *pOutStream, FdfOutputMode iOutMode, bool bOutMsg)
{
HRESULT retc=S_OK;
unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char java_script[MAX_XML_PAR_VAL_LEN + 1];
int par_num;
bool js_fl = False;
KpString out_str;
KpString data_str;
const XmlTagPars *dat_rec_ptr = NULL;
int ii;
// unsigned char out_val[KP_MAX_FILE_LIN_LEN+1];
bool uni_fl = False;
UniChar *uni_buf = NULL;
const unsigned char *pnts = NULL;

   if(((pDataRec == NULL) || (pOutStream == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((iOutMode != FdfOutputFdf) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);

   js_fl = False;
   if(SUCCEEDED(retc))
   {
      retc = pDataRec->SeekTextPar("JavaScript", java_script, &par_num);
      if(SUCCEEDED(retc)) js_fl = True;
      if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
   }

   if(SUCCEEDED(retc))
   {
      *pOutStream << "%FDF-1.2" << endl;
      *pOutStream << "1 0 obj<</FDF<<";
      if(js_fl)
      {
//       retc = pDataRec->SeekTextPar("Doc", par_val, &par_num);
//       if(bOutMsg && (retc == KP_E_KWD_NOT_FOUND))
//          retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
         {
            *pOutStream << "/JavaScript<</Doc 2 0 R >> >> >>" << endl;
            *pOutStream << "endobj" << endl;
            *pOutStream << "2 0 obj" << endl;
//          *pOutStream << "[ (" << par_val << ") 3 0 R ]" << endl;
            *pOutStream << "[ (mano_pdf) 3 0 R ]" << endl;
            *pOutStream << "endobj" << endl;
         }
      }
      else // if(js_fl)
      {
         *pOutStream << "/Fields[";

         dat_rec_ptr = pDataRec;
         ii = FIRST_FDF_FIELD;
         while(dat_rec_ptr && SUCCEEDED(retc))
         {
            retc = dat_rec_ptr->GetCurTextPar(par_nam, par_val);
            if(SUCCEEDED(retc))
               *pOutStream << "<</T(" << par_nam << ")/V " << ii++ << " 0 R>>";

            if(SUCCEEDED(retc)) retc = dat_rec_ptr->GetNextBrother((KpTreeEntry **)&dat_rec_ptr);

         } // while(dat_rec_ptr && SUCCEEDED(retc))

         if(SUCCEEDED(retc))
         {
            *pOutStream << "]>>>>" << endl;
            *pOutStream << "endobj" << endl;
         }

      } // else // if(js_fl)

   } // if(SUCCEEDED(retc))

   dat_rec_ptr = pDataRec;
   ii = FIRST_FDF_FIELD;
   while(dat_rec_ptr && SUCCEEDED(retc))
   {
      retc = dat_rec_ptr->GetCurTextPar(par_nam, par_val);

//    if(SUCCEEDED(retc))
//    {
//       data_str = (const char *)par_val;
//       retc = EncodePdfParText(&out_str, data_str);
// // KpMsgOutF_0(out_str.ExtractUnsignedValueA());
//    }

// nepadeda – Acrobatas vis tiek nerodo user data
//    if(SUCCEEDED(retc)) retc = EncodePdfParText(out_val, par_val, KP_MAX_FILE_LIN_LEN);

      if(SUCCEEDED(retc))
      {
         uni_fl = False;
         pnts = par_val;
         while(*pnts && (!uni_fl)) uni_fl = (*pnts++ >= KPT_FirstKptChar);

         if(uni_fl)
         {
            KP_NEWA(uni_buf, UniChar, 1 + strlen(par_val) + 1);

            if(SUCCEEDED(retc))
            {
               uni_buf[0] = 0xFEFF;
               retc = KptStrToUnicode(uni_buf + 1, par_val, dat_rec_ptr->GetValCtbl());
               if(bOutMsg && FAILED(retc))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               retc = UniStrToA85(&data_str, uni_buf);
// printf("---- >>>> %d %d %x\n", strlen(data_str.ExtractValueA()), strlen(par_val), retc);
               if(bOutMsg && FAILED(retc))
                  retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
            }

         }
         else // if(uni_fl)
         {
            out_str = (const char *)par_val; // out_val;

            retc = StrToA85(&data_str, out_str); // out_str);
// printf("---- <<<< %d %d %x\n", strlen(data_str.ExtractValueA()), strlen(par_val), retc);
            if(bOutMsg && FAILED(retc))
               retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);

         } // else // if(uni_fl)

      } // if(SUCCEEDED(retc))

      if(SUCCEEDED(retc))
      {
         *pOutStream << ii++ << " 0 obj" << endl;
//        if(!uni_fl)
            *pOutStream << "<</Filter[/A85]>>" << endl;
         *pOutStream << "stream" << endl;
//       if(uni_fl) pOutStream->write((const char *)uni_buf, wcslen(uni_buf) * sizeof(UniChar));
//       else
         {
KpString str_tmp(data_str.substr(2, data_str.length()-2));
            *pOutStream << str_tmp.ExtractValueA();
         }
         *pOutStream << endl;
         *pOutStream << "endstream" << endl;
         *pOutStream << "endobj" << endl;
      }

      KP_DELETE(uni_buf);

      if(SUCCEEDED(retc)) retc = dat_rec_ptr->GetNextBrother((KpTreeEntry **)&dat_rec_ptr);

   } // while(dat_rec_ptr && SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      *pOutStream << "trailer" << endl;
      *pOutStream << "<</Root 1 0 R>>" << endl;
      *pOutStream << "%%EOF" << endl;
   }

   if(SUCCEEDED(retc))
      if(pOutStream->fail() || pOutStream->eof())
      {
         retc = KP_E_FERROR;
         if(bOutMsg) retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }

return(retc);
}


// ------------------------------
HRESULT KpStApp::EncAtmKod(KpString *AtmKod, KpString FileName)
{
HRESULT retc = S_OK;
KpString new_atm_kod;
KpString file_name;
int atmkod_length;
int fname_length;
int count;
int shift;
int ii;
char ch;
char ch1;
char ch2;
KpString tmp_str;

   if((AtmKod == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      new_atm_kod = "";
      file_name = FileName;

      retc = file_name.tolower();
   }

   if(SUCCEEDED(retc))
   {
      atmkod_length = AtmKod->length();
      count = atmkod_length;
      fname_length = file_name.length();
      if(fname_length < count) count = fname_length;
      shift = fname_length - count - 4; // iki ".fdf"
      if(shift < 0) shift = 0;

      for(ii = 0; ii < count; ii++)
      {
         tmp_str = AtmKod->substr(ii, 1);
         ch1 = (tmp_str.ExtractUnsignedValueA())[0];
         tmp_str = file_name.substr(ii + shift, 1);
         ch2 = (tmp_str.ExtractUnsignedValueA())[0] & 0x1F;
         ch = ch1 ^ ch2;

         new_atm_kod += ch;
      }

      new_atm_kod += AtmKod->substr(count, atmkod_length - count);

      *AtmKod = new_atm_kod;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedKeyReg(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=NULL;
DWORD dwBufLen;
DWORD dwValType;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_buf[KP_MAX_FILE_LIN_WDT + 1];
unsigned char publisher[KP_MAX_FNAME_LEN + 1];
int prod_ver=0;
int num_of_lics=0;
// unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int key_add = 0;
int lic_high = 0;

// --------------------
   hKey=0;

   if(SUCCEEDED(retc)) retc=GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
// if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);


#if FALSE
char str_buf[100];
sprintf(str_buf, "%d", prod_ver);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// if(SUCCEEDED(retc))
// {
//    m_iInstKey1=0;
//    m_iInstKey2=0;
//    m_iInstKey3=0;
//    m_iInstKey4=0;
// }
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY4);

   if(SUCCEEDED(retc))
   {
//    m_iLicID=KpstRand(0);
      retc=InitLicId();
   }
// if(SUCCEEDED(retc))
// {
//    m_iLicCode1=0;
//    m_iLicCode2=0;
//    m_iLicCode3=0;
// }
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE3);

   if(SUCCEEDED(retc))
   {
      if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
      {
         sprintf((char *)key_name,
            "Software\\%s\\%d", // "Software\\%s\\%s",
            publisher,
            prod_ver // prod_name
            );

         retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey);
         if(retw!=ERROR_SUCCESS)
         {
            retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
            KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         }

// -------------------- key
         key_buf[0]=Nul;

         if(SUCCEEDED(retc))
         {
            dwBufLen=KP_MAX_FILE_LIN_WDT;
            retw=RegQueryValueEx(hKey, "RegKey", NULL, &dwValType, (LPBYTE)key_buf, &dwBufLen);
            if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
            {
               key_buf[0]=Nul;
               retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
//             KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            }
            else key_buf[dwBufLen]=Nul;
         }

         if(SUCCEEDED(retc)) retc = ExtractHigh(key_buf, &key_add, 16);

         if(SUCCEEDED(retc)) retc = SaveRestDaysInitHp11(key_add); // anksèiau reikëjo tik po lic_high nuskanavimo, dabar galima ir èia

         if(SUCCEEDED(retc)) retc = ScanInstKeyFull(key_buf);


// -------------------- lic
         key_buf[0]=Nul;

         if(SUCCEEDED(retc))
         {
            dwBufLen=KP_MAX_FILE_LIN_WDT;
            retw=RegQueryValueEx(hKey, "Licence", NULL, &dwValType, (LPBYTE)key_buf, &dwBufLen);
            if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
            {
               key_buf[0]=Nul;
               retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            }
            else key_buf[dwBufLen]=Nul;
         }

         if(SUCCEEDED(retc)) retc = ExtractHigh(key_buf, &lic_high, 12);
//       if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_high, KP11_LIC_HIGH);
         if(SUCCEEDED(retc)) retc = SaveLicHighHp11(lic_high);

//       if(SUCCEEDED(retc)) retc = SaveRestDaysInitHp11(key_add); // anksèiau reikëjo tik èia, po lic_high nuskanavimo, dabar galima ir iðkart po key_add nuskanavimo

         if(SUCCEEDED(retc)) retc = ScanLic(key_buf);

         if(SUCCEEDED(retc)) retc=UnpackLic();

         if(hKey)
         {
            retw=RegCloseKey(hKey);
//          if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            hKey=NULL;
         }

      } // if((num_of_lics==0) || (this-ptr->m_iKpStMode!=KpStarterMode))

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
#if FALSE
HRESULT KpStApp::GetLicHigh(void)
{
HRESULT retc = S_OK;
static unsigned char dat_fname[KP_MAX_FNAME_LEN+100];
KpString dat_fname_str;
KpString par_val_str;
int lic_high = 0;

   par_val_str = "0";

// ---------------------------
   if(SUCCEEDED(retc)) retc = GetAppPath(dat_fname, True);

// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dat_fname), KP_E_SYSTEM_ERROR, GetLastError(), True);
// if(SUCCEEDED(retc)) strcat(dat_fname, "\\");

   if(SUCCEEDED(retc))
   {
      strcat(dat_fname, KPST_FDF_DATA_FNAME);
      dat_fname_str = dat_fname;
   }

// ---------------------------
   if(SUCCEEDED(retc))
   {
      retc = GetDataDatVariable(&dat_fname_str, (const unsigned char *)"LH", &par_val_str, False);
      if(FAILED(retc))
      {
         par_val_str = "0";
         retc = S_OK;
      }
   }

   if(SUCCEEDED(retc)) sscanf(par_val_str.ExtractValueA(), "%d", &lic_high);
// if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_high, KP11_LIC_HIGH);
   if(SUCCEEDED(retc)) retc = SaveLicHighHp11(lic_high);

return(retc);
}
#endif


HRESULT KpStApp::GetSavedKeyDat(KpString *psRegDatStr)
{
HRESULT retc = S_OK;
KpString dat_str;
KpString rest_str;
KpString *sub_str = NULL;
int tab_pos;
int num_of_lics = 0;
static unsigned char key_buf[KP_MAX_FILE_LIN_WDT + 1];
const unsigned char *pnts = NULL;
const char *pnts1 = NULL;
int key_add = 0;
int lic_high = 0;
bool check_flash = False;

#ifdef Logging
PutLogMessage_("[RDD 1]");
#endif

   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);

// --------------------
// if(SUCCEEDED(retc))
// {
//    m_iInstKey1=0;
//    m_iInstKey2=0;
//    m_iInstKey3=0;
//    m_iInstKey4=0;
// }
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY4);

   if(SUCCEEDED(retc))
   {
//    m_iLicID=KpstRand(0);
      retc=InitLicId();
   }
// if(SUCCEEDED(retc))
// {
//    m_iLicCode1=0;
//    m_iLicCode2=0;
//    m_iLicCode3=0;
// }
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_LIC_CODE3);

   if(SUCCEEDED(retc))
   {
      if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
      {
         if(SUCCEEDED(retc)) retc = GetDataDatParStr(&dat_str, check_flash);

         if(psRegDatStr && SUCCEEDED(retc)) *psRegDatStr = dat_str; // gràþinam iðkoduotà data.dat reikðmæ

         if(SUCCEEDED(retc))
         {
            key_buf[0] = Nul;

            tab_pos = dat_str.index("\t");
//          sub_str = &static_cast<KpString>(dat_str.substr(0, tab_pos));
         }
         KP_NEW(sub_str, KpString(dat_str.substr(0, tab_pos)));
         if(SUCCEEDED(retc))
         {
#if (CompilerGr==Mingw) || (__WATCOMC__ > 1201)
            pnts = sub_str->ExtractUnsignedValueA();
#else
            pnts = (const unsigned char *)(pnts1 = *sub_str);
#endif
            if(pnts)
            {
               strncpy(key_buf, pnts, KP_MAX_FILE_LIN_WDT);
#if (Compiler==Mingw)
//             KP_DELETEA(pnts);
#endif
               pnts = NULL;
            }
         }
         KP_DELETE(sub_str);
         if(SUCCEEDED(retc)) key_buf[KP_MAX_FILE_LIN_WDT] = Nul;
#ifdef Logging
PutLogMessage_("[RDD 2] %d %s %x", cMemBank[KP11_COMPID/2], key_buf, retc);
#endif
         if(SUCCEEDED(retc)) retc = ExtractHigh(key_buf, &lic_high, 12);
//       if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_high, KP11_LIC_HIGH);
         if(SUCCEEDED(retc)) retc = SaveLicHighHp11(lic_high);

         if(SUCCEEDED(retc)) retc = ScanInstCodeFull(key_buf);

         if(SUCCEEDED(retc))
         {
            rest_str=dat_str.substr(tab_pos+1, dat_str.length()-(tab_pos+1));

            tab_pos=rest_str.index("\t");
         }
         KP_NEW(sub_str, KpString(rest_str.substr(0, tab_pos)));
         if(SUCCEEDED(retc))
         {
#if (CompilerGr==Mingw) || (__WATCOMC__ > 1201)
            pnts = sub_str->ExtractUnsignedValueA();
#else
            pnts = (const unsigned char *)(pnts1 = *sub_str);
#endif
            if(pnts)
            {
               strncpy(key_buf, pnts, KP_MAX_FILE_LIN_WDT);
#if (Compiler==Mingw)
//             KP_DELETEA(pnts);
#endif
               pnts = NULL;
            }
         }
         KP_DELETE(sub_str);
         if(SUCCEEDED(retc)) key_buf[KP_MAX_FILE_LIN_WDT]=Nul;

         if(SUCCEEDED(retc)) retc = ExtractHigh(key_buf, &key_add, 16);

//       if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
//       if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high); // reikðmæ dar turim, o jau ir nebereikia
         if(SUCCEEDED(retc))
         {
//          retc = SaveRestDaysInitHp11AndRestore(key_add); // èia negerai – HP11_LICID dar nenustatytas
            retc = SaveRestDaysInitHp11(key_add); // tik atsimenam á KP11_REST_DAYS_INIT, á failà áraðinësim ir inicializuosim po CheckReg() – kai jau bus nustatytas HP11_LICID
            if(FAILED(retc)) KP_ERROR(retc, null);
         }

         if(SUCCEEDED(retc)) retc = ScanInstKeyFull(key_buf);

      } // if((num_of_lics==0) || (this-ptr->m_iKpStMode!=KpStarterMode))

   } // if(SUCCEEDED(retc))

// ---------------------
// if(SUCCEEDED(retc)) retc = GetLicHigh();

return(retc);
}


// ------------------------------
#if FALSE
HRESULT KpStApp::SaveKeyReg(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_buf[KP_MAX_FILE_LIN_WDT + 1];
DWORD dwDisposition;
bool admin_fl;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
// unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int lic_high = 0;

   if(SUCCEEDED(retc)) retc=GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
// if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);

// ---------------------
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );

      retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, NULL /* "" */, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition);

      if(retw!=ERROR_SUCCESS)
      {
         retc=TestAdmin(&admin_fl);
         if(SUCCEEDED(retc))
         {
            if(!admin_fl)
            {
               retc=KP_E_ACCESS_DENIED;
               KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
               KpMsgOut(KPST_MSG_REG_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
      }
   }

// --------------------- key
   if(SUCCEEDED(retc)) /* retc = */ FormatInstCodeFull(key_buf);

// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
   if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high);
   if(SUCCEEDED(retc)) retc = AddHigh(key_buf, lic_high, 12);

   if(SUCCEEDED(retc))
   {
      retw=RegSetValueEx(hKey, "RegKey", 0, REG_SZ, key_buf, strlen(key_buf));
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

// --------------------- lic
   if(SUCCEEDED(retc)) /* retc = */ FormatLicCodeFull(key_buf);

// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
// if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high); // jau turim
   if(SUCCEEDED(retc)) retc = AddHigh(key_buf, lic_high, 12);

   if(SUCCEEDED(retc))
   {
      retw=RegSetValueEx(hKey, "Licence", 0, REG_SZ, key_buf, strlen(key_buf));
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(hKey)
   {
      retw=RegCloseKey(hKey);
      if(retw!=ERROR_SUCCESS)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      hKey=0;
   }

return(retc);
}
#endif


// ------------------------------
HRESULT KpStApp::SaveKeyDat(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
bool admin_fl;
KpFStream *p_out_file=NULL;
static unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
static unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *add_data=NULL;
KpString data_str;
KpString out_str;
bool data_fl[KPSTAP_NUM_OF_SETS]={False, False, False};
static unsigned char dat_fname[KP_MAX_FNAME_LEN+100];
KpString dat_fname_str;
// unsigned char val_buf[MAX_LONG_DIGITS + 1];
// KpString val_buf_str;
int lic_high = 0;
int key_add = 0;

   KP_NEWA(add_data, unsigned char, KP_MAX_FILE_LIN_LEN + 100);

// if(SUCCEEDED(retc)) retc = GetAppPath(dat_fname, True); // netinka xipa.bin – paleidþiamas ið virtualaus pakatalogio ./bin
// if(SUCCEEDED(retc)) GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dat_fname);
   if(SUCCEEDED(retc)) retc = GetLocalPath(dat_fname, KP_LocalDir, True);

// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dat_fname), KP_E_SYSTEM_ERROR, GetLastError(), True);
// if(SUCCEEDED(retc)) strcat(dat_fname, "\\");

   if(SUCCEEDED(retc))
   {
      strcat(dat_fname, KPST_FDF_DATA_FNAME);
      dat_fname_str = dat_fname;
   }

   KP_NEW(p_out_file, KpFStream((const char *)dat_fname, ios::out));

   if(SUCCEEDED(retc)) if(p_out_file->fail()) retc = KP_E_DIR_ERROR;

// -----------------------------
   if(SUCCEEDED(retc)) /* retc = */ FormatInstCodeFull(code_buf);
// if(SUCCEEDED(retc)) retc = RemoveSpaces(code_buf);

#ifdef Logging
PutLogMessage_("[SKD 1] %d %s %x", cMemBank[KP11_COMPID/2], code_buf, retc);
#endif

// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
   if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high);
   if(SUCCEEDED(retc)) retc = AddHigh(code_buf, lic_high, 12);

   if(SUCCEEDED(retc)) /* retc = */ FormatInstKeyFull(key_buf);
// if(SUCCEEDED(retc)) retc = RemoveSpaces(key_buf);

// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
// if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high); // jau turim, o jau ir nebereikia
   if(SUCCEEDED(retc)) retc = GetRestDaysInitHp11(&key_add);
   if(SUCCEEDED(retc)) retc = AddHigh(key_buf, key_add, 16);

   if(SUCCEEDED(retc)) retc = FormAddData(add_data, data_fl, 1, 0, False);

#ifdef Logging // #if FALSE //
PutLogMessage_("[sk] li: %d pv: %d rli: %d rpv: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
PutLogMessage_("[sk] lc: %x %x %x", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
PutLogMessage_("[sk] ic: %x %x %x %x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
PutLogMessage_("[sk] ik: %x %x %x %x", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
#endif

   if(SUCCEEDED(retc))
   {
      data_str = (const char *)code_buf;
      data_str += "\t";
      data_str += (const char *)key_buf;
      data_str += "\t";
      data_str += (const char *)add_data;

      retc = StrToA85(&out_str, data_str);
      if(FAILED(retc))
         retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

// -----------------------------
   if(SUCCEEDED(retc))
   {
      *p_out_file << "%FDF-1.2" << endl;
      *p_out_file << "1 0 obj<</FDF<</Fields[<</T(PI)/V 3 0 R>>]>>>>" << endl; // KPST_PROGRAM_ID_VAR_NAME
      *p_out_file << "endobj" << endl;
      *p_out_file << "3 0 obj" << endl;
      *p_out_file << "<</Filter[/A85]>>" << endl;
      *p_out_file << "stream" << endl;

KpString str_tmp(out_str.substr(2, out_str.length()-2));
      *p_out_file << str_tmp.ExtractValueA() << ">" << endl;

      *p_out_file << "endstream" << endl;
      *p_out_file << "endobj" << endl;
      *p_out_file << "trailer" << endl;
      *p_out_file << "<</Root 1 0 R>>" << endl;
      *p_out_file << "%%EOF" << endl;

      p_out_file->close();

      if((p_out_file->fail() || p_out_file->eof()) && SUCCEEDED(retc)) retc = KP_E_FERROR;
   }

// -----------------------------
#if FALSE
// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
   if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)val_buf, "%d", lic_high);
      val_buf_str = val_buf;
      retc = SetDataDatVariable(&dat_fname_str, (const unsigned char *)"LH", &val_buf_str, False);
   }
#endif

// -----------------------------
   if((retc == KP_E_DIR_ERROR) || (retc == KP_E_FERROR))
   {
#ifdef Logging
PutLogMessage_("[SKD 1.5] %d %s %x", cMemBank[KP11_COMPID/2], code_buf, retc);
#endif
      retc0 = TestAdmin(&admin_fl);
      if(SUCCEEDED(retc0))
      {
         if(!admin_fl)
         {
            retc = KP_E_ACCESS_DENIED;
         /* retc = */ KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
//          KpMsgOut(KPST_MSG_REG_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
         }
         else
         {
// negerai – IPA TUX atmintuke pirmà k. paleidþiant bando raðyti á CD-ROM-iná atmintukà
//          retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
            retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }
      }
      else if(SUCCEEDED(retc)) retc = retc0;
   }

// -----------------------------
   KP_DELETE(p_out_file);
   KP_DELETEA(add_data);

#ifdef Logging
PutLogMessage_("[SKD 2] %d %s [%s] %x", cMemBank[KP11_COMPID/2], code_buf, dat_fname, retc);
unsigned char *fbuf = null;
ReadFileContents(dat_fname, &fbuf, NULL, False, False);
if(fbuf != null)
{
PutLogMessage_(fbuf);
KP_DELETEA(fbuf);
}
#endif

return(retc);
}


// ------------------------------
HRESULT KpStApp::DelSavedKey(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
LONG retw0=ERROR_SUCCESS;
HKEY hKey=0;
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
DWORD dwBufLen;
DWORD dwValType;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
bool admin_fl;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;

   if(SUCCEEDED(retc)) retc=GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

// --------------------
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d",
         publisher,
         prod_ver
         );

      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, KEY_ALL_ACCESS, &hKey);
      if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
   }

   if(SUCCEEDED(retc))
   {
// --------------------------------------- tikrinam ar dar yra
      dwBufLen=KP_MAX_FILE_LIN_WDT;
      retw=RegQueryValueEx(hKey, "RegKey", NULL, &dwValType, (LPBYTE)key_buf, &dwBufLen);
      if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
      {
         key_buf[0]=Nul;
         retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }
      else key_buf[dwBufLen]=Nul;

      if(SUCCEEDED(retc) /* retc==KP_E_KWD_NOT_FOUND */)
      {
// --------------------------------------- taip - metam lauk
         retw=ERROR_SUCCESS;

#if FALSE
//       retw=RegDeleteKeyEx(hKey, "RegKey", KEY_WOW64_32KEY, 0);
         retw=RegDeleteKey(hKey, "RegKey");

//       retw0=RegDeleteKeyEx(hKey, "Licence", KEY_WOW64_32KEY, 0);
         retw0=RegDeleteKey(hKey, "Licence");
         if(retw==ERROR_SUCCESS) retw=retw0;
#endif

         sprintf((char *)key_name, "Software\\%s", publisher);

         retw0=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey);
         if(retw0!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND; // neturetu taip buti - ka tik matem subkey

         if(SUCCEEDED(retc))
         {
            sprintf((char *)key_name, "%d", prod_ver);

            retw0=RegDeleteKey(hKey, (LPCTSTR)key_name);
            if(retw==ERROR_SUCCESS) retw=retw0;

            if(retw!=ERROR_SUCCESS)
            {
               retc=TestAdmin(&admin_fl);
               if(SUCCEEDED(retc))
               {
                  if(!admin_fl)
                  {
                     retc=KP_E_ACCESS_DENIED;
                     KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
                     KpMsgOut(KPST_MSG_UNREG_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
                  }
                  else
                  {
// neturetu taip buti - ka tik dar buvo
//                   retc=S_OK;
// static unsigned char str_buf[2000];
//                   sprintf((char *)str_buf, (const char *)KPST_MSG_ALLREADY_REMOVED, prod_name);
//                   KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);

//                   retc=KP_E_SYSTEM_ERROR;
                     retc=KP_E_KWD_NOT_FOUND;
                     retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
                  }

               } // if(SUCCEEDED(retc))

            } // if(retw!=ERROR_SUCCESS)

         } // if(SUCCEEDED(retc))

      } // if(SUCCEEDED(retc) /* retc==KP_E_KWD_NOT_FOUND */)

   } // if(SUCCEEDED(retc))

// --------------------
   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      hKey=NULL;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetAtmKodTxt(unsigned char *lpszAtmKodBuf)
{
HRESULT retc=S_OK;
// long flash_id;
static unsigned char dat_fname[KP_MAX_FNAME_LEN+100];
filebuf fb;
KpInStream *in_file_ptr = NULL;
XmlTagPars *data_rec = NULL;
static unsigned char par_val[TV_TAG_LEN + MAX_XML_PAR_VAL_LEN + 1];
// int par_num;
// unsigned char *pntd;

dat_fname[0] = Nul;
strcpy(par_val, KPST_ATM_KOD_NULL);

   KP_ASSERT(lpszAtmKodBuf, E_INVALIDARG, null, True);

// ---------------------------
// if(SUCCEEDED(retc)) retc = GetIniFlashId(&flash_id);

// ---------------------------
   if(SUCCEEDED(retc)) retc = GetAppPath(dat_fname, True);

// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dat_fname), KP_E_SYSTEM_ERROR, GetLastError(), True);
// if(SUCCEEDED(retc)) strcat(dat_fname, "\\");

   if(SUCCEEDED(retc)) strcat(dat_fname, KPST_FDF_DATA_FNAME);

#if FALSE // èia senas AtmKod algoritmas
   if(SUCCEEDED(retc))
   {
      if(!fb.open((const char *)dat_fname, ios::in))
      {
//       retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, NULL);
//       strcpy(par_val, KPST_ATM_KOD_NULL);
      }
      else
      {
         KP_NEW(in_file_ptr, KpInStream(&fb));

         if(SUCCEEDED(retc))
         {
            retc = GetKpstFdfDataRec(&data_rec, in_file_ptr, FdfInputFdf);

            if((data_rec == NULL) || FAILED(retc)) // && SUCCEEDED(retc))
            {
//             retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
//             retc = KP_E_FILE_FORMAT;
//             strcpy(par_val, KPST_ATM_KOD_NULL);
               retc = S_OK;
            }
            else if(SUCCEEDED(retc))
            {
               retc = data_rec->SeekTextPar("AI", par_val, &par_num);
               if(retc == KP_E_KWD_NOT_FOUND)
               {
//                if(flash_id != 0) /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
                  strcpy(par_val, KPST_ATM_KOD_NULL);
                  retc = S_OK;
               }
            }
         }

         KP_DELETE(data_rec);

         fb.close();

         KP_DELETE(in_file_ptr);

      } // else // if(!fb.open((const char *)dat_fname, ios::in))

      if(SUCCEEDED(retc))
      {
         pntd = strchr(par_val, '-');
         if(pntd == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         *(pntd+1) = Nul;
         if(strlen(par_val) >= TV_TAG_LEN - 2 * MAX_LONG_DIGITS) // - 6)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
      }

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      flash_id = flash_id & 0xFFFF;
      flash_id = flash_id ^ 0xFFFF;

      sprintf((char *)lpszAtmKodBuf, "%s%ld%d", par_val, flash_id, ChSum(flash_id));
   }
#else // #if FALSE // èia senas AtmKod algoritmas

KpString fname_s((const char *)dat_fname);
KpString atm_kod_s;

   if(SUCCEEDED(retc)) retc = GetDataDatVariable(&fname_s, (const unsigned char *)"AI", &atm_kod_s, False);
   if(SUCCEEDED(retc))
   {
      strncpy(lpszAtmKodBuf, atm_kod_s.ExtractValueA(), TV_TAG_LEN);
      lpszAtmKodBuf[TV_TAG_LEN] = Nul;
   }

#endif // naujas algoritmas

return(retc);
}


// ------------------------------
HRESULT KpStApp::CheckPrivileges(const unsigned char *lpszMsg)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
HKEY res_key=0;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT + 1];
unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1];
DWORD dwDisposition;
bool admin_fl;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
// unsigned char prod_name[KP_MAX_FNAME_LEN+1];


   if(SUCCEEDED(retc)) retc=GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
// if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);

   admin_fl = bAdminFl;

// --------------------- key
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );

      if(admin_fl)
         retw = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, NULL /* "" */, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
            &hKey, &dwDisposition);

   /* retc = */ GetSavedKeyDat(NULL);
   /* if(SUCCEEDED(retc)) retc = */ ReCalcLicCode();
   /* if(SUCCEEDED(retc)) retc = */ UnpackInstCode();
      retc = SaveKeyDat(); // fiktyviai tikrinam ar ásiraðo

//    if((retw != ERROR_SUCCESS) || (!admin_fl)) // leidþiam ir ne adminui registruotis – diegiamiems MIKams (ISM)
      if(FAILED(retc))
      {
//       retc = TestAdmin(&admin_fl);
//       if(SUCCEEDED(retc))
         {
            if(!admin_fl)
            {
//             retc = KP_E_ACCESS_DENIED; // paliekam SaveKeyDat() klaidos kodà
               KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
               KpMsgOut(lpszMsg, IDI_ERROR, KP_MB_BAIGTI);
            }
            else
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
      }
   }

// -----------------
// if(SUCCEEDED(retc))
   if(retw == ERROR_SUCCESS)
   {
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      retw = RegCreateKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR)key_name,
         0, NULL /* "" */, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw != ERROR_SUCCESS)
      {
//       retc = KP_E_ACCESS_DENIED;
         KpErrorProc.OutputErrorMessage(KP_E_ACCESS_DENIED, retw, False, __FILE__, __LINE__, 0L, NULL);
//       KpMsgOut(lpszMsg, IDI_ERROR, KP_MB_BAIGTI);
      }
   }

return(retc);
}


//-------------------------------------------- hash function / pseudo random generator
int KpstRand(int prev)
{
HRESULT retc=S_OK;

#if TRUE
static KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_RAND;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=prev;

// PutLogMessage_("KpStApp::KR ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars);

return(rc_pars.value);

#else

return((prev*30497L+22571) % 65536);

#endif
}


int KpstXRand(int prev)
{
HRESULT retc = S_OK;

#if TRUE
static KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_XRAND;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=prev;

// PutLogMessage_("KpStApp::KXR ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars);

return(rc_pars.value);
#endif
}


//------------------- converts integer security key to pseudo-hex string
unsigned char EncKpHexDig(int iDigit)
{
HRESULT retc = S_OK;
unsigned char ret_val = '0';

   switch(iDigit)
   {
   case  0: ret_val = 'J'; break;
   case  1: ret_val = '1'; break;
   case  2: ret_val = '2'; break;
   case  3: ret_val = '3'; break;
   case  4: ret_val = '4'; break;
   case  5: ret_val = '5'; break;
   case  6: ret_val = '6'; break;
   case  7: ret_val = '7'; break;
   case  8: ret_val = '8'; break;
   case  9: ret_val = '9'; break;
   case 10: ret_val = 'A'; break;
   case 11: ret_val = 'L'; break;
   case 12: ret_val = 'R'; break;
   case 13: ret_val = 'G'; break;
   case 14: ret_val = 'E'; break;
   case 15: ret_val = 'U'; break;
   case 16: ret_val = 'B'; break;
   case 17: ret_val = 'C'; break;
   case 18: ret_val = 'D'; break;
   case 19: ret_val = 'F'; break;
   case 20: ret_val = 'H'; break;
   case 21: ret_val = 'Y'; break;
   case 22: ret_val = 'K'; break;
   case 23: ret_val = 'M'; break;
   case 24: ret_val = 'N'; break;
   case 25: ret_val = 'X'; break;
   case 26: ret_val = 'P'; break;
   case 27: ret_val = 'Q'; break;
   case 28: ret_val = 'S'; break;
   case 29: ret_val = 'T'; break;
   case 30: ret_val = 'V'; break;
   case 31: ret_val = 'Z'; break;
   default:
      retc = KP_E_ILL_CODE; // KP_ERROR(E_INVALIDARG, null, True);
      break;
   }

return(ret_val);
}


HRESULT FormatKeyHex(unsigned char *szKeyBuf, int iKey)
{
HRESULT retc=S_OK;
unsigned char *pntd;

   sprintf((char *)szKeyBuf, "%04X", iKey);

   pntd=szKeyBuf;
   while(*pntd)
   {
      switch(*pntd)
      {
      case '0':
         *pntd='J';
         break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         break;
      case 'A':
         *pntd='A';
         break;
      case 'B':
         *pntd='L';
         break;
      case 'C':
         *pntd='R';
         break;
      case 'D':
         *pntd='G';
         break;
      case 'E':
         *pntd='E';
         break;
      case 'F':
         *pntd='U';
         break;
      }

      pntd++;
   }

return(retc);
}


#if Envir==MSWin32Mfc
HRESULT FormatKeyHex(CString *sKey, int iKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[MAX_LONG_DIGITS+1];

   if(sKey==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=FormatKeyHex(key_buf, iKey);
   if(SUCCEEDED(retc)) *sKey=key_buf;

return(retc);
}
#endif


int DecKpHexDig(unsigned char cDigit)
{
HRESULT retc = S_OK;
int ret_val = 0;

   switch(toupper(cDigit))
   {
   case 'J': ret_val = 0; break;
   case '1': ret_val = 1; break;
   case '2': ret_val = 2; break;
   case '3': ret_val = 3; break;
   case '4': ret_val = 4; break;
   case '5': ret_val = 5; break;
   case '6': ret_val = 6; break;
   case '7': ret_val = 7; break;
   case '8': ret_val = 8; break;
   case '9': ret_val = 9; break;
   case 'A': ret_val = 10; break;
   case 'L': ret_val = 11; break;
   case 'R': ret_val = 12; break;
   case 'G': ret_val = 13; break;
   case 'E': ret_val = 14; break;
   case 'U': ret_val = 15; break;
   case 'B': ret_val = 16; break;
   case 'C': ret_val = 17; break;
   case 'D': ret_val = 18; break;
   case 'F': ret_val = 19; break;
   case 'H': ret_val = 20; break;
   case 'Y': ret_val = 21; break;
   case 'K': ret_val = 22; break;
   case 'M': ret_val = 23; break;
   case 'N': ret_val = 24; break;
   case 'X': ret_val = 25; break;
   case 'P': ret_val = 26; break;
   case 'Q': ret_val = 27; break;
   case 'S': ret_val = 28; break;
   case 'T': ret_val = 29; break;
   case 'V': ret_val = 30; break;
   case 'Z': ret_val = 31; break;
   default:
      retc = KP_E_ILL_CODE; // KP_ERROR(E_INVALIDARG, null, True);
      break;
   }

return(ret_val);
}


HRESULT ScanKeyHex(const unsigned char *szKeyBuf, int *piKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[5];
unsigned char *pntd;

   if(szKeyBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(strlen(szKeyBuf)>4)
   {
// KP_TRACE(szKeyBuf);
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      strncpy(key_buf, szKeyBuf, 4);
      key_buf[4]=Nul;

      pntd=key_buf;
      while(*pntd)
      {
         switch(toupper(*pntd))
         {
         case 'J':
            *pntd='0';
            break;
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
            break;
         case 'A':
            *pntd='A';
            break;
         case 'L':
            *pntd='B';
            break;
         case 'R':
            *pntd='C';
            break;
         case 'G':
            *pntd='D';
            break;
         case 'E':
            *pntd='E';
            break;
         case 'U':
            *pntd='F';
            break;
         default:
            retc=KP_E_ILL_CODE; // retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            break;
         }

         pntd++;
      }

      sscanf((const char *)key_buf, "%x", piKey);
   }

return(retc);
}

#if Envir==MSWin32Mfc
HRESULT ScanKeyHex(const CString *sKey, int *piKey)
{
HRESULT retc = S_OK;
unsigned char *buf_ptr;

   if((sKey==NULL) || (piKey==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(buf_ptr, unsigned char[sKey->GetLength() + 1);

   if(SUCCEEDED(retc)) strcpy(buf_ptr, *sKey);

   if(SUCCEEDED(retc)) retc = ScanKeyHex(buf_ptr, piKey);

return(retc);
}
#endif


// ------------------------------
HRESULT KpStApp::FormatLicCodeFull(unsigned char *lpszLic)
{
HRESULT retc=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int lic_code1=0;
int lic_code2=0;
int lic_code3=0;

   if((lpszLic==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code1, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code2, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code3, KP11_LIC_CODE3);

   if(SUCCEEDED(retc)) retc=FormatKeyHex(code_buf, lic_code1 /* m_iLicCode1 */);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszLic, code_buf);
      strcat(lpszLic, "-");
      retc=FormatKeyHex(code_buf, lic_code2 /* m_iLicCode2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszLic, code_buf);
      strcat(lpszLic, "-");
      retc=FormatKeyHex(code_buf, lic_code3 /* m_iLicCode3 */);
   }
   if(SUCCEEDED(retc))
      strcat(lpszLic, code_buf);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ScanLic(const unsigned char *lpszLic)
{
HRESULT retc=S_OK;
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT+1];
int lic_code1=0;
int lic_code2=0;
int lic_code3=0;

   if((lpszLic==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszLic) != 4 + 1 + 4 + 1 + 4)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
   {
      strcpy(lic_buf, lpszLic);
      if((lic_buf[4]!='-') || (lic_buf[9]!='-'))
         retc=KP_E_ILL_CODE;
   }

   if(SUCCEEDED(retc)){ lic_buf[4]=Nul; lic_buf[9]=Nul; }

   if(SUCCEEDED(retc)) retc=ScanKeyHex(lic_buf, &lic_code1 /* &m_iLicCode1 */); // outputs error messages !!!
   if(SUCCEEDED(retc)) retc=ScanKeyHex(lic_buf+5, &lic_code2 /* &m_iLicCode2 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(lic_buf+10, &lic_code3 /* &m_iLicCode3 */);

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code1, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code2, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code3, KP11_LIC_CODE3);

return(retc);
}


// ------------------------------
HRESULT KpStApp::UnpackLic(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_lic_r;
int prod_ver=0;
int lic_id=0;
int lic_code1=0;
int lic_code2=0;
int lic_code3=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code1, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code2, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_code3, KP11_LIC_CODE3);

   if(SUCCEEDED(retc))
   {
      ch_sum_lic_r=KpstRand(lic_code3 /* m_iLicCode3 */);

      lic_id = lic_code1 /* m_iLicCode1 */ ^ ch_sum_lic_r;
//    m_iLicID=lic_id;
      retc=EmuTv.SetHp11Variable(lic_id, KP11_LICID);
   }
   if(SUCCEEDED(retc))
      if((lic_code2 /* m_iLicCode2 */ ^ ch_sum_lic_r)!=prod_ver)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
      if((lic_id +prod_ver)%0x10000 != lic_code3 /* m_iLicCode3 */)
         retc=KP_E_ILL_CODE;
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_UNPACK_LIC;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::UL ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc = KP_E_ILL_CODE;

return(retc);
}


// ------------------------------
HRESULT KpStApp::CalcLicCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_lic_r;
int prod_ver=0;
int lic_id=0;
int lic_code1=0;
int lic_code2=0;
int lic_code3=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

   if(SUCCEEDED(retc))
   {
      lic_code3 /* m_iLicCode3 */ = (lic_id /* m_iLicID */ + prod_ver)%0x10000;
      ch_sum_lic_r=KpstRand(lic_code3 /* m_iLicCode3 */);
      lic_code1 /* m_iLicCode1 */ = lic_id /* m_iLicID */ ^ ch_sum_lic_r;
      lic_code2 /* m_iLicCode2 */ = prod_ver^ch_sum_lic_r;
   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code1, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code2, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(lic_code3, KP11_LIC_CODE3);
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_CALC_LIC_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::CLC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ReCalcLicCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_rand;
int prod_ver=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      ch_sum_rand=KpstRand(m_iInstCode4);

//    m_iLicID=m_iInstCode1^ch_sum_rand;
      retc=EmuTv.SetHp11Variable(m_iInstCode1^ch_sum_rand, KP11_LICID);
   }

#if FALSE
   if(SUCCEEDED(retc))
      if(m_iInstCode2^ch_sum_rand!=prod_ver)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
      if(m_iInstCode3^ch_sum_rand!=m_iCompId)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
      if(m_iInstCode4!=(m_iLicID+prod_ver+KpstRand(m_iCompId))%0x10000)
         retc=KP_E_ILL_CODE;
#endif

   if(SUCCEEDED(retc)) retc=CalcLicCode();
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_RECALC_LIC_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::RCLC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ParseLicCodeHigh(const unsigned char *lpszLicCodeHigh)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszLicCodeHigh != null, E_INVALIDARG, null, True);
// KP_ASSERT(strlen(lpszLicCodeHigh) == KPST_NUM_OF_LIC_CHARS, E_INVALIDARG, lpszLicCodeHigh, True);
   if(SUCCEEDED(retc)) if(strlen(lpszLicCodeHigh) != KPST_NUM_OF_LIC_CHARS) KP_WARNING(E_INVALIDARG, lpszLicCodeHigh);
   if(SUCCEEDED(retc)) PutLogMessage_("PLCH(%s)", lpszLicCodeHigh);

unsigned char code_buf[KPST_NUM_OF_LIC_CHARS + 1];
int lic_high = 0;
   if(SUCCEEDED(retc))
   {
      strcpy(code_buf, lpszLicCodeHigh);
      retc = ExtractHigh(code_buf, &lic_high, 12);
   }
// if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_high, KP11_LIC_HIGH);
   if(SUCCEEDED(retc)) retc = SaveLicHighHp11(lic_high);

int lic_code1 = 0;
int lic_code2 = 0;
int lic_code3 = 0;
   if(SUCCEEDED(retc))
   {
      retc = ScanKeyHex(code_buf + (KPST_NUM_OF_KEY_SEGM_CHARS + 1) * 2, &lic_code3 /* &m_iLicCode3 */);
      code_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 2 + 1] = Nul;
   }
   if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_code3, KP11_LIC_CODE3);

   if(SUCCEEDED(retc))
   {
      retc = ScanKeyHex(code_buf + KPST_NUM_OF_KEY_SEGM_CHARS + 1, &lic_code2 /* &m_iLicCode2 */);
      code_buf[KPST_NUM_OF_KEY_SEGM_CHARS] = Nul;
   }
   if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_code2, KP11_LIC_CODE2);

   if(SUCCEEDED(retc)) retc = ScanKeyHex(code_buf, &lic_code1 /* &m_iLicCode1 */);
   if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(lic_code1, KP11_LIC_CODE1);


   if(SUCCEEDED(retc))
   {
// KpMsgOutF_5("%d %lx %d %d %d", cMemBank[KP11_BLOCK_PROCESSING/2], retc, prod_ver, m_Ini.m_iProdVer, cMemBank[KP11_PRODVER/2]);
      retc = UnpackLic();
// KpMsgOutF_5("%d %lx %d %d %d", cMemBank[KP11_BLOCK_PROCESSING/2], retc, prod_ver, m_Ini.m_iProdVer, cMemBank[KP11_PRODVER/2]);
#if FALSE
// KpMsgOutF_4("%04x-%04x-%04x %d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2], cMemBank[KP11_LICID/2]);
// KpMsgOutF_5("%d %lx %d %d %d", cMemBank[KP11_BLOCK_PROCESSING/2], retc, prod_ver, m_Ini.m_iProdVer, cMemBank[KP11_PRODVER/2]);
      if(FAILED(retc)) if(prod_ver == 6010) // apjungiam MaTau5e v1.11 su v1.10
      {
         retc = SetIniProdVer(2010);
         if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));
         if(SUCCEEDED(retc)) retc = SendIniToHp11(&m_Ini);
         if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));

         if(SUCCEEDED(retc)) retc = UnpackLic();
      }
#endif
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::FormatInstCodeFull(unsigned char *lpszCode)
{
HRESULT retc = S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int inst_code1 = 0;
int inst_code2 = 0;
int inst_code3 = 0;
int inst_code4 = 0;

   if((lpszCode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code1, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code2, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code3, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code4, KP11_INST_CODE4);

   if(SUCCEEDED(retc)) retc=FormatKeyHex(code_buf, inst_code1 /* m_iInstCode1 */);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszCode, code_buf);
//    strcat(lpszCode, " - ");
      strcat(lpszCode, "-");
      retc=FormatKeyHex(code_buf, inst_code2 /* m_iInstCode2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszCode, code_buf);
//    strcat(lpszCode, " - ");
      strcat(lpszCode, "-");
      retc=FormatKeyHex(code_buf, inst_code3 /* m_iInstCode3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszCode, code_buf);
//    strcat(lpszCode, " - ");
      strcat(lpszCode, "-");
      retc=FormatKeyHex(code_buf, inst_code4 /* m_iInstCode4 */);
   }
   if(SUCCEEDED(retc))
      strcat(lpszCode, code_buf);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ScanInstCodeFull(const unsigned char *lpszCode)
{
HRESULT retc=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int inst_code1=0;
int inst_code2=0;
int inst_code3=0;
int inst_code4=0;

   if((lpszCode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszCode) != KPST_NUM_OF_KEY_CHARS /* 4 + 1 + 4 + 1 + 4 + 1 + 4 */)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
   {
      strcpy(code_buf, lpszCode);
      if((code_buf[4]!='-') || (code_buf[9]!='-') || (code_buf[14]!='-'))
         retc=KP_E_ILL_CODE;
   }

   if(SUCCEEDED(retc)){ code_buf[4]=Nul; code_buf[9]=Nul; code_buf[14]=Nul; }

   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf, &inst_code1 /* &m_iInstCode1 */); // outputs error messages !!!
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+5, &inst_code2 /* &m_iInstCode2 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+10, &inst_code3 /* &m_iInstCode3 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+15, &inst_code4 /* &m_iInstCode4 */);

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code1, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code2, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code3, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code4, KP11_INST_CODE4);

return(retc);
}


// ------------------------------
HRESULT KpStApp::CalcInstCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_rand;
int comp_id=0;
int prod_ver=0;
int lic_id=0;
int inst_code1=0;
int inst_code2=0;
int inst_code3=0;
int inst_code4=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

   if(SUCCEEDED(retc))
   {
      inst_code4 /* m_iInstCode4 */ = (lic_id /* m_iLicID */ +prod_ver+KpstRand(comp_id /* m_iCompId */))%0x10000;
      ch_sum_rand = KpstRand(inst_code4 /* m_iInstCode4 */);

      inst_code1 /* m_iInstCode1 */ = lic_id /* m_iLicID */ ^ ch_sum_rand;
      inst_code2 /* m_iInstCode2 */ = prod_ver^ch_sum_rand;
      inst_code3 /* m_iInstCode3 */ = comp_id /* m_iCompId */ ^ ch_sum_rand;

#if FALSE // #ifdef Debug
char str_buf[1000];
sprintf(str_buf, "lic: %d prodver: %d compid: %d sum: %d summod: %d randsum: %d %x",
                  m_iLicID, prod_ver, m_iCompId,
                  m_iLicID+prod_ver+m_iCompId,
                  inst_code4 /* m_iInstCode4 */, ch_sum_rand, ch_sum_rand);
KpMsgOut(str_buf, KP_MB_TESTI);
#endif

   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code1, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code2, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code3, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_code4, KP11_INST_CODE4);
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_CALC_INST_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::CIC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::UnpackInstCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_rand;
int inst_code1=0;
int inst_code2=0;
int inst_code3=0;
int inst_code4=0;
int rem_lic_id=0;
int rem_prod_ver=0;
int rem_ses_id=0;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code1, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code2, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code3, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code4, KP11_INST_CODE4);

   if(SUCCEEDED(retc))
   {
      ch_sum_rand=KpstRand(inst_code4 /* m_iInstCode4 */);

      rem_lic_id /* m_iRemLicID */ = inst_code1 /* m_iInstCode1 */ ^ ch_sum_rand;
      rem_prod_ver /* m_iRemProdVer */ = inst_code2 /* m_iInstCode2 */ ^ ch_sum_rand;
      rem_ses_id /* m_iRemSesID */ = inst_code3 /* m_iInstCode3 */ ^ ch_sum_rand;
   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_lic_id, KP11_REM_LICID);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_prod_ver, KP11_REM_PRODVER);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_ses_id, KP11_REM_SESID);

   if(SUCCEEDED(retc))
      if(ch_sum_rand!=KpstRand((rem_lic_id /* m_iRemLicID */ + rem_prod_ver /* m_iRemProdVer */ +
                        KpstRand(rem_ses_id /* m_iRemSesID */))%0x10000))
         retc=KP_E_ILL_CODE;
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_UNPACK_INST_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::UIC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc=KP_E_ILL_CODE;

return(retc);
}


// ------------------------------
HRESULT KpStApp::FormatInstKeyFull(unsigned char *lpszKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
int inst_key1=0;
int inst_key2=0;
int inst_key3=0;
int inst_key4=0;

   if((lpszKey==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_key1, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_key2, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_key3, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_key4, KP11_INST_KEY4);

   if(SUCCEEDED(retc))
      retc=FormatKeyHex(key_buf, inst_key1 /* m_iInstKey1 */);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszKey, key_buf);
//    strcat(lpszKey, " - ");
      strcat(lpszKey, "-");
      retc=FormatKeyHex(key_buf, inst_key2 /* m_iInstKey2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszKey, key_buf);
//    strcat(lpszKey, " - ");
      strcat(lpszKey, "-");
      retc=FormatKeyHex(key_buf, inst_key3 /* m_iInstKey3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszKey, key_buf);
//    strcat(lpszKey, " - ");
      strcat(lpszKey, "-");
      retc=FormatKeyHex(key_buf, inst_key4 /* m_iInstKey4 */);
   }
   if(SUCCEEDED(retc))
      strcat(lpszKey, key_buf);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ScanInstKeyFull(const unsigned char *lpszKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
int inst_key1=0;
int inst_key2=0;
int inst_key3=0;
int inst_key4=0;

   if((lpszKey==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszKey) != KPST_NUM_OF_KEY_CHARS /* 4 + 1 + 4 + 1 + 4 + 1 + 4 */)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
   {
      strcpy(key_buf, lpszKey);
      if((key_buf[4]!='-') || (key_buf[9]!='-') || (key_buf[14]!='-'))
         retc=KP_E_ILL_CODE;
   }

   if(SUCCEEDED(retc)){ key_buf[4]=Nul; key_buf[9]=Nul; key_buf[14]=Nul; }

   if(SUCCEEDED(retc)) retc=ScanKeyHex(key_buf, &inst_key1 /* &m_iInstKey1 */); // outputs error messages !!!
   if(SUCCEEDED(retc)) retc=ScanKeyHex(key_buf+5, &inst_key2 /* &m_iInstKey2 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(key_buf+10, &inst_key3 /* &m_iInstKey3 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(key_buf+15, &inst_key4 /* &m_iInstKey4 */);

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key1, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key2, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key3, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key4, KP11_INST_KEY4);

return(retc);
}


// ------------------------------
HRESULT KpStApp::CalcInstKey(void)
{
HRESULT retc=S_OK;

#if FALSE
int inst_code1=0;
int inst_code2=0;
int inst_code3=0;
int inst_code4=0;
int inst_key1=0;
int inst_key2=0;
int inst_key3=0;
int inst_key4=0;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code1, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code2, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code3, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&inst_code4, KP11_INST_CODE4);

   if(SUCCEEDED(retc))
   {
      inst_key1 /* m_iInstKey1 */ = KpstRand(inst_code1 /* m_iInstCode1 */);
      inst_key2 /* m_iInstKey2 */ = KpstRand(inst_code2 /* m_iInstCode2 */);
      inst_key3 /* m_iInstKey3 */ = KpstRand(inst_code3 /* m_iInstCode3 */);
      inst_key4 /* m_iInstKey4 */ = KpstRand(inst_code4 /* m_iInstCode4 */);
   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key1, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key2, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key3, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(inst_key4, KP11_INST_KEY4);
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_CALC_INST_KEY;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::CIK ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc = KP_E_REFUSED;

return(retc);
}


// ------------------------------
HRESULT KpStApp::FormatRemCodeFull(unsigned char *lpszRemCode)
{
HRESULT retc=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int rem_code1=0;
int rem_code2=0;
int rem_code3=0;
int rem_code4=0;

   if((lpszRemCode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code1, KP11_REM_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code2, KP11_REM_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code3, KP11_REM_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code4, KP11_REM_CODE4);

   if(SUCCEEDED(retc))
      retc=FormatKeyHex(code_buf, rem_code1 /* m_iRemCode1 */);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszRemCode, code_buf);
//    strcat(lpszRemCode, " - ");
      strcat(lpszRemCode, "-");
      retc=FormatKeyHex(code_buf, rem_code2 /* m_iRemCode2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszRemCode, code_buf);
//    strcat(lpszRemCode, " - ");
      strcat(lpszRemCode, "-");
      retc=FormatKeyHex(code_buf, rem_code3 /* m_iRemCode3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszRemCode, code_buf);
//    strcat(lpszRemCode, " - ");
      strcat(lpszRemCode, "-");
      retc=FormatKeyHex(code_buf, rem_code4 /* m_iRemCode4 */);
   }
   if(SUCCEEDED(retc))
      strcat(lpszRemCode, code_buf);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ScanRemCodeFull(const unsigned char *lpszRemCode)
{
HRESULT retc=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int rem_code1=0;
int rem_code2=0;
int rem_code3=0;
int rem_code4=0;

   if((lpszRemCode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszRemCode) != KPST_NUM_OF_KEY_CHARS /* 4 + 1 + 4 + 1 + 4 + 1 + 4 */)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
   {
      strcpy(code_buf, lpszRemCode);
      if((code_buf[4]!='-') || (code_buf[9]!='-') || (code_buf[14]!='-'))
         retc=KP_E_ILL_CODE;
   }

   if(SUCCEEDED(retc)){ code_buf[4]=Nul; code_buf[9]=Nul; code_buf[14]=Nul; }

   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf, &rem_code1 /* &m_iRemCode1 */); // outputs error messages !!!
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+5, &rem_code2 /* &m_iRemCode2 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+10, &rem_code3 /* &m_iRemCode3 */);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+15, &rem_code4 /* &m_iRemCode4 */);

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code1, KP11_REM_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code2, KP11_REM_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code3, KP11_REM_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code4, KP11_REM_CODE4);

return(retc);
}


// ------------------------------
HRESULT KpStApp::CalcRemoveCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_rand;
int comp_id=0;
int prod_ver=0;
int lic_id=0;
int rem_code1=0;
int rem_code2=0;
int rem_code3=0;
int rem_code4=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

   rem_code4 /* m_iRemCode4 */ = (lic_id /* m_iLicID */ +prod_ver*2+KpstRand(comp_id /* m_iCompId */))%0x10000;
   ch_sum_rand = KpstRand(rem_code4 /* m_iRemCode4 */);

   rem_code1 /* m_iRemCode1 */ = lic_id /* m_iLicID */ ^ ch_sum_rand;
   rem_code2 /* m_iRemCode2 */ = prod_ver^ch_sum_rand;
   rem_code3 /* m_iRemCode3 */ = comp_id /* m_iCompId */ ^ ch_sum_rand;

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code1, KP11_REM_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code2, KP11_REM_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code3, KP11_REM_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_code4, KP11_REM_CODE4);
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_CALC_REM_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::URC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::UnpackRemCode(void)
{
HRESULT retc=S_OK;

#if FALSE
int ch_sum_rand;
int rem_lic_id=0;
int rem_prod_ver=0;
int rem_ses_id=0;
int rem_code1=0;
int rem_code2=0;
int rem_code3=0;
int rem_code4=0;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code1, KP11_REM_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code2, KP11_REM_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code3, KP11_REM_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&rem_code4, KP11_REM_CODE4);

   if(SUCCEEDED(retc))
   {
      ch_sum_rand=KpstRand(rem_code4 /* m_iRemCode4 */);

      rem_lic_id /* m_iRemLicID */ = rem_code1 /* m_iRemCode1 */ ^ ch_sum_rand;
      rem_prod_ver /* m_iRemProdVer */ = rem_code2 /* m_iRemCode2 */ ^ ch_sum_rand;
      rem_ses_id /* m_iRemSesID */ = rem_code3 /* m_iRemCode3 */ ^ ch_sum_rand;
   }

   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_lic_id, KP11_REM_LICID);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_prod_ver, KP11_REM_PRODVER);
   if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(rem_ses_id, KP11_REM_SESID);

   if(SUCCEEDED(retc))
      if(ch_sum_rand!=KpstRand((rem_lic_id /* m_iRemLicID */ + (rem_prod_ver /* m_iRemProdVer */)*2+
                        KpstRand(rem_ses_id /* m_iRemSesID */))%0x10000))
         retc=KP_E_ILL_CODE;
#endif

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_UNPACK_REM_CODE;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::URC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::ExtractHigh(unsigned char *lpszCodeBuf, int *piHighCode, int iNumBytes)
{
HRESULT retc = S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;
int value = 0;
int digit = 0;
int len = 0;

   KP_ASSERT(lpszCodeBuf, E_INVALIDARG, null, True);
// KP_ASSERT(piHighCode, E_INVALIDARG, null, True);

// iðmetam minusus
   if(SUCCEEDED(retc))
   {
      pnts = pntd = lpszCodeBuf;

      while(*pnts)
      {
         if(*pnts == '-') pnts++;
         else *pntd++ = *pnts++;
      }
      *pntd = Nul;
   }

// skaitmenø skaièius
   if(SUCCEEDED(retc))
   {
      len = strlen(lpszCodeBuf);
      if(len > iNumBytes /* KPST_NUM_OF_HIGH_CODE_BITS */) len = iNumBytes /* KPST_NUM_OF_HIGH_CODE_BITS */;
   }

// skanuojam
   if(SUCCEEDED(retc))
   {
      pntd = lpszCodeBuf;
      for(int ii = 0; ii < len; ii++)
      {
         value <<= 1;

         if(*pntd != Spc)
         {
            digit = DecKpHexDig(*pntd);
            if(digit & 0x10) value |= 1;
            digit &= 0xF;
            *pntd = EncKpHexDig(digit);
         }

         pntd++;
      }
   }

// sukiðam minusus atgal
   if(SUCCEEDED(retc))
   {
      pnts = pntd = lpszCodeBuf + strlen(lpszCodeBuf);
      pntd += (pnts - lpszCodeBuf - 1) / 4;

      *pntd = Nul;

      while((pnts > lpszCodeBuf) && SUCCEEDED(retc))
      {
         KP_ASSERT(pntd > lpszCodeBuf, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
         {
            *(--pntd) = *(--pnts);
            if(((pnts - lpszCodeBuf) % 4 == 0) && (pntd > lpszCodeBuf)) *(--pntd) = '-';
         }
      }
   }

// gràþinam nuèiulptà reikðmæ
   if((piHighCode != NULL) /* && SUCCEEDED(retc) */) *piHighCode = value;

return(retc);
}


HRESULT KpStApp::AddHigh(unsigned char *lpszCodeBuf, int iHighCode, int iNumBytes)
{
HRESULT retc = S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;
int value = iHighCode;
int mask = 1 << (iNumBytes - 1);
int digit = 0;
int len = 0;

   KP_ASSERT(lpszCodeBuf, E_INVALIDARG, null, True);

// iðmetam minusus
   if(SUCCEEDED(retc))
   {
      pnts = pntd = lpszCodeBuf;

      while(*pnts)
      {
         if(*pnts == '-') pnts++;
         else *pntd++ = *pnts++;
      }
      *pntd = Nul;
   }
// skaitmenø skaièius
   if(SUCCEEDED(retc))
   {
      len = strlen(lpszCodeBuf);
      if(len > iNumBytes /* KPST_NUM_OF_HIGH_CODE_BITS */) len = iNumBytes /* KPST_NUM_OF_HIGH_CODE_BITS */;
   }

// uþmetinëjam bitus
   if(SUCCEEDED(retc))
   {
      pntd = lpszCodeBuf;
      for(int ii = 0; ii < len; ii++)
      {
         digit = DecKpHexDig(*pntd);
         if(value & mask) digit |= 0x10;
         *pntd = EncKpHexDig(digit);

         mask >>= 1;
         pntd++;
      }
   }

// sukiðam minusus atgal
   if(SUCCEEDED(retc))
   {
      pnts = pntd = lpszCodeBuf + strlen(lpszCodeBuf);
      pntd += (pnts - lpszCodeBuf - 1) / 4;

      *pntd = Nul;

      while((pnts > lpszCodeBuf) && SUCCEEDED(retc))
      {
         KP_ASSERT(pntd > lpszCodeBuf, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
         {
            *(--pntd) = *(--pnts);
            if(((pnts - lpszCodeBuf) % 4 == 0) && (pntd > lpszCodeBuf)) *(--pntd) = '-';
         }
      }
   }

return(retc);
}


// ------------------------------
HRESULT CheckResRequest_RC(void *pKpStAppObjPtr)
{
HRESULT retc=S_OK;
int prod_ver=0;
int num_of_lics=0;
int ii;
KpStApp *this_ptr=(KpStApp *)pKpStAppObjPtr;

   cMemBank[KP11_BLOCK_PROCESSING/2]=True;

   if((pKpStAppObjPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(this_ptr->m_pLicListSocket==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) if(this_ptr->m_pLicArray==NULL)
   {
//    retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      retc = KP_E_SYSTEM_ERROR;
//    retc = KP_E_REFUSED;
   }

   if(SUCCEEDED(retc)) retc=this_ptr->GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
      if((cMemBank[KP11_REM_LICID/2] /* this_ptr->m_iRemLicID */ != this_ptr->m_iKpstRand0) ||
         (cMemBank[KP11_REM_PRODVER/2] /* this_ptr->m_iRemProdVer */ != prod_ver))
            retc=KP_E_ACCESS_DENIED;

   if(SUCCEEDED(retc))
   {
      retc = KP_E_REFUSED;

// gal licencijos atnaujinimas?
      for(ii = 0; ii < num_of_lics; ii++)
         if(
            (this_ptr->m_pLicArray[ii].m_iLicState!=KpstLicFree) &&
//          (strcmp(this_ptr->m_pLicArray[ii].m_lpszHost, this_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName)==0) &&
            (this_ptr->m_pLicArray[ii].m_Host.S_un.S_addr==this_ptr->m_pLicListSocket->m_PackedUrl.m_Addr.S_un.S_addr) &&
            (this_ptr->m_pLicArray[ii].m_iSessionID == cMemBank[KP11_REM_SESID/2] /* this_ptr->m_iRemSesID */)
           )
         {
            this_ptr->m_pLicArray[ii].m_iLicState=KpstLicBusy;
            this_ptr->m_pLicArray[ii].m_iSecondsToKill=KPST_INI_SECS_TO_KILL;
            retc=S_OK;
            break;
         }

// ne - kuriam nauja
      if(retc == KP_E_REFUSED) for(ii = 0; ii < num_of_lics; ii++)
         if(this_ptr->m_pLicArray[ii].m_iLicState==KpstLicFree)
         {
            this_ptr->m_pLicArray[ii].m_iLicState=KpstLicBusy;
//          (strcpy(this_ptr->m_pLicArray[ii].m_lpszHost, this_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName);
            this_ptr->m_pLicArray[ii].m_Host.S_un.S_addr=this_ptr->m_pLicListSocket->m_PackedUrl.m_Addr.S_un.S_addr;
            this_ptr->m_pLicArray[ii].m_iSessionID = cMemBank[KP11_REM_SESID/2] /* this_ptr->m_iRemSesID */;
            this_ptr->m_pLicArray[ii].m_iSecondsToKill=KPST_INI_SECS_TO_KILL;
            retc=S_OK;
            break;
         }
   }

   if(SUCCEEDED(retc)) cMemBank[KP11_BLOCK_PROCESSING/2]=False;

return(retc);
}


// ------------------------------
HRESULT CheckRelRequest_RC(void *pKpStAppObjPtr)
{
HRESULT retc=S_OK;
int prod_ver=0;
int num_of_lics=0;
int ii;
KpStApp *this_ptr=(KpStApp *)pKpStAppObjPtr;

   if((pKpStAppObjPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(this_ptr->m_pLicListSocket==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) if(this_ptr->m_pLicArray==NULL)
   {
//    retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      retc = KP_E_SYSTEM_ERROR;
//    retc = KP_E_REFUSED;
   }

   if(SUCCEEDED(retc)) retc=this_ptr->GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
      if((cMemBank[KP11_REM_LICID/2] /* this_ptr->m_iRemLicID */ != this_ptr->m_iKpstRand0) ||
         (cMemBank[KP11_REM_PRODVER/2] /* this_ptr->m_iRemProdVer */ != prod_ver))
            retc=KP_E_ACCESS_DENIED;

   if(SUCCEEDED(retc))
   {
      retc = KP_E_REFUSED;
      for(ii = 0; ii < num_of_lics; ii++) // if(this_ptr->m_pLicArray[ii].m_iLicState!=KpstLicFree)
         if(
//          (strcmp(this_ptr->m_pLicArray[ii].m_lpszHost, this_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName)==0) &&
            (this_ptr->m_pLicArray[ii].m_Host.S_un.S_addr==this_ptr->m_pLicListSocket->m_PackedUrl.m_Addr.S_un.S_addr) &&
            (this_ptr->m_pLicArray[ii].m_iSessionID == cMemBank[KP11_REM_SESID/2] /* this_ptr->m_iRemSesID */)
           )
         {
            this_ptr->m_pLicArray[ii].m_iLicState=KpstLicFree;
            this_ptr->m_pLicArray[ii].m_iSecondsToKill=0;
            retc=S_OK;
//          break;
         }
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::TestKey(void)
{
HRESULT retc=S_OK;
int lic_id = 0;
int ini_lic_id = 0;

   if(SUCCEEDED(retc)) retc = GetIniIniLicID(&ini_lic_id);
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

#if FALSE
#if FALSE
int comp_id_1;
int prod_ver=0;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   comp_id_1 = KpstRand(m_iCompId);
   if((m_iInstKey1!=KpstRand(comp_id_1)) ||
      (m_iInstKey2!=KpstRand((prod_ver^comp_id_1)&0xFFFF))
/* || (m_iInstKey3!=KpstRand((m_iLicID^comp_id_1)&0xFFFF)) */ )
      retc=KP_E_ILL_CODE;
#endif
      if((m_iInstKey1!=KpstRand(m_iInstCode1)) ||
         (m_iInstKey2!=KpstRand(m_iInstCode2)) ||
         (m_iInstKey3!=KpstRand(m_iInstCode3)) ||
         (m_iInstKey4!=KpstRand(m_iInstCode4))
            retc=KP_E_ILL_CODE;
#endif

#if FALSE
static KpRcPars rc_pars;
static int check_buf[8];

// check_buf[0]=m_iInstCode1;
// check_buf[1]=m_iInstCode2;
// check_buf[2]=m_iInstCode3;
// check_buf[3]=m_iInstCode4;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf, KP11_INST_CODE1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+1, KP11_INST_CODE2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+2, KP11_INST_CODE3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+3, KP11_INST_CODE4);

// check_buf[4]=m_iInstKey1;
// check_buf[5]=m_iInstKey2;
// check_buf[6]=m_iInstKey3;
// check_buf[7]=m_iInstKey4;

   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+4, KP11_INST_KEY1);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+5, KP11_INST_KEY2);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+6, KP11_INST_KEY3);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(check_buf+7, KP11_INST_KEY4);

   rc_pars.iOpCode = KP_RC_KEY_CHECK;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.enc.iDataLen = sizeof(check_buf);
   rc_pars.enc.pData = check_buf;
   rc_pars.value = False;

// PutLogMessage_("KpStApp::TK ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());
#ifdef Debug_RYt_putw
PutLogMessage_("TK() .... %x %x", &rc_pars, check_buf);
#endif

   retc=EmuTv.ExecRemoteCall(&rc_pars);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc=KP_E_ILL_CODE;
#endif

static KpRcPars rc_pars;

   if(m_iKpStMode == KpStarterMode) // KpStRegMode)
   {
      rc_pars.iOpCode = KP_RC_KEY_CHECK_INTERN_AND_CALLBACK;
      rc_pars.enc.iCallBackIx = KP_RC_CBIX_RegSert;
   }
   else rc_pars.iOpCode = KP_RC_KEY_CHECK_INTERN;

   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::TK1 ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
   {
      retc = KP_E_ILL_CODE;

      if((ini_lic_id != KpstRand(0)) && (lic_id != KpstRand(0)) && (lic_id != ini_lic_id)) retc = KP_E_REFUSED;
   }

return(retc);
}


HRESULT KpStApp::UnRegSert(void)
{
HRESULT retc = S_OK;

static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_CALLBACK;
   rc_pars.enc.iCallBackIx = KP_RC_CBIX_UnRegSert;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::URS ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc)) retc = KP_E_SYSTEM_ERROR;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetRegUrl(unsigned char *lpszServerBuf, unsigned char *lpszUrlBuf, const unsigned char *lpszHttpQuery)
{
HRESULT retc = S_OK;
int prod_ver = 0;
int num_of_lics = 0;
int port = 0;
unsigned char reg_url[KP_MAX_FNAME_LEN + 1];
int lic_high = 0;

// ----------------------
   KP_ASSERT(lpszHttpQuery != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics < 0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = GetIniRegURL(reg_url);

// ----------------------
   if(SUCCEEDED(retc))
   {
      port = prod_ver;
      if(port < KP_MIN_USER_PORT) port += KP_MIN_USER_PORT;
   }

   if((num_of_lics != 0) && (m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
   {
int len = strlen(reg_url);
      KP_ASSERT(len + MAX_LONG_DIGITS + 2 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      sprintf((char *)reg_url + len, ":%d/", port);
   }

   if((lpszServerBuf != null) && SUCCEEDED(retc)) strcpy(lpszServerBuf, reg_url);

// ----------------------
   if((lpszUrlBuf != null) && SUCCEEDED(retc))
   {
      KP_ASSERT(strlen(reg_url) + strlen(lpszHttpQuery) + KPST_NUM_OF_KEY_CHARS < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

unsigned char *code_buf_ptr = null;
      if(SUCCEEDED(retc))
      {
         strcat(reg_url, lpszHttpQuery);
         code_buf_ptr = reg_url + strlen(reg_url);

         if(strcmp(lpszHttpQuery, KPST_HTTP_REGISTER) == 0) retc = FormatInstCodeFull(code_buf_ptr);
         else if(strcmp(lpszHttpQuery, KPST_HTTP_REMOVE) == 0) retc = FormatRemCodeFull(code_buf_ptr);
         else KP_ERROR(E_INVALIDARG, null);
      }

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetLicHighHp11(&lic_high);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->AddHigh(code_buf_ptr, lic_high, 12);

      if(SUCCEEDED(retc)) strcpy(lpszUrlBuf, reg_url);

   } // if((lpszUrlBuf != null) && SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SendCodeHttp(HRESULT hRetc, const unsigned char *lpszHttpQuery, bool bRecKey, bool bForcedTestRestDaysMsg)
{
HRESULT retc = S_OK;
KpSocket *sock_ptr = NULL;
unsigned char *rcv_buf = NULL;
long read;
/* const */ unsigned char *pnts;
unsigned char *pntd;
unsigned char url_buf[2*KP_MAX_FNAME_LEN+1];
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *out_buf = null;
unsigned char reg_url[KP_MAX_FNAME_LEN+1];
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int key_add = 0;
int lic_high = 0;

   KP_ASSERT(lpszHttpQuery != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   if(SUCCEEDED(retc)) retc = GetRegUrl(reg_url, null, lpszHttpQuery);

   KP_NEWA(rcv_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 100);
   KP_NEWA(out_buf, unsigned char, KP_MAX_FILE_LIN_LEN + KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1);
   KP_NEWO(sock_ptr, KpSocket);

   if(SUCCEEDED(retc)) retc=sock_ptr->Resolve(reg_url, False);
// PutLogMessage((const unsigned char *)"SendCodeHttp()", null);
   if(SUCCEEDED(retc)) retc=sock_ptr->Connect(False);

// KpMsgOut(reg_url, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   if(SUCCEEDED(retc))
   {
      strcpy(url_buf, sock_ptr->m_PackedUrl.m_lpszFileName);
      strcat(url_buf, lpszHttpQuery);
      if(strcmp(lpszHttpQuery, KPST_HTTP_REGISTER)==0) /* retc = */ FormatInstCodeFull(code_buf);
      else if(strcmp(lpszHttpQuery, KPST_HTTP_REMOVE)==0) /* retc = */ FormatRemCodeFull(code_buf);
      else
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   }
// if(SUCCEEDED(retc)) retc=RemoveSpaces(code_buf);

// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);

   if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high);

   if(SUCCEEDED(retc)) /* retc = */ AddHigh(code_buf, lic_high, 12);

// KP_TRACE("SendHttpRequest");

   if(SUCCEEDED(retc))
   {
      strcat(url_buf, code_buf);
      retc=sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, url_buf, False); // "GET"
   }

// KpMsgOutF(url_buf);

// KP_TRACE("RcvHttpTxtMsg");

   if(SUCCEEDED(retc))
   {
      read = KP_MAX_FILE_LIN_LEN;
      retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, False);

#if FALSE // #if TRUE // #ifdef Debug //
static char str_buf[1000];
// if(SUCCEEDED(retc))
{
sprintf(str_buf, "rcv_buf[%d] >>>", read);
strcat(str_buf, (const char *)rcv_buf);
strcat(str_buf, "<<<");
// KP_TRACE(str_buf);
KpMsgOutF(str_buf);
}
#endif
   }

   if(SUCCEEDED(retc))
   {
      rcv_buf[read]=Nul;
      pnts=strstr(rcv_buf, KPST_REG_OK_short);
      if(pnts != null)
      {
         if(bRecKey)
         {
            pnts += strlen(KPST_REG_OK_short);
            while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
            if(*pnts == ':') pnts++;
            while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
            pntd = (unsigned char *)pnts;
            while((*pntd != Nul) && (strchr(lpszEols, *pntd) == null)) pntd++;
            *pntd = Nul;
            if(SUCCEEDED(retc)) retc = ExtractHigh(pnts, &key_add, 16);

//          if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
//          if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high); // dar turim, o jau ir nebereikia
            if(SUCCEEDED(retc))
            {
//             retc = SaveRestDaysInitHp11AndInit(key_add); // èia negerai – HP11_LICID dar nenustatytas
               retc = SaveRestDaysInitHp11(key_add); // tik atsimenam á KP11_REST_DAYS_INIT, á failà áraðinësim ir inicializuosim po CheckReg() – kai jau bus nustatytas HP11_LICID
               if(FAILED(retc)) KP_ERROR(retc, null);
            }

         /* if(SUCCEEDED(retc)) */ retc = ScanInstKeyFull(pnts);
         }
      }
      else
      {
         pnts = strstr(rcv_buf, KPST_REG_EXPIRED_short); // KPST_REG_REFUSED_short);
         if(pnts != null)
         {
            pnts += strlen(KPST_REG_EXPIRED_short); // KPST_REG_REFUSED_short);
            while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
            if(*pnts == ':') pnts++;
            while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
            pntd = (unsigned char *)pnts;
            while((*pntd != Nul) && (strchr(lpszEols, *pntd) == null)) pntd++;
            *pntd = Nul;

            retc = KP_E_EXPIRED; // KP_E_REFUSED;

            if(hRetc != KP_E_EXPIRED) // KP_E_REFUSED)
            {
HRESULT retc0 = S_OK;
static KpChar str_buf_i[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char str_buf[KP_MAX_FILE_LIN_WDT + 1];

               if(SUCCEEDED(retc0)) /* retc0 = */ DecodeKpStrUnicode(str_buf_i, KP_MAX_FILE_LIN_WDT, pnts, UC_UTF_8);
               if(SUCCEEDED(retc0))
               {
                  str_buf_i[KP_MAX_FILE_LIN_WDT] = C_Nul;
               /* retc0 = */ KptStrDecode(str_buf, str_buf_i, TV_MAIN_CTBL);
               }
               if(SUCCEEDED(retc0))
               {
                  str_buf[KP_MAX_FILE_LIN_WDT] = Nul;

                  strcpy(out_buf, prod_name);
                  strcat(out_buf, "\n                         \n");
                  strcat(out_buf, str_buf);

                  if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
                  {
                  /* retc = */ SpcEolToSpc(out_buf);
                     KP_ERRORL(retc, out_buf);
                  }
                  else
                  {
                     if((!RestDaysWarningShowed()) || bForcedTestRestDaysMsg) KpMsgOut(out_buf, IDI_ERROR, KP_MB_TESTI);
//                   m_iRestDaysWarningShowed = True;
                     KP_WARNING0(retc, null);
                  }
               }

//             retc0 = EmuTv.SetHp11Variable(-1, KP11_REST_DAYS_INIT); if(SUCCEEDED(retc)) retc = retc0;
//             retc0 = EmuTv.SetHp11Variable(0 /* -KPST_MINS_PER_DAY */, KP11_REST_MINS); if(SUCCEEDED(retc)) retc = retc0;
//             retc0 = EmuTv.SetHp11Variable(0 /* -1 */, KP11_REST_MINS + 2); if(SUCCEEDED(retc)) retc = retc0;

               retc0 = ResetRestDaysHp11(); if(SUCCEEDED(retc)) retc = retc0;
            }
         }
         else
         {
            pnts = strstr(rcv_buf, KPST_REG_ERROR_short);
            if(pnts != null)
            {
               pnts += strlen(KPST_REG_ERROR_short);
               while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
               if(*pnts == ':') pnts++;
               while((*pnts != Nul) && (strchr(lpszSpaces, *pnts) != null)) pnts++;
               pntd = (unsigned char *)pnts;
               while((*pntd != Nul) && (strchr(lpszEols, *pntd) == null)) pntd++;
               *pntd = Nul;

               retc = KP_E_REFUSED; // KP_E_TRANS_ERR;

               if(hRetc != KP_E_REFUSED) // KP_E_TRANS_ERR)
               {
HRESULT retc0 = S_OK;
static KpChar str_buf_i[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char str_buf[KP_MAX_FILE_LIN_WDT + 1];

                  if(SUCCEEDED(retc0)) /* retc0 = */ DecodeKpStrUnicode(str_buf_i, KP_MAX_FILE_LIN_WDT, pnts, UC_UTF_8);
                  if(SUCCEEDED(retc0))
                  {
                     str_buf_i[KP_MAX_FILE_LIN_WDT] = C_Nul;
                  /* retc0 = */ KptStrDecode(str_buf, str_buf_i, TV_MAIN_CTBL);
                  }
                  if(SUCCEEDED(retc0))
                  {
                     str_buf[KP_MAX_FILE_LIN_WDT] = Nul;

                     strcpy(out_buf, prod_name);
                     strcat(out_buf, "\n                         \n");
                     strcat(out_buf, str_buf);

                     if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
                     {
                     /* retc = */ SpcEolToSpc(out_buf);
                        KP_ERRORL(retc, out_buf);
                     }
                     else KpMsgOut(out_buf, IDI_ERROR, KP_MB_TESTI);
                  }
               }
            }
            else KP_ERROR(KP_E_TRANS_ERR, null);
         }
      }
   }

   KP_DELETE(sock_ptr);
   KP_DELETEA(out_buf);
   KP_DELETEA(rcv_buf);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CheckReg(HINSTANCE hInst, bool *pbLicEntered, bool bTestRestDays, bool bRunTime)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
bool skip_fl = False;
bool bound = False;
bool ch_fl = False;
bool lic_fl = False;
bool ci_direct = False;
int num_of_lics = 0;
int lic_id = 0;
int prod_ver = 0;
int prod_ver_saved = 0;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
bool obj_fl = False;
int lic_high = 0;
bool terms_downloaded = False; // ar pavyko aktyvacijos kreipinys á prodreg serverá? Jei taip – iðsaugojam terminuotø licencijø parametrus, ignoruodami lokaliai susikaupusius

   if(pbLicEntered) *pbLicEntered = False;

   if(SUCCEEDED(retc)) retc = GetIniCiDirect(&ci_direct);
   if(SUCCEEDED(retc)) retc = GetIniBound(&bound);
   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&ch_fl);
   if(SUCCEEDED(retc)) retc = GetIniLicFlash(&lic_fl);

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR)) obj_fl = True;

// int rest_days_init_sav;
// EmuTv.GetHp11Variable(&rest_days_init_sav, KP11_REST_DAYS_INIT);

#if TRUE // FALSE
// int lic_high
int rest_days_init;
long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 1: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

   if(SUCCEEDED(retc))
   {
//    if(bound) // net ir nepririðtiems reikia (pvz., StartGrp) – kad nusiimtø KP11_BLOCK_PROCESSING
      if ((!ch_fl) || lic_fl) // grynai atmintukiniams negalima – KP11_BLOCK_PROCESSING turi nustatyti TestFlash()
      {

// ­itÓ vietÓ lau_ia smilas ipai_20060210.exe

//    if(bound && SUCCEEDED(retc))
//    {

// :00415E18 807DF800                cmp byte[ebp-08], 00
// :00415E1C 7406                    je 00415E24               // Íia keiÍia ß   // :00415E1C E903000000              jmp 00415E24
// :00415E1E 837DEC00                cmp dword[ebp-14], 000                      // :00415E21 00                                                .
// :00415E22 7D05                    jge 00415E29
// ---------
// :00415E24 E90C020000              jmp 00416035

// --------------------------
         retc = GetSavedKeyReg();
#ifdef Logging // #if FALSE //
PutLogMessage_("[ch s 9] li: %d pv: %d rli: %d rpv: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
PutLogMessage_("[ch s 10] lc: %x %x %x", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
PutLogMessage_("[ch s 11] ic: %x %x %x %x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
PutLogMessage_("[ch s 12] ik: %x %x %x %x", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
#endif

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 2: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

//       if(SUCCEEDED(retc)) retc=GetSavedKey();

// :00415E29 837DEC00                cmp dword[ebp-14], 000
// :00415E2D 7C0B                    jl 00415E3A
// :00415E2F 8B45E0                  mov eax, dword[ebp-20]
// :00415E32 E882E4FFFF              call 004142B9
// :00415E37 8945EC                  mov dword[ebp-14], eax


         if(SUCCEEDED(retc))
         {
            retc0 = GetCommonCompID();
            if(SUCCEEDED(retc)) retc = retc0;
         }
         else
         {
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "%d", retc-MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0));
KpMsgOut(str_buf, KP_MB_TESTI);
#endif

// --------------------------
            if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_ILL_CODE))
            {
#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 3: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

               retc = GetSavedKeyDat(NULL);

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 4: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

               if(SUCCEEDED(retc))
               {
                  retc0 = GetCommonCompID();
                  if(SUCCEEDED(retc)) retc = retc0;

                  if(SUCCEEDED(retc)) retc = ReCalcLicCode();
#ifdef Logging // #if FALSE //
// KpMsgOutF_4("CheckReg pries lic_id: %d prod_ver: %d rem_lic_id: %d rem_prod_ver: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
PutLogMessage_("[ch r 1] li: %d pv: %d rli: %d rpv: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
// KpMsgOutF_3("CheckReg pries lic_code: %d-%d-%d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
PutLogMessage_("[ch r 2] lc: %x %x %x", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
// KpMsgOutF_4("CheckReg pries inst_code: %d-%d-%d-%d", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
PutLogMessage_("[ch r 3] ic: %x %x %x %x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
// KpMsgOutF_4("CheckReg pries inst_key: %d-%d-%d-%d", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
PutLogMessage_("[ch r 4] ik: %x %x %x %x", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
#endif
                  if(SUCCEEDED(retc)) retc = UnpackInstCode(); // iðtraukiam KP11_REM_PRODVER vëlesniam palyginimui ir lic. ávedimo edit laukø uþpildymui per OpenLicWindow()
#ifdef Logging // #if FALSE //
// KpMsgOutF_4("CheckReg po lic_id: %d prod_ver: %d rem_lic_id: %d rem_prod_ver: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
PutLogMessage_("[ch p 5] li: %d pv: %d rli: %d rpv: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
// KpMsgOutF_3("CheckReg po lic_code: %d-%d-%d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
PutLogMessage_("[ch p 6] lc: %x %x %x", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
// KpMsgOutF_4("CheckReg po inst_code: %d-%d-%d-%d", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
PutLogMessage_("[ch p 7] ic: %x %x %x %x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
// KpMsgOutF_4("CheckReg po inst_key: %d-%d-%d-%d", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
PutLogMessage_("[ch p 8] ik: %x %x %x %x", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);
#endif
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_id, KP11_LICID);
                  if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&prod_ver_saved, KP11_REM_PRODVER); // nustatytas su UnpackInstCode()

               }
               else
               {
//                m_iCompId=0;
                  if(SUCCEEDED(retc0)) retc0 = EmuTv.SetHp11Variable(0, KP11_COMPID);

//                m_iLicID=KpstRand(0);
                  if(SUCCEEDED(retc0)) retc0 = InitLicId();

                  if(SUCCEEDED(retc0)) retc0 = CalcLicCode();
                  if(SUCCEEDED(retc0)) retc0 = CalcInstCode();

//                m_iInstKey1=1234; // 0;
//                m_iInstKey2=5678; // 0;
//                m_iInstKey3=9012; // 0;
//                m_iInstKey4=3456; // 0;

                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(1234, KP11_INST_KEY1);
                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(5678, KP11_INST_KEY2);
                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(9012, KP11_INST_KEY3);
                  if(SUCCEEDED(retc)) retc = EmuTv.SetHp11Variable(3456, KP11_INST_KEY4);

                  if(/* bAdminFl && */ SUCCEEDED(retc0))
                  {
                     if(obj_fl)
                     {
// TODO jei objektø þiûryklë – áraðyti data.dat failà á objektà
                     }
                     else /* retc0 = */ SaveKeyDat(); // data.dat raðom tik jei ne objektø þiûryklë
                  }

               /* if(SUCCEEDED(retc0)) retc0= */ GetCommonCompID();
               }
            }

         } // else // if(SUCCEEDED(retc))

#if FALSE // #ifdef Logging
PutLogMessage("%04x-%04x-%04x %d %d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2], cMemBank[KP11_LICID/2], cMemBank[KP11_PRODVER/2]);
// cMemBank[KP11_PRODVER/2] = 6010;
// KpMsgOutF_1("%d", cMemBank[KP11_BLOCK_PROCESSING/2]);
#endif

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 5: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

         if(SUCCEEDED(retc)) retc = CalcInstCode();

         if(SUCCEEDED(retc)) retc = TestKey();

// GetIniBound(&bound);
// KpMsgOutF("%04x-%04x-%04x-%04x %d %d %d %x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2], cMemBank[KP11_COMPID/2], cMemBank[KP11_PRODVER/2], bound, retc);

// KpMsgOutF("CHKR 0 %x %x %x %x", retc, KP_E_REFUSED, KP_E_EXPIRED, KP_E_TIMEOUT);

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 6: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

         if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_ILL_CODE) || (retc == KP_E_REFUSED) || (retc == KP_E_EXPIRED) ||
            (retc == KP_E_FILE_FORMAT)) // ðitaip gaunasi, kai failo nëra – EOF duoda tik po pirmos eilutës perskaitymo
         {

// cMemBank[KP11_PRODVER/2] = 2222;
// KpMsgOutF_3("%d %d %d", cMemBank[KP11_BLOCK_PROCESSING/2], m_Ini.m_iProdVer, cMemBank[KP11_PRODVER/2]);
// jeigu prod_ver == 6010, o lic. iðsaugota ið 2010 – ReCalcLicCode() nustato prod_ver = 2010 – gràþinam atgal
//          if(cMemBank[KP11_PRODVER/2] == 2010) cMemBank[KP11_PRODVER/2] = 6010;
            /* if(SUCCEEDED(retc)) retc = */ EnctIniData(sizeof(KpStIniData));
            /* if(SUCCEEDED(retc)) retc = */ SendIniToHp11(&m_Ini);
            /* if(SUCCEEDED(retc)) retc = */ EnctIniData(sizeof(KpStIniData));
// KpMsgOutF_3("%d %d %d", cMemBank[KP11_BLOCK_PROCESSING/2], m_Ini.m_iProdVer, cMemBank[KP11_PRODVER/2]);

            if(pbLicEntered) *pbLicEntered = True;

// KpMsgOutF_4("ci_direct: %d num_of_lics: %d m_iKpStMode: %d KpStarterMode: %d", ci_direct, num_of_lics, m_iKpStMode, KpStarterMode);

            if(
               (
// jei comp. id. ið failo - paprastam paleidëjui nesiregistruoti
                  (!ci_direct)
// jei paleidëjas - nesiregistruoti net ir kai comp. id. tiesioginis – TUX IPA paleidëjo registravimasis kaþko iðlûþta
// reikia prenumeruojamiems (StartGrp.exe nerodo registravimo klaidø); jeigu reikës TUX IPA – nenaudot ci_direct
//             || (m_iKpStMode == KpStarterMode)
               ) &&
               (
                  (
// jei tinklinë versija (num_of_lics > 0) - kiekvienà kartà paleidþiant tyliai registruotis prie lokalaus serverio
                     (num_of_lics == 0) &&
// TEV objektø þiûryklei reikia registruotis dinamiðkai
                     (!obj_fl)
                  ) ||
// jei ne paleidëjas (pvz., redaktorius) - nesiregistruoti net ir tinklinëje versijoje
                  (m_iKpStMode != KpStarterMode)
               )
              )
            {
// KpMsgOutF_0("neregistruojam");
               KpMsgOut((retc == KP_E_REFUSED)?KPST_MSG_INVALID_REG:KPST_MSG_NOT_REG, IDI_INFORMATION, KP_MB_BAIGTI);
               retc = KP_E_NOTINST;
// pas Þydrûnæ meta á ekranà
//             KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            }
            else
            {
// KpMsgOutF_0("registruojam");
               retc = S_OK;
               skip_fl = False;

               for(int ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)
               {
                  if((
                        (num_of_lics == 0)
//                   || (m_iKpStMode != KpStarterMode) // registruojam ir paleidëjuje (prenumeruojami)
                        ) && SUCCEEDED(retc))
                  {
// TEV objektø þiûryklei admino nereikalauti
// Jau niekam admino nereikalauti – jeigu admino nëra, registruojam tik lokaliam useriui. Admino reikia tik iðregistravimui
//                   if(SUCCEEDED(retc)) if(!obj_fl) retc = CheckPrivileges(KPST_MSG_REG_NOT_ADMIN);

#ifndef KpstregSilent
                     if(SUCCEEDED(retc))
                     {
// ------------------------------- tikrinam cmd line parametrus – jei yra, tada lic kodà imam ið ten
// KpMsgOutF("KpStApp::CheckReg() 1 %x %d %d", m_plCmdLineArgs, m_iKpStMode, KpStRegMode);
                        if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // parametru lic. kodà galima perduot tik registratoriaus programai
                        {
const unsigned char *par_ptr = (const unsigned char *)(m_plCmdLineArgs->GetValue());
                           KP_ASSERT(par_ptr != null, E_INVALIDARG, null, True);
// KpMsgOutF("KpStApp::CheckReg() 2 %s", par_ptr);
                           if(SUCCEEDED(retc))
                              if(strstr(par_ptr, "/SILENT") == null) // raktas /SILENT tik nugesina licencijos ávedimo dialogà, lic. kodas imamas ið data.dat kaip visada
                              {
// parsinam lic. kodà ið parametro
                                 KP_ASSERT(strlen(par_ptr) <= KPST_NUM_OF_LIC_CHARS, KP_E_BUFFER_OVERFLOW, null, True);
                                 if(SUCCEEDED(retc)) retc = ParseLicCodeHigh(par_ptr);
                              }
                        }
// --------------
                        else // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode))
                        {
// PutLogMessage_("CheckReg(): lic_id: %d  m_iKpstRand0: %d  prod_ver_saved: %d  prod_ver: %d  ii: %d", lic_id, m_iKpstRand0, prod_ver_saved, prod_ver, ii);
                           retc = EnterLicence(hInst, False, ((lic_id != m_iKpstRand0) && (prod_ver_saved == prod_ver)) || (ii > 0)); // True); // False); //
// KpMsgOutF_4("%04x-%04x-%04x %d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2], cMemBank[KP11_LICID/2]);
                           if(retc == KP_E_SKIP)
                           {
                              skip_fl = True;
                              retc = S_OK;
                           }
                           if(retc == KP_E_CANCEL) KpMsgOut((obj_fl?KPST_MSG_OBJ_REG_NOT_YET:KPST_MSG_REG_NOT_YET), IDI_WARNING, KP_MB_GERAI);
                        }
                     }
#endif

                     if(SUCCEEDED(retc)) retc = CalcInstCode();
// KpMsgOutF_4("%04x-%04x-%04x-%04x", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);

                  } // if(((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)) && SUCCEEDED(retc))

                  if(SUCCEEDED(retc))
                  {
                     if(!skip_fl)
                     {
// KpMsgOutF("CHKR 1 %x", retc);
                        if(SUCCEEDED(retc)) retc = SendCodeHttp(S_OK, KPST_HTTP_REGISTER, True);
// KpMsgOutF("CHKR 2 %x", retc);
// PutLogMessage_("CHKR 2 %x", retc);

                        if(SUCCEEDED(retc)) retc = TestKey();
                        if(SUCCEEDED(retc)) terms_downloaded = True;

                        if((retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
                        {
                           if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
                           {
                              KP_ERRORL(retc, null);
                              break;
                           }
                           else if(ii == 0)
                           {
                              retc = S_OK;

                              if((num_of_lics == 0) || (m_iKpStMode != KpStarterMode))
                                 PutMsgFirewall(KPST_MSG_CHECK_CONN);
                              else
                                 PutMsgFirewall(KPST_MSG_CHECK_CONN_LOC);
                           }

                        } // if(retc==KP_E_TRANS_ERR)
                        else
                           break; // viskas gerai arba klaida ne dël ryðio – einam lauk ið kartojimo

                     } // if(!skip_fl)

                  } // if(SUCCEEDED(retc))

               } // for(ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)

            /* if(SUCCEEDED(retc)) retc = */ EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH); // bibliotekiniø licencijø paðtu neregistruojam

               if(skip_fl || /* (retc == KP_E_REFUSED) || */ (retc == KP_E_ILL_CODE) || (retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
               {
                  if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
                  {
                     if(skip_fl && SUCCEEDED(retc)) retc = KP_E_CANCEL;
                     KP_ERRORL(retc, null);
                  }
                  else
                  {
                     if((
                           (num_of_lics == 0)
//                      || (m_iKpStMode != KpStarterMode) // registruojam ir paleidëjuje (prenumeruojami)
                        ) && (lic_high == 0))
                     {
                        retc = S_OK;
                        retc = EnterNewKey(hInst, skip_fl?(const unsigned char *)"":KPST_MSG_REG_UNSUC);
                        if(SUCCEEDED(retc)) terms_downloaded = True;
                        if(retc == KP_E_CANCEL) KpMsgOut((obj_fl?KPST_MSG_OBJ_REG_NOT_YET:KPST_MSG_REG_NOT_YET), IDI_WARNING, KP_MB_GERAI);
                     }
                     else
                        if((retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
                           KpMsgOut(KPST_MSG_REG_UNSUC_LOC, IDI_ERROR, KP_MB_BAIGTI);
                  }
               }

#if FALSE
               if(SUCCEEDED(retc))
                  if((num_of_lics==0) || (m_iKpStMode != KpStarterMode))
                     retc = SaveKeyReg();
#endif
            } // else // if((!ci_direct) && ((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)))

         } // if((retc == KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE) || (retc == KP_E_REFUSED))
         else
         {
            if(FAILED(retc)) retc = KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);

// kreipiamës á serverá dël terminuotø licencijø skaitikliø atnaujinimo
            if((bTestRestDays ||
               (m_iKpStMode == KpStRegMode) || (m_iKpStMode == KpStIpSvrMode)) // (m_iKpStMode != KpStarterMode))
               && SUCCEEDED(retc))
            {
// int rest_days_init_sav;
//             EmuTv.GetHp11Variable(&rest_days_init_sav, KP11_REST_DAYS_INIT);
#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 6.1: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

// KpMsgOutF("CHKR 3 %x", retc);
               if(SUCCEEDED(retc)) retc = SendCodeHttp(S_OK, KPST_HTTP_REGISTER, True, bRunTime);
// KpMsgOutF("CHKR 4 %x", retc);
// PutLogMessage_("CHKR 4 %x", retc);
               if(SUCCEEDED(retc)) retc = TestKey();

// int rest_days_init_new;
//             EmuTv.GetHp11Variable(&rest_days_init_new, KP11_REST_DAYS_INIT);

               if(/* (rest_days_init_new != rest_days_init_sav) && */ SUCCEEDED(retc)) terms_downloaded = True;

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 6.2: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif
               if((retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR)) retc = S_OK; // ignoruojam nepavykusá ryðá
            }
         }

//       if(ci_direct) retc0=SaveCompID(False); if(SUCCEEDED(retc)) retc=retc0;

      } // if(bound)
      else /* retc = */ TestKey(); // tik KP11_BLOCK_PROCESSING i­valymui, kai nepriri­tas nei prie kompo, nei prie atmintuko

// KpMsgOutF_1("CheckReg [2]: %x", retc);

   } // if(SUCCEEDED(retc))

   if(bound && ci_direct /* && bAdminFl */ /* && SUCCEEDED(retc) */) // data.dat iðsaugoti ir nesëkmës atveju – kad liktø lic. kodas aktyvacijai paleidimo metu
      if((num_of_lics==0) || (m_iKpStMode != KpStarterMode))
      {
         if(obj_fl)
         {
// TODO jei objektø þiûryklë – áraðyti data.dat failà á objektà
         }
         else
         {
            retc0 = SaveKeyDat(); // data.dat raðom tik jei ne objektø þiûryklë
            if((m_iKpStMode == KpStRegMode) && SUCCEEDED(retc))
            {
               retc = retc0; // registr.exe èia rimta klaida – neáraðius neveiks produktas
               if(FAILED(retc)) // if(FAILED(retc0))
               {
                  if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstreg.exe reþimas – praneðimø neiðvedinëjam
                     KP_ERRORL(retc, null)
                  else
                  {
                     KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                     if((!bAdminFl) || (retc == KP_E_ACCESS_DENIED)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
                     else KP_ERROR(retc, null);
                  }
               }
            }
         }
      }

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 7: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

// --------------------------
// raðom KP11_REST_DAYS_INIT á failà, kalkuliuojam m_lRestMinutes
PutLogMessage_("CHKR 5.0  bRunTime: %d  t_d: %d  retc: %x", bRunTime, terms_downloaded, retc);
   if(((!bRunTime) || terms_downloaded) && SUCCEEDED(retc))
      retc = (/* m_iKpStMode == KpStarterMode */ (!terms_downloaded))?ResumeRestDaysHp11():InitRestDaysHp11();
PutLogMessage_("CHKR 5.1  bRunTime: %d  t_d: %d  retc: %x", bRunTime, terms_downloaded, retc);

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("CHKRG() 8: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::RemoveReg(HRESULT hRetc, HINSTANCE hInst)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
// unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *out_buf = NULL;
bool skip_fl = False;
bool bound = False;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int num_of_lics = 0;
int lic_id = 0;
int prod_ver = 0;
int prod_ver_saved = 0;
int lic_high = 0;
bool silent = False;
const unsigned char *par_ptr = null;

   if(SUCCEEDED(retc)) retc = GetIniBound(&bound);
   if(SUCCEEDED(retc)) retc = GetIniProdNameDec(prod_name);
   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode))
   {
      par_ptr = (const unsigned char *)(m_plCmdLineArgs->GetValue());
      KP_ASSERT(par_ptr != null, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc)) silent = (strstr(par_ptr, "/SILENT") != null); // jei lentynos StartGrp.exe tylus iðregistravimas (raktas /SILENT) – admino netikrinam
   }

   if(bound && SUCCEEDED(retc))
   {
      KP_NEWA(out_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

      for(int ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)
      {
         if(SUCCEEDED(retc))
         {
            if((num_of_lics == 0) || (m_iKpStMode!=KpStarterMode))
            {
               if((!silent) && SUCCEEDED(retc)) retc = CheckPrivileges(KPST_MSG_UNREG_NOT_ADMIN);

               if(SUCCEEDED(retc))
               {
                  if(ii == 0)
                  {
                     retc = GetSavedKeyReg();
                     if(SUCCEEDED(retc))
                     {
                        retc0 = GetCommonCompID();
                        if(SUCCEEDED(retc)) retc = retc0;

                        if(SUCCEEDED(retc)) retc = CalcInstCode();
                     }
                     else if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_ILL_CODE))
                     {
                        retc = GetSavedKeyDat(NULL);

                        retc0 = GetCommonCompID();
                        if(SUCCEEDED(retc)) retc = retc0;

                        if(SUCCEEDED(retc)) retc = ReCalcLicCode();
                     }

// KpMsgOutF_4("RemoveReg pries lic_id: %d prod_ver: %d rem_lic_id: %d rem_prod_ver: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
// KpMsgOutF_3("RemoveReg pries lic_code: %d-%d-%d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
// KpMsgOutF_4("RemoveReg pries inst_code: %d-%d-%d-%d", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
// KpMsgOutF_4("RemoveReg pries inst_key: %d-%d-%d-%d", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);

                     if(SUCCEEDED(retc)) retc = UnpackInstCode(); // iðtraukiam KP11_REM_PRODVER vëlesniam palyginimui ir lic. ávedimo edit laukø uþpildymui per OpenLicWindow()

// KpMsgOutF_1("RemoveReg po retc: %d", retc);
// KpMsgOutF_4("RemoveReg po lic_id: %d prod_ver: %d rem_lic_id: %d rem_prod_ver: %d", cMemBank[KP11_LICID/2], m_Ini.m_iProdVer, cMemBank[KP11_REM_LICID/2], cMemBank[KP11_REM_PRODVER/2]);
// KpMsgOutF_3("RemoveReg po lic_code: %d-%d-%d", cMemBank[KP11_LIC_CODE1/2], cMemBank[KP11_LIC_CODE2/2], cMemBank[KP11_LIC_CODE3/2]);
// KpMsgOutF_4("RemoveReg po inst_code: %d-%d-%d-%d", cMemBank[KP11_INST_CODE1/2], cMemBank[KP11_INST_CODE2/2], cMemBank[KP11_INST_CODE3/2], cMemBank[KP11_INST_CODE4/2]);
// KpMsgOutF_4("RemoveReg po inst_key: %d-%d-%d-%d", cMemBank[KP11_INST_KEY1/2], cMemBank[KP11_INST_KEY2/2], cMemBank[KP11_INST_KEY3/2], cMemBank[KP11_INST_KEY4/2]);

                     if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);
                     if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&prod_ver_saved, KP11_REM_PRODVER); // nustatytas su UnpackInstCode()

                  } // if(ii == 0)

//                if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // parametru lic. kodà galima perduot tik registratoriaus programai
                  if(silent)
                  {
// const unsigned char *par_ptr = (const unsigned char *)(m_plCmdLineArgs->GetValue());
//                   KP_ASSERT(par_ptr != null, E_INVALIDARG, null, True);
// KpMsgOutF("KpStApp::CheckReg() 2 %s", par_ptr);
//                   if(SUCCEEDED(retc)) if(!silent) // if(strstr(par_ptr, "/SILENT") == null) // raktas /SILENT tik nugesina licencijos ávedimo dialogà, lic. kodas imamas ið data.dat kaip visada
//                   {
// parsinam lic. kodà ið parametro
//                      KP_ASSERT(strlen(par_ptr) <= KPST_NUM_OF_LIC_CHARS, KP_E_BUFFER_OVERFLOW, null, True);
//                      if(SUCCEEDED(retc)) retc = ParseLicCodeHigh(par_ptr);
//                   }
                  }
// --------------
                  else // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode))
                  {

                     if(SUCCEEDED(retc))
                     {
                        skip_fl = False;
                        retc = EnterLicence(hInst, True, ((lic_id != m_iKpstRand0) && (prod_ver_saved == prod_ver)) || (ii > 0)); // True);
                        if(retc == KP_E_SKIP)
                        {
                           skip_fl = True;
                           retc = S_OK;
                        }
                     }
                     else if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_ILL_CODE) ||
                        (retc == KP_E_FILE_FORMAT) || (retc == KP_E_EOF) || (retc == KP_E_FILE_NOT_FOUND))
                     {
                        retc = S_OK;
                        skip_fl = False;
                        retc = EnterLicence(hInst, True, ii > 0);
                        if(retc == KP_E_SKIP)
                        {
                           skip_fl = True;
                           retc = S_OK;
                        }
                     }
                     else KP_ERROR(retc, null);

                  } // else // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode))

               } // if(SUCCEEDED(retc)) // retc = CheckPrivileges(KPST_MSG_UNREG_NOT_ADMIN);

               retc0 = GetCommonCompID(); if(SUCCEEDED(retc)) retc = retc0;
            }
            else // if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
            {
//             m_iLicID = KpstRand(0);
               retc = InitLicId();

               if(SUCCEEDED(retc)) retc = CalcLicCode();
// dinaminis m_iCompId jau sugeneruotas registruojantis - geriau nekeisti
//             retc0=GetCommonCompID(); if(SUCCEEDED(retc)) retc=retc0;
            }

         } // if(SUCCEEDED(retc))

         if(SUCCEEDED(retc)) retc = CalcInstCode();
         if(SUCCEEDED(retc)) retc = CalcRemoveCode();

         if(SUCCEEDED(retc))
         {
            if(!skip_fl)
            {
               retc = SendCodeHttp(hRetc, KPST_HTTP_REMOVE, False);

               if((num_of_lics == 0) || (m_iKpStMode != KpStarterMode))
               {
                  if((retc == KP_E_REFUSED) || (retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR))
                  {
                     if(((retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR)) && (ii == 0))
                     {
                        if(silent) // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstun.exe reþimas – praneðimø neiðvedinëjam
                           KP_ERRORL(retc, null)
                        else
                        {
                           retc = S_OK;
                           PutMsgFirewall(KPST_MSG_CHECK_CONN);
                        }
                     }

                     if(FAILED(retc)) break; // jeigu klaida ne ryðio – nekartojam

                  } // if((retc==KP_E_REFUSED) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
                  else
                     break; // viskas gerai arba klaida ne dël ryðio – nekartojam

               } // if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
               else
                  break; // lokalaus serverio reþime nekartojam

            } // if(!skip_fl)

         } // if(SUCCEEDED(retc))

      } // for(int ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)

      if(((num_of_lics == 0) || (m_iKpStMode != KpStarterMode)))
      {
         if(SUCCEEDED(retc))
         {
            retc = DelSavedKey();
            if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;
         }

         if(retc != KP_E_CANCEL)
         {
         /* if(SUCCEEDED(retc)) retc */ retc0 = IncCompID(); if(SUCCEEDED(retc)) retc = retc0;

            retc0 = SaveCompID(False /* True */);
            if((!silent) && SUCCEEDED(retc)) // if(((m_plCmdLineArgs == NULL) || (m_iKpStMode != KpStRegMode)) && SUCCEEDED(retc)) // command line kpstun.exe reþimas – leidþiam bût neadminu
               retc = retc0; // reikia leist áraðyt iðmetimo kodà diegiamiems MIKams – jie ne adminai

PutLogMessage_("[RR 1] inced %d", cMemBank[KP11_COMPID/2]);
GetSavedCompID();
PutLogMessage_("[RR 2] saved %d", cMemBank[KP11_COMPID/2]);


            /* if(SUCCEEDED(retc)) retc = */ EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);

            if((skip_fl || (retc == KP_E_REFUSED) || (retc == KP_E_NO_CONN) || (retc == KP_E_TRANS_ERR)) && (lic_high == 0))
            {
               if(silent) // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstun.exe reþimas – praneðimø neiðvedinëjam
                  KP_ERRORL(retc, KPST_MSG_UNREG_UNSUCC)
               else
                  retc = RemCodeInfo(hInst, KPST_MSG_UNREG_UNSUCC);
            }
            else
            {
               strcpy(out_buf, prod_name);
               strcat(out_buf, "\n                                    \n");
               strcat(out_buf, SUCCEEDED(retc)?KPST_MSG_UNREG_SUCC:KPST_MSG_UNREG_UNSUCC);
               if(silent) // if((m_plCmdLineArgs != NULL) && (m_iKpStMode == KpStRegMode)) // command line kpstun.exe reþimas – praneðimø neiðvedinëjam
               {
               /* retc = */ SpcEolToSpc(out_buf);
                  KP_ERRORL(retc, out_buf);
               }
               else
                  retc = KpMsgOut(out_buf, SUCCEEDED(retc)?IDI_INFORMATION:IDI_ERROR, KP_MB_BAIGTI);
            }
         }
      }

   } // if(bound)

   KP_DELETEA(out_buf);

return(retc);
}


// ------------------------------
HRESULT ForceTextToHex(unsigned char *lpszFlashIdStr)
{
HRESULT retc=S_OK;
unsigned char *pntd = NULL;
unsigned char ch;

   if((lpszFlashIdStr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntd = lpszFlashIdStr;

      while(*pntd && SUCCEEDED(retc))
      {
         if(!TvIsHexDigit(*pntd))
         {
            if(*pntd == Spc) ch = '0'; // ' '
            else
            {
               ch = *pntd & 0xF;
               if(ch < 10) ch += '0';
               else ch = 'A' + ch - 10;
            }

            *pntd = ch;
         }

         pntd++;
      }
   }

return(retc);
}


// ==================================================================
HRESULT TestFlashID_RC(void *pTestFlashIdParsPtr)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
DWORD dwBufLen;
DWORD dwValType;
long dev_count = 0L;
static unsigned char dev_name[KP_MAX_FNAME_LEN+1];
bool found = False;
unsigned char dev_num_str[MAX_LONG_DIGITS+1];
int ii;
static unsigned char ser_no_txt[KP_MAX_FNAME_LEN + 1];
long vid;
long pid;
long dev_id;
static unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FNAME_LEN + 1];
TestFlashIdPars_1 *test_fl_pars_ptr = (TestFlashIdPars_1 *)pTestFlashIdParsPtr;
unsigned char drive_path[10];
ULARGE_INTEGER vol_size;
bool lic_flash = false;
// #ifdef Logging
// fstream out_file((char *)lpszLogFileName, ios::out | ios::ate);
// #endif

// KpMsgOutF_0("TestFlashID_RC():");

   cMemBank[KP11_BLOCK_PROCESSING/2] = True;

   if (theKpStAppPtr == NULL)
         retc = KpErrorProc.OutputErrorMessage(E_POINTER, null, False, __FILE__, __LINE__, 0L);
   if (SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniLicFlash(&lic_flash);
   if ((lic_flash == 0) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

   if((pTestFlashIdParsPtr == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((test_fl_pars_ptr->m_pThis == NULL) || (test_fl_pars_ptr->m_pbFound == NULL) || (test_fl_pars_ptr->m_piNumOfFlashes == NULL))
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      drive_path[0] = test_fl_pars_ptr->m_cDriveLetter;
      drive_path[1] = ':';
      drive_path[2] = Nul;

      vol_size.HighPart = vol_size.LowPart = 0L;
      if(!GetDiskFreeSpaceEx((char const *)drive_path, NULL, &vol_size, NULL))
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         vol_size.HighPart = vol_size.LowPart = 0L;
      }
   }

// --------------------------- atidarom registro raktà
   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum");
//    strcpy(key_name, "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum");
      key_name[0]='S';
      key_name[1]='Y';
      key_name[2]='S';
      key_name[3]='T';
      key_name[4]='E';
      key_name[5]='M';
      key_name[6]='\\';
      key_name[7]='C';
      key_name[8]='u';
      key_name[9]='r';
      key_name[10]='r';
      key_name[11]='e';
      key_name[12]='n';
      key_name[13]='t';
      key_name[14]='C';
      key_name[15]='o';
      key_name[16]='n';
      key_name[17]='t';
      key_name[18]='r';
      key_name[19]='o';
      key_name[20]='l';
      key_name[21]='S';
      key_name[22]='e';
      key_name[23]='t';
      key_name[24]='\\';
      key_name[25]='S';
      key_name[26]='e';
      key_name[27]='r';
      key_name[28]='v';
      key_name[29]='i';
      key_name[30]='c';
      key_name[31]='e';
      key_name[32]='s';
      key_name[33]='\\';
#ifndef KPST_FLASH_SERNO_DISK
      key_name[34]='U';
      key_name[35]='S';
      key_name[36]='B';
      key_name[37]='S';
      key_name[38]='T';
      key_name[39]='O';
      key_name[40]='R';
      key_name[41]='\\';
      key_name[42]='E';
      key_name[43]='n';
      key_name[44]='u';
      key_name[45]='m';
      key_name[46]=Nul;
#else
      key_name[34]='D';
      key_name[35]='i';
      key_name[36]='s';
      key_name[37]='k';
      key_name[38]='\\';
      key_name[39]='E';
      key_name[40]='n';
      key_name[41]='u';
      key_name[42]='m';
      key_name[43]=Nul;
#endif

      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "Count");
      key_name[0]='C';
      key_name[1]='o';
      key_name[2]='u';
      key_name[3]='n';
      key_name[4]='t';
      key_name[5]=Nul;

      dwBufLen=sizeof(dev_count);
      retw = RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)&dev_count, &dwBufLen);
      if((dwValType != REG_DWORD) || (retw != ERROR_SUCCESS))
      {
         dev_count = 0L;
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE_1("TestFlashID_RC(): Negaliu atidaryti %s", key_name);
      }
      else *test_fl_pars_ptr->m_piNumOfFlashes = dev_count;
   }

#if FALSE // #ifdef Logging
unsigned char str_buf[400];
PutLogDate(&out_file);
sprintf((char *)str_buf, " dev_count:%d", dev_count);
EncodeText(str_buf);
out_file << '\t' << str_buf << endl;
#endif

// KP_TRACE_("TestFlashID_RC() dev_count: %d", dev_count);

   for(ii=0; (ii < dev_count) && (!found) && SUCCEEDED(retc); ii++)
   {
      sprintf((char *)dev_num_str, "%d", ii);

      dwBufLen=KP_MAX_FNAME_LEN;
      retw=RegQueryValueEx(hKey, (const char *)dev_num_str, NULL, &dwValType, (LPBYTE)dev_name, &dwBufLen);
      if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
      {
         dev_name[0]=Nul;
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
      else dev_name[dwBufLen]=Nul;

// !!!!!! èia testuojam kliento atmintukà Plius78m/klaida_issitryne_8P1-51431-0485
// strcpy(dev_name, "USB\\Vid_18a5&Pid_0304\\00000000003718");

#ifdef Logging
static unsigned char dev_name_enc[KP_MAX_FNAME_LEN+1];
strcpy(dev_name_enc, dev_name);
EncodeText(dev_name_enc);
PutLogMessage_("TFIRC: %s", dev_name_enc);
#endif

// KP_TRACE_("TestFlashID_RC() dev_name: [%s]", dev_name);

#if FALSE // #ifdef Logging
// unsigned char str_buf[400];
PutLogDate(&out_file);
sprintf((char *)str_buf, " >>>> ii:%d dev_name:%s", ii, dev_name);
EncodeText(str_buf);
out_file << '\t' << str_buf << endl;
#endif
// KP_TRACE_1("TestFlashID_RC(): %d dev_name:", ii);
// KP_TRACE(dev_name);


      dev_id = vid = pid = 0L;
      ser_no_txt[0] = Nul;

// ---------------- ser.no.
      if(SUCCEEDED(retc)) retc = GetFlashSerNo(dev_name, &dev_id, ser_no_txt, &vid, &pid,
#ifdef KPST_FLASH_SERNO_DISK
         True
#else
         False
#endif
      );

// KP_TRACE_("TestFlashID_RC() ser_no_txt: [%s]", ser_no_txt);

      if(FAILED(retc))
      {
         dev_id = 0L;
         vid = 0L;
         pid = 0L;
         ser_no_txt[0] = Nul;
         retc = S_OK;
      }

// ------------------ vid/pid, jei KPST_FLASH_SERNO_DISK
#ifdef KPST_FLASH_SERNO_DISK
      vid = 0L;
      pid = 0L;

      if(SUCCEEDED(retc)) retc = GetFlashVidPid(ser_no_txt, &vid, &pid);

      if(FAILED(retc))
      {
         vid = 0L;
         pid = 0L;
         retc = S_OK;
      }
#endif

#ifdef Logging
PutLogMessage_("TFIRCVP: %x %x", vid, pid);
#endif

// ---------------------------
// long dev_id_0 = dev_id;

      if(SUCCEEDED(retc)) dev_id ^= vid;
// long dev_id_vid = dev_id;

      if(SUCCEEDED(retc)) dev_id ^= pid;
// long dev_id_pid = dev_id;

// --------------------------------
// tomo dydá xorinam prie dev_id

      if(SUCCEEDED(retc)) dev_id ^= vol_size.LowPart;

// KpMsgOutF_5("[%s] [%s] [%s] %x %x", dev_name, pntd, pntd1, vid, pid);
// KpMsgOutF_5("ser_no_hex: %lx vid: %lx pid: %lx vol_size: %ld %lx", dev_id_0, vid, pid, vol_size.LowPart, vol_size.LowPart);
// KpMsgOutF_4("dev_id: orig: %lx ^vid: %lx ^pid: %lx ^vol_size: %lx", dev_id_0, dev_id_vid, dev_id_pid, dev_id);
// fstream out_file("serno.txt", ios::out | ios::ate);
// out_file << "ser_no_hex: " << hex << dev_id_0 << " vid: " << vid << " pid: " << pid << " vol_size: " << dec << vol_size.LowPart << " " << hex << vol_size.LowPart << endl;
// out_file << "dev_id: orig: " << hex << dev_id_0 << " ^vid: " << dev_id_vid << " ^pid: " << dev_id_pid << " ^vol_size: " << dev_id << endl;
// out_file << endl;
// out_file.close();

// KP_TRACE_("TestFlashID_RC() dev_id: %lx m_lFlashId: %lx", dev_id, test_fl_pars_ptr->m_lFlashId);

#ifdef Logging
PutLogMessage_("TFIRC: %x %x", dev_id, test_fl_pars_ptr->m_lFlashId);
#endif

// ------------------------ tikrinam
      if(SUCCEEDED(retc)) if(dev_id == test_fl_pars_ptr->m_lFlashId) found = True;
// KP_TRACE_2("TestFlashID_RC(): ser. no. hex: %x reikia: %x", dev_id, test_fl_pars_ptr->m_lFlashId);
// KpMsgOutF_2("TestFlashID_RC(): rg: %x fl: %x", dev_id, test_fl_pars_ptr->m_lFlashId);

   } // for(ii=0; (ii<dev_count) && (!found) && SUCCEEDED(retc); ii++)

// ---------------------------------
   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      hKey=NULL;
   }

   if(found &&
      (!lic_flash) && // pririðtoms per FlashId licencijoms atmintuko neuþtenka, dar bus tikrinama ir licencija
      SUCCEEDED(retc))
         cMemBank[KP11_BLOCK_PROCESSING/2] = False;

   if(SUCCEEDED(retc)) *test_fl_pars_ptr->m_pbFound = found;

// #ifdef Logging
// out_file.close();
// #endif

return(retc);
}


// -----------------------------------------
HRESULT GetFlashSerNo(const unsigned char *lpszDevName, long *plSerNo, unsigned char *lpszSerNoTxt, long *plVid, long *plPid, bool bDiskDevNameFormat)
{
HRESULT retc = S_OK;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
unsigned char *pntd = NULL;
unsigned char *pntd1 = NULL;
int st_pos;
long ser_no;
long vid;
long pid;

   KP_ASSERT(lpszDevName, E_INVALIDARG, null, True);

   if(plSerNo) *plSerNo = 0L;
   if(lpszSerNoTxt) lpszSerNoTxt[0] = Nul;
   if(plVid) *plVid = 0L;
   if(plPid) *plPid = 0L;

   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, name, type, lpszDevName);

// #ifndef KPST_FLASH_SERNO_DISK
// "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum" lauko reik­mïs:
//    "USB\\Vid_3538&Pid_0042\\00000000000B18" ser. no. = 0x00000B18
//    "USB\\VID_3538&PID_0042\\000000000000A1" ser. no. = "000000A1"
//    "USB\\VID_058F&PID_6387\\5XL3S443" ser. no. = "5XL3S443"
//    USB\VID_152D&PID_2338\7D1200BE6E50

// #else
// laukø "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum" ir
//    "SYSTEM\\CurrentControlSet\\Services\\partmgr\\Enum" reik­mïs:
//    "USBSTOR\\Disk&Ven_Generic&Prod_USB_Flash_Disk&Rev_0.00\\000000000000A1&0" ser. no. = "000000A1"
//    "USBSTOR\\Disk&Ven_JetFlash&Prod_Transcend_2GB&Rev_8.07\\5XL3S443&0" ser. no. = "5XL3S443"
//    USBSTOR\Disk&Ven_WDC_WD12&Prod_00BEVE-00WZT0&Rev_\7D1200BE6E50&0

// ie­kom paskutinio '&'
   if(bDiskDevNameFormat && SUCCEEDED(retc))
   {
      pntd = name;
      do
      {
         pntd1 = strchr(pntd + 1, '&');
         if(pntd1) pntd = pntd1;
      } while(pntd1);
      if(*pntd == '&') *pntd = Nul;
   }
// #endif

// ---------------------------------
// name --> ser.no. --> dev_id
// ieðkom name[] paskutinio '\\' // nafig reikia?
   if(SUCCEEDED(retc))
   {
      pntd = name;
//    do
//    {
//       pntd1 = strchr(pntd, '\\');
//       if(pntd1) pntd = pntd1 + 1;
//    } while(pntd1);

//    if(lpszSerNoTxt) strcpy(lpszSerNoTxt, pntd);
   }

   if(SUCCEEDED(retc))
   {
      st_pos = strlen(pntd /* name */) - MAX_LONG_HEX_DIGITS;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
      if(st_pos < 0) st_pos = 0;
// KP_TRACE_1("GetFlashSerNo(): ser. no. txt: %s", pntd /* name */ + st_pos);

      if(lpszSerNoTxt) strcpy(lpszSerNoTxt, pntd /* name */ + st_pos);

      retc = ForceTextToHex(pntd /* name */ + st_pos);
   }

   ser_no = 0L;
   if(SUCCEEDED(retc))
      if(sscanf((const char *)pntd /* name */ + st_pos, "%lx", &ser_no) != 1)
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
         ser_no = 0L;
      }
   if(plSerNo) *plSerNo = ser_no;

// ---------------------------------
// path --> vid/pid, xorinam prie dev_id
   vid = pid = 0L;

   if((!bDiskDevNameFormat) && SUCCEEDED(retc))
   {
// ieðkom path[] paskutinio '\\'  // galima bûtø dar kartà TvFnameSplit()
      if(SUCCEEDED(retc))
      {
         pntd = path;
         do
         {
            pntd1 = strchr(pntd, '\\');
            if(pntd1) pntd = pntd1 + 1;
         } while(pntd1);
      }

// ieðkom '&', atskyrëjo tarp VID ir PID
// "Vid_3538&Pid_0042"
// "VID_3538&PID_0042"

      pntd1 = null;
      if(SUCCEEDED(retc))
      {
         pntd1 = strchr(pntd, '&');
         if(pntd1 == null)
            retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null /* pntd */, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(pntd1 && SUCCEEDED(retc))
      {
         *pntd1++ = Nul;

         strlwr(pntd);
         strlwr(pntd1);

         if((strstr(pntd, "vid_") != pntd) || (strstr(pntd1, "pid_") != pntd1))
         {
//          *(--pntd1) = '&';
            retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null /* pntd */, False, __FILE__, __LINE__, 0L, NULL);
         }
         else
         {
            pntd += strlen("vid_");
            pntd1 += strlen("pid_");

// -------- vid
            if(SUCCEEDED(retc))
            {
               st_pos = strlen(pntd) - MAX_LONG_HEX_DIGITS;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
               if(st_pos < 0) st_pos = 0;
               retc = ForceTextToHex(pntd + st_pos);
            }
            if(SUCCEEDED(retc))
            {
               if(sscanf((const char *)pntd + st_pos, "%lx", &vid) != 1)
               {
                  retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null /* pntd */, False, __FILE__, __LINE__, 0L, NULL);
                  vid = 0L;
               }
            }

// -------- pid
            if(SUCCEEDED(retc))
            {
               st_pos = strlen(pntd1) - MAX_LONG_HEX_DIGITS;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
               if(st_pos < 0) st_pos = 0;
               retc = ForceTextToHex(pntd1 + st_pos);
            }
            if(SUCCEEDED(retc))
            {
               if(sscanf((const char *)pntd1 + st_pos, "%lx", &pid) != 1)
               {
                  retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null /* pntd */, False, __FILE__, __LINE__, 0L, NULL);
                  pid = 0L;
               }
            }

         } // else // if((strstr(pntd, "vid_") != pntd) || (strstr(pntd1, "pid_") != pntd1))

      } // if(pntd1 && SUCCEEDED(retc)) // pntd1 = strchr(pntd, '\\');

   } // if((!bDiskDevNameFormat) && SUCCEEDED(retc))

   if(plVid) *plVid = vid;
   if(plPid) *plPid = pid;

return(retc);
}


// -------------------------
HRESULT GetFlashVidPid(const unsigned char *lpszSerNoTxt, long *plVid, long *plPid)
{
HRESULT retc = S_OK;
static unsigned char key_name[KP_MAX_FNAME_LEN + KP_MAX_FNAME_LEN + 1];
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
DWORD dwBufLen;
DWORD dwValType;
long dev_count = 0L;
bool found = False;
unsigned char dev_num_str[MAX_LONG_DIGITS + 1];
int ii;
static unsigned char dev_name[KP_MAX_FNAME_LEN+1];
// long ser_no = 0L;
long vid = 0L;
long pid = 0L;
static unsigned char ser_no_txt[KP_MAX_FNAME_LEN + 1];
static unsigned char ser_no_txt_src[KP_MAX_FNAME_LEN + 1];

   ser_no_txt_src[0] = Nul;
   KP_ASSERT(lpszSerNoTxt, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(ser_no_txt_src, lpszSerNoTxt);
      strlwr(ser_no_txt_src);
   }

   if(plVid) *plVid = 0L;
   if(plPid) *plPid = 0L;

// --------------------------- atidarom registro raktà
   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum");
      key_name[0]='S';
      key_name[1]='Y';
      key_name[2]='S';
      key_name[3]='T';
      key_name[4]='E';
      key_name[5]='M';
      key_name[6]='\\';
      key_name[7]='C';
      key_name[8]='u';
      key_name[9]='r';
      key_name[10]='r';
      key_name[11]='e';
      key_name[12]='n';
      key_name[13]='t';
      key_name[14]='C';
      key_name[15]='o';
      key_name[16]='n';
      key_name[17]='t';
      key_name[18]='r';
      key_name[19]='o';
      key_name[20]='l';
      key_name[21]='S';
      key_name[22]='e';
      key_name[23]='t';
      key_name[24]='\\';
      key_name[25]='S';
      key_name[26]='e';
      key_name[27]='r';
      key_name[28]='v';
      key_name[29]='i';
      key_name[30]='c';
      key_name[31]='e';
      key_name[32]='s';
      key_name[33]='\\';
      key_name[34]='U';
      key_name[35]='S';
      key_name[36]='B';
      key_name[37]='S';
      key_name[38]='T';
      key_name[39]='O';
      key_name[40]='R';
      key_name[41]='\\';
      key_name[42]='E';
      key_name[43]='n';
      key_name[44]='u';
      key_name[45]='m';
      key_name[46]=Nul;

      retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "Count");
      key_name[0]='C';
      key_name[1]='o';
      key_name[2]='u';
      key_name[3]='n';
      key_name[4]='t';
      key_name[5]=Nul;

      dwBufLen = sizeof(dev_count);
      retw = RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)&dev_count, &dwBufLen);
      if((dwValType != REG_DWORD) || (retw != ERROR_SUCCESS))
      {
         dev_count = 0L;
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE_1("GetFlashVidPid(): Negaliu atidaryti %s", key_name);
      }
   }

   for(ii=0; (ii < dev_count) && (!found) && SUCCEEDED(retc); ii++)
   {
      sprintf((char *)dev_num_str, "%d", ii);

      dwBufLen = KP_MAX_FNAME_LEN;
      retw = RegQueryValueEx(hKey, (const char *)dev_num_str, NULL, &dwValType, (LPBYTE)dev_name, &dwBufLen);
      if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
      {
         dev_name[0]=Nul;
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
      else dev_name[dwBufLen]=Nul;

// !!!!!! èia testuojam kliento atmintukà Plius78m/klaida_issitryne_8P1-51431-0485
// strcpy(dev_name, "USB\\Vid_18a5&Pid_0304\\00000000003718");

      /* ser_no = */ vid = pid = 0L;
      ser_no_txt[0] = 0;

// ---------------- ser.no.
      if(SUCCEEDED(retc)) retc = GetFlashSerNo(dev_name, NULL /* &ser_no */, ser_no_txt, &vid, &pid, False);
      if(SUCCEEDED(retc)) strlwr(ser_no_txt);
      else
      {
//       ser_no = 0L;
         vid = 0L;
         pid = 0L;
         ser_no_txt[0] = 0;
         retc = S_OK;
      }

// ------------------------ tikrinam
      if(SUCCEEDED(retc)) if(strcmp(ser_no_txt, ser_no_txt_src /* lpszSerNoTxt */) == 0)
      {
         found = True;
         if(plVid) *plVid = vid;
         if(plPid) *plPid = pid;
      }

   } // for(ii=0; (ii<dev_count) && (!found) && SUCCEEDED(retc); ii++)

// ---------------------------------
   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      hKey=NULL;
   }

return(retc);
}


// ==================================================================
#ifndef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::EnctBuf(void *pcBuffer, long lBufLen, int iSeed, bool bCheckErrors)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
unsigned char *pntd;
long rest;
int cur_len;

   rc_pars.iOpCode = KP_RC_ENCT;
   rc_pars.iParBlSize = sizeof(rc_pars);

#ifdef Debug_RYt_putw
PutLogMessage_("EB() .... %x %x", &rc_pars, pcBuffer);
#endif

   pntd=(unsigned char *)pcBuffer;
   rest=lBufLen;
   while((rest>0) && SUCCEEDED(retc))
   {
      cur_len=(rest<=Maxint)?rest:Maxint;

      rc_pars.enc.iDataLen = cur_len;
      rc_pars.enc.pData = pntd;
      rc_pars.enc.lCtrl = iSeed;

#if FALSE // #ifdef Debug
KP_TRACE("=================================");
// sprintf(str_buf, "iOpCode     %o:%o", ((rc_pars.iOpCode>>16) & 0xFFFF), (rc_pars.iOpCode & 0xFFFF)); KP_TRACE(str_buf);
// sprintf(str_buf, "iParBlSize  %o:%o", ((rc_pars.iParBlSize>>16) & 0xFFFF), (rc_pars.iParBlSize & 0xFFFF)); KP_TRACE(str_buf);
// sprintf(str_buf, "iDataLen    %o:%o", ((rc_pars.enc.iDataLen>>16) & 0xFFFF), (rc_pars.enc.iDataLen & 0xFFFF)); KP_TRACE(str_buf);
// sprintf(str_buf, "pData       %o:%o", ((((long)rc_pars.enc.pData)>>16) & 0xFFFF), (((long)rc_pars.enc.pData) & 0xFFFF)); KP_TRACE(str_buf);

pnts=(unsigned char *)&rc_pars;
for(ii=0; ii<sizeof(rc_pars); ii++)
{
sprintf(str_buf, "rc_pars[%d]:%o", ii, *pnts++);
KP_TRACE(str_buf);
}
#endif

// PutLogMessage_("KpStApp::ETB ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

      retc=EmuTv.ExecRemoteCall(&rc_pars, bCheckErrors);

      pntd+=cur_len;
      rest-=cur_len;
   }

return(retc);
}
#endif


// -------------------------------------------
#define KPSTAP_ENC_STR_LEN 32
unsigned char lpszEncStr[KPSTAP_ENC_STR_LEN]=
{
   0x5f, 0x34, 0x18, 0x26, 0xDF, 0xF5, 0x33, 0x1E,
   0x86, 0x99, 0x25, 0x64, 0x3A, 0xBC, 0xDE, 0xF0,
   0x12, 0x34, 0x56, 0x78, 0x98, 0x69, 0x92, 0x56,
   0x43, 0x30, 0x82, 0x30, 0x42, 0xF4, 0x2A, 0xFE
};

HRESULT /* KpStApp:: */ EnctBufSimpl(void *pcBuffer, long lBufLen)
{
HRESULT retc=S_OK;
long ll;

   KP_ASSERT(pcBuffer, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) for(ll = 0L; ll < lBufLen; ll++)
      ((unsigned char *)pcBuffer)[ll] ^= lpszEncStr[ll%KPSTAP_ENC_STR_LEN];

return(retc);
}


HRESULT /* KpStApp:: */ EnctBufMed(void *pcBuffer, long lBufLen, int ProdVer, long lEntryId)
{
HRESULT retc = S_OK;
unsigned int mask = ProdVer ^ (ProdVer / 1000) ^ lEntryId;
long ll;

   KP_ASSERT(pcBuffer, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) for(ll = 0L; ll < lBufLen; ll++)
      ((unsigned char *)pcBuffer)[ll] ^= (unsigned char)((mask ^ ll) & 0xFF);

return(retc);
}


// ---------------------------------------------
// TODO: algoritmas nejautrus pradinei kaukës reikðmei, keièiasi tik viso uþkoduoto masyvo reikðmës, atkoduoto masyvo skiriasi tik paskutinis baitas
HRESULT /* KpStApp:: */ EnctBufInc(void *pcBuffer, long lBufLen, int /* ProdVer */, long /* lEntryId */, bool bEncode)
{
HRESULT retc = S_OK;
// unsigned int mask_init = (ProdVer ^ (ProdVer / 1000) ^ lEntryId) & 0xFF;
unsigned int mask = 0;
long ll;

   KP_ASSERT(pcBuffer, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) for(ll = lBufLen - 1L; ll >= 0L; ll--)
   {
unsigned int mask_sav = ((unsigned char *)pcBuffer)[ll];

      ((unsigned char *)pcBuffer)[ll] ^= (unsigned char)((mask ^ ll) & 0xFF);

      mask = bEncode? ((unsigned char *)pcBuffer)[ll] : mask_sav;
   }

return(retc);
}


// -------------------------------------------
#ifndef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::EnctIniData(int iSize, bool bCheckErrors)
{
HRESULT retc=S_OK;
#if FALSE // #ifdef Debug
char str_buf[200];
int ii;
unsigned char *pnts;
#endif

   if(SUCCEEDED(retc)) retc = EnctBuf(&m_Ini, ((iSize - sizeof(m_Ini.m_iCheckSum))/4)*4, // (sizeof(KpStIniData)/4)*4);
                                          m_Ini.m_iCheckSum, bCheckErrors);

#if FALSE // #ifdef Debug
KP_TRACE("--------------------------");

sprintf(str_buf, "m_Ini: [%d]", sizeof(m_Ini)); KP_TRACE(str_buf);

sprintf(str_buf, "lpszCmdStr:       %d[%d]", (long)m_Ini.m_lpszCmdStr         - (long)&m_Ini, sizeof(m_Ini.m_lpszCmdStr     )); KP_TRACE(str_buf);
sprintf(str_buf, "iProlShowTime:    %d[%d]", (long)&m_Ini.m_iProlShowTime     - (long)&m_Ini, sizeof(m_Ini.m_iProlShowTime  )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszProlFName:    %d[%d]", (long)m_Ini.m_lpszProlFName      - (long)&m_Ini, sizeof(m_Ini.m_lpszProlFName  )); KP_TRACE(str_buf);
sprintf(str_buf, "iBitmapWdt:       %d[%d]", (long)&m_Ini.m_iBitmapWdt        - (long)&m_Ini, sizeof(m_Ini.m_iBitmapWdt     )); KP_TRACE(str_buf);
sprintf(str_buf, "iBitmapHgt:       %d[%d]", (long)&m_Ini.m_iBitmapHgt        - (long)&m_Ini, sizeof(m_Ini.m_iBitmapHgt     )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszPwdWndName:   %d[%d]", (long)m_Ini.m_lpszPwdWndName     - (long)&m_Ini, sizeof(m_Ini.m_lpszPwdWndName )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszPwd:          %d[%d]", (long)m_Ini.m_lpszPwd            - (long)&m_Ini, sizeof(m_Ini.m_lpszPwd        )); KP_TRACE(str_buf);
sprintf(str_buf, "iPwdEdCtrl:       %d[%d]", (long)&m_Ini.m_iPwdEdCtrl        - (long)&m_Ini, sizeof(m_Ini.m_iPwdEdCtrl     )); KP_TRACE(str_buf);
sprintf(str_buf, "iPwdOkBut:        %d[%d]", (long)&m_Ini.m_iPwdOkBut         - (long)&m_Ini, sizeof(m_Ini.m_iPwdOkBut      )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszVolName:      %d[%d]", (long)m_Ini.m_lpszVolName        - (long)&m_Ini, sizeof(m_Ini.m_lpszVolName    )); KP_TRACE(str_buf);
sprintf(str_buf, "lSerNo:           %d[%d]", (long)&m_Ini.m_lSerNo            - (long)&m_Ini, sizeof(m_Ini.m_lSerNo         )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszBmpFName:     %d[%d]", (long)m_Ini.m_lpszBmpFName       - (long)&m_Ini, sizeof(m_Ini.m_lpszBmpFName   )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszEpilFName:    %d[%d]", (long)m_Ini.m_lpszEpilFName      - (long)&m_Ini, sizeof(m_Ini.m_lpszEpilFName  )); KP_TRACE(str_buf);
sprintf(str_buf, "iEpilShowTime:    %d[%d]", (long)&m_Ini.m_iEpilShowTime     - (long)&m_Ini, sizeof(m_Ini.m_iEpilShowTime  )); KP_TRACE(str_buf);
sprintf(str_buf, "iAlignmentField:  %d[%d]", (long)&m_Ini.iAlignmentField     - (long)&m_Ini, sizeof(m_Ini.iAlignmentField  )); KP_TRACE(str_buf);


pnts=(unsigned char *)&m_Ini;
for(ii=0; ii<sizeof(m_Ini); ii++)
{
sprintf(str_buf, "m_Ini[%d]:%x", ii, *pnts++);
KP_TRACE(str_buf);
}
#endif

return(retc);
}
#endif




// ==================================================================
#ifndef KPST_MOVE_TO_KPHP11
HRESULT TestIniChSum_RC(void *pRetC)
{
HRESULT retc=S_OK;
unsigned char *ini_ptr=NULL;
int ch_sum;

   if(((pRetC==NULL) || (theKpStAppPtr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ini_ptr=(unsigned char *)&(theKpStAppPtr->m_Ini);
      ch_sum=0;
      while(ini_ptr!=(unsigned char *)&(theKpStAppPtr->m_Ini.m_iCheckSum)) ch_sum+=(*ini_ptr++);

      if(ch_sum!=theKpStAppPtr->m_Ini.m_iCheckSum)
         *(HRESULT *)pRetC=retc=KP_E_FILE_FORMAT;
   }

return(retc);
}
#endif


// ==================================================================
#ifndef KPST_MOVE_TO_KPHP11
HRESULT SetIniChSum_RC(void * /* pVoid */)
{
HRESULT retc=S_OK;
unsigned char *ini_ptr=NULL;
int ch_sum;

   if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ini_ptr=(unsigned char *)&(theKpStAppPtr->m_Ini);
      ch_sum=0;
      while(ini_ptr!=(unsigned char *)&(theKpStAppPtr->m_Ini.m_iCheckSum)) ch_sum+=(*ini_ptr++);

      theKpStAppPtr->m_Ini.m_iCheckSum=ch_sum;
   }

return(retc);
}
#endif


// -------------------------------------------
#ifdef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::GetIniElement(void *pValBuf, long lOffset, int iLen)
{
HRESULT retc = S_OK;
// unsigned char *buf_tmp = NULL;
static unsigned char par_buf[KP_MAX_FILE_LIN_WDT + 1];
static KpRcPars rc_pars;

   KP_ASSERT(pValBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(iLen <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);

// KP_NEWA(buf_tmp, unsigned char, iLen + 4 + 4);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_GET_INI_ELEM;
      rc_pars.iParBlSize = sizeof(KpRcPars);
      rc_pars.enc.iDataLen = iLen;
      rc_pars.enc.pData = par_buf; // buf_tmp;
      rc_pars.enc.lCtrl = lOffset;

// PutLogMessage_("KpStApp::GIE ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("GIE() ....>>>> %x %x", &rc_pars, par_buf); // buf_tmp);
#endif

      retc=EmuTv.ExecRemoteCall(&rc_pars);
   }

   if(SUCCEEDED(retc)) memcpy(pValBuf, par_buf /* buf_tmp */, iLen);

// KP_DELETEA(buf_tmp);

return(retc);
}
#endif

HRESULT KpStApp::GetIniElementIfNotStopped(void *pValBuf, long lOffset, int iLen)
{
HRESULT retc=S_OK;
// unsigned char *buf_tmp = NULL;
static unsigned char par_buf[KP_KWD_LEN /* KP_MAX_FILE_LIN_WDT */ + 1];
static KpRcPars rc_pars;

// PutLogMessage_("GetIniElementIfNotStopped() %d %d", MemBankObj[KP11_BLOCK_PROCESSING/2], MemBankObj[KP11_BLOCK_TERM/2]);

   KP_ASSERT(pValBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(iLen <= KP_KWD_LEN /* KP_MAX_FILE_LIN_WDT */, KP_E_BUFFER_OVERFLOW, null, True);

// KP_NEWA(buf_tmp, unsigned char, iLen + 4 + 4);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_GET_INI_ELEM_IF_NOT_STOPPED;
      rc_pars.iParBlSize = sizeof(KpRcPars);
      rc_pars.enc.iDataLen = iLen;
      rc_pars.enc.pData = par_buf; // buf_tmp;
      rc_pars.enc.lCtrl = lOffset;

// PutLogMessage_("KpStApp::GIEINS ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("GIEINS() ....>>>> %x %x", &rc_pars, par_buf); // buf_tmp);
#endif

      retc=EmuTv.ExecRemoteCall(&rc_pars);
   }

   if(SUCCEEDED(retc)) memcpy(pValBuf, par_buf /* buf_tmp */, iLen);

// KP_DELETEA(buf_tmp);

return(retc);
}

#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::SetIniElement(const void *pValBuf, long lOffset, int iLen)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;

   if((pValBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(
      (
         (((KP_MAX_FILE_LIN_WDT + 1 + 4) / 4) * 4 > HP11_INI_ELEM_BUF_LEN) ||
         (((TV_TAG_LEN + 1 + 4) / 4) * 4 > HP11_INI_ELEM_BUF_LEN) ||
         (((KP_MAX_FNAME_LEN + 1 + 4) / 4) * 4 > HP11_INI_ELEM_BUF_LEN) ||
         (((KP_MAX_FTYPE_LEN + 1 + 4) / 4) * 4 > HP11_INI_ELEM_BUF_LEN) ||
         (((iLen + 4) / 4) * 4 > HP11_INI_ELEM_BUF_LEN)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_SET_INI_ELEM;
      rc_pars.iParBlSize = sizeof(KpRcPars);
      rc_pars.enc.iDataLen = iLen;
      rc_pars.enc.pData = (void *)pValBuf;
      rc_pars.enc.lCtrl = lOffset;

// PutLogMessage_("KpStApp::SIE ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SIE() .... %x %x", &rc_pars, pValBuf);
#endif

      retc = EmuTv.ExecRemoteCall(&rc_pars);
   }

return(retc);
}
#endif


//============================================
HRESULT KpStApp::GetIniCmdStr(unsigned char *lpszCmdStrBuf)
{
HRESULT retc=S_OK;

   if((lpszCmdStrBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszCmdStrBuf, IniDataBuf.m_lpszCmdStr - (unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(lpszCmdStrBuf, m_Ini.m_lpszCmdStr);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniProlShowTime(int *piProlShTim)
{
HRESULT retc=S_OK;

   if((piProlShTim==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piProlShTim, (unsigned char *)&IniDataBuf.m_iProlShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piProlShTim=m_Ini.m_iProlShowTime;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniProlFName(unsigned char *lpszProlFNameBuf)
{
HRESULT retc=S_OK;

   if((lpszProlFNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszProlFNameBuf, IniDataBuf.m_lpszProlFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszProlFNameBuf, m_Ini.m_lpszProlFName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniBitmapWdt(int *piBmpWdt)
{
HRESULT retc=S_OK;

   if((piBmpWdt==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piBmpWdt, (unsigned char *)&IniDataBuf.m_iBitmapWdt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piBmpWdt = m_Ini.m_iBitmapWdt;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniBitmapHgt(int *piBmpHgt)
{
HRESULT retc=S_OK;

   if((piBmpHgt==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piBmpHgt, (unsigned char *)&IniDataBuf.m_iBitmapHgt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piBmpHgt = m_Ini.m_iBitmapHgt;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPwdWndName(unsigned char *lpszPwdWndNameBuf)
{
HRESULT retc=S_OK;

   if((lpszPwdWndNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszPwdWndNameBuf, IniDataBuf.m_lpszPwdWndName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPwdWndNameBuf, m_Ini.m_lpszPwdWndName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPwd(unsigned char *lpszPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszPwdBuf, IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(lpszPwdBuf, m_Ini.m_lpszPwd);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniOldPwd(unsigned char *lpszOldPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszOldPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszOldPwdBuf, IniDataBuf.m_lpszOldPwd - (unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(lpszOldPwdBuf, m_Ini.m_lpszOldPwd);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPwdEdCtrl(int *piPwdEdCtrl)
{
HRESULT retc=S_OK;

   if((piPwdEdCtrl==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piPwdEdCtrl, (unsigned char *)&IniDataBuf.m_iPwdEdCtrl - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piPwdEdCtrl = m_Ini.m_iPwdEdCtrl;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPwdOkBut(int *piPwdOkBut)
{
HRESULT retc=S_OK;

   if((piPwdOkBut==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piPwdOkBut, (unsigned char *)&IniDataBuf.m_iPwdOkBut - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piPwdOkBut = m_Ini.m_iPwdOkBut;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniVolName(unsigned char *lpszVolNameBuf)
{
HRESULT retc=S_OK;

   if((lpszVolNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszVolNameBuf, IniDataBuf.m_lpszVolName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszVolNameBuf, m_Ini.m_lpszVolName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniSerNo(long *plSerNo)
{
HRESULT retc=S_OK;

   if((plSerNo==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(plSerNo, (unsigned char *)&IniDataBuf.m_lSerNo - (unsigned char *)&IniDataBuf, sizeof(long));
#else
      *plSerNo = m_Ini.m_lSerNo;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniBmpFName(unsigned char *lpszBmpFNameBuf)
{
HRESULT retc=S_OK;

   if((lpszBmpFNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszBmpFNameBuf, IniDataBuf.m_lpszBmpFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszBmpFNameBuf, m_Ini.m_lpszBmpFName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniEpilFName(unsigned char *EpilFNameBuf)
{
HRESULT retc=S_OK;

   if((EpilFNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(EpilFNameBuf, IniDataBuf.m_lpszEpilFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(EpilFNameBuf, m_Ini.m_lpszEpilFName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniEpilShowTime(int *piEpilShowTime)
{
HRESULT retc=S_OK;

   if((piEpilShowTime==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piEpilShowTime, (unsigned char *)&IniDataBuf.m_iEpilShowTime - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piEpilShowTime = m_Ini.m_iEpilShowTime;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPresetFName(unsigned char *lpszPresFNameBuf)
{
HRESULT retc=S_OK;

   if((lpszPresFNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszPresFNameBuf, IniDataBuf.m_lpszPresetFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPresFNameBuf, m_Ini.m_lpszPresetFName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniRezFName(unsigned char *lpszRezFNameBuf)
{
HRESULT retc=S_OK;

   if((lpszRezFNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszRezFNameBuf, IniDataBuf.m_lpszRezFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRezFNameBuf, m_Ini.m_lpszRezFName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniCheckCD(bool *pbCheckCD)
{
HRESULT retc=S_OK;

   if((pbCheckCD==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbCheckCD, (unsigned char *)&IniDataBuf.m_bCheckCD - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbCheckCD = m_Ini.m_bCheckCD;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniBound(bool *pbBound)
{
HRESULT retc=S_OK;

   if((pbBound==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbBound, (unsigned char *)&IniDataBuf.m_bBound - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbBound = m_Ini.m_bBound;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniProdVer(int *piProdVer)
{
HRESULT retc=S_OK;

   if((piProdVer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piProdVer, (unsigned char *)&IniDataBuf.m_iProdVer - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piProdVer = m_Ini.m_iProdVer;
#endif
   }

return(retc);
}

int GetProdVer(void)
{
    int prod_ver = 0;
    if (theKpStAppPtr)
    {
        if (FAILED(theKpStAppPtr->GetIniProdVer(&prod_ver)))
            prod_ver = 0;
    }
    return prod_ver;
}

HRESULT KpStApp::GetIniProdName(unsigned char *lpszProdNameBuf)
{
HRESULT retc = S_OK;

   if((lpszProdNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszProdNameBuf, IniDataBuf.lpszProdName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszProdNameBuf, m_Ini.m_lpszProdName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniProdNameDec(unsigned char *lpszProdNameBuf)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc)) retc = GetIniProdName(lpszProdNameBuf);

   if((iMsgLangOff == KpLangPl_1250) && SUCCEEDED(retc)) // lenkiðkas produkto vardas visada 1257 lentelëje – perkoduojam
   {
KpChar *istr_buf = NULL;
      KP_NEWA(istr_buf, KpChar, strlen(lpszProdNameBuf) + 1);

      if(SUCCEEDED(retc)) KptStrEncode(istr_buf, lpszProdNameBuf, TV_MAIN_CTBL); // 71
      if(SUCCEEDED(retc)) KptStrDecode(lpszProdNameBuf, istr_buf, 79); // Windows-1250 CE

      KP_DELETEA(istr_buf);
   }

return(retc);
}

HRESULT KpStApp::GetIniWndName(unsigned char *lpszWndNameBuf)
{
HRESULT retc = S_OK;

   if((lpszWndNameBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszWndNameBuf, IniDataBuf.lpszWndName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszWndNameBuf, m_Ini.m_lpszWndName);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniPublisher(unsigned char *lpszPublisherBuf)
{
HRESULT retc=S_OK;

   if((lpszPublisherBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszPublisherBuf, IniDataBuf.m_lpszPublisher - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPublisherBuf, m_Ini.m_lpszPublisher);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniRegURL(unsigned char *lpszRegURLBuf)
{
HRESULT retc=S_OK;

   if((lpszRegURLBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszRegURLBuf, IniDataBuf.m_lpszRegURL - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRegURLBuf, m_Ini.m_lpszRegURL);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniRezVar(unsigned char *lpszRezVarBuf)
{
HRESULT retc=S_OK;

   if((lpszRezVarBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszRezVarBuf, IniDataBuf.m_lpszRezVar - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRezVarBuf, m_Ini.m_lpszRezVar);
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniKumul(bool *pbKumul)
{
HRESULT retc=S_OK;

   if((pbKumul==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbKumul, (unsigned char *)&IniDataBuf.m_bKumul - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbKumul = m_Ini.m_bKumul;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniShuffCnt(int *piShuffCnt)
{
HRESULT retc=S_OK;

   if((piShuffCnt==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piShuffCnt, (unsigned char *)&IniDataBuf.m_iShuffCnt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piShuffCnt = m_Ini.m_iShuffCnt;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniAttOff(long *plAttOff)
{
HRESULT retc=S_OK;

   if((plAttOff==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(plAttOff, (unsigned char *)&IniDataBuf.m_lAttOff - (unsigned char *)&IniDataBuf, sizeof(long));
#else
      *plAttOff = m_Ini.m_lAttOff;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniAttExt(unsigned char *lpszAttExtBuf)
{
HRESULT retc=S_OK;

   if((lpszAttExtBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszAttExtBuf, IniDataBuf.m_lpszAttExt - (unsigned char *)&IniDataBuf, KP_MAX_FTYPE_LEN+1);
#else
      strcpy(lpszAttExtBuf, m_Ini.m_lpszAttExt);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniCiDirect(bool *pbCiDirect)
{
HRESULT retc=S_OK;

   if((pbCiDirect==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbCiDirect, IniDataBuf.m_bCiDirect-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbCiDirect=m_Ini.m_bCiDirect;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniFlashId(long *plFlashId)
{
HRESULT retc=S_OK;

   if((plFlashId==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(plFlashId, (unsigned char *)&IniDataBuf.m_lFlashId-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      *plFlashId=m_Ini.m_lFlashId;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniCheckFlash(bool *pbCheckFlash)
{
HRESULT retc=S_OK;

   if((pbCheckFlash==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbCheckFlash, (unsigned char *)&IniDataBuf.m_bCheckFlash-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbCheckFlash=m_Ini.m_bCheckFlash;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniLicFlash(bool *pbLicFlash)
{
HRESULT retc = S_OK;

   if((pbLicFlash == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc = GetIniElement(pbCheckFlash, (unsigned char *)&IniDataBuf.m_bLicFlash - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbLicFlash = m_Ini.m_bLicFlash;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniNumOfLics(int *piNumOfLics)
{
HRESULT retc=S_OK;

   if((piNumOfLics==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piNumOfLics, (unsigned char *)&IniDataBuf.m_iNumOfLics-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piNumOfLics=m_Ini.m_iNumOfLics;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniTestCid(unsigned char *lpszTestCidBuf)
{
HRESULT retc=S_OK;

   if((lpszTestCidBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszTestCidBuf, IniDataBuf.m_lpszTestCid-(unsigned char *)&IniDataBuf, KPST_TXTCD_CHARS_PER_VAL_TID+1);
#else
      strcpy(lpszTestCidBuf, m_Ini.m_lpszTestCid);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniIniLicID(int *piIniLicID)
{
HRESULT retc=S_OK;

   if((piIniLicID==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piIniLicID, (unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piIniLicID=m_Ini.m_iIniLicID;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniCompIdMode(int *piCompIdMode)
{
HRESULT retc=S_OK;

   if((piCompIdMode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piCompIdMode, (unsigned char *)&IniDataBuf.m_iCompIdMode-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piCompIdMode=m_Ini.m_iCompIdMode;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniOnTop(bool *pbOnTop)
{
HRESULT retc=S_OK;

   if((pbOnTop==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbOnTop, (unsigned char *)&IniDataBuf.m_bOnTop-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbOnTop=m_Ini.m_bOnTop;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniFullScr(bool *pbFullScr)
{
HRESULT retc=S_OK;

   if((pbFullScr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbFullScr, (unsigned char *)&IniDataBuf.m_bFullScr-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbFullScr=m_Ini.m_bFullScr;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniSubst(bool *pbSubst)
{
HRESULT retc=S_OK;

   if((pbSubst==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbSubst, (unsigned char *)&IniDataBuf.m_bSubst-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbSubst=m_Ini.m_bSubst;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniEboard(bool *pbEboard)
{
HRESULT retc=S_OK;

   if((pbEboard==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbEboard, (unsigned char *)&IniDataBuf.m_bEboard-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbEboard=m_Ini.m_bEboard;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniUserPwd(unsigned char *lpszUserPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszUserPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszUserPwdBuf, IniDataBuf.m_lpszUserPwd-(unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(lpszUserPwdBuf, m_Ini.m_lpszUserPwd);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniAdminPwd(unsigned char *lpszAdminPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszAdminPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszAdminPwdBuf, IniDataBuf.m_lpszAdminPwd-(unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(lpszAdminPwdBuf, m_Ini.m_lpszAdminPwd);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniUserData(unsigned char *lpszUserDataBuf)
{
HRESULT retc=S_OK;

   if((lpszUserDataBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszUserDataBuf, IniDataBuf.m_lpszUserData-(unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(lpszUserDataBuf, m_Ini.m_lpszUserData);
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniClearClipBrd(bool *pbClearClipBrd)
{
HRESULT retc=S_OK;

   if((pbClearClipBrd==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbClearClipBrd, (unsigned char *)&IniDataBuf.m_bClearClipBrd-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbClearClipBrd=m_Ini.m_bClearClipBrd;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniUpdNum(int *piUpdNum)
{
HRESULT retc=S_OK;

   if((piUpdNum==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piUpdNum, (unsigned char *)&IniDataBuf.m_iUpdNum - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piUpdNum = m_Ini.m_iUpdNum;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniShowIE(bool *pbShowIE)
{
HRESULT retc=S_OK;

   if((pbShowIE==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbShowIE, (unsigned char *)&IniDataBuf.m_bShowIE-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbShowIE=m_Ini.m_bShowIE;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniHideBkmrks(bool *pbHideBkmrks)
{
HRESULT retc=S_OK;

   if((pbHideBkmrks==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbHideBkmrks, (unsigned char *)&IniDataBuf.m_bHideBkmrks-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbHideBkmrks=m_Ini.m_bHideBkmrks;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniSoundMuted(bool *pbSoundMuted)
{
HRESULT retc=S_OK;

   if((pbSoundMuted==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbSoundMuted, (unsigned char *)&IniDataBuf.m_bSoundMuted-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbSoundMuted=m_Ini.m_bSoundMuted;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniTestUpdates(bool *pbTestUpdates)
{
HRESULT retc=S_OK;

   if((pbTestUpdates==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(pbTestUpdates, (unsigned char *)&IniDataBuf.m_bTestUpdates-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbTestUpdates=m_Ini.m_bTestUpdates;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniFindBut(bool *pbFindBut)
{
HRESULT retc=S_OK;

   if((pbFindBut == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc = GetIniElement(pbFindBut, (unsigned char *)&IniDataBuf.m_bFindBut - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbFindBut = m_Ini.m_bFindBut;
#endif
   }

return(retc);
}


HRESULT KpStApp::GetIniCheckSum(int *piCheckSum)
{
HRESULT retc=S_OK;

   if((piCheckSum==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(piCheckSum, (unsigned char *)&IniDataBuf.m_iCheckSum-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piCheckSum=m_Ini.m_iCheckSum;
#endif
   }

return(retc);
}


//============================================
HRESULT KpStApp::SetIniCmdStr(const unsigned char *lpszCmdStrVal)
{
HRESULT retc=S_OK;

   if((lpszCmdStrVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszCmdStrVal, IniDataBuf.m_lpszCmdStr - (unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(m_Ini.m_lpszCmdStr, lpszCmdStrVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniProlShowTime(int iProlShTim)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iProlShTim, (unsigned char *)&IniDataBuf.m_iProlShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iProlShowTime=iProlShTim;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniProlFName(const unsigned char *lpszProlFNameVal)
{
HRESULT retc=S_OK;

   if((lpszProlFNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszProlFNameVal, IniDataBuf.m_lpszProlFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszProlFName, lpszProlFNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniBitmapWdt(int iBmpWdtVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iBmpWdtVal, (unsigned char *)&IniDataBuf.m_iBitmapWdt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iBitmapWdt = iBmpWdtVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniBitmapHgt(int iBmpHgtVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iBmpHgtVal, (unsigned char *)&IniDataBuf.m_iBitmapHgt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iBitmapHgt = iBmpHgtVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPwdWndName(const unsigned char *lpszPwdWndNameVal)
{
HRESULT retc=S_OK;

   if((lpszPwdWndNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszPwdWndNameVal, IniDataBuf.m_lpszPwdWndName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszPwdWndName, lpszPwdWndNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPwd(const unsigned char *lpszPwdVal)
{
HRESULT retc=S_OK;

   if((lpszPwdVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszPwdVal, IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(m_Ini.m_lpszPwd, lpszPwdVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniOldPwd(const unsigned char *lpszOldPwdVal)
{
HRESULT retc=S_OK;

   if((lpszOldPwdVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszOldPwdVal, IniDataBuf.m_lpszOldPwd - (unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(m_Ini.m_lpszOldPwd, lpszOldPwdVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPwdEdCtrl(int iPwdEdCtrlVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iPwdEdCtrlVal, (unsigned char *)&IniDataBuf.m_iPwdEdCtrl - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iPwdEdCtrl = iPwdEdCtrlVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPwdOkBut(int iPwdOkButVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iPwdOkButVal, (unsigned char *)&IniDataBuf.m_iPwdOkBut - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iPwdOkBut = iPwdOkButVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniVolName(const unsigned char *lpszVolNameVal)
{
HRESULT retc=S_OK;

   if((lpszVolNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszVolNameVal, IniDataBuf.m_lpszVolName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszVolName, lpszVolNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniSerNo(long lSerNoVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&lSerNoVal, (unsigned char *)&IniDataBuf.m_lSerNo - (unsigned char *)&IniDataBuf, sizeof(long));
#else
      m_Ini.m_lSerNo = lSerNoVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniBmpFName(const unsigned char *lpszBmpFNameVal)
{
HRESULT retc=S_OK;

   if((lpszBmpFNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszBmpFNameVal, IniDataBuf.m_lpszBmpFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszBmpFName, lpszBmpFNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniEpilFName(const unsigned char *EpilFNameVal)
{
HRESULT retc=S_OK;

   if((EpilFNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(EpilFNameVal, IniDataBuf.m_lpszEpilFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszEpilFName, EpilFNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniEpilShowTime(int iEpilShowTimeVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iEpilShowTimeVal, (unsigned char *)&IniDataBuf.m_iEpilShowTime - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iEpilShowTime = iEpilShowTimeVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPresetFName(const unsigned char *lpszPresFNameVal)
{
HRESULT retc=S_OK;

   if((lpszPresFNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszPresFNameVal, IniDataBuf.m_lpszPresetFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszPresetFName, lpszPresFNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniRezFName(const unsigned char *lpszRezFNameVal)
{
HRESULT retc=S_OK;

   if((lpszRezFNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszRezFNameVal, IniDataBuf.m_lpszRezFName - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszRezFName, lpszRezFNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniCheckCD(bool bCheckCDVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bCheckCDVal, (unsigned char *)&IniDataBuf.m_bCheckCD - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bCheckCD = bCheckCDVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniBound(bool bBoundVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bBoundVal, (unsigned char *)&IniDataBuf.m_bBound - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bBound = bBoundVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniProdVer(int iProdVerVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iProdVerVal, (unsigned char *)&IniDataBuf.m_iProdVer - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iProdVer = iProdVerVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniProdName(const unsigned char *lpszProdNameVal)
{
HRESULT retc=S_OK;

   if((lpszProdNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszProdNameVal, IniDataBuf.lpszProdName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszProdName, lpszProdNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniWndName(const unsigned char *lpszWndNameVal)
{
HRESULT retc=S_OK;

   if((lpszWndNameVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszWndNameVal, IniDataBuf.lpszWndName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszWndName, lpszWndNameVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniPublisher(const unsigned char *lpszPublisherVal)
{
HRESULT retc=S_OK;

   if((lpszPublisherVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszPublisherVal, IniDataBuf.m_lpszPublisher - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszPublisher, lpszPublisherVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniRegURL(const unsigned char *lpszRegURLVal)
{
HRESULT retc=S_OK;

   if((lpszRegURLVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszRegURLVal, IniDataBuf.m_lpszRegURL - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszRegURL, lpszRegURLVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniRezVar(const unsigned char *lpszRezVarVal)
{
HRESULT retc=S_OK;

   if((lpszRezVarVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszRezVarVal, IniDataBuf.m_lpszRezVar - (unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.m_lpszRezVar, lpszRezVarVal);
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniKumul(bool bKumulVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bKumulVal, (unsigned char *)&IniDataBuf.m_bKumul - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bKumul = bKumulVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniShuffCnt(int iShuffCntVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iShuffCntVal, (unsigned char *)&IniDataBuf.m_iShuffCnt - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iShuffCnt = iShuffCntVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniAttOff(long lAttOffVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&lAttOffVal, (unsigned char *)&IniDataBuf.m_lAttOff - (unsigned char *)&IniDataBuf, sizeof(long));
#else
      m_Ini.m_lAttOff = lAttOffVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniAttExt(const unsigned char *lpszAttExtVal)
{
HRESULT retc=S_OK;

   if((lpszAttExtVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszAttExtVal, IniDataBuf.m_lpszAttExt - (unsigned char *)&IniDataBuf, KP_MAX_FTYPE_LEN+1);
#else
      strcpy(m_Ini.m_lpszAttExt, lpszAttExtVal);
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniCiDirect(bool bCiDirect)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(bCiDirect, IniDataBuf.m_bCiDirect-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bCiDirect = bCiDirect;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniFlashId(long lFlashIdVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&lFlashIdVal, (unsigned char *)&IniDataBuf.m_lFlashId-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      m_Ini.m_lFlashId=lFlashIdVal;
#endif
   }

return(retc);
}

HRESULT KpStApp::SetIniCheckFlash(bool bCheckFlashVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bCheckFlashVal, (unsigned char *)&IniDataBuf.m_bCheckFlash-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bCheckFlash=bCheckFlashVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniLicFlash(bool bLicFlashVal)
{
HRESULT retc = S_OK;

   if (SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc = SetIniElement(&bLicFlashVal, (unsigned char *)&IniDataBuf.m_bLicFlash - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bLicFlash = bLicFlashVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniNumOfLics(int iNumOfLicsVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iNumOfLicsVal, (unsigned char *)&IniDataBuf.m_iNumOfLics-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iNumOfLics=iNumOfLicsVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniTestCid(const unsigned char *lpszTestCidVal)
{
HRESULT retc=S_OK;

   if((lpszTestCidVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszTestCidVal, IniDataBuf.m_lpszTestCid-(unsigned char *)&IniDataBuf, KPST_TXTCD_CHARS_PER_VAL_TID+1);
#else
      strcpy(m_Ini.m_lpszTestCid, lpszTestCidVal);
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniIniLicID(int iIniLicIDVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iIniLicIDVal, (unsigned char *)&IniDataBuf.m_iIniLicID-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iIniLicID=iIniLicIDVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniCompIdMode(int iCompIdModeVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iCompIdModeVal, (unsigned char *)&IniDataBuf.m_iCompIdMode-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iCompIdMode=iCompIdModeVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniOnTop(bool bOnTopVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bOnTopVal, (unsigned char *)&IniDataBuf.m_bOnTop-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bOnTop=bOnTopVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniFullScr(bool bFullScrVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bFullScrVal, (unsigned char *)&IniDataBuf.m_bFullScr-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bFullScr=bFullScrVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniSubst(bool bSubstVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bSubstVal, (unsigned char *)&IniDataBuf.m_bSubst-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bSubst=bSubstVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniEboard(bool bEboardVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bEboardVal, (unsigned char *)&IniDataBuf.m_bEboard-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bEboard=bEboardVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniUserPwd(const unsigned char *lpszUserPwdVal)
{
HRESULT retc=S_OK;

   if((lpszUserPwdVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszUserPwdVal, IniDataBuf.m_lpszUserPwd-(unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(m_Ini.m_lpszUserPwd, lpszUserPwdVal);
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniAdminPwd(const unsigned char *lpszAdminPwdVal)
{
HRESULT retc=S_OK;

   if((lpszAdminPwdVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszAdminPwdVal, IniDataBuf.m_lpszAdminPwd-(unsigned char *)&IniDataBuf, TV_TAG_LEN + 1);
#else
      strcpy(m_Ini.m_lpszAdminPwd, lpszAdminPwdVal);
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniUserData(const unsigned char *lpszUserDataVal)
{
HRESULT retc=S_OK;

   if((lpszUserDataVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszUserDataVal, IniDataBuf.m_lpszUserData-(unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(m_Ini.m_lpszUserData, lpszUserDataVal);
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniClearClipBrd(bool bClearClipBrdVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bClearClipBrdVal, (unsigned char *)&IniDataBuf.m_bClearClipBrd-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bClearClipBrd=bClearClipBrdVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniUpdNum(int iUpdNumVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iUpdNumVal, (unsigned char *)&IniDataBuf.m_iUpdNum - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iUpdNum = iUpdNumVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniShowIE(bool bShowIEVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bShowIEVal, (unsigned char *)&IniDataBuf.m_bShowIE-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bShowIE=bShowIEVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniHideBkmrks(bool bHideBkmrksVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bHideBkmrksVal, (unsigned char *)&IniDataBuf.m_bHideBkmrks-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bHideBkmrks=bHideBkmrksVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniSoundMuted(bool bSoundMutedVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&bSoundMutedVal, (unsigned char *)&IniDataBuf.m_bSoundMuted-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bSoundMuted=bSoundMutedVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniTestUpdates(bool bTestUpdatesVal)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc = SetIniElement(&bTestUpdatesVal, (unsigned char *)&IniDataBuf.m_bTestUpdates - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bTestUpdates = bTestUpdatesVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniFindBut(bool bFindButVal)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc = SetIniElement(&bFindButVal, (unsigned char *)&IniDataBuf.m_bFindBut - (unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bFindBut = bFindButVal;
#endif
   }

return(retc);
}


HRESULT KpStApp::SetIniCheckSum(int iCheckSumVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iCheckSumVal, (unsigned char *)&IniDataBuf.m_iCheckSum - (unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.m_iCheckSum = iCheckSumVal;
#endif
   }

return(retc);
}


// =================================================================
HRESULT KpStApp::TestFlash(void)
{
HRESULT retc = S_OK;
unsigned char drive_path[10];
UINT drive_type;
int ii;
bool found = False;
int prod_ver;
int prod_ver_new;
long flash_id;
int num_fl;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
#if TRUE // #ifndef Logging
unsigned char out_msg[KP_MAX_FNAME_LEN+100];
#endif
bool ch_fl = False;
unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
unsigned char ini_path[KP_MAX_FNAME_LEN+1];
unsigned char ini_name[KP_MAX_FNAME_LEN+1];
unsigned char ini_type[KP_MAX_FTYPE_LEN+1];

PutLogMessage_("KpStApp::TFL() 1");

   strcpy(drive_path, "A:\\");

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc=GetIniCheckFlash(&ch_fl);

// KpMsgOutF("TestFlash() [0]: retc: %d prod_ver: %d  ch_fl: %d  found: %d", retc, prod_ver, ch_fl, found);

// Èia Audrius lauþia ipak_20071024_atmintuke.exe

   if(
      ch_fl &&
// :0041C733 807DFC00                cmp byte[ebp-04], 00
// :0041C737 7406                    je 0041C73F
      SUCCEEDED(retc)
// :0041C739 837DE400                cmp dword[ebp-1C], 000
// :0041C73D 7D05                    jge 0041C744
// :0041C73F E9E2010000              jmp 0041C926
     )
#if TRUE // #ifndef Logging
      while(
               (!found) && // False && //
// :0041C744 807DF800                cmp byte[ebp-08], 00
// :0041C748 7511                    jne 0041C75B // Íia keiÍia ß // :0041C748 EB11                    jmp 0041C75B
               (
                  (retc == KP_E_TIMEOUT) || (retc == KP_E_EXPIRED) ||
// :0041C74A 817DE413030480          cmp dword[ebp-1C], 80040313
// :0041C751 7406                    je 0041C759
                  SUCCEEDED(retc)
// :0041C753 837DE400                cmp dword[ebp-1C], 000
// :0041C757 7C02                    jl 0041C75B
               )
            )
// :0041C759 EB05                    jmp 0041C760
// :0041C75B E9C6010000              jmp 0041C926
#endif // #ifndef Logging
   {
      retc = S_OK;
// :0041C760 C745E400000000          mov dword[ebp-1C], 00000000

// PutLogMessage_("TestFlash() [1]: retc: %lx  found: %d", retc, found);

      for(ii='B' /* 'A'*/; (ii<='Z') && (!found) && SUCCEEDED(retc); ii++)
      {
PutLogMessage_("KpStApp::TFL() 2: %c", ii);
         drive_path[0]=ii;
         drive_type = GetDriveType((const char *)drive_path);

PutLogMessage_("KpStApp::TFL() 2.1");

// KP_TRACE_("TestFlash(): drive_path: [%s] drive_type: %d DRIVE_REMOVABLE: %d DRIVE_CDROM: %d", drive_path, drive_type, DRIVE_REMOVABLE, DRIVE_CDROM);

// PutLogMessage_("TestFlash() [1.5] retc: %lx drive_path: %s %d %d", retc, drive_path, drive_type, DRIVE_REMOVABLE);

         if((drive_type == DRIVE_REMOVABLE) ||
            (drive_type == DRIVE_CDROM) || // cd8 formatuotiems atmintukams
            (drive_type == DRIVE_FIXED)) // SanDisk hard disku apsimetantiems atmintukams
         {
// KpMsgOut(drive_path, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KP_TRACE("TestFlash(): diskas tinka");

// PutLogMessage_("TestFlash() [2] retc: %lx drive_path: %s", retc, drive_path);

// reikia, kad netikrintu irenginiu su neikistais diskais
            if(GetVolumeInformation((const char *)drive_path, NULL, 0, NULL, NULL, NULL, NULL, 0L))
            {
// KpMsgOut("+++", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KpMsgOut(drive_path, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

PutLogMessage_("KpStApp::TFL() 2.2");

               if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, m_lpszIniFName);
               strcpy(ini_path, drive_path);
               strcat(ini_path, ini_name);
               strcat(ini_path, ".");
               strcat(ini_path, ini_type);

// printf(">>> %s %d\n", ini_path, prod_ver);
// KpMsgOut(ini_path, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KP_TRACE_("TestFlash(): ini_path: [%s]", ini_path);

#if FALSE // #ifdef Logging
unsigned char str_buf[1000];
static unsigned char log_fname[KP_MAX_FNAME_LEN+1];
unsigned char *file_buf = NULL;
fstream out_file((char *)lpszLogFileName, ios::out | ios::ate);
out_file << "---------------------------" << endl;
PutLogDate(&out_file);
sprintf((char *)str_buf, " drive_path:%s ini_path:%s prod_ver:%05d", drive_path, ini_path, prod_ver);
EncodeText(str_buf);
out_file << '\t' << str_buf;
#endif
// PutLogMessage_("TestFlash() [3] retc: %lx ini_path: %s", retc, ini_path);
               if(SUCCEEDED(retc)) retc = LoadIniFile(ini_path, True, False);
// PutLogMessage_("TestFlash(): [4]: retc: %x KP_E_DIR_ERROR: %x KP_E_FILE_FORMAT; %x", retc, KP_E_DIR_ERROR, KP_E_FILE_FORMAT);
               if((retc == KP_E_FILE_NOT_FOUND) || (retc == KP_E_DIR_ERROR) || (retc == KP_E_FILE_FORMAT))
               {
                  retc = S_OK;
// KP_TRACE_1("TestFlash(): nerandu %s", ini_path);
               }
               else if(SUCCEEDED(retc))
               {
// PutLogMessage_("TestFlash(): radau %s", ini_path);

PutLogMessage_("KpStApp::TFL() 2.3");

                  if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver_new);
// PutLogMessage_("TestFlash() [5]: retc: %lx prod_ver: %d prod_ver_new: %d", retc, prod_ver, prod_ver_new);

#if FALSE // #ifdef Logging
sprintf((char *)str_buf, " prod_ver_new:%05d", prod_ver_new);
EncodeText(str_buf);
out_file << str_buf;
#endif
// KP_TRACE_2("TestFlash(): ProdVer: %d ProdVerNew: %d", prod_ver, prod_ver_new);

// !!! èia jautri vieta nulauþimui – galima ðità tikrinimà uþblokuoti,
// o tada pakiðti kità priregistruotà atmintukà su tinkamai pervadintu .ini
// TODO: tikrinimà if(prod_ver == prod_ver_new) reikëtø kikðti gilyn á TestFlashId_RC()
                  if((prod_ver == prod_ver_new) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc = GetIniFlashId(&flash_id);
#if FALSE // #ifdef Logging
sprintf((char *)str_buf, " flash_id:%x", flash_id);
EncodeText(str_buf);
out_file << str_buf;
#endif
// PutLogMessage_("TestFlash() [6]: retc: %lx fli: %x", retc, flash_id);

                     if(SUCCEEDED(retc))
                     {
                        retc = TestFlashId(flash_id, &found, &num_fl, drive_path[0]);
                        if(FAILED(retc)) KP_WARNING0(retc, null);
                     }
// PutLogMessage_("TestFlash() [6.1]: %x %s", retc, found?"radau":"neradau");
PutLogMessage_("KpStApp::TFL() 2.4");

#if FALSE // #ifdef Debug // #if TRUE //
// printf("<<< %s %d %lx %d %d\n", ini_path, prod_ver_new, flash_id, found, num_fl);
char str_buf[100];
sprintf(str_buf, "<<< %s %d %lx %d %d\n", ini_path, prod_ver_new, flash_id, found, num_fl);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
                  }
               }

#if FALSE // #ifdef Logging
out_file << endl;

out_file << "--------------------------->>>>" << endl;
GetLogFileName(log_fname);
if(SUCCEEDED(ReadFileContents(log_fname, &file_buf, NULL, False, False)))
{
out_file << file_buf;
KP_DELETEA(file_buf);
}
out_file << "---------------------------<<<<" << endl;
sprintf((char *)str_buf, "dir %s >> %s", drive_path, lpszLogFileName);
out_file << str_buf << endl;

out_file.close();
Sleep(500);
system((char *)str_buf);
Sleep(500);

TestFlashId(0, &found, &num_fl, drive_path[0]);
#endif
            }
         }

      } // for(ii='B' /* 'A'*/; (ii<='Z') && (!found) && SUCCEEDED(retc); ii++)
// :0041C8C0 E9ABFEFFFF              jmp 0041C770

PutLogMessage_("KpStApp::TFL() 3");

#if TRUE // #ifndef Logging
// PutLogMessage_("TestFlash() [7]: retc: %lx found: %d", retc, found);

      if(
         (!found) &&
// :0041C8C5 807DF800                cmp byte[ebp-08], 00
// :0041C8C9 7506                    jne 0041C8D1

         SUCCEEDED(retc) // FAILED(retc) //
// :0041C8CB 837DE400                cmp dword[ebp-1C], 000
// :0041C8CF 7D02                    jge 0041C8D3 // Audrius keiÍia ß // // :0041C8CF 7C02                    jl 0041C8D3
// :0041C8D1 EB4E                    jmp 0041C921
        )
      {
         strcpy(out_msg, KPST_MSG_INSERT_FLASH);
// :0041C8D3 BAC6BF4600              mov edx, 0046BFC6
// :0041C8D8 8D853CF9FFFF            lea eax, dword[ebp+FFFFF93C]
// :0041C8DE E8B2B80000              call 00428195
         strcat(out_msg, prod_name);
// :0041C8E3 8D95BCFDFFFF            lea edx, dword[ebp+FFFFFDBC]
// :0041C8E9 8D853CF9FFFF            lea eax, dword[ebp+FFFFF93C]
// :0041C8EF E8B3B90000              call 004282A7
         strcat(out_msg, KPST_MSG_INSERT_FLASH_1);
// :0041C8F4 BAE8BF4600              mov edx, 0046BFE8
// :0041C8F9 8D853CF9FFFF            lea eax, dword[ebp+FFFFF93C]
// :0041C8FF E8A3B90000              call 004282A7

         retc=KpMsgOut(out_msg, IDI_ERROR, (DialogLang==KP_LNG_LIT)?KP_MB_GERAI_ATSAUKTI:KP_MB_OK_CANCEL, KPST_CHK_SER_FLASH_TIMEOUT);
// :0041C904 B988130000              mov ecx, 00001388
// :0041C909 BB05000000              mov ebx, 00000005
// :0041C90E BA017F0000              mov edx, 00007F01
// :0041C913 8D853CF9FFFF            lea eax, dword[ebp+FFFFF93C]
// :0041C919 E878DE0000              call 0042A796
// :0041C91E 8945E4                  mov dword[ebp-1C], eax
      }

#endif // #ifndef Logging

   } // while((!found) && SUCCEEDED(retc))
// :0041C921 E91EFEFFFF              jmp 0041C744

PutLogMessage_("KpStApp::TFL() 4");

   if(found && SUCCEEDED(retc))
   {
      strcpy(m_lpszFlashDevName, drive_path);
      m_lpszFlashDevName[2] = Nul; // nukandam '\\' gale
      retc = SetPdfPar(JS_FLASH_DEV_PAR_NAME, m_lpszFlashDevName);

// ext. vieweriø reikia visiems projektams, ne tik atmintukiniams
//    if(SUCCEEDED(retc)) retc = InitExtViewers();
   }

// if(FAILED(retc)) PutLogMessage_("www %lx", retc); // if(FAILED(retc)) KP_WARNING(retc, "www"); // !!!!!!
   if((retc == KP_E_TIMEOUT) || (retc == KP_E_EXPIRED)) retc = S_OK;

PutLogMessage_("KpStApp::TFL() 5");

return(retc);
// :0041C926 8B45E4                  mov eax, dword[ebp-1C]

}
// :0041C929 89EC                    mov esp, ebp
// :0041C92B 5D                      pop ebp
// :0041C92C 5F                      pop edi
// :0041C92D 5E                      pop esi
// :0041C92E 5A                      pop edx
// :0041C92F 59                      pop ecx
// :0041C930 5B                      pop ebx
// :0041C931 C3                      ret


//==============================================
LicStatus::LicStatus()
{
   m_iLicState=KpstLicFree;
// m_lpszHost[0]=Nul;
   m_Host.S_un.S_addr=INADDR_NONE;
   m_iSessionID=0;
   m_iSecondsToKill=0;
}


// ---------------------------------------------
HRESULT KpStApp::CheckLicSvr(int iTimerId)
{
HRESULT retc=S_OK;
int num_of_lics=0;

   if((iTimerId == m_iLicManagTimer) && (m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics);
      if(num_of_lics<0) num_of_lics = 0;

      if((num_of_lics>0) && SUCCEEDED(retc))
      {
//       retc=CheckReg(m_hInstance);
         retc=SendCodeHttp(S_OK, KPST_HTTP_REGISTER, True);
         if(FAILED(retc))
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


//==============================================
HRESULT KpStApp::GetIniPwdRC(unsigned char *lpszPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
      retc = GetIniElementIfNotStopped(lpszPwdBuf, IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf, TV_TAG_LEN);
#else
      strcpy(lpszPwdBuf, m_Ini.m_lpszPwd);
#endif
   }

return(retc);
}


//==============================================
int ChSum(long lVal)
{
long ch_sum;
long cur_val;
int ii;

   cur_val = lVal;
   ch_sum = 0;

   for(ii = 1; ii <= MAX_LONG_DIGITS; ii++)
   {
      ch_sum = ch_sum + (cur_val % 10) * ii;
      cur_val = cur_val / 10;
   }

return(ch_sum % 10);
}

int ChSum(const unsigned char *lpszString)
{
long ch_sum;
int ii;
const unsigned char *pnts = NULL;

   ch_sum = 0;
   ii = 1;

   if(lpszString)
   {
      pnts = lpszString;
      while(*pnts) ch_sum += ((*pnts++) * (ii++)) % 10;
   }

return(ch_sum % 10);
}


// =================================================================
HRESULT InitResumeRestDays_RC(void * /* pKpStAppObjPtr */, bool bForceAdmin, bool bLoadSaved, bool bRestMinsCalculated)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &(app_ptr->m_lRestMinutes);

   if(cMemBank[KP11_REST_DAYS_INIT/2])
   {
      KP_ASSERT(app_ptr, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
      {
//       retc = KP_E_KWD_NOT_FOUND;
         if(bLoadSaved) retc = app_ptr->LoadRegDatRestDaysInit();
PutLogMessage_("IRRDRC() 1: %d %d %d", bForceAdmin, bLoadSaved, bRestMinsCalculated);
         if(((!bLoadSaved) || (retc == KP_E_KWD_NOT_FOUND)) && (!bRestMinsCalculated)) // iðkvieèiamas tik kai KP11_REST_DAYS ið tikro buvo atnaujintas
         {
// dar nieko neáraðyta – pirmas kartas, inicializuojam minuèiø skaitiklá
            *rest_mins_ptr = (long)(cMemBank[KP11_REST_DAYS_INIT/2]) * KPST_MINS_PER_DAY; // esam hp11 viduje, kintamuosius skaitom tiesiai
PutLogMessage_("IRRDRC() 2: l_h: %d r_d_i: %d r_m: %d", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_REST_DAYS_INIT/2], cMemBank[KP11_REST_MINS/2]);
            retc = S_OK;
#if FALSE
            if(*rest_mins_ptr <= (long)KPST_MINS_PER_DAY * KPST_REST_DAYS_WARNING)
            {
               PostThreadMessage(iKpMainThread, WM_COMMAND, KPST_ID_REST_DAYS_EXCEEDED, *rest_mins_ptr / KPST_MINS_PER_DAY);
// KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, KPST_ID_REST_DAYS_EXCEEDED);
            }
#endif
         }

         if(*rest_mins_ptr <= 0L)
         {
// KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, KPST_ID_REST_DAYS_EXCEEDED);
            retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
// nereikia – tada nespëja pagauti KPST_ID_REST_DAYS_EXCEEDED praneðimo – WM_QUIT suvalgo EmuTt::WaitForRemoteCallCompletion()
// //       PostQuitMessage(IDABORT);
//          PostThreadMessage(iKpMainThread, WM_QUIT, IDABORT, 0L);

            cMemBank[KP11_BLOCK_TERM/2] = 1;
         }
      }

   /* if(SUCCEEDED(retc)) retc = */ app_ptr->SaveRegDatRestDaysInit(bForceAdmin);

      if(SUCCEEDED(retc))
//       if(!bForceAdmin) // registratoriui gal nereikëtø?
            retc = app_ptr->SetRestMinsTimer();

   } // if(cMemBank[KP11_REST_DAYS_INIT/2])
   else
      cMemBank[KP11_BLOCK_TERM/2] = 0;

PutLogMessage_("IRRDRC(): l_h: %d l_l_h: %d r_d_i: %d r_m: %ld retc: %x", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_LICID/2], cMemBank[KP11_REST_DAYS_INIT/2], *rest_mins_ptr, retc);
return(retc);
}


HRESULT InitRestDays_RC(void *pKpStAppObjPtr)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &(app_ptr->m_lRestMinutes);

// PutLogMessage_("IRDRC()");
   if(cMemBank[KP11_REST_DAYS_INIT/2])
   {
      KP_ASSERT(app_ptr, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);

#if FALSE   // inicializavimo nëra – inicializuojama visada tik pirmà kartà – kai slapto failo dar nëra,
            // po to bet kuri inicializacija – tik eilinis pratæsimas, kai imamas maþiausias ið turimø likæs galiojimo laikas
      if(SUCCEEDED(retc)) *rest_mins_ptr = (long)(cMemBank[KP11_REST_DAYS_INIT/2]) * KPST_MINS_PER_DAY; // esam hp11 viduje, kintamuosius skaitom tiesiai

      if(SUCCEEDED(retc)) retc = app_ptr->SaveRegDatRestDaysInit(True);

      if(SUCCEEDED(retc)) retc = app_ptr->SetRestMinsTimer(); // gal ir nereikëtø – starterio programa èia ðiaip jau nepapuola

// PutLogMessage_("InitRestDays_RC(): lic_high: %d rest_days: %d", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_REST_DAYS_INIT/2]);

#else

// PutLogMessage_("IRDRC() %x", retc);
      if(SUCCEEDED(retc)) retc = InitResumeRestDays_RC(pKpStAppObjPtr, False /* True */, False); // lentyniniai produktai aktyvuojasi ne adminais

#endif

   } // if(cMemBank[KP11_REST_DAYS_INIT/2])
   else
      cMemBank[KP11_BLOCK_TERM/2] = 0;

return(retc);
}


HRESULT ResumeRestDays_RC(void *pKpStAppObjPtr)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //

   if(cMemBank[KP11_REST_DAYS_INIT/2])
   {
      KP_ASSERT(app_ptr, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = InitResumeRestDays_RC(pKpStAppObjPtr, False, True);

   } // if(cMemBank[KP11_REST_DAYS_INIT/2])
   else
      cMemBank[KP11_BLOCK_TERM/2] = 0;

PutLogMessage_("ResumeRestDays_RC(): lic_high: %d lic_low_hash: %d  rest_days: %d", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_LICID/2], cMemBank[KP11_REST_DAYS_INIT/2]);
return(retc);
}


HRESULT ResetRestDays_RC(void *pKpStAppObjPtr)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &(app_ptr->m_lRestMinutes);

   if(cMemBank[KP11_REST_DAYS_INIT/2])
   {
      KP_ASSERT(app_ptr, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) *rest_mins_ptr = 0L; // esam hp11 viduje, kintamuosius skaitom tiesiai

#if FALSE   // inicializavimo nëra – inicializuojama visada tik pirmà kartà – kai slapto failo dar nëra,
            // po to bet kuri inicializacija – tik eilinis pratæsimas, kai imamas maþiausias ið turimø likæs galiojimo laikas
      if(SUCCEEDED(retc)) retc = app_ptr->SaveRegDatRestDaysInit(True);

      if(SUCCEEDED(retc)) retc = app_ptr->SetRestMinsTimer(); // gal ir nereikëtø – starterio programa èia ðiaip jau nepapuola

#else
// PutLogMessage_("RRDRC() 1: l_h: %d r_d_i: %d r_m: %d", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_REST_DAYS_INIT/2], cMemBank[KP11_REST_MINS/2]);
      if(SUCCEEDED(retc)) retc = InitResumeRestDays_RC(pKpStAppObjPtr, False /* True */, // lentyniniai produktai aktyvuojasi ne adminais
                                                                              False, True);
PutLogMessage_("RRDRC() 2: l_h: %d r_d_i: %d r_m: %d", cMemBank[KP11_LIC_HIGH/2], cMemBank[KP11_REST_DAYS_INIT/2], cMemBank[KP11_REST_MINS/2]);
#endif

   } // if(cMemBank[KP11_REST_DAYS_INIT/2])
   else
      cMemBank[KP11_BLOCK_TERM/2] = 0;

return(retc);
}


HRESULT ProcessRestDays_RC(void * /* pKpStAppObjPtr */)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
long *rest_mins_ptr = (long *)(cMemBank + KP11_REST_MINS / 2); // &(app_ptr->m_lRestMinutes);

   if(cMemBank[KP11_REST_DAYS_INIT/2])
   {
      KP_ASSERT(app_ptr, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT(((long)(cMemBank)) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(((long)rest_mins_ptr) % 4 == 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(KP11_REST_MINS % 4 == 0, KP_E_SYSTEM_ERROR, null, True);

PutLogMessage_("PRDRC() 1: l_h: %d r_d_i: %d r_m: %ld", cMemBank[KP11_LIC_HIGH/2] /* lic_high */, cMemBank[KP11_REST_DAYS_INIT/2] /* rest_days_init */, *rest_mins_ptr /* rest_mins */);
      if(SUCCEEDED(retc)) (*rest_mins_ptr)--;
PutLogMessage_("PRDRC() 2: l_h: %d r_d_i: %d r_m: %ld", cMemBank[KP11_LIC_HIGH/2] /* lic_high */, cMemBank[KP11_REST_DAYS_INIT/2] /* rest_days_init */, *rest_mins_ptr /* rest_mins */);
      if(SUCCEEDED(retc)) retc = app_ptr->SaveRegDatRestDaysInit(False);
PutLogMessage_("PRDRC() 3: l_h: %d r_d_i: %d r_m: %ld", cMemBank[KP11_LIC_HIGH/2] /* lic_high */, cMemBank[KP11_REST_DAYS_INIT/2] /* rest_days_init */, *rest_mins_ptr /* rest_mins */);

      if(SUCCEEDED(retc)) if(*rest_mins_ptr <= 0L)
      {
//       retc = EmuTv.SetHp11Variable(1, KP11_BLOCK_TERM); // negalima – mes jau HP11 viduj
         cMemBank[KP11_BLOCK_TERM/2] = 1;

//       PostThreadMessage(iKpMainThread, WM_COMMAND, KPST_ID_REST_DAYS_EXCEEDED, *rest_mins_ptr / KPST_MINS_PER_DAY);
         retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
      }

   } // if(cMemBank[KP11_REST_DAYS_INIT/2])

PutLogMessage_("PRDRC(): l_h: %d r_d_i: %d r_m: %ld", cMemBank[KP11_LIC_HIGH/2] /* lic_high */, cMemBank[KP11_REST_DAYS_INIT/2] /* rest_days_init */, *rest_mins_ptr /* rest_mins */);
return(retc);
}


// TODO !!!!
// dekrementuoti supporto galiojimo laikà
// http://www.tev.lt/prodcheck.php?code=8R34-GR52-5U2U
// gràþina skaièiukà – likusá supporto galiojimo laikà
// jei pasibaigë – gràþina 0
// jei supportas begalinis – gràþina klaidà (tipo, „operacija duotai licencijai nepritaikoma“)


// ------------------------------------------------------
bool bSertRegistered = False;

HRESULT RegSert_RC(void * /* pKpStAppObjPtr */)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
unsigned char pwd_wnd[KP_MAX_FNAME_LEN + 1];
unsigned char pwd[TV_TAG_LEN + 1];
unsigned char cert_fname[TV_TAG_LEN + 1];
unsigned char cmd_buf[KP_MAX_FNAME_LEN + TV_TAG_LEN * 2 + 1];

   if(app_ptr == NULL) retc = E_POINTER;

// PutLogMessage_("RSRC");

#ifdef KPST_MOVE_TO_KPHP11
   strcpy(pwd_wnd, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszPwdWndName - (unsigned char *)&IniDataBuf);
   strcpy(pwd, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf);
   strcpy(cert_fname, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszOldPwd - (unsigned char *)&IniDataBuf);
#else
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniPwdWndName(pwd_wnd);
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniPwd(pwd);
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniOldPwd(cert_fname);
#endif

   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(pwd_wnd);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(pwd);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(cert_fname);

   if((!bSertRegistered) && (pwd_wnd[0] == Nul) && (pwd[0] != Nul) && (cert_fname[0] != Nul) && SUCCEEDED(retc))
   {
// importpfx -f tadas.pfx -p 123456 -t USER -s MY
unsigned char *pntd = cmd_buf;
//    strcpy(cmd_buf, "importpfx -f ");
      *pntd++ = 'i';
      *pntd++ = 'm';
      *pntd++ = 'p';
      *pntd++ = 'o';
      *pntd++ = 'r';
      *pntd++ = 't';
      *pntd++ = 'p';
      *pntd++ = 'f';
      *pntd++ = 'x';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 'f';
      *pntd++ = ' ';

      strcpy(pntd, cert_fname);
      pntd += strlen(pntd);

//    strcat(cmd_buf, ".pfx -p ");
      *pntd++ = '.';
      *pntd++ = 'p';
      *pntd++ = 'f';
      *pntd++ = 'x';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 'p';
      *pntd++ = ' ';

      strcpy(pntd, pwd);
      strcat(cmd_buf, " -t USER -s MY");

      retc = StartProcess(cmd_buf, KPST_CUR_DIR, NULL, NULL, SW_SHOWMINIMIZED);

      bSertRegistered = True;
   }

return(retc);
}


HRESULT UnRegSert_RC(void * /* pKpStAppObjPtr */)
{
HRESULT retc = S_OK;
KpStApp *app_ptr = theKpStAppPtr; // (KpStApp *)pKpStAppObjPtr; //
unsigned char pwd_wnd[KP_MAX_FNAME_LEN + 1];
unsigned char pwd[TV_TAG_LEN + 1];
unsigned char cert_fname[TV_TAG_LEN + 1];
unsigned char cmd_buf[KP_MAX_FNAME_LEN + TV_TAG_LEN * 2 + 1];

   if(app_ptr == NULL) retc = E_POINTER;

// PutLogMessage_("URSRC");

#ifdef KPST_MOVE_TO_KPHP11
   strcpy(pwd_wnd, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszPwdWndName - (unsigned char *)&IniDataBuf);
   strcpy(pwd, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf);
   strcpy(cert_fname, (unsigned char *)(cMemBank + HP11_RC_INI_BUF / 2) + IniDataBuf.m_lpszOldPwd - (unsigned char *)&IniDataBuf);
#else
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniPwdWndName(pwd_wnd);
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniPwd(pwd);
   if(SUCCEEDED(retc)) retc = app_ptr->GetIniOldPwd(cert_fname);
#endif

   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(pwd_wnd);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(pwd);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(cert_fname);

   if(/* (!bSertRegistered) && */ (pwd_wnd[0] == Nul) && (pwd[0] != Nul) && (cert_fname[0] != Nul) && SUCCEEDED(retc))
   {
// certmgr.exe -del -c -s my -n "Tadas"
unsigned char *pntd = cmd_buf;
//    strcpy(cmd_buf, "certmgr.exe -del -c -s my -n \"");
      *pntd++ = 'c';
      *pntd++ = 'e';
      *pntd++ = 'r';
      *pntd++ = 't';
      *pntd++ = 'm';
      *pntd++ = 'g';
      *pntd++ = 'r';
      *pntd++ = '.';
      *pntd++ = 'e';
      *pntd++ = 'x';
      *pntd++ = 'e';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 'd';
      *pntd++ = 'e';
      *pntd++ = 'l';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 'c';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 's';
      *pntd++ = ' ';
      *pntd++ = 'm';
      *pntd++ = 'y';
      *pntd++ = ' ';
      *pntd++ = '-';
      *pntd++ = 'n';
      *pntd++ = ' ';
      *pntd++ = '\"';

      strcpy(pntd, cert_fname);
      strcat(cmd_buf, "\"");

      retc = StartProcess(cmd_buf, KPST_CUR_DIR, NULL, NULL, SW_SHOWMINIMIZED);

      bSertRegistered = True;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::ScanLicTmp(long *piLicID, int *piProdVer, const unsigned char *lpszLicCode)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

int lic_code1_sav = 0;
int lic_code2_sav = 0;
int lic_code3_sav = 0;
int lic_high_sav = 0;

// --------------------- lpszLicCode[] perkopijuojam á darbiná buferá
unsigned char code_buf[KPST_NUM_OF_LIC_CHARS + 1];
   KP_ASSERT(lpszLicCode != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszLicCode) <= KPST_NUM_OF_LIC_CHARS, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(code_buf, lpszLicCode);

// --------------------- atsimenam buvusias reikðmes
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_code1_sav, KP11_LIC_CODE1);
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_code2_sav, KP11_LIC_CODE2);
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_code3_sav, KP11_LIC_CODE3);
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high_sav, KP11_LIC_HIGH);

   if(SUCCEEDED(retc))
   {
int lic_high_chsum = 0;
      if(SUCCEEDED(retc)) retc = ExtractHigh(code_buf, &lic_high_chsum, 12);
      if(SUCCEEDED(retc))
      {
         retc = SaveLicHighHp11(lic_high_chsum); // iðsaugojam á KP11_LIC_HIGH su ChSum patikrinimu
         if(FAILED(retc)) KP_ERROR(retc, null);
      }

// --------------------- skanuojam LicCode á KP11_LIC_CODE* (m_iLicCode*)
      if(SUCCEEDED(retc)) retc = ScanLic(code_buf);

// --------------------- iðtraukiam kodà be LicHigh
static KpRcPars rc_pars;

      rc_pars.iOpCode = KP_RC_UNPACK_LIC_TMP;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.value = 0;

// PutLogMessage_("KpStApp::SLT ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

      if((piLicID != NULL) && SUCCEEDED(retc)) *piLicID =
         ((lic_high_chsum << 8) & 0xFFFF0000) | // LicHigh be ChSum lipdom á vyresná rezultato þodá (8 bitai LicHigh ir 4 bitai ChSum = 12 bitø)
         ((rc_pars.value >> 16) & 0xFFFF); // LicID be LicHigh – vyresniajame gràþinamo rc_pars.value þodyje
      if((piProdVer != NULL) && SUCCEEDED(retc)) *piProdVer = rc_pars.value & 0xFFFF; // ProdVer – jaunesniajame gràþinamo rc_pars.value þodyje

// --------------------- atstatom buvusias reikðmes
      if(SUCCEEDED(retc0)) retc0 = EmuTv.SetHp11Variable(lic_code1_sav, KP11_LIC_CODE1);
      if(SUCCEEDED(retc0)) retc0 = EmuTv.SetHp11Variable(lic_code2_sav, KP11_LIC_CODE2);
      if(SUCCEEDED(retc0)) retc0 = EmuTv.SetHp11Variable(lic_code3_sav, KP11_LIC_CODE3);
      if(SUCCEEDED(retc0)) retc0 = EmuTv.SetHp11Variable(lic_high_sav, KP11_LIC_HIGH);
      if(SUCCEEDED(retc)) retc = retc0;

   } // if(SUCCEEDED(retc))

return(retc);
}
