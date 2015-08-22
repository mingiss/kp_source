// ----------------------------
// atmintukas.cpp
// atmintukas.bat paleidimas, parametras ið clipboardo
// atmintukas.exe
//


// ------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
#include <initguid.h>
#include <ddk/ntddstor.h>
#include <ddk/ntddvol.h>
// #include <ddk/usbioctl.h>
// #include <ddk/usbscan.h>
#include <setupapi.h>
#endif

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

#if Compiler != Watcom
using namespace std;
#endif

#include "md5.h"

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


// #define NO_CLIPBOARD // jei apibrëþta, atmintuko ser. nr. ima ne ið iðkarpinës, o perduoda fiktyvø 000000
#define DIRECT_SERNO // jei apibrëþta, atmintuko ser. nr. ima ið árenginio handle getDevID(), ne ið iðkarpinës

#define SER_NO_BUF_LEN 100

// #define DISK_FLASH_EXE_NAME_CHAR ("DiskFlash.exe")
// #define DISK_FLASH_EXE_NAME ((const unsigned char *)DISK_FLASH_EXE_NAME_CHAR)

#if CompilerGr==Mingw
using namespace std;
#endif


// ------------------------------------
const unsigned char lpszProdName[] = "atmintukas";
KpErrorProcClass KpErrorProc(True, 43);
int iProdVerGlob=0;
bool bServiceFl=False;
int iUpdNumGlob = -1;

KpStApp theApp;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_5+1]=
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

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
#ifdef DIRECT_SERNO
int getDevID(HANDLE h_dev)
{
HRESULT retc = S_OK;
STORAGE_DEVICE_NUMBER deviceNumber;
DWORD block;
int id_dev = 0;

	memset((void*) &deviceNumber, 0, sizeof(deviceNumber));
	KP_ASSERT(DeviceIoControl(h_dev, IOCTL_STORAGE_GET_DEVICE_NUMBER, 0, 0, &deviceNumber, sizeof(STORAGE_DEVICE_NUMBER), &block, 0),
      KP_E_SYSTEM_ERROR, GetLastError(), True);

   if(SUCCEEDED(retc))
      id_dev = (deviceNumber.DeviceType << 8) | deviceNumber.DeviceNumber;

return(id_dev);
}
#endif


// -----------------------------------------
int main(/* int argc, char** argv */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpStApp *app_ptr = NULL;
long ser_no = 0L;
unsigned char ser_no_buf[SER_NO_BUF_LEN+1];
unsigned char ser_no_txt[SER_NO_BUF_LEN+1];
unsigned char disk_name[100];
unsigned char disk_root_path[100];
unsigned char disk_letter[100];
unsigned char cmd_buf[2000];
int st_pos = 0;
time_t ltime;
tm *tm_ptr=NULL;
long dev_id = 0L;
long vid = 0L;
long pid = 0L;
ULARGE_INTEGER vol_size;
unsigned char *atm_cod_pref = NULL;
unsigned char atm_cod[TV_TAG_LEN + 1];
unsigned char atm_cod_md5[MD5_RES_WDT + TV_TAG_LEN + 1];

   app_ptr=(&theApp);
   theKpStAppPtr = /* static_cast<KpStApp *> */ (&theApp);

   if(SUCCEEDED(retc)) retc=app_ptr->InitStApp(NULL, NULL, NULL, KpStEditMode);

// ------------------------------------
   if(SUCCEEDED(retc)) retc = ReadFileContents((const unsigned char *)"atmintukas.ini", &atm_cod_pref, NULL, True, False);
   KP_ASSERT(atm_cod_pref, KP_E_SYSTEM_ERROR, null, True);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(atm_cod_pref);
   KP_ASSERT(strlen(atm_cod_pref) == 3, E_INVALIDARG, atm_cod_pref, True);

// ------------------------------------
   cout << "Atmintuko disko raidë:";
   cin >> disk_name;
   disk_name[1] = ':';
   disk_name[2] = Nul;

   strcpy(disk_root_path, disk_name);
   strcat(disk_root_path, "\\");

   strcpy(disk_letter, disk_name);
   disk_letter[1] = Nul;

#if FALSE
   if(SUCCEEDED(retc))
   {
//    if(!system(DISK_FLASH_EXE_NAME))
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

fstream in_file(DISK_FLASH_EXE_NAME_CHAR, ios_base::in);

      if(!in_file.fail())
      {
         in_file.close();

         retc = StartProcess(DISK_FLASH_EXE_NAME, (const unsigned char *)".", NULL, NULL, SW_SHOWNORMAL);
      }
   }
#endif

// -----------------------
#ifdef NO_CLIPBOARD
   strcpy(ser_no_buf, "00000000");
#else

// -----------------------
#  ifdef DIRECT_SERNO

#define SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN 1024

HANDLE h_dev = INVALID_HANDLE_VALUE;
// VOLUME_DISK_EXTENTS diskExtents;
static char path[KP_MAX_FNAME_LEN + 1];
int id_dev = 0;
const char *chr0;
const char *chr1;
DWORD block;
HANDLE h_info = INVALID_HANDLE_VALUE;
SP_DEVICE_INTERFACE_DATA interfaceData;
static char buffer[SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN+1];
SP_DEVICE_INTERFACE_DETAIL_DATA *interfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA*) buffer;

// -----------------------
   if(SUCCEEDED(retc))
   {
      sprintf(path, "\\\\.\\%s", disk_name);
      h_dev = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
      KP_ASSERT(h_dev != INVALID_HANDLE_VALUE, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

#if FALSE
   KP_ASSERT(DeviceIoControl(h_dev, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, 0, 0, &diskExtents, sizeof(diskExtents), &block, 0),
      KP_E_SYSTEM_ERROR, GetLastError(), True);

   if(h_dev != INVALID_HANDLE_VALUE) CloseHandle(h_dev);
   h_dev = INVALID_HANDLE_VALUE;

// -----------------------
   if(SUCCEEDED(retc))
   {
      sprintf(path, "\\\\.\\PHYSICALDRIVE%i", diskExtents.Extents[0].DiskNumber);
		h_dev = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
      KP_ASSERT(h_dev != INVALID_HANDLE_VALUE, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }
#endif

   if(SUCCEEDED(retc))
   {
      id_dev = getDevID(h_dev);
      KP_ASSERT(id_dev, KP_E_SYSTEM_ERROR, null, True);
   }

   if(h_dev != INVALID_HANDLE_VALUE) CloseHandle(h_dev);
   h_dev = INVALID_HANDLE_VALUE;

// -----------------------
   if(SUCCEEDED(retc))
   {
   	h_info = SetupDiGetClassDevs(&GUID_DEVINTERFACE_DISK, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
      KP_ASSERT(h_info != INVALID_HANDLE_VALUE, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   for(int nn = 0; SUCCEEDED(retc); nn++)
   {
      interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
// cout << "------------- " << nn << endl;
      KP_ASSERT(SetupDiEnumDeviceInterfaces(h_info, 0, &GUID_DEVINTERFACE_DISK, nn, &interfaceData),
         KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc))
      {
         interfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
         KP_ASSERT(SetupDiGetDeviceInterfaceDetail(h_info, &interfaceData, interfaceDetailData,
            SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN, &block, 0),
               KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      if(SUCCEEDED(retc))
      {
         h_dev = CreateFile(interfaceDetailData->DevicePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
         if(h_dev != INVALID_HANDLE_VALUE)
         {
// cout << "........ " << hex << id_dev << " " << hex << getDevID(h_dev) << " " << interfaceDetailData->DevicePath << endl;
            if(getDevID(h_dev) == id_dev)
            {
               KP_ASSERT(interfaceDetailData->DevicePath, KP_E_SYSTEM_ERROR, null, True);
               KP_ASSERT(strlen(interfaceDetailData->DevicePath) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
               if(SUCCEEDED(retc)) strcpy(path, interfaceDetailData->DevicePath);
               break;
            }

            CloseHandle(h_dev);
            h_dev = INVALID_HANDLE_VALUE;
         }
         else KP_WARNING(KP_E_FILE_NOT_FOUND, interfaceDetailData->DevicePath);
      }
   }

   if(h_info != INVALID_HANDLE_VALUE) SetupDiDestroyDeviceInfoList(h_info);
   h_info = INVALID_HANDLE_VALUE;

   if(h_dev != INVALID_HANDLE_VALUE) CloseHandle(h_dev);
   h_dev = INVALID_HANDLE_VALUE;

// ----------------------------------------
// \\?\usbstor#disk&ven_generic&prod_usb_flash_disk&rev_#00000000000154&0#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}
// !!!! Raimis turi atmintuką, kurio varde yra ampersendas, kuris po to laužia komandą system() – pirmas atmintukas.bat parametras ser_no_txt prasideda ampersandu

// printf("------------------- path: %s\n", path);
// fstream out_file("serno.txt", ios::out | ios::ate);
// out_file << path << endl;
// out_file.close();

// -----------------------
   ser_no_buf[0] = Nul;
   ser_no_txt[0] = Nul;

   if(SUCCEEDED(retc))
   {
// cout << path << endl;
      chr0 = strrchr(path, '&');
      KP_ASSERT(chr0, KP_E_SYSTEM_ERROR, null, True);
   }
   if(SUCCEEDED(retc))
   {
      chr1 = strchr(path, '#');
      KP_ASSERT(chr1, KP_E_SYSTEM_ERROR, null, True);
   }
   if(SUCCEEDED(retc))
   {
      chr1 = strchr(chr1 + 1, '#');
      KP_ASSERT(chr1, KP_E_SYSTEM_ERROR, null, True);
   }
   if(SUCCEEDED(retc))
   {
      chr1 += 1;
      KP_ASSERT((chr0 - chr1) < SER_NO_BUF_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   }

   if(SUCCEEDED(retc))
      sprintf((char *)ser_no_buf, "%.*s", chr0 - chr1, chr1);

// --------------------------
#  else // #  ifdef DIRECT_SERNO

   if(SUCCEEDED(retc))
      if(!system("UVCView.x86.exe"))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      strcpy(ser_no_buf, "        ");
      retc = KpGetClipboardData(HWND_DESKTOP, CF_TEXT, ser_no_buf + MAX_LONG_HEX_DIGITS, SER_NO_BUF_LEN - MAX_LONG_HEX_DIGITS, True);
      ser_no_buf[SER_NO_BUF_LEN] = Nul;
   }

#  endif // #  ifdef DIRECT_SERNO

#endif // #else // #ifdef NO_CLIPBOARD

   if(SUCCEEDED(retc))
   {
      st_pos = strlen(ser_no_buf) - MAX_LONG_HEX_DIGITS;
      if(st_pos < 0) st_pos = 0;

      strcpy(ser_no_txt, ser_no_buf + st_pos); // tekstinis kodas atmintuko identifikacijai ir paieðkai

      retc = ForceTextToHex(ser_no_buf + st_pos); // ðeðioliktainis kodas pririðimui
   }

// ----------------------- ser_no – deðimtainis kodas lipdukui
   ser_no = 0L;
   if(SUCCEEDED(retc))
      if(sscanf((const char *)ser_no_buf + st_pos, "%lx", &ser_no) != 1)
      {
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         ser_no = 0L;
      }



// -------------------------- dev_id – ðeðioliktainis kodas pririðimui
   dev_id = ser_no;

// long dev_id_0 = ser_no;
// long dev_id_vid = ser_no;
// long dev_id_pid = ser_no;

// ------------------ vid/pid --> dev_id
   if(SUCCEEDED(retc)) retc = GetFlashVidPid(ser_no_txt, &vid, &pid);
   if(SUCCEEDED(retc))
   {
      dev_id ^= vid;
// dev_id_vid = dev_id;
      dev_id ^= pid;
// dev_id_pid = dev_id;
   }

// ----------------- vol_size --> dev_id
   vol_size.HighPart = vol_size.LowPart = 0L;
   if(SUCCEEDED(retc))
   {
      vol_size.HighPart = vol_size.LowPart = 0L;
      if(!GetDiskFreeSpaceEx((char const *)disk_name, NULL, &vol_size, NULL))
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         vol_size.HighPart = vol_size.LowPart = 0L;
      }
   }
   if(SUCCEEDED(retc)) dev_id ^= vol_size.LowPart;

   if(SUCCEEDED(retc))
   {
// ----------------------- ser_no – deðimtainis kodas lipdukui
      ser_no = ser_no & 0xFFFF;
      ser_no = ser_no ^ 0xFFFF;

// ----------------
      time(&ltime);
      tm_ptr = gmtime(&ltime);

unsigned char date_buf[TV_TAG_LEN + 1];
      sprintf((char *)date_buf, "%04d.%02d.%02d", 1900 + tm_ptr->tm_year, 1 + tm_ptr->tm_mon, tm_ptr->tm_mday);

// ----------------
// fstream out_file("serno.txt", ios::out | ios::ate);
// out_file << path << endl;
// out_file << "ser_no_hex: " << hex << dev_id_0 << " vid: " << vid << " pid: " << pid << " vol_size: " << dec << vol_size.LowPart << " " << hex << vol_size.LowPart << endl;
// out_file << "dev_id: orig: " << hex << dev_id_0 << " ^vid: " << dev_id_vid << " ^pid: " << dev_id_pid << " ^vol_size: " << dev_id << endl;
// out_file << endl;
// out_file.close();

// ---------------- tekstinis atm. kodas
      sprintf((char *)atm_cod, "%s-%05d-%03d", atm_cod_pref, ser_no, (int)(ltime % 1000)); // (int)(ltime & 0x1FF));
      sprintf((char *)atm_cod + strlen(atm_cod), "%01d", ChSum(atm_cod));


// ---------------- registruoju pas Gintarą
// http://www.tev.lt/usbraktai.php?raktas=".$cele[0]."&id=".md5($cele[0]."w0r1UkazZ")."&data=".$cele[2]."
// ".$cele[0]." – atmintuko lic. kodas
// ".md5($cele[0]."w0r1UkazZ")." - md5 nuo lic. kodo su uodega
// ".$cele[2]." - data
// http://www.tev.lt/usbraktai.php?raktas=T78-65503-3301&id=018beee215e14e453fa2447bc9085ac7&data=2012.01.04
//

unsigned char get_cmd[KP_MAX_FNAME_LEN + 1];
      strcpy(get_cmd, KPST_USBRAKTAI_FILE); // "/usbraktai.php"

      strcat(get_cmd, KPST_USBRAKTAI_RAKTAS); // "?raktas="
      strcat(get_cmd, atm_cod);

      strcat(get_cmd, KPST_USBRAKTAI_ID); // "&id="
      strcpy(atm_cod_md5, atm_cod);
      strcat(atm_cod_md5, KPST_USBRAKTAI_ID_TAIL); // "w0r1UkazZ"
unsigned char *hash_ptr = null;
      hash_ptr = (unsigned char *)MD5String((char *)atm_cod_md5);
      KP_ASSERT(hash_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(strlen(hash_ptr) == MD5_RES_WDT, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) strcat(get_cmd, hash_ptr);
      if(hash_ptr != null) free(hash_ptr);
      hash_ptr = null;

      if(SUCCEEDED(retc))
      {
         strcat(get_cmd, KPST_USBRAKTAI_DATA); // "&data="
         strcat(get_cmd, date_buf);
      }

KpSocket *sock_ptr = NULL;
      KP_NEWO(sock_ptr, KpSocket());

      if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(KPST_USBRAKTAI_URL, True); // "http://www.tev.lt/usbraktai.php"
      if(SUCCEEDED(retc)) retc = sock_ptr->Connect(True);

      if(SUCCEEDED(retc)) retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD, get_cmd, True);

unsigned char *rcv_buf = null;
long read = TV_TAG_LEN;
      KP_NEWA(rcv_buf, unsigned char, TV_TAG_LEN + 100);

      if(SUCCEEDED(retc)) retc = sock_ptr->RcvHttpMsg(rcv_buf, &read, True);
      KP_ASSERT(read < TV_TAG_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) rcv_buf[read] = Nul;

      KP_ASSERT(read >= strlen(KPST_USBRAKTAI_OK), KP_E_TRANS_ERR, null, True);
      if(SUCCEEDED(retc))
         if(strcmp(rcv_buf + read - strlen(KPST_USBRAKTAI_OK), KPST_USBRAKTAI_OK) != 0)
         {
            KP_ASSERT(read >= strlen(KPST_USBRAKTAI_ERR), KP_E_TRANS_ERR, null, True);
            KP_ASSERT(strcmp(rcv_buf + read - strlen(KPST_USBRAKTAI_ERR), KPST_USBRAKTAI_ERR) != 0, KP_E_REFUSED, null, True);
            if(SUCCEEDED(retc)) KP_ERROR(KP_E_TRANS_ERR, null);
         }
#if FALSE
printf(">>>%s<<< >>>%s<<< %d %x\n", get_cmd, rcv_buf, read, retc);
fstream out_file("atmintukas.lst", ios_base::out);
out_file << get_cmd << endl;
out_file.close();
#endif
      KP_DELETE(sock_ptr);

      KP_DELETEA(rcv_buf);

      retc = S_OK;

// ---------------- paleidžiam batą
//    sprintf((char *)cmd_buf, "atmintukas.bat %s %05d%01d %04d.%02d.%02d %s %s %s %s",
//    sprintf((char *)cmd_buf, "atmintukas.bat %s %s-%05d%1d-%03d %04d.%02d.%02d %s %s %08lX %s",
//    sprintf((char *)cmd_buf, "atmintukas.bat %s %s%01d %s %s %s %08lX %s",
      sprintf((char *)cmd_buf, "atmintukas.bat %s %s %s %s %s %08lX %s",
         ser_no_txt, // ser_no_buf + st_pos, // tekstinis kodas atmintuko identifikacijai ir paieðkai
//       atm_cod_pref, ser_no, ChSum(ser_no), (int)(ltime & 0x1FF), // kodas lipdukui
         atm_cod, // ChSum(atm_cod), // kodas lipdukui
         date_buf,
         disk_root_path, disk_name,
         dev_id, // ser_no_buf + st_pos, // ðeðioliktainis kodas pririðimui
         disk_letter);

// cout << cmd_buf << endl;

   /* if(! */ system((const char *)cmd_buf) /* ) */ ;
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

// ----------------------------------
   /* if(SUCCEEDED(retc)) */ retc0 = app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

   KP_DELETEA(atm_cod_pref);

// system("pause");

return(RET_CODE_MAIN(retc));
}

