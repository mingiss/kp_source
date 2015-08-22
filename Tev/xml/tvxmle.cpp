// ==================================================
// tvxmle.cpp
// endings and suffixes skipper for searching in flex. languages


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
#include <ctype.h>
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
#include "kpctype.h"
#include "kptt.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsort.h"
#include "tvmain.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlis.h"

// #define PrintCvt // print words converted to main form


// ---------------------------------------------------
class TvXmlEsClass TvXmlEs;


// ---------------------------------------------------
TvXmlEsClass::TvXmlEsClass(void)
{
unsigned char **e_tbl=NULL;

   lhOpenResult=S_OK;

   e_tbl=plpszaEndSkipTableCompact_l;
   while(*e_tbl) e_tbl++;
   iEndSkipTableSize_l=(e_tbl-plpszaEndSkipTableCompact_l)/TV_XE_COMP_ENTRY_SIZ;
   if((e_tbl-plpszaEndSkipTableCompact_l)%TV_XE_COMP_ENTRY_SIZ!=0)
      lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   e_tbl=plpszaEndSkipTableCompact_e;
   while(*e_tbl) e_tbl++;
   iEndSkipTableSize_e=(e_tbl-plpszaEndSkipTableCompact_e)/TV_XE_COMP_ENTRY_SIZ;
   if((e_tbl-plpszaEndSkipTableCompact_e)%TV_XE_COMP_ENTRY_SIZ!=0)
      lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   e_tbl=plpszaEndSkipTableCompact_v;
   while(*e_tbl) e_tbl++;
   iEndSkipTableSize_v=(e_tbl-plpszaEndSkipTableCompact_v)/TV_XE_COMP_ENTRY_SIZ;
   if((e_tbl-plpszaEndSkipTableCompact_v)%TV_XE_COMP_ENTRY_SIZ!=0)
      lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   e_tbl=plpszaEndSkipTableCompact_r;
   while(*e_tbl) e_tbl++;
   iEndSkipTableSize_r=(e_tbl-plpszaEndSkipTableCompact_r)/TV_XE_COMP_ENTRY_SIZ;
   if((e_tbl-plpszaEndSkipTableCompact_r)%TV_XE_COMP_ENTRY_SIZ!=0)
      lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT TvXmlEsClass::GetOpenResult(void)
{
return(lhOpenResult);
}


// -------------------------
KpChar *TvCleanIxSpchI(KpChar *iazStr)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar *pntd;

   if(iazStr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=pntd=iazStr;

      while(*pnts)
      {
         if(
            TvIsAlpha(*pnts) ||
            (*pnts==C_Spc) ||
            (*pnts==EXACT_ENTRY_CHR) || // '#'
            (*pnts==WORD_START_CHR) ||  // '.'
            (*pnts==DOUBLE_ENTRIES_CHR) || // '*'
            (*pnts==DOUBLE_ENTRIES_KPCHAR) // C_Bpoint, bullet
           )
            *(pntd++)=(*pnts);

         pnts++;
      }

      *pntd=C_Nul;
   }

return(iazStr);
}


// ---------------------------------------------------
HRESULT /*TvXmlEsClass::*/EndCmp(const unsigned char *pucEndPtr, const unsigned char *pucLowLomit, int iNumOfBytes, const unsigned char *lpszTableEntry, int *iCmpRes, unsigned char ucLanguage, EC_Types iEcType)
{
HRESULT retc=S_OK;
int cmp_res;
const unsigned char *pnt1;
const unsigned char *pnt2;
unsigned char cc1;
unsigned char cc2;
unsigned int byt_cnt;
KpChar in_ch1;
KpChar in_ch2;
int wgt1;
int wgt2;
int ctbl;
int sm;
int sort_mode_sav;

   sort_mode_sav=SortMode;
   SortMode=KP_LNG_LIS;

   cmp_res=2;
   byt_cnt=strlen((const char *)lpszTableEntry);
   pnt2=lpszTableEntry+byt_cnt;
   if(iNumOfBytes>=0) byt_cnt=(unsigned int)iNumOfBytes;
   pnt1=pucEndPtr;

   ctbl=1;
   if(SUCCEEDED(retc))
   {
      if(iEcType<KPT_Ctnum)
      {
         ctbl=iEcType;
//       if(ucLanguage!=KP_LNG_NO)
//          retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      else switch(ucLanguage) // switch(SortMode)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIX:
      case KP_LNG_LIS:
      case KP_LNG_GER:
         ctbl=TV_XE_CTBL; // 71;
         break;
      default:
         ctbl=1;
         break;
      }
   }

   while(((cmp_res==0) || (cmp_res==2)) && ((unsigned int)(pucEndPtr-pnt1)<byt_cnt) && (pnt2>lpszTableEntry) /* && (pnt1>pucLowLomit) */ && SUCCEEDED(retc))
   {
      pnt1--; pnt2--;

      if(pnt1>=pucLowLomit) cc1=/* tolower */(*pnt1);
      else cc1=WORD_START_CHR; // '.'
      if(cisnotalpha(cc1)) cc1=WORD_START_CHR; // '.'

      cc2=/* tolower */ (*pnt2);

      if(SUCCEEDED(retc))
      {
         retc=KptCharEncode(&in_ch1, cc1, ctbl);
         if(retc==KP_E_UNKN_CHR)
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         retc=KptCharEncode(&in_ch2, cc2, ctbl);
         if(retc==KP_E_UNKN_CHR)
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         in_ch1=TvKpToLower(in_ch1);
         in_ch2=TvKpToLower(in_ch2);

//       if((ucLanguage!=KP_LNG_LIT) && (ucLanguage!=KP_LNG_LIX) && (ucLanguage!=KP_LNG_LIS))
         if(iEcType==EC_ASCII)
         {
            in_ch1=TvToLat(in_ch1);
            in_ch2=TvToLat(in_ch2);
         }

         wgt1=iCharWeigths[in_ch1];
         wgt2=iCharWeigths[in_ch2];

         sm=SortMode;

         if((sm==KP_LNG_LIT) || (sm==KP_LNG_LIX) || (sm==KP_LNG_LIS))
         {
            if(wgt1/10000==C_Y) wgt1=C_I*10000+wgt1%10000;
            if(wgt1/10000==C_y) wgt1=C_i*10000+wgt1%10000;
            if(wgt2/10000==C_Y) wgt2=C_I*10000+wgt2%10000;
            if(wgt2/10000==C_y) wgt2=C_i*10000+wgt2%10000;
         }

// ne - galunes visada surusiuotos pagal KP_LNG_LIS
#if FALSE
         wgt1=RoundChWgt(wgt1);
         wgt2=RoundChWgt(wgt2);

         if(sm==KP_LNG_LIX)
         {
            wgt1-=wgt1%10000;
            wgt2-=wgt2%10000;
         }
#endif

         if(wgt1>wgt2) cmp_res=1;
         if(wgt1<wgt2) cmp_res=(-1);
         if(wgt1==wgt2) cmp_res=0;
      }

   } // while(((cmp_res==0) || (cmp_res==2)) && ((unsigned int)(pucEndPtr-pnt1)<byt_cnt) && (pnt2>lpszTableEntry) /* && (pnt1>pucLowLomit) */)

// if((pnt1==pucLowLomit) && (pnt2>lpszTableEntry) && (cmp_res==0)) cmp_res=(-1);
   if(cmp_res==2) cmp_res=1;
   *iCmpRes=cmp_res;

   SortMode=sort_mode_sav;

return(retc);
}


// ---------------------------------------------------
HRESULT TvXmlEsClass::Replace
(
unsigned char **plpszTblPtr,
unsigned char **ppucPntDest,
unsigned char *lpszDest,
bool *pbReplaced
)
{
HRESULT retc=S_OK;
int end_len;
int src_len;
unsigned char *pntt;

   *pbReplaced=False;

// leave original, if the word consists only of found ending and it is not longer than 1 letters
   end_len=strlen((const char *)*plpszTblPtr);
   if((**plpszTblPtr)==WORD_START_CHR) end_len--; // '.'
   src_len=strlen((const char *)*(plpszTblPtr+1));
   pntt=*ppucPntDest-end_len;
   if((pntt>lpszDest) || ((**plpszTblPtr)==WORD_START_CHR) || ((end_len>1) && (src_len>1))) // '.'
      if((!cisnotalpha(*(pntt-1))) || ((**plpszTblPtr)==WORD_START_CHR) || ((end_len>1) && (src_len>1))) // '.'
         if(*(plpszTblPtr+1))
         {
            strcpy((char *)pntt, (const char *)*(plpszTblPtr+1));
            *ppucPntDest=pntt+src_len;
            *pbReplaced=True;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// ---------------------------------------------------
HRESULT TvXmlEsClass::IdToMainForm(unsigned char *FormsToChange, unsigned char *FormTable)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pntd;

   if((FormTable==NULL) || (FormsToChange==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=FormTable;
      while((*pnts) && SUCCEEDED(retc))
      {
         if((*(pnts+1))==Nul)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            pntd=(unsigned char *)strchr((const char *)FormsToChange, *pnts);
            if(pntd!=NULL)
               *pntd=*(pnts+1);
            pnts+=2;
         }
      }
   }

return(retc);
}


// ---------------------------------------------------
HRESULT TvXmlEsClass::CutEndings(unsigned char *lpszDest, const unsigned char *lpszSrc, unsigned char ucLanguage, EC_Types iEcType, bool bProcessIrr)
{
HRESULT retc=lhOpenResult;
unsigned char **p_tbl=NULL;
unsigned char **e_tbl=NULL;
unsigned char **tbl_end=NULL;
int tbl_siz=0;
unsigned char **unreg_tbl=NULL;
const unsigned char *pnts;
const unsigned char *pnts1;
unsigned char *pntd;
unsigned char **tbl_ptr;
int set;
int delta;
int ii;
int jj;
int slen;
unsigned char *f_tbl=NULL;
unsigned char c_form[TV_MAX_FORMS+1];
bool replaced;
int ctbl;
#ifdef PrintCvt // Debug
unsigned char pref_buf[TV_XL_MAX_IX_LEN+1];
unsigned char end_buf[TV_XL_MAX_IX_LEN+1];
unsigned char frm_buf[TV_XL_MAX_IX_LEN+1];
unsigned char src_buf[TV_XL_MAX_IX_LEN+1];
bool print_fl;
#endif

#ifdef PrintCvt // Debug
pref_buf[0]=Nul;
end_buf[0]=Nul;
frm_buf[0]=Nul;
strcpy(src_buf, lpszSrc);
TvCleanSpch(src_buf);
print_fl=((strlen(src_buf)>2) && (ucLanguage!=KP_LNG_NO));
#endif

   ctbl=1;
   if(SUCCEEDED(retc))
   {
      if(iEcType<KPT_Ctnum)
      {
         ctbl=iEcType;
//       if(ucLanguage!=KP_LNG_NO)
//          retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      else switch(ucLanguage) // switch(SortMode)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIX:
      case KP_LNG_LIS:
      case KP_LNG_GER:
         ctbl=TV_XE_CTBL; // 71;
         break;
      default:
         ctbl=1;
         break;
      }
   }

   if(SUCCEEDED(retc)) switch(ucLanguage)
   {
   case KP_LNG_LIT:
   case KP_LNG_LIS:
   case KP_LNG_LIX:
      p_tbl=plpszauPrefixes_l;
      e_tbl=plpszaEndSkipTableCompact_l;
      tbl_siz=iEndSkipTableSize_l;
      unreg_tbl=plpszauUnRegForms_l;
      f_tbl=lpszToMainForm_l;
      break;
   case KP_LNG_ENG:
      p_tbl=plpszauPrefixes_e;
      e_tbl=plpszaEndSkipTableCompact_e;
      tbl_siz=iEndSkipTableSize_e;
      unreg_tbl=plpszauUnRegForms_e;
      f_tbl=lpszToMainForm_e;
      break;
   case KP_LNG_GER:
      p_tbl=plpszauPrefixes_v;
      e_tbl=plpszaEndSkipTableCompact_v;
      tbl_siz=iEndSkipTableSize_v;
      unreg_tbl=plpszauUnRegForms_v;
      f_tbl=lpszToMainForm_v;
      break;
   case KP_LNG_FRE:
      p_tbl=plpszauPrefixes_f;
      e_tbl=plpszaEndSkipTableCompact_f;
      tbl_siz=iEndSkipTableSize_f;
      unreg_tbl=plpszauUnRegForms_f;
      f_tbl=lpszToMainForm_f;
      break;
   case KP_LNG_RUS:
      p_tbl=plpszauPrefixes_r;
      e_tbl=plpszaEndSkipTableCompact_r;
      tbl_siz=iEndSkipTableSize_r;
      unreg_tbl=plpszauUnRegForms_r;
      f_tbl=lpszToMainForm_r;
      break;
   case KP_LNG_NO: break;
   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      break;
   }

   if(SUCCEEDED(retc))
   {
      if(e_tbl!=NULL) tbl_end=e_tbl+tbl_siz*TV_XE_COMP_ENTRY_SIZ;

      pnts=lpszSrc;
      pntd=lpszDest;

#ifdef PrintCvt // Debug
if(print_fl)
{
// printf("%c %d %s", ucLanguage, iEcType, lpszSrc);
printf("%c\t%s", ucLanguage, lpszSrc);
}
#endif

#ifdef Debug
if(strcmp(lpszSrc, "PIKTAS#")==0)
ii=0;
#endif

      do
      {
// --------------------------------
// prefixes

         if(p_tbl!=NULL)
         {
            tbl_ptr=p_tbl;

            while(*tbl_ptr)
            {
               if(*(tbl_ptr+1)==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
                  slen=strlen(*tbl_ptr);
                  if(strncmp((const char *)pnts, (const char *)(*tbl_ptr), slen)==0)
                  {
#ifdef PrintCvt // Debug
if(print_fl)
strcpy(pref_buf, *tbl_ptr);
#endif
                     pnts1=(*(tbl_ptr+1));
                     while(*pnts1) *(pntd++)=(*pnts1++);
                     pnts+=slen;

                     break; // while(*tbl_ptr)
                  }
               }

               if(SUCCEEDED(retc))
               {
                  tbl_ptr++;
                  tbl_ptr++;
                  if(*tbl_ptr==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
                  tbl_ptr++;
               }

            } // while(*tbl_ptr)

         } // if(p_tbl!=NULL)


// --------------------------------
// to the end of the word
         while(TvIsAlpha8(*pnts, ctbl) && *pnts) *(pntd++)=(*pnts++);

// ------------
// cut ending
         c_form[0]=Nul;

// find last letter (first occurence)
         if(e_tbl!=NULL)
         {
            set=tbl_siz;
            delta=set/2;
            tbl_ptr=(unsigned char **)(e_tbl+delta*TV_XE_COMP_ENTRY_SIZ);

            if((*tbl_ptr)!=NULL)
            {
               do
               {
                  retc=EndCmp(pntd, lpszDest, 1, *tbl_ptr, &ii, ucLanguage, iEcType);

                  if(SUCCEEDED(retc))
                  {
                     set=(set+1)/2;
                     delta=(set+1)/2;
                     if(set>0)
                     {
                        if(ii>0)
                        {
                           tbl_ptr-=delta*TV_XE_COMP_ENTRY_SIZ;
                           if(tbl_ptr<e_tbl) tbl_ptr=e_tbl;
                        }
                        if(ii<0)
                        {
                           tbl_ptr+=delta*TV_XE_COMP_ENTRY_SIZ;
                           if(tbl_ptr>=tbl_end)
                              tbl_ptr=tbl_end-TV_XE_COMP_ENTRY_SIZ;
                           if(tbl_ptr<e_tbl) tbl_ptr=e_tbl;
                        }
                     }
                  }
               } while((set>delta) && (ii!=0) && SUCCEEDED(retc));

// return back to whole ending
               while((ii==0) && (tbl_ptr>e_tbl) && SUCCEEDED(retc))
               {
                  tbl_ptr-=TV_XE_COMP_ENTRY_SIZ;
                  retc=EndCmp(pntd, lpszDest, 1, *tbl_ptr, &ii, ucLanguage, iEcType);
               }
               if((ii!=0) && (tbl_ptr<tbl_end-TV_XE_COMP_ENTRY_SIZ) && SUCCEEDED(retc))
               {
                  tbl_ptr+=TV_XE_COMP_ENTRY_SIZ;
                  retc=EndCmp(pntd, lpszDest, 1, *tbl_ptr, &ii, ucLanguage, iEcType);
               }

               if(((*(tbl_ptr+1))==NULL) || ((*(tbl_ptr+2))==NULL))
                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// look for whole ending
               if((ii==0) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) do
                  {
                     retc=EndCmp(pntd, lpszDest, -1, *tbl_ptr, &jj, ucLanguage, iEcType);
                     retc=EndCmp(pntd, lpszDest, 1, *tbl_ptr, &ii, ucLanguage, iEcType);
                     if(jj!=0) tbl_ptr+=TV_XE_COMP_ENTRY_SIZ;
                  } while((jj!=0) && (ii==0) && (tbl_ptr<tbl_end) && SUCCEEDED(retc));

// cut found ending
                  if((jj==0) && SUCCEEDED(retc))
                  {
#ifdef PrintCvt // Debug
if(print_fl)
strcpy(end_buf, *tbl_ptr);
#endif
                     retc=Replace(tbl_ptr, &pntd, lpszDest, &replaced);
// gram. forms
                     if(replaced && (f_tbl!=NULL) && SUCCEEDED(retc))
                     {
                        if((*(tbl_ptr+2))!=NULL)
                           if(strlen((const char *)*(tbl_ptr+2))<=TV_MAX_FORMS)
                              strcpy((char *)c_form, (const char *)*(tbl_ptr+2));
                        if(strlen((const char *)c_form)==0)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc))
                           retc=IdToMainForm(c_form, f_tbl);
                     }
                  }

               } // if((ii==0) && SUCCEEDED(retc))

            } // if((*tbl_ptr)!=NULL)

         } // if(e_tbl!=NULL)


// ------------
// test for irregularities

// was there ending changes?
//       if(False)
         if(bProcessIrr /* && (strlen((const char *)c_form)!=0) */)
         {
            if(unreg_tbl!=NULL)
            {
               tbl_ptr=unreg_tbl;

               while(*tbl_ptr)
               {
                  tbl_ptr++;

                  if(*tbl_ptr)
                  {
// daug galuniu numetamos pagal kita gram. forma
//                   if(strchr((const char *)c_form, **(tbl_ptr-1))!=NULL)
                     {
#ifdef Debug
if(strcmp(*tbl_ptr, "ÛS")==0)
ii=0;
#endif
                        retc=EndCmp(pntd, lpszDest, -1, *tbl_ptr, &ii, ucLanguage, iEcType);
                        if(ii==0)
                        {
#ifdef Debug
// if(strcmp(lpszDest, "ATSIGRIEB")==0)
// ii=0;

// printf("%s %s %s\n", pntd, lpszDest, *tbl_ptr);
// fflush(stdout);
#endif

#ifdef PrintCvt // Debug
if(print_fl)
strcpy(frm_buf, *tbl_ptr);
#endif
                           retc=Replace(tbl_ptr, &pntd, lpszDest, &replaced);
                           break;
                        }
                     }
                     tbl_ptr++;
                     if(*tbl_ptr) tbl_ptr++;
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                  } // if(*tbl_ptr)

               } // while(*tbl_ptr)

            } // if(unreg_tbl!=NULL)

         } // if(c_form!=Nul)

// ------------
         while(!TvIsAlpha8(*pnts, ctbl) && (*pnts) && SUCCEEDED(retc)) *(pntd++)=(*pnts++);

      } while(*pnts && SUCCEEDED(retc));

      *pntd=Nul;

#ifdef PrintCvt // Debug
if(print_fl)
{
printf("\t%s", lpszDest);
printf("\t");
if(strlen(pref_buf)) printf("p: %s", pref_buf);
printf("\t");
if(strlen(end_buf)) printf("e: %s", end_buf);
printf("\t");
if(strlen(frm_buf)) printf("f: %s", frm_buf);
printf("\n", lpszDest);
}
#endif

   } // if(SUCCEEDED(retc))


return(retc);
}


// ---------------------------------------------------
HRESULT TvXmlEsClass::CutEndingsDelCjts(KpChar *iazDest, KpChar *iazSrc, unsigned char ucLanguage, EC_Types iEcType, bool bDelCjtsFl)
{
HRESULT retc=S_OK;
int chr_cnt;
unsigned char *str_buf=NULL;
unsigned char *str_buf_1=NULL;
int ctbl;
unsigned char *pnts;

   if(((iazDest==NULL) || (iazSrc==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   ctbl=1;
   if(SUCCEEDED(retc))
   {
      if(iEcType<KPT_Ctnum)
      {
         ctbl=iEcType;
//       if(ucLanguage!=KP_LNG_NO)
//          retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      else switch(ucLanguage)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIX:
      case KP_LNG_LIS:
      case KP_LNG_GER:
         ctbl=TV_XE_CTBL;
         break;
      default:
         ctbl=1;
         break;
      }
   }

   if(SUCCEEDED(retc))
   {
      TvKpStrCpy(iazDest, iazSrc);
      if((iEcType>=EC_First_Type) || (ucLanguage!=KP_LNG_NO)) TvKpStrLwr(iazDest);

//    TvCleanCtrls(iazDest);
      TvCleanIxSpchI(iazDest);

      TvKpStrClearAccents(iazDest);

#if FALSE
      if(
         (ucLanguage!=KP_LNG_LIT) && (ucLanguage!=KP_LNG_LIX) && (ucLanguage!=KP_LNG_LIS) &&
         (ucLanguage!=KP_LNG_GER) &&
         ((ucLanguage!=KP_LNG_NO) || (iEcType==EC_ASCII))
        )
         TvIStrLat(iazDest);
#endif

      chr_cnt=TvKpStrLen(iazDest);
   }

   KP_NEWA(str_buf, unsigned char, chr_cnt + TV_XL_MAX_IX_LEN + 1);
   KP_NEWA(str_buf_1, unsigned char, chr_cnt + TV_XL_MAX_IX_LEN + 1);

   if(SUCCEEDED(retc))
   {
      retc = KptStrDecode(str_buf, iazDest, TV_XE_CTBL /* (iEcType<EC_First_Type)?iEcType:TV_XE_CTBL */ /* ctbl */);
      if(retc == KP_E_UNKN_CHR)
      {
         retc = S_OK;
#ifdef Debug
// !!!   retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
#endif
      }
   }

   str_buf_1[0]=WORD_START_CHR; // '.'
   if(bDelCjtsFl && SUCCEEDED(retc)) retc=DelCjts(str_buf_1+1, str_buf, ucLanguage, iEcType);

#if FALSE // #ifdef Debug
if(strcmp(str_buf_1, "ABI|PUSIS#")==0)
str_buf[0]=Nul;
#endif

#if FALSE // #ifdef Debug
unsigned char out_buf[100];
unsigned char lang_buf[10];
strcpy(out_buf, "CutEndings: ");
lang_buf[0]=ucLanguage;
lang_buf[1]=Nul;
strcat(out_buf, lang_buf);
sprintf((char *)lang_buf, " %d ", iEcType);
strcat(out_buf, lang_buf);
strcat(out_buf, str_buf_1);
#endif

   if(SUCCEEDED(retc)) retc=CutEndings(str_buf, str_buf_1, ucLanguage, iEcType, True);

#if FALSE // #ifdef Debug
strcat(out_buf, " ");
strcat(out_buf, str_buf);
KP_TRACE(out_buf);
#endif

   if(SUCCEEDED(retc))
   {
      pnts=str_buf;
      if(*pnts==WORD_START_CHR) pnts++; // '.'
      strcpy(str_buf_1, pnts);
   }

// if(iEcType==EC_ASCII) TvStrLat(str_buf);

   if(SUCCEEDED(retc))
   {
      retc=KptStrEncode(iazDest, str_buf_1, TV_XE_CTBL /* ctbl */);
      if(retc==KP_E_UNKN_CHR)
         retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

if(iEcType==EC_ASCII) TvKpStrLat(iazDest);

   KP_DELETEA(str_buf);
   KP_DELETEA(str_buf_1);

return(retc);
}
