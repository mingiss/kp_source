// ==================================================
// tvxmlevc0.cpp
// endings and suffixes skipper for searching in flex. languages
// german language - fictive entries
// compressed endings file


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <fstream>
#include <string>
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
unsigned char *plpszaToGrForm_v[] = 
{
   NULL, NULL
};


// -------------------------------------------------
unsigned char lpszToMainForm_v[] = 
{
#if Compiler==Msvc60
   (unsigned char *)
#endif
   ""
};


// -------------------------------------------------
unsigned char *plpszauPrefixes_v[] = 
{
   NULL, NULL, NULL
};


// -------------------------------------------------
unsigned char *plpszaEndSkipTableCompact_v[] = 
{
   NULL, NULL, NULL
};


// -------------------------------------------------
unsigned char *plpszauUnRegForms_v[] = 
{
   NULL, NULL, NULL
};
