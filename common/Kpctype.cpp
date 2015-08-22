// ==================================================
// kpctype.cpp
// type conversations & character processing for KP C++ projects
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
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
#include "kpsort.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvxml.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpthp.h"


// =========================================== predefined spec. character strings
unsigned char lpszSpaces[] = " \t\xA0"; // C_NBSP
unsigned char lpszEols[] =   "\r\n";      // "\r\n\f";
unsigned char lpszSpcEol[] = " \t\xA0\r\n"; // C_NBSP // " \t\r\n\f";
unsigned char lpszSpcEolNotNBSP[] = " \t\r\n";
unsigned char lpszSpcEolNotTabNotFF[] = " \r\n";
unsigned char lpszWordDelims[] = ".,:;!? \xA0\t\r\n";

unsigned char lpszIxSpcEol[] = "/- \t\r\n";
// unsigned char lpszIxSpcEolNoAlt[] = "- \t\r\n";
unsigned char *lpszIxSpcEolPtr = lpszIxSpcEol;

unsigned char lpszSpCharsSpcEol[] = "/.,- \t\r\n";

unsigned char lpszIxSpChars[] = "/.,-"; // "/.,- \t\r\n"
// unsigned char lpszIxSpCharsNoAlt[] = ".,-"; // ".,- \t\r\n"
unsigned char *lpszIxSpCharsPtr = lpszIxSpChars;

unsigned char lpszNotDigits[] =
//"\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
//"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
   " !\"#$%&'()*+,-./"
   ":;<=>?"
   "@ABCDEFGHIJKLMNO"
   "PQRSTUVWXYZ[\\]^_"
   "`abcdefghijklmno"
   "pqrstuvwxyz{|}~"
//"\x7f"
//"ÄÅÇÉÑÖÜáàâäãåçéè"
//"êëíìîïñóòôöõúùûü"
//"†°¢£§•¶ß®©™´¨≠ÆØ"
//"_____µ∂∑∏____Ωæ_"
//"______∆«_______œ"
//"–—“”‘’÷◊ÿ_______"
//"‡·‚„‰ÂÊÁËÈÍÎÏÌÓÔ"
//"ÒÚÛÙıˆ˜¯_˙˚¸˝_\xff"
   ;

KpChar iazPunctuators[] =
{
   C_Point,    // '.'
   C_Comma,    // ','
   C_Colon,    // ':'
   C_Semic,    // ';'
   C_Excl,     // '!'
   C_Ex_Ov,    // apverstas '!'
   C_Quest,    // '?'
   C_Qst_Ov,   // apverstas '?'

   C_Dots,     // '...'
// C_Cdots,    // '...' - daugtaskis per viduri
// C_Minus,    // '-'
// C_EnDash,   // -- - vidutinio ilgio bruksnys
// C_EmDash,   // --- - ilgas bruksnys

   C_Nul
};


KpChar iazSimplySpaces[] =
{
   C_Spc,
   C_Ht,
// C_NBSP,

   C_Nul
};


KpChar iazSpaces[] =
{
   C_Spc,
   C_Ht,
   C_NBSP,
   C_QemSpc,         /* 1/4 m space */
   C_EnSpc,          /* n space */
   C_EmSpc,          /* m space */
   C_2emSpc,         /* 2 m space */
   C_NullSpc,        /* null space, \Null */

   C_Nul
};


KpChar iazSpcEol[] =
{
   C_Spc,
   C_Ht,
   C_NBSP,
   C_QemSpc,         /* 1/4 m space */
   C_EnSpc,          /* n space */
   C_EmSpc,          /* m space */
   C_2emSpc,         /* 2 m space */
   C_NullSpc,        /* null space, \Null */

   C_Cr,
   C_Lf,
   C_break,
// C_Ff,

   C_Nul
};


KpChar iazSpCharsSpcEol[] =
{
   C_Slash, // ???
   C_Point,
   C_Dash,

   C_Spc,
   C_Ht,
   C_NBSP,
   C_QemSpc,         /* 1/4 m space */
   C_EnSpc,          /* n space */
   C_EmSpc,          /* m space */
   C_2emSpc,         /* 2 m space */
   C_NullSpc,        /* null space, \Null */

   C_Cr,
   C_Lf,
   C_break,
// C_Ff,

   C_Nul
};


// ================================================== character conversations, testing
// --------------------------------------------------
KpChar TvKpToUpper(KpChar uiCh)
{
KpChar *cptr;
KpChar retch;

   retch=uiCh;
   cptr=KptUpLowTbl+1;
   while(*cptr && (*cptr!=retch)) cptr+=2;

   if(*cptr) retch=*(cptr-1);

return(retch);
}


// --------------------------------------------------
KpChar TvKpToLower(KpChar uiCh)
{
KpChar *cptr;
KpChar retch;

   retch=uiCh;
   cptr=KptUpLowTbl;
   while(*cptr && (*cptr!=retch)) cptr+=2;

   if(*cptr) retch=*(cptr+1);

return(retch);
}


// --------------------------------------------------
unsigned char TvToUpper(unsigned char ucCh, int iCtbl)
{
KpChar *cptr;
KpChar kp_ch;
unsigned char retch;

   retch = ucCh;

   if(SUCCEEDED(KptCharEncode(&kp_ch, ucCh, iCtbl)))
   {
      cptr=KptLatUpLowTbl+1;
      while(*cptr && (*cptr!=kp_ch)) cptr+=2;

      if(*cptr) kp_ch=(*(cptr-1));

      if(FAILED(KptCharDecode(&retch, kp_ch, iCtbl))) retch = '?';
   }

return(retch);
}


// --------------------------------------------------
unsigned char TvToLower(unsigned char ucCh, int iCtbl)
{
KpChar *cptr;
KpChar kp_ch;
unsigned char retch;

   retch = ucCh;

#ifdef Debug
if(ucCh == 0xD6)
ucCh = 0xD6;
#endif

   if(SUCCEEDED(KptCharEncode(&kp_ch, ucCh, iCtbl)))
   {
      cptr=KptUpLowTbl; // KptLatUpLowTbl;
      while(*cptr && (*cptr!=kp_ch)) cptr+=2;

      if(*cptr) kp_ch=(*(cptr+1));

      if(FAILED(KptCharDecode(&retch, kp_ch, iCtbl))) retch = '?';
   }

return(retch);
}


// --------------------------------------------------
unsigned char TvToUpperLat(unsigned char ucCh)
{
KpChar *cptr;
unsigned char retch;

   retch=ucCh;
   cptr=KptLatUpLowTbl+1;
   while(*cptr && (*cptr!=retch)) cptr+=2;

   if(*cptr) retch=(unsigned char)(*(cptr-1));

return(retch);
}


// --------------------------------------------------
unsigned char TvToLowerLat(unsigned char ucCh)
{
KpChar *cptr;
unsigned char retch;

   retch=ucCh;
   cptr=KptLatUpLowTbl;
   while(*cptr && (*cptr!=retch)) cptr+=2;

   if(*cptr) retch=(unsigned char)(*(cptr+1));

return(retch);
}


// --------------------------------------------------
bool TvIsDigit(KpChar uiCh)
{
bool retc = False;

   switch(uiCh)
   {
      case C_0:
      case C_1:
      case C_2:
      case C_3:
      case C_4:
      case C_5:
      case C_6:
      case C_7:
      case C_8:
      case C_9:
         retc = True;
         break;
   }

return(retc);
}


// --------------------------------------------------
bool TvIsDecDigit(KpChar uiCh)
{
bool retc = False;

   switch(uiCh)
   {
      case C_Plus:
      case C_Dash:
         retc = True;
         break;
      default:
         retc = TvIsDigit(uiCh);
         break;
   }

return(retc);
}


// --------------------------------------------------
bool TvIsFloatDigit(KpChar uiCh)
{
bool retc = False;

   switch(uiCh)
   {
      case C_Point:
      case C_E:
      case C_e:
         retc = True;
         break;
      default:
         retc = TvIsDecDigit(uiCh);
         break;
   }

return(retc);
}


// --------------------------------------------------
bool TvIsDelim(KpChar uiCh)
{
bool retc=False;

   retc=((uiCh<KPT_FirstKptChar) && (!TvIsLatinAlpha(uiCh)) && (!TvIsDigit(uiCh)));

return(retc);
}


// --------------------------------------------------
bool TvIsRealDigit(KpChar uiCh)
{
bool retc=False;

   switch(uiCh)
   {
      case C_0:
      case C_1:
      case C_2:
      case C_3:
      case C_4:
      case C_5:
      case C_6:
      case C_7:
      case C_8:
      case C_9:

      case C_Dash:
      case C_e:
      case C_E:
      case C_Point:

         retc=True;
         break;
   }

return(retc);
}


// --------------------------------------------------
bool TvIsHexDigit(KpChar uiCh)
{
bool retc=False;

   switch(uiCh)
   {
      case C_0:
      case C_1:
      case C_2:
      case C_3:
      case C_4:
      case C_5:
      case C_6:
      case C_7:
      case C_8:
      case C_9:

      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':

      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
         retc=True;
         break;
   }

return(retc);
}


// --------------------------------------------------
bool TvIsAlpha(KpChar uiCh)
{
#if FALSE
KpChar *cptr;

// if(uiCh==C_a_Diaer)
// cptr=KptUpLowTbl;

   cptr=KptUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;

return(*cptr != Nul);
#else
bool retv=False;

   if(uiCh<C_CharSize0)
      retv=(isalpha(KptToLatTbl[uiCh])!=0);

return(retv);
#endif
}


// --------------------------------------------------
bool TvIsAlpha8(unsigned char cCh, int iCtbl)
{
HRESULT retc=S_OK;
bool retv=False;
KpChar cur_ch=C_Nul;

   retc=KptCharEncode(&cur_ch, cCh, iCtbl);
   if(FAILED(retc))
   {
      if(retc!=KP_E_UNKN_CHR)
         retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
      cur_ch=C_Nul;
      retc=S_OK;
   }

return(TvIsAlpha(cur_ch));
}


// --------------------------------------------------
bool TvIsUpper(KpChar uiCh)
{
KpChar *cptr;
bool retc=False;

   cptr=KptUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;
   if(*cptr != Nul) retc=((cptr-KptUpLowTbl)%2==0);

return(retc);
}


// --------------------------------------------------
bool TvIsLower(KpChar uiCh)
{
KpChar *cptr;
bool retc=False;

   cptr=KptUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;
   if(*cptr != Nul) retc=((cptr-KptUpLowTbl)%2==1);

return(retc);
}


// --------------------------------------------------
bool TvIsLatinAlpha(KpChar uiCh)
{
KpChar *cptr;

   cptr=KptLatUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;

return(*cptr != Nul);
}


// --------------------------------------------------
bool TvIsLatinUpper(KpChar uiCh)
{
KpChar *cptr;
bool retc=False;

   cptr=KptLatUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;
   if(*cptr != Nul) retc=((cptr-KptUpLowTbl)%2==0);

return(retc);
}


// --------------------------------------------------
bool TvIsLatinLower(KpChar uiCh)
{
KpChar *cptr;
bool retc=False;

   cptr=KptLatUpLowTbl;
   while(*cptr && (*cptr!=uiCh)) cptr++;
   if(*cptr != Nul) retc=((cptr-KptUpLowTbl)%2==1);

return(retc);
}


// --------------------------------------------------
bool TvIsLatStr(const unsigned char *lpszStr)
{
bool retv = True;
const unsigned char *pnts = NULL;

   if(lpszStr)
   {
      pnts = lpszStr;
      while(*pnts)
         if(*pnts++ >= KPT_FirstKptChar)
         {
            retv = False;
            break;
         }
   }

return(retv);
}


// --------------------------------------------------
KpChar TvToLat(KpChar uiCh)
{
KpChar retch;

   retch=uiCh;
   if((uiCh<C_CharSize0) && (uiCh>=0)) retch=KptToLatTbl[uiCh];

return(retch);
}


// --------------------------------------------------
KpChar *TvKpStrLat(KpChar *piazStr)
{
HRESULT retc=S_OK;
KpChar *pnti;

   if(piazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti = piazStr;
      if(pnti) while(*pnti)
      {
         *pnti = TvToLat(*pnti);
         pnti++;
      }
   }

return(piazStr);
}


// --------------------------------------------------
unsigned char *TvStrLat(unsigned char *lpszStr, int iCtbl)
{
HRESULT retc=S_OK;
KpChar *i_text_buf = NULL;

   if((lpszStr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(i_text_buf, KpChar, strlen(lpszStr) + 1);

   if(SUCCEEDED(retc))
   {
      retc=KptStrEncode(i_text_buf, lpszStr, iCtbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) retc=S_OK;
   }

   if(SUCCEEDED(retc)) TvKpStrLat(i_text_buf);

   if(SUCCEEDED(retc))
   {
      retc=KptStrDecode(lpszStr, i_text_buf, iCtbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) retc=S_OK;
   }

   KP_DELETEA(i_text_buf);

return(lpszStr);
}


// --------------------------------------------------
KpChar *TvKpStrSpchLat(KpChar *piazStr)
{
HRESULT retc = S_OK;
KpChar *pnti;

   if(piazStr == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti = piazStr;
      if(pnti) while(*pnti)
      {
         if(!TvIsAlpha(*pnti)) *pnti = TvToLat(*pnti);
         pnti++;
      }
   }

return(piazStr);
}


// --------------------------------------------------
unsigned char *TvStrSpchLat(unsigned char *lpszStr, int iCtbl)
{
HRESULT retc = S_OK;
KpChar *i_text_buf = NULL;

   if((lpszStr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(i_text_buf, KpChar, strlen(lpszStr) + 1);

   if(SUCCEEDED(retc))
   {
      retc = KptStrEncode(i_text_buf, lpszStr, iCtbl);
      if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF)) retc = S_OK;
   }

   if(SUCCEEDED(retc)) TvKpStrSpchLat(i_text_buf);

   if(SUCCEEDED(retc))
   {
      retc = KptStrDecode(lpszStr, i_text_buf, iCtbl);
      if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF)) retc = S_OK;
   }

   KP_DELETEA(i_text_buf);

return(lpszStr);
}


// --------------------------------------------------
KpChar TvClearAccent(KpChar uiCh)
{
KpChar retch;

   retch=uiCh;
   if((uiCh<C_CharSize0) && (uiCh>=0)) retch=KptNoAccTbl[uiCh];

return(retch);
}


// --------------------------------------------------
KpChar *TvKpStrClearAccents(KpChar *piazStr)
{
HRESULT retc=S_OK;
KpChar *pnti;
// int ii;

   if(piazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti=piazStr;
      if(pnti) while(*pnti)
      {
// ii = *pnti;
         *pnti = TvClearAccent(*pnti);
// KP_TRACE_2("TvKpStrClearAccents: %d --> %d", ii, *pnti);
         pnti++;
      }
   }

return(piazStr);
}


// --------------------------------------------------
unsigned char *TvStrClearAccents(unsigned char *lpszStr, int iCtbl)
{
HRESULT retc=S_OK;
KpChar *i_text_buf = NULL;

   if((lpszStr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(i_text_buf, KpChar, strlen(lpszStr) + 1);

   if(SUCCEEDED(retc))
   {
      retc=KptStrEncode(i_text_buf, lpszStr, iCtbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) retc=S_OK;
   }

   if(SUCCEEDED(retc)) TvKpStrClearAccents(i_text_buf);

   if(SUCCEEDED(retc))
   {
      retc=KptStrDecode(lpszStr, i_text_buf, iCtbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) retc=S_OK;
   }

   KP_DELETEA(i_text_buf);

return(lpszStr);
}


// --------------------------------------------------
unsigned char *TvStrUpr(unsigned char *lpszStr, int iCtbl)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvToUpper(*pnts, iCtbl);
         pnts++;
      }
   }

return(lpszStr);
}


// --------------------------------------------------
unsigned char *TvStrLwr(unsigned char *lpszStr, int iCtbl)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvToLower(*pnts, iCtbl);
         pnts++;
      }
   }

return(lpszStr);
}


// --------------------------------------------------
unsigned char *TvStrUprLat(unsigned char *lpszStr)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvToUpperLat(*pnts);
         pnts++;
      }
   }

return(lpszStr);
}


// --------------------------------------------------
unsigned char *TvStrLwrLat(unsigned char *lpszStr)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvToLowerLat(*pnts);
         pnts++;
      }
   }

return(lpszStr);
}


// --------------------------------------------------
// #if (CompilerGr==Msvc)
unsigned char *strlwr(unsigned char *str)
{
return(TvStrLwrLat(str));
}

unsigned char *strupr(unsigned char *str)
{
return(TvStrUprLat(str));
}
// #endif


// --------------------------------------------------
KpChar *TvKpStrUpr(KpChar *piazStr)
{
HRESULT retc=S_OK;
KpChar *pnts;

   if(piazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=piazStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvKpToUpper(*pnts);
         pnts++;
      }
   }

return(piazStr);
}


// --------------------------------------------------
KpChar *TvKpStrLwr(KpChar *piazStr)
{
HRESULT retc=S_OK;
KpChar *pnts;

   if(piazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=piazStr;
      if(pnts) while(*pnts)
      {
         *pnts=TvKpToLower(*pnts);
         pnts++;
      }
   }

return(piazStr);
}


// --------------------------------------------------
HRESULT TestAllowed
(
const unsigned char *lpszCheckString,
const unsigned char *lpszCharsAllowed
)
{
HRESULT retc=S_OK;
const unsigned char *pntc;

   if((lpszCheckString==NULL) || (lpszCharsAllowed==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntc=lpszCheckString;

      while((*pntc) && SUCCEEDED(retc))
         if(strchr((const char *)lpszCharsAllowed, *pntc++)==NULL)
            retc=KP_E_UNKN_CHR;
   }

return(retc);
}


bool TvIsLatinLowerStr(const unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *pntc;
bool retv=True;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntc=lpszString;
      if(pntc==NULL) retv=False;
      else if(*pntc==Nul) retv=False;

      if(retv) while((*pntc) && retv) if(!TvIsLatinLower((KpChar)(*pntc++))) retv=False;
   }

return(retv);
}


bool TvIsNumber(const unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *pntc;
unsigned char *buf = null;
bool retv = True;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(buf, unsigned char, strlen(lpszString) + 1);
   if(SUCCEEDED(retc)) strcpy(buf, lpszString);
   if(SUCCEEDED(retc)) CutInitTrailSpcs(buf);

   if(SUCCEEDED(retc))
   {
      pntc=buf;
      if(pntc==NULL) retv=False;
      else if(*pntc==Nul) retv=False;

      if(retv) while((*pntc) && retv) if(!isdigit(*pntc++)) retv=False;
   }

   KP_DELETEA(buf);

return(retv);
}


bool TvIsNumValue(const unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *units = null;
unsigned char *pntd = null;
unsigned char *buf = null;
bool retv = True;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(buf, unsigned char, strlen(lpszString) + 1);
   if(SUCCEEDED(retc)) strcpy(buf, lpszString);
   if(SUCCEEDED(retc)) CutInitTrailSpcs(buf);

   if((pntd==NULL) && SUCCEEDED(retc))
   {
      units=(const unsigned char *)"%";
      pntd=strstr(lpszString, units);
   }

   if((pntd==NULL) && SUCCEEDED(retc))
   {
      units=(const unsigned char *)"mm";
      pntd=strstr(lpszString, units);
   }

   if((pntd==NULL) && SUCCEEDED(retc))
   {
      units=(const unsigned char *)"cm";
      pntd=strstr(lpszString, units);
   }

   if((pntd==NULL) && SUCCEEDED(retc))
   {
      units=(const unsigned char *)"pt";
      pntd=strstr(lpszString, units);
   }

   if((pntd!=NULL) && SUCCEEDED(retc))
   {
      if(strcmp(pntd, units)!=0) retv=False;
      *pntd=Nul;
   }

   if(retv && SUCCEEDED(retc))
   {
      CutInitTrailSpcs(buf);
      retv=TvIsNumber(buf);
   }

   KP_DELETEA(buf);

return(retv);
}


bool TvIsHexNum(const unsigned char *lpszHexString)
{
return(SUCCEEDED(TestAllowed(lpszHexString, (const unsigned char *)"0123456789ABCDEFabcdef")));
}


bool TvIsOctNum(const unsigned char *lpszOctString)
{
return(SUCCEEDED(TestAllowed(lpszOctString, (const unsigned char *)"01234567")));
}


bool TvIsRomanNumber(const unsigned char *lpszRomanString)
{
return(SUCCEEDED(TestAllowed(lpszRomanString, (const unsigned char *)"IVXLCM")));
}


// --------------------------------------------------
bool TvIsColor(const unsigned char *lpszParVal)
{
HRESULT retc=S_OK;
bool retv=False;
int p_ix;

   if(lpszParVal==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszParVal)==7)
      {
         if((lpszParVal[0]=='#') && TvIsHexNum(lpszParVal+1)) retv=True;
      }
      else if(strlen(lpszParVal)==6)
      {
         if(TvIsHexNum(lpszParVal)) retv=True;
      }
   }

   if((!retv) && SUCCEEDED(retc))
   {
      retc = GetKwrdIndex(&p_ix, lpszParVal, ColorNames, -1, False, True);

      if(SUCCEEDED(retc)) if(p_ix >= 0) retv = True;
   }

return(retv);
}


// ================================================== integer conversations
// -------------------------------------------
#if FALSE
long labs(long arg)
{
long retval;

   if(arg>=0L) retval=arg;
   else retval=(-arg);

return(retval);
}
#endif


/*---------------------*/
unsigned char *itooct(unsigned long val, unsigned char *buf, int posnum)
{
HRESULT retc=S_OK;
unsigned long ii;
int jj;

   if(buf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ii=val;
      jj=posnum;
      if(0==jj) jj=12;
      buf[jj]=0;
      while(ii)
      {
         buf[--jj]=(unsigned char)(ii&07)|'0';
         ii=(ii>>3)&017777;
      }
      if(0!=posnum) while(jj>0) buf[--jj]='0';
      strcpy(buf,buf+jj);
   }

return(buf);
}


// --------------------------------------------------
HRESULT ScanRoman(const unsigned char *lpszRomanNumber, int *piArabicNumber)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   if((piArabicNumber==NULL) || (lpszRomanNumber==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piArabicNumber=0;
      pnts=lpszRomanNumber;
   }

   if(SUCCEEDED(retc)) while((*pnts) && SUCCEEDED(retc))
   {
      switch(*pnts)
      {
         case 'I':
            (*piArabicNumber)++;
            break;

         case 'V':
            if(*piArabicNumber<=1/*3*/) *piArabicNumber=(-(*piArabicNumber));
            if((*piArabicNumber>1/*3*/) && (*piArabicNumber<5))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) (*piArabicNumber)+=5;
            break;

         case 'X':
            if(*piArabicNumber<=1/*8*/) *piArabicNumber=(-(*piArabicNumber));
            if((*piArabicNumber>1/*8*/) && (*piArabicNumber<10))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) (*piArabicNumber)+=10;
            break;

         case 'L':
         case 'C':
         case 'M':
//          retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
            retc=E_NOTIMPL;
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      pnts++;
   }

return(retc);
}


// --------------------------------------------------
HRESULT FormatRoman(unsigned char *lpszRomanNumber, int iArabicNumber)
{
HRESULT retc=S_OK;
unsigned char *pntd;
int ii, ii1, ii5, ii10;

   if(lpszRomanNumber==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(iArabicNumber>=40)
      {
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, False, __FILE__, __LINE__, 0L);
         strcpy(lpszRomanNumber, "???");
      }
      else
      {
         pntd=lpszRomanNumber;

         ii1=iArabicNumber%5;
         ii5=(iArabicNumber/5)%2;
         ii10=(iArabicNumber/10)%5;

         for(ii=0; ii<ii10; ii++) *(pntd++)='X';
         if(ii5)
         {
            if(ii1<4)
            {
               *(pntd++)='V';
               for(ii=0; ii<ii1; ii++) *(pntd++)='I';
            }
            else
            {
               *(pntd++)='I';
               *(pntd++)='X';
            }
         }
         else
         {
            if(ii1<4)
               for(ii=0; ii<ii1; ii++) *(pntd++)='I';
            else
            {
               *(pntd++)='I';
               *(pntd++)='V';
            }
         }

         *pntd=Nul;

      } // else if(iArabicNumber>=40)

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT SkipCr(unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=pntd=lpszString;
      while(*pnts)
      {
         if(*pnts!=Cr) *(pntd++)=(*pnts);
         pnts++;
      }
      *pntd=Nul;
   }

return(retc);
}


// --------------------------------------------------
KpChar iazLitChars[] =
{
   C_A_Ogon,         // 259 /* A, */
   C_a_Ogon,         // 260 /* a, */
   C_C_Car,          // 273 /* Cv */
   C_c_Car,          // 274 /* cv */
   C_E_Adot,         // 267 /* E. */
   C_e_Adot,         // 268 /* e. */
   C_E_Ogon,         // 261 /* E, */
   C_e_Ogon,         // 262 /* e, */
   C_I_Ogon,         // 263 /* I, */
   C_i_Ogon,         // 264 /* i, */
   C_S_Car,          // 285 /* Sv */
   C_s_Car,          // 286 /* sv */
   C_U_Ogon,         // 265 /* U, */
   C_u_Ogon,         // 266 /* u, */
   C_U_Macr,         // 299 /* U_ */
   C_u_Macr,         // 300 /* u_ */
   C_Z_Car,          // 289 /* Zv */
   C_z_Car,          // 290 /* zv */

   C_A_Grave,        // 337 /* A` */
   C_a_Grave,        // 338 /* a` */
   C_E_Grave,        // 339 /* E` */
   C_e_Grave,        // 340 /* e` */
   C_I_Grave,        // 341 /* I` */
   C_i_Grave,        // 342 /* i` */
   C_O_Grave,        // 343 /* O` */
   C_o_Grave,        // 344 /* o` */
   C_U_Grave,        // 345 /* U` */
   C_u_Grave,        // 346 /* u` */

   C_A_Acute,        // 347 /* A' */
   C_a_Acute,        // 348 /* a' */
   C_E_Acute,        // 351 /* E' */
   C_e_Acute,        // 352 /* e' */
   C_I_Acute,        // 353 /* I' */
   C_i_Acute,        // 354 /* i' */
   C_O_Acute,        // 359 /* O' */
   C_o_Acute,        // 360 /* o' */
   C_U_Acute,        // 365 /* U' */
   C_u_Acute,        // 366 /* u' */
   C_Y_Acute,        // 367 /* Y' */
   C_y_Acute,        // 368 /* y' */

   C_A_Tilde,        // 377 /* A~ */
   C_a_Tilde,        // 378 /* a~ */
   C_N_Tilde,        // 379 /* N~ */
   C_n_Tilde,        // 380 /* n~ */
   C_O_Tilde,        // 381 /* O~ */
   C_o_Tilde,        // 382 /* o~ */

   C_Y_Grave,        // 558 // Y`
   C_y_Grave,        // 559 // y`
   C_E_Tilde,        // 560 // E~
   C_e_Tilde,        // 561 // e~
   C_I_Tilde,        // 562 // I~
   C_i_Tilde,        // 563        // i~
   C_U_Tilde,        // 564 // U~
   C_u_Tilde,        // 565 // u~
   C_Y_Tilde,        // 566 // Y~
   C_y_Tilde,        // 567 // y~
   C_L_Tilde,        // 568 // L~
   C_l_Tilde,        // 569 // l~
   C_M_Tilde,        // 570 // M~
   C_m_Tilde,        // 571 // m~
   C_R_Tilde,        // 572 // R~
   C_r_Tilde,        // 573 // r~
   C_A_Ogon_Acute,   // 574
   C_a_Ogon_Acute,   // 575
   C_E_Ogon_Acute,   // 576
   C_e_Ogon_Acute,   // 577
   C_E_Adot_Acute,   // 578
   C_e_Adot_Acute,   // 579
   C_I_Ogon_Acute,   // 580
   C_i_Ogon_Acute,   // 581
   C_U_Ogon_Acute,   // 582
   C_u_Ogon_Acute,   // 583
   C_U_Macr_Acute,   // 584
   C_u_Macr_Acute,   // 585
   C_A_Ogon_Grave,   // 586
   C_a_Ogon_Grave,   // 587
   C_E_Ogon_Grave,   // 588
   C_e_Ogon_Grave,   // 589
   C_E_Adot_Grave,   // 590
   C_e_Adot_Grave,   // 591
   C_I_Ogon_Grave,   // 592
   C_i_Ogon_Grave,   // 593
   C_U_Ogon_Grave,   // 594
   C_u_Ogon_Grave,   // 595
   C_U_Macr_Grave,   // 596
   C_u_Macr_Grave,   // 597
   C_A_Ogon_Tilde,   // 598
   C_a_Ogon_Tilde,   // 599
   C_E_Ogon_Tilde,   // 600
   C_e_Ogon_Tilde,   // 601
   C_E_Adot_Tilde,   // 602
   C_e_Adot_Tilde,   // 603
   C_I_Ogon_Tilde,   // 604
   C_i_Ogon_Tilde,   // 605
   C_U_Ogon_Tilde,   // 606
   C_u_Ogon_Tilde,   // 607
   C_U_Macr_Tilde,   // 608
   C_u_Macr_Tilde,   // 609

   C_Nul
};

KpChar iazPolChars[] =
{
   C_A_Ogon,         // 259 /* A, */
   C_a_Ogon,         // 260 /* a, */
   C_C_Acute,        // 349 /* C' */
   C_c_Acute,        // 350 /* c' */
   C_E_Ogon,         // 261 /* E, */
   C_e_Ogon,         // 262 /* e, */
   C_L_Slash,        // 383 /* L/ */
   C_l_Slash,        // 384 /* l/ */
   C_N_Acute,        // 357 /* N' */
   C_n_Acute,        // 358 /* n' */
   C_O_Acute,        // 359 /* O' */
   C_o_Acute,        // 360 /* o' */
   C_S_Acute,        // 363 /* S' */
   C_s_Acute,        // 364 /* s' */
   C_Z_Acute,        // 369 /* Z' */
   C_z_Acute,        // 370 /* z' */
   C_Z_Adot,         // 269 /* Z. */
   C_z_Adot,         // 270 /* z. */

   C_W,
   C_w,

   C_Nul
};

KpChar iazGerChars[] =
{
   C_A_Diaer,        // 301 /* A.. */
   C_a_Diaer,        // 302 /* a.. */
   C_O_Diaer,        // 307 /* O.. */
   C_o_Diaer,        // 308 /* o.. */
   C_U_Diaer,        // 309 /* U.. */
   C_u_Diaer,        // 310 /* u.. */

   C_ss,             // 134 /* sharp s (german, C_beta) */

   C_W,
   C_w,
   C_Q,
   C_q,
   C_X,
   C_x,

   C_Nul
};

KpChar iazRusChars[] =
{
   C_A_Cyr,          // 135
   C_B_Cyr,          // 136
   C_V_Cyr,          // 137
   C_G_Cyr,          // 138
   C_D_Cyr,          // 139
   C_E_Cyr,          // 140
   C_Zh_Cyr,         // 141
   C_Z_Cyr,          // 142
   C_I_Cyr,          // 143
   C_J_Cyr,          // 144
   C_K_Cyr,          // 145
   C_L_Cyr,          // 146
   C_M_Cyr,          // 147
   C_N_Cyr,          // 148
   C_O_Cyr,          // 149
   C_P_Cyr,          // 150
   C_R_Cyr,          // 151
   C_S_Cyr,          // 152
   C_T_Cyr,          // 153
   C_U_Cyr,          // 154
   C_F_Cyr,          // 155
   C_H_Cyr,          // 156
   C_C_Cyr,          // 157
   C_Ch_Cyr,         // 158
   C_Sh_Cyr,         // 159
   C_Shch_Cyr,       // 160
   C_Hard_Cyr,       // 161
   C_Y_Cyr,          // 162
   C_Soft_Cyr,       // 163
   C_Ee_Cyr,         // 164
   C_Yu_Cyr,         // 165
   C_Ya_Cyr,         // 166

   C_a_Cyr,          // 167
   C_b_Cyr,          // 168
   C_v_Cyr,          // 169
   C_g_Cyr,          // 170
   C_d_Cyr,          // 171
   C_e_Cyr,          // 172
   C_zh_Cyr,         // 173
   C_z_Cyr,          // 174
   C_i_Cyr,          // 175
   C_j_Cyr,          // 176
   C_k_Cyr,          // 177
   C_l_Cyr,          // 178
   C_m_Cyr,          // 179
   C_n_Cyr,          // 180
   C_o_Cyr,          // 181
   C_p_Cyr,          // 182
   C_r_Cyr,          // 183
   C_s_Cyr,          // 184
   C_t_Cyr,          // 185
   C_u_Cyr,          // 186
   C_f_Cyr,          // 187
   C_h_Cyr,          // 188
   C_c_Cyr,          // 189
   C_ch_Cyr,         // 190
   C_sh_Cyr,         // 191
   C_shch_Cyr,       // 192
   C_hard_Cyr,       // 193
   C_y_Cyr,          // 194
   C_soft_Cyr,       // 195
   C_ee_Cyr,         // 196
   C_yu_Cyr,         // 197
   C_ya_Cyr,         // 198

   C_A_Cyr_Acute,    // 765
   C_E_Cyr_Acute,    // 766
   C_I_Cyr_Acute,    // 767
   C_O_Cyr_Acute,    // 768
   C_U_Cyr_Acute,    // 769
   C_Y_Cyr_Acute,    // 770
   C_Ee_Cyr_Acute,   // 771
   C_Yu_Cyr_Acute,   // 772
   C_Ya_Cyr_Acute,   // 773

   C_a_Cyr_Acute,    // 774
   C_e_Cyr_Acute,    // 775
   C_i_Cyr_Acute,    // 776
   C_o_Cyr_Acute,    // 777
   C_u_Cyr_Acute,    // 778
   C_y_Cyr_Acute,    // 779
   C_ee_Cyr_Acute,   // 780
   C_yu_Cyr_Acute,   // 781
   C_ya_Cyr_Acute,   // 782

   C_Nul
};

HRESULT TestLang(const KpChar *piazInStr, int iLangId, bool *pbFound)
{
HRESULT retc=S_OK;
const KpChar *pnts;
const KpChar *test_str;

   if((piazInStr==NULL) || (pbFound==NULL) ||
      ((iLangId!=KP_LNG_LIT) && (iLangId!=KP_LNG_LIX) && (iLangId!=KP_LNG_LIS) && (iLangId!=KP_LNG_ENG) && (iLangId!=KP_LNG_GER) && (iLangId!=KP_LNG_FRE) && (iLangId!=KP_LNG_POL) && (iLangId!=KP_LNG_RUS))
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbFound=False;
      pnts=piazInStr;

      while((!(*pbFound)) && (*pnts) && SUCCEEDED(retc))
      {
         switch(iLangId)
         {
         case KP_LNG_LIT:
         case KP_LNG_LIS:
         case KP_LNG_LIX: test_str=iazLitChars; break;
         case KP_LNG_GER: test_str=iazGerChars; break;
         case KP_LNG_RUS: test_str=iazRusChars; break;
         case KP_LNG_POL: test_str=iazPolChars; break;
         default:
            retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
            break;
         }

         if(SUCCEEDED(retc))
            if(TvKpStrChr(test_str, *pnts)!=NULL) *pbFound=True;

         pnts++;
      }
   }

return(retc);
}


// -------------------------
int *TvCleanCtrls(int *iazStr)
{
HRESULT retc=S_OK;
int *pnts;
int *pntd;

   if(iazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=pntd=iazStr;

      while(*pnts)
      {
         switch(*pnts)
         {
         case C_hyph:
            break;
         case C_Lf:
         case C_Ht:
         case C_Vt:
            *(pntd++)=(*pnts);
            break;
         default:
            if((*pnts)>=C_Spc) *(pntd++)=(*pnts);
            break;
         }
         pnts++;
      }

      *pntd=C_Nul;
   }

return(iazStr);
}


// -------------------------
unsigned char *TvCleanSpch(unsigned char *lpszStr)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if(lpszStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=pntd=lpszStr;

      while(*pnts)
      {
         if(
            TvIsAlpha((KpChar)*pnts) ||
            (*pnts==C_Spc) // ||
//          (*pnts==EXACT_ENTRY_CHR) || // '#'
//          (*pnts==WORD_START_CHR) ||  // '.'
//          (*pnts==DOUBLE_ENTRIES_CHR) || // '*'
//          (*pnts==DOUBLE_ENTRIES_CHR16) // C_Bpoint, bullet
           )
            *(pntd++)=(*pnts);

         pnts++;
      }

      *pntd=Nul;
   }

return(lpszStr);
}


// -------------------------
#define URL_HEX_WDT 2
HRESULT ScanHexUrl(unsigned char *lpszURL)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char hex_buf[URL_HEX_WDT+1];
int ch;
int ii;

   if(lpszURL==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=pntd=lpszURL;
      while(*pnts)
      {
         switch(*pnts)
         {
         case '@': // '%'
            pnts++;
            for(ii=0; ii<URL_HEX_WDT; ii++)
            {
               if(*pnts==Nul)
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszURL, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) hex_buf[ii]=(*pnts++);
            }

            if(SUCCEEDED(retc))
            {
               hex_buf[URL_HEX_WDT]=Nul;
               if(!TvIsHexNum(hex_buf))
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszURL, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               sscanf((char *)hex_buf, "%x", &ch);
               *(pntd++)=ch;
            }
            break;
         case '^':
            pnts++;
            *(pntd++)='%';
            break;
         default:
            *(pntd++)=(*pnts++);
            break;
         }
      }

      *pntd=Nul;
   }

return(retc);
}


HRESULT EncodeText(unsigned char *lpszString)
{
HRESULT retc = S_OK;
unsigned char *pnts;

   KP_ASSERT(lpszString, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszString;
      while(*pnts)
      {
         if((*pnts < Spc) || (*pnts >= 127)) *pnts = '?';
         else (*pnts) = 126 - (*pnts - Spc);
         pnts++;
      }
   }

return(retc);
}


HRESULT DecodeText(unsigned char *lpszString)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszString;
      while(*pnts)
      {
         if(*pnts!='?') (*pnts)=126-(*pnts-Spc);
         pnts++;
      }
   }

return(retc);
}


// ---------------------------------- Ascii85 coding
// source http://www.stillhq.com/cgi-bin/cvsweb/ascii85/

// ---------------------------------- Ascii85 decoding
static unsigned long pow85[] = {
        85*85*85*85, 85*85*85, 85*85, 85, 1
};


HRESULT A85decoder::wput(int iBytes)
{
HRESULT retc=S_OK;

  switch (iBytes)
  {
  case 4:
     m_sOutStr+=(char)(m_lTuple >> 24);
     m_sOutStr+=(char)(m_lTuple >> 16);
     m_sOutStr+=(char)(m_lTuple >>  8);
     m_sOutStr+=(char)(m_lTuple);
     break;
  case 3:
     m_sOutStr+=(char)(m_lTuple >> 24);
     m_sOutStr+=(char)(m_lTuple >> 16);
     m_sOutStr+=(char)(m_lTuple >>  8);
     break;
  case 2:
     m_sOutStr+=(char)(m_lTuple >> 24);
     m_sOutStr+=(char)(m_lTuple >> 16);
     break;
  case 1:
     m_sOutStr+=(char)(m_lTuple >> 24);
     break;
  }

return(retc);
}


A85decoder::A85decoder(/* const */ KpString *psA85Str)
{
   m_lhOpenResult=S_OK;
   m_lTuple = 0L;
   m_iCount = 0;
   m_lpszPnts = NULL;
   
// ----------------------------
   if(psA85Str==NULL)
   {
      m_lhOpenResult=E_INVALIDARG;
#ifdef Debug
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(m_lhOpenResult))
   {
#if (CompilerGr==Mingw) || (__WATCOMC__ >= 1202)
//    KP_DELETEA(m_lpszPnts);
      m_lpszPnts = psA85Str->ExtractValueA();
#else
      m_lpszPnts = *psA85Str;
#endif

      if(m_lpszPnts==NULL)
      {
         m_lhOpenResult=E_INVALIDARG;
#ifdef Debug
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   }

// ----------------------------
   if(SUCCEEDED(m_lhOpenResult)) if(*m_lpszPnts++ != '<')
   {
      m_lhOpenResult=KP_E_FILE_FORMAT;
#ifdef Debug
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }
   if(SUCCEEDED(m_lhOpenResult)) if(*m_lpszPnts++ != '~')
   {
      m_lhOpenResult=KP_E_FILE_FORMAT;
#ifdef Debug
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }
}


A85decoder::~A85decoder()
{
#if (CompilerGr==Mingw)
// KP_DELETEA(m_lpszPnts);
#endif
   m_lpszPnts = NULL;
}


HRESULT A85decoder::GetOpenResult(void)
{
return(m_lhOpenResult);
}


HRESULT A85decoder::Process(void)
{
HRESULT retc=S_OK;
int ch;

   if(m_lpszPnts==NULL)
   {
      retc=KP_E_ILLFUNC;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(retc))
   {
      while(*m_lpszPnts && SUCCEEDED(retc))
      {
         ch = *m_lpszPnts++;
         switch (ch)
         {
         default:
            if (ch < '!' || ch > 'u')
            {
               retc=KP_E_FILE_FORMAT; // bad character in ascii85 region
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            if(SUCCEEDED(retc))
            {
               m_lTuple += (ch - '!') * pow85[m_iCount++];
               if (m_iCount == 5)
               {
                  wput(4);
                  m_iCount = 0;
                  m_lTuple = 0L;
               }
            }
            break;

         case 'z':
            if (m_iCount != 0)
            {
               retc=KP_E_FILE_FORMAT; // z inside ascii85 5-tuple
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            if(SUCCEEDED(retc))
            {
//             m_sOutStr+='\0';
//             m_sOutStr+='\0';
//             m_sOutStr+='\0';
//             m_sOutStr+='\0';
               retc=KP_E_FILE_FORMAT; // null bytes in text mode
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            break;

         case '~':
            if (*m_lpszPnts++ != '>')
            {
               retc=KP_E_FILE_FORMAT; // ~ without > in ascii85 section
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            if(SUCCEEDED(retc)) if (*m_lpszPnts)
            {
               retc=KP_E_FILE_FORMAT; // characters after ~> in ascii85 section
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(retc, m_lpszPnts, True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            if(SUCCEEDED(retc))
            {
               if (m_iCount > 0)
               {
                  m_iCount--;
                  m_lTuple += pow85[m_iCount];
                  wput(m_iCount);
               }
            }
            break;

         case '\n': case '\r': case '\t': case ' ':
         /* case '\0': */ case '\f': case '\b': case 0177:
            break;

         } // switch (ch)

      } // while(*m_lpszPnts && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

return(retc);
}


HRESULT A85decoder::RetrieveResult(KpString *psOutStr)
{
HRESULT retc=S_OK;

   if((psOutStr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(retc)) *psOutStr = m_sOutStr;

return(retc);
}


HRESULT A85toStr(KpString *psOutStr, /* const */ KpString sA85Str)
{
HRESULT retc=S_OK;
A85decoder dec(&sA85Str);

   if((psOutStr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(retc)) retc=dec.GetOpenResult();
   if(SUCCEEDED(retc)) retc=dec.Process();
   if(SUCCEEDED(retc)) retc=dec.RetrieveResult(psOutStr);

return(retc);
}


// ---------------------------------- Ascii85 encoding
HRESULT A85encoder::encode(void)
{
HRESULT retc=S_OK;
int ii;
unsigned char buf[5];
unsigned char *pntd = buf;
unsigned long tuple=m_lTuple;

   ii = 5;
   do
   {
      *pntd++ = (unsigned char)(tuple % 85);
      tuple /= 85;
   } while (--ii > 0);
   ii = m_iCount;
   do
   {
      m_sOutStr += (char)(*--pntd + '!');
//    if (m_lPos++ >= m_lWidth)
//    {
//       m_lPos = 0;
//       m_sOutStr += '\n';
//    }
   } while (ii-- > 0);

return(retc);
}


// ------------------------------
void A85encoder::InitMembers(void)
{
   m_lhOpenResult = S_OK;
   m_iCount = 0;
   m_lTuple = 0L;
   m_lPos = 2L;
   m_lWidth = 72L;
   m_sOutStr = "<~";
   m_iInBufLen = 0;

#if CompilerGr==Mingw
// KP_DELETEA(m_lpszPnts);
#endif
   m_lpszPnts = NULL;
}


A85encoder::A85encoder(/* const */ KpString *psInStr)
{
   InitMembers();

   if(psInStr == NULL)
   {
      m_lhOpenResult = E_INVALIDARG;
#ifdef Debug
      m_lhOpenResult = KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(m_lhOpenResult))
   {
#if (CompilerGr==Mingw) || (__WATCOMC__ >= 1202)
//    KP_DELETEA(m_lpszPnts);
      m_lpszPnts = psInStr->ExtractValueA();
#else
      m_lpszPnts = *psInStr;
#endif

      if(m_lpszPnts==NULL)
      {
         m_lhOpenResult = E_INVALIDARG;
#ifdef Debug
         m_lhOpenResult = KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   }

   if(SUCCEEDED(m_lhOpenResult)) m_iInBufLen = strlen(m_lpszPnts);
}


A85encoder::A85encoder(const UniChar *psaInStr)
{
   InitMembers();

   if(psaInStr == NULL)
   {
      m_lhOpenResult = E_INVALIDARG;
#ifdef Debug
      m_lhOpenResult = KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(m_lhOpenResult))
   {
      m_lpszPnts = (const /* unsigned */ char *)psaInStr;

      m_iInBufLen = wcslen(psaInStr) * sizeof(UniChar);
   }
}


HRESULT A85encoder::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// ---------------------------------------
HRESULT A85encoder::Process(void)
{
HRESULT retc=S_OK;
unsigned char ch;
int ll;

   if(m_lpszPnts==NULL)
   {
      retc=KP_E_ILLFUNC;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   ll = m_iInBufLen;
   if(SUCCEEDED(retc)) while((ll--) /* *m_lpszPnts */ && SUCCEEDED(retc))
   {
      ch = *m_lpszPnts++;

      switch(m_iCount++)
      {
      case 0: m_lTuple |= (ch << 24); break;
      case 1: m_lTuple |= (ch << 16); break;
      case 2: m_lTuple |= (ch <<  8); break;
      case 3:
         m_lTuple |= ch;
         if (m_lTuple == 0L)
         {
            m_sOutStr += 'z';
//          if (m_lPos++ >= m_lWidth)
//          {
//             m_lPos = 0L;
//             m_sOutStr += '\n';
//          }
         } else
         retc=encode();

         m_lTuple = 0L;
         m_iCount = 0;
         break;
      }
   }

return(retc);
}


HRESULT A85encoder::RetrieveResult(KpString *psOutA85Str)
{
HRESULT retc=S_OK;

   if((psOutA85Str==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if((m_lpszPnts!=NULL) && SUCCEEDED(retc))
   {
        if(m_iCount > 0L) encode();
//      if(m_lPos + 2 > m_lWidth) m_sOutStr += '\n';
        m_sOutStr += "~>"; // "~>\n";

#if CompilerGr==Mingw
//    KP_DELETEA(m_lpszPnts);
#endif
      m_lpszPnts=NULL;
   }

   if(SUCCEEDED(retc)) *psOutA85Str = m_sOutStr;

return(retc);
}


HRESULT StrToA85(KpString *psOutA85Str, /* const */ KpString sInStr)
{
HRESULT retc=S_OK;
A85encoder enc(&sInStr);

   if((psOutA85Str==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(retc)) retc=enc.GetOpenResult();
   if(SUCCEEDED(retc)) retc=enc.Process();
   if(SUCCEEDED(retc)) retc=enc.RetrieveResult(psOutA85Str);

return(retc);
}


HRESULT UniStrToA85(KpString *psOutA85Str, const UniChar *psaInUniStr)
{
HRESULT retc=S_OK;
A85encoder enc(psaInUniStr);

   if((psOutA85Str==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

   if(SUCCEEDED(retc)) retc=enc.GetOpenResult();
   if(SUCCEEDED(retc)) retc=enc.Process();
   if(SUCCEEDED(retc)) retc=enc.RetrieveResult(psOutA85Str);

return(retc);
}


// --------------------------------- hyphenation
HRESULT KpWordHyphenate(KpChar *aizWord)
{
HRESULT retc = S_OK;
static KpChar word[KP_MAX_FILE_LIN_WDT+1];
static KpChar new_word[KP_MAX_FILE_LIN_WDT+1];
KpChar *pnto = NULL;
KpChar *pnts = NULL;
KpChar *pntd = NULL;

   if((aizWord == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) if(TvKpStrLen(aizWord) >= KP_MAX_FILE_LIN_WDT)
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

// _od· kopijuojam · word[], palikdami tik raides
// TODO: ignoruoti ir tagus (kaip XML-inius, taip ir tex/rtf-nius) (o gal jau veikia? juk ne raidÎs?)
   if(SUCCEEDED(retc))
   {
      pnts = aizWord;
      pntd = word;

      while((*pnts) && SUCCEEDED(retc))
      {
         if(TvIsAlpha(*pnts)) *pntd++ = *pnts;
         pnts++;
      }
      if(SUCCEEDED(retc)) *pntd = C_Nul;
   }
   if(SUCCEEDED(retc)) TvKpStrClearAccents(word);

// skiemenuojam per wordbuf[]
   if(SUCCEEDED(retc)) if(TvKpStrLen(word) >= FileLinLen)
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
   {
      retc = KptStrDecode(wordbuf, word, TV_MAIN_CTBL);
      if(FAILED(retc))
         retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) hyprun();

   if(SUCCEEDED(retc)) if(strlen(wordbuf) >= KP_MAX_FILE_LIN_WDT)
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      retc = KptStrEncode(word, wordbuf, TV_MAIN_CTBL);
      if(FAILED(retc))
         retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

// apjungiam skiemenuot‡ _od· su originaliais spec. simboliais
   if(SUCCEEDED(retc))
   {
      pnto = aizWord;
      pnts = word;
      pntd = new_word;

      while((*pnto || *pnts) && SUCCEEDED(retc))
      {
// spec. simbolius tiesiai · rezultato _od·
         while(*pnto && (!TvIsAlpha(*pnto)) && SUCCEEDED(retc))
         {
            if(((pntd - new_word) >= KP_MAX_FILE_LIN_WDT) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) *pntd++ = *pnto++;
         }

// kÎlimo _enkl‡(us) · rezultato _od·
         while(*pnts && (*pnts == C_hyph) && SUCCEEDED(retc))
         {
            if(((pntd - new_word) >= KP_MAX_FILE_LIN_WDT) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) *pntd++ = *pnts++;
         }

// raides · rezultato _od·
         while(*pnto && TvIsAlpha(*pnto) && TvIsAlpha(*pnts) && SUCCEEDED(retc))
         {
            if(TvClearAccent(*pnto) != *pnts++)
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(((pntd - new_word) >= KP_MAX_FILE_LIN_WDT) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) *pntd++ = *pnto++;
         }
      }
      if(SUCCEEDED(retc)) *pntd = C_Nul;

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc)) TvKpStrCpy(aizWord, new_word);

return(retc);
}

HRESULT KpStrHyphenate(KpChar *aizSentence)
{
HRESULT retc = S_OK;
static KpChar word[KP_MAX_FILE_LIN_WDT+1];
static KpChar new_sentence[KP_MAX_FILE_LIN_LEN+1];
KpChar *pnts = NULL;
KpChar *pntd = NULL;
KpChar *pntr = NULL;
int ll;

   if((aizSentence == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      pnts = aizSentence;
      pntr = new_sentence;

      while(*pnts && SUCCEEDED(retc))
      {

// tarpus tiesiai · rezultato sakin·
// '(' atskyrÎjas (pvz., "pavienis(-Î)"), ')' - ne (pvz., "(pra-)pulti")
         while(*pnts && ((TvStrChr(lpszSpcEol, *pnts) != NULL) || (*pnts == C_Lpar)) && SUCCEEDED(retc))
         {
            if(((pntr - new_sentence) >= KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) *pntr++ = *pnts++;
         }

// _od· · word[]
// '(' atskyrÎjas
         pntd = word;
         while(*pnts && (TvStrChr(lpszSpcEol, *pnts) == NULL) && (*pnts != C_Lpar) && SUCCEEDED(retc))
         {
            if(((pntd - word) >= KP_MAX_FILE_LIN_WDT) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) *pntd++ = *pnts++;
         }
         if(SUCCEEDED(retc)) *pntd = C_Nul;

// unsigned char str_buf[KP_MAX_FILE_LIN_WDT];
// KptStrDecode(str_buf, word, TV_MAIN_CTBL);
// printf("%s\n", (const char *)str_buf);

// skiemenuojam _od·
         if((TvKpStrChr(word, C_hyph) == NULL) && SUCCEEDED(retc))  // neskiemenuojam jau suskiemenuot¯
         /* retc = */ KpWordHyphenate(word); // po klaid¯ nestabdom, tik perkopijuojam neliest‡ _od· atgal

// _od· prijungiam prie rezultato
         if(SUCCEEDED(retc))
         {
            ll = TvKpStrLen(word);
            if((pntr - new_sentence) + ll >= KP_MAX_FILE_LIN_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc))
         {
            TvKpStrCpy(pntr, word);
            pntr += ll;
         }

      } // while(*pnts && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      *pntr = C_Nul;
      TvKpStrCpy(aizSentence, new_sentence);
   }

return(retc);
}
