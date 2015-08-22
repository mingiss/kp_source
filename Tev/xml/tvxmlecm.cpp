// ==================================================
// tvxmlecm.cpp
// endings and suffixes skipper for searching in flex. languages
// endings joining utility - secondary *.cpp table file generator
//

// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpctype.h"
#include "kpstdio.h"
#include "kpstring.h"
#include "kpsort.h"

#include "tvmain.h"
#include "tvxml.h"
#include "tvxmle.h"
#include "tvxmlecm.h"

// ------------------------------
#define WITH_DIACR                 // use diacrytics in output


// ================================================== objects
TvXmlEcm_tag *pTvXmlEcm=NULL;

KpErrorProc_tag KpErrorProc(TRUE, 71);

int SortMode=KP_LNG_LIS;


// =============================================
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}
   

// ================================================== private methods of TvXmlEcm_tag
// --------------------------------------------------
HRESULT TvXmlEcm_tag::CheckTables()
{
HRESULT retc=S_OK;
const unsigned char **pnts;
long lcnt=1;
const unsigned char *pntc;
unsigned char *pntm;


// ---------------------------------------------------------------------
   pnts=plpszaTGrFrm;
   while((*pnts!=NULL) && SUCCEEDED(retc))
   {
      pnts++;
      if(*pnts==NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         pntc=(*pnts);
         while(*pntc && SUCCEEDED(retc))
         {
            pntm = (unsigned char *)strchr((const char *)lpszTMnFrm, *pntc);
            if(pntm==NULL)
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            else
            {
               if(((pntm-lpszTMnFrm)%2)!=1)
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            }

            pntc++;
         }
      }

      pnts++;
   }

   if(*(pnts+1)!=NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);



   
// ---------------------------------------------------------------------
   if(SUCCEEDED(retc))
      if((strlen((const char *)lpszTMnFrm)%2)!=0)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);




// ---------------------------------------------------------------------
   pnts=plpszaESkpTbl;
   while((*pnts!=NULL) && SUCCEEDED(retc))
   {

// printf(">>%s<<\n",*pnts);

// --------------------
#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }

#ifndef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

// --------------------
#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }

#ifndef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

// --------------------
      if(SUCCEEDED(retc))
         if(strlen((const char *)(*pnts))==0)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      if(SUCCEEDED(retc))
      {
         retc=TestAllowed(*pnts, lpszTMnFrm);
         if(!SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(retc, *pnts, True, __FILE__, __LINE__, lcnt, NULL);
      }
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }

      if(SUCCEEDED(retc))
      {
         retc=TestAllowed(*pnts, lpszFrms);
         if(!SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(retc, *pnts, True, __FILE__, __LINE__, lcnt, NULL);
      }
      pnts++;

      lcnt++;
   }

   if((*(pnts+1)!=NULL) || (*(pnts+2)!=NULL) || (*(pnts+3)!=NULL) || (*(pnts+4)!=NULL) || (*(pnts+5)!=NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);

// printf("%ld\n", lcnt);


// ---------------------------------------------------------------------
   pnts=plpszaURgFrms;
   while((*pnts!=NULL) && SUCCEEDED(retc))
   {
// --------------------
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }

// --------------------
#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }

#ifndef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

// --------------------
#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         pnts++;
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         pnts++;
      }

#ifndef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         if(*pnts==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);

         pnts++;
      }
#endif

   } // while((*pnts!=NULL) && SUCCEEDED(retc))

   if((*(pnts+1)!=NULL) || (*(pnts+2)!=NULL) || (*(pnts+3)!=NULL) || (*(pnts+4)!=NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, lcnt, NULL);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutHat(void)
{
HRESULT retc=S_OK;
const unsigned char **pnts;
unsigned char str_buf[KP_MSG_LEN+1];

   if(lpOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      fputs("// ==================================================\n", lpOutFile);

      fprintf(lpOutFile, "// %s\n", lpszFName);
      fputs("// endings and suffixes skipper for searching in flex. languages\n", lpOutFile);
      fputs("// ", lpOutFile);
      switch(uiFId)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIS:
      case KP_LNG_LIX:
         fputs("lithuanian", lpOutFile); break;
      }
      fputs(" language\n", lpOutFile);

      fputs("// compressed endings file\n", lpOutFile);
      fputs("// !!! do not change - generated by tvxmlecm.exe !!!\n", lpOutFile);
      fprintf(lpOutFile, "// !!! original file - %s%c.cpp !!!\n", KP_LNG_CFNAM, uiFId);
      fputs("\n\n", lpOutFile);

      fputs("// ================================================== definitions\n", lpOutFile);
      fputs("#include \"envir.h\"\n", lpOutFile);
      fputs("\n", lpOutFile);
      fputs("#include <stdio.h>\n", lpOutFile);
      fputs("#if OsGr==MSWin\n", lpOutFile);
      fputs("#include <windows.h>\n", lpOutFile);
      fputs("#endif\n", lpOutFile);
      fputs("\n", lpOutFile);
      fputs("#include \"kpstdlib.h\"\n", lpOutFile);
      fputs("#include \"kptt.h\"\n", lpOutFile);
      fputs("\n", lpOutFile);
      fputs("#include \"tvmain.h\"\n", lpOutFile);
      fputs("#include \"tvxmle.h\"\n", lpOutFile);
      fputs("\n\n", lpOutFile);

// ---------------------------------------
// plpszaToGrForm_l
      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char *plpszaToGrForm_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);
      pnts=plpszaTGrFrm;
      while((*pnts) && SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, "   (unsigned char *)\"%s\", ", *pnts);
         if(strlen((const char *)str_buf)<=TV_XE_COL_WDT)
            retc=TvPutSN(lpOutFile, str_buf, TV_XE_COL_WDT);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         pnts++;

         if(*pnts)
         {
            fprintf(lpOutFile, "(unsigned char *)\"%s\",\n", *pnts);
            pnts++;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      fputs("   NULL, NULL\n};\n", lpOutFile);
      fputs("\n\n", lpOutFile);

// ---------------------------------------
// lpszToMainForm_l
      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char lpszToMainForm_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);
      fprintf(lpOutFile, "#if Compiler==Msvc60\n");
      fprintf(lpOutFile, "   (unsigned char *)\n");
      fprintf(lpOutFile, "#endif\n");
      fprintf(lpOutFile, "   \"%s\"\n", lpszTMnFrm);
      fputs("};\n", lpOutFile);
      fputs("\n\n", lpOutFile);

// ---------------------------------------
// plpszaUnRegForms_l
#if FALSE
      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char *plpszauUnRegForms_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);

      pnts=plpszaURgFrms;
      while((*pnts) && SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, "   (unsigned char *)\"%s\", ", *pnts);
         if(
            (strlen((const char *)str_buf)<=TV_XE_COL_WDT) &&
            (strlen((const char *)*pnts)==TV_XE_GRGR_COL_WDT)
           )
            retc=TvPutSN(lpOutFile, str_buf, TV_XE_COL_WDT);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
         pnts++;

#ifdef WITH_DIACR
         if(SUCCEEDED(retc))
         {
            if(*pnts)
            {
               if(strlen(*pnts)>TV_XE_UNREG_COL_WDT)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
               pnts++;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }
#endif

         if(SUCCEEDED(retc))
         {
            if(*pnts)
            {
               sprintf((char *)str_buf, "(unsigned char *)\"%s\", ", *pnts);
               if(strlen((const char *)str_buf)<=TV_XE_UNREG_COL_WDT)
                  retc=TvPutSN(lpOutFile, str_buf, TV_XE_UNREG_COL_WDT);
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
               pnts++;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }

#ifndef WITH_DIACR
         if(SUCCEEDED(retc))
         {
            if(*pnts)
            {
               if(strlen(*pnts)>TV_XE_UNREG_COL_WDT)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
               pnts++;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }
#endif

#ifdef WITH_DIACR
         if(SUCCEEDED(retc))
         {
            if(*pnts) pnts++;
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }
#endif

         if(SUCCEEDED(retc))
         {
            if(*pnts)
            {
               strcpy((char *)str_buf, (const char *)*pnts);
               fprintf(lpOutFile, "(unsigned char *)\"%s\",\n", TvStrUpr(str_buf));
               pnts++;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }

#ifndef WITH_DIACR
         if(*pnts) pnts++;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#endif

      }

      fputs("   NULL, NULL, NULL\n};\n", lpOutFile);
#endif

      if(ferror(lpOutFile) || feof(lpOutFile))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutFullPrefixTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
HRESULT retc0;
FILE *outfile;
const unsigned char **pnts;
long lcnt=1;
unsigned char str_buf[TV_XE_INV_1_COL+1];
int str_buf_i[TV_XE_INV_1_COL+1];
int slen;

   outfile=fopen((const char *)lpszFileName, "w");
   if(outfile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      pnts=plpszaPrefixTbl;
      while((*pnts!=NULL) && SUCCEEDED(retc))
      {

// ---------------
#ifdef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

         if(SUCCEEDED(retc)) strcpy(str_buf, *pnts);

         if(SUCCEEDED(retc))                    
         {
            slen=strlen(str_buf);
            retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
         }                   
         if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
         if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
         if(SUCCEEDED(retc))                    
            retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);
                   
         if(SUCCEEDED(retc))
            retc=TvPutSN(outfile, str_buf, TV_XE_INV_1_COL);

#ifndef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

// ---------------
         if(SUCCEEDED(retc)) pnts++;

#ifdef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

         if(SUCCEEDED(retc)) strcpy(str_buf, *pnts);

         if(SUCCEEDED(retc))                    
         {
            slen=strlen(str_buf);
            retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
         }                   
         if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
         if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
         if(SUCCEEDED(retc))                    
            retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);
                   
         if(SUCCEEDED(retc))                    
            retc=TvPutSN(outfile, str_buf, TV_XE_INV_2_COL);

#ifndef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

// ---------------
         if(SUCCEEDED(retc)) pnts++;
         
         if(SUCCEEDED(retc))
            retc=TvPutSN(outfile, *pnts, TV_XE_INV_3_COL);

         if(SUCCEEDED(retc))
         {
            fprintf(outfile, "\n");
            if(ferror(outfile) || feof(outfile))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            pnts+=2;
            lcnt++;
         }
      
      } // while((*pnts!=NULL) && SUCCEEDED(retc))
      
   } // if(SUCCEEDED(retc))

   if(outfile!=NULL)
   {
      if(fclose(outfile)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutPrefixTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
FILE *infile;
unsigned char col1_buf[TV_XE_INV_1_COL+2+1];
unsigned char col1_sav[TV_XE_INV_1_COL+1];
unsigned char col2_buf[TV_XE_INV_2_COL+2+1];
unsigned char col2_sav[TV_XE_INV_2_COL+1];
unsigned char col3_buf[TV_XE_INV_3_COL+2+1];
unsigned char col3_sav[TV_XE_INV_3_COL+1];
unsigned char str_buf[TV_XE_INV_1_COL+1];
bool end_fl=FALSE;
char format[200];

   infile=NULL;

   col1_sav[0]=Nul;
   col2_sav[0]=Nul;
   col3_sav[0]=Nul;

   infile=fopen((const char *)lpszFileName, "r");
   if(infile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      sprintf(format, "(unsigned char *)%c%ds, (unsigned char *)%c%ds, (unsigned char *)%c%ds,\n",
                      '%', TV_XE_INV_1_COL, '%', TV_XE_INV_2_COL, '%', TV_XE_INV_3_COL);


      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char *plpszauPrefixes_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);

      if(ferror(lpOutFile) || feof(lpOutFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
   }

   while(!end_fl && SUCCEEDED(retc))
   {
      fgets((char *)col1_buf+1, TV_XE_INV_1_COL+1, infile);
      fgets((char *)col2_buf+1, TV_XE_INV_2_COL+1, infile);
      fgets((char *)col3_buf+1, TV_XE_INV_3_COL+1, infile);
      fgets((char *)str_buf, TV_XE_INV_1_COL+1, infile);
      if(ferror(infile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
      if(feof(infile)) end_fl=TRUE;

      if(((strlen((const char *)str_buf)!=1) || (str_buf[0]!='\n')) && !end_fl && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

      if(!end_fl && SUCCEEDED(retc))
      {
         col1_buf[TV_XE_INV_1_COL+1]=Nul;
         col2_buf[TV_XE_INV_2_COL+1]=Nul;
         col3_buf[TV_XE_INV_3_COL+1]=Nul;

         if(strcmp((const char *)col1_buf+1, (const char *)col1_sav)!=0)
         {
            strcpy((char *)col1_sav, (const char *)col1_buf+1);
            strcpy((char *)col2_sav, (const char *)col2_buf+1);
            strcpy((char *)col3_sav, (const char *)col3_buf+1);

            if(SUCCEEDED(retc)) retc=CutTrailSpcs(col1_buf+1);
            if(SUCCEEDED(retc)) retc=CutTrailSpcs(col2_buf+1);
            if(SUCCEEDED(retc)) retc=CutTrailSpcs(col3_buf+1);

// invert ending
            if(SUCCEEDED(retc))
            {

// enclose in ""
               col1_buf[0]='\"';
               strcat((char *)col1_buf, "\"");
               col2_buf[0]='\"';
               strcat((char *)col2_buf, "\"");
               col3_buf[0]='\"';
               strcat((char *)col3_buf, "\"");

               fprintf(lpOutFile, format, col1_buf, col2_buf, col3_buf);

               if(ferror(lpOutFile) || feof(lpOutFile))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
            }
         }
         else
            if(strcmp((const char *)col2_buf+1, (const char *)col2_sav)!=0)
               retc=KpErrorProc.OutputErrorMessage(TV_E_DOUBLE_INDEX, col1_sav, True, __FILE__, __LINE__, 0L, NULL);
      }

   } // while(!end_fl && SUCCEEDED(retc))

   if(SUCCEEDED(retc)) fputs("   NULL, NULL, NULL\n};\n\n\n", lpOutFile);

   if(infile!=NULL) fclose(infile);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutInvertedESkpTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
HRESULT retc0;
FILE *outfile;
const unsigned char **pnts;
long lcnt=1;
unsigned char str_buf[TV_XE_INV_1_COL+1];
int str_buf_i[TV_XE_INV_1_COL+1];
const unsigned char *pntr;
unsigned char *pntw;
int slen;

   outfile=fopen((const char *)lpszFileName, "w");
   if(outfile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      pnts=plpszaESkpTbl;
      while((*pnts!=NULL) && SUCCEEDED(retc))
      {

// ---------------
#ifdef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

         slen=strlen((const char *)*pnts);
         if(slen>TV_XE_INV_1_COL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, *pnts, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
         {
            pntw=str_buf;
            pntr=(*pnts)+slen;

            while(pntr>(*pnts)) *(pntw++)=(*(--pntr));
            *pntw=Nul;
         }

         if(SUCCEEDED(retc))                    
         {
            slen=strlen(str_buf);
            retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
         }                   
         if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
         if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
         if(SUCCEEDED(retc))                    
            retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);
                   
         if(SUCCEEDED(retc))
            retc=TvPutSN(outfile, str_buf, TV_XE_INV_1_COL);

#ifndef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

// ---------------
         if(SUCCEEDED(retc)) pnts++;

#ifdef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

         if(SUCCEEDED(retc)) strcpy(str_buf, *pnts);

         if(SUCCEEDED(retc))                    
         {
            slen=strlen(str_buf);
            retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
         }                   
         if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
         if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
         if(SUCCEEDED(retc))                    
            retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);
                   
         if(SUCCEEDED(retc))                    
            retc=TvPutSN(outfile, str_buf, TV_XE_INV_2_COL);

#ifndef WITH_DIACR
         if(SUCCEEDED(retc)) pnts++;
#endif

// ---------------
         if(SUCCEEDED(retc)) pnts++;
         
         if(SUCCEEDED(retc))
            retc=TvPutSN(outfile, *pnts, TV_XE_INV_3_COL);

         if(SUCCEEDED(retc))
         {
            fprintf(outfile, "\n");
            if(ferror(outfile) || feof(outfile))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            pnts+=2;
            lcnt++;
         }
      
      } // while((*pnts!=NULL) && SUCCEEDED(retc))
      
   } // if(SUCCEEDED(retc))

   if(outfile!=NULL)
   {
      if(fclose(outfile)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutCompactedESkpTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
FILE *infile;
unsigned char col1_buf[TV_XE_INV_1_COL+2+1];
unsigned char col1_sav[TV_XE_INV_1_COL+1];
unsigned char col2_buf[TV_XE_INV_2_COL+2+1];
unsigned char col2_sav[TV_XE_INV_2_COL+1];
unsigned char col3_buf[TV_XE_INV_3_COL+2+1];
unsigned char col3_sav[TV_XE_INV_3_COL+1];
unsigned char str_buf[TV_XE_INV_1_COL+1];
unsigned char *pntw;
unsigned char *pntr;
unsigned char col1_inverted[TV_XE_INV_1_COL+1+2];
bool end_fl=FALSE;
char format[200];

   infile=NULL;

   col1_sav[0]=Nul;
   col2_sav[0]=Nul;
   col3_sav[0]=Nul;

   infile=fopen((const char *)lpszFileName, "r");
   if(infile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      sprintf(format, "(unsigned char *)%c%ds, (unsigned char *)%c%ds, (unsigned char *)%c%ds,\n",
                      '%', TV_XE_INV_1_COL, '%', TV_XE_INV_2_COL, '%', TV_XE_INV_3_COL);


      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char *plpszaEndSkipTableCompact_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);

      if(ferror(lpOutFile) || feof(lpOutFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
   }

   while(!end_fl && SUCCEEDED(retc))
   {
      fgets((char *)col1_buf+1, TV_XE_INV_1_COL+1, infile);
      fgets((char *)col2_buf+1, TV_XE_INV_2_COL+1, infile);
      fgets((char *)col3_buf+1, TV_XE_INV_3_COL+1, infile);
      fgets((char *)str_buf, TV_XE_INV_1_COL+1, infile);
      if(ferror(infile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
      if(feof(infile)) end_fl=TRUE;

      if(((strlen((const char *)str_buf)!=1) || (str_buf[0]!='\n')) && !end_fl && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

      if(!end_fl && SUCCEEDED(retc))
      {
         col1_buf[TV_XE_INV_1_COL+1]=Nul;
         col2_buf[TV_XE_INV_2_COL+1]=Nul;
         col3_buf[TV_XE_INV_3_COL+1]=Nul;

         if(strcmp((const char *)col1_buf+1, (const char *)col1_sav)!=0)
         {
            strcpy((char *)col1_sav, (const char *)col1_buf+1);
            strcpy((char *)col2_sav, (const char *)col2_buf+1);
            strcpy((char *)col3_sav, (const char *)col3_buf+1);

            retc=CutTrailSpcs(col1_buf+1);
            if(SUCCEEDED(retc)) retc=CutTrailSpcs(col2_buf+1);
            if(SUCCEEDED(retc)) retc=CutTrailSpcs(col3_buf+1);

// invert ending
            if(SUCCEEDED(retc))
            {
               pntw=col1_inverted+1;
               pntr=col1_buf+1+strlen((const char *)col1_buf+1);
               while(pntr>col1_buf+1) *(pntw++)=(*(--pntr));
               *pntw=Nul;

// enclose in ""
               col1_inverted[0]='\"';
               strcat((char *)col1_inverted, "\"");
               col2_buf[0]='\"';
               strcat((char *)col2_buf, "\"");
               col3_buf[0]='\"';
               strcat((char *)col3_buf, "\"");

               fprintf(lpOutFile, format, col1_inverted, col2_buf, col3_buf);

               if(ferror(lpOutFile) || feof(lpOutFile))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
            }
         }
         else
            if(strcmp((const char *)col2_buf+1, (const char *)col2_sav)!=0)
               retc=KpErrorProc.OutputErrorMessage(TV_E_DOUBLE_INDEX, col1_sav, True, __FILE__, __LINE__, 0L, NULL);
      }

   } // while(!end_fl && SUCCEEDED(retc))

   if(SUCCEEDED(retc)) fputs("   NULL, NULL, NULL\n};\n\n\n", lpOutFile);

   if(infile!=NULL) fclose(infile);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutInvertedURgFrmsTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
FILE *outfile;
const unsigned char **pnts;
const unsigned char *c_sav;
unsigned char str_buf[TV_XE_INV_1_COL+1];
int str_buf_i[TV_XE_INV_1_COL+1];
const unsigned char *pntr;
unsigned char *pntw;
int slen;

   outfile=fopen((const char *)lpszFileName, "w");
   if(outfile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

// ---------------------------------------
// plpszaUnRegForms_l
   pnts=plpszaURgFrms;

   while((*pnts) && SUCCEEDED(retc))
   {
      c_sav=*pnts;
      pnts++;

#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         if(*pnts)
         {
            if(strlen(*pnts)>TV_XE_UNREG_COL_WDT)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
            pnts++;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         if(*pnts)
         {
#ifdef Debug
if(strcmp(*pnts, "IÐK")==0)
slen=0;
#endif
            slen=strlen(*pnts);
            if(slen>TV_XE_UNREG_COL_WDT)
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, *pnts, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               pntw=str_buf;
               pntr=(*pnts)+slen;

               while(pntr>(*pnts)) *(pntw++)=(*(--pntr));
               *pntw=Nul;
            }                   
         
            if(SUCCEEDED(retc))                    
            {
               slen=strlen(str_buf);
               retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
            }                   
            if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
            if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
            if(SUCCEEDED(retc))                    
               retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);
                   
            if(SUCCEEDED(retc))                    
               retc=TvPutSN(outfile, str_buf, TV_XE_UNREG_COL_WDT);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

#ifndef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         if(*pnts)
         {
            if(strlen(*pnts)>TV_XE_UNREG_COL_WDT)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
            pnts++;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

// -------------------------------
      if(SUCCEEDED(retc))
      {
         if(*pnts) pnts++;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      
#ifdef WITH_DIACR
      if(SUCCEEDED(retc))
      {
         if(*pnts) pnts++;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         if(*pnts)
         {             
            if(SUCCEEDED(retc)) strcpy(str_buf, *pnts);

            if(SUCCEEDED(retc))                    
            {
               slen=strlen(str_buf);
               retc=KptStrEncode(str_buf_i, str_buf, &slen, TV_XE_CTBL);
            }                   
            if(SUCCEEDED(retc)) str_buf_i[slen]=C_Nul;   
            if(SUCCEEDED(retc)) TvIStrLwr(str_buf_i);
            if(SUCCEEDED(retc))                    
               retc=KptStrDecode(str_buf, str_buf_i, TvIntStrLen(str_buf_i), TV_XE_CTBL);

            if(strlen(str_buf)<=TV_XE_UNREG_COL_WDT)
               retc=TvPutSN(outfile, str_buf, TV_XE_UNREG_COL_WDT);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
            pnts++;
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

#ifndef WITH_DIACR
      if(*pnts) pnts++;
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(SUCCEEDED(retc))
      {
         if(c_sav)
         {
            if(strlen(c_sav)<=TV_XE_GRGR_COL_WDT)
               retc=TvPutSN(outfile, c_sav, TV_XE_GRGR_COL_WDT);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         fprintf(outfile, "\n");
         if(ferror(outfile) || feof(outfile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
      }

   } // while((*pnts) && SUCCEEDED(retc))

   if(outfile!=NULL)
   {
      if(fclose(outfile)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::PutURgFrmsTbl(unsigned char *lpszFileName)
{
HRESULT retc=S_OK;
FILE *infile;
unsigned char col1_buf[TV_XE_UNREG_COL_WDT+2+1];
unsigned char col2_buf[TV_XE_UNREG_COL_WDT+2+1];
unsigned char grgr_buf[TV_XE_COL_WDT+2+1];
unsigned char *pntw;
unsigned char *pntr;
unsigned char col1_inverted[TV_XE_UNREG_COL_WDT+1+2];
bool end_fl=FALSE;
char format[200];

   infile=NULL;

   infile=fopen((const char *)lpszFileName, "r");
   if(infile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      sprintf(format, "(unsigned char *)%c%ds, (unsigned char *)%c%ds, (unsigned char *)%c%ds,\n",
                      '%', TV_XE_COL_WDT, '%', TV_XE_UNREG_COL_WDT, '%', TV_XE_UNREG_COL_WDT);

      fputs("// -------------------------------------------------\n", lpOutFile);
      fprintf(lpOutFile, "unsigned char *plpszauUnRegForms_%c[] = \n", uiFId);
      fputs("{\n", lpOutFile);

      if(ferror(lpOutFile) || feof(lpOutFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
   }

   while(!end_fl && SUCCEEDED(retc))
   {
      fgets((char *)col1_buf+1, TV_XE_UNREG_COL_WDT+1, infile);
      fgets((char *)col2_buf+1, TV_XE_UNREG_COL_WDT+1, infile);
      fgets((char *)grgr_buf+1, TV_XE_COL_WDT+1, infile);

      if(ferror(infile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFileName, True, __FILE__, __LINE__, 0L, NULL);
      if(feof(infile)) end_fl=TRUE;

      if(!end_fl && SUCCEEDED(retc))
      {
         col1_buf[TV_XE_UNREG_COL_WDT+1]=Nul;
         col2_buf[TV_XE_UNREG_COL_WDT+1]=Nul;
         grgr_buf[TV_XE_GRGR_COL_WDT+1]=Nul;

         retc=CutTrailSpcs(col1_buf+1);
         if(SUCCEEDED(retc)) retc=CutTrailSpcs(col2_buf+1);

// invert unreg form
         if(SUCCEEDED(retc))
         {
            pntw=col1_inverted+1;
            pntr=col1_buf+1+strlen((const char *)col1_buf+1);
            while(pntr>col1_buf+1) *(pntw++)=(*(--pntr));
            *pntw=Nul;

// enclose in ""
            col1_inverted[0]='\"';
            strcat((char *)col1_inverted, "\"");
            col2_buf[0]='\"';
            strcat((char *)col2_buf, "\"");
            grgr_buf[0]='\"';
            strcat((char *)grgr_buf, "\"");

            fprintf(lpOutFile, format, grgr_buf, col1_inverted, col2_buf);

            if(ferror(lpOutFile) || feof(lpOutFile))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
         
         } // if(SUCCEEDED(retc))

      } // if(!end_fl && SUCCEEDED(retc))

   } // while(!end_fl && SUCCEEDED(retc))

   if(SUCCEEDED(retc)) fputs("   NULL, NULL, NULL\n};\n", lpOutFile);

   if(infile!=NULL) fclose(infile);

return(retc);
}


// ================================================== public methods of TvXmlEcm_tag
// --------------------------------------------------
TvXmlEcm_tag::TvXmlEcm_tag
(
const unsigned int uiFileIdn,
const unsigned char **plpszaToGrForm,
const unsigned char *lpszToMainForm,
const unsigned char *lpszForms,
const unsigned char **plpszaPrefixTable,
const unsigned char **plpszaEndSkipTable,
const unsigned char **plpszaUnRegForms
)
{
unsigned char str_buf[10];

   lhOpenResult=S_OK;

   lpOutFile=NULL;
   lpszFName[0]=Nul;

   uiFId=uiFileIdn;

   plpszaTGrFrm=plpszaToGrForm;
   lpszTMnFrm=lpszToMainForm;
   lpszFrms=lpszForms;
   plpszaPrefixTbl=plpszaPrefixTable;
   plpszaESkpTbl=plpszaEndSkipTable;
   plpszaURgFrms=plpszaUnRegForms;

   if((lpszTMnFrm==NULL) || (lpszFrms==NULL) ||
      (plpszaESkpTbl==NULL) || (plpszaURgFrms==NULL))
         lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(lhOpenResult))
   {
#if OsGr==Unix
      strcpy((char *)lpszFName, "/home/kp/source/tev/xml/");
#else
      lpszFName[0]=Nul;
#endif
      strcat((char *)lpszFName, KP_LNG_CFNAM);
      str_buf[0]=(unsigned char)uiFileIdn; str_buf[1]=Nul;
      strcat((char *)lpszFName, (const char *)str_buf);
      strcat((char *)lpszFName, "c.cpp");

      lpOutFile = fopen((const char *)lpszFName, "w");
      if(lpOutFile==NULL)

         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
   }
}


// --------------------------------------------------
TvXmlEcm_tag::~TvXmlEcm_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::GetOpenResult(void)
{
return(lhOpenResult);
}

 
// --------------------------------------------------
HRESULT TvXmlEcm_tag::Process()
{
HRESULT retc=S_OK;
unsigned char fname[KP_MAX_FNAME_LEN+1];
char com_buf[KP_MAX_FNAME_LEN+20+1];

   retc=CheckTables();


   if(SUCCEEDED(retc)) retc=PutHat();

   if(SUCCEEDED(retc)) retc=TvUniFname.Generate(fname);

   if(SUCCEEDED(retc)) retc=PutFullPrefixTbl(fname);
   if(SUCCEEDED(retc)) retc=SortTextFile(fname, TRUE);
   if(SUCCEEDED(retc)) retc=PutPrefixTbl(fname);

   if(SUCCEEDED(retc)) retc=PutInvertedESkpTbl(fname);
   if(SUCCEEDED(retc)) retc=SortTextFile(fname, TRUE);
   if(SUCCEEDED(retc)) retc=PutCompactedESkpTbl(fname);

   if(SUCCEEDED(retc)) retc=PutInvertedURgFrmsTbl(fname);
   if(SUCCEEDED(retc)) retc=SortTextFile(fname, TRUE);
   if(SUCCEEDED(retc)) retc=PutURgFrmsTbl(fname);

#if OsGr==Unix
   strcpy(com_buf, "rm ");
#else
   strcpy(com_buf, "del ");
#endif
   strcat(com_buf, (const char *)fname);
   system(com_buf);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlEcm_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(lpOutFile!=NULL)
   {
      if(fclose(lpOutFile)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L, NULL);
      lpOutFile=NULL;
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(void)
{
HRESULT retc=S_OK;
HRESULT retc0;

   printf("\nEndings joining\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

// ---------------------------
   KP_NEWO(pTvXmlEcm, TvXmlEcm_tag(KP_LNG_LIT, (const unsigned char **)plpszaToGrForm_l,
                                 (const unsigned char *)lpszToMainForm_l,
                                 (const unsigned char *)lpszForms_l,
                                 (const unsigned char **)plpszaPrefixes_l,
                                 (const unsigned char **)plpszaEndSkipTable_l,
                                 (const unsigned char **)plpszaUnRegForms_l));
   
   if(SUCCEEDED(retc)) retc=pTvXmlEcm->Process();

   if(pTvXmlEcm!=NULL)
   {
      retc0=pTvXmlEcm->CloseFiles(TRUE);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(pTvXmlEcm);
   }
   

// ---------------------------
   KP_NEWO(pTvXmlEcm, TvXmlEcm_tag(KP_LNG_GER, (const unsigned char **)plpszaToGrForm_l, // plpszaToGrForm_v, !!!
                                 (const unsigned char *)lpszToMainForm_l, // lpszToMainForm_v, !!!
                                 (const unsigned char *)lpszForms_l, // lpszForms_v !!!
                                 (const unsigned char **)plpszaPrefixes_v,
                                 (const unsigned char **)plpszaEndSkipTable_v,
                                 (const unsigned char **)plpszaUnRegForms_v));
   
   if(SUCCEEDED(retc)) retc=pTvXmlEcm->Process();

   if(pTvXmlEcm!=NULL)
   {
      retc0=pTvXmlEcm->CloseFiles(TRUE);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(pTvXmlEcm);
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

// ---------------------------
#ifdef Debug
unsigned char str_buf[100];
printf("\nPress any key:");
gets((char *)str_buf);
printf("\n");
#endif

return(RET_CODE(retc));
}
