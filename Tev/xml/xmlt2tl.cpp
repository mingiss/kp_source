// ==================================================
// xmlt2tl.cpp
// extract level corresponding XMLT tags 
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <iostream.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpsock.h"
#include "kpwindow.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "xmlt2tl.h"


#if Envir!=MSWin32Con
#error Envir!=MSWin32Con
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "xmlt2tl";
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(TRUE, 43);
// int SortMode=KP_LNG_LIT;
// int iDelimCtbl = TV_COMMON_DELIM_CTBL;
bool bServiceFl=False;

XmlT2TL *pXmlT2TL=NULL;

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

// --------------------------------------------------
XmlT2TL::XmlT2TL(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
   m_lhOpenResult=S_OK;

   m_lEntryId=0L;
   KpErrorProc.SetLPar(0L);

// --------------------------
   m_lpszInFileName[0]=Nul;
   m_lpInFileObj=NULL;

   m_lpszOutFileName[0]=Nul;
   m_lpOutFileObj=NULL;

// --------------------------
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=OpenFiles(lpszInFname, lpszOutFname);
}

      
// --------------------------------------------------
HRESULT XmlT2TL::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlT2TL::OpenFiles(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;
   
// --------------------------------------------------
   if((lpszInFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszInFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszInFileName, lpszInFname);
      m_lpInFileObj = new XmlI(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True, False);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

// --------------------------
   if((lpszOutFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszOutFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszOutFileName, lpszOutFname);
      m_lpOutFileObj = new XmlI(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2TL::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(m_lpOutFileObj!=NULL)
   {
      retc0=m_lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(m_lpInFileObj!=NULL)
   {
      KP_DELETE(m_lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2TL::Process(int iLevel)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars *tag_pars=NULL;
XmlNode *cur_entry = NULL;
XmlNode *first_child = NULL;
long entr_id;
int par_num;
bool found_fl=False;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   while(SUCCEEDED(retc))
   {
      do
      {
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, False);

         if((in_ch==XC_StEntry) && SUCCEEDED(retc))
         {
            m_lEntryId++;
            entr_id=0L;
            if(tag_pars!=NULL) retc=tag_pars->SeekNumPar("id", &entr_id, &par_num);
            if(entr_id!=0L)
            {
               KpErrorProc.SetLPar(entr_id);
               m_lEntryId=entr_id;
            }
            else KpErrorProc.SetLPar(m_lEntryId);

            if((cur_entry!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               cur_entry = new XmlNode(in_ch, tag_pars, NULL, (const unsigned char *)"",
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       NULL);
               if(cur_entry==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();
         }
         KP_DELETE(tag_pars);

      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

// ------------------------- process level
//    if(SUCCEEDED(retc)) retc=cur_entry->SupressToLevel(iLevel);
//    if(SUCCEEDED(retc)) retc=cur_entry->DelLevelTags(iLevel);
//    if(SUCCEEDED(retc)) retc=cur_entry->DelTags(XC_Level);
//    if(SUCCEEDED(retc)) retc=cur_entry->UpLevelGroups();
//    if(SUCCEEDED(retc)) retc=cur_entry->DelEmptyTags();
//    if(SUCCEEDED(retc)) retc=cur_entry->RenumCtgMng();
      if(SUCCEEDED(retc)) retc=cur_entry->ProcessLevel(iLevel, False);

// -------------------------
      if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);

// -------------------------
      KP_DELETE(cur_entry);
      
      /* retc= */ KpErrorProc.SetLTxt((const unsigned char *)"");

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

   KpErrorProc.SetLPar(0L);

return(retc);
}


//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
unsigned char *l_argv[4]; 
int ii;
int level;

   printf("\nXMLT dictionary level supressing\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc==4)
      {
         for(ii=0; ii<argc; ii++)
            l_argv[ii]=(unsigned char *)argv[ii];
      }

#ifdef Debug
      else // if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=4;
         l_argv[0]=(unsigned char *)"vlzt2tl";

         l_argv[1]=(unsigned char *)"g:/kp/source/tev/lvz05/lvza.xml";
 
         l_argv[2]=(unsigned char *)"g:/kp/source/tev/lvz05/lvza4.xml";

         l_argv[3]=(unsigned char *)"4";
      }
#endif

      if(SUCCEEDED(retc))
      {
         if(l_argc==4)
         {
            level=0;
            if(SUCCEEDED(retc)) sscanf((const char *)l_argv[3], "%d", &level);

            if(SUCCEEDED(retc))
            {
               pXmlT2TL = new XmlT2TL((const unsigned char *)l_argv[1], (const unsigned char *)l_argv[2]);
               if(pXmlT2TL!=NULL) retc=pXmlT2TL->GetOpenResult();
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {  
               if(pXmlT2TL->m_lpOutFileObj==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
               
               if(SUCCEEDED(retc)) retc=PutXmlHat(pXmlT2TL->m_lpOutFileObj->FilePtr, pXmlT2TL->m_lpszOutFileName);

               if(SUCCEEDED(retc)) retc=pXmlT2TL->Process(level);

               if(SUCCEEDED(retc)) retc=PutXmlTail(pXmlT2TL->m_lpOutFileObj->FilePtr);
               
               retc0=pXmlT2TL->CloseFiles(SUCCEEDED(retc));
               if(SUCCEEDED(retc)) retc=retc0;
            }
         }
         else // if(l_argc>=4)
         {
            printf("Bad number of parameters:\n");
            printf("   c:>xmlt2tl.exe infile.xml outfile.tex 2\n");
            printf("                                         ^\n");
            printf("      [dictionary level] ----------------'\n");
            if(SUCCEEDED(retc)) retc=E_INVALIDARG;
         }

      } // if(SUCCEEDED(retc))

      KP_DELETE(pXmlT2TL);

   } // if(SUCCEEDED(retc))

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
printf("\nPress any key:");
gets((char *)str_buf);
printf("\n");
#endif

return(RET_CODE_MAIN(retc));
}
