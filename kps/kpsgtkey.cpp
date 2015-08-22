// ---------------------
// kpsgtkey.cpp
// get answer key to registration code
//

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kperr.h"
#include "kpstring.h"
#include "kptt.h"
#include "kpctype.h"


#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// ------------------------------------------ static data
KpErrorProc_tag KpErrorProc(True, 43);


// ------------------------------------------ 
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
unsigned char in_buf[KP_MAX_FILE_LIN_WDT+1];
int comp_id;
int prod_vers;
// int license;

// if(!gets((char *)in_buf))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   if(argc!=2)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) strcpy(in_buf, argv[1]);

   if(SUCCEEDED(retc)) TvStrUpr(in_buf);

   if(SUCCEEDED(retc)) if(strlen(in_buf) != 4 + 1 + 4 /* + 1 + 4 */)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if((in_buf[4]!='-') /* || (in_buf[9]!='-') */)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)){ in_buf[4]=Nul; /* in_buf[9]=Nul; */}

   if(SUCCEEDED(retc)) retc=ScanKeyHex(in_buf, &comp_id);
   if(SUCCEEDED(retc)) retc=FormatKeyHex(in_buf, rand(comp_id));
   if(SUCCEEDED(retc)) printf((const char *)in_buf);

   if(SUCCEEDED(retc)) printf("-");

   if(SUCCEEDED(retc)) retc=ScanKeyHex(in_buf+5, &prod_vers);
   if(SUCCEEDED(retc)) retc=FormatKeyHex(in_buf, rand(prod_vers));
   if(SUCCEEDED(retc)) printf((const char *)in_buf);

/*
   if(SUCCEEDED(retc)) printf("-");

   if(SUCCEEDED(retc)) retc=ScanKeyHex(in_buf+10, &license);
   if(SUCCEEDED(retc)) retc=FormatKeyHex(in_buf, rand(license));
   if(SUCCEEDED(retc)) printf((const char *)in_buf);
*/

   if(SUCCEEDED(retc)) printf("\n");

   if(SUCCEEDED(retc)) printf("Produktas: %d v%03.2f\n", (comp_id^prod_vers)/1000, ((comp_id^prod_vers)%1000)/100.0);
// if(SUCCEEDED(retc)) printf("Licenzija: %d\n", comp_id^license);


return(RET_CODE(retc));
}
