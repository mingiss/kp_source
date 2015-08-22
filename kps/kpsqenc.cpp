//-------------------------
// kpsqenc.cpp
// ,, '' --> " encoder for Inno Setup message files
//

#include "envir.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"

int main(void)
{
HRESULT retc=S_OK;
FILE *in_file=NULL;
FILE *out_file=NULL;
int in_ch;
int in_ch_1;

   if(SUCCEEDED(retc))
   {
      in_file=fopen("Lithuanian_MKP.txt", "r");
      if(in_file==NULL)
      {
         retc=KP_E_FILE_NOT_FOUND;
         printf("Nerandu input failo.\n");
      }
   }
   
   if(SUCCEEDED(retc))
   {
      out_file=fopen("Lithuanian_MKP.isl", "w");
      if(out_file==NULL)
      {
         retc=KP_E_DIR_ERROR;
         printf("Negaliu sukurti output failp.\n");
      }
   }

   while(SUCCEEDED(retc))
   {
      in_ch=fgetc(in_file);
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         printf("Input failo klaida.\n");
      }
      if(SUCCEEDED(retc)) if(feof(in_file)) retc=KP_E_EOF;

      if(SUCCEEDED(retc)) switch(in_ch)
      {
         case ',':
         case '\'':
         case '`':
            in_ch_1=fgetc(in_file);
            if(ferror(in_file))
            {
               retc=KP_E_FERROR;
               printf("Input failo klaida.\n");
            }
            if(SUCCEEDED(retc)) if(feof(in_file))
            {
               retc=KP_E_EOF;
      
               fputc(in_ch, out_file);
               if((ferror(out_file) || feof(out_file)) && SUCCEEDED(retc))
               {
                  retc=KP_E_FERROR;
                  printf("Output failo klaida.\n");
               }
            }

            if(SUCCEEDED(retc)) switch(in_ch)
            {
               case ',':
                  if(in_ch_1==',') in_ch=132;   // C_LBquote
                  else
                  {
                     fputc(in_ch, out_file);
                     if(ferror(out_file) || feof(out_file))
                     {
                        retc=KP_E_FERROR;
                        printf("Output failo klaida.\n");
                     }
                     in_ch=in_ch_1;
                  }                  
                  break;
                                    
               case '\'':
                  if(in_ch_1=='\'') in_ch=148; // C_Rquote
                  else
                  {
                     fputc(in_ch, out_file);
                     if(ferror(out_file) || feof(out_file))
                     {
                        retc=KP_E_FERROR;
                        printf("Output failo klaida.\n");
                     }
                     in_ch=in_ch_1;
                  }                  
                  break;
            
               case '`':
                  if(in_ch_1=='`') in_ch=147;   // C_LAquote
                  else
                  {
                     fputc(in_ch, out_file);
                     if(ferror(out_file) || feof(out_file))
                     {
                        retc=KP_E_FERROR;
                        printf("Output failo klaida.\n");
                     }
                     in_ch=in_ch_1;
                  }                  
                  break;
            
            } // switch(in_ch)
                  
            break;

      } // switch(in_ch)
      
      if(SUCCEEDED(retc))
      {
         fputc(in_ch, out_file);
         if(ferror(out_file) || feof(out_file))
         {
            retc=KP_E_FERROR;
            printf("Output failo klaida.\n");
         }
      }
   }

   if(retc==KP_E_EOF) retc=S_OK;
   
   if(in_file!=NULL) fclose(in_file);
   in_file=NULL;
   
   if(out_file!=NULL)
   {
      if(fclose(out_file))
      {
         retc=KP_E_FERROR;
         printf("Negaliu uzdaryti output failo.\n");
      }
      out_file=NULL;
   }

system("pause");

return(RET_CODE(retc));
}
