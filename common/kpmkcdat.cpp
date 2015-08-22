// ==================================================
// kpmkcdat.cpp
// create file kpcurdat.cpp
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string.h>
#include <string>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpmsg.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpcolors.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kptt.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"


// -----------------------------
const unsigned char lpszProdName[] = "kpmkcdat";
int iProdVerGlob=0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;
int iUpdNumGlob = -1;

int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------
int main(void)
{
HRESULT retc=S_OK;
FILE *outfile=NULL;
time_t ltime;
tm *tm_ptr=NULL;

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      outfile = fopen(KP_CURDAT_CPP_FNAME, "w");
      if(outfile==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      fprintf(outfile, "// ---------------------------\n");
      fprintf(outfile, "// kpcurdat.cpp\n");
      fprintf(outfile, "// kompiliavimo data\n");
      fprintf(outfile, "// neredaguoti - failas generuojamas automatiskai\n");
      fprintf(outfile, "//\n");
      fprintf(outfile, "\n");
      fprintf(outfile, "// -----------------------------------------\n");
      fprintf(outfile, "#include \"envir.h\"\n");
      fprintf(outfile, "#include \"iBshn.h\"\n");
      fprintf(outfile, "#include \"lzdshn.h\"\n");
      fprintf(outfile, "\n");
      fprintf(outfile, "#include <stdio.h>\n");
      fprintf(outfile, "#include <string>\n");
      fprintf(outfile, "#include <fstream>\n");
      fprintf(outfile, "#include <time.h>\n");
      fprintf(outfile, "#include <windows.h>\n");
      fprintf(outfile, "#include <windowsx.h>\n");
      fprintf(outfile, "#include <commctrl.h>\n");
      fprintf(outfile, "#include <richedit.h>\n");
      fprintf(outfile, "#include <Richole.h>\n");
      fprintf(outfile, "\n");
      fprintf(outfile, "#ifdef IBSH_RES_MODE_XGECKO\n");
      fprintf(outfile, "#if CompilerGr==Mingw\n");
      fprintf(outfile, "#include \"IInputStream.hh\"\n");
      fprintf(outfile, "#include \"IString.hh\"\n");
      fprintf(outfile, "#include \"XApplication.hh\"\n");
      fprintf(outfile, "#include \"XGecko.hh\"\n");
      fprintf(outfile, "#include \"XGeckoDOMEvent.hh\"\n");
      fprintf(outfile, "#include \"XGeckoInit.hh\"\n");
      fprintf(outfile, "#endif\n");
      fprintf(outfile, "#endif\n");
      fprintf(outfile, "\n");
      fprintf(outfile, "#if Compiler != Watcom\n");
      fprintf(outfile, "using namespace std;\n");
      fprintf(outfile, "#endif\n");
      fprintf(outfile, "\n");
#if FALSE
      fprintf(outfile, "#if CompilerGr==Mingw\n");
      fprintf(outfile, "#include \"IInputStream.hh\"\n");
      fprintf(outfile, "#include \"IString.hh\"\n");
      fprintf(outfile, "#include \"XApplication.hh\"\n");
      fprintf(outfile, "#include \"XGecko.hh\"\n");
      fprintf(outfile, "#include \"XGeckoDOMEvent.hh\"\n");
      fprintf(outfile, "#include \"XGeckoInit.hh\"\n");
      fprintf(outfile, "#endif\n");
      fprintf(outfile, "\n");
#endif      
      fprintf(outfile, "#include \"kpstdlib.h\"\n");
      fprintf(outfile, "#include \"kperrno.h\"\n");
      fprintf(outfile, "#include \"kptt.h\"\n");
      fprintf(outfile, "#include \"kptree.h\"\n");
      fprintf(outfile, "#include \"kpctype.h\"\n");
      fprintf(outfile, "#include \"kpstring.h\"\n");
      fprintf(outfile, "#include \"kpcolors.h\"\n");
      fprintf(outfile, "#include \"kpfonts.h\"\n");
      fprintf(outfile, "#include \"kpstdio.h\"\n");
      fprintf(outfile, "#include \"kpttucf.h\"\n");
      fprintf(outfile, "#include \"res_com.h\"\n");
#if FALSE
      fprintf(outfile, "#if CompilerGr==Mingw\n");
      fprintf(outfile, "#include \"tvxml.h\"\n");
      fprintf(outfile, "#include \"KpPubDlg.h\"\n");
      fprintf(outfile, "#include \"KpGecko.h\"\n");
      fprintf(outfile, "#endif\n");
#endif      
      fprintf(outfile, "#include \"kpwindow.h\"\n");
      fprintf(outfile, "#include \"kpsock.h\"\n");
      fprintf(outfile, "#include \"kperr.h\"\n");
      fprintf(outfile, "#include \"kphp11i.h\"\n");
      fprintf(outfile, "#include \"kphp11t.h\"\n");
      fprintf(outfile, "#include \"kphp11y.h\"\n");
      fprintf(outfile, "#include \"kphp11d.h\"\n");
      fprintf(outfile, "#include \"kphp11rc.h\"\n");
      fprintf(outfile, "#include \"kpcapp.h\"\n");
      fprintf(outfile, "#include \"kpstmsg.h\"\n");
      fprintf(outfile, "#include \"tvmain.h\"\n");
      fprintf(outfile, "#include \"tvrtf.h\"\n");
      fprintf(outfile, "#include \"tvrtfo.h\"\n");
      fprintf(outfile, "#include \"tvtex.h\"\n");
      fprintf(outfile, "#include \"tvxml.h\"\n");
      fprintf(outfile, "#include \"xmlp.h\"\n");
      fprintf(outfile, "#include \"xmlh.h\"\n");
      fprintf(outfile, "#include \"xmlf.h\"\n");
      fprintf(outfile, "#include \"xml8.h\"\n");
      fprintf(outfile, "#include \"xmlu.h\"\n");
      fprintf(outfile, "#include \"xmlo1.h\"\n");
      fprintf(outfile, "#include \"xmlt.h\"\n");
      fprintf(outfile, "#include \"xmlis.h\"\n");
      fprintf(outfile, "#include \"xmli.h\"\n");
      fprintf(outfile, "#include \"xmlg.h\"\n");
      fprintf(outfile, "#include \"KpFileSys.h\"\n");
      fprintf(outfile, "#include \"KpPubDlg.h\"\n");
      fprintf(outfile, "#include \"xmln.h\"\n");
      fprintf(outfile, "#include \"kpstap.h\"\n");
      fprintf(outfile, "\n");
      fprintf(outfile, "extern const unsigned char lpszProdDate[] = \"");

      time(&ltime);
      tm_ptr=gmtime(&ltime);
      if(tm_ptr) fprintf(outfile, "%04d.%02d.%02d",
            1900+tm_ptr->tm_year, 1+tm_ptr->tm_mon, tm_ptr->tm_mday);

      fprintf(outfile, "\";\n");

      if(feof(outfile) || ferror(outfile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fclose(outfile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_MAIN(retc));
}
