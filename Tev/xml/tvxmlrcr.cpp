// ==================================================
// tvxmlrcr.cpp
// XML references corrector


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"

#include "tvmain.h"
#include "kpttucf.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlo2.h"
#include "xmlis.h"
#include "tvxmlrcr.h"


// ================================================== objects
TvXmlRcr_tag *pTvXmlRcr=NULL;
// TvXmlFmse_tag *pTvXmlFmse=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);
int SortMode=KP_LNG_LIT;
bool bFreeTextInUs=True;


// =============================================
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}
   

// ================================================== public methods of TvXmlRcr_tag
TvXmlRcr_tag::TvXmlRcr_tag(const unsigned char **plpszInFnames, int iNumOfInFiles, const unsigned char *lpszOutFname /* , long lMaxSeIxInit */)
: XmlO2_tag()
{
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fnam[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];

   KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(lhOpenResult))
      lhOpenResult=OpenFiles(plpszInFnames, iNumOfInFiles, (const unsigned char *)"rb",
                           lpszOutFname, (const unsigned char *)"w");

   if(SUCCEEDED(lhOpenResult)) lhOpenResult=TvFnameSplit(disk, path, fnam, type, plpszInFnames[0]);
   if(SUCCEEDED(lhOpenResult)) SortMode=tolower(fnam[0]);

// lMaxSeIx=lMaxSeIxInit;
}


// --------------------------------------------------
TvXmlRcr_tag::~TvXmlRcr_tag(void)
{
   XmlO2_tag_destructor();
}


// --------------------------------------------------
HRESULT TvXmlRcr_tag::Process(void)
{
HRESULT retc=S_OK;
bool eof_fl=FALSE;
int in_ch;
XmlTagPars_tag *tag_par=NULL;
bool in_dict=FALSE;
bool after_dict=FALSE;
int ii;
// long ll;
int ch;
XmlTagPars_tag *tag_par1=NULL;

   if((lpInFileObjs[0]==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutXmlHat(lpOutFileObj, m_lpszOutFname);

   if(SUCCEEDED(retc))
      do
      {
         retc=lpInFileObjs[0]->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, FALSE);
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }

         if(!eof_fl && SUCCEEDED(retc))
         {
            switch(in_ch)
            {

            case XC_Version:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_DocType:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
//             else
//                if(strcmp((const char *)str_par, (const char *)TV_XM_DtdName)!=0)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_StyleSheet:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
//             else
//                if(strcmp((const char *)str_par, (const char *)TV_XM_CssName)!=0)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_Dict:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               in_dict=TRUE;
               break;

            case XC_Dict_e:
               if(!in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               in_dict=FALSE;
               after_dict=TRUE;
               break;

            default:
               if((!in_dict) && (TvStrChr(lpszSpcEol, in_ch)==NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);

               if(SUCCEEDED(retc))
                  switch(in_ch)
                  {
                  case XC_NrtEntry:
                     lLastIdx=0;
                     if(tag_par!=NULL) retc=tag_par->SeekNumPar("id", &lLastIdx, &ii);

                     retc=TransferField(XC_NrtEntry, XC_NrtEntry_e, XL_IX_DataFile /* XL_IX_NoIndex */,
                                             0L, FALSE, FALSE, FALSE, tag_par);
                     break;

                  case XC_StEntry:
                     if(SUCCEEDED(retc))
                        retc=lpInFileObjs[0]->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, TRUE);
                     if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                        retc=lpInFileObjs[0]->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                     KP_DELETE(tag_par1);

                     lLastIdx=0;
                     if(tag_par!=NULL) retc=tag_par->SeekNumPar("id", &lLastIdx, &ii);

                     KpErrorProc.SetLPar(lLastIdx);

//                   ll=lLastIdx;
//                   if(ll==0)
//                   {
//                      ll=lMaxSeIx;
//                      if(lMaxSeIx!=0) lMaxSeIx++;
//                   }

                     if(SUCCEEDED(retc)) retc=lpOutFileObj->SetIndent((const unsigned char *)"", XL_IX_DataFile);

                     if(SUCCEEDED(retc)) retc=TransferField(XC_StEntry, XC_StEntry_e, XL_IX_SeIndex,
                                             0L, FALSE, FALSE, FALSE, tag_par);
                     break;

                  default:
                     if(TvStrChr(lpszSpcEol,in_ch)==NULL)
                        retc=KpErrorProc.OutputErrorMessage(TV_E_FREE_CHARS, null, FALSE, __FILE__, __LINE__, lLastIdx);
                     break;

                  }

               break;
            
            } // switch(in_ch)

         } // if(!eof_fl && SUCCEEDED(retc))

         KP_DELETE(tag_par);

      } while(!eof_fl && SUCCEEDED(retc));

   KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(retc)) retc=PutXmlTail(lpOutFileObj);

return(retc);
}


//------------------------------
#if FALSE

// ================================================== public methods of TvXmlFmse_tag
TvXmlFmse_tag::TvXmlFmse_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlO2_tag()
{
   lhOpenResult=OpenFile(lpszInFname, (const unsigned char *)"rb",
                           lpszOutFname, (const unsigned char *)"w");
}


// --------------------------------------------------
TvXmlFmse_tag::~TvXmlFmse_tag(void)
{
   XmlO2_tag_destructor();
}


// --------------------------------------------------
HRESULT TvXmlFmse_tag::Process(long *plMaxSeIndex)
{
HRESULT retc=S_OK;
bool eof_fl=FALSE;
int in_ch;
XmlTagPars_tag *tag_par=NULL;
bool in_dict=FALSE;
bool after_dict=FALSE;
long max_ix;
int ii;
long ll;

   max_ix=0L;

   if((lpInFileObj==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      do
      {
         retc=lpInFileObj->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, FALSE);
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }

         if(!eof_fl && SUCCEEDED(retc))
         {
            switch(in_ch)
            {

            case XC_Version:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_DocType:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
//             else
//                if(strcmp((const char *)str_par, (const char *)TV_XM_DtdName)!=0)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_StyleSheet:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
//             else
//                if(strcmp((const char *)str_par, (const char *)TV_XM_CssName)!=0)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               break;

            case XC_Dict:
               if(in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               in_dict=TRUE;
               break;

            case XC_Dict_e:
               if(!in_dict || after_dict)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
               in_dict=FALSE;
               after_dict=TRUE;
               break;

            default:
               if((!in_dict) && (TvStrChr(lpszSpcEol, in_ch)==NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);

               if(SUCCEEDED(retc))
                  switch(in_ch)
                  {
                  case XC_NrtEntry:
                     lLastIdx=0;
                     if(tag_par!=NULL) retc=tag_par->SeekNumPar("id", &lLastIdx, &ii);

                     retc=lpInFileObj->SkipToCharProc(XC_NrtEntry_e, XL_IX_DataFile);
                     break;

                  case XC_StEntry:
                     lLastIdx=0;
                     if(tag_par!=NULL) retc=tag_par->SeekNumPar("id", &lLastIdx, &ii);
                     
                     ll=lLastIdx;
                     if(max_ix<ll) max_ix=ll;
                     retc=lpInFileObj->SkipToCharProc(XC_StEntry_e, XL_IX_DataFile);
                     break;

//                default:
//                   if(TvStrChr(lpszSpcEol,in_ch)==NULL)
//                      retc=KpErrorProc.OutputErrorMessage(TV_E_FREE_CHARS, null, FALSE, __FILE__, __LINE__, lLastIdx);
//                   break;

                  }
               break;
                
            }  // switch(in_ch)

         } // if(!eof_fl && SUCCEEDED(retc))

         KP_DELETE(tag_par);

      } while(!eof_fl && SUCCEEDED(retc));

   *plMaxSeIndex=max_ix+1;

return(retc);
}

#endif

// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
// long max_ix=0;
int l_argc;
const unsigned char *l_argv[MAX_NUM_OF_LIST_ENTRIES+2];
int ii;
#ifdef Debug
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
#endif


#ifdef Debug
// int polinkis[] = {C_p, C_o, C_l, C_i, C_n, C_k, C_i, C_s, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)polinkis, TvIntStrLen(polinkis), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);

// int polinki[] = {C_p, C_o, C_l, C_i, C_n, C_k, C_i_Ogon, C_Nul};      
// Chars16ToIndexEntry(str_buf, (Chars16 *)polinki, TvIntStrLen(polinki), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);
// retc=KptStrDecode(str_buf, polinki, TvIntStrLen(polinki), TV_XE_CTBL);

// int polinki1[] = {C_V, C_I, C_D, C_U, C_T, C_I, C_N, C_I_Ogon, C_Spc, C_V, C_A, C_R, C_T, C_O, C_J, C_I, C_M, C_O, C_Spc, C_P, C_O, C_L, C_I, C_N, C_K, C_I_Ogon, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)polinki1, TvIntStrLen(polinki1), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);

// int paveldejims[] = {C_M, C_O, C_K, C_E, C_S, C_T, C_I, C_S, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)paveldejims, TvIntStrLen(paveldejims), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);

// int paveldejim[] = {C_M, C_O, C_K, C_E, C_S, C_T, C_I_Ogon, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)paveldejim, TvIntStrLen(paveldejim), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);

// int taton[] = {C_T, C_A_Circ, C_T, C_O, C_N, C_N, C_E, C_M, C_E, C_N, C_T, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)taton, TvIntStrLen(taton), KP_MAX_FILE_LIN_WDT, KP_LNG_ENG);

// int comparisons[] = {C_C, C_O, C_M, C_hyph, C_P, C_A, C_R, C_I, C_S, C_O, C_N, C_S, C_Spc, C_O, C_F, C_Spc, C_U, C_T, C_I, C_L, C_I, C_T, C_Y, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)comparisons, TvIntStrLen(comparisons), KP_MAX_FILE_LIN_WDT, KP_LNG_ENG);

// int str_int[] = {C_N, C_A, C_M, C_A, C_S, C_Numb, C_Nul};
// Chars16ToIndexEntry(str_buf, (Chars16 *)str_int, TvIntStrLen(str_int), KP_MAX_FILE_LIN_WDT, KP_LNG_LIT);
#endif


   printf("\nXML references correction\n");
   printf(  "(Input file indexes must be allready sorted with xmlicv.exe)\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if((argc>=3) && (argc<=MAX_NUM_OF_LIST_ENTRIES+2))
      for(ii=0; ii<argc; ii++) l_argv[ii]=(const unsigned char *)argv[ii];
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
//    l_argc=3;
      l_argc=4;

      l_argv[0]=(const unsigned char *)"tvxmlrcr";
      
//    l_argv[1]=(const unsigned char *)"/home/kp/source/tev/mcm/kpn1.xml";
//    l_argv[1]=(const unsigned char *)"d:\\kp\\source\\tev\\mcm\\kpn1.xml";
//    l_argv[1]=(const unsigned char *)"d:\\kp\\source\\tev\\mcm\\mcm_out\\mcm.xml";
//    l_argv[1]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm.xml";
//    l_argv[1]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\mcm_out\\mcmc.xml";
//    l_argv[1]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\kpn1.xml";
      l_argv[1]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\mcm_out\\emcc.xml";
      
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcmx2.xml";
//    l_argv[2]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\mcm_out\\mcmx2.xml";
//    l_argv[2]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\kpn2.xml";
      l_argv[2]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\mcm_out\\emcx2.xml";

//    l_argv[3]=(const unsigned char *)"/home/kp/source/tev/mcm/kpn2.xml";
//    l_argv[3]=(const unsigned char *)"d:\\kp\\source\\tev\\mcm\\kpn2.xml";
//    l_argv[3]=(const unsigned char *)"d:\\kp\\source\\tev\\mcm\\mcm_out\\mcm1.xml";
//    l_argv[3]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm1.xml";
//    l_argv[3]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\mcm_out\\mcm1.xml";
      l_argv[3]=(const unsigned char *)"f:\\kp\\source\\tev\\mcm\\kpn2.xml";
   }
#endif

   if((l_argc>=3) && (l_argc<=MAX_NUM_OF_LIST_ENTRIES+2))
   {

#if FALSE
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pTvXmlFmse, TvXmlFmse_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc = pTvXmlFmse->Process(&max_ix);

         if(pTvXmlFmse!=NULL)
         {
            retc0=pTvXmlFmse->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pTvXmlFmse);
      }
#endif

      if(SUCCEEDED(retc))
      {
         KP_NEWO(pTvXmlRcr, TvXmlRcr_tag(l_argv+1, l_argc-2, (unsigned char *)l_argv[l_argc-1] /* , max_ix */));

         if(SUCCEEDED(retc)) retc=pTvXmlRcr->Process();
         
         if(pTvXmlRcr!=NULL)
         {
            retc0=pTvXmlRcr->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pTvXmlRcr);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>TvXmlRcr.exe infile.xml outfile.xml\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
printf("\nPress any key:");
gets((char *)str_buf);
printf("\n");
#endif

return(RET_CODE(retc));
}

