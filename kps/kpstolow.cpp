// ------------------------
// kpstolow.cpp
// converts text file to lower case
//

// ------------------------
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// ------------------------
int main(int /* argc */, char** argv)
{
FILE *file;
char ch;
long pos;

   file=fopen(argv[1], "rb+");
   if(file==NULL) printf("File not found\n");
   else
   {         
      pos=0L;
      while(1)
      {
         if(fseek(file, pos, SEEK_SET))
         {
            printf("File error\n");
            break;
         }

         ch=fgetc(file);
         if(ferror(file))
         {
            printf("File input error\n");
            break;
         }
         if(feof(file)) break;

         if(fseek(file, pos, SEEK_SET))
         {
            printf("File error\n");
            break;
         }
         fputc(tolower(ch), file);
         if(ferror(file) || feof(file))
         {
            printf("File input error\n");
            break;
         }
         
         pos++;
      }

      if(fclose(file)) printf("Directory I/O\n");
   }
         

return(0);
}


