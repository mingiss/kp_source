// ==================================================
// xmlb.cpp
// XML low level 8-bit RAM file


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdio.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <iostream>
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
#include "xmlb.h"


// ================================================== methods of TvXmlBFile_tag
// --------------------------------------------------
TvXmlBFile::TvXmlBFile
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
XL_FileTypes uiFileType,
bool bMapToPrivate
)
{
int ii;

   m_lhOpenResult=S_OK;

   m_iCharPos=0;
   m_lCharNum=0L;

   m_lpszBufPtr=NULL;
   m_lBufLen=0L;
   ii = sscanf((const char *)lpszFileName, "%x %x", &m_lpszBufPtr, &m_lBufLen);
   if((ii != 2) || (m_lpszBufPtr==0L) || (m_lBufLen==0L))
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFileName, True, __FILE__, __LINE__, 0L);

#if FALSE
fstream out_file("xmlb.txt", ios::out | ios::binary);
out_file << lpszFileName << endl;
out_file << hex << (int)m_lpszBufPtr << (int)m_lBufLen << endl;
out_file.write((const char *)m_lpszBufPtr, m_lBufLen);
out_file.close();
#endif

   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=Constructor(lpszFileName, lpszMode, uiFileType, bMapToPrivate);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=Reset();

   m_iCodeTable = (strchr(lpszMode, 'b') != null)?TV_CTBL_TRANSPARENT:1;
   m_iEncMode = UC_PlainText;

// if(SUCCEEDED(m_lhOpenResult))
//    if(TvStrChrArr(m_lpszFMode, (const unsigned char *)"wWaA")==NULL)
//       m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT TvXmlBFile::GetRawFilePtr(FILE **lppFilePtrPtr, bool bCheckError)
{
HRESULT retc=S_OK;

   if((lppFilePtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      if(bCheckError)
         retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

// if(SUCCEEDED(retc))
// {
//    retc=E_NOTIMPL;
//    if(bCheckError)
//       retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
// }

   if(SUCCEEDED(retc)) *lppFilePtrPtr=NULL;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::Reset(void)
{
HRESULT retc=S_OK;

   m_lCharNum=0L;
   if((m_lpszBufPtr!=NULL) && (m_lBufLen > 0))
   {
      if((strchr((const char *)m_lpszFMode, 'w')!=NULL) || (strchr((const char *)m_lpszFMode, 'W')!=NULL))
      {
//       m_lpszBufPtr[0]=Nul;
         memset(m_lpszBufPtr, Nul, m_lBufLen);
      }
   }
   else
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::Fseek(long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) switch(iOrigin)
   {
   case SEEK_CUR: m_lCharNum+=lOffset; break;
   case SEEK_END: m_lCharNum=m_lBufLen-lOffset; break;
   case SEEK_SET: m_lCharNum=lOffset; break;
   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      break;
   }

   if(((m_lCharNum<0) || (m_lCharNum>=m_lBufLen)) && SUCCEEDED(retc))
   {
      m_lBufLen=0L;
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::CloseFile(bool /* bCheckFileExist */)
{
HRESULT retc=S_OK;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::VirtDestruct(void)
{
HRESULT retc=S_OK;

   retc=CloseFile(False);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::PutChar(KpChar iOutch, bool bCheckErrors)
{
HRESULT retc=S_OK;
unsigned char ch_out;

   if((m_lpszBufPtr==0L) || (m_lBufLen==0L))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_iCharPos++;
      if(TvStrChr(lpszEols, iOutch)!=NULL) m_iCharPos=0;

      if(iOutch<KPT_FirstKptChar)
      {
         if((iOutch==C_Lf) && (!m_bBinFlg))
         {
#if FALSE
char str_buf[100];
sprintf(str_buf, "%d", m_iEncMode);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
            if((m_iEncMode == UC_UTF_16_Big_Endian) && SUCCEEDED(retc)) retc=PutChar(0, bCheckErrors);
            if(SUCCEEDED(retc)) retc=PutChar(C_Cr, bCheckErrors); // '\n' '\r'
            if((m_iEncMode == UC_UTF_16) && SUCCEEDED(retc)) retc=PutChar(0, bCheckErrors);
         }
         if(SUCCEEDED(retc))
         {
            if(m_lCharNum < m_lBufLen-1)
            {
               m_lpszBufPtr[m_lCharNum++]=(unsigned char)iOutch;
               m_lpszBufPtr[m_lCharNum]=Nul;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }
      }
      else
      {
         ch_out=(unsigned char)iOutch;
         if((iOutch>=KPT_Ctbsiz) || (m_iCodeTable!=0))
            retc=KptCharDecode(&ch_out, iOutch, m_iCodeTable);
         if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
         {
            if(bCheckErrors) retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
//          else retc=S_OK;
         }

         if(SUCCEEDED(retc))
         {
            if(m_lCharNum < m_lBufLen-1)
            {
               m_lpszBufPtr[m_lCharNum++]=ch_out;
               m_lpszBufPtr[m_lCharNum]=Nul;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

      } // else if(iOutch<KPT_FirstKptChar)

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *piCharPos=m_iCharPos;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::GetCharNum(long *plCharNum)
{
HRESULT retc=S_OK;

   if(plCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *plCharNum=m_lCharNum;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlBFile::GetChar(KpChar *piInch)
{
HRESULT retc=S_OK;
unsigned char in_ch;

// if(SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);

   if((piInch==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(((m_lpszBufPtr==0L) || (m_lBufLen==0L)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(m_lCharNum >= m_lBufLen) retc = KP_E_EOF;

   if(SUCCEEDED(retc))
   {
      in_ch=m_lpszBufPtr[m_lCharNum++];

      m_iCharPos++;
      if(TvStrChr(lpszEols, (KpChar)in_ch) != NULL) m_iCharPos = 0;

      retc = KptCharEncode(piInch, in_ch, m_iCodeTable);
      if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
      {
//       if(bCheckErrors)
            retc = KpErrorProc.OutputErrorMessage(retc, null, True /* False */, __FILE__, __LINE__, in_ch);
PutLogMessage_("TvXmlBFile::GetChar: %d", m_iCodeTable);
//       else retc=S_OK;
//       *piInch = '?';
      }

   } // if(SUCCEEDED(retc))

return(retc);
}


// ================================================== low level file creation procedure
HRESULT CreateNewBFile
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool m_bMapToPrivate
)
{
HRESULT retc=S_OK;

   if(lppFileObjPtrPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWO(*lppFileObjPtrPtr, TvXmlBFile(lpszFNam, lpszFMod, uiFTyp, m_bMapToPrivate));

// char str_buf[200];
// sprintf(str_buf, "%lx %lx %s", lppFileObjPtrPtr, *lppFileObjPtrPtr, lpszFNam);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI); // !!!!

// if(SUCCEEDED(retc)) retc = (*lppFileObjPtrPtr)->SetEncoding(UC_PlainText, 0);

return(retc);
}
