// ---------------------------
// kpstaf.cpp
// 8cd atmintuko perregistravimas i CD-ROM ir atgal
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <winioctl.h>

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
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpttucf.h"
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
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"


// -----------------------------------------
#define TEV_AUTORUN_PRODVER_STR "1017"


// -----------------------------------------
const unsigned char *lpszaAutoRunKwds[VT_MaxAutoRunKwd_1 + 1] =
{
   (const unsigned char *)"Open",
   (const unsigned char *)"Icon",
   (const unsigned char *)"Action",
   (const unsigned char *)"VolType",
   (const unsigned char *)"StartIn",

   null
};

const unsigned char *lpszaLockActionKwds[VT_MaxFlashAction_1 + 1] =
{
   (const unsigned char *)"unlock",       // Fl_ToCd
   (const unsigned char *)"restore",      // Fl_ToFlash
   (const unsigned char *)"restoreall",   // Fl_ToFlashAll

   null, // Fl_ToHd
   null, // Fl_Delete
   null, // Fl_CountOnly
   null, // Fl_SetRegAccess

   null
};


const unsigned char *lpszaVolTypeKwds[VT_MaxVolType_2 + 1] =
{
   (const unsigned char *)"CDROM",        // Vt_CDROM
   (const unsigned char *)"TevCDROM",     // Vt_TevCDROM
   (const unsigned char *)"TevLiveCD",    // Vt_TevLiveCD

   (const unsigned char *)"Removable",    // Vt_Removable
   (const unsigned char *)"FlashUSB",     // Vt_FlashUSB
   (const unsigned char *)"TevLocked",    // Vt_TevLocked
   (const unsigned char *)"TevUnLocked",  // Vt_TevUnLocked
   (const unsigned char *)"FlashCDROM",   // Vt_FlashCDROM
   (const unsigned char *)"FlashRO",      // Vt_FlashRO
   (const unsigned char *)"FlashRW",      // Vt_FlashRW
   (const unsigned char *)"FlashTUX",     // Vt_FlashTUX

   null
};


// -----------------------------------------
// iesko 8cd formato atmintuko
// suranda jo (arba siaip vienintelio prijungto) ser, nr.
// #define Check8cd // ar ieskoti atmintuko su 8cd zyme?
HRESULT GetFlashRam
(
   FlashActions
#ifdef Check8cd
      iFlashAction         // in
#endif
      ,
   int *piDevNum,          // out - rasto atmintuko irenginio nr.
   long *plSerNo           // out - rasto atmintuko ser. nr.
)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char key_name[KP_MAX_FNAME_LEN+1];
HKEY hKey=0;
LONG retw=ERROR_SUCCESS;
DWORD dwBufLen;
DWORD dwValType;
int dev_count=-1;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
int st_pos;
int dev_num = -1;
long ser_no = -1L;
unsigned char dev_name[100];
#ifdef Check8cd
MEDIA_TYPE phys_med_typ = Unknown;
UINT log_med_typ = DRIVE_UNKNOWN;
int dev;
int dev_from=0;
int dev_to=0;
HANDLE raw_file = INVALID_HANDLE_VALUE;
void *mbr_buf = NULL;
MBR_Record mbr;
DWORD num_bytes;
bool found = False;
#endif

// --------------------------
   if(((piDevNum == NULL) || (plSerNo == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

#ifdef Check8cd
   if(SUCCEEDED(retc)) switch(iFlashAction)
   {
   case Fl_ToCd:
      log_med_typ = DRIVE_REMOVABLE;
      phys_med_typ = RemovableMedia;

      dev_from = 0;
      dev_to = 10;
      break;

   case Fl_ToFlash:
   case Fl_ToFlashAll:
      log_med_typ = DRIVE_CDROM;
      phys_med_typ = FixedMedia; // CD-ROM-ui atskiro tipo nera :(

      dev_from = 1;
      dev_to = 'Z'-'A';
      break;

// case :
//    log_med_typ = DRIVE_FIXED;
//    phys_med_typ = FixedMedia;
//    break;

   }
#endif

   if(SUCCEEDED(retc)) dev_num = -1;


// ----------------------------- check count of USB Flash sticks
   if(SUCCEEDED(retc))
//    if(iWindowsVersion<WinXP)
      {
//       strcpy(key_name, "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum");
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

         hKey = 0;
         retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_QUERY_VALUE, &hKey);
         if(retw!=ERROR_SUCCESS)
         {
// ka tik ijungus kompa nebuna visai
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            retc = KP_E_FILE_NOT_FOUND;
         }

         if(SUCCEEDED(retc))
         {
//          strcpy(key_name, "Count");
            key_name[0]='C';
            key_name[1]='o';
            key_name[2]='u';
            key_name[3]='n';
            key_name[4]='t';
            key_name[5]=Nul;

            dwBufLen=sizeof(dev_count);
            if(RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)&dev_count, &dwBufLen)==ERROR_SUCCESS)
            {
               if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            }
         }
         if(SUCCEEDED(retc))
         {
            if(dev_count<1) retc = KP_E_FILE_NOT_FOUND; // nera nei vieno
            else if(dev_count > 1)
            {
#if FALSE // nereikia, jei keli - rakinam paskutini
               KpMsgOut("Matau kelis atmintukus, atrakinti galima tik vienà. Iðtraukite visas ðiuo metu nereikalingas USB iðorinës atminties laikmenas.", IDI_WARNING, KP_MB_TESTI);

               if(RegQueryValueEx(hKey, (const char *)key_name, NULL, &dwValType, (LPBYTE)&dev_count, &dwBufLen)==ERROR_SUCCESS)
               {
                  if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               }

               if(dev_count<1) retc = KP_E_FILE_NOT_FOUND; // neliko nei vieno
               else if(dev_count > 1) retc = KP_E_DOUBLE_CALL; // vis dar keli
#endif
            }
         }

      } // if((iWindowsVersion<WinXP) && SUCCEEDED(retc))

//=======================================================
#ifdef Check8cd

// --------------------------
   if(SUCCEEDED(retc))
   {
      mbr_buf = VirtualAlloc(NULL, KILO_BYTE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
      if(mbr_buf == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   for(dev=dev_from; (dev<dev_to) && (dev_num < 0) && SUCCEEDED(retc); dev++)
   {

// --------------------------
      raw_file = INVALID_HANDLE_VALUE;

      if(SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) switch(iFlashAction)
         {
         case Fl_ToCd:
            sprintf((char *)dev_name, "\\\\.\\PhysicalDrive%d", dev);
            break;
         case Fl_ToFlash:
         case Fl_ToFlashAll:
            sprintf((char *)dev_name, "\\\\.\\%c:", 'A' + dev);
            break;
         }

         raw_file = CreateFile(
            (LPCTSTR)dev_name, // LPCTSTR lpFileName,
            FILE_READ_DATA, // GENERIC_READ, // GENERIC_WRITE, // DWORD dwDesiredAccess,
            FILE_SHARE_READ, // 0, // DWORD dwShareMode,
            NULL, // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            OPEN_EXISTING, // CREATE_ALWAYS, // DWORD dwCreationDisposition,
            FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes,
            NULL // HANDLE hTemplateFile
            );
//       if(raw_file == INVALID_HANDLE_VALUE)
//          retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// jei klaida - nieko nedaryti, tiesiog kol kas neradom ir tiek
      }


      if((raw_file != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {

// -------------------------- ar atitinka ieskoma tipa (REMOWABLE, etc.)?
static DISK_GEOMETRY disk_geom[1];
DWORD ll;
UINT drive_type;

         found = False;
         if(SUCCEEDED(retc)) switch(iFlashAction)
         {
         case Fl_ToCd:

            if(!DeviceIoControl(
               raw_file, // HANDLE hDevice,
               IOCTL_DISK_GET_DRIVE_GEOMETRY, // IOCTL_STORAGE_GET_MEDIA_TYPES, // DWORD dwIoControlCode,
               NULL, // LPVOID lpInBuffer,
               0, // DWORD nInBufferSize,
               disk_geom, // LPVOID lpOutBuffer,
               sizeof(disk_geom), // DWORD nOutBufferSize,
               &num_bytes, // LPDWORD lpBytesReturned,
               NULL // LPOVERLAPPED lpOverlapped
               ))
            {
               ll = GetLastError();
               if(ll != ERROR_NOT_READY) // ERROR_RESOURCE_NAME_NOT_FOUND)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);

// jei tik ERROR_NOT_READY - irenginys be tomo, nieko nedaryti, einam toliau
            }
            else
            {
               if((disk_geom[0].MediaType == phys_med_typ) && SUCCEEDED(retc)) found = True;
            }
            break;

         case Fl_ToFlash:
         case Fl_ToFlashAll:

            drive_type=GetDriveType((const char *)dev_name+4); // "\\.\I:"
            if((drive_type == log_med_typ) && SUCCEEDED(retc)) found = True;
            break;
         }


         if(found && SUCCEEDED(retc))
         {

// -------------------------- bandom skaityti MBR sektoriu
            if(!ReadFile(raw_file, mbr_buf, /* sizeof(MBR_Record) */ KILO_BYTE, &num_bytes, NULL))
            {
// vel "no volume in the drive"
//             retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// nieko nedaryti, pereinam prie tolesnio irenginio
            }
            else
            {

               if((num_bytes != /* sizeof(MBR_Record) */ KILO_BYTE) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               if(SUCCEEDED(retc))
               {
                  memcpy(&mbr, mbr_buf, sizeof(mbr));

// ar disko zyme "8cd"?
                  if(strcmp((char *)&mbr.m_iDiskSignature, "8cd") == 0)
                  {
// radom, ieskom ser. no.
// gal dar patikrint, ar nera kitu tokiu? atrakinti galima tik viena

                     dev_num = dev;

#if FALSE
                     if(iWindowsVersion>=WinXP)
                     {
// --------------------------
MEDIA_SERIAL_NUMBER_DATA serno_data;

                        if(SUCCEEDED(retc))
                           if(!DeviceIoControl(
                              raw_file, // (HANDLE) hDevice,                      // handle to device
                              IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER, // dwIoControlCode
                              NULL,                                  // lpInBuffer
                              0,                                     // nInBufferSize
                              &serno_data, // (LPVOID) lpOutBuffer,                  // output buffer
                              sizeof(serno_data), // (DWORD) nOutBufferSize,                // size of output buffer
                              &num_bytes, // (LPDWORD) lpBytesReturned,             // number of bytes returned
                              NULL // (LPOVERLAPPED) lpOverlapped            // OVERLAPPED structure
                              ))
                                 retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

                        if(SUCCEEDED(retc)) if(num_bytes!=sizeof(serno_data))
                           retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);


#if FALSE
unsigned char str_buf[100];
if(SUCCEEDED(retc))
{
sprintf((char *)str_buf, "%ld", serno_data.SerialNumberLength);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
}
#endif // #if FALSE


//                      if(SUCCEEDED(retc)) ser_no =

// TODO: ser. no. inside XP !!!


                     }
                     else // if(iWindowsVersion>=WinXP)
#endif // #if FALSE
                     {


// =============================================
#else // #ifdef Check8cd

   dev_num = dev_count-1;

#endif
// =============================================

                        if((hKey==0) && SUCCEEDED(retc))
                           retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                        if(SUCCEEDED(retc))
                        {
                           dwBufLen=KP_MAX_FNAME_LEN;
unsigned char str_buf[100];
                           sprintf((char *)str_buf, "%d", dev_count-1);
                           retw=RegQueryValueEx(hKey, (const char *)str_buf /* "0" */, NULL, NULL,
                              (LPBYTE)dev_name, &dwBufLen);
                           if(retw==ERROR_SUCCESS) dev_name[dwBufLen]=Nul;
                           else
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                        }

// "USB\\Vid_3538&Pid_0042\\00000000000B18" - lauko reiksme
// ser. no. = 0x0B18

                        if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, dev_name);

                        if(SUCCEEDED(retc))
                        {
                           ser_no = -1L;
                           st_pos=strlen(name)-8;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
                           if(st_pos<0) st_pos=0;
                           if(sscanf((const char *)name+st_pos, "%lx", &ser_no)!=1)
                           {
                              ser_no = -1L;
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                           }
                        }

#ifdef Check8cd
                     } // else // if(iWindowsVersion>=WinXP)

                  } // if(strcmp((char *)&mbr->m_iDiskSignature, "8cd") == 0)

               } // if(SUCCEEDED(retc)) // if((num_bytes != /* sizeof(MBR_Record) */ KILO_BYTE) && SUCCEEDED(retc))

            } // else // if(!ReadFile(raw_file, mbr_buf, /* sizeof(MBR_Record) */ KILO_BYTE, &num_bytes, NULL))

// --------------------------
         } // if(found && SUCCEEDED(retc))


// --------------------------
      } // if((raw_file != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))

      if(raw_file != INVALID_HANDLE_VALUE)
      {
         if(!CloseHandle(raw_file))
         {
            retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) retc = retc0;
         }
         raw_file = INVALID_HANDLE_VALUE;
      }

// --------------------------
   } // for(dev=0; (dev<10) && SUCCEEDED(retc); dev++)


// --------------------------
   if(mbr_buf)
   {
      if(!VirtualFree(mbr_buf, 0, MEM_RELEASE))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      mbr_buf = NULL;
   }
#endif // #ifdef Check8cd


// --------------------------
   if((dev_num < 0) && SUCCEEDED(retc)) retc = KP_E_FILE_NOT_FOUND;

   if(SUCCEEDED(retc))
   {
      *piDevNum = dev_num;
      *plSerNo = ser_no;
   }

return(retc);
}


// -----------------------------------------
HRESULT FlashToCdRom
(
   long lSerNo,               // in - atmintuko ser. nr.
   FlashActions iFlashAction, // in
   int *piMatches             // out - rastu atmintuku irasu skaicius
                              //    0 - nerado, grazina KP_E_FILE_NOT_FOUND
                              //    >1 - rado kelis, blogai - sugadins kito atmintuko skaityma, grazina KP_E_DOUBLE_CALL
)
{
HRESULT retc = S_OK;
static unsigned char key_name[KP_MAX_FNAME_LEN+1];
static unsigned char sub_key_name[KP_MAX_FNAME_LEN+1];
static unsigned char sub_sub_key_name[KP_MAX_FNAME_LEN+1];
static unsigned char cur_key_name[KP_MAX_FNAME_LEN+1];
DWORD key_len;
HKEY hKey=0;
HKEY hSubKey=0;
HKEY hSubSubKey=0;
LONG retw=ERROR_SUCCESS;
bool done = False;
bool sub_done = False;
int matches = 0;
int cur_key = 0;
int cur_sub_key = 0;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
const unsigned char *pnts;
unsigned char *pntd;
int st_pos;
long cur_ser_no;
bool found = False;

// ------------------------------------
   if((piMatches == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);


// ------------------------------------
// reikia rasti toki rakta:
// "SYSTEM\\CurrentControlSet\\Enum\\USBSTOR\\Disk&Ven_Generic&Prod_USB_Flash_Disk&Rev_0.00\\00000000000B18&0"
// 0xB18 - lSerNo

   if(SUCCEEDED(retc))
   {
//    strcpy(key_name, "SYSTEM\\CurrentControlSet\\Enum\\USBSTOR");
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
      key_name[25]='E';
      key_name[26]='n';
      key_name[27]='u';
      key_name[28]='m';
      key_name[29]='\\';
      key_name[30]='U';
      key_name[31]='S';
      key_name[32]='B';
      key_name[33]='S';
      key_name[34]='T';
      key_name[35]='O';
      key_name[36]='R';
      key_name[37]=Nul;

      hKey = 0;
      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)key_name, 0, KEY_ENUMERATE_SUB_KEYS, &hKey);
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      done = False;
      matches = 0;
      cur_key = 0;
      while((!done) && SUCCEEDED(retc))
      {
         key_len = KP_MAX_FNAME_LEN;
         retw=RegEnumKeyEx(
            hKey, // HKEY hKey,
            cur_key, // DWORD dwIndex,
            (char *)sub_key_name, // LPTSTR lpName,
            &key_len, // LPDWORD lpcName,
            NULL, // LPDWORD lpReserved,
            NULL, // LPTSTR lpClass,
            NULL, // LPDWORD lpcClass,
            NULL // PFILETIME lpftLastWriteTime
            );
         if(retw == ERROR_NO_MORE_ITEMS) done = True;
         else if(retw!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

         if((!done) && (retw==ERROR_SUCCESS))
         {
// KpMsgOut(sub_key_name, IDI_ASTERISK, KP_MB_TESTI);

//          if((strstr(sub_key_name, "CdRom") == sub_key_name) || (iFlashAction != Fl_ToFlashAll))
            if((strstr(sub_key_name, "Disk") == sub_key_name) || (iFlashAction != Fl_ToFlashAll))
            {

               if(strlen(key_name) + strlen(sub_key_name) + 2 >= KP_MAX_FNAME_LEN)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

               if(SUCCEEDED(retc))
               {
                  strcpy(cur_key_name, key_name);
                  strcat(cur_key_name, "\\");
                  strcat(cur_key_name, sub_key_name);

                  hSubKey = 0;
                  if(SUCCEEDED(retc))
                  {
                     retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)cur_key_name, 0,
                           KEY_ENUMERATE_SUB_KEYS, &hSubKey);
                     if(retw!=ERROR_SUCCESS)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                  }

                  sub_done = False;
                  cur_sub_key = 0;

                  while((!sub_done) && SUCCEEDED(retc))
                  {
                     key_len = KP_MAX_FNAME_LEN;
                     retw=RegEnumKeyEx(
                        hSubKey, // HKEY hKey,
                        cur_sub_key, // DWORD dwIndex,
                        (char *)sub_sub_key_name, // LPTSTR lpName,
                        &key_len, // LPDWORD lpcName,
                        NULL, // LPDWORD lpReserved,
                        NULL, // LPTSTR lpClass,
                        NULL, // LPDWORD lpcClass,
                        NULL // PFILETIME lpftLastWriteTime
                        );
                     if(retw == ERROR_NO_MORE_ITEMS) sub_done = True;
                     else if(retw!=ERROR_SUCCESS)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

                     if((!sub_done) && (retw==ERROR_SUCCESS))
                     {

#if FALSE
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
strcpy(str_buf, cur_key_name);
strcat(str_buf, "\\");
strcat(str_buf, sub_sub_key_name);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif

                        found = False;

                        if(iFlashAction != Fl_ToFlashAll)
                        {
// ---------------------- istraukiam ser.no.
                           if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, sub_sub_key_name);

                           if(SUCCEEDED(retc))
                           {
                              pntd = strchr(name, '&');
                              if(pntd==NULL)
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                              else
                                 *pntd=Nul;
                           }

                           if(SUCCEEDED(retc))
                           {
                              cur_ser_no = -1L;
                              st_pos=strlen(name)-8;  // skaitmenu gali buti daugiau, negu tilps i long (8 sesioliktainiai skaitmenys)
                              if(st_pos<0) st_pos=0;
                              if(sscanf((const char *)name+st_pos, "%lx", &cur_ser_no)!=1)
                              {
                                 cur_ser_no = -1L;
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                              }
                           }

                           if((cur_ser_no == lSerNo) && SUCCEEDED(retc)) found = True;

                        } // if(iFlashAction != Fl_ToFlashAll)


// ------------------ tinka
                        if((found || (iFlashAction == Fl_ToFlashAll)) && SUCCEEDED(retc))
                        {
                           if(strlen(key_name) + strlen(sub_key_name) + strlen(sub_sub_key_name) + 3 >= KP_MAX_FNAME_LEN)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

                           hSubSubKey = 0;

                           if(SUCCEEDED(retc))
                           {
                              strcpy(cur_key_name, key_name);
                              strcat(cur_key_name, "\\");
                              strcat(cur_key_name, sub_key_name);
                           }

                           if(SUCCEEDED(retc)) if(iFlashAction == Fl_Delete)
                           {
//                            retc = SetRegKeyAccess(cur_key_name);

                              hSubSubKey = 0;
                              if(SUCCEEDED(retc))
                              {
                                 retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)cur_key_name, 0,
                                    KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, // | DELETE // atveriam subkey trynimui
                                    &hSubSubKey);
                                 if(retw!=ERROR_SUCCESS)
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                              }
                           }

                           if(SUCCEEDED(retc))
                           {
                              strcat(cur_key_name, "\\");
                              strcat(cur_key_name, sub_sub_key_name);
                           }

                        }

                        if((iFlashAction == Fl_ToFlashAll) && SUCCEEDED(retc))
                        {
DWORD val_typ;
unsigned char val_buf[100];
DWORD val_nbytes = sizeof(val_buf);

                           hSubSubKey = 0;
                           if(SUCCEEDED(retc))
                           {
                              retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)cur_key_name, 0,
                                 KEY_QUERY_VALUE, &hSubSubKey);
                              if(retw!=ERROR_SUCCESS)
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                           }

                           if(SUCCEEDED(retc))
                              if(ERROR_SUCCESS!=RegQueryValueEx(hSubSubKey, "Service", NULL, &val_typ, (BYTE *)val_buf, &val_nbytes))
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                           if((val_typ!=REG_SZ) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);

                           if(SUCCEEDED(retc)) if(strcmp(val_buf, "cdrom") == 0) found = True;

                           if(hSubSubKey)
                           {
                              retw=RegCloseKey(hSubSubKey);
//                            if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
                              if(retw!=ERROR_SUCCESS)
                                 KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
                              hSubSubKey=0;
                           }
                        }


// --------------- tinka ir Fl_ToFlashAll

                        if(found && SUCCEEDED(retc))
                        {
                           matches++;

// tikrinam, ar adminas
                           hSubSubKey = 0;
                           if(SUCCEEDED(retc))
                           {
                              retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)cur_key_name, 0,
                                 WRITE_DAC , &hSubSubKey);
                              if(retw!=ERROR_SUCCESS)
                              {
                                 retc = KP_E_ACCESS_DENIED;
                                 KpMsgOut("Atmintuko atrakinimui reikia papildomø privilegijø, prisijunkite administratoriumi", IDI_ERROR, KP_MB_TESTI);
                                 KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
//                               KpErrorProc.OutputErrorMessage(retc, cur_key_name, False, __FILE__, __LINE__, 0L, NULL);
                              }
                           }
                           if(hSubSubKey)
                           {
                              retw=RegCloseKey(hSubSubKey);
//                            if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
                              if(retw!=ERROR_SUCCESS)
                                 KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
                              hSubSubKey=0;
                           }

// gerai - rakinam
                           if(SUCCEEDED(retc)) retc = SetRegKeyAccess(cur_key_name);

                           if(SUCCEEDED(retc)) switch(iFlashAction)
                           {
                           case Fl_ToCd:
                           case Fl_ToFlash:
                           case Fl_ToFlashAll:
                           case Fl_ToHd:
// atveriam lauku rasymui
                              hSubSubKey = 0;
                              if(SUCCEEDED(retc))
                              {
                                 retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)cur_key_name, 0,
                                    KEY_SET_VALUE, &hSubSubKey);
                                 if(retw!=ERROR_SUCCESS)
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                              }

                              break;

                           } // switch(iFlashAction)

                           if(SUCCEEDED(retc)) switch(iFlashAction)
                           {
                           case Fl_ToCd:
// #if FALSE
// "ClassGUID"="{4D36E965-E325-11CE-BFC1-08002BE10318}"
                              if(SUCCEEDED(retc))
                              {
                                 pnts = (const unsigned char *)"{4D36E965-E325-11CE-BFC1-08002BE10318}";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "ClassGUID", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }
// "Driver"="{4D36E965-E325-11CE-BFC1-08002BE10318}"
                              if(SUCCEEDED(retc))
                              {
//                               pnts = (const unsigned char *)"{4D36E965-E325-11CE-BFC1-08002BE10318}";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "Driver", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }
// #endif
// "Service"="cdrom"
                              if(SUCCEEDED(retc))
                              {
                                 pnts = (const unsigned char *)"cdrom";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "Service", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }

                              break;

                           case Fl_ToFlash:
                           case Fl_ToFlashAll:
// #if FALSE
// "ClassGUID"="{4D36E967-E325-11CE-BFC1-08002BE10318}"
                              if(SUCCEEDED(retc))
                              {
                                 pnts = (const unsigned char *)"{4D36E967-E325-11CE-BFC1-08002BE10318}";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "ClassGUID", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }
// "Driver"="{4D36E967-E325-11CE-BFC1-08002BE10318}"
                              if(SUCCEEDED(retc))
                              {
//                               pnts = (const unsigned char *)"{4D36E967-E325-11CE-BFC1-08002BE10318}";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "Driver", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }
// #endif
// "Service"="disk"
                              if(SUCCEEDED(retc))
                              {
                                 pnts = (const unsigned char *)"disk";
                                 if(ERROR_SUCCESS!=RegSetValueEx(hSubSubKey, "Service", 0, REG_SZ, (BYTE *)pnts, strlen(pnts)+1))
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                              }

                              break;

                           case Fl_ToHd:
// TODO: !!!
                              if(SUCCEEDED(retc))
                                 retc = KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);
                              break;


                           case Fl_Delete:
// trinam rakta
                              if(SUCCEEDED(retc)) retc=KpRegDeleteTree(hSubSubKey, sub_sub_key_name);

                              cur_sub_key--; // istrynus pasislinko

                              break;

                           } // switch(iFlashAction)

                           if(hSubSubKey)
                           {
                              retw=RegCloseKey(hSubSubKey);
//                            if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
                              if(retw!=ERROR_SUCCESS)
                                 KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
                              hSubSubKey=0;
                           }

                        }

                     } // if((!sub_done) && (retw==ERROR_SUCCESS))

                     cur_sub_key++;

                  } // while((!sub_done) && SUCCEEDED(retc))

//-------------------
                  if(hSubKey)
                  {
                     retw=RegCloseKey(hSubKey);
//                   if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
                     if(retw!=ERROR_SUCCESS)
                        KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
                     hSubKey=0;
                  }

               } // if(SUCCEEDED(retc))



            } // if((strstr(sub_key_name, "Disk") == sub_key_name) || (iFlashAction != Fl_ToFlashAll))

         } // if((!done) && (retw==ERROR_SUCCESS))

         cur_key++;

      } // while((!done) && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
      hKey=NULL;
   }

   if(SUCCEEDED(retc))
   {
      *piMatches = matches;

      if(iFlashAction != Fl_ToFlashAll)
      {
         if(matches < 1) retc = KP_E_FILE_NOT_FOUND;
         else if(matches >1) retc = KP_E_DOUBLE_CALL;
      }
   }

return(retc);
}


// --------------------------------------
HRESULT LockFlash(FlashActions iLockAction)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
int dev_num = -1;
long ser_no = 0L;
int matches=0;
unsigned char str_buf[100];
HKEY hKey=0;
LONG retw=ERROR_SUCCESS;
bool found = True;
DWORD val_typ;
long upd_num;
DWORD val_nbytes;


// -------------------------------
#if FALSE
HANDLE system_user;

   if(SUCCEEDED(retc))
      if(!LogonUser("SYSTEM", KPST_CUR_DIR, "", LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &system_user))
//    if(!LogonUser("admin", KPST_CUR_DIR, "uraganas", LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &system_user))
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif


// -------------------------------
   if(SUCCEEDED(retc)) switch(iLockAction)
   {
   case Fl_ToCd:
   case Fl_ToFlash:
   case Fl_SetRegAccess:

// ------------------------------- ieskom 8cd atmintuko
      if(SUCCEEDED(retc))
      {
         retc = GetFlashRam(iLockAction, &dev_num, &ser_no);
         if(((dev_num < 0) && SUCCEEDED(retc)) || (retc == KP_E_FILE_NOT_FOUND))
         {
            KpMsgOut("Reikiamai suformatuoto atmintuko nerandu, gal neturite administratoriaus teisiø?", IDI_ERROR, KP_MB_TESTI);
            retc = KP_E_FILE_NOT_FOUND;
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         if(retc == KP_E_DOUBLE_CALL)
         {
            KpMsgOut("Negaliu atrakinti keliø atmintukø ið karto", IDI_ERROR, KP_MB_TESTI);
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

#if FALSE
if(SUCCEEDED(retc))
{
sprintf((char *)str_buf, "%lx", ser_no);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
}
#endif

// ------------------------------- skaiciuojam tokio ser. no. atmintuku draiverius
      if(SUCCEEDED(retc))
      {
         retc = FlashToCdRom(ser_no, Fl_CountOnly, &matches);

#if FALSE
if(SUCCEEDED(retc))
{
sprintf((char *)str_buf, "%lx %d", ser_no, matches);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
}
#endif

         if(((matches < 1) && SUCCEEDED(retc)) || (retc == KP_E_FILE_NOT_FOUND))
         {
            retc = KP_E_FILE_NOT_FOUND;
            KpMsgOut("Nerandu atmintuko tvarkyklës parametrø", IDI_ERROR, KP_MB_TESTI);
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }

// radom kelis draiverius, reikia ismesti
         if(((matches > 1) && SUCCEEDED(retc)) || (retc == KP_E_DOUBLE_CALL))
         {
            retc = KP_E_DOUBLE_CALL;

            retc0 = FlashToCdRom(ser_no, Fl_Delete, &matches);
            if(SUCCEEDED(retc)) retc = retc0;

            KpMsgOut("Radau kelis vienodus atmintuko tvarkyklës parametrø blokus. Atmintukà iðtraukite, vël ákiðkite ir atrakinimo procedûrà pakartokite.", IDI_WARNING, KP_MB_TESTI);
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }
      }


// ------------------
   case Fl_ToFlashAll:

// ------------------------------------ verciam i CD-ROM
      if(SUCCEEDED(retc)) retc = FlashToCdRom(ser_no, iLockAction, &matches);

// ------------------------------
      if(SUCCEEDED(retc)) switch(iLockAction)
      {
      case Fl_ToCd:
#if TRUE // FALSE
         hKey = 0;
         found = True;
         if(SUCCEEDED(retc))
         {
            retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)"Software\\TEV\\" TEV_AUTORUN_PRODVER_STR, 0,
               KEY_QUERY_VALUE, &hKey);
            if(retw!=ERROR_SUCCESS)
            {
               retw=RegOpenKeyEx(HKEY_CURRENT_USER, (const char *)"Software\\TEV\\" TEV_AUTORUN_PRODVER_STR, 0,
                  KEY_QUERY_VALUE, &hKey);
               if(retw!=ERROR_SUCCESS)
                  found = False;
            }
         }
         if(found && SUCCEEDED(retc))
         {
            val_nbytes = sizeof(upd_num);
            if(ERROR_SUCCESS != RegQueryValueEx(hKey, (const char *)"Installed", NULL, &val_typ, (BYTE *)&upd_num, &val_nbytes))
               found = False;
            else
            {
               if((val_typ!=REG_DWORD) || (val_nbytes!=sizeof(upd_num)))
                  found = False;
               else
               {
                  if(upd_num < 1) found = False;
               }
            }
         }

         if(SUCCEEDED(retc))
         {
            if(found)
               KpMsgOut("Atmintukas sëkmingai atrakintas, iðtraukite já ir vël ákiðkite.", IDI_ASTERISK, KP_MB_TESTI);
            else
            {
// !!! TODO - tik ne Vistoj
               KpMsgOut("Atmintukas sëkmingai atrakintas. Pasibaigus programos TevAutoRun diegimui, atmintukà iðtraukite ir vël ákiðkite.", IDI_ASTERISK, KP_MB_TESTI);
               retc = StartProcess((const unsigned char *)"TevAutoRunSetup.exe", KPST_CUR_DIR, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
            }
         }

         if(hKey)
         {
            retw=RegCloseKey(hKey);
//          if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, &KpTraceWindow);
#endif
            hKey=0;
         }
#else
         KpMsgOut("Atmintukas sëkmingai atrakintas, iðtraukite já ir vël ákiðkite.", IDI_ASTERISK, KP_MB_TESTI);
#endif
         break;

      case Fl_ToFlash:
         KpMsgOut("Atmintukas sëkmingai u_rakintas, iðtraukite já ir vël ákiðkite.", IDI_ASTERISK, KP_MB_TESTI);
         break;

      case Fl_ToFlashAll:
         if(matches>0) sprintf((char *)str_buf, "Visi %d atmintukø áraðai sëkmingai atstatyti", matches);
         else strcpy(str_buf, "Nerandu në vieno tinkamo atmintuko áraðo");
         KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
         break;

      } // switch(iLockAction)

// ------------------------------
      break;

   } // if(SUCCEEDED(retc)) switch(iLockAction)

return(retc);
}


// --------------------------------------
HRESULT LockFlashStr(const unsigned char *lpszLockAction)
{
HRESULT retc=S_OK;
static unsigned char action_str[KP_MAX_FNAME_LEN+1];
int kwd_ix;

   if((lpszLockAction == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      strncpy(action_str, lpszLockAction, KP_MAX_FNAME_LEN);
      action_str[KP_MAX_FNAME_LEN] = Nul;
      strlwr(action_str);

      retc = CutInitTrailSpcs(action_str);
   }
   if(SUCCEEDED(retc))
   {
      kwd_ix = Fl_None;
      if(SUCCEEDED(retc))
      {
         retc = GetKwrdIndex(&kwd_ix, action_str, lpszaLockActionKwds, -1, False, True);
         if(retc == KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, action_str, True, __FILE__, __LINE__, 0L);
      }
   }
   if(SUCCEEDED(retc)) retc = LockFlash((FlashActions)kwd_ix);

return(retc);
}


// -------------------------------------------
HRESULT ParseTevAutorun(const unsigned char *lpszPath, TevAutorunPars *pParBuf, bool bRootDir)
{
HRESULT retc=S_OK;
KpFStream autorun_file;
static unsigned char fname[KP_MAX_FNAME_LEN+1];
static unsigned char vol_fname[KP_MAX_FNAME_LEN+1];
static unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];
int kwd_ix;
int kwd_ix_1;
unsigned char *val_ptr = NULL;
UINT drive_type;
static unsigned char vol_name[KP_MAX_FNAME_LEN+1];
static unsigned char full_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_disk[KP_MAX_FNAME_LEN+1];
static unsigned char app_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_name[KP_MAX_FNAME_LEN+1];
static unsigned char app_type[KP_MAX_FTYPE_LEN+1];
DWORD ll;

   if(((lpszPath == NULL) || (pParBuf == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc))
//    if(strlen(lpszPath) + strlen(TEV_AUTORUN_INF_FNAME) + 2 >= KP_MAX_FNAME_LEN)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pParBuf->m_lpszOpen[0] = Nul;
      pParBuf->m_lpszStartIn[0] = Nul;
      pParBuf->m_lpszIcon[0] = Nul;
      pParBuf->m_iAction = Fl_None;
      pParBuf->m_iVolType = Vt_NoVol;
   }

   if(SUCCEEDED(retc))
   {
      ll = GetFullPathName((const char *)lpszPath, KP_MAX_FNAME_LEN, (char *)full_path, NULL);
      if(!ll)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      else if(ll >= KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

// ------- vol_fname   
   if(SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_name, app_type, full_path);
   KP_ASSERT(strlen(app_disk) + strlen(TEV_AUTORUN_INF_FNAME) + 2 < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(vol_fname, app_disk);
      strcat(vol_fname, "\\");
   }
      
// ------------- fname kelias su sleðu      
   if(SUCCEEDED(retc))
   {
      strcpy(fname, full_path);
      strcat(fname, "\\");
   }
   if(bRootDir && SUCCEEDED(retc)) strcpy(fname, vol_fname);

// -------------   
PutLogMessage_("ParseTevAutorun() %s", vol_fname);
   KP_ASSERT(GetVolumeInformation((const char *)vol_fname /* fname */ /* app_disk */, (char *)vol_name, KP_MAX_FNAME_LEN,
            NULL, NULL, NULL, NULL, 0), KP_E_DIR_ERROR, GetLastError(), True);
   
   if(SUCCEEDED(retc))
   {
      strcat(fname, TEV_AUTORUN_INF_FNAME);

      autorun_file.open((const char *)fname, ios::in);
      if(!autorun_file.fail())
      {
         do
         {
            autorun_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
            if(autorun_file.eof() && SUCCEEDED(retc)) retc = KP_E_EOF;
            if(SUCCEEDED(retc)) if(autorun_file.fail())
            {
               retc = KP_E_FERROR;
               KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
            {
               val_ptr = strchr(in_str, '=');
               if(val_ptr == NULL)
               {
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
                  if(SUCCEEDED(retc)) if((in_str[0] != ';') && (in_str[0] != Nul))
                     if(strcmp(in_str, "[autorun]") != 0)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str /* fname */, True, __FILE__, __LINE__, 0L);
               }
               else
               {
                  *val_ptr++ = Nul;
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(val_ptr);

                  kwd_ix = NoAutoRunIx;
                  if(SUCCEEDED(retc))
                  {
                     retc = GetKwrdIndex(&kwd_ix, in_str, lpszaAutoRunKwds, -1, False, True);
                     if(retc == KP_E_KWD_NOT_FOUND)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                     else if(SUCCEEDED(retc))
                     {
                        switch(kwd_ix)
                        {
                        case OpenIx:
                           if(strlen(val_ptr) >= KP_MAX_FNAME_LEN)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, val_ptr, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc)) strcpy(pParBuf->m_lpszOpen, val_ptr);
                           break;

                        case StartInIx:
                           if(strlen(val_ptr) >= KP_MAX_FNAME_LEN)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, val_ptr, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc)) strcpy(pParBuf->m_lpszStartIn, val_ptr);
                           break;

                        case IconIx:
                           if(strlen(val_ptr) >= KP_MAX_FNAME_LEN)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, val_ptr, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc)) strcpy(pParBuf->m_lpszIcon, val_ptr);
                           break;

                        case ActionIx:
                           retc = GetKwrdIndex(&kwd_ix_1, val_ptr, lpszaLockActionKwds, -1, False, True);
                           if(retc == KP_E_KWD_NOT_FOUND)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, val_ptr, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc)) pParBuf->m_iAction = (FlashActions)kwd_ix_1;
                           break;

                        case VolTypeIx:
                           retc = GetKwrdIndex(&kwd_ix_1, val_ptr, lpszaVolTypeKwds, -1, False, True);
                           if(retc == KP_E_KWD_NOT_FOUND)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, val_ptr, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc)) pParBuf->m_iVolType = (TvVolTypes)kwd_ix_1;
                           break;
                        }

                     } // else // if(retc == KP_E_KWD_NOT_FOUND)

                  } // if(SUCCEEDED(retc))

               } // else // if(val_ptr == NULL)

            } // else // if(autorun_file.fail())

         } while(SUCCEEDED(retc));

         retc = S_OK;

         autorun_file.close();

      } // if(!autorun_file.fail())

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc)) if(pParBuf->m_iVolType < 0)
   {
      drive_type = GetDriveType((const char *)app_disk);
      switch(drive_type)
      {
      case DRIVE_CDROM: pParBuf->m_iVolType = Vt_CDROM; break;
      case DRIVE_REMOVABLE: pParBuf->m_iVolType = Vt_Removable; break;
      }
   }

// KP_ASSERT(pParBuf->m_iVolType >= 0, KP_E_DIR_ERROR, null, True);

return(retc);
}

