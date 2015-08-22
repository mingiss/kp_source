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
               case '�': *(pntd++)='A'; break;
               case '�': *(pntd++)='a'; break;
               case '�': *(pntd++)='C'; *(pntd++)='Z'; break;
               case '�': *(pntd++)='c'; *(pntd++)='z'; break;
               case '�': *(pntd++)='E'; break;
               case '�': *(pntd++)='e'; break;
               case '�': *(pntd++)='E'; break;
               case '�': *(pntd++)='e'; break;
               case '�': *(pntd++)='I'; break;
               case '�': *(pntd++)='i'; break;
               case '�': *(pntd++)='S'; *(pntd++)='Z'; break;
               case '�': *(pntd++)='s'; *(pntd++)='z'; break;
               case '�': *(pntd++)='U'; break;
               case '�': *(pntd++)='u'; break;   
               case '�': *(pntd++)='U'; break;
               case '�': *(pntd++)='u'; break;
               case '�': *(pntd++)='Z'; *(pntd++)='Z'; break;
               case '�': *(pntd++)='z'; *(pntd++)='z'; break;
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


