// ==================================================
// kpstring.cpp
// string processing
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#if Compiler != Watcom
#include <sstream>
#endif
#include <stdio.h>
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
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpsort.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvxml.h"

// ================================================== char string processing
// --------------------------------------------------
unsigned char *TvStrChr(const unsigned char *lpszString, KpChar iCh)
{
        const unsigned char *str_ptr;
        unsigned char *ret_ptr;

        str_ptr=lpszString;

        while((*str_ptr) && (*str_ptr!=iCh)) str_ptr++;
        if(*str_ptr!=Nul) ret_ptr=(unsigned char *)str_ptr;
        else ret_ptr=NULL;

        return(ret_ptr);
}


// --------------------------------------------------
unsigned char *TvStrChrArr(const unsigned char *lpszString, const unsigned char *lpszTestChars)
{
        const unsigned char *test_ptr;
        unsigned char *ret_ptr;

        test_ptr=lpszTestChars;
        ret_ptr=NULL;

        while(*test_ptr)
        {
                ret_ptr=TvStrChr(lpszString, (KpChar)(*test_ptr++));
                if(ret_ptr!=NULL) break;
        }

        return(ret_ptr);
}


// --------------------------------------------------
int TvStrCmp(const unsigned char *lpszStr1, const unsigned char *lpszStr2, bool bSkipSpc, int iSortLng, bool bCaseSens, int iCtbl, bool bRoundFlg)
{
int retv = 0;
HRESULT retc = S_OK;
const unsigned char *pnts1, *pnts2;
KpChar in_ch1, in_ch2;
int wgt1, wgt2;

   if(((lpszStr1 == NULL) || (lpszStr2 == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pnts1=lpszStr1;
   pnts2=lpszStr2;

   while(((*pnts1) || (*pnts2)) && (retv==0))
   {
      if(bSkipSpc)
      {
         if(*pnts1) while(((TvStrChr(lpszSpCharsSpcEol /* lpszSpChars */ /* lpszSpcEol */, (KpChar)*pnts1)!=NULL) || (*pnts1 == '\'')) && (*pnts1!=Nul)) pnts1++;
         if(*pnts2) while(((TvStrChr(lpszSpCharsSpcEol /* lpszSpChars */ /* lpszSpcEol */, (KpChar)*pnts2)!=NULL) || (*pnts2 == '\'')) && (*pnts2!=Nul)) pnts2++;
      }

      if((*pnts1) && (*pnts2))
      {
         retc=KptCharEncode(&in_ch1, *pnts1, iCtbl);
         if(retc==KP_E_UNKN_CHR)
         {
            retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            in_ch1=C_Quest; // '?'
         }

         retc=KptCharEncode(&in_ch2, *pnts2, iCtbl);
         if(retc==KP_E_UNKN_CHR)
         {
            retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            in_ch2=C_Quest; // '?'
         }

         wgt1 = iCharWeigths[in_ch1];
         wgt2 = iCharWeigths[in_ch2];

// if(((in_ch1 == '*') && (in_ch2 == '#')) || ((in_ch1 == '#') && (in_ch2 == '*')))
// printf("---- %c %c %d %d", in_ch1, in_ch2, wgt1, wgt2);

         if((iSortLng==KP_LNG_LIT) || (iSortLng==KP_LNG_LIX) || (iSortLng==KP_LNG_LIS))
         {
            if(wgt1/10000==C_Y) wgt1=C_I*10000+wgt1%10000;
            if(wgt1/10000==C_y) wgt1=C_i*10000+wgt1%10000;
            if(wgt2/10000==C_Y) wgt2=C_I*10000+wgt2%10000;
            if(wgt2/10000==C_y) wgt2=C_i*10000+wgt2%10000;
         }

         if(!bCaseSens)
         {
//          in_ch1=TvToLower(in_ch1);
//          in_ch2=TvToLower(in_ch2);
            wgt1 = ToLowWgt(wgt1);
            wgt2 = ToLowWgt(wgt2);
         }

         if(bRoundFlg)
         {
            if(iSortLng!=KP_LNG_LIS)
            {
               wgt1=RoundChWgt(wgt1);
               wgt2=RoundChWgt(wgt2);

               if(iSortLng==KP_LNG_LIX)
               {
                  wgt1-=wgt1%10000;
                  wgt2-=wgt2%10000;
               }
            }
         }

         if(wgt1 > wgt2) retv = 1;
         if(wgt1 < wgt2) retv = (-1);

// if(((in_ch1 == '*') && (in_ch2 == '#')) || ((in_ch1 == '#') && (in_ch2 == '*')))
// printf(" %d %d %d\n", wgt1, wgt2, retv);

         pnts1++;
         pnts2++;
      }
      else break;
   }

   if(retv==0)
   {
      if((*pnts1) && (*pnts2==Nul)) retv=1;
      if((*pnts1==Nul) && (*pnts2)) retv=(-1);
   }

return(retv);
}


// --------------------------------------------------
int TvStrCmpStrict_(const void *lpszStr1, const void *lpszStr2)
{
int retv=0;
HRESULT retc=S_OK;

   if((lpszStr1==NULL) || (lpszStr2==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retv=TvStrCmp((const unsigned char *)lpszStr1,
         (const unsigned char *)lpszStr2, False, SortMode,
         False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

   if((retv == 0) && SUCCEEDED(retc))
      retv=TvStrCmp((const unsigned char *)lpszStr1,
         (const unsigned char *)lpszStr2, False, SortMode,
         True, // False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

return(retv);
}


// --------------------------------------------------
int TvStrPtrCmpStrict(const void *plpszStr1, const void *plpszStr2)
{
int retv=0;
HRESULT retc=S_OK;

   if((plpszStr1==NULL) || (plpszStr2==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retv=TvStrCmp(*(const unsigned char **)plpszStr1,
         *(const unsigned char **)plpszStr2,
         False,
         SortMode,
         False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

   if((retv == 0) && SUCCEEDED(retc))
      retv=TvStrCmp(*(const unsigned char **)plpszStr1,
         *(const unsigned char **)plpszStr2,
         False,
         SortMode,
         True, // False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

return(retv);
}


int TvStrPtrCmpStrictRev(const void *plpszStr1, const void *plpszStr2)
{
return(-TvStrPtrCmpStrict(plpszStr1, plpszStr2));
}


// --------------------------------------------------
int TvStrPtrCmpStrictSkipSpcEx(const void *plpszStr1, const void *plpszStr2, bool bCutLastWord)
{
int retv=0;
HRESULT retc=S_OK;
unsigned char *str_buf_1 = NULL;
unsigned char *str_buf_2 = NULL;
int len1 = 0;
int len2 = 0;
unsigned char *pntd;

   if(((plpszStr1==NULL) || (plpszStr2==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((*(const unsigned char **)plpszStr1==NULL) || (*(const unsigned char **)plpszStr2==NULL))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) len1 = strlen(*(const unsigned char **)plpszStr1);
   KP_NEWA(str_buf_1, unsigned char, len1 + 1);
   if(SUCCEEDED(retc)) strcpy(str_buf_1, *(const unsigned char **)plpszStr1);

   if(SUCCEEDED(retc)) len2 = strlen(*(const unsigned char **)plpszStr2);
   KP_NEWA(str_buf_2, unsigned char, len2 + 1);
   if(SUCCEEDED(retc)) strcpy(str_buf_2, *(const unsigned char **)plpszStr2);

// -------------------- nukandam paskutini zodi - rusiuojant indexus ten buna lizdo id
   if(bCutLastWord && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         pntd = str_buf_1 + len1 -1;
         while(pntd >= str_buf_1)
         {
            if(*pntd == Spc)
            {
               *pntd = Nul;
               break;
            }
            pntd--;
         }
      }

      if(SUCCEEDED(retc))
      {
         pntd = str_buf_2 + len2 -1;
         while(pntd >= str_buf_2)
         {
            if(*pntd == Spc)
            {
               *pntd = Nul;
               break;
            }
            pntd--;
         }
      }
   }

// --------------------
   if(SUCCEEDED(retc))
      retv=TvStrCmp(str_buf_1, // *(const unsigned char **)plpszStr1,
         str_buf_2, // *(const unsigned char **)plpszStr2,
         True,
         SortMode,
         False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

   if((retv == 0) && SUCCEEDED(retc))
      retv=TvStrCmp(str_buf_1, // *(const unsigned char **)plpszStr1,
         str_buf_2, // *(const unsigned char **)plpszStr2,
         True,
         SortMode,
         True, // False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

   if((retv == 0) && SUCCEEDED(retc))
      retv=TvStrCmp(str_buf_1, // *(const unsigned char **)plpszStr1,
         str_buf_2, // *(const unsigned char **)plpszStr2,
         False, // True, // bool bSkipSpc
         SortMode,
         True, // False, // bool bCaseSens
         /* ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))? */ 71 /* :1 */, // TV_IX_CTBL
         True /* False */);

// --------------------
   KP_DELETEA(str_buf_2);
   KP_DELETEA(str_buf_1);

#if FALSE // #ifdef Debug
char str_buf[200];
sprintf(str_buf, ">>>%s<<< >>>%s<<< %d", *(const unsigned char **)plpszStr1, *(const unsigned char **)plpszStr2, retv);
KP_TRACE(str_buf);
#endif

return(retv);
}


int TvStrPtrCmpStrictSkipSpc(const void *plpszStr1, const void *plpszStr2)
{
return(TvStrPtrCmpStrictSkipSpcEx(plpszStr1, plpszStr2, False));
}


int TvStrPtrCmpStrictSkipSpcCutLastWord(const void *plpszStr1, const void *plpszStr2)
{
return(TvStrPtrCmpStrictSkipSpcEx(plpszStr1, plpszStr2, True));
}


int TvStrPtrCmpStrictRevSkipSpc(const void *plpszStr1, const void *plpszStr2)
{
return(-TvStrPtrCmpStrictSkipSpc(plpszStr1, plpszStr2));
}


// --------------------------------------------------
int TvStrMatch(const unsigned char *lpszStr1, const unsigned char *lpszStr2)
{
int retv=0;
HRESULT retc=S_OK;
const unsigned char *pnts1, *pnts2;

   if(((lpszStr1 == NULL) || (lpszStr2 == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pnts1=lpszStr1;
   pnts2=lpszStr2;

   while((*pnts1) || (*pnts2))
   {
      if(*pnts1 == *pnts2)
      {
         retv++;

         pnts1++;
         pnts2++;
      }
      else break;
   }

return(retv);
}


// ==================================================
// --------------------------------------------------
HRESULT CutTrailSpcs(unsigned char *lpszString, const unsigned char *spcs)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszString!=NULL)
   {
        pnts=lpszString+strlen((const char *)lpszString);

        while(pnts>lpszString)
           {
                --pnts;
//              if(*pnts != Spc)
                if(TvStrChr(spcs, *pnts) == NULL)
                {
                        pnts++;
                        break;
                }
        }

        *pnts=Nul;
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT CutInitSpcs(unsigned char *lpszString, const unsigned char *spcs)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if(lpszString!=NULL)
   {
      pntd=pnts=lpszString;

//    while(*pnts==Spc) pnts++;
      while(TvStrChr(spcs, *pnts)) pnts++;

      while(*pnts) *(pntd++)=(*pnts++);
      *pntd=Nul;
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT CutInitTrailSpcs(unsigned char *lpszString, const unsigned char *spcs)
{
HRESULT retc;

   retc=CutInitSpcs(lpszString, spcs);
   if(SUCCEEDED(retc)) retc=CutTrailSpcs(lpszString, spcs);

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpaces(unsigned char *lpszString)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if(lpszString!=NULL)
   {
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         while((*pnts) && (strchr((const char *)lpszSpcEol, *pnts)!=NULL)) pnts++;
         if(*pnts) *(pntd++) = (*pnts++);
      }

      *pntd=Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpacesCode(unsigned char *lpszString)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if(lpszString!=NULL)
   {
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         while((*pnts) && (strchr((const char *)lpszSpcEol, *pnts)!=NULL)) pnts++;
         if(*pnts == '\"')
         {
            *(pntd++) = (*pnts++);
            while(*pnts) // viduj kabuèiø
            {
               if(*pnts == '\"') // kabutës u_sidaro
               {
                  *(pntd++) = (*pnts++);
                  break;
               }
               else if(*pnts == '\\') *(pntd++) = (*pnts++); // escape simbolis
               if(*pnts) *(pntd++) = (*pnts++);
            }
         }
         else if(*pnts) *(pntd++) = (*pnts++);
      }

      *pntd=Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT ExtractStringLitteral(unsigned char *lpszStrBuffer, const unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;

   if(((lpszString == NULL) || (lpszStrBuffer == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      pnts = lpszString;
      pntd = lpszStrBuffer;

      if(*pnts++ != '\"')
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) while(*pnts)
   {
      if(*pnts == '\"') break;
      else if(*pnts == '\\') pnts++;
      if(*pnts) *pntd++ = *pnts++;
   }

   if(SUCCEEDED(retc)) *pntd = Nul;

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpCharsSpc(unsigned char *lpszString)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if(lpszString!=NULL)
   {
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         while((*pnts) && ((strchr((const char *)lpszSpCharsSpcEol /* lpszSpChars */, *pnts)!=NULL) || (*pnts < Spc))) pnts++;
         if(*pnts) *(pntd++)=(*pnts++);
      }

      *pntd=Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpKpCharsSpc(KpChar *iazString)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar *pntd;

   if(iazString!=NULL)
   {
      pnts=iazString;
      pntd=iazString;

      while(*pnts)
      {
         while((*pnts) && ((TvKpStrChr(iazSpCharsSpcEol, *pnts)!=NULL) || (*pnts < C_Spc))) pnts++;
         if(*pnts) *pntd++ = *pnts++;
      }

      *pntd=C_Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpCharsCom(unsigned char *lpszString)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;

   if(lpszString!=NULL)
   {
// --------------------------------- sutraukiam dvigubus tarpus

// KP_TRACE("----------------------------- Prieð SpcEolToSpc");
// KP_TRACE(lpszString)

      if(SUCCEEDED(retc)) retc = SpcEolToSpc(lpszString);

// KP_TRACE("----------------------------- Po SpcEolToSpc");
// KP_TRACE(lpszString)

// --------------------------------- iðmetam sutrumpinimus - _od_ius su taðkais gale
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         if(*pnts == '.')
         {
            while(pntd > lpszString)
            {
               if(*(pntd-1) == ' ') break;
               else pntd--;
            }
            pnts++;
         }
         else *pntd++ = *pnts++;
      }

      *pntd=Nul;

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = SpcEolToSpc(lpszString);

// --------------------------------- iðmetam skaitmenis, sp. chars, [...], -...
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         if(*pnts == '[')
         {
            while((*pnts) && (*pnts != ']')) pnts++;
            if(*pnts) pnts++;
         }
         else if(*pnts == ']') { pnts++; pntd = lpszString; }
         else if(*pnts == Spc) // ' '
         {
            *pntd++ = *pnts++; while(*pnts == Spc) pnts++; // ' '
            if(*pnts == '-') while((*pnts) && (*pnts != Spc)) pnts++;
         }
         else if(*pnts == '-')
         {
            if(pntd != lpszString) *pntd++ = *pnts++;
            else
            {
               while((*pnts) && (*pnts != Spc)) pnts++; // ' '
               while(*pnts == Spc) pnts++;
            }
         }
         else
         {
            while(
                  (*pnts) &&
                  (
//                   (strchr((const char *)lpszSpChars, *pnts)!=NULL) ||
//                   (*pnts < Spc) ||
                     ((*pnts < 'A') && (*pnts != Spc))
                  )
                 ) pnts++;
            if(*pnts) *pntd++ = *pnts++;
         }
      }

      *pntd=Nul;

// KP_TRACE(lpszString)

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = SpcEolToSpc(lpszString);

// ---------------------
#if FALSE // #ifdef Debug
stringstream str_stream;
#endif

#if FALSE // #ifdef Debug
KP_TRACE("-----------------------------");
pnts=lpszString;
while(*pnts)
{
str_stream.str("");
str_stream << hex << (int)*pnts << " " << *pnts;
KP_TRACE(KpString(str_stream.str()));
pnts++;
}
#endif

// --------------------------------- imetam pavienes raides
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         if((*pnts == Spc) && (*(pnts+1) != Spc) && (*(pnts+1))) // ' '
         {
            if((*(pnts+2) == Spc) || (*(pnts+2) == Nul)) pnts+=2; // ' '
            else *pntd++ = *pnts++;
         }
         else if((pntd == lpszString) /* (pnts == lpszString) */ && (*pnts != Spc) && (*pnts)) // ' '
         {
            if(*(pnts+1) == Spc) pnts+=2; // ' '
            else if(*(pnts+1) == Nul) pnts++;
            else *pntd++ = *pnts++;
         }
         else *pntd++ = *pnts++;
      }

      *pntd=Nul;

#if FALSE // #ifdef Debug
KP_TRACE("-----------------------------");
pnts=lpszString;
while(*pnts)
{
str_stream.str("");
str_stream << hex << (int)*pnts << " " << *pnts;
KP_TRACE(KpString(str_stream.str()));
pnts++;
}
#endif

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = SpcEolToSpc(lpszString);

   }

return(retc);
}


// --------------------------------------------------
HRESULT RemoveSpKpCharsCom(KpChar *iazString)
{
HRESULT retc=S_OK;
const KpChar *pnts;
KpChar *pntd;

   if(iazString!=NULL)
   {
// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(iazString);

// --------------------------------- iðmetam sutrumpinimus - _od_ius su taðkais gale
      pnts=iazString;
      pntd=iazString;

      while(*pnts)
      {
         if(*pnts == C_Point) // '.'
         {
            while(pntd > iazString)
            {
               if(*(pntd-1) == C_Spc) break; // ' '
               else pntd--;
            }
            pnts++;
         }
         else *pntd++ = *pnts++;
      }

      *pntd=C_Nul;

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(iazString);

// --------------------------------- iðmetam skaitmenis, sp. chars, [...], -...
      pnts=iazString;
      pntd=iazString;

      while(*pnts)
      {
         if(*pnts == C_Lbrack) // '['
         {
            while((*pnts) && (*pnts != C_Rbrack)) pnts++; // ']'
            if(*pnts) pnts++;
         }
         else if(*pnts == C_Rbrack) { pnts++; pntd = iazString; } // ']'
         else if(*pnts == C_Spc) // ' '
         {
            *pntd++ = *pnts++; while(*pnts == C_Spc) pnts++; // ' '
            if(*pnts == C_Dash) while((*pnts) && (*pnts != C_Spc)) pnts++; // '-' // ' '
         }
         else if(*pnts == C_Dash) // '-'
         {
            if(pntd != iazString) *pntd++ = *pnts++;
            else
            {
               while((*pnts) && (*pnts != C_Spc)) pnts++; // ' '
               while(*pnts == C_Spc) pnts++; // ' '
            }
         }
         else
         {
            while(
                  (*pnts) &&
                  (
//                   (TvKpStrChr(lpszSpChars, *pnts)!=NULL) ||
//                   (*pnts < C_Spc) || // ' '
                     ((*pnts < C_A) && (*pnts != C_Spc)) // 'A' // ' '
                  )
                 ) pnts++;
            if(*pnts) *pntd++ = *pnts++;
         }
      }

      *pntd=C_Nul;

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(iazString);

// --------------------------------- imetam pavienes raides
      pnts=iazString;
      pntd=iazString;

      while(*pnts)
      {
         if((*pnts == C_Spc) && (*(pnts+1) != C_Spc) && (*(pnts+1))) // ' '
         {
            if((*(pnts+2) == C_Spc) || (*(pnts+2) == Nul)) pnts+=2; // ' '
            else *pntd++ = *pnts++;
         }
         else if((pntd == iazString) /* (pnts == iazString) */ && (*pnts != C_Spc) && (*pnts)) // ' '
         {
            if(*(pnts+1) == C_Spc) pnts+=2; // ' '
            else if(*(pnts+1) == C_Nul) pnts++;
            else *pntd++ = *pnts++;
         }
         else *pntd++ = *pnts++;
      }

      *pntd=C_Nul;

// --------------------------------- sutraukiam dvigubus tarpus
      if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(iazString);

   }

return(retc);
}


// --------------------------------------------------
HRESULT SpcEolToSpc(unsigned char *lpszString)
{
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   if(lpszString!=NULL)
   {
      pnts=lpszString;
      pntd=lpszString;

      while(*pnts)
      {
         while(TvStrChr(lpszSpcEol, (KpChar)*pnts)!=NULL) pnts++;

         while((*pnts) && (TvStrChr(lpszSpcEol, (KpChar)*pnts)==NULL)) *(pntd++)=(*pnts++);

         if((*pnts) && TvStrChr(lpszSpcEol, (KpChar)*pnts)!=NULL){ *(pntd++)=Spc; pnts++; }
      }

      *pntd=Nul;
   }

return(CutTrailSpcs(lpszString));
}


// --------------------------------------------------
HRESULT KpSpcEolToSpc(KpChar *iazString)
{
const KpChar *pnts = NULL;
KpChar *pntd = NULL;

   if(iazString!=NULL)
   {
      pnts=iazString;
      pntd=iazString;

      while(*pnts)
      {
         while(TvKpStrChr(iazSpcEol, *pnts)!=NULL) pnts++;

         while((*pnts) && (TvKpStrChr(iazSpcEol, *pnts)==NULL)) *(pntd++)=(*pnts++);

         if((*pnts) && TvKpStrChr(iazSpcEol, *pnts)!=NULL){ *pntd++ = C_Spc; pnts++; }
      }

      *pntd=Nul;
   }

return(CutTrailSpcsKp(iazString));
}


HRESULT DoubleCrToSingle(unsigned char *lpszString)
{
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   if(lpszString != NULL)
   {
      pnts = lpszString;
      pntd = lpszString;

      while(*pnts != Nul)
         if((*pntd++ = *pnts++) == '\n')
            while(*pnts == '\n') pnts++;

      *pntd = Nul;
   }

return(S_OK);
}

// ==================================================
// --------------------------------------------------
unsigned char szSpcStr[]={"                                                   "};
unsigned char *TvSpcs(int iSpcCnt)
{
        unsigned char *pnts;
        int ii;

        pnts=szSpcStr;
        ii=strlen((const char *)szSpcStr);
        if(ii>=iSpcCnt) pnts=szSpcStr+ii-iSpcCnt;
        else
      /*retc=*/KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

        return(pnts);
}


unsigned char *DoubleEscape(unsigned char *lpszOutStr, const unsigned char *lpszInStr)
{
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   if(lpszOutStr && lpszInStr)
   {
      pnts = lpszInStr;
      pntd = lpszOutStr;

      while(*pnts)
      {
         switch(*pnts)
         {
         case '\"':
         case '\'':
         case '\\':
            *pntd++ = '\\';
            break;
         }
         *pntd++ = *pnts++;
      }
      *pntd = Nul;
   }

return(lpszOutStr);
}


// --------------------------------------------------
unsigned char *strcpy(unsigned char *dest, const unsigned char *src)
{
HRESULT retc = S_OK;
KP_ASSERT((src != null) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strcpy((char *)dest, (const char *)src));
}

unsigned char *strcpy(unsigned char *dest, const char *src)
{
HRESULT retc = S_OK;
KP_ASSERT((src != NULL) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strcpy((char *)dest, src));
}

unsigned char *strncpy(unsigned char *dest, const unsigned char *src, size_t nbytes)
{
HRESULT retc = S_OK;
KP_ASSERT((src != null) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strncpy((char *)dest, (const char *)src, nbytes));
}

unsigned char *strncpy(unsigned char *dest, const char *src, size_t nbytes)
{
HRESULT retc = S_OK;
KP_ASSERT((src != NULL) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strncpy((char *)dest, src, nbytes));
}

int /* size_t */ strlen(const unsigned char *src)
{
HRESULT retc = S_OK;
KP_ASSERT(src != null, E_POINTER, null, True);
return(strlen((const char *)src));
}

unsigned char *strcat(unsigned char *dest, const unsigned char *src)
{
HRESULT retc = S_OK;
KP_ASSERT((src != null) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strcat((char *)dest, (const char *)src));
}

unsigned char *strcat(unsigned char *dest, const char *src)
{
HRESULT retc = S_OK;
KP_ASSERT((src != NULL) && (dest != null), E_POINTER, null, True);
return((unsigned char *)strcat((char *)dest, src));
}

unsigned char *strchr(const unsigned char *src, unsigned char ch)
{
HRESULT retc = S_OK;
KP_ASSERT(src != null, E_POINTER, null, True);
return((unsigned char *)strchr((const char *)src, ch));
}

unsigned char *strstr(const unsigned char *src, const unsigned char *substr)
{
HRESULT retc = S_OK;
KP_ASSERT((src != null) && (substr != null), E_POINTER, null, True);
return((unsigned char *)strstr((const char *)src, (const char *)substr));
}

unsigned char *strstr(const unsigned char *src, const char *substr)
{
HRESULT retc = S_OK;
KP_ASSERT((src != null) && (substr != NULL), E_POINTER, null, True);
return((unsigned char *)strstr((const char *)src, substr));
}

int strcmp(const unsigned char *str1, const unsigned char *str2)
{
HRESULT retc = S_OK;
KP_ASSERT((str1 != null) && (str2 != null), E_POINTER, null, True);
return(strcmp((const char *)str1, (const char *)str2));
}

int strcmp(const unsigned char *str1, const char *str2)
{
HRESULT retc = S_OK;
KP_ASSERT((str1 != null) && (str2 != NULL), E_POINTER, null, True);
return(strcmp((const char *)str1, str2));
}

int strcmp(const char *str1, const unsigned char *str2)
{
HRESULT retc = S_OK;
KP_ASSERT((str1 != NULL) && (str2 != null), E_POINTER, null, True);
return(strcmp(str1, (const char *)str2));
}

// --------------------------------------------------
unsigned char *TvStrCpy(unsigned char *dest, const unsigned char *src)
{
const unsigned char *pnts;
unsigned char *pntd;

   pnts = src;
   pntd = dest;

   if(pnts && dest)
   {
      while(*pnts) *pntd++ = *pnts++;
      *pntd = Nul;
   }

return(dest);
}


// ================================================== KpChar string processing
// --------------------------------------------------
const KpChar *TvKpStrChr(const KpChar *iazString, KpChar iChar)
{
const KpChar *str_ptr;
const KpChar *ret_ptr;

        str_ptr=iazString;

        while((*str_ptr) && (*str_ptr!=iChar)) str_ptr++;
        if(*str_ptr!=C_Nul) ret_ptr=str_ptr;
        else ret_ptr=NULL;

return(ret_ptr);
}


// --------------------------------------------------
const KpChar *TvKpStrStr(const KpChar *piazSrc, const KpChar *piazSubStr)
{
const KpChar *retv=NULL;
int src_len;
int sub_len;
const KpChar *pnts;
const KpChar *pntb;
int ii;

   src_len=TvKpStrLen(piazSrc);
   sub_len=TvKpStrLen(piazSubStr);
   for(ii=0; ii<=src_len-sub_len; ii++)
   {
      pnts=piazSrc+ii;
      pntb=piazSubStr;
      while(*pntb)
      {
         if((*pnts)==(*pntb)){ pnts++; pntb++; }
         else break;
      }
      if((*pntb)==C_Nul)
      {
         retv=piazSrc+ii;
         break;
      }
   }

return(retv);
}


// --------------------------------------------------
int TvKpStrCmp(const KpChar *iazStr1, const KpChar *iazStr2, bool bDotLessToDot)
{
int retv=0;
const KpChar *pnts1, *pnts2;
KpChar ichar1, ichar2;
   pnts1=iazStr1;
   pnts2=iazStr2;

   while((*pnts1) && (*pnts2) && (retv==0))
   {
      ichar1 = *pnts1;
      ichar2 = *pnts2;

      if(bDotLessToDot)
      {
         switch(ichar1)
         {
            case C_i_Grave_Dotless: ichar1=C_i_Grave; break;
            case C_i_Acute_Dotless: ichar1=C_i_Acute; break;
            case C_i_Tilde_Dotless: ichar1=C_i_Tilde; break;
         }

         switch(ichar2)
         {
            case C_i_Grave_Dotless: ichar2=C_i_Grave; break;
            case C_i_Acute_Dotless: ichar2=C_i_Acute; break;
            case C_i_Tilde_Dotless: ichar2=C_i_Tilde; break;
         }
      }

      if((ichar1)>(ichar2)) retv=1;
      if((ichar1)<(ichar2)) retv=(-1);

      pnts1++;
      pnts2++;
   }

   if(retv==0)
   {
      if((*pnts1) && (*pnts2==C_Nul)) retv=1;
      if((*pnts1==C_Nul) && (*pnts2)) retv=(-1);
   }

return(retv);
}

int TvKpStrCmp(const KpChar *iazStr1, const KpChar *iazStr2)
{
return(TvKpStrCmp(iazStr1, iazStr2, False));
}


// --------------------------------------------------
KpChar *TvKpStrCpy(KpChar *iazStr1, const KpChar *iazStr2)
{
KpChar *pnts1;
const KpChar *pnts2;

        pnts1=iazStr1;
        pnts2=iazStr2;

        while(*pnts2) (*pnts1++)=(*pnts2++);
        *pnts1=C_Nul;

return(iazStr1);
}


// --------------------------------------------------
KpChar *TvStr2Kp(KpChar *piazDest, const unsigned char *lpszSrc)
{
KpChar *pntd;
const unsigned char *pnts;

        pntd=piazDest;
        pnts=lpszSrc;

        while(*pnts) (*pntd++)=(KpChar)(*pnts++);
        *pntd=C_Nul;

return(piazDest);
}


// --------------------------------------------------
KpChar *TvKpStrNCpy(KpChar *piazStr1, const KpChar *piazStr2, int iBufSize)
{
KpChar *pntd;
const KpChar *pnts;

        pntd=piazStr1;
        pnts=piazStr2;

        while((*pnts) && (pntd-piazStr1<iBufSize)) (*pntd++)=(*pnts++);
        if(pntd-piazStr1<iBufSize) *pntd=C_Nul;

return(piazStr1);
}


// --------------------------------------------------
int TvKpStrLen(const KpChar *iazStr)
{
        const KpChar *pnts;
        int byt_cnt=0;

        pnts=iazStr;

        while(*pnts++) byt_cnt++;

        return(byt_cnt);
}


// --------------------------------------------------
KpChar *TvKpStrChCat(KpChar *iazStr, KpChar iChar)
{
        int str_len;

        str_len=TvKpStrLen(iazStr);
        iazStr[str_len]=iChar;
        iazStr[str_len+1]=C_Nul;

        return(iazStr);
}


// --------------------------------------------------
KpChar *TvKpStrCat(KpChar *iazDest, const KpChar *iazSrc)
{
        int str_len;

        str_len=TvKpStrLen(iazDest);
        TvKpStrCpy(iazDest+str_len, iazSrc);

        return(iazDest);
}


// ==================================================
// --------------------------------------------------
HRESULT CutTrailSpcsKp(KpChar *iazString)
{
HRESULT retc=S_OK;
KpChar *pnts;

   if(iazString!=NULL)
   {
        pnts=iazString+TvKpStrLen(iazString);

           while(pnts>iazString)
           {
                   --pnts;
                   if(*pnts!=C_Spc)
                   {
                           pnts++;
                           break;
                }
        }

        *pnts=C_Nul;
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT CutInitSpcsKp(KpChar *iazString)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar *pntd;

   if(iazString!=NULL)
   {
           pntd=pnts=iazString;

           while(*pnts==C_Spc) pnts++;

           while(*pnts) *(pntd++)=(*pnts++);
           *pntd=C_Nul;
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT CutInitTrailSpcsKp(KpChar *iazString)
{
HRESULT retc;

   retc=CutInitSpcsKp(iazString);
   if(SUCCEEDED(retc)) retc=CutTrailSpcsKp(iazString);

return(retc);
}


//===================================================
//-------------------------------------
unsigned char chuge *msbcpy(unsigned char chuge *out, const unsigned char chuge *in)
{
const unsigned char chuge *cc;
unsigned char chuge *dd;

   cc=in; dd=out;
   while(*cc)
   {
     if(fstrchr(lpszSpcEol, *cc)==NULL){ *dd=(*cc); dd=PtInc(dd); }
     cc=PtInc(cc);
   }
   *dd='\0';

return(out);
}


unsigned char chuge *msncpy(unsigned char chuge *out, const unsigned char chuge *in, int count)
{
int ii,jj,ll; unsigned char chuge *cc;

   jj = fstrlen(in);
   ll = min(jj, count);
   fstrncpy(out, in, ll);
   if(jj < ll)
   {
      cc = PtMov(out, jj);
      for(ii = jj; ii < ll; ii++)
      {
         *cc = Spc;
         cc = PtInc(cc);
      }
   }

   *PtMov(out, ll) = '\0';

return(out);
}


// ================================================== common text array functions
int TvGetArraySize(void **ppaPtrArray)
{
int retv=0;
void **vptr;

   if(ppaPtrArray!=NULL)
   {
      vptr=ppaPtrArray;
      while(*vptr++) retv++;
   }

return(retv);
}


HRESULT SplitWordsI(KpChar *iazWordsBuf, KpChar **piazWordsPts, const KpChar *iazTextToSplit, int iMaxNumOfWords)
{
HRESULT retc=S_OK;
KpChar **pts_ptr;
const KpChar *pnts;
KpChar *pntd;

   if((iazWordsBuf==NULL) || (piazWordsPts==NULL) || (iazTextToSplit==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pts_ptr=piazWordsPts;
   pnts=iazTextToSplit;
   pntd=iazWordsBuf;

   while((*pnts) && SUCCEEDED(retc))
   {
      if((pts_ptr-piazWordsPts)>=iMaxNumOfWords-1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         (*pts_ptr++)=pntd;

         while((TvKpStrChr(iazSpcEol, *pnts)==NULL) && (*pnts) && SUCCEEDED(retc))
            (*pntd++)=(*pnts++);

         while((TvKpStrChr(iazSpcEol, *pnts)!=NULL) && (*pnts) && SUCCEEDED(retc))
         {
            (*pntd++)=C_Nul;
            pnts++;
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      *pntd=C_Nul;
      *pts_ptr=NULL;
   }

return(retc);
}


HRESULT SplitWords(unsigned char *lpszWordsBuf, unsigned char **plpszWordsPts, const KpChar *iazTextToSplit, int iMaxNumOfWords, int iKptCtbl)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char **pts_ptr;
const KpChar *pnts;
unsigned char *pntd;

   if((lpszWordsBuf==NULL) || (plpszWordsPts==NULL) || (iazTextToSplit==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pts_ptr=plpszWordsPts;
   pnts=iazTextToSplit;
   pntd=lpszWordsBuf;

   while((*pnts) && SUCCEEDED(retc))
   {
      if((pts_ptr-plpszWordsPts)>=iMaxNumOfWords-1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         (*pts_ptr++)=pntd;

         while((TvKpStrChr(iazSpcEol, *pnts)==NULL) && (*pnts) && SUCCEEDED(retc))
         {
            retc0=KptCharDecode(pntd, *pnts++, iKptCtbl);
            if(retc0==KP_E_UNKN_CHR) *pntd='?';
            else if(SUCCEEDED(retc)) retc=retc0;
            pntd++;
         }

         while((TvKpStrChr(iazSpcEol, *pnts)!=NULL) && (*pnts) && SUCCEEDED(retc))
         {
            (*pntd++)=Nul;
            pnts++;
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      (*pntd++)=Nul;
      *pts_ptr=NULL;
   }

   if(SUCCEEDED(retc)) retc=retc0;

return(retc);
}


// ============================================= strings of lines/fields/words
// ---------------------------------------------
HRESULT CountStrings(int *piStrsCount, unsigned char *lpszStringsBuf, const unsigned char *lpszDelimStr, bool bExactDelims)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(((piStrsCount==NULL) || (lpszStringsBuf==NULL) || (lpszDelimStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStringsBuf;
      *piStrsCount=1;

      while(*pnts)
      {
         while((TvStrChr(lpszDelimStr, (KpChar)*pnts)==NULL) && (*pnts)) pnts++;
         if(*pnts)
         {
            (*piStrsCount)++;
            pnts++;
            if(!bExactDelims) while(TvStrChr(lpszDelimStr, (KpChar)*pnts)!=NULL) pnts++;
         }
      }
   }

return(retc);
}


// ---------------------------------------------
HRESULT SplitStrings(unsigned char ***pPtrArrPtr, int *piStrsCount, unsigned char *lpszStringsBuf, const unsigned char *lpszDelimStr, bool bExactDelims)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char **pntd;

   if(((pPtrArrPtr==NULL) || (piStrsCount==NULL) || (lpszStringsBuf==NULL) || (lpszDelimStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = CountStrings(piStrsCount, lpszStringsBuf, lpszDelimStr, bExactDelims);

   KP_NEWA(*pPtrArrPtr, unsigned char *, (*piStrsCount) + 1);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStringsBuf;
      pntd=*pPtrArrPtr;
      *(pntd++)=pnts;

      while(*pnts)
      {
         while((TvStrChr(lpszDelimStr, (KpChar)*pnts)==NULL) && (*pnts)) pnts++;
         if(*pnts)
         {
            *(pnts++)=Nul;
            *(pntd++)=pnts;
            if(!bExactDelims) while(TvStrChr(lpszDelimStr, (KpChar)*pnts)!=NULL) pnts++;
         }
      }

      *pntd=NULL;
   }

return(retc);
}


#if FALSE
//-------------------------------
HRESULT SplitStrings(unsigned char *lpszStringsBuf, unsigned char ***pPtrArrPtr, int *piStrsCount)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;
int ii;

   if((lpszStringsBuf==NULL) || (pPtrArrPtr==NULL) || (piStrsCount==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// skaiciuojam eilutes
   if(SUCCEEDED(retc))
   {
      *piStrsCount=0;
      pnts=lpszStringsBuf;
      while(*pnts)
      {
         while((*pnts!=Lf) && (*pnts)) pnts++;
         pnts++;
         (*piStrsCount)++;
      }
   }

// sukuriam masyva
   KP_NEWA(*pPtrArrPtr, unsigned char *, *piStrsCount);

   if(SUCCEEDED(retc))
   {
      pnts=lpszStringsBuf;
      ii=0;
      while((*pnts) && SUCCEEDED(retc))
      {
         if(ii>=*piStrsCount)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            (*pPtrArrPtr)[ii++]=pnts;

            while((*pnts!=Lf) && (*pnts)) pnts++;
            pntd=pnts;
            if(*pnts) pnts++;
            *pntd=Nul;
            while(True)
            {
               if(pntd<=lpszStringsBuf) break;
               pntd--;
               if(*pntd==Cr) *pntd=Nul;
               else break;
            }
         }
      }

      if(ii!=*piStrsCount)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}
#endif


// -----------------------------------------
#if (CompilerGr==Mingw) || (__WATCOMC__ >= 1202)
void KpString::InitMembers(void)
{
   m_lpszExtractedValue = NULL;
}


KpString::~KpString() // : std::~string()
{
HRESULT retc = S_OK;

   KP_DELETEA(m_lpszExtractedValue);
}


// --------------------------------------
const unsigned char *KpString::ExtractUnsignedValueA(void) // const
{
HRESULT retc = S_OK;
int len;
const unsigned char *retv = NULL;
unsigned char *pntd = null;
std::string::iterator it;

   KP_DELETEA(m_lpszExtractedValue);

   len = this->length();
   KP_NEWA(m_lpszExtractedValue, unsigned char, len + 1);

   if(SUCCEEDED(retc))
   {
      pntd = m_lpszExtractedValue;
      for (it = this->begin(); it < this->end(); it++)
         *pntd++ = *it;
      *pntd++ = Nul;
   }

   retv = m_lpszExtractedValue;
   if(FAILED(retc)) retv = (const unsigned char *)"";

return(retv);
}

#else // #if (CompilerGr==Mingw)
// --------------------------------------
const unsigned char *KpString::ExtractUnsignedValueA(void) // const
{
const char *pnts;

   pnts = *this;

return((const unsigned char *)pnts);
}

#endif // #if (CompilerGr==Mingw)


// -----------------------------------------
#if (CompilerGr==Watcom) && (__WATCOMC__ < 1202)
KpString& KpString::operator = (char cChar)
{
String tmp;
char buffer[2];

   buffer[0]=cChar;
   buffer[1]=Nul;
   *this = (const char *)buffer;

return(*this);
};


KpString& KpString::erase(size_t _Pos, size_t _Count)
{
KpString tmp;
const char *pnts;

   pnts = (*this)(0, _Pos);
   tmp = pnts;
   tmp += (*this)(_Pos+_Count, NPOS);
   *this = tmp;

return(*this);
};
#endif


// --------------------------------------
HRESULT KpString::tolower(void)
{
HRESULT retc = S_OK;
const unsigned char *pnts;
unsigned char *buf = NULL;

   if(SUCCEEDED(retc))
   {
      pnts = ExtractUnsignedValueA();
      if(pnts == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   KP_NEWA(buf, unsigned char, strlen(pnts) + 1);

   if(SUCCEEDED(retc))
   {
      strcpy(buf, pnts);
      TvStrLwrLat(buf);
      *this = (char *)buf;
   }

   KP_DELETEA(buf);

return(retc);
}


// --------------------------------------
int Tv_string_Cmp(const void /* string */ *psStr1, const void /* string */ *psStr2)
{
const KpString *pnts1 = (const KpString *)psStr1;
const KpString *pnts2 = (const KpString *)psStr2;
int retv = -1;

   if((pnts1!=NULL) && (pnts2!=NULL))
   {
      if(*pnts1 == *pnts2) retv = 0;
      else if(*pnts1 < *pnts2) retv = -1;
      else /* if(*pnts1 > *pnts2) */ retv = 1;
   }

return(retv);
}


// --------------------------------------
HRESULT GetWord(const unsigned char **lpszpStrPtr, unsigned char *lpszWordBuf, const unsigned char *lpszDelims, unsigned char *pcDelim)
{
HRESULT retc = S_OK;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   if(((lpszpStrPtr == NULL) || (lpszWordBuf == NULL) || (lpszDelims == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(*lpszpStrPtr == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts = *lpszpStrPtr;
      pntd = lpszWordBuf;

      while(*pnts && TvStrChr(lpszDelims, *pnts)) pnts++; // praleidþiam skirtukus
      while(*pnts && (TvStrChr(lpszDelims, *pnts) == NULL)) *pntd++ = *pnts++;

      *pntd = Nul;

      if(pcDelim) *pcDelim = *pnts;
      if(*pnts) pnts++;
      *lpszpStrPtr = pnts;
   }

return(retc);
}


#if FALSE
// ------------------------------------------------------------------
// kopijuoja TCHAR eilutæ á char buferá, code table neapdoroja, unicode vyresnius baitus tiesiog nukanda
char *tcstrcpy(char *lpszDest, const TCHAR *pszSrc)
{
const TCHAR *pnts = pszSrc;
char *pntd = lpszDest;

   if(pszSrc == NULL) xlogf(7, L"KP pszSrc == NULL");
   else if(lpszDest == NULL) xlogf(7, L"KP lpszDest == NULL");
   else
   {
      while(*pnts) *pntd++ = *pnts++;
      *pntd = 0;
   }

return(lpszDest);
}

// ------------------------------------------------------------------
// kopijuoja char eilutæ á TCHAR buferá, code table neapdoroja, tiesiog papildo unicode vyresnius baitus
TCHAR *ctstrcpy(TCHAR *pszDest, const char *lpszSrc)
{
const char *pnts = lpszSrc;
TCHAR *pntd = pszDest;

   if(lpszSrc == NULL) xlogf(7, L"KP lpszSrc == NULL");
   else if(pszDest == NULL) xlogf(7, L"KP pszDest == NULL");
   else
   {
      while(*pnts) *pntd++ = *pnts++;
      *pntd = 0;
   }

return(pszDest);
}
#endif


// --------------------------------------
HRESULT ReplaceSubstr(unsigned char *lpszInBuf, const unsigned char *lpszKeyName, const unsigned char *lpszKeyValue, long lBufLen)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszInBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszKeyName != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszKeyValue != null, E_INVALIDARG, null, True);

unsigned char *tmp_buf = null;
   KP_NEWA(tmp_buf, unsigned char, lBufLen + 1);

unsigned char *pntdo = tmp_buf;
   if(SUCCEEDED(retc)) *pntdo = Nul;

const unsigned char *pnts = lpszInBuf;
unsigned char *pntdi = strstr(pnts, lpszKeyName);
   while((pntdi != null) && SUCCEEDED(retc))
   {
      KP_ASSERT((pntdo - tmp_buf) /* strlen(tmp_buf) */ + strlen(pnts) + strlen(lpszKeyValue) /* + strlen(pntdi) */ < lBufLen, KP_E_BUFFER_OVERFLOW, null, True);

      *pntdi = Nul;

      strcpy(pntdo, pnts);
      pntdo += strlen(pnts);

      strcpy(pntdo, lpszKeyValue);
      pntdo += strlen(lpszKeyValue);

      pnts = pntdi + strlen(lpszKeyName);
      pntdi = strstr(pnts, lpszKeyName);
   }

   strcpy(pntdo, pnts);

// --------- gràþinam á input buferá
   strcpy(lpszInBuf, tmp_buf);

   KP_DELETEA(tmp_buf);

return(retc);
}
