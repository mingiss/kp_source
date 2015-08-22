// ==================================================
// xmlt2.cpp, former xmlx2.cpp
// XML file dump to stdout as pipe


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpttucf.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlu.h"
#include "xmlt.h"
#include "xmlt2.h"

// ================================================== objects
XmlT2_tag *pXmlT2=NULL;

KpErrorProc_tag KpErrorProc(TRUE, 43);


// ================================================== public methods of XmlT2_tag
XmlT2_tag::XmlT2_tag(const unsigned char *lpszInFname)
{
   lpInFileObj=NULL;
   lhOpenResult=S_OK;

   if(strlen((const char *)lpszInFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszInFname, TRUE, __FILE__, __LINE__, 0L);
   else strcpy((char *)lpszInFName, (const char *)lpszInFname);

   KP_NEWO(lpInFileObj, XmlO1_tag(lpszInFName, (const unsigned char *)"rb", CreateNewUniFile,
                        alpszIndexNames, aiIndexWidths, XC_FirstDictTag, plpszaXmlttDictTags,
                        XM_VERS_XML10, iaXmlNulCodeTables));
}


// --------------------------------------------------
XmlT2_tag::~XmlT2_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT XmlT2_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlT2_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlTagPars_tag *tag_par_ptr;
unsigned char par_nam[TV_TAG_LEN+1 + 1];

unsigned char *par_val = null;
   KP_NEWA(par_val, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

   if(lpInFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", TRUE, __FILE__, __LINE__, 0L);

   while(SUCCEEDED(retc))
   {
      retc=lpInFileObj->GetCharProc(&in_ch, &tag_pars, XL_IX_DataFile, FALSE);
      
      if(SUCCEEDED(retc)) printf("%d", in_ch);
      
      tag_par_ptr=tag_pars;
      while(tag_par_ptr && SUCCEEDED(retc))
      {
         retc=tag_par_ptr->GetCurTextPar(par_nam, par_val);
         if(SUCCEEDED(retc)) printf(" %s=\"%s\"", par_nam, par_val);

         if(SUCCEEDED(retc)) retc=tag_par_ptr->GetNextBranch(&tag_par_ptr);
      }

      if(SUCCEEDED(retc)) printf("\n", in_ch);

      KP_DELETE(tag_pars);

   } // while(SUCCEEDED(retc))

   printf("%d\n", EOF);

   KP_DELETE(par_val);

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);
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
char *l_argv[2];

   printf("\nXML file dump\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==2)
   {
      l_argv[0]=argv[0];
      l_argv[1]=argv[1];
   }
// #ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=2;
      l_argv[0]="xmlt2";
//    l_argv[1]="/home/kp/source/tev/lox/pvz.xml";
//    l_argv[1]="/home/kp/source/tev/vlz/vlz_a.xml";
      l_argv[1]="f:\\wrk\\kp\\source\\tev\\vlz\\vlz_xmlt\\vlz_a.xml";
   }
// #endif

   if(l_argc==2)
   {
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pXmlT2, XmlT2_tag((unsigned char *)(l_argv[1])));

         if(SUCCEEDED(retc)) retc=pXmlT2->Process();
 
         if(pXmlT2!=NULL)
         {
            retc0=pXmlT2->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlT2);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlt2.exe infile.xml\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
