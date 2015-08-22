// ==================================================
// xmlsty2.cpp
// Dummy style for non lzdsh applications
//


// ==================================== definitions
#include "envir.h"
#include "iBshn.h"

#include <stdlib.h>
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
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "xmlsty.h"


// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// ----------------------------------
COLORREF KpColorScheme[KpNumOfShadows3]={
/* W2k: */ RGB(214,211,206), // Win98: RGB(191,191,191), // XP: RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor
};


// ----------------------------------
const unsigned char *lpszaParStyInlineCmds[XMLT_NUM_OF_PAR_STYLES] =
{
   (const unsigned char *)"",
   (const unsigned char *)""
};


// -------------------------------------------------------------
const char *lpszNodeBmpFNames[XC_TG_NumOfDictTagsArr68] =
{
   NULL, // XC_Dict
   NULL, // XC_Dict_e,

   NULL, // XC_NrtEntry,
   NULL, // XC_NrtEntry_e,
   NULL, // "node_se.bmp", // XC_StEntry,
   NULL, // XC_StEntry_e,

   NULL, // XC_HeadWord,
   NULL, // XC_HeadWord_e,
   NULL, // XC_Label,
   NULL, // XC_Label_e,
   NULL, // XC_TrWord,
   NULL, // XC_TrWord_e,
   NULL, // XC_UsNoteDst,
   NULL, // XC_UsNoteDst_e,
   NULL, // XC_Reference,
   NULL, // XC_Reference_e,
   NULL, // XC_StEntryText,
   NULL, // XC_StEntryText_e,
   NULL, // XC_Paragraph,
   NULL, // XC_Paragraph_e,

      NULL, // XC_Version_obs,
      NULL, // XC_Version_obs_e,
      NULL, // XC_DocType_obs,
      NULL, // XC_DocType_obs_e,

   NULL, // XC_Variant,
   NULL, // XC_Variant_e,
   NULL, // XC_PartOfSpeechSrc,
   NULL, // XC_PartOfSpeechSrc_e,

   NULL, // "node_hg.bmp", // XC_HeadWordGroup,
   NULL, // XC_HeadWordGroup_e,
   NULL, // "node_tg.bmp", // XC_TranslGroup,
   NULL, // XC_TranslGroup_e,

   NULL, // XC_FormDst,
   NULL, // XC_FormDst_e,
   NULL, // XC_FormSrc,
   NULL, // XC_FormSrc_e,

   NULL, // XC_ExplSrc,
   NULL, // XC_ExplSrc_e,

   NULL, // XC_Example,
   NULL, // XC_Example_e,
   NULL, // "node_eg.bmp", // XC_ExampleGroup,
   NULL, // XC_ExampleGroup_e,

   NULL, // XC_Parenth,
   NULL, // XC_Parenth_e,

   NULL, // XC_Idiom,
   NULL, // XC_Idiom_e,

   NULL, // "node_id.bmp", // XC_IdiomGroup,
   NULL, // XC_IdiomGroup_e,

   NULL, // "node_s1.bmp", // XC_CtgGroup,
   NULL, // XC_CtgGroup_e,

   NULL, // XC_Base,
   NULL, // XC_Base_e,
   NULL, // "node_cg.bmp", // XC_CompoundGroup,
   NULL, // XC_CompoundGroup_e,
   NULL, // XC_CompoundWord,
   NULL, // XC_CompoundWord_e,

   NULL, // "node_s2.bmp", // XC_MngGroup,
   NULL, // XC_MngGroup_e,

   NULL, // XC_Asterix,
   NULL, // XC_Asterix_e,

   NULL, // XC_CtrlSrc,
   NULL, // XC_CtrlSrc_e,

   NULL, // XC_PrGroup,
   NULL, // XC_PrGroup_e,
   NULL, // XC_Pron,
   NULL, // XC_Pron_e,

   NULL, // XC_Abbr,
   NULL, // XC_Abbr_e,

   NULL, // XC_Hom,
   NULL, // XC_Hom_e,

   NULL, // XC_ContextSrc,
   NULL, // XC_ContextSrc_e,

   NULL, // XC_CtrlGroup,
   NULL, // XC_CtrlGroup_e,

   NULL, // XC_PartOfSpeechDst,
   NULL, // XC_PartOfSpeechDst_e

   NULL, // XC_FormGroupSrc,
   NULL, // XC_FormGroupSrc_e,

      NULL, // XC_StyleSheet_obs,
      NULL, // XC_StyleSheet_obs_e

   NULL, // XC_VarNorm,
   NULL, // XC_VarNorm_e,

   NULL, // XC_AbbrNorm,
   NULL, // XC_AbbrNorm_e,

   NULL, // "node_s3.bmp", // XC_MngNearGroup,
   NULL, // XC_MngNearGroup_e,

   NULL, // XC_PronRed,
   NULL, // XC_PronRed_e,

   NULL, // XC_Nul,
   NULL, // XC_Nul_e,

   NULL, // XC_Similar,
   NULL, // XC_Similar_e,

   NULL, // XC_Approx,
   NULL, // XC_Approx_e,

   NULL, // XC_Text,
   NULL, // XC_Text_e,

   NULL, // XC_Info,
   NULL, // XC_Info_e,

   NULL, // XC_Expand,
   NULL, // XC_Expand_e,

   NULL, // "node_eg.bmp", // XC_StructGroup,
   NULL, // XC_StructGroup_e,

   NULL, // XC_Gloss,
   NULL, // XC_Gloss_e,

   NULL, // XC_FwNote,
   NULL, // XC_FwNote_e,

   NULL, // XC_Italic,
   NULL, // XC_Italic_e,

   NULL, // XC_ModCpdSrc,
   NULL, // XC_ModCpdSrc_e,

   NULL, // XC_Symb,
   NULL, // XC_Symb_e,

   NULL, // XC_Inform,
   NULL, // XC_Inform_e,
   NULL, // XC_Uncount,
   NULL, // XC_Uncount_e,

   NULL, // XC_PhrGroup,
   NULL, // XC_PhrGroup_e,

   NULL, // "node_s2.bmp", // XC_CpdMngGroup,
   NULL, // XC_CpdMngGroup_e,

   NULL, // XC_Obs,
   NULL, // XC_Obs_e,
   NULL, // XC_Arch,
   NULL, // XC_Arch_e,
   NULL, // XC_VeryInform,
   NULL, // XC_VeryInform_e,
   NULL, // XC_Vulgar,
   NULL, // XC_Vulgar_e,

   NULL, // XC_Super,
   NULL, // XC_Super_e,

   NULL, // XC_Count,
   NULL, // XC_Count_e,

   NULL, // XC_HiLight,
   NULL, // XC_HiLight_e,
   NULL, // XC_SemiBold,
   NULL, // XC_SemiBold_e,

   NULL, // XC_CtrlDst,
   NULL, // XC_CtrlDst_e,

   NULL, // XC_ExplNorm,
   NULL, // XC_ExplNorm_e,

   NULL, // XC_Struct,
   NULL, // XC_Struct_e,
   NULL, // XC_OblStruct,
   NULL, // XC_OblStruct_e,

   NULL, // XC_Usage,
   NULL, // XC_Usage_e,

   NULL, // XC_HBase,
   NULL, // XC_HBase_e,

   NULL, // XC_ModCpdGroup,
   NULL, // XC_ModCpdGroup_e,

   NULL, // XC_ExampleTransl,
   NULL, // XC_ExampleTransl_e,

   NULL, // XC_IdiomTransl,
   NULL, // XC_IdiomTransl_e,

   NULL, // XC_TechNote,
   NULL, // XC_TechNote_e,

   NULL, // "node_s2.bmp", // XC_IdMngGroup,
   NULL, // XC_IdMngGroup_e,

   NULL, // XC_RefInf,
   NULL, // XC_RefInf_e,

   NULL, // XC_SrcWord,
   NULL, // XC_SrcWord_e,

   NULL, // XC_ModCpdDst,
   NULL, // XC_ModCpdDst_e,

   NULL, // XC_ContextDst,
   NULL, // XC_ContextDst_e,

   NULL, // XC_ExplDst,
   NULL, // XC_ExplDst_e,

   NULL, // XC_RefWord,
   NULL, // XC_RefWord_e,

   NULL, // XC_RefNum,
   NULL, // XC_RefNum_e,

   NULL, // XC_RefXWord,
   NULL, // XC_RefXWord_e,

   NULL, // XC_RefTab,
   NULL, // XC_RefTab_e,

   NULL, // XC_RefPage,
   NULL, // XC_RefPage_e,

   NULL, // XC_RefHom,
   NULL, // XC_RefHom_e,

   NULL, // XC_SingleCpdWord,
   NULL, // XC_SingleCpdWord_e,

   NULL, // XC_FormGroupDst,
   NULL, // XC_FormGroupDst_e,

   NULL, // "node_cg.bmp", // XC_DerivGroup,
   NULL, // XC_DerivGroup_e,

   NULL, // XC_Derivative,
   NULL, // XC_Derivative_e,

   NULL, // XC_StressParGroup,
   NULL, // XC_StressParGroup_e

   NULL, // XC_StressPar,
   NULL, // XC_StressPar_e,

   NULL, // XC_PunctMark,
   NULL, // XC_PunctMark_e,

   NULL, // XC_LevelGroup,
   NULL, // XC_LevelGroup_e,

   NULL, // XC_Level,
   NULL, // XC_Level_e,

   NULL, // XC_UsNoteSrc,
   NULL, // XC_UsNoteSrc_e,

   NULL, // XC_Img,
   NULL, // XC_Img_e,

   NULL, // XC_RefSecSynGr,
   NULL, // XC_RefSecSynGr_e,
   NULL, // XC_RefSecSyn,
   NULL, // XC_RefSecSyn_e,

   NULL, // XC_RefPriSynGr,
   NULL, // XC_RefPriSynGr_e,
   NULL, // XC_RefPriSyn,
   NULL, // XC_RefPriSyn_e,

   NULL, // XC_RefSynGr,
   NULL, // XC_RefSynGr_e,
   NULL, // XC_RefSyn,
   NULL, // XC_RefSyn_e,

   NULL, // XC_RefExamplGr,
   NULL, // XC_RefExamplGr_e,
   NULL, // XC_RefExampl,
   NULL, // XC_RefExampl_e,

   NULL, // XC_RefAntGr,
   NULL, // XC_RefAntGr_e,
   NULL, // XC_RefAnt,
   NULL, // XC_RefAnt_e,

   NULL, // XC_RefExamplSinglGr
   NULL, // XC_RefExamplSinglGr_e

   NULL, // XC_Subscript,
   NULL, // XC_Subscript_e,

   NULL, // XC_CodeExampleInline
   NULL, // XC_CodeExampleInline_e

   NULL, // XC_EnumGr,
   NULL, // XC_EnumGr_e,

   NULL, // XC_Enum,
   NULL, // XC_Enum_e,

   NULL, // XC_CodeBaseWord,
   NULL, // XC_CodeBaseWord_e,

   NULL, // XC_CodeExample,
   NULL, // XC_CodeExample_e,

   NULL, // XC_Table,
   NULL, // XC_Table_e,
   NULL, // XC_TableRow,
   NULL, // XC_TableRow_e,
   NULL, // XC_TableCell,
   NULL, // XC_TableCell_e,

   NULL, // XC_Equiation,
   NULL, // XC_Equiation_e,

   NULL, // XC_Break,
   NULL, // XC_Break_e,

   NULL, // XC_EquInline,
   NULL, // XC_EquInline_e,

   NULL, // XC_Special,
   NULL, // XC_Special_e,

   NULL, // "node_eg.bmp", // XC_ExampleGroupForced
   NULL, // XC_ExampleGroupForced_e

   NULL, // XC_ExplForced,
   NULL, // XC_ExplForced_e,

   NULL, // XC_VarGroup,
   NULL, // XC_VarGroup_e,

   NULL, // XC_Relatives,
   NULL, // XC_Relatives_e,

   NULL, // XC_Page,
   NULL, // XC_Page_e,

   NULL, // XC_SemNr,
   NULL, // XC_SemNr_e,

   NULL, // XC_TrWordLit,
   NULL, // XC_TrWordLit_e,

   NULL, // XC_TrWordEng,
   NULL, // XC_TrWordEng_e,

   NULL, // XC_TrWordGer,
   NULL, // XC_TrWordGer_e,

   NULL, // XC_TrWordFre,
   NULL, // XC_TrWordFre_e,

   NULL, // XC_TrWordPol,
   NULL, // XC_TrWordPol_e,

   NULL, // XC_TrWordRus,
   NULL, // XC_TrWordRus_e,

   NULL, // XC_Species
   NULL, // XC_Species_e,

   NULL, // "node_eg.bmp", // XC_StructGroupForced,
   NULL, // XC_StructGroupForced_e,

   NULL, // XC_VarBold
   NULL, // XC_VarBold_e

   NULL, // XC_RefAntStrictGr
   NULL, // XC_RefAntStrictGr_e
   NULL, // XC_RefAntStrict
   NULL, // XC_RefAntStrict_e
};


// ------------------------------------
/* const */ RT_FontDescriptor iaRtfFonts[KPT_NumOfTypefaces9+1] =
{
   RT_FontDescriptor_tag(False, False, "Times New Roman",    0,              KPT_NoCodeTable, RT_TG_FRoman), // KPT_Times_New_Roman,     // 0
   RT_FontDescriptor_tag(False, True,  "Palemonas",          186,            71,              RT_TG_FRoman), // KPT_TimesLT,             // 1
   RT_FontDescriptor_tag(False, True,  "Palemonas",          0,              74/*80*/,        RT_TG_FRoman), // KPT_TimesLT_Accented,    // 2

   RT_FontDescriptor_tag(False, True,  "Palemonas",          0,              74/*82*/,        RT_TG_FNil),   // KPT_PhoneticTMUniv,      // 3

   RT_FontDescriptor_tag(False, False, "",                   0,              KPT_NoCodeTable, RT_TG_FSwiss), // KPT_HelveticaLT,         // 4
   RT_FontDescriptor_tag(False, True,  "Symbol",             2,              85,              RT_TG_FRoman), // KPT_Symbol,              // 5
   RT_FontDescriptor_tag(False, False, "",                   0,              KPT_NoCodeTable, RT_TG_FRoman), // KPT_Wingdings2,          // 6
   RT_FontDescriptor_tag(False, False, "",                   0,              KPT_NoCodeTable, RT_TG_FRoman), // KPT_Haettenschweiler,    // 7
   RT_FontDescriptor_tag(False, True,  "Arial",              186 /* 0 */,    71 /* 1 */,      RT_TG_FSwiss), // KPT_Arial,               // 8

   RT_FontDescriptor_tag(False, False, "",                   0,              KPT_NoCodeTable, RT_TG_FModern),// KPT_Courier,             // 9

   RT_FontDescriptor_tag(True,  False, "",                   RT_NoCodeTable, KPT_NoCodeTable, RT_TG_FNil)
};


// ------------------------------------
KPS_FontStyle aFontStyles[KPS_NumOfFontStyles16] =
{
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_FlagsUndef,KpColorUndefined, KpColorUndefined),  // KPS_Undefined,              //  0    \FSA
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpBlack,          KpColorUndefined),  // KPS_TimesLT,                //  1    \FSB
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpBlack,          KpColorUndefined),  // KPS_TimesLTAcc,             //  2    \FSC
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Underl,    KpRed,            KpColorUndefined),  // KPS_TimesLTAccUndRed,       //  3    \FSD
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Italic,    KpRed,            KpColorUndefined),  // KPS_TimesLTAccItRed,        //  4    \FSE
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBlue,           KpColorUndefined),  // KPS_TimesLTAccBoldEnlBlue,  //  5    \FSF
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpDarkgreen,      KpColorUndefined),  // KPS_TimesLTAccBoldGreen,    //  6    \FSG
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpRed,            KpColorUndefined),  // KPS_TimesLTAccRed,          //  7    \FSH
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpRed,            KpColorUndefined),  // KPS_TimesLTAccBoldRed,      //  8    \FSI
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBrown,          KpColorUndefined),  // KPS_TimesLTAccBoldEnlBrown, //  9    \FSJ
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpBrown,          KpColorUndefined),  // KPS_TimesLTAccBrown,        // 10    \FSK
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpOchre,          KpColorUndefined),  // KPS_TimesLTAccBoldOchre,    // 11    \FSL
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Italic,    KpBlack,          KpColorUndefined),  // KPS_TimesLTAccIt,           // 12    \FSM
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBlack,          KpColorUndefined),  // KPS_TimesLTAccBold,         // 13    \FSN
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_BoldItal,  KpBlack,          KpColorUndefined),  // KPS_TimesLTAccBoldIt,       // 14    \FSO
   KPS_FontStyle_tag(KPT_PhoneticTMUniv,    iMainFontSize*9/8,       KPS_Straight,  KpMagenta,        KpColorUndefined),  // KPS_PhonMagenta,            // 15    \FSP
   KPS_FontStyle_tag(KPT_PhoneticTMUniv,    iMainFontSize*5/8,       KPS_Straight,  KpMagenta,        KpColorUndefined),  // KPS_PhonMagentaReduc,       // 16    \FSQ
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize,           KPS_Super,     KpBlack,          KpColorUndefined),  // KPS_TimesLTAccSup,          // 17    \FSR
   KPS_FontStyle_tag(KPT_Symbol,            iMainFontSize,           KPS_Straight,  KpBlack,          KpColorUndefined),  // KPS_Symbol,                 // 18    \FSS
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Underl,    KpBlack,          KpColorUndefined),  // KPS_TimesLTAccUnd,          // 19    \FST
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpGray,           KpColorUndefined),  // KPS_TimesLTGray,            // 20    \FSU
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpGray,           KpColorUndefined),  // KPS_TimesLTBoldGray,        // 21    \FSV
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Italic,    KpGray,           KpColorUndefined),  // KPS_TimesLTItGray,          // 22    \FSW
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_ItalicFl,  KpColorUndefined, KpColorUndefined),  // KPS_Italic,                 // 23    \FSX
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_BoldFl,    KpColorUndefined, KpColorUndefined),  // KPS_Bold,                   // 24    \FSY
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_UnderlFl,  KpColorUndefined, KpColorUndefined),  // KPS_Underline,              // 25    \FSZ
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_SuperFl,   KpColorUndefined, KpColorUndefined),  // KPS_SuperScript,            // 26    \FSa
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_SubFl,     KpColorUndefined, KpColorUndefined),  // KPS_SubScript,              // 27    \FSb
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_SmCapsFl,  KpColorUndefined, KpColorUndefined),  // !!! KPS_SmallCaps,          // 28    \FSc
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_CapsFl,    KpColorUndefined, KpColorUndefined),  // !!! KPS_Caps,               // 29    \FSd
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize,           KPS_SmCaps,    KpRed,            KpColorUndefined),  // KPS_TimesLTAccSmcapsRed,    // 30    \FSe
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpBlue,           KpColorUndefined),  // KPS_TimesLTBlue,            // 31    \FSf
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBlue,           KpColorUndefined),  // KPS_TimesLTAccBoldBlue,     // 32    \FSg
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize,           KPS_Super,     KpBlue,           KpColorUndefined),  // KPS_TimesLTAccSupBlue,      // 33    \FSh
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Straight,  KpDarkcyan,       KpColorUndefined),  // KPS_TimesLTCyan,            // 34    \FSi
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_SmCaps,    KpDarkcyan,       KpColorUndefined),  // KPS_ArialSmcapsCyan,        // 35    \FSj
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*5/8,       KPS_Bold,      KpDarkcyan,       KpColorUndefined),  // KPS_TimesLTAccBoldReducCyan,// 36    \FSk
   KPS_FontStyle_tag(KPT_Symbol,            iMainFontSize,           KPS_Straight,  KpDarkcyan,       KpColorUndefined),  // KPS_SymbolCyan,             // 37    \FSl
   KPS_FontStyle_tag(KPT_Symbol,            iMainFontSize*5/8,       KPS_Straight,  KpDarkcyan,       KpColorUndefined),  // KPS_Wingdings2Cyan,         // 38    \FSm
   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBlack,          KpColorUndefined),  // KPS_TimesLTAccBoldEnl,      // 39    \FSn

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize/* *9/8 */, KPS_Bold,      KpGray,           KpColorUndefined),  // KPS_TimesLTAccBoldEnlGray,  // 40    \FSo
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_Straight,  KpRed,            KpColorUndefined),  // KPS_ArialRed,               // 41    \FSp
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_Bold,      KpDarkgreen,      KpColorUndefined),  // KPS_ArialBoldGreen,         // 42    \FSq
   KPS_FontStyle_tag(KPT_TypefaceUndefined, iMainFontSize,           KPS_Straight,  KpRed,            KpColorUndefined),  // KPS_HaettRed,               // 43    \FSr
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_Bold,      KpOchre,          KpColorUndefined),  // KPS_ArialBoldOchre          // 44    \FSs
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_Bold,      KpBrown,          KpColorUndefined),  // KPS_ArialBoldBrown,         // 45    \FSt
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*10/11,     KPS_Bold,      KpBlack,          KpColorUndefined),  // KPS_ArialBold,              // 46    \FSu
   KPS_FontStyle_tag(KPT_Arial,             iMainFontSize*6/8,       KPS_Straight,  KpBlack,          KpColorUndefined),  // KPS_ArialReduc,             // 47    \FSv

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpBrown,          KpColorUndefined),  // KPS_TimesLTAccBoldBrown     // 48    \FSw

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize /* *9/8 */,KPS_Bold,      KpOchre,          KpColorUndefined),  // KPS_TimesLTAccBoldEnlOchre, // 49    \FSx

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8 /* *8/7 */,KPS_Bold,  KpBlack,          KpColorUndefined),  // KPS_TimesLTAccBoldVeryEnl,  // 50    \FSy

   KPS_FontStyle_tag(KPT_Times_New_Roman,   iMainFontSize,           KPS_Straight,  KpBlue,           KpColorUndefined),  // KPS_TimesBlue,              // 51    \FSz
   KPS_FontStyle_tag(KPT_Times_New_Roman,   iMainFontSize,           KPS_Straight,  KpGray,           KpColorUndefined),  // KPS_TimesGray,              // 52    \FS?
   KPS_FontStyle_tag(KPT_Times_New_Roman,   iMainFontSize,           KPS_Straight,  KpDarkcyan,       KpColorUndefined),  // KPS_TimesCyan,              // 53    \FS?

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize/* *9/8 */, KPS_Bold,      KpRed,            KpColorUndefined),  // KPS_TimesLTAccBoldEnlRed,   // 40    \FS?

   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_FlagsUndef,KpBlack /* KpColorUndefined */, KpLightyellow), // KPS_CommonBackYellow, // 55

   KPS_FontStyle_tag(KPT_TimesLT_Accented,  iMainFontSize*9/8,       KPS_Italic,    KpBlue,           KpColorUndefined),  // KPS_TimesLTAccItalicBlue,   // 56
   KPS_FontStyle_tag(KPT_Courier,           iMainFontSize,           KPS_Straight,  KpBlack,          KpColorUndefined),  // KPS_CourierBlack,           // 57

   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_FlagsUndef,KpWhite,          KpDarkBlue/*KpGrayBlue*/),        // KPS_WhiteBackDarkBlue,          // 58
   KPS_FontStyle_tag(KPT_TypefaceUndefined, KPS_FontSizeUndef,       KPS_FlagsUndef,KpWhite,          KpBrown),           // KPS_WhiteBackBrown,         // 59
};


// ------------------------------------
const KPS_FontStyles iaTagFonts[XC_TG_NumOfDictTagsArr68] = // SGML Tage file styles, import from tvxmlt.css !!!
{

  KPS_TimesLT,              //  1 // XC_Dict
     KPS_FontStyleUndefined,//  0 // XC_Dict_e
  KPS_TimesLT,              //  1 // XC_NrtEntry
     KPS_FontStyleUndefined,//  0 // XC_NrtEntry_e
  KPS_TimesLT,              //  1 // XC_StEntry
     KPS_FontStyleUndefined,//  0 // XC_StEntry_e
  KPS_TimesLTAccBoldVeryEnl,// 50 // KPS_TimesLTAccBoldEnl,    // 39 // XC_HeadWord
     KPS_FontStyleUndefined,//  0 // XC_HeadWord_e
  KPS_ArialSmcapsCyan,      // 35 // KPS_TimesLTAccSmcapsRed,  // 30 // KPS_TimesLTAccUndRed, //  3 // KPS_TimesLTAccItRed // 4 // XC_Label
     KPS_FontStyleUndefined,//  0 // XC_Label_e
  KPS_TimesLTAcc,           //  2 // XC_TrWord
     KPS_FontStyleUndefined,//  0 // XC_TrWord_e
  KPS_ArialReduc,           // 47 // KPS_TimesLT,              //  1 // XC_UsNoteDst  !!!---
     KPS_FontStyleUndefined,//  0 // XC_UsNoteDst_e
  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_Reference
     KPS_FontStyleUndefined,//  0 // XC_Reference_e
  KPS_TimesLT,              //  1 // XC_StEntryText
     KPS_FontStyleUndefined,//  0 // XC_StEntryText_e

  KPS_FontStyleUndefined,   //  0 // XC_Paragraph
     KPS_FontStyleUndefined,//  0 // XC_Paragraph_e

     KPS_FontStyleUndefined,//  0 // XC_Version
     KPS_FontStyleUndefined,//  0 // XC_Version_e
     KPS_FontStyleUndefined,//  0 // XC_DocType
     KPS_FontStyleUndefined,//  0 // XC_DocType_e

  KPS_TimesLTAccBoldVeryEnl,// 50 // KPS_TimesLTAccBoldEnlBrown,// 9 // XC_Variant
     KPS_FontStyleUndefined,//  0 // XC_Variant_e
  KPS_TimesLTAccIt,         // 12 // XC_PartOfSpeechSrc
     KPS_FontStyleUndefined,//  0 // XC_PartOfSpeechSrc_e

  KPS_TimesLT,              //  1 // XC_HeadWordGroup
     KPS_FontStyleUndefined,//  0 // XC_HeadWordGroup_e
  KPS_TimesLT,              //  1 // XC_TranslGroup
     KPS_FontStyleUndefined,//  0 // XC_TranslGroup_e

  KPS_TimesLTAccBoldEnlRed, // 40 // XC_FormDst
     KPS_FontStyleUndefined,//  0 // XC_FormDst_e
  KPS_TimesLTAccBoldEnlRed, // 40 // XC_FormSrc  // SemiBold flag !!!
     KPS_FontStyleUndefined,//  0 // XC_FormSrc_e

  KPS_TimesLTAccIt,         // 12 // KPS_TimesLTAccItRed,      // 4 // KPS_ArialRed,             // 41 // KPS_HaettRed,             // 43 // // KPS_TimesLTAccRed   //  7 // XC_ExplSrc
     KPS_FontStyleUndefined,//  0 // XC_ExplSrc_e

  KPS_TimesLTAccBoldGreen,       // 6 // KPS_ArialBoldGreen,  //  42 // XC_Example
     KPS_FontStyleUndefined,//  0 // XC_Example_e
  KPS_TimesLT,              //  1 // XC_ExampleGroup
     KPS_FontStyleUndefined,//  0 // XC_ExampleGroup_e

  KPS_FontStyleUndefined,   //  0 // XC_Parenth
     KPS_FontStyleUndefined,//  0 // XC_Parenth_e

  KPS_TimesLTAccBoldGreen,       // 6 // KPS_ArialBoldGreen,       // 42 // KPS_TimesLTAccBoldEnlOchre, // 49 // KPS_ArialBoldOchre,     // 44 // XC_Idiom !!!---
     KPS_FontStyleUndefined,//  0 // XC_Idiom_e

  KPS_TimesLT,              //  1 // XC_IdiomGroup
     KPS_FontStyleUndefined,//  0 // XC_IdiomGroup_e

  KPS_TimesLT,              //  1 // XC_CtgGroup
     KPS_FontStyleUndefined,//  0 // XC_CtgGroup_e

  KPS_TimesLTAccBoldEnl,    // 39 // KPS_TimesLTAccBoldIt,  // 14  // XC_Base
     KPS_FontStyleUndefined,//  0 // XC_Base_e
  KPS_TimesLT,              //  1 // XC_CompoundGroup
     KPS_FontStyleUndefined,//  0 // XC_CompoundGroup_e
  KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccBoldEnlBrown,  // 9 // KPS_ArialBoldBrown,       // 45 // XC_CompoundWord
     KPS_FontStyleUndefined,//  0 // XC_CompoundWord_e

  KPS_TimesLT,              //  1 // XC_MngGroup
     KPS_FontStyleUndefined,//  0 // XC_MngGroup_e

  KPS_TimesLTAccBoldEnl,    // 39 // XC_Asterix
     KPS_FontStyleUndefined,//  0 // XC_Asterix_e

  KPS_TimesLTAccIt,         // 12  // KPS_TimesLTAcc,           //  2 // KPS_ArialBold,            // 46 // KPS_TimesLTAccBold,       // 13 // XC_CtrlSrc
     KPS_FontStyleUndefined,//  0 // XC_CtrlSrc_e

  KPS_TimesLT,              //  1 // XC_PrGroup
     KPS_FontStyleUndefined,//  0 // XC_PrGroup_e
  KPS_PhonMagenta,          // 20 // XC_Pron
     KPS_FontStyleUndefined,//  0 // XC_Pron_e

  KPS_TimesLTItGray,        // 22 // XC_Abbr
     KPS_FontStyleUndefined,//  0 // XC_Abbr_e

  KPS_TimesLTAccSup,        // 17 // XC_Hom
     KPS_FontStyleUndefined,//  0 // XC_Hom_e

  KPS_TimesLTAccIt,         // 12 // KPS_TimesLTAccItRed,      //  4 // KPS_TimesLTAccRed,   //  7  // XC_ContextSrc // xmlt - for diference with XC_Label only !!!
     KPS_FontStyleUndefined,//  0 // XC_ContextSrc_e

  KPS_TimesLT,              //  1 // XC_CtrlGroup
     KPS_FontStyleUndefined,//  0 // XC_CtrlGroup_e

  KPS_TimesLTAccIt,         // 12 // XC_PartOfSpeechDst
     KPS_FontStyleUndefined,//  0 // XC_PartOfSpeechDst_e

  KPS_TimesLT,              //  1 // XC_FormGroupSrc,
     KPS_FontStyleUndefined,//  0 // XC_FormGroupSrc_e,

     KPS_FontStyleUndefined,//  0 // XC_StyleSheet,
     KPS_FontStyleUndefined,//  0 // XC_StyleSheet_e,

  KPS_TimesLTAccBrown,      // 10 // XC_VarNorm
     KPS_FontStyleUndefined,//  0 // XC_VarNorm_e

  KPS_TimesLTAcc,           //  2 // XC_AbbrNorm
     KPS_FontStyleUndefined,//  0 // XC_AbbrNorm_e

  KPS_TimesLT,              //  1 // XC_MngNearGroup
     KPS_FontStyleUndefined,//  0 // XC_MngNearGroup_e

  KPS_PhonMagentaReduc,     // 16 // XC_PronRed
     KPS_FontStyleUndefined,//  0 // XC_PronRed_e

     KPS_FontStyleUndefined,//  0 // XC_Nul
     KPS_FontStyleUndefined,//  0 // XC_Nul_e

  KPS_SymbolCyan,           // 37 // XC_Similar
     KPS_FontStyleUndefined,//  0 // XC_Similar_e

  KPS_SymbolCyan,           // 37 // XC_Approx
     KPS_FontStyleUndefined,//  0 // XC_Approx_e

  KPS_FontStyleUndefined,   //  0 // XC_Text
     KPS_FontStyleUndefined,//  0 // XC_Text_e

  KPS_TimesLT,              //  1 // XC_Info
     KPS_FontStyleUndefined,//  0 // XC_Info_e

  KPS_TimesLTAccBold,         // 13 // KPS_ArialBold,            // 46 // KPS_TimesLTAccBoldEnl,    // 39 // XC_Expand
     KPS_FontStyleUndefined,//  0 // XC_Expand_e

  KPS_TimesLT,              //  1 // XC_StructGroup
     KPS_FontStyleUndefined,//  0 // XC_StructGroup_e

  KPS_TimesLTAccIt,         // 12 // XC_Gloss
     KPS_FontStyleUndefined,//  0 // XC_Gloss_e

  KPS_ArialReduc,           // 47 // XC_FwNote
     KPS_FontStyleUndefined,//  0 // XC_FwNote_e

  KPS_CommonItalic,         // 23 // XC_Italic
     KPS_FontStyleUndefined,//  0 // XC_Italic_e

  KPS_TimesLTAccIt,         // 12 // XC_ModCpdSrc
     KPS_FontStyleUndefined,//  0 // XC_ModCpdSrc_e

  KPS_Symbol,               // 18 // XC_Symb
     KPS_FontStyleUndefined,//  0 // XC_Symb_e

  KPS_SymbolCyan,           // 37 // XC_Inform
     KPS_FontStyleUndefined,//  0 // XC_Inform_e
  KPS_SymbolCyan,           // 37 // XC_Uncount
     KPS_FontStyleUndefined,//  0 // XC_Uncount_e

  KPS_TimesLT,              //  1 // XC_PhrGroup
     KPS_FontStyleUndefined,//  0 // XC_PhrGroup_e

  KPS_TimesLT,              //  1 // XC_CpdMngGroup
     KPS_FontStyleUndefined,//  0 // XC_CpdMngGroup_e

  KPS_SymbolCyan,           // 37 // XC_Obs
     KPS_FontStyleUndefined,//  0 // XC_Obs_e
  KPS_SymbolCyan,           // 37 // XC_Arch
     KPS_FontStyleUndefined,//  0 // XC_Arch_e
  KPS_SymbolCyan,           // 37 // XC_VeryInform
     KPS_FontStyleUndefined,//  0 // XC_VeryInform_e
  KPS_SymbolCyan,           // 37 // XC_Vulgar
     KPS_FontStyleUndefined,//  0 // XC_Vulgar_e

  KPS_CommonSuperScript,    // 26 // XC_Super
     KPS_FontStyleUndefined,//  0 // XC_Super_e

  KPS_SymbolCyan,           // 37 // XC_Count
     KPS_FontStyleUndefined,//  0 // XC_Count_e

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
  KPS_WhiteBackBrown,         // 59
// #elif IBSH_SKIN == IBSH_SKIN_STANDART
#else
  KPS_WhiteBackDarkBlue,      // 58 // KPS_CommonBackYellow,     // 55 // KPS_CommonUnderline,      // 25 // XC_HiLight
// #else
// #error iaTagFonts[XC_HiLight]
#endif
     KPS_FontStyleUndefined,//  0 // XC_HiLight_e
  KPS_CommonBold,           // 24 // XC_SemiBold   // semibold flag !!!
     KPS_FontStyleUndefined,//  0 // XC_SemiBold_e

  KPS_TimesLTAccIt,   // 12 (xmlt !!!) // KPS_TimesLTAcc,           //  2 // XC_CtrlDst
     KPS_FontStyleUndefined,//  0 // XC_CtrlDst_e

  KPS_TimesLTAccRed,        //  7 // XC_ExplNorm
     KPS_FontStyleUndefined,//  0 // XC_ExplNorm_e

  KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccItOchre,    // ?? // KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccBoldEnlBrown,  // 9 // KPS_ArialBoldBrown,       // 45 // XC_Struct
    KPS_FontStyleUndefined,//  0 // XC_Struct_e
  KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccBoldEnlBrown,  // 9 // KPS_ArialBoldBrown,       // 45 // XC_OblStruct
     KPS_FontStyleUndefined,//  0 // XC_OblStruct_e

  KPS_TimesLTAccBoldGreen,  //  6 // KPS_ArialBoldGreen,       // 42 // XC_Usage
     KPS_FontStyleUndefined,//  0 // XC_Usage_e

  KPS_TimesLTAccBoldEnl,    // 39 // KPS_TimesLTAccBold,       // 13 // XC_HBase
     KPS_FontStyleUndefined,//  0 // XC_HBase_e

  KPS_TimesLT,              //  1 // XC_ModCpdGroup
     KPS_FontStyleUndefined,//  0 // XC_ModCpdGroup_e

  KPS_TimesLTAcc,           //  2 // XC_ExampleTransl
     KPS_FontStyleUndefined,//  0 // XC_ExampleTransl_e

  KPS_TimesLTAcc,           //  2 // XC_IdiomTransl
     KPS_FontStyleUndefined,//  0 // XC_IdiomTransl_e

  KPS_ArialReduc,           // 47 // // KPS_TimesLT,              //  1 // XC_TechNote
     KPS_FontStyleUndefined,//  0 // XC_TechNote_e

  KPS_TimesLT,              //  1 // XC_IdMngGroup
     KPS_FontStyleUndefined,//  0 // XC_IdMngGroup_e

  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_Refinf
     KPS_FontStyleUndefined,//  0 // XC_Refinf_e

  KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccBoldEnlBrown, // 9 // KPS_ArialBoldBrown,       // 45 // XC_SrcWord
     KPS_FontStyleUndefined,//  0 // XC_SrcWord_e

  KPS_TimesLTAcc,           //  2 // XC_ModCpdDst
     KPS_FontStyleUndefined,//  0 // XC_ModCpdDst_e

  KPS_TimesLTAccIt,         // 12 // XC_ContextDst
     KPS_FontStyleUndefined,//  0 // XC_ContextDst_e

  KPS_TimesLTAccIt,         // 12 // KPS_TimesLTAccRed,        //  7 // KPS_TimesLTAccItRed,      //  4 // XC_ExplDst
     KPS_FontStyleUndefined,//  0 // XC_ExplDst_e

  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_RefWord
     KPS_FontStyleUndefined,//  0 // XC_RefWord_e

  KPS_TimesLTAccBoldEnlBlue,// 32 // XC_RefNum
     KPS_FontStyleUndefined,//  0 // XC_RefNum_e

  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_RefXWord
     KPS_FontStyleUndefined,//  0 // XC_RefXWord_e

  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_RefTab
     KPS_FontStyleUndefined,//  0 // XC_RefTab_e

  KPS_TimesLTAccBoldEnlBlue,//  5 // XC_RefPage
     KPS_FontStyleUndefined,//  0 // XC_RefPage_e

  KPS_TimesLTAccSupBlue,    // 33 // XC_RefHom
     KPS_FontStyleUndefined,//  0 // XC_RefHom_e

  KPS_TimesLTAccBoldEnlOchre, // 49 //  KPS_TimesLTAccBoldEnlBrown,  // 9 // KPS_ArialBoldBrown,       // 45 // XC_SingleCpdWord
     KPS_FontStyleUndefined,//  0 // XC_SingleCpdWord_e

  KPS_TimesLT,              //  1 // XC_FormGroupDst
     KPS_FontStyleUndefined,//  0 // XC_FormGroupDst_e

  KPS_TimesLT,              //  1 // XC_DerivGroup
     KPS_FontStyleUndefined,//  0 // XC_DerivGroup_e

  KPS_TimesLTAccBoldEnlOchre,// 49 // XC_Derivative
    KPS_FontStyleUndefined,//  0 // XC_Derivative_e

  KPS_TimesLT,              //  1 // XC_StressParGroup
     KPS_FontStyleUndefined,//  0 // XC_StressParGroup_e

  KPS_TimesLT,              //  1 // XC_StressPar
     KPS_FontStyleUndefined,//  0 // XC_StressPar_e

  KPS_TimesLTGray,          // 20 // XC_PunctMark
     KPS_FontStyleUndefined,//  0 // XC_PunctMark_e

     KPS_FontStyleUndefined,//  0 // XC_LevelGroup
     KPS_FontStyleUndefined,//  0 // XC_LevelGroup_e

     KPS_FontStyleUndefined,//  0 // XC_Level
     KPS_FontStyleUndefined,//  0 // XC_Level_e

  KPS_ArialReduc,           // 47 // XC_UsNoteSrc
     KPS_FontStyleUndefined,//  0 // XC_UsNoteSrc_e

     KPS_FontStyleUndefined,//  0 // XC_Img
     KPS_FontStyleUndefined,//  0 // XC_Img_e

     KPS_FontStyleUndefined,//  0 // XC_RefSecSynGr
     KPS_FontStyleUndefined,//  0 // XC_RefSecSynGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefSecSyn
     KPS_FontStyleUndefined,//  0 // XC_RefSecSyn_e

     KPS_FontStyleUndefined,//  0 // XC_RefPriSynGr
     KPS_FontStyleUndefined,//  0 // XC_RefPriSynGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefPriSyn
     KPS_FontStyleUndefined,//  0 // XC_RefPriSyn_e

     KPS_FontStyleUndefined,//  0 // XC_RefSynGr
     KPS_FontStyleUndefined,//  0 // XC_RefSynGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefSyn
     KPS_FontStyleUndefined,//  0 // XC_RefSyn_e

     KPS_FontStyleUndefined,//  0 // XC_RefExamplGr
     KPS_FontStyleUndefined,//  0 // XC_RefExamplGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefExampl
     KPS_FontStyleUndefined,//  0 // XC_RefExampl_e

     KPS_FontStyleUndefined,//  0 // XC_RefAntGr
     KPS_FontStyleUndefined,//  0 // XC_RefAntGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefAnt
     KPS_FontStyleUndefined,//  0 // XC_RefAnt_e

     KPS_FontStyleUndefined,//  0 // XC_RefExamplSinglGr
     KPS_FontStyleUndefined,//  0 // XC_RefExamplSinglGr_e

  KPS_CommonSubScript,      // 27 // XC_Subscript
     KPS_FontStyleUndefined,//  0 // XC_Subscript_e

  KPS_CourierBlack,         // 57 // XC_CodeExampleInline
     KPS_FontStyleUndefined,//  0 // XC_CodeExampleInline_e

     KPS_FontStyleUndefined,//  0 // XC_EnumGr
     KPS_FontStyleUndefined,//  0 // XC_EnumGr_e

  KPS_TimesLT,              //  1 // XC_Enum
     KPS_FontStyleUndefined,//  0 // XC_Enum_e

  KPS_TimesLTAccBold,       // 13 // XC_CodeBaseWord
     KPS_FontStyleUndefined,//  0 // XC_CodeBaseWord_e, /*  5233 */

  KPS_CourierBlack,         // 57 // XC_CodeExample
     KPS_FontStyleUndefined,//  0 // XC_CodeExample_e

     KPS_FontStyleUndefined,//  0 // XC_Table
     KPS_FontStyleUndefined,//  0 // XC_Table_e
     KPS_FontStyleUndefined,//  0 // XC_TableRow
     KPS_FontStyleUndefined,//  0 // XC_TableRow_e
  KPS_FontStyleUndefined,   //  0 // XC_TableCell
     KPS_FontStyleUndefined,//  0 // XC_TableCell_e

  KPS_TimesLT,              //  1 // XC_Equiation
     KPS_FontStyleUndefined,//  0 // XC_Equiation_e

     KPS_FontStyleUndefined,//  0 // XC_Break
     KPS_FontStyleUndefined,//  0 // XC_Break_e

  KPS_TimesLT,              //  1 // XC_EquInline
     KPS_FontStyleUndefined,//  0 // XC_EquInline_e

     KPS_FontStyleUndefined,//  0 // XC_Special
     KPS_FontStyleUndefined,//  0 // XC_Special_e

  KPS_TimesLT,              //  1 // XC_ExampleGroupForced
     KPS_FontStyleUndefined,//  0 // XC_ExampleGroupForced_e

  KPS_TimesLTAccIt,         // 12 // KPS_TimesLTAccItRed,      // 4 // KPS_ArialRed,             // 41 // KPS_HaettRed,             // 43 // // KPS_TimesLTAccRed   //  7 // XC_ExplForced
     KPS_FontStyleUndefined,//  0 // XC_ExplForced_e

  KPS_TimesLT,              //  1 // XC_VarGroup
     KPS_FontStyleUndefined,//  0 // XC_VarGroup_e

  KPS_SymbolCyan,           // 37 // XC_Relatives
     KPS_FontStyleUndefined,//  0 // XC_Relatives_e

  KPS_TimesLT,              //  1 // XC_Page
     KPS_FontStyleUndefined,//  0 // XC_Page_e

  KPS_TimesLT,              //  1 // XC_SemNr
     KPS_FontStyleUndefined,//  0 // XC_SemNr_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordLit
     KPS_FontStyleUndefined,//  0 // XC_TrWordLit_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordEng
     KPS_FontStyleUndefined,//  0 // XC_TrWordEng_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordGer
     KPS_FontStyleUndefined,//  0 // XC_TrWordGer_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordFre
     KPS_FontStyleUndefined,//  0 // XC_TrWordFre_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordPol
     KPS_FontStyleUndefined,//  0 // XC_TrWordPol_e

  KPS_TimesLTAcc,           //  2 // XC_TrWordRus
     KPS_FontStyleUndefined,//  0 // XC_TrWordRus_e

  KPS_TimesLTAccBrown,      // 10 // XC_Species
     KPS_FontStyleUndefined,//  0 // XC_Species_e

  KPS_TimesLT,              //  1 // XC_StructGroupForced
     KPS_FontStyleUndefined,//  0 // XC_StructGroupForced_e

  KPS_TimesLTAccBoldEnlBrown,// 9 // XC_VarBold
     KPS_FontStyleUndefined,//  0 // XC_VarBold_e

     KPS_FontStyleUndefined,//  0 // XC_RefAntStrictGr
     KPS_FontStyleUndefined,//  0 // XC_RefAntStrictGr_e
  KPS_TimesLTAccItalicBlue, // 56 // XC_RefAntStrict
     KPS_FontStyleUndefined,//  0 // XC_RefAntStrict_e
};


// ------------------------------------ additional TvRtfO_tag methods
HRESULT TvRtfO::PutStyleSheet(void)
{
return(S_OK);
}


