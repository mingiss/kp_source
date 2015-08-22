// ==================================================
// xmlrpt.cpp
// XML tag extractor


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlrpt.h"
#include "kpcapp.h"
#include "kpstap.h"


// ================================================== objects
const unsigned char lpszProdName[] = "xmlrpt";
int iProdVerGlob=0;

XmlRpt_tag *pXmlRpt=NULL;

KpErrorProc_tag KpErrorProc(TRUE, 43);
bool bFreeTextInUs=True;
bool bServiceFl=False;

int iazPl[] = {'p', 'l', C_Nul };                           //"plural / daugiskaita"
int iazSg[] = {'s', 'g', C_Nul };                           //"singular / vienaskaita"

int iazAux[] = {'a', 'u', 'x', C_Nul };                     //"auxiliary / pagalbinis, tarnybinis"

int iazComp[] = {'c', 'o', 'm', 'p', C_Nul };               //"comparative (degree) / aukðtesnysis (laipsnis)"
int iazSuperl[] = {'s', 'u', 'p', 'e', 'r', 'l', C_Nul };   //"superlative (degree) / aukðèiausiasis (laipsnis)"

int iazInf[] = {'i', 'n', 'f', C_Nul };                     //"infinitive / bendratis"
int iazPI[] = {'p', 'I', C_Nul };                           //"participle I / pirmasis dalyvis"
int iazPII[] = {'p', 'I', 'I', C_Nul };                     //"participle II / antrasis dalyvis"
int iazPast[] = {'p', 'a', 's', 't', C_Nul };               //"past tense / bûtasis laikas"
int iazPass[] = {'p', 'a', 's', 's', C_Nul };               //"passive (voice) / neveikiamoji (rûðis)"
int iazGer[] = {'g', 'e', 'r', C_Nul };                     //"gerund / gerundijus"


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ================================================== public methods of XmlRpt_tag
XmlRpt_tag::XmlRpt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
int ii, jj;

   lpInFileObj=NULL;
   lpOutFile=NULL;
   lhOpenResult=S_OK;

   lEntryId=0L;

   bFirstFl=True;
   iTabPosSav=iTabPos=RP_MAX_TAGS+1;
   iNumOfTabPos=0;

   for(ii=0; ii<RP_MAX_TAGS+1; ii++)
   {
      for(jj=0; jj<RP_MAX_TAGS+1; jj++) aiXmlTgArr[ii][jj]=C_Nul;
      aiValSavArr[ii][0]=C_Nul;
      aiValSavPtr[ii]=0;
      aiPrevValSavArr[ii][0]=C_Nul;
   }
   aiXmlDeclArr[0]=C_Nul;

   if(strlen((const char *)lpszInFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszInFname, TRUE, __FILE__, __LINE__, lEntryId);
   else strcpy((char *)lpszInFName, (const char *)lpszInFname);

   if(SUCCEEDED(lhOpenResult))
   {
      if(strlen((const char *)lpszOutFname)>=KP_MAX_FNAME_LEN)
         lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszOutFname, TRUE, __FILE__, __LINE__, lEntryId);
      else strcpy((char *)lpszOutFName, (const char *)lpszOutFname);
   }

   KP_NEWO(lpInFileObj, XmlO1_tag(lpszInFName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain, alpszIndexNames, aiIndexWidths, XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True));

   if(SUCCEEDED(lhOpenResult))
   {
      KP_NEWO(lpOutFile, 
#ifdef RP_OUT_FILE_UTF8
         UcFile_tag(lpszOutFName, UC_UTF_8, (const unsigned char *)"w"));
#else
         TvXml8File_tag(lpszOutFName, (const unsigned char *)"wb", XL_FT_DataFile, True));
#endif

#ifndef RP_OUT_FILE_UTF8
      if(SUCCEEDED(lhOpenResult))
         lhOpenResult=lpOutFile->SetEncoding(UC_PlainText, RP_CODE_TABLE);
#endif
   }
}


// --------------------------------------------------
XmlRpt_tag::~XmlRpt_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::DeclineXmlTag(const unsigned char *lpszTag)
{
HRESULT retc=S_OK;
int ii;
unsigned char tag_buf[TV_XL_MAX_TAG_WDT+1];
unsigned char *pnts;
int ar_ptr;

   for(ar_ptr=0; ar_ptr<RP_MAX_TAGS; ar_ptr++) if(aiXmlDeclArr[ar_ptr]==C_Nul) break;
   if(ar_ptr>=RP_MAX_TAGS)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszTag, TRUE, __FILE__, __LINE__, lEntryId);

   if(SUCCEEDED(retc))
   {
      for(ii=0; ii<XC_LastDictTag-XC_FirstDictTag; ii++)
      {
         strncpy((char *)tag_buf, (const char *)plpszaXmlttDictTags[ii], TV_XL_MAX_TAG_WDT);
         tag_buf[TV_XL_MAX_TAG_WDT]=Nul;
         pnts=tag_buf;
         while((*pnts!=Spc) && (*pnts!=TV_XM_TagEndCh) && (*pnts!=Nul)) pnts++;
         *pnts=Nul;
         if(strcmp(tag_buf+1, lpszTag+1)==0)
         {
            aiXmlDeclArr[ar_ptr]=XC_FirstDictTag+ii;
            break;
         }
      }

      if(ii>=XC_LastDictTag-XC_FirstDictTag)
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, lpszTag, TRUE, __FILE__, __LINE__, lEntryId);

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::AcceptXmlTag(const unsigned char *lpszTag)
{
HRESULT retc=S_OK;
int ii;
unsigned char tag_buf[TV_XL_MAX_TAG_WDT+1];
unsigned char in_buf[TV_XL_MAX_TAG_WDT+1];
unsigned char *pnts;
const unsigned char *pntin;
unsigned char *pntbuf;
int ar_ptr;
int lok_ptr;

   for(ar_ptr=0; ar_ptr<RP_MAX_TAGS; ar_ptr++) if(aiXmlTgArr[ar_ptr][0]==C_Nul) break;
   if(ar_ptr>=RP_MAX_TAGS)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszTag, TRUE, __FILE__, __LINE__, lEntryId);

   if(SUCCEEDED(retc))
   {
      iNumOfTabPos=ar_ptr+2;

      lok_ptr=0;
      pntin=lpszTag;
      while((*pntin!=Nul) && SUCCEEDED(retc))
      {
         pntbuf=in_buf;
         while((*pntin!=Nul) && (*pntin!='/') && SUCCEEDED(retc)) *(pntbuf++)=(*pntin++);
         *pntbuf=Nul;
         if(*pntin=='/') pntin++;

         for(ii=0; ii<XC_LastDictTag-XC_FirstDictTag; ii++)
         {
            strncpy((char *)tag_buf, (const char *)plpszaXmlttDictTags[ii], TV_XL_MAX_TAG_WDT);
            tag_buf[TV_XL_MAX_TAG_WDT]=Nul;
            pnts=tag_buf;
            while((*pnts!=Spc) && (*pnts!=TV_XM_TagEndCh) && (*pnts!=TV_XM_EndTagIndCh) && (*pnts!=Nul)) pnts++;
            *pnts=Nul;
            if(strcmp(tag_buf+1, in_buf)==0)
            {
               if(lok_ptr<RP_MAX_TAGS)
                  aiXmlTgArr[ar_ptr][lok_ptr++]=XC_FirstDictTag+ii;
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszTag, TRUE, __FILE__, __LINE__, lEntryId);
               break;
            }
         }

         if(ii>=XC_LastDictTag-XC_FirstDictTag)
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, lpszTag, TRUE, __FILE__, __LINE__, lEntryId);

      } // while((*pntin!=Nul) && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::PutSeId(void)
{
HRESULT retc=S_OK;
unsigned char out_str[TV_TAG_LEN+1];

   if(bFirstFl) bFirstFl=False;
   else
   {
#ifdef RP_OUT_FILE_UTF8
      retc=lpOutFile->PutCharProc(C_Lf, True, False); // '\n'
#else
      retc=lpOutFile->PutChar(C_Lf, True); // '\n'
#endif
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)out_str, "%06ld", lEntryId);
#ifdef RP_OUT_FILE_UTF8
      retc=lpOutFile->PutStrProc(out_str);
#else
      retc=lpOutFile->PutStr(out_str);
#endif
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::PutChar(KpChar iInChar)
{
HRESULT retc=S_OK;
unsigned char out_str[TV_TAG_LEN+1];
KpChar out_ch;

   out_ch=iInChar;

#ifdef RP_OUT_FILE_UTF8
   retc=lpOutFile->PutCharProc(out_ch, False, False);
#else
   switch(out_ch)
   {
   case C_hhyph: out_ch=C_hyph; break;
   case C_Lang: out_ch=C_Less; break;
   case C_Rang: out_ch=C_Great; break;
   case C_QemSpc: out_ch=C_Spc; break;
   }
   retc=lpOutFile->PutChar(TvClearAccent(out_ch), True);
#endif

   if(retc==KP_E_UNKN_CHR)
   {
      sprintf((char *)out_str, "%d", iInChar);
      if(iInChar<C_CharSize0)
      {
         if(plpszaXmlSpecCharTagsMain[iInChar]!=NULL)
         {
#ifdef RP_OUT_FILE_UTF8
            retc=lpOutFile->PutStrProc(plpszaXmlSpecCharTagsMain[iInChar]);
#else
            retc=lpOutFile->PutStr(plpszaXmlSpecCharTagsMain[iInChar]);
#endif
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, TRUE, __FILE__, __LINE__, lEntryId);
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, TRUE, __FILE__, __LINE__, lEntryId);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::PutStrInt(const KpChar *iazOutStr)
{
HRESULT retc=S_OK;
int jj;
unsigned char ch_out;

   for(jj=0; (iazOutStr[jj]!=C_Nul) && (jj<KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc); jj++)
   {
//    switch(in_ch)
//    {
//       case XC_Parenth: in_ch='('; break;
//       case XC_Parenth_e: in_ch=')'; break;
//       case XC_Asterix: in_ch='*'; break;
//    }

      if((iazOutStr[jj]>=XC_FirstDictTag) && (iazOutStr[jj]<XC_LastDictTag))
      {
#ifdef RP_OUT_FILE_UTF8
         retc=lpOutFile->PutStrProc(plpszaXmlttDictTags[iazOutStr[jj]-XC_FirstDictTag]);
#else
         retc=lpOutFile->PutStr(plpszaXmlttDictTags[iazOutStr[jj]-XC_FirstDictTag]);
#endif
      }
      else
      {
         retc=KptCharDecode(&ch_out, iazOutStr[jj], lpOutFile->m_iCodeTable);
         if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
            retc=PutChar(C_Quest); // '?'
         else
            retc=PutChar(iazOutStr[jj]);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::ProcessPrevVals(void)
{
HRESULT retc=S_OK;
int last_tag;
int last_prev_tag;
int ii;

   last_tag=iNumOfTabPos;
   while((aiValSavArr[last_tag][0]==C_Nul) && (last_tag>0)) last_tag--;

   if(last_tag==iNumOfTabPos-1)
   {
      if(aiPrevValSavArr[1][0]!=C_Nul)
      {
         last_prev_tag=iNumOfTabPos;
         while((aiPrevValSavArr[last_prev_tag][0]==C_Nul) && (last_prev_tag>0)) last_prev_tag--;

         retc=PutSeId();

         for(ii=1; (ii<=last_prev_tag) && SUCCEEDED(retc); ii++)
         {
#ifdef RP_OUT_FILE_UTF8
            retc=lpOutFile->PutCharProc(C_Ht, True, False); // '\t'
#else
            retc=lpOutFile->PutChar(C_Ht, True); // '\t'
#endif
            if(SUCCEEDED(retc)) retc=PutStrInt(aiPrevValSavArr[ii]);
         }

         for(ii=last_prev_tag+1; (ii<=iNumOfTabPos-1) && SUCCEEDED(retc); ii++)
         {
#ifdef RP_OUT_FILE_UTF8
             retc=lpOutFile->PutCharProc(C_Ht, True, False); // '\t'
#else
             retc=lpOutFile->PutChar(C_Ht, True); // '\t'
#endif
             if(SUCCEEDED(retc)) retc=PutStrInt(aiValSavArr[ii]);
         }
      }
   }
   else
   {
      for(ii=0; (ii<=iTabPosSav) && ( ii<RP_MAX_TAGS+1); ii++)
         TvKpStrCpy(aiPrevValSavArr[ii], aiValSavArr[ii]);
      for(ii=iTabPosSav+1; ii<RP_MAX_TAGS+1; ii++) aiPrevValSavArr[ii][0]=C_Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch, in_ch1;
int spc_sav;
bool first_non_space;
int last_char;
XmlTagPars_tag *tag_par=NULL;
int par_num;
const int *pnti, *pnts;
int *pntd;
int ii;
int val_sav[KP_MAX_FILE_LIN_LEN+1];
static unsigned char val_buf[MAX_XML_PAR_VAL_LEN + 1];
int cur_val_ptr;
int msg_len;

   if((lpInFileObj==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", TRUE, __FILE__, __LINE__, lEntryId);

   bFirstFl=True;
   iTabPosSav=iTabPos=RP_MAX_TAGS+1;

   while(SUCCEEDED(retc))
   {
      iTabPosSav=iTabPos;

      retc=lpInFileObj->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, False, True);

      if(SUCCEEDED(retc))
      {
         if(in_ch==XC_StEntry)
         {
            if(tag_par!=NULL)
            {
               if(SUCCEEDED(retc)) retc=ProcessPrevVals();

               if(SUCCEEDED(retc)) retc=tag_par->SeekNumPar("id", &lEntryId, &par_num);
#ifdef Debug
if(lEntryId==32)
lEntryId=32;
#endif
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, lEntryId);
               KP_DELETE(tag_par);

               if(SUCCEEDED(retc)) retc=PutSeId();
               if(SUCCEEDED(retc))
               {
                  iTabPosSav=iTabPos=0;
                  for(ii=iTabPos; ii<RP_MAX_TAGS+1; ii++)
                  {
                     aiValSavPtr[ii]=0;
                     aiValSavArr[ii][0]=C_Nul;
                     aiPrevValSavArr[ii][0]=C_Nul;
                  }
               }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lEntryId);
         }
         else
         {
            for(ii=0; ii<RP_MAX_TAGS+1; ii++)
            {
               pnti=TvKpStrChr(aiXmlTgArr[ii], in_ch);
               if(pnti!=NULL) break;
            }
// process tag parameters and contents
            if(pnti!=NULL)
            {
               iTabPos=(pnti-(int *)aiXmlTgArr)/(RP_MAX_TAGS+1)+1;

               if(iTabPos<=iTabPosSav)
               {
                  retc=ProcessPrevVals();
                  if(SUCCEEDED(retc)) retc=PutSeId();
                  iTabPosSav=0;
               }

               TvKpStrCpy(val_sav, aiValSavArr[iTabPos]);

               for(ii=iTabPos; ii<RP_MAX_TAGS+1; ii++)
               {
                  aiValSavPtr[ii]=0;
                  aiValSavArr[ii][0]=C_Nul;
               }

// tag parameters
               if((tag_par!=NULL) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc))
                  {
                     cur_val_ptr=TvKpStrLen(aiValSavArr[iTabPos]);

                     retc=tag_par->SeekTextPar("href", val_buf, &par_num);
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else if(SUCCEEDED(retc))
                     {
                        msg_len=KP_MAX_FILE_LIN_LEN-cur_val_ptr;
                        if(strlen(val_buf)>=msg_len)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                        if(SUCCEEDED(retc))
                           retc=KptStrEncode(aiValSavArr[iTabPos]+cur_val_ptr, val_buf, /* &msg_len, */ lpOutFile->m_iCodeTable);
                        if((retc==KP_E_UNKN_CHR) ||(retc==KP_E_FONT_UNDEF))
                           retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, lEntryId);
                        if(SUCCEEDED(retc))
                        {
                           cur_val_ptr+=msg_len;
                           if(cur_val_ptr>=KP_MAX_FILE_LIN_LEN-2)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                        }
                        if(SUCCEEDED(retc))
                        {
                           aiValSavArr[iTabPos][cur_val_ptr++]=C_Colon; // ':'
                           aiValSavArr[iTabPos][cur_val_ptr]=C_Nul;
                        }
                     }
                  }

                  if(SUCCEEDED(retc))
                  {
                     cur_val_ptr=TvKpStrLen(aiValSavArr[iTabPos]);

                     retc=tag_par->SeekTextPar("src", val_buf, &par_num);
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else if(SUCCEEDED(retc))
                     {
                        msg_len=KP_MAX_FILE_LIN_LEN-cur_val_ptr;
                        if(strlen(val_buf)>=msg_len)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                        if(SUCCEEDED(retc))
                           retc=KptStrEncode(aiValSavArr[iTabPos]+cur_val_ptr, val_buf, /* &msg_len, */ lpOutFile->m_iCodeTable);
                        if((retc==KP_E_UNKN_CHR) ||(retc==KP_E_FONT_UNDEF))
                           retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, lEntryId);
                        if(SUCCEEDED(retc))
                        {
                           cur_val_ptr+=msg_len;
                           if(cur_val_ptr>=KP_MAX_FILE_LIN_LEN-2)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                        }
                        if(SUCCEEDED(retc))
                        {
                           aiValSavArr[iTabPos][cur_val_ptr++]=C_Colon; // ':'
                           aiValSavArr[iTabPos][cur_val_ptr]=C_Nul;
                        }
                     }
                  }
               }

               KP_DELETE(tag_par);

               if(SUCCEEDED(retc)) aiValSavPtr[iTabPos]=TvKpStrLen(aiValSavArr[iTabPos]);

// tag contents
#ifdef RP_OUT_FILE_UTF8
               retc=lpOutFile->PutCharProc(C_Ht, True, False); // '\t'
#else
               retc=lpOutFile->PutChar(C_Ht, True); // '\t'
#endif
               for(ii=iTabPosSav+1; (ii<iTabPos) && SUCCEEDED(retc); ii++)
               {
                  if(SUCCEEDED(retc)) retc=PutStrInt(aiValSavArr[ii]);
#ifdef RP_OUT_FILE_UTF8
                  retc=lpOutFile->PutCharProc(C_Ht, True, False); // '\t'
#else
                  retc=lpOutFile->PutChar(C_Ht, True); // '\t'
#endif
               }

               spc_sav=C_Nul;
               first_non_space=True;
               last_char=C_Nul;

               if(SUCCEEDED(retc))
                  if(plpszaXmlttDictTags[*pnti+1-XC_FirstDictTag]!=NULL)
                     if(plpszaXmlttDictTags[*pnti+1-XC_FirstDictTag][0]!=C_Nul)
                        do
               {
                  retc=lpInFileObj->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, False, True);
                  KP_DELETE(tag_par);

                  if((in_ch!=((*pnti)|1)) && SUCCEEDED(retc))
                  {
                     if(
                        (in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag) &&
                        (in_ch!=XC_Parenth) && (in_ch!=XC_Parenth_e) &&
                        (strlen(plpszaXmlttDictTags[(in_ch|1)-XC_FirstDictTag])!=0)
                       )
                     {
                        do
                        {
                           retc=lpInFileObj->GetCharProc(&in_ch1, &tag_par, XL_IX_DataFile, False, True);
                           KP_DELETE(tag_par);

                        } while((in_ch1!=(in_ch|1)) && SUCCEEDED(retc));
                     }
                     else // if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag) ...
                     {
                        if((TvStrChr(lpszSpcEol, in_ch)!=NULL) || (in_ch==C_NBSP)) in_ch=Spc;

                        if(in_ch==Spc) spc_sav=in_ch;
                        else
                        {
// put saved spaces - skip duplicate, leading and trailing spaces
                           if((spc_sav!=C_Nul) && (in_ch!=XC_Parenth_e) && (last_char!=XC_Parenth) && SUCCEEDED(retc))
                           {
                              if(!first_non_space)
                              {
                                 if(aiValSavPtr[iTabPos]<KP_MAX_FILE_LIN_LEN)
                                    aiValSavArr[iTabPos][aiValSavPtr[iTabPos]++]=spc_sav;
                                 else
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                              }
                           }
                           spc_sav=C_Nul;
                           first_non_space=False;
// put character
                           if(SUCCEEDED(retc))
                           {
                              if(aiValSavPtr[iTabPos]<KP_MAX_FILE_LIN_LEN)
                                 aiValSavArr[iTabPos][aiValSavPtr[iTabPos]++]=in_ch;
                              else
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
                           }

                           last_char=in_ch;

                        } // else // if(in_ch==Spc)

                     } // else // if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))

                  } // if((in_ch!=((*pnti)|1)) && SUCCEEDED(retc))

               } while((in_ch!=((*pnti)|1)) && SUCCEEDED(retc));

               aiValSavArr[iTabPos][aiValSavPtr[iTabPos]]=C_Nul;

// suppress secondary gram forms (not parts of speech)
               if(SUCCEEDED(retc))
               {
                  if(
                     (*pnti==XC_PartOfSpeechSrc) &&
                     (
                        (TvKpStrCmp(aiValSavArr[iTabPos], iazPl)==0) ||
                        (TvKpStrCmp(aiValSavArr[iTabPos], iazSg)==0) ||

// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazAux)==0) ||

// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazComp)==0) ||
// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazSuperl)==0) ||

// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazInf)==0) ||
// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazPI)==0) ||
// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazPII)==0) ||
// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazPast)==0) ||
                        (TvKpStrCmp(aiValSavArr[iTabPos], iazPass)==0) // ||
// !!!                  (TvKpStrCmp(aiValSavArr[iTabPos], iazGer)==0)
                     )
                    )
                     TvKpStrCpy(aiValSavArr[iTabPos], val_sav);
               }

// eliminate <pt></pt> pairs
               if(SUCCEEDED(retc))
               {
                  pnts=aiValSavArr[iTabPos];
                  pntd=aiValSavArr[iTabPos];
                  while(*pnts!=C_Nul)
                  {
                     if((*pnts==XC_Parenth) && (*(pnts+1)==XC_Parenth_e)) pnts+=2;
                     else *(pntd++)=(*pnts++);
                  }
                  *pntd=C_Nul;
               }

               if(SUCCEEDED(retc)) retc=PutStrInt(aiValSavArr[iTabPos]);

            } // if(pnti!=NULL)
            else
            {
               pnti=TvKpStrChr(aiXmlDeclArr, in_ch);
               if(pnti!=NULL)
               {
// skip tag contents
// does not process subtags - until first closing tag - second (embedded) opening tag is possible !!!
                  if(SUCCEEDED(retc)) do
                  {
                     retc=lpInFileObj->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, False, True);
                     KP_DELETE(tag_par);

                  } while((in_ch!=((*pnti)|1)) && SUCCEEDED(retc));

               } // if(pnti!=NULL)

            } // else // if(pnti!=NULL)

         } // else // if(in_ch==XC_StEntry)

      } // if(SUCCEEDED(retc))

      KP_DELETE(tag_par);

   } // while(SUCCEEDED(retc))

#ifdef RP_OUT_FILE_UTF8
   /* retc= */lpOutFile->PutCharProc(C_Lf, True, False); // '\n'
#else
   /* retc= */lpOutFile->PutChar(C_Lf, True); // '\n'
#endif

return(retc);
}


// --------------------------------------------------
HRESULT XmlRpt_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;

   if(lpOutFile!=NULL)
   {
      retc=lpOutFile->CloseFile(bCheckFileExist);
      KP_DELETE(lpOutFile);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lEntryId);
   }

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lEntryId);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
char *l_argv[3+2*RP_MAX_TAGS+1];
int ii;

   printf("\nXML tag extractor\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc>3)
   {
      for(ii=0; (ii<argc) && (ii<3+2*RP_MAX_TAGS+1); ii++) l_argv[ii]=argv[ii];
   }
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
//    l_argc=4;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="/home/kp/source/tev/mcm/kpn1.xml";
//    l_argv[2]="/home/kp/source/tev/mcm/kpn1_tw.txt";
//    l_argv[3]="tw";

//    l_argc=9;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="/home/kp/source/tev/alk/spl.xml";
//    l_argv[2]="/home/kp/source/tev/alk/rpt.txt";
//    l_argv[3]="hw/v/scw";
//    l_argv[4]="ps";
//    l_argv[5]="tw";
//    l_argv[6]="-eg";
//    l_argv[7]="-id";
//    l_argv[8]="-ic";

//    l_argc=5;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="d:\\kp\\source\\tev\\otel\\otel.xml";
//    l_argv[2]="d:\\kp\\source\\tev\\otel\\kpn1.txt";
//    l_argv[3]="hw";
//    l_argv[4]="tw/cd/xd/gr/dp/un/fun/tn";

//    l_argc=4;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="d:\\kp\\source\\tev\\mcm\\mcm_out\\mcm.xml";
//    l_argv[2]="d:\\kp\\source\\tev\\mcm\\l_index.txt";
//    l_argv[3]="tw/cd/xd/gr/dp/un/fun/tn";

//    l_argc=4;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="d:/kp/source/tev/otel/otel.xml";
//    l_argv[2]="d:/kp/source/tev/otel/otel_le.txt";
//    l_argv[3]="tw/cd/xd";

//    l_argc=5;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="d:/kp/source/tev/otel/otel.xml";
//    l_argv[2]="d:/kp/source/tev/otel/otel_le.txt";
//    l_argv[3]="hw";
//    l_argv[4]="v/vn/ef/base/hbase/mc/cw/lc/ld/ls/lo/lu/lw/le/li";

//    l_argc=6;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="f:/wrk/kp/source/tev/vlz/vlz_a.xml";
//    l_argv[2]="f:/wrk/kp/source/tev/vlz/vlz_a.txt";
//    l_argv[3]="hw";
//    l_argv[4]="v/vn/ef/bhw/hbase/mc/cw/scw/ld/ls/lo/lu/lw/le/li";
//    l_argv[5]="tw";

//    l_argc=6;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="f:/wrk/kp/source/tev/lvz/lvz_geo/lvz_geo.xml";
//    l_argv[2]="f:/wrk/kp/source/tev/lvz/lvz_geo/lvz_geo.txt";
//    l_argv[3]="hw";
//    l_argv[4]="v/vn/ef/base/hbase/mc/cw/lc/ld/ls/lo/lu/lw/le/li";
//    l_argv[5]="tw";

//    l_argc=6;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="f:/wrk/kp/source/tev/vlz/vlz_v.xml";
//    l_argv[2]="f:/wrk/kp/source/tev/vlz/vlz_v.txt";
//    l_argv[3]="hw";
//    l_argv[4]="v/vn/ef/bhw/hbase/mc/cw/scw/ld/ls/lo/lu/lw/le/li";
//    l_argv[5]="tw";

//    l_argc=4;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="f:/kp/source/tev/mcm/mcm_out/emc1.xml";
//    l_argv[2]="f:/kp/source/tev/mcm/eq_rpt.txt";
//    l_argv[3]="eq/img";

//    l_argc=4;
//    l_argv[0]="xmlrpt";
//    l_argv[1]="f:/kp/source/tev/mcm/mcm_out/emc1.xml";
//    l_argv[2]="f:/kp/source/tev/mcm/xr_rpt_1.txt";
//    l_argv[3]="xr";

      l_argc=5;
      l_argv[0]="xmlrpt";
//    l_argv[1]="d:/kp/source/tev/otel/otel.xml";
      l_argv[1]="g:/kp/source/tev/aklz/aklz_d.xml";
//    l_argv[2]="d:/kp/source/tev/otel/otel_le.txt";
      l_argv[2]="f:/kp/source/tev/aklz/kpn1.txt";
      l_argv[3]="tw";
      l_argv[4]="hw";

   }
#endif

   if((l_argc>3) && (l_argc<=3+2*RP_MAX_TAGS))
   {
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pXmlRpt, XmlRpt_tag((unsigned char *)(l_argv[1]), (unsigned char *)(l_argv[2])));

         if(SUCCEEDED(retc))
            for(ii=3; (ii<l_argc) && SUCCEEDED(retc); ii++)
            {
               if(l_argv[ii][0]=='-') retc=pXmlRpt->DeclineXmlTag((const unsigned char *)(l_argv[ii]));
               else retc=pXmlRpt->AcceptXmlTag((const unsigned char *)(l_argv[ii]));
            }

         if(SUCCEEDED(retc)) retc=pXmlRpt->Process();

         if(pXmlRpt!=NULL)
         {
            retc0=pXmlRpt->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlRpt);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlrpt.exe infile.xml outfile.lst tw\n");
      printf("                                                     ^\n");
      printf("                                   tag to extract ---'\n\n");

      printf("               c:>xmlrpt.exe infile.xml outfile.lst hw/v/scw ps tw -eg -id -ic\n");
      printf("                                                    `------' `---' `---------'\n");
      printf("                                                        ^      ^        ^\n");
      printf("                  tag group to extract into the same ---'      |        |\n");
      printf("                     (first) tab position                      |        |\n");
      printf("                  tags to extract to next tab positions -------'        |\n");
      printf("                  tags, which contents must be skipped -----------------'\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}
