// ==================================================
// tvrtft.cpp
// RTF to Kpt code table conversion


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
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
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "tvrtf.h"


int iRtf2KptCTblArr[RT_MAX_NUM_OF_RTF_CTBLS]=
{
   74 /*76*/ /* 71 */,        //    0  ANSI_CHARSET         // ECMA Latin 1 (MS Windows ANSI) (Ascii english)
   KPT_NoCodeTable,           //    1  DEFAULT_CHARSET
   1, // ???? // 85, // 83, // 75   (', \, {, } and all letters are needed for output) */ 
                              //    2  SYMBOL_CHARSET       // MS Windows Symbol Font, also MS Windows Wingdings !!! - must be processed separately
   KPT_NoCodeTable,           //    3
   KPT_NoCodeTable,           //    4
   KPT_NoCodeTable,           //    5
   KPT_NoCodeTable,           //    6
   KPT_NoCodeTable,           //    7
   KPT_NoCodeTable,           //    8
   KPT_NoCodeTable,           //    9
   KPT_NoCodeTable,           //   10
   KPT_NoCodeTable,           //   11
   KPT_NoCodeTable,           //   12
   KPT_NoCodeTable,           //   13
   KPT_NoCodeTable,           //   14
   KPT_NoCodeTable,           //   15
   KPT_NoCodeTable,           //   16
   KPT_NoCodeTable,           //   17
   KPT_NoCodeTable,           //   18
   KPT_NoCodeTable,           //   19
   KPT_NoCodeTable,           //   20
   KPT_NoCodeTable,           //   21
   KPT_NoCodeTable,           //   22
   KPT_NoCodeTable,           //   23
   KPT_NoCodeTable,           //   24
   KPT_NoCodeTable,           //   25
   KPT_NoCodeTable,           //   26
   KPT_NoCodeTable,           //   27
   KPT_NoCodeTable,           //   28
   KPT_NoCodeTable,           //   29
   KPT_NoCodeTable,           //   30
   KPT_NoCodeTable,           //   31
   KPT_NoCodeTable,           //   32
   KPT_NoCodeTable,           //   33
   KPT_NoCodeTable,           //   34
   KPT_NoCodeTable,           //   35
   KPT_NoCodeTable,           //   36
   KPT_NoCodeTable,           //   37
   KPT_NoCodeTable,           //   38
   KPT_NoCodeTable,           //   39
   KPT_NoCodeTable,           //   40
   KPT_NoCodeTable,           //   41
   KPT_NoCodeTable,           //   42
   KPT_NoCodeTable,           //   43
   KPT_NoCodeTable,           //   44
   KPT_NoCodeTable,           //   45
   KPT_NoCodeTable,           //   46
   KPT_NoCodeTable,           //   47
   KPT_NoCodeTable,           //   48
   KPT_NoCodeTable,           //   49
   KPT_NoCodeTable,           //   50
   KPT_NoCodeTable,           //   51
   KPT_NoCodeTable,           //   52
   KPT_NoCodeTable,           //   53
   KPT_NoCodeTable,           //   54
   KPT_NoCodeTable,           //   55
   KPT_NoCodeTable,           //   56
   KPT_NoCodeTable,           //   57
   KPT_NoCodeTable,           //   58
   KPT_NoCodeTable,           //   59
   KPT_NoCodeTable,           //   60
   KPT_NoCodeTable,           //   61
   KPT_NoCodeTable,           //   62
   KPT_NoCodeTable,           //   63
   KPT_NoCodeTable,           //   64
   KPT_NoCodeTable,           //   65
   KPT_NoCodeTable,           //   66
   KPT_NoCodeTable,           //   67
   KPT_NoCodeTable,           //   68
   KPT_NoCodeTable,           //   69
   KPT_NoCodeTable,           //   70
   KPT_NoCodeTable,           //   71
   KPT_NoCodeTable,           //   72
   KPT_NoCodeTable,           //   73
   KPT_NoCodeTable,           //   74
   KPT_NoCodeTable,           //   75
   KPT_NoCodeTable,           //   76
   KPT_NoCodeTable,           //   77  MAC_CHARSET
   KPT_NoCodeTable,           //   78
   KPT_NoCodeTable,           //   79
   KPT_NoCodeTable,           //   80
   KPT_NoCodeTable,           //   81
   KPT_NoCodeTable,           //   82
   KPT_NoCodeTable,           //   83
   KPT_NoCodeTable,           //   84
   KPT_NoCodeTable,           //   85
   KPT_NoCodeTable,           //   86
   KPT_NoCodeTable,           //   87
   KPT_NoCodeTable,           //   88
   KPT_NoCodeTable,           //   89
   KPT_NoCodeTable,           //   90
   KPT_NoCodeTable,           //   91
   KPT_NoCodeTable,           //   92
   KPT_NoCodeTable,           //   93
   KPT_NoCodeTable,           //   94
   KPT_NoCodeTable,           //   95
   KPT_NoCodeTable,           //   96
   KPT_NoCodeTable,           //   97
   KPT_NoCodeTable,           //   98
   KPT_NoCodeTable,           //   99
   KPT_NoCodeTable,           //  100
   KPT_NoCodeTable,           //  101
   KPT_NoCodeTable,           //  102
   KPT_NoCodeTable,           //  103
   KPT_NoCodeTable,           //  104
   KPT_NoCodeTable,           //  105
   KPT_NoCodeTable,           //  106
   KPT_NoCodeTable,           //  107
   KPT_NoCodeTable,           //  108
   KPT_NoCodeTable,           //  109
   KPT_NoCodeTable,           //  110
   KPT_NoCodeTable,           //  111
   KPT_NoCodeTable,           //  112
   KPT_NoCodeTable,           //  113
   KPT_NoCodeTable,           //  114
   KPT_NoCodeTable,           //  115
   KPT_NoCodeTable,           //  116
   KPT_NoCodeTable,           //  117
   KPT_NoCodeTable,           //  118
   KPT_NoCodeTable,           //  119
   KPT_NoCodeTable,           //  120
   KPT_NoCodeTable,           //  121
   KPT_NoCodeTable,           //  122
   KPT_NoCodeTable,           //  123
   KPT_NoCodeTable,           //  124
   KPT_NoCodeTable,           //  125
   KPT_NoCodeTable,           //  126
   KPT_NoCodeTable,           //  127
   1,                         //  128  SHIFTJIS_CHARSET  // Mincho, Gothic, MS Mincho, MS Gothic (is mcm sourcu)
   1,                         //  129  HANGEUL_CHARSET, HANGUL_CHARSET  // Batang, Dotum, Gulim (is mcm sourcu)
   KPT_NoCodeTable,           //  130  JOHAB_CHARSET
   KPT_NoCodeTable,           //  131
   KPT_NoCodeTable,           //  132
   KPT_NoCodeTable,           //  133
   1,                         //  134  GB2312_CHARSET    // SimSun, SimHei (is mcm sourcu)
   KPT_NoCodeTable,           //  135
   1,                         //  136  CHINESEBIG5_CHARSET  // PMingLiU, MingLiU (is mcm sourcu)
   KPT_NoCodeTable,           //  137
   KPT_NoCodeTable,           //  138
   KPT_NoCodeTable,           //  139
   KPT_NoCodeTable,           //  140
   KPT_NoCodeTable,           //  141
   KPT_NoCodeTable,           //  142
   KPT_NoCodeTable,           //  143
   KPT_NoCodeTable,           //  144
   KPT_NoCodeTable,           //  145
   KPT_NoCodeTable,           //  146
   KPT_NoCodeTable,           //  147
   KPT_NoCodeTable,           //  148
   KPT_NoCodeTable,           //  149
   KPT_NoCodeTable,           //  150
   KPT_NoCodeTable,           //  151
   KPT_NoCodeTable,           //  152
   KPT_NoCodeTable,           //  153
   KPT_NoCodeTable,           //  154
   KPT_NoCodeTable,           //  155
   KPT_NoCodeTable,           //  156
   KPT_NoCodeTable,           //  157
   KPT_NoCodeTable,           //  158
   KPT_NoCodeTable,           //  159
   KPT_NoCodeTable,           //  160
   78,                        //  161  GREEK_CHARSET     // MS Windows Greek CharSet
   1,                         //  162  TURKISH_CHARSET   // MS Windows Tur(key)
   KPT_NoCodeTable,           //  163  VIETNAMESE_CHARSET
   KPT_NoCodeTable,           //  164
   KPT_NoCodeTable,           //  165
   KPT_NoCodeTable,           //  166
   KPT_NoCodeTable,           //  167
   KPT_NoCodeTable,           //  168
   KPT_NoCodeTable,           //  169
   KPT_NoCodeTable,           //  170
   KPT_NoCodeTable,           //  171
   KPT_NoCodeTable,           //  172
   KPT_NoCodeTable,           //  173
   KPT_NoCodeTable,           //  174
   KPT_NoCodeTable,           //  175
   KPT_NoCodeTable,           //  176
   1,                         //  177  HEBREW_CHARSET    // MS Windows Hebrew
   1,                         //  178  ARABIC_CHARSET    // MS Windows Arabic
   KPT_NoCodeTable,           //  179
   KPT_NoCodeTable,           //  180
   KPT_NoCodeTable,           //  181
   KPT_NoCodeTable,           //  182
   KPT_NoCodeTable,           //  183
   KPT_NoCodeTable,           //  184
   KPT_NoCodeTable,           //  185
   76 /* 71 */ ,              //  186  BALTIC_CHARSET    // LST 1282-93 (Baltic-RIM), Win-1257
   KPT_NoCodeTable,           //  187
   KPT_NoCodeTable,           //  188
   KPT_NoCodeTable,           //  189
   KPT_NoCodeTable,           //  190
   KPT_NoCodeTable,           //  191
   KPT_NoCodeTable,           //  192
   KPT_NoCodeTable,           //  193
   KPT_NoCodeTable,           //  194
   KPT_NoCodeTable,           //  195
   KPT_NoCodeTable,           //  196
   KPT_NoCodeTable,           //  197
   KPT_NoCodeTable,           //  198
   KPT_NoCodeTable,           //  199
   KPT_NoCodeTable,           //  200
   KPT_NoCodeTable,           //  201
   KPT_NoCodeTable,           //  202
   KPT_NoCodeTable,           //  203
   73,                        //  204  RUSSIAN_CHARSET   // MS Windows-1251, Windows Cyrillic
   KPT_NoCodeTable,           //  205
   KPT_NoCodeTable,           //  206
   KPT_NoCodeTable,           //  207
   KPT_NoCodeTable,           //  208
   KPT_NoCodeTable,           //  209
   KPT_NoCodeTable,           //  210
   KPT_NoCodeTable,           //  211
   KPT_NoCodeTable,           //  212
   KPT_NoCodeTable,           //  213
   KPT_NoCodeTable,           //  214
   KPT_NoCodeTable,           //  215
   KPT_NoCodeTable,           //  216
   KPT_NoCodeTable,           //  217
   KPT_NoCodeTable,           //  218
   KPT_NoCodeTable,           //  219
   KPT_NoCodeTable,           //  220
   KPT_NoCodeTable,           //  221
   KPT_NoCodeTable,           //  222  THAI_CHARSET
   KPT_NoCodeTable,           //  223
   KPT_NoCodeTable,           //  224
   KPT_NoCodeTable,           //  225
   KPT_NoCodeTable,           //  226
   KPT_NoCodeTable,           //  227
   KPT_NoCodeTable,           //  228
   KPT_NoCodeTable,           //  229
   KPT_NoCodeTable,           //  230
   KPT_NoCodeTable,           //  231
   KPT_NoCodeTable,           //  232
   KPT_NoCodeTable,           //  233
   KPT_NoCodeTable,           //  234
   KPT_NoCodeTable,           //  235
   KPT_NoCodeTable,           //  236
   KPT_NoCodeTable,           //  237
   79,                        //  238  EASTEUROPE_CHARSET   // MS Windows  CE (Central Europe), Win-1250
   KPT_NoCodeTable,           //  239
   KPT_NoCodeTable,           //  240
   KPT_NoCodeTable,           //  241
   KPT_NoCodeTable,           //  242
   KPT_NoCodeTable,           //  243
   KPT_NoCodeTable,           //  244
   KPT_NoCodeTable,           //  245
   KPT_NoCodeTable,           //  246
   KPT_NoCodeTable,           //  247
   KPT_NoCodeTable,           //  248
   KPT_NoCodeTable,           //  249
// RT_FIRST_USER_RTF_CTBL
   82,                        //  250           // Windows universal Phonetic "PhoneticTMUniv", non standard RTF !!!
   86,                        //  251           // MS Windows Wingdings, non standard RTF !!!
   85,                        //  252           // MS Windows Symbol Font, also could be under RTF name MTMI (mathematical font), non standard RTF !!!
   81,                        //  253           // Windows basic Phonetic "PhoneticTM", non standard RTF !!!
   80,                        //  254           // Windows LT Accented "TimesLT Accented", non standard RTF !!!
// RT_LAST_USER_RTF_CTBL
   KPT_NoCodeTable,           //  255  OEM_CHARSET
};


int iKpt2RtfCTblArr[KPT_Ctnum]=
{
  DEFAULT_CHARSET,   //   1 //  0
  ANSI_CHARSET,      //   0 //  1 ISO-646        IRV version, basic Latin, ASCII       
  DEFAULT_CHARSET,   //   1 //  2 KOI-7          ISO Registration #37, basic Cyrillic, KOI-7-1
  DEFAULT_CHARSET,   //   1 //  3 ISO-5426       Extended Latin, based on ASCII        
  DEFAULT_CHARSET,   //   1 //  4 ISO-5427       Extended Cyrillic, based on ASCII     
  DEFAULT_CHARSET,   //   1 //  5 ISO-5428       Greek, based on ASCII                 
  DEFAULT_CHARSET,   //   1 //  6 ISO-6438       African coded character set, based on ASCII
  DEFAULT_CHARSET,   //   1 //  7                                       
  DEFAULT_CHARSET,   //   1 //  8                                       
  DEFAULT_CHARSET,   //   1 //  9                                       
  DEFAULT_CHARSET,   //   1 // 10                TeX TEV output character set        
  DEFAULT_CHARSET,   //   1 // 11                                       
  DEFAULT_CHARSET,   //   1 // 12                                       
  DEFAULT_CHARSET,   //   1 // 13                                       
  DEFAULT_CHARSET,   //   1 // 14                                    
  DEFAULT_CHARSET,   //   1 // 15                                    
  DEFAULT_CHARSET,   //   1 // 16                                    
  DEFAULT_CHARSET,   //   1 // 17                                    
  DEFAULT_CHARSET,   //   1 // 18                                    
  DEFAULT_CHARSET,   //   1 // 19                                    
  DEFAULT_CHARSET,   //   1 // 20                                    
  DEFAULT_CHARSET,   //   1 // 21                German, based on ASCII              
  DEFAULT_CHARSET,   //   1 // 22                French, based on ASCII              
  DEFAULT_CHARSET,   //   1 // 23                Norvegian/danish, based on ASCII    
  DEFAULT_CHARSET,   //   1 // 24                Swedish/finnish, based on ASCII     
  DEFAULT_CHARSET,   //   1 // 25                                    
  DEFAULT_CHARSET,   //   1 // 26                                    
  DEFAULT_CHARSET,   //   1 // 27                                    
  DEFAULT_CHARSET,   //   1 // 28                                    
  DEFAULT_CHARSET,   //   1 // 29                                    
  DEFAULT_CHARSET,   //   1 // 30                                    
  DEFAULT_CHARSET,   //   1 // 31 IBM-437        DOS Multilingual, Latin I, PC-8       
  DEFAULT_CHARSET,   //   1 // 32 IBM-852        DOS Central European, Slavic, Latin II
  DEFAULT_CHARSET,   //   1 // 33 IBM-850        DOS Western, Multilingual, Latin I+   
  DEFAULT_CHARSET,   //   1 // 34 IBM-863        DOS Canadian-French                   
  DEFAULT_CHARSET,   //   1 // 35                                      
  DEFAULT_CHARSET,   //   1 // 36                                      
  DEFAULT_CHARSET,   //   1 // 37                                      
  DEFAULT_CHARSET,   //   1 // 38                                      
  DEFAULT_CHARSET,   //   1 // 39                                      
  DEFAULT_CHARSET,   //   1 // 40                                      
  DEFAULT_CHARSET,   //   1 // 41 IBM-774        DOS Lithuanian standard, based on IBM-437
  DEFAULT_CHARSET,   //   1 // 42 IBM-772        DOS Lithuanian standard, based on IBM-855 Cyrillic
  DEFAULT_CHARSET,   //   1 // 43 IBM-773        DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic
  DEFAULT_CHARSET,   //   1 // 44 IBM-770        Baltic, Fotonija, RST 1095-89         
  DEFAULT_CHARSET,   //   1 // 45 ISO-8859-4     Baltic, old variant of Baltic-RIM     
  DEFAULT_CHARSET,   //   1 // 46 IBM-771        DOS Lithuanian, IBM-Kbl, based on IBM-437
  DEFAULT_CHARSET,   //   1 // 47 IBM-855        DOS Cyrillic only, without Latin      
  DEFAULT_CHARSET,   //   1 // 48 IBM-855        DOS Cyrillic                          
  DEFAULT_CHARSET,   //   1 // 49 IBM-773        DOS Lithuanian with Polish letters (TEV), IBM-Kbl, based on IBM-855 Cyrillic
  DEFAULT_CHARSET,   //   1 // 50                DOS Lithuanian accented, based on IBM-Kbl
  DEFAULT_CHARSET,   //   1 // 51 KOI8-R         DOS Cyrillic                          
  DEFAULT_CHARSET,   //   1 // 52 ISO-IR-111     DOS Cyrillic, ISO-K, code set of russian made PC
  DEFAULT_CHARSET,   //   1 // 53 IBM-773(-)     DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic TEX TEV
  DEFAULT_CHARSET,   //   1 // 54 IBM-771(-)     DOS Lithuanian, IBM-Kbl, based on IBM-437 TEX TEV
  DEFAULT_CHARSET,   //   1 // 55
  DEFAULT_CHARSET,   //   1 // 56
  DEFAULT_CHARSET,   //   1 // 57
  DEFAULT_CHARSET,   //   1 // 58
  DEFAULT_CHARSET,   //   1 // 59
  DEFAULT_CHARSET,   //   1 // 60
  DEFAULT_CHARSET,   //   1 // 61 DKOI, EBCDIC
  DEFAULT_CHARSET,   //   1 // 62
  DEFAULT_CHARSET,   //   1 // 63
  DEFAULT_CHARSET,   //   1 // 64
  DEFAULT_CHARSET,   //   1 // 65
  DEFAULT_CHARSET,   //   1 // 66
  DEFAULT_CHARSET,   //   1 // 67
  DEFAULT_CHARSET,   //   1 // 68
  DEFAULT_CHARSET,   //   1 // 69
  DEFAULT_CHARSET,   //   1 // 70
  BALTIC_CHARSET,    // 186 // 71 Windows-1257  Baltic RIM, LST 1282-93, ISO-8859-13  
  DEFAULT_CHARSET,   //   1 // 72               Windows SC                            
  RUSSIAN_CHARSET,   // 204 // 73 Windows-1251  Windows Cyrillic                      
  ANSI_CHARSET,      //   0 // 74 ISO-Latin-1   Windows-1252, ANSI, ECMA Latin 1      
  SYMBOL_CHARSET,    //   2 // 75               Windows Symbol Font for TEX formula fields
  BALTIC_CHARSET,    // 186 // 76 Windows-1257  Baltic-RIM, some RTF accented characters added
  RUSSIAN_CHARSET,   // 204 // 77 Windows-1251  Cyrillic without latin, with spec. chars (for TEX tags)
  GREEK_CHARSET,     // 161 // 78 Windows-1253  Greek                                 
  EASTEUROPE_CHARSET,// 238 // 79 Windows-1250  CE, ANSI-2, Central European          
  254,               // 254 // 80    "TimesLT Accented"   Windows lithuanian accented charset    
  253,               // 253 // 81    "PhoneticTM"         Windows Phonetic basic charset        
  250,               // 250 // 82    "PhoneticTMUniv"     Windows Phonetic full (Universal) charset
  SYMBOL_CHARSET,    //   2 // 83               Windows Symbol Font                   
  DEFAULT_CHARSET,   //   1 // 84               Windows Verdana Font 8-bit encoding   

// SYMBOL_CHARSET,   //   2                   
  252,               // 252 // 85               Windows Symbol Font with ASCII lowerpart for RTF output
  
  251,               // 251 // 86               Windows Wingdings                     
  DEFAULT_CHARSET,   //   1 // 87               LED Phonetic charset                  
  DEFAULT_CHARSET,   //   1 // 88                                      
  DEFAULT_CHARSET,   //   1 // 89                                      
  DEFAULT_CHARSET,   //   1 // 90                                      
  DEFAULT_CHARSET,   //   1 // 91               Norsk Data lithuanian                 
  DEFAULT_CHARSET,   //   1 // 92               Lithuanian ASCII based standart       
  DEFAULT_CHARSET,   //   1 // 93               Norsk Data polish                     
  DEFAULT_CHARSET,   //   1 // 94                                      
  DEFAULT_CHARSET,   //   1 // 95                                      
  DEFAULT_CHARSET,   //   1 // 96                                      
  DEFAULT_CHARSET,   //   1 // 97                                      
  DEFAULT_CHARSET,   //   1 // 98                                      
  DEFAULT_CHARSET,   //   1 // 99               Transparent code table for i/o of 8-bit codes without decoding
};


// --------------------------------------------------
int ConvertRtf2KptCTbl(int iRtfCTbl)
{
int kpt_ctbl = 1;

   if((iRtfCTbl>=0) && (iRtfCTbl<RT_MAX_NUM_OF_RTF_CTBLS))
      kpt_ctbl=iRtf2KptCTblArr[iRtfCTbl];
   else
   {
//    kpt_ctbl=KPT_NoCodeTable;
      kpt_ctbl=1;
   }

return(kpt_ctbl);
}

// --------------------------------------------------
int ConvertKpt2RtfCTbl(int iKptCTbl)
{
int rtf_ctbl = DEFAULT_CHARSET;

   if((iKptCTbl>=0) && (iKptCTbl<KPT_Ctnum))
      rtf_ctbl=iKpt2RtfCTblArr[iKptCTbl];
   else
      rtf_ctbl=DEFAULT_CHARSET;
      
// user defined charsets
   if((rtf_ctbl>=RT_FIRST_USER_RTF_CTBL) && (rtf_ctbl<RT_LAST_USER_RTF_CTBL))
      rtf_ctbl=DEFAULT_CHARSET;

return(rtf_ctbl);
}
