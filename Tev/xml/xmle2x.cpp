// ==================================================
// xmle2x.cpp
// SGML CTBL-43 to TEX converter
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmlt2x0.h"
#include "xmle2x.h"
#include "xmlsty.h"


// ================================================== objects
KpErrorProc_tag KpErrorProc(TRUE, 71);
XmlE2X *pXmlE2X=NULL;
bool bServiceFl=False;

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------------------------
HRESULT XmlNode::TestChildContents(int /* iTestTag */, KpChar *lpiazTestValue, bool *pFoundFlg)
{
HRESULT retc=S_OK;

   if(pFoundFlg==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pFoundFlg=False;
      if(lpiazTestValue==NULL) *pFoundFlg=True;
   }

return(retc);
}


XmlE2X::XmlE2X(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
// :XmlT2X0(lpszInFname, lpszOutFname)
{
   XmlT2X0_constructor(lpszInFname, lpszOutFname, False);
}

      
// --------------------------------------------------
HRESULT XmlE2X::OpenFilesLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;
unsigned char str_buf[100];
FILE *f_tmp=NULL;

   if(((lpszInFname==NULL) || (lpszOutFname==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpInFileObj = new XmlI(m_lpszInFileName, (const unsigned char *)"rb", CreateNew8File,
                                       plpszaXmlSpecCharTagsEdi,
                                       NULL, NULL, caIxLangs, iaIxEncodings,
                                       XC_FirstDictTag, plpszaSgmDictTags,
                                       XM_VERS_SGML /* XM_VERS_SGML_TAGE */ /* kad gaudytø entities */, 
                                       iaSgmCodeTablesEdi, True, False, True);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

// if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_UTF_PlainText, TV_MAIN_SGM_CTBL, TV_MAIN_SGM_CTBL);
// if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_PlainText, TV_CTBL_TRANSPARENT, TV_CTBL_TRANSPARENT);
   if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_PlainText, TV_MAIN_SGME_CTBL, TV_MAIN_SGME_CTBL);


   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }
                                                          
   if(SUCCEEDED(retc))
   {
      f_tmp=fopen((char *)m_lpszOutFileName, "r");
      if(f_tmp!=NULL)
      {
         fclose(f_tmp);
         
         printf("\nFailas %s jau yra, ar norite ji istrinti? (T/N):", m_lpszOutFileName);
         gets((char *)str_buf);
         printf("\n");
         if((str_buf[0]!='T') && (str_buf[0]!='t')) retc=KP_E_CANCEL;
      }
   }
                                                               
   if(SUCCEEDED(retc))
   {
      m_lpOutFileObj = new TvTexFile(m_lpszOutFileName, (const unsigned char *)"w", iNumOfTexTagsLocal);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlE2X::Process(void)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars *tag_pars=NULL;
XmlNode *cur_entry=NULL;
XmlNode *env_entry=NULL;
int char_pos=0;
KpChar last_char=C_Nul;
int num_of_chars=0;
KpChar prev_tag=XC_Nul;
long ll;
int par_num;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {    
      do
      {     
         KP_DELETE(tag_pars);

         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, True);

      } while((in_ch!=XC_HeadWordGroup) && SUCCEEDED(retc));
                      
      if(SUCCEEDED(retc))
      {
         if(tag_pars!=NULL)
         {
            retc=tag_pars->SeekNumPar("id", &ll, &par_num);
            if(SUCCEEDED(retc)) m_lEntryId=ll;
            else m_lEntryId++;
         }
         else m_lEntryId++;
      }
      
      KP_DELETE(tag_pars);

      KpErrorProc.SetLPar(m_lEntryId);
         
      if(SUCCEEDED(retc))
      {                                                      
         cur_entry=new XmlNode(in_ch, NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaSgmDictTags, NULL);
         if(cur_entry==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);
      if(SUCCEEDED(retc)) retc=cur_entry->IncreaseIndent(); 

//---------------             
      if(SUCCEEDED(retc))
      {                                                      
         tag_pars=new XmlTagPars((const unsigned char *)"id", m_lEntryId);
         if(tag_pars==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }             
                   
      if(SUCCEEDED(retc))
      {                                                      
         env_entry=new XmlNode(XC_StEntry, tag_pars, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaSgmDictTags, NULL);
         if(cur_entry==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
      }

      KP_DELETE(tag_pars);

      if(SUCCEEDED(retc)) retc=env_entry->AppendChild(cur_entry);
      if(SUCCEEDED(retc))
      {
         cur_entry=env_entry;
         env_entry=NULL;
      }
      
//---------------             
//    if(SUCCEEDED(retc)) retc=cur_entry->DelLevelTags(FullLevel);
      if(SUCCEEDED(retc)) retc=cur_entry->ProcessLevel(FullLevel, True);

//---------------             
      if(SUCCEEDED(retc)) retc=cur_entry->CreateGrpCounters(); 

// -----------------
      if(SUCCEEDED(retc)) retc=LocalEntryProc(cur_entry);

// -----------------
//    if(SUCCEEDED(retc)) retc=cur_entry->InsertDelimiters(XC_FirstDictTag, XC_LastDictTag);

// -----------------
//    if(SUCCEEDED(retc)) retc=cur_entry->Hyphenate(); 

// -----------------
      char_pos=0;
      last_char=C_Nul;
      num_of_chars=0;
      prev_tag=XC_Nul;
      if(SUCCEEDED(retc)) retc=cur_entry->CountCharactersTex(&num_of_chars, prev_tag, False);
      if(SUCCEEDED(retc)) retc=cur_entry->WriteTex(m_lpOutFileObj, &char_pos,
                  MAXLONG, 0, num_of_chars, XC_Dict, prev_tag, &last_char, False);

//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(C_Lf, TexNoType, False, LAST_WORD_LEN);
                                               
      KP_DELETE(cur_entry);

   } while(SUCCEEDED(retc));

   KpErrorProc.SetLPar(0L);
   if(retc==KP_E_EOF) retc=S_OK;

return(retc);
}


// ================================================== main
//---------------------------------------------
HRESULT GetLetMetrics(const unsigned char *lpszbLetL, /* const */ unsigned char *lpszbLetter, unsigned char *lpszFullLetter, int *piBoxWdt, int *piDown)
{
HRESULT retc=S_OK;

   strcpy(lpszFullLetter, lpszbLetter);

        if(lpszbLetL[0]=='A'){ strcpy(lpszFullLetter, lpszFullLetterA); *piBoxWdt=iBoxWdtA;  *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'); }
   else if(lpszbLetL[0]=='B'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'); }
   else if(lpszbLetL[0]=='C')
   {
      if(lpszbLetL[1]!='_'){                                            *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'); }
      else{                                                             *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   }
   else if(lpszbLetL[0]=='D'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='E'){ strcpy(lpszFullLetter, lpszFullLetterE); *piBoxWdt=iBoxWdtE;  *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='F'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='G'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='H'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='I'){ strcpy(lpszFullLetter, lpszFullLetterI); *piBoxWdt=iBoxWdtI;  *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='J'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='K'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='L'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='M'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='N'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='O'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='P'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='R'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'); }
   else if(lpszbLetL[0]=='S')
   {
      if(lpszbLetL[1]!='_'){                                            *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'); }
      else{                                                             *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   }
   else if(lpszbLetL[0]=='T'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='U'){ strcpy(lpszFullLetter, lpszFullLetterU); *piBoxWdt=iBoxWdtU;  *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='V'){                                          *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'+1); }
   else if(lpszbLetL[0]=='Z')
   {
      if(lpszbLetL[1]!='_'){                                            *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'-2); }
      else{                                                             *piBoxWdt=3;         *piDown=iInitDown+iLetHight*(lpszbLetL[0]-'A'-1); }
   }

   else if((lpszbLetL[0]=='0') || (lpszbLetL[0]=='1')){                 *piBoxWdt=4;         *piDown=iInitDown+iLetHight*('A'-'A'); }

return(retc);
}


//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
unsigned char *l_argv[4];
const unsigned char *pnt_let; 
unsigned char letter[10];     
unsigned char full_letter[10];
unsigned char letl[10];       
int box_wdt;
int down;

   printf("\nXML to SGML Tage dictionary converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc==4)
      {
         l_argv[0]=(unsigned char *)argv[0];
         l_argv[1]=(unsigned char *)argv[1];
         l_argv[2]=(unsigned char *)argv[2];
         l_argv[3]=(unsigned char *)argv[3];
      }
#ifdef Debug
      else // if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=4;

         l_argv[0]=(unsigned char *)"xmle2x";

//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lvtt/lvtte.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lvtt/lvt_pvze.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/aklz/aklz_a.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/aklz/aklz_e.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/aklz/kpn2.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/mcm/mcm_sgm/mac_a.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/mcm/kpn1.sgm";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/aklz/kpn2.sgm";
         l_argv[1]=(unsigned char *)"f:/kp/source/tev/aklz/kpn1.sgm";

//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/lvtt/lvtt.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/lvtt/lvt_pvz.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/aklz/aklz_a.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/aklz/aklz_e.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/aklz/kpn2.tex";
//       l_argv[2]=(unsigned char *)"d:/Local/Tev/mac/mac_a/mac_a.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/mcm/kpn1.tex";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/aklz/kpn2.tex";
         l_argv[2]=(unsigned char *)"f:/kp/source/tev/aklz/kpn1.tex";
         
         l_argv[3]=(unsigned char *)"1";
        
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==4)
      {
         pXmlE2X = new XmlE2X((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlE2X!=NULL)
         {
            retc=pXmlE2X->GetOpenResult();

            if(SUCCEEDED(retc))
            {
               strcpy(letl, "A");
               strcpy(letter, "A");
      
               pnt_let=strchr(l_argv[2], '.');
               if(pnt_let!=NULL)
               {
                  if(pnt_let>l_argv[2])
                  {
                     if(*(pnt_let-1)=='_')
                     {
                        if(pnt_let>l_argv[2]+1)
                        {
                           letl[0]=toupper(*(pnt_let-2));
                           strcpy(letl+1, "_");
      
                           switch(toupper(*(pnt_let-2)))
                           {
                           case 'C': letter[0]='¦'; break;
                           case 'S': letter[0]='¡'; break;
                           case 'Z': letter[0]='¹'; break;
                           }
                        }
                     }
                     else letl[0]=letter[0]=toupper(*(pnt_let-1));
                  }
               }
            }
            
            if(SUCCEEDED(retc))
            {
               strcpy(full_letter, letter);
               retc=GetLetMetrics(letl, letter, full_letter, &box_wdt, &down);
            }

            if(SUCCEEDED(retc)) retc=pXmlE2X->WriteHeader(letter, full_letter, l_argv[3], box_wdt, down);

            if(SUCCEEDED(retc)) retc=pXmlE2X->Process();

            if(SUCCEEDED(retc)) retc=pXmlE2X->WriteTail(letl, (unsigned char *)"");

            retc0=pXmlE2X->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlE2X);

//          if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmle2x.exe infile.sgm outfile.tex 1\n");
         printf("                                                    ^\n");
         printf("               Start page number -------------------'\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}
