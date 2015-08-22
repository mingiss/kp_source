// ==================================================
// xmli.cpp
// Xml file I/O with authomatic index generating
// layer between xmlf and xmloi2
//

// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
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
#include "kptt.h"
#include "tvmain.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "tvxmle.h"
#include "xmli.h"


// ======================================================
const unsigned char *lpszaXmlTagIxNames[XC_TG_NumOfDictTagsArr68]=
{
  (unsigned char *)"",     // XC_Dict
  (unsigned char *)"",     // XC_Dict_e
  (unsigned char *)"",     // XC_NrtEntry
  (unsigned char *)"",     // XC_NrtEntry_e
  (unsigned char *)"se",   // XC_StEntry
  (unsigned char *)"",     // XC_StEntry_e
  (unsigned char *)"hw",   // XC_HeadWord
  (unsigned char *)"",     // XC_HeadWord_e
  (unsigned char *)"la",   // XC_Label
  (unsigned char *)"",     // XC_Label_e
  (unsigned char *)"tw",   // XC_TrWord
  (unsigned char *)"",     // XC_TrWord_e
  (unsigned char *)"dc",   // XC_UsNoteDst
  (unsigned char *)"",     // XC_UsNoteDst_e
  (unsigned char *)"xr",   // XC_Reference
  (unsigned char *)"",     // XC_Reference_e
  (unsigned char *)"st",   // XC_StEntryText
  (unsigned char *)"",     // XC_StEntryText_e

  (unsigned char *)"tx",   // XC_Paragraph
  (unsigned char *)"",     // XC_Paragraph_e

  (unsigned char *)"",     // XC_Version
  (unsigned char *)"",     // XC_Version_e
  (unsigned char *)"",     // XC_DocType
  (unsigned char *)"",     // XC_DocType_e

  (unsigned char *)"hw",   // XC_Variant
  (unsigned char *)"",     // XC_Variant_e
  (unsigned char *)"ps",   // XC_GramForm
  (unsigned char *)"",     // XC_GramForm_e

  (unsigned char *)"",     // XC_HeadWordGroup
  (unsigned char *)"",     // XC_HeadWordGroup_e
  (unsigned char *)"",     // XC_TranslGroup
  (unsigned char *)"",     // XC_TranslGroup_e

  (unsigned char *)"",     // XC_FormDst
  (unsigned char *)"",     // XC_FormDst_e
  (unsigned char *)"",     // XC_FormSrc
  (unsigned char *)"",     // XC_FormSrc_e

  (unsigned char *)"ic",   // XC_ExplSrc
  (unsigned char *)"",     // XC_ExplSrc_e

  (unsigned char *)"le",   // XC_Example
  (unsigned char *)"",     // XC_Example_e
  (unsigned char *)"",     // XC_ExampleGroup
  (unsigned char *)"",     // XC_ExampleGroup_e

  (unsigned char *)"tx",   // XC_Parenth // prijungti prie tevo
  (unsigned char *)"",     // XC_Parenth_e

  (unsigned char *)"le",   // XC_Idiom
  (unsigned char *)"",     // XC_Idiom_e

  (unsigned char *)"",     // XC_IdiomGroup
  (unsigned char *)"",     // XC_IdiomGroup_e

  (unsigned char *)"",     // XC_CtgGroup
  (unsigned char *)"",     // XC_CtgGroup_e

  (unsigned char *)"" /* "hw" */,   // XC_Base
  (unsigned char *)"",     // XC_Base_e
  (unsigned char *)"",     // XC_CompoundGroup
  (unsigned char *)"",     // XC_CompoundGroup_e
  (unsigned char *)"hw",   // XC_CompoundWord
  (unsigned char *)"",     // XC_CompoundWord_e

  (unsigned char *)"",     // XC_MngGroup
  (unsigned char *)"",     // XC_MngGroup_e

  (unsigned char *)"",     // XC_Asterix
  (unsigned char *)"",     // XC_Asterix_e

  (unsigned char *)"", // "sp",   // XC_CtrlSrc // buna kitu indexiniu tagu viduje - kol kas neiseina
  (unsigned char *)"",     // XC_CtrlSrc_e

  (unsigned char *)"",     // XC_PrGroup
  (unsigned char *)"",     // XC_PrGroup_e
  (unsigned char *)"ph",   // XC_Pron
  (unsigned char *)"",     // XC_Pron_e,

  (unsigned char *)"ct",   // XC_Abbr,
  (unsigned char *)"",     // XC_Abbr_e,

  (unsigned char *)"",     // XC_Hom,
  (unsigned char *)"",     // XC_Hom_e,

  (unsigned char *)"ic", // "co",   // XC_ContextSrc,
  (unsigned char *)"",     // XC_ContextSrc_e,

  (unsigned char *)"",     // XC_CtrlGroup,
  (unsigned char *)"",     // XC_CtrlGroup_e,

  (unsigned char *)"ps",   // XC_PartOfSpeechDst,
  (unsigned char *)"",     // XC_PartOfSpeechDst_e,

  (unsigned char *)"",     // XC_FormGroupSrc,
  (unsigned char *)"",     // XC_FormGroupSrc_e,

  (unsigned char *)"",     // XC_StyleSheet
  (unsigned char *)"",     // XC_StyleSheet_e

  (unsigned char *)"le", // "hw",   // XC_VarNorm
  (unsigned char *)"",     // XC_VarNorm_e

  (unsigned char *)"ct",   // XC_AbbrNorm,
  (unsigned char *)"",     // XC_AbbrNorm_e,

  (unsigned char *)"",     // XC_MngNearGroup,
  (unsigned char *)"",     // XC_MngNearGroup_e,

  (unsigned char *)"ph",   // XC_PronRed
  (unsigned char *)"",     // XC_PronRed_e

  (unsigned char *)"",     // XC_Null
  (unsigned char *)"",     // XC_Null_e

  (unsigned char *)"",     // XC_Similar
  (unsigned char *)"",     // XC_Similar_e

  (unsigned char *)"",     // XC_Approx
  (unsigned char *)"",     // XC_Approx_e

  (unsigned char *)"tx",   // XC_Text // prijungti prie tevo
  (unsigned char *)"",     // XC_Text_e

  (unsigned char *)"",     // XC_Info
  (unsigned char *)"",     // XC_Info_e

  (unsigned char *)"le", // "hw", // XC_Expand
  (unsigned char *)"",     // XC_Expand_e

  (unsigned char *)"",     // XC_StructGroup,
  (unsigned char *)"",     // XC_StructGroup_e,

  (unsigned char *)"dc" /* "tw" */,   // XC_Gloss
  (unsigned char *)"",     // XC_Gloss_e

  (unsigned char *)"dc",   // XC_FwNote
  (unsigned char *)"",     // XC_FwNote_e

  (unsigned char *)"tx",   // XC_Italic // prijungti prie tevo
  (unsigned char *)"",     // XC_Italic_e

  (unsigned char *)"le", // "co",   // XC_ModCpdSrc
  (unsigned char *)"",     // XC_ModCpdSrc_e

  (unsigned char *)"",     // XC_Symb
  (unsigned char *)"",     // XC_Symb_e

  (unsigned char *)"la",   // XC_Inform
  (unsigned char *)"",     // XC_Inform_e
  (unsigned char *)"la",   // XC_Uncount
  (unsigned char *)"",     // XC_Uncount_e

  (unsigned char *)"",     // XC_PhrGroup
  (unsigned char *)"",     // XC_PhrGroup_e

  (unsigned char *)"",     // XC_CpdMngGroup
  (unsigned char *)"",     // XC_CpdMngGroup_e

  (unsigned char *)"la",   // XC_Obs
  (unsigned char *)"",     // XC_Obs_e
  (unsigned char *)"la",   // XC_Arch
  (unsigned char *)"",     // XC_Arch_e
  (unsigned char *)"la",   // XC_VeryInform
  (unsigned char *)"",     // XC_VeryInform_e
  (unsigned char *)"la",   // XC_Vulgar
  (unsigned char *)"",     // XC_Vulgar_e

  (unsigned char *)"tx",   // XC_Super // prijungti prie tevo
  (unsigned char *)"",     // XC_Super_e

  (unsigned char *)"la",   // XC_Count
  (unsigned char *)"",     // XC_Count_e

  (unsigned char *)"tx",   // XC_HiLight // prijungti prie tevo
  (unsigned char *)"",     // XC_HiLight_e
  (unsigned char *)"tx",   // XC_SemiBold // prijungti prie tevo
  (unsigned char *)"",     // XC_SemiBold_e

  (unsigned char *)"", // "sp",   // XC_CtrlDst, // buna kitu indexiniu tagu viduje - kol kas neiseina
  (unsigned char *)"",     // XC_CtrlDst_e,

  (unsigned char *)"dc", // "ic",   // XC_ExplNorm
  (unsigned char *)"",     // XC_ExplNorm_e

  (unsigned char *)"le", // "hw",   // XC_Struct,
  (unsigned char *)"",     // XC_Struct_e,
  (unsigned char *)"le", // "hw",   // XC_OblStruct,
  (unsigned char *)"",     // XC_OblStruct_e,

  (unsigned char *)"le",   // XC_Usage,
  (unsigned char *)"",     // XC_Usage_e,

  (unsigned char *)"" /* "hw" */,   // XC_HBase,
  (unsigned char *)"",     // XC_HBase_e,

  (unsigned char *)"",     // XC_ModCpdGroup
  (unsigned char *)"",     // XC_ModCpdGroup_e

  (unsigned char *)"tw",   // XC_ExampleTransl
  (unsigned char *)"",     // XC_ExampleTransl_e

  (unsigned char *)"tw",   // XC_IdiomTransl
  (unsigned char *)"",     // XC_IdiomTransl_e

  (unsigned char *)"", // "ed",   // XC_TechNote
  (unsigned char *)"",     // XC_TechNote_e

  (unsigned char *)"",     // XC_IdMngGroup
  (unsigned char *)"",     // XC_IdMngGroup_e

  (unsigned char *)"xr",   // XC_Refinf
  (unsigned char *)"",     // XC_Refinf_e

  (unsigned char *)"hw",   // XC_SrcWord,
  (unsigned char *)"",     // XC_SrcWord_e,

  (unsigned char *)"tw",   // XC_ModCpdDst
  (unsigned char *)"",     // XC_ModCpdDst_e

  (unsigned char *)"tw",   // XC_ContextDst
  (unsigned char *)"",     // XC_ContextDst_e

  (unsigned char *)"dc",   // XC_ExplDst
  (unsigned char *)"",     // XC_ExplDst_e

  (unsigned char *)"xr",   // XC_RefWord
  (unsigned char *)"",     // XC_RefWord_e

  (unsigned char *)"",     // XC_RefNum
  (unsigned char *)"",     // XC_RefNum_e

  (unsigned char *)"xr",   // XC_RefXWord
  (unsigned char *)"",     // XC_RefXWord_e

  (unsigned char *)"",     // XC_RefTab
  (unsigned char *)"",     // XC_RefTab_e

  (unsigned char *)"",     // XC_RefPage
  (unsigned char *)"",     // XC_RefPage_e

  (unsigned char *)"",     // XC_RefHom,
  (unsigned char *)"",     // XC_RefHom_e,

  (unsigned char *)"hw",   // XC_SingleCpdWord
  (unsigned char *)"",     // XC_SingleCpdWord_e

  (unsigned char *)"",     // XC_FormGroupDst
  (unsigned char *)"",     // XC_FormGroupDst_e

  (unsigned char *)"",     // XC_DerivGroup
  (unsigned char *)"",     // XC_DerivGroup_e

  (unsigned char *)"hw",   // XC_Derivative
  (unsigned char *)"",     // XC_Derivative_e

  (unsigned char *)"",     // XC_StressParGroup
  (unsigned char *)"",     // XC_StressParGroup_e

  (unsigned char *)"",     // XC_StressPar
  (unsigned char *)"",     // XC_StressPar_e

  (unsigned char *)"",     // XC_PunctMark
  (unsigned char *)"",     // XC_PunctMark_e

  (unsigned char *)"",     // XC_LevelGroup
  (unsigned char *)"",     // XC_LevelGroup_e

  (unsigned char *)"",     // XC_Level
  (unsigned char *)"",     // XC_Level_e

// (unsigned char *)"",     // XC_Text
// (unsigned char *)"",     // XC_Text_e

  (unsigned char *)"ic",   // XC_UsNoteSrc
  (unsigned char *)"",     // XC_UsNoteSrc_e

  (unsigned char *)"",     // XC_Img
  (unsigned char *)"",     // XC_Img_e

  (unsigned char *)"",     // XC_RefSecSynGr
  (unsigned char *)"",     // XC_RefSecSynGr_e
  (unsigned char *)"xr",   // XC_RefSecSyn
  (unsigned char *)"",     // XC_RefSecSyn_e

  (unsigned char *)"",     // XC_RefPriSynGr
  (unsigned char *)"",     // XC_RefPriSynGr_e
  (unsigned char *)"xr",   // XC_RefPriSyn
  (unsigned char *)"",     // XC_RefPriSyn_e

  (unsigned char *)"",     // XC_RefSynGr
  (unsigned char *)"",     // XC_RefSynGr_e
  (unsigned char *)"xr",   // XC_RefSyn
  (unsigned char *)"",     // XC_RefSyn_e

  (unsigned char *)"",     // XC_RefExamplGr
  (unsigned char *)"",     // XC_RefExamplGr_e
  (unsigned char *)"xr",   // XC_RefExampl
  (unsigned char *)"",     // XC_RefExampl_e

  (unsigned char *)"",     // XC_RefAntGr
  (unsigned char *)"",     // XC_RefAntGr_e
  (unsigned char *)"xr",   // XC_RefAnt
  (unsigned char *)"",     // XC_RefAnt_e

  (unsigned char *)"",     // XC_RefExamplSinglGr
  (unsigned char *)"",     // XC_RefExamplSinglGr_e

  (unsigned char *)"tx",   // XC_Subscript
  (unsigned char *)"",     // XC_Subscript_e

  (unsigned char *)"",     // XC_CodeExampleInline
  (unsigned char *)"",     // XC_CodeExampleInline_e

  (unsigned char *)"",     // XC_EnumGr
  (unsigned char *)"",     // XC_EnumGr_e

  (unsigned char *)"",     // XC_Enum
  (unsigned char *)"",     // XC_Enum_e

  (unsigned char *)"",     // XC_CodeBaseWord
  (unsigned char *)"",     // XC_CodeBaseWord_e

  (unsigned char *)"",     // XC_CodeExample
  (unsigned char *)"",     // XC_CodeExample_e

  (unsigned char *)"",     // XC_Table
  (unsigned char *)"",     // XC_Table_e
  (unsigned char *)"",     // XC_TableRow
  (unsigned char *)"",     // XC_TableRow_e
  (unsigned char *)"",     // XC_TableCell
  (unsigned char *)"",     // XC_TableCell_e

  (unsigned char *)"",     // XC_Equiation
  (unsigned char *)"",     // XC_Equiation_e

  (unsigned char *)"",     // XC_Break
  (unsigned char *)"",     // XC_Break_e

  (unsigned char *)"",     // XC_EquInline
  (unsigned char *)"",     // XC_EquInline_e

  (unsigned char *)"",     // XC_Special
  (unsigned char *)"",     // XC_Special_e

  (unsigned char *)"",     // XC_ExampleGroupForced
  (unsigned char *)"",     // XC_ExampleGroupForced_e

  (unsigned char *)"dc", // "ic",   // XC_ExplForced
  (unsigned char *)"",     // XC_ExplForced_e

  (unsigned char *)"",     // XC_VarGroup
  (unsigned char *)"",     // XC_VarGroup_e

  (unsigned char *)"",     // XC_Relatives
  (unsigned char *)"",     // XC_Relatives_e

  (unsigned char *)"", // "tx",   // XC_Page // prijungti prie tevo
  (unsigned char *)"",     // XC_Page_e

  (unsigned char *)"",     // XC_SemNr
  (unsigned char *)"",     // XC_SemNr_e

  (unsigned char *)"tw",   // XC_TrWordLit
  (unsigned char *)"",     // XC_TrWordLit_e

  (unsigned char *)"tw",   // XC_TrWordEng
  (unsigned char *)"",     // XC_TrWordEng_e

  (unsigned char *)"tw",   // XC_TrWordGer
  (unsigned char *)"",     // XC_TrWordGer_e

  (unsigned char *)"tw",   // XC_TrWordFre
  (unsigned char *)"",     // XC_TrWordFre_e

  (unsigned char *)"tw",   // XC_TrWordPol
  (unsigned char *)"",     // XC_TrWordPol_e

  (unsigned char *)"tw",   // XC_TrWordRus
  (unsigned char *)"",     // XC_TrWordRus_e

  (unsigned char *)"", // "hw",   // XC_Species
  (unsigned char *)"",     // XC_Species_e

  (unsigned char *)"",     // XC_StructGroupForced
  (unsigned char *)"",     // XC_StructGroupForced_e

  (unsigned char *)"le", // "hw",   // XC_VarBold
  (unsigned char *)"",     // XC_VarBold_e

  (unsigned char *)"",     // XC_RefAntStrictGr
  (unsigned char *)"",     // XC_RefAntStrictGr_e
  (unsigned char *)"xr",   // XC_RefAntStrict
  (unsigned char *)"",     // XC_RefAntStrict_e

};


// ======================================================
XmlI::XmlI
(
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
   const unsigned char **plpszaXmlSpCharTags,
   const unsigned char **lppszFileIndexNames,
   const int *aiFileIndexLengths,
   const unsigned char *acIndexLangs,
   const EC_Types *aiIndexEncs,
   KpChar iFirstTag,
   const unsigned char **plpszaTags,
   XmlVersions iVersion,
   const int *piaCodeTables,
   bool bMultiLine,
   bool bMapToPrivate,
   bool bProcessSubkeys
)
{
HRESULT retc = S_OK;
const unsigned char **pntss;
int ii, jj;

// ---------------------------
   m_lhOpenResult = S_OK;
   FilePtr=NULL;
   lpszFName[0]=Nul;
   pCurIndexBuf=NULL;
   pCurTxIndexBuf=NULL;
   m_iInsideOfXr=0;
   iCurIxTag=0;
   lEntryId=0L;
   iFirstDictTag=(KpChar)XC_FirstDictTag;
   iLastDictTag=(KpChar)XC_LastDictTag;
   for(ii=0; ii<XC_TG_NumOfDictTags00; ii++) aiXmlTagIxIx[ii]=0;
   lpTagStack=NULL;
   lpiazBaseSav[0]=C_Nul;
   bPutToBase=False;

// ---------------------------
   plpszaTagNames=plpszaTags;
   if(plpszaTagNames==NULL) plpszaTagNames=plpszaDefTagNames;
   iFirstDictTag=iFirstTag;
   pntss=plpszaTags;
   if(pntss!=NULL) while(*pntss) pntss++;
   iLastDictTag=(KpChar)(iFirstTag+(pntss-plpszaTags));
#if FALSE
   if(SUCCEEDED(retc))
      if(
         ((iFirstDictTag != XC_FirstDictTag) || (iLastDictTag != XC_LastDictTag)) // &&
//       ((iFirstDictTag != HTM_TG_FirstTag) || (iLastDictTag != HTM_TG_LastTag))
        )
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
#endif

// ---------------------------
   if(SUCCEEDED(retc))
   {
      if((lppszFileIndexNames!=NULL) && (aiFileIndexLengths!=NULL))
      {
         lppszFileIndexNamesPtr=lppszFileIndexNames;
         aiFileIndexLengthsPtr=aiFileIndexLengths;
      }
      else
      {
         lppszFileIndexNamesPtr=lppszFileIndexNamesFict;
         aiFileIndexLengthsPtr=aiFileIndexLengthsFict;
         if((lppszFileIndexNames!=NULL) || (aiFileIndexLengths!=NULL))
            retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      iNumOfIndexes=0;
      pntss=lppszFileIndexNamesPtr;
      while(*pntss) { pntss++; iNumOfIndexes++;}
      if((iNumOfIndexes<XL_IX_DefSeIndex) || (iNumOfIndexes>XL_IX_MaxNumOfIndexes))
      {
         iNumOfIndexes=XL_IX_MaxNumOfIndexes;
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) for(ii=0; ii<XC_TG_NumOfDictTags00; ii++)
   {
      if(lpszaXmlTagIxNames[ii])
         if((strlen(lpszaXmlTagIxNames[ii])!=0) && (strcmp(lpszaXmlTagIxNames[ii], "tx") != 0))
         {
            for(jj=0; jj<iNumOfIndexes; jj++)
            {
               if(strcmp(lpszaXmlTagIxNames[ii], lppszFileIndexNamesPtr[jj])==0)
               {
                  aiXmlTagIxIx[ii]=jj;
                  break;
               }
            }
         }
   }

   acIndexLanguages=acIndexLangs;
   if((acIndexLanguages==NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   aiIndexEncodings=aiIndexEncs;
   if((aiIndexEncodings==NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// ---------------------------
   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszFileName)<KP_MAX_FNAME_LEN) strcpy((char *)lpszFName, (const char *)lpszFileName);
      else retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

// ---------------------------
// XML data file
   KP_NEWO(FilePtr, XmlO1(lpszFName, lpszMode, CreateLowLevelObj,
               plpszaXmlSpCharTags,
               lppszFileIndexNamesPtr, aiFileIndexLengthsPtr,
               iFirstDictTag, plpszaTags, False,
               iVersion, piaCodeTables, bMultiLine, bMapToPrivate));

// ---------------------------
// tag stack
   KP_NEW(lpTagStack, TvXmlTagStack(NULL, C_Nul, NULL, 0));

   m_bProcessSubkeys = bProcessSubkeys;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ---------------------------
XmlI::~XmlI()
{
HRESULT retc = S_OK;
TvXmlTagStack *prev_stack_ptr;
KpChar cur_tag;

   CloseFile(False);

   if(lpTagStack != NULL)
   {
      lpTagStack->GetPrevTagPtr(&prev_stack_ptr);
      lpTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

      KP_DELETE(lpTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// -------------------------------
HRESULT XmlI::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// -------------------------------
HRESULT XmlI::GetFileMode(bool *pbBinFl, bool *pbWriteFl, bool *pbAppendFl)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetFileMode(pbBinFl, pbWriteFl, pbAppendFl);

return(retc);
}


// -------------------------------
HRESULT XmlI::GetEncoding(UC_Modes *piEncMode, int *piCodeTable, int *piDefCodeTable)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetEncoding(piEncMode, piCodeTable, piDefCodeTable);

return(retc);
}


// -------------------------------
HRESULT XmlI::SetEncoding(UC_Modes iEncMode, int iCodeTable, int iDefCodeTable)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SetEncoding(iEncMode, iCodeTable, iDefCodeTable);

return(retc);
}


// -------------------------------
HRESULT XmlI::GetVersion(XmlVersions *piVersion)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetVersion(piVersion);

return(retc);
}


// -------------------------------
HRESULT XmlI::SetPathMode(XL_PathMode iPathMode)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SetPathMode(iPathMode);

return(retc);
}

XL_PathMode XmlI::GetPathMode(void)
{
HRESULT retc=S_OK;
XL_PathMode reti = XL_RelativePath;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      reti=FilePtr->GetPathMode();

return(reti);
}

// -------------------------------
HRESULT XmlI::SetScale(int iScale)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SetScale(iScale);

return(retc);
}

int XmlI::GetScale(void)
{
HRESULT retc=S_OK;
int reti = 10;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      reti=FilePtr->GetScale();

return(reti);
}

// -------------------------------
HRESULT XmlI::Reset(void)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->Reset();

return(retc);
}


// -------------------------------
HRESULT XmlI::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if((FilePtr==NULL) && bCheckFileExist)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(pCurIndexBuf!=NULL)
   {
      if(SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

      KP_DELETE(pCurIndexBuf);
   }
   iCurIxTag=0;
   m_iInsideOfXr=0;

   if(pCurTxIndexBuf!=NULL)
   {
      if(SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

      KP_DELETE(pCurTxIndexBuf);
   }

   if(FilePtr!=NULL)
   {
      retc=FilePtr->CloseFile(bCheckFileExist);

      KP_DELETE(FilePtr);
   }

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::GetCharProc(KpChar *piInch, XmlTagPars **pTagParsPtr, bool bCheckFeof, bool bProcSpcEol)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetCharProc(piInch, pTagParsPtr, XL_IX_DataFile, bCheckFeof, bProcSpcEol);

return(retc);
}


// -------------------------------
HRESULT XmlI::UnGetCharProc(KpChar iOutch, XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->UnGetCharProc(iOutch, pTagPars, XL_IX_DataFile);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::GetNumVal(long *plValue, bool bCheckFeof)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetNumVal(plValue, XL_IX_DataFile, bCheckFeof);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::SkipEol(void)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SkipEol(XL_IX_DataFile);

return(retc);
}


// -------------------------------
HRESULT XmlI::SkipSpaces(void)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SkipSpaces(XL_IX_DataFile);

return(retc);
}


// -------------------------------
HRESULT XmlI::SkipToCharProc(KpChar uiDelimCh)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SkipToCharProc(uiDelimCh, XL_IX_DataFile);

return(retc);
}


// ======================================================
HRESULT XmlI::PutChar(KpChar iOutch, XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;
bool multiline_sav;

   if(SUCCEEDED(retc)) retc=FilePtr->m_fFiles[XL_IX_DataFile]->GetMultiline(&multiline_sav);

   if(
      (
         (iOutch==XL_Version) ||
         (iOutch==XL_DocType) ||
         (iOutch==XL_StyleSheet) ||
         (iOutch==XC_Dict) ||
         (iOutch==XC_Dict_e)
      ) &&
      SUCCEEDED(retc)
     )
     retc=FilePtr->m_fFiles[XL_IX_DataFile]->SetMultiline(True);

   if(
      (iOutch==XC_Dict_e) &&
      (!multiline_sav) &&
      SUCCEEDED(retc)
     )
      retc=FilePtr->PutCharProc(C_Lf, NULL, XL_IX_DataFile);

   if(SUCCEEDED(retc)) retc=FilePtr->PutCharProc(iOutch, pTagPars, XL_IX_DataFile);

   if(
      (
         (iOutch==XC_StEntry_e) ||
         (iOutch==XC_NrtEntry_e)
      ) &&
      (!multiline_sav) &&
      SUCCEEDED(retc)
     )
      retc=FilePtr->PutCharProc(C_Lf, NULL, XL_IX_DataFile);

   if(SUCCEEDED(retc)) retc=FilePtr->m_fFiles[XL_IX_DataFile]->SetMultiline(multiline_sav);

return(retc);
}


// -------------------------------
// ar itraukia <tw> is <cg>, <sg> ir kt. i indexa? Cia kazka buriu tik su <eg> ir <id> !!!
HRESULT XmlI::PutCharProc(KpChar iOutch, XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;
long lpar;
int ii;
bool put_ix=True;
const unsigned char *pnts;
KpChar cur_tag;
unsigned char out_str[TV_XL_HW_IX_LEN+KP_MAX_FILE_LIN_WDT+1];
bool ix_delim;
int ix_lang;
int min_len;
XmlVersions file_vers;

   if((lpTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if((FilePtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(FilePtr->m_fFiles[XL_IX_DefDataFile]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetCharNum(&lpar);

   if(SUCCEEDED(retc)) retc=FilePtr->m_fFiles[XL_IX_DefDataFile]->GetVersion(&file_vers);

   if(SUCCEEDED(retc)) retc=lpTagStack->GetCurTag(&cur_tag);

// output to data file
   if(SUCCEEDED(retc))
   {
      if(file_vers < XM_VERS_HTML) // ==XM_VERS_SGML_TAGE
      {
         switch(iOutch)
         {
#if FALSE
            case C_o_Slash:   // XC_Inform
            case C_Multipl:   // XC_VeryInform
            case C_Rouble:    // XC_Vulgar
            case C_cent:      // XC_Uncount
//          case C_c:         // XC_Count
            case C_PlMin:     // XC_Approx
//          case C_Eq:        // XC_Similar
            case C_Dag:       // XC_Obs
            case C_Ddag:      // XC_Arch
            case C_Ast:       // XC_Asterix
            case C_Pound:
#endif
            case C_Dots:
               if((cur_tag!=XC_Symb) && SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(iOutch, pTagPars);
               if((cur_tag!=XC_Symb) && SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;

            case XC_Inform:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_o_Slash, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_VeryInform:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Multipl, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Vulgar:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Rouble, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Uncount:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_cent, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Count:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_c, pTagPars); // 'c'
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Approx:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_PlMin, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Similar:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Eq, pTagPars); // '='
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Obs:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Dag, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Arch:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Ddag, pTagPars);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;
            case XC_Asterix:
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(C_Ast, pTagPars); // '*'
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;

            case C_deg:
            case C_Pound:
            case C_RO:
               if((cur_tag!=XC_Symb) && SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb, NULL);
               if(SUCCEEDED(retc)) retc=PutChar(iOutch, pTagPars);
               if((cur_tag!=XC_Symb) && SUCCEEDED(retc)) retc=PutCharProc((KpChar)XC_Symb_e, NULL);
               break;

            case C_break:  retc=PutChar(C_Circ, pTagPars); break; // '^'
            case C_Ff:     retc=PutChar(C_At, pTagPars); break; // '@'
            case C_hyph:   retc=PutChar(C_Lslash, pTagPars); break; // '\\'
            case C_hhyph:  retc=PutChar(C_Amp, pTagPars); break; // '&'
//          case C_EnSpc:  retc=PutChar(C_Underl, pTagPars); break; // '_'
            case C_NBSP:   retc=PutChar(C_Underl, pTagPars); break; // '_'
            case C_QemSpc: retc=PutChar(C_Numb, pTagPars); break; // '#'

            case XC_PartOfSpeechDst: retc=PutChar((KpChar)XC_PartOfSpeechSrc, pTagPars); break;
            case XC_PartOfSpeechDst_e: retc=PutChar((KpChar)XC_PartOfSpeechSrc_e, pTagPars); break;

            case XC_CompoundWord: retc=PutChar((KpChar)XC_SrcWord, pTagPars); break;
            case XC_CompoundWord_e: retc=PutChar((KpChar)XC_SrcWord_e, pTagPars); break;
            case XC_Derivative: retc=PutChar((KpChar)XC_SrcWord, pTagPars); break;
            case XC_Derivative_e: retc=PutChar((KpChar)XC_SrcWord_e, pTagPars); break;

            case XC_Idiom: retc=PutChar((KpChar)XC_Example, pTagPars); break;
            case XC_Idiom_e: retc=PutChar((KpChar)XC_Example_e, pTagPars); break;
            case XC_Struct: retc=PutChar((KpChar)XC_Example, pTagPars); break;
            case XC_Struct_e: retc=PutChar((KpChar)XC_Example_e, pTagPars); break;
            case XC_OblStruct: retc=PutChar((KpChar)XC_Example, pTagPars); break;
            case XC_OblStruct_e: retc=PutChar((KpChar)XC_Example_e, pTagPars); break;
            case XC_Usage: retc=PutChar((KpChar)XC_Example, pTagPars); break;
            case XC_Usage_e: retc=PutChar((KpChar)XC_Example_e, pTagPars); break;

            default: retc=PutChar(iOutch, pTagPars); break;
         }

      } // if(file_vers < XM_VERS_HTML)
      else
         retc=PutChar(iOutch, pTagPars);

   } // if(SUCCEEDED(retc))

// if(iOutch==XC_Base)
// iOutch=XC_Base;

// index output
   if((iOutch!=XC_Italic) && (iOutch!=XC_Italic_e) && SUCCEEDED(retc))
   {
      if((iOutch>=iFirstDictTag) && (iOutch<iLastDictTag))
      {
// <tw> inside of <eg> and <id>
         if((iOutch==XC_TrWord) || (iOutch==XC_TrWord_e))
         {
            ii=0;
            do
            {
               retc=GetStackTag(lpTagStack, ii++, &cur_tag);
            } while
              (
               (cur_tag!=XC_HeadWordGroup) &&
               (cur_tag!=XC_ExampleGroup) &&
               (cur_tag!=XC_IdiomGroup) &&
               (cur_tag!=C_Nul) &&
               SUCCEEDED(retc)
              );

            if(SUCCEEDED(retc))
            {
               if(cur_tag==XC_ExampleGroup)
               {
                  if(iOutch==XC_TrWord) iOutch=(KpChar)XC_ExampleTransl;
                  else iOutch=(KpChar)XC_ExampleTransl_e;
               }
               if(cur_tag==XC_IdiomGroup)
               {
                  if(iOutch==XC_TrWord) iOutch=(KpChar)XC_IdiomTransl;
                  else iOutch=(KpChar)XC_IdiomTransl_e;
               }
            }
         }

// tag stack processing
         if((strcmp((const char *)plpszaTagNames[(iOutch&(~1))+1-iFirstDictTag], "")!=0) && SUCCEEDED(retc))
         {
            if((iOutch & 0x01) == 0) retc=PushTag(&lpTagStack, iOutch, NULL, 0);
            else
            {
               retc=PopTag(&lpTagStack, &cur_tag);
               if(cur_tag != (iOutch & (~0x01)))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            }
         }

// base word buffer
         if(((iOutch==XC_StEntry) || (iOutch==XC_NrtEntry)) && SUCCEEDED(retc))
            lpiazBaseSav[0]=C_Nul;

// !!! process subtags of XC_Base & XC_HeadWord !!!
         bPutToBase=False;
         if(((iOutch==XC_Base) || (iOutch==XC_HBase)) && SUCCEEDED(retc))
         {
            lpiazBaseSav[0]=C_Nul;
            bPutToBase=True;
         }
         if((iOutch==XC_HeadWord) && (lpiazBaseSav[0]==C_Nul) && SUCCEEDED(retc))
            bPutToBase=True;

// start tag of index entry
         if(SUCCEEDED(retc)) retc=GetStackTag(lpTagStack, 1, &cur_tag);

// if(iOutch==XC_TechNote)
// iOutch=XC_TechNote;

         if(
            (aiXmlTagIxIx[iOutch-iFirstDictTag]!=0) &&
            ((iOutch!=XC_TechNote) || (cur_tag==XC_HeadWordGroup)) &&
            (iCurIxTag==0) &&
            SUCCEEDED(retc)
           )
         {
            if(pCurIndexBuf!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               iCurIxTag = iOutch;
               KP_NEW(pCurIndexBuf, XmlIs_IndexRecord(FilePtr, aiXmlTagIxIx[iOutch-iFirstDictTag], lEntryId,
                  False, True, True, m_bProcessSubkeys,
                  acIndexLanguages[aiXmlTagIxIx[iOutch-iFirstDictTag]],
//                aiIndexEncodings[aiXmlTagIxIx[iOutch-iFirstDictTag]],
                  1));

               m_iInsideOfXr = 0;
            }

            put_ix=False;
         }

// <se> - parameter to index
         if((iOutch==XC_StEntry) && (iOutch==iCurIxTag) && SUCCEEDED(retc))
         {
            if(pCurIndexBuf==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if(pTagPars==NULL)
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
               }
               else
               {
                  if(SUCCEEDED(retc)) retc=pTagPars->SeekNumPar("id", &lEntryId, &ii);
                  if(SUCCEEDED(retc)) retc=FilePtr->PutNumVal(lEntryId, aiXmlTagIxIx[iOutch-iFirstDictTag]);
                  if(SUCCEEDED(retc)) retc=FilePtr->PutNumVal(lpar, aiXmlTagIxIx[iOutch-iFirstDictTag]);
                  if(SUCCEEDED(retc)) retc=FilePtr->PutCharProc(C_Lf, NULL, aiXmlTagIxIx[iOutch-iFirstDictTag]); // '\n'

                  put_ix=False;
               }
            }
         }

// single tags as indexes - put tag name to index
         if(SUCCEEDED(retc))
         {
            if((strlen(plpszaTagNames[(iOutch-iFirstDictTag)|0x01])==0) && (iOutch==iCurIxTag))
            {
               if(pCurIndexBuf==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

               if((!m_iInsideOfXr) && SUCCEEDED(retc))
               {
                  pnts=plpszaTagNames[iOutch-iFirstDictTag];
                  if(*pnts==TV_XM_TagStartCh /* '<' */) pnts++;
                  while((*pnts!=TV_XM_TagEndCh /* '>' */) && (*pnts!=TV_XM_EndTagIndCh /* '/' */) && (*pnts!=Nul) && SUCCEEDED(retc))
                     retc=pCurIndexBuf->PutChar((KpChar)(*pnts++));
               }

               put_ix=False;
            }
         }

// end tag of index entry
         if(SUCCEEDED(retc))
         {
            if(
               (
                  (iOutch==(iCurIxTag|0x01)) ||
                  ((iOutch==XC_StEntry) && (iOutch==iCurIxTag)) ||
                  ((strlen(plpszaTagNames[(iOutch-iFirstDictTag)|0x01])==0) && (iOutch==iCurIxTag))
               ) &&
               SUCCEEDED(retc)
              )
            {
               if(pCurIndexBuf==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
                  retc = pCurIndexBuf->CompleteIndexRecord(True);

                  KP_DELETE(pCurIndexBuf);
                  iCurIxTag = 0;
               }
            }
         }

      } // if((iOutch>=iFirstDictTag) && (iOutch<iLastDictTag) && SUCCEEDED(retc))
      else
      {
// base word contents
         retc=lpTagStack->GetCurTag(&cur_tag);
         if(iOutch==(KpChar)TV_XM_CompDelim) bPutToBase=False;
         if((bPutToBase || (cur_tag==XC_Base) || (cur_tag==XC_HBase)) && SUCCEEDED(retc))
         {
            ii=(-1);
            while(lpiazBaseSav[++ii]!=C_Nul);
            if(ii<TV_XL_HW_IX_LEN)
            {
               lpiazBaseSav[ii++]=iOutch;
               lpiazBaseSav[ii++]=C_Nul;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
         }

      } // else // if((iOutch>=iFirstDictTag) && (iOutch<iLastDictTag) && SUCCEEDED(retc))

      if((iCurIxTag!=0) && put_ix && SUCCEEDED(retc))
      {

// tags inside of index to '(' and ')'
         if((iOutch>=iFirstDictTag) && (iOutch<iLastDictTag) && SUCCEEDED(retc))
         {
            if(strlen(plpszaTagNames[(iOutch-iFirstDictTag)|0x01])==0) // single tags - no output
               iOutch=C_Nul;
            else if((iOutch==XC_Reference) /* || (iOutch==XC_TechNote) */) m_iInsideOfXr++;
            else if((iOutch==XC_Reference_e) /* || (iOutch==XC_TechNote_e) */) m_iInsideOfXr--;
//          else if((iOutch==XC_TechNote) || (iOutch==XC_Level)) iOutch = (KpChar)MC_LeftBracket; // C_Lbrack // '['
//          else if((iOutch==XC_TechNote_e) || (iOutch==XC_Level_e)) iOutch = (KpChar)MC_RightBracket; // C_Rbrack // ']'
            else
            {
KpChar out_ch;
               if((iOutch & 0x01)==0) out_ch = (KpChar)MC_LeftParenthese; // C_Lpar; // '(' double tags - convert to parentheses for further parentheses processing
               else out_ch = (KpChar)MC_RightParenthese; // C_Rpar; // ')'

               if(lpszaXmlTagIxNames[(iOutch & (~0x01)) - iFirstDictTag]!=NULL)
               {
                  if(strlen(lpszaXmlTagIxNames[(iOutch & (~0x01)) - iFirstDictTag]) == 0)
                  {
                     if((iOutch & 0x01)==0) out_ch = (KpChar)MC_LeftBracket; // C_Lbrack // '['
                     else out_ch = (KpChar)MC_RightBracket; // C_Rbrack // ']'
                  }
                  else if(strcmp(lpszaXmlTagIxNames[(iOutch & (~0x01)) - iFirstDictTag], "tx") != 0)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, plpszaXmlttDictTags[iOutch & (~0x01) - iFirstDictTag], False, __FILE__, __LINE__, 0L);
               }
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

               iOutch = out_ch;
            }
         }

// index contents
         if((pCurIndexBuf==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);

         if((!m_iInsideOfXr) && SUCCEEDED(retc)) switch(iOutch)
         {
         case TV_XM_CompBaseChar: // '~'
            if(lpiazBaseSav[0]!=C_Nul)
            {
               ii=0;
               while((lpiazBaseSav[ii]!=C_Nul) && SUCCEEDED(retc))
                  retc=pCurIndexBuf->PutChar(lpiazBaseSav[ii++]);
            }
            else
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, "Nëra bazës", False, __FILE__, __LINE__, 0L);
               sprintf((char *)out_str, "Lizdas %ld, hw:%s : Nëra bazës\n", KpErrorProc.lMsgPar, KpErrorProc.szaMsgText);
               printf((const char *)out_str);
            }
            break;

         case C_Nul: break; // single tags - no output

         default: retc=pCurIndexBuf->PutChar(iOutch); break;
         }

      } // if((iCurIxTag!=0) && put_ix && SUCCEEDED(retc))

//------------------------------
// TX index
      if(SUCCEEDED(retc))
      {
         ix_delim=False;
         if((iOutch>=iFirstDictTag) && (iOutch<iLastDictTag)) ix_delim=True;
         if(TvStrChr(lpszWordDelims, iOutch)!=NULL) ix_delim=True;

         if(ix_delim)
         {
// close previous TX index entry
            if(pCurTxIndexBuf!=NULL)
            {

#ifdef Debug
if(iOutch==C_Spc)
{
GetStackTag(lpTagStack, 0, &cur_tag);
if(cur_tag==(KpChar)XC_Example)
cur_tag=(KpChar)XC_Example;
}
#endif

               retc=pCurTxIndexBuf->CompleteIndexRecord(True);

               KP_DELETE(pCurTxIndexBuf);
            }

// open next TX index entry
            ix_lang=KP_LNG_UP;
            ii=0;
            if(
               (
                  ((iOutch >= iFirstDictTag) && (iOutch < iLastDictTag)) ||
                  ((iOutch >= XL_FirstSysTag) && (iOutch < XL_LastSysTag))
               )
              ) cur_tag=iOutch;
            else
               retc=GetStackTag(lpTagStack, ii++, &cur_tag);

            if(SUCCEEDED(retc)) do
            {
//             if(SUCCEEDED(retc))
//                if(((cur_tag<iFirstDictTag) || (cur_tag>=iLastDictTag)) && (cur_tag!=0) && SUCCEEDED(retc))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc)) ix_lang = GetTagLang(cur_tag);

               if(SUCCEEDED(retc))
                  retc=GetStackTag(lpTagStack, ii++, &cur_tag);

            } while((ix_lang==KP_LNG_UP) && SUCCEEDED(retc));

            if(((ix_lang!=KP_LNG_NA) || (cur_tag==XC_Label)) && SUCCEEDED(retc))
            {
               min_len=2;
               if((cur_tag==XC_FormSrc) || (cur_tag==XC_FormDst)) min_len=3;
               KP_NEW(pCurTxIndexBuf, XmlIs_IndexRecord(FilePtr, XL_IX_TxIndex, lEntryId,
                  False, True, True, m_bProcessSubkeys,
#ifdef XL_TX_GRAM
                  ix_lang,
#else
                  caIxLangs[XL_IX_TxIndex],
#endif
//                aiIndexEncodings[XL_IX_TxIndex],
                  min_len));
            }

         } // if(ix_delim)
         else
         {
// TX index contents
            if(pCurTxIndexBuf)
            {
               switch(iOutch)
               {
               case TV_XM_CompBaseChar: // '~'
                  if(lpiazBaseSav[0]!=C_Nul)
                  {
                     ii=0;
                     while((lpiazBaseSav[ii]!=C_Nul) && SUCCEEDED(retc))
                        retc=pCurTxIndexBuf->PutChar(lpiazBaseSav[ii++]);
                  }
                  else
                  {
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, "N?ra baz?s", False, __FILE__, __LINE__, 0L);
                     sprintf((char *)out_str, "Lizdas %ld, hw:%s : N?ra baz?s\n", KpErrorProc.lMsgPar, KpErrorProc.szaMsgText);
                     printf((const char *)out_str);
                  }
                  break;

               case C_Nul: break; // single tags - no output

               default:
#ifdef Debug
GetStackTag(lpTagStack, 0, &cur_tag);
if(cur_tag==(KpChar)XC_Example)
cur_tag=(KpChar)XC_Example;
#endif
                  retc=pCurTxIndexBuf->PutChar(iOutch);
                  break;
               }

            } // if(pCurTxIndexBuf)

         } // else // if(ix_delim)

      } // if(SUCCEEDED(retc))

   } // if((iOutch!=XC_Italic) && (iOutch!=XC_Italic_e) && SUCCEEDED(retc))

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::PutStr(const unsigned char *lpszOutstr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   if(lpszOutstr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszOutstr;

      while(*pnts && SUCCEEDED(retc))
         retc=PutCharProc((KpChar)(*pnts++), NULL);
   }

// if(SUCCEEDED(retc))
//    retc=FilePtr->PutStr(lpszOutstr, XL_IX_DataFile);

return(retc);
}


// -------------------------------
HRESULT XmlI::PutKpStr(const KpChar *iazOutstr)
{
HRESULT retc=S_OK;
const KpChar *pnts;

   if(iazOutstr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=iazOutstr;

      while(*pnts && SUCCEEDED(retc))
         retc=PutCharProc(*pnts++, NULL);
   }

// if(SUCCEEDED(retc))
//    retc=FilePtr->PutIntStr(iazOutstr, XL_IX_DataFile);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::PutNumVal(const long lValue)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->PutNumVal(lValue, XL_IX_DataFile);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetCharPos(piCharPos, XL_IX_DataFile);

return(retc);
}


// -------------------------------
HRESULT XmlI::GetCharNum(long *plCharNum)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetCharNum(plCharNum, XL_IX_DataFile);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::SetBaseIndent(const unsigned char *lpszBaseIndent)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(lpszBaseIndent == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SetBaseIndent(lpszBaseIndent, XL_IX_DataFile);

return(retc);
}


HRESULT XmlI::GetBaseIndent(const unsigned char **plpszBaseIndentPtr)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(plpszBaseIndentPtr == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetBaseIndent(plpszBaseIndentPtr, XL_IX_DataFile);

return(retc);
}


HRESULT XmlI::SetIndent(const unsigned char *lpszIndent)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(lpszIndent == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SetIndent(lpszIndent, XL_IX_DataFile);

return(retc);
}


// ======================================================
HRESULT ConvTagStrict(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) switch(*piCurTag)
   {
   case XC_ExampleTransl: *piCurTag=(KpChar)XC_TrWord; break;
   case XC_IdiomTransl: *piCurTag=(KpChar)XC_TrWord; break;
   case XC_IdMngGroup: *piCurTag=(KpChar)XC_MngGroup; break;
   case XC_CpdMngGroup: *piCurTag=(KpChar)XC_MngGroup; break;
   }

return(retc);
}


// -------------------------------
HRESULT XmlI::GetCurTagStrict(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((lpTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpTagStack->GetCurTag(piCurTag);

   if(SUCCEEDED(retc)) retc=ConvTagStrict(piCurTag);

return(retc);
}


// ======================================================
// -------------------------------
HRESULT XmlI::SearchEntry
(
long *plEntryIdx,
long *plOffset,
const unsigned char *lpszKeyword,
int iFileIndex,
bool bTestNotFound
)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SearchEntry(plEntryIdx, plOffset, lpszKeyword, iFileIndex, bTestNotFound);

return(retc);
}


//-------------------------------------
HRESULT XmlI::SearchEntryFirst
(
long *plEntryIdx,
long *plOffset,
const unsigned char *lpszKeyword,
int iFileIndex,
bool bTestNotFound
)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SearchEntryFirst(plEntryIdx, plOffset, lpszKeyword, iFileIndex, bTestNotFound);

return(retc);
}


// -------------------------------
HRESULT XmlI::GetImage(void *lpBuffer, const int iByteCount, int iFileIndex, bool bCheckFeof)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->GetImage(lpBuffer, iByteCount, iFileIndex, bCheckFeof);

return(retc);
}


// -------------------------------
HRESULT XmlI::Fseek(int iFileIndex, const long lOffset, int iOrigin)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->Fseek(iFileIndex, lOffset, iOrigin);

return(retc);
}


// -------------------------------
HRESULT XmlI::Ftell(int iFileIndex, long *plOffset)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->Ftell(iFileIndex, plOffset);

return(retc);
}


// -------------------------------
HRESULT XmlI::SeekEntry(const long lEntryIdx, long *plEntryLen)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->SeekEntry(lEntryIdx, plEntryLen);

return(retc);
}

// -------------------------------
HRESULT XmlI::ReadEntryImg(long lEntryIdx, unsigned char **plpszEntryImg, long *plEntryLen)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->ReadEntryImg(lEntryIdx, plpszEntryImg, plEntryLen);

return(retc);
}


// -------------------------------
HRESULT XmlI::PutImage(const void *lpBuffer, int iByteCount, int iFileIndex)
{
HRESULT retc=S_OK;

   if(FilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=FilePtr->PutImage(lpBuffer, iByteCount, iFileIndex);

return(retc);
}
