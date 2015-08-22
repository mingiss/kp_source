// ==================================================
// kpstdio.cpp
// common I/O tools
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdio.h>
#include <string.h>
#include <string>
// #include <iostream.h>
#include <iostream>
// #include <fstream.h>
#include <fstream>
#include <time.h>
#include <sys/timeb.h>
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#endif
#if CompilerGr==Msvc
#include <ShellAPI.h>
#endif

#include <b64/encode.h>
#include <b64/decode.h>

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

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
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
#include "kpmsg.h"


// ==================================================
unsigned char *lpszaPartTypeNames[KPT_Ctbsiz /* PartitionEntry.m_cPartType */] =
{
/* 0x00 */ (unsigned char *)"Empty",
/* 0x01 */ (unsigned char *)"DOS 12-bit FAT",
/* 0x02 */ (unsigned char *)"XENIX root",
/* 0x03 */ (unsigned char *)"XENIX /usr",
/* 0x04 */ (unsigned char *)"DOS 3.0+ 16-bit FAT (up to 32M)",
/* 0x05 */ (unsigned char *)"DOS 3.3+ Extended Partition",
/* 0x06 */ (unsigned char *)"DOS 3.31+ 16-bit FAT (over 32M)",
/* 0x07 */ (unsigned char *)"Windows NT NTFS / OS/2 IFS (e.g., HPFS) / Advanced Unix / QNX2.x pre-1988",
/* 0x08 */ (unsigned char *)"OS/2 (v1.0-1.3 only) / AIX boot partition / SplitDrive / Commodore DOS / DELL partition spanning multiple drives / QNX 1.x and 2.x (\"qny\")",
/* 0x09 */ (unsigned char *)"AIX data partition / Coherent filesystem / QNX 1.x and 2.x (\"qnz\")",
/* 0x0a */ (unsigned char *)"OS/2 Boot Manager / Coherent swap partition / OPUS",
/* 0x0b */ (unsigned char *)"WIN95 OSR2 FAT32",
/* 0x0c */ (unsigned char *)"WIN95 OSR2 FAT32, LBA-mapped",
/* 0x0d */ (unsigned char *)"?",
/* 0x0e */ (unsigned char *)"WIN95: DOS 16-bit FAT, LBA-mapped",
/* 0x0f */ (unsigned char *)"WIN95: Extended partition, LBA-mapped",
/* 0x10 */ (unsigned char *)"OPUS (?)",
/* 0x11 */ (unsigned char *)"Hidden DOS 12-bit FAT / Leading Edge DOS 3.x logically sectored FAT",
/* 0x12 */ (unsigned char *)"Configuration/diagnostics partition",
/* 0x13 */ (unsigned char *)"?",
/* 0x14 */ (unsigned char *)"Hidden DOS 16-bit FAT <32M / AST DOS with logically sectored FAT",
/* 0x15 */ (unsigned char *)"",
/* 0x16 */ (unsigned char *)"Hidden DOS 16-bit FAT >=32M",
/* 0x17 */ (unsigned char *)"Hidden IFS (e.g., HPFS)",
/* 0x18 */ (unsigned char *)"AST SmartSleep Partition",
/* 0x19 */ (unsigned char *)"Unused",
/* 0x1a */ (unsigned char *)"?",
/* 0x1b */ (unsigned char *)"Hidden WIN95 OSR2 FAT32",
/* 0x1c */ (unsigned char *)"Hidden WIN95 OSR2 FAT32, LBA-mapped",
/* 0x1e */ (unsigned char *)"Hidden WIN95 16-bit FAT, LBA-mapped",
/* 0x1f */ (unsigned char *)"?",
/* 0x20 */ (unsigned char *)"Unused",
/* 0x21 */ (unsigned char *)"Reserved / Unused / HP Volume Expansion (SpeedStor variant)",
/* 0x22 */ (unsigned char *)"Unused",
/* 0x23 */ (unsigned char *)"Reserved",
/* 0x24 */ (unsigned char *)"NEC DOS 3.x",
/* 0x25 */ (unsigned char *)"?",
/* 0x26 */ (unsigned char *)"Reserved",
/* 0x27 */ (unsigned char *)"?",
/* 0x28 */ (unsigned char *)"?",
/* 0x29 */ (unsigned char *)"?",
/* 0x2a */ (unsigned char *)"AtheOS File System (AFS)",
/* 0x2b */ (unsigned char *)"SyllableSecure (SylStor)",
/* 0x2c */ (unsigned char *)"?",
/* 0x2d */ (unsigned char *)"?",
/* 0x2e */ (unsigned char *)"?",
/* 0x2f */ (unsigned char *)"?",
/* 0x30 */ (unsigned char *)"?",
/* 0x31 */ (unsigned char *)"Reserved",
/* 0x32 */ (unsigned char *)"NOS",
/* 0x33 */ (unsigned char *)"Reserved",
/* 0x34 */ (unsigned char *)"Reserved",
/* 0x35 */ (unsigned char *)"JFS on OS/2 or eCS",
/* 0x36 */ (unsigned char *)"Reserved",
/* 0x37 */ (unsigned char *)"?",
/* 0x38 */ (unsigned char *)"THEOS ver 3.2 2gb partition",
/* 0x39 */ (unsigned char *)"Plan 9 partition",
/* 0x39 */ (unsigned char *)"THEOS ver 4 spanned partition",
/* 0x3a */ (unsigned char *)"THEOS ver 4 4gb partition",
/* 0x3b */ (unsigned char *)"THEOS ver 4 extended partition",
/* 0x3c */ (unsigned char *)"PartitionMagic recovery partition",
/* 0x3d */ (unsigned char *)"Hidden NetWare",
/* 0x3e */ (unsigned char *)"?",
/* 0x3f */ (unsigned char *)"?",
/* 0x40 */ (unsigned char *)"Venix 80286",
/* 0x41 */ (unsigned char *)"Linux/MINIX (sharing disk with DRDOS) / Personal RISC Boot / PPC PReP (Power PC Reference Platform) Boot",
/* 0x42 */ (unsigned char *)"Linux swap (sharing disk with DRDOS) / SFS (Secure Filesystem) / Windows 2000 dynamic extended partition marker",
/* 0x43 */ (unsigned char *)"Linux native (sharing disk with DRDOS)",
/* 0x44 */ (unsigned char *)"GoBack partition",
/* 0x45 */ (unsigned char *)"Boot-US boot manager / Priam / EUMEL/Elan",
/* 0x46 */ (unsigned char *)"EUMEL/Elan",
/* 0x47 */ (unsigned char *)"EUMEL/Elan",
/* 0x48 */ (unsigned char *)"EUMEL/Elan",
/* 0x49 */ (unsigned char *)"?",
/* 0x4a */ (unsigned char *)"Mark Aitchison's ALFS/THIN lightweight filesystem for DOS / AdaOS Aquila (Withdrawn)",
/* 0x4b */ (unsigned char *)"?",
/* 0x4c */ (unsigned char *)"Oberon partition",
/* 0x4d */ (unsigned char *)"QNX4.x",
/* 0x4e */ (unsigned char *)"QNX4.x 2nd part",
/* 0x4f */ (unsigned char *)"QNX4.x 3rd part / Oberon partition",
/* 0x50 */ (unsigned char *)"OnTrack Disk Manager (older versions) RO / Lynx RTOS / Native Oberon (alt)",
/* 0x51 */ (unsigned char *)"OnTrack Disk Manager RW (DM6 Aux1) / Novell",
/* 0x52 */ (unsigned char *)"CP/M / Microport SysV/AT",
/* 0x53 */ (unsigned char *)"Disk Manager 6.0 Aux3",
/* 0x54 */ (unsigned char *)"Disk Manager 6.0 Dynamic Drive Overlay (DDO)",
/* 0x55 */ (unsigned char *)"EZ-Drive",
/* 0x56 */ (unsigned char *)"Golden Bow VFeature Partitioned Volume / 56 DM converted to EZ-BIOS / AT&T MS-DOS 3.x logically sectored FAT",
/* 0x57 */ (unsigned char *)"DrivePro / VNDI Partition",
/* 0x58 */ (unsigned char *)"?",
/* 0x59 */ (unsigned char *)"?",
/* 0x5a */ (unsigned char *)"?",
/* 0x5b */ (unsigned char *)"?",
/* 0x5c */ (unsigned char *)"Priam EDisk",
/* 0x5d */ (unsigned char *)"?",
/* 0x5e */ (unsigned char *)"?",
/* 0x5f */ (unsigned char *)"?",
/* 0x60 */ (unsigned char *)"?",
/* 0x61 */ (unsigned char *)"SpeedStor",
/* 0x62 */ (unsigned char *)"?",
/* 0x63 */ (unsigned char *)"Unix System V (SCO, ISC Unix, UnixWare, ...), Mach, GNU Hurd",
/* 0x64 */ (unsigned char *)"PC-ARMOUR protected partition / 64 Novell Netware 286, 2.xx",
/* 0x65 */ (unsigned char *)"Novell Netware 386, 3.xx or 4.xx",
/* 0x66 */ (unsigned char *)"Novell Netware SMS Partition",
/* 0x67 */ (unsigned char *)"Novell",
/* 0x68 */ (unsigned char *)"Novell",
/* 0x69 */ (unsigned char *)"Novell Netware 5+, Novell Netware NSS Partition",
/* 0x6a */ (unsigned char *)"?",
/* 0x6b */ (unsigned char *)"?",
/* 0x6c */ (unsigned char *)"?",
/* 0x6d */ (unsigned char *)"?",
/* 0x6e */ (unsigned char *)"??",
/* 0x6f */ (unsigned char *)"?",
/* 0x70 */ (unsigned char *)"DiskSecure Multi-Boot",
/* 0x71 */ (unsigned char *)"Reserved",
/* 0x72 */ (unsigned char *)"?",
/* 0x73 */ (unsigned char *)"Reserved",
/* 0x74 */ (unsigned char *)"Reserved / Scramdisk partition",
/* 0x75 */ (unsigned char *)"IBM PC/IX",
/* 0x76 */ (unsigned char *)"Reserved",
/* 0x77 */ (unsigned char *)"M2FS/M2CS partition / VNDI Partition",
/* 0x78 */ (unsigned char *)"XOSL FS",
/* 0x79 */ (unsigned char *)"?",
/* 0x7a */ (unsigned char *)"?",
/* 0x7b */ (unsigned char *)"?",
/* 0x7c */ (unsigned char *)"?",
/* 0x7d */ (unsigned char *)"?",
/* 0x7e */ (unsigned char *)"Unused",
/* 0x7f */ (unsigned char *)"Unused",
/* 0x80 */ (unsigned char *)"MINIX until 1.4a",
/* 0x81 */ (unsigned char *)"MINIX since 1.4b, early Linux / Mitac disk manager",
/* 0x82 */ (unsigned char *)"Linux swap / Solaris x86 / Prime",
/* 0x83 */ (unsigned char *)"Linux native partition",
/* 0x84 */ (unsigned char *)"Hibernation partition / OS/2 hidden C: drive",
/* 0x85 */ (unsigned char *)"Linux extended partition",
/* 0x86 */ (unsigned char *)"Old Linux RAID partition superblock / FAT16 volume set",
/* 0x87 */ (unsigned char *)"NTFS volume set",
/* 0x88 */ (unsigned char *)"Linux plaintext partition table",
/* 0x89 */ (unsigned char *)"?",
/* 0x8a */ (unsigned char *)"Linux Kernel Partition (used by AiR-BOOT)",
/* 0x8b */ (unsigned char *)"Legacy Fault Tolerant FAT32 volume",
/* 0x8c */ (unsigned char *)"Legacy Fault Tolerant FAT32 volume using BIOS extd INT 13h",
/* 0x8d */ (unsigned char *)"Free FDISK hidden Primary DOS FAT12 partitition",
/* 0x8e */ (unsigned char *)"Linux Logical Volume Manager partition",
/* 0x8f */ (unsigned char *)"?",
/* 0x90 */ (unsigned char *)"Free FDISK hidden Primary DOS FAT16 partitition",
/* 0x91 */ (unsigned char *)"Free FDISK hidden DOS extended partitition",
/* 0x92 */ (unsigned char *)"Free FDISK hidden Primary DOS large FAT16 partitition",
/* 0x93 */ (unsigned char *)"Hidden Linux native partition / Amoeba",
/* 0x94 */ (unsigned char *)"Amoeba bad block table",
/* 0x95 */ (unsigned char *)"MIT EXOPC native partitions",
/* 0x96 */ (unsigned char *)"?",
/* 0x97 */ (unsigned char *)"Free FDISK hidden Primary DOS FAT32 partitition",
/* 0x98 */ (unsigned char *)"Free FDISK hidden Primary DOS FAT32 partitition (LBA) / Datalight ROM-DOS Super-Boot Partition",
/* 0x99 */ (unsigned char *)"DCE376 logical drive",
/* 0x9a */ (unsigned char *)"Free FDISK hidden Primary DOS FAT16 partitition (LBA)",
/* 0x9b */ (unsigned char *)"Free FDISK hidden DOS extended partitition (LBA)",
/* 0x9c */ (unsigned char *)"?",
/* 0x9d */ (unsigned char *)"?",
/* 0x9e */ (unsigned char *)"?",
/* 0x9f */ (unsigned char *)"BSD/OS",
/* 0xa0 */ (unsigned char *)"Laptop hibernation partition",
/* 0xa1 */ (unsigned char *)"Laptop hibernation partition / HP Volume Expansion (SpeedStor variant)",
/* 0xa2 */ (unsigned char *)"?",
/* 0xa3 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant)",
/* 0xa4 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant)",
/* 0xa5 */ (unsigned char *)"BSD/386, 386BSD, NetBSD, FreeBSD",
/* 0xa6 */ (unsigned char *)"OpenBSD / HP Volume Expansion (SpeedStor variant)",
/* 0xa7 */ (unsigned char *)"NeXTStep",
/* 0xa8 */ (unsigned char *)"Mac OS-X",
/* 0xa9 */ (unsigned char *)"NetBSD",
/* 0xaa */ (unsigned char *)"Olivetti Fat 12 1.44MB Service Partition",
/* 0xab */ (unsigned char *)"Mac OS-X Boot partition / GO! partition",
/* 0xac */ (unsigned char *)"?",
/* 0xad */ (unsigned char *)"?",
/* 0xae */ (unsigned char *)"ShagOS filesystem",
/* 0xaf */ (unsigned char *)"MacOS X HFS / ShagOS swap partition",
/* 0xb0 */ (unsigned char *)"BootStar Dummy",
/* 0xb1 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant)",
/* 0xb2 */ (unsigned char *)"?",
/* 0xb3 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant)",
/* 0xb4 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant)",
/* 0xb5 */ (unsigned char *)"?",
/* 0xb6 */ (unsigned char *)"HP Volume Expansion (SpeedStor variant) / Corrupted Windows NT mirror set (master), FAT16 file system",
/* 0xb7 */ (unsigned char *)"Corrupted Windows NT mirror set (master), NTFS file system / BSDI BSD/386 filesystem",
/* 0xb8 */ (unsigned char *)"BSDI BSD/386 swap partition",
/* 0xb9 */ (unsigned char *)"?",
/* 0xba */ (unsigned char *)"?",
/* 0xbb */ (unsigned char *)"Boot Wizard hidden",
/* 0xbc */ (unsigned char *)"?",
/* 0xbd */ (unsigned char *)"?",
/* 0xbe */ (unsigned char *)"Solaris 8 boot partition",
/* 0xbf */ (unsigned char *)"New Solaris x86 partition",
/* 0xc0 */ (unsigned char *)"CTOS / REAL/32 secure small partition / NTFT Partition / DR-DOS/Novell DOS secured partition",
/* 0xc1 */ (unsigned char *)"DRDOS/secured (FAT-12)",
/* 0xc2 */ (unsigned char *)"Unused / Hidden Linux",
/* 0xc3 */ (unsigned char *)"Hidden Linux swap",
/* 0xc4 */ (unsigned char *)"DRDOS/secured (FAT-16, < 32M)",
/* 0xc5 */ (unsigned char *)"DRDOS/secured (extended)",
/* 0xc6 */ (unsigned char *)"DRDOS/secured (FAT-16, >= 32M) / Windows NT corrupted FAT16 volume/stripe set",
/* 0xc7 */ (unsigned char *)"Windows NT corrupted NTFS volume/stripe set / Syrinx boot",
/* 0xc8 */ (unsigned char *)"Reserved for DR-DOS 8.0+",
/* 0xc9 */ (unsigned char *)"Reserved for DR-DOS 8.0+",
/* 0xca */ (unsigned char *)"Reserved for DR-DOS 8.0+",
/* 0xcb */ (unsigned char *)"DR-DOS 7.04+ secured FAT32 (CHS)/",
/* 0xcc */ (unsigned char *)"DR-DOS 7.04+ secured FAT32 (LBA)/",
/* 0xcd */ (unsigned char *)"CTOS Memdump?",
/* 0xce */ (unsigned char *)"DR-DOS 7.04+ FAT16X (LBA)/",
/* 0xcf */ (unsigned char *)"DR-DOS 7.04+ secured EXT DOS (LBA)/",
/* 0xd0 */ (unsigned char *)"REAL/32 secure big partition / Multiuser DOS secured partition",
/* 0xd1 */ (unsigned char *)"Old Multiuser DOS secured FAT12",
/* 0xd2 */ (unsigned char *)"?",
/* 0xd3 */ (unsigned char *)"?",
/* 0xd4 */ (unsigned char *)"Old Multiuser DOS secured FAT16 <32M",
/* 0xd5 */ (unsigned char *)"Old Multiuser DOS secured extended partition",
/* 0xd6 */ (unsigned char *)"Old Multiuser DOS secured FAT16 >=32M",
/* 0xd7 */ (unsigned char *)"?",
/* 0xd8 */ (unsigned char *)"CP/M-86",
/* 0xd9 */ (unsigned char *)"?",
/* 0xda */ (unsigned char *)"Non-FS Data / Powercopy Backup",
/* 0xdb */ (unsigned char *)"Digital Research CP/M, Concurrent CP/M, Concurrent DOS / CTOS (Convergent Technologies OS -Unisys) / KDG Telemetry SCPU boot",
/* 0xdc */ (unsigned char *)"?",
/* 0xdd */ (unsigned char *)"Hidden CTOS Memdump?",
/* 0xde */ (unsigned char *)"Dell PowerEdge Server utilities (FAT fs)",
/* 0xdf */ (unsigned char *)"DG/UX virtual disk manager partition / BootIt EMBRM",
/* 0xe0 */ (unsigned char *)"Reserved by STMicroelectronics for a filesystem called ST AVFS",
/* 0xe1 */ (unsigned char *)"DOS access or SpeedStor 12-bit FAT extended partition",
/* 0xe2 */ (unsigned char *)"?",
/* 0xe3 */ (unsigned char *)"DOS R/O or SpeedStor",
/* 0xe4 */ (unsigned char *)"SpeedStor 16-bit FAT extended partition < 1024 cyl.",
/* 0xe5 */ (unsigned char *)"Tandy MSDOS with logically sectored FAT",
/* 0xe6 */ (unsigned char *)"Storage Dimensions SpeedStor",
/* 0xe7 */ (unsigned char *)"?",
/* 0xe8 */ (unsigned char *)"?",
/* 0xe9 */ (unsigned char *)"?",
/* 0xea */ (unsigned char *)"?",
/* 0xeb */ (unsigned char *)"BeOS BFS",
/* 0xec */ (unsigned char *)"SkyOS SkyFS",
/* 0xed */ (unsigned char *)"Unused",
/* 0xee */ (unsigned char *)"Indication that this legacy MBR is followed by an EFI header",
/* 0xef */ (unsigned char *)"Partition that contains an EFI file system",
/* 0xf0 */ (unsigned char *)"Linux/PA-RISC boot loader",
/* 0xf1 */ (unsigned char *)"Storage Dimensions SpeedStor",
/* 0xf2 */ (unsigned char *)"DOS 3.3+ secondary partition",
/* 0xf3 */ (unsigned char *)"Reserved",
/* 0xf4 */ (unsigned char *)"SpeedStor large partition / Prologue single-volume partition",
/* 0xf5 */ (unsigned char *)"Prologue multi-volume partition",
/* 0xf6 */ (unsigned char *)"Storage Dimensions SpeedStor",
/* 0xf7 */ (unsigned char *)"Unused",
/* 0xf8 */ (unsigned char *)"?",
/* 0xf9 */ (unsigned char *)"pCache",
/* 0xfa */ (unsigned char *)"Bochs",
/* 0xfb */ (unsigned char *)"VMware File System partition",
/* 0xfc */ (unsigned char *)"VMware Swap partition",
/* 0xfd */ (unsigned char *)"Linux raid partition with autodetect using persistent superblock",
/* 0xfe */ (unsigned char *)"SpeedStor > 1024 cyl. / LANstep / IBM PS/2 IML (Initial Microcode Load) partition, located at the end of the disk / Windows NT Disk Administrator hidden partition / Linux Logical Volume Manager partition (old)",
/* 0xff */ (unsigned char *)"Xenix Bad Block Table",
};


// ==================================================
HRESULT TvFnameSplit
(
unsigned char *lpszDiskBuf,
unsigned char *lpszPathBuf,
unsigned char *lpszFNameBuf,
unsigned char *lpszFTypeBuf,
const unsigned char *lpszFullName
)
{
HRESULT retc=S_OK;
unsigned char *disk_ptr;
unsigned char *path_ptr;
unsigned char *fnam_ptr;
unsigned char *typ_ptr;
unsigned char *pnts;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];

   if((lpszDiskBuf==NULL) || (lpszPathBuf==NULL) || (lpszFNameBuf==NULL) ||
      (lpszFTypeBuf==NULL) || (lpszFullName==NULL))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen((const char *)lpszFullName)>=KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszFullName);

      disk_ptr = pnts = path_ptr = fnam_ptr = typ_ptr = str_buf;

      do
      {
         if(*pnts == ':') path_ptr = pnts + 1;
         if((*pnts == '\\') || (*pnts == '/')) fnam_ptr = pnts + 1;
         if(*pnts == '.') typ_ptr = pnts;
         pnts++;
      } while(*pnts);
   }

// type
   if(SUCCEEDED(retc))
   {
      if(typ_ptr <= fnam_ptr) typ_ptr=(unsigned char *)"";
      else *(typ_ptr++)=Nul;
   }
   KP_ASSERT(strlen(typ_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(lpszFTypeBuf, typ_ptr);

// fname
   if(SUCCEEDED(retc)) if(fnam_ptr < path_ptr) fnam_ptr = path_ptr;
   KP_ASSERT(strlen(fnam_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(lpszFNameBuf, fnam_ptr);

// path
   if(SUCCEEDED(retc))
   {
      if(fnam_ptr == path_ptr) strcpy(lpszPathBuf, ".");
      else /* if(fnam_ptr > path_ptr) */
      {
         *fnam_ptr-- = Nul;
         if((*fnam_ptr=='\\') || (*fnam_ptr=='/')) *fnam_ptr = Nul;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

         KP_ASSERT(strlen(path_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc)) strcpy(lpszPathBuf, path_ptr);
      }
   }

// disk
   if(SUCCEEDED(retc)) *path_ptr=Nul;
   KP_ASSERT(strlen(disk_ptr) < KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(lpszDiskBuf, disk_ptr);

return(retc);
}


// ================================================== TvUniFnameClass
TvUniFnameClass TvUniFname;


TvUniFnameClass::TvUniFnameClass(void)
{
   struct timeb tstruct;

   iCallCnt=0;

   ftime(&tstruct);
   iCallCnt=(tstruct.millitm/(1000/18))%100;
}



HRESULT TvUniFnameClass::Generate(unsigned char *lpszFNameBuf)
{
HRESULT retc=S_OK;
struct timeb tstruct;
char time_buf[20];

   if(lpszFNameBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      iCallCnt++;
      if(iCallCnt>=100) iCallCnt=0;

      ftime(&tstruct);
      sprintf(time_buf, "%ld%hu", tstruct.time, tstruct.millitm/(1000/18));
      sprintf((char *)lpszFNameBuf, "tv%s%02d.tmp", time_buf+strlen(time_buf)-4, iCallCnt);
   }

return(retc);
}


HRESULT TvUniFnameClass::RandInt(long *plVal)
{
HRESULT retc=S_OK;
struct timeb tstruct;

   if(plVal==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      iCallCnt++;
      if(iCallCnt>=100) iCallCnt=0;

      ftime(&tstruct);
      *plVal=(long)tstruct.time+tstruct.millitm/(1000/18)+iCallCnt;
   }

return(retc);
}


// ================================================== text output to FILE
HRESULT TvPutSN
(
        FILE *pfOutFile,
        const unsigned char *lpszOutString,
        const int iOutWdt
        )
{
        HRESULT retc=S_OK;
        int slen;
        int ii;

        fputs((const char *)lpszOutString, pfOutFile);
        if(ferror(pfOutFile) || feof(pfOutFile))
                retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

        slen=strlen((const char *)lpszOutString);
        if(SUCCEEDED(retc))
                if(slen>iOutWdt)
                        retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszOutString, True, __FILE__, __LINE__, 0L);

        for(ii=0; (ii<iOutWdt-slen) && SUCCEEDED(retc); ii++)
        {
                fputc(Spc, pfOutFile);
                if(ferror(pfOutFile) || feof(pfOutFile))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
        }

        return(retc);
}

/*-----------------------------------------*/
unsigned char *fgetss(unsigned char *buf, int maxnum, FILE *fil)
{
unsigned char *retstr,*pntc;

   retstr=NULL;
   fgets((char *)buf, maxnum, fil);
   if(!feof(fil) && !ferror(fil))
   {
      if((pntc=(unsigned char *)strchr((const char *)buf, Cr))!=NULL) *pntc=Nul;
      if((pntc=(unsigned char *)strchr((const char *)buf, Lf))!=NULL) *pntc=Nul;
      retstr=buf;
   }

return(retstr);
}

/*-----------------------------------------*/
int fputss(const unsigned char *buf, FILE *fil)
{
int retc;

  retc=fputs((const char *)buf, fil);
  if(retc!=EOF) retc=fputs("\n", fil);

return(retc);
}


/*-----------------------------------------*/
HRESULT SplitToLines(unsigned char *lpszTextBuf, int iLineWdt, int iBufLen)
{
HRESULT retc = S_OK;
unsigned char *buf_ptr = null;
unsigned char *pntd;
unsigned char *pnts;
int ch_cnt;

// SplitToLines() used by KpErrorProc_tag itself
// klaidos pranešimas nulauš
   KP_NEWA(buf_ptr, unsigned char, iBufLen + 1);

   if(SUCCEEDED(retc))
   {
      pnts=lpszTextBuf;
      pntd=buf_ptr;
      ch_cnt=0;
      while((*pnts) && SUCCEEDED(retc))
      {
         ch_cnt++;
         if(*pnts==Lf) ch_cnt=0;
         if(pntd-buf_ptr>=iBufLen-2)
         {
            retc=KP_E_BUFFER_OVERFLOW;
//          retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, NULL, True, __FILE__, __LINE__, 0L);
         }
         if(SUCCEEDED(retc))
         {
            *(pntd++)=(*pnts++);
            if(ch_cnt>=iLineWdt)
            {
               *(pntd++)=Lf;
               ch_cnt=0;
            }
         }
      }

      *pntd=Nul;
      strcpy(lpszTextBuf, buf_ptr);
   }

   KP_DELETEA(buf_ptr);

return(retc);
}


//--------------------------------
HRESULT CheckFile(const unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
FILE *fptr;

   fptr=fopen((const char *)lpszFileName,"r");
   if(fptr==NULL) retc=KP_E_DIR_ERROR;
   else
   {
      if(fclose(fptr)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


//--------------------------------
HRESULT CheckEmpty(const unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
FILE *fptr;

   fptr=fopen((const char *)lpszFileName,"r");
   if(fptr==NULL)
   {
      fptr=fopen((const char *)lpszFileName,"w");
      if(fptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if(fclose(fptr)!=0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);
      }
   }
   else
   {
      if(fclose(fptr)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------
HRESULT KpGetFileSizeFile(FILE *pInFile, long *plFileSize)
{
HRESULT retc = S_OK;

   KP_ASSERT(pInFile, E_INVALIDARG, null, True);
   KP_ASSERT(plFileSize, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
      if(fseek(pInFile, 0, SEEK_END))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plFileSize=ftell(pInFile);
      if(*plFileSize<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fseek(pInFile, 0, SEEK_SET))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


HRESULT KpGetFileSizeName(const unsigned char *lpszFileName, long *plFileSize, bool bOutputErrorMessages)
{
HRESULT retc = S_OK;
FILE *in_file = NULL;

   KP_ASSERT(lpszFileName, E_INVALIDARG, null, True);
   KP_ASSERT(plFileSize, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      in_file = fopen((const char *)lpszFileName, "rb");
// CreateFileEx()
      if(in_file == NULL)
      {
         retc = KP_E_FILE_NOT_FOUND;
         if(bOutputErrorMessages) KP_ERROR(retc, lpszFileName);
      }
   }

   if(SUCCEEDED(retc)) retc = KpGetFileSizeFile(in_file, plFileSize);
// BOOL WINAPI GetFileSizeEx(  __in   HANDLE hFile,  __out  PLARGE_INTEGER lpFileSize);

   if(in_file) fclose(in_file);

return(retc);
}


// --------------------------------
HRESULT ReadFileContents(const unsigned char *lpszFileName, unsigned char **plpszFileContPtr, long *plFileLen, bool bCheckFileNotFound, bool bBinary)
{
HRESULT retc=S_OK;
FILE *in_file;
long ll;
unsigned char *pntd;

// ---------------------------------
   if((plpszFileContPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *plpszFileContPtr=NULL;

// ---------------------------------
   in_file=NULL;
   if(SUCCEEDED(retc))
   {
      in_file=fopen((const char *)lpszFileName, bBinary?"rb":"r");
      if(!in_file)
      {
         retc=KP_E_FILE_NOT_FOUND;
         if(bCheckFileNotFound)
            retc=KpErrorProc.OutputErrorMessage(retc, lpszFileName, True, __FILE__, __LINE__, 0L);
      }
   }

// ---------------------------------
   if(SUCCEEDED(retc)) retc = KpGetFileSizeFile(in_file, &ll);

   if((plFileLen!=NULL) && SUCCEEDED(retc)) *plFileLen=ll;

   ll += KP_MAX_FILE_LIN_LEN + ll / 2; // MT8+ 4x1 kazkas netelpa lucija-st@yandex.ru
   KP_NEWA(*plpszFileContPtr, unsigned char, ll + 4 + 1); // papildom 4, kad apvalintøsi iki þodþio ribos

// ---------------------------------
   if(SUCCEEDED(retc))
   {
      pntd = *plpszFileContPtr;

      while((!feof(in_file)) && SUCCEEDED(retc))
      {
         if (pntd - (*plpszFileContPtr) >= ll)
         {
            unsigned char str_buf[KP_MAX_FNAME_LEN * 2 + 1];
            sprintf((char *)str_buf, "%s[%d]", lpszFileName, ll);
            KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, str_buf, False, __FILE__, __LINE__, 0L);
            retc = KP_E_BUFFER_OVERFLOW;
         }

         if(SUCCEEDED(retc))
         {
            *pntd=fgetc(in_file);
            if(ferror(in_file))
               retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, bCheckFileNotFound?lpszFileName:null, True, __FILE__, __LINE__, 0L);
         }

         if((!feof(in_file)) && SUCCEEDED(retc)) pntd++;
      }

      if((plFileLen != NULL) && SUCCEEDED(retc)) *plFileLen = pntd - *plpszFileContPtr; // patikslinam – tekstiniams failams gali sumaþët po /r/n konvertavimo

      *pntd=Nul;
   }
   if (retc == KP_E_BUFFER_OVERFLOW) retc = S_OK;

// ---------------------------------
   if(in_file) fclose(in_file);
   in_file=NULL;

return(retc);
}


HRESULT MakeWordListFile(const unsigned char *lpszFileName)
{
HRESULT retc = S_OK;
fstream in_file;
fstream out_file;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char fname[KP_MAX_FNAME_LEN+1];
static unsigned char ftype[KP_MAX_FTYPE_LEN+1];
static unsigned char out_fname[KP_MAX_FNAME_LEN+1];
bool spc_eol_fl = False;
unsigned char ch;

   if((lpszFileName == null) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszFileName, ios_base::in);
      if(in_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFileName, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      retc = TvFnameSplit(disk, path, fname, ftype, lpszFileName);

      if(SUCCEEDED(retc))
      {
         strcpy(out_fname, disk);
         strcat(out_fname, path);
         if(strchr(lpszFileName, '\\')) strcat(out_fname, "\\");
         else strcat(out_fname, "/");
         strcat(out_fname, fname);
         strcat(out_fname, ".lst");

// KP_TRACE_1("MakeWordListFile: %s", out_fname);

         out_file.open((const char *)out_fname, ios_base::out);
         if(out_file.fail())
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_fname, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         spc_eol_fl = False;

         do
         {
            in_file.get((char &)ch); // in_file >> ch;
            if(in_file.eof()) retc = KP_E_EOF;
            if(SUCCEEDED(retc)) if(in_file.fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if(strchr(lpszSpcEol, ch) != NULL) spc_eol_fl = True;
               else
               {
                  if(spc_eol_fl) out_file << endl;
                  spc_eol_fl = False;

                  out_file << ch;

                  if(out_file.fail())
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_fname, True, __FILE__, __LINE__, 0L);
               }
            }

         } while(SUCCEEDED(retc));

         if(retc == KP_E_EOF) retc = S_OK;

         if(SUCCEEDED(retc))
         {
            out_file.close();
            if(out_file.fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_fname, True, __FILE__, __LINE__, 0L);
         }

      } // else // if(out_file.fail())

      in_file.close();

   } // else // if(in_file.fail())

return(retc);
}


// --------------------------------
HRESULT CreatePath(const unsigned char *lpszPathName, bool bPutErrorMsg)
{
HRESULT retc=S_OK;
unsigned char path_buf[KP_MAX_FNAME_LEN+1];
/* const */ unsigned char *pnts;
unsigned char *pntd;
DWORD err=NO_ERROR;

// KP_TRACE_2("CreatePath(%s, %d)", lpszPathName, bPutErrorMsg);

   if(lpszPathName==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(strlen(lpszPathName)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      strcpy(path_buf, lpszPathName);

      pnts = strchr(path_buf, ':');
      if(pnts != NULL) pnts++;
      else
      {
        pnts = strstr(path_buf, "\\\\");
        if(pnts == NULL) pnts = strstr(path_buf, "//");
        if(pnts != NULL){ *pnts++ = '\\'; *pnts++ = '\\'; }
        else pnts = path_buf;
      }
      if((*pnts == '\\') || (*pnts == '/')) *pnts++ = '\\';

      do
      {
         pntd = strchr(pnts, '\\');
         if(pntd == NULL) pntd = strchr(pnts, '/');
         if(pntd != NULL)
         {
            *pntd = Nul;

            if(!CreateDirectory((const char *)path_buf, NULL))
            {
// unsigned char str_buf[400];
// strcpy(str_buf, path_buf);
// EncodeText(str_buf);
// KpErrorProc.OutputErrorMessage(S_OK, str_buf, False, __FILE__, __LINE__, 0L);

               err=GetLastError();
               if((err!=ERROR_ALREADY_EXISTS) && (err!=NO_ERROR))
               {
                  retc = KP_E_DIR_ERROR;
                  KpErrorProc.OutputErrorMessage(retc, err, bPutErrorMsg && (err!=SE_ERR_ACCESSDENIED), __FILE__, __LINE__, 0L);
               }
            }

            *(pntd++) = '\\';
            pnts=pntd;
         }

      } while((pntd!=NULL) && SUCCEEDED(retc));
   }

return(retc);
}


// ----------------------------------
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT KpCountFolderFileSizeCnt(const unsigned char *lpszPath, int *piCount, long *plSize)
{
HRESULT retc=S_OK;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
unsigned char *user_fmask = NULL;
unsigned char *user_file = NULL;
int cnt = 0;
long file_size = 0L;
long full_size = 0L;
int dir_cnt = 0;

   KP_ASSERT(lpszPath, E_INVALIDARG, null, True);
// KP_ASSERT(piCount, E_INVALIDARG, null, True);
// KP_ASSERT(plSize, E_INVALIDARG, null, True);

   KP_NEWA(user_fmask, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(user_file, unsigned char, KP_MAX_FNAME_LEN + 100);

// -------------------------------
   KP_ASSERT(strlen(lpszPath) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(user_fmask, lpszPath);
      strcat(user_fmask, "\\*.*");
   }

// --------------- atidarom
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)user_fmask, &file_data);
   if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      retw = GetLastError();
      if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
      {
         KP_WARNING(KP_E_SYSTEM_ERROR, user_fmask);
         KP_ERROR(KP_E_SYSTEM_ERROR, retw);
      }
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
   {
      KP_ASSERT(strlen(lpszPath) + 1 + strlen(file_data.cFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

      if(SUCCEEDED(retc))
      {
         strcpy(user_file, lpszPath);
         strcat(user_file, "\\");
         strcat(user_file, file_data.cFileName);
      }
// KpMsgOutF_2("----- %s %s", lpszPath, file_data.cFileName);
      if(SUCCEEDED(retc))
      {
// ---------- pakatalogis
         if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
            {
// KpMsgOutF_2("===== %s %s", user_file, file_data.cFileName);
               retc = KpCountFolderFileSizeCnt(user_file, &dir_cnt, &file_size);
               if(SUCCEEDED(retc))
               {
                  cnt += dir_cnt + 1; // pridedam dar ir katalogà
                  full_size += file_size;
               }
            }
         }
         else
         {
// ------------------ paprastas failas
// ---------------- failø skaièius
            cnt++;

// ---------------- failo dydis
            if(SUCCEEDED(retc)) retc = KpGetFileSizeName(user_file, &file_size);
            if(SUCCEEDED(retc))
            {
               file_size /= 1000;
               if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ;
               full_size += file_size;
            }

         } // else // if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

      } // if(SUCCEEDED(retc))

// ---------------- kitas failas
      retw = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retw = GetLastError();
            if(retw == ERROR_NO_MORE_FILES)
            {
               // retc = KP_E_FILE_NOT_FOUND;
            }
            else KP_ERROR(KP_E_SYSTEM_ERROR, retw);
         }

   } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// --------------- uþdarom
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      if(!FindClose(enumeration))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      enumeration = INVALID_HANDLE_VALUE;

   } // if(enumeration != INVALID_HANDLE_VALUE)

   if(SUCCEEDED(retc))
   {
      if(piCount) *piCount = cnt;
      if(plSize) *plSize = full_size;
   }

   KP_DELETEA(user_file);
   KP_DELETEA(user_fmask);

return(retc);
}
#endif



// ----------------------------------
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT KpDeleteFolderContents(const unsigned char *lpszPath,
   HWND hProgressWnd, time_t iStartTime, long lFullSize, long *plProcessedSize, long *plUsbSpeed)
{
HRESULT retc=S_OK;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
unsigned char *user_fmask = null;
unsigned char *user_file = null;
unsigned char *str_buf = null;
time_t cur_time;
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];

   KP_ASSERT(lpszPath, E_INVALIDARG, null, True);

   KP_NEWA(user_fmask, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(user_file, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(str_buf, unsigned char, KP_MAX_FNAME_LEN + 200);

// -------------------------------
   KP_ASSERT(strlen(lpszPath) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(user_fmask, lpszPath);
      strcat(user_fmask, "\\*.*");
   }

// --------------- atidarom
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)user_fmask, &file_data);
   if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      retw = GetLastError();
      if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
         KP_ERROR(KP_E_SYSTEM_ERROR, retw);
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
   {
      KP_ASSERT(strlen(lpszPath) + 1 + strlen(file_data.cFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

      if(SUCCEEDED(retc))
      {
         strcpy(user_file, lpszPath);
         strcat(user_file, "\\");
         strcat(user_file, file_data.cFileName);
      }

      if(SUCCEEDED(retc))
      {
// ---------- pakatalogis
         if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
            {
// ------------- trinam rekursiðkai
               if(SUCCEEDED(retc)) retc = KpDeleteFolderContents(user_file, hProgressWnd, iStartTime, lFullSize, plProcessedSize, plUsbSpeed);

// ----------- progreso langelio praneðimas
               if(hProgressWnd && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, user_file);
                  if(SUCCEEDED(retc))
                  {
                     sprintf((char *)str_buf, (const char *)KP_MSG_DELETING_FILE, fname, ftype); // user_file);
                     retc = KpSetProgressTxt(hProgressWnd, str_buf);
                  }

// ----------- nustatom progreso langelio naujà pradinæ pozicijà
                  if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(hProgressWnd);

// ----------- pridedam katalogo trynimo ekvivalentiná laikà
                  KP_ASSERT(plProcessedSize, E_INVALIDARG, null, True);
                  (*plProcessedSize) += KPIO_DIR_ACCESS_FILE_SIZE_EQ;
               }

// ---------- trinam katalogà
               KP_ASSERT(RemoveDirectory((const char *)user_file), KP_E_DIR_ERROR, user_file, True);
            }
         }
         else
         {
// ------------------ paprastas failas

// ----------- progreso langelio praneðimas
            if(hProgressWnd && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, user_file);
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)str_buf, (const char *)KP_MSG_DELETING_FILE, fname, ftype); // user_file);
                  retc = KpSetProgressTxt(hProgressWnd, str_buf);
               }

// ----------- nustatom progreso langelio naujà pradinæ pozicijà
               if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(hProgressWnd);

// ----------- pridedam failo trynimo ekvivalentiná laikà
               KP_ASSERT(plProcessedSize, E_INVALIDARG, null, True);
               (*plProcessedSize) += KPIO_DIR_ACCESS_FILE_SIZE_EQ;
            }

// --------------- trinam failà
            KP_ASSERT(DeleteFile((const char *)user_file), KP_E_DIR_ERROR, user_file, True);

         } // else // if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
         if(hProgressWnd && SUCCEEDED(retc))
         {
            KP_ASSERT(plProcessedSize, E_INVALIDARG, null, True);
            KP_ASSERT(plUsbSpeed, E_INVALIDARG, null, True);

            if(SUCCEEDED(retc))
            {
               time(&cur_time);
               cur_time -= iStartTime;
               if(cur_time <= 0) cur_time = 1;

//             (*plProcessedSize) += KPIO_DIR_ACCESS_FILE_SIZE_EQ;

               *plUsbSpeed = *plProcessedSize / cur_time;
            }

            if(SUCCEEDED(retc)) retc = KpSetProgressTime(hProgressWnd, Maxint); // (int)(lFullSize / *plUsbSpeed));
//          if(SUCCEEDED(retc)) retc = KpSetProgressPos(hProgressWnd, (int)(*plProcessedSize * 100 / lFullSize));
//          if(SUCCEEDED(retc)) retc = KpSetProgressPosInc(hProgressWnd, KPIO_DIR_ACCESS_FILE_SIZE_EQ);
            if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(hProgressWnd, *plProcessedSize, lFullSize);
         }

      } // if(SUCCEEDED(retc))

// ---------------- kitas failas
      retw = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retw = GetLastError();
            if(retw == ERROR_NO_MORE_FILES)
            {
               // retc = KP_E_FILE_NOT_FOUND;
            }
            else KP_ERROR(KP_E_SYSTEM_ERROR, retw);
         }

   } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// --------------- uþdarom
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      if(!FindClose(enumeration))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      enumeration = INVALID_HANDLE_VALUE;

   } // if(enumeration != INVALID_HANDLE_VALUE)

   KP_DELETEA(str_buf);
   KP_DELETEA(user_file);
   KP_DELETEA(user_fmask);

return(retc);
}
#endif


// ----------------------------------
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT KpCopyFolder(const unsigned char *lpszSrcPath, const unsigned char *lpszDstPath,
   HWND hProgressWnd, time_t iStartTime, long lFullSize, long *plProcessedSize, long *plUsbSpeed, bool bOutMsg)
{
HRESULT retc=S_OK;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
unsigned char *src_fmask = NULL;
unsigned char *src_file = NULL;
unsigned char *dst_file = NULL;
unsigned char *str_buf= NULL;
long file_size;
time_t cur_time;
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];
BOOL cancel = False;

   KP_ASSERT(lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszDstPath, E_INVALIDARG, null, True);

   KP_NEWA(src_fmask, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(src_file, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(dst_file, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(str_buf, unsigned char, KP_MAX_FNAME_LEN + 200);

// -------------------------------
   KP_ASSERT(strlen(lpszSrcPath) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(src_fmask, lpszSrcPath);
      strcat(src_fmask, "\\*.*");
   }

// --------------- atidarom
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)src_fmask, &file_data);
   if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      retw = GetLastError();
      if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
         KP_ERROR(KP_E_SYSTEM_ERROR, retw);
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
   {
      KP_ASSERT(strlen(lpszSrcPath) + 1 + strlen(file_data.cFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(src_file, lpszSrcPath);
         strcat(src_file, "\\");
         strcat(src_file, file_data.cFileName);
      }

      KP_ASSERT(strlen(lpszDstPath) + 1 + strlen(file_data.cFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(dst_file, lpszDstPath);
         strcat(dst_file, "\\");
         strcat(dst_file, file_data.cFileName);
      }

// ----------- progreso langelio praneðimas
#if FALSE
      if(hProgressWnd && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, src_file);
         if(SUCCEEDED(retc))
         {
            sprintf((char *)str_buf, KP_MSG_COPYING_FILE, fname, ftype); // src_file);
            retc = KpSetProgressTxt(hProgressWnd, str_buf);
         }
      }
#endif

      if(SUCCEEDED(retc))
      {
// ---------- pakatalogis
         if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
            {
// ----------- progreso langelio praneðimas
               if(hProgressWnd && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, dst_file);
                  if(SUCCEEDED(retc))
                  {
                     sprintf((char *)str_buf, (const char *)KP_MSG_COPYING_DIR, fname, ftype); // dst_file);
                     retc = KpSetProgressTxt(hProgressWnd, str_buf);
                  }
               }

// ----------- kuriam katalogà
               if(SUCCEEDED(retc))
               {
                  strcpy(str_buf, dst_file);
                  strcat(str_buf, "\\");
                  retc = CreatePath(str_buf, bOutMsg);
               }

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
               if(hProgressWnd && SUCCEEDED(retc))
               {
                  KP_ASSERT(plProcessedSize, E_INVALIDARG, null, True);
                  KP_ASSERT(plUsbSpeed, E_INVALIDARG, null, True);

                  if(SUCCEEDED(retc))
                  {
                     time(&cur_time);
                     cur_time -= iStartTime;
                     if(cur_time <= 0) cur_time = 1;

// ----------- pridedam katalogo kûrimo ekvivalentiná laikà
                     (*plProcessedSize) += KPIO_DIR_ACCESS_FILE_SIZE_EQ;

                     *plUsbSpeed = *plProcessedSize / cur_time;
                  }

                  if(SUCCEEDED(retc)) retc = KpSetProgressTime(hProgressWnd, Maxint); // (int)(lFullSize / *plUsbSpeed));
//                if(SUCCEEDED(retc)) retc = KpSetProgressPos(hProgressWnd, (int)(*plProcessedSize * 100 / lFullSize));
                  if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(hProgressWnd, *plProcessedSize, lFullSize);
               }

// ---------- kopijuojam rekursiðkai
               if(SUCCEEDED(retc)) retc = KpCopyFolder(src_file, dst_file, hProgressWnd, iStartTime, lFullSize, plProcessedSize, plUsbSpeed, bOutMsg);
            }
         }
         else
         {
// ------------------ paprastas failas

// ----------- progreso langelio praneðimas
            if(hProgressWnd && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, dst_file);
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)str_buf, (const char *)KP_MSG_COPYING_FILE, fname, ftype); // dst_file);
                  retc = KpSetProgressTxt(hProgressWnd, str_buf);
               }
            }

// ----------- kuriam katalogà
            if(SUCCEEDED(retc)) retc = CreatePath(dst_file, bOutMsg);

// --------------- kopijuojam
            if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(hProgressWnd);
//          if(SUCCEEDED(retc)) if(!CopyFile((const char *)src_file, (const char *)dst_file, False))
            if(SUCCEEDED(retc)) if(!CopyFileEx((const char *)src_file, (const char *)dst_file, KpCopyFileCallBack, &hProgressWnd, &cancel, 0L))
            {
               KpErrorProc.OutputErrorMessage(KP_E_FERROR, dst_file, bOutMsg, __FILE__, __LINE__, 0L, NULL);
               retc = KP_E_FERROR;
            }

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
            if(hProgressWnd && SUCCEEDED(retc))
            {
               KP_ASSERT(plProcessedSize, E_INVALIDARG, null, True);
               KP_ASSERT(plUsbSpeed, E_INVALIDARG, null, True);

               if(SUCCEEDED(retc)) retc = KpGetFileSizeName(src_file, &file_size);
               if(SUCCEEDED(retc))
               {
                  file_size /= 1000;
                  if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ;
               }

               if(SUCCEEDED(retc))
               {
                  time(&cur_time);
                  cur_time -= iStartTime;
                  if(cur_time <= 0) cur_time = 1;

                  (*plProcessedSize) += file_size + KPIO_DIR_ACCESS_FILE_SIZE_EQ;

                  *plUsbSpeed = *plProcessedSize / cur_time;
               }

               if(SUCCEEDED(retc)) retc = KpSetProgressTime(hProgressWnd, Maxint); // (int)(lFullSize / *plUsbSpeed));
//             if(SUCCEEDED(retc)) retc = KpSetProgressPos(hProgressWnd, (int)(*plProcessedSize * 100 / lFullSize));
               if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(hProgressWnd, *plProcessedSize, lFullSize);
            }

         } // else // if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

      } // if(SUCCEEDED(retc))

// ---------------- kitas failas
      retw = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retw = GetLastError();
            if(retw == ERROR_NO_MORE_FILES)
            {
               // retc = KP_E_FILE_NOT_FOUND;
            }
            else KP_ERROR(KP_E_SYSTEM_ERROR, retw);
         }

   } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// --------------- uþdarom
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      if(!FindClose(enumeration))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      enumeration = INVALID_HANDLE_VALUE;

   } // if(enumeration != INVALID_HANDLE_VALUE)

   KP_DELETEA(str_buf);
   KP_DELETEA(dst_file);
   KP_DELETEA(src_file);
   KP_DELETEA(src_fmask);

return(retc);
}
#endif


// ----------------------------------
HRESULT ConvertSlashes(unsigned char *lpszPath, unsigned char cSlash)
{
HRESULT retc=S_OK;
unsigned char *pnts = NULL;

   KP_ASSERT(lpszPath, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszPath;
      while(*pnts)
      {
         if((*pnts == '/') || (*pnts == '\\')) *pnts = cSlash;
         pnts++;
      }
   }

return(retc);
}


// ------------------- set file creation date
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT ChFileTimeCrtd(const unsigned char* lpszFName, const SYSTEMTIME *ptt)
{
HRESULT retc=S_OK;
HANDLE hh=INVALID_HANDLE_VALUE;
FILETIME ft;

   if((lpszFName==NULL) || (ptt==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!SystemTimeToFileTime(ptt, &ft))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
         retc=KP_E_SYSTEM_ERROR;
#endif
      }

   if(SUCCEEDED(retc))
   {
      hh=CreateFile((const char *)lpszFName, GENERIC_WRITE, FILE_SHARE_WRITE,
               0, OPEN_EXISTING, /* FILE_ATTRIBUTE_NORMAL| */ FILE_FLAG_BACKUP_SEMANTICS, 0);
      if(hh==INVALID_HANDLE_VALUE)
      {
#if FALSE // #ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
         retc=KP_E_FILE_NOT_FOUND;
#endif
      }
      else
      {
         if(!SetFileTime(hh, &ft, 0, &ft))
         {
#if FALSE // #ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
            retc=KP_E_FERROR;
#endif
         }

         if(!CloseHandle(hh))
            if(SUCCEEDED(retc))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
               retc=KP_E_FERROR;
#endif
            }
      }
   }

return(retc);
}
#endif


// ------------------- get file creation date
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT KpGetFileCrTime(const unsigned char* lpszFName, SYSTEMTIME *pCrTime, SYSTEMTIME *pWrTime)
{
HRESULT retc=S_OK;
HANDLE hh=INVALID_HANDLE_VALUE;
FILETIME cr_time;
FILETIME wr_time;

   KP_ASSERT(lpszFName, E_INVALIDARG, null, True);
// KP_ASSERT(pCrTime, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      hh = CreateFile((const char *)lpszFName, GENERIC_READ, FILE_SHARE_READ,
               0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS /* FILE_ATTRIBUTE_NORMAL */, 0);
      if(hh == INVALID_HANDLE_VALUE)
      {
#if FALSE // #ifdef Debug
         KP_ERROR(KP_E_FILE_NOT_FOUND, GetLastError());
#else
         retc = KP_E_FILE_NOT_FOUND;
#endif
      }
      else
      {
         KP_ASSERT(GetFileTime(hh, &cr_time, NULL, &wr_time), KP_E_FERROR, GetLastError(), True);

         if(pCrTime != NULL) KP_ASSERT(FileTimeToSystemTime(&cr_time, pCrTime), KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(pWrTime != NULL) KP_ASSERT(FileTimeToSystemTime(&wr_time, pWrTime), KP_E_SYSTEM_ERROR, GetLastError(), True);


         if(!CloseHandle(hh))
            if(SUCCEEDED(retc))
            {
#ifdef Debug
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
//             retc=KP_E_FERROR;
#endif
            }
      }
   }

return(retc);
}
#endif


HRESULT PutLogDate(fstream *poutFile)
{
HRESULT retc = S_OK;
time_t ltime;
tm *tm_ptr=NULL;

   if((poutFile == NULL) && SUCCEEDED(retc))
   {
      retc = E_INVALIDARG;
//    KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      time(&ltime);
      tm_ptr=gmtime(&ltime);
      if(tm_ptr == NULL)
      {
         retc = KP_E_SYSTEM_ERROR;
//       KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      poutFile->fill('0');

      poutFile->width(4);
      *poutFile << tm_ptr->tm_year + 1900 << ".";

      poutFile->width(2);
      *poutFile << tm_ptr->tm_mon + 1 << ".";

      poutFile->width(2);
      *poutFile << tm_ptr->tm_mday << " ";

      poutFile->width(2);
      *poutFile << (tm_ptr->tm_hour + 2) % 24 << ":";

      poutFile->width(2);
      *poutFile << tm_ptr->tm_min << ":";

      poutFile->width(2);
      *poutFile << tm_ptr->tm_sec;

      *poutFile << " " << lpszProdName << "[";

      poutFile->width(5);
      *poutFile << iProdVerGlob << ":" << lpszProdDate << "] ";

      poutFile->fill(' ');
      poutFile->width(1);

      *poutFile << ltime;

      if(poutFile->fail())
      {
         retc = KP_E_FERROR;
//       KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


#undef KP_LOCAL_LOG_FILE
#ifdef Debug
#define KP_LOCAL_LOG_FILE
#endif
#ifdef Logging
#define KP_LOCAL_LOG_FILE
#endif
HRESULT GetLogFileName(unsigned char *lpszLogFName)
{
HRESULT retc = S_OK;
const unsigned char *temp_dir = null;
// static unsigned char temp_dir[KP_MAX_FNAME_LEN + 1];
#ifdef KP_LOCAL_LOG_FILE
// static unsigned char fname_temp[KP_MAX_FNAME_LEN + 1];
#endif
static unsigned char disk_temp[KP_MAX_FNAME_LEN + 1];
static unsigned char path_temp[KP_MAX_FNAME_LEN + 1];
static unsigned char name_temp[KP_MAX_FNAME_LEN + 1];
static unsigned char type_temp[KP_MAX_FNAME_LEN + 1];
static unsigned char app_name[KP_MAX_FNAME_LEN + 1];
static unsigned char disk_app[KP_MAX_FNAME_LEN + 1];
static unsigned char path_app[KP_MAX_FNAME_LEN + 1];
static unsigned char name_app[KP_MAX_FNAME_LEN + 1];
static unsigned char type_app[KP_MAX_FNAME_LEN + 1];
int ii;

   if((lpszLogFName == NULL) && SUCCEEDED(retc))
   {
      retc = E_INVALIDARG;
//    KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
#ifdef KP_LOCAL_LOG_FILE
#	if FALSE
      KP_ASSERT(GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)fname_temp, NULL),
         KP_E_SYSTEM_ERROR, GetLastError(), True);
      temp_dir = fname_temp;
#	endif
static unsigned char local_dir[KP_MAX_FNAME_LEN + 1];
		retc = GetLocalPath(local_dir, KP_LocalDir, False);
		temp_dir = local_dir;
#else
      temp_dir = (unsigned char *)getenv("TEMP");
//		retc = GetLocalPath(temp_dir, KP_Temp_Dir, False); // lûþta statiniuose destruktoriuose
#endif
//    if(temp_dir == NULL) retc = KP_E_SYSTEM_ERROR;
   }

   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk_temp, path_temp, name_temp, type_temp, temp_dir);

   if(SUCCEEDED(retc)) retc = GetAppName(app_name);

   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk_app, path_app, name_app, type_app, app_name);

   if(SUCCEEDED(retc))
   {
      strcpy(app_name, disk_temp);
      strcat(app_name, path_temp);
      ii=strlen(app_name);
      if(ii>0){ if(app_name[ii-1]!='\\') strcat(app_name, "\\"); }
      else strcat(app_name, "\\");
      strcat(app_name, name_temp);
      strcat(app_name, "\\");
      strcat(app_name, name_app);
      strcat(app_name, ".log");

   }

   if(lpszLogFName)
   {
      *lpszLogFName = Nul;
      if(SUCCEEDED(retc)) strcpy(lpszLogFName, app_name);
   }

return(retc);
}


HRESULT DelLogFile(void)
{
HRESULT retc = S_OK;
static unsigned char log_fname[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc)) retc = GetLogFileName(log_fname);
   DeleteFile((const char *)log_fname);

return(retc);
}


HRESULT PutLogMessage(const unsigned char *lpszMsg, unsigned char *lpszLogFName)
{
HRESULT retc = S_OK;
FILE *log_file=NULL;
static unsigned char log_fname[KP_MAX_FNAME_LEN+1];
time_t ltime;
tm *tm_ptr=NULL;
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];
#ifndef ENCODE_LOG
bool xfs_fl = False;
#endif
unsigned char *out_str = null;
int out_str_len = 0;
const unsigned char *pnts = null;

   out_str_len = KP_MAX_FILE_LIN_LEN + 1;
   if(lpszMsg != null) out_str_len += strlen(lpszMsg);

// KP_NEWA(out_str, unsigned char, out_str_len); // iððkvieèiamas ir ið KP_NEWA, gali uzsiciklint
   out_str = new unsigned char[out_str_len];
   if(out_str == null) retc = KP_E_OUTOFMEM;

   if(SUCCEEDED(retc)) retc = GetLogFileName(log_fname);

#ifndef ENCODE_LOG
   if(SUCCEEDED(retc)) if(strstr(log_fname, KP_XFS_LOG_FNAME) != null) xfs_fl = True;
#endif

   if(SUCCEEDED(retc))
   {
//    log_file = fopen((const char *)log_fname, xfs_fl?"ab":"a");
      log_file = fopen((const char *)log_fname,
#ifdef ENCODE_LOG
         "ab"
#else
         "a"
#endif
         );
      if(log_file == NULL) retc = KP_E_DIR_ERROR;
   }

   if(SUCCEEDED(retc))
   {
      time(&ltime);
      tm_ptr=gmtime(&ltime);
      if(tm_ptr) sprintf((char *)out_str, "%04d.%02d.%02d %02d:%02d:%02d %s[%05d:%s] %ld ",
         1900+tm_ptr->tm_year, 1+tm_ptr->tm_mon, tm_ptr->tm_mday, tm_ptr->tm_hour+2, tm_ptr->tm_min, tm_ptr->tm_sec,
         lpszProdName, iProdVerGlob, lpszProdDate, ltime);

#if FALSE
      if(xfs_fl)
      {
         pnts = out_str;
         while(*pnts) fputc(*pnts++ ^ 0xAA, log_file);
         if(lpszMsg)
         {
            pnts = lpszMsg;
            while(*pnts) fputc(*pnts++ ^ 0xAA, log_file);
         }
         fputc('\r' ^ 0xAA, log_file);
         fputc('\n' ^ 0xAA, log_file);
      }
      else
      {
         fputs((const char *)out_str, log_file);
         if(lpszMsg) fputs((const char *)lpszMsg, log_file);
         fputs("\n", log_file);
      }
#else
      if(lpszMsg != null) strcat(out_str, lpszMsg);
      strcat(out_str, "\n");
      out_str_len = strlen(out_str);
#  ifdef ENCODE_LOG
      if(SUCCEEDED(retc)) retc = EncodeLogBuf(out_str, out_str_len);
#  endif
      fwrite(out_str, out_str_len, 1, log_file);
#endif

      if(feof(log_file) || ferror(log_file)) retc = KP_E_FERROR;

      if(fclose(log_file)) retc = KP_E_FERROR;
   }

   if(lpszLogFName)
   {
      *lpszLogFName = Nul;
//    if(SUCCEEDED(retc)) strcpy(lpszLogFName, log_fname);
      if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, lpszLogFName, ftype, log_fname);
      if(SUCCEEDED(retc)){ strcat(lpszLogFName, "."); strcat(lpszLogFName, ftype); }
   }

// KP_DELETEA(out_str); // iððkvieèiamas ir ið KP_DELETEA, gali uzsiciklint
   if(out_str != null) delete [] out_str;
   out_str = null;

return(retc);
}


HRESULT PutLogMessage(const char *lpszMsg, unsigned char *lpszLogFName)
{
return(PutLogMessage((const unsigned char *)lpszMsg, lpszLogFName));
}


HRESULT PutLogMessage(const KpChar *iazMsg, unsigned char *lpszLogFName)
{
HRESULT retc = S_OK;
unsigned char *str_buf = null;

   KP_ASSERT(iazMsg != NULL, E_INVALIDARG, null, True);

// KP_NEWA(str_buf, unsigned char, TvKpStrLen(iazMsg) + 1); // iððkvieèiamas ir ið KP_NEWA, gali uzsiciklint
   str_buf = new unsigned char[TvKpStrLen(iazMsg) + 1];
   if(str_buf == null) retc = KP_E_OUTOFMEM;

   if(SUCCEEDED(retc)) KptStrDecode(str_buf, iazMsg, TV_MAIN_CTBL);

   if(SUCCEEDED(retc)) PutLogMessage(str_buf, lpszLogFName);

// KP_DELETEA(str_buf); // iððkvieèiamas ir ið KP_DELETEA, gali uzsiciklint
   if(str_buf != null) delete [] str_buf;
   str_buf = null;

return(retc);
}


HRESULT CopyLogToDesktop(void)
{
HRESULT retc = S_OK;
static unsigned char log_full_path_temp[KP_MAX_FNAME_LEN + 1];
static unsigned char log_full_path_desktop[KP_MAX_FNAME_LEN + 1];
static unsigned char log_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetLogFileName(log_full_path_temp);

   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, log_fname, ftype, log_full_path_temp);
   if(SUCCEEDED(retc)){ strcat(log_fname, "."); strcat(log_fname, ftype); }

   if(SUCCEEDED(retc)) retc = GetLocalPath(log_full_path_desktop, KP_Desktop);
   if(SUCCEEDED(retc)) strcat(log_full_path_desktop, log_fname);

   KP_ASSERT(CopyFile((const char *)log_full_path_temp, (const char *)log_full_path_desktop, False), KP_E_FERROR, null, False); // True negalima, nes uþsiciklins

return(retc);
}


// --------------------------------------------------
HRESULT PutEncodedLogMsg(const unsigned char *lpszMsg, fstream *pOutFile)
{
HRESULT retc = S_OK;
unsigned char *file_buf = null;
int file_len = 0;

   KP_ASSERT(lpszMsg != null, E_INVALIDARG, null, True);
   KP_ASSERT(pOutFile != NULL, E_INVALIDARG, null, True);

   file_len = strlen(lpszMsg);
   KP_NEWA(file_buf, unsigned char, file_len + 1);

   if(SUCCEEDED(retc)) strcpy(file_buf, lpszMsg);

#ifdef ENCODE_LOG
   if(SUCCEEDED(retc)) retc = EncodeLogBuf(file_buf, file_len);
#endif

   if(SUCCEEDED(retc)) pOutFile->write((const char *)file_buf, file_len);

   KP_DELETEA(file_buf);

return(retc);
}


// --------------------------------------------------
HRESULT DecodeXfsLog(const unsigned char *lpszLogFname, fstream *pOutFile, bool bOutMsg)
{
HRESULT retc = S_OK;
fstream in_file;
bool end_fl = False;
unsigned char in_ch;

// KpMsgOutF("DecodeXfsLog(): %s", lpszLogFname);

   KP_ASSERTE(pOutFile != NULL, E_INVALIDARG, null, bOutMsg);
   KP_ASSERTE(lpszLogFname != NULL, E_INVALIDARG, null, bOutMsg);

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszLogFname, ios_base::in | ios_base::binary);
      KP_ASSERTE(!in_file.fail(), KP_E_FILE_NOT_FOUND, lpszLogFname, bOutMsg);
   }

   end_fl = False;
   if(SUCCEEDED(retc)) do
   {
      in_file.read((char *)&in_ch, 1);
      end_fl = in_file.eof();
      if(!end_fl)
      {
         KP_ASSERTE(!in_file.fail(), KP_E_FERROR, lpszLogFname, bOutMsg);

         if(SUCCEEDED(retc))
         {
            *pOutFile << (char)(in_ch ^ 0xAA);
            KP_ASSERTE(!pOutFile->fail(), KP_E_FERROR, null, bOutMsg);
         }
      }
   } while(!end_fl && SUCCEEDED(retc));

return(retc);
}


HRESULT EncodeLogBuf(unsigned char *pBuffer, int iDataLen)
{
HRESULT retc = S_OK;

   KP_ASSERT(pBuffer != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) for(int ii = 0; ii < iDataLen; ii++) pBuffer[ii] ^= 0xAA;

return(retc);
}


HRESULT EncodeLogBase64(const unsigned char *lpszFname, fstream *pOutFile)
{
HRESULT retc = S_OK;
fstream in_file;
fstream base64_file;
unsigned char base64_fname[KP_MAX_FNAME_LEN + 1];
base64::encoder E;
unsigned char *file_buf = null;
long file_len = 0L;

   KP_ASSERT(pOutFile != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetLocalPath(base64_fname, KP_LocalDir, False);
   if(SUCCEEDED(retc)) strcat(base64_fname, "\\base64.txt");

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszFname, ios_base::in | ios_base::binary);
      KP_ASSERTE(!in_file.fail(), KP_E_FILE_NOT_FOUND, base64_fname, False);

      if(SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) base64_file.open((const char *)base64_fname, ios_base::out);
         KP_ASSERT(!base64_file.fail(), KP_E_DIR_ERROR, base64_fname, False);

         if(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) E.encode(in_file, base64_file);
            base64_file.close();
         }

         if(SUCCEEDED(retc)) if(!in_file.eof()) KP_ASSERTE(!in_file.fail(), KP_E_FERROR, base64_fname, False);
         KP_ASSERTE(!pOutFile->fail(), KP_E_FERROR, base64_fname, False);

         in_file.close();
      }
   }

   if(SUCCEEDED(retc)) retc = ReadFileContents(base64_fname, &file_buf, &file_len, False, False);
#ifdef ENCODE_LOG
   if(SUCCEEDED(retc)) retc = EncodeLogBuf(file_buf, file_len);
#endif
   if(SUCCEEDED(retc)) pOutFile->write((const char *)file_buf, file_len);
   KP_ASSERTE(!pOutFile->fail(), KP_E_FERROR, null, False);

   KP_DELETEA(file_buf);

   if(SUCCEEDED(retc)) DeleteFile((const char *)base64_fname);

return(retc);
}


// ----------------------------------------------- for kpx compatibility
void File::cfclr(void)
{
   fn[0] = '\0';
   tmpfn[0] = '\0';
   fwfl = devfl = False;
   conwn = NULL;
   fp = NULL;
   vbufp = NULL;
   filpnt = 0l;
   filelen = 0l;
   buffl = False;
}


FILE *File::cfopen(const unsigned char *fnam, const unsigned char *mode, Wndw *wn)
{
// unsigned char drive[MAXDRIVE], dir[MAXDIR], buf[10];
unsigned char *fnpnt;
// Wndw *wnsav;
bool err;

   err = False;
   cfclr();
   strncpy(fn, fnam, Fnsiz);
   msbcpy(fn, fn);
   strlwr(fn);
   cfstat(mode, wn);
   if(fwfl && (!devfl))
   {
//    fnpnt = tmpfn;
//    fnsplit(fn, drive, dir, buf, buf);
//    strcpy(buf, "KP$$$");
//    strcat(buf, cfunpk(T_mpfn, 3));
//    T_mpfn = (T_mpfn + 1) % 1000;
//    fnmerge(fnpnt, drive, dir, buf, "._kp");
   }
   else fnpnt = fn;

   if(!(fwfl && (conwn != NULL)))
   {
      if((fp = fopen((const char *)fnpnt, (const char *)mode)) == NULL) cfclr();
      else
      {
#if FALSE
         filelen = filelength(fileno(fp));
#else
         if (fseek(fp, 0, SEEK_END) != 0) err = True;
         if(!err) filelen = ftell(fp);
#endif
         if(filelen < 0l) cfpurge();
         else cwfseek(0l);
      }
   }
   else
   {
//    wnsav=W_curw;
//    wintop(conwn);
//    fp = &T_fictf;
//    wincur(wnsav);
   }

   if(err) cfclr();

return(fp);
}


FILE *File::cvfopen(const unsigned char *fnam, const unsigned char *mode, Wndw *wn)
{
FILE *ff;

   ff = cfopen(fnam, mode, wn);
// if(ff != NULL) csetvbuf();

return(ff);
}


int File::cfpurge(void)
{
int rc;

   if(fp)
   {
      rc=0;
      if(!(fwfl&& (conwn!=NULL)))
      {
         rc = fclose(fp);
#if Compiler != Mingw // nëra unlink()
         if(fwfl) rc |= unlink((const char *)tmpfn);
#endif
      }
   }
   else rc=EOF;

  cfclr();

return(rc);
}


int File::cvfpurge()
{
int ii;
unsigned char *vpnt;

   vpnt = vbufp;
   ii = cfpurge();
   if(vpnt!=NULL) cfree(vpnt);

return(ii);
}


void File::cfstat(const unsigned char *mode, Wndw * /* wn */)
{
unsigned char buf[MAXFILE];
unsigned char name[MAXFILE];
// struct stat st;

   strcpy(buf, mode);
   strlwr(buf);
   fwfl = (strchr(buf, 'w') != NULL);
   TvFnameSplit(buf, buf, name, buf, fn);
   strlwr(name);
   devfl = False;
   conwn = NULL;

// if(stat(name, &st) == 0)
// {
//    fil->devfl = (st.st_dev < 0);
//    if(fil->devfl != False)
//    {
//       strcpy(fil->fn, name);
// /*    if(st.st_size > 112) fil->conwn = wn; */
//    }
//    if(strcmp(name, "con") == 0) conwn = wn;
// }

}


int File::cfseek(long offset)
{
#if FALSE
long ll, mm;
int retf;

   retf = (fp == NULL);
   if(retf) cfclr();
   if(!retf)
   {
//    fp->flags &= ~_F_EOF;
      retf = ((offset < 0) || (offset >= filelen));
//    if(retf) fp->flags |= _F_EOF;
   }
   if(!retf)
   {
/*    ll = ftell(fp); */
      ll = filpnt;
      ll -= /* (char chuge *) */ (fp->curp) - /* (char chuge *) */ (fp->buffer);
      mm = filelen-ll; if(mm > fp->bsize) mm=fp->bsize;
      if(!((fp->flags)&_F_BIN))
      {
         retf |= fseek(fp,offset,SEEK_SET);
         buffl = False;
      }
      else if((offset<ll)||(offset>=ll+mm)||(!buffl)){
      ll = offset-fp->bsize/2; if(ll<0l) ll=0l;
      retf |= fseek(fp,ll,SEEK_SET);
      retf |= (fgetc(fp)==EOF);
      buffl = True;
      mm = filelen-ll; if(mm>fp->bsize) mm=fp->bsize;
   }
   if(buffl)
   {
/*    (char chuge *) */(fp->curp)=
      fp->buffer+(short /* size_t */)(offset-ll);
      fp->level=(short)(
   /* (char chuge *) */(/* (char chuge *) */fp->buffer+
      (short /* size_t */)mm) - /* (char chuge *) */fp->curp);
   /* if((fp->flags)&_F_OUT) fp->level=-fp->level; */
      fp->flags&=~(_F_EOF|_F_ERR);
   }
   filpnt = offset;
   }

return(retf);
#endif
// return(fsetpos(fp, &offset));
// return(lseek(fileno(fp), offset, SEEK_SET) < 0l);
return(fseek(fp, offset, SEEK_SET) != 0);
}


int File::cwfseek(long offset)
{
int retf;

   retf = (fp == NULL);
   if(!retf)
   {
      retf |= fseek(fp, offset, SEEK_SET);
      filpnt = offset;
      buffl = False;
   }
   else cfclr();

return(retf);
}


int File::cfgetc(void)
{
int rc;

   rc=EOF;

   if(fp!=NULL)
   {
      rc = fgetc(fp);
      filpnt++;
   }
   else cfclr();

return(rc);
}


unsigned char *File::cfgetss(unsigned char *buf, int maxnum)
{  /* ivedimas; '\n' neiveda  */
unsigned char chuge *pnt, chuge *retp;
unsigned char ch;

   pnt=buf;
   do
   {
      ch = cfgetc();
      if((!cfeof()) && (ch != (unsigned char)EOF) && (ch != Lf) && (ch != Cr) && (PtDiff(pnt, buf) < maxnum - 1))
      {
         *pnt = ch;
         pnt = PtInc(pnt);
      }

   } while((!cfeof()) && (ch != (unsigned char)EOF) && (ch != Lf));
   *pnt = Nul;

   if(ch == Cr) ch = cfgetc();

   retp=buf;
   if(cfeof() || (ch == (unsigned char)EOF)) retp = NULL;

return(retp);
}


// -----------------------------------------------
HRESULT KpInStream::GetWord(KpString *pWordBuf, const unsigned char *lpszDelims, unsigned char *pcDelim)
{
HRESULT retc=S_OK;
char chs;
unsigned char ch;
bool found = False;

   if(((pWordBuf == NULL) || (lpszDelims == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   found = False;
   while((!found) && SUCCEEDED(retc))
   {
      get(chs);
      ch = chs;
      if(fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if(TvStrChr(lpszDelims, ch))
      {
         found = True;
         if(pcDelim) *pcDelim = ch;
         break;
      }

      if((!found) && SUCCEEDED(retc)) *pWordBuf += ch;

   } // while((!found) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------------------
int CountFileLines(const unsigned char *lpszFileName)
{
HRESULT retc = S_OK;
int cnt = 0;
fstream in_file;
static unsigned char str_buf[KP_MAX_FILE_LIN_LEN+1];

   KP_ASSERT(lpszFileName, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszFileName, ios_base::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, lpszFileName, True);
   }

   if(SUCCEEDED(retc))
   {
      cnt = 0;
      do
      {
         in_file.getline((char *)str_buf, KP_MAX_FILE_LIN_LEN);

         if(in_file.eof()) retc = KP_E_EOF;
         KP_ASSERT(!in_file.fail(), KP_E_FERROR, null, True);
         if(SUCCEEDED(retc)) cnt++;

      } while(SUCCEEDED(retc));

      if(retc == KP_E_EOF) retc = S_OK;

      in_file.close();

   } // if(SUCCEEDED(retc)) // KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, lpszFileName, True);

return(cnt);
}


// -----------------------------------------------
HRESULT ReadStrArr(const unsigned char *lpszFileName, unsigned char **plpszStrContents, int *piArrSize, const unsigned char *lpszPrefix)
{
HRESULT retc = S_OK;
int cnt = 0;
fstream in_file;
static unsigned char str_buf[KP_MAX_FILE_LIN_LEN+1];

   KP_ASSERT(lpszFileName, E_INVALIDARG, null, True);
   KP_ASSERT(plpszStrContents, E_INVALIDARG, null, True);
   KP_ASSERT(piArrSize, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPrefix, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszFileName, ios_base::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, lpszFileName, True);
   }

   if(SUCCEEDED(retc))
   {
      cnt = 0;
      while((cnt < *piArrSize) && SUCCEEDED(retc))
      {
         in_file.getline((char *)str_buf, KP_MAX_FILE_LIN_LEN);

         KP_ASSERT(plpszStrContents[cnt] == NULL, KP_E_DOUBLE_CALL, null, False);
         KP_NEWA(plpszStrContents[cnt], unsigned char, strlen(lpszPrefix) + strlen(str_buf) + 1);
         if(SUCCEEDED(retc))
         {
            strcpy(plpszStrContents[cnt], lpszPrefix);
            strcat(plpszStrContents[cnt], str_buf);
         }

         if(SUCCEEDED(retc)) if(in_file.eof()) retc = KP_E_EOF;
         KP_ASSERT(!in_file.fail(), KP_E_FERROR, null, True);
         if(SUCCEEDED(retc)) cnt++;
      }

      if(SUCCEEDED(retc)) if(cnt >= *piArrSize) retc = KP_E_BUFFER_OVERFLOW;

      if(retc == KP_E_EOF) retc = S_OK;

      KP_ASSERT(cnt > *piArrSize, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) *piArrSize = cnt;

      in_file.close();

   } // if(SUCCEEDED(retc)) // KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, lpszFileName, True);

return(cnt);
}


HRESULT KpDirFile(const unsigned char *lpszInitPath, const unsigned char *lpszSrcPath, fstream *pLogFile, bool bOutMsg, bool bEncode)
{
HRESULT retc = S_OK;
unsigned char *src_fmask = NULL;
unsigned char *src_file = NULL;
unsigned char *src_file_enc = NULL;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
long ll;

   KP_ASSERT(lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(pLogFile, E_INVALIDARG, null, True);

// -------------------------------
   KP_NEWA(src_fmask, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(src_file, unsigned char, KP_MAX_FNAME_LEN + 100);
   KP_NEWA(src_file_enc, unsigned char, KP_MAX_FNAME_LEN + 100);

// -------------------------------
   KP_ASSERTE(strlen(lpszSrcPath) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, bOutMsg);
   if(SUCCEEDED(retc))
   {
      strcpy(src_fmask, lpszSrcPath);
      strcat(src_fmask, "\\*.*");
   }

// --------------- atidarom
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)src_fmask, &file_data);
   if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      retw = GetLastError();
      KP_ASSERTE((retw == ERROR_FILE_NOT_FOUND) || (retw == ERROR_PATH_NOT_FOUND) || (retw == ERROR_NO_MORE_FILES), KP_E_SYSTEM_ERROR, retw, bOutMsg);
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
   {
      if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
      {
         strcpy(src_file, lpszSrcPath);
         strcat(src_file, "\\");
         strcat(src_file, file_data.cFileName);

         strcpy(src_file_enc, src_file);
         if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(src_file_enc, strlen(src_file));

// ----------- iðvedam
         if(strstr(src_file, lpszInitPath) == src_file)
         {
            ll = strlen(lpszInitPath);
            if(src_file[ll] == '\\') pLogFile->write((const char *)(src_file_enc + ll + 1), strlen(src_file + ll + 1));
            else pLogFile->write((const char *)src_file_enc, strlen(src_file));
         }
         else pLogFile->write((const char *)src_file_enc, strlen(src_file));

unsigned char str_buf[100];
int str_buf_len;
         if((file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
            if(SUCCEEDED(KpGetFileSizeName(src_file, &ll, bOutMsg)))
            {
               sprintf((char *)str_buf, "\t%ld", ll);
               str_buf_len = strlen(str_buf);
               if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
               pLogFile->write((const char *)str_buf, str_buf_len);
            }

         strcpy(str_buf, "\n");
         if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, 1);
         pLogFile->write((const char *)str_buf, 1);

         KP_ASSERTE(!pLogFile->fail(), KP_E_FERROR, null, bOutMsg);

// ---------- pakatalogis - listinam rekursiðkai
         if(SUCCEEDED(retc))
            if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
               retc = KpDirFile(lpszInitPath, src_file, pLogFile, bOutMsg, bEncode);

      } // if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))

// ---------------- kitas failas
      retw = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retw = GetLastError();
            KP_ASSERTE(retw == ERROR_NO_MORE_FILES, KP_E_SYSTEM_ERROR, retw, bOutMsg);
         }

   } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// --------------- uþdarom
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      KP_ASSERT(FindClose(enumeration), KP_E_SYSTEM_ERROR, retw, False);
      enumeration = INVALID_HANDLE_VALUE;
   }

   KP_DELETEA(src_fmask);
   KP_DELETEA(src_file);
   KP_DELETEA(src_file_enc);

return(retc);
}


HRESULT KpDir(const unsigned char *lpszSrcPath, fstream *pLogFile, bool bOutMsg, bool bEncode)
{
return(KpDirFile(lpszSrcPath, lpszSrcPath, pLogFile, bOutMsg, bEncode));
}


HRESULT KpDir(const unsigned char *lpszSrcPath, const unsigned char *lpszLogFile, bool bOutMsg, bool bEncode)
{
HRESULT retc = S_OK;
fstream out_file;
static unsigned char src_path[KP_MAX_FNAME_LEN + 1];
int ll;

   KP_ASSERT(lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszLogFile, E_INVALIDARG, null, True);

// -------------------------------
   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)lpszLogFile, ios_base::out | ios_base::app);
      KP_ASSERTE(!out_file.fail(), KP_E_DIR_ERROR, lpszLogFile, bOutMsg);
   }

   KP_ASSERTE(GetFullPathName((const char *)lpszSrcPath, KP_MAX_FNAME_LEN, (char *)src_path, NULL),
      KP_E_SYSTEM_ERROR, GetLastError(), bOutMsg);
   if(SUCCEEDED(retc))
   {
      ll = strlen(src_path);
      if(ll > 0) if(src_path[ll - 1] == '\\') src_path[ll - 1] = Nul;
   }

   if(SUCCEEDED(retc)) retc = KpDir(src_path, &out_file, bOutMsg, bEncode);

   if(SUCCEEDED(retc)) out_file.close();

return(retc);
}
