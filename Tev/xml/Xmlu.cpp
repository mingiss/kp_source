// ==================================================
// xmlu.cpp
// XML low level file in Unicode format


// ================================================== definitions, static fields
#include "envir.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <iostream>
#include <fstream>
#if Compiler != Watcom
#include <sstream>
#endif
#if Compiler==Msvc60
//#include <stdafx.h>
#endif
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
#include "kpsort.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xml8.h"
#include "xmlb.h"
#include "xmlu.h"

#if Compiler != Watcom
using namespace std;
#endif


// ================================================== methods of TvXmlUniFile_tag
// --------------------------------------------------
TvXmlUniFile::TvXmlUniFile
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
XL_FileTypes uiFileType,
XmlfLowLevelCrFunPtr CreateLowLevelObj,
bool bMapToPrivate,
UC_Modes iEncMode
)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   retc = Constructor(lpszFileName, lpszMode, uiFileType, bMapToPrivate);

   lpfUniFilePtr=NULL;

   if(SUCCEEDED(retc))
   {
      if(uiFileType==XL_FT_DataFile) m_iEncMode=iEncMode; // UC_UTF_8;
      else
      {
         if(
            (TvStrChr(m_lpszFMode, C_b)!=NULL) || // 'b'
            (TvStrChr(m_lpszFMode, C_B)!=NULL) // 'B'
           )
            m_iEncMode=UC_Binary;
         else
            m_iEncMode=UC_PlainText;
      }

      KP_NEWO(lpfUniFilePtr, UcFile(m_lpszFName, m_iEncMode, m_lpszFMode, CreateLowLevelObj, bMapToPrivate));
   }
#ifdef KPTTUCF_XMLF_FILE
UC_Modes enc_mode;
int ctbl;
   if(SUCCEEDED(retc)) if(lpfUniFilePtr->lpFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=lpfUniFilePtr->lpFile->GetEncoding(&enc_mode, &ctbl);
   if(SUCCEEDED(retc)) retc=lpfUniFilePtr->lpFile->SetEncoding(enc_mode, TV_CTBL_TRANSPARENT);
#endif

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// --------------------------------------------------
HRESULT TvXmlUniFile::GetRawFilePtr(FILE **lppFilePtrPtr, bool /* bCheckError */)
{
HRESULT retc=S_OK;

   *lppFilePtrPtr=NULL;

   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=lpfUniFilePtr->GetRawFilePtr(lppFilePtrPtr);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::Reset(void)
{
HRESULT retc=S_OK;

   retc=Fseek(0, SEEK_SET);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::Fseek(long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpfUniFilePtr->Fseek(lOffset, iOrigin);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;

   if(lpfUniFilePtr!=NULL)
   {
      retc0=lpfUniFilePtr->CloseFile(True);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(lpfUniFilePtr);
   }
   else
   {
      retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::VirtDestruct(void)
{
HRESULT retc=S_OK;

   retc=CloseFile(False);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::PutChar(KpChar iOutch, bool bCheckErrors)
{
HRESULT retc=S_OK;
KpChar kp_ch_out;
unsigned char ch_out;

#if FALSE
if(iOutch == C_NBSP)
{
unsigned char str_buf[100];
sprintf((char *)str_buf, "<%d>", m_iCodeTable);
lpfUniFilePtr->PutStrProc(str_buf, m_bMapToPrivate);
}
#endif

   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   kp_ch_out=iOutch;
   if((iOutch >= KPT_Ctbsiz) && (m_iCodeTable > 0))
   {

#if FALSE
stringstream str_stream;
str_stream << "TvXmlUniFile::PutChar: m_iCodeTable: " << m_iCodeTable;
KpMsgOut(KpString(str_stream.str()), IDI_ASTERISK, KP_MB_TESTI);
#endif

      retc = KptCharDecode(&ch_out, iOutch, m_iCodeTable);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
      {
         ch_out=C_Quest;
         retc=KpErrorProc.OutputErrorMessage(retc, null, bCheckErrors, __FILE__, __LINE__, 0L);
      }
      kp_ch_out = ch_out;
   }

   if(SUCCEEDED(retc))
      retc=lpfUniFilePtr->PutCharProc(kp_ch_out, bCheckErrors, m_bMapToPrivate);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=lpfUniFilePtr->GetCharPos(piCharPos);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::GetCharNum(long *plCharNum)
{
HRESULT retc=S_OK;

   if(plCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=lpfUniFilePtr->GetCharNum(plCharNum);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlUniFile::GetChar(KpChar *piInch)
{
HRESULT retc=S_OK;

   *piInch=C_Nul;

   if(lpfUniFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((piInch==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piInch=C_Nul;

      retc=lpfUniFilePtr->GetCharProc(piInch);
   }

return(retc);
}


// ================================================== low level file creation procedure
HRESULT CreateNewUniFile
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
)
{
HRESULT retc=S_OK;

   if(lppFileObjPtrPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWO(*lppFileObjPtrPtr, TvXmlUniFile(lpszFNam, lpszFMod, uiFTyp, CreateNew8File, bMapToPrivate, UC_UTF_8));

   if(SUCCEEDED(retc)) retc = (*lppFileObjPtrPtr)->SetEncoding(UC_UTF_8, 0);

return(retc);
}


HRESULT CreateNewUniBFile
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
)
{
HRESULT retc=S_OK;

   if(lppFileObjPtrPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWO(*lppFileObjPtrPtr, TvXmlUniFile(lpszFNam, lpszFMod, uiFTyp, CreateNewBFile, bMapToPrivate, UC_UTF_8));

   if(SUCCEEDED(retc)) retc = (*lppFileObjPtrPtr)->SetEncoding(UC_UTF_8, 0);

return(retc);
}


HRESULT CreateNewUni16BFile
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
)
{
HRESULT retc = S_OK;

   if(lppFileObjPtrPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWO(*lppFileObjPtrPtr, TvXmlUniFile(lpszFNam, lpszFMod, uiFTyp, CreateNewBFile, bMapToPrivate, UC_UTF_16));

   if(SUCCEEDED(retc)) retc = (*lppFileObjPtrPtr)->SetEncoding(UC_UTF_16, 0);

return(retc);
}
