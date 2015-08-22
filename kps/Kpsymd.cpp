// date in 3-positions ymd format

#include <stdio.h>
#include <time.h>
#include <string.h>

void main(int argc, char **argv)
{
int year, month, day;
char *next_ptr;
time_t now;
struct tm *l_time;

//   year=2002;
//   month=8;
//   day=27;
   
//   year-=2000;

   if(argc<=1)
   {
      now = time((time_t *)NULL);
      l_time = localtime(&now);

      year=l_time->tm_year-100;
      month=l_time->tm_mon+1;
      day=l_time->tm_mday;   
   }
   else
   {
      next_ptr=strchr(argv[1],'.');
      if(next_ptr!=NULL)
      {
         sscanf(argv[1], "%d", &year);
         if(year>100) year-=2000;
         sscanf(next_ptr+1, "%d", &month);
         next_ptr=strchr(next_ptr+1,'.');
         sscanf(next_ptr+1, "%d", &day);
      }
      else
      {
         year=argv[1][0]-'0';
         month=argv[1][1]-'0';
         sscanf(argv[1]+2, "%d", &day);
      }
   }

   if(year<10) year+='0';
   else year+='A'-10;
   if(month<10) month+='0';
   else month+='A'-10;
   if(day<10) day+='0';
   else day+='A'-10;
   
   printf("%c%c%c\n", year, month, day);
   
}
