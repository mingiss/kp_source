// Dump c_XXXX.nls code page file of WinNT/2000

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include	<stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"

#include "tvxml.h"

// ================================================== KpErrorProc_tag local functions
KpErrorProc_tag KpErrorProc(TRUE, 71);

// --------------------------------------------------
HRESULT KpErrorProc_tag::FormatErrorMessage
(
	const HRESULT lhRetc,
	unsigned char *lpszMsg
)
{
return(FormatErrorMessageMain(lhRetc, lpszMsg));
}


// --------------------------------------------------
main()
{
FILE *in_file;
int in_word;
int kpt_char;
int in_char;
const unsigned char *char_name;
int ii;
int jj;
int kk;
HRESULT retc=S_OK;

   in_file=fopen("c_773.nls","rb");
   if(in_file!=NULL)
   {
      fread(&in_word, 2, 1, in_file); // signature 0x000D

      fread(&in_word, 2, 1, in_file);    // code table number

      fread(&in_word, 2, 1, in_file);   // coding byte count - must be 1

      for(ii=0; ii<4; ii++) fread(&in_word, 2, 1, in_file); // signature 0x003F x 4

      for(ii=0; ii<6; ii++) fwrite(&in_word, 2, 1, in_file); // signature 0 x 6

      fread(&in_word, 2, 1, in_file); // DOS codepage size, must be 0x0203

      for(kk=0; (kk<2) && SUCCEEDED(retc); kk++)   // Windows & DOS tables
      {                       // codepage to Unicode
         printf("Windows/DOS to Unicode ----------------------------------\n\n");

         for(ii=0; ii<KPT_Ctbsiz; ii++)
         {
            in_word=0;
            fread(&in_word, 2, 1, in_file);

            kpt_char=C_Unkn;   // kpt_char
            for(jj=0; (jj<C_Charsize1) && (kpt_char==C_Unkn); jj++)
               if((int)iaUniChars[jj]==in_word) kpt_char=jj;

            if(kpt_char==C_Unkn) char_name=(const unsigned char *)"Unknown"; // char_name
            else
            {
               if(kpt_char<C_Spc) char_name=(const unsigned char *)"ctrl";
               else
               {
                  char_name=plpszaXmlSpecCharTags[kpt_char];
                  if(char_name==NULL) char_name=(const unsigned char *)"no XML";
               }
            }
               
            printf("0x%02x %3d   0x%04x %5d %s\n", ii, ii, in_word, in_word, char_name);
         }
      
         if(kk==0) fread(&in_word, 1, 2, in_file); // 0x0100

         printf("\n");
      }

      for(ii=0; ii<2; ii++) fread(&in_word, 2, 1, in_file);  // reserved 0 x 3

      printf("Unicode to codepage ----------------------------------------\n\n");

      for(ii=0; ii<KPT_Utbsiz; ii++)  // output Unicode to codepage table
      {
         in_word=0;
         fread(&in_word, 1, 1, in_file); 

         if(ferror(in_file) || feof(in_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, NULL, TRUE, __FILE__, __LINE__, 0L);

         if((in_word!=C_Quest) && SUCCEEDED(retc))
         {
            kpt_char=C_Unkn;   // kpt_char
            for(jj=0; (jj<C_Charsize1) && (kpt_char==C_Unkn); jj++)
               if((int)iaUniChars[jj]==ii) kpt_char=jj;

            if(kpt_char==C_Unkn) char_name=(const unsigned char *)"Unknown"; // char_name
            else
            {
               if(kpt_char<C_Spc) char_name=(const unsigned char *)"ctrl";
               else
               {
                  char_name=plpszaXmlSpecCharTags[kpt_char];
                  if(char_name==NULL) char_name=(const unsigned char *)"no XML";
               }
            }
               
            in_char=in_word;  // in_char
            if(in_char<C_Spc) in_char=C_Spc;

            printf("0x%04x %5d %10s   0x%02x %3d %c\n", ii, ii, char_name, in_word, in_word, in_char);
         }
      }


      fclose(in_file);
   }
   else 
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);


return(RET_CODE(retc));
}
