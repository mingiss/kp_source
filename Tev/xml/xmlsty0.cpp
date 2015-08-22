// ==================================================
// xmlsty0.cpp
// Dummy style for xmln applications
//


// ==================================== definitions
#include "envir.h"

#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <richedit.h>
#include <Richole.h>

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
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "tvmain.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvtex.h"
#include "tvxmle.h"
#include "xmlsty.h"


//------------------------------------------
int iDelimCtbl = 1;
bool bS1toS2=False;
int SortMode=KP_LNG_ENG;
bool bMultiplToVeryInform = True;
bool bCutEndingsAfterApostrophe = False;
bool bFreeTextInUs = True;
int iCurFontSize=22;


//------------------------------------------
unsigned char caTgLangs[XC_TG_NumOfDictTagsArr68] =   // language codes of tags
{
      KP_LNG_NA,     // XC_Dict
      KP_LNG_NA,     // XC_Dict_e,

      KP_LNG_NA,     // XC_NrtEntry,
      KP_LNG_NA,     // XC_NrtEntry_e,

      KP_LNG_NA,     // XC_StEntry,
      KP_LNG_NA,     // XC_StEntry_e,

   KP_LNG_LIT,       // XC_HeadWord,
      KP_LNG_NA,     // XC_HeadWord_e,

      KP_LNG_NA,     // XC_Label,
      KP_LNG_NA,     // XC_Label_e,

   KP_LNG_GER,       // XC_TrWord,
      KP_LNG_NA,     // XC_TrWord_e,

   KP_LNG_GER,       // XC_UsNoteDst,
      KP_LNG_NA,     // XC_UsNoteDst_e,

   KP_LNG_LIT,       // XC_Reference,
      KP_LNG_NA,     // XC_Reference_e,

      KP_LNG_NA,     // XC_StEntryText,
      KP_LNG_NA,     // XC_StEntryText_e,

   KP_LNG_UP,        // XC_Paragraph,
      KP_LNG_NA,     // XC_Paragraph_e,

      KP_LNG_NA,     // XC_Version,
      KP_LNG_NA,     // XC_Version_e,

      KP_LNG_NA,     // XC_DocType,
      KP_LNG_NA,     // XC_DocType_e,

   KP_LNG_LIT,       // XC_Variant,
      KP_LNG_NA,     // XC_Variant_e,

      KP_LNG_NA,     // XC_PartOfSpeechSrc,
      KP_LNG_NA,     // XC_PartOfSpeechSrc_e,

      KP_LNG_NA,     // XC_HeadWordGroup,
      KP_LNG_NA,     // XC_HeadWordGroup_e,

      KP_LNG_NA,     // XC_TranslGroup,
      KP_LNG_NA,     // XC_TranslGroup_e,

   KP_LNG_GER, // KP_LNG_NA, // XC_FormDst,
      KP_LNG_NA,     // XC_FormDst_e,

   KP_LNG_LIT, // KP_LNG_NA, // XC_FormSrc,
      KP_LNG_NA,     // XC_FormSrc_e,

   KP_LNG_LIT,       // XC_ExplSrc,
      KP_LNG_NA,     // XC_ExplSrc_e,

   KP_LNG_LIT,       // XC_Example,
      KP_LNG_NA,     // XC_Example_e,

      KP_LNG_NA,     // XC_ExampleGroup,
      KP_LNG_NA,     // XC_ExampleGroup_e,

   KP_LNG_UP,        // XC_Parenth,
      KP_LNG_NA,     // XC_Parenth_e,

   KP_LNG_LIT,       // XC_Idiom,
      KP_LNG_NA,     // XC_Idiom_e,

      KP_LNG_NA,     // XC_IdiomGroup,
      KP_LNG_NA,     // XC_IdiomGroup_e,

      KP_LNG_NA,     // XC_CtgGroup,
      KP_LNG_NA,     // XC_CtgGroup_e,

   KP_LNG_LIT,       // XC_Base,
      KP_LNG_NA,     // XC_Base_e,

      KP_LNG_NA,     // XC_CompoundGroup,
      KP_LNG_NA,     // XC_CompoundGroup_e,

   KP_LNG_LIT,       // XC_CompoundWord,
      KP_LNG_NA,     // XC_CompoundWord_e,

      KP_LNG_NA,     // XC_MngGroup,
      KP_LNG_NA,     // XC_MngGroup_e,

      KP_LNG_NA,     // XC_Asterix,
      KP_LNG_NA,     // XC_Asterix_e,

      KP_LNG_NA,     // XC_CtrlSrc,
      KP_LNG_NA,     // XC_CtrlSrc_e,

      KP_LNG_NA,     // XC_PrGroup,
      KP_LNG_NA,     // XC_PrGroup_e,

      KP_LNG_NA,     // XC_Pron,
      KP_LNG_NA,     // XC_Pron_e,

   KP_LNG_NO,        // XC_Abbr,
      KP_LNG_NA,     // XC_Abbr_e,

      KP_LNG_NA,     // XC_Hom,
      KP_LNG_NA,     // XC_Hom_e,

   KP_LNG_LIT,       // XC_ContextSrc,
      KP_LNG_NA,     // XC_ContextSrc_e,

      KP_LNG_NA,     // XC_CtrlGroup,
      KP_LNG_NA,     // XC_CtrlGroup_e,

      KP_LNG_NA,     // XC_PartOfSpeechDst,
      KP_LNG_NA,     // XC_PartOfSpeechDst_e,

      KP_LNG_NA,     // XC_FormGroupSrc,
      KP_LNG_NA,     // XC_FormGroupSrc_e,

      KP_LNG_NA,     // XC_StyleSheet,
      KP_LNG_NA,     // XC_StyleSheet_e,

   KP_LNG_LIT,       // XC_VarNorm,
      KP_LNG_NA,     // XC_VarNorm_e,

   KP_LNG_NO,        // XC_AbbrNorm,
      KP_LNG_NA,     // XC_AbbrNorm_e,  space after not allowed - may be in free text

      KP_LNG_NA,     // XC_MngNearGroup
      KP_LNG_NA,     // XC_MngNearGroup_e

      KP_LNG_NA,     // XC_PronRed
      KP_LNG_NA,     // XC_PronRed_e

      KP_LNG_NA,     // XC_Nul
      KP_LNG_NA,     // XC_Nul_e

      KP_LNG_NA,     // XC_Similar
      KP_LNG_NA,     // XC_Similar_e

      KP_LNG_NA,     // XC_Approx
      KP_LNG_NA,     // XC_Approx_e

   KP_LNG_UP,        // XC_Text
      KP_LNG_NA,     // XC_Text_e

      KP_LNG_NA,     // XC_Info
      KP_LNG_NA,     // XC_Info_e

   KP_LNG_LIT,       // XC_Expand !!! gali buti abiem kalbom
      KP_LNG_NA,     // XC_Expand_e

      KP_LNG_NA,     // XC_StructGroup
      KP_LNG_NA,     // XC_StructGroup_e

   KP_LNG_GER,       // XC_Gloss
      KP_LNG_NA,     // XC_Gloss_e

      KP_LNG_NA,     // XC_FwNote
      KP_LNG_NA,     // XC_FwNote_e

   KP_LNG_UP,        // XC_Italic
      KP_LNG_NA,     // XC_Italic_e

   KP_LNG_LIT,       // XC_ModCpdSrc
      KP_LNG_NA,     // XC_ModCpdSrc_e

      KP_LNG_NA,     // XC_Symb
      KP_LNG_NA,     // XC_Symb_e

      KP_LNG_NA,     // XC_Inform
      KP_LNG_NA,     // XC_Inform_e

      KP_LNG_NA,     // XC_Uncount
      KP_LNG_NA,     // XC_Uncount_e

      KP_LNG_NA,     // XC_PhrGroup
      KP_LNG_NA,     // XC_PhrGroup_e

      KP_LNG_NA,     // XC_CpdMngGroup
      KP_LNG_NA,     // XC_CpdMngGroup_e

      KP_LNG_NA,     // XC_Obs
      KP_LNG_NA,     // XC_Obs_e

      KP_LNG_NA,     // XC_Arch
      KP_LNG_NA,     // XC_Arch_e

      KP_LNG_NA,     // XC_VeryInform
      KP_LNG_NA,     // XC_VeryInform_e

      KP_LNG_NA,     // XC_Vulgar
      KP_LNG_NA,     // XC_Vulgar_e

   KP_LNG_UP,        // XC_Super
      KP_LNG_NA,     // XC_Super_e

      KP_LNG_NA,     // XC_Count
      KP_LNG_NA,     // XC_Count_e

   KP_LNG_UP,        // XC_HiLight
      KP_LNG_NA,     // XC_HiLight_e

   KP_LNG_UP,        // XC_SemiBold
      KP_LNG_NA,     // XC_SemiBold_e

      KP_LNG_NA,     // XC_CtrlDst,
      KP_LNG_NA,     // XC_CtrlDst_e,

   KP_LNG_LIT,       // XC_ExplNorm, !!! gali buti abiem kalbom
      KP_LNG_NA,     // XC_ExplNorm_e,

   KP_LNG_LIT,       // XC_Struct,
      KP_LNG_NA,     // XC_Struct_e,

   KP_LNG_LIT,       // XC_OblStruct,
      KP_LNG_NA,     // XC_OblStruct_e,

   KP_LNG_LIT,       // XC_Usage,
      KP_LNG_NA,     // XC_Usage_e,

   KP_LNG_LIT,       // XC_HBase,
      KP_LNG_NA,     // XC_HBase_e,

     KP_LNG_NA,      // XC_ModCpdGroup
     KP_LNG_NA,      // XC_ModCpdGroup_e

   KP_LNG_GER,       // XC_ExampleTransl
     KP_LNG_NA,      // XC_ExampleTransl_e

   KP_LNG_GER,       // XC_IdiomTransl
     KP_LNG_NA,      // XC_IdiomTransl_e

     KP_LNG_NA,      // XC_TechNote
     KP_LNG_NA,      // XC_TechNote_e

     KP_LNG_NA,      // XC_IdMngGroup
     KP_LNG_NA,      // XC_IdMngGroup_e

     KP_LNG_NA,      // XC_Refinf
     KP_LNG_NA,      // XC_Refinf_e

   KP_LNG_LIT,       // XC_SrcWord,
     KP_LNG_NA,      // XC_SrcWord_e,

   KP_LNG_GER,       // XC_ModCpdDst
     KP_LNG_NA,      // XC_ModCpdDst_e

   KP_LNG_GER,       // XC_ContextDst
     KP_LNG_NA,      // XC_ContextDst_e

   KP_LNG_GER,       // XC_ExplDst
     KP_LNG_NA,      // XC_ExplDst_e

   KP_LNG_LIT,       // XC_RefWord
     KP_LNG_NA,      // XC_RefWord_e

     KP_LNG_NA,      // XC_RefNum
     KP_LNG_NA,      // XC_RefNum_e

   KP_LNG_LIT,       // XC_RefXWord
     KP_LNG_NA,      // XC_RefXWord_e

     KP_LNG_NA,      // XC_RefTab
     KP_LNG_NA,      // XC_RefTab_e

     KP_LNG_NA,      // XC_RefPage
     KP_LNG_NA,      // XC_RefPage_e

     KP_LNG_NA,      // XC_RefHom,
     KP_LNG_NA,      // XC_RefHom_e,

   KP_LNG_LIT,       // XC_SingleCpdWord
     KP_LNG_NA,      // XC_SingleCpdWord_e

     KP_LNG_NA,      // XC_FormGroupDst,
     KP_LNG_NA,      // XC_FormGroupDst_e,

     KP_LNG_NA,      // XC_DerivGroup
     KP_LNG_NA,      // XC_DerivGroup_e

   KP_LNG_LIT,       // XC_Derivative
     KP_LNG_NA,      // XC_Derivative_e

     KP_LNG_NA,      // XC_StressParGroup
     KP_LNG_NA,      // XC_StressParGroup_e

     KP_LNG_NA,      // XC_StressPar
     KP_LNG_NA,      // XC_StressPar_e

     KP_LNG_NA,      // XC_PunctMark
     KP_LNG_NA,      // XC_PunctMark_e

     KP_LNG_NA,      // XC_LevelGroup
     KP_LNG_NA,      // XC_LevelGroup_e

     KP_LNG_NA,      // XC_Level
     KP_LNG_NA,      // XC_Level_e

// KP_LNG_UP,        // XC_TextExpr
//   KP_LNG_NA,      // XC_TextExpr_e

   KP_LNG_LIT,       // XC_UsNoteSrc,
     KP_LNG_NA,      // XC_UsNoteSrc_e,

     KP_LNG_NA,      // XC_Img
     KP_LNG_NA,      // XC_Img_e

     KP_LNG_NA,      // XC_RefSecSynGr
     KP_LNG_NA,      // XC_RefSecSynGr_e

   KP_LNG_LIT,       // XC_RefSecSyn
     KP_LNG_NA,      // XC_RefSecSyn_e

     KP_LNG_NA,      // XC_RefPriSynGr
     KP_LNG_NA,      // XC_RefPriSynGr_e

   KP_LNG_LIT,       // XC_RefPriSyn
     KP_LNG_NA,      // XC_RefPriSyn_e

     KP_LNG_NA,      // XC_RefSynGr
     KP_LNG_NA,      // XC_RefSynGr_e

   KP_LNG_LIT,       // XC_RefSyn
     KP_LNG_NA,      // XC_RefSyn_e

     KP_LNG_NA,      // XC_RefExamplGr
     KP_LNG_NA,      // XC_RefExamplGr_e

   KP_LNG_LIT,       // XC_RefExampl
     KP_LNG_NA,      // XC_RefExampl_e

     KP_LNG_NA,      // XC_RefAntGr
     KP_LNG_NA,      // XC_RefAntGr_e

   KP_LNG_LIT,       // XC_RefAnt
     KP_LNG_NA,      // XC_RefAnt_e

     KP_LNG_NA,      // XC_RefExamplSinglGr
     KP_LNG_NA,      // XC_RefExamplSinglGr_e

   KP_LNG_UP,        // XC_Subscript
     KP_LNG_NA,      // XC_Subscript_e

     KP_LNG_NA,      // XC_CodeExampleInline
     KP_LNG_NA,      // XC_CodeExampleInline

      KP_LNG_NA,     // XC_EnumGr
      KP_LNG_NA,     // XC_EnumGr_e

   KP_LNG_LIT,       // XC_Enum
      KP_LNG_NA,     // XC_Enum_e

   KP_LNG_ENG,       // XC_CodeBaseWord
      KP_LNG_NA,     // XC_CodeBaseWord_e

   KP_LNG_ENG,       // XC_CodeExample
      KP_LNG_NA,     // XC_CodeExample_e

      KP_LNG_NA,     //  XC_Table
      KP_LNG_NA,     //  XC_Table_e
      KP_LNG_NA,     //  XC_TableRow
      KP_LNG_NA,     //  XC_TableRow_e
   KP_LNG_LIT,       //  XC_TableCell
      KP_LNG_NA,     //  XC_TableCell_e

      KP_LNG_NA,     //  XC_Equiation
      KP_LNG_NA,     //  XC_Equiation_e

      KP_LNG_NA,     //  XC_Break
      KP_LNG_NA,     //  XC_Break_e

      KP_LNG_NA,     //  XC_EquInline
      KP_LNG_NA,     //  XC_EquInline_e

      KP_LNG_NA,     //  XC_Special
      KP_LNG_NA,     //  XC_Special_e

      KP_LNG_NA,     //  XC_ExampleGroupForced
      KP_LNG_NA,     //  XC_ExampleGroupForced_e

   KP_LNG_LIT,       //  XC_ExplForced
      KP_LNG_NA,     //  XC_ExplForced_e

      KP_LNG_NA,     //  XC_VarGroup
      KP_LNG_NA,     //  XC_VarGroup_e

      KP_LNG_NA,     //  XC_Relatives
      KP_LNG_NA,     //  XC_Relatives_e

      KP_LNG_NA,     //  XC_Page
      KP_LNG_NA,     //  XC_Page_e

      KP_LNG_NA,     //  XC_SemNr
      KP_LNG_NA,     //  XC_SemNr_e

   KP_LNG_LIT,       //  XC_TrWordLit
      KP_LNG_NA,     //  XC_TrWordLit_e

   KP_LNG_ENG,       //  XC_TrWordEng
      KP_LNG_NA,     //  XC_TrWordEng_e

   KP_LNG_GER,       //  XC_TrWordGer
      KP_LNG_NA,     //  XC_TrWordGer_e

   KP_LNG_FRE,       //  XC_TrWordFre
      KP_LNG_NA,     //  XC_TrWordFre_e

   KP_LNG_POL,       //  XC_TrWordPol
      KP_LNG_NA,     //  XC_TrWordPol_e

   KP_LNG_RUS,       //  XC_TrWordRus
      KP_LNG_NA,     //  XC_TrWordRus_e

   KP_LNG_LAT,       //  XC_Species
      KP_LNG_NA,     //  XC_Species_e

      KP_LNG_NA,     // XC_StructGroupForced
      KP_LNG_NA,     // XC_StructGroupForced_e

   KP_LNG_LIT,       // XC_VarBold,
      KP_LNG_NA,     // XC_VarBold_e,

      KP_LNG_NA,     // XC_RefAntStrictGr
      KP_LNG_NA,     // XC_RefAntStrictGr_e
   KP_LNG_LIT,       // XC_RefAntStrict
      KP_LNG_NA,     // XC_RefAntStrict_e
};


// -----------------------------------
const unsigned char caIxLangs[XL_IX_NumOfIndexes3] = // former caLvzIxLangs
{
   KP_LNG_NO,   // XL_IX_DataFile,      // XML data file
   KP_LNG_NO,   // XL_IX_SeIndex,       // standard entry index file
   KP_LNG_NO,   // KP_LNG_LIT,  // XL_IX_HwIndex,       // headword index file

   KP_LNG_NO,   // KP_LNG_GER,  // XL_IX_TwIndex,       // translated headword index file

   KP_LNG_NO,   // XL_IX_LaIndex,       // label index file
   KP_LNG_NO,   // XL_IX_StIndex,       // standard entry text index file
   KP_LNG_NO,   // XL_IX_EdIndex,       // editorial notes index file (record creation date etc.)

   KP_LNG_NO,   // XL_IX_TxIndex,       // full text index file
   KP_LNG_NO,   // XL_IX_HxIndex,       // headword full text index file
};


// -----------------------------------
bool baLevelTags[XC_TG_NumOfDictTagsArr68/2][NumOfLevels1] =
{
// FullLevel AcademicLevel BigLevel Level_3 SchoolLevel Level_5 SimplyLevel

   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Dict,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_NrtEntry,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_StEntry,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_HeadWord,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Label,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWord,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_UsNoteDst,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Reference
   { False,     False,      False,  False,     False,    False,  False, }, // XC_StEntryText,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Paragraph,
   { False,     False,      False,  False,     False,    False,  False, }, // XC_Version,
   { False,     False,      False,  False,     False,    False,  False, }, // XC_DocType,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Variant,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_PartOfSpeechSrc,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_HeadWordGroup,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TranslGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_FormDst,
   {  True,      True,       True,  False,     False,    False,  False, }, // XC_FormSrc,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ExplSrc,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Example,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ExampleGroup,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Parenth,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Idiom,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_IdiomGroup,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_CtgGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Base,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_CompoundGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_CompoundWord,
   {  True,      True,       True,   True,      True,     True,  True,  }, // XC_MngGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Asterix,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_CtrlSrc,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_PrGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Pron,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Abbr,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Hom,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ContextSrc,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_CtrlGroup,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_PartOfSpeechDst,
   {  True,      True,       True,  False,     False,    False,  False, }, // XC_FormGroupSrc,
   { False,     False,      False,  False,     False,    False,  False, }, // XC_StyleSheet,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_VarNorm,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_AbbrNorm,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_MngNearGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_PronRed
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Nul
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Similar
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Approx
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Text
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Info
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Expand
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_StructGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Gloss
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_FwNote
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Italic
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ModCpdSrc
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Symb
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Inform
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Uncount
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_PhrGroup
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_CpdMngGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Obs
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Arch
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_VeryInform
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Vulgar
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Super
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Count
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_HiLight
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_SemiBold
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_CtrlDst
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ExplNorm
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Struct,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_OblStruct,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Usage,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_HBase,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ModCpdGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ExampleTransl
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_IdiomTransl
   { False,     False,      False,  False,     False,    False,  False, }, // XC_TechNote
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_IdMngGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Refinf
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_SrcWord,
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ModCpdDst
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ContextDst
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_ExplDst
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefWord
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefNum
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefXWord
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefTab
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefPage
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_RefHom
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_SingleCpdWord
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_FormGroupDst
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_DerivGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Derivative
   {  True,      True,       True,  False,     False,    False,  False, }, // XC_StressParGroup
   {  True,      True,       True,  False,     False,    False,  False, }, // XC_StressPar
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_PunctMark
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_LevelGroup
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Level
// {  True,      True,       True,   True,      True,     True,   True, }, // XC_TextExpr
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_UsNoteSrc,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Img
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefSecSynGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefSecSyn
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefPriSynGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefPriSyn
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefSynGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefSyn
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefExamplGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefExampl
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefAntGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefAnt
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefExamplSinglGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Subscript
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_CodeExampleInline
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_EnumGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Enum
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_CodeBaseWord
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_CodeExample
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Table
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TableRow
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TableCell
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Equiation
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Break
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_EquInline
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Special
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_ExampleGroupForced
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_ExplForced
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_VarGroup
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Relatives
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_Page
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_SemNr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordLit,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordEng,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordGer,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordFre,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordPol,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_TrWordRus,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_Species,
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_StructGroupForced
   {  True,      True,       True,   True,      True,     True,  False, }, // XC_VarBold
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefAntStrictGr
   {  True,      True,       True,   True,      True,     True,   True, }, // XC_RefAntStrict
};


// ------------------------------------
// delimiters between tags: lpszXmlTagDelimiters[PreviousTag/2][NextTag/2]
//

const char *lpszXmlTagDelimiters[XC_TG_NumOfDictTagsArr68/2][XC_TG_NumOfDictTagsArr68/2] = // possibly import from tvxmlt.css !!!
{
// <di> <ue> <se> <hw> <la> <tw> <un> <xr> <st> <p> XC_Version XC_DocType <v> <ps> <hg> <tg> <f> <fs> <ic> <le> <eg> <pt> <li> <id> <s1> <base> <cg> <lc> <s2> <ast/> <sp> <pr> <ph> <ct> <hm> <co> <pp> <gr> <fg> XC_StyleSheet <vn> <cn> <s3> <pd> XC_Nul  <sim/> <apr/> XC_Text XC_Info <ef> <sg> <gl> <fun> <i> <mc> XC_Symb <if/> <uc/> <pvp> XC_CpdMngGroup <obs/> <arc/> <vif/> <vul/> <su> <cnt/> <hl> <sb> <dp> <in> <ls> <lo> <lu> <hbase>  <mg> XC_ExampleTransl XC_IdiomTransl <ed> XC_IdMngGroup XC_Refinf <lw> <md> <cd> <dc> <x> <xs> <fx> <t> <n> <hm!!!> <cw> <fd> <dg> <ld> <ag> <ac> <cp> <lg> <lv> <us> <img/> <xcg> <xc> <xpg> <xp> <xyg> <xy> <xeg> <xe> <xag> <xa> <xng> <sub> <ce> <ng> <en> <cb> <cl> <table> <tr> <td> <eq><br/> <el> <sl><egf><icf> <vg><rel/> <tn> <nr><twl><twe><twg><twf><twp><twr><vs><sgf> <vb> <xtg> <xt>

   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <di>    XC_Dict
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ue>    XC_NrtEntry,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <se>    XC_StEntry,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hw>    XC_HeadWord,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <la>    XC_Label,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <tw>    XC_TrWord,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <un>    XC_UsNoteDst,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xr>    XC_Reference,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <st>    XC_StEntryText,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <p>     XC_Paragraph,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Version,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_DocType,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <v>     XC_Variant,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ps>    XC_PartOfSpeechSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hg>    XC_HeadWordGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <tg>    XC_TranslGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <f>     XC_FormDst,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <fs>    XC_FormSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ic>    XC_ExplSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <le>    XC_Example,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <eg>    XC_ExampleGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <pt>    XC_Parenth,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <li>    XC_Idiom,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <id>    XC_IdiomGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <s1>    XC_CtgGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <base>  XC_Base,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cg>    XC_CompoundGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lc>    XC_CompoundWord,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <s2>    XC_MngGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ast/>  XC_Asterix,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sp>    XC_CtrlSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <pr>    XC_PrGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ph>    XC_Pron,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ct>    XC_Abbr,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hm>    XC_Hom,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <co>    XC_ContextSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <pp>    XC_CtrlGroup,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <gr>    XC_PartOfSpeechDst,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <fg>    XC_FormGroupSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_StyleSheet,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vn>    XC_VarNorm,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cn>    XC_AbbrNorm,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <s3>    XC_MngNearGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <pd>    XC_PronRed
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Nul
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sim/>  XC_Similar
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <apr/>  XC_Approx
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Text
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Info
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ef>    XC_Expand
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sg>    XC_StructGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <gl>    XC_Gloss
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <fun>   XC_FwNote
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <i>     XC_Italic
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <mc>    XC_ModCpdSrc
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Symb
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <if/>   XC_Inform
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <uc/>   XC_Uncount
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <pvp>   XC_PhrGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_CpdMngGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <obs/>  XC_Obs
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <arc/>  XC_Arch
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vif/>  XC_VeryInform
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vul/>  XC_Vulgar
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <su>    XC_Super
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cnt/>  XC_Count
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hl>    XC_HiLight
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sb>    XC_SemiBold
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <dp>    XC_CtrlDst
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <in>    XC_ExplNorm
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ls>    XC_Struct
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lo>    XC_OblStruct
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lu>    XC_Usage
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hbase> XC_HBase,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <mg>    XC_ModCpdGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_ExampleTransl
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_IdiomTransl
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ed>    XC_TechNote
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_IdMngGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, //         XC_Refinf
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lw>    XC_SrcWord
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <md>    XC_ModCpdDst
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cd>    XC_ContextDst
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <dc>    XC_ExplDst
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <x>     XC_RefWord
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xs>    XC_RefNum
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <fx>    XC_RefXWord
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <t>     XC_RefTab
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <n>     XC_RefPage
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <hm>    XC_RefHom,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cw>    XC_SingleCpdWord
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <fd>    XC_FormGroupDst
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <dg>    XC_DerivGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ld>    XC_Derivative
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ag>    XC_StressParGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ac>    XC_StressPar
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cp>    XC_PunctMark
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lg>    XC_LevelGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <lv>    XC_Level
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <us>    XC_UsNoteSrc,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <img/>  XC_Img
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xcg>   XC_RefSecSynGr        // AKLZ "Dar vartojama"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xc>    XC_RefSecSyn
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xpg>   XC_RefPriSynGr        // AKLZ "Zr."
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xp>    XC_RefPriSyn
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xyg>   XC_RefSynGr           // AKLZ "Zr. dar"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xy>    XC_RefSyn
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xeg>   XC_RefExamplGr        // AKLZ "Pavyzdziai:"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xe>    XC_RefExampl
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xag>   XC_RefAntGr           // AKLZ "Plg.,"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xa>    XC_RefAnt
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xng>   XC_RefExamplSinglGr   // AKLZ "Pavyzdys:"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sub>   XC_Subscript
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ce>    XC_CodeExampleInline
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <ng>    XC_EnumGr
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <en>    XC_Enum
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cb>    XC_CodeBaseWord
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <cl>    XC_CodeExample
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <table> XC_Table
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <tr>    XC_TableRow
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <td>    XC_TableCell
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <eq>    XC_Equiation
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <br/>   XC_Break,
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <el>    XC_EquInline
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sl>    XC_Special
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <egf>   XC_ExampleGroupForced
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <icf>   XC_ExplForced
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vg>    XC_VarGroup
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <rel/>  XC_Relatives
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <tn>    XC_Page
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <nr>    XC_SemNr
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twl>   XC_TrWordLit
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twe>   XC_TrWordEng
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twg>   XC_TrWordGer
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twf>   XC_TrWordFre
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twp>   XC_TrWordPol
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <twr>   XC_TrWordRus
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vs>    XC_Species
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <sgf>   XC_StructGroupForced
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <vb>    XC_VarBold
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xtg>   XC_RefAntStrictGr           // AKLZ "Plg.,"
   { "",  "",  "",  "",  "",  "",  "",  "",  "", "",        "",        "", "",  "",  "",  "", "",  "",  "",  "",  "",  "",  "",  "",  "",    "",  "",  "",  "",    "",  "",  "",  "",  "",  "",  "",  "",  "",  "",           "",  "",  "",  "",  "",    "",     "",    "",     "",     "",  "",  "",  "",   "", "",  "",     "",   "",   "",   "",            "",    "",    "",    "",    "",  "",    "",  "",  "",  "",  "",  "",  "",  "",     "",   "",              "",            "",  "",           "",       "",  "",  "",  "",  "", "",  "",  "", "", "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",  "",    "",   "",  "",   "",  "",   "",  "",   "",  "",   "",  "",   "",   "",  "",  "",  "",  "",  "",     "",  "",  "",  "",  "",  "",  "",  "",  "",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "", "",  "",  "",   "",  "", }, // <xt>    XC_RefAntStrict
};
