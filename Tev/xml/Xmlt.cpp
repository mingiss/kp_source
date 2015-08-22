// ==================================================
// xmlt.cpp
// XML dictionary file speciffic fields (index tags etc.)
//

// ================================================== definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>
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

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxmle.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlg.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvtex.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "KpFileSys.h"
#include "xmln.h"


// ================================================== static fields
const unsigned char *alpszIndexNames[XL_IX_NumOfIndexes3+1] =
{
   (unsigned char *)"",      // XL_IX_DataFile,

   (unsigned char *)"se",    // XL_IX_SeIndex,

   (unsigned char *)"hw",    // XL_IX_HwIndex,
   (unsigned char *)"tw",    // XL_IX_TwIndex,
   (unsigned char *)"la",    // XL_IX_LaIndex,
   (unsigned char *)"st",    // XL_IX_StIndex,
   (unsigned char *)"ed",    // XL_IX_EdIndex,

   (unsigned char *)"tx",    // XL_IX_TxIndex,
   (unsigned char *)"hx",    // XL_IX_HxIndex,

   NULL
};


// --------------------------------------------------
const unsigned char *alpszDefIndexNames[XL_IX_NumOfIndexes3+1] =
{
   (unsigned char *)"",      // XL_IX_DataFile,

   (unsigned char *)"",      // XL_IX_SeIndex,

   (unsigned char *)"",      // XL_IX_HwIndex,
   (unsigned char *)"",      // XL_IX_TwIndex,
   (unsigned char *)"",      // XL_IX_LaIndex,
   (unsigned char *)"",      // XL_IX_StIndex,
   (unsigned char *)"",      // XL_IX_EdIndex,

   (unsigned char *)"",      // XL_IX_TxIndex,
   (unsigned char *)"",      // XL_IX_HxIndex,

   NULL
};


// --------------------------------------------------
const int aiIndexWidths[XL_IX_NumOfIndexes3] =
{
   0,                                                          // XL_IX_DataFile,

   2*sizeof(long),                                             // XL_IX_SeIndex,
// text file line format:    id   offset
// binary file: [offset, size] pairs for each entry id, [MAXLONG, 0] means no entry for this entry id

   TV_XL_HW_IX_LEN+sizeof(long),                               // XL_IX_HwIndex,
   TV_XL_HW_IX_LEN+sizeof(long),                               // XL_IX_TwIndex,
   TV_XL_LA_IX_LEN+sizeof(long),                               // XL_IX_LaIndex,
   TV_XL_LA_IX_LEN+sizeof(long), // TV_XL_NUM_LEN+sizeof(long) // XL_IX_StIndex,
   TV_XL_LA_IX_LEN+sizeof(long),                               // XL_IX_EdIndex,

   TV_XL_TX_IX_LEN+sizeof(long),                               // XL_IX_TxIndex,
   TV_XL_HW_IX_LEN+sizeof(long),                               // XL_IX_HxIndex,

};


// --------------------------------------------------
const EC_Types iaIxEncodings[XL_IX_NumOfIndexes3] =
{
   EC_UTF_8,   // XML data file
   EC_ASCII,   // XL_IX_SeIndex,       // standard entry index file
   EC_ASCII,   // XL_IX_HwIndex,       // headword index file

   EC_ASCII,   // XL_IX_TwIndex,       // translated headword index file

   EC_ASCII,   // XL_IX_LaIndex,       // label index file
   EC_ASCII,   // XL_IX_StIndex,       // standard entry text index file
   EC_ASCII,   // XL_IX_EdIndex,       // editorial notes index file (record creation date etc.)

   EC_ASCII,   // XL_IX_TxIndex,       // full text index file
   (EC_Types)TV_IX_CTBL, // 71, // XL_IX_HxIndex,       // headword index file
};


// --------------------------------------------------
const int auiIndexTags[2*XL_IX_NumOfIndexes3] =
{
   XC_Dict,          XC_Dict_e,         // XL_IX_DataFile,

   XC_StEntry,       XC_StEntry_e,      // XL_IX_SeIndex,

   XC_HeadWord,      XC_HeadWord_e,     // XL_IX_HwIndex,
   XC_TrWord,        XC_TrWord_e,       // XL_IX_TwIndex,
   XC_Label,         XC_Label_e,        // XL_IX_LaIndex,
   XC_StEntryText,   XC_StEntryText_e,  // XL_IX_StIndex,
   XC_TechNote,      XC_TechNote_e,     // XL_IX_EdIndex,

   XL_Text,          XL_Text_e,         // XL_IX_TxIndex,
   XC_HeadWord,      XC_HeadWord_e,     // XL_IX_HxIndex,
};


// --------------------------------------------------
const int iaXmlDictNulCodeTables[XC_TG_NumOfDictTagsArr68] = // XML Unicode file fictive code tables
{
  0,    // XC_Dict,
  0,    // XC_Dict_e,
  0,    // XC_NrtEntry,
  0,    // XC_NrtEntry_e,
  0,    // XC_StEntry,
  0,    // XC_StEntry_e,
  0,    // XC_HeadWord,
  0,    // XC_HeadWord_e,
  0,    // XC_Label,
  0,    // XC_Label_e,
  0,    // XC_TrWord,
  0,    // XC_TrWord_e,
  0,    // XC_UsNoteDst,
  0,    // XC_UsNoteDst_e,
  0,    // XC_Reference
  0,    // XC_Reference_e,
  0,    // XC_StEntryText,
  0,    // XC_StEntryText_e,

  0,    // XC_Paragraph,
  0,    // XC_Paragraph_e,

  0,    // XC_Version,
  0,    // XC_Version_e,
  0,    // XC_DocType,
  0,    // XC_DocType_e,

  0,    // XC_Variant,
  0,    // XC_Variant_e,
  0,    // XC_PartOfSpeechSrc,
  0,    // XC_PartOfSpeechSrc_e,

  0,    // XC_HeadWordGroup,
  0,    // XC_HeadWordGroup_e,
  0,    // XC_TranslGroup,
  0,    // XC_TranslGroup_e,

  0,    // XC_FormDst,
  0,    // XC_FormDst_e,
  0,    // XC_FormSrc,
  0,    // XC_FormSrc_e,

  0,    // XC_ExplSrc,
  0,    // XC_ExplSrc_e,

  0,    // XC_Example,
  0,    // XC_Example_e,
  0,    // XC_ExampleGroup,
  0,    // XC_ExampleGroup_e,

  0,    // XC_Parenth,
  0,    // XC_Parenth_e,

  0,    // XC_Idiom,
  0,    // XC_Idiom_e,

  0,    // XC_IdiomGroup,
  0,    // XC_IdiomGroup_e,

  0,    // XC_CtgGroup,
  0,    // XC_CtgGroup_e,

  0,    // XC_Base,
  0,    // XC_Base_e,
  0,    // XC_CompoundGroup,
  0,    // XC_CompoundGroup_e,
  0,    // XC_CompoundWord,
  0,    // XC_CompoundWord_e,

  0,    // XC_MngGroup,
  0,    // XC_MngGroup_e,

  0,    // XC_Asterix,
  0,    // XC_Asterix_e,

  0,    // XC_CtrlSrc,
  0,    // XC_CtrlSrc_e,

  0,    // XC_PrGroup,
  0,    // XC_PrGroup_e,
  0,    // XC_Pron,
  0,    // XC_Pron_e,

  0,    // XC_Abbr,
  0,    // XC_Abbr_e,

  0,    // XC_Hom,
  0,    // XC_Hom_e,

  0,    // XC_ContextSrc,
  0,    // XC_ContextSrc_e,

  0,    // XC_CtrlGroup,
  0,    // XC_CtrlGroup_e,

  0,    // XC_PartOfSpeechDst,
  0,    // XC_PartOfSpeechDst_e,

  0,    // XC_FormGroupSrc,
  0,    // XC_FormGroupSrc_e,

  0,    // XC_StyleSheet,
  0,    // XC_StyleSheet_e,

  0,    // XC_VarNorm,
  0,    // XC_VarNorm_e,

  0,    // XC_AbbrNorm,
  0,    // XC_AbbrNorm_e,  space after not allowed - may be in free text

  0,    // XC_MngNearGroup
  0,    // XC_MngNearGroup_e

  0,    // XC_PronRed
  0,    // XC_PronRed_e

  0,    // XC_Null
  0,    // XC_Null_e

  0,    // XC_Similar
  0,    // XC_Similar_e

  0,    // XC_Approx
  0,    // XC_Approx_e

  0,    // XC_Text
  0,    // XC_Text_e

  0,    // XC_Info
  0,    // XC_Info_e

  0,    // XC_Expand
  0,    // XC_Expand_e

  0,    // XC_StructGroup
  0,    // XC_StructGroup_e

  0,    // XC_Gloss
  0,    // XC_Gloss_e

  0,    // XC_FwNote
  0,    // XC_FwNote_e

  0,    // XC_Italic
  0,    // XC_Italic_e

  0,    // XC_ModCpdSrc
  0,    // XC_ModCpdSrc_e

  0,    // XC_Symb
  0,    // XC_Symb_e

  0,    // XC_Inform
  0,    // XC_Inform_e
  0,    // XC_Uncount
  0,    // XC_Uncount_e

  0,    // XC_PhrGroup
  0,    // XC_PhrGroup_e

  0,    // XC_CpdMngGroup
  0,    // XC_CpdMngGroup_e

  0,    // XC_Obs
  0,    // XC_Obs_e
  0,    // XC_Arch
  0,    // XC_Arch_e
  0,    // XC_VeryInform
  0,    // XC_VeryInform_e
  0,    // XC_Vulgar
  0,    // XC_Vulgar_e

  0,    // XC_Super
  0,    // XC_Super_e

  0,    // XC_Count
  0,    // XC_Count_e

  0,    // XC_HiLight
  0,    // XC_HiLight_e
  0,    // XC_SemiBold
  0,    // XC_SemiBold_e

  0,    // XC_CtrlDst
  0,    // XC_CtrlDst_e

  0,    // XC_ExplNorm
  0,    // XC_ExplNorm_e

  0,    // XC_Struct,
  0,    // XC_Struct_e,
  0,    // XC_OblStruct,
  0,    // XC_OblStruct_e,

  0,    // XC_Usage,
  0,    // XC_Usage_e,

  0,    // XC_HBase,
  0,    // XC_HBase_e,

  0,    // XC_ModCpdGroup
  0,    // XC_ModCpdGroup_e

  0,    // XC_ExampleTransl
  0,    // XC_ExampleTransl_e

  0,    // XC_IdiomTransl
  0,    // XC_IdiomTransl_e

  0,    // XC_TechNote
  0,    // XC_TechNote_e

  0,    // XC_IdMngGroup
  0,    // XC_IdMngGroup_e

  0,    // XC_Refinf
  0,    // XC_Refinf_e,

  0,    // XC_SrcWord,
  0,    // XC_SrcWord_e,

  0,    // XC_ModCpdDst
  0,    // XC_ModCpdDst_e

  0,    // XC_ContextDst
  0,    // XC_ContextDst_e

  0,    // XC_ExplDst
  0,    // XC_ExplDst_e

  0,    // XC_RefWord
  0,    // XC_RefWord_e

  0,    // XC_RefNum
  0,    // XC_RefNum_e

  0,    // XC_RefXWord
  0,    // XC_RefXWord_e

  0,    // XC_RefTab
  0,    // XC_RefTab_e

  0,    // XC_RefPage
  0,    // XC_RefPage_e

  0,    // XC_RefHom
  0,    // XC_RefHom_e

  0,    // XC_SingleCpdWord
  0,    // XC_SingleCpdWord_e

  0,    // XC_FormGroupDst
  0,    // XC_FormGroupDst_e

  0,    // XC_DerivGroup
  0,    // XC_DerivGroup_e

  0,    // XC_Derivative
  0,    // XC_Derivative_e

  0,    // XC_StressParGroup
  0,    // XC_StressParGroup_e

  0,    // XC_StressPar
  0,    // XC_StressPar_e

  0,    // XC_PunctMark
  0,    // XC_PunctMark_e

  0,    // XC_LevelGroup
  0,    // XC_LevelGroup_e

  0,    // XC_Level
  0,    // XC_Level_e

// 0,    // XC_TextExpr
// 0,    // XC_TextExpr_e

  0,    // XC_UsNoteSrc,
  0,    // XC_UsNoteSrc_e,

  0,    // XC_Img,
  0,    // XC_Img_e,

  0,    // XC_RefSecSynGr
  0,    // XC_RefSecSynGr_e
  0,    // XC_RefSecSyn
  0,    // XC_RefSecSyn_e

  0,    // XC_RefPriSynGr
  0,    // XC_RefPriSynGr_e
  0,    // XC_RefPriSyn
  0,    // XC_RefPriSyn_e

  0,    // XC_RefSynGr
  0,    // XC_RefSynGr_e
  0,    // XC_RefSyn
  0,    // XC_RefSyn_e

  0,    // XC_RefExamplGr
  0,    // XC_RefExamplGr_e
  0,    // XC_RefExampl
  0,    // XC_RefExampl_e

  0,    // XC_RefAntGr
  0,    // XC_RefAntGr_e
  0,    // XC_RefAnt
  0,    // XC_RefAnt_e

  0,    // XC_RefExamplSinglGr
  0,    // XC_RefExamplSinglGr_e

  0,    // XC_Subscript
  0,    // XC_Subscript_e

  0,    // XC_CodeExampleInline
  0,    // XC_CodeExampleInline_e

  0,    // XC_EnumGr
  0,    // XC_EnumGr_e

  0,    // XC_Enum
  0,    // XC_Enum_e

  0,    // XC_CodeBaseWord
  0,    // XC_CodeBaseWord_e

  0,    // XC_CodeExample
  0,    // XC_CodeExample_e

  0,    // XC_Table
  0,    // XC_Table_e
  0,    // XC_TableRow
  0,    // XC_TableRow_e
  0,    // XC_TableCell
  0,    // XC_TableCell_e

  0,    // XC_Equiation
  0,    // XC_Equiation_e

  0,    // XC_Break
  0,    // XC_Break_e

  0,    // XC_EquInline
  0,    // XC_EquInline_e

  0,    // XC_Special
  0,    // XC_Special_e

  0,    // XC_ExampleGroupForced,
  0,    // XC_ExampleGroupForced_e,

  0,    // XC_ExplForced,
  0,    // XC_ExplForced_e,

  0,    // XC_VarGroup
  0,    // XC_VarGroup_e

  0,    // XC_Relatives
  0,    // XC_Relatives_e

  0,    // XC_Page
  0,    // XC_Page_e

  0,    // XC_SemNr
  0,    // XC_SemNr_e

  0,    // XC_TrWordLit
  0,    // XC_TrWordLit_e

  0,    // XC_TrWordEng
  0,    // XC_TrWordEng_e

  0,    // XC_TrWordGer
  0,    // XC_TrWordGer_e

  0,    // XC_TrWordFre
  0,    // XC_TrWordFre_e

  0,    // XC_TrWordPol
  0,    // XC_TrWordPol_e

  0,    // XC_TrWordRus
  0,    // XC_TrWordRus_e

  0,    // XC_Species
  0,    // XC_Species_e

  0,    // XC_StructGroupForced
  0,    // XC_StructGroupForced_e

  0,    // XC_VarBold,
  0,    // XC_VarBold_e,

  0,    // XC_RefAntStrictGr
  0,    // XC_RefAntStrictGr_e
  0,    // XC_RefAntStrict
  0,    // XC_RefAntStrict_e
};


const bool baXmlDictTagsFreeText[XC_TG_NumOfDictTagsArr68] = // free text presence in dictionary XML tags, kazkaip apjungt su TestEmbedded !!!
{
  False,    // XC_Dict,
  False,    // XC_Dict_e,
  False, // True, // XC_NrtEntry,
  False,    // XC_NrtEntry_e,
  False,    // XC_StEntry,
  False,    // XC_StEntry_e,
  True,     // XC_HeadWord,
  False,    // XC_HeadWord_e,
  True,     // XC_Label,
  False,    // XC_Label_e,
  True,     // XC_TrWord,
  False,    // XC_TrWord_e,
  True,     // XC_UsNoteDst,
  False,    // XC_UsNoteDst_e,
  True,     // XC_Reference,
  False,    // XC_Reference_e,
  True,     // XC_StEntryText,
  False,    // XC_StEntryText_e,

  True,     // XC_Paragraph,
  False,    // XC_Paragraph_e,

  False,    // XC_Version,
  False,    // XC_Version_e,
  False,    // XC_DocType,
  False,    // XC_DocType_e,

  True,     // XC_Variant,
  False,    // XC_Variant_e,
  True,     // XC_PartOfSpeechSrc,
  False,    // XC_PartOfSpeechSrc_e,

  False,    // XC_HeadWordGroup,
  False,    // XC_HeadWordGroup_e,
  False,    // XC_TranslGroup,
  False,    // XC_TranslGroup_e,

  True,     // XC_FormDst,
  False,    // XC_FormDst_e,
  True,     // XC_FormSrc,
  False,    // XC_FormSrc_e,

  True,     // XC_ExplSrc,
  False,    // XC_ExplSrc_e,
  True,     // XC_Example,
  False,    // XC_Example_e,

  False,    // XC_ExampleGroup,
  False,    // XC_ExampleGroup_e,

  True,     // XC_Parenth,
  False,    // XC_Parenth_e,

  True,     // XC_Idiom,
  False,    // XC_Idiom_e,

  False,    // XC_IdiomGroup,
  False,    // XC_IdiomGroup_e,

  False,    // XC_CtgGroup,
  False,    // XC_CtgGroup_e,

  True,     // XC_Base,
  False,    // XC_Base_e,
  False,    // XC_CompoundGroup,
  False,    // XC_CompoundGroup_e,
  True,     // XC_CompoundWord,
  False,    // XC_CompoundWord_e,

  False,    // XC_MngGroup,
  False,    // XC_MngGroup_e,

  False,    // XC_Asterix,
  False,    // XC_Asterix_e,

  True,     // XC_CtrlSrc,
  False,    // XC_CtrlSrc_e,

  False,    // XC_PrGroup,
  False,    // XC_PrGroup_e,
  True,     // XC_Pron,
  False,    // XC_Pron_e,

  True,     // XC_Abbr,
  False,    // XC_Abbr_e,

  True,     // XC_Hom,
  False,    // XC_Hom_e,

  True,     // XC_ContextSrc,
  False,    // XC_ContextSrc_e,

  False,    // XC_CtrlGroup,
  False,    // XC_CtrlGroup_e,

  True,     // XC_PartOfSpeechDst,
  False,    // XC_PartOfSpeechDst_e,

  False,    // XC_FormGroupSrc,
  False,    // XC_FormGroupSrc_e,

  False,    // XC_StyleSheet,
  False,    // XC_StyleSheet_e,

  True,     // XC_VarNorm,
  False,    // XC_VarNorm_e,

  True,     // XC_AbbrNorm,
  False,    // XC_AbbrNorm_e,

  False,    // XC_MngNearGroup,
  False,    // XC_MngNearGroup_e,

  True,     // XC_PronRed
  False,    // XC_PronRed_e

  False,    // XC_Null
  False,    // XC_Null_e

  False,    // XC_Similar
  False,    // XC_Similar_e

  False,    // XC_Approx
  False,    // XC_Approx_e

  True,     // XC_Text
  False,    // XC_Text_e

  True,     // XC_Info
  False,    // XC_Info_e

  True,     // XC_Expand
  False,    // XC_Expand_e

  False,    // XC_StructGroup
  False,    // XC_StructGroup_e

  True,     // XC_Gloss
  False,    // XC_Gloss_e

  True,     // XC_FwNote
  False,    // XC_FwNote_e

  True,     // XC_Italic
  False,    // XC_Italic_e

  True,     // XC_ModCpdSrc
  False,    // XC_ModCpdSrc_e

  True,     // XC_Symb
  False,    // XC_Symb_e

  False,    // XC_Inform
  False,    // XC_Inform_e
  False,    // XC_Uncount
  False,    // XC_Uncount_e

  False,    // XC_PhrGroup
  False,    // XC_PhrGroup_e

  False,    // XC_CpdMngGroup
  False,    // XC_CpdMngGroup_e

  False,    // XC_Obs
  False,    // XC_Obs_e
  False,    // XC_Arch
  False,    // XC_Arch_e
  False,    // XC_VeryInform
  False,    // XC_VeryInform_e
  False,    // XC_Vulgar
  False,    // XC_Vulgar_e

  True,     // XC_Super
  False,    // XC_Super_e

  False,    // XC_Count
  False,    // XC_Count_e

  True,     // XC_HiLight
  False,    // XC_HiLight_e
  True,     // XC_SemiBold
  False,    // XC_SemiBold_e

  True,     // XC_CtrlDst
  False,    // XC_CtrlDst_e

  True,     // XC_ExplNorm
  False,    // XC_ExplNorm_e

  True,     // XC_Struct,
  False,    // XC_Struct_e,
  True,     // XC_OblStruct,
  False,    // XC_OblStruct_e,

  True,     // XC_Usage,
  False,    // XC_Usage_e,

  True,     // XC_HBase,
  False,    // XC_HBase_e,

  False,    // XC_ModCpdGroup
  False,    // XC_ModCpdGroup_e

  True,     // XC_ExampleTransl
  False,    // XC_ExampleTransl_e

  True,     // XC_IdiomTransl
  False,    // XC_IdiomTransl_e

  True,     // XC_TechNote
  False,    // XC_TechNote_e

  False,    // XC_IdMngGroup
  False,    // XC_IdMngGroup_e

  True,     // XC_Refinf,
  False,    // XC_Refinf_e,

  True,     // XC_SrcWord,
  False,    // XC_SrcWord_e,

  True,     // XC_ModCpdDst
  False,    // XC_ModCpdDst_e

  True,     // XC_ContextDst
  False,    // XC_ContextDst_e

  True,     // XC_ExplDst
  False,    // XC_ExplDst_e

  True,     // XC_RefWord
  False,    // XC_RefWord_e

  True,     // XC_RefNum
  False,    // XC_RefNum_e

  True,     // XC_RefXWord
  False,    // XC_RefXWord_e

  True,     // XC_RefTab
  False,    // XC_RefTab_e

  True,     // XC_RefPage
  False,    // XC_RefPage_e

  True,     // XC_RefHom
  False,    // XC_RefHom_e

  True,     // XC_SingleCpdWord
  False,    // XC_SingleCpdWord_e

  False,    // XC_FormGroupDst
  False,    // XC_FormGroupDst_e

  False,    // XC_DerivGroup
  False,    // XC_DerivGroup_e

  True,     // XC_Derivative
  False,    // XC_Derivative_e

  False,    // XC_StressParGroup
  False,    // XC_StressParGroup_e

  True,     // XC_StressPar
  False,    // XC_StressPar_e

  True,     // XC_PunctMark
  False,    // XC_PunctMark_e

  False,    // XC_LevelGroup
  False,    // XC_LevelGroup_e

  True,     // XC_Level
  False,    // XC_Level_e

// True,     // XC_TextExpr
// False,    // XC_TextExpr_e

  True,     // XC_UsNoteSrc,
  False,    // XC_UsNoteSrc_e,

  False,    // XC_Img,
  False,    // XC_Img_e,

  False,    // XC_RefSecSynGr
  False,    // XC_RefSecSynGr_e
  True,     // XC_RefSecSyn
  False,    // XC_RefSecSyn_e

  False,    // XC_RefPriSynGr
  False,    // XC_RefPriSynGr_e
  True,     // XC_RefPriSyn
  False,    // XC_RefPriSyn_e

  False,    // XC_RefSynGr
  False,    // XC_RefSynGr_e
  True,     // XC_RefSyn
  False,    // XC_RefSyn_e

  False,    // XC_RefExamplGr
  False,    // XC_RefExamplGr_e
  True,     // XC_RefExampl
  False,    // XC_RefExampl_e

  False,    // XC_RefAntGr
  False,    // XC_RefAntGr_e
  True,     // XC_RefAnt
  False,    // XC_RefAnt_e

  False,    // XC_RefExamplSinglGr
  False,    // XC_RefExamplSinglGr_e

  True,     // XC_Subscript
  False,    // XC_Subscript_e

  True,     // XC_CodeExampleInline
  False,    // XC_CodeExampleInline_e

  False,    // XC_EnumGr
  False,    // XC_EnumGr_e

  True,     // XC_Enum
  False,    // XC_Enum_e

  True,     // XC_CodeBaseWord
  False,    // XC_CodeBaseWord_e

  True,     // XC_CodeExample
  False,    // XC_CodeExample_e

  False,    // XC_Table
  False,    // XC_Table_e
  False,    // XC_TableRow
  False,    // XC_TableRow_e
  True,     // XC_TableCell
  False,    // XC_TableCell_e

  False,    // XC_Equiation
  False,    // XC_Equiation_e

  False,    // XC_Break
  False,    // XC_Break_e

  True,     // XC_EquInline
  False,    // XC_EquInline_e

  True,     // XC_Special
  False,    // XC_Special_e

  False,    // XC_ExampleGroupForced,
  False,    // XC_ExampleGroupForced_e,

  True,     // XC_ExplForced,
  False,    // XC_ExplForced_e,

  False,    // XC_VarGroup
  False,    // XC_VarGroup_e

  False,    // XC_Relatives
  False,    // XC_Relatives_e

  True,     // XC_Page
  False,    // XC_Page_e

  True,     // XC_SemNr
  False,    // XC_SemNr_e

  True,     // XC_TrWordLit
  False,    // XC_TrWordLit_e

  True,     // XC_TrWordEng
  False,    // XC_TrWordEng_e

  True,     // XC_TrWordGer
  False,    // XC_TrWordGer_e

  True,     // XC_TrWordFre
  False,    // XC_TrWordFre_e

  True,     // XC_TrWordPol
  False,    // XC_TrWordPol_e

  True,     // XC_TrWordRus
  False,    // XC_TrWordRus_e

  True,     // XC_Species
  False,    // XC_Species_e

  False,    // XC_StructGroupForced
  False,    // XC_StructGroupForced_e

  True,     // XC_VarBold,
  False,    // XC_VarBold_e,

  False,    // XC_RefAntStrictGr
  False,    // XC_RefAntStrictGr_e
  True,     // XC_RefAntStrict
  False,    // XC_RefAntStrict_e
};


const KpChar uiazXmlParGrTags[XC_TG_NumOfDictTagsArr68]=
{
  C_Nul,             // XC_Dict
  C_Nul,             // XC_Dict_e
  (KpChar)XC_Dict,   // XC_NrtEntry
  (KpChar)XC_Dict,           // XC_NrtEntry_e
  (KpChar)XC_Dict,           // XC_StEntry
  (KpChar)XC_Dict,           // XC_StEntry_e
  (KpChar)XC_HeadWordGroup,  // XC_HeadWord
  (KpChar)XC_HeadWordGroup,  // XC_HeadWord_e
  C_Nul,             // XC_Label
  C_Nul,             // XC_Label_e
  (KpChar)XC_TranslGroup,    // XC_TrWord
  (KpChar)XC_TranslGroup,    // XC_TrWord_e
  (KpChar)XC_HeadWordGroup,  // XC_UsNoteDst
  (KpChar)XC_HeadWordGroup,  // XC_UsNoteDst_e
  C_Nul,             // XC_Reference
  C_Nul,             // XC_Reference_e
  (KpChar)XC_StEntry,        // XC_StEntryText
  (KpChar)XC_StEntry,        // XC_StEntryText_e

  C_Nul,             // XC_Paragraph
  C_Nul,             // XC_Paragraph_e

  C_Nul,             // XC_Version
  C_Nul,             // XC_Version_e
  C_Nul,             // XC_DocType
  C_Nul,             // XC_DocType_e

  C_Nul,             // XC_Variant
  C_Nul,             // XC_Variant_e
  C_Nul,             // XC_PartOfSpeechSrc
  C_Nul,             // XC_PartOfSpeechSrc_e

  (KpChar)XC_StEntry,        // XC_HeadWordGroup
  (KpChar)XC_StEntry,        // XC_HeadWordGroup_e
  C_Nul,             // XC_TranslGroup
  C_Nul,             // XC_TranslGroup_e

  (KpChar)XC_FormGroupDst,      // XC_FormDst
  (KpChar)XC_FormGroupDst,      // XC_FormDst_e
  (KpChar)XC_FormGroupSrc,      // XC_FormSrc
  (KpChar)XC_FormGroupSrc,      // XC_FormSrc_e

  C_Nul,             // XC_ExplSrc
  C_Nul,             // XC_ExplSrc_e
  (KpChar)XC_ExampleGroup,   // XC_Example
  (KpChar)XC_ExampleGroup,   // XC_Example_e

  (KpChar)XC_HeadWordGroup,  // XC_ExampleGroup
  (KpChar)XC_HeadWordGroup,  // XC_ExampleGroup_e

  C_Nul,             // XC_Parenth
  C_Nul,             // XC_Parenth_e

  (KpChar)XC_IdiomGroup,     // XC_Idiom
  (KpChar)XC_IdiomGroup,     // XC_Idiom_e

  (KpChar)XC_HeadWordGroup,  // XC_IdiomGroup
  (KpChar)XC_HeadWordGroup,  // XC_IdiomGroup_e

  (KpChar)XC_HeadWordGroup,  // XC_CtgGroup
  (KpChar)XC_HeadWordGroup,  // XC_CtgGroup_e,

  (KpChar)XC_HeadWordGroup,  // XC_Base,
  (KpChar)XC_HeadWordGroup,  // XC_Base_e,
  (KpChar)XC_HeadWordGroup,  // XC_CompoundGroup,
  (KpChar)XC_HeadWordGroup,  // XC_CompoundGroup_e,
  (KpChar)XC_CompoundGroup,  // XC_CompoundWord,
  (KpChar)XC_CompoundGroup,  // XC_CompoundWord_e,

  (KpChar)XC_HeadWordGroup,  // XC_MngGroup
  (KpChar)XC_HeadWordGroup,  // XC_MngGroup_e,

  C_Nul,             // XC_Asterix,
  C_Nul,             // XC_Asterix_e,

  (KpChar)XC_CtrlGroup,   // XC_CtrlSrc,
  (KpChar)XC_CtrlGroup,   // XC_CtrlSrc_e,

  (KpChar)XC_HeadWordGroup,  // XC_PrGroup,
  (KpChar)XC_HeadWordGroup,  // XC_PrGroup_e,
  (KpChar)XC_PrGroup,        // XC_Pron,
  (KpChar)XC_PrGroup,        // XC_Pron_e,

  C_Nul,    // XC_Abbr,
  C_Nul,    // XC_Abbr_e,

  C_Nul,    // XC_Hom,
  C_Nul,    // XC_Hom_e,

  C_Nul,    // XC_ContextSrc,
  C_Nul,    // XC_ContextSrc_e,

  C_Nul,    // XC_CtrlGroup,
  C_Nul,    // XC_CtrlGroup_e,

  C_Nul,    // XC_PartOfSpeechDst,
  C_Nul,    // XC_PartOfSpeechDst_e,

  C_Nul,    // XC_FormGroupSrc,
  C_Nul,    // XC_FormGroupSrc_e,

  C_Nul,    // XC_StyleSheet
  C_Nul,    // XC_StyleSheet_e

  C_Nul,    // XC_VarNorm
  C_Nul,    // XC_VarNorm_e

  C_Nul,    // XC_AbbrNorm,
  C_Nul,    // XC_AbbrNorm_e,

  (KpChar)XC_HeadWordGroup,  // XC_MngNearGroup,
  (KpChar)XC_HeadWordGroup,  // XC_MngNearGroup_e,

  (KpChar)XC_Pron,  // XC_PronRed
  (KpChar)XC_Pron,  // XC_PronRed_e

  C_Nul,    // XC_Null
  C_Nul,    // XC_Null_e

  C_Nul,    // XC_Similar
  C_Nul,    // XC_Similar_e

  C_Nul,    // XC_Approx
  C_Nul,    // XC_Approx_e

  C_Nul,    // XC_Text
  C_Nul,    // XC_Text_e

  C_Nul,    // XC_Info
  C_Nul,    // XC_Info_e

  C_Nul,    // XC_Expand
  C_Nul,    // XC_Expand_e

  (KpChar)XC_HeadWordGroup,  // XC_StructGroup,
  (KpChar)XC_HeadWordGroup,  // XC_StructGroup_e,

  (KpChar)XC_TranslGroup,    // XC_Gloss
  (KpChar)XC_TranslGroup,    // XC_Gloss_e

  (KpChar)XC_HeadWordGroup,  // XC_FwNote
  (KpChar)XC_HeadWordGroup,  // XC_FwNote_e

  C_Nul,    // XC_Italic
  C_Nul,    // XC_Italic_e

  (KpChar)XC_ModCpdGroup,    // XC_ModCpdSrc
  (KpChar)XC_ModCpdGroup,    // XC_ModCpdSrc_e

  C_Nul,    // XC_Symb
  C_Nul,    // XC_Symb_e

  C_Nul,    // XC_Inform
  C_Nul,    // XC_Inform_e
  C_Nul,    // XC_Uncount
  C_Nul,    // XC_Uncount_e

  C_Nul,    // XC_PhrGroup
  C_Nul,    // XC_PhrGroup_e

  (KpChar)XC_PhrGroup, // XC_CpdMngGroup
  (KpChar)XC_PhrGroup, // XC_CpdMngGroup_e

  C_Nul,    // XC_Obs
  C_Nul,    // XC_Obs_e
  C_Nul,    // XC_Arch
  C_Nul,    // XC_Arch_e
  C_Nul,    // XC_VeryInform
  C_Nul,    // XC_VeryInform_e
  C_Nul,    // XC_Vulgar
  C_Nul,    // XC_Vulgar_e

  C_Nul,    // XC_Super
  C_Nul,    // XC_Super_e

  C_Nul,    // XC_Count
  C_Nul,    // XC_Count_e

  C_Nul,    // XC_HiLight
  C_Nul,    // XC_HiLight_e
  C_Nul,    // XC_SemiBold
  C_Nul,    // XC_SemiBold_e

  (KpChar)XC_CtrlGroup,   // XC_CtrlDst,
  (KpChar)XC_CtrlGroup,   // XC_CtrlDst_e,

  C_Nul,             // XC_ExplNorm
  C_Nul,             // XC_ExplNorm_e

  (KpChar)XC_StructGroup,    // XC_Struct,
  (KpChar)XC_StructGroup,    // XC_Struct_e,
  (KpChar)XC_StructGroup,    // XC_OblStruct,
  (KpChar)XC_StructGroup,    // XC_OblStruct_e,

  (KpChar)XC_ExampleGroup,   // XC_Usage,
  (KpChar)XC_ExampleGroup,   // XC_Usage_e,

  (KpChar)XC_HeadWordGroup,  // XC_HBase,
  (KpChar)XC_HeadWordGroup,  // XC_HBase_e,

  (KpChar)XC_TranslGroup,    // XC_ModCpdGroup
  (KpChar)XC_TranslGroup,    // XC_ModCpdGroup_e

  (KpChar)XC_ExampleGroup,   // XC_ExampleTransl
  (KpChar)XC_ExampleGroup,   // XC_ExampleTransl_e

  (KpChar)XC_IdiomGroup,     // XC_IdiomTransl
  (KpChar)XC_IdiomGroup,     // XC_IdiomTransl_e

  C_Nul,    // XC_TechNote
  C_Nul,    // XC_TechNote_e

  (KpChar)XC_IdiomGroup,     // XC_IdMngGroup
  (KpChar)XC_IdiomGroup,     // XC_IdMngGroup_e

  C_Nul,             // XC_Refinf
  C_Nul,             // XC_Refinf_e

  C_Nul,             // XC_SrcWord,
  C_Nul,             // XC_SrcWord_e,

  (KpChar)XC_TranslGroup, // XC_ModCpdGroup,   // XC_ModCpdDst
  (KpChar)XC_TranslGroup, // XC_ModCpdGroup,   // XC_ModCpdDst_e

  (KpChar)XC_TranslGroup, // XC_ContextDst
  (KpChar)XC_TranslGroup, // XC_ContextDst_e

  C_Nul,   // XC_ExplDst
  C_Nul,   // XC_ExplDst_e

  (KpChar)XC_RefInf,      // XC_RefWord
  (KpChar)XC_RefInf,      // XC_RefWord_e

  (KpChar)XC_RefInf,      // XC_RefNum
  (KpChar)XC_RefInf,      // XC_RefNum_e

  (KpChar)XC_RefInf,      // XC_RefXWord
  (KpChar)XC_RefInf,      // XC_RefXWord_e

  (KpChar)XC_RefInf,      // XC_RefTab
  (KpChar)XC_RefInf,      // XC_RefTab_e

  (KpChar)XC_RefInf,      // XC_RefPage
  (KpChar)XC_RefInf,      // XC_RefPage_e

  (KpChar)XC_RefInf,      // XC_RefHom
  (KpChar)XC_RefInf,      // XC_RefHom_e

  (KpChar)XC_CompoundGroup, // XC_SingleCpdWord
  (KpChar)XC_CompoundGroup, // XC_SingleCpdWord_e

  (KpChar)XC_TranslGroup,    // XC_FormGroupDst
  (KpChar)XC_TranslGroup,    // XC_FormGroupDst_e

  (KpChar)XC_HeadWordGroup,  // XC_DerivGroup
  (KpChar)XC_HeadWordGroup,  // XC_DerivGroup_e

  (KpChar)XC_DerivGroup,     // XC_Derivative
  (KpChar)XC_DerivGroup,     // XC_Derivative_e

  C_Nul,             // XC_StressParGroup
  C_Nul,             // XC_StressParGroup_e

  (KpChar)XC_StressParGroup, // XC_StressPar
  (KpChar)XC_StressParGroup, // XC_StressPar_e

  C_Nul,             // XC_PunctMark
  C_Nul,             // XC_PunctMark_e

  C_Nul,             // XC_LevelGroup
  C_Nul,             // XC_LevelGroup_e

  (KpChar)XC_LevelGroup,     // XC_Level
  (KpChar)XC_LevelGroup,     // XC_Level_e

// C_Nul,    // XC_TextExpr
// C_Nul,    // XC_TextExpr_e

  (KpChar)XC_HeadWordGroup,  // XC_UsNoteSrc
  (KpChar)XC_HeadWordGroup,  // XC_UsNoteSrc_e

  C_Nul,    // XC_Img
  C_Nul,    // XC_Img_e

  (KpChar)XC_HeadWordGroup,  // XC_RefSecSynGr
  (KpChar)XC_HeadWordGroup,  // XC_RefSecSynGr_e
  (KpChar)XC_RefSecSynGr,    // XC_RefSecSyn
  (KpChar)XC_RefSecSynGr,    // XC_RefSecSyn_e

  (KpChar)XC_HeadWordGroup,  // XC_RefPriSynGr
  (KpChar)XC_HeadWordGroup,  // XC_RefPriSynGr_e
  (KpChar)XC_RefPriSynGr,    // XC_RefPriSyn
  (KpChar)XC_RefPriSynGr,    // XC_RefPriSyn_e

  (KpChar)XC_HeadWordGroup,  // XC_RefSynGr
  (KpChar)XC_HeadWordGroup,  // XC_RefSynGr_e
  (KpChar)XC_RefSynGr,       // XC_RefSyn
  (KpChar)XC_RefSynGr,       // XC_RefSyn_e

  (KpChar)XC_HeadWordGroup,  // XC_RefExamplGr
  (KpChar)XC_HeadWordGroup,  // XC_RefExamplGr_e
  (KpChar)XC_RefExamplGr,    // XC_RefExampl
  (KpChar)XC_RefExamplGr,    // XC_RefExampl_e

  (KpChar)XC_HeadWordGroup,  // XC_RefAntGr
  (KpChar)XC_HeadWordGroup,  // XC_RefAntGr_e
  (KpChar)XC_RefAntGr,       // XC_RefAnt
  (KpChar)XC_RefAntGr,       // XC_RefAnt_e

  (KpChar)XC_HeadWordGroup,  // XC_RefExamplSinglGr
  (KpChar)XC_HeadWordGroup,  // XC_RefExamplSinglGr_e

  C_Nul,    // XC_Subscript
  C_Nul,    // XC_Subscript_e

  C_Nul,    // XC_CodeExampleInline
  C_Nul,    // XC_CodeExampleInline_e

  C_Nul,    // XC_EnumGr
  C_Nul,    // XC_EnumGr_e

  (KpChar)XC_EnumGr,  // XC_Enum
  (KpChar)XC_EnumGr,  // XC_Enum_e

  C_Nul,    // XC_CodeBaseWord
  C_Nul,    // XC_CodeBaseWord_e

  C_Nul,    // XC_CodeExample
  C_Nul,    // XC_CodeExample_e

  C_Nul,    // XC_Table
  C_Nul,    // XC_Table_e
  (KpChar)XC_Table, // XC_TableRow
  (KpChar)XC_Table, // XC_TableRow_e
  (KpChar)XC_TableRow, // XC_TableCell
  (KpChar)XC_TableRow, // XC_TableCell_e

  C_Nul,   // XC_Equiation
  C_Nul,   // XC_Equiation_e

  (KpChar)XC_Paragraph,   // XC_Break
  (KpChar)XC_Paragraph,   // XC_Break_e

  C_Nul,   // XC_EquInline
  C_Nul,   // XC_EquInline_e

  C_Nul,   // XC_Special
  C_Nul,   // XC_Special_e

  (KpChar)XC_HeadWordGroup,  // XC_ExampleGroupForced,
  (KpChar)XC_HeadWordGroup,  // XC_ExampleGroupForced_e,

  C_Nul,  // XC_ExplForced,
  C_Nul,  // XC_ExplForced_e,

  C_Nul,  // XC_VarGroup
  C_Nul,  // XC_VarGroup_e

  C_Nul,  // XC_Relatives
  C_Nul,  // XC_Relatives_e


  C_Nul,  // XC_Page
  C_Nul,  // XC_Page_e

  C_Nul,  // XC_SemNr
  C_Nul,  // XC_SemNr_e

  (KpChar)XC_TranslGroup,    // XC_TrWordLit
  (KpChar)XC_TranslGroup,    // XC_TrWordLit_e

  (KpChar)XC_TranslGroup,    // XC_TrWordEng
  (KpChar)XC_TranslGroup,    // XC_TrWordEng_e

  (KpChar)XC_TranslGroup,    // XC_TrWordGer
  (KpChar)XC_TranslGroup,    // XC_TrWordGer_e

  (KpChar)XC_TranslGroup,    // XC_TrWordFre
  (KpChar)XC_TranslGroup,    // XC_TrWordFre_e

  (KpChar)XC_TranslGroup,    // XC_TrWordPol
  (KpChar)XC_TranslGroup,    // XC_TrWordPol_e

  (KpChar)XC_TranslGroup,    // XC_TrWordRus
  (KpChar)XC_TranslGroup,    // XC_TrWordRus_e

  (KpChar)XC_HeadWordGroup,  // XC_Species
  (KpChar)XC_HeadWordGroup,  // XC_Species_e

  (KpChar)XC_HeadWordGroup,  // XC_StructGroupForced,
  (KpChar)XC_HeadWordGroup,  // XC_StructGroupForced_e,

  C_Nul,                     // XC_VarBold
  C_Nul,                     // XC_VarBold_e

  (KpChar)XC_HeadWordGroup,  // XC_RefAntStrictGr
  (KpChar)XC_HeadWordGroup,  // XC_RefAntStrictGr_e
  (KpChar)XC_RefAntStrictGr,       // XC_RefAntStrict
  (KpChar)XC_RefAntStrictGr,       // XC_RefAntStrict_e
};


const KpChar uiazXmlGrTags[]=
{
  (KpChar)XC_Dict,
  (KpChar)XC_Dict_e,

  (KpChar)XC_NrtEntry,
  (KpChar)XC_NrtEntry_e,
  (KpChar)XC_StEntry,
  (KpChar)XC_StEntry_e,

  (KpChar)XC_HeadWordGroup,
  (KpChar)XC_HeadWordGroup_e,

  (KpChar)XC_TranslGroup,
  (KpChar)XC_TranslGroup_e,

  (KpChar)XC_ExampleGroup,
  (KpChar)XC_ExampleGroup_e,
  (KpChar)XC_ExampleGroupForced,
  (KpChar)XC_ExampleGroupForced_e,
  (KpChar)XC_IdiomGroup,
  (KpChar)XC_IdiomGroup_e,

  (KpChar)XC_CtgGroup,
  (KpChar)XC_CtgGroup_e,
  (KpChar)XC_MngGroup,
  (KpChar)XC_MngGroup_e,
  (KpChar)XC_MngNearGroup,
  (KpChar)XC_MngNearGroup_e,
  (KpChar)XC_CpdMngGroup,
  (KpChar)XC_CpdMngGroup_e,
  (KpChar)XC_IdMngGroup,
  (KpChar)XC_IdMngGroup_e,

  (KpChar)XC_CompoundGroup,
  (KpChar)XC_CompoundGroup_e,
  (KpChar)XC_StructGroup,
  (KpChar)XC_StructGroup_e,
  (KpChar)XC_StructGroupForced,
  (KpChar)XC_StructGroupForced_e,
  (KpChar)XC_DerivGroup,
  (KpChar)XC_DerivGroup_e,
  (KpChar)XC_PhrGroup,
  (KpChar)XC_PhrGroup_e,
  (KpChar)XC_ModCpdGroup,
  (KpChar)XC_ModCpdGroup_e,

  (KpChar)XC_RefSecSynGr,
  (KpChar)XC_RefSecSynGr_e,
  (KpChar)XC_RefPriSynGr,
  (KpChar)XC_RefPriSynGr_e,
  (KpChar)XC_RefSynGr,
  (KpChar)XC_RefSynGr_e,
  (KpChar)XC_RefExamplGr,
  (KpChar)XC_RefExamplGr_e,
  (KpChar)XC_RefAntGr,
  (KpChar)XC_RefAntGr_e,
  (KpChar)XC_RefAntStrictGr,
  (KpChar)XC_RefAntStrictGr_e,
  (KpChar)XC_RefExamplSinglGr,
  (KpChar)XC_RefExamplSinglGr_e,

// ---------------------- reiketu eilutes perkelimo/atitraukimu, bet nereikia KP_LISTBOX node
//(KpChar)XC_Paragraph,
//(KpChar)XC_Paragraph_e,
//(KpChar)XC_Break,
//(KpChar)XC_Break_e,
//(KpChar)XC_EnumGr,
//(KpChar)XC_EnumGr_e,
//(KpChar)XC_Enum,
//(KpChar)XC_Enum_e,
//(KpChar)XC_Table,
//(KpChar)XC_Table_e,
//(KpChar)XC_TableRow,
//(KpChar)XC_TableRow_e,
//(KpChar)XC_CodeExample,
//(KpChar)XC_CodeExample_e,
//(KpChar)XC_Equiation,
//(KpChar)XC_Equiation_e,
//(KpChar)XC_Img,
//(KpChar)XC_Img_e,

  C_Nul
};


const KpChar uiazXmlNodeGrTags[]=
{
  (KpChar)XC_HeadWordGroup,

  (KpChar)XC_TranslGroup,

  (KpChar)XC_ExampleGroup,
  (KpChar)XC_ExampleGroupForced,
  (KpChar)XC_IdiomGroup,

  (KpChar)XC_CompoundGroup,
  (KpChar)XC_StructGroup,
  (KpChar)XC_StructGroupForced,
  (KpChar)XC_DerivGroup,
  (KpChar)XC_ModCpdGroup, // ???
  (KpChar)XC_PhrGroup,

  C_Nul
};


const KpChar uiazXmlHwGrTags[]=
{
// must correspond tags in uiazXmlHwInvTags[]
  (KpChar)XC_HeadWordGroup,
  (KpChar)XC_VarGroup,

  (KpChar)XC_ExampleGroup,
  (KpChar)XC_ExampleGroupForced,
  (KpChar)XC_IdiomGroup,

  (KpChar)XC_CompoundGroup,
  (KpChar)XC_StructGroup,
  (KpChar)XC_StructGroupForced,
  (KpChar)XC_DerivGroup,
  (KpChar)XC_ModCpdGroup, // ???
  (KpChar)XC_PhrGroup,

  C_Nul
};


const KpChar uiazXmlHwInvTags[]=
{
// must correspond tags in uiazXmlHwGrTags[]
   (KpChar)XC_HeadWord,

   (KpChar)XC_Example,
   (KpChar)XC_Idiom,

   (KpChar)XC_CompoundWord,
   (KpChar)XC_Struct,
   (KpChar)XC_Derivative,
   (KpChar)XC_CompoundWord,
   (KpChar)XC_CompoundWord,

   C_Nul
};


const KpChar uiazXmlHwTags[]=
{
   (KpChar)XC_HeadWord,
   (KpChar)XC_Variant,
   (KpChar)XC_VarNorm,

// must be saved empty such tags before <tg> with changed to <tw> (XmlNode_tag::Hw2Tw())
   (KpChar)XC_Example,
   (KpChar)XC_Usage,
   (KpChar)XC_Idiom,

   (KpChar)XC_CompoundWord,
   (KpChar)XC_Struct,
   (KpChar)XC_OblStruct,
   (KpChar)XC_Derivative,
   (KpChar)XC_SrcWord,

   C_Nul
};


const KpChar uiazXmlCpdGrTags[]=
{
   (KpChar)XC_CompoundGroup,
// (KpChar)XC_StructGroup,
// (KpChar)XC_StructGroupForced,
   (KpChar)XC_DerivGroup,
   (KpChar)XC_ModCpdGroup, // ???
   (KpChar)XC_PhrGroup,

   C_Nul
};


const KpChar uiazXmlVariantTags[]=
{
   (KpChar)XC_HeadWord,
   (KpChar)XC_Variant,
   (KpChar)XC_VarGroup,

   (KpChar)XC_Example,
   (KpChar)XC_Usage,
   (KpChar)XC_Idiom,

   (KpChar)XC_CompoundWord,
   (KpChar)XC_Struct,
   (KpChar)XC_OblStruct,
   (KpChar)XC_Derivative,
   (KpChar)XC_SrcWord,

  C_Nul
};


const KpChar uiazXmlCtgGrTags[]=
{
   (KpChar)XC_CtgGroup,
   (KpChar)XC_MngGroup,
   (KpChar)XC_MngNearGroup,
   (KpChar)XC_CpdMngGroup,
   (KpChar)XC_IdMngGroup,

   C_Nul
};


const KpChar uiazXmlSingleTags[]=
{
   (KpChar)XC_Asterix,
   (KpChar)XC_Similar,
   (KpChar)XC_Approx,
   (KpChar)XC_Inform,
   (KpChar)XC_Uncount,
   (KpChar)XC_Obs,
   (KpChar)XC_Arch,
   (KpChar)XC_VeryInform,
   (KpChar)XC_Vulgar,
   (KpChar)XC_Count,

   C_Nul
};


// --------------------------------------
HBITMAP hNodeBitmaps[XC_TG_NumOfDictTagsArr68] =
{
   0, // XC_Dict
   0, // XC_Dict_e,

   0, // XC_NrtEntry,
   0, // XC_NrtEntry_e,
   0, // XC_StEntry,
   0, // XC_StEntry_e,

   0, // XC_HeadWord,
   0, // XC_HeadWord_e,
   0, // XC_Label,
   0, // XC_Label_e,
   0, // XC_TrWord,
   0, // XC_TrWord_e,
   0, // XC_UsNoteDst,
   0, // XC_UsNoteDst_e,
   0, // XC_Reference,
   0, // XC_Reference_e,
   0, // XC_StEntryText,
   0, // XC_StEntryText_e,
   0, // XC_Paragraph,
   0, // XC_Paragraph_e,

       0, // XC_Version_obs,
       0, // XC_Version_obs_e,
       0, // XC_DocType_obs,
       0, // XC_DocType_obs_e,

   0, // XC_Variant,
   0, // XC_Variant_e,
   0, // XC_PartOfSpeechSrc,
   0, // XC_PartOfSpeechSrc_e,

   0, // XC_HeadWordGroup,
   0, // XC_HeadWordGroup_e,
   0, // XC_TranslGroup,
   0, // XC_TranslGroup_e,

   0, // XC_FormDst,
   0, // XC_FormDst_e,
   0, // XC_FormSrc,
   0, // XC_FormSrc_e,

   0, // XC_ExplSrc,
   0, // XC_ExplSrc_e,

   0, // XC_Example,
   0, // XC_Example_e,
   0, // XC_ExampleGroup,
   0, // XC_ExampleGroup_e,

   0, // XC_Parenth,
   0, // XC_Parenth_e,

   0, // XC_Idiom,
   0, // XC_Idiom_e,

   0, // XC_IdiomGroup,
   0, // XC_IdiomGroup_e,

   0, // XC_CtgGroup,
   0, // XC_CtgGroup_e,

   0, // XC_Base,
   0, // XC_Base_e,
   0, // XC_CompoundGroup,
   0, // XC_CompoundGroup_e,
   0, // XC_CompoundWord,
   0, // XC_CompoundWord_e,

   0, // XC_MngGroup,
   0, // XC_MngGroup_e,

   0, // XC_Asterix,
   0, // XC_Asterix_e,

   0, // XC_CtrlSrc,
   0, // XC_CtrlSrc_e,

   0, // XC_PrGroup,
   0, // XC_PrGroup_e,
   0, // XC_Pron,
   0, // XC_Pron_e,

   0, // XC_Abbr,
   0, // XC_Abbr_e,

   0, // XC_Hom,
   0, // XC_Hom_e,

   0, // XC_ContextSrc,
   0, // XC_ContextSrc_e,

   0, // XC_CtrlGroup,
   0, // XC_CtrlGroup_e,

   0, // XC_PartOfSpeechDst,
   0, // XC_PartOfSpeechDst_e

   0, // XC_FormGroupSrc,
   0, // XC_FormGroupSrc_e,

       0, // XC_StyleSheet_obs,
       0, // XC_StyleSheet_obs_e

   0, // XC_VarNorm,
   0, // XC_VarNorm_e,

   0, // XC_AbbrNorm,
   0, // XC_AbbrNorm_e,

   0, // XC_MngNearGroup,
   0, // XC_MngNearGroup_e,

   0, // XC_PronRed,
   0, // XC_PronRed_e,

   0, // XC_Nul,
   0, // XC_Nul_e,

   0, // XC_Similar,
   0, // XC_Similar_e,

   0, // XC_Approx,
   0, // XC_Approx_e,

   0, // XC_Text,
   0, // XC_Text_e,

   0, // XC_Info,
   0, // XC_Info_e,

   0, // XC_Expand,
   0, // XC_Expand_e,

   0, // XC_StructGroup,
   0, // XC_StructGroup_e,

   0, // XC_Gloss,
   0, // XC_Gloss_e,

   0, // XC_FwNote,
   0, // XC_FwNote_e,

   0, // XC_Italic,
   0, // XC_Italic_e,

   0, // XC_ModCpdSrc,
   0, // XC_ModCpdSrc_e,

   0, // XC_Symb,
   0, // XC_Symb_e,

   0, // XC_Inform,
   0, // XC_Inform_e,
   0, // XC_Uncount,
   0, // XC_Uncount_e,

   0, // XC_PhrGroup,
   0, // XC_PhrGroup_e,

   0, // XC_CpdMngGroup,
   0, // XC_CpdMngGroup_e,

   0, // XC_Obs,
   0, // XC_Obs_e,
   0, // XC_Arch,
   0, // XC_Arch_e,
   0, // XC_VeryInform,
   0, // XC_VeryInform_e,
   0, // XC_Vulgar,
   0, // XC_Vulgar_e,

   0, // XC_Super,
   0, // XC_Super_e,

   0, // XC_Count,
   0, // XC_Count_e,

   0, // XC_HiLight,
   0, // XC_HiLight_e,
   0, // XC_SemiBold,
   0, // XC_SemiBold_e,

   0, // XC_CtrlDst,
   0, // XC_CtrlDst_e,

   0, // XC_ExplNorm,
   0, // XC_ExplNorm_e,

   0, // XC_Struct,
   0, // XC_Struct_e,
   0, // XC_OblStruct,
   0, // XC_OblStruct_e,

   0, // XC_Usage,
   0, // XC_Usage_e,

   0, // XC_HBase,
   0, // XC_HBase_e,

   0, // XC_ModCpdGroup,
   0, // XC_ModCpdGroup_e,

   0, // XC_ExampleTransl,
   0, // XC_ExampleTransl_e,

   0, // XC_IdiomTransl,
   0, // XC_IdiomTransl_e,

   0, // XC_TechNote,
   0, // XC_TechNote_e,

   0, // XC_IdMngGroup,
   0, // XC_IdMngGroup_e,

   0, // XC_RefInf,
   0, // XC_RefInf_e,

   0, // XC_SrcWord,
   0, // XC_SrcWord_e,

   0, // XC_ModCpdDst,
   0, // XC_ModCpdDst_e,

   0, // XC_ContextDst,
   0, // XC_ContextDst_e,

   0, // XC_ExplDst,
   0, // XC_ExplDst_e,

   0, // XC_RefWord,
   0, // XC_RefWord_e,

   0, // XC_RefNum,
   0, // XC_RefNum_e,

   0, // XC_RefXWord,
   0, // XC_RefXWord_e,

   0, // XC_RefTab,
   0, // XC_RefTab_e,

   0, // XC_RefPage,
   0, // XC_RefPage_e,

   0, // XC_RefHom,
   0, // XC_RefHom_e,

   0, // XC_SingleCpdWord,
   0, // XC_SingleCpdWord_e,

   0, // XC_FormGroupDst,
   0, // XC_FormGroupDst_e,

   0, // XC_DerivGroup,
   0, // XC_DerivGroup_e,

   0, // XC_Derivative,
   0, // XC_Derivative_e,

   0, // XC_StressParGroup,
   0, // XC_StressParGroup_e

   0, // XC_StressPar,
   0, // XC_StressPar_e,

   0, // XC_PunctMark,
   0, // XC_PunctMark_e,

   0, // XC_LevelGroup,
   0, // XC_LevelGroup_e,

   0, // XC_Level,
   0, // XC_Level_e,

   0, // XC_UsNoteSrc,
   0, // XC_UsNoteSrc_e,

   0, // XC_Img,
   0, // XC_Img_e,

   0, // XC_RefSecSynGr,
   0, // XC_RefSecSynGr_e,
   0, // XC_RefSecSyn,
   0, // XC_RefSecSyn_e,

   0, // XC_RefPriSynGr,
   0, // XC_RefPriSynGr_e,
   0, // XC_RefPriSyn,
   0, // XC_RefPriSyn_e,

   0, // XC_RefSynGr,
   0, // XC_RefSynGr_e,
   0, // XC_RefSyn,
   0, // XC_RefSyn_e,

   0, // XC_RefExamplGr,
   0, // XC_RefExamplGr_e,
   0, // XC_RefExampl,
   0, // XC_RefExampl_e,

   0, // XC_RefAntGr,
   0, // XC_RefAntGr_e,
   0, // XC_RefAnt,
   0, // XC_RefAnt_e,

   0, // XC_RefExamplSinglGr
   0, // XC_RefExamplSinglGr_e

   0, // XC_Subscript,
   0, // XC_Subscript_e,

   0, // XC_CodeExampleInline
   0, // XC_CodeExampleInline_e

   0, // XC_EnumGr,
   0, // XC_EnumGr_e,

   0, // XC_Enum,
   0, // XC_Enum_e,

   0, // XC_CodeBaseWord,
   0, // XC_CodeBaseWord_e,

   0, // XC_CodeExample,
   0, // XC_CodeExample_e,

   0, // XC_Table,
   0, // XC_Table_e,
   0, // XC_TableRow,
   0, // XC_TableRow_e,
   0, // XC_TableCell,
   0, // XC_TableCell_e,

   0, // XC_Equiation,
   0, // XC_Equiation_e,

   0, // XC_Break,
   0, // XC_Break_e,

   0, // XC_EquInline,
   0, // XC_EquInline_e,

   0, // XC_Special,
   0, // XC_Special_e,

   0, // XC_ExampleGroupForced
   0, // XC_ExampleGroupForced_e

   0, // XC_ExplForced,
   0, // XC_ExplForced_e,

   0, // XC_VarGroup,
   0, // XC_VarGroup_e,

   0, // XC_Relatives,
   0, // XC_Relatives_e,

   0, // XC_Page,
   0, // XC_Page_e,

   0, // XC_SemNr,
   0, // XC_SemNr_e,

   0, // XC_TrWordLit,
   0, // XC_TrWordLit_e,

   0, // XC_TrWordEng,
   0, // XC_TrWordEng_e,

   0, // XC_TrWordGer,
   0, // XC_TrWordGer_e,

   0, // XC_TrWordFre,
   0, // XC_TrWordFre_e,

   0, // XC_TrWordPol,
   0, // XC_TrWordPol_e,

   0, // XC_TrWordRus,
   0, // XC_TrWordRus_e,

   0, // XC_Species,
   0, // XC_Species_e,

   0, // XC_StructGroupForced,
   0, // XC_StructGroupForced_e,

   0, // XC_VarBold,
   0, // XC_VarBold_e,

   0, // XC_RefAntStrictGr,
   0, // XC_RefAntStrictGr_e,
   0, // XC_RefAntStrict,
   0, // XC_RefAntStrict_e,
};


// ================================================== free xmlt functions
HRESULT PutXmlHat(XmlO1 *pOutFile, const unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
XL_FileTypes fil_typ;
bool bin_fl;
bool wr_fl;
bool ap_fl;
XmlTagPars *tag_par = NULL;
UC_Modes enc_mode;
int ctbl, def_ctbl;
XmlVersions version;
bool multiline_sav;
#if FALSE
static unsigned char css_name[KP_MAX_FNAME_LEN+1];
#endif

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetVersion(&version);
   if((version!=XM_VERS_XML10) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileType(&fil_typ, XL_IX_DataFile);
   if(SUCCEEDED(retc) && (fil_typ!=XL_FT_Undefined) && (fil_typ!=XL_FT_DataFile))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileMode(&bin_fl, &wr_fl, &ap_fl);

   if((fil_typ==XL_FT_DataFile) && wr_fl && (!bin_fl) && (SUCCEEDED(retc)))
   {
      if(SUCCEEDED(retc)) retc=pOutFile->m_fFiles[XL_IX_DataFile]->GetMultiline(&multiline_sav);
      if(SUCCEEDED(retc)) retc=pOutFile->m_fFiles[XL_IX_DataFile]->SetMultiline(True);

// XC_Version
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"version", (const unsigned char *)"1.0", NULL));

      if(SUCCEEDED(retc)) retc = pOutFile->GetEncoding(&enc_mode, &ctbl, &def_ctbl);
      if(SUCCEEDED(retc))
      {
         if(enc_mode<UC_Unicode)
         {
            if(lpszaXmlCtblNames[ctbl][0]) retc = tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCtblNames[ctbl]);
            else if(lpszaXmlCtblNamesWin[ctbl][0]) retc = tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCtblNamesWin[ctbl]);
            else KP_ERROR(KP_E_SYSTEM_ERROR, null);
         }
         else
            retc=tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCodingModes[enc_mode]);
      }
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_Version, tag_par, XL_IX_DataFile);

      KP_DELETE(tag_par);

// XC_DocType
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"di", (const unsigned char *)"", NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"SYSTEM", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"", TV_XM_DtdName);
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_DocType, tag_par, XL_IX_DataFile);

      KP_DELETE(tag_par);

// XC_StyleSheet
#if FALSE
      if(SUCCEEDED(retc))
      {
         css_name[0] = Nul;
         if((strchr(TV_XM_CssName, '/')==NULL) && (strchr(TV_XM_CssName, '\\')==NULL) && SUCCEEDED(retc))
            retc = GetAppPath(css_name, True);
         if(strlen(css_name) + strlen(TV_XM_CssName) >= KP_MAX_FNAME_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) strcat(css_name, TV_XM_CssName);
      }
#endif
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"href", TV_XM_CssName, NULL)); // css_name));

      if(SUCCEEDED(retc)) retc=tag_par->GetOpenResult();
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text/css");
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_StyleSheet, tag_par, XL_IX_DataFile);

      KP_DELETE(tag_par);

// XC_Dict
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"name", lpszFileName, NULL));

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XC_Dict, tag_par, XL_IX_DataFile);

      KP_DELETE(tag_par);

// ------------------
      if(SUCCEEDED(retc)) retc=pOutFile->m_fFiles[XL_IX_DataFile]->SetMultiline(multiline_sav);
   }

return(retc);
}


HRESULT PutXmlHatI(XmlI *pOutFile, const unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
bool bin_fl;
bool wr_fl;
bool ap_fl;
XmlTagPars *tag_par;
UC_Modes enc_mode;
int ctbl, def_ctbl;
XmlVersions version;
bool multiline_sav;

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetVersion(&version);
   if((version!=XM_VERS_XML10) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileMode(&bin_fl, &wr_fl, &ap_fl);

   if(wr_fl && (!bin_fl) && (SUCCEEDED(retc)))
   {
      if(SUCCEEDED(retc)) retc=pOutFile->FilePtr->m_fFiles[XL_IX_DataFile]->GetMultiline(&multiline_sav);
      if(SUCCEEDED(retc)) retc=pOutFile->FilePtr->m_fFiles[XL_IX_DataFile]->SetMultiline(True);

// XC_Version
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"version", (const unsigned char *)"1.0", NULL));

      if(SUCCEEDED(retc)) retc=pOutFile->GetEncoding(&enc_mode, &ctbl, &def_ctbl);
      if(SUCCEEDED(retc))
      {
         if(enc_mode<UC_Unicode)
         {
            if(lpszaXmlCtblNames[ctbl][0]) retc=tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCtblNames[ctbl]);
            else if(lpszaXmlCtblNamesWin[ctbl][0]) retc=tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCtblNamesWin[ctbl]);
            else KP_ERROR(KP_E_SYSTEM_ERROR, null);
         }
         else
            retc=tag_par->AddTextPar((const unsigned char *)"encoding", lpszaXmlCodingModes[enc_mode]);
      }
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_Version, tag_par);

      KP_DELETE(tag_par);

// XC_DocType
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"di", (const unsigned char *)"", NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"SYSTEM", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"", TV_XM_DtdName);
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_DocType, tag_par);

      KP_DELETE(tag_par);

// XC_StyleSheet
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"href", TV_XM_CssName, NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text/css");
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_StyleSheet, tag_par);

      KP_DELETE(tag_par);

// XC_Dict
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"name", lpszFileName, NULL));

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XC_Dict, tag_par);

      KP_DELETE(tag_par);

// ------------------
      if(SUCCEEDED(retc)) retc=pOutFile->FilePtr->m_fFiles[XL_IX_DataFile]->SetMultiline(multiline_sav);
   }

return(retc);
}


HRESULT PutXmlTail(XmlO1 *pOutFile)
{
HRESULT retc=S_OK;
XL_FileTypes fil_typ;
bool bin_fl;
bool wr_fl;
bool ap_fl;
bool multiline;

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileType(&fil_typ, XL_IX_DataFile);
   if(SUCCEEDED(retc) && (fil_typ!=XL_FT_Undefined) && (fil_typ!=XL_FT_DataFile))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileMode(&bin_fl, &wr_fl, &ap_fl);

   if((fil_typ==XL_FT_DataFile) && wr_fl && (!bin_fl) && (SUCCEEDED(retc)))
   {
      if(SUCCEEDED(retc)) retc=pOutFile->m_fFiles[XL_IX_DataFile]->GetMultiline(&multiline);

      if((!multiline) && SUCCEEDED(retc)) retc=pOutFile->PutCharProc(C_Lf, NULL, XL_IX_DataFile);

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XC_Dict_e, NULL, XL_IX_DataFile);
   }

return(retc);
}


HRESULT PutXmlTailI(XmlI *pOutFile)
{
HRESULT retc=S_OK;
bool bin_fl;
bool wr_fl;
bool ap_fl;

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->GetFileMode(&bin_fl, &wr_fl, &ap_fl);

   if(wr_fl && (!bin_fl) && (SUCCEEDED(retc)))
      retc=pOutFile->PutCharProc((KpChar)XC_Dict_e, NULL);

return(retc);
}


// --------------------------------------------------
HRESULT XmltTestEmbedded(KpChar iTagCh, KpChar iPrevTag, bool *pbEmbedded)
{
HRESULT retc=S_OK;

   if(pbEmbedded==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbEmbedded=False;

      switch(iPrevTag)
      {
      case C_Nul:
         *pbEmbedded=
         (
            (iTagCh==XL_Version) ||
            (iTagCh==XL_DocType) ||
            (iTagCh==XL_StyleSheet) ||
            (iTagCh==XC_Dict) ||
            (iTagCh==XC_Special)
         );
         break;

      case XC_Dict:
         *pbEmbedded=
         (
            (iTagCh==XC_StEntry) ||
            (iTagCh==XC_NrtEntry) ||
            (iTagCh==XC_Special)
         );
         break;

      case XC_NrtEntry:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Img) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Special) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XC_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_StEntry:
         *pbEmbedded=
         (
            (iTagCh==XC_StEntryText) ||
            (iTagCh==XC_HeadWordGroup) ||
            (iTagCh==XC_VarGroup) ||
            (iTagCh==XC_Special)
         );
         break;

      case XC_StEntryText:
         *pbEmbedded=
         (
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_HeadWordGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_HeadWord) ||
            (iTagCh==XC_Base) ||
            (iTagCh==XC_HBase) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_SemNr) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) || // can be free text in abbreviation explanations
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_CompoundGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_DerivGroup) ||
            (iTagCh==XC_CtgGroup) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||
            (iTagCh==XC_UsNoteDst) ||
            (iTagCh==XC_UsNoteSrc) ||
            (iTagCh==XC_FwNote) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_RefSecSynGr) ||
            (iTagCh==XC_RefPriSynGr) ||
            (iTagCh==XC_RefSynGr) ||
            (iTagCh==XC_RefExamplGr) ||
            (iTagCh==XC_RefExamplSinglGr) ||
            (iTagCh==XC_RefAntGr) ||
            (iTagCh==XC_RefAntStrictGr) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_Similar) ||
            (iTagCh==XC_Approx) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_VarGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_HeadWord) ||
            (iTagCh==XC_Base) ||
            (iTagCh==XC_HBase) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_Hom) ||

            (iTagCh==XC_CompoundWord) ||
            (iTagCh==XC_SrcWord) ||

            (iTagCh==XC_Struct) ||
            (iTagCh==XC_OblStruct) ||

            (iTagCh==XC_Derivative) ||

            (iTagCh==XC_ModCpdSrc) ||
            (iTagCh==XC_ModCpdDst) ||

            (iTagCh==XC_Example) ||
            (iTagCh==XC_Usage) ||

            (iTagCh==XC_Idiom) ||

            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) || // can be free text in abbreviation explanations
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_UsNoteDst) ||
            (iTagCh==XC_UsNoteSrc) ||
            (iTagCh==XC_FwNote) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_Similar) ||
            (iTagCh==XC_Approx) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_HeadWord:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||

//          (iTagCh==XC_Italic) ||
//          (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
//          (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_Reference) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==VL_XM_CompDelim) || // C_Vertl
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Eq) || (iTagCh==C_Apost) || (iTagCh==C_Excl) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) || (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Base:
      case XC_HBase:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Asterix) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Slash) ||
            (TvIsAlpha((Chars16)iTagCh)) ||
//          (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Apost) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) ||
            (iTagCh==C_Minus) || (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Expand:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
//          (iTagCh==XC_PrGroup) ||

            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Eq) || (iTagCh==C_Apost) || (iTagCh==C_Excl) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) || (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Variant:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||

            (iTagCh==XC_RefSecSyn) ||

//          (iTagCh==XC_Italic) ||
//          (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
//          (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Apost) || (iTagCh==C_Eq) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) || (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_VarNorm:
      case XC_VarBold:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Hom) ||
//          (iTagCh==XC_Asterix) ||

            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Apost) || (iTagCh==C_Eq) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) || (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_CompoundGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_CompoundWord) ||
            (iTagCh==XC_SrcWord) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_PhrGroup) ||
//          (iTagCh==XC_CompoundGroup) ||
            (iTagCh==XC_DerivGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_CtgGroup) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_StructGroup:
      case XC_StructGroupForced:
         *pbEmbedded=
         (
//          (iTagCh==XC_CompoundWord) ||
            (iTagCh==XC_Struct) ||
            (iTagCh==XC_OblStruct) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_SrcWord) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Info) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
//          (iTagCh==XC_PhrGroup) ||
//          (iTagCh==XC_CompoundGroup) ||
//          (iTagCh==XC_DerivGroup) ||
//          (iTagCh==XC_StructGroup) ||
//          (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
//          (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_CtgGroup) ||
            (iTagCh==XC_MngGroup) ||
//          (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_DerivGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_Derivative) ||
            (iTagCh==XC_SrcWord) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_PhrGroup) ||
            (iTagCh==XC_CompoundGroup) ||
//          (iTagCh==XC_DerivGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_CtgGroup) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_PhrGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_CompoundGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_DerivGroup) ||

            (iTagCh==XC_CompoundWord) ||
            (iTagCh==XC_Struct) ||
            (iTagCh==XC_OblStruct) ||
            (iTagCh==XC_Derivative) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_SrcWord) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Info) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
//          (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_CtgGroup) ||
            (iTagCh==XC_MngGroup) ||
//          (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_CompoundWord:
      case XC_Derivative:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||

//          (iTagCh==XC_Italic) ||
//          (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
//          (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
//          (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Apost) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) && (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_ModCpdGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_ModCpdSrc) ||
            (iTagCh==XC_ModCpdDst) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_ModCpdSrc:
      case XC_ModCpdDst:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
//          (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
//          (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Apost) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) && (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Struct:
      case XC_OblStruct:
         *pbEmbedded=
         (
//          (iTagCh==XC_Hom) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||

//          (iTagCh==XC_Italic) ||
//          (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
//          (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
//          (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Apost) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) || (iTagCh==C_Minus) && (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_CtgGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_CompoundGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_DerivGroup) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_PrGroup) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_MngGroup) ||
//          (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
//          (iTagCh==XC_Inform) ||
//          (iTagCh==XC_VeryInform) ||
//          (iTagCh==XC_Vulgar) ||
//          (iTagCh==XC_Obs) ||
//          (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_MngGroup:
      case XC_CpdMngGroup:
      case XC_IdMngGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_CompoundGroup) ||
            (iTagCh==XC_StructGroup) ||
            (iTagCh==XC_StructGroupForced) ||
            (iTagCh==XC_DerivGroup) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_PrGroup) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) || // !!! gali but kategorija
            (iTagCh==XC_PartOfSpeechDst) || // !!! gali but kategorija
//          (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_IdiomGroup) ||

            (iTagCh==XC_UsNoteSrc) ||

            (iTagCh==XC_RefExamplGr) ||
            (iTagCh==XC_RefExamplSinglGr) ||
            (iTagCh==XC_RefSecSynGr) ||
            (iTagCh==XC_RefPriSynGr) ||
            (iTagCh==XC_RefSynGr) ||
            (iTagCh==XC_RefAntGr) ||
            (iTagCh==XC_RefAntStrictGr) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_MngNearGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
//          (iTagCh==XC_Hom) ||
//          (iTagCh==XC_Expand) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_PrGroup) ||
//          (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
//          (iTagCh==XC_PartOfSpeechSrc) ||
//          (iTagCh==XC_PartOfSpeechDst) ||
//          (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
//          (iTagCh==XC_IdiomGroup) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_ExampleGroup:
      case XC_ExampleGroupForced:
         *pbEmbedded=
         (
            (iTagCh==XC_Example) ||
            (iTagCh==XC_Usage) ||
            (iTagCh==XC_SrcWord) ||
            (iTagCh==XC_Expand) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_PartOfSpeechSrc) ||
//          (iTagCh==XC_PartOfSpeechDst) ||
//          (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_Info) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_MngGroup) ||
//          (iTagCh==XC_CpdMngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_TranslGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_Example:
      case XC_Usage:
      case XC_SrcWord:
         *pbEmbedded=
         (
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Paragraph) || // !!!
//          (iTagCh==XC_Table) || // !!!
            (iTagCh==XC_EnumGr) || // !!!

            (iTagCh==XC_RefExampl) ||

//          (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
//          (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
            (TvIsDigit((Chars16)iTagCh)) ||
            (iTagCh==VL_CH_IdiomDelim) || // C_Diamond
            (iTagCh==C_simeq) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Minus) || (iTagCh==C_Colon) || (iTagCh==C_QemSpc) ||
            (iTagCh==C_Lbrack) || (iTagCh==C_Rbrack) || (iTagCh==C_Lang) || (iTagCh==C_Rang) ||
//          (iTagCh==C_Slash) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_EnDash) || (iTagCh==C_Apost) || (iTagCh==C_Slash) ||
            (iTagCh==C_LBquote) || (iTagCh==C_Rquote) ||
            (iTagCh==C_Excl) || (iTagCh==C_Quest) ||
            (iTagCh==C_Circ) || (iTagCh==C_MidRing) ||
            (iTagCh==C_Perc) ||
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_IdiomGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Idiom) ||
            (iTagCh==XC_SrcWord) ||
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_ExampleGroup) ||
            (iTagCh==XC_ExampleGroupForced) ||
            (iTagCh==XC_MngGroup) ||
            (iTagCh==XC_IdMngGroup) ||
            (iTagCh==XC_MngNearGroup) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
//          (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
//          (iTagCh==XC_Reference) ||
//          (iTagCh==XC_Refinf) ||
            (iTagCh==XC_TranslGroup) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_Idiom:
         *pbEmbedded=
         (
//          (iTagCh==XC_Hom) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
            (iTagCh==VL_CH_IdiomDelim) || // !!! C_Diamond
            (iTagCh==C_simeq) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Minus) ||
            (iTagCh==C_Lbrack) || (iTagCh==C_Rbrack) || (iTagCh==C_Lang) || (iTagCh==C_Rang) ||
            (iTagCh==C_NBSP) ||
//          (iTagCh==C_Slash) ||
            (iTagCh==C_EnDash) || (iTagCh==C_Apost) || (iTagCh==C_Slash) ||
//          (iTagCh==C_Colon) || (iTagCh==C_QemSpc) ||
            (iTagCh==C_Excl) || (iTagCh==C_Quest) ||
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_TranslGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
            (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_ExampleTransl) ||
            (iTagCh==XC_IdiomTransl) ||
            (iTagCh==XC_TrWord) ||
            (iTagCh==XC_TrWordEng) ||
            (iTagCh==XC_TrWordGer) ||
            (iTagCh==XC_TrWordFre) ||
            (iTagCh==XC_TrWordPol) ||
            (iTagCh==XC_TrWordRus) ||
            (iTagCh==XC_TrWordLit) ||
            (iTagCh==XC_Gloss) ||
            (iTagCh==XC_Expand) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_FormGroupDst) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||

            (iTagCh==XC_Similar) ||
            (iTagCh==XC_Approx) ||

            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul)
         );
         break;

      case XC_TrWord:
      case XC_TrWordLit:
      case XC_TrWordEng:
      case XC_TrWordGer:
      case XC_TrWordFre:
      case XC_TrWordPol:
      case XC_TrWordRus:
      case XC_ExampleTransl:
      case XC_IdiomTransl:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Reference) ||
//          (iTagCh==XC_Refinf) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Paragraph) ||
//          (iTagCh==XC_Table) ||
            (iTagCh==XC_EnumGr) || // !!!
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||


//          (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
//          (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||

            (iTagCh==XC_Reference) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvIsDigit((Chars16)iTagCh)) ||
//          (iTagCh==VL_CH_IdiomDelim) || // !!! C_Diamond
            (iTagCh==C_Lbrack) || (iTagCh==C_Rbrack) || (iTagCh==C_Lang) || (iTagCh==C_Rang) ||
            (iTagCh==C_EnDash) || (iTagCh==C_Apost) ||
            (iTagCh==C_Excl) || (iTagCh==C_Quest) ||
            (iTagCh==C_Minus) || (iTagCh==C_QemSpc) ||
            (iTagCh==C_LBquote) || (iTagCh==C_Rquote) ||
            (iTagCh==VL_CH_ExamplDelim) || // ';'
            (iTagCh==C_NBSP) ||
            (iTagCh==C_simeq) || // !!!
            (iTagCh==C_Perc) ||
            (iTagCh==C_Circ) || (iTagCh==C_MidRing) ||
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Gloss:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
//          (iTagCh==XC_Reference) ||
//          (iTagCh==XC_Refinf) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Paragraph) ||
//          (iTagCh==XC_Table) ||
            (iTagCh==XC_EnumGr) || // !!!
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvIsDigit((Chars16)iTagCh)) ||
//          (iTagCh==VL_CH_IdiomDelim) || // !!! C_Diamond
            (iTagCh==C_Lbrack) || (iTagCh==C_Rbrack) || (iTagCh==C_Lang) || (iTagCh==C_Rang) ||
            (iTagCh==C_EnDash) || (iTagCh==C_Apost) ||
            (iTagCh==C_Excl) || (iTagCh==C_Quest) ||
            (iTagCh==C_Minus) || (iTagCh==C_QemSpc) ||
            (iTagCh==C_LBquote) || (iTagCh==C_Rquote) ||
            (iTagCh==VL_CH_ExamplDelim) || // ';'
            (iTagCh==C_NBSP) ||
            (iTagCh==C_simeq) || // !!!
            (iTagCh==C_Perc) ||
            (iTagCh==C_Circ) || (iTagCh==C_MidRing) ||
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_FwNote:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Paragraph) ||
            (iTagCh==XC_Table) ||
            (iTagCh==XC_EnumGr) ||

            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||
            (iTagCh==XC_CodeExample) ||
            (iTagCh==XC_CodeExampleInline) ||
            (iTagCh==XC_CodeBaseWord) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_UsNoteDst:
      case XC_UsNoteSrc:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_RefWord) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Paragraph) ||
            (iTagCh==XC_Table) ||
            (iTagCh==XC_EnumGr) ||

            (iTagCh==XC_Gloss) ||

            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||
            (iTagCh==XC_CodeExample) ||
            (iTagCh==XC_CodeExampleInline) ||
            (iTagCh==XC_CodeBaseWord) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XC_Img) ||
            (iTagCh==XC_Equiation) ||
            (iTagCh==XC_EquInline) ||

            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            ((iTagCh<C_CharSize0) && bFreeTextInUs)
         );
         break;

      case XC_TechNote:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_RefWord) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Paragraph) ||
            (iTagCh==XC_Table) ||
            (iTagCh==XC_EnumGr) ||

            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_PrGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_Pron) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_Nul) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special)

//          (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
//          (iTagCh<C_CharSize0)
         );
         break;

      case XC_Pron:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_PronRed) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Minus) || (iTagCh==C_Apost) || (iTagCh==C_Colon) ||
            (iTagCh==C_Lpar) || (iTagCh==C_Rpar) ||
//          (iTagCh==C_Slash) ||
            (iTagCh==C_Vertl) ||
            (iTagCh==C_QemSpc)
#else
            (iTagCh<C_CharSize0)
#endif
         );

//       if(iTagCh==XC_Abbr)
//       {
//          *pbEmbedded=True;
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (const unsigned char *)"Abbreviations inside of <ph>", False, __FILE__, __LINE__, lEntryId);
//       }
         break;

      case XC_PronRed:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh))
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_PartOfSpeechSrc:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh))
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_PartOfSpeechDst:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh))
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_StressParGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_StressPar) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
//          (iTagCh==XC_Parenth)
         );
         break;

      case XC_StressPar:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Super) ||
//          (iTagCh==XC_Subscript) ||
#ifdef VL_TEST_CHARS_ALLOWED
            TvIsDigit((Chars16)iTagCh) || TvIsAlpha((Chars16)iTagCh)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_CtrlGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_CtrlSrc) ||
            (iTagCh==XC_CtrlDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_FormSrc) ||
            (iTagCh==XC_FormDst) ||
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_CtrlSrc:
      case XC_CtrlDst:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Spc)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_FormGroupSrc:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_FormSrc) ||
//          (iTagCh==XC_Info) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
//          (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_CtrlSrc) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_FormSrc:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Minus) || (iTagCh==C_Lpar) || (iTagCh==C_Rpar) ||
//          (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_FormGroupDst:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_FormDst) ||
//          (iTagCh==XC_Info) ||
            (iTagCh==XC_PartOfSpeechDst) ||
//          (iTagCh==XC_StressParGroup) ||
//          (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_CtrlDst) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Nul)
         );
         break;

      case XC_FormDst:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Minus) || (iTagCh==C_Lpar) || (iTagCh==C_Rpar) ||
//          (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Slash)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Label:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

//          (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh))
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_ContextSrc:
      case XC_ContextDst:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_PunctMark:
      case XC_Abbr:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

//          (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Point) || (iTagCh==C_Spc)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_AbbrNorm:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

//          (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (iTagCh==C_Point) || (iTagCh==C_Spc)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Hom:
      case XC_RefHom:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

//          (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsDigit((Chars16)iTagCh))
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_ExplSrc:
      case XC_ExplNorm:
      case XC_ExplDst:
      case XC_ExplForced:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Variant) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvIsDigit((Chars16)iTagCh)) ||
            (iTagCh==C_Minus) || // '-'
            (iTagCh==C_Plus) || // '+'
            (iTagCh==C_Colon) || (iTagCh==C_Semic) || (iTagCh==C_Quest) || (iTagCh==C_EnDash) ||
            (iTagCh==C_NBSP) ||
            (iTagCh==C_LBquote) || (iTagCh==C_Rquote) ||
            (iTagCh==C_Perc) || (iTagCh==C_Circ) || (iTagCh==C_QemSpc) ||
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Reference:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_RefWord) ||
            (iTagCh==XC_RefNum) ||
            (iTagCh==XC_RefHom) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_RefXWord) ||
            (iTagCh==XC_RefTab) ||
            (iTagCh==XC_RefPage) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Img) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
            (iTagCh==C_Slash) ||
            (iTagCh==C_Spc) || (TvIsDigit((Chars16)iTagCh)) || (iTagCh==C_Point) || (iTagCh==C_Minus)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_RefInf:
         *pbEmbedded=
         (
            (iTagCh==XC_TechNote) ||

            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_RefWord) ||
            (iTagCh==XC_RefNum) ||
            (iTagCh==XC_RefHom) ||
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_RefXWord) ||
            (iTagCh==XC_RefTab) ||
            (iTagCh==XC_RefPage) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) ||
            (iTagCh==C_Slash) ||
            (iTagCh==C_Spc) || (TvIsDigit((Chars16)iTagCh)) || (iTagCh==C_Point) || (iTagCh==C_Minus)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_RefWord:
         *pbEmbedded=
         (
            (iTagCh==XC_Hom) ||
            (iTagCh==XC_RefHom) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_RefNum:
      case XC_RefXWord:
      case XC_RefTab:
      case XC_RefPage:
      case XC_Page:
      case XC_SemNr:
         *pbEmbedded=
         (
            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_RefSecSynGr:
         *pbEmbedded=
         (
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special)
         );
         break;

      case XC_RefPriSynGr:
         *pbEmbedded=
         (
            (iTagCh==XC_RefPriSyn) ||
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special)
         );
         break;

      case XC_RefSynGr:
         *pbEmbedded=
         (
            (iTagCh==XC_RefSyn) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_Abbr) ||

            (iTagCh==XC_Special)
         );
         break;

      case XC_RefExamplGr:
         *pbEmbedded=
         (
            (iTagCh==XC_Example) ||
//          (iTagCh==XC_RefExampl) ||
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special)
         );
         break;

      case XC_RefExamplSinglGr:
         *pbEmbedded=
         (
            (iTagCh==XC_Example) ||
//          (iTagCh==XC_RefExampl)
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special)
         );
         break;

      case XC_RefAntGr:
         *pbEmbedded=
         (
            (iTagCh==XC_RefAnt) ||
            (iTagCh==XC_RefNum) ||
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special)

//          (iTagCh==XL_Text) ||
//          (iTagCh<C_CharSize0) // !!! neturetu buti
         );
         break;

      case XC_RefAntStrictGr:
         *pbEmbedded=
         (
            (iTagCh==XC_RefAntStrict) ||
            (iTagCh==XC_RefNum) ||
            (iTagCh==XC_Label) ||

            (iTagCh==XC_Special) ||

            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Abbr) // ||

//          (iTagCh==XL_Text) ||
//          (iTagCh<C_CharSize0) // !!! neturetu buti
         );
         break;

      case XC_RefSecSyn:
      case XC_RefPriSyn:
      case XC_RefSyn:
      case XC_RefExampl:
      case XC_RefAnt:
      case XC_RefAntStrict:
         *pbEmbedded=
         (
            (iTagCh==XC_RefNum) ||

            (iTagCh==XC_AbbrNorm) ||

            (iTagCh==XC_Special) ||

            (iTagCh==XL_Text) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Parenth:
         *pbEmbedded=
         (
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
//          (iTagCh==XC_Hom) ||
//          (iTagCh==XC_RefHom) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_Label) ||
            (iTagCh==XC_ContextSrc) ||
            (iTagCh==XC_ContextDst) ||
            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_FormGroupDst) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
#ifdef VL_TEST_CHARS_ALLOWED
            (TvIsAlpha((Chars16)iTagCh)) || (TvIsDigit((Chars16)iTagCh)) ||
            (TvStrChr(lpszVlzDelims, iTagCh)!=NULL) ||
//          (iTagCh==VL_XM_CompDelim) || // C_Vertl
            (iTagCh==VL_XM_BaseAbbr) || // C_Tilde
            (iTagCh==C_Minus) || (iTagCh==C_Slash) ||
            (iTagCh==C_EnDash) ||
            (iTagCh==C_Apost) || (iTagCh==C_QemSpc) ||
            (iTagCh==C_Excl) || (iTagCh==C_Quest) ||
            (iTagCh==C_Apost) || (iTagCh==C_Colon) || (iTagCh==C_Semic) ||
            (iTagCh==VL_CH_ExamplDelim) || // ';'
            (iTagCh==C_NBSP) ||
            (iTagCh==C_Perc) || (iTagCh==C_Circ) ||
            (iTagCh==C_LBquote) || (iTagCh==C_Rquote) || // (iTagCh==C_LAquote) ||
            (iTagCh==C_Lbrack) || (iTagCh==C_Rbrack) // || (iTagCh==C_Lang) || (iTagCh==C_Rang)
#else
            (iTagCh<C_CharSize0)
#endif
         );
         break;

      case XC_Paragraph:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||
            (iTagCh==XC_Paragraph) || // !!!
            (iTagCh==XC_Break) ||

            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||
//          (iTagCh==XC_CodeExample) ||
            (iTagCh==XC_CodeExampleInline) ||
            (iTagCh==XC_CodeBaseWord) ||

            (iTagCh==XC_EnumGr) || // !!!
//          (iTagCh==XC_Table) || // !!!
            (iTagCh==XC_Equiation) ||
            (iTagCh==XC_EquInline) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Img) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_EnumGr:
         *pbEmbedded=
         (
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Enum)
         );
         break;

      case XC_Enum:
         *pbEmbedded=
         (
            (iTagCh==XC_Reference) ||

            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||
            (iTagCh==XC_CodeExample) ||
            (iTagCh==XC_CodeExampleInline) ||
            (iTagCh==XC_CodeBaseWord) ||

            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefNum) ||  // mac projektui

            (iTagCh==XC_Equiation) ||
            (iTagCh==XC_EquInline) ||
            (iTagCh==XC_Img) ||

            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_Paragraph) ||

            (iTagCh==XC_Special) ||

            (iTagCh==XL_Text) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Table:
         *pbEmbedded=
         (
            (iTagCh==XC_Special) ||

            (iTagCh==XC_TableRow)
         );
         break;

      case XC_TableRow:
         *pbEmbedded=
         (
            (iTagCh==XC_Special) ||

            (iTagCh==XC_TableCell)
         );
         break;

      case XC_TableCell:
         *pbEmbedded=
         (
            (iTagCh==XC_Paragraph) ||
            (iTagCh==XC_Italic) ||
            (iTagCh==XC_CodeBaseWord) ||
            (iTagCh==XC_Img) ||

            (iTagCh==XC_Special) ||

            (iTagCh==XL_Text) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Italic:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_HiLight:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_SemiBold:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Super:
      case XC_Subscript:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Symb) ||
            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

//    case XC_Info:
//       *pbEmbedded=
//       (
//          (iTagCh==XC_Special) ||
//          (iTagCh==XL_Text) ||
//          (iTagCh<C_CharSize0)
//       );
//       break;

      case XC_CodeExample:
      case XC_CodeExampleInline:
      case XC_CodeBaseWord:
         *pbEmbedded=
         (
            (iTagCh==XC_Special) ||
            (iTagCh==XL_Text) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_EquInline:
         *pbEmbedded=
         (
            (iTagCh==XC_Subscript) ||
            (iTagCh==XC_Super) ||
            (XC_SemiBold) ||

            (iTagCh==XC_Special) ||

            (iTagCh==XL_Text) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XL_Text:
//    case XL_TextExpr:
         *pbEmbedded=
         (
//          (iTagCh==XC_Parenth) ||

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

//          (iTagCh==XC_Symb) ||
//          (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
//          (iTagCh==XC_Inform) ||
//          (iTagCh==XC_VeryInform) ||
//          (iTagCh==XC_Vulgar) ||
//          (iTagCh==XC_Obs) ||
//          (iTagCh==XC_Arch) ||
//          (iTagCh==XC_Uncount) ||
//          (iTagCh==XC_Count) ||

            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Symb:
         *pbEmbedded=
         (
// ----
// reikia lvzg2t
            (iTagCh==XC_Asterix) ||

            (iTagCh==XC_Similar) ||
            (iTagCh==XC_Approx) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||
// ----

            (iTagCh==XC_LevelGroup) ||
            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Img) ||
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Nul:
         *pbEmbedded=
         (
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_Variant) ||
//          (iTagCh==XC_Hom) ||
//          (iTagCh==XC_RefHom) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_FormGroupDst) ||
            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_PunctMark)

//          (iTagCh==XC_LevelGroup) ||
//          (iTagCh==XC_Level) ||
//          (iTagCh==XC_Special) ||
         );
         break;

      case XC_LevelGroup:
         *pbEmbedded=
         (
            (iTagCh==XC_HeadWord) ||
            (iTagCh==XC_Variant) ||
            (iTagCh==XC_VarNorm) ||
            (iTagCh==XC_VarBold) ||
            (iTagCh==XC_Base) ||
            (iTagCh==XC_HBase) ||
            (iTagCh==XC_CompoundWord) ||
            (iTagCh==XC_ModCpdGroup) ||
            (iTagCh==XC_ModCpdSrc) ||
            (iTagCh==XC_ModCpdDst) ||
            (iTagCh==XC_SingleCpdWord) ||
            (iTagCh==XC_PhrGroup) ||
            (iTagCh==XC_Derivative) ||
            (iTagCh==XC_Struct) ||
            (iTagCh==XC_OblStruct) ||
            (iTagCh==XC_SrcWord) ||
            (iTagCh==XC_Example) ||
            (iTagCh==XC_Usage) ||
            (iTagCh==XC_Idiom) ||

            (iTagCh==XC_TrWord) ||
            (iTagCh==XC_ExampleTransl) ||
            (iTagCh==XC_IdiomTransl) ||

            (iTagCh==XC_Expand) ||
            (iTagCh==XC_Abbr) ||
            (iTagCh==XC_AbbrNorm) ||
            (iTagCh==XC_Gloss) ||

            (iTagCh==XC_Hom) ||

            (iTagCh==XC_PrGroup) ||
            (iTagCh==XC_Pron) ||
            (iTagCh==XC_PronRed) ||

            (iTagCh==XC_PartOfSpeechSrc) ||
            (iTagCh==XC_PartOfSpeechDst) ||
            (iTagCh==XC_Asterix) ||
            (iTagCh==XC_FormGroupDst) ||
            (iTagCh==XC_FormDst) ||
            (iTagCh==XC_FormGroupSrc) ||
            (iTagCh==XC_FormSrc) ||
            (iTagCh==XC_CtrlGroup) ||
            (iTagCh==XC_CtrlSrc) ||
            (iTagCh==XC_CtrlDst) ||
            (iTagCh==XC_StressParGroup) ||
            (iTagCh==XC_StressPar) ||

            (iTagCh==XC_ExplSrc) ||
            (iTagCh==XC_ExplNorm) ||
            (iTagCh==XC_ExplDst) ||
            (iTagCh==XC_ExplForced) ||
            (iTagCh==XC_ContextSrc) ||
            (iTagCh==XC_ContextDst) ||

            (iTagCh==XC_Label) ||
            (iTagCh==XC_Symb) ||
            (iTagCh==XC_Similar) ||
            (iTagCh==XC_Approx) ||
            (iTagCh==XC_Inform) ||
            (iTagCh==XC_Uncount) ||
            (iTagCh==XC_Count) ||
            (iTagCh==XC_Obs) ||
            (iTagCh==XC_Arch) ||
            (iTagCh==XC_VeryInform) ||
            (iTagCh==XC_Vulgar) ||

            (iTagCh==XC_Reference) ||
            (iTagCh==XC_RefInf) ||
            (iTagCh==XC_RefWord) ||
            (iTagCh==XC_RefNum) ||
            (iTagCh==XC_RefXWord) ||
            (iTagCh==XC_RefTab) ||
            (iTagCh==XC_RefPage) ||
            (iTagCh==XC_RefHom) ||

            (iTagCh==XC_UsNoteDst) ||
            (iTagCh==XC_UsNoteSrc) ||
            (iTagCh==XC_FwNote) ||
            (iTagCh==XC_TechNote) ||
            (iTagCh==XC_StEntryText) ||

            (iTagCh==XL_Text) ||
//          (iTagCh==XL_TextExpr) ||
            (iTagCh==XC_Italic) ||
            (iTagCh==XC_HiLight) ||
            (iTagCh==XC_SemiBold) ||
            (iTagCh==XC_Super) ||
            (iTagCh==XC_Subscript) ||
            (iTagCh==XC_Paragraph) ||
            (iTagCh==XC_Table) ||
            (iTagCh==XC_TableRow) ||
            (iTagCh==XC_TableCell) ||
            (iTagCh==XC_EnumGr) ||
            (iTagCh==XC_Parenth) ||
            (iTagCh==XC_PunctMark) ||

            (iTagCh==XC_Level) ||
            (iTagCh==XC_Special) ||

            (iTagCh==XC_Img) ||
// gali buti laisvas tekstas XL_Text laukuose
            (iTagCh==XL_Text) ||
////        (iTagCh==XL_TextExpr) ||
            (iTagCh<C_CharSize0)
         );
         break;

      case XC_Level:
         *pbEmbedded=
         (
            (iTagCh==XC_Special) ||
            (iTagCh==XL_Text) ||
//          (iTagCh<C_CharSize0)
            TvIsDigit(iTagCh)
         );
         break;

      case XC_Special:
         *pbEmbedded=
         (
            (iTagCh==XL_Text) ||
            (iTagCh<C_CharSize0)
         );
         break;

// ==========================================
// ------- HTML
#if TRUE // FALSE
      case HTM_TG_HTML:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_HEAD) ||
            (iTagCh == HTM_TG_BODY)
         );
         break;

      case HTM_TG_HEAD:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_META) ||
            (iTagCh == HTM_TG_LINK) ||
            (iTagCh == HTM_TG_SCRIPT) ||
            (iTagCh == HTM_TG_STYLE)
         );
         break;

      case HTM_TG_TITLE:
         *pbEmbedded=
         (
            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_BODY:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_CENTER) ||
            (iTagCh == HTM_TG_BIG) ||
            (iTagCh == HTM_TG_H1) ||
            (iTagCh == HTM_TG_H2) ||
            (iTagCh == HTM_TG_H3) ||
            (iTagCh == HTM_TG_H4) ||
            (iTagCh == HTM_TG_H5) ||
            (iTagCh == HTM_TG_H6) ||
            (iTagCh == HTM_TG_P) ||
            (iTagCh == HTM_TG_HR) ||
            (iTagCh == HTM_TG_PRE) ||
            (iTagCh == HTM_TG_SAMP) ||
            (iTagCh == HTM_TG_DIV) ||
            (iTagCh == HTM_TG_IFRAME) ||
            (iTagCh == HTM_TG_TABLE) ||
            (iTagCh == HTM_TG_UL) ||
            (iTagCh == HTM_TG_OL) ||
            (iTagCh == HTM_TG_FORM) ||
            (iTagCh == HTM_TG_MARQUEE) ||

//          (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) // ||

//          (iTagCh == HTM_TG_B) ||
//          (iTagCh == HTM_TG_I) ||
//          (iTagCh == HTM_TG_SUP) ||
//          (iTagCh == HTM_TG_SUB) ||
//          (iTagCh == HTM_TG_TT) ||
//          (iTagCh == HTM_TG_FONT) ||
//          (iTagCh == HTM_TG_A) ||
//          (iTagCh == HTM_TG_CODE) ||

//          (iTagCh == XL_Text) ||
//          (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_DIV:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_CENTER) ||
            (iTagCh == HTM_TG_BIG) ||
            (iTagCh == HTM_TG_H1) ||
            (iTagCh == HTM_TG_H2) ||
            (iTagCh == HTM_TG_H3) ||
            (iTagCh == HTM_TG_H4) ||
            (iTagCh == HTM_TG_H5) ||
            (iTagCh == HTM_TG_H6) ||
            (iTagCh == HTM_TG_P) ||
            (iTagCh == HTM_TG_HR) ||
            (iTagCh == HTM_TG_PRE) ||
            (iTagCh == HTM_TG_SAMP) ||
            (iTagCh == HTM_TG_IFRAME) ||
            (iTagCh == HTM_TG_TABLE) ||
            (iTagCh == HTM_TG_UL) ||
            (iTagCh == HTM_TG_OL) ||
            (iTagCh == HTM_TG_FORM) ||
            (iTagCh == HTM_TG_MARQUEE) ||

//          (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == HTM_TG_CAPTION) ||
            (iTagCh == HTM_TG_TH) ||
            (iTagCh == HTM_TG_TD) ||
            (iTagCh == HTM_TG_LI) // ||

//          (iTagCh == HTM_TG_B) ||
//          (iTagCh == HTM_TG_I) ||
//          (iTagCh == HTM_TG_SUP) ||
//          (iTagCh == HTM_TG_SUB) ||
//          (iTagCh == HTM_TG_TT) ||
//          (iTagCh == HTM_TG_FONT) ||
//          (iTagCh == HTM_TG_A) ||
//          (iTagCh == HTM_TG_CODE) ||

//          (iTagCh == XL_Text) ||
//          (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_TABLE:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_CAPTION) ||
            (iTagCh == HTM_TG_TBODY) // ||
         );
         break;

      case HTM_TG_TBODY:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_TR) // ||
         );
         break;

      case HTM_TG_TR:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_TH) ||
            (iTagCh == HTM_TG_TD) // ||
         );
         break;

      case HTM_TG_UL:
      case HTM_TG_OL:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_LI) // ||
         );
         break;

      case HTM_TG_FORM:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||
            (iTagCh == HTM_TG_INPUT) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_CENTER:
      case HTM_TG_BIG:
      case HTM_TG_H1:
      case HTM_TG_H2:
      case HTM_TG_H3:
      case HTM_TG_H4:
      case HTM_TG_H5:
      case HTM_TG_H6:
      case HTM_TG_P:
      case HTM_TG_PRE:
      case HTM_TG_SAMP:
      case HTM_TG_CAPTION:
      case HTM_TG_TH:
      case HTM_TG_TD:
      case HTM_TG_LI:
      case HTM_TG_NOSCRIPT:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_B:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_I:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_SUP:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_SUB:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_TT:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_A:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_SPAN) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_CODE:
         *pbEmbedded=
         (
            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

      case HTM_TG_SPAN:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_B) ||
            (iTagCh == HTM_TG_I) ||
            (iTagCh == HTM_TG_SUP) ||
            (iTagCh == HTM_TG_SUB) ||
            (iTagCh == HTM_TG_TT) ||
            (iTagCh == HTM_TG_FONT) ||
            (iTagCh == HTM_TG_A) ||
            (iTagCh == HTM_TG_CODE) ||
            (iTagCh == HTM_TG_BR) ||
            (iTagCh == HTM_TG_NOBR) ||
            (iTagCh == HTM_TG_IMG) ||
            (iTagCh == HTM_TG_OBJECT) ||
            (iTagCh == HTM_TG_EMBED) ||

            (iTagCh == XL_Text) ||
            (iTagCh < C_CharSize0)
         );
         break;

   case HTM_TG_OBJECT:
         *pbEmbedded=
         (
            (iTagCh == HTM_TG_PARAM) // ||
         );
         break;
#endif
      }

   } // if(SUCCEEDED(retc))

   if((iTagCh==C_Nul) && SUCCEEDED(retc)) *pbEmbedded=True;

   if(SUCCEEDED(retc)) retc=XmltTestEmbeddedLocal(iTagCh, iPrevTag, pbEmbedded);

return(retc);
}


// ----------------------------------------------
HRESULT GetGrTag(KpChar iTag, KpChar *piGrTag)
{
HRESULT retc=S_OK;

   if(piGrTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if((iTag>=XC_FirstDictTag) && (iTag<XC_LastDictTag) && (piGrTag!=NULL))
      {
         if(((iTag&1)!=0) || (TvKpStrChr(uiazXmlGrTags, iTag)!=NULL)) *piGrTag=C_Nul; // no grouping for closing and group tags
         else
         {
            *piGrTag=uiazXmlParGrTags[iTag-XC_FirstDictTag];
            if((*piGrTag==XC_HeadWordGroup) && (iTag!=XC_HeadWord)) *piGrTag=C_Nul;
         }
      }
      else
      {
         *piGrTag=C_Nul;
//       retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
   }

return(S_OK);
}

//---------------------------------
HRESULT XmlIcv(const unsigned char *lpszFileName)
{
unsigned char cmd_str[KP_MAX_FNAME_LEN+10+1];

   strcpy(cmd_str, "xmlicv ");
   strncpy(cmd_str+strlen(cmd_str), lpszFileName, KP_MAX_FNAME_LEN);
   cmd_str[KP_MAX_FNAME_LEN+10]=Nul;
   system((const char *)cmd_str);

return(S_OK);
}


// ----------------------------------
HRESULT LoadXmltTreeBitmaps(void)
{
HRESULT retc = S_OK;

   for(int ii = 0; (ii<XC_TG_NumOfDictTags00) && SUCCEEDED(retc); ii++)
   {
      if(lpszNodeBmpFNames[ii] && (!hNodeBitmaps[ii]) && SUCCEEDED(retc))
      {
         hNodeBitmaps[ii] = (HBITMAP)LoadImage(hKpInstance, lpszNodeBmpFNames[ii], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
         if(hNodeBitmaps[ii]==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


// -----------------------------------------------------------
const unsigned char *GetTagDelimiter(KpChar iPreviousTag, KpChar iNextTag)
{
const unsigned char *delim_ptr = (const unsigned char *)"";

   if(iPreviousTag == XL_Text) iPreviousTag = XC_Text_obs;
   if(iNextTag == XL_Text) iNextTag = XC_Text_obs;

   if((iPreviousTag >= XC_FirstDictTag) && (iPreviousTag < XC_LastDictTag) &&
      (iNextTag >= XC_FirstDictTag) && (iNextTag < XC_LastDictTag))
         delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(iPreviousTag - XC_FirstDictTag)/2][(iNextTag - XC_FirstDictTag)/2];

return(delim_ptr);
}

bool TestTagLevel(KpChar iTag, int iLevel)
{
HRESULT retc = S_OK;
bool retv = True;

   if(((iLevel < 0) || (iLevel >= NumOfLevels)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(iTag == XL_Text) iTag = XC_Text_obs;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag) && SUCCEEDED(retc))
      retv = baLevelTags[(iTag - XC_FirstDictTag)/2][iLevel];

// return(retc);
return(retv);
}


HBITMAP GetNodeBitmap(KpChar iTag)
{
HBITMAP retv = 0;

   if(iTag == XL_Text) iTag = XC_Text_obs;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
      retv = hNodeBitmaps[iTag - XC_FirstDictTag];

return(retv);
}


const unsigned char *GetTagName(KpChar iTag, const unsigned char * const plpszaTagNames[], KpChar iFirstDictTag, KpChar iLastDictTag)
{
HRESULT retc = S_OK;
const unsigned char *tag_name = (const unsigned char *)""; // = null; //

   if((iTag >= iFirstDictTag) && (iTag < iLastDictTag) && (iLastDictTag > C_Nul))
   {
      KP_ASSERT(plpszaTagNames != NULL, E_INVALIDARG, null, True);

const unsigned char * const *pnts = plpszaTagNames;
int tags_count = 0;
      if(SUCCEEDED(retc)) while(*pnts++) tags_count++;

      KP_ASSERT(iTag - iFirstDictTag < tags_count, E_INVALIDARG, null, True);

      if(SUCCEEDED(retc)) tag_name = plpszaTagNames[iTag - iFirstDictTag];
   }

   else if((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
      tag_name = plpszaXmlSysTags[iTag - XL_FirstSysTag];

   else if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag)) // < XM_FirstDictTagCode + XM_MaxNumOfDictTags))
      tag_name = plpszaXmlttDictTags[iTag - XC_FirstDictTag];

   else if((iTag >= HTM_TG_FirstTag) && (iTag < HTM_TG_LastTag)) // < HTM_TG_FirstTag + XH_MaxNumOfHtmTags))
      tag_name = plpszaHtmlTags[iTag - HTM_TG_FirstTag];

   else if((iTag >= XG_FirstGrpTag) && (iTag < XG_LastGrpTag))
      tag_name = plpszaGrpTags[iTag - XG_FirstGrpTag];

return(tag_name);
}


KpChar GetXmlParGrTag(KpChar iTag)
{
KpChar gr_tag = C_Nul;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
      gr_tag = uiazXmlParGrTags[iTag - XC_FirstDictTag];

return(gr_tag);
}


bool TestTagFreeText(KpChar iTag)
{
bool retv = True;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
      retv = baXmlDictTagsFreeText[iTag - XC_FirstDictTag];

return(retv);
}


unsigned char GetTagLang(KpChar iTag)
{
unsigned char retv = KP_LNG_NA;

   if(iTag == XL_Text) retv = KP_LNG_UP;
   else
      if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
         retv = caTgLangs[iTag - XC_FirstDictTag];

return(retv);
}
