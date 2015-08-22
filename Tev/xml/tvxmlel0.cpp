// ==================================================
// tvxmlel0.cpp
// endings and suffixes skipper for searching in flex. languages
// fictive entries for not yet ready languages
// other grammatical things
//


// ================================================== definitions
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
#include "kptt.h"
#include "tvmain.h"
#include "tvxmle.h"


// -------------------------------------------------
unsigned char *plpszaToGrForm_e[] = {NULL, NULL};
unsigned char lpszToMainForm_e[] = {""};
unsigned char *plpszauPrefixes_e[] = {   NULL, NULL, NULL   };
unsigned char *plpszaEndSkipTableCompact_e[] = {
// (unsigned char *)"'S", (unsigned char *)"", (unsigned char *)"A",
// (unsigned char *)"S", (unsigned char *)"", (unsigned char *)"A",
NULL, NULL, NULL
};
unsigned char *plpszauUnRegForms_e[] = {NULL, NULL, NULL};


// -------------------------------------------------
unsigned char *plpszaToGrForm_f[] = {NULL, NULL};
unsigned char lpszToMainForm_f[] = {""};
unsigned char *plpszauPrefixes_f[] = {   NULL, NULL, NULL   };
unsigned char *plpszaEndSkipTableCompact_f[] = {NULL, NULL, NULL};
unsigned char *plpszauUnRegForms_f[] = {NULL, NULL, NULL};


// -------------------------------------------------
unsigned char *plpszaToGrForm_r[] = {NULL, NULL};
unsigned char lpszToMainForm_r[] = {""};
unsigned char *plpszauPrefixes_r[] = {   NULL, NULL, NULL   };
unsigned char *plpszaEndSkipTableCompact_r[] = {NULL, NULL, NULL};
unsigned char *plpszauUnRegForms_r[] = {NULL, NULL, NULL};


//==================================================
const unsigned char *lpszaGramForms_v[] =
{
(unsigned char *)"sub",         // 32
(unsigned char *)"m",           // 2
(unsigned char *)"f",           // 3
(unsigned char *)"n",           // 1
(unsigned char *)"sg",          // 26
(unsigned char *)"pl",          // 4
(unsigned char *)"G",           // 42
(unsigned char *)"D",           // 50
(unsigned char *)"A",           // 52

(unsigned char *)"vt",          // 29
(unsigned char *)"vi",          // 27
(unsigned char *)"vimp",        // 28
(unsigned char *)"impf",        // 15
(unsigned char *)"inf",         // 16
(unsigned char *)"präs",        // 49
(unsigned char *)"präs.",       // 33
(unsigned char *)"part II",     // 21

(unsigned char *)"a",           // 5
(unsigned char *)"comp",        // 39
(unsigned char *)"superl",      // 40

(unsigned char *)"adv",         // 7
(unsigned char *)"pron",        // 22
(unsigned char *)"pron rez",    // 38
(unsigned char *)"pron indef",  // 41
(unsigned char *)"pron adv",    // 43
(unsigned char *)"pron dem",    // 44
(unsigned char *)"pron poss",   // 45
(unsigned char *)"pron pers",   // 47
(unsigned char *)"pron rel",    // 48
(unsigned char *)"pron refl",   // 55
(unsigned char *)"pron inter",  // 57

(unsigned char *)"num",         // 20
(unsigned char *)"num indef",   // 56

(unsigned char *)"cj",          // 8

(unsigned char *)"imp",         // 14

(unsigned char *)"prtc",        // 24

(unsigned char *)"int",         // 36  ???

(unsigned char *)"inv",         // 37  ???

(unsigned char *)"prp",         // 23
};


const unsigned char *lpszaGramForms_l[] =
{
(unsigned char *)"dkt.",        // 46
(unsigned char *)"veiksm.",     // 34
(unsigned char *)"modalinis",   // 53
(unsigned char *)"neatsk.",     // 30
(unsigned char *)"atsk.",       // 31
(unsigned char *)"prieðdëlis",  // 35
(unsigned char *)"bûdv.",       // 54
};
