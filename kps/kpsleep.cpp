// ---------------------------
// kpsleep.cpp parametras - milisekundziu skaicius
//
// kpsleep.exe kopijuojamas i sleep.exe
//

// -----------------------------------------
#include <stdio.h>
#include <windows.h>

#include <envir.h>
#include <kpstdlib.h>

// -----------------------------------------
int main(int argc, char** argv)
{
HRESULT retc=S_OK;
int ii;

   if(argc<2)
   {
      printf("Nurodykite parametra - milisekundziu skaiciu\n");
      retc=E_INVALIDARG;
   }
   
   if(SUCCEEDED(retc))
   {
      sscanf(argv[1], "%d", &ii);
      Sleep(ii);
   }
    
return(RET_CODE(retc));
}

