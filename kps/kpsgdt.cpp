// kpsgdt.cpp
// get file modidication date

#include <windows.h>
#include <stdio.h>


bool is_leap(int year)
{
bool retc=FALSE;

   if(year % 4 == 0) retc=TRUE;
   if(year % 100 == 0) retc=FALSE;

return(retc);
}


int days_per_year(int year)
{
return(is_leap(year)?366:365);
}


int days_per_month(int month, int year)
{
int days;

   switch(month)
   {
   case 1:
   case 3:
   case 5:
   case 7:
   case 8:
   case 10:
   case 12:
      days=31;
      break;
   case 4:
   case 6:
   case 9:
   case 11:
      days=30;
      break;
   case 2:
      days=is_leap(year)?29:28;
      break;
   }

return(days);
}


int main(int argc, char **argv)
{
WIN32_FILE_ATTRIBUTE_DATA FileData;
double f_time;
BOOL retc;
int year=0;
int month=0;
int day=0;
int hour=0;
int minute=0;
int second=0;

   if(argc==2)
   {
      retc=GetFileAttributesEx(argv[1], GetFileExInfoStandard, &FileData);
      if(retc)
      {
         f_time=(unsigned long)FileData.ftLastWriteTime.dwHighDateTime;
         f_time*=0x10000;
         f_time*=0x10000;
         f_time+=(unsigned long)FileData.ftLastWriteTime.dwLowDateTime; 
         f_time/=10000000;  // count of seconds after 1601.01.01 00:00:00
         f_time+=2*60*60;   // timezone correction


         year=1601;
         while(f_time>=(days_per_year(year)+1)*24*60*60)
            f_time-=days_per_year(year++)*24*60*60;

         month=1;
         while(f_time>=(days_per_month(month,year)+1)*24*60*60)
            f_time-=days_per_month(month++,year)*24*60*60;

         day=(int)(f_time/(24*60*60));
         f_time-=day*24*60*60;

         hour=(int)(f_time/(60*60));
         f_time-=hour*60*60;

         minute=(int)(f_time/60);
         f_time-=minute*60;

         second=(int)f_time;

      }
      
      printf("%04d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second);

      if(!retc) printf("File %s not found\n",argv[1]);
   }
   else
   {
      printf("%04d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second);

      printf("\nOutputs file modification date:\n\n");
      printf("   kpsgdt <file_name>\n\n");
      
      retc=FALSE;
   }

return(retc);
}
