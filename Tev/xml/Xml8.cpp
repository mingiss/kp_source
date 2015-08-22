// ==================================================
// xml8.cpp
// XML low level 8-bit file


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif

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
#include "kpctype.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"


// ================================================== methods of TvXml8File_tag
// --------------------------------------------------
TvXml8File::TvXml8File
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
XL_FileTypes uiFileType,
bool bMapToPrivate
)
{
   m_lhOpenResult=Constructor(lpszFileName, lpszMode, uiFileType, bMapToPrivate);

   iCharPos=0;
   lCharNum=0L;

   lpfFilePtr = NULL;

   m_iCodeTable=1;
   m_iEncMode=UC_PlainText;

// Windows-1257 for output files
// if(SUCCEEDED(m_lhOpenResult))
//    if(TvStrChrArr(m_lpszFMode, (const unsigned char *)"wWaA")!=NULL) m_iCodeTable=71;

   if(SUCCEEDED(m_lhOpenResult))
   {
      lpfFilePtr = fopen((const char *)m_lpszFName, (const char *)m_lpszFMode);
      if(lpfFilePtr==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }
}


// --------------------------------------------------
HRESULT TvXml8File::GetRawFilePtr(FILE **lppFilePtrPtr, bool /* bCheckError */)
{
HRESULT retc=S_OK;

   *lppFilePtrPtr=NULL;

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      *lppFilePtrPtr=lpfFilePtr;

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(lpfFilePtr!=NULL)
   {
      if(fclose(lpfFilePtr)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
      lpfFilePtr=NULL;
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::Reset(void)
{
HRESULT retc=S_OK;

   retc=Fseek(0, SEEK_SET);

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::Fseek(long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(lpfFilePtr!=NULL)
   {
      if(fseek(lpfFilePtr, lOffset, iOrigin)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }
   else
   {
//    if(!bCheckFileExist) retc=KP_E_NO_FILE;
//    else
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::VirtDestruct(void)
{
HRESULT retc=S_OK;

   retc=CloseFile(False);

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::PutChar(KpChar iOutch, bool bCheckErrors)
{
HRESULT retc=S_OK;
unsigned char ch_out;

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      iCharPos++;
      if(TvStrChr(lpszEols, iOutch)!=NULL) iCharPos=0;

      if(iOutch<KPT_FirstKptChar)
      {
// #if OsGr==Unix
         if((iOutch==C_Lf) && (!m_bBinFlg)) // '\n'
//          if((strchr((const char *)m_lpszFMode, 'b')!=NULL) || (strchr((const char *)m_lpszFMode, 'B')!=NULL))
            {
//             putc('\r', lpfFilePtr); // aklz_h2e - failas atidarytas su fopen() kaip tekstinis, Cr jau prideda sistema automatiškai
               lCharNum++;
            }
// #endif
         putc(iOutch, lpfFilePtr); lCharNum++;
      }
      else
      {
         ch_out=(unsigned char)iOutch;
         if((iOutch>=KPT_Ctbsiz) || (m_iCodeTable!=0))
         {
            retc=KptCharDecode(&ch_out, iOutch, m_iCodeTable);
            if(((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) && bCheckErrors)
            {
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, iOutch);
               ch_out=C_Quest;
            }
         }

         if(SUCCEEDED(retc))
         {
            putc(ch_out, lpfFilePtr);
            lCharNum++;
         }
      } // else if(iOutch<KPT_FirstKptChar)

// output errors
      if((ferror(lpfFilePtr) || feof(lpfFilePtr)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *piCharPos=iCharPos;

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::GetCharNum(long *plCharNum)
{
HRESULT retc=S_OK;

   if(plCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *plCharNum=lCharNum;

return(retc);
}


// --------------------------------------------------
HRESULT TvXml8File::GetChar(KpChar *piInch)
{
HRESULT retc=S_OK;
unsigned char in_ch;
unsigned char out_str[30];

   if((piInch==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piInch=C_Nul;

      in_ch=getc(lpfFilePtr);

      if(ferror(lpfFilePtr))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         if(feof(lpfFilePtr)) retc=KP_E_EOF;

      if(SUCCEEDED(retc))
      {

//if((in_ch==155) && (m_iCodeTable==80))
//in_ch=155;
if(in_ch=='@')
in_ch='@';

// printf("%c\n", in_ch);

// KP_TRACE_2("TvXml8File::GetChar: m_iEncMode:%d m_iCodeTable:%d", m_iEncMode, m_iCodeTable);

         retc=KptCharEncode(piInch, in_ch, m_iCodeTable);
         if(retc==KP_E_UNKN_CHR)
         {
            sprintf((char *)out_str, "%s: %x[%d]", m_lpszFName, in_ch, m_iCodeTable);
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, True, __FILE__, __LINE__, 0L);
//          retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, False, __FILE__, __LINE__, 0L);
//          *piInch = '@';
         }
      }
   }

return(retc);
}


// ================================================== low level file creation procedure
HRESULT CreateNew8File
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool m_bMapToPrivate
)
{
HRESULT retc=S_OK;

   KP_ASSERT(lppFileObjPtrPtr !=NULL, E_INVALIDARG, null, True);

   KP_NEWO(*lppFileObjPtrPtr, TvXml8File(lpszFNam, lpszFMod, uiFTyp, m_bMapToPrivate));

// if(SUCCEEDED(retc)) retc = (*lppFileObjPtrPtr)->SetEncoding(UC_PlainText, 0);

return(retc);
}
