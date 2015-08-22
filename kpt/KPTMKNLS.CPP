// Make c_XXXX.nls code page file for WinNT/2000

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include	<stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"


#define CODE_TABLE 49
unsigned char U_2_code[KPT_Utbsiz];


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
FILE *out_file;
int out_word;
int ii;
int jj;
int kpt_char;

   for(ii=0; ii<KPT_Utbsiz; ii++)  U_2_code[ii]=C_Quest;  // init Uinicode to codepage table

   out_file=fopen("c_773.nls","wb");
   if(out_file!=NULL)
   {
      out_word=0x000D; fwrite(&out_word, 2, 1, out_file); // signature 0x000D

      out_word=771; fwrite(&out_word, 2, 1, out_file);    // code table number

      out_word=1; fwrite(&out_word, 2, 1, out_file);      // one-byte coding

      out_word=0x003F;        // signature 0x003F x 4
      for(ii=0; ii<4; ii++) fwrite(&out_word, 2, 1, out_file);

      out_word=0;            // signature 0 x 6
      for(ii=0; ii<6; ii++) fwrite(&out_word, 2, 1, out_file);

      out_word=0x0203; fwrite(&out_word, 2, 1, out_file); // DOS codepage size

      for(ii=0; ii<2; ii++)   // Windows & DOS tables
      {                       // codepage to Unicode
         for(jj=0; jj<KPT_Ctbsiz; jj++)
         {
            if(jj<KPT_Ctbsiz/2) kpt_char=Ctptr8[CODE_TABLE*2][jj];  // lower part
            else kpt_char=Ctptr8[CODE_TABLE*2+1][jj-KPT_Ctbsiz/2]; // higher part
            if(kpt_char<0) kpt_char=C_Quest;  // 	C_Unkn, C_Noch
            out_word=iaUniChars[kpt_char];
            if((kpt_char>=0) && (out_word!=0)) U_2_code[out_word]=jj;
            
         /* if(ii==0) */ fwrite(&out_word, 2, 1, out_file);
         /* else  fwrite(&jj, 2, 1, out_file); */
         }
      
         if(ii==0){ out_word=0x0100; fwrite(&out_word, 1, 2, out_file); }
      }

      out_word=0;  // reserved 0 x 3
      for(ii=0; ii<2; ii++) fwrite(&out_word, 2, 1, out_file);

      fwrite(U_2_code, 1, KPT_Utbsiz, out_file);  // output Uinicode to codepage table

      if(ferror(out_file) || feof(out_file)) printf("File I/O error.\n");

      if(fclose(out_file)!=0) printf("Directory I/O error.\n");
   }
   else printf("Directory I/O error.\n");

return(0);
}