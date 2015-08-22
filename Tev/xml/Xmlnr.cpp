// ==================================================
// xmlnr.cpp
// XML dictionary entry node RTF functions
//


// ==================================== definitions
#include "envir.h"
#include "iBshn.h"

#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
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
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvxml.h"
#include "tvmain.h"
#include "tvtex.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "xmlsty.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "tvxmls.h"


// ==================================== class XmlNode methods
//-----------------------------------
// lpszOutBuf[KP_MAX_FILE_LIN_LEN+1]
HRESULT XmlNode::GenRtfFontAttr(/* TvRtfO *lpOutFile, */ unsigned char *lpszOutBuf, KPS_FontStyles iFontStyle)
{
HRESULT retc=S_OK;
int font_typeface;
int font_siz;
KpColor font_col;
int font_flags;
unsigned char *pntd;

   if((iFontStyle<0) || (iFontStyle>=KPS_NumOfFontStyles00) || (lpszOutBuf==NULL) /* || (lpOutFile==NULL) */)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pntd=lpszOutBuf;

   if(SUCCEEDED(retc))
   {
      font_typeface=aFontStyles[iFontStyle].GetTypeface();
      if(font_typeface!=KPT_TypefaceUndefined)
      {
//       if(SUCCEEDED(retc)) retc=lpOutFile->SetFont(font_typeface); // !!! reiketu faktinio isvedimo metu - reiketu analizuoti isvedama eilute

         if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_Font])+
            MAX_LONG_DIGITS + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            *(pntd++)=RC_KeywordStart;
            strcpy(pntd, plpszaRtfTagTable[RT_TG_Font]);
            pntd+=strlen(plpszaRtfTagTable[RT_TG_Font]);
            sprintf((char *)pntd, "%d ", font_typeface);
            while(*pntd) pntd++;
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      font_siz=aFontStyles[iFontStyle].GetFontSize();
      if(font_siz!=KPS_FontSizeUndef)
      {
         if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_fs])+
            MAX_LONG_DIGITS + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            *(pntd++)=RC_KeywordStart;
            strcpy(pntd, plpszaRtfTagTable[RT_TG_fs]);
            pntd+=strlen(plpszaRtfTagTable[RT_TG_fs]);
            sprintf((char *)pntd, "%d ", font_siz);
            while(*pntd) pntd++;
         }
      }
   }

   if(SUCCEEDED(retc)) font_flags=aFontStyles[iFontStyle].GetFontFlags();

   if(SUCCEEDED(retc)) if(font_flags & KPS_BoldFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_b])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_b]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_b]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_NoBoldFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_b]) + 1 + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_b]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_b]);
         *(pntd++)='0';
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_ItalicFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_i])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_i]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_i]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_NoItalicFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_i])+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_i]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_i]);
         *(pntd++)='0';
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_UnderlFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_ul])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_ul]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_ul]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_NoUnderlFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_ulnone])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_ulnone]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_ulnone]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_SuperFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_super])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_super]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_super]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_SubFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_sub])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_sub]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_sub]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_NoSupSubFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_nosupersub])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_nosupersub]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_nosupersub]);
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_SmCapsFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_scaps])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_scaps]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_scaps]);
         *(pntd++)=Spc;
      }
   }

// if(SUCCEEDED(retc)) if(font_flags & KPS_NoSmCapsFl) // !!! ???
   if(SUCCEEDED(retc)) if(!(font_flags & KPS_SmCapsFl))
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_scaps])+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_scaps]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_scaps]);
         *(pntd++)='0';
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc)) if(font_flags & KPS_CapsFl)
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_Caps])+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_Caps]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_Caps]);
         *(pntd++)=Spc;
      }
   }

// if(SUCCEEDED(retc)) if(font_flags & KPS_NoCapsFl) //  !!! ???
   if(SUCCEEDED(retc)) if(!(font_flags & KPS_CapsFl))
   {
      if((((pntd-lpszOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_Caps])+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         *(pntd++)=RC_KeywordStart;
         strcpy(pntd, plpszaRtfTagTable[RT_TG_Caps]);
         pntd+=strlen(plpszaRtfTagTable[RT_TG_Caps]);
         *(pntd++)='0';
         *(pntd++)=Spc;
      }
   }

   if(SUCCEEDED(retc))
   {
      font_col=aFontStyles[iFontStyle].GetColor();
      if(font_col!=KpColorUndefined)
      {
         if((((pntd-lpszOutBuf) + 1 + strlen(plpszaRtfTagTable[RT_TG_cf]) +
            MAX_LONG_DIGITS + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            *(pntd++)=RC_KeywordStart;
            strcpy(pntd, plpszaRtfTagTable[RT_TG_cf]);
            pntd+=strlen(plpszaRtfTagTable[RT_TG_cf]);
            sprintf((char *)pntd, "%d ", font_col);
            while(*pntd) pntd++;
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      font_col=aFontStyles[iFontStyle].GetBackColor();
      if(font_col!=KpColorUndefined)
      {
         if((((pntd-lpszOutBuf) + 1 + strlen(plpszaRtfTagTable[RT_TG_highlight]) +
            MAX_LONG_DIGITS + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            *(pntd++)=RC_KeywordStart;
            strcpy(pntd, plpszaRtfTagTable[RT_TG_highlight]);
            pntd+=strlen(plpszaRtfTagTable[RT_TG_highlight]);
            sprintf((char *)pntd, "%d ", font_col);
            while(*pntd) pntd++;
         }
      }
   }

return(retc);
}


//-----------------------------------
// lpiaOutBuf[KP_MAX_FILE_LIN_LEN+1]
// lpszFormatStr - formato eilute is lpszXmlTagDelimiters[][]
HRESULT XmlNode::GenRtfFontAttrStr(TvRtfO *lpOutFile, KpChar *lpiaOutBuf, const unsigned char *lpszFormatStr, bool *pbParStyleFlg, int iNumOfParStyles, int iBaseDepth)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
const unsigned char *pnts0;
KpChar *pntd;
KPS_FontStyles sty_no;
int par_sty;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
int fld_depth;
int ii;
KpChar i_char;
int uni_code;

   if((lpszFormatStr==NULL) || (lpiaOutBuf==NULL) || (pbParStyleFlg==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszFormatStr)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc))
// if(strchr(lpszFormatStr, '.')!=NULL)
// retc=S_OK;

   if(SUCCEEDED(retc)) *pbParStyleFlg=False;

// if(SUCCEEDED(retc))
// if(strchr(lpszFormatStr, NS_CTRL_START)!=NULL) // '$'
// pnts=lpszFormatStr;

   pntd=lpiaOutBuf;
   pnts=lpszFormatStr;

   while((*pnts) && SUCCEEDED(retc))
   {
      if(*pnts==NS_CTRL_START) // '$'
      {
         pnts++;
         switch(*pnts++)
         {
// font style
         case 'f':
            strcpy(sty_buf, pnts);
            sty_buf[NS_STY_NO_WDT]=Nul;

            sty_no=KPS_FontStyleUndefined;
            if(SUCCEEDED(retc)) if(sscanf((const char *)sty_buf, "%d", &sty_no)!=1)
            {
               sty_no=KPS_FontStyleUndefined;
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;

            if((sty_no<0) || (sty_no>=KPS_NumOfFontStyles00))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=GenRtfFontAttr(sty_buf, sty_no);
            if(SUCCEEDED(retc)) if(((pntd-lpiaOutBuf)+strlen(sty_buf))>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               pnts0=sty_buf;
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);
            }
            break;

// paragraph style
         case 's':
            fld_depth=lpOutFile->GetFldDepth();
            if((((pntd-lpiaOutBuf)+1+fld_depth-iBaseDepth+1+strlen(plpszaRtfTagTable[RT_TG_pard])+
               1+strlen(plpszaRtfTagTable[RT_TG_plain]) + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(!(*pbParStyleFlg))
                  for(ii=0; ii<(fld_depth-iBaseDepth); ii++)
                     *(pntd++)=(KpChar)TX_SP_FieldEnd;
               if(!(*pbParStyleFlg)) *(pntd++)=(KpChar)TX_SP_FieldStart;

               *(pntd++)=(KpChar)TX_SP_KeywordStart;

               pnts0=plpszaRtfTagTable[RT_TG_pard];
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);

               *(pntd++)=(KpChar)TX_SP_KeywordStart;

               pnts0=plpszaRtfTagTable[RT_TG_plain];
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);
            }

            if(SUCCEEDED(retc))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_PAR_STY_WDT]=Nul;
            }

            par_sty=(-1);
            if(SUCCEEDED(retc)) if(sscanf((const char *)sty_buf, "%d", &par_sty)!=1)
            {
               par_sty=(-1);
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
               for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;

            if((((pntd-lpiaOutBuf)+1+strlen(plpszaRtfTagTable[RT_TG_s])+
               MAX_LONG_DIGITS + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               *(pntd++)=(KpChar)TX_SP_KeywordStart;

               pnts0=plpszaRtfTagTable[RT_TG_s];
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);

               sprintf((char *)sty_buf, "%d", par_sty);
               pnts0=sty_buf;
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);
            }

            par_sty-=KPP_FIRST_PAR_STYLE;
            if(((par_sty<0) || (par_sty>=iNumOfParStyles)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if((((pntd-lpiaOutBuf)+strlen(lpszaParStyInlineCmds[par_sty]) + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  pnts0=lpszaParStyInlineCmds[par_sty];
                  while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);
               }
            }

            if((((pntd-lpiaOutBuf)+fld_depth-iBaseDepth-1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(!(*pbParStyleFlg))
                  for(ii=0; ii<(fld_depth-iBaseDepth-2); ii++)
                     *(pntd++)=(KpChar)TX_SP_FieldStart;
               *pbParStyleFlg=True;
            }
            break;

// unicode character
         case 'u':
            if((((pntd-lpiaOutBuf)+1+1+strlen(plpszaRtfTagTable[RT_TG_u])+MAX_LONG_DIGITS+
               1 + strlen(plpszaRtfTagTable[RT_TG_SpecChr]) + MAX_LONG_DIGITS + 1 + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               *(pntd++)=(KpChar)TX_SP_FieldStart;
#if FALSE
               *(pntd++)=(KpChar)TX_SP_KeywordStart;

               pnts0=plpszaRtfTagTable[RT_TG_u];
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);

               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((Chars16)(*pnts))); ii++)
                  *(pntd++)=(KpChar)(*pnts++);
#if FALSE
               *(pntd++)=(KpChar)TX_SP_KeywordStart;

               pnts0=plpszaRtfTagTable[RT_TG_SpecChr];
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);

               sprintf(sty_buf, "%02x", C_Quest); // '?'
               pnts0=sty_buf;
               while(*pnts0) *(pntd++)=(KpChar)(*pnts0++);
#else
               *(pntd++)=C_Spc;
               *(pntd++)=C_Quest; // '?'
#endif
#else
               strncpy(sty_buf, pnts, NS_UNI_CODE_WDT);
               sty_buf[NS_UNI_CODE_WDT]=Nul;
               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((KpChar)(*pnts))); ii++)
                  pnts++;

               uni_code=0L;
               if(SUCCEEDED(retc)) if(sscanf((char *)sty_buf, "%x", &uni_code)!=1)
               {
                  uni_code=0L;
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               }

               if(SUCCEEDED(retc))
               {
                  if((uni_code>=KPT_UniPrivateStart) && (uni_code<=KPT_UniPrivateEnd))
                     i_char=(KpChar)(uni_code-KPT_UniPrivateStart);
                  else
                  {
                     for(i_char=C_Nul; i_char<C_CharSize0; i_char=(KpChar)(i_char+1))
                        if(iaUniChars[i_char]==uni_code) break;
                  }
               }

               if(((i_char<0) || (i_char>=C_CharSize0)) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc)) *(pntd++)=i_char;
#endif
               if(SUCCEEDED(retc)) *(pntd++)=(KpChar)TX_SP_FieldEnd;
            }
            break;

// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;
            retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);
            break;

// output of spec. chars
         case NS_CTRL_START:  // '$' itself
            *(pntd++)=(KpChar)TX_SP_Doll; // C_Doll; // '$'; //
            break;

         case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
            *(pntd++)=(KpChar)TX_SP_Lslash; // C_Lslash; // '\\'; //
            break;

//       case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
//          *(pntd++)=(KpChar)TX_SP_Amp; // C_Amp; // '&'; //
//          break;

         case C_Numb:         // '#' itself, single '#' --> C_QemSpc
            *(pntd++)=(KpChar)TX_SP_Numb; // C_Numb; // '#'; //
            break;

         case C_Lbrack:       // '[' itself, single '[' --> \rm
            *(pntd++)=(KpChar)TX_SP_Lbrack; // C_Lbrack; // '['; //
            break;
         case C_Rbrack:       // ']' itself, single ']' --> end of \rm
            *(pntd++)=(KpChar)TX_SP_Rbrack; // C_Rbrack; // ']'; //
            break;

         case C_Lcurl:        // '{' itself, single '{' --> \bf
            *(pntd++)=(KpChar)TX_SP_Lcurl; // C_Lcurl; // '{'; //
            break;
         case C_Rcurl:        // '}' itself, single '}' --> end of \bf
            *(pntd++)=(KpChar)TX_SP_Rcurl; // C_Rcurl; // '}'; //
            break;


// formatting symbols
         case C_Underl:       // "$_" --> C_NBSP
            *(pntd++)=C_NBSP;
            break;
         case C_At:           // "$@" --> C_Ff
            *(pntd++)=C_Ff; // Ff;
            break;
         case C_Circ:         // "$^" --> C_hbreak
            *(pntd++)=C_hbreak; // C_break;
            break;
         case C_Point:        // "$." --> C_NullSpc
            *(pntd++)=C_NullSpc;
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
            *(pntd++) = (KpChar)TX_SP_Doll; // C_Doll; '$'; // NS_CTRL_START;
            *(pntd++) = (KpChar)(*(pnts-1));
            break;
         }
      }
      else
      {
         if((((pntd-lpiaOutBuf)+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=KptCharEncode(pntd++, *pnts++, iDelimCtbl);
      }
   }

   if(SUCCEEDED(retc)) *pntd=C_Nul;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::PutRtfFontAttr(TvRtfO *lpOutFile, KPS_FontStyles iFontStyle)
{
HRESULT retc=S_OK;
int font_typeface;
int font_flags;
KpColor font_col;
int font_siz;

   if(
      (
         ((iFontStyle<0) || (iFontStyle>=KPS_NumOfFontStyles00)) &&
         (iFontStyle!=KPS_FontStyleUndefined)
      ) ||
      (lpOutFile==NULL)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(iFontStyle!=KPS_FontStyleUndefined)
   {
      if(SUCCEEDED(retc))
      {
         font_typeface=aFontStyles[iFontStyle].GetTypeface();
         if(font_typeface!=KPT_TypefaceUndefined)
         {
//          if(SUCCEEDED(retc)) retc=lpOutFile->SetFont(font_typeface); // nustato PutKwrd(RT_TG_Font, ...
            if(SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_Font, font_typeface);
         }
      }

      if(SUCCEEDED(retc))
      {
         font_siz=aFontStyles[iFontStyle].GetFontSize();
         if(font_siz!=KPS_FontSizeUndef) retc=lpOutFile->PutKwrd(RT_TG_fs, font_siz);
      }


      if(SUCCEEDED(retc)) font_flags=aFontStyles[iFontStyle].GetFontFlags();

      if((font_flags & KPS_BoldFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_b);
      if((font_flags & KPS_NoBoldFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_b, 0);
      if((font_flags & KPS_ItalicFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_i);
      if((font_flags & KPS_NoItalicFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_i, 0);
      if((font_flags & KPS_UnderlFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_ul);
      if((font_flags & KPS_NoUnderlFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_ulnone);
      if((font_flags & KPS_SuperFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_super);
      if((font_flags & KPS_SubFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_sub);
      if((font_flags & KPS_NoSupSubFl) && SUCCEEDED(retc)) retc=lpOutFile->PutKwrd(RT_TG_nosupersub);
      if((font_flags & KPS_SmCapsFl) && SUCCEEDED(retc))
      {
         retc=lpOutFile->PutKwrd(RT_TG_scaps);
         if(SUCCEEDED(retc)) retc=lpOutFile->pCurrentField->SetCaps(VT_SmCaps);
      }
//    if((font_flags & KPS_NoSmCapsFl) && SUCCEEDED(retc)) // !!! ???
      if((!(font_flags & KPS_SmCapsFl)) && SUCCEEDED(retc))
      {
         retc=lpOutFile->PutKwrd(RT_TG_scaps, 0);
         if((!(font_flags & KPS_CapsFl)) && SUCCEEDED(retc)) retc=lpOutFile->pCurrentField->SetCaps(VT_CapsUndefined);
      }
      if((font_flags & KPS_CapsFl) && SUCCEEDED(retc))
      {
         retc=lpOutFile->PutKwrd(RT_TG_Caps);
         if(SUCCEEDED(retc)) retc=lpOutFile->pCurrentField->SetCaps(VT_ToUpper);
      }
//    if((font_flags & KPS_NoCapsFl) && SUCCEEDED(retc)) // !!! ???
      if((!(font_flags & KPS_CapsFl)) && SUCCEEDED(retc))
      {
         retc=lpOutFile->PutKwrd(RT_TG_Caps, 0);
         if((!(font_flags & KPS_SmCapsFl)) && SUCCEEDED(retc)) retc=lpOutFile->pCurrentField->SetCaps(VT_CapsUndefined);
      }


      if(SUCCEEDED(retc))
      {
         font_col = aFontStyles[iFontStyle].GetColor();
         if(font_col!=KpColorUndefined) retc=lpOutFile->PutKwrd(RT_TG_cf, font_col);
      }

      if(SUCCEEDED(retc))
      {
         font_col = aFontStyles[iFontStyle].GetBackColor();
         if(font_col!=KpColorUndefined) retc=lpOutFile->PutKwrd(RT_TG_highlight, font_col);
      }

   } // if(iFontStyle!=KPS_FontStyleUndefined)

return(retc);
}


// ---------------------------------------------
HRESULT XmlNode::PutRtfIntStr(TvRtfO *lpOutFile, const KpChar *iaOutStr, bool *pbParStyleFlg, int iNumOfParStyles, int iBaseDepth)
{
HRESULT retc=S_OK;
const KpChar *pnts;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
KPS_FontStyles sty_no;
int par_sty;
int uni_code;
KpChar i_char;
int fld_depth;
int ii;

   if((lpOutFile==NULL) || (iaOutStr==NULL) || (pbParStyleFlg==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pnts=iaOutStr;
   if(SUCCEEDED(retc)) while((*pnts) && SUCCEEDED(retc))
   {
      if(*pnts == (KpChar)NS_CTRL_START) // '$'
      {
         pnts++;
         switch(*pnts++)
         {
// font style
         case 'f':
            for(ii=0; (ii<NS_STY_NO_WDT) && (TvIsDigit(*pnts)); ii++) sty_buf[ii] = (unsigned char)(*pnts++);
            sty_buf[ii] = Nul;

            sty_no=KPS_FontStyleUndefined;
            if(SUCCEEDED(retc)) if(sscanf((const char *)sty_buf, "%d", &sty_no)!=1)
            {
               sty_no=KPS_FontStyleUndefined;
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            if((sty_no<0) || (sty_no>=KPS_NumOfFontStyles00))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=GenRtfFontAttr(sty_buf, sty_no);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutStr(sty_buf);
            break;

// paragraph style
         case 's':
            fld_depth=lpOutFile->GetFldDepth();
            if(SUCCEEDED(retc)) if(!(*pbParStyleFlg))
               for(ii=0; (ii<(fld_depth-iBaseDepth)) && SUCCEEDED(retc); ii++)
                  retc=lpOutFile->PutCharProc((KpChar)TX_SP_FieldEnd, True);
            if(SUCCEEDED(retc)) if(!(*pbParStyleFlg))
               retc=lpOutFile->PutCharProc((KpChar)TX_SP_FieldStart, True);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_KeywordStart, True);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutStr(plpszaRtfTagTable[RT_TG_pard]);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_KeywordStart, True);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutStr(plpszaRtfTagTable[RT_TG_plain]);

            for(ii=0; (ii<NS_PAR_STY_WDT) && (TvIsDigit(*pnts)) && SUCCEEDED(retc); ii++)
               sty_buf[ii] = (unsigned char)(*pnts++);
            sty_buf[ii] = Nul;

            par_sty=(-1);
            if(SUCCEEDED(retc)) if(sscanf((const char *)sty_buf, "%d", &par_sty)!=1)
            {
               par_sty=(-1);
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_KeywordStart, True);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutStr(plpszaRtfTagTable[RT_TG_s]);

            if(SUCCEEDED(retc))
            {
               sprintf((char *)sty_buf, "%d", par_sty);
               retc=lpOutFile->PutStr(sty_buf);
            }

            par_sty-=KPP_FIRST_PAR_STYLE;
            if(((par_sty<0) || (par_sty>=iNumOfParStyles)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutStr(lpszaParStyInlineCmds[par_sty]);

            if(SUCCEEDED(retc)) if(!(*pbParStyleFlg))
               for(ii=0; ii<(fld_depth-iBaseDepth-2); ii++)
                  retc=lpOutFile->PutCharProc((KpChar)TX_SP_FieldStart, True);

            if(SUCCEEDED(retc)) *pbParStyleFlg=True;

            break;

// unicode character
         case 'u':
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_FieldStart, True);

            for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit(*pnts)) && SUCCEEDED(retc); ii++)
               sty_buf[ii] = (unsigned char)(*pnts++);
            sty_buf[ii] = Nul;

            uni_code = 0L;
            if(SUCCEEDED(retc)) if(sscanf((char *)sty_buf, "%x", &uni_code)!=1)
            {
               uni_code = 0L;
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }

            i_char = C_Nul;
            if(SUCCEEDED(retc))
            {
               if((uni_code>=KPT_UniPrivateStart) && (uni_code<=KPT_UniPrivateEnd))
                  i_char=(KpChar)(uni_code-KPT_UniPrivateStart);
               else
               {
                  for(i_char=C_Nul; i_char<C_CharSize0; i_char=(KpChar)(i_char+1))
                     if(iaUniChars[i_char]==uni_code) break;
               }
            }

            if(((i_char<0) || (i_char>=C_CharSize0)) && SUCCEEDED(retc))
            {
               i_char = C_Nul;
               retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(i_char, True);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_FieldEnd, True);

            break;

// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (TvIsDigit(*pnts)); ii++) pnts++;
            retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, False, __FILE__, __LINE__, 0L);
            break;

// output of spec. chars
         case NS_CTRL_START:  // '$' itself
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Doll, True);
            break;

         case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Lslash, True);
            break;

//       case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
//          if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Amp, True);
//          break;

         case C_Numb:         // '#' itself, single '#' --> C_QemSpc
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Numb, True);
            break;

         case C_Lbrack:       // '[' itself, single '[' --> \rm
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Lbrack, True);
            break;
         case C_Rbrack:       // ']' itself, single ']' --> end of \rm
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Rbrack, True);
            break;

         case C_Lcurl:        // '{' itself, single '{' --> \bf
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Lcurl, True);
            break;
         case C_Rcurl:        // '}' itself, single '}' --> end of \bf
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Rcurl, True);
            break;


// formatting symbols
         case C_Underl:       // "$_" --> C_NBSP
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_NBSP, True);
            break;
         case C_At:           // "$@" --> C_Ff
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_Ff, True);
            break;
         case C_Circ:         // "$^" --> C_hbreak
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_hbreak, True); // C_break;
            break;
         case C_Point:        // "$." --> C_NullSpc
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_NullSpc, True);
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_SP_Doll, True); // NS_CTRL_START;
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(*(pnts-1), True);
            break;
         }
      }
      else // if(*pnts == (KpChar)NS_CTRL_START) // '$'
         retc=lpOutFile->PutCharProc(*pnts++, True);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlNode::WriteRtf(TvRtfO *lpOutFile, KpChar /* iFatherTag */, /* KpChar iFirstTag, */ KpChar iPrevTag, int iNumOfParStyles, int iBaseDepth)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
XmlTagPars *tag_pars = NULL;
KpChar *cont_ptr = NULL;
KpChar cur_tag = C_Nul;
// unsigned char *delim_str = NULL;
// unsigned char *val_buf = NULL;
const unsigned char *delim_ptr = NULL;
unsigned char *delim_buf = NULL;
KpChar *i_delim_buf=NULL;
// long tag_val;
// int par_num;
bool par_sty_fl;
CapsIndicators caps_ind;
KpChar *cont_buf = NULL;
const KpChar *pnts = NULL;
KpChar *pntd = NULL;


   if((
       (lpOutFile == NULL) // ||
//     (iFatherTag < m_iFirstTag) || CheckLastTag(iFatherTag) ||
//     (iPrevTag < m_iFirstTag) || CheckLastTag(iPrevTag)
      ) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   m_iPrevOutTag = iPrevTag;

// KP_NEWA(delim_str, unsigned char, MAX_XML_PAR_VAL_LEN + 1);
// KP_NEWA(val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   KP_NEWA(delim_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);
   KP_NEWA(i_delim_buf, KpChar, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc)) retc=lpOutFile->OpenField();

// loop on brothers
   loop_brother = this;
   while((loop_brother != NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

// if(cur_tag==XC_FwNote)
// cur_tag=XC_FwNote;

// delimiters
      if(SUCCEEDED(retc)) retc=lpOutFile->OpenField();

// default attributes of delimiters
      if(SUCCEEDED(retc)) retc=PutRtfFontAttr(lpOutFile, NS_DEFAULT_DELIM_STYLE);

// delimiter string

//    delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(m_iPrevOutTag - m_iFirstTag /* iFirstTag */)/2][(cur_tag - m_iFirstTag /* iFirstTag */)/2];
      delim_ptr = GetTagDelimiter(m_iPrevOutTag, cur_tag);
#if TRUE
      if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_buf, delim_ptr, cur_tag, tag_pars);
#else
      if(strlen(delim_ptr) >= KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) strcpy(delim_str, delim_ptr);

      if(SUCCEEDED(retc)) switch(cur_tag)
      {
      case XC_CtgGroup:
      case XC_MngNearGroup:
         if(tag_pars==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=tag_pars->SeekTextPar("num", val_buf, &par_num);
         if(((strlen(delim_str)+strlen(val_buf))>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sprintf((char *)delim_buf, (const char *)delim_str, val_buf);
         break;
      case XC_MngGroup:
         if(tag_pars==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=tag_pars->SeekNumPar("num", &tag_val, &par_num);
         if(((strlen(delim_str)+MAX_LONG_DIGITS)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sprintf((char *)delim_buf, (const char *)delim_str, tag_val);
         break;
      default:
         if((strlen(delim_str)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) strcpy(delim_buf, delim_str);
         break;
      }
#endif

      if(SUCCEEDED(retc)) retc=GenRtfFontAttrStr(lpOutFile, i_delim_buf, delim_buf, &par_sty_fl, iNumOfParStyles, iBaseDepth);

#ifdef Debug
// unsigned char str_buf[1000];
// strcpy(str_buf, ">>>");
// KptStrDecode(str_buf+3, i_delim_buf, TvIntStrLen(cont_buf), 80);
// strcat(str_buf, "<<<");
// KP_TRACE(str_buf);
#endif

      if(SUCCEEDED(retc)) retc=lpOutFile->PutKpStr(i_delim_buf, True);
      m_iPrevOutTag = cur_tag;
      if((!par_sty_fl) && SUCCEEDED(retc)) retc=lpOutFile->CloseField();


// contents start
      if(SUCCEEDED(retc)) retc=lpOutFile->OpenField();

// contents attributes
      if(SUCCEEDED(retc)) retc=PutRtfFontAttr(lpOutFile, GetTagFont(cur_tag)); // iaTagFonts[cur_tag - m_iFirstTag /* iFirstTag */]);

//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->WriteRtf(lpOutFile, cur_tag, (KpChar)XC_Nul, iNumOfParStyles, iBaseDepth);

      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XL_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// contents group
         if(SUCCEEDED(retc))
         {
//          if(iFatherTag==XC_TechNote)
//          {
//             retc=lpOutFile->PutKwrd(RT_TG_Font, NRF_Symbol);
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_O_times, True);
//          }
//          else
            {
// contents attributes - must be output also for empty tags !!!
//             if(SUCCEEDED(retc)) retc=PutRtfFontAttr(lpOutFile, GetTagFont(iFatherTag)); // iaTagFonts[iFatherTag - m_iFirstTag /* iFirstTag */]);
// contents
               if(SUCCEEDED(retc)) retc=lpOutFile->pCurrentField->GetCaps(&caps_ind);
               if(SUCCEEDED(retc))
               {
                  KP_NEWA(cont_buf, KpChar, TvKpStrLen(cont_ptr) + 1);
                  if(SUCCEEDED(retc))
                  {
//                   TvIntStrCpy(cont_buf, cont_ptr);
// delete bullets
                     pnts=cont_ptr;
                     pntd=cont_buf;
                     while(*pnts)
                     {
                        if(*pnts!=DOUBLE_ENTRIES_KPCHAR) *(pntd++)=(*pnts); // C_Bpoint
                        pnts++;
                     }
                     *pntd=C_Nul;

// caps
                     if(caps_ind==VT_SmCaps) TvKpStrLwr(cont_buf);

//                   retc = lpOutFile->PutKpStr(cont_buf, True);
                     retc = PutRtfIntStr(lpOutFile, cont_buf, &par_sty_fl, iNumOfParStyles, iBaseDepth);
#ifdef Debug
// unsigned char str_buf[1000];
// KptStrDecode(str_buf, cont_buf, TvIntStrLen(cont_buf), 80);
// KP_TRACE(str_buf);
#endif
                  }

                  KP_DELETEA(cont_buf);
               }
            }
         }
      }

      if(SUCCEEDED(retc)) retc=lpOutFile->CloseField();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// last tag in group - delimiter
   if(SUCCEEDED(retc)) retc=lpOutFile->OpenField();

// default attributes of delimiter
   if(SUCCEEDED(retc)) retc=PutRtfFontAttr(lpOutFile, NS_DEFAULT_DELIM_STYLE);
// delimiter text
   if(SUCCEEDED(retc)) retc=GenRtfFontAttrStr(lpOutFile, i_delim_buf,
//    (const unsigned char *)lpszXmlTagDelimiters[(cur_tag - m_iFirstTag /* iFirstTag */)/2][(XC_Nul - m_iFirstTag /* iFirstTag */)/2],
      GetTagDelimiter(cur_tag, XC_Nul),
      &par_sty_fl, iNumOfParStyles, iBaseDepth);

   if(SUCCEEDED(retc)) retc=lpOutFile->PutKpStr(i_delim_buf, True);
   m_iPrevOutTag = (KpChar)XC_Nul;
   if((!par_sty_fl) && SUCCEEDED(retc)) retc=lpOutFile->CloseField();

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteRtf(lpOutFile);

   if(SUCCEEDED(retc)) retc = lpOutFile->CloseField();

// KP_DELETEA(str_buf);
// KP_DELETEA(val_buf);
   KP_DELETEA(delim_buf);
   KP_DELETEA(i_delim_buf);

return(retc);
}


// ---------------------------------------------
KPS_FontStyles GetTagFont(KpChar iTag)
{
KPS_FontStyles tag_font = KPS_FontStyleUndefined;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
      tag_font = iaTagFonts[iTag - XC_FirstDictTag];

return(tag_font);
}
