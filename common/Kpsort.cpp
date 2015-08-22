// ==================================================
// kpsort.cpp
// sort/search capabilities
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
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
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvxml.h"

// ================================================== sort order definition
int iCharWeigths[C_CharArrSize44] =
{
#include "KpCharWgt.cpp"
};


// ===================== ============================= keyword search
// --------------------- -----------------------------
int TvStrStrArr(const unsigned char *lpszTestStr, const unsigned char **plpszStrArr)
{
int p_ix;
HRESULT retc;

   retc=GetKwrdIndex(&p_ix, lpszTestStr, plpszStrArr, -1, True, True);
   if(!SUCCEEDED(retc)) p_ix=(-1);

   return(p_ix);
}


// --------------------------------------------------
HRESULT GetKwrdIndex
(
   int *piIndex,
   const unsigned char *lpszKeywrd,
   const unsigned char * const *plpszKeytable,
   const int iTabSize,
   bool bCaseSens,
   bool bWholeWords
)
{
HRESULT retc=S_OK;
int id1;
unsigned char str3[KP_KWD_LEN+1];
int ii;

   if((piIndex==NULL) || (lpszKeywrd==NULL) || (plpszKeytable==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszKeywrd)>=KP_KWD_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piIndex=TV_TG_NoKey;

      id1=0;
      while
      (
         ((iTabSize<0) || (id1<iTabSize)) &&
         ((iTabSize>=0) || (plpszKeytable[id1]!=NULL)) &&
         (*piIndex==TV_TG_NoKey) &&
         SUCCEEDED(retc)
      )
      {
         strcpy(str3,lpszKeywrd);
         if(plpszKeytable[id1]!=NULL)
         {
            ii=strlen(plpszKeytable[id1]);
            if(ii>=KP_KWD_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(!bWholeWords) str3[ii]=Nul;

               if(TvStrCmp(str3, plpszKeytable[id1], False, KP_LNG_ENG, bCaseSens, 1, False)==0)
                  *piIndex=id1;
            }
         }
         id1++;
      }

      if((*piIndex==TV_TG_NoKey) && SUCCEEDED(retc))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, NULL, True, __FILE__, __LINE__, 0L);
         retc=KP_E_KWD_NOT_FOUND;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT GetKwrdIndexSkipSpc
(
   int *piIndex,
   const unsigned char *lpszKeywrd,
   const unsigned char **plpszKeytable,
   const int iTabSize,
   bool bCaseSens,
   bool bWholeWords
)
{
HRESULT retc=S_OK;
int id1;
unsigned char str1[KP_KWD_LEN+1];
unsigned char str2[KP_KWD_LEN+1];
unsigned char str3[KP_KWD_LEN+1];
const unsigned char *sptr;
unsigned char *dptr;


   if((piIndex==NULL) || (lpszKeywrd==NULL) || (plpszKeytable==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      sptr=lpszKeywrd;
      dptr=str1;
      while((*sptr) && SUCCEEDED(retc))
      {
         if(*sptr!=Spc)
         {
            if(dptr-str1<KP_KWD_LEN) *(dptr++)=(*sptr);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         }
         sptr++;
      }
      *dptr=Nul;
   }

   if(SUCCEEDED(retc))
   {
      *piIndex=TV_TG_NoKey;

      id1=0;
      while
         (
            ((iTabSize<0) || (id1<iTabSize)) &&
            ((iTabSize>=0) || (plpszKeytable[id1]!=NULL)) &&
            (*piIndex==TV_TG_NoKey) &&
            SUCCEEDED(retc)
            )
      {
         if(plpszKeytable[id1]!=NULL)
         {
            sptr=plpszKeytable[id1];
            dptr=str2;
            while((*sptr) && SUCCEEDED(retc))
            {
               if(*sptr!=Spc)
               {
                  if(dptr-str2<KP_KWD_LEN) *(dptr++)=(*sptr);
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
               }
               sptr++;
            }
            *dptr=Nul;

            str3[0]=Nul;
            if(SUCCEEDED(retc))
            {
               strcpy(str3, str1);
               if(!bWholeWords) str3[strlen(str2)]=Nul;
            }

            if(SUCCEEDED(retc))
               if(TvStrCmp(str3, str2, False, KP_LNG_ENG, bCaseSens, 1, False)==0)
                  *piIndex=id1;
         }
         id1++;
      }

      if((*piIndex==TV_TG_NoKey) && SUCCEEDED(retc))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, NULL, True, __FILE__, __LINE__, 0L);
         retc=KP_E_KWD_NOT_FOUND;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT GetKwrdIntIndex
(
   int *piIndex,
   KpChar *iazKeywrd,
   KpChar **piazKeytable,
   const int iTabSize,
   bool bWholeWords
)
{
HRESULT retc=S_OK;
int id1;
KpChar str3[KP_KWD_LEN+1];
int ii;

   if((piIndex==NULL) || (iazKeywrd==NULL) || (piazKeytable==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(TvKpStrLen(iazKeywrd)>=KP_KWD_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piIndex=TV_TG_NoKey;

      id1=0;
      while
      (
         ((iTabSize<0) || (id1<iTabSize)) &&
         ((iTabSize>=0) || (piazKeytable[id1]!=NULL)) &&
         (*piIndex==TV_TG_NoKey) &&
         SUCCEEDED(retc)
      )
      {
         TvKpStrCpy(str3, iazKeywrd);
         if(piazKeytable[id1]!=NULL)
         {
            ii=TvKpStrLen(piazKeytable[id1]);
            if(ii>=KP_KWD_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(!bWholeWords) str3[ii]=C_Nul;

               if(TvKpStrCmp(str3, piazKeytable[id1])==0)
                  *piIndex=id1;
            }
         }
         id1++;
      }

      if((*piIndex==TV_TG_NoKey) && SUCCEEDED(retc))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, NULL, True, __FILE__, __LINE__, 0L);
         retc=KP_E_KWD_NOT_FOUND;
      }
   }

return(retc);
}


// ================================================== sort tools
// --------------------------------------------------
#if FALSE
HRESULT SortTextFile(const unsigned char *lpszFname, bool bReverse)
{
HRESULT retc=S_OK;
unsigned char fnam_tmp[KP_MAX_FNAME_LEN+1];
char com_buf[KP_MAX_FNAME_LEN+8+1+8+8+1];
char *pntd;

   retc=TvUniFname.Generate(fnam_tmp);

   if(SUCCEEDED(retc))
   {
      strcpy(com_buf, "sort ");
      if(bReverse)
      {
#if OsGr==Unix
         strcat(com_buf, "-r ");
#else
         strcat(com_buf, "/R ");
#endif
      }
      pntd=com_buf+strlen(com_buf);
      sprintf(pntd, "< %s > %s", lpszFname, fnam_tmp);
      if(system(com_buf)==(-1))
         retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      sprintf(com_buf,
#if OsGr==Unix
              "cp %s %s",
#else
              "copy %s %s > nul",
#endif
              fnam_tmp, lpszFname);
      if(system(com_buf)==(-1))
         retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      sprintf(com_buf,
#if OsGr==Unix
              "rm %s",
#else
              "del %s",
#endif
              fnam_tmp);
      if(system(com_buf)==(-1))
         retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}
#endif


HRESULT SortTextFile(const unsigned char *lpszFname, bool bReverse, bool bSkipSpc)
{
HRESULT retc=S_OK;
unsigned char *strs_buf=NULL;
unsigned char **str_ptrs=NULL;
int str_cnt=0;
FILE *out_file=NULL;
int ii;
long ll;

   if(SUCCEEDED(retc)) retc=ReadFileContents(lpszFname, &strs_buf, &ll, True, False);
   if((strs_buf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=SplitStrings(&str_ptrs, &str_cnt, strs_buf, lpszEols, False);

   if((str_ptrs==NULL) && (str_cnt>0) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// paskutine tuscia eilute po paskutinio Cr/Lf - SplitStrings algoritmo siuksle
   if((str_cnt>0) && SUCCEEDED(retc))
      if(strlen(str_ptrs[str_cnt-1])==0) str_cnt--;

   if((str_cnt>0) && SUCCEEDED(retc))
      qsort(str_ptrs, str_cnt, sizeof(*str_ptrs),
         bReverse?
         (bSkipSpc?TvStrPtrCmpStrictRevSkipSpc:TvStrPtrCmpStrictRev):
         (bSkipSpc?TvStrPtrCmpStrictSkipSpc:TvStrPtrCmpStrict));

   if(SUCCEEDED(retc))
   {
      out_file=fopen((const char *)lpszFname, "w");
      if(out_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) for(ii=0; (ii<str_cnt) && SUCCEEDED(retc); ii++)
   {
      fputs((const char *)str_ptrs[ii], out_file);
      fputs("\n", out_file);
      if(ferror(out_file) || feof(out_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fclose(out_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFname, True, __FILE__, __LINE__, 0L);

   KP_DELETEA(str_ptrs);
   KP_DELETEA(strs_buf);

return(retc);
}

// --------------------------------------------------
unsigned char *TvKpStrToSort(unsigned char *lpszOutStr, const KpChar *piazInStr, bool bStrictFl)
{
HRESULT retc=S_OK;
const KpChar *pnts;
unsigned char *pntd;

   if(((lpszOutStr == NULL) || (piazInStr == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts = piazInStr;
      pntd = lpszOutStr;

      while(*pnts && SUCCEEDED(retc))
      {
         *pntd = TvToLat(*pnts);

         if(bStrictFl) *pntd = tolower(*pntd);

         switch(*pnts)
         {
         case C_C_Car:
         case C_S_Car:
         case C_Z_Car:
            pntd++;
            *pntd++ = 'Z';
            break;

         case C_c_Car:
         case C_s_Car:
         case C_z_Car:
            pntd++;
            *pntd++ = 'z';
            break;

         case C_Y:
            if((SortMode == KP_LNG_LIT) && bStrictFl) *pntd = C_I;
            pntd++;
            break;
         case C_y:
            if((SortMode == KP_LNG_LIT) && bStrictFl) *pntd = C_i;
            pntd++;
            break;

         case C_Point: pntd++; break;

         case C_Spc:
         case C_Dash:
            if(!bStrictFl) *pntd++ = '-';
            break;

         case C_Comma: break;

         default: if(isalnum(*pntd)) pntd++; break;
         }

         pnts++;
      }

      *pntd = Nul;
   }

return(lpszOutStr);
}
