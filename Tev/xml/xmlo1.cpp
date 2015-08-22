// ==================================================
// xmlo1.cpp,fromer tvxmlio1.cpp
// XML multifile


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
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
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
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
#include "xmlsty.h"
#include "xml8.h"
#include "xmlb.h"
#include "xmlu.h"


// ================================================== static data
const unsigned char *lppszFileIndexNamesFict[] = {(const unsigned char *)"", NULL};
const int aiFileIndexLengthsFict[] = {0};


// ================================================== private methods of XmlO1_tag

// ================================================== public methods of XmlO1_tag
// ================================================== open files
// --------------------------------------------------
XmlO1::XmlO1(
   const unsigned char *lpszFileName,
   const unsigned char *lpszMode,
   HRESULT CreateLowLevelObj
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   ),
   const unsigned char * const *plpszaXmlSpCharTags,
   const unsigned char * const *lppszFileIndexNames,
   const int *aiFileIndexLengths,
   KpChar iFirstTag,
   const unsigned char * const *plpszaTags,
   bool bExternalTagsArray,
   XmlVersions iVersion,
   const int *piaCodeTables,
   bool bMultiLine,
   bool bMapToPrivate
)
{
HRESULT retc = S_OK;
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fname[KP_MAX_FNAME_LEN+1];
unsigned char ftype[KP_MAX_FTYPE_LEN+1];
unsigned char cur_fname[KP_MAX_FNAME_LEN+7+1];
bool b_mode;
bool w_mode;
bool ap_mode;
int ii;
const unsigned char * const *pntss;

// ---------------------------
   m_lhOpenResult = S_OK;

   for(ii=0; ii<XL_IX_MaxNumOfIndexes; ii++)
   {
      m_fFiles[ii]=NULL;
      m_fRepFiles[ii]=NULL;
   }

   m_lpszFName[0]=Nul;
   m_lpszFMode[0]=Nul;

// ---------------------------
   if((lppszFileIndexNames!=NULL) && (aiFileIndexLengths!=NULL))
   {
      m_lppszFileIndexNamesPtr = lppszFileIndexNames;
      m_aiFileIndexLengthsPtr = aiFileIndexLengths;
   }
   else
   {
      m_lppszFileIndexNamesPtr = lppszFileIndexNamesFict;
      m_aiFileIndexLengthsPtr = aiFileIndexLengthsFict;
      if((lppszFileIndexNames!=NULL) || (aiFileIndexLengths!=NULL))
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_iNumOfIndexes = 0;
      pntss = m_lppszFileIndexNamesPtr;
      while(*pntss) { pntss++; m_iNumOfIndexes++;}
      if((m_iNumOfIndexes<XL_IX_DefSeIndex) || (m_iNumOfIndexes>XL_IX_MaxNumOfIndexes))
      {
         m_iNumOfIndexes=XL_IX_MaxNumOfIndexes;
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
   }


// ---------------------------
   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszFileName)<KP_MAX_FNAME_LEN) strcpy((char *)m_lpszFName, (const char *)lpszFileName);
      else
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszMode)<TV_TAG_LEN) strcpy((char *)m_lpszFMode, (const char *)lpszMode);
      else retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

// ---------------------------
   if(SUCCEEDED(retc)) retc = GetFileMode(&b_mode, &w_mode, &ap_mode);
   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, m_lpszFName);
   if(SUCCEEDED(retc))
   {
      strcat(disk, path);
      ii=strlen(disk);
      if(ii>0) if(disk[ii-1]!='\\') strcat(disk, "\\");
      strcat(disk, fname);
      strcpy(fname, disk);
   }

// --------------------------- open index files
   if((CreateLowLevelObj!=CreateNewBFile) && (CreateLowLevelObj!=CreateNewUniBFile) && SUCCEEDED(retc))
      for(ii=XL_IX_DefSeIndex; (ii<m_iNumOfIndexes) && SUCCEEDED(retc); ii++)
   {
      strcpy((char *)cur_fname, (const char *)fname);
      strcat((char *)cur_fname, "_");
      strcat((char *)cur_fname, (const char *)m_lppszFileIndexNamesPtr[ii]);
      strcat((char *)cur_fname, (b_mode?".ix":".ixt"));

      KP_NEWO(m_fFiles[ii], TvXmlFile(cur_fname, m_lpszFMode,
                                    (ii==XL_IX_DefSeIndex)?XL_FT_MainIxFile:XL_FT_IxFile, CreateNew8File,
                                    NULL,
                                    (ii==XL_IX_DefSeIndex)?TV_XL_NUM_LEN:m_aiFileIndexLengthsPtr[ii]-sizeof(long),
                                    iFirstTag, plpszaTags, bExternalTagsArray,
                                    XM_NO_VERS, NULL, False, False));

// ------------------ open report file
      if((!b_mode) && w_mode && SUCCEEDED(retc))
      {
         strcpy((char *)cur_fname, (const char *)fname);
         strcat((char *)cur_fname, "_");
         strcat((char *)cur_fname, (const char *)m_lppszFileIndexNamesPtr[ii]);
         strcat((char *)cur_fname, ".txt");

         KP_NEWO(m_fRepFiles[ii], TvXmlFile(cur_fname, m_lpszFMode,
                                    XL_FT_ReportFile, CreateNew8File,
                                    NULL,
                                    4+2*m_aiFileIndexLengthsPtr[ii],
                                    iFirstTag, plpszaTags, bExternalTagsArray,
                                    XM_NO_VERS, NULL, False, False));
      }

      retc = S_OK;
   }


// ---------------------------
// XML data file
   m_fFiles[XL_IX_DefDataFile]=NULL;
   if(
         (
            ((!b_mode) && w_mode) ||
            (b_mode && (!w_mode))

         ) && SUCCEEDED(retc)
   )
   {
      KP_NEWO(m_fFiles[XL_IX_DefDataFile], TvXmlFile(m_lpszFName,
         (const unsigned char *)(w_mode?(ap_mode?"ab":"wb"):"rb"),
         XL_FT_DataFile, CreateLowLevelObj, plpszaXmlSpCharTags,
         TV_XL_NUM_LEN, iFirstTag, plpszaTags, bExternalTagsArray,
         iVersion, piaCodeTables, bMultiLine, bMapToPrivate));
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// --------------------------------------------------
XmlO1::~XmlO1()
{
   CloseFile(False);
// KP_TRACE("XmlO1::~XmlO1()");
}


// --------------------------------------------------
HRESULT XmlO1::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlO1::GetFileType(XL_FileTypes *puiFileType, int iFileIndex)
{
HRESULT retc=S_OK;

   if((puiFileType==NULL) || (iFileIndex<0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if((m_fFiles[iFileIndex]==NULL) || (iFileIndex>=m_iNumOfIndexes)) *puiFileType=XL_FT_Undefined;
      else retc=m_fFiles[iFileIndex]->GetFileType(puiFileType);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetFileMode(bool *pbBinFl, bool *pbWriteFl, bool *pbAppendFl)
{
HRESULT retc=S_OK;

   if((pbBinFl==NULL) || (pbWriteFl==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbBinFl=((strchr((const char *)m_lpszFMode,'b')!=NULL) || (strchr((const char *)m_lpszFMode,'B')!=NULL));

      *pbWriteFl=(
                  (strchr((const char *)m_lpszFMode,'w')!=NULL) ||
                  (strchr((const char *)m_lpszFMode,'W')!=NULL) ||
                  (strchr((const char *)m_lpszFMode,'a')!=NULL) ||
                  (strchr((const char *)m_lpszFMode,'A')!=NULL)
                 );

      *pbAppendFl=(
                  (strchr((const char *)m_lpszFMode,'a')!=NULL) ||
                  (strchr((const char *)m_lpszFMode,'A')!=NULL)
                 );
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetEncoding(UC_Modes *piEncMode, int *piCodeTable, int *piDefCodeTable)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->GetEncoding(piEncMode, piCodeTable, piDefCodeTable);

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SetEncoding(UC_Modes iEncMode, int iCodeTable, int iDefCodeTable)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->SetEncoding(iEncMode, iCodeTable, iDefCodeTable);

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetVersion(XmlVersions *piVersion)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->GetVersion(piVersion);

return(retc);
}


// -------------------------------
HRESULT XmlO1::SetPathMode(XL_PathMode iPathMode)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->SetPathMode(iPathMode);

return(retc);
}

XL_PathMode XmlO1::GetPathMode(void)
{
HRESULT retc=S_OK;
XL_PathMode reti = XL_RelativePath;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      reti=m_fFiles[XL_IX_DefDataFile]->GetPathMode();

return(reti);
}

// -------------------------------
HRESULT XmlO1::SetScale(int iScale)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->SetScale(iScale);

return(retc);
}

int XmlO1::GetScale(void)
{
HRESULT retc=S_OK;
int reti = 10;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      reti=m_fFiles[XL_IX_DefDataFile]->GetScale();

return(reti);
}

// --------------------------------------------------
HRESULT XmlO1::GetCurTag(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if((m_fFiles[XL_IX_DefDataFile]==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=m_fFiles[XL_IX_DefDataFile]->GetCurTag(piCurTag);

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::Reset(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[XL_IX_DefDataFile]->Reset();

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;
int ii;

   for(ii=0; ii<m_iNumOfIndexes; ii++)
   {
      if(m_fFiles[ii]!=NULL)
      {
         retc0 = m_fFiles[ii]->CloseFile(bCheckFileExist);
         if(SUCCEEDED(retc)) retc=retc0;
         KP_DELETE(m_fFiles[ii]);
      }

      if(m_fRepFiles[ii]!=NULL)
      {
         retc0 = m_fRepFiles[ii]->CloseFile(bCheckFileExist);
         if(SUCCEEDED(retc)) retc=retc0;
         KP_DELETE(m_fRepFiles[ii]);
      }
   }

return(retc);
}


// --------------------------------------------------
KpChar XmlO1::GetLastTag(void)
{
KpChar retv = C_Nul;

   if(m_fFiles[XL_IX_DefDataFile]) retv = m_fFiles[XL_IX_DefDataFile]->GetLastTag();

return(retv);
}


const unsigned char * const *XmlO1::GetTagsArrPtr(void) const
{
const unsigned char * const *retp = NULL;

   if(m_fFiles[XL_IX_DefDataFile]) retp = m_fFiles[XL_IX_DefDataFile]->GetTagsArrPtr();

return(retp);
}


// ================================================== text input
long ll=0;
// --------------------------------------------------
HRESULT XmlO1::GetCharProc
(
KpChar *piInch,
XmlTagPars **pTagParsPtr,
int iFileIndex,
bool bCheckFeof,
bool bProcSpcEol
)
{
HRESULT retc=S_OK;

   KP_ASSERT(piInch != NULL, E_INVALIDARG, null, True);
   KP_ASSERT((iFileIndex >= 0) && (iFileIndex < m_iNumOfIndexes), E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) *piInch=C_Nul;

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetCharProc(piInch, pTagParsPtr, bCheckFeof, bProcSpcEol);
   }

#ifdef Debug
if(++ll==118973)
ll=118973;
#endif

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::UnGetCharProc(KpChar iOutch, XmlTagPars *pTagPars, int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->UnGetCharProc(iOutch, pTagPars);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetNumVal(long *plValue, int iFileIndex, bool bCheckFeof)
{
HRESULT retc=S_OK;

   if((plValue==NULL) || (iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      *plValue=0L;

      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetNumVal(plValue, bCheckFeof);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SkipEol(int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->SkipEol();
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SkipSpaces(int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->SkipSpaces();
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SkipToCharProc(KpChar uiDelimCh, int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->SkipToCharProc(uiDelimCh);
   }

return(retc);
}


// ================================================== text output
// --------------------------------------------------
HRESULT XmlO1::PutCharProc
(
KpChar iOutch,
XmlTagPars *pTagPars,
int iFileIndex
)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->PutCharProc(iOutch, pTagPars, True);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutRepCharProc
(
KpChar iOutch,
int iFileIndex
)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fRepFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=m_fRepFiles[iFileIndex]->PutCharProc(iOutch, NULL, True);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutStr(const unsigned char *lpszOutstr, int iFileIndex)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   if((lpszOutstr==NULL) || (iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszOutstr;

      while(*pnts && SUCCEEDED(retc))
         retc=PutCharProc((KpChar)(*pnts++), NULL, iFileIndex);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutRepStr(const unsigned char *lpszOutstr, int iFileIndex)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   if((lpszOutstr==NULL) || (iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszOutstr;

      while(*pnts && SUCCEEDED(retc))
         retc=PutRepCharProc((KpChar)(*pnts++), iFileIndex);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutKpStr(const KpChar *iazOutstr, int iFileIndex)
{
HRESULT retc=S_OK;
const KpChar *pnts;
XmlVersions fvers;
int ii;

   if((iazOutstr==NULL) || (iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=iazOutstr;

      while(*pnts && SUCCEEDED(retc))
      {
         if(iFileIndex == XL_IX_DefDataFile)
         {
            if((m_fFiles[iFileIndex] == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc = m_fFiles[iFileIndex]->GetVersion(&fvers);

            if(SUCCEEDED(retc))
            {
               if(XM_IS_VERS_HTML_TAGE(fvers))
               {
                  switch(*pnts)
                  {
                  case NS_CTRL_START: // '$'
                     switch(*(pnts+1))
                     {
// !!!! TODO font style
                     case 'f':
                        pnts++;
                        for(ii = 0; (ii < NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;
                        break;

// !!!! TODO paragraph style
                     case 's':
                        pnts++;
                        for(ii = 0; (ii < NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;
                        break;

// !!!! TODO condensed font
                     case 'q':
                        pnts++;
                        for(ii = 0; (ii < NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;
                        break;

// !!!! TODO unicode character
                     case 'u':
                        pnts++;
                        for(ii = 0; (ii < NS_UNI_CODE_WDT) && (TvIsHexDigit(*pnts)); ii++) pnts++;
                        retc = KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, False, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) retc = PutCharProc('?', NULL, iFileIndex);
                        break;

// output of spec. chars
//                   case NS_CTRL_START:  // '$' itself
//                   case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
// //                case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
//                   case C_Numb:         // '#' itself, single '#' --> C_QemSpc
//                   case C_Lbrack:       // '[' itself, single '[' --> \rm
//                   case C_Rbrack:       // ']' itself, single ']' --> end of \rm
//                   case C_Lcurl:        // '{' itself, single '{' --> \bf
//                   case C_Rcurl:        // '}' itself, single '}' --> end of \bf
//                   case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstų į TX_TG_BD
//                      pnts++;
//                      retc=PutCharProc(*pnts++), NULL, iFileIndex);
//                      break;

//                   case C_Bpoint:       // bullet itself, kad nenumestų DOUBLE_ENTRIES_KPCHAR
//                      pnts += 2;
//                      retc=PutCharProc(C_hBpoint, NULL, iFileIndex);
//                      break;

// formatting symbols
//                   case C_Underl:       // "$_" --> C_NBSP
//                      pnts += 2;
//                      retc=PutCharProc(C_NBSP, NULL, iFileIndex);
//                      break;
//                   case C_At:           // "$@" --> C_Ff
//                      pnts += 2;
//                      retc=PutCharProc(C_Ff, NULL, iFileIndex);
//                      break;
//                   case C_Circ:         // "$^" --> C_hbreak
//                      pnts += 2;
//                      retc=PutCharProc(C_hbreak, NULL, iFileIndex);
//                      break;
//                   case C_Point:        // "$." --> C_NullSpc, \Null
//                      pnts += 2;
// //                   retc=PutCharProc(C_NullSpc, NULL, iFileIndex);
//                      break;

                     default:
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
                        retc=PutCharProc(*pnts++, NULL, iFileIndex);
//                      if(*pnts && SUCCEEDED(retc)) retc = PutCharProc(*pnts++), NULL, iFileIndex);
                        break;

                     } // switch(*(pnts+1))

                     break; // case NS_CTRL_START: // '$'

                  default:
                     if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
                     break;

                  } // switch(*pnts)

               } // if(XM_IS_VERS_HTML_TAGE(fvers))
               else
               {
#if FALSE // netinka exportuojant į TeX
                  switch(*pnts)
                  {
                  case NS_CTRL_START: // '$'
                     switch(*(pnts+1))
                     {
                     case 'f':
                     case 's':
                     case 'u':
                     case 'q':
                        if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
                        break;
                     default:
                        if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                        if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
                        break;
                     }
                     break;

                  case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//                case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
                  case C_Numb:         // '#' itself, single '#' --> C_QemSpc
                  case C_Lbrack:       // '[' itself, single '[' --> \rm
                  case C_Rbrack:       // ']' itself, single ']' --> end of \rm
                  case C_Lcurl:        // '{' itself, single '{' --> \bf
                  case C_Rcurl:        // '}' itself, single '}' --> end of \bf
                  case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstų į TX_TG_BD
                  case C_Bpoint:       // bullet itself, kad nenumestų DOUBLE_ENTRIES_KPCHAR
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
                     break;

                  case C_hBpoint:       // bullet itself, kad nenumestų DOUBLE_ENTRIES_KPCHAR
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Bpoint, NULL, XL_IX_DefDataFile);
                     break;
                  case C_NBSP: // C_NBSP --> "$_"
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Underl, NULL, XL_IX_DefDataFile);
                     break;
                  case C_Ff: // C_Ff --> "$@"
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_At, NULL, XL_IX_DefDataFile);
                     break;
                  case C_hbreak: // C_hbreak --> "$^"
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Circ, NULL, XL_IX_DefDataFile);
                     break;
                  case C_NullSpc: // C_NullSpc, \Null --> "$."
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Point, NULL, XL_IX_DefDataFile);
                     break;
                  case C_hyph: // '\\'
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Lslash, NULL, XL_IX_DefDataFile);
                     break;
                  case C_QemSpc: // '#'
                     pnts++;
                     if(SUCCEEDED(retc)) retc = PutCharProc(C_Numb, NULL, XL_IX_DefDataFile);
                     break;

                  default:
                     if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
                     break;

                  } // switch(*pnts)
#else
                  if(SUCCEEDED(retc)) retc = PutCharProc(*pnts++, NULL, XL_IX_DefDataFile);
#endif

               } // else // if(XM_IS_VERS_HTML_TAGE(fvers))

            } // if(SUCCEEDED(retc))

         } // if(iFileIndex == XL_IX_DefDataFile)
         else
            retc = PutCharProc(*pnts++, NULL, iFileIndex);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutRepKpStr(const KpChar *iazOutstr, int iFileIndex)
{
HRESULT retc=S_OK;
const KpChar *pnts;

   if((iazOutstr==NULL) || (iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=iazOutstr;

      while(*pnts && SUCCEEDED(retc))
         retc=PutRepCharProc(*pnts++, iFileIndex);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutNumVal(const long lValue, int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->PutNumVal(lValue);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::CompleteIndexEntry(int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->CompleteIndexEntry();
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetCharPos(int *piCharPos, int iFileIndex)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *piCharPos=0;

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetCharPos(piCharPos);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetCharNum(long *plCharNum, int iFileIndex)
{
HRESULT retc=S_OK;

   if(plCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *plCharNum=0L;

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetCharNum(plCharNum);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SetBaseIndent(const unsigned char *lpszBaseIndent,  int iFileIndex)
{
HRESULT retc=S_OK;

   if(lpszBaseIndent==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->SetBaseIndent(lpszBaseIndent);
   }

return(retc);
}


HRESULT XmlO1::GetBaseIndent(const unsigned char **plpszBaseIndentPtr,  int iFileIndex)
{
HRESULT retc=S_OK;

   if(plpszBaseIndentPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetBaseIndent(plpszBaseIndentPtr);
   }

return(retc);
}


HRESULT XmlO1::SetIndent(const unsigned char *lpszIndent,  int iFileIndex)
{
HRESULT retc=S_OK;

   if(lpszIndent==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->SetIndent(lpszIndent);
   }

return(retc);
}


HRESULT XmlO1::IncIndent(int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->IncIndent();
   }

return(retc);
}


HRESULT XmlO1::DecIndent(int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->DecIndent();
   }

return(retc);
}


// --------------------------------------------------
#if 0
HRESULT XmlO1::CompleteOpenTags(int iTag)
{
HRESULT retc=S_OK;

   retc=m_fFiles[XL_IX_DefDataFile]->CompleteOpenTags(iTag);

return(retc);
}
#endif

// --------------------------------------------------
HRESULT XmlO1::CompleteOpenTags(KpChar iTag, int iFileIndex)
{
HRESULT retc=S_OK;
KpChar cur_tag;
bool put_close_needed;

   retc=m_fFiles[iFileIndex]->m_lpTagStack->GetCurTag(&cur_tag);

   while((cur_tag!=iTag) && SUCCEEDED(retc))
   {
      retc=m_fFiles[iFileIndex]->m_lpTagStack->GetPutClose(&put_close_needed);
      if(SUCCEEDED(retc))
      {
         if(put_close_needed)
         {
            retc=PutCharProc((KpChar)(cur_tag+1), NULL, False);
            if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->m_lpTagStack->GetCurTag(&cur_tag);
         }
         else
         {
            retc=PopTag(&m_fFiles[iFileIndex]->m_lpTagStack, &cur_tag);
            if((m_fFiles[iFileIndex]->m_lpTagStack==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
         }
      }
   }

return(retc);
}


// ================================================== binary input
// --------------------------------------------------
HRESULT XmlO1::GetImage
(
void *lpBuffer,
const int iByteCount,
int iFileIndex,
bool bCheckFeof
)
{
HRESULT retc=S_OK;

   if(lpBuffer==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->GetImage(lpBuffer, iByteCount, bCheckFeof);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::Fseek(int iFileIndex, const long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(lOffset<0L)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->Fseek(lOffset, iOrigin);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::Ftell(int iFileIndex, long *plOffset)
{
HRESULT retc=S_OK;

   if(plOffset==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->Ftell(plOffset);
   }

return(retc);
}


// ================================================== binary output
// --------------------------------------------------
HRESULT XmlO1::PutLong(const long lValue,  int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         retc=m_fFiles[iFileIndex]->PutLong(lValue);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::PutImage(const void *lpBuffer, const int iByteCount,  int iFileIndex)
{
HRESULT retc=S_OK;

   if(iFileIndex!=XL_IX_DefNoIndex)
   {
      if((iFileIndex<0) || (iFileIndex>=m_iNumOfIndexes))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         retc=m_fFiles[iFileIndex]->PutImage(lpBuffer, iByteCount);
   }

return(retc);
}
