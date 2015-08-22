// ---------------------------
// kpstapr.cpp
// common application for program starters
// install key & Co - secret part
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"

#include <time.h>
#include <fstream>

// #if ((CompilerGr==Msvc) && (Envir!=MSWin32Mfc))
#if (CompilerGr==Msvc)
#include <WINSOCK2.H>
#endif
#include <windows.h>
#include <richedit.h>
#include <winsock.h>
#include <mmsystem.h>
#include <direct.h>
#include <ctype.h>
#include <stdio.h>
#include <string>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpstdio.h"

#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "kpstmsg.h"
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

// #define KPST_CNT_REG_PATH_1 m_CntRegPath1 ("C:\\Program Files\\Common Files\\Adobe\\LocalData") // ("C:\\RegisteredPackages") // ("C:\\Temp") // ("C:\\Documents and Settings") // "C:\\WINNT" //
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
   m_CntRegPath1[30]='A';
   m_CntRegPath1[31]='d';
   m_CntRegPath1[32]='o';
   m_CntRegPath1[33]='b';
   m_CntRegPath1[34]='e';
   m_CntRegPath1[35]='\\';
   m_CntRegPath1[36]='L';
   m_CntRegPath1[37]='o';
   m_CntRegPath1[38]='c';
   m_CntRegPath1[39]='a';
   m_CntRegPath1[40]='l';
   m_CntRegPath1[41]='D';
   m_CntRegPath1[42]='a';
   m_CntRegPath1[43]='t';
   m_CntRegPath1[44]='a';
   m_CntRegPath1[45]=Nul;

// #define KPST_CNT_REG_PATH_2 ("\\Descriptors") // ("") // ("\\ ") // ("\\All Users") //
   m_CntRegPath2[ 0]='\\';
   m_CntRegPath2[ 1]='D';
   m_CntRegPath2[ 2]='e';
   m_CntRegPath2[ 3]='s';
   m_CntRegPath2[ 4]='c';
   m_CntRegPath2[ 5]='r';
   m_CntRegPath2[ 6]='i';
   m_CntRegPath2[ 7]='p';
   m_CntRegPath2[ 8]='t';
   m_CntRegPath2[ 9]='o';
   m_CntRegPath2[10]='r';
   m_CntRegPath2[11]='s';
   m_CntRegPath2[12]=Nul;
}


// ------------------------------
int NormalizeCompId(long lValue)
{
int ret_val=0;
long in_val=lValue;
int signif;

// ---------------------------
// in_val=(in_val & 0xFFFF) + (in_val >> 16);

   signif=0x10000/10;
   in_val=(in_val % signif) + (in_val / signif);

// ret_val=((in_val*10) /* + m_iInstCount */) & 0xFFFF;
   ret_val=((in_val*10) /* + m_iInstCount */) % 65530;


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
#ifdef Debug
unsigned char out_str[100];
sprintf((char *)out_str, "comp_id: %d", ret_val);
KP_TRACE(out_str);
#endif

   if(ret_val==0) ret_val=1;

#ifdef Debug
#ifdef DebugStop
unsigned char str_buf[100];
sprintf((char *)str_buf, "GetPhysCID galas cid:%d", ret_val);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

return(ret_val);
}


// ------------------------------
HRESULT KpStApp::GetPhysCompId(void)
{
HRESULT retc=S_OK;
bool ci_direct=False;
long cur_comp_id = 0;
long new_comp_id=0; // cumulated
int comp_id=0;
int comp_id_mode = 0;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetPhysCID pradzia", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// KpMsgOut("###", IDI_ASTERISK, KP_MB_TESTI);

// ------------------------
   if(SUCCEEDED(retc)) retc = GetIniCompIdMode(&comp_id_mode);

// --------------------------- BIOS Date
   if((comp_id_mode & KPST_COMPID_BIOS_DATE) && SUCCEEDED(retc))
   {
#if TRUE // #if FALSE //
unsigned char dat_buf[BIOS_DAT_SIZE+1];
unsigned char *pntd;

      if(SUCCEEDED(retc)) retc=GetBIOSDate(dat_buf);
      if(SUCCEEDED(retc))
      {
// KpMsgOut(dat_buf, KP_MB_TESTI);
#ifdef Logging
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
#ifdef Logging
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

      if(SUCCEEDED(retc)) retc=GetDiskInfo((unsigned char *)"C:\\", &cur_comp_id, disk_label_buf);

      if(SUCCEEDED(retc)) new_comp_id += cur_comp_id;
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

      if(SUCCEEDED(retc)) new_comp_id += cur_comp_id;

   } // if((comp_id_mode & KPST_COMPID_DISK_ID) && SUCCEEDED(retc))


// ---------------------------
#if FALSE // #if TRUE //
   if(SUCCEEDED(retc)) retc=GetIniCiDirect(&ci_direct);
   if(SUCCEEDED(retc))
   {
#ifndef AllwaysCid
      if(ci_direct)
#endif
         new_comp_id = getHardDriveComputerID();
#ifndef AllwaysCid
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_NOTINST, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }
#endif



// if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID); // negalima - mes jau RC threade
   comp_id = cMemBank[KP11_COMPID/2];

   if(SUCCEEDED(retc))
   {
      new_comp_id=NormalizeCompId(new_comp_id);
#ifdef Logging
char buf[50];
sprintf(buf, "dcidn: %d", new_comp_id);
KP_TRACE(buf);
#endif
      if(new_comp_id > comp_id /* m_iCompId */)
      {
//       m_iCompId=new_comp_id;
//       retc=EmuTv.SetHp11Variable(new_comp_id, KP11_COMPID);
         cMemBank[KP11_COMPID/2] = (short)new_comp_id;
      }
   }
#ifdef Logging
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
char szBiosDate[80+1];
DWORD dwBufLen;
#endif
unsigned char key_name[KP_MAX_FNAME_LEN+1];

   strcpy(lpszDatBuf, "XXXX.XX.XX");

#if (Envir==MSDos) || (Envir==MSDosCon)

   strncpy(str_buf, (char *)0xffff5, 8);
   str_buf[8]=0;
   PackBIOSDate(lpszDatBuf, str_buf);

#elif (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)

   if(SUCCEEDED(retc)) win_ver=iWindowsVersion;

   if(SUCCEEDED(retc))
   {
      if(win_ver < WinNT)
      {
         strncpy(str_buf, (char *)0xffff5, 8);
         str_buf[8]=0;
         PackBIOSDate(lpszDatBuf, str_buf);
      }
      else
      {
//       strcpy(key_name, "HARDWARE\\DESCRIPTION\\System");
         key_name[0]='H';
         key_name[1]='A';
         key_name[2]='R';
         key_name[3]='D';
         key_name[4]='W';
         key_name[5]='A';
         key_name[6]='R';
         key_name[7]='E';
         key_name[8]='\\';
         key_name[9]='D';
         key_name[10]='E';
         key_name[11]='S';
         key_name[12]='C';
         key_name[13]='R';
         key_name[14]='I';
         key_name[15]='P';
         key_name[16]='T';
         key_name[17]='I';
         key_name[18]='O';
         key_name[19]='N';
         key_name[20]='\\';
         key_name[21]='S';
         key_name[22]='y';
         key_name[23]='s';
         key_name[24]='t';
         key_name[25]='e';
         key_name[26]='m';
         key_name[27]=Nul;

         retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
         if(retw!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
         {
            dwBufLen=80;

//          strcpy(key_name, "SystemBiosDate");
            key_name[0]='S';
            key_name[1]='y';
            key_name[2]='s';
            key_name[3]='t';
            key_name[4]='e';
            key_name[5]='m';
            key_name[6]='B';
            key_name[7]='i';
            key_name[8]='o';
            key_name[9]='s';
            key_name[10]='D';
            key_name[11]='a';
            key_name[12]='t';
            key_name[13]='e';
            key_name[14]=Nul;

            retw=RegQueryValueEx(hKey, (const char *)key_name, NULL, NULL, (LPBYTE) szBiosDate, &dwBufLen);
            if(retw==ERROR_SUCCESS) szBiosDate[dwBufLen]=Nul;
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
         if(hKey)
         {
            retw=RegCloseKey(hKey);
//          if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            hKey=NULL;
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




   sprintf((char *)str_buf, "ebp: %x bp: %x ss: %x ss:bp: %x", r_ebp, r_bp, r_ss, (r_ss<<8)+r_bp);
   KpMsgOut(str_buf, KP_MB_TESTI);



   sprintf((char *)str_buf, "ser_no: %d", MediaID.main.midSerialNum);
   KpMsgOut(str_buf, KP_MB_TESTI);

   strncpy(str_buf, MediaID.main.midVolLabel, 11);
   str_buf[11]=Nul;
   KpMsgOut(str_buf, KP_MB_TESTI);


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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_INC_COMPID;
   rc_pars.iParBlSize=sizeof(rc_pars);
   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::CreateRegPath(SYSTEMTIME *p_TtPtr /* *p_StPtr */)
{
HRESULT retc=S_OK;
HRESULT retcf=S_OK;
HRESULT retc0=S_OK;
// MSWin32Version win_vers;
// int sp;
// int max_day;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name_tmp[KP_MAX_FILE_LIN_WDT+1];


   if((p_TtPtr /* p_StPtr */==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, GetLastError(), True, __FILE__, __LINE__, 0L, NULL  );

   if(SUCCEEDED(retc))
   {
// =====================================
#if FALSE
// ------------------------- remember current system time
      GetSystemTime(p_StPtr);
//    GetLocalTime(p_StPtr);

      win_vers=iWindowsVersion;

      if((win_vers==Win98c) || (win_vers==Win98) || (win_vers==Win98SE))
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

// ============================================
      strcpy(key_name, KPST_CNT_REG_PATH_1);

      strcpy(key_name_tmp, key_name);
      strcat(key_name_tmp, KPST_CNT_REG_PATH_2);
      strcat(key_name_tmp, "\\");
      retcf=CreatePath(key_name_tmp);
//    if(SUCCEEDED(retcf))
//    if(!_mkdir((const char *)key_name))
//    {
         retc0=ChFileTimeCrtd(key_name, p_TtPtr);
//       if(SUCCEEDED(retcf)) retcf=retc0;
//       if(SUCCEEDED(retc)) retc=retc0;
//    }
      strcat(key_name, KPST_CNT_REG_PATH_2);
//    if(SUCCEEDED(retcf))
//    {
//       if(!_mkdir((const char *)key_name))
//       {
            retc0=ChFileTimeCrtd(key_name, p_TtPtr);
//          if(SUCCEEDED(retcf)) retc=retc0;
//          if(SUCCEEDED(retc)) retc=retc0;
//       }
//    }


#if FALSE
      if(bForceAdmin && SUCCEEDED(retcf))
      {
//       !!!! TODO
         DWORD SetNamedSecurityInfo(
            (char *)key_name, // LPTSTR pObjectName,
            SE_FILE_OBJECT,   // SE_OBJECT_TYPE ObjectType,
            DACL_SECURITY_INFORMATION, // SECURITY_INFORMATION SecurityInfo,
            NULL,             // PSID psidOwner,
            NULL,             // PSID psidGroup,
            PACL pDacl,       // PACL pDacl,
            NULL              // PACL pSacl
            );

         retcf=KP_E_DIR_ERROR;
         KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
         if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
         if(SUCCEEDED(retc)) retc=retcf;
      }
#endif

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetRegCompID(HKEY hQueryKey, const unsigned char *lpszSubKey, int iProdVer, int *piIdOut)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY res_key=0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwBufLen;
DWORD dwValType;

   if(((lpszSubKey==NULL) || (piIdOut==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      retw=RegOpenKeyEx(hQueryKey,
         (LPCTSTR)lpszSubKey,
         0, KEY_QUERY_VALUE, &res_key);
      if(retw!=ERROR_SUCCESS)
      {
         retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
//       KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }
   }

// --------------------
   if(SUCCEEDED(retc))
   {
      *piIdOut=0;

      key_buf[0]=Nul;

      dwBufLen=KP_MAX_FILE_LIN_WDT;
      retw=RegQueryValueEx(res_key,
         "EstDispl",
         NULL, &dwValType,
         (LPBYTE)key_buf, &dwBufLen);
      if(retw==ERROR_SUCCESS) key_buf[dwBufLen]=Nul;
      else
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         retc=S_OK;
      }
   }

   if(SUCCEEDED(retc))
   {
#ifdef Logging
char buf[100];
sprintf(buf, "rcid: %s", key_buf);
KP_TRACE(buf);
#endif
      sscanf((const char *)key_buf, "%x", piIdOut);
      *piIdOut^=iProdVer;
      *piIdOut/=10;
#ifdef Logging
sprintf(buf, "rcidn: %d", *piIdOut);
KP_TRACE(buf);
#endif
   }

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
HRESULT KpStApp::GetSavedCompID(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
int cnt1;
int prod_ver=0;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetSavedCID pradzia", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

#ifdef KPST_WINDOWS_INTERFACE
DWORD read;
HANDLE in_file=INVALID_HANDLE_VALUE;
#else
FILE *in_file=NULL;
#endif

int comp_id=0;

// m_iInstCount=0;
// m_iCompId=0;
// if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_COMPID);
   cMemBank[KP11_COMPID/2] = 0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "strlen(key_name): %d", strlen(key_name));
KP_TRACE(str_buf);
#endif

      retc0=GetRegCompID(HKEY_LOCAL_MACHINE, key_name, prod_ver, &cnt1);
      if(SUCCEEDED(retc0)) if(cnt1 > comp_id /* m_iCompId */) comp_id /* m_iCompId */ = cnt1;
                // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino

#ifdef Debug
#if FALSE // #if TRUE // #ifdef DebugStop
unsigned char str_buf[1000];
sprintf((char *)str_buf, "%s GetSavedCID local retc:%x cnt1:%d cid:%d", key_name, retc, cnt1, comp_id);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

      retc0=GetRegCompID(HKEY_CURRENT_USER, key_name, prod_ver, &cnt1);
      if(SUCCEEDED(retc0)) if(cnt1 > comp_id /* m_iCompId */) comp_id /* m_iCompId */=cnt1;
                // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino

#ifdef Debug
#if FALSE // #if TRUE // #ifdef DebugStop
sprintf((char *)str_buf, "%s GetSavedCID global retc:%x cnt1:%d cid:%d", key_name, retc, cnt1, comp_id);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   }

// -------------------- file
   if(SUCCEEDED(retc) || (retc==KP_E_KWD_NOT_FOUND))
   {
      retc=S_OK;

      strcpy(key_name, KPST_CNT_REG_PATH_1);
      strcat(key_name, KPST_CNT_REG_PATH_2);
      strcat((char *)key_name, "\\");
      strcat(key_name, pkg_name);
//    strcat((char *)key_name, "\\cbdata");
//    strcat(key_name, " ");

#ifdef KPST_WINDOWS_INTERFACE
      in_file=CreateFile((const char *)key_name, GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      if(in_file==INVALID_HANDLE_VALUE)
#else
      in_file=fopen((const char *)key_name, "r");
      if(in_file==NULL)
#endif
      {
//       retc=KP_E_KWD_NOT_FOUND; // KP_E_FILE_NOT_FOUND
//       KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FILE_NOT_FOUND */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
      }
      else
      {
#ifdef KPST_WINDOWS_INTERFACE
         if(!ReadFile(in_file, &cnt1, sizeof(cnt1), &read, NULL))
#else
//       fscanf(in_file, "%x", &cnt1);
         fread(&cnt1, sizeof(cnt1), 1, in_file);
         if(ferror(in_file) || feof(in_file))
#endif
         {
//          retc=KP_E_KWD_NOT_FOUND; // KP_E_FERROR
//          KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND /* KP_E_FERROR */, GetLastError(), False, __FILE__, __LINE__, 0L, &KpTraceWindow);
         }
         else
         {
            retc=S_OK;
#if FALSE // #ifdef Debug // #ifdef Logging
char buf[100];
sprintf(buf, "%s fcid: %d %x", key_name, cnt1, cnt1);
KpMsgOut(buf, IDI_ASTERISK, KP_MB_TESTI);
// KP_TRACE(buf);
#endif
            cnt1^=prod_ver;
            cnt1/=10;
#if FALSE // #ifdef Debug // #ifdef Logging
sprintf(buf, "fcidn: %d", cnt1);
KpMsgOut(buf, IDI_ASTERISK, KP_MB_TESTI);
// KP_TRACE(buf);
#endif
//          if(cnt1>m_iInstCount) m_iInstCount=cnt1;
            if(cnt1 > comp_id /* m_iCompId */) comp_id /* m_iCompId */ = cnt1;
                                                   // jei m_iCompID==0xFFFF, o cnt1=m_iCompID+1=0x0 - liks senas
                                                   // arba jei is registro perskaite senesni, o kitas vartotojas jau pajaunino
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

      } // else // if(in_file==NULL)

   } // if(SUCCEEDED(retc) || (retc==KP_E_KWD_NOT_FOUND))

#ifdef Debug
#if FALSE // #if TRUE // #ifdef DebugStop
unsigned char str_buf[100];
sprintf((char *)str_buf, "GetSavedCID galas retc:%x cid:%d", retc, comp_id);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(comp_id, KP11_COMPID);
   cMemBank[KP11_COMPID/2] = comp_id;


return(retc);
}


// ------------------------------
HRESULT GetCommonCompID_RC(void *pKpStAppObjPtr)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
bool ci_direct=False;
int num_of_lics=0;
KpStApp *this_ptr=(KpStApp *)pKpStAppObjPtr;
#ifndef AllwaysCid
int comp_id=0;
#endif

   if((pKpStAppObjPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=this_ptr->GetIniCiDirect(&ci_direct);
   if(SUCCEEDED(retc)) retc=this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
   {
      if(num_of_lics && (this_ptr->m_iKpStMode==KpStarterMode))
         retc=this_ptr->GetTimCompId();
      else
      {
#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetCommonCID pradzia", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

#if FALSE
/*       retc0= */ this_ptr->GetSavedCnt(); // if(SUCCEEDED(retc)) retc=retc0;
         retc0=this_ptr->GetCompId(); if(SUCCEEDED(retc)) retc=retc0;
#else
//       this_ptr->m_iCompId=0;
//       if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_COMPID);
         cMemBank[KP11_COMPID/2]=0;

         retc0=this_ptr->GetSavedCompID(); if(SUCCEEDED(retc)) retc=retc0;
#ifndef AllwaysCid
//       if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
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
// atnaujina m_iCompID tik jei mazesnis uz issaugota (perskaityta su GetSavedCompID())
                  retc0=this_ptr->GetPhysCompId();
                  if(SUCCEEDED(retc)) retc=retc0;
               }
#ifndef AllwaysCid
               else if(this_ptr->m_iKpStMode==KpStarterMode)
                  KpErrorProc.OutputErrorMessage(KP_E_NOTINST, null, False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
         }
         if(ci_direct) retc0=this_ptr->SaveCompID(False); if(SUCCEEDED(retc)) retc=retc0;

#endif // #else // #if FALSE

      } // else // if(num_of_lics && (this-ptr->m_iKpStMode==KpStarterMode))

   } // if(SUCCEEDED(retc))

// #ifdef Debug
// if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
// #endif
   retc=S_OK;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("GetCommonCID galas", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

#ifdef Debug
// cMemBank[KP11_COMPID/2]=1800;
#endif

return(retc);
}


// ------------------------------------------
HRESULT KpStApp::SaveRegCompID(HKEY hQueryKey, const unsigned char *lpszSubKey, int iProdVer)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY res_key=0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwDisposition;
int comp_id=0;

   if((lpszSubKey==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
   comp_id = cMemBank[KP11_COMPID/2];

   if(SUCCEEDED(retc))
   {
      retw=RegCreateKeyEx(hQueryKey, (LPCTSTR)lpszSubKey,
         0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw!=ERROR_SUCCESS)
      {
         retc=KP_E_ACCESS_DENIED;
         KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
//       KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
      }
   }

// --------------------
   if(SUCCEEDED(retc))
   {
//    sprintf((char *)key_buf, "%x", (m_iInstCount*10)^iProdVer);
      sprintf((char *)key_buf, "%x", (comp_id /* m_iCompId */ *10)^iProdVer);

      retw=RegSetValueEx(res_key,
         "EstDispl",
         0, REG_SZ,
         key_buf,
         strlen(key_buf));
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
      res_key=0;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::SaveCompID(bool bForceAdmin)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HRESULT retcf=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
int out_val;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
int prod_ver=0;
// SYSTEMTIME st;
SYSTEMTIME tt;

#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FILE_LIN_WDT+1];
int name_len;
#endif
HANDLE out_file=INVALID_HANDLE_VALUE;
DWORD written;
#else
FILE *out_file=NULL;
#endif
int comp_id=0;

// if((!bCiDirect) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

// if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
   comp_id = cMemBank[KP11_COMPID/2];

   if(SUCCEEDED(retc))
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);

// -------------------- registry
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      if(bForceAdmin || bAdminFl)
      {
         if(!bAdminFl) retc0 = KP_E_ACCESS_DENIED;
         else retc0=SaveRegCompID(HKEY_LOCAL_MACHINE, key_name, prod_ver);
         if(FAILED(retc0))
         {
            KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin)
            {
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
               if(SUCCEEDED(retc)) retc=retc0;
            }
         }
      }

      retc0=SaveRegCompID(HKEY_CURRENT_USER, key_name, prod_ver);
      if(FAILED(retc0)) KpErrorProc.OutputErrorMessage(retc0, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc=retc0;
   }

// -------------------- file

// C:\WINNT\RegisteredPackages\{A2F3B5A7-2D39-4A4E-96E6-BFADEBCBB27B}
// 319494 SQLODBC.CAB
//   7281 SQLODBC.CAT
//   1014 SQLODBC.INF

// if(SUCCEEDED(retc))
   if(bForceAdmin || bAdminFl)
   {
      retcf=S_OK;

      if(!bAdminFl) retcf = KP_E_ACCESS_DENIED;

// ---------------------------------------
      if(SUCCEEDED(retcf)) retcf=CreateRegPath(&tt /* &st */);

      if(SUCCEEDED(retcf))
      {
         strcpy(key_name, KPST_CNT_REG_PATH_1);
         strcat(key_name, KPST_CNT_REG_PATH_2);
         strcat((char *)key_name, "\\");
         strcat(key_name, pkg_name);
//       if(!_mkdir((const char *)key_name))
//       {
//          retc0=ChFileTimeCrtd(key_name, &tt);
// //       if(SUCCEEDED(retcf)) retc=retc0;
// //       if(SUCCEEDED(retc)) retc=retc0;
//       }

//       strcat((char *)key_name, "\\cbdata");
//       strcat(key_name, " ");
      }

#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
//    if(SUCCEEDED(retcf))
//    {
//       name_len=strlen(KP_WIN_UNICODE_FNAME_PREFIX);
//       retcf=KptStrEncode(key_name_i, KP_WIN_UNICODE_FNAME_PREFIX, &name_len, 1);
//       if(SUCCEEDED(retc)) retc=retcf;
//    }
      if(SUCCEEDED(retcf))
      {
         name_len=strlen(key_name);
//       retcf=KptStrEncode(key_name_i+strlen(KP_WIN_UNICODE_FNAME_PREFIX), key_name, &name_len, 1);
//       retcf=KptStrEncode(key_name_i, key_name, &name_len, 1);
         retcf=KptStrToUnicode(key_name_w, key_name, &name_len, 1);
//       if(FAILED(retcf))
//          retcf=KpErrorProc.OutputErrorMessage(retcf, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retcf;
      }
      if(SUCCEEDED(retcf))
      {
//       key_name_w[name_len++]=iaUniChars[C_A_Ogon];
         key_name_w[name_len]=C_Nul;

#if FALSE

int *pnti;
int low_byte;
int high_byte;

         pnti=key_name_i;
         while(*pnti)
         {
            low_byte=(*pnti & 0xFF);
            high_byte=(((*pnti)>>16) & 0xFF);
            *pnti=(low_byte<<16 | high_byte);
            pnti++;
         }
#endif
      }
#endif
#endif

      if(SUCCEEDED(retcf))
      {
#ifdef KPST_WINDOWS_INTERFACE
            out_file=
#ifdef KPST_UNICODE_FNAMES
               CreateFileW((WCHAR *)key_name_w,
#else
               CreateFile((const char *)key_name,
#endif
            GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
         if((out_file==INVALID_HANDLE_VALUE) || (out_file==NULL))
#else
         out_file=fopen((const char *)key_name, "w");
         if(out_file==NULL)
#endif
         {
//          retcf=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// !!!!     retcf=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, key_name, True, __FILE__, __LINE__, 0L, NULL);
//          if(SUCCEEDED(retc)) retc=retcf;
            retcf=KP_E_DIR_ERROR;
            KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
            if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
            if(SUCCEEDED(retc)) retc=retcf;
         }

         if(SUCCEEDED(retcf))
         {
//          out_val=(m_iInstCount*10)^prod_ver;
            out_val=(comp_id /* m_iCompId */ * 10) ^ prod_ver;

#ifdef KPST_WINDOWS_INTERFACE
            if(!WriteFile(out_file, &out_val, sizeof(out_val), &written, NULL))
#else
//          fprintf(out_file, "%x\n", out_val);
            fwrite(&out_val, sizeof(out_val), 1, out_file);
            if(ferror(out_file) || feof(out_file))
#endif
            {
//             retcf=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//             if(SUCCEEDED(retc)) retc=retcf;
               retcf=KP_E_FERROR;
            }
#ifdef KPST_WINDOWS_INTERFACE
            if(!CloseHandle(out_file))
#else
            if(fclose(out_file))
#endif
            {
               if(SUCCEEDED(retcf))
               {
//                retcf=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                if(SUCCEEDED(retc)) retc=retcf;
                  retcf=KP_E_DIR_ERROR;
               }
            }

         } // if(SUCCEEDED(retcf))

// ------------------- reset file creation date
         if(SUCCEEDED(retcf))
         {
            retcf=ChFileTimeCrtd(key_name, &tt);
//          if(SUCCEEDED(retc)) retc=retcf;
         }

      }  // if(SUCCEEDED(retcf)

// ----------------------- restore system time
//    SetSystemTime(&st);

   } // if(SUCCEEDED(retc))


   if(FAILED(retcf) && SUCCEEDED(retc))
   {
      KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
      if(bForceAdmin)
      {
         KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
         retc=retcf;
      }
   }

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
LicStatus lic_buf_one;
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
      retw=RegQueryValueEx(res_key,
         (const char *)val_name,
         NULL, &dwValType,
         (LPBYTE)key_buf, &dwBufLen);
      if(retw==ERROR_SUCCESS) key_buf[dwBufLen]=Nul;
      else
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         retc=S_OK;
      }

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
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
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

   if(SUCCEEDED(retc))
   {
      lic_buf=new LicStatus[num_of_lics];
      if(lic_buf==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, False, __FILE__, __LINE__, 0L, NULL);
   }

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
      strcat(key_name, KPST_CNT_REG_PATH_2);
      strcat((char *)key_name, "\\");
      strcat(key_name, pkg_name);

#ifdef KPST_WINDOWS_INTERFACE
      in_file=CreateFile((const char *)key_name, GENERIC_READ, FILE_SHARE_READ,
               0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
      if(in_file==INVALID_HANDLE_VALUE)
#else
      in_file=fopen((const char *)key_name, "rb");
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
            retc=EnctBufSimpl(lic_buf, sizeof(LicStatus)*num_of_lics);

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

   if(lic_buf) delete [] lic_buf;
   lic_buf=NULL;

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
         0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw!=ERROR_SUCCESS)
      {
         retc=KP_E_ACCESS_DENIED;
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

         retw=RegSetValueEx(res_key,
            (const char *)val_name,
            0, REG_SZ,
            key_buf,
            strlen(key_buf));
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
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
LicStatus *lic_buf=NULL;
int num_of_lics=0;
int prod_ver=0;
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
UniChar key_name_w[KP_MAX_FILE_LIN_WDT+1];
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

      if(SUCCEEDED(retc))
      {
         lic_buf=new LicStatus[num_of_lics];
         if(lic_buf==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, False, __FILE__, __LINE__, 0L, NULL);
      }

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

//    if(SUCCEEDED(retc))
      {
         retcf=S_OK;

         if(SUCCEEDED(retcf)) retcf=CreateRegPath(&tt);

         if(SUCCEEDED(retcf))
         {
            strcpy(key_name, KPST_CNT_REG_PATH_1);
            strcat(key_name, KPST_CNT_REG_PATH_2);
            strcat((char *)key_name, "\\");
            strcat(key_name, pkg_name);
         }

// ---------------------------
#ifdef KPST_WINDOWS_INTERFACE
#ifdef KPST_UNICODE_FNAMES
         if(SUCCEEDED(retcf))
         {
            name_len=strlen(key_name);
            retcf=KptStrToUnicode(key_name_w, key_name, &name_len, 1);
//          if(FAILED(retcf))
//             retcf=KpErrorProc.OutputErrorMessage(retcf, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) retc=retcf;
         }
         if(SUCCEEDED(retcf))
         {
            key_name_w[name_len]=C_Nul;
         }
#endif
#endif

         if(SUCCEEDED(retcf))
         {
#ifdef KPST_WINDOWS_INTERFACE
            out_file=
#ifdef KPST_UNICODE_FNAMES
               CreateFileW((WCHAR *)key_name_w,
#else
               CreateFile((const char *)key_name,
#endif
               GENERIC_WRITE, FILE_SHARE_WRITE,
               0, CREATE_ALWAYS, /* FILE_ATTRIBUTE_NORMAL| */ /* FILE_FLAG_POSIX_SEMANTICS */ 0, 0);
            if((out_file==INVALID_HANDLE_VALUE) || (out_file==NULL))
#else
            out_file=fopen((const char *)key_name, "wb");
            if(out_file==NULL)
#endif
            {
               retcf=KP_E_DIR_ERROR;
               KpErrorProc.OutputErrorMessage(retcf, null, False, __FILE__, __LINE__, 0L, NULL);
               if(bForceAdmin && SUCCEEDED(retc)) KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
               if(SUCCEEDED(retc)) retc=retcf;
            }

            if(SUCCEEDED(retcf))
            {
               memcpy(lic_buf, m_pLicArray, sizeof(LicStatus)*num_of_lics);
               retc0=EnctBufSimpl(lic_buf, sizeof(LicStatus)*num_of_lics);
               if(SUCCEEDED(retc)) retc=retc0;

#ifdef KPST_WINDOWS_INTERFACE
               if(!WriteFile(out_file, lic_buf, sizeof(LicStatus)*num_of_lics, &written, NULL))
#else
               fwrite(lic_buf, sizeof(LicStatus)*num_of_lics, 1, out_file);
               if(ferror(out_file) || feof(out_file))
#endif
               {
//                retcf=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                if(SUCCEEDED(retc)) retc=retcf;
                  retcf=KP_E_FERROR;
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
//                   retcf=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                   if(SUCCEEDED(retc)) retc=retcf;
                     retcf=KP_E_DIR_ERROR;
                  }
               }

            } // if(SUCCEEDED(retcf))

// ------------------- reset file creation date
            if(SUCCEEDED(retcf))
            {
               retcf=ChFileTimeCrtd(key_name, &tt);
//             if(SUCCEEDED(retc)) retc=retcf;
            }

         }  // if(SUCCEEDED(retcf)

      } // if(SUCCEEDED(retc))

   } // else // if(m_pLicArray==NULL)

   if(lic_buf) delete [] lic_buf;
   lic_buf=NULL;

   if(SUCCEEDED(retc)) retc=retcf;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetKpstFdfLine(KpString *psOutStr, KpInStream *pInStream)
{
HRESULT retc=S_OK;
unsigned char in_line[KP_MAX_FILE_LIN_LEN+1];

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

   if(SUCCEEDED(retc)) *psOutStr = (const char *)in_line;

return(retc);
}


HRESULT KpStApp::GetKpstFdfData(KpString *psOutStr, KpInStream *pInStream, FdfInputMode iInpMode)
{
HRESULT retc=S_OK;
KpString in_str;
KpString a85_str;
int ii, jj;

   if(((psOutStr==NULL) || (pInStream == NULL) || (iInpMode < 0) || (iInpMode >= FdfInputMax)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) if(pInStream->fail())
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(iInpMode)
   {
   case FdfInputFdf:

      if(SUCCEEDED(retc)) retc = GetKpstFdfLine(&in_str, pInStream);
      if(SUCCEEDED(retc))
         if(in_str!="%FDF-1.2")
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);

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
   case FdfInputRawA85:

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

      break;

   case FdfInputRawAscii:
      if(SUCCEEDED(retc)) retc = GetKpstFdfLine(psOutStr, pInStream);
      break;

   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   } // if(SUCCEEDED(retc)) switch(iInpMode)

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
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
int num_of_lics=0;
// unsigned char prod_name[KP_MAX_FNAME_LEN+1];

// --------------------
   hKey=0;

   if(SUCCEEDED(retc)) retc=GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
// if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);


#if FALSE
char str_buf[100];
sprintf(str_buf, "%d", prod_ver);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
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
            KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         }

// -------------------- key
         key_buf[0]=Nul;

         if(SUCCEEDED(retc))
         {
            dwBufLen=KP_MAX_FILE_LIN_WDT;
            retw=RegQueryValueEx(hKey,
               "RegKey",
               NULL, &dwValType,
               (LPBYTE)key_buf, &dwBufLen);
            if(retw==ERROR_SUCCESS) key_buf[dwBufLen]=Nul;
            else
            {
               retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            }
         }

         if(SUCCEEDED(retc)) retc=ScanInstKeyFull(key_buf);

// -------------------- lic
         key_buf[0]=Nul;

         if(SUCCEEDED(retc))
         {
            dwBufLen=KP_MAX_FILE_LIN_WDT;
            retw=RegQueryValueEx(hKey,
               "Licence",
               NULL, &dwValType,
               (LPBYTE)key_buf, &dwBufLen);
            if(retw==ERROR_SUCCESS) key_buf[dwBufLen]=Nul;
            else
            {
               retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            }
         }

         if(SUCCEEDED(retc)) retc=ScanLic(key_buf);

         if(SUCCEEDED(retc)) retc=UnpackLic();

         if(hKey)
         {
            retw=RegCloseKey(hKey);
//          if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
            hKey=NULL;
         }

      } // if((num_of_lics==0) || (this-ptr->m_iKpStMode!=KpStarterMode))

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetSavedKeyDat(void)
{
HRESULT retc=S_OK;
KpFStream *p_in_file=NULL;
KpString dat_str;
KpString rest_str;
KpString *sub_str = NULL;
int tab_pos;
int num_of_lics=0;
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
unsigned char ini_path[KP_MAX_FNAME_LEN+1];
unsigned char ini_name[KP_MAX_FNAME_LEN+1];
unsigned char ini_type[KP_MAX_FTYPE_LEN+1];
unsigned char dat_fname[KP_MAX_FNAME_LEN+1];
const /* unsigned */ char *pnts = NULL;

   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
   if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, ini_fname);
   if(SUCCEEDED(retc))
   {
      strcpy(dat_fname, ini_disk);
      strcat(dat_fname, ini_path);
      strcat(dat_fname, "\\");
      strcat(dat_fname, KPST_FDF_DATA_FNAME);
   }

   if(SUCCEEDED(retc))
   {
      p_in_file=new KpFStream((const char *)dat_fname, ios::in);
      if(p_in_file==NULL)
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
         retc=KP_E_KWD_NOT_FOUND;
      }
   }

// --------------------
   if(SUCCEEDED(retc)) if(p_in_file->fail())
   {
//    retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);
      retc=KP_E_KWD_NOT_FOUND;
   }

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

// -------------------- key
         if(SUCCEEDED(retc)) retc=GetKpstFdfData(&dat_str, p_in_file, FdfInputFdf);

         if(SUCCEEDED(retc))
         {
            key_buf[0] = Nul;

            tab_pos = dat_str.index("\t");
//          sub_str = &static_cast<KpString>(dat_str.substr(0, tab_pos));
            sub_str = new KpString(dat_str.substr(0, tab_pos));
            if(sub_str)
            {
#if Compiler==Mingw
               pnts = sub_str->ExtractUnsignedValue();
#else
               pnts = *sub_str;
#endif               
               if(pnts)
               {
                  strncpy(key_buf, pnts, KP_MAX_FILE_LIN_WDT);
#if (Compiler==Mingw)
                  delete [] pnts;
#endif
                  pnts = NULL;
               }
               delete sub_str;
               sub_str = NULL;
            }
            key_buf[KP_MAX_FILE_LIN_WDT]=Nul;

            retc=ScanInstCodeFull(key_buf);
         }

         if(SUCCEEDED(retc))
         {
            rest_str=dat_str.substr(tab_pos+1, dat_str.length()-(tab_pos+1));

            tab_pos=rest_str.index("\t");
            sub_str = new KpString(rest_str.substr(0, tab_pos));
            if(sub_str)
            {
#if (Compiler==Mingw)
               pnts = sub_str->ExtractUnsignedValue();
#else
               pnts = *sub_str;
#endif
               if(pnts)
               {
                  strncpy(key_buf, pnts, KP_MAX_FILE_LIN_WDT);
#if (Compiler==Mingw)
                  delete [] pnts;
#endif
                  pnts = NULL;
               }
               delete sub_str;
               sub_str = NULL;
            }
            key_buf[KP_MAX_FILE_LIN_WDT]=Nul;

            retc=ScanInstKeyFull(key_buf);
         }

      } // if((num_of_lics==0) || (this-ptr->m_iKpStMode!=KpStarterMode))

   } // if(SUCCEEDED(retc))

   if(p_in_file) delete p_in_file;
   p_in_file=NULL;

return(retc);
}


// ------------------------------
#if FALSE
HRESULT KpStApp::SaveKeyReg(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwDisposition;
bool admin_fl;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
// unsigned char prod_name[KP_MAX_FNAME_LEN+1];

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
         0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
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
   if(SUCCEEDED(retc))
      retc=FormatKeyHex(key_buf, m_iInstKey1);
   if(SUCCEEDED(retc))
   {
      key_buf[4]='-';
      retc=FormatKeyHex(key_buf+5, m_iInstKey2);
   }
   if(SUCCEEDED(retc))
   {
      key_buf[9]='-';
      retc=FormatKeyHex(key_buf+10, m_iInstKey3);
   }
   if(SUCCEEDED(retc))
   {
      key_buf[14]='-';
      retc=FormatKeyHex(key_buf+15, m_iInstKey4);
   }
   key_buf[19]=Nul;

   if(SUCCEEDED(retc))
   {
      retw=RegSetValueEx(hKey,
         "RegKey",
         0, REG_SZ,
         key_buf,
         strlen(key_buf));
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

// --------------------- lic
   if(SUCCEEDED(retc))
      retc=FormatKeyHex(key_buf, m_iLicCode1);
   if(SUCCEEDED(retc))
   {
      key_buf[4]='-';
      retc=FormatKeyHex(key_buf+5, m_iLicCode2);
   }
   if(SUCCEEDED(retc))
   {
      key_buf[9]='-';
      retc=FormatKeyHex(key_buf+10, m_iLicCode3);
   }
   key_buf[14]=Nul;

   if(SUCCEEDED(retc))
   {
      retw=RegSetValueEx(hKey,
         "Licence",
         0, REG_SZ,
         key_buf,
         strlen(key_buf));
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
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *add_data=NULL;
KpString data_str;
KpString out_str;
bool data_fl[KPSTAP_NUM_OF_SETS]={False, False, False};
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
unsigned char ini_path[KP_MAX_FNAME_LEN+1];
unsigned char ini_name[KP_MAX_FNAME_LEN+1];
unsigned char ini_type[KP_MAX_FTYPE_LEN+1];
unsigned char dat_fname[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc))
   {
      add_data=new unsigned char[KP_MAX_FILE_LIN_LEN+100];
      if(add_data==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
   if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, ini_fname);
   if(SUCCEEDED(retc))
   {
      strcpy(dat_fname, ini_disk);
      strcat(dat_fname, ini_path);
      strcat(dat_fname, "\\");
      strcat(dat_fname, KPST_FDF_DATA_FNAME);
   }

   if(SUCCEEDED(retc))
   {
      p_out_file=new KpFStream((const char *)dat_fname, ios::out);
      if(p_out_file==NULL)
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
         retc=KP_E_KWD_NOT_FOUND;
      }
   }

   if(SUCCEEDED(retc)) if(p_out_file->fail()) retc=KP_E_DIR_ERROR;

// -----------------------------
   if(SUCCEEDED(retc)) retc=FormatInstCodeFull(code_buf);
   if(SUCCEEDED(retc)) retc=RemoveSpaces(code_buf);
   if(SUCCEEDED(retc)) retc=FormatInstKeyFull(key_buf);
   if(SUCCEEDED(retc)) retc=RemoveSpaces(key_buf);

   if(SUCCEEDED(retc)) retc=FormAddData(add_data, data_fl, 1, 0, False);

   if(SUCCEEDED(retc))
   {
      data_str=(const char *)code_buf;
      data_str+="\t";
      data_str+=(const char *)key_buf;
      data_str+="\t";
      data_str+=(const char *)add_data;

      retc=StrToA85(&out_str, data_str);
      if(FAILED(retc))
         retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

// -----------------------------
   if(SUCCEEDED(retc))
   {
      *p_out_file << "%FDF-1.2" << endl;
      *p_out_file << "1 0 obj<</FDF<</Fields[<</T(PI)/V 3 0 R>>]>>>>" << endl;
      *p_out_file << "endobj" << endl;
      *p_out_file << "3 0 obj" << endl;
      *p_out_file << "<</Filter[/A85]>>" << endl;
      *p_out_file << "stream" << endl;
      *p_out_file << out_str.substr(2, out_str.length()-2) << ">" << endl;
      *p_out_file << "endstream" << endl;
      *p_out_file << "endobj" << endl;
      *p_out_file << "trailer" << endl;
      *p_out_file << "<</Root 1 0 R>>" << endl;
      *p_out_file << "%%EOF" << endl;

      p_out_file->close();

      if((p_out_file->fail() || p_out_file->eof()) && SUCCEEDED(retc)) retc=KP_E_FERROR;
   }

// -----------------------------
   if((retc==KP_E_DIR_ERROR) || (retc==KP_E_FERROR))
   {
      retc0=TestAdmin(&admin_fl);
      if(SUCCEEDED(retc0))
      {
         if(!admin_fl)
         {
            retc=KP_E_ACCESS_DENIED;
            retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            KpMsgOut(KPST_MSG_REG_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      else if(SUCCEEDED(retc)) retc=retc0;
   }

// -----------------------------
   if(p_out_file) delete p_out_file;
   p_out_file=NULL;

   if(add_data!=NULL) delete [] add_data;
   add_data=NULL;

return(retc);
}


// ------------------------------
HRESULT KpStApp::DelSavedKey(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
LONG retw0=ERROR_SUCCESS;
HKEY hKey=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
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
      retw=RegQueryValueEx(hKey,
         "RegKey",
         NULL, &dwValType,
         (LPBYTE)key_buf, &dwBufLen);
      if(retw==ERROR_SUCCESS) key_buf[dwBufLen]=Nul;
      else
      {
         retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }

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
//                   KpMsgOut(KPST_MSG_ALLREADY_REMOVED, IDI_ERROR, KP_MB_TESTI);

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
HRESULT KpStApp::CheckPrivileges(const unsigned char *lpszMsg)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
HKEY res_key=0;
unsigned char pkg_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
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
         retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
            &hKey, &dwDisposition);

      if((retw!=ERROR_SUCCESS) || (!admin_fl))
      {
//       retc=TestAdmin(&admin_fl);
//       if(SUCCEEDED(retc))
         {
            if(!admin_fl)
            {
               retc=KP_E_ACCESS_DENIED;
               KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
               KpMsgOut(lpszMsg, IDI_ERROR, KP_MB_BAIGTI);
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
      }
   }

// ----------------- 
   if(SUCCEEDED(retc))
   {
      sprintf((char *)pkg_name, (const char *)KPST_CNT_PKG_FMT, prod_ver);
      sprintf((char *)key_name, (const char *)KPST_CNT_REG_KEY_FMT, pkg_name);

      retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR)key_name,
         0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &res_key, &dwDisposition);

      if(retw!=ERROR_SUCCESS)
      {
         retc=KP_E_ACCESS_DENIED;
         KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
         KpMsgOut(lpszMsg, IDI_ERROR, KP_MB_BAIGTI);
      }
   }

return(retc);
}


//-------------------------------------------- hash function / pseudo random generator
int KpstRand(int prev)
{
HRESULT retc=S_OK;

#if TRUE
KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_RAND;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=prev;

   retc=EmuTv.ExecRemoteCall(&rc_pars);

return(rc_pars.value);

#else

return((prev*30497L+22571) % 65536);

#endif
}


//------------------- converts integer security key to pseudo-hex string
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


HRESULT ScanKeyHex(const unsigned char *szKeyBuf, int *piKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[5];
unsigned char *pntd;

   if(szKeyBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(strlen(szKeyBuf)>4)
   {
KP_TRACE(szKeyBuf);
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
HRESULT retc=S_OK;
unsigned char *buf_ptr;

   if((sKey==NULL) || (piKey==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      buf_ptr=new unsigned char[sKey->GetLength()+1];
      if(buf_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) strcpy(buf_ptr, *sKey);

   if(SUCCEEDED(retc)) retc=ScanKeyHex(buf_ptr, piKey);

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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_UNPACK_LIC;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=False;

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc=KP_E_ILL_CODE;

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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_CALC_LIC_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_RECALC_LIC_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// ------------------------------
HRESULT KpStApp::FormatInstCodeFull(unsigned char *lpszCode)
{
HRESULT retc=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
int inst_code1=0;
int inst_code2=0;
int inst_code3=0;
int inst_code4=0;

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
      strcat(lpszCode, " - ");
      retc=FormatKeyHex(code_buf, inst_code2 /* m_iInstCode2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszCode, code_buf);
      strcat(lpszCode, " - ");
      retc=FormatKeyHex(code_buf, inst_code3 /* m_iInstCode3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszCode, code_buf);
      strcat(lpszCode, " - ");
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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_CALC_INST_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_UNPACK_INST_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=False;

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
      strcat(lpszKey, " - ");
      retc=FormatKeyHex(key_buf, inst_key2 /* m_iInstKey2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszKey, key_buf);
      strcat(lpszKey, " - ");
      retc=FormatKeyHex(key_buf, inst_key3 /* m_iInstKey3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszKey, key_buf);
      strcat(lpszKey, " - ");
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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_CALC_INST_KEY;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=False;

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc=KP_E_REFUSED;

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
      strcat(lpszRemCode, " - ");
      retc=FormatKeyHex(code_buf, rem_code2 /* m_iRemCode2 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszRemCode, code_buf);
      strcat(lpszRemCode, " - ");
      retc=FormatKeyHex(code_buf, rem_code3 /* m_iRemCode3 */);
   }
   if(SUCCEEDED(retc))
   {
      strcat(lpszRemCode, code_buf);
      strcat(lpszRemCode, " - ");
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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_CALC_REM_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
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

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_UNPACK_REM_CODE;
   rc_pars.iParBlSize=sizeof(rc_pars);
   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

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
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      retc=KP_E_SYSTEM_ERROR;
//    retc=KP_E_REFUSED;
   }

   if(SUCCEEDED(retc)) retc=this_ptr->GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
      if((cMemBank[KP11_REM_LICID/2] /* this_ptr->m_iRemLicID */ != this_ptr->m_iKpstRand0) ||
         (cMemBank[KP11_REM_PRODVER/2] /* this_ptr->m_iRemProdVer */ != prod_ver))
            retc=KP_E_ACCESS_DENIED;

   if(SUCCEEDED(retc))
   {
      retc=KP_E_REFUSED;

// gal licencijos atnaujinimas?
      for(ii=0; ii<num_of_lics; ii++)
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
      if(retc==KP_E_REFUSED) for(ii=0; ii<num_of_lics; ii++)
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
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      retc=KP_E_SYSTEM_ERROR;
//    retc=KP_E_REFUSED;
   }

   if(SUCCEEDED(retc)) retc=this_ptr->GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=this_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
      if((cMemBank[KP11_REM_LICID/2] /* this_ptr->m_iRemLicID */ != this_ptr->m_iKpstRand0) ||
         (cMemBank[KP11_REM_PRODVER/2] /* this_ptr->m_iRemProdVer */ != prod_ver))
            retc=KP_E_ACCESS_DENIED;

   if(SUCCEEDED(retc))
   {
      retc=KP_E_REFUSED;
      for(ii=0; ii<num_of_lics; ii++) // if(this_ptr->m_pLicArray[ii].m_iLicState!=KpstLicFree)
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

   if(SUCCEEDED(retc)) retc=GetIniIniLicID(&ini_lic_id);
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

#if FALSE
#if FALSE
int comp_id_1;
int prod_ver=0;

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

   comp_id_1=KpstRand(m_iCompId);

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
KpRcPars rc_pars;
int check_buf[8];

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

   rc_pars.iOpCode=KP_RC_KEY_CHECK;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.enc.iDataLen=sizeof(check_buf);
   rc_pars.enc.pData=check_buf;
   rc_pars.value=False;

   retc=EmuTv.ExecRemoteCall(&rc_pars);

   if((!rc_pars.value) && SUCCEEDED(retc))
      retc=KP_E_ILL_CODE;
#endif

KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_KEY_CHECK_INTERN;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.value=False;

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc))
   {
      retc=KP_E_ILL_CODE;

      if((ini_lic_id!=KpstRand(0)) && (lic_id!=KpstRand(0)) && (lic_id != ini_lic_id)) retc = KP_E_REFUSED;
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SendCodeHttp(HRESULT hRetc, const unsigned char *lpszHttpQuery, bool bRecKey)
{
HRESULT retc=S_OK;
KpSocket *sock_ptr=NULL;
unsigned char *rcv_buf=NULL;
long read;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char url_buf[2*KP_MAX_FNAME_LEN+1];
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *out_buf=NULL;
unsigned char reg_url[KP_MAX_FNAME_LEN+1];
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int num_of_lics=0;
int prod_ver=0;
int port=0;

   if(SUCCEEDED(retc)) retc=GetIniRegURL(reg_url);
   if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      port=prod_ver;
      if(port<KP_MIN_USER_PORT) port += KP_MIN_USER_PORT;
   }

   if(SUCCEEDED(retc))
   {
      rcv_buf=new unsigned char[KP_MAX_FILE_LIN_LEN+1];
      if(rcv_buf==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      out_buf=new unsigned char[KP_MAX_FILE_LIN_LEN+KP_MAX_FNAME_LEN+KP_MAX_FILE_LIN_WDT+1];
      if(out_buf==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      sock_ptr=new KpSocket();
      if(sock_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) retc=sock_ptr->GetOpenResult();

   if((num_of_lics!=0) && (m_iKpStMode==KpStarterMode) && SUCCEEDED(retc))
   {
      sprintf((char *)url_buf, ":%d/", port);
      strcat(reg_url, url_buf);
   }

   if(SUCCEEDED(retc)) retc=sock_ptr->Resolve(reg_url, False);
   if(SUCCEEDED(retc)) retc=sock_ptr->Connect(False);

// KpMsgOut(reg_url, IDI_ASTERISK, KP_MB_TESTI);

   if(SUCCEEDED(retc))
   {
      strcpy(url_buf, sock_ptr->m_PackedUrl.lpszFileName);
      strcat(url_buf, lpszHttpQuery);
      if(strcmp(lpszHttpQuery, KPST_HTTP_REGISTER)==0) retc=FormatInstCodeFull(code_buf);
      else if(strcmp(lpszHttpQuery, KPST_HTTP_REMOVE)==0) retc=FormatRemCodeFull(code_buf);
      else
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) retc=RemoveSpaces(code_buf);

KP_TRACE("SendHttpRequest");

   if(SUCCEEDED(retc))
   {
      strcat(url_buf, code_buf);
      retc=sock_ptr->SendHttpRequest((const unsigned char *)HTTP_GET_REQUEST_CMD, url_buf, False); // "GET"
   }

// KpMsgOut(url_buf, IDI_ASTERISK, KP_MB_TESTI);

KP_TRACE("RcvHttpTxtMsg");

   if(SUCCEEDED(retc))
   {
      read=KP_MAX_FILE_LIN_LEN;
      retc=sock_ptr->RcvHttpMsg(rcv_buf, &read, False);

#ifdef Debug // #if FALSE //
char str_buf[1000];
if(SUCCEEDED(retc))
{
sprintf(str_buf, "rcv_buf[%d] >>>", read);
strcat(str_buf, (const char *)rcv_buf);
strcat(str_buf, "<<<");
KP_TRACE(str_buf);
}
#endif
   }

   if(SUCCEEDED(retc))
   {
      rcv_buf[read]=Nul;
      pnts=strstr(rcv_buf, KPST_REG_OK);
      if(pnts)
      {
         if(bRecKey)
         {
            pnts+=strlen(KPST_REG_OK);
            while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
            pntd=(unsigned char *)pnts;
            while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;
            *pntd=Nul;
            retc=ScanInstKeyFull(pnts);
         }
      }
      else
      {
         pnts=strstr(rcv_buf, KPST_REG_ERROR);
         if(pnts)
         {
            pnts+=strlen(KPST_REG_ERROR);
            while(*pnts && (strchr(lpszSpaces, *pnts)!=NULL)) pnts++;
            pntd=(unsigned char *)pnts;
            while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;
            *pntd=Nul;

            if(hRetc!=KP_E_REFUSED)
            {
               strcpy(out_buf, prod_name);
               strcat(out_buf, "\n                         \n");
               strcat(out_buf, pnts);
               KpMsgOut(out_buf, IDI_ERROR, KP_MB_TESTI);
            }

            retc=KP_E_REFUSED;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_TRANS_ERR, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }

   if(sock_ptr!=NULL) delete sock_ptr;
   sock_ptr=NULL;

   if(out_buf!=NULL) delete out_buf;
   out_buf=NULL;

   if(rcv_buf!=NULL) delete rcv_buf;
   rcv_buf=NULL;


return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CheckReg(HINSTANCE hInst, bool *pbLicEntered)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
bool skip_fl=False;
bool bound=False;
bool ci_direct=False;
int num_of_lics=0;

   if((pbLicEntered==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) *pbLicEntered=False;

   if(SUCCEEDED(retc)) retc=GetIniCiDirect(&ci_direct);
   if(SUCCEEDED(retc)) retc=GetIniBound(&bound);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(SUCCEEDED(retc))
   {
      if(bound)
      {

// ðità vietà lauþia smilas ipai_20060210.exe

//    if(bound && SUCCEEDED(retc))
//    {

// :00415E18 807DF800                cmp byte[ebp-08], 00
// :00415E1C 7406                    je 00415E24               // èia keièia á   // :00415E1C E903000000              jmp 00415E24
// :00415E1E 837DEC00                cmp dword[ebp-14], 000                      // :00415E21 00                                                .
// :00415E22 7D05                    jge 00415E29
// ---------
// :00415E24 E90C020000              jmp 00416035

// --------------------------
         retc=GetSavedKeyReg();

//       if(SUCCEEDED(retc)) retc=GetSavedKey();

// :00415E29 837DEC00                cmp dword[ebp-14], 000
// :00415E2D 7C0B                    jl 00415E3A
// :00415E2F 8B45E0                  mov eax, dword[ebp-20]
// :00415E32 E882E4FFFF              call 004142B9
// :00415E37 8945EC                  mov dword[ebp-14], eax


         if(SUCCEEDED(retc))
         {
            retc0=GetCommonCompID();
            if(SUCCEEDED(retc)) retc=retc0;
         }
         else
         {
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "%d", retc-MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x200 + 0x100 +  0));
KpMsgOut(str_buf, KP_MB_TESTI);
#endif

// --------------------------
            if((retc==KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE))
            {
               retc=GetSavedKeyDat();

               if(SUCCEEDED(retc))
               {
                  retc0=GetCommonCompID();
                  if(SUCCEEDED(retc)) retc=retc0;

                  if(SUCCEEDED(retc)) retc=ReCalcLicCode();
               }
               else
               {
//                m_iCompId=0;
                  if(SUCCEEDED(retc0)) retc0=EmuTv.SetHp11Variable(0, KP11_COMPID);

//                m_iLicID=KpstRand(0);
                  if(SUCCEEDED(retc0)) retc0=InitLicId();

                  if(SUCCEEDED(retc0)) retc0=CalcLicCode();
                  if(SUCCEEDED(retc0)) retc0=CalcInstCode();

//                m_iInstKey1=1234; // 0;
//                m_iInstKey2=5678; // 0;
//                m_iInstKey3=9012; // 0;
//                m_iInstKey4=3456; // 0;

                  if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(1234, KP11_INST_KEY1);
                  if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(5678, KP11_INST_KEY2);
                  if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(9012, KP11_INST_KEY3);
                  if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(3456, KP11_INST_KEY4);

                  if(bAdminFl && SUCCEEDED(retc0)) retc0=SaveKeyDat();

               /* if(SUCCEEDED(retc0)) retc0= */ GetCommonCompID();
               }
            }

         } // else // if(SUCCEEDED(retc))

         if(SUCCEEDED(retc)) retc=CalcInstCode();

         if(SUCCEEDED(retc)) retc=TestKey();

         if((retc==KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE) || (retc == KP_E_REFUSED))
         {
            *pbLicEntered=True;

            if((!ci_direct) && ((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)))
            {
               KpMsgOut((retc == KP_E_REFUSED)?KPST_MSG_INVALID_REG:KPST_MSG_NOT_REG, IDI_INFORMATION, KP_MB_BAIGTI);
               retc=KP_E_NOTINST;
               KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            }
            else
            {
               retc=S_OK;
               skip_fl=False;
               if(((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)) && SUCCEEDED(retc))
               {
                  retc=CheckPrivileges(KPST_MSG_REG_NOT_ADMIN);

                  if(SUCCEEDED(retc))
                  {
                     retc=EnterLicence(hInst, False, False);
                     if(retc==KP_E_SKIP)
                     {
                        skip_fl=True;
                        retc=S_OK;
                     }
                  }

                  if(SUCCEEDED(retc)) retc=CalcInstCode();

               } // if(((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)) && SUCCEEDED(retc))

               if(SUCCEEDED(retc))
               {
                  if(!skip_fl)
                  {
                     if(SUCCEEDED(retc)) retc=SendCodeHttp(S_OK, KPST_HTTP_REGISTER, True);
                     if(SUCCEEDED(retc)) retc=TestKey();

                     if((retc==KP_E_REFUSED) || (retc==KP_E_ILL_CODE) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
                     {
                        if((retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
                        {
                           retc=S_OK;

                           if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
                              KpMsgOut(KPST_MSG_CHECK_CONN, IDI_WARNING, KP_MB_TESTI);
                           else
                              KpMsgOut(KPST_MSG_CHECK_CONN_LOC, IDI_WARNING, KP_MB_TESTI);

                           retc=SendCodeHttp(S_OK, KPST_HTTP_REGISTER, True);

                           if(SUCCEEDED(retc)) retc=TestKey();
                        }

                        if((retc==KP_E_REFUSED) || (retc==KP_E_ILL_CODE) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
                           if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
                           {
                              retc=S_OK;
                              retc=EnterNewKey(hInst, KPST_MSG_REG_UNSUC);
                           }
                           else
                              if((retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
                                 KpMsgOut(KPST_MSG_REG_UNSUC_LOC, IDI_ERROR, KP_MB_BAIGTI);

                     } // if(retc==KP_E_TRANS_ERR)

                  } // if(!skip_fl)
                  else
                     if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
                        retc=EnterNewKey(hInst, (const unsigned char *)"");

               } // if(SUCCEEDED(retc))
#if FALSE
               if(SUCCEEDED(retc))
                  if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
                     retc=SaveKeyReg();
#endif
            } // else // if((!ci_direct) && ((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)))

         } // if((retc==KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE) || (retc == KP_E_REFUSED))
         else
            if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);


//       if(ci_direct) retc0=SaveCompID(False); if(SUCCEEDED(retc)) retc=retc0;

      } // if(bound)
      else retc=TestKey(); // tik KP11_BLOCK_PROCESSING iðvalymui, kai nepririðtas nei prie kompo, nei prie atmintuko

   } // if(SUCCEEDED(retc))

   if(ci_direct && bAdminFl && SUCCEEDED(retc))
      if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
         retc=SaveKeyDat();

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::RemoveReg(HRESULT hRetc, HINSTANCE hInst)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *out_buf=NULL;
bool skip_fl=False;
bool bound=False;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int num_of_lics=0;

   if(SUCCEEDED(retc)) retc=GetIniBound(&bound);
   if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;

   if(bound && SUCCEEDED(retc))
   {
      out_buf=new unsigned char[KP_MAX_FILE_LIN_LEN+1];
      if(out_buf==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
         {
            retc=CheckPrivileges(KPST_MSG_UNREG_NOT_ADMIN);

            if(SUCCEEDED(retc))
            {
               retc=GetSavedKeyReg();
               if(SUCCEEDED(retc))
               {
                  retc0=GetCommonCompID();
                  if(SUCCEEDED(retc)) retc=retc0;

                  if(SUCCEEDED(retc)) retc=CalcInstCode();
               }
               else if((retc==KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE))
               {
                  retc=GetSavedKeyDat();

                  retc0=GetCommonCompID();
                  if(SUCCEEDED(retc)) retc=retc0;

                  if(SUCCEEDED(retc)) retc=ReCalcLicCode();
               }

               if(SUCCEEDED(retc))
               {
                  skip_fl=False;
                  retc=EnterLicence(hInst, True, True);
                  if(retc==KP_E_SKIP)
                  {
                     skip_fl=True;
                     retc=S_OK;
                  }
               }
               else if((retc==KP_E_KWD_NOT_FOUND) || (retc==KP_E_ILL_CODE))
               {
                  retc=S_OK;
                  skip_fl=False;
                  retc=EnterLicence(hInst, True, False);
                  if(retc==KP_E_SKIP)
                  {
                     skip_fl=True;
                     retc=S_OK;
                  }
               }
            }

            retc0=GetCommonCompID(); if(SUCCEEDED(retc)) retc=retc0;
         }
         else // if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
         {
//          m_iLicID=KpstRand(0);
            retc=InitLicId();

            if(SUCCEEDED(retc)) retc=CalcLicCode();
// dinaminis m_iCompId jau sugeneruotas registruojantis - geriau nekeisti
//          retc0=GetCommonCompID(); if(SUCCEEDED(retc)) retc=retc0;
         }

      } // if(SUCCEEDED(retc))

      if(SUCCEEDED(retc)) retc=CalcInstCode();
      if(SUCCEEDED(retc)) retc=CalcRemoveCode();

      if(((num_of_lics==0) || (m_iKpStMode!=KpStarterMode)) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc))
         {
            retc=DelSavedKey();
            if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
         }
         if(SUCCEEDED(retc)) retc=IncCompID();

         retc0=SaveCompID(True); if(SUCCEEDED(retc)) retc=retc0;

      }

      if((!skip_fl) && SUCCEEDED(retc))
      {
         retc=SendCodeHttp(hRetc, KPST_HTTP_REMOVE, False);

         if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))
         {
            if(SUCCEEDED(retc))
            {
               strcpy(out_buf, prod_name);
               strcat(out_buf, "\n                                    \n");
               strcat(out_buf, KPST_MSG_UNREG_SUCC);
               retc=KpMsgOut(out_buf, IDI_INFORMATION, KP_MB_BAIGTI);
            }

            if((retc==KP_E_REFUSED) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
            {
               if((retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
               {
                  retc=S_OK;
                  KpMsgOut(KPST_MSG_CHECK_CONN, IDI_WARNING, KP_MB_TESTI);
                  retc=SendCodeHttp(hRetc, KPST_HTTP_REMOVE, False);
               }

               if(SUCCEEDED(retc))
               {
                  strcpy(out_buf, prod_name);
                  strcat(out_buf, "\n                                    \n");
                  strcat(out_buf, KPST_MSG_UNREG_SUCC);
                  retc=KpMsgOut(out_buf, IDI_INFORMATION, KP_MB_BAIGTI);
               }

               if((retc==KP_E_REFUSED) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))
               {
                  retc=S_OK;

                  if(SUCCEEDED(retc))
                  {
                     strcpy(out_buf, prod_name);
                     strcat(out_buf, "                    \n");
                     strcat(out_buf, "                                        \n");
                     strcat(out_buf, KPST_MSG_UNREG_KOD);
                     strcat(out_buf, "                                        \n");

                     retc=FormatRemCodeFull(code_buf);
                  }

                  if(SUCCEEDED(retc))
                  {
                     strcat(out_buf, code_buf);
                     strcat(out_buf, "                   \n");
                     strcat(out_buf, "                                        \n");

                     strcat(out_buf, KPST_MSG_UNREG_UNSUCC);
                     strcat(out_buf, " ");
                     strcat(out_buf, KPST_MSG_UNREG_PASTU);
                     strcat(out_buf, KPST_MSG_UNREG_DARBO_LAIKAS);
                     strcat(out_buf, KPST_MSG_UNREG_TELEF);
                     retc=KpMsgOut(out_buf, IDI_WARNING, KP_MB_BAIGTI);
                  }

               } // if((retc==KP_E_REFUSED) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))

            } // if((retc==KP_E_REFUSED) || (retc==KP_E_NO_CONN) || (retc==KP_E_TRANS_ERR))

         } // if((num_of_lics==0) || (m_iKpStMode!=KpStarterMode))

      } // if(!skip_fl)
      else
      {
         if(SUCCEEDED(retc))
         {
            strcpy(out_buf, prod_name);
            strcat(out_buf, "                    \n");
            strcat(out_buf, "                                        \n");
            strcat(out_buf, KPST_MSG_UNREG_KOD);
            strcat(out_buf, "                                        \n");

            retc=FormatRemCodeFull(code_buf);
         }
         if(SUCCEEDED(retc))
         {
            strcat(out_buf, code_buf);
            strcat(out_buf, "                   \n");
            strcat(out_buf, "                                        \n");

            strcat(out_buf, KPST_MSG_UNREG_PASTU);
            strcat(out_buf, KPST_MSG_UNREG_DARBO_LAIKAS);
            strcat(out_buf, KPST_MSG_UNREG_TELEF);
            retc=KpMsgOut(out_buf, IDI_WARNING, KP_MB_BAIGTI);
         }

      } // else // if(!skip_fl)

   } // if(bound)

   if(out_buf!=NULL) delete out_buf;
   out_buf=NULL;

return(retc);
}


// ==================================================================
extern HRESULT TestFlashID_RC(void *pTestFlashIdParsPtr)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
DWORD dwBufLen;
DWORD dwValType;
long dev_count;
unsigned char dev_name[KP_MAX_FNAME_LEN+1];
bool found=False;
unsigned char dev_num_str[MAX_LONG_DIGITS+1];
int ii;
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char name[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];
long dev_id;
unsigned char key_name[KP_MAX_FNAME_LEN+1];
int st_pos;
TestFlashIdPars *test_fl_pars_ptr=(TestFlashIdPars *)pTestFlashIdParsPtr;

   if((pTestFlashIdParsPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((test_fl_pars_ptr->m_pThis==NULL) || (test_fl_pars_ptr->m_pbFound==NULL) || (test_fl_pars_ptr->m_piNumOfFlashes==NULL))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

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
      if(SUCCEEDED(retc))
         if(RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)&dev_count, &dwBufLen)==ERROR_SUCCESS)
      {
         if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) *test_fl_pars_ptr->m_piNumOfFlashes=dev_count;
      }
   }

   for(ii=0; (ii<dev_count) && (!found) && SUCCEEDED(retc); ii++)
   {
      sprintf((char *)dev_num_str, "%d", ii);

      dwBufLen=KP_MAX_FNAME_LEN;
      retw=RegQueryValueEx(hKey, (const char *)dev_num_str, NULL, NULL,
         (LPBYTE)dev_name, &dwBufLen);
      if(retw==ERROR_SUCCESS) dev_name[dwBufLen]=Nul;
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, dev_name);

// printf("--- %s\n", name);

// "USB\\Vid_3538&Pid_0042\\00000000000B18" - lauko reiksme
// ser. no. = 0x0B18

      if(SUCCEEDED(retc))
      {
         st_pos=strlen(name)-8;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
         if(st_pos<0) st_pos=0;
         if(sscanf((const char *)name+st_pos, "%lx", &dev_id)!=1)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc)) if(dev_id==test_fl_pars_ptr->m_lFlashId) found=True;
   }

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

   if(found && SUCCEEDED(retc)) cMemBank[KP11_BLOCK_PROCESSING/2]=False;

   if(SUCCEEDED(retc)) *test_fl_pars_ptr->m_pbFound=found;

return(retc);
}


// ==================================================================
#ifndef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::EnctBuf(void *pcBuffer, long lBufLen)
{
HRESULT retc=S_OK;
KpRcPars rc_pars;
unsigned char *pntd;
long rest;
int cur_len;

   rc_pars.iOpCode=KP_RC_ENCT;
   rc_pars.iParBlSize=sizeof(rc_pars);

   pntd=(unsigned char *)pcBuffer;
   rest=lBufLen;
   while((rest>0) && SUCCEEDED(retc))
   {
      cur_len=(rest<=Maxint)?rest:Maxint;

      rc_pars.enc.iDataLen=cur_len;
      rc_pars.enc.pData=pntd;

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

      retc=EmuTv.ExecRemoteCall(&rc_pars);

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

HRESULT KpStApp::EnctBufSimpl(void *pcBuffer, long lBufLen)
{
HRESULT retc=S_OK;
int ii;

   if((pcBuffer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) for(ii=0; ii<lBufLen; ii++)
      ((unsigned char *)pcBuffer)[ii]^=lpszEncStr[ii%KPSTAP_ENC_STR_LEN];

return(retc);
}


// -------------------------------------------
#ifndef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::EnctIniData(void)
{
HRESULT retc=S_OK;
#if FALSE // #ifdef Debug
char str_buf[200];
int ii;
unsigned char *pnts;
#endif

   if(SUCCEEDED(retc)) retc=EnctBuf(&m_Ini, (sizeof(KpStIniData)/4)*4);

#if FALSE // #ifdef Debug
KP_TRACE("--------------------------");

sprintf(str_buf, "m_Ini: [%d]", sizeof(m_Ini)); KP_TRACE(str_buf);

sprintf(str_buf, "lpszCmdStr:       %d[%d]", (long)m_Ini.lpszCmdStr           - (long)&m_Ini, sizeof(m_Ini.lpszCmdStr     )); KP_TRACE(str_buf);
sprintf(str_buf, "iProlShowTime:    %d[%d]", (long)&m_Ini.iProlShowTime       - (long)&m_Ini, sizeof(m_Ini.iProlShowTime  )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszProlFName:    %d[%d]", (long)m_Ini.lpszProlFName        - (long)&m_Ini, sizeof(m_Ini.lpszProlFName  )); KP_TRACE(str_buf);
sprintf(str_buf, "iBitmapWdt:       %d[%d]", (long)&m_Ini.iBitmapWdt          - (long)&m_Ini, sizeof(m_Ini.iBitmapWdt     )); KP_TRACE(str_buf);
sprintf(str_buf, "iBitmapHgt:       %d[%d]", (long)&m_Ini.iBitmapHgt          - (long)&m_Ini, sizeof(m_Ini.iBitmapHgt     )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszPwdWndName:   %d[%d]", (long)m_Ini.lpszPwdWndName       - (long)&m_Ini, sizeof(m_Ini.lpszPwdWndName )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszPwd:          %d[%d]", (long)m_Ini.lpszPwd              - (long)&m_Ini, sizeof(m_Ini.lpszPwd        )); KP_TRACE(str_buf);
sprintf(str_buf, "iPwdEdCtrl:       %d[%d]", (long)&m_Ini.iPwdEdCtrl          - (long)&m_Ini, sizeof(m_Ini.iPwdEdCtrl     )); KP_TRACE(str_buf);
sprintf(str_buf, "iPwdOkBut:        %d[%d]", (long)&m_Ini.iPwdOkBut           - (long)&m_Ini, sizeof(m_Ini.iPwdOkBut      )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszVolName:      %d[%d]", (long)m_Ini.lpszVolName          - (long)&m_Ini, sizeof(m_Ini.lpszVolName    )); KP_TRACE(str_buf);
sprintf(str_buf, "lSerNo:           %d[%d]", (long)&m_Ini.lSerNo              - (long)&m_Ini, sizeof(m_Ini.lSerNo         )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszBmpFName:     %d[%d]", (long)m_Ini.lpszBmpFName         - (long)&m_Ini, sizeof(m_Ini.lpszBmpFName   )); KP_TRACE(str_buf);
sprintf(str_buf, "lpszEpilFName:    %d[%d]", (long)m_Ini.lpszEpilFName        - (long)&m_Ini, sizeof(m_Ini.lpszEpilFName  )); KP_TRACE(str_buf);
sprintf(str_buf, "iEpilShowTime:    %d[%d]", (long)&m_Ini.iEpilShowTime       - (long)&m_Ini, sizeof(m_Ini.iEpilShowTime  )); KP_TRACE(str_buf);
sprintf(str_buf, "iAlignmentField:  %d[%d]", (long)&m_Ini.iAlignmentField     - (long)&m_Ini, sizeof(m_Ini.iAlignmentField)); KP_TRACE(str_buf);


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
HRESULT retc=S_OK;
unsigned char *buf_tmp=NULL;
KpRcPars rc_pars;

   if((pValBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      buf_tmp = new unsigned char[iLen+4+4];
      if(buf_tmp==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode=KP_RC_GET_INI_ELEM;
      rc_pars.iParBlSize=sizeof(KpRcPars);
      rc_pars.enc.iDataLen=iLen;
      rc_pars.enc.pData=buf_tmp;
      rc_pars.enc.lCtrl=lOffset;

      retc=EmuTv.ExecRemoteCall(&rc_pars);
   }

   if(SUCCEEDED(retc)) memcpy(pValBuf, buf_tmp, iLen);

   if(buf_tmp!=NULL) delete [] buf_tmp;
   buf_tmp=NULL;

return(retc);
}
#endif

HRESULT KpStApp::GetIniElementIfNotStopped(void *pValBuf, long lOffset, int iLen)
{
HRESULT retc=S_OK;
unsigned char *buf_tmp=NULL;
KpRcPars rc_pars;

   if((pValBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      buf_tmp = new unsigned char[iLen+4+4];
      if(buf_tmp==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode=KP_RC_GET_INI_ELEM_IF_NOT_STOPPED;
      rc_pars.iParBlSize=sizeof(KpRcPars);
      rc_pars.enc.iDataLen=iLen;
      rc_pars.enc.pData=buf_tmp;
      rc_pars.enc.lCtrl=lOffset;

      retc=EmuTv.ExecRemoteCall(&rc_pars);
   }

   if(SUCCEEDED(retc)) memcpy(pValBuf, buf_tmp, iLen);

   if(buf_tmp!=NULL) delete [] buf_tmp;
   buf_tmp=NULL;

return(retc);
}

#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::SetIniElement(const void *pValBuf, long lOffset, int iLen)
{
HRESULT retc=S_OK;
KpRcPars rc_pars;

   if((pValBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(
      (
         (((KP_MAX_FILE_LIN_WDT+1+4)/4)*4>HP11_INI_ELEM_BUF_LEN) ||
         (((KP_KWD_LEN+1+4)/4)*4>HP11_INI_ELEM_BUF_LEN) ||
         (((KP_MAX_FNAME_LEN+1+4)/4)*4>HP11_INI_ELEM_BUF_LEN) ||
         (((KP_MAX_FTYPE_LEN+1+4)/4)*4>HP11_INI_ELEM_BUF_LEN) ||
         (((iLen+4)/4)*4>HP11_INI_ELEM_BUF_LEN)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode=KP_RC_SET_INI_ELEM;
      rc_pars.iParBlSize=sizeof(KpRcPars);
      rc_pars.enc.iDataLen=iLen;
      rc_pars.enc.pData=(void *)pValBuf;
      rc_pars.enc.lCtrl=lOffset;

      retc=EmuTv.ExecRemoteCall(&rc_pars);
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
      retc=GetIniElement(lpszCmdStrBuf, IniDataBuf.lpszCmdStr-(unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(lpszCmdStrBuf, m_Ini.lpszCmdStr);
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
      retc=GetIniElement(piProlShTim, (unsigned char *)&IniDataBuf.iProlShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piProlShTim=m_Ini.iProlShowTime;
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
      retc=GetIniElement(lpszProlFNameBuf, IniDataBuf.lpszProlFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszProlFNameBuf, m_Ini.lpszProlFName);
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
      retc=GetIniElement(piBmpWdt, (unsigned char *)&IniDataBuf.iBitmapWdt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piBmpWdt=m_Ini.iBitmapWdt;
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
      retc=GetIniElement(piBmpHgt, (unsigned char *)&IniDataBuf.iBitmapHgt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piBmpHgt=m_Ini.iBitmapHgt;
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
      retc=GetIniElement(lpszPwdWndNameBuf, IniDataBuf.lpszPwdWndName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPwdWndNameBuf, m_Ini.lpszPwdWndName);
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
      retc=GetIniElement(lpszPwdBuf, IniDataBuf.lpszPwd-(unsigned char *)&IniDataBuf, KP_KWD_LEN+1);
#else
      strcpy(lpszPwdBuf, m_Ini.lpszPwd);
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
      retc=GetIniElement(lpszOldPwdBuf, IniDataBuf.lpszOldPwd-(unsigned char *)&IniDataBuf, KP_KWD_LEN+1);
#else
      strcpy(lpszOldPwdBuf, m_Ini.lpszOldPwd);
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
      retc=GetIniElement(piPwdEdCtrl, (unsigned char *)&IniDataBuf.iPwdEdCtrl-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piPwdEdCtrl=m_Ini.iPwdEdCtrl;
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
      retc=GetIniElement(piPwdOkBut, (unsigned char *)&IniDataBuf.iPwdOkBut-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piPwdOkBut=m_Ini.iPwdOkBut;
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
      retc=GetIniElement(lpszVolNameBuf, IniDataBuf.lpszVolName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszVolNameBuf, m_Ini.lpszVolName);
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
      retc=GetIniElement(plSerNo, (unsigned char *)&IniDataBuf.lSerNo-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      *plSerNo=m_Ini.lSerNo;
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
      retc=GetIniElement(lpszBmpFNameBuf, IniDataBuf.lpszBmpFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszBmpFNameBuf, m_Ini.lpszBmpFName);
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
      retc=GetIniElement(EpilFNameBuf, IniDataBuf.lpszEpilFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(EpilFNameBuf, m_Ini.lpszEpilFName);
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
      retc=GetIniElement(piEpilShowTime, (unsigned char *)&IniDataBuf.iEpilShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piEpilShowTime=m_Ini.iEpilShowTime;
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
      retc=GetIniElement(lpszPresFNameBuf, IniDataBuf.lpszPresetFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPresFNameBuf, m_Ini.lpszPresetFName);
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
      retc=GetIniElement(lpszRezFNameBuf, IniDataBuf.lpszRezFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRezFNameBuf, m_Ini.lpszRezFName);
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
      retc=GetIniElement(pbCheckCD, (unsigned char *)&IniDataBuf.bCheckCD-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbCheckCD=m_Ini.bCheckCD;
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
      retc=GetIniElement(pbBound, (unsigned char *)&IniDataBuf.bBound-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbBound=m_Ini.bBound;
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
      retc=GetIniElement(piProdVer, (unsigned char *)&IniDataBuf.iProdVer-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piProdVer=m_Ini.iProdVer;
#endif
   }

return(retc);
}

HRESULT KpStApp::GetIniProdName(unsigned char *lpszProdNameBuf)
{
HRESULT retc=S_OK;

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

HRESULT KpStApp::GetIniPublisher(unsigned char *lpszPublisherBuf)
{
HRESULT retc=S_OK;

   if((lpszPublisherBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElement(lpszPublisherBuf, IniDataBuf.lpszPublisher-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszPublisherBuf, m_Ini.lpszPublisher);
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
      retc=GetIniElement(lpszRegURLBuf, IniDataBuf.lpszRegURL-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRegURLBuf, m_Ini.lpszRegURL);
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
      retc=GetIniElement(lpszRezVarBuf, IniDataBuf.lpszRezVar-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(lpszRezVarBuf, m_Ini.lpszRezVar);
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
      retc=GetIniElement(pbKumul, (unsigned char *)&IniDataBuf.bKumul-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      *pbKumul=m_Ini.bKumul;
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
      retc=GetIniElement(piShuffCnt, (unsigned char *)&IniDataBuf.iShuffCnt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      *piShuffCnt=m_Ini.iShuffCnt;
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
      retc=GetIniElement(plAttOff, (unsigned char *)&IniDataBuf.lAttOff-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      *plAttOff=m_Ini.lAttOff;
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
      retc=GetIniElement(lpszAttExtBuf, IniDataBuf.lpszAttExt-(unsigned char *)&IniDataBuf, KP_MAX_FTYPE_LEN+1);
#else
      strcpy(lpszAttExtBuf, m_Ini.lpszAttExt);
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
      retc=SetIniElement(lpszCmdStrVal, IniDataBuf.lpszCmdStr-(unsigned char *)&IniDataBuf, KP_MAX_FILE_LIN_WDT+1);
#else
      strcpy(m_Ini.lpszCmdStr, lpszCmdStrVal);
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
      retc=SetIniElement(&iProlShTim, (unsigned char *)&IniDataBuf.iProlShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iProlShowTime=iProlShTim;
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
      retc=SetIniElement(lpszProlFNameVal, IniDataBuf.lpszProlFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszProlFName, lpszProlFNameVal);
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
      retc=SetIniElement(&iBmpWdtVal, (unsigned char *)&IniDataBuf.iBitmapWdt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iBitmapWdt=iBmpWdtVal;
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
      retc=SetIniElement(&iBmpHgtVal, (unsigned char *)&IniDataBuf.iBitmapHgt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iBitmapHgt=iBmpHgtVal;
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
      retc=SetIniElement(lpszPwdWndNameVal, IniDataBuf.lpszPwdWndName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszPwdWndName, lpszPwdWndNameVal);
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
      retc=SetIniElement(lpszPwdVal, IniDataBuf.lpszPwd-(unsigned char *)&IniDataBuf, KP_KWD_LEN+1);
#else
      strcpy(m_Ini.lpszPwd, lpszPwdVal);
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
      retc=SetIniElement(lpszOldPwdVal, IniDataBuf.lpszOldPwd-(unsigned char *)&IniDataBuf, KP_KWD_LEN+1);
#else
      strcpy(m_Ini.lpszOldPwd, lpszOldPwdVal);
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
      retc=SetIniElement(&iPwdEdCtrlVal, (unsigned char *)&IniDataBuf.iPwdEdCtrl-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iPwdEdCtrl=iPwdEdCtrlVal;
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
      retc=SetIniElement(&iPwdOkButVal, (unsigned char *)&IniDataBuf.iPwdOkBut-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iPwdOkBut=iPwdOkButVal;
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
      retc=SetIniElement(lpszVolNameVal, IniDataBuf.lpszVolName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszVolName, lpszVolNameVal);
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
      retc=SetIniElement(&lSerNoVal, (unsigned char *)&IniDataBuf.lSerNo-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      m_Ini.lSerNo=lSerNoVal;
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
      retc=SetIniElement(lpszBmpFNameVal, IniDataBuf.lpszBmpFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszBmpFName, lpszBmpFNameVal);
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
      retc=SetIniElement(EpilFNameVal, IniDataBuf.lpszEpilFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszEpilFName, EpilFNameVal);
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
      retc=SetIniElement(&iEpilShowTimeVal, (unsigned char *)&IniDataBuf.iEpilShowTime-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iEpilShowTime=iEpilShowTimeVal;
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
      retc=SetIniElement(lpszPresFNameVal, IniDataBuf.lpszPresetFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszPresetFName, lpszPresFNameVal);
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
      retc=SetIniElement(lpszRezFNameVal, IniDataBuf.lpszRezFName-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszRezFName, lpszRezFNameVal);
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
      retc=SetIniElement(&bCheckCDVal, (unsigned char *)&IniDataBuf.bCheckCD-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.bCheckCD=bCheckCDVal;
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
      retc=SetIniElement(&bBoundVal, (unsigned char *)&IniDataBuf.bBound-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.bBound=bBoundVal;
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
      retc=SetIniElement(&iProdVerVal, (unsigned char *)&IniDataBuf.iProdVer-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iProdVer=iProdVerVal;
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

HRESULT KpStApp::SetIniPublisher(const unsigned char *lpszPublisherVal)
{
HRESULT retc=S_OK;

   if((lpszPublisherVal==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(lpszPublisherVal, IniDataBuf.lpszPublisher-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszPublisher, lpszPublisherVal);
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
      retc=SetIniElement(lpszRegURLVal, IniDataBuf.lpszRegURL-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszRegURL, lpszRegURLVal);
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
      retc=SetIniElement(lpszRezVarVal, IniDataBuf.lpszRezVar-(unsigned char *)&IniDataBuf, KP_MAX_FNAME_LEN+1);
#else
      strcpy(m_Ini.lpszRezVar, lpszRezVarVal);
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
      retc=SetIniElement(&bKumulVal, (unsigned char *)&IniDataBuf.bKumul-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.bKumul=bKumulVal;
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
      retc=SetIniElement(&iShuffCntVal, (unsigned char *)&IniDataBuf.iShuffCnt-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iShuffCnt=iShuffCntVal;
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
      retc=SetIniElement(&lAttOffVal, (unsigned char *)&IniDataBuf.lAttOff-(unsigned char *)&IniDataBuf, sizeof(long));
#else
      m_Ini.lAttOff=lAttOffVal;
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
      retc=SetIniElement(lpszAttExtVal, IniDataBuf.lpszAttExt-(unsigned char *)&IniDataBuf, KP_MAX_FTYPE_LEN+1);
#else
      strcpy(m_Ini.lpszAttExt, lpszAttExtVal);
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
      retc=SetIniElement(lpszAttExtVal, IniDataBuf.m_bCiDirect-(unsigned char *)&IniDataBuf, sizeof(bool));
#else
      m_Ini.m_bCiDirect=bCiDirect;
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


HRESULT KpStApp::SetIniCheckSum(int iCheckSumVal)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      retc=SetIniElement(&iCheckSumVal, (unsigned char *)&IniDataBuf.iCheckSum-(unsigned char *)&IniDataBuf, sizeof(int));
#else
      m_Ini.iShuffCnt=iCheckSumVal;
#endif
   }

return(retc);
}


// =================================================================
HRESULT KpStApp::TestFlash(void)
{
HRESULT retc=S_OK;
unsigned char drive_path[10];
UINT drive_type;
int ii;
bool found=False;
int prod_ver;
int prod_ver_new;
long flash_id;
int num_fl;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
unsigned char out_msg[KP_MAX_FNAME_LEN+100];
bool ch_fl=False;
unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
unsigned char ini_path[KP_MAX_FNAME_LEN+1];
unsigned char ini_name[KP_MAX_FNAME_LEN+1];
unsigned char ini_type[KP_MAX_FTYPE_LEN+1];

   strcpy(drive_path, "A:\\");

   if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc=GetIniCheckFlash(&ch_fl);

// èia Audrius lauþia ipak_20071024_atmintuke.exe

   if(
      ch_fl &&
// :0041C733 807DFC00                cmp byte[ebp-04], 00
// :0041C737 7406                    je 0041C73F
      SUCCEEDED(retc)
// :0041C739 837DE400                cmp dword[ebp-1C], 000
// :0041C73D 7D05                    jge 0041C744
// :0041C73F E9E2010000              jmp 0041C926
     ) while(
               (!found) && // False && //
// :0041C744 807DF800                cmp byte[ebp-08], 00
// :0041C748 7511                    jne 0041C75B // èia keièia á // :0041C748 EB11                    jmp 0041C75B
               (
                  (retc==KP_E_TIMEOUT) ||
// :0041C74A 817DE413030480          cmp dword[ebp-1C], 80040313
// :0041C751 7406                    je 0041C759
                  SUCCEEDED(retc)
// :0041C753 837DE400                cmp dword[ebp-1C], 000
// :0041C757 7C02                    jl 0041C75B
               )
            )
// :0041C759 EB05                    jmp 0041C760
// :0041C75B E9C6010000              jmp 0041C926
   {
      retc = S_OK;
// :0041C760 C745E400000000          mov dword[ebp-1C], 00000000

      for(ii='B' /* 'A'*/; (ii<='Z') && (!found) && SUCCEEDED(retc); ii++)
      {
         drive_path[0]=ii;
         drive_type=GetDriveType((const char *)drive_path);
         if((drive_type==DRIVE_REMOVABLE) || (drive_type==DRIVE_CDROM)) // DRIVE_CDROM - cd8 formatuotiems atmintukams
         {
// KpMsgOut(drive_path, IDI_ASTERISK, KP_MB_TESTI);

// reikia, kad netikrintu irenginiu su neikistais diskais
            if(GetVolumeInformation((const char *)drive_path, NULL, 0, NULL, NULL, NULL, NULL, 0L))
            {
// KpMsgOut("+++", IDI_ASTERISK, KP_MB_TESTI);
// KpMsgOut(drive_path, IDI_ASTERISK, KP_MB_TESTI);

               if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, m_lpszIniFName);
               strcpy(ini_path, drive_path);
               strcat(ini_path, ini_name);
               strcat(ini_path, ".");
               strcat(ini_path, ini_type);

// printf(">>> %s %d\n", ini_path, prod_ver);
// KpMsgOut(ini_path, IDI_ASTERISK, KP_MB_TESTI);

               if(SUCCEEDED(retc)) retc=LoadIniFile(ini_path, True);
               if(retc==KP_E_DIR_ERROR) retc=S_OK;
               else if(SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) retc=GetIniProdVer(&prod_ver_new);
                  if((prod_ver==prod_ver_new) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc=GetIniFlashId(&flash_id);
                     if(SUCCEEDED(retc)) retc=TestFlashId(flash_id, &found, &num_fl);

#if FALSE // #ifdef Debug // #if TRUE //
// printf("<<< %s %d %lx %d %d\n", ini_path, prod_ver_new, flash_id, found, num_fl);
char str_buf[100];
sprintf(str_buf, "<<< %s %d %lx %d %d\n", ini_path, prod_ver_new, flash_id, found, num_fl);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
                  }
               }
            }
         }

      } // for(ii='B' /* 'A'*/; (ii<='Z') && (!found) && SUCCEEDED(retc); ii++)
// :0041C8C0 E9ABFEFFFF              jmp 0041C770

      if(
         (!found) &&
// :0041C8C5 807DF800                cmp byte[ebp-08], 00
// :0041C8C9 7506                    jne 0041C8D1

         SUCCEEDED(retc) // FAILED(retc) //
// :0041C8CB 837DE400                cmp dword[ebp-1C], 000
// :0041C8CF 7D02                    jge 0041C8D3 // Audrius keièia á // // :0041C8CF 7C02                    jl 0041C8D3
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

   } // while((!found) && SUCCEEDED(retc))
// :0041C921 E91EFEFFFF              jmp 0041C744

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


//==============================================
HRESULT KpStApp::GetIniPwdRC(unsigned char *lpszPwdBuf)
{
HRESULT retc=S_OK;

   if((lpszPwdBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
      retc=GetIniElementIfNotStopped(lpszPwdBuf, IniDataBuf.lpszPwd-(unsigned char *)&IniDataBuf, KP_KWD_LEN+1);
#else
      strcpy(lpszPwdBuf, m_Ini.lpszPwd);
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
