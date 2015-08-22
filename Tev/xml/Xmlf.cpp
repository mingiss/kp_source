// ==================================================
// xmlf.cpp
// XML file (main or index)
// second lowest level
//

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
// #include <iostream>
#include <fstream>
#if Compiler != Watcom
#include <sstream>
#endif
#if OsGr==MSWin
#include <windows.h>
#include <time.h>
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
#include "kpsort.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlg.h"
#include "htmt.h"

// ================================================== static fields
const unsigned char *plpszaDefTagNames[] = {NULL};

// ================================================== KpFile
HRESULT KpFile::Constructor
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
XL_FileTypes /* uiFileType */,
bool bMapToPrivate
)
{
   m_lhOpenResult=S_OK;

   m_iCodeTable=0;
   m_iEncMode=UC_No_Mode;

   m_lpszFName[0]=Nul;
   m_lpszFMode[0]=Nul;
   m_bBinFlg = False;

   m_bMapToPrivate=bMapToPrivate;

   if(SUCCEEDED(m_lhOpenResult))
   {
      if(strlen((const char *)lpszFileName)<KP_MAX_FNAME_LEN)
         strcpy((char *)m_lpszFName, (const char *)lpszFileName);
      else m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFileName, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(m_lhOpenResult))
   {
      if(strlen((const char *)lpszMode)<TV_TAG_LEN)
         strcpy((char *)m_lpszFMode, (const char *)lpszMode);
      else m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszMode, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(m_lhOpenResult))
      m_bBinFlg = (strchr(lpszMode, C_B) || strchr(lpszMode, C_b)); // 'b' 'B'

return(S_OK);
}


// --------------------------------------------------
HRESULT KpFile::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT KpFile::GetEncoding(UC_Modes *piEncodingMode, int *piCtbl)
{
HRESULT retc=S_OK;

   if(piEncodingMode!=NULL) *piEncodingMode=m_iEncMode;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(piCtbl!=NULL) *piCtbl=m_iCodeTable;
   else
      if(SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT KpFile::SetEncoding(UC_Modes iEncodingMode, int iCtbl)
{
HRESULT retc=S_OK;

// test and set enc_mode
   if((iEncodingMode<0) || (iEncodingMode>=UC_Num_Of_Modes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((iEncodingMode!=UC_No_Mode) && SUCCEEDED(retc))
   {
      if(
         (
            ((m_iEncMode<UC_Unicode16) && (iEncodingMode>=UC_Unicode16)) ||
            ((m_iEncMode<UC_Unicode) && (iEncodingMode>=UC_Unicode)) ||
            ((iEncodingMode<UC_Unicode16) && (m_iEncMode>=UC_Unicode16)) ||
            ((iEncodingMode<UC_Unicode) && (m_iEncMode>=UC_Unicode)) ||
            ((m_iEncMode<UC_Unicode) && (iEncodingMode!=m_iEncMode))
         ) &&
         (m_iEncMode!=UC_No_Mode)
        )
      {
char str_buf[100];
         sprintf(str_buf, "%d %d %d", iEncodingMode, iCtbl, m_iEncMode);
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, str_buf, True, __FILE__, __LINE__, 0L);
      }
      if((iEncodingMode==UC_UTF_7) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
// zr. komentara funkcijoje TvXmlFile::SetEncoding()
//    if((iCtbl!=0) && (iCtbl!=1) && (iEncodingMode!=UC_PlainText) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      if((iEncodingMode<UC_Unicode16) && SUCCEEDED(retc)) m_iEncMode=iEncodingMode;
   }

// set m_iCodeTable
   if(((iCtbl<0) || (iCtbl>=KPT_Ctnum)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(/* (iCtbl!=0) && */ SUCCEEDED(retc)) m_iCodeTable=iCtbl;

return(retc);
}


// --------------------------------------------------
HRESULT KpFile::PutStr(const unsigned char *lpszOutStr, bool bCheckErrors)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   pnts=lpszOutStr;

   if(pnts!=NULL)
      while((*pnts) && SUCCEEDED(retc))
         retc=PutChar((KpChar)(*pnts++), bCheckErrors);

return(retc);
}


// --------------------------------------------------
HRESULT KpFile::PutStrCtbl(const unsigned char *lpszOutStr, bool bCheckErrors, int iCtbl)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
KpChar kpt_char;

   pnts=lpszOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc))
   {
      retc=KptCharEncode(&kpt_char, (*pnts++), iCtbl);
      if(SUCCEEDED(retc)) retc=PutChar(kpt_char, bCheckErrors);
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpFile::PutKpStr(const KpChar *lpaizOutStr, bool bCheckErrors)
{
HRESULT retc=S_OK;
const KpChar *pnts;

   pnts=lpaizOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc)) retc=PutChar(*pnts++, bCheckErrors);

return(retc);
}


// --------------------------------------------------
HRESULT KpFile::PutKpStr(const KpChar *lpaizOutStr, bool bCheckErrors, int iCTbl)
{
HRESULT retc=S_OK;
UC_Modes enc_mode;
int ctbl_sav;
const KpChar *pnts;

   retc=GetEncoding(&enc_mode, &ctbl_sav);
   if(SUCCEEDED(retc)) retc=SetEncoding(enc_mode, iCTbl);

   pnts=lpaizOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc)) retc=PutChar(*pnts++, bCheckErrors);

   if(SUCCEEDED(retc)) retc=SetEncoding(enc_mode, ctbl_sav);

return(retc);
}


// ================================================== methods of TvXmlFile
// ================================================== init
// --------------------------------------------------
TvXmlFile::TvXmlFile
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
XL_FileTypes uiFileType,
HRESULT (*CreateLowLevelObj)
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
),
const unsigned char * const *plpszaXmlSpCharTags,
int iIndexWidth,
KpChar iFirstTag,
const unsigned char * const *plpszaTags,
bool bExternalTagsArray,
XmlVersions iVersion,
const int *piaCtbls,
bool bMultiLine,
bool bMapToPrivate
)
{
HRESULT retc = S_OK;
const unsigned char * const *pntss = NULL;
UC_Modes enc_mode;
int ii, ll;

   m_lhOpenResult = S_OK;

   m_lpLowLevelFile=NULL;
   m_lpRawFile=NULL;

   m_lpTagStack = NULL;

   m_bMultiLine = bMultiLine;

   m_plpszaXmlSpecCharTags = NULL;
// if((plpszaXmlSpCharTags == NULL) && SUCCEEDED(retc))
//    retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
// if(SUCCEEDED(retc))
      m_plpszaXmlSpecCharTags = plpszaXmlSpCharTags;

// -----------------
   m_iLastDictTagCurrent = m_iLastDictTagOrig = m_iFirstDictTag = C_Nul;
   m_lpszaTagNamesBufPtr = m_lpszaTagNamesBuf;
   for(ii = 0; ii < XL_MaxNumOfTags; ii++) m_lpszaTagNamesArray[ii] = null;

   m_iLastDictTagCurrent = m_iLastDictTagOrig = m_iFirstDictTag = iFirstTag;

   m_plpszaTagNamesOrig = plpszaTags;
   if(m_plpszaTagNamesOrig == NULL) m_plpszaTagNamesOrig = plpszaDefTagNames;

   if(bExternalTagsArray) m_lpszaTagNames = m_plpszaTagNamesOrig;
   else
   {
      m_lpszaTagNames = m_lpszaTagNamesArray;

      pntss = m_plpszaTagNamesOrig;
      if(pntss) while((*pntss) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc))
         {
            ii = pntss - m_plpszaTagNamesOrig;
            if(ii >= XL_MaxNumOfTags)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            ll = strlen(*pntss);
            if(ll + 1 >= TV_XL_TAG_BUF_SIZE - (m_lpszaTagNamesBufPtr - m_lpszaTagNamesBuf))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            strcpy(m_lpszaTagNamesBufPtr, *pntss);
            m_lpszaTagNamesArray[ii] = m_lpszaTagNamesBufPtr;
            m_lpszaTagNamesBufPtr += ll + 1;
         }

         pntss++;
      }

   } // else // if(bExternalTagsArray)

   if(SUCCEEDED(retc)) GetLastTag();
   if(SUCCEEDED(retc)) m_iLastDictTagOrig = m_iLastDictTagCurrent;

   m_piaCodeTablesOrig = piaCtbls;
// if((m_piaCodeTablesOrig == NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   m_iDefCodeTable=0;

// -----------------
   m_iXmlVers=iVersion;

   m_iPathMode = XL_RelativePath;
   m_iScale = 10;

   m_lpszFName[0]=Nul;
   if(strlen((const char *)lpszFileName)<KP_MAX_FNAME_LEN)
      strcpy((char *)m_lpszFName, (const char *)lpszFileName);
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFileName, True, __FILE__, __LINE__, 0L);

// strcpy(m_lpszIndentStr, (const unsigned char *)"\n");
   m_lpszIndentStr[0]=Nul;
   strcpy(m_lpszBaseIndentStr, "   ");

   m_iUnGetCnt=0;

   m_bUnGetChProcCnt=0;
   for(ii=0; ii<TV_XL_UNGET_BUF_SIZ; ii++) m_pUnGetChPars[ii] = NULL;

   m_uiFType = uiFileType;

   m_iIxWdt = iIndexWidth;

   KP_ASSERT(CreateLowLevelObj != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc))
   {
      retc = CreateLowLevelObj(&m_lpLowLevelFile, lpszFileName, lpszMode, uiFileType, bMapToPrivate);
      if(SUCCEEDED(retc))
      {
         KP_ASSERT(m_lpLowLevelFile != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
         {
            retc = m_lpLowLevelFile->GetOpenResult();
            if(FAILED(retc)) KP_DELETE(m_lpLowLevelFile);
         }
      }
   }

   if(SUCCEEDED(retc))
      retc = m_lpLowLevelFile->GetEncoding(&enc_mode, &m_iDefCodeTable);
   if(
      (
         (m_iXmlVers==XM_VERS_SGML_TAGE) ||
         (m_iXmlVers==XM_NO_VERS) // index files
      )&&
      SUCCEEDED(retc)
     )
      retc = m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable=TV_CTBL_TRANSPARENT);

   KP_NEW(m_lpTagStack, TvXmlTagStack(NULL, C_Nul, NULL, 0));

   if(SUCCEEDED(retc))
   {
      retc = m_lpLowLevelFile->GetRawFilePtr(&m_lpRawFile, False);
      if(retc == E_NOTIMPL)
      {
         retc = S_OK;
         m_lpRawFile = NULL;
      }
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// --------------------------------------------------
TvXmlFile::~TvXmlFile()
{
HRESULT retc = S_OK;
TvXmlTagStack *prev_stack_ptr;
KpChar cur_tag;

   for(int ii = 0; ii < m_bUnGetChProcCnt; ii++) KP_DELETE(m_pUnGetChPars[ii]);

   m_bUnGetChProcCnt = 0;

   if(m_lpLowLevelFile != NULL)
   {
      m_lpLowLevelFile->CloseFile(False);
      m_lpLowLevelFile->VirtDestruct();
      KP_DELETE(m_lpLowLevelFile);
   }

   if(m_lpTagStack != NULL)
   {
      m_lpTagStack->GetPrevTagPtr(&prev_stack_ptr);
      m_lpTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr != NULL) || (cur_tag != C_Nul))
         KpErrorProc.OutputErrorMessage(TV_E_OPEN_TAG, null, False, __FILE__, __LINE__, 0L);

      KP_DELETE(m_lpTagStack);
   }
// else
//    KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetOpenResult(void)
{
return(m_lhOpenResult);
}


//====================================
KpChar TvXmlFile::GetLastTag(void)
{
HRESULT retc = S_OK;
const unsigned char * const *pntss;
int ii = 0;

// pntss = m_lpszaTagNames;
   ii = m_iLastDictTagCurrent - m_iFirstDictTag;
   pntss = m_lpszaTagNames + ii; // tagø gali tik daugëti - pradedam nuo paskutinio

   while(*pntss) pntss++;
   ii = pntss - m_lpszaTagNames;
   if(ii >= XL_MaxNumOfTags)
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) m_iLastDictTagCurrent = (KpChar)(m_iFirstDictTag + ii);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
// return(retc);
return(m_iLastDictTagCurrent);
}


bool TvXmlFile::CheckLastTag(KpChar iTag)
{
bool retv = False;

   if(iTag >= m_iLastDictTagCurrent)
      if(iTag >= GetLastTag()) retv = True;

return(retv);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetFileType(XL_FileTypes *puiFileType)
{
HRESULT retc=S_OK;

   if(puiFileType==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *puiFileType=m_uiFType;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetVersion(XmlVersions *piVersion)
{
HRESULT retc=S_OK;

   if(piVersion==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piVersion=m_iXmlVers;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetEncoding(UC_Modes *piEncodingMode, int *piCtbl, int *piDefCtbl)
{
HRESULT retc=S_OK;

   if(piCtbl!=NULL) *piDefCtbl=m_iDefCodeTable;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((m_lpLowLevelFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_lpLowLevelFile->GetEncoding(piEncodingMode, piCtbl);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SetEncoding(UC_Modes iEncodingMode, int iCtbl, int iDefCtbl)
{
HRESULT retc=S_OK;
int cur_ctbl;
UC_Modes cur_enc_mode;

   retc=m_lpLowLevelFile->GetEncoding(&cur_enc_mode, &cur_ctbl);

// test and set iDefCtbl
   if((iDefCtbl!=0) && SUCCEEDED(retc))
   {
      if(
         (
            (
               (m_iDefCodeTable!=0) &&
               (m_iDefCodeTable!=1) &&
               (m_iDefCodeTable!=99) &&
               (m_iDefCodeTable!=iDefCtbl)
            ) // ||
// galima ir unikodiniams failams - m_iDefCodeTable naudojama literaliniu
//    konstantu laikinam saugojimui lpsz stringuose
//    (xmlf.cpp eilute ~946, KptStrDecode(par_val, par_val_i, TvKpStrLen(par_val_i), m_iDefCodeTable) funkcijoje PutCharProc())
//          (
//             (cur_enc_mode!=UC_No_Mode) &&
//             (cur_enc_mode!=UC_PlainText)
//          )
         ) &&
         SUCCEEDED(retc)
        )
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) m_iDefCodeTable=iDefCtbl;
   }

// set iEncodingMode and iCtbl
   cur_ctbl=iCtbl;
   if(cur_ctbl==0) cur_ctbl=m_iDefCodeTable;
   if(SUCCEEDED(retc)) retc=m_lpLowLevelFile->SetEncoding(iEncodingMode, cur_ctbl);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetMultiline(bool *pbMultiLine)
{
HRESULT retc=S_OK;

   if(pbMultiLine==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pbMultiLine=m_bMultiLine;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SetMultiline(bool bMultiLine)
{
   m_bMultiLine=bMultiLine;

return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetCurTag(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if((m_lpTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(piCurTag);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::Reset(void)
{
HRESULT retc=S_OK;

   if((m_lpLowLevelFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_lpLowLevelFile->Reset();

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(m_lpLowLevelFile==NULL)
   {
      retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      retc=m_lpLowLevelFile->CloseFile(bCheckFileExist);

return(retc);
}


// ================================================== text output
// --------------------------------------------------
HRESULT TvXmlFile::PutChar(KpChar iOutch, bool bCheckErrors)
{
HRESULT retc=S_OK;

   if(m_lpLowLevelFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_lpLowLevelFile->PutChar(iOutch, bCheckErrors);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::PutStr(const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   pnts=lpszOutStr;

   if(pnts!=NULL)
      while((*pnts) && SUCCEEDED(retc))
         retc=PutChar((KpChar)(*pnts++), True);

return(retc);
}

// HTM_TG_STYLE
// --------------------------------------------------
unsigned char lpszDictTaggingDelims[] = "/* \t\xA0"; // C_NBSP

HRESULT TvXmlFile::PutCharProc
(
KpChar iOutch,
XmlTagPars *pTagPars,
bool bCheckIndex
)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpChar *out_str_i = NULL;
KpChar outch;
const unsigned char *outsptr;
bool xml_char;
bool xml_ent;
const unsigned char *pnts;
unsigned char *pntd;
KpChar cur_tag = C_Nul;
KpChar prev_tag = C_Nul;
XmlTagPars *tag_par = NULL;
XmlTagPars *new_par = NULL;
XmlTagPars *sub_par = NULL;
unsigned char par_nam[TV_TAG_LEN + 1] = {""};
KpChar *par_val_i = NULL;
KpChar *start_ptr_i;
KpChar *end_ptr_i;
KpChar *par_ptr_i;
UC_Modes enc_mode;
int ctbl;
int char_pos;
// long char_num;
KpChar first_tag;
KpChar last_tag;
const unsigned char * const *tag_names;
const unsigned char *tag_ptr;
const int *code_tables = NULL;

unsigned char *val_buf = null;
   KP_NEWA(val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

unsigned char *val_buf_dst = null;
   KP_NEWA(val_buf_dst, unsigned char, 2 * MAX_XML_PAR_VAL_LEN + 1);

KpChar *val_buf_i = NULL;
   KP_NEWA(val_buf_i, KpChar, MAX_XML_PAR_VAL_LEN + 1);

KpChar *val_buf_dst_i = NULL;
   KP_NEWA(val_buf_dst_i, KpChar, 2 * MAX_XML_PAR_VAL_LEN + 1);

int par_num;
bool null_ref;
// bool after_delim;
unsigned char str_buf[MAX_LONG_DIGITS+1];
const KpChar *pntsi;
KpChar *pntdi;
XL_PathMode path_mode = GetPathMode();
XmlParRec *par_rec = NULL;

#if FALSE // #ifdef Debug
TvXmlTagStack *prev_ptr;
int prev_prev_tag;
if((iOutch & 0xfffe) == XC_Paragraph) // HTM_TG_P) // XC_Img)
{
m_lpTagStack->GetCurTag(&cur_tag);
m_lpTagStack->GetPrevTagPtr(&prev_ptr);
prev_ptr->GetCurTag(&prev_tag);
prev_ptr->GetPrevTagPtr(&prev_ptr);
prev_ptr->GetCurTag(&prev_prev_tag);
KP_TRACE_4("PutCharProc pradzia: iOutch:%d cur_tag:%d prev_tag:%d prev_prev_tag:%d", iOutch, cur_tag, prev_tag, prev_prev_tag);
}
else KP_TRACE_1("PutCharProc pradzia: iOutch:%d", iOutch);

// if(iOutch == XC_Img_e) return(retc);
#endif

   outch = iOutch;

   KP_ASSERT(m_lpTagStack != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_lpLowLevelFile != NULL, KP_E_NO_FILE, null, True);

   KP_NEWA(out_str_i, KpChar, KP_MAX_FILE_LIN_LEN + 1);
   KP_NEWA(par_val_i, KpChar, KP_MAX_FILE_LIN_LEN + 1);

   if(outch && SUCCEEDED(retc))
   {

#if FALSE // #ifdef Debug
if(outch==C_Great) // '>'
outch=C_Great; // '>';
#endif
#ifdef Debug
if(outch==XC_TranslGroup_e)
outch=XC_TranslGroup_e;
#endif

// Xml tag character
      if(
         ((outch >= XL_FirstSysTag) && (outch < XL_LastSysTag)) ||
         ((outch >= m_iFirstDictTag) && (!CheckLastTag(outch) /* outch < m_iLastDictTagCurrent */)) ||
         (
            (outch>=HTM_TG_FirstTag) && (outch<HTM_TG_LastTag) &&
            XM_IS_VERS_HTML(m_iXmlVers)
         )
        )
      {
         tag_par=pTagPars;

         if(XM_IS_VERS_HTML(m_iXmlVers) && SUCCEEDED(retc))
         {
            switch(outch)
            {
            case XC_Dict: outch=(KpChar)HTM_TG_BODY; tag_par=NULL; break;
            case XC_Dict_e: outch=(KpChar)HTM_TG_BODY_e; tag_par=NULL; break;

            case XC_Reference: outch=(KpChar)HTM_TG_A; break;
            case XC_Reference_e: outch = (KpChar)HTM_TG_A_e; break;

            case XC_Paragraph: outch=(KpChar)HTM_TG_P; break;
            case XC_Paragraph_e: outch = (KpChar)HTM_TG_P_e; break;

            case XC_Italic: outch=(KpChar)HTM_TG_I; break;
            case XC_Italic_e: outch=(KpChar)HTM_TG_I_e; break;
            case XC_Subscript: outch=(KpChar)HTM_TG_SUB; break;
            case XC_Subscript_e: outch=(KpChar)HTM_TG_SUB_e; break;
            case XC_Super: outch=(KpChar)HTM_TG_SUP; break;
            case XC_Super_e: outch=(KpChar)HTM_TG_SUP_e; break;
            case XC_Img: outch=(KpChar)HTM_TG_IMG; break; // outch=(KpChar)HTM_TG_OBJECT; break; // outch=(KpChar)HTM_TG_EMBED; break; //
//          case XC_Img:
//             retc = PutCharProc(HTM_TG_IFRAME, tag_par, bCheckIndex);
//             outch=(KpChar)HTM_TG_IFRAME_e;
//             tag_par = NULL;
//             break;
#if FALSE
            case XC_Equiation:
            case XC_EquInline:
               outch=(KpChar)HTM_TG_EMBED;
//             retc = PutCharProc(HTM_TG_IFRAME, tag_par, bCheckIndex);
//             outch=(KpChar)HTM_TG_IFRAME_e;
//             tag_par = NULL;
               break;
#endif
            }
         }

#ifdef Debug
if(outch==(KpChar)HTM_TG_P)
outch=(KpChar)HTM_TG_P;
#endif

         if((outch>=XL_FirstSysTag) && (outch<XL_LastSysTag))
         {
            first_tag = (KpChar)XL_FirstSysTag;
            last_tag = (KpChar)XL_LastSysTag;
            tag_names = plpszaXmlSysTags;
            code_tables = iaXmlSysCodeTables;
         }
         else if((outch >= m_iFirstDictTag) && (!CheckLastTag(outch) /* outch < m_iLastDictTagCurrent */))
         {
            first_tag = m_iFirstDictTag;
            last_tag = GetLastTag(); // m_iLastDictTagCurrent;
            tag_names = m_lpszaTagNames;
            code_tables = m_piaCodeTablesOrig;
         }
         else
         {
            first_tag = (KpChar)HTM_TG_FirstTag;
            last_tag = (KpChar)HTM_TG_LastTag;
            tag_names = plpszaHtmlTags;
            code_tables = iaHtmNulCodeTables;
         }

// tag stack processing
         cur_tag=outch;
         if(SUCCEEDED(retc))
            retc=m_lpLowLevelFile->GetEncoding(&enc_mode, &ctbl);

         if(strcmp((const char *)tag_names[(outch&(~1))+1-first_tag], "")!=0)
         {
            if((outch & 0x01) == 0) retc=PushTag(&m_lpTagStack, outch, NULL, 0);
            else
            {
               if((m_lpTagStack == NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(&cur_tag);
               if(SUCCEEDED(retc))
               {
                  if(cur_tag == (outch & (~0x01))) retc=PopTag(&m_lpTagStack, &cur_tag);
                  else
                  {
                     if(XM_IS_VERS_HTML(m_iXmlVers))
                     {
                        switch(cur_tag)
                        {
                        case HTM_TG_I: retc = PutCharProc(HTM_TG_I_e, NULL, bCheckIndex); break;
                        case HTM_TG_B: retc = PutCharProc(HTM_TG_B_e, NULL, bCheckIndex); break;
                        case XC_RefWord: retc = PutCharProc(XC_RefWord_e, NULL, bCheckIndex); break;
                        default:
                           if(outch == (KpChar)HTM_TG_P_e)
                              retc = PutCharProc(cur_tag+1, NULL, bCheckIndex);
                           else
                           {
#if FALSE // #if TRUE //
stringstream str_stream;
str_stream << "cur_tag: " << cur_tag << "outch: " << outch;
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, KpString(str_stream.str()).ExtractUnsignedValueA(), True, __FILE__, __LINE__, 0L);
#else
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
#endif
                           }
                           break;
                        }
                        if(SUCCEEDED(retc)) retc=PopTag(&m_lpTagStack, &cur_tag);
                           if(cur_tag != (outch & (~0x01)))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                     }
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                  }
               }

               if(SUCCEEDED(retc))
               {
                  if(m_lpTagStack!=NULL) retc=m_lpTagStack->GetCurTag(&cur_tag);
                  else
                  {
                     cur_tag=(KpChar)(outch&(~1));
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                  }
               }
            }

// set default low level file code table for tag output
            if(SUCCEEDED(retc)) retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
         }

#if FALSE
// put eol, if output row allready full
         if(SUCCEEDED(retc)) retc=GetCharPos(&char_pos);
         if(
            (char_pos > TV_XML_CHAR_POS_THRESHOLD) &&
            (m_uiFType==XL_FT_DataFile) &&
            (outch!=XC_Reference_e) &&  // prevent insertion of eols/spaces
            SUCCEEDED(retc)
           )
            retc=PutChar(C_Lf, False); // retc=PutStr(m_lpszIndentStr);
#endif

// add XMLT tag as parameter for HTML files
#ifdef Debug
// if(outch == XL_DocType) KP_TRACE_3("xmlf:PutCharProc: m_plpszaTagNamesOrig:%lx plpszaXmlSysTags:%lx outch:%d", m_plpszaTagNamesOrig, plpszaXmlSysTags, outch);
#endif

#ifdef Debug
// if(outch == XC_Paragraph_e) KP_TRACE_1(">>>%s<<<", tag_names[outch-first_tag]);
#endif
         if(
            (
               ((outch >= XL_FirstSysTag) && (outch < XL_LastSysTag)) ||
               ((outch >= m_iFirstDictTag) && (!CheckLastTag(outch) /* outch < m_iLastDictTagCurrent */))
            ) &&
            XM_IS_VERS_HTML_TAGE(m_iXmlVers) && // XM_IS_VERS_HTML(m_iXmlVers) && (m_plpszaTagNamesOrig != plpszaHtmlTags) &&
            (tag_names != plpszaHtmlTags) &&
            (tag_names != plpszaXmlSysTags) &&
            ((outch & 0x01) == 0) && SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc))
               if(strlen(tag_names[outch - first_tag]) >= KP_MAX_FILE_LIN_LEN)
                  retc = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               retc0 = KptStrEncode(out_str_i, tag_names[outch - first_tag], TV_CTBL_ASCII);
               if(FAILED(retc0)) KP_WARNING(retc0, tag_names[outch - first_tag]);

               start_ptr_i = out_str_i;
               if(*start_ptr_i == TV_XM_TagStartCh)
               {
                  start_ptr_i++;
                  if(*start_ptr_i == '?') start_ptr_i++;
                  else if(*start_ptr_i == '!') start_ptr_i++;
                  else if(*start_ptr_i == '/') start_ptr_i++;
                  {
                     if(*start_ptr_i == '-') start_ptr_i++;
                     if(*start_ptr_i == '-') start_ptr_i++;
                  }
                  while(*start_ptr_i == C_Spc) start_ptr_i++;
               }

               end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_1); // " ?>"
               if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_1 + 1); // "?>"
               if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_2); // " -->"
               if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_2 + 1); // "-->"
               if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_3); // "/>"
               if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrChr(out_str_i, TV_XM_TagEndCh);  // '>'

               if(end_ptr_i != NULL) *end_ptr_i = C_Nul;
            }

            KP_ASSERT(new_par == NULL, KP_E_SYSTEM_ERROR, null, True);
            if(tag_par != NULL) KP_NEWO(new_par, XmlTagPars(tag_par));
            if(SUCCEEDED(retc))
            {
               if(new_par == NULL){ KP_NEWO(new_par, XmlTagPars((const unsigned char *)"class", start_ptr_i)); }
               else retc = new_par->AddKpTextPar((const unsigned char *)"class", start_ptr_i);
            }
            tag_par = new_par;
         }

// correct <a> href parameter
         if((outch==HTM_TG_A) && SUCCEEDED(retc))
         {
            KP_ASSERT(new_par == NULL, KP_E_SYSTEM_ERROR, null, False);
            if(tag_par == NULL)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
KP_TRACE("<a> be parametrø");
            }
            else
            {
//             if(SUCCEEDED(retc)) retc = CopyTagPars(tag_par, &new_par);
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

//------
               if(SUCCEEDED(retc))
               {
                  null_ref = True;
//                after_delim = False;
                  sub_par = NULL;

                  retc = new_par->SeekKpTextPar("href", val_buf_i, &par_num);
                  if(SUCCEEDED(retc))
                  {
                     pntdi = val_buf_dst_i;
                     *pntdi = C_Nul;
// -------------
                     if(path_mode == XL_TuxPath)
                        if(TvKpStrStr(val_buf_i, TV_XL_TUX_PATH_PREFIX_W) != val_buf_i) // "tux:"
                        {
                           TvKpStrCpy(val_buf_dst_i, TV_XL_TUX_PATH_PREFIX_W);
                           pntdi += TvKpStrLen(TV_XL_TUX_PATH_PREFIX_W);
                        }

                     TvKpStrCpy(pntdi, val_buf_i);
// --------------
                     while(*pntdi)
                     {
                        if(*pntdi == C_Point) // '.'
                           if(TvKpToLower((KpChar)pntdi[1]) == C_x) // 'x'
                              if(TvKpToLower((KpChar)pntdi[2]) == C_m) // 'm'
                                 if(TvKpToLower((KpChar)pntdi[3]) == C_l) // 'l'
                                 {
                                    pntdi[1] = C_h; // 'h'
                                    pntdi[2] = C_t; // 't'
                                    pntdi[3] = C_m; // 'm'
                                 }

//                      if((*pntd!='0') && after_delim) null_ref=False;
                        if((*pntdi != C_0) && (*pntdi != (KpChar)TV_XM_HrefDelim)) null_ref = False; // '0'

                        if(*pntdi == (KpChar)TV_XM_HrefDelim)
                        {
                           *pntdi = (KpChar)TV_HTM_HrefDelim;
//                         after_delim = True;
                        }
                        pntdi++;
                     }

                     if(null_ref)
                     {
                        KP_DELETE(new_par);
                        KP_NEWO(new_par, XmlTagPars((const unsigned char *)"class", (const unsigned char *)"null", NULL));
                     }

                     if(SUCCEEDED(retc))
                     {
                        retc = new_par->SetKpTextPar(par_num, val_buf_dst_i);
                        tag_par = new_par;
                     }

                  } // if(SUCCEEDED(retc)) // retc = SeekKpTextPar("href", val_buf_i, &par_num);

                  else if(retc == KP_E_KWD_NOT_FOUND)
                  {
//                   retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
                     retc = S_OK;
                  }

               } // if(SUCCEEDED(retc)) // new_par = new XmlTagPars(tag_par);

            } // else // if(tag_par==NULL)

         } // if((outch==HTM_TG_A) && SUCCEEDED(retc))

// correct <img> src parameter
         if((outch == HTM_TG_IMG) && SUCCEEDED(retc))
         {
            if((tag_par != NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num);
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

// KP_TRACE("---------------------");
// KP_TRACE(val_buf);
// KP_TRACE(val_buf_dst);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

                     if(SUCCEEDED(retc)) strcat(val_buf_dst, (GetScale()<=10)?"img\\":"imgx\\");
                  }

// KP_TRACE(val_buf_dst);

                  strcat(val_buf_dst, val_buf);
// KP_TRACE(val_buf_dst);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".jpg");
// KP_TRACE(val_buf_dst);

                  if(SUCCEEDED(retc))
                  {
                     retc = new_par->SetTextPar(par_num, val_buf_dst);
                     tag_par = new_par;
                  }

               } // if(SUCCEEDED(retc)) // retc = tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_IMG) && SUCCEEDED(retc))

// correct <object> src parameter
// <object data="rect.svg" width="300" height="100" type="image/svg+xml" codebase="http://www.adobe.com/svg/viewer/install/" />
// <object type="image/svg+xml" data="file.svg" width="300" height="200"></object>

         if((outch==HTM_TG_OBJECT) && SUCCEEDED(retc))
         {
            if((tag_par != NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num); // ateina ið XC_Img
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

                     if(SUCCEEDED(retc)) strcat(val_buf_dst, "img/");
                  }

                  strcat(val_buf_dst, val_buf);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".svg");

                  if(SUCCEEDED(retc)) retc = new_par->SetParName(par_num, (const unsigned char *)"data");
                  if(SUCCEEDED(retc)) retc = new_par->SetTextPar(par_num, val_buf_dst);
                  if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"image/svg+xml");
                  if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"pluginspage", (const unsigned char *)"http://www.adobe.com/svg/viewer/install/");

                  if(SUCCEEDED(retc)) tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc=tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_OBJECT) && SUCCEEDED(retc))

// correct <iframe> href parameter
#if FALSE
// <iframe src="rect.svg" width="300" height="100"></iframe>

         if((outch==HTM_TG_IFRAME) && SUCCEEDED(retc))
         {
            if((tag_par!=NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num); // ateina ið XC_Img
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

                     if(SUCCEEDED(retc)) strcat(val_buf_dst, "img/");
                  }

                  strcat(val_buf_dst, val_buf);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".svg");

                  if(SUCCEEDED(retc)) retc = new_par->SetTextPar(par_num, val_buf_dst);
//                if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"image/svg+xml");
//                if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"pluginspage", (const unsigned char *)"http://www.adobe.com/svg/viewer/install/");

                  if(SUCCEEDED(retc)) tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc=tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_IFRAME) && SUCCEEDED(retc))
#endif

// <iframe src="rect.svg" width="300" height="100"></iframe>

         if((outch==HTM_TG_IFRAME) && SUCCEEDED(retc))
         {
            if((tag_par!=NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num); // ateina ið XC_Img
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

//                   strcat(val_buf_dst, "mml/");
                  }

                  strcat(val_buf_dst, val_buf);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".xhtml");

                  if(SUCCEEDED(retc)) retc = new_par->SetTextPar(par_num, val_buf_dst);
//                if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"image/svg+xml");

                  if(SUCCEEDED(retc)) tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc=tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_IFRAME) && SUCCEEDED(retc))

// correct <embed> href parameter
#if FALSE
// <embed src="rect.svg" width="300" height="100" type="image/svg+xml" pluginspage="http://www.adobe.com/svg/viewer/install/" />
         if((outch==HTM_TG_EMBED) && SUCCEEDED(retc))
         {
            if((tag_par!=NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num); // ateina ið XC_Img
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

                     strcat(val_buf_dst, "img/");
                  }

                  strcat(val_buf_dst, val_buf);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".svg");

                  if(SUCCEEDED(retc)) retc = new_par->SetTextPar(par_num, val_buf_dst);
                  if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"image/svg+xml");
                  if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"pluginspage", (const unsigned char *)"http://www.adobe.com/svg/viewer/install/");

                  if(SUCCEEDED(retc)) tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc=tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_EMBED) && SUCCEEDED(retc))
#endif

// <EMBED TYPE="text/mathml" src="lzdsh3.mml" HEIGHT=300 WIDTH=200>
         if((outch==HTM_TG_EMBED) && SUCCEEDED(retc))
         {
            if((tag_par!=NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num); // ateina ið XC_Img
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  if((strchr(val_buf, '/') == 0) && (strchr(val_buf, '\\') == 0))
                  {
                     if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
//                      if(strstr(val_buf, TV_XL_ABS_FILE_PATH_PREFIX) != val_buf) // "file://"
                        {
                           strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX);
                           pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
                           retc = GetAppPath(pntd, True);
                        }

//                   strcat(val_buf_dst, "mml/");
                  }

                  strcat(val_buf_dst, val_buf);
//                if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".mml");
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".xhtml");

                  if(SUCCEEDED(retc)) retc = new_par->SetTextPar(par_num, val_buf_dst);
//                if(SUCCEEDED(retc)) retc = new_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text/mathml");

                  if(SUCCEEDED(retc)) tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc=tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_EMBED) && SUCCEEDED(retc))

// correct <script> src parameter
         if((outch == HTM_TG_SCRIPT) && SUCCEEDED(retc))
         {
            if((tag_par != NULL) && SUCCEEDED(retc))
            {
               KP_ASSERT(tag_par != NULL, KP_E_FILE_FORMAT, null, True);
               KP_NEWO(new_par, XmlTagPars(tag_par));

               if(SUCCEEDED(retc))
                  retc = new_par->SeekTextPar("src", val_buf, &par_num);

               val_buf_dst[0] = Nul;

               if(SUCCEEDED(retc))
               {
                  if(path_mode == XL_TuxPath)
                     if(strstr(val_buf, TV_XL_TUX_PATH_PREFIX) != val_buf) // "tux:"
                        strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX);

                  strcat(val_buf_dst, val_buf);

                  retc = new_par->SetTextPar(par_num, val_buf_dst);
                  tag_par = new_par;

               } // if(SUCCEEDED(retc)) // retc = tag_par->SeekTextPar("src", val_buf, &par_num);

               retc = S_OK;

            } // if((tag_par!=NULL) && SUCCEEDED(retc))

         } // if((outch==HTM_TG_SCRIPT) && SUCCEEDED(retc))

// correct <style> subparameter url(...) values
// <style>
// body
// {
//    cursor: url(openhand_8_8.cur), default;
// }
// </style>
// èia neiðeina, reikia aukðtesniam lygmeny
//       if((outch == HTM_TG_STYLE) && SUCCEEDED(retc))
//       {
//       }

// tag formatting
         if(SUCCEEDED(retc))
         {
            if(
               (outch >= m_iFirstDictTag) && (!CheckLastTag(outch) /* outch < m_iLastDictTagCurrent */) &&
               XM_IS_VERS_HTML_TAGE(m_iXmlVers) // XM_IS_VERS_HTML(m_iXmlVers) && (m_plpszaTagNamesOrig != plpszaHtmlTags)
              )
            {
               if(outch&0x01) tag_ptr = plpszaHtmlTags[HTM_TG_SPAN_e - HTM_TG_FirstTag];
               else tag_ptr = plpszaHtmlTags[HTM_TG_SPAN - HTM_TG_FirstTag];
            }
            else tag_ptr = tag_names[outch-first_tag];
         }

         if(SUCCEEDED(retc))
            if(strlen(tag_ptr) >= KP_MAX_FILE_LIN_LEN)
               retc = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            retc0 = KptStrEncode(out_str_i, tag_ptr, TV_CTBL_ASCII);
            if(FAILED(retc0)) KP_WARNING(retc0, tag_ptr);

            end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_1); // " ?>"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_1 + 1); // "?>"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_4); // "]>"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_2); // " -->"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_2 + 1); // "-->"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrStr(out_str_i, TV_XL_TAG_SUFF_3); // "/>"
            if(end_ptr_i == NULL) end_ptr_i = (KpChar*)TvKpStrChr(out_str_i, TV_XM_TagEndCh);  // '>'
         }

         if((m_iXmlVers!=XM_VERS_SGML_TAGE) && SUCCEEDED(retc))
         {
            if(end_ptr_i != NULL)
            {
               *end_ptr_i = C_Nul;

// tag parameters
//             form_str = (const unsigned char *)" %s=\"%s\"";
               par_ptr_i = out_str_i + TvKpStrLen(out_str_i);
               while((tag_par != NULL) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) retc = tag_par->TestValueConsistence();
                  if(SUCCEEDED(retc)) retc = tag_par->GetCurKpTextPar(par_nam, par_val_i);
#ifdef Debug
// if(outch == XL_DocType) KP_TRACE(par_nam);
#endif
                  if(SUCCEEDED(retc))
                     if(par_ptr_i + strlen(par_nam) + TvKpStrLen(par_val_i) + 10 /* strlen(form_str) */ >= out_str_i + KP_MAX_FILE_LIN_LEN)
                        retc = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc))
                  {
//                   sprintf((char *)par_ptr_i, (strlen(par_val_i) > 0)?((strlen(par_nam) > 0)?(const char *)form_str:" %s\"%s\""):" %s%s", par_nam, par_val_i);
                     *par_ptr_i++ = C_Spc;
                     *par_ptr_i = C_Nul;

                     if(par_nam[0] != Nul) // (strlen(par_nam) > 0)
                     {
                        retc0 = KptStrEncode(par_ptr_i, par_nam, TV_CTBL_ASCII);
                        if(FAILED(retc0)) KP_WARNING(retc0, par_nam);

                        par_ptr_i += TvKpStrLen(par_ptr_i);
                        if(par_val_i[0] != C_Nul) *par_ptr_i++ = '=';
                        *par_ptr_i = C_Nul;
                     }

                     if(par_val_i[0] != C_Nul) // if(TvKpStrLen(par_val_i) > 0)
                     {
                        *par_ptr_i++ = '\"';
                        TvKpStrCpy(par_ptr_i, par_val_i);
                        par_ptr_i += TvKpStrLen(par_ptr_i);
                        *par_ptr_i++ = '\"';
                        *par_ptr_i = C_Nul;
                     }

                     retc = tag_par->GetNextBrother((KpTreeEntry **)&tag_par);
                  }

               } // while((tag_par!=NULL) && SUCCEEDED(retc))

               if(SUCCEEDED(retc))
                  if(TvKpStrLen(out_str_i) + strlen(tag_ptr + (end_ptr_i - out_str_i)) >= KP_MAX_FILE_LIN_LEN)
                     retc = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  if(m_bMultiLine)
                  {
//                   strcat(out_str_i, tag_ptr + (end_ptr_i - out_str_i));
                     retc0 = KptStrEncode(out_str_i + TvKpStrLen(out_str_i), tag_ptr + (end_ptr_i - out_str_i), TV_CTBL_ASCII);
                     if(FAILED(retc0)) KP_WARNING(retc0, tag_ptr + (end_ptr_i - out_str_i));
                  }
                  else
                  {
                     pntdi = out_str_i + TvKpStrLen(out_str_i);
                     pnts = tag_ptr + (end_ptr_i - out_str_i);
                     do
                     {
                        (*pntdi++) = (*pnts);
                        if((*pnts != Nul) && (*pnts != TV_XM_TagEndCh)) pnts++; // '>'
                        else break;
                     } while(SUCCEEDED(retc));
                     *pntdi = C_Nul;
                  }
               }
            }
            else // if(end_ptr_i != NULL)
            {
               if(pTagPars!=NULL)
                  retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
            }
         }

// -----------
//       if(new_par != NULL)
//       {
//          retc0 = new_par->SetNextBrother(NULL); // !!!!???? Neaiðku, kas iðvalo nukerpamà uodegà
//          if(SUCCEEDED(retc)) retc = retc0;

            KP_DELETE(new_par);
//       }

// -----------
// put Xml tag
//       retc = PutStr(out_str);
         pntsi = out_str_i;
// GetCharNum(&char_num);

         if(SUCCEEDED(retc))
//          if(((outch&0x01) == 0) || (strcmp((const char *)tag_names[(outch&(~1))+1-first_tag], "")!=0))
            if(
               (strcmp((const char *)tag_names[outch-first_tag], "")!=0) &&
               (
                  (
                     (outch != XC_Equiation) && // dar nesugalvojau kokiu HTML tagu keist -
                     (outch != XC_EquInline)    // lieka atidarantis <span class="eq" src="e0001000">, o <eq/> tagas pavienis - u_daranèio </span> nëra
                  ) ||                          // (nors praktiðkai ka_ko u_daranèiø </span> per daug bûna)
                  (!XM_IS_VERS_HTML(m_iXmlVers))
               )
              )
               while((*pntsi != C_Nul) && SUCCEEDED(retc))
               {
                  if(TvStrChr(lpszEols, *pntsi) != NULL)
                  {
                     if(!XM_IS_VERS_HTML(m_iXmlVers) || (outch == XL_DocType))
                        retc=PutChar(C_Lf, False); // retc=PutStr(m_lpszIndentStr);
                  }
                  else
                  {
                     retc=GetCharPos(&char_pos);
                     if((char_pos==0) && SUCCEEDED(retc))
                     {
                        if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(&cur_tag);
// KP_TRACE_("m_lpszIndentStr 1: %d", cur_tag);
                        if(
                           (cur_tag != C_Nul) &&
                           (cur_tag != HTM_TG_HTML) &&
                           (cur_tag != HTM_TG_HEAD) &&
                           (cur_tag != HTM_TG_STYLE) &&
                           (cur_tag != HTM_TG_SCRIPT) &&
                           (cur_tag != HTM_TG_PRE) &&
                           (cur_tag != HTM_TG_CODE) &&
                           (cur_tag != XL_Comment) &&
                           SUCCEEDED(retc)
                          )
                        {
                           retc = PutStr(m_lpszIndentStr);
                        }
                     }
                     if(SUCCEEDED(retc)) retc = PutChar(*pntsi, True);
                  }
                  pntsi++;
// GetCharNum(&char_num);
               }

// set low level file code table for tag contents
// reiketu tik uzdarancioms gairems - atidarancioms jau nustatyta anksciau
         if((cur_tag!=C_Nul) && SUCCEEDED(retc))
         {
            if(
               ((cur_tag < XL_FirstSysTag) || (cur_tag >= XL_LastSysTag)) &&
               ((cur_tag < m_iFirstDictTag) || (CheckLastTag(cur_tag) /* cur_tag >= m_iLastDictTagCurrent */)) &&
               (
                  (cur_tag < HTM_TG_FirstTag) || (cur_tag >= HTM_TG_LastTag) ||
                  (!XM_IS_VERS_HTML(m_iXmlVers))
               ) &&
               SUCCEEDED(retc)
              )
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// jau suskaièiuota su outch - gal jau nereikia - outch == cur_tag?
            if((cur_tag>=XL_FirstSysTag) && (cur_tag<XL_LastSysTag))
            {
               first_tag = (KpChar)XL_FirstSysTag;
               last_tag = (KpChar)XL_LastSysTag;
               tag_names = plpszaXmlSysTags;
               code_tables = iaXmlSysCodeTables;
            }
            else if((cur_tag >= m_iFirstDictTag) && (!CheckLastTag(cur_tag) /* cur_tag < m_iLastDictTagCurrent */))
            {
               first_tag = m_iFirstDictTag;
               last_tag = GetLastTag(); // m_iLastDictTagCurrent;
               tag_names = m_lpszaTagNames;
               code_tables = m_piaCodeTablesOrig;
            }
            else
            {
               first_tag = (KpChar)HTM_TG_FirstTag;
               last_tag = (KpChar)HTM_TG_LastTag;
               tag_names = plpszaHtmlTags;
               code_tables = iaHtmNulCodeTables;
            }

            if(((cur_tag < first_tag) || (cur_tag >= last_tag)) && (cur_tag != 0) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//          if((code_tables == NULL) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if(strcmp((const char *)tag_names[(cur_tag&(~1))+1-first_tag], "")!=0)
               {
                  if(SUCCEEDED(retc))
                  {
//                   ctbl = code_tables[cur_tag - first_tag];
                     ctbl = GetTagCodeTable(cur_tag, first_tag, last_tag, code_tables);

                     if(ctbl >= 0)
                        retc=m_lpLowLevelFile->SetEncoding(enc_mode, ctbl);
                     else if(ctbl == KPT_UpCodeTable)
                     {
TvXmlTagStack *tag_stack_ptr;
                        tag_stack_ptr = m_lpTagStack;
                        while((tag_stack_ptr!=NULL) && SUCCEEDED(retc))
                        {
                           retc=tag_stack_ptr->GetPrevTag(&prev_tag);
                           if(prev_tag==0) break;
                           else
                           {
                              if((prev_tag >= XL_FirstSysTag) && (prev_tag < XL_LastSysTag))
                              {
                                 first_tag = (KpChar)XL_FirstSysTag;
                                 last_tag = (KpChar)XL_LastSysTag;
                                 tag_names = plpszaXmlSysTags;
                                 code_tables = iaXmlSysCodeTables;
                              }
                              else if((prev_tag >= m_iFirstDictTag) && (!CheckLastTag(prev_tag) /* prev_tag < m_iLastDictTagCurrent */))
                              {
                                 first_tag = m_iFirstDictTag;
                                 last_tag = GetLastTag(); // m_iLastDictTagCurrent;
                                 tag_names = m_lpszaTagNames;
                                 code_tables = m_piaCodeTablesOrig;
                              }
                              else
                              {
                                 first_tag = (KpChar)HTM_TG_FirstTag;
                                 last_tag = (KpChar)HTM_TG_LastTag;
                                 tag_names = plpszaHtmlTags;
                                 code_tables = iaHtmNulCodeTables;
                              }

                              if(GetTagCodeTable(prev_tag, first_tag, last_tag, code_tables)
                                 /* code_tables[prev_tag - first_tag] */ != KPT_UpCodeTable) break;
                              else
                                 retc = tag_stack_ptr->GetPrevTagPtr(&tag_stack_ptr);
                           }
                        }
                        if(SUCCEEDED(retc))
                        {
//                         if(prev_tag != 0)
                              retc=m_lpLowLevelFile->SetEncoding(enc_mode, GetTagCodeTable(prev_tag, first_tag, last_tag, code_tables)
                                                                        /* code_tables[prev_tag-first_tag] */);
//                         else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
                        }
                     }
                     else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
                  }
                  else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
               }
            }
         }

// ------------------------ aprëminam HTML _od_ius reikðminiais tagais
         if(XM_IS_VERS_HTML_TAGE(m_iXmlVers) && // XM_IS_VERS_HTML(m_iXmlVers) && (m_plpszaTagNamesOrig != plpszaHtmlTags) &&
            SUCCEEDED(retc)) switch(outch)
         {
         case HTM_TG_A: retc = PutCharProc(XC_RefWord, NULL, bCheckIndex); break;
         case HTM_TG_P:
            if((m_lpTagStack == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc = m_lpTagStack->GetPrevTag(&prev_tag);
            if(SUCCEEDED(retc)) retc = PutCharProc(prev_tag, NULL, bCheckIndex);
            break;
         }

// ---- embedinam MathML failà
         if(XM_IS_VERS_HTML(m_iXmlVers) && SUCCEEDED(retc)) switch(outch)
         {
         case XC_Equiation:
         case XC_EquInline:
            if((pTagPars!=NULL) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  retc=pTagPars->SeekTextPar("src", val_buf, &par_num);
               val_buf_dst[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  strcpy(val_buf_dst, "mml\\");
                  strcat(val_buf_dst, val_buf);
                  if(strchr(val_buf, '.') == 0) strcat(val_buf_dst, ".mml");
               }

KP_TRACE(val_buf_dst);

               if(SUCCEEDED(retc))
               {
                  pntd = NULL;
                  retc = ReadFileContents(val_buf_dst, &pntd, NULL, False, False);
                  if(retc == KP_E_FILE_NOT_FOUND)
                  {
                     retc = S_OK;
                     if(SUCCEEDED(retc)) retc = PutStr((const unsigned char *)"{");
                     if(SUCCEEDED(retc)) retc = PutStr(val_buf_dst);
                     if(SUCCEEDED(retc)) retc = PutStr((const unsigned char *)"}");
                  }
                  else if(pntd && SUCCEEDED(retc))
                     retc = PutStr(pntd);

                  KP_DELETEA(pntd);
               }
            }
            break;
         }


// ----------------------------- <a name="...">
         if((outch==XC_StEntry) &&
            XM_IS_VERS_HTML(m_iXmlVers) &&
            SUCCEEDED(retc))
         {
            if((pTagPars==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               retc=pTagPars->SeekTextPar("id", val_buf, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            KP_NEWO(new_par, XmlTagPars((const unsigned char *)"name", val_buf, NULL));

            if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)HTM_TG_A, new_par, bCheckIndex);
            if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)HTM_TG_A_e, NULL, bCheckIndex);

            KP_DELETE(new_par);
         }
      }

//---------------------------------
// ordinary character
      else // if((outch>=XC_FirstDictTag) && (outch<XC_NumOfDictTags))
      {

// !!!! keiciam kirciuotas betaskes i taskuotas, reiketu tik liet. kalboj siaip jau
         if(SUCCEEDED(retc)) switch(outch)
         {
         case C_i_Grave_Dotless: outch = C_i_Grave; break;
         case C_i_Acute_Dotless: outch = C_i_Acute; break;
         case C_i_Tilde_Dotless: outch = C_i_Tilde; break;
         }

         if(SUCCEEDED(retc)) if(XM_IS_VERS_HTML(m_iXmlVers)) switch(outch)
         {
         case C_QemSpc: outch = C_NBSP; break;
         case C_lSpc:
//          GetCharPos(&char_pos);
//          if(char_pos >= iNumOfChars ??? -LAST_WORD_LEN) // ka_kà kaip TEX-e padaryt - suskaièiuot pastraipos ilgá prieð iðvedant mazgà? !!!!
//             outch=C_NBSP;
//          else
               outch=C_Spc;
            break;
         }

// ---------------------------------------- SGML valdantys simboliai
#ifdef Debug
if(outch==C_NullSpc)
outch=C_NullSpc;
#endif
         if((m_iXmlVers >= XM_VERS_SGML) && (m_iXmlVers < XM_VERS_HTML) && SUCCEEDED(retc))
         {
            switch(outch)
            {
// \  - soft hyphen - minkstas kelimo zenklas
// (&  - hard hyphen - zodzio kelimas per prievarta - eilutes lauzimas vidury
// zodzio - keiciamas i "-$^", ismestas)
// #  - 1/4 em-space - 1/4 m tarpas ($\,$)
// { } - bold srifto gabaliukas
// [ ] - stataus srifto gabaliukas, realizuotas tik RLZ TeX'o stiliuje, tik
// iterptiniams zodziams (<ct>) ir suvalgo paprastus tarpus
// $$ $\ $& $# ${ $} $[ $] - patys simboliai $ \ # { } [ ]
// $^ - line break - eilutes perlauzimas, pirmoji puse islyginama iki desinio
// krasto (\hfill), anksciau buvo vien tik "^"
// $@ - page break - puslapio pabaiga, anksciau buvo vien tik "@"
// $_ - en-space - n-tarpas, anksciau buvo vien tik "_"
// $. - null space (\Null), skirtuku atskyrejas, tarpu valgytojas
            case C_NullSpc:
               retc=PutChar(NS_CTRL_START, False);
               if(SUCCEEDED(retc)) retc=PutChar(C_Point, False);
               outch = C_Nul;
               break;
// $qNN (NN - dvizenklis skaicius - $q10 $q40) - atstumu tarp raidziu suspaudimas,
//        skaicius - desimtosios punkto dalys ($q40 reiskia suspaudima 4-ais
//        punktais). Suspaudimas prasideda nuo sio zenklo. Vieta, nuo kurios
//        suspaudimo jau nebereikia pazymima zenklu $q00. Kiekvieno lizdo
//        pradzioje suspaudimas automatiskai panaikinamas ($q00).
// $uNNNN - sesioliktainis Unicode simbolio kodas
// $fNN - perjungimas i fonta nr. NN (zr. KPS_FontStyles, kpfonts.h)
// $sNN - pastraipos nr. NN pozymis, kiekvienam projektui specifines,
            }
         }

// -------------------------- -", rombas (VL_CH_IdiomDelim C_Diamond)
         if(
            XM_IS_VERS_HTML(m_iXmlVers) &&
            ((outch == C_Dash_Diaer) || (outch == C_diamond) || (outch == C_Diamond) || (outch == C_bdiamond)) &&
            SUCCEEDED(retc)
           )
         {
            val_buf_dst[0] = Nul;

// èia nereikia - pridës <img> iðvedimas
//          if((path_mode == XL_TuxPath) && SUCCEEDED(retc))
//             strcpy(val_buf_dst, TV_XL_TUX_PATH_PREFIX); // "tux:"

            if((path_mode == XL_AbsolutePath) && SUCCEEDED(retc))
            {
               strcpy(val_buf_dst, TV_XL_ABS_FILE_PATH_PREFIX); // "file://"
               pntd = val_buf_dst + strlen(TV_XL_ABS_FILE_PATH_PREFIX);
               retc = GetAppPath(pntd, True);
            }

            if(SUCCEEDED(retc)) strcat(val_buf_dst, (GetScale()<=10)?"img/":"imgx/"); // "img\\":"imgx\\");

            if(SUCCEEDED(retc)) switch(outch)
            {
            case C_Dash_Diaer:
               strcat(val_buf_dst, "dash_diaer.jpg");
               break;
            case C_diamond:
            case C_Diamond:
            case C_bdiamond:
               strcat(val_buf_dst, "diamond.jpg");
               break;
            }

            KP_NEWO(new_par, XmlTagPars((const unsigned char *)"src", val_buf_dst, NULL)); // (const unsigned char *)"img/dash_diaer.jpg"); //

            if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)HTM_TG_IMG, new_par, bCheckIndex);

            KP_DELETE(new_par);

            outch = C_Nul;
         }

// -------------------------- tarpas - taginam kiekvienà þodá
         if(
            (TvStrChr(lpszDictTaggingDelims /* lpszSpaces */, outch) != NULL) &&
            XM_IS_VERS_HTML_TAGE(m_iXmlVers) && // XM_IS_VERS_HTML(m_iXmlVers) && (m_plpszaTagNamesOrig != plpszaHtmlTags) &&
            SUCCEEDED(retc)
           )
         {
            if(m_lpTagStack == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(&cur_tag);
            if(((cur_tag < XC_FirstDictTag) || (cur_tag >= XC_LastDictTag)) && SUCCEEDED(retc))
            {
// stringstream str_stream;
// str_stream << cur_tag;
// KpMsgOut(KpString(str_stream.str()), IDI_ASTERISK, KP_MB_TESTI);

// gali bûti - pvz. <i> ???
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, cur_tag);
            }

            if(SUCCEEDED(retc)) retc=PutCharProc(cur_tag+1, NULL, bCheckIndex);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)outch, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(cur_tag, NULL, bCheckIndex);

            outch = C_Nul;
         }

// ------------------------- Lf - lau_iam eilutæ
         if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(&cur_tag);

         if(XM_IS_VERS_HTML(m_iXmlVers) && (TvStrChr(lpszEols, outch)!=NULL) && SUCCEEDED(retc))
         {
// KP_TRACE_("HTM_TG_BR: %d", cur_tag);
            if(
               (cur_tag != C_Nul) &&
               (cur_tag != HTM_TG_HTML) &&
               (cur_tag != HTM_TG_HEAD) &&
               (cur_tag != HTM_TG_STYLE) &&
               (cur_tag != HTM_TG_SCRIPT) &&
               (cur_tag != HTM_TG_PRE) &&
               (cur_tag != HTM_TG_CODE) &&
               (cur_tag != XL_Comment) &&
               SUCCEEDED(retc)
              )
               retc = PutCharProc(HTM_TG_BR, NULL, bCheckIndex);
         }

// put eol, if output row allready full
         if(SUCCEEDED(retc)) retc=GetCharPos(&char_pos);
         if(
            (TvStrChr(lpszSpaces, outch) != NULL) &&
            (char_pos > TV_XML_CHAR_POS_THRESHOLD) &&
            (m_uiFType==XL_FT_DataFile) &&
            (cur_tag != HTM_TG_PRE) &&
            (cur_tag != HTM_TG_CODE)
           ) outch = C_Lf;

// put character
         if(((outch<0) || (outch>=C_CharSize0)) && SUCCEEDED(retc))
         {
            sprintf((char *)str_buf, "iOutch:%d outch:%d", iOutch, outch);
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, str_buf, False /* True */, __FILE__, __LINE__, 0L);
            outch = '?';
         }

         if(SUCCEEDED(retc))
         {
            xml_char=False;
            xml_ent=False;
            outsptr=NULL;

            if(m_plpszaXmlSpecCharTags!=NULL) outsptr=(m_plpszaXmlSpecCharTags[outch]);
            if(outsptr==NULL)
            {
//             sprintf(str_buf, "%d", outch);
//             retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, str_buf, True, __FILE__, __LINE__, 0L);
            }
            else
            {
               if(
                  (cur_tag == HTM_TG_SCRIPT) ||
                  (cur_tag == HTM_TG_PRE) ||
                  (cur_tag == HTM_TG_CODE)
                 )
               {
// neveikia Gintaro JavaScript'ai Lentynoje
// inputas turi bûti esceipintas (&lt; &gt; &amp;), outpute entity keièiam paèiais simboliais < > &
// iraðyto failo jau nebeperskaitysim – < ir & lauð parserá
                  if(outch == '<') outsptr = (const unsigned char *)"<";
                  if(outch == '>') outsptr = (const unsigned char *)">";
                  if(outch == '&') outsptr = (const unsigned char *)"&";
               }

               xml_char=True;
               if(*outsptr == TV_XM_SpCharSt /* '&' */)
                  xml_ent=True;
            }
         }

         if(
            outch &&
            (
               (outch != C_Bpoint) || // bullet
               (!XM_IS_VERS_HTML_TAGE(m_iXmlVers)) // (!XM_IS_VERS_HTML(m_iXmlVers) || (m_plpszaTagNamesOrig == plpszaHtmlTags))
            ) &&
            SUCCEEDED(retc)
           )
         {
// skip delimiters of spec. characters in index files
            if(xml_ent && ((m_uiFType==XL_FT_IxFile) || (m_uiFType==XL_FT_MainIxFile) || (m_uiFType==XL_FT_ReportFile)) )
            {
               while(*outsptr)
               {
                  if(
                     (*outsptr != TV_XM_SpCharSt /* '&' */) &&
                     (*outsptr != TV_XM_SpCharEnd /* ';' */)
                    )
                     retc=PutChar((KpChar)(toupper(*outsptr)), True);

                  outsptr++;
               }
            }
            else // if(xml_ent && ((m_uiFType==XL_FT_IxFile) || (m_uiFType==XL_FT_MainIxFile)) )
            {
               if(TvStrChr(TV_XM_CtrlChars, outch)==NULL)
               {
                  if(TvStrChr(lpszEols, outch)!=NULL)
                  {
// reikia Exploreriui - vien eilutes lauzymo nerodo kaip tarpo
//                   retc=PutChar(C_Spc, False);
// nereikia, tarpo nerodo siaip, nezinau kodel

                     if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False); // retc=PutStr(m_lpszIndentStr);
                  }
                  else
                  {
                     retc=GetCharPos(&char_pos);
                     if((char_pos==0) && SUCCEEDED(retc))
                     {
                        if(SUCCEEDED(retc)) retc = m_lpTagStack->GetCurTag(&cur_tag);
// KP_TRACE_("m_lpszIndentStr 2: %d", cur_tag);
                        if(
                           (cur_tag != C_Nul) &&
                           (cur_tag != HTM_TG_HTML) &&
                           (cur_tag != HTM_TG_HEAD) &&
                           (cur_tag != HTM_TG_STYLE) &&
                           (cur_tag != HTM_TG_SCRIPT) &&
                           (cur_tag != HTM_TG_PRE) &&
                           (cur_tag != HTM_TG_CODE) &&
                           (cur_tag != XL_Comment) &&
                           SUCCEEDED(retc)
                          )
                        {
                           retc = PutStr(m_lpszIndentStr);
                        }
                     }
#ifdef Debug
if(outch==C_z_Car)
outch=C_z_Car;
#endif
                     if(SUCCEEDED(retc))
                        retc=PutChar((KpChar)outch, False);
                  }
               }
               else
               {
                  if(
                     (m_plpszaXmlSpecCharTags==NULL) &&
                     (
                        (outch==(KpChar)TV_XM_SpCharSt) ||    // '&'
                        (outch==(KpChar)TV_XM_TagStartCh) ||  // '<'
                        (outch==(KpChar)TV_XM_TagEndCh)       // '>'
                     )
                    )
                     retc=PutChar(outch, False);
                  else
                     retc=KP_E_UNKN_CHR;
               }

               if(retc==KP_E_UNKN_CHR)
               {
 // no output of entities for XM_VERS_SGML files ??? - restored
                  if(xml_char /* && ((m_iXmlVers>=XM_VERS_HTML) || (!xml_ent)) */ )
                  {
                     retc=S_OK;
                     retc=PutStr(outsptr);
                  }
                  else if(outch == C_NullSpc) retc = S_OK; // Ievos PP11-12 darbas6.cpp po "fr << "" kaþkodël atsiranda
                  else
                  {
char str_buf[100];
sprintf(str_buf, "[%d]", outch);
                     retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, str_buf /* outsptr */, True, __FILE__, __LINE__, 0L);
                  }
               }

            } // else if((m_uiFType==XL_FT_IxFile) || (m_uiFType==XL_FT_MainIxFile))

         } // if(SUCCEEDED(retc))

      } // else if((outch>=XC_FirstDictTag) && (outch<XC_NumOfDictTags))

   } // if(outch && SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      retc=GetCharPos(&char_pos);
      if(bCheckIndex && (m_uiFType==XL_FT_IxFile) && (char_pos>m_iIxWdt) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
   }

   KP_DELETEA(out_str_i);
   KP_DELETEA(par_val_i);

#if FALSE // #ifdef Debug
if((iOutch & 0xfffe) == XC_Paragraph) // HTM_TG_P) // XC_Img)
{
m_lpTagStack->GetCurTag(&cur_tag);
m_lpTagStack->GetPrevTagPtr(&prev_ptr);
prev_ptr->GetCurTag(&prev_tag);
prev_ptr->GetPrevTagPtr(&prev_ptr);
prev_ptr->GetCurTag(&prev_prev_tag);
KP_TRACE_4("PutCharProc galas: iOutch:%d cur_tag:%d prev_tag:%d prev_prev_tag:%d", iOutch, cur_tag, prev_tag, prev_prev_tag);
}
else KP_TRACE_1("PutCharProc galas: iOutch:%d", iOutch);
#endif

// ----------------------
   KP_DELETEA(val_buf);
   KP_DELETEA(val_buf_dst);
   KP_DELETEA(val_buf_i);
   KP_DELETEA(val_buf_dst_i);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::PutCharExp(KpChar iOutch)
{
HRESULT retc=S_OK;
const KpChar *pnts;

   if((iOutch<0) || (iOutch>=C_CharSize0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=iaszUniStrs[iOutch];
      while(*pnts && SUCCEEDED(retc))
         retc=PutCharProc(*pnts++, NULL, False);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::PutKpStr(const KpChar *iazOutstr)
{
HRESULT retc=S_OK;
const KpChar *pnts;

   pnts=iazOutstr;

   while(*pnts && SUCCEEDED(retc))
      retc=PutCharProc(*pnts++, NULL, False);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::PutNumVal(const long lValue)
{
HRESULT retc=S_OK;
char form_buf[20];
unsigned char str_buf[TV_XL_MAX_IX_LEN+1];

   sprintf(form_buf, "%%%dld", TV_XL_NUM_LEN);
   sprintf((char *)str_buf, form_buf, lValue);
   if(strlen((const char *)str_buf) != TV_XL_NUM_LEN)
      retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
   str_buf[TV_XL_NUM_LEN]=Nul;
   if(SUCCEEDED(retc)) retc=PutStr(str_buf);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::CompleteIndexEntry(void)
{
HRESULT retc=S_OK;
int char_pos;

   retc=GetCharPos(&char_pos);
   while((char_pos<m_iIxWdt) && SUCCEEDED(retc))
   {
      retc=PutCharProc(C_Spc, NULL, True);
      if(SUCCEEDED(retc)) retc=GetCharPos(&char_pos);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SetBaseIndent(const unsigned char *lpszBaseIndent)
{
HRESULT retc=S_OK;

   if(lpszBaseIndent==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen((const char *)lpszBaseIndent)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) strcpy((char *)m_lpszBaseIndentStr, (const char *)lpszBaseIndent);

return(retc);
}


HRESULT TvXmlFile::GetBaseIndent(const unsigned char **plpszBaseIndentPtr)
{
HRESULT retc=S_OK;

   if(plpszBaseIndentPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *plpszBaseIndentPtr = m_lpszBaseIndentStr;

return(retc);
}


HRESULT TvXmlFile::SetIndent(const unsigned char *lpszIndent)
{
HRESULT retc=S_OK;

   if(lpszIndent==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen((const char *)lpszIndent)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_lpszBaseIndentStr[0]) strcpy(m_lpszIndentStr, lpszIndent);
      else
      {
         if(lpszIndent[0] == Lf) strcpy(m_lpszIndentStr, "\n");
         else m_lpszIndentStr[0] = Nul;
      }
   }

return(retc);
}


HRESULT TvXmlFile::IncIndent(void)
{
HRESULT retc=S_OK;

   if(strlen((const char *)m_lpszIndentStr)<TV_TAG_LEN-strlen(m_lpszBaseIndentStr)) // 3)
      strcat(m_lpszIndentStr, m_lpszBaseIndentStr); // "   ");
// else
//    retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


HRESULT TvXmlFile::DecIndent(void)
{
HRESULT retc=S_OK;
int cur_indent;

   cur_indent=strlen((const char *)m_lpszIndentStr)-strlen(m_lpszBaseIndentStr); // 3;
// if(cur_indent<1)
   if(cur_indent<0)
   {
//    cur_indent=1;
      cur_indent=0;
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }
   m_lpszIndentStr[cur_indent]=Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(m_lpLowLevelFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=m_lpLowLevelFile->GetCharPos(piCharPos);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetCharNum(long *plCharNum)
{
HRESULT retc=S_OK;

   if(plCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(m_lpLowLevelFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=m_lpLowLevelFile->GetCharNum(plCharNum);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::CompleteOpenTags(KpChar iTag)
{
HRESULT retc=S_OK;
KpChar cur_tag;
bool put_close_needed;

   retc=m_lpTagStack->GetCurTag(&cur_tag);

   while((cur_tag!=iTag) && SUCCEEDED(retc))
   {
      retc=m_lpTagStack->GetPutClose(&put_close_needed);
      if(SUCCEEDED(retc))
      {
         if(put_close_needed)
         {
            retc=PutCharProc((KpChar)(cur_tag+1), NULL, False);
            if(SUCCEEDED(retc)) retc=m_lpTagStack->GetCurTag(&cur_tag);
         }
         else
         {
            retc=PopTag(&m_lpTagStack, &cur_tag);
            if((m_lpTagStack==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
         }
      }
   }

return(retc);
}


// ================================================== low level text input
// --------------------------------------------------
HRESULT TvXmlFile::GetChar(KpChar *piInch, bool bCheckFeof)
{
HRESULT retc=S_OK;

   if(m_lpLowLevelFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((piInch==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piInch=C_Nul;

      if(m_iUnGetCnt>0) *piInch=m_iaUnGetBuf[--m_iUnGetCnt];
      else
      {
         retc = m_lpLowLevelFile->GetChar(piInch);
         if(bCheckFeof && (retc == KP_E_EOF))
            KpErrorProc.OutputErrorMessage(retc=KP_E_EOF, m_lpszFName, True, __FILE__, __LINE__, 0L);
      }
   }

// printf("%c\n", (char)(*piInch));

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::UnGetChar(unsigned char cChar)
{
return(UnGetChar((KpChar)cChar));
}

HRESULT TvXmlFile::UnGetChar(KpChar iChar)
{
HRESULT retc=S_OK;

   if(m_lpLowLevelFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_iUnGetCnt<TV_XL_UNGET_BUF_SIZ) m_iaUnGetBuf[m_iUnGetCnt++]=iChar;
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::Fscanf(const char *lpszFormat, void *pValue)
{
HRESULT retc=S_OK;

   if(m_lpRawFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fscanf(m_lpRawFile, lpszFormat, pValue);
      if(ferror(m_lpRawFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
      if(feof(m_lpRawFile) && SUCCEEDED(retc)) retc=KP_E_EOF;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetNumVal(long *plValue, bool bCheckFeof)
{
HRESULT retc=S_OK;

   if((m_lpLowLevelFile==NULL) || (m_lpRawFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((plValue==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plValue=0L;

      retc=Fscanf("%ld", plValue);
      if(bCheckFeof && retc==KP_E_EOF)
         retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SkipEol(void)
{
HRESULT retc=S_OK;
KpChar in_ch;

   do retc=GetChar(&in_ch, False);
   while((TvStrChr(lpszSpcEol, in_ch)!=NULL) && (in_ch!=C_Lf) && SUCCEEDED(retc)); // '\n'

   if(SUCCEEDED(retc))
      if(in_ch!=C_Lf) retc=UnGetChar(in_ch); // '\n'

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetCharSkipSpc(KpChar *piInch, bool bCheckFeof)
{
HRESULT retc=S_OK;

   do retc=GetChar(piInch, bCheckFeof);
   while((TvStrChr(lpszSpcEol, *piInch)!=NULL) && SUCCEEDED(retc));

return(retc);
}


// ================================================== text input with XML tag processing
HRESULT TvXmlFile::TestTagEnd(const unsigned char *lpszTagEndStr, bool *pbFound, bool bUngetFl)
{
HRESULT retc = S_OK;
int ii, jj, ll;
KpChar in_ch;

   if(((lpszTagEndStr == NULL) || (pbFound == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbFound = False;

      ll = strlen(lpszTagEndStr);
      if(ll < 1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      else if(ll == 1) *pbFound = True;
   }

   if((!*pbFound) /* (ll > 1) */ && SUCCEEDED(retc))
   {
      for(ii = 1; ii < ll; ii++)
      {
         retc=GetChar(&in_ch, True);
         if((in_ch != lpszTagEndStr[ii]) && SUCCEEDED(retc)) break;
      }

      if(SUCCEEDED(retc))
      {
         if(ii >= ll)
         {
            *pbFound = True;
            ii = ll - 1;
         }
         if(bUngetFl) retc=UnGetChar(in_ch);
      }

      if(bUngetFl && SUCCEEDED(retc)) for(jj = ii - 1; (jj >= 1) && SUCCEEDED(retc); jj--)
         retc=UnGetChar(lpszTagEndStr[jj]);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::GetCharProc
(
KpChar *piInch,
XmlTagPars **ppTagParsPtr,
bool bCheckFeof,
bool bProcSpcEol
)
{
HRESULT retc=S_OK;
KpChar in_ch;
KpChar iin_ch;
unsigned char tag_buf[TV_TAG_LEN+1];
// unsigned char *par_buf = null;
KpChar *par_buf = NULL;
unsigned char *style_str = null;
int tag_buf_ix;
int tag_ix;
bool end_of_pars;
bool val_ready;  // flag of presence of parameter value
bool val_end;
unsigned char delim;
XmlTagPars *tag_par = NULL;
XmlTagPars *style_pars = NULL;
bool comment_fl;
bool comment_pending;
bool comment_end_fl;
UC_Modes enc_mode;
int ctbl;
KpChar cur_tag = C_Nul;
KpChar prev_tag = C_Nul;
const unsigned char *pnts;
unsigned char *pntd;
int uni_ch;
int jj;
bool no_push = False;
// unsigned char ch;
// bool single_tag=False;
const unsigned char *tag_name = (const unsigned char *)"";
const unsigned char *tag_end_name = (const unsigned char *)"";
int ll;

   if(((piInch==NULL) || (ppTagParsPtr == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(m_bUnGetChProcCnt>0)
   {
      *piInch = m_iUnGetChProcBuf[m_bUnGetChProcCnt-1];
      *ppTagParsPtr = m_pUnGetChPars[m_bUnGetChProcCnt-1];
      m_pUnGetChPars[m_bUnGetChProcCnt-1] = NULL;
      m_bUnGetChProcCnt--;
   }
   else
   {

   if(SUCCEEDED(retc)) *piInch=C_Nul;
   if(ppTagParsPtr != NULL) *ppTagParsPtr = NULL;

   if((m_lpLowLevelFile == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

// KP_NEWA(par_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);
   KP_NEWA(par_buf, KpChar, KP_MAX_FILE_LIN_LEN + 1);

// !!! tag stack processing
// !!! encoding tables

   if(SUCCEEDED(retc)) retc = GetChar((KpChar *)&in_ch, bCheckFeof);

#ifdef Debug
if(in_ch==C_Amp)
in_ch=C_Amp;
#endif

// Ctrl/Z - end of file
   if((in_ch==(Eof /* Ctrl Z */)) && (m_uiFType==XL_FT_DataFile) && SUCCEEDED(retc))
   {
      if(bCheckFeof)
         retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, m_lpszFName, True, __FILE__, __LINE__, 0L);
      else
         retc=KP_E_EOF;
   }

// multiple spaces and eol's to one space
   if(bProcSpcEol && SUCCEEDED(retc))
   {
      if((m_uiFType==XL_FT_DataFile) && (TvStrChr(lpszSpcEol, in_ch)!=NULL))
      {
         do retc=GetChar(&in_ch, bCheckFeof);
         while((TvStrChr(lpszSpcEol, in_ch)!=NULL) && SUCCEEDED(retc));
         if(SUCCEEDED(retc))
         {
            retc=UnGetChar(in_ch);
            in_ch=C_Spc;
         }
      }
   }

#ifdef Debug
if(in_ch == C_Cr)
in_ch = C_Cr;
#endif

   if((in_ch == C_Cr) && SUCCEEDED(retc)) if((m_uiFType==XL_FT_DataFile) /* && (!m_lpLowLevelFile->m_bBinFlg) */)
   {
      retc=GetChar(&in_ch, bCheckFeof);
      if((in_ch != C_Lf) && SUCCEEDED(retc))
      {
         retc=UnGetChar(in_ch);
         in_ch=C_Lf;
      }
   }

// check comment end tag
   comment_end_fl = False;
   if((in_ch=='-') && (m_uiFType==XL_FT_DataFile) && SUCCEEDED(retc))
      retc = TestTagEnd(XM_COMMENT_END_STR_STRICT, &comment_end_fl, True);

   if(SUCCEEDED(retc))
   {
// XML tag processing
      if(((in_ch==(KpChar)TV_XM_TagStartCh /* '<' */) && (m_uiFType==XL_FT_DataFile)) || comment_end_fl)
      {
// set default low level file code table for tag input
         if(SUCCEEDED(retc))
            retc=m_lpLowLevelFile->GetEncoding(&enc_mode, &ctbl);

         if(SUCCEEDED(retc)) retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);

// --------
         tag_buf_ix = 0;
         comment_fl = False;
         comment_pending = True;
         ll = strlen(XM_COMMENT_START_STR);

         tag_buf[tag_buf_ix++]=(int)in_ch;
         if(SUCCEEDED(retc)) do
         {
            retc=GetChar(&in_ch, True);
            if(SUCCEEDED(retc))
            {
               if((in_ch<0) || (in_ch>=KPT_Ctbsiz))
                  retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);

// atpa_ástam komentaro prad_ià "<!--"
#if TRUE // FALSE
               if((!comment_fl) && SUCCEEDED(retc))
               {
                  if(tag_buf_ix < ll)
                  {
                     if(in_ch != XM_COMMENT_START_STR[tag_buf_ix]) comment_pending = False;
                  }
                  else comment_fl = comment_pending;
               }

// tikrinam <!--[if ...]>...<![endif]-->
               if(comment_fl && (in_ch == '[') && SUCCEEDED(retc))
                  comment_pending = comment_fl = False;
#endif
               if(tag_buf_ix<TV_TAG_LEN-1) tag_buf[tag_buf_ix++]=(int)in_ch;
               else
                  if(SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
            }
// skaitom iki '>', tarpo arba
// kol randam komentaro prad_ià "<!--" (komentaras gali prasidëti ið karto be tarpo)
         } while((in_ch != (KpChar)TV_XM_TagEndCh /* '>' */) && (TvStrChr(lpszSpcEol,in_ch) == NULL) && (!comment_fl) &&
                  SUCCEEDED(retc));

// system tags
         tag_name = (const unsigned char *)"";
         tag_end_name = (const unsigned char *)"";

         if((tag_buf_ix <= 0) && SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            tag_buf[--tag_buf_ix]=Nul;
            if(tag_buf_ix>0) if(tag_buf[tag_buf_ix-1] == TV_XM_EndTagIndCh) // '/' prieð paskutiná '>' - pavienis tagas
            {
               if(in_ch != (KpChar)TV_XM_TagEndCh) //  '>'
                  retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  tag_buf[--tag_buf_ix]=Nul;
                  retc = UnGetChar(in_ch);
                  in_ch = TV_XM_EndTagIndCh; // '/'
               }
            }
         }

         if(SUCCEEDED(retc))
         {
            retc = GetTagIndex(&tag_ix, tag_buf, plpszaXmlSysTags);

            if(SUCCEEDED(retc))
            {
               *piInch=(KpChar)(XL_FirstSysTag + tag_ix);
               tag_name = plpszaXmlSysTags[tag_ix];
               tag_end_name = plpszaXmlSysTags[(tag_ix & (~1))+1];

// jau nustatyta tago ávedimo metu
// //          if(strcmp(plpszaXmlSysTags[tag_ix], XM_COMMENT_START_STR)==0) comment_fl=True;
//             if(*piInch == XL_Comment) comment_fl=True;
            }
            else if(retc==TV_E_UNKN_TAG)
            {
// local tags
               retc=S_OK;
               if(SUCCEEDED(retc))
               {
                  retc = GetTagIndex(&tag_ix, tag_buf, m_lpszaTagNames);
                  if(retc == TV_E_UNKN_TAG) // KP_E_KWD_NOT_FOUND
                  {
// neradom tago, kuriam naujà
                     retc = KpErrorProc.OutputErrorMessage(retc, tag_buf, m_lpszaTagNames != m_lpszaTagNamesArray, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                        if(tag_buf[1] == TV_XM_EndTagIndCh) // '/'   // ne_inomas tagas prasideda nuo u_daranèio
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                     {
                        ll = strlen(tag_buf);
                        if(2 * ll + 6 >= TV_XL_TAG_BUF_SIZE - (m_lpszaTagNamesBufPtr - m_lpszaTagNamesBuf))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc))
                     {
                        tag_ix = GetLastTag() /* m_iLastDictTagCurrent */ - m_iFirstDictTag;
                        if(tag_ix >= XL_MaxNumOfTags-1)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc))
                     {
                        strcpy(m_lpszaTagNamesBufPtr, tag_buf);
                        m_lpszaTagNamesArray[tag_ix] = m_lpszaTagNamesBufPtr;

                        m_lpszaTagNamesBufPtr += ll;
                        *m_lpszaTagNamesBufPtr++ = TV_XM_TagEndCh; // '>'
                        *m_lpszaTagNamesBufPtr++ = Nul; // paliekam vietos galimam pavienio tago galui ".../>"
                        *m_lpszaTagNamesBufPtr++ = Nul;

                        m_lpszaTagNamesArray[tag_ix + 1] = m_lpszaTagNamesBufPtr;
                        *m_lpszaTagNamesBufPtr++ = tag_buf[0]; // TV_XM_TagStartCh; // '<'
                        *m_lpszaTagNamesBufPtr++ = TV_XM_EndTagIndCh; // '/'
                        if(tag_buf[0])
                        {
                           strcpy(m_lpszaTagNamesBufPtr, tag_buf+1);
                           m_lpszaTagNamesBufPtr += ll - 1;
                        }
                        *m_lpszaTagNamesBufPtr++ = TV_XM_TagEndCh; // '>'
                        *m_lpszaTagNamesBufPtr++ = Nul;

                        m_iLastDictTagCurrent += 2;
                     }
                  }
               }

#ifdef Debug
if((KpErrorProc.lMsgPar==4250) && (strcmp(tag_buf, "<reikðmë")==0)) // !!!
KpErrorProc.lMsgPar=4250;
#endif

               if(SUCCEEDED(retc))
               {
                  *piInch=(KpChar)(m_iFirstDictTag + tag_ix);
                  tag_name = m_lpszaTagNames[tag_ix];
                  tag_end_name = m_lpszaTagNames[(tag_ix & (~1))+1];
               }

            } // else if(retc==TV_E_UNKN_TAG)

            else
               retc=KpErrorProc.OutputErrorMessage(retc, tag_buf, True, __FILE__, __LINE__, 0L);

         } // if(SUCCEEDED(retc))


// tag parameters
         if(
            (in_ch!=(KpChar)TV_XM_TagEndCh) && // '>'
            (in_ch!=(KpChar)TV_XM_EndTagIndCh) && // '/'
            (!comment_fl) && // komentaro tago vidus jau ne fiktyvus parametras, o tago turinys
            SUCCEEDED(retc)
           )
         {
            end_of_pars=False;
            if(SUCCEEDED(retc)) do
            {
               tag_buf_ix=0;
               do retc=GetCharSkipSpc(&in_ch, True);
               while(in_ch==C_Comma); // ',' // kam to reikia???

// parameter name
               if(SUCCEEDED(retc))
               {
                  if(isalpha(in_ch) || (in_ch == C_Colon) || // ':'
                     ((in_ch >= KPT_FirstKptChar) && (in_ch < KPT_Ctbsiz)) ||
                     (
                        (TvIsRealDigit(in_ch) || (TvStrChr(lpszMathOperators, in_ch)!=NULL)) &&
                        ((*piInch == XL_IfComment) || (*piInch == XL_If))
                     ) // loginiø formuliø operatoriai ir operandai
//                   || comment_fl // komentaro tago vidus jau ne fiktyvus parametras, o tago turinys
                     )
                  {
                     val_end=False;
                     do
                     {
                        if(tag_buf_ix < TV_TAG_LEN-1) tag_buf[tag_buf_ix++] = (int)in_ch;
                        else retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

                        if(SUCCEEDED(retc)) retc=GetChar(&in_ch, True);

                        if(SUCCEEDED(retc))
                        {
// komentaro tago vidus jau ne fiktyvus parametras, o tago turinys
//                         if(comment_fl) val_end = ((TvStrChr(lpszSpcEol, in_ch)!=NULL) || (in_ch == '-')); // galas gali bûti ir be tarpo
//                         else
                              val_end=
                              (
                                 (!isalnum(in_ch)) &&
                                 (in_ch != C_Colon) && // ':'
                                 ((in_ch<KPT_FirstKptChar) || (in_ch>=KPT_Ctbsiz)) &&
                                 (in_ch!=C_Dash) // '-'
                              );
                        }
                     } while((!val_end) && SUCCEEDED(retc));
                     if((TvStrChr(lpszSpcEol, in_ch)!=NULL) && SUCCEEDED(retc)) retc=GetCharSkipSpc(&in_ch, True);
                  }
                  else
                     if(
                        (in_ch!=(KpChar)TV_XM_TagTextValCh) && /* '\"' */
                        (in_ch!=(KpChar)TV_XM_TagVersValCh) /* '\'' */
                       )
                        end_of_pars=True;
               }
               tag_buf[tag_buf_ix]=Nul;
               strlwr(tag_buf);

#ifdef Debug
// KP_TRACE_1("TvXmlFile::GetCharProc: tag_buf: %s", tag_buf);
// if(comment_fl) KP_TRACE_1("TvXmlFile::GetCharProc: comment word: %s", tag_buf);
#endif
               tag_buf_ix=0;

// komentaro tago vidus jau ne fiktyvus parametras, o tago turinys
#if FALSE
// test comment end
               if(comment_fl)
               {
                  if((in_ch==C_Dash) && SUCCEEDED(retc))
                     retc = TestTagEnd(XM_COMMENT_END_STR_STRICT, &end_of_pars, True); // "-->"
                  if((!end_of_pars) && SUCCEEDED(retc)) retc=UnGetChar(in_ch);
               }
               else // if(comment_fl)
#endif
               {
// chars before parameter value
                  val_ready=False;
                  delim=Nul;
                  if((!end_of_pars) && SUCCEEDED(retc)) switch(in_ch)
                  {
                  case TV_XM_TagValCh: /* '=' */
                     retc=GetCharSkipSpc(&in_ch, True);
                     if(SUCCEEDED(retc))
                     {
                        if((in_ch==(KpChar)TV_XM_TagTextValCh /* '\"' */) || (in_ch==(KpChar)TV_XM_TagVersValCh /* '\'' */))
                        {
                           delim=(unsigned char)in_ch;
                           retc=GetChar(&in_ch, True);
                        }
                        else
                        {
                           if(m_iXmlVers>=XM_VERS_XML)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                        }
                     }
                     val_ready=SUCCEEDED(retc);
                     break;

                  case TV_XM_TagTextValCh: /* '\"' */
                  case TV_XM_TagVersValCh: /* '\'' */
                     if(strlen(tag_buf)==0)
                     {
                        delim=(unsigned char)in_ch;
                        retc=GetChar(&in_ch, True);
                        val_ready=SUCCEEDED(retc);
                        break;
                     }
                  default:
                     retc=UnGetChar(in_ch);
                     break;
                  }

// parameter value
                  if((!end_of_pars) && val_ready && SUCCEEDED(retc))
                  {
                     val_end=False;
                     do
                     {
// end of parameter value?
                        switch(delim)
                        {
                        case TV_XM_TagTextValCh: /* '\"' */
                           if(in_ch==(KpChar)TV_XM_TagTextValCh) val_end=True;
                           break;
                        case TV_XM_TagVersValCh: /* '\'' */
                           if(in_ch==(KpChar)TV_XM_TagVersValCh) val_end=True;
                           break;
                        case Nul:
                           if(TvStrChr(lpszSpcEol, in_ch)!=NULL) val_end=True;
                           if(
                              (in_ch==C_Comma) || // ','
//                            (in_ch==C_Dash) || // '-'
                              (in_ch==C_Quest) || // '?'
                              (in_ch==(KpChar)TV_XM_TagEndCh /* '>' */)
                             )
                           {
                              val_end=True;
                              retc=UnGetChar(in_ch);
                           }
                           break;
                        }
// get next value char
                        if((!val_end) && SUCCEEDED(retc))
                        {
                           if(tag_buf_ix<KP_MAX_FILE_LIN_LEN-1)
                           {
#if FALSE
                              in_ch=TvToLat(in_ch);
                              if((in_ch<0) || (in_ch>=KPT_Ctbsiz))
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//                            retc=KptCharDecode(&ch, in_ch, m_iDefCodeTable);
//                            if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
//                               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);

                              if(SUCCEEDED(retc)) par_buf[tag_buf_ix++] = (unsigned char)in_ch;
#endif
                              if(SUCCEEDED(retc)) par_buf[tag_buf_ix++] = in_ch;
                           }
                           else retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

                           if(SUCCEEDED(retc)) retc=GetChar(&in_ch, True);
                        }

                     } while((!val_end) && SUCCEEDED(retc));

                  } // if((!end_of_pars) && val_ready && SUCCEEDED(retc))

               } // else // if(comment_fl)

               par_buf[tag_buf_ix] = C_Nul;
//             strlwr(par_buf);

// parse style parameter
               if(SUCCEEDED(retc)) if(strcmp(tag_buf, "style") == 0)
               {
                  KP_NEWA(style_str, unsigned char, TvKpStrLen(par_buf) + 1);

                  if(SUCCEEDED(retc))
                  {
                     retc = KptStrDecode(style_str, par_buf, 1);
#ifdef Debug
// cout << "===>>> " << style_str << endl;

// if(strcmp(style_str, "width:457.25pt;padding:0cm 5.4pt 0cm 5.4pt") == 0)
// retc = S_OK;
#endif
                     if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
                        retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }

                  if(SUCCEEDED(retc))
                     retc = ParseStyleParameters(&style_pars, style_str, NULL);

                  KP_DELETEA(style_str);
               }

// put parameter to return object
               if(SUCCEEDED(retc)) if(((strlen(tag_buf) > 0) || (TvKpStrLen(par_buf) > 0) /* || (strlen(par_buf) > 0) */))
               {
                  if(tag_par == NULL)
                  {
                     if(style_pars != NULL) KP_NEWO(tag_par, XmlTagPars(tag_buf, style_pars, NULL))
                     else KP_NEWO(tag_par, XmlTagPars(tag_buf, par_buf, NULL));
                  }
                  else
                  {
                     if(style_pars) retc = tag_par->AddParPar(tag_buf, style_pars);
                     else retc = tag_par->AddKpTextPar(tag_buf, par_buf);
                  }
               }

               KP_DELETE(style_pars);

            } while((!end_of_pars) && SUCCEEDED(retc));

         } // if((in_ch!=TV_XM_TagEndCh /* '>' */) && SUCCEEDED(retc))

// rest tag chars
         if(SUCCEEDED(retc)) switch(in_ch)
         {
// komentaro tago vidus jau ne parametras, o tago turinys
// komentaro galas apdorojamas kaip atskiras tagas
#if FALSE
         case '-':
//          retc=GetChar(&in_ch, True);
//          if((in_ch!=C_Dash) && SUCCEEDED(retc)) // '-'
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
//          if(SUCCEEDED(retc)) retc=GetChar(&in_ch, True);
//          if((in_ch!=(KpChar)TV_XM_TagEndCh /* '>' */) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc = TestTagEnd(XM_COMMENT_END_STR_STRICT, &comment_fl, False); // "-->"
            if((!comment_fl) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
//             if(
//                (tag_name[0]!=TV_XM_TagStartCh /* '<' */) ||
//                (tag_name[1]!='!') ||
//                (tag_name[2]!='-') ||
//                (tag_name[3]!='-')
//               )
               if(*piInch != XL_Comment)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
#endif

         case '?':
            retc=GetChar(&in_ch, True);
            if((in_ch!=(KpChar)TV_XM_TagEndCh /* '>' */) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
               if(tag_name==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(strlen(tag_name)<2)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(
                  (tag_name[0]!=TV_XM_TagStartCh /* '<' */) ||
                  (tag_name[1]!='?')
                 )
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;

         case ']':
            retc=GetChar(&in_ch, True);
            if((in_ch!=(KpChar)TV_XM_TagEndCh /* '>' */) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
               if(tag_name==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(strlen(tag_name)<2)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(
                  (tag_name[0]!=TV_XM_TagStartCh /* '<' */) ||
                  (tag_name[1]!='[')
                 )
               {
//                if(strlen(tag_name)<5)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
//                if(SUCCEEDED(retc))
//                   if(
//                      (tag_name[0]!=TV_XM_TagStartCh /* '<' */) ||
//                      (tag_name[1]!='!') ||
//                      (tag_name[2]!='-') ||
//                      (tag_name[3]!='-') ||
//                      (tag_name[4]!='[')
//                     )
                  if((*piInch != XL_IfComment) && (*piInch != XL_If))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                 }
            break;

         case TV_XM_EndTagIndCh: // '/'  - single tag with parameters <.../>
            retc=GetChar(&in_ch, True);
            if((in_ch!=(KpChar)TV_XM_TagEndCh /* '>' */) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               pnts = tag_name;
               if(pnts==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc))
               if(strlen(pnts)<2)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               pnts += strlen(pnts);
               while(pnts > tag_name)
               {
                  if(TvStrChr(lpszSpcEol, *(pnts - 1)) == NULL) break;
                  pnts--;
               }
               if(pnts <= tag_name)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, tag_name, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) if(*(--pnts) != TV_XM_TagEndCh) // '>'
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, tag_name, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) if(pnts <= tag_name)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, tag_name, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(*(--pnts) != TV_XM_EndTagIndCh) // '/'
               {
// paprastas laukas kaip pavienis:
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                  if(m_lpszaTagNames != m_lpszaTagNamesArray) // stacionarûs tagai
                     retc = UnGetCharProc((KpChar)(*piInch+1), NULL);
                  else
                  {
                     pnts++;
                     if((pnts + 3 != m_lpszaTagNamesArray[tag_ix+1]) || (*(pnts + 1))) // jei sukurtas tagas, tai <...>00</...>0 - palikta vieta áraðyti "/>"
                     {
//                      if(pnts + 2 != m_lpszaTagNamesArray[tag_ix+1]) // jei tagas nesukurtas, ið stacionarios dalies, tai <...>0</...>0
//                         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, tag_name /* m_lpszaTagNamesArray[tag_ix+1] */, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc))
                           retc = UnGetCharProc((KpChar)(*piInch+1), NULL); // tagas ið stacionarios dalies, ne naujai sukurtas

// PutLogMessage_5(">>>--- nesukurtas %lx %s %s %lx %s", m_lpszaTagNamesArray[tag_ix+1], m_lpszaTagNamesArray[tag_ix+1], m_lpszaTagNamesArray[tag_ix+1]+1, pnts, pnts);
                     }
                     else // tagas su dviem nuliais, naujai sukurtas - áraðom "/>"
                     {
                        pntd = (unsigned char *)pnts;

                        *pntd++ = TV_XM_EndTagIndCh; // '/'
                        *pntd++ = TV_XM_TagEndCh; // '>'
                        *pntd++ = Nul;

//                      m_lpszaTagNamesArray[tag_ix+1][0] = Nul; // iðvalom uþdarantá tagà
                        *pntd++ = Nul;

// PutLogMessage_0(">>>--- sukurtas");
                     }
                  }

                  no_push=True;
               }
//             else single_tag=True;
            }

            break;

         case TV_XM_TagEndCh: /* '>' */
            break;

         default:
            if(!comment_fl) // komentaro tagas dabar baigiasi bet kokiu simboliu: "<!--"
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, GetTagName(*piInch), True, __FILE__, __LINE__, in_ch);
            break;
         }

// tag stack processing
         cur_tag=*piInch;
         if(
            (
               !(
                  ((cur_tag >= m_iFirstDictTag) && (!CheckLastTag(cur_tag) /* cur_tag < m_iLastDictTagCurrent */)) ||
                  ((cur_tag >= XL_FirstSysTag) && (cur_tag < XL_LastSysTag))
                )
            ) &&
            SUCCEEDED(retc)
           )
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if((!no_push) && SUCCEEDED(retc))
         {
            if(strcmp((const char *)tag_end_name, "")!=0)
            {
               if(((*piInch) & 0x01) == 0) retc = PushTag(&m_lpTagStack, (*piInch), NULL, 0);
               else
               {
#ifdef Debug
// m_lpTagStack->GetCurTag(&cur_tag);
// if(cur_tag != ((*piInch) & (~0x01)))
// KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
#endif
                  retc = PopTag(&m_lpTagStack, &cur_tag);
                  if(SUCCEEDED(retc))
                  {
                     if(cur_tag != ((*piInch) & (~0x01)))
                     {
// KP_TRACE_2("GetCharProc: cur_tag:%d *piInch:%d", cur_tag, *piInch);
char str_buf[100];
                        sprintf(str_buf, "%d %s %d %s", cur_tag, GetTagName(cur_tag), *piInch, GetTagName(*piInch));
                        /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, str_buf, True, __FILE__, __LINE__, 0L);

// bandom gelbët - suveiks, jei tik trûksta uþdaranèio tago
                        if(SUCCEEDED(retc))
                        {
                           iin_ch = *piInch;
                           retc =  UnGetCharProc(*piInch, tag_par);
                        }
                        KP_DELETE(tag_par);

                        if(SUCCEEDED(retc)) (*piInch) = cur_tag | 0x01; // imituojam uþdarantá tagà

// iðimam dar vienà tagà ið steko – dabar ten dar vienu per daug – GetCharProc() po UnGetCharProc() steko neprocesina
                        if(SUCCEEDED(retc)) retc = PopTag(&m_lpTagStack, &cur_tag);
                        if(SUCCEEDED(retc)) if(cur_tag != (iin_ch & (~0x01))) // if(cur_tag != ((*piInch) & (~0x01)))
                        {
                           sprintf(str_buf, "%d %s %d %s", cur_tag, GetTagName(cur_tag), iin_ch, GetTagName(iin_ch)); // *piInch, GetTagName(*piInch));
                           /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, str_buf, True, __FILE__, __LINE__, 0L);
                        }

//                      if(SUCCEEDED(retc)) retc = PushTag(&m_lpTagStack, (*piInch) & (~0x01), NULL, 0); // GetCharProc() po UnGetCharProc() steko neprocesina

                     }
                     else // if(SUCCEEDED(retc))
                     {
                        if(m_lpTagStack != NULL) retc = m_lpTagStack->GetCurTag(&cur_tag);
                        else
                        {
                           cur_tag = (KpChar)((*piInch)&(~1));
                           retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                        }
                     }

                  } // if(SUCCEEDED(retc))

               } // else // if(((*piInch) & 0x01) == 0)

            } // if(strcmp((const char *)tag_end_name, "")!=0)
            else
            {
// paviene gaire
               if(m_lpTagStack!=NULL) retc=m_lpTagStack->GetCurTag(&cur_tag);
               else
               {
                  cur_tag=(KpChar)((*piInch)&(~1));
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
               }
            }
         }

// return tag parameters
         if((ppTagParsPtr != NULL) && SUCCEEDED(retc))
         {
            KP_ASSERT(*ppTagParsPtr == NULL, KP_E_DOUBLE_CALL, null, True);
            *ppTagParsPtr = tag_par;
         }
         else KP_DELETE(tag_par);
         tag_par = NULL;

// test parameters of some common tags
         if(SUCCEEDED(retc)) retc = TestPars(*piInch, *ppTagParsPtr);

// set low level file code table
         if(SUCCEEDED(retc))
            retc=m_lpLowLevelFile->GetEncoding(&enc_mode, &ctbl);

         if(
            ((cur_tag < m_iFirstDictTag) || (CheckLastTag(cur_tag) /* cur_tag >= m_iLastDictTagCurrent */)) &&
            ((cur_tag < XL_FirstSysTag) || (cur_tag >= XL_LastSysTag)) &&
            (cur_tag != 0) && SUCCEEDED(retc)
           )
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, cur_tag);
         if(SUCCEEDED(retc))
         {
            if(cur_tag != 0)
            {
               ctbl = GetTagCodeTable(cur_tag) /* m_piaCodeTables[cur_tag - m_iFirstDictTag] */;
               if(ctbl >= 0)
                  retc = m_lpLowLevelFile->SetEncoding(enc_mode, ctbl);
               else if(ctbl == KPT_UpCodeTable)
               {
TvXmlTagStack *tag_stack_ptr;
                  tag_stack_ptr = m_lpTagStack;
                  while((tag_stack_ptr != NULL) && SUCCEEDED(retc))
                  {
                     retc = tag_stack_ptr->GetPrevTag(&prev_tag);
                     if(prev_tag == 0) break;
                     else
                     {
                        if(GetTagCodeTable(prev_tag) /* m_piaCodeTables[prev_tag - m_iFirstDictTag] */ != KPT_UpCodeTable) break;
                        else
                           retc = tag_stack_ptr->GetPrevTagPtr(&tag_stack_ptr);
                     }
                  }
                  if(SUCCEEDED(retc))
                  {
//                   if(prev_tag != 0)
                        retc=m_lpLowLevelFile->SetEncoding(enc_mode, GetTagCodeTable(prev_tag) /* m_piaCodeTables[prev_tag - m_iFirstDictTag] */);
//                   else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
                  }
               }
               else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
            }
            else retc=m_lpLowLevelFile->SetEncoding(enc_mode, m_iDefCodeTable);
         }

// -------------
      }
      else // if((in_ch==TV_XM_TagStartCh /* '<' */) && (m_uiFType==XL_FT_DataFile))
      {

// spec. character
         if((in_ch==(KpChar)TV_XM_SpCharSt /* '&' */) && (m_uiFType==XL_FT_DataFile))
         {
            if(m_iXmlVers==XM_VERS_SGML_TAGE) *piInch=in_ch;
            else
            {
               tag_buf_ix=0;
//             if((in_ch<0) || (in_ch>=KPT_Ctbsiz))
//                retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
               tag_buf[tag_buf_ix++]=(int)in_ch;
               if(SUCCEEDED(retc)) do
               {
                  retc=GetChar(&in_ch, True);
                  if(SUCCEEDED(retc))
                  {
                     if((in_ch<0) || (in_ch>=KPT_Ctbsiz))
                        retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
                     if(tag_buf_ix<TV_TAG_LEN-1) tag_buf[tag_buf_ix++]=(int)in_ch;
                     else
                        if(SUCCEEDED(retc))
                           retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
                  }
               } while((in_ch!=(KpChar)TV_XM_SpCharEnd /* ';' */) && SUCCEEDED(retc));

               if(SUCCEEDED(retc))
               {
                  tag_buf[tag_buf_ix]=Nul;
                  retc = SearchSpecChar(&iin_ch, tag_buf, m_plpszaXmlSpecCharTags);
               }
               if((retc==KP_E_UNKN_CHR) || (retc==KP_E_KWD_NOT_FOUND))
               {
// ------------ unicode character
                  if((tag_buf[1]==TV_XM_UniChST) || // '#'
                     (tag_buf[1]=='U'))   // benjamin/hop spec. unicodiniu simboliu pazymejimai,
                                          // atitinka &#x...;: &U2212; = &#x2212;
                  {
                     retc=S_OK;

                     if(tag_buf[1]=='U')
                     {
                        sscanf((const char *)tag_buf+2, "%x", &uni_ch);
                        pnts=tag_buf+2;
                        while(TvIsHexDigit((KpChar)*pnts)) pnts++;
                     }
                     else
                     {
                        if(tag_buf[2]=='x')
                        {
                           sscanf((const char *)tag_buf+3, "%x", &uni_ch);
                           pnts=tag_buf+3;
                           while(TvIsHexDigit((KpChar)*pnts)) pnts++;
                        }
                        else
                        {
                           sscanf((const char *)tag_buf+2, "%d", &uni_ch);
                           pnts=tag_buf+2;
                           while(isdigit(*pnts)) pnts++;
                        }
                     }

                     if((*pnts++)!=TV_XM_SpCharEnd)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                     {
                        iin_ch=C_Unkn;
                        for(jj=0; jj<C_CharSize0; jj++)
                           if(iaUniChars[jj]==uni_ch)
                           {
                              iin_ch=(KpChar)jj;
                              break;
                           }
                        if(iin_ch==C_Unkn)
                        {
                           iin_ch=C_Quest; // '?'
                           retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
                        }
                     }
                  }
                  else // if((tag_buf[1]==TV_XM_UniChST) ...
                  {
                     retc=KpErrorProc.OutputErrorMessage(retc, tag_buf, True, __FILE__, __LINE__, 0L); // tag_buf[1] /* iin_ch */);
                     iin_ch=C_Quest; // '?'
                  }
               }

               if(SUCCEEDED(retc) || (retc==KP_E_UNKN_CHR)) *piInch=iin_ch;

            } // else // if(m_iXmlVers==XM_VERS_SGML_TAGE)

         } // if((in_ch==TV_XM_SpCharSt /* '&' */) && (m_uiFType==XL_FT_DataFile))

// ordinary char
         else
         {
XmlVersions vers = XM_NO_VERS;
            if(SUCCEEDED(retc)) retc = GetVersion(&vers);

KpChar father_tag = C_Nul;
            if((m_lpTagStack != NULL) && SUCCEEDED(retc))
               retc = m_lpTagStack->GetCurTag(&father_tag);
// !!!!!
//          if(m_iXmlVers==XM_VERS_SGML_TAGE) // !!!
            if(
               (father_tag != XC_UsNoteSrc) && (father_tag != XC_UsNoteDst) && (father_tag != XC_TechNote) &&
               (father_tag != XC_CodeExample) && (father_tag != XC_CodeExampleInline) && (father_tag != XC_Special) &&
               (father_tag != HTM_TG_SCRIPT) && (father_tag != HTM_TG_PRE) && (father_tag != HTM_TG_CODE) &&
               ((father_tag < XG_FirstGrpTag) || (father_tag >= XG_LastGrpTag))
              )
            {

// ------------------------------------------------------ 'x
               if(
                  (
                     (in_ch == C_Apost) ||
                     ((in_ch == C_Plus) && XM_IS_VERS_SGML(vers)) ||
                     (in_ch == C_Acute)
                  ) && // '\''
                  (!XM_IS_VERS_HTML(vers)) &&
                  SUCCEEDED(retc)
                 )
               {
PutLogMessage_("TvXmlFile::GetCharProc() +++++ ");
                  if(SUCCEEDED(retc)) retc=GetChar(&iin_ch, True);
                  if(SUCCEEDED(retc)) switch(iin_ch)
                  {
                  case C_A:      in_ch = C_A_Acute;      break;
                  case C_A_Ogon: in_ch = C_A_Ogon_Acute; break;
                  case C_E:      in_ch = C_E_Acute;      break;
                  case C_E_Ogon: in_ch = C_E_Ogon_Acute; break;
                  case C_E_Adot: in_ch = C_E_Adot_Acute; break;
                  case C_I:      in_ch = C_I_Acute;      break;
                  case C_I_Ogon: in_ch = C_I_Ogon_Acute; break;
                  case C_Y:      in_ch = C_Y_Acute;      break;
                  case C_O:      in_ch = C_O_Acute;      break;
                  case C_U:      in_ch = C_U_Acute;      break;
                  case C_U_Ogon: in_ch = C_U_Ogon_Acute; break;
                  case C_U_Macr: in_ch = C_U_Macr_Acute; break;
                  case C_a:      in_ch = C_a_Acute;      break;
                  case C_a_Ogon: in_ch = C_a_Ogon_Acute; break;
                  case C_e:      in_ch = C_e_Acute;      break;
                  case C_e_Ogon: in_ch = C_e_Ogon_Acute; break;
                  case C_e_Adot: in_ch = C_e_Adot_Acute; break;
                  case C_i:      in_ch = C_i_Acute;      break;
                  case C_i_Ogon: in_ch = C_i_Ogon_Acute; break;
                  case C_y:      in_ch = C_y_Acute;      break;
                  case C_o:      in_ch = C_o_Acute;      break;
                  case C_u:      in_ch = C_u_Acute;      break;
                  case C_u_Ogon: in_ch = C_u_Ogon_Acute; break;
                  case C_u_Macr: in_ch = C_u_Macr_Acute; break;
                  case C_A_Cyr:  in_ch = C_A_Cyr_Acute;  break;
                  case C_E_Cyr:  in_ch = C_E_Cyr_Acute;  break;
                  case C_I_Cyr:  in_ch = C_I_Cyr_Acute;  break;
                  case C_O_Cyr:  in_ch = C_O_Cyr_Acute;  break;
                  case C_U_Cyr:  in_ch = C_U_Cyr_Acute;  break;
                  case C_Y_Cyr:  in_ch = C_Y_Cyr_Acute;  break;
                  case C_Ee_Cyr: in_ch = C_Ee_Cyr_Acute; break;
                  case C_Yu_Cyr: in_ch = C_Yu_Cyr_Acute; break;
                  case C_Ya_Cyr: in_ch = C_Ya_Cyr_Acute; break;
                  case C_a_Cyr:  in_ch = C_a_Cyr_Acute;  break;
                  case C_e_Cyr:  in_ch = C_e_Cyr_Acute;  break;
                  case C_i_Cyr:  in_ch = C_i_Cyr_Acute;  break;
                  case C_o_Cyr:  in_ch = C_o_Cyr_Acute;  break;
                  case C_u_Cyr:  in_ch = C_u_Cyr_Acute;  break;
                  case C_y_Cyr:  in_ch = C_y_Cyr_Acute;  break;
                  case C_ee_Cyr: in_ch = C_ee_Cyr_Acute; break;
                  case C_yu_Cyr: in_ch = C_yu_Cyr_Acute; break;
                  case C_ya_Cyr: in_ch = C_ya_Cyr_Acute; break;
                  default:
                     retc=UnGetChar(iin_ch);
                     break;
                  }

               } // if((in_ch == C_Apost) || (in_ch == C_Plus) || (in_ch == C_Acute)) // '\''

// ------------------------------------------------------ ~x
               if((in_ch == C_Tilde) || (in_ch == C_TildeAcc)) // '~'
               {
                  if(SUCCEEDED(retc)) retc=GetChar(&iin_ch, True);
                  if(SUCCEEDED(retc)) switch(iin_ch)
                  {
                  case C_A:      in_ch = C_A_Tilde;      break;
                  case C_A_Ogon: in_ch = C_A_Ogon_Tilde; break;
                  case C_E:      in_ch = C_E_Tilde;      break;
                  case C_E_Ogon: in_ch = C_E_Ogon_Tilde; break;
                  case C_E_Adot: in_ch = C_E_Adot_Tilde; break;
                  case C_I:      in_ch = C_I_Tilde;      break;
                  case C_I_Ogon: in_ch = C_I_Ogon_Tilde; break;
                  case C_Y:      in_ch = C_Y_Tilde;      break;
                  case C_O:      in_ch = C_O_Tilde;      break;
                  case C_U:      in_ch = C_U_Tilde;      break;
                  case C_U_Ogon: in_ch = C_U_Ogon_Tilde; break;
                  case C_U_Macr: in_ch = C_U_Macr_Tilde; break;
                  case C_a:      in_ch = C_a_Tilde;      break;
                  case C_a_Ogon: in_ch = C_a_Ogon_Tilde; break;
                  case C_e:      in_ch = C_e_Tilde;      break;
                  case C_e_Ogon: in_ch = C_e_Ogon_Tilde; break;
                  case C_e_Adot: in_ch = C_e_Adot_Tilde; break;
                  case C_i:      in_ch = C_i_Tilde;      break;
                  case C_i_Ogon: in_ch = C_i_Ogon_Tilde; break;
                  case C_y:      in_ch = C_y_Tilde;      break;
                  case C_o:      in_ch = C_o_Tilde;      break;
                  case C_u:      in_ch = C_u_Tilde;      break;
                  case C_u_Ogon: in_ch = C_u_Ogon_Tilde; break;
                  case C_u_Macr: in_ch = C_u_Macr_Tilde; break;
                  case C_l:      in_ch = C_l_Tilde;      break;
                  case C_m:      in_ch = C_m_Tilde;      break;
                  case C_n:      in_ch = C_n_Tilde;      break;
                  case C_r:      in_ch = C_r_Tilde;      break;
                  default:
                     retc=UnGetChar(iin_ch);
                     break;
                  }

               } // if((in_ch == C_Tilde) || (in_ch == C_TildeAcc)) // '`'

// ------------------------------------------------------ `x
               if((in_ch == C_Grave) || (in_ch == C_GraveAcc)) // '`'
               {
                  if(SUCCEEDED(retc)) retc=GetChar(&iin_ch, True);
                  if(SUCCEEDED(retc)) switch(iin_ch)
                  {
                  case C_A: in_ch = C_A_Grave; break;
                  case C_E: in_ch = C_E_Grave; break;
                  case C_I: in_ch = C_I_Grave; break;
                  case C_Y: in_ch = C_Y_Grave; break;
                  case C_O: in_ch = C_O_Grave; break;
                  case C_U: in_ch = C_U_Grave; break;
                  case C_a: in_ch = C_a_Grave; break;
                  case C_e: in_ch = C_e_Grave; break;
                  case C_i: in_ch = C_i_Grave; break;
                  case C_y: in_ch = C_y_Grave; break;
                  case C_o: in_ch = C_o_Grave; break;
                  case C_u: in_ch = C_u_Grave; break;
                  default:
                     retc=UnGetChar(iin_ch);
                     break;
                  }

               } // if(in_ch != C_Grave) // '`'

// ------------------------------------------------------ "x
               if((in_ch == C_Quote) || (in_ch == C_Diaer)) // '\"'
               {
                  if(SUCCEEDED(retc)) retc=GetChar(&iin_ch, True);
                  if(SUCCEEDED(retc))
                  {
                     if(XM_IS_VERS_HTML(vers))
                     {
                        if(SUCCEEDED(retc)) retc=UnGetChar(iin_ch); // ka_kodël ungetinasi atbula tvarka
                        if(SUCCEEDED(retc)) switch(iin_ch)
                        {
                        case C_A:
                        case C_E:
                        case C_I:
                        case C_Y:
                        case C_O:
                        case C_U:
                        case C_a:
                        case C_e:
                        case C_i:
                        case C_y:
                        case C_o:
                        case C_u:
                        case C_Dash:
                           retc=UnGetChar(C_NullSpc);
                           break;
                        }
                     }
                     else switch(iin_ch)
                     {
                     case C_A: in_ch = C_A_Diaer; break;
                     case C_E: in_ch = C_E_Diaer; break;
                     case C_I: in_ch = C_I_Diaer; break;
                     case C_Y: in_ch = C_Y_Diaer; break;
                     case C_O: in_ch = C_O_Diaer; break;
                     case C_U: in_ch = C_U_Diaer; break;
                     case C_a: in_ch = C_a_Diaer; break;
                     case C_e: in_ch = C_e_Diaer; break;
                     case C_i: in_ch = C_i_Diaer; break;
                     case C_y: in_ch = C_y_Diaer; break;
                     case C_o: in_ch = C_o_Diaer; break;
                     case C_u: in_ch = C_u_Diaer; break;
                     case C_Dash: in_ch = C_Dash_Diaer; break;
                     default:
                        retc=UnGetChar(iin_ch);
                        break;
                     }
                  }

               } // if(in_ch != C_Quote) // '\"'

// ------------------------------------------------------ x"
               if(SUCCEEDED(retc)) retc=GetChar(&iin_ch, False);
//             if(retc == KP_E_EOF) retc = S_OK;
//             else
                  if(SUCCEEDED(retc))
               {
                  if(iin_ch != C_Quote) // '\"'
                     retc=UnGetChar(iin_ch);
                  else
                  {
                     if(XM_IS_VERS_HTML(vers))
                     {
                        if(SUCCEEDED(retc)) retc=UnGetChar(iin_ch); // ka_kodël ungetinasi atbula tvarka
                        if(SUCCEEDED(retc)) switch(in_ch)
                        {
                        case C_Dash:
                        case C_C:
                        case C_c:
                        case C_S:
                        case C_s:
                        case C_Y:
                        case C_y:
                        case C_e:
                        case C_a:
                        case C_g:
                        case C_F_Cyr:
                        case C_f_Cyr:
                        case C_Soft_Cyr:
                        case C_soft_Cyr:
                        case C_N:
                           retc=UnGetChar(C_NullSpc);
                           break;
                        }
                     }
                     else switch(in_ch)
                     {
                     case C_Dash: in_ch = C_Dash_Diaer; break; // '-' // TX_TG_dtb
                     case C_C: in_ch = C_C_Cedil; break;       // 'C'
                     case C_c: in_ch = C_c_Cedil; break;       // 'c'
                     case C_S: in_ch = C_S_Acute; break;       // 'S'
                     case C_s: in_ch = C_s_Acute; break;       // 's'
                     case C_Y: in_ch = C_Y_Grave /* C_Y_Diaer */; break; // 'Y'
                     case C_y: in_ch = C_y_Grave /* C_y_Diaer */; break; // 'y'
                     case C_e: in_ch = C_e_Circ; break;        // 'e'
                     case C_a: in_ch = C_alpha; break;         // 'a'
                     case C_g: in_ch = C_gamma; break;         // 'g'
                     case C_F_Cyr: in_ch = C_Fita_Cyr; break;
                     case C_f_Cyr: in_ch = C_fita_Cyr; break;
                     case C_Soft_Cyr: in_ch = C_Yat_Cyr; break;
                     case C_soft_Cyr: in_ch = C_yat_Cyr; break;
                     case C_N: in_ch = C_No; break;
                     default:
                        retc=UnGetChar(iin_ch);
                        break;
                     }
                  }
               }

            } // if(m_iXmlVers==XM_VERS_SGML_TAGE)

            *piInch=in_ch;

         } // else // if((in_ch==TV_XM_SpCharSt /* '&' */) && (m_uiFType==XL_FT_DataFile))
      }
   }

   if((retc == KP_E_EOF) && bCheckFeof)
      KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);

   KP_DELETEA(par_buf);

   } // else // if(m_bUnGetChProcCnt>0)

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::UnGetCharProc(KpChar iInch, XmlTagPars *pTagParsPtr)
{
HRESULT retc=S_OK;

   if(m_bUnGetChProcCnt>=TV_XL_UNGET_BUF_SIZ)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_iUnGetChProcBuf[m_bUnGetChProcCnt]=iInch;

      m_pUnGetChPars[m_bUnGetChProcCnt] = NULL;
//    retc=CopyTagPars(pTagParsPtr, m_pUnGetChPars+m_bUnGetChProcCnt);
      if((pTagParsPtr != NULL) && SUCCEEDED(retc))
         KP_NEWO(m_pUnGetChPars[m_bUnGetChProcCnt], XmlTagPars(pTagParsPtr));

      if(SUCCEEDED(retc)) m_bUnGetChProcCnt++;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SkipSpaces(void)
{
HRESULT retc=S_OK;

#if FALSE
KpChar in_ch;

   do retc=GetChar(&in_ch, False);
   while((TvStrChr(lpszSpcEol, in_ch)!=NULL) && SUCCEEDED(retc));

   if(SUCCEEDED(retc)) retc=UnGetChar(in_ch);
#else
KpChar in_ch;
XmlTagPars *tag_pars=NULL;

   do
   {
      KP_DELETE(tag_pars);

      retc = GetCharProc(&in_ch, &tag_pars, False, True);
   }
   while((TvStrChr(lpszSpcEol, in_ch)!=NULL) && SUCCEEDED(retc));

   if(SUCCEEDED(retc)) retc=UnGetCharProc(in_ch, tag_pars);

   KP_DELETE(tag_pars);
#endif

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::TestPars(KpChar iChar, XmlTagPars *pTagParsPtr)
{
HRESULT retc = S_OK;
int par_cnt;
unsigned char par_nam[TV_TAG_LEN + 1];
unsigned char *par_val = null;
int par_num;
UC_Modes enc_mode = UC_No_Mode;
int ctbl = 0;
int def_ctbl = 0;
const unsigned char *test_str = null;

   KP_ASSERT(m_lpLowLevelFile != NULL, KP_E_NO_FILE, null, True);

   KP_NEWA(par_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc))
     retc = GetEncoding(&enc_mode, &ctbl, &def_ctbl);

   if((iChar>=XL_FirstSysTag) && (iChar<XL_LastSysTag) && SUCCEEDED(retc))
   {
// closing tags - can have parameters if tag name consists of multiple words
//    if((iChar&1)!=C_Nul)
//       if((pTagParsPtr!=NULL) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// <?xml version='1.0' encoding="UTF-8" ?>
      if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_Version_STR)==0)
      {
         KP_ASSERT(m_iXmlVers >= XM_VERS_XHTML, KP_E_FILE_FORMAT, null, True);

         if((pTagParsPtr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=pTagParsPtr->GetParCnt(&par_cnt);

         if((par_cnt!=2)  && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            test_str=(unsigned char *)"version";
            retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if((par_num!=0) || (strcmp(strlwr(par_val), "1.0")!=0))
                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, par_val, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            test_str=(unsigned char *)"encoding";
            retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
            if((par_num!=1) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
// parse Unicode coding mode
               retc=GetKwrdIndex((int *)(&enc_mode), par_val, lpszaXmlCodingModes, UC_Num_Of_Modes, False, True);
               if(retc==KP_E_KWD_NOT_FOUND)
               {
// parse code table
                  enc_mode=UC_No_Mode;
                  retc=GetKwrdIndex(&def_ctbl, par_val, lpszaXmlCtblNames, KPT_Ctnum, False, True);
                  if(retc==KP_E_KWD_NOT_FOUND)
                  {
                     retc=GetKwrdIndex(&def_ctbl, par_val, lpszaXmlCtblNamesWin, KPT_Ctnum, False, True);
                     if(retc==KP_E_KWD_NOT_FOUND)
                     {
                        def_ctbl=0;
                        retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, par_val, True, __FILE__, __LINE__, 0L);
                     }
                  }
                  ctbl=def_ctbl;
               }
            }
         }

      } // if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_Version_STR)==0)

// <!DOCTYPE di SYSTEM "dict.dtd">
// <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
// <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
// <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
      if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_DOCTYPE_STR)==0)
      {
         if((pTagParsPtr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=pTagParsPtr->GetParCnt(&par_cnt);

         if(SUCCEEDED(retc)) switch(m_iXmlVers)
         {
         case XM_VERS_HTML40:
         case XM_VERS_HTML401_TRANS:
         case XM_VERS_HTML401:
         case XM_VERS_HTML401_FRAME:
         case XM_VERS_HTML_TAGE:
         case XM_VERS_XHTML:
            KP_ASSERT((par_cnt == 3) || (par_cnt == 4), KP_E_FILE_FORMAT, null, True);

            if(SUCCEEDED(retc))
            {
               test_str=(unsigned char *)"html";
               retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, False, __FILE__, __LINE__, 0L);
               else
                  if((strlen(par_val)>0) || (par_num!=0))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               test_str=(unsigned char *)"public";
               retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, False, __FILE__, __LINE__, 0L);
               else
                  if((strlen(par_val)>0) || (par_num!=1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               retc = pTagParsPtr->GetTextPar(par_nam, par_val, 2);
               if(SUCCEEDED(retc))
                  KP_ASSERT((strlen(par_nam) == 0) && (TvStrCmp(par_val, plpszaHtmlVersionIds[m_iXmlVers], False, KP_LNG_ENG, False, 1, False) == 0),
                     KP_E_FILE_FORMAT, par_val, False);
            }

            if((par_cnt>3) && SUCCEEDED(retc))
            {
               retc=pTagParsPtr->GetTextPar(par_nam, par_val, 3);
               if(SUCCEEDED(retc))
                  if((strlen(par_nam)>0) || (TvStrCmp(par_val, plpszaHtmlDtds[m_iXmlVers], False, KP_LNG_ENG, False, 1, False)!=0))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            break;

         case XM_VERS_XML10:
            if((par_cnt!=3)  && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               test_str=(unsigned char *)"system";
               retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  if((par_num!=1) || (strlen(par_val)>0))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               retc=pTagParsPtr->GetTextPar(par_nam, par_val, 2);
               if(SUCCEEDED(retc))
                  if((strlen(par_nam)>0) || (strlen(par_val)==0))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            }

            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
            break;
         }

      } // if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_DOCTYPE_STR)==0)

// <?xml-stylesheet href="tvxmlt.css" type="text/css" ?>
// <?xml-stylesheet href="..\hop.xsl" type="text/xsl" ?>
      if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_Stylesheet_STR)==0)
      {
         if((m_iXmlVers!=XM_VERS_XML10) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if((pTagParsPtr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=pTagParsPtr->GetParCnt(&par_cnt);

         if((par_cnt!=2)  && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            test_str=(unsigned char *)"href";
            retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
            if(((par_num!=0) || (strlen(par_val)==0)) && SUCCEEDED(retc))
                retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            test_str=(unsigned char *)"type";
            retc=pTagParsPtr->SeekTextPar(test_str, par_val, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(
                  (par_num!=1) ||
                  (
                     (strcmp(strlwr(par_val), "text/css")!=0) &&
                     (strcmp(strlwr(par_val), "text/xsl")!=0)
                  )
                 )
                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, par_val, True, __FILE__, __LINE__, 0L);
         }

      } // if(strcmp(plpszaXmlSysTags[iChar-XL_FirstSysTag], XM_Stylesheet_STR)==0)

// set enc_mode and ctbl
      if(SUCCEEDED(retc)) retc=SetEncoding(enc_mode, ctbl, def_ctbl);

   } // if((iChar>=XL_FirstSysTag) && (*piInch<XL_LastSysTag))


   if((iChar >= m_iFirstDictTag) && (!CheckLastTag(iChar) /* iChar < m_iLastDictTagCurrent */) && SUCCEEDED(retc))
   {
// closing tags - can have parameters if tag name consists of multiple words
//    if((iChar&1)!=C_Nul)
//       if((pTagParsPtr!=NULL) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// test HTML tag pars, parse code table
      if(SUCCEEDED(retc) && XM_IS_VERS_HTML(m_iXmlVers))
         retc=HtmtTestPars(iChar, pTagParsPtr, &enc_mode, &ctbl, &def_ctbl, m_lpszaTagNames, m_iFirstDictTag, GetLastTag());
// set enc_mode and ctbl
      if(SUCCEEDED(retc)) retc=SetEncoding(enc_mode, ctbl, def_ctbl);

#if FALSE // #ifdef Debug
GetEncoding(&enc_mode, &ctbl, &def_ctbl);
KP_TRACE_5("TvXmlFile::GetCharProc: %s enc_mode:%d ctbl:%d def_ctbl:%d m_iDefCodeTable:%d", GetTagName(iChar), enc_mode, ctbl, def_ctbl, m_iDefCodeTable);
#endif

   } // if((iChar>=m_iFirstDictTag) && (!CheckLastTag(*piInch) /* *piInch < m_iLastDictTagCurrent */))

   KP_DELETEA(par_val);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::SkipToCharProc(KpChar iDelimCh)
{
HRESULT retc=S_OK;
KpChar in_ch;

   do retc=GetCharProc(&in_ch, NULL, False, True);
   while((in_ch!=iDelimCh) && SUCCEEDED(retc));

return(retc);
}


// ================================================== binary output
// --------------------------------------------------
HRESULT TvXmlFile::PutImage(const void *lpBuffer, const int iByteCount)
{
HRESULT retc=S_OK;

   if(m_lpRawFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fwrite(lpBuffer, 1, iByteCount, m_lpRawFile);

      if(ferror(m_lpRawFile) || feof(m_lpRawFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::PutLong(const long lValue)
{
return(PutImage(&lValue, sizeof(long)));      // !!! depends on processor
}


// ================================================== binary input
// --------------------------------------------------
HRESULT TvXmlFile::GetImage(void *lpBuffer, const int iByteCount, bool bCheckFeof)
{
HRESULT retc=S_OK;
unsigned char *buf_ptr;
int byt_cnt;

   if(m_lpRawFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((lpBuffer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      buf_ptr = (unsigned char *)lpBuffer;
      byt_cnt=iByteCount;

      if(byt_cnt>0)
      {
         if(m_iUnGetCnt>0)
         {
            if((m_iaUnGetBuf[m_iUnGetCnt-1]<0) || (m_iaUnGetBuf[m_iUnGetCnt-1]>=KPT_Ctbsiz))
               retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
            (*buf_ptr++)=(unsigned char)m_iaUnGetBuf[--m_iUnGetCnt];
            byt_cnt--;
         }

         fread(buf_ptr, 1, byt_cnt, m_lpRawFile);
         if(ferror(m_lpRawFile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc) && feof(m_lpRawFile)) retc=KP_E_EOF;

         if(bCheckFeof && (retc==KP_E_EOF))
            retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, m_lpszFName, True, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::Fseek(long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(m_lpRawFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   else
   {
      if(fseek(m_lpRawFile, lOffset, iOrigin)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlFile::Ftell(long *plOffset)
{
HRESULT retc=S_OK;

   if(plOffset==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *plOffset=0L;

   if((m_lpRawFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plOffset=ftell(m_lpRawFile);
      if(*plOffset==(-1L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
int TvXmlFile::GetTagCodeTable(KpChar iTag, KpChar iFirstTag, KpChar iLastTag, const int *piaCodeTables)
{
// HRESULT retc=S_OK;
int ctbl = m_iDefCodeTable;

   if(iFirstTag == C_Nul) iFirstTag = m_iFirstDictTag;
   if(iFirstTag == m_iFirstDictTag) iLastTag = m_iLastDictTagOrig;   // kai pilni parametrai, iLastTag bûna m_iLastDictTagCurrent -
                                                                     // gali iðlipti u_ m_piaCodeTablesOrig[] ribø
   if(iLastTag == C_Nul) iLastTag = m_iLastDictTagOrig /* m_iLastDictTagCurrent */;
   if(piaCodeTables == NULL) piaCodeTables = m_piaCodeTablesOrig;

// if(SUCCEEDED(retc))
   {
      if(iTag == XL_Text) ctbl = iaXmlSysCodeTables[iTag - XL_FirstSysTag]; // KPT_UpCodeTable;
      else
      {
         if(piaCodeTables == NULL)
         {
//          retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         }
         else
         {
            if((iTag >= iFirstTag) && (iTag < iLastTag))
               ctbl = piaCodeTables[iTag - iFirstTag];
         }
      }
   }

// return(retc);
return(ctbl);
}
