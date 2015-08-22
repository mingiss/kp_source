// ==================================================
// tvxmlelc0.cpp
// endings and suffixes skipper for searching in flex. languages
// lithuanian language - fictive entries
// obsolete - index encodings should be used
//


// ================================================== definitions
#include "envir.h"

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
unsigned char *plpszaToGrForm_l[] = 
{
   NULL, NULL
};


// -------------------------------------------------
unsigned char lpszToMainForm_l[] = 
{
#if Compiler==Msvc60
   (unsigned char *)
#endif
   ""
};


// -------------------------------------------------
unsigned char *plpszauPrefixes_l[] =
{                                                                           
   NULL, NULL, NULL
};


// -------------------------------------------------
unsigned char *plpszaEndSkipTableCompact_l[] = 
{
   NULL, NULL, NULL
};


// -------------------------------------------------
unsigned char *plpszauUnRegForms_l[] = 
{
   NULL, NULL, NULL
};


