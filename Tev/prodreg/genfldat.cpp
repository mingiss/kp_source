// -------------------
// genfldat.cpp
// generate garbage file
//

#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <sys/timeb.h>
#include <iostream.h>
#include <fstream.h>
#include <windows.h>

#define ios_base ios

#define FL_DAT_HAT "TVFL001.01"


int main(int argc, char** argv) 
{
long f_size = 0L;
fstream out_file;
struct _timeb timeb_buf; 
long cur_val;
short cur_val_f;
char cur_val_ch;
long ll;
int ii;
char fname[MAX_PATH+1];
DWORD free_clust, secs_per_clust, bytes_per_sect, total_clust;

   if((argc != 3) && (argc != 2)) printf("Nurodykite parametrus - kelià iki generuojamo failo fl.dat ir jo dydá.\n");
   else
   {
      strcpy(fname, argv[1]);
      strcat(fname, "fl.dat");
       
      f_size = 0L;
      if(argc == 3) sscanf(argv[2], "%ld", &f_size);
      else
      {
         if(GetDiskFreeSpace(argv[1], &secs_per_clust, &bytes_per_sect, &free_clust, &total_clust))
            f_size = free_clust * secs_per_clust * bytes_per_sect;
         else printf("GetDiskFreeSpace klaida %ld\n", GetLastError());
      }
      
      out_file.open(fname, ios_base::out | ios_base::binary);
      if(out_file.fail()) printf("Negaliu sukurti failo %s.\n", fname);
      else
      {
         out_file << FL_DAT_HAT;
         if(f_size >= strlen(FL_DAT_HAT))
         {
            for(ll = 0; ll < (f_size - strlen(FL_DAT_HAT))/sizeof(cur_val_f)/100; ll++)
            {
               _ftime(&timeb_buf);
               cur_val = timeb_buf.time + timeb_buf.millitm;        

               for(ii = 0; ii< 100; ii++)
               {
                  cur_val_f = (short)((cur_val + rand()) & 0xFFFF);
                  out_file.write((const char *)&cur_val_f, sizeof(cur_val_f));
                  if(out_file.fail()){ printf("Failo %s raðymo klaida.\n", fname); break; }
               }
            }
         
            for(ll = 0; ll < f_size - strlen(FL_DAT_HAT) - ((f_size - strlen(FL_DAT_HAT))/sizeof(cur_val_f)/100)*100*sizeof(cur_val_f); ll++)
            {
               cur_val_ch = (char)((cur_val + rand()) & 0xFF);
               out_file.write((const char *)&cur_val_ch, sizeof(cur_val_ch));
               if(out_file.fail()){ printf("Failo %s raðymo klaida.\n", fname); break; }
            }
         }
         out_file.close();

      } // else // if(out_file.fail())   
      
   } // else // if(argc != 2)

return(0);
}

