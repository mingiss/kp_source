// ==================================================
// tvxml.cpp
// XML common things
//

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
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlg.h"


// ==================================================  static data
const unsigned char lpszXmlDelims[] = "(),;:/";
const unsigned char lpszXmlPunct[]=" .-"; // " .-()";

// ------------------------------
const KpChar TV_XL_URL_FILE_PREFIX_W[] = {'f', 'i', 'l', 'e', ':', '/', C_Nul};
#if KP_XGECKO_VER == 124 // "1.2.4"
const KpChar TV_XL_TUX_PATH_PREFIX_W[] = {C_t, C_u, C_x, C_Colon, C_Nul}; // "tux:"
#endif
#if KP_XGECKO_VER == 130 // "1.3.0"
const KpChar TV_XL_TUX_PATH_PREFIX_W[] = {C_t, C_u, C_x, C_Colon, C_Slash, C_Slash, C_Slash, C_Nul}; // "tux:///"
#endif

// ------------------------------
const KpChar TV_XL_TAG_SUFF_1[] = { C_Spc, '?', TV_XM_TagEndCh, C_Nul }; // " ?>"
const KpChar TV_XL_TAG_SUFF_2[] = { C_Spc, '-', '-', TV_XM_TagEndCh, C_Nul }; // " -->"
const KpChar TV_XL_TAG_SUFF_3[] = { TV_XM_EndTagIndCh, TV_XM_TagEndCh, C_Nul }; // "/>"
const KpChar TV_XL_TAG_SUFF_4[] = { ']', TV_XM_TagEndCh, C_Nul }; // "]>"

// --------------------------------------------------
const unsigned char *plpszaXmlSysTags[XL_NumOfSysTags5+1] = // General XML tag names (native)
{
                   XM_Version_STR,              // XL_Version
                // "<?xml ?>\n",
                // "<?xml version=\'1.0\' encoding=\"UTF-8\" ?>\n",
                // "<?XML VERSION=\"1.0\" RMD=\"ALL\" ?>\n",
                // "<?XML ENCODING=\"UTF-8\" ?>\n",
  (unsigned char *)"",                          // XL_Version_e

                   XM_DOCTYPE_STR,              // XL_DocType
                // "<!DOCTYPE di SYSTEM>\n",
                // "<!DOCTYPE di SYSTEM \"%s\">\n",
  (unsigned char *)"",                          // XL_DocType_e

                   XM_Stylesheet_STR,           // XL_StyleSheet
                // "<?xml-stylesheet ?>\n",
                // "<?xml-stylesheet href=\"%s\" type=\"text/css\" ?>\n",
  (unsigned char *)"",                          // XL_StyleSheet_e

                  XM_COMMENT_START_STR, // XM_COMMENT_STR, // XL_Comment
                  XM_COMMENT_END_STR, // (unsigned char *)"", // XL_Comment_e

  (unsigned char *)"<!--[if ]>",                // XL_IfComment
  (unsigned char *)"",                          // XL_IfComment_e

  (unsigned char *)"<![endif]-->",              // XL_EndIfComment
  (unsigned char *)"",                          // XL_EndIfComment_e

  (unsigned char *)"<![if ]>",                  // XL_If
  (unsigned char *)"",                          // XL_If_e

  (unsigned char *)"<![endif]>",                // XL_EndIf
  (unsigned char *)"",                          // XL_EndIf_e

  (unsigned char *)"<tx>", // "",               // XL_Text
  (unsigned char *)"</tx>", // "",              // XL_Text_e

  NULL
};


const int iaXmlSysCodeTables[XL_NumOfSysTags5] = // General XML tags fictive code tables for Unicode file
{
   1, // XL_Version
   0, // XL_Version_e

   1, // XL_DocType
   0, // XL_DocType_e

   1, // XL_StyleSheet
   0, // XL_StyleSheet_e

   1, // XL_Comment
   0, // XL_Comment_e

   1, // XL_IfComment
   0, // XL_IfComment_e

   1, // XL_EndIfComment
   0, // XL_EndIfComment_e

   1, // XL_If
   0, // XL_If_e

   1, // XL_EndIf
   0, // XL_EndIf_e

   KPT_UpCodeTable,  // XL_Text
   0,  // XL_Text_e

};


// -------------------------------------------------
const KpChar uiazSysGrTags[]=
{
  (KpChar)XL_Version,
  (KpChar)XL_Version_e,

  (KpChar)XL_DocType,
  (KpChar)XL_DocType_e,

  (KpChar)XL_StyleSheet,
  (KpChar)XL_StyleSheet_e,

  (KpChar)XL_StyleSheet,
  (KpChar)XL_StyleSheet_e,

  C_Nul
};


// -------------------------------------------------
const unsigned char *lpszaXmlCodingModes[UC_Num_Of_Modes+1] =
{
// "ISO-10646-ucs-2"
// "ISO-10646-ucs-4"

   (unsigned char *)"",         //  UC_No_Mode
   (unsigned char *)"",         //  UC_UTF_Binary
   (unsigned char *)"",         //  UC_UTF_PlainText
   (unsigned char *)"",         //  UC_Unicode
   (unsigned char *)"UTF-7",    //  UC_UTF_7
   (unsigned char *)"UTF-8",    //  UC_UTF_8
   (unsigned char *)"",         //  UC_Unicode16
   (unsigned char *)"UTF-16",   //  UC_UTF_16
   (unsigned char *)"UTF-16",   //  UC_UTF_16_Big_Endian
   NULL
};


// -------------------------------------------------
const unsigned char *lpszaXmlCtblNames[KPT_Ctnum+1] = // lpszaXmlCtblNamesIso[]
{
// N - supported by Netscape 6.0
// * - kp internal
// N  "ISO-8859-1"         Western
// N  "ISO-8859-2"         Central European
// N  "ISO-8859-3"         South European
// N  "ISO-8859-5"         Cyrillic
// N  "ISO-8859-6"         Arabic
// N  "ISO-8859-7"         Greek
// N  "ISO-8859-8"         Visual Hebrew
// N  "ISO-8859-8-I"       Hebrew
// N  "ISO-8859-9"         Turkish
// N  "ISO-8859-10"        Nordic
// N  "ISO-8859-13"        Baltic      // almost the same, like "Windows-1257"
// N  "ISO-8859-14"        Celtic
// N  "ISO-8859-15"        Western
// N  "ISO-2022-JP"        Japanese
// N  "Windows-1252"       Western
// N  "Windows-1254"       Turkish
// N  "Windows-1255"       Hebrew
// N  "Windows-1256"       Arabic
// N  "Windows-1258"       Vietnamese
// N  "IBM-857"            Turkish
// N  "IBM-862"            Hebrew
// N  "IBM-864"            Arabic
// N  "MacRoman"           Western
// N  "MacCE"              Central European
// N  "MacGreek"           Greek
// N  "MacCyrillic"        Cyrillic
// N  "MacUkrainian"       Cyrillic/Ukrainian
// N  "MacIcelandic"       Icelandic
// N  "MacCroatian"        Croatian
// N  "MacRomanian"        Romanian
// N  "MacTurkish"         Turkish
// N  "MacHebrew"          Hebrew
// N  "MacArabic"          Arabic
// N  "MacFarsi"           Farsi
// N  "MacDevanagari"      Hindi
// N  "MacGujarati"        Gujarati
// N  "MacGurmukhi"        Gurmukhi
// N  "KOI8-U"             Cyrillic/Ukrainian
// N  "CP-866"             Cyrillic/Russian
// N  "ARMSCII-8"          Armenian
// N  "Shift_JIS"          Japanese
// N  "EUC-JP"             Japanese
// N  "EUC-KR"             Korean
// N  "EUC-TW"             Chinese Traditional
// N  "Big5"               Chinese Traditional
// N  "Big5-HKSCS"         Chinese Traditional
// N  "GB2312"             Chinese Simplified
// N  "GBK"                Chinese Simplified
// N  "GB18030"            Chinese Simplified
// N  "HZ"                 Chinese Simplified
// N  "TIS-620"            Thai
// N  "TCVN"               Vietnamese
// N  "VISCII"             Vietnamese
// N  "VPS"                Vietnamese

  (unsigned char *)"",                     //  0
  (unsigned char *)"ISO-646",              //  1  *  (ASCII)
  (unsigned char *)"KOI-7",                //  2  *  Cyrillic (KOI-7-1)
  (unsigned char *)"ISO-5426",             //  3  *  Extended Latin
  (unsigned char *)"ISO-5427",             //  4  *  Extended Cyrillic
  (unsigned char *)"ISO-5428",             //  5  *  Greek
  (unsigned char *)"ISO-6438",             //  6  *  African
  (unsigned char *)"",                     //  7
  (unsigned char *)"",                     //  8
  (unsigned char *)"",                     //  9
  (unsigned char *)"",                     // 10
  (unsigned char *)"",                     // 11
  (unsigned char *)"",                     // 12
  (unsigned char *)"",                     // 13
  (unsigned char *)"",                     // 14
  (unsigned char *)"",                     // 15
  (unsigned char *)"",                     // 16
  (unsigned char *)"",                     // 17
  (unsigned char *)"",                     // 18
  (unsigned char *)"",                     // 19
  (unsigned char *)"",                     // 20
  (unsigned char *)"",                     // 21
  (unsigned char *)"",                     // 22
  (unsigned char *)"",                     // 23
  (unsigned char *)"",                     // 24
  (unsigned char *)"",                     // 25
  (unsigned char *)"",                     // 26
  (unsigned char *)"",                     // 27
  (unsigned char *)"",                     // 28
  (unsigned char *)"",                     // 29
  (unsigned char *)"",                     // 30
  (unsigned char *)"",                     // 31  *  Multilingual (Latin I)
  (unsigned char *)"",                     // 32  N  Central European  (Slavic, Latin II)
  (unsigned char *)"",                     // 33  N  Western  (Multilingual, Latin I+)
  (unsigned char *)"",                     // 34  *  Canadian-French
  (unsigned char *)"",                     // 35
  (unsigned char *)"",                     // 36
  (unsigned char *)"",                     // 37
  (unsigned char *)"",                     // 38
  (unsigned char *)"",                     // 39
  (unsigned char *)"",                     // 40
  (unsigned char *)"",                     // 41  *  Lithuanian + IBM-437
  (unsigned char *)"",                     // 42  *  Lithuanian + Cyrillic IBM-855
  (unsigned char *)"",                     // 43  *  Lithuanian Kbl + Cyrillic IBM-855
  (unsigned char *)"",                     // 44  *  Baltic  (RST 1095-89)
  (unsigned char *)"ISO-8859-4",           // 45  N  Baltic
  (unsigned char *)"",                     // 46  ?  DOS Lithuanian, IBM-Kbl, based on IBM-437, without Cyrillic
  (unsigned char *)"",                     // 47  *  DOS Cyrillic only, without Latin
  (unsigned char *)"",                     // 48  N  DOS Cyrillic
  (unsigned char *)"",                     // 49  *  IBM-Kbl with polish TEV
  (unsigned char *)"",                     // 50
  (unsigned char *)"KOI8-R",               // 51  N  Cyrillic
  (unsigned char *)"ISO-IR-111",           // 52  N  Cyrillic  (ISO-K) ???
  (unsigned char *)"",                     // 53
  (unsigned char *)"",                     // 54
  (unsigned char *)"",                     // 55
  (unsigned char *)"",                     // 56
  (unsigned char *)"",                     // 57
  (unsigned char *)"",                     // 58
  (unsigned char *)"",                     // 59
  (unsigned char *)"",                     // 60
  (unsigned char *)"DKOI",                 // 61
  (unsigned char *)"",                     // 62
  (unsigned char *)"",                     // 63
  (unsigned char *)"",                     // 64
  (unsigned char *)"",                     // 65
  (unsigned char *)"",                     // 66
  (unsigned char *)"",                     // 67
  (unsigned char *)"",                     // 68
  (unsigned char *)"",                     // 69
  (unsigned char *)"",                     // 70
  (unsigned char *)"ISO-8859-13",          // 71  N  Baltic RIM, LST 1282-93, ISO 8859-13; almost the same, like "ISO-8859-13"
  (unsigned char *)"",                     // 72  *  Windows SC
  (unsigned char *)"",                     // 73  N  Windows Cyrillic
  (unsigned char *)"ISO-8859-1",           // 74  ?  Windows-1252, ANSI, ECMA Latin 1, ISO-Latin-1
  (unsigned char *)"",                     // 75  *  Windows Symbol Font for TEX formula fields
  (unsigned char *)"",                     // 76  *  Baltic-RIM, some RTF accented characters added
  (unsigned char *)"",                     // 77  *  Cyrillic without latin, with spec. chars (for TEX tags)
  (unsigned char *)"",                     // 78  N  Greek
  (unsigned char *)"",                     // 79  N  CE, ANSI-2, Central European
  (unsigned char *)"",                     // 80  *  Windows lithuanian accented charset "TimesLT Accented"
  (unsigned char *)"",                     // 81  *  Windows Phonetic basic charset "PhoneticTM"
  (unsigned char *)"",                     // 82  *  Windows Phonetic full (Universal) charset "PhoneticTMUniv"
  (unsigned char *)"",                     // 83  *  Windows Symbol Font
  (unsigned char *)"",                     // 84  *  Windows Verdana Font 8-bit encoding
  (unsigned char *)"",                     // 85  *  Windows Symbol Font with ASCII lowerpart for RTF output
  (unsigned char *)"",                     // 86
  (unsigned char *)"",                     // 87
  (unsigned char *)"",                     // 88
  (unsigned char *)"",                     // 89
  (unsigned char *)"",                     // 90
  (unsigned char *)"",                     // 91  *  Norsk Data lithuanian
  (unsigned char *)"",                     // 92  *  Lithuanian ASCII based standart
  (unsigned char *)"",                     // 93  *  Norsk Data polish
  (unsigned char *)"",                     // 94
  (unsigned char *)"",                     // 95
  (unsigned char *)"",                     // 96
  (unsigned char *)"",                     // 97
  (unsigned char *)"",                     // 98
  (unsigned char *)"",                     // 99  *  Transparent code table for i/o of 8-bit codes without decoding

  NULL
};


// -------------------------------------------------
const unsigned char *lpszaXmlCtblNamesWin[KPT_Ctnum+1] =
{
  (unsigned char *)"",                     //  0
  (unsigned char *)"",                     //  1  *  (ASCII)
  (unsigned char *)"",                     //  2  *  Cyrillic (KOI-7-1)
  (unsigned char *)"",                     //  3  *  Extended Latin
  (unsigned char *)"",                     //  4  *  Extended Cyrillic
  (unsigned char *)"",                     //  5  *  Greek
  (unsigned char *)"",                     //  6  *  African
  (unsigned char *)"",                     //  7
  (unsigned char *)"",                     //  8
  (unsigned char *)"",                     //  9
  (unsigned char *)"",                     // 10
  (unsigned char *)"",                     // 11
  (unsigned char *)"",                     // 12
  (unsigned char *)"",                     // 13
  (unsigned char *)"",                     // 14
  (unsigned char *)"",                     // 15
  (unsigned char *)"",                     // 16
  (unsigned char *)"",                     // 17
  (unsigned char *)"",                     // 18
  (unsigned char *)"",                     // 19
  (unsigned char *)"",                     // 20
  (unsigned char *)"",                     // 21
  (unsigned char *)"",                     // 22
  (unsigned char *)"",                     // 23
  (unsigned char *)"",                     // 24
  (unsigned char *)"",                     // 25
  (unsigned char *)"",                     // 26
  (unsigned char *)"",                     // 27
  (unsigned char *)"",                     // 28
  (unsigned char *)"",                     // 29
  (unsigned char *)"",                     // 30
  (unsigned char *)"IBM-437",              // 31  *  Multilingual (Latin I)
  (unsigned char *)"IBM-852",              // 32  N  Central European  (Slavic, Latin II)
  (unsigned char *)"IBM-850",              // 33  N  Western  (Multilingual, Latin I+)
  (unsigned char *)"IBM-863",              // 34  *  Canadian-French
  (unsigned char *)"",                     // 35
  (unsigned char *)"",                     // 36
  (unsigned char *)"",                     // 37
  (unsigned char *)"",                     // 38
  (unsigned char *)"",                     // 39
  (unsigned char *)"",                     // 40
  (unsigned char *)"IBM-774",              // 41  *  Lithuanian + IBM-437
  (unsigned char *)"IBM-772",              // 42  *  Lithuanian + Cyrillic IBM-855
  (unsigned char *)"IBM-773",              // 43  *  Lithuanian Kbl + Cyrillic IBM-855
  (unsigned char *)"IBM-770",              // 44  *  Baltic  (RST 1095-89)
  (unsigned char *)"",                     // 45  N  Baltic
  (unsigned char *)"IBM-771",              // 46  ?  DOS Lithuanian, IBM-Kbl, based on IBM-437, without Cyrillic
  (unsigned char *)"IBM-855",              // 47  *  DOS Cyrillic only, without Latin
  (unsigned char *)"IBM-855",              // 48  N  DOS Cyrillic
  (unsigned char *)"IBM-773",              // 49  *  IBM-Kbl with polish TEV
  (unsigned char *)"",                     // 50
  (unsigned char *)"",                     // 51  N  Cyrillic
  (unsigned char *)"",                     // 52  N  Cyrillic  (ISO-K) ???
  (unsigned char *)"",                     // 53
  (unsigned char *)"",                     // 54
  (unsigned char *)"",                     // 55
  (unsigned char *)"",                     // 56
  (unsigned char *)"",                     // 57
  (unsigned char *)"",                     // 58
  (unsigned char *)"",                     // 59
  (unsigned char *)"",                     // 60
  (unsigned char *)"EBCDIC",               // 61
  (unsigned char *)"",                     // 62
  (unsigned char *)"",                     // 63
  (unsigned char *)"",                     // 64
  (unsigned char *)"",                     // 65
  (unsigned char *)"",                     // 66
  (unsigned char *)"",                     // 67
  (unsigned char *)"",                     // 68
  (unsigned char *)"",                     // 69
  (unsigned char *)"",                     // 70
  (unsigned char *)"Windows-1257",         // 71  N  Baltic RIM, LST 1282-93, ISO 8859-13; almost the same, like "ISO-8859-13"
  (unsigned char *)"",                     // 72  *  Windows SC
  (unsigned char *)"Windows-1251",         // 73  N  Windows Cyrillic
  (unsigned char *)"Windows-1252",         // 74  ?  Windows-1252, ANSI, ECMA Latin 1, ISO-Latin-1
  (unsigned char *)"",                     // 75  *  Windows Symbol Font for TEX formula fields
  (unsigned char *)"Windows-1257",         // 76  *  Baltic-RIM, some RTF accented characters added
  (unsigned char *)"Windows-1251",         // 77  *  Cyrillic without latin, with spec. chars (for TEX tags)
  (unsigned char *)"Windows-1253",         // 78  N  Greek
  (unsigned char *)"Windows-1250",         // 79  N  CE, ANSI-2, Central European
  (unsigned char *)"",                     // 80  *  Windows lithuanian accented charset "TimesLT Accented"
  (unsigned char *)"",                     // 81  *  Windows Phonetic basic charset "PhoneticTM"
  (unsigned char *)"",                     // 82  *  Windows Phonetic full (Universal) charset "PhoneticTMUniv"
  (unsigned char *)"",                     // 83  *  Windows Symbol Font
  (unsigned char *)"",                     // 84  *  Windows Verdana Font 8-bit encoding
  (unsigned char *)"",                     // 85  *  Windows Symbol Font with ASCII lowerpart for RTF output
  (unsigned char *)"",                     // 86
  (unsigned char *)"",                     // 87
  (unsigned char *)"",                     // 88
  (unsigned char *)"",                     // 89
  (unsigned char *)"",                     // 90
  (unsigned char *)"",                     // 91  *  Norsk Data lithuanian
  (unsigned char *)"",                     // 92  *  Lithuanian ASCII based standart
  (unsigned char *)"",                     // 93  *  Norsk Data polish
  (unsigned char *)"",                     // 94
  (unsigned char *)"",                     // 95
  (unsigned char *)"",                     // 96
  (unsigned char *)"",                     // 97
  (unsigned char *)"",                     // 98
  (unsigned char *)"",                     // 99  *  Transparent code table for i/o of 8-bit codes without decoding

  NULL
};


// --------------------------------- static fields for HTML versions
const unsigned char *plpszaHtmlVersionIds[XM_MaxVers_5+1] =
{
   (const unsigned char *)"",                                           // XM_NO_VERS,
   (const unsigned char *)"",                                           // XM_NO_SGML,
   (const unsigned char *)"",                                           // XM_NO_SGML_TAGE,
   (const unsigned char *)"",                                           // XM_NO_HTML,
   (const unsigned char *)"-//W3C//DTD HTML 4.0 Transitional//EN",      // XM_VERS_HTML40,         // HTML v4.0
   (const unsigned char *)"-//W3C//DTD HTML 4.01 Transitional//EN",     // XM_VERS_HTML401_TRANS,  // HTML v4.01 Transitional
   (const unsigned char *)"-//W3C//DTD HTML 4.01//EN",                  // XM_VERS_HTML401,        // HTML v4.01
   (const unsigned char *)"-//W3C//DTD HTML 4.01 Frameset//EN",         // XM_VERS_HTML401_FRAME,  // HTML v4.01 with Frameset
   (const unsigned char *)"-//W3C//DTD HTML 4.01 Transitional//EN",     // XM_VERS_HTML_TAGE
   (const unsigned char *)"-//W3C//DTD XHTML 1.0 Strict//EN",           // XM_VERS_XHTML,          // XHTML // "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN"
   (const unsigned char *)"-//W3C//DTD XHTML 1.0 Strict//EN",           // XM_VERS_XHTML_TAGE      // "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN"
   (const unsigned char *)"",                                           // XM_VERS_XML,            // for distinguishing between HTML and XML only
   (const unsigned char *)"",                                           // XM_VERS_XML10,          // XML v1.0
   (const unsigned char *)"",                                           // XM_VERS_SVG

   NULL
};

const unsigned char *plpszaHtmlDtds[XM_MaxVers_5+1] =
{
   (const unsigned char *)"",                                                             // XM_NO_VERS,
   (const unsigned char *)"",                                                             // XM_NO_SGML,
   (const unsigned char *)"",                                                             // XM_NO_SGML_TAGE,
   (const unsigned char *)"",                                                             // XM_NO_HTML,
   (const unsigned char *)"http://www.w3.org/TR/REC-html40/loose.dtd",                    // XM_VERS_HTML40,         // HTML v4.0
   (const unsigned char *)"http://www.w3.org/TR/html4/loose.dtd",                         // XM_VERS_HTML401_TRANS,  // HTML v4.01 Transitional
   (const unsigned char *)"http://www.w3.org/TR/1999/REC-html401-19991224/strict.dtd",    // XM_VERS_HTML401,        // HTML v4.01
   (const unsigned char *)"http://www.w3.org/TR/1999/REC-html401-19991224/frameset.dtd",  // XM_VERS_HTML401_FRAME,  // HTML v4.01 with Frameset
   (const unsigned char *)"http://www.w3.org/TR/html4/loose.dtd",                         // XM_VERS_HTML_TAGE
   (const unsigned char *)"DTD/xhtml1-strict.dtd",                                        // XM_VERS_XHTML,          // XHTML // "http://www.w3.org/TR/MathML2/dtd/xhtml-math11-f.dtd"
   (const unsigned char *)"DTD/xhtml1-strict.dtd",                                        // XM_VERS_XHTML_TAGE // "http://www.w3.org/TR/MathML2/dtd/xhtml-math11-f.dtd"
   (const unsigned char *)"",                                                             // XM_VERS_XML,            // for distingwishing between HTML and XML only
   (const unsigned char *)"",                                                             // XM_VERS_XML10,          // XML v1.0
   (const unsigned char *)"",                                                             // XM_VERS_SVG

   NULL
};


// ==================================================  additional functions
// --------------------------------------------------
HRESULT GetTagIndex(int *piIndex, const unsigned char *lpszKeywrd, const unsigned char * const *plpszKeytable)
{
HRESULT retc=S_OK;
int id1;
unsigned char tag_buf[TV_TAG_LEN+1];
unsigned char table_entry_buf[TV_TAG_LEN+1];
const unsigned char *pnts;
unsigned char *pntd;

   *piIndex=XC_TG_NoTag;

   if(strlen(lpszKeywrd)>=TV_TAG_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszKeywrd, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntd=tag_buf;
      pnts=lpszKeywrd;
      while((*pnts) && (TvStrChr(lpszSpcEol, (KpChar)*pnts)==NULL) &&
         (*pnts!=TV_XM_TagEndCh) && // '>'
         ((*pnts!=TV_XM_EndTagIndCh) || (*(pnts+1)!=TV_XM_TagEndCh)) && // '/', '>' - single tags "/>"
         (pntd-tag_buf<TV_TAG_LEN))
         *(pntd++)=tolower(*pnts++);
      if(pntd-tag_buf>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      *pntd=Nul;
   }

   if(SUCCEEDED(retc))
   {
      id1=0;
      while((plpszKeytable[id1]!=NULL) && (*piIndex==XC_TG_NoTag) && SUCCEEDED(retc))
      {
         pntd=table_entry_buf;
         pnts=plpszKeytable[id1];
         while((*pnts) && (TvStrChr(lpszSpcEol, (KpChar)*pnts)==NULL) &&
            (*pnts!=TV_XM_TagEndCh) && // '>'
            ((*pnts!=TV_XM_EndTagIndCh) || (*(pnts+1)!=TV_XM_TagEndCh)) && // '/', '>' - single tags "/>"
            (pntd-table_entry_buf<TV_TAG_LEN))
            *(pntd++)=tolower(*pnts++);
         if(pntd-table_entry_buf>=TV_TAG_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         *pntd=Nul;

         if(strcmp(tag_buf, table_entry_buf)==0) *piIndex=id1;
         id1++;
      }

      if((*piIndex==XC_TG_NoTag) && SUCCEEDED(retc))
      {
         retc=TV_E_UNKN_TAG;
//       retc=KpErrorProc.OutputErrorMessage(TV_E_UNKN_TAG, lpszKeywrd, True, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}
