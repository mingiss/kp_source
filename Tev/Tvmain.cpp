// ==================================================
// tvmain.cpp
// main module for dictionary processing


// ==================================================
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
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
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"

#include "tvmain.h"



// ================================================== TRACE() variables
int AllCnt=5;
int FopenCnt=5;


// ================================================== KpErrorProc_tag local functions
// --------------------------------------------------
HRESULT KpErrorProcClass::FormatErrorMessage
(
   const HRESULT lhRetc,
   unsigned char *lpszMsg
)
{
HRESULT retc=S_OK;
unsigned char *msgptr=(unsigned char *)"";
unsigned char tmp_msg[KP_MSG_LEN+1];

   switch(lhRetc)
   {
      case TV_E_TAG_OVERFL:      msgptr=(unsigned char *)"Keyword too long"; break;
      case TV_E_TAG_UNEXPECTED:  msgptr=(unsigned char *)"Tag unexpected"; break;
      case TV_E_DOUBLE_FONT_DEF: msgptr=(unsigned char *)"Duplicated font definition"; break;
      case TV_E_DOUBLE_INDEX:    msgptr=(unsigned char *)"Duplicate index"; break;
      case TV_E_UNKN_TAG:        msgptr=(unsigned char *)"Unknown tag"; break;
      case TV_E_FREE_CHARS:      msgptr=(unsigned char *)"Characters outside of fields"; break;
      case TV_E_BAD_INDEX:       msgptr=(unsigned char *)"Corrupted index file"; break;
      case TV_E_OPEN_TAG:        msgptr=(unsigned char *)"Unclosed tags"; break;
//
      default:
         retc=FormatErrorMessageMain(lhRetc, tmp_msg);
         if(SUCCEEDED(retc)) msgptr=tmp_msg;
         break;
   }

   if(SUCCEEDED(retc))
      if(strlen(msgptr)>KP_MSG_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL /* pListBox */);
   if(SUCCEEDED(retc))
      strcpy((char *)lpszMsg,(const char *)msgptr);

return(retc);
}


