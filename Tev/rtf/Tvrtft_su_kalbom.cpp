// ==================================================
// tvrtft.cpp
// RTF to Kpt code table conversion


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#include <stdio.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "tvrtf.h"


// -------------------------------------------------
int iaKpt2RtfLangCodesArr[KPT_Ctnum]=
{
      0, // (unsigned char *)"",                                      //  0
      0, // (unsigned char *)"IRV version, basic Latin, ASCII",       //  1   ISO-646
      0, // (unsigned char *)"ISO Registration #37, basic Cyrillic, KOI-7-1",
                                                                      //  2   KOI-7
      0, // (unsigned char *)"Extended Latin, based on ASCII",        //  3   ISO-5426
      0, // (unsigned char *)"Extended Cyrillic, based on ASCII",     //  4   ISO-5427
      0, // (unsigned char *)"Greek, based on ASCII",                 //  5   ISO-5428
      0, // (unsigned char *)"African coded character set, based on ASCII",
                                                                      //  6   ISO-6438
      0, // (unsigned char *)"",                                      //  7
      0, // (unsigned char *)"",                                      //  8
      0, // (unsigned char *)"",                                      //  9
      0, // (unsigned char *)"TeX TEV output character set",          // 10
      0, // (unsigned char *)"",                                      // 11
      0, // (unsigned char *)"",                                      // 12
      0, // (unsigned char *)"",                                      // 13
      0, // (unsigned char *)"",                                      // 14
      0, // (unsigned char *)"",                                      // 15
      0, // (unsigned char *)"",                                      // 16
      0, // (unsigned char *)"",                                      // 17
      0, // (unsigned char *)"",                                      // 18
      0, // (unsigned char *)"",                                      // 19
      0, // (unsigned char *)"",                                      // 20
      0, // (unsigned char *)"German, based on ASCII",                // 21
      0, // (unsigned char *)"French, based on ASCII",                // 22
      0, // (unsigned char *)"Norvegian/danish, based on ASCII",      // 23
      0, // (unsigned char *)"Swedish/finnish, based on ASCII",       // 24
      0, // (unsigned char *)"",                                      // 25
      0, // (unsigned char *)"",                                      // 26
      0, // (unsigned char *)"",                                      // 27
      0, // (unsigned char *)"",                                      // 28
      0, // (unsigned char *)"",                                      // 29
      0, // (unsigned char *)"",                                      // 30
      0, // (unsigned char *)"DOS Multilingual, Latin I, PC-8",       // 31  IBM-437
      0, // (unsigned char *)"DOS Central European, Slavic, Latin II",// 32  IBM-852
      0, // (unsigned char *)"DOS Western, Multilingual, Latin I+",   // 33  IBM-850
      0, // (unsigned char *)"DOS Canadian-French",                   // 34  IBM-863
      0, // (unsigned char *)"",                                      // 35
      0, // (unsigned char *)"",                                      // 36
      0, // (unsigned char *)"",                                      // 37
      0, // (unsigned char *)"",                                      // 38
      0, // (unsigned char *)"",                                      // 39
      0, // (unsigned char *)"",                                      // 40
      0, // (unsigned char *)"DOS Lithuanian standard, based on IBM-437",
                                                                      // 41  IBM-774
      0, // (unsigned char *)"DOS Lithuanian standard, based on IBM-855 Cyrillic",
                                                                      // 42  IBM-772
      0, // (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic",
                                                                      // 43  IBM-773
      0, // (unsigned char *)"Baltic, Fotonija, RST 1095-89",         // 44  IBM-770
      0, // (unsigned char *)"Baltic, old variant of Baltic-RIM",     // 45  ISO-8859-4
      0, // (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-437",
                                                                      // 46  IBM-771
      0, // (unsigned char *)"DOS Cyrillic only, without Latin",      // 47  IBM-855
      0, // (unsigned char *)"DOS Cyrillic",                          // 48  IBM-855
      0, // (unsigned char *)"DOS Lithuanian with Polish letters (TEV), IBM-Kbl, based on IBM-855 Cyrillic",
                                                                      // 49  IBM-773
      0, // (unsigned char *)"DOS Lithuanian accented, based on IBM-Kbl",
                                                                      // 50
      0, // (unsigned char *)"DOS Cyrillic",                          // 51  KOI8-R
      0, // (unsigned char *)"DOS Cyrillic, ISO-K, code set of russian made PC",
                                                                      // 52  ISO-IR-111
      0, // (unsigned char *)"",                                      // 53
      0, // (unsigned char *)"",                                      // 54
      0, // (unsigned char *)"",                                      // 55
      0, // (unsigned char *)"",                                      // 56
      0, // (unsigned char *)"",                                      // 57
      0, // (unsigned char *)"",                                      // 58
      0, // (unsigned char *)"",                                      // 59
      0, // (unsigned char *)"",                                      // 60
      0, // (unsigned char *)"",                                      // 61  DKOI, EBCDIC
      0, // (unsigned char *)"",                                      // 62
      0, // (unsigned char *)"",                                      // 63
      0, // (unsigned char *)"",                                      // 64
      0, // (unsigned char *)"",                                      // 65
      0, // (unsigned char *)"",                                      // 66
      0, // (unsigned char *)"",                                      // 67
      0, // (unsigned char *)"",                                      // 68
      0, // (unsigned char *)"",                                      // 69
      0, // (unsigned char *)"",                                      // 70
   1063, // (unsigned char *)"Baltic RIM, LST 1282-93, ISO 8859-13",  // 71  Windows-1257
      0, // (unsigned char *)"Windows SC",                            // 72
      0, // (unsigned char *)"Windows Cyrillic",                      // 73  Windows-1251
   1033, // (unsigned char *)"Windows-1252, ANSI, ECMA Latin 1",      // 74   ISO-Latin-1
      0, // (unsigned char *)"Windows Symbol Font for TEX formula fields",
                                                                      // 75
      0, // (unsigned char *)"Baltic-RIM, some RTF accented characters added",
                                                                      // 76  Windows-1257 
      0, // (unsigned char *)"Cyrillic without latin, with spec. chars (for TEX tags)",
                                                                      // 77  Windows-1251 
      0, // (unsigned char *)"Greek",                                 // 78  Windows-1253
      0, // (unsigned char *)"CE, ANSI-2, Central European",          // 79  Windows-1250
      0, // (unsigned char *)"Windows lithuanian accented charset",   // 80 // "TimesLT Accented"
      0, // (unsigned char *)"Windows Phonetic basic charset",        // 81 // "PhoneticTM"
      0, // (unsigned char *)"Windows Phonetic full (Universal) charset",
                                                                      // 82 // "PhoneticTMUniv"
      0, // (unsigned char *)"Windows Symbol Font",                   // 83
      0, // (unsigned char *)"Windows Verdana Font 8-bit encoding",   // 84
      0, // (unsigned char *)"Windows Symbol Font with ASCII lowerpart for RTF output",
                                                                      // 85
      0, // (unsigned char *)"Windows Wingdings",                     // 86
      0, // (unsigned char *)"LED Phonetic charset",                  // 87
      0, // (unsigned char *)"",                                      // 88
      0, // (unsigned char *)"",                                      // 89
      0, // (unsigned char *)"",                                      // 90
      0, // (unsigned char *)"Norsk Data lithuanian",                 // 91
      0, // (unsigned char *)"Lithuanian ASCII based standart",       // 92
      0, // (unsigned char *)"Norsk Data polish",                     // 93
      0, // (unsigned char *)"",                                      // 94
      0, // (unsigned char *)"",                                      // 95
      0, // (unsigned char *)"",                                      // 96
      0, // (unsigned char *)"",                                      // 97
      0, // (unsigned char *)"",                                      // 98
      0, // (unsigned char *)"Transparent code table for i/o of 8-bit codes without decoding",
};    
      

// ------------------------------------------
int iRtf2KptCTblArr[RT_MAX_NUM_OF_RTF_CTBLS]=
{
   74 /*76*/ /* 71 */,        //    0     ECMA Latin 1 (MS Windows ANSI) (Ascii english)
   KPT_NoCodeTable,           //    1
   1, // 85, // 83, 75   (', \, {, } and all letters are needed for output) */ //   2     MS Windows Symbol Font, also MS Windows Wingdings !!! - must be processed separately
   KPT_NoCodeTable,           //    3
   KPT_NoCodeTable,           //    4
   KPT_NoCodeTable,           //    5
   KPT_NoCodeTable,           //    6
   KPT_NoCodeTable,           //    7
   KPT_NoCodeTable,           //    8
   KPT_NoCodeTable,           //    9
   KPT_NoCodeTable,           //    10
   KPT_NoCodeTable,           //    11
   KPT_NoCodeTable,           //    12
   KPT_NoCodeTable,           //    13
   KPT_NoCodeTable,           //    14
   KPT_NoCodeTable,           //    15
   KPT_NoCodeTable,           //    16
   KPT_NoCodeTable,           //    17
   KPT_NoCodeTable,           //    18
   KPT_NoCodeTable,           //    19
   KPT_NoCodeTable,           //    20
   KPT_NoCodeTable,           //    21
   KPT_NoCodeTable,           //    22
   KPT_NoCodeTable,           //    23
   KPT_NoCodeTable,           //    24
   KPT_NoCodeTable,           //    25
   KPT_NoCodeTable,           //    26
   KPT_NoCodeTable,           //    27
   KPT_NoCodeTable,           //    28
   KPT_NoCodeTable,           //    29
   KPT_NoCodeTable,           //    30
   KPT_NoCodeTable,           //    31
   KPT_NoCodeTable,           //    32
   KPT_NoCodeTable,           //    33
   KPT_NoCodeTable,           //    34
   KPT_NoCodeTable,           //    35
   KPT_NoCodeTable,           //    36
   KPT_NoCodeTable,           //    37
   KPT_NoCodeTable,           //    38
   KPT_NoCodeTable,           //    39
   KPT_NoCodeTable,           //    40
   KPT_NoCodeTable,           //    41
   KPT_NoCodeTable,           //    42
   KPT_NoCodeTable,           //    43
   KPT_NoCodeTable,           //    44
   KPT_NoCodeTable,           //    45
   KPT_NoCodeTable,           //    46
   KPT_NoCodeTable,           //    47
   KPT_NoCodeTable,           //    48
   KPT_NoCodeTable,           //    49
   KPT_NoCodeTable,           //    50
   KPT_NoCodeTable,           //    51
   KPT_NoCodeTable,           //    52
   KPT_NoCodeTable,           //    53
   KPT_NoCodeTable,           //    54
   KPT_NoCodeTable,           //    55
   KPT_NoCodeTable,           //    56
   KPT_NoCodeTable,           //    57
   KPT_NoCodeTable,           //    58
   KPT_NoCodeTable,           //    59
   KPT_NoCodeTable,           //    60
   KPT_NoCodeTable,           //    61
   KPT_NoCodeTable,           //    62
   KPT_NoCodeTable,           //    63
   KPT_NoCodeTable,           //    64
   KPT_NoCodeTable,           //    65
   KPT_NoCodeTable,           //    66
   KPT_NoCodeTable,           //    67
   KPT_NoCodeTable,           //    68
   KPT_NoCodeTable,           //    69
   KPT_NoCodeTable,           //    70
   KPT_NoCodeTable,           //    71
   KPT_NoCodeTable,           //    72
   KPT_NoCodeTable,           //    73
   KPT_NoCodeTable,           //    74
   KPT_NoCodeTable,           //    75
   KPT_NoCodeTable,           //    76
   KPT_NoCodeTable,           //    77
   KPT_NoCodeTable,           //    78
   KPT_NoCodeTable,           //    79
   KPT_NoCodeTable,           //    80
   KPT_NoCodeTable,           //    81
   KPT_NoCodeTable,           //    82
   KPT_NoCodeTable,           //    83
   KPT_NoCodeTable,           //    84
   KPT_NoCodeTable,           //    85
   KPT_NoCodeTable,           //    86
   KPT_NoCodeTable,           //    87
   KPT_NoCodeTable,           //    88
   KPT_NoCodeTable,           //    89
   KPT_NoCodeTable,           //    90
   KPT_NoCodeTable,           //    91
   KPT_NoCodeTable,           //    92
   KPT_NoCodeTable,           //    93
   KPT_NoCodeTable,           //    94
   KPT_NoCodeTable,           //    95
   KPT_NoCodeTable,           //    96
   KPT_NoCodeTable,           //    97
   KPT_NoCodeTable,           //    98
   KPT_NoCodeTable,           //    99
   KPT_NoCodeTable,           //    100
   KPT_NoCodeTable,           //    101
   KPT_NoCodeTable,           //    102
   KPT_NoCodeTable,           //    103
   KPT_NoCodeTable,           //    104
   KPT_NoCodeTable,           //    105
   KPT_NoCodeTable,           //    106
   KPT_NoCodeTable,           //    107
   KPT_NoCodeTable,           //    108
   KPT_NoCodeTable,           //    109
   KPT_NoCodeTable,           //    110
   KPT_NoCodeTable,           //    111
   KPT_NoCodeTable,           //    112
   KPT_NoCodeTable,           //    113
   KPT_NoCodeTable,           //    114
   KPT_NoCodeTable,           //    115
   KPT_NoCodeTable,           //    116
   KPT_NoCodeTable,           //    117
   KPT_NoCodeTable,           //    118
   KPT_NoCodeTable,           //    119
   KPT_NoCodeTable,           //    120
   KPT_NoCodeTable,           //    121
   KPT_NoCodeTable,           //    122
   KPT_NoCodeTable,           //    123
   KPT_NoCodeTable,           //    124
   KPT_NoCodeTable,           //    125
   KPT_NoCodeTable,           //    126
   KPT_NoCodeTable,           //    127
   1,                         //    128  // Mincho, Gothic, MS Mincho, MS Gothic (is mcm sourcu)
   1,                         //    129  // Batang, Dotum, Gulim (is mcm sourcu)
   KPT_NoCodeTable,           //    130
   KPT_NoCodeTable,           //    131
   KPT_NoCodeTable,           //    132
   KPT_NoCodeTable,           //    133
   1,                         //    134  // SimSun, SimHei (is mcm sourcu)
   KPT_NoCodeTable,           //    135
   1,                         //    136  // PMingLiU, MingLiU (is mcm sourcu)
   KPT_NoCodeTable,           //    137
   KPT_NoCodeTable,           //    138
   KPT_NoCodeTable,           //    139
   KPT_NoCodeTable,           //    140
   KPT_NoCodeTable,           //    141
   KPT_NoCodeTable,           //    142
   KPT_NoCodeTable,           //    143
   KPT_NoCodeTable,           //    144
   KPT_NoCodeTable,           //    145
   KPT_NoCodeTable,           //    146
   KPT_NoCodeTable,           //    147
   KPT_NoCodeTable,           //    148
   KPT_NoCodeTable,           //    149
   KPT_NoCodeTable,           //    150
   KPT_NoCodeTable,           //    151
   KPT_NoCodeTable,           //    152
   KPT_NoCodeTable,           //    153
   KPT_NoCodeTable,           //    154
   KPT_NoCodeTable,           //    155
   KPT_NoCodeTable,           //    156
   KPT_NoCodeTable,           //    157
   KPT_NoCodeTable,           //    158
   KPT_NoCodeTable,           //    159
   KPT_NoCodeTable,           //    160
   78,                        //    161   MS Windows Greek CharSet
   1,                         //    162   MS Windows Tur(key)
   KPT_NoCodeTable,           //    163
   KPT_NoCodeTable,           //    164
   KPT_NoCodeTable,           //    165
   KPT_NoCodeTable,           //    166
   KPT_NoCodeTable,           //    167
   KPT_NoCodeTable,           //    168
   KPT_NoCodeTable,           //    169
   KPT_NoCodeTable,           //    170
   KPT_NoCodeTable,           //    171
   KPT_NoCodeTable,           //    172
   KPT_NoCodeTable,           //    173
   KPT_NoCodeTable,           //    174
   KPT_NoCodeTable,           //    175
   KPT_NoCodeTable,           //    176
   1,                         //    177   MS Windows Hebrew
   1,                         //    178   MS Windows Arabic
   KPT_NoCodeTable,           //    179
   KPT_NoCodeTable,           //    180
   KPT_NoCodeTable,           //    181
   KPT_NoCodeTable,           //    182
   KPT_NoCodeTable,           //    183
   KPT_NoCodeTable,           //    184
   KPT_NoCodeTable,           //    185
   76 /* 71 */ ,              //    186  LST 1282-93 (Baltic-RIM), Win-1257
   KPT_NoCodeTable,           //    187
   KPT_NoCodeTable,           //    188
   KPT_NoCodeTable,           //    189
   KPT_NoCodeTable,           //    190
   KPT_NoCodeTable,           //    191
   KPT_NoCodeTable,           //    192
   KPT_NoCodeTable,           //    193
   KPT_NoCodeTable,           //    194
   KPT_NoCodeTable,           //    195
   KPT_NoCodeTable,           //    196
   KPT_NoCodeTable,           //    197
   KPT_NoCodeTable,           //    198
   KPT_NoCodeTable,           //    199
   KPT_NoCodeTable,           //    200
   KPT_NoCodeTable,           //    201
   KPT_NoCodeTable,           //    202
   KPT_NoCodeTable,           //    203
   73,                        //    204  MS Windows-1251, Windows Cyrillic
   KPT_NoCodeTable,           //    205
   KPT_NoCodeTable,           //    206
   KPT_NoCodeTable,           //    207
   KPT_NoCodeTable,           //    208
   KPT_NoCodeTable,           //    209
   KPT_NoCodeTable,           //    210
   KPT_NoCodeTable,           //    211
   KPT_NoCodeTable,           //    212
   KPT_NoCodeTable,           //    213
   KPT_NoCodeTable,           //    214
   KPT_NoCodeTable,           //    215
   KPT_NoCodeTable,           //    216
   KPT_NoCodeTable,           //    217
   KPT_NoCodeTable,           //    218
   KPT_NoCodeTable,           //    219
   KPT_NoCodeTable,           //    220
   KPT_NoCodeTable,           //    221
   KPT_NoCodeTable,           //    222
   KPT_NoCodeTable,           //    223
   KPT_NoCodeTable,           //    224
   KPT_NoCodeTable,           //    225
   KPT_NoCodeTable,           //    226
   KPT_NoCodeTable,           //    227
   KPT_NoCodeTable,           //    228
   KPT_NoCodeTable,           //    229
   KPT_NoCodeTable,           //    230
   KPT_NoCodeTable,           //    231
   KPT_NoCodeTable,           //    232
   KPT_NoCodeTable,           //    233
   KPT_NoCodeTable,           //    234
   KPT_NoCodeTable,           //    235
   KPT_NoCodeTable,           //    236
   KPT_NoCodeTable,           //    237
   79,                        //    238   MS Windows  CE (Central Europe), Win-1250
   KPT_NoCodeTable,           //    239
   KPT_NoCodeTable,           //    240
   KPT_NoCodeTable,           //    241
   KPT_NoCodeTable,           //    242
   KPT_NoCodeTable,           //    243
   KPT_NoCodeTable,           //    244
   KPT_NoCodeTable,           //    245
   KPT_NoCodeTable,           //    246
   KPT_NoCodeTable,           //    247
   KPT_NoCodeTable,           //    248
   KPT_NoCodeTable,           //    249
   82,                        //    250   Windows universal Phonetic "PhoneticTMUniv", non standard RTF !!!
   86,                        //    251   MS Windows Wingdings, non standard RTF !!!
   85,                        //    252   MS Windows Symbol Font, also could be under RTF name MTMI (mathematical font),non standard RTF !!!
   81,                        //    253   Windows basic Phonetic "PhoneticTM", non standard RTF !!!
   80,                        //    254   Windows LT Accented "TimesLT Accented", non standard RTF !!!
   KPT_NoCodeTable,           //    255
};


// --------------------------------------------------
int ConvertRtf2KptCTbl(int iRtfCTbl)
{
int kpt_ctbl;

   if((iRtfCTbl>=0) && (iRtfCTbl<RT_MAX_NUM_OF_RTF_CTBLS))
      kpt_ctbl=iRtf2KptCTblArr[iRtfCTbl];
   else
   {
//    kpt_ctbl=KPT_NoCodeTable;
      kpt_ctbl=1;
   }

return(kpt_ctbl);
}
