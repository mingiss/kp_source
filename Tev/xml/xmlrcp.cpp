// ==================================================
// xmlrcp.cpp
// search for compounds with no headword translation (':' needed)


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpttucf.h"

#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlrcp.h"


// ================================================== objects
XmlRcp_tag *pXmlRcp=NULL;

KpErrorProc_tag KpErrorProc(TRUE, 43);


// ================================================== public methods of XmlRcp_tag
XmlRcp_tag::XmlRcp_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{

   lpInFileObj=NULL;
   lpOutFile=NULL;
   lhOpenResult=S_OK;

   lEntryId=0L;

   lpiazHwSav[0]=C_Nul;
   iHwPtr=0;
   bHwInput=False;
   bCpdReached=bTrReached=False;

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
                                       alpszIndexNames, aiIndexWidths, XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlNulCodeTables));

   KP_NEW(lpOutFile, UcFile_tag(lpszOutFName, UC_UTF_8, (const unsigned char *)"w"));
}


// --------------------------------------------------
XmlRcp_tag::~XmlRcp_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::PutSeId(void)
{
HRESULT retc=S_OK;
unsigned char out_str[TV_TAG_LEN+1];

   if(SUCCEEDED(retc))
   {
      sprintf((char *)out_str, "%06ld", lEntryId);
      retc=lpOutFile->PutStrProc(out_str);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::PutChar(int iInChar)
{
HRESULT retc=S_OK;
unsigned char out_str[TV_TAG_LEN+1];

   retc=lpOutFile->PutCharProc((Chars16)iInChar, False, False);

   if(retc==KP_E_UNKN_CHR)
   {
      sprintf((char *)out_str, "%d", iInChar);
      if(iInChar<C_CharSize0)
      {
         if(plpszaXmlSpecCharTags[iInChar]!=NULL)
            retc=lpOutFile->PutStrProc(plpszaXmlSpecCharTags[iInChar]);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, TRUE, __FILE__, __LINE__, lEntryId);
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, out_str, TRUE, __FILE__, __LINE__, lEntryId);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::PutStrInt(const int *iazOutStr)
{
HRESULT retc=S_OK;
int jj;

   for(jj=0; (iazOutStr[jj]!=C_Nul) && (jj<KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc); jj++)
   {
//    switch(in_ch)
//    {
//       case XC_Parenth: in_ch='('; break;
//       case XC_Parenth_e: in_ch=')'; break;
//       case XC_Asterix: in_ch='*'; break;
//    }

      if((iazOutStr[jj]>=XC_FirstDictTag) && (iazOutStr[jj]<XC_LastDictTag))
         retc=lpOutFile->PutStrProc(plpszaXmlttDictTags[iazOutStr[jj]-XC_FirstDictTag]);
      else
         retc=PutChar(iazOutStr[jj]);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_par=NULL;
int par_num;

   if((lpInFileObj==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", TRUE, __FILE__, __LINE__, lEntryId);

   while(SUCCEEDED(retc))
   {
      retc=lpInFileObj->GetCharProc(&in_ch, &tag_par, XL_IX_DataFile, FALSE);

      if(SUCCEEDED(retc))
      {
         switch(in_ch)
         {
         case XC_StEntry:
            if(tag_par!=NULL)
            {

               if(bCpdReached && (!bTrReached))
               {
                  if(SUCCEEDED(retc)) retc=PutSeId();
                  if(SUCCEEDED(retc)) retc=PutChar(C_Spc);
                  if(SUCCEEDED(retc)) retc=PutStrInt(lpiazHwSav);
                  if(SUCCEEDED(retc)) retc=PutChar(C_Lf);
               }
               
               lpiazHwSav[0]=C_Nul;
               iHwPtr=0;
               bHwInput=False;
               bCpdReached=bTrReached=False;
               
               if(SUCCEEDED(retc)) retc=tag_par->SeekNumPar("id", &lEntryId, &par_num);

               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, lEntryId);
               KP_DELETE(tag_par);

            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lEntryId);
            break;

         case XC_HeadWord:
            bHwInput=True;
            break;

         case XC_HeadWord_e:
            bHwInput=False;
            break;

         case XC_TranslGroup:
         case XC_TrWord:
         case XC_Gloss:
         case XC_ModCpdDst:
            if(!bCpdReached) bTrReached=True;
            break;

         case XC_CompoundGroup:
         case XC_StructGroup:
         case XC_DerivGroup:
         case XC_PhrGroup:
         case XC_CompoundWord:
         case XC_Struct:
         case XC_OblStruct:
         case XC_Derivative:
         case XC_SrcWord:
         case XC_SingleCpdWord:
            bCpdReached=True;
            break;

         default:
            if(bHwInput)
            {
               if(iHwPtr<KP_MAX_FILE_LIN_LEN)
               {
                  lpiazHwSav[iHwPtr++]=in_ch;
                  lpiazHwSav[iHwPtr]=C_Nul;
               }
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, lEntryId);
            }
            break;
         
         } // switch(in_ch)

      } // if(SUCCEEDED(retc))

   } // while(SUCCEEDED(retc))

   if(bCpdReached && (!bTrReached))
   {
      if(SUCCEEDED(retc)) retc=PutSeId();
      if(SUCCEEDED(retc)) retc=PutChar(C_Spc);
      if(SUCCEEDED(retc)) retc=PutStrInt(lpiazHwSav);
      if(SUCCEEDED(retc)) retc=PutChar(C_Lf);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlRcp_tag::CloseFiles(bool bCheckFileExist)
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
char *l_argv[3];
int ii;

   printf("\nXML compounds finder\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      for(ii=0; ii<argc; ii++) l_argv[ii]=argv[ii];
   }
// #ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=3;
      l_argv[0]="xmlrcp";
      l_argv[1]="d:\\kp\\source\\tev\\otel\\otel.xml";
      l_argv[2]="d:\\kp\\source\\tev\\otel\\kpn1.txt";
   }
// #endif

   if(l_argc==3)
   {
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pXmlRcp, XmlRcp_tag((unsigned char *)(l_argv[1]), (unsigned char *)(l_argv[2])));

         if(SUCCEEDED(retc)) retc=pXmlRcp->Process();
         
         if(pXmlRcp!=NULL)
         {
            retc0=pXmlRcp->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlRcp);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlrcp.exe infile.xml outfile.lst\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
