//-----------------------------------------------
// kpsfsz.cpp
// file size


#include <fstream>
#include <windows.h>


using namespace std;

/*---------------------------------------------*/
int main(int argc, char **argv)
{
HANDLE in_file;
int fs;

   if(argc < 2) cout << 0 << endl;
   else
   {
      in_file = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);   
      if(in_file == INVALID_HANDLE_VALUE) cout << 0 << endl;
      else
      {
         fs = GetFileSize(in_file, NULL);
         if(fs == INVALID_FILE_SIZE) cout << 0 << endl;
         else cout << fs << endl;
      }
   }

return(0);
}

