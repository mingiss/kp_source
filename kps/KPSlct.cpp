//-----------------------------------------------
// kpslct.cpp
// count of lines in file


#include <fstream>
#include <windows.h>

#define KP_MAX_FILE_LIN_LEN 4096

using namespace std;

/*---------------------------------------------*/
int main(int argc, char **argv)
{
int lcnt;
char in_line[KP_MAX_FILE_LIN_LEN + 1];

   if(argc < 2) cout << 0 << endl;
   else
   {
fstream in_file(argv[1], ios::in);
      if(in_file.fail()) cout << 0 << endl;
      else
      {
         lcnt = 0;

         do
         {
            in_file.getline(in_line, KP_MAX_FILE_LIN_LEN);
            if(!in_file.fail()) lcnt++;
             
         } while(!in_file.fail());
         
         cout << lcnt << endl;
         
         in_file.close(); 
      }
   }
   
return(0);
}

