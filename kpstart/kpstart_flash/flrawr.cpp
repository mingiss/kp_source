// ---------------------------
// flrawr.cpp, USB flash RAM raw read/write 
//

// ---------------------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <time.h>
#include <windows.h>
#include <winioctl.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpstap.h"


// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
int iProdVerGlob=0;
const unsigned char lpszProdName[] = "flrawr"; 
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
HRESULT GetDevPartOffset(
   int iDevNum,         // in - reikiamo atmintuko irenginio nr. 
   long *plPartOffset,  // out - rasto dalmens pradzios adresas 
   int iPartNum,        // in - kurio dalmens pradzios reikia, 0..4; -1 - reikia neparticionuoto atmintuko
   int iParType0,       // in - reikiamas pirmo dalmens tipas
   int iParType1,       // in - reikiamas antro dalmens tipas
   int iParType2,       // in - reikiamas trecio dalmens tipas
   int iParType3        // in - reikiamas ketvirto dalmens tipas
   )
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HANDLE raw_file = INVALID_HANDLE_VALUE;
DWORD num_bytes;
unsigned char dev_name[100];
DRIVE_LAYOUT_INFORMATION /* DRIVE_LAYOUT_INFORMATION_EX */ part_info[10];


// --------------------------   
   if(((plPartOffset == NULL) || (iPartNum < -1) || (iPartNum > 3)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   
   if(SUCCEEDED(retc)) *plPartOffset = 0L;
            

// --------------------------   
   if(SUCCEEDED(retc))
      sprintf((char *)dev_name, "\\\\.\\PhysicalDrive%d", iDevNum); 

   if(SUCCEEDED(retc))
   {
      raw_file = CreateFile(
         (LPCTSTR)dev_name, // LPCTSTR lpFileName,
         FILE_READ_DATA, // GENERIC_READ, // GENERIC_WRITE, // DWORD dwDesiredAccess,
         FILE_SHARE_READ, // 0, // DWORD dwShareMode,
         NULL, // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         OPEN_EXISTING, // CREATE_ALWAYS, // DWORD dwCreationDisposition,
         FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes,
         NULL // HANDLE hTemplateFile
         );
      if(raw_file == INVALID_HANDLE_VALUE)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }   


// --------------------------   
   if(SUCCEEDED(retc))
      if(!DeviceIoControl(
         raw_file, // (HANDLE) hDevice,               // handle to device
         IOCTL_DISK_GET_DRIVE_LAYOUT, // IOCTL_DISK_GET_DRIVE_LAYOUT_EX, // dwIoControlCode
         NULL,                           // lpInBuffer
         0,                              // nInBufferSize
         part_info, // (LPVOID) lpOutBuffer,           // output buffer
         sizeof(part_info), // (DWORD) nOutBufferSize,         // size of output buffer
         &num_bytes, // (LPDWORD) lpBytesReturned,      // number of bytes returned
         NULL // (LPOVERLAPPED) lpOverlapped     // OVERLAPPED structure
         ))
            retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);


#if FALSE // #if TRUE // 
unsigned char str_buf[100];
   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%d %d", sizeof(PARTITION_INFORMATION), num_bytes-(sizeof(DRIVE_LAYOUT_INFORMATION)-sizeof(PARTITION_INFORMATION)));  
      KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
   }
#endif

   if((num_bytes-(sizeof(DRIVE_LAYOUT_INFORMATION)-sizeof(PARTITION_INFORMATION)) == sizeof(PARTITION_INFORMATION) * part_info[0].PartitionCount /* 4 */) && SUCCEEDED(retc))
   {
#if TRUE // #if FALSE
unsigned char str_buf[100];
      if(SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, "%ld", part_info[0].PartitionCount); 
         KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
      }
#endif

      if((part_info[0].PartitionCount == 4) && (iPartNum >= 0))
      {
#if TRUE // #if FALSE
static unsigned char str_buf[1000];
         if(SUCCEEDED(retc))
         {
            sprintf((char *)str_buf, "%x[%ld.%ld] %x[%ld.%ld] %x[%ld.%ld] %x[%ld.%ld]", 
               part_info[0].PartitionEntry[0].PartitionType, part_info[0].PartitionEntry[0].StartingOffset.u.HighPart, part_info[0].PartitionEntry[0].StartingOffset.u.LowPart,
               part_info[0].PartitionEntry[1].PartitionType, part_info[0].PartitionEntry[1].StartingOffset.u.HighPart, part_info[0].PartitionEntry[1].StartingOffset.u.LowPart,
               part_info[0].PartitionEntry[2].PartitionType, part_info[0].PartitionEntry[2].StartingOffset.u.HighPart, part_info[0].PartitionEntry[2].StartingOffset.u.LowPart,
               part_info[0].PartitionEntry[3].PartitionType, part_info[0].PartitionEntry[3].StartingOffset.u.HighPart, part_info[0].PartitionEntry[3].StartingOffset.u.LowPart);
            KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
         }
#endif
         if(
            (part_info[0].PartitionEntry[0].PartitionType == iParType0) && // 1
            (part_info[0].PartitionEntry[1].PartitionType == iParType1) && // 6
            (part_info[0].PartitionEntry[2].PartitionType == iParType2) && // 0
            (part_info[0].PartitionEntry[3].PartitionType == iParType3) && // 0 
            (part_info[0].PartitionEntry[iPartNum /* 1 */].StartingOffset.u.HighPart == 0L)
           )
            *plPartOffset = part_info[0].PartitionEntry[iPartNum /* 1 */].StartingOffset.u.LowPart;
         else 
            retc = KP_E_FILE_NOT_FOUND;         
      
      } // if((part_info[0].PartitionCount == 4) && (iPartNum >= 0))
      else if((part_info[0].PartitionCount == 1) && (iPartNum < 0))
      {
#if TRUE // #if FALSE
static unsigned char str_buf[1000];
         if(SUCCEEDED(retc))
         {
            sprintf((char *)str_buf, "%x[%ld.%ld]", 
               part_info[0].PartitionEntry[0].PartitionType, part_info[0].PartitionEntry[0].StartingOffset.u.HighPart, part_info[0].PartitionEntry[0].StartingOffset.u.LowPart);
            KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
         }
#endif
         if(
            (part_info[0].PartitionEntry[0].PartitionType == iParType0) && // 0
            (part_info[0].PartitionEntry[0].StartingOffset.u.HighPart == 0L)
           )
            *plPartOffset = part_info[0].PartitionEntry[0].StartingOffset.u.LowPart;
         else 
            retc = KP_E_FILE_NOT_FOUND;         
      
      } // if((part_info[0].PartitionCount == 0) && (iPartNum < 0))
      else
         retc = KP_E_FILE_NOT_FOUND;         
      
   } // if((num_bytes-(sizeof(DRIVE_LAYOUT_INFORMATION)-sizeof(PARTITION_INFORMATION)) == sizeof(PARTITION_INFORMATION) * 4) && SUCCEEDED(retc))
   else
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   

// --------------------------   
   if(raw_file != INVALID_HANDLE_VALUE)
   {
      if(!CloseHandle(raw_file))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      raw_file = INVALID_HANDLE_VALUE;
   }

return(retc);
}


// -----------------------------------------
HRESULT GetFlashRam(
   int *piDevNum,       // out - rasto atmintuko irenginio nr. 
   long *plPartOffset,  // out - rasto dalmens pradzios adresas 
   int iPartNum,        // in - kurio dalmens pradzios reikia, 0..4
   int iParType0,       // in - reikiamas pirmo dalmens tipas
   int iParType1,       // in - reikiamas antro dalmens tipas
   int iParType2,       // in - reikiamas trecio dalmens tipas
   int iParType3        // in - reikiamas ketvirto dalmens tipas
   )
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
int dev;
HANDLE raw_file = INVALID_HANDLE_VALUE;
DWORD num_bytes;
// static unsigned char str_buf[1000];
unsigned char dev_name[100];
long part_offset = 0L;


// --------------------------   
   if(((piDevNum == NULL) || (plPartOffset == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   
   if(SUCCEEDED(retc))
   {
      *piDevNum = -1;
      *plPartOffset = 0L;
   }      

   if(SUCCEEDED(retc)) for(dev=0; (dev<10) && (part_offset==0L) && SUCCEEDED(retc); dev++)
   {

// --------------------------   
      raw_file = INVALID_HANDLE_VALUE;
      
      if(SUCCEEDED(retc))
      {
         sprintf((char *)dev_name, "\\\\.\\PhysicalDrive%d", dev); 
// KpMsgOut(dev_name, IDI_ASTERISK, KP_MB_TESTI);
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
      }   
   

// --------------------------   
      if((raw_file != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {

#if FALSE
typedef struct _DISK_GEOMETRY {
  LARGE_INTEGER Cylinders;
  MEDIA_TYPE MediaType;
  DWORD TracksPerCylinder;
  DWORD SectorsPerTrack;
  DWORD BytesPerSector;
} DISK_GEOMETRY;
#endif

static DISK_GEOMETRY disk_geom[1];
DWORD ll;

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
// KpMsgOut("Klaida IOCTL_DISK_GET_DRIVE_GEOMETRY", IDI_ASTERISK, KP_MB_TESTI);
            ll = GetLastError();
// KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, True, __FILE__, __LINE__, 0L, NULL);
            if(ll != ERROR_NOT_READY) // ERROR_RESOURCE_NAME_NOT_FOUND)
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
            
//          sprintf((char *)str_buf, "%s Error %ld", dev_name, ll);
         }
         else
         {
#if FALSE // #if TRUE // 
            sprintf((char *)str_buf, "%s %d ", dev_name, disk_geom[0].MediaType);
         
            switch(disk_geom[0].MediaType)
            {
            case Unknown: 
               strcat(str_buf, "Unknown  Format is unknown");
               break;
            case F5_1Pt2_512: 
               strcat(str_buf, "F5_1Pt2_512  A 5.25\" floppy, with 1.2MB and 512 bytes/sector.");
               break;
            case F3_1Pt44_512: 
               strcat(str_buf, "F3_1Pt44_512  A 3.5\" floppy, with 1.44MB and 512 bytes/sector.");
               break;
            case F3_2Pt88_512: 
               strcat(str_buf, "F3_2Pt88_512  A 3.5\" floppy, with 2.88MB and 512 bytes/sector.");
               break;
            case F3_20Pt8_512: 
               strcat(str_buf, "F3_20Pt8_512  A 3.5\" floppy, with 20.8MB and 512 bytes/sector.");
               break;
            case F3_720_512: 
               strcat(str_buf, "F3_720_512  A 3.5\" floppy, with 720KB and 512 bytes/sector.");
               break;
            case F5_360_512: 
               strcat(str_buf, "F5_360_512  A 5.25\" floppy, with 360KB and 512 bytes/sector.");
               break;
            case F5_320_512: 
               strcat(str_buf, "F5_320_512  A 5.25\" floppy, with 320KB and 512 bytes/sector.");
               break;
            case F5_320_1024: 
               strcat(str_buf, "F5_320_1024  A 5.25\" floppy, with 320KB and 1024 bytes/sector.");
               break;
            case F5_180_512: 
               strcat(str_buf, "F5_180_512  A 5.25\" floppy, with 180KB and 512 bytes/sector.");
               break;
            case F5_160_512: 
               strcat(str_buf, "F5_160_512  A 5.25\" floppy, with 160KB and 512 bytes/sector.");
               break;
            case RemovableMedia: 
               strcat(str_buf, "RemovableMedia  Removable media other than floppy.");
               break;
            case FixedMedia: 
               strcat(str_buf, "FixedMedia  Fixed hard disk media.");
               break;
            case F3_120M_512: 
               strcat(str_buf, "F3_120M_512  A 3.5\" floppy, with 120MB and 512 bytes/sector.");
               break;
            case F3_640_512: 
               strcat(str_buf, "F3_640_512  A 3.5\" floppy, with 640MB and 512 bytes/sector.");
               break;
            case F5_640_512:
               strcat(str_buf, "F5_640_512  A 5.25\" floppy, with 640KB and 512 bytes/sector.");
               break;
            case F5_720_512:
               strcat(str_buf, "F5_720_512  A 5.25\" floppy, with 720KB and 512 bytes/sector.");
               break;
            case F3_1Pt2_512:
               strcat(str_buf, "F3_1Pt2_512  A 3.5\" floppy, with 1.2MB and 512 bytes/sector.");
               break;
            case F3_1Pt23_1024:
               strcat(str_buf, "F3_1Pt23_1024  A 3.5\" floppy, with 1.23MB and 1024 bytes/sector.");
               break;
            case F5_1Pt23_1024:
               strcat(str_buf, "F5_1Pt23_1024  A 5.25\" floppy, with 1.23KB and 1024 bytes/sector.");
               break;
            case F3_128Mb_512:
               strcat(str_buf, "F3_128Mb_512  A 3.5\" floppy, with 128MB and 512 bytes/sector.");
               break;
            case F3_230Mb_512:
               strcat(str_buf, "F3_230Mb_512  A 3.5\" floppy, with 230MB and 512 bytes/sector.");
               break;
            case F8_256_128:
               strcat(str_buf, "F8_256_128  An 8\" floppy, with 256KB and 128 bytes/sector.");
               break;
            case F3_200Mb_512:
               strcat(str_buf, "F3_200Mb_512  A 3.5\" floppy, with 200MB and 512 bytes/sector. (HiFD).");
               break;
            case F3_240M_512:
               strcat(str_buf, "F3_240M_512  A 3.5\" floppy, with 240MB and 512 bytes/sector. (HiFD).");
               break;
            case F3_32M_512:
               strcat(str_buf, "F3_32M_512  A 3.5\" floppy, with 32MB and 512 bytes/sector.");
               break;
            }

// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

#endif

            if((disk_geom[0].MediaType == RemovableMedia) && SUCCEEDED(retc))
            {
// KpMsgOut(dev_name, IDI_ASTERISK, KP_MB_TESTI);

               retc = GetDevPartOffset(dev, &part_offset, iPartNum, iParType0, iParType1, iParType2, iParType3);

               if(/* part_offset && */ SUCCEEDED(retc))
               {
                  *piDevNum = dev;
                  *plPartOffset = part_offset;
               }
               if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;
            }      
         
         } // else // if(!DeviceIoControl(

// if(SUCCEEDED(retc)) KpMsgOut(dev_name, IDI_ASTERISK, KP_MB_TESTI);

      } // if((raw_file != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   
   
// --------------------------   
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

   if(SUCCEEDED(retc))
   {
//    if(*plPartOffset == 0L) retc = KP_E_FILE_NOT_FOUND;
      if(*piDevNum < 0) retc = KP_E_FILE_NOT_FOUND;
   }      

return(retc);
}


// -----------------------------------------
HRESULT ReadRawDevData(int iDevNum, long lOffset, const unsigned char *lpszOutFileName, long lNumOfBytes)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HANDLE raw_file = INVALID_HANDLE_VALUE;
DWORD num_bytes;
// static unsigned char data_buf[KILO_BYTE];
void *data_buf = NULL;
// static unsigned char str_buf[1000];
// unsigned char str_txt[10];
// int ii;
unsigned char dev_name[100];
long rest;
long to_read;
FILE *out_file = NULL;


// --------------------------   
   if(SUCCEEDED(retc))
      sprintf((char *)dev_name, "\\\\.\\PhysicalDrive%d", iDevNum); 

   rest = lNumOfBytes;
   
   if(SUCCEEDED(retc))
   {
      raw_file = CreateFile(
         (LPCTSTR)dev_name, // "\\\\.\\PhysicalDrive3", // "\\\\.\\C:", // "flrawr.txt", // LPCTSTR lpFileName,
         FILE_READ_DATA, // GENERIC_READ, // GENERIC_WRITE, // DWORD dwDesiredAccess,
         FILE_SHARE_READ, // 0, // DWORD dwShareMode,
         NULL, // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         OPEN_EXISTING, // CREATE_ALWAYS, // DWORD dwCreationDisposition,
         FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes,
         NULL // HANDLE hTemplateFile
         );
      if(raw_file == INVALID_HANDLE_VALUE)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }   

   if(SUCCEEDED(retc))
   {
      out_file = fopen((const char *)lpszOutFileName, "wb");
      if(out_file == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      data_buf = VirtualAlloc(NULL, KILO_BYTE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
      if(data_buf == NULL) 
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }


// --------------------------   
   if(SUCCEEDED(retc))
      if(SetFilePointer(raw_file, lOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);


// --------------------------   
   while(rest && SUCCEEDED(retc))
   {
      to_read = KILO_BYTE;
      if(to_read > rest) to_read = rest;
      rest -= to_read;
       
      if(SUCCEEDED(retc))
         if(!ReadFile(raw_file, data_buf, KILO_BYTE /* to_read */, &num_bytes, NULL)) 
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

//    if((num_bytes != to_read) && SUCCEEDED(retc))
//       retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         fwrite(data_buf, 1, to_read /* num_bytes */, out_file);
         if(ferror(out_file) || feof(out_file))
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

#if FALSE
      if(SUCCEEDED(retc))
      {
         str_buf[0] = Nul;
//       for(ii = 0; ii<num_bytes; ii++)
         for(ii = 0; ii<4; ii++)
         {
            sprintf((char *)str_txt, "[%x] ", data_buf[ii]);
            strcat(str_buf, str_txt); 
         }
         KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
      }
#endif

   } // while(rest && SUCCEEDED(retc))
        

// --------------------------   
   if(data_buf)
   {
      if(!VirtualFree(data_buf, 0, MEM_RELEASE))  
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      data_buf = NULL;
   }

   if(out_file)
   {
      if(fclose(out_file))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      out_file = NULL;
   }   

   if(raw_file != INVALID_HANDLE_VALUE)
   {
      if(!CloseHandle(raw_file))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      raw_file = INVALID_HANDLE_VALUE;
   }

return(retc);
}


// -----------------------------------------
HRESULT WriteRawDevData(int iDevNum, long lOffset, const unsigned char *lpszInFileName)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HANDLE raw_file = INVALID_HANDLE_VALUE;
DWORD num_bytes;
void *data_buf = NULL;
unsigned char dev_name[100];
long rest;
long to_read;
HANDLE in_file = INVALID_HANDLE_VALUE;


// --------------------------   
   if(SUCCEEDED(retc))
      sprintf((char *)dev_name, "\\\\.\\PhysicalDrive%d", iDevNum); 

   if(SUCCEEDED(retc))
   {
      raw_file = CreateFile(
         (LPCTSTR)dev_name, // "\\\\.\\PhysicalDrive3", // "\\\\.\\C:", // "flrawr.txt", // LPCTSTR lpFileName,
         FILE_WRITE_DATA, // GENERIC_READ, // GENERIC_WRITE, // DWORD dwDesiredAccess,
         0, // FILE_SHARE_READ, // DWORD dwShareMode,
         NULL, // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         OPEN_EXISTING, // CREATE_ALWAYS, // DWORD dwCreationDisposition,
         FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes,
         NULL // HANDLE hTemplateFile
         );
      if(raw_file == INVALID_HANDLE_VALUE)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }   


   if(SUCCEEDED(retc))
   {
      in_file = CreateFile(
         (LPCTSTR)lpszInFileName, // "\\\\.\\PhysicalDrive3", // "\\\\.\\C:", // "flrawr.txt", // LPCTSTR lpFileName,
         GENERIC_READ, // GENERIC_WRITE, // DWORD dwDesiredAccess,
         0, // FILE_SHARE_READ, // DWORD dwShareMode,
         NULL, // LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         OPEN_EXISTING, // CREATE_ALWAYS, // DWORD dwCreationDisposition,
         FILE_ATTRIBUTE_NORMAL, // DWORD dwFlagsAndAttributes,
         NULL // HANDLE hTemplateFile
         );
      if(in_file == INVALID_HANDLE_VALUE)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }   

   if(SUCCEEDED(retc))
   {
      rest = GetFileSize(in_file, NULL);
      if(rest == INVALID_FILE_SIZE)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      data_buf = VirtualAlloc(NULL, KILO_BYTE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
      if(data_buf == NULL) 
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   
// --------------------------   
   if(SUCCEEDED(retc))
      if(SetFilePointer(raw_file, lOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)   
         retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);


// --------------------------   
#if FALSE
   if(SUCCEEDED(retc))
      if(!WriteFile(raw_file, "kuku", 4, &num_bytes, NULL)) 
         retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

   while(rest && SUCCEEDED(retc))
   {
      to_read = KILO_BYTE;
      if(to_read > rest) to_read = rest;
      rest -= to_read;
       
      if(SUCCEEDED(retc))
         if(!ReadFile(in_file, data_buf, to_read, &num_bytes, NULL)) 
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if((num_bytes != to_read) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!WriteFile(raw_file, data_buf, KILO_BYTE, &num_bytes, NULL)) 
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   } // while(rest && SUCCEEDED(retc))
        

// --------------------------   
   if(data_buf)
   {
      if(!VirtualFree(data_buf, 0, MEM_RELEASE))  
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      data_buf = NULL;
   }

   if(in_file != INVALID_HANDLE_VALUE)
   {
      if(!CloseHandle(in_file))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      in_file = INVALID_HANDLE_VALUE;
   }   

   if(raw_file != INVALID_HANDLE_VALUE)
   {
      if(!CloseHandle(raw_file))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      raw_file = INVALID_HANDLE_VALUE;
   }

return(retc);
}


// --------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE, // hInstance,
                     HINSTANCE, // hPrevInstance,
                     LPSTR,     // lpCmdLine,
                     int        // nCmdShow
                     )
{
HRESULT retc = S_OK;
int dev = -1;
long part_offset = 0L;
// static unsigned char str_buf[1000];

   if(SUCCEEDED(retc)) retc = KpInit();

// if(SUCCEEDED(retc)) retc = ReadRawDevData();

   dev = -1;
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 1, 1, 6, 0, 0);
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 1, 6, 0, 0);
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 0xd1, 0, 0, 0);
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 1, 0xB, 0, 0); // Windows'u suformatuotos dvi fixed particijos
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 1, 0, 0, 0);
   if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 6, 0, 0, 0);
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, 0, 7, 0, 0, 0); // Viena NTFS particija
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, -1, 4, 0, 0, 0); // Windows'u suformatuota viena removable particija
// if(SUCCEEDED(retc)) retc = GetFlashRam(&dev, &part_offset, -1, 4, 0, 0, 0); // CD-ROM FS
   
// if((part_offset == 0L) && SUCCEEDED(retc))
   if(((dev < 0) && SUCCEEDED(retc)) || (retc == KP_E_FILE_NOT_FOUND))
   {
      KpMsgOut("Reikiamai suformatuoto atmintuko nerandu, gal neturite administratoriaus teisiø?", IDI_ERROR, KP_MB_TESTI);
      retc = KP_E_FILE_NOT_FOUND;
   }

#if FALSE // #if TRUE // 
   if(SUCCEEDED(retc))
   {
//    sprintf((char *)str_buf, "%d %ld", dev, part_offset);
//    KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

//    retc = ReadRawDevData(dev, part_offset, (const unsigned char *)"flrawr.dat", 10*KILO_BYTE);
//    retc = ReadRawDevData(dev, 0, (const unsigned char *)"flrawr.dat", 8225280);
//    retc = ReadRawDevData(dev, 0, (const unsigned char *)"flrawr.dat", 186726400);
//    retc = ReadRawDevData(dev, 0, (const unsigned char *)"flrawr.dat", 512);
      retc = ReadRawDevData(dev, 0, (const unsigned char *)"flrawr.dat", 54716928);
   }

   if(SUCCEEDED(retc)) KpMsgOut("Duomenys sëkmingai perskaityti", IDI_ASTERISK, KP_MB_TESTI);
#endif

#if FALSE // #if TRUE // 
   if(SUCCEEDED(retc))
   {
//    retc = WriteRawDevData(dev, part_offset, (const unsigned char *)"flrawr.dat");
      retc = WriteRawDevData(dev, 0, (const unsigned char *)"flrawr.dat");
   }

   if(SUCCEEDED(retc)) KpMsgOut("Duomenys sëkmingai áraðyti", IDI_ASTERISK, KP_MB_TESTI);
#endif

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_WIN(retc));
}

