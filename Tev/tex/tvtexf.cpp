// ==================================================
// tvtexf.cpp
// Tex file formatting - splitting of long lines, concatenation of short lines


// ================================================== definitions
#include	<stdio.h>
#include "envir.h"
#include "kpmain.h"
#include "kptt.h"
#include "tvmain.h"
#include "tvtex.h"


//---------------------------------------------
TvErrorProc_tag TvErrorProc(TRUE, 43);


//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=TV_S_OK;
FILE *infile=NULL;
FILE *outfile=NULL;
unsigned char cc;
unsigned char last_char=Nul;
int ch_cnt=0;

   printf("\nTex file formatter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(argc!=3)
   {
      retc=TvErrorProc.OutputErrorMessage(TV_E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
      printf("               c:>tvtexf.exe infile.tex outfile.tex\n");
   }

   if(SUCCEEDED(retc))
   {
      infile=fopen(argv[1], "r");
      if(infile==NULL)
         retc=TvErrorProc.OutputErrorMessage(TV_E_FILE_NOT_FOUND, (const unsigned char *)argv[1], TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      outfile=fopen(argv[2], "w");
      if(outfile==NULL)
         retc=TvErrorProc.OutputErrorMessage(TV_E_FILE_NOT_FOUND, (const unsigned char *)argv[2], TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) do
   {
      cc=getc(infile);
      if(ferror(infile))
         retc=TvErrorProc.OutputErrorMessage(TV_E_FERROR, (const unsigned char *)argv[1], TRUE, __FILE__, __LINE__, 0L);

      if(!feof(infile) && SUCCEEDED(retc))
      {
         if(((cc=='\n') || (cc==TX_KeywordStart) || (cc==TX_CommentStart)) &&
            (last_char=='\n'))
         {
            putc(last_char, outfile);
            ch_cnt=0;
            last_char=Nul;
         }

         if((cc=='\n') || (cc==Spc))
         {
            if(last_char!='\n') last_char=cc;
         }
         else
         {
            if((last_char==Spc) || (last_char=='\n'))
            {
               if(ch_cnt>=TX_CHAR_POS_THRESHOLD)
               {
                  putc('\n', outfile);
                  ch_cnt=0;
               }
               else
               {
                  putc(Spc, outfile);
                  ch_cnt++;
               }
               last_char=Nul;
            }

            putc(cc, outfile);
            ch_cnt++;
      
         } // else // if((cc==Spc) || (cc=='\n'))

         if(ferror(outfile))
            retc=TvErrorProc.OutputErrorMessage(TV_E_FERROR, (const unsigned char *)argv[2], TRUE, __FILE__, __LINE__, 0L);

      } // if(!feof(infile) && SUCCEEDED(retc))

   } while(!feof(infile) && SUCCEEDED(retc));

   if(infile!=NULL)
   {
      if(fclose(infile)!=0)
         retc=TvErrorProc.OutputErrorMessage(TV_E_FERROR, (const unsigned char *)argv[1], TRUE, __FILE__, __LINE__, 0L);
   }

   if(outfile!=NULL)
   {
      if(fclose(outfile)!=0)
         retc=TvErrorProc.OutputErrorMessage(TV_E_FERROR, (const unsigned char *)argv[2], TRUE, __FILE__, __LINE__, 0L);
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_MAIN(retc));
}
