// ---------------------------
// kpspost.cpp
// post praneðimo siuntimas
//
// pirmas command line parametras – IP adresas (URL su porto nr.), 
// antras – failo vardas serveryje
// treèias – POST praneðimo turinys (tarp kabuèiø jei su tarpais)
//
// kpspost.exe http://www.tev.lt /diag.php "pranesimas" 
// kpspost.exe http://127.0.0.1:49494 / "EXT=/n/h/Apage=10 C:\Users\mindaugas\Documents\TEST\testinis\DAT9\cd\matematika_tau_9_1.pdf" 
//

// -----------------------------------------
#include "envir.h"

#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kpspost";

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;

KpCommonApp TheApp;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ---------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
int ii;
long ll;
KpTreeEntry *next_par = NULL;
const unsigned char *ip_ptr = null;
const unsigned char *rem_file_ptr = null;
const unsigned char *post_msg_ptr = null;
static unsigned char post_boundary[KP_MAX_FNAME_LEN + 100];
KpSocket *sock_ptr = NULL;

   if(SUCCEEDED(retc)) retc = TheApp.GetOpenResult();

   if(SUCCEEDED(retc)) retc = TheApp.InitCommonApp(hInstance, lpCmdLine);
   
   if(SUCCEEDED(retc))
   {
      KP_ASSERT(TheApp.m_plCmdLineArgs != NULL, E_INVALIDARG, null, True);
      
      ii = 0;
      if(SUCCEEDED(retc)) retc = TheApp.m_plCmdLineArgs->CountEntries(&ii);
      KP_ASSERT(ii == 3, E_INVALIDARG, null, True);
       
      if(SUCCEEDED(retc)) ip_ptr = (const unsigned char *)TheApp.m_plCmdLineArgs->GetValue();
      KP_ASSERT(ip_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      
      if(SUCCEEDED(retc)) retc = TheApp.m_plCmdLineArgs->GetFirstChild(&next_par);
      KP_ASSERT(next_par != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) rem_file_ptr = (const unsigned char *)next_par->GetValue();
      KP_ASSERT(rem_file_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      
      if(SUCCEEDED(retc)) retc = next_par->GetFirstChild(&next_par);
      KP_ASSERT(next_par != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) post_msg_ptr = (const unsigned char *)next_par->GetValue();
      KP_ASSERT(post_msg_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      
      if(SUCCEEDED(retc))
      {
         strcpy(post_boundary, "----------------------");
         retc = TvUniFname.Generate(post_boundary + strlen(post_boundary));
      }
      
      KP_NEWO(sock_ptr, KpSocket());
               
      if(SUCCEEDED(retc)) retc = sock_ptr->Resolve(ip_ptr, True); // "http://127.0.0.1:49494"
      if(SUCCEEDED(retc)) retc = sock_ptr->Connect(True);
               
      if(SUCCEEDED(retc))
      {
         ll = strlen(post_msg_ptr);
         retc = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD, rem_file_ptr, // "/" 
            True, ll, False, post_boundary);
      }
      
      if(SUCCEEDED(retc)) retc = sock_ptr->SendMsg(post_msg_ptr, ll, True);
      
      KP_DELETE(sock_ptr);

      retc0 = TheApp.CloseCommonApp();
      if(SUCCEEDED(retc)) retc = retc0;
   }

return(RET_CODE_WIN(retc));
}
