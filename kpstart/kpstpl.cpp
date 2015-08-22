// ---------------------------
// kpstpl.cpp
// sablonas programos paleidimui su registracija
//
//

#include <windows.h>

#include "kperrno.h"
#include "kperr.h"
#include "kpsttrg.h"

// -----------------------------------------
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
HRESULT retc = E_ACCESSDENIED;

// tikrinam registracijà
   if(SUCCEEDED(KpsTestReg()))
   {
      retc = S_OK;

// pavyko
KpMsgOut("Vysks gerai", IDI_ASTERISK, KP_MB_TESTI);



// ....


   }

return(retc);
}
