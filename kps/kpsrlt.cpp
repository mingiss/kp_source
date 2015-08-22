// kpsrlt.cpp
// rename lit. files

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// int main(int /* argc */, char **argv)
int main(void)
{
unsigned char file_name[1000+1];
unsigned char cmd_buf[1000+1];
const unsigned char *pnts;
unsigned char *pntd;
FILE *infile;
FILE *outfile;

   infile=fopen("kpsrlt.mcl", "r");
   outfile=fopen("kpsrlt.bat", "w");
   
   while(!feof(infile))
   {
      fgets((char *)file_name, 1000, infile);
      
      if(!feof(infile))
      {
         pntd=file_name+strlen((const char *)file_name);
         if(pntd>file_name) if((*(pntd-1)=='\n') || (*(pntd-1)=='\r')) pntd--;
         if(pntd>file_name) if((*(pntd-1)=='\n') || (*(pntd-1)=='\r')) pntd--;
         *pntd=0;
                  
         strcpy((char *)cmd_buf, "ren \"");
         strcat((char *)cmd_buf, (const char *)file_name); // argv[1]);
         strcat((char *)cmd_buf, "\" \"");
   
//       pnts=(const unsigned char *)argv[1]+strlen(argv[1]);
         pnts=file_name+strlen((const char *)file_name);
         while((pnts!=file_name) && (*pnts!='\\')) pnts--;
         if(*pnts=='\\') pnts++;
   
         pntd=cmd_buf+strlen((const char *)cmd_buf);
      
         while(*pnts)
         {
            switch(*pnts)
            {
               case 'µ': *(pntd++)='A'; break;
               case 'Ð': *(pntd++)='a'; break;
               case '¶': *(pntd++)='C'; *(pntd++)='Z'; break;
               case 'Ñ': *(pntd++)='c'; *(pntd++)='z'; break;
               case '·': *(pntd++)='E'; break;
               case 'Ò': *(pntd++)='e'; break;
               case '¸': *(pntd++)='E'; break;
               case 'Ó': *(pntd++)='e'; break;
               case '½': *(pntd++)='I'; break;
               case 'Ô': *(pntd++)='i'; break;
               case '¾': *(pntd++)='S'; *(pntd++)='Z'; break;
               case 'Õ': *(pntd++)='s'; *(pntd++)='z'; break;
               case 'Æ': *(pntd++)='U'; break;
               case 'Ö': *(pntd++)='u'; break;   
               case 'Ç': *(pntd++)='U'; break;
               case '×': *(pntd++)='u'; break;
               case 'Ï': *(pntd++)='Z'; *(pntd++)='Z'; break;
               case 'Ø': *(pntd++)='z'; *(pntd++)='z'; break;
               case ' ': *(pntd++)='-'; break;
               case '_': *(pntd++)='-'; break;
               default: *(pntd++)=(*pnts); break;           
            }
            
            pnts++;
         }
         
         strcpy((char *)pntd, "\"\n");
         
//       printf((const char *)cmd_buf); printf("\n");
//       system((const char *)cmd_buf);

         fputs((const char *)cmd_buf, outfile);
      }
   }
   
   fclose(outfile);
   fclose(infile);
   
return(0);
}


