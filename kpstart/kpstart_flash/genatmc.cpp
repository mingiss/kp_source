// ===================================================
// genatmc.cpp
// atmintuko kodo antros dalies generatorius
// invertuotas ser. no. ir chsum
//


// ------------------------------------
#include "envir.h"

#include <stdio.h>
#include <iostream.h>
// #include <iostream>
#include <fstream.h>
// #include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <richedit.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstdio.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "chkvol.h"


// ------------------------------------
const unsigned char lpszProdName[] = "genatmc";
KpErrorProc_tag KpErrorProc(True, 43);
int iProdVerGlob=0;
bool bServiceFl=False;

KpStApp theApp;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
int main(int argc, char** argv)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpStApp *app_ptr=NULL;
long ser_no;
// unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
int st_pos = 0;

   app_ptr=(&theApp);
   theKpStAppPtr = /* static_cast<KpStApp *> */ (&theApp);

   if(SUCCEEDED(retc)) retc=app_ptr->InitStApp(NULL, NULL, NULL, KpStEditMode);

   if((argc != 2) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, "Nurodykite parametrà - atmintuko serijiná numerá ðeðioliktainiu formatu.", True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      st_pos = strlen(argv[1]) - MAX_LONG_HEX_DIGITS;
      if(st_pos < 0) st_pos = 0;
      if(sscanf(argv[1] + st_pos, "%lx", &ser_no) != 1)
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ser_no = ser_no & 0xFFFF;
      ser_no = ser_no ^ 0xFFFF;

//    retc = FormatKeyHex(key_buf, ser_no);
   }

// printf("%s%1d\n", key_buf, ChSum(ser_no));
   printf("%05d%01d\n", ser_no, ChSum(ser_no));

   /* if(SUCCEEDED(retc)) */ retc0=app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE_MAIN(retc));
}

