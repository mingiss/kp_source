// ==================================================
// xmlt2h.cpp
// XMLT to HTML converter


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "htmt.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "xmlt2h.h"
#include "kpcapp.h"
#include "kpstap.h"


#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// ================================================== objects
const unsigned char lpszProdName[] = "xmlt2h";
const unsigned char lpszDictName[] = "xmlt2h";
int iProdVerGlob=0;
XmlT2H_tag *pXmlT2H=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------
HRESULT XmltTestEmbeddedLocal(KpChar iTagCh, KpChar iPrevTag, bool *pbEmbedded)
{
HRESULT retc=S_OK;

   if(pbEmbedded==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((iTagCh == XC_UsNoteSrc) && (iPrevTag == XC_Paragraph)) *pbEmbedded = True;
      
return(retc);
}


// ================================================== public methods of XmlT2H_tag
XmlT2H_tag::XmlT2H_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(False) 
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlT2H_tag::~XmlT2H_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlT2H_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpInFileObj = new XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                    plpszaXmlSpecCharTagsMain, 
                                    alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings, 
                                    XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                    XM_VERS_XML10, iaXmlNulCodeTables, True, True, False);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }


   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpOutFileObj = new XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       NULL,
                                       NULL, NULL, caIxLangs, iaIxEncodings, 
                                       XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_HTML_TAGE /* XM_VERS_HTML401_TRANS */, iaXmlNulCodeTables, True, False, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2H_tag::Process(bool /* bTrimSpaces */)
{
HRESULT retc=S_OK;
KpChar in_ch;
KpChar test_ch;
XmlTagPars_tag *tag_pars=NULL;
int cur_tag;
bool emb_fl;
int par_num;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(m_lpOutFileObj->FilePtr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(m_lpOutFileObj->FilePtr->fFiles[0]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutHtmHat(m_lpOutFileObj->FilePtr->fFiles[0], lpszDictName /* m_lpszOutFileName */, NULL, (const unsigned char *)"tvxmlth.css",
                                       KP_LNG_LIT, 0, NULL, NULL);

// ---------------------------------- skip header
   if(SUCCEEDED(retc)) do
   {
      retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, True /* bTrimSpaces */);

      if((in_ch==XC_Dict) && SUCCEEDED(retc))
         retc=m_lpInFileObj->UnGetCharProc(in_ch, tag_pars);
      KP_DELETE(tag_pars);

   } while((in_ch!=XC_Dict) && SUCCEEDED(retc));

// ----------------------------------
   if(SUCCEEDED(retc)) do
   {
      if(SUCCEEDED(retc)) retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, True /* bTrimSpaces */);

      if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);

      if(SUCCEEDED(retc))
      {
         test_ch = in_ch;
         if(in_ch == XC_Reference_e) test_ch = XC_RefWord_e;
         if(in_ch == XC_Paragraph_e) test_ch = cur_tag + 1;
      }

      if(SUCCEEDED(retc)) retc=XmltTestEmbedded(test_ch, cur_tag, &emb_fl);
      if((!emb_fl) && (test_ch!=(cur_tag|0x01)) && (test_ch!=C_Spc) && SUCCEEDED(retc))
      {
char str_buf[100];         
         sprintf(str_buf, "%d inside of %d", test_ch, cur_tag); 
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, str_buf, False, __FILE__, __LINE__, 0L);
      }

      if((emb_fl || (test_ch==(cur_tag|0x01))) && SUCCEEDED(retc))
      {
//----------------------------
         if((in_ch==XC_StEntry) && SUCCEEDED(retc))
         {
            m_lEntryId=0L;
            if(tag_pars!=NULL) retc=tag_pars->SeekNumPar("id", &m_lEntryId, &par_num);
            KpErrorProc.SetLPar(m_lEntryId);

            if((m_lEntryId==0L) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         }

//----------------------------
         if(SUCCEEDED(retc))
         {
            if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))
            {
// tag output
               if(
                  (strcmp((const char *)plpszaXmlttDictTagsFull[(in_ch&(~1))+1-XC_FirstDictTag], "")!=0) ||
                  ((in_ch & (~0x01))==XC_Symb)
                 )
               {
                  if((in_ch & 0x01)==0)
                  {
                     if(SUCCEEDED(retc)) retc=PutOpenTag(in_ch, tag_pars);
#ifdef Debug
if(in_ch == XC_UsNoteSrc)
in_ch = XC_UsNoteSrc;

if(in_ch == XC_Paragraph)
in_ch = XC_Paragraph;
#endif
                     if((in_ch == XC_Paragraph) && SUCCEEDED(retc)) 
                        retc=PutOpenTag(cur_tag, NULL);
                     if((in_ch == XC_Reference) && SUCCEEDED(retc)) 
                        retc=PutOpenTag(XC_RefWord, NULL);
                  }
                  else
                  {
                     if((in_ch == XC_Reference_e) && SUCCEEDED(retc)) 
                        retc=PutClosingTag(XC_RefWord_e, NULL);
                     if((in_ch == XC_Paragraph_e) && SUCCEEDED(retc)) 
                        retc=PutClosingTag(cur_tag + 1, NULL);
                     if(SUCCEEDED(retc)) retc=PutClosingTag(in_ch, tag_pars);
                  }
               }
            }
            else
// ordinary character
               retc=m_lpOutFileObj->PutCharProc(in_ch, tag_pars);
         }
      }

      KP_DELETE(tag_pars);

   } while(SUCCEEDED(retc));

   KpErrorProc.SetLPar(0L);
   if(retc==KP_E_EOF) retc=S_OK;

   if(SUCCEEDED(retc)) retc=PutHtmTail(m_lpOutFileObj->FilePtr->fFiles[0]);

// if(SUCCEEDED(retc)) retc=PopTag(&m_pTagStack, &cur_tag);
// if((cur_tag!=C_Nul) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
char *l_argv[3];

   printf("\nXMLT to HTML converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=argv[0];
      l_argv[1]=argv[1];
      l_argv[2]=argv[2];
   }
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=3;

      l_argv[0]="xmlt2h";

//    l_argv[1]="f:/wrk/kp/source/tev/mcm/mcm_out/mcm1.xml";
//    l_argv[1]="f:/wrk/kp/source/tev/mcm/mcm_out/mcmx2.xml";
      l_argv[1]="f:/kp/source/tev/xml/kpn1.xml";

//    l_argv[2]="f:/wrk/kp/source/tev/mcm/mcm_out/mcm1.htm";
//    l_argv[2]="f:/wrk/kp/source/tev/mcm/mcm_out/mcmx2.htm";
      l_argv[2]="f:/kp/source/tev/xml/kpn1.htm";
   }
#endif

   if(l_argc==3)
   {
      if(SUCCEEDED(retc))
      {
         pXmlT2H = new XmlT2H_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlT2H!=NULL)
         {
            retc=pXmlT2H->GetOpenResult();

            if(SUCCEEDED(retc)) retc=pXmlT2H->Process(False);

            retc0=pXmlT2H->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlT2H);

            if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlt2h.exe infile.xml outfile.htm\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}


