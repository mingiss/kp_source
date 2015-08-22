// ==================================================
// txu2t.cpp
// converting Unicode TEX file to plain text ASCII file with TEX-like spec. character encoding
//


// ================================================== definitions

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>

#include "kpstdlib.h"
#include "kpstring.h"
#include "kptt.h"
#include "kpttucf.h"
#include "kperr.h"

#include "tvmain.h"
#include "tvtex.h"

#include "txu2t.h"


// ================================================== objects
TxU2T_tag *pTxU2T=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);

// ================================================== public methods of TxU2T_tag
TxU2T_tag::TxU2T_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
   lhOpenResult=S_OK;

// --------------------------
   lpszInFileName[0]=Nul;
   lpInFileObj=NULL;
   if(lpszInFname==NULL)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) if(strlen(lpszInFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      strcpy(lpszInFileName, lpszInFname);
      KP_NEWO(lpInFileObj, UcFile_tag(lpszInFileName, UC_UTF_16, (const unsigned char *)"rb"));
   }

// --------------------------
   lpszOutFileName[0]=Nul;
   lpOutFileObj=NULL;
   if((lpszOutFname==NULL) && SUCCEEDED(lhOpenResult))
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) if(strlen(lpszOutFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      strcpy(lpszOutFileName, lpszOutFname);
      KP_NEW(lpOutFileObj, ofstream);
      if(lpOutFileObj != NULL)
      {
         lpOutFileObj->open((const char *)lpszOutFileName);
         if(lpOutFileObj->fail())
         {
            KP_DELETE(lpOutFileObj);
            lhOpenResult = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
         }
      }
   }
}


// --------------------------------------------------
TxU2T_tag::~TxU2T_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT TxU2T_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(lpOutFileObj!=NULL)
   {
      lpOutFileObj->close();
      if(lpOutFileObj->fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, NULL, TRUE, __FILE__, __LINE__, 0L);

      KP_DELETE(lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TxU2T_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT TxU2T_tag::Process(void)
{
HRESULT retc=S_OK;
Chars16 in_ch;
bool put_sp;

   if((lpInFileObj==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);

   while(SUCCEEDED(retc))
   {
      retc=lpInFileObj->GetCharProc(&in_ch);
      if((in_ch>=C_Charsize1) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, NULL, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if((plpszaTexSpecCharTags[in_ch]!=NULL) && (in_ch!=C_Lf) && (in_ch!=C_Colon) && (in_ch!=C_At))
         {
            *lpOutFileObj << plpszaTexSpecCharTags[in_ch];

            put_sp=False;
            if(strlen(plpszaTexSpecCharTags[in_ch])>1) if(plpszaTexSpecCharTags[in_ch][0]=='\\')
            {
               put_sp=True;
               if(strlen(plpszaTexSpecCharTags[in_ch])>3) if(plpszaTexSpecCharTags[in_ch][2]==Spc) put_sp=False;
            }
            if(put_sp) *lpOutFileObj << Spc;
         }
         else
         {
            if(in_ch<KPT_FirstKptChar) *lpOutFileObj << (char)in_ch;
            else
            {
               if(in_ch==C_LAapost) *lpOutFileObj << '\'';
               else
               {
                  *lpOutFileObj << '?';
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, NULL, FALSE, __FILE__, __LINE__, 0L);
               }
            }
         }
         if(lpOutFileObj->fail() && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
      }

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

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

   printf("\nTEX Unicode to plain text file converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=argv[0];
      l_argv[1]=argv[1];
      l_argv[2]=argv[2];
   }
#ifdef Debug
   else
   {
      l_argc=3;
      l_argv[0]="txu2t";
      l_argv[1]="/mnt/win_d/kp/source/tev/tex/turinys.txu";
      l_argv[2]="/mnt/win_d/kp/source/tev/tex/turinys.txt";
   }
#endif

   if(l_argc==3)
   {
      KP_NEWO(pTxU2T, TxU2T_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

      if(SUCCEEDED(retc))
      {
         retc=pTxU2T->Process();

         retc0=pTxU2T->CloseFiles(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("   c:>txu2t.exe infile.txu outfile.txt\n");
      retc=E_INVALIDARG;
   }

   KP_DELETE(pTxU2T);

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
