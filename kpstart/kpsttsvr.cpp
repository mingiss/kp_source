// ---------------------------
// kpsttsvr.cpp
// rezultatu serverio kpstlsvr.exe testeris - floodintojas 
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>
#include <richedit.h>
#include <richedit.h>
#include <time.h>
#include <string>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstap.h"

// -----------------------------------------
const unsigned char lpszProdName[] = "kpsttsvr"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
#ifdef Debug
bool bServiceFl=False; // True; //   
#else
bool bServiceFl=False; // bool bServiceFl=True;
#endif

int iKpstrSvrTimer = 0;


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


/*--------------------------------------------------- main */
// int APIENTRY WinMain(HINSTANCE hInstance,
//                   HINSTANCE /* hPrevInstance */,
//                   LPSTR     /* lpCmdLine */,
//                   int       /* nCmdShow */)
int main(int argc, char** argv)
{
HRESULT retc=S_OK;
unsigned char adr_str[KP_MAX_FNAME_LEN+1];
int site_num = 0;
KpSocket_tag *flood_socket = NULL;
// const unsigned char *data_msg = NULL;
unsigned char data_msg[KP_MAX_FILE_LIN_LEN+1];
int ii;

   adr_str[0] = Nul;
   
   if(SUCCEEDED(retc)) retc = KpInit();

   if(SUCCEEDED(retc))
   {
      if(argc>2)
      {
         sscanf(argv[1], "%d", &site_num);

         if(strlen(argv[2]) > KP_MAX_FNAME_LEN)
            retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
         {
            strncpy(adr_str, argv[2], KP_MAX_FNAME_LEN);
            adr_str[KP_MAX_FNAME_LEN] = Nul;
         }
      }
      else
      {
      /* retc = */ KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         site_num = 1;
         strcpy(adr_str, "127.0.0.1:13006");
      }
   }   


   for(ii = 0; (ii<100) && SUCCEEDED(retc); ii++)
   {
      printf("%d\n", ii);

      KP_NEWO(flood_socket, KpSocket_tag());

      if(SUCCEEDED(retc)) retc=flood_socket->Resolve(adr_str, True);

      if(SUCCEEDED(retc)) retc=flood_socket->Connect(True);
   
// POST / HTTP/1.1
// Accept: */*
// Content-Type: application/x-www-form-urlencoded
// Content-Length: 92
// User-Agent: AcroForms
// Host: 127.0.0.1:18008
// Cache-Control: no-cache
// 
// sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

      if(SUCCEEDED(retc))
      {
//       data_msg = (const unsigned char *)"sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980"; 
//       data_msg = (const unsigned char *)"sl=Paulius%7cKaulius%7c66666666666%7c269546566%7c2189455%7c333332%7c950636646%7c604176385%7c756486419%7c2080629319";
         sprintf((char *)data_msg, "sl=Paulius|Kaulius|%d%05d|269546566|2189455|333332|950636646|604176385|756486419|2080629319", site_num, ii);
         retc=flood_socket->SendHttpRequest(HTTP_POST_REQUEST_CMD, (const unsigned char *)"/", True, strlen(data_msg)); // "POST"
      }
   
      if(SUCCEEDED(retc)) retc=flood_socket->SendMsg(data_msg, strlen(data_msg), True);
   
      KP_DELETE(flood_socket);
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

   system("pause");
   
return(RET_CODE_MAIN(retc));
}
