// ==================================================
// tvxmlc.cpp
// XML spec. chars entities routines
// KpCharToStrNoCtrl() adapted to mcmr2x
//

// ================================================== definitions
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
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsort.h"
#include "tvmain.h"
#include "tvxmls.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlis.h"

// ===================================================
// --------------------------------------------------
HRESULT SearchSpecChar(KpChar *puiInCh, const unsigned char *lpszCharText, const unsigned char * const *plpszaXmlSpCharTags)
{
HRESULT retc=S_OK;
int ii;

   *puiInCh=C_Nul;

   if(plpszaXmlSpCharTags!=NULL)
      retc = GetKwrdIndex((int *)puiInCh, lpszCharText, plpszaXmlSpCharTags, C_CharSize0, True, True);
   else retc=KP_E_KWD_NOT_FOUND;

   if(retc==KP_E_KWD_NOT_FOUND)
   {
      retc=GetKwrdIndex(&ii, lpszCharText, plpszaXmlAddSpChars, -1, True, True);
      if(SUCCEEDED(retc)) *puiInCh=iXmlAddSpChars[ii];
      else if(retc==KP_E_KWD_NOT_FOUND) retc=KP_E_UNKN_CHR;
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpCharToStrNoCtrl
(
unsigned char *lpszOutStrBuf,
const KpChar *auiTextBuf,
const int iNumOfChars,
const int iOutStrLen,
const unsigned char ** /* plpszaXmlSpCharTags */,
EC_Types iEcType
)
{
HRESULT retc=S_OK;
int ii;
unsigned char *pntd;
KpChar last_char=C_Spc;
bool is_space, is_spec;
int cur_ch;
// unsigned char *pntw;
// const unsigned char *pntc;
// unsigned char ch_buf[TV_XM_MAX_CHAR_LEN+1];
// int ch_len;

   pntd=lpszOutStrBuf;
   *pntd=Nul;

   for(ii=0; (ii<iNumOfChars) && SUCCEEDED(retc); ii++)
   {
      is_space=False;
      is_spec=False;

      if(SUCCEEDED(retc))
         if((auiTextBuf[ii]<0) || (auiTextBuf[ii]>=C_CharSize0))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
            is_space=True;
         }

      if(SUCCEEDED(retc))
      {
         is_space|=((TvStrChr(lpszSpcEol, auiTextBuf[ii])!=0) ||
                    ((TvStrChr(lpszIxSpcEolPtr, auiTextBuf[ii])!=0) && (iEcType==EC_ASCII)));
         is_spec=(
            (!TvIsAlpha(auiTextBuf[ii])) &&
            (!TvIsDigit(auiTextBuf[ii])) &&
            (!is_space) &&
            ((TvStrChr(lpszIxSpCharsPtr, auiTextBuf[ii])==0) || (iEcType==EC_ASCII)) &&
            (auiTextBuf[ii]!=EXACT_ENTRY_CHR) && // C_Numb, '#' naudojamas indexuose pilnam variantui pazymeti
            (auiTextBuf[ii]!=DOUBLE_ENTRIES_KPCHAR) && // C_Bpoint, Bullet naudojamas homonimu etc. atskyrimui
            (auiTextBuf[ii]!=DOUBLE_ENTRIES_CHR) &&  // C_Ast, '*' naudojamas homonimu etc. atskyrimui
            ((auiTextBuf[ii]!=C_Apost) || (bCutEndingsAfterApostrophe) || (iEcType==EC_ASCII))
                 );
         if(!is_spec)
         {
            if((last_char!=C_Spc) || !is_space)
            {
               last_char=is_space?C_Spc:auiTextBuf[ii];
               if(last_char>=C_CharSize0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

#if FALSE // TRUE //
               if(SUCCEEDED(retc))
               {
                  pntc=NULL;
                  if(plpszaXmlSpCharTags!=NULL) pntc=plpszaXmlSpCharTags[last_char];
                  if(pntc==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, NULL, True, __FILE__, __LINE__, 0L);
               }

               if(SUCCEEDED(retc))
               {
                  pntw=ch_buf;
                  while(*pntc && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc))
                     {
                        if((pntw-ch_buf)>=TV_XM_MAX_CHAR_LEN-1)
                           retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, True, __FILE__, __LINE__, 0L);

                        if((*pntc!=TV_XM_SpCharSt) && (*pntc!=TV_XM_SpCharEnd))
                           (*pntw++)=(*pntc);
                        pntc++;
                     }
                  }
                  if(SUCCEEDED(retc)) (*pntw++)=Nul;

               } // if(SUCCEEDED(retc))

               if(SUCCEEDED(retc))
               {
                  ch_len=strlen((const char *)ch_buf);

                  if((int)(pntd-lpszOutStrBuf+ch_len)>=iOutStrLen-1)
                     retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  strcpy((char *)pntd, (const char *)ch_buf);
                  pntd+=ch_len;
               }
#else
               if((last_char==C_Numb) && (pntd>lpszOutStrBuf) && SUCCEEDED(retc))
               {
                  while(*(pntd-1)==C_Spc)
                  {
                     pntd--;
                     if(pntd==lpszOutStrBuf) break;
                  }
               }

               if(((int)(pntd-lpszOutStrBuf)>=iOutStrLen-1) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) switch(iEcType)
               {
               case EC_ASCII:
                  if(
                     (last_char!=DOUBLE_ENTRIES_CHR) &&   // Bullet, '*' - tik tikslaus indexo atveju
                     (last_char!=DOUBLE_ENTRIES_KPCHAR) &&
                     (last_char!=(KpChar)TV_XM_CompDelim)
                    )
                     (*pntd++)=(unsigned char)KptToLatTbl[last_char];
                  break;
               default:
                  if(iEcType<KPT_Ctnum)
                  {
                     if(
                        (last_char==DOUBLE_ENTRIES_KPCHAR) ||   // Bullet - verciam i '*'
                        (last_char==DOUBLE_ENTRIES_CHR)       // '*' - paliekam
                       )
                        *(pntd++)=(unsigned char)KptToLatTbl[last_char];
                     else if(last_char!=(KpChar)TV_XM_CompDelim)
                     {
                        cur_ch=KptNoAccTbl[last_char];
                        retc=KptCharDecode(pntd, (KpChar)cur_ch, iEcType);
                        if(retc==KP_E_UNKN_CHR)
                        {
                           cur_ch=KptToLatTbl[cur_ch];
                           retc=KptCharDecode(pntd, (KpChar)cur_ch, iEcType);
                           if(retc==KP_E_UNKN_CHR)
                              retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                        }
                        pntd++;
                     }
                  }
                  else
                     retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
               }
#endif
            } // if((last_char!=C_Spc) || !is_space)

         } // if(!is_spec)

      } // if(SUCCEEDED(retc))

   } // for(ii=0; (ii<iNumOfChars) && SUCCEEDED(retc); ii++)

   *pntd=Nul;

   if(
      (
         (iEcType>=EC_First_Type) // ||
//       (ucLanguage!=KP_LNG_NO)
      ) &&
      SUCCEEDED(retc)
     )
      TvStrLwr(lpszOutStrBuf, (iEcType<KPT_Ctnum)?iEcType:1);

return(retc);
}


// --------------------------------------------------
const unsigned char *plpszaXmlAddSpChars[] =      // additional XML spec char tags for KpChar
{
   (const unsigned char *)"&pound;",  // C_Pound
   NULL,
};

KpChar iXmlAddSpChars[] =             // KpChar equivalents of plpszaXmlAddSpChars
{
   C_Pound,   // "&pound;"
};

