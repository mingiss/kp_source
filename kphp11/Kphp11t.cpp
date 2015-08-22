// ----------------------------------
// kphp11t.cpp
// local Win32 thread functions
//
// 2012.10.12 mp WinXP nesiinicializuodavo terminuot÷ licencij÷ termino keitimas vykdymo metu
//

#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11p.h"
#include "kphp11d.h"
#include "kphp11tt.h"
#include "kphp11mz.h"
#include "kphp11rc.h"
#include "kphp11ry.h"
#include "kphp11w.h"
#include "kphp11s.h"
#include "kphp11m.h"
#include "kphp11t.h"
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
#include "kpstmsg.h"


// -----------------------------------------
#ifdef Debug
// KpConsole KpTraceWindow;
// KpConsole KpTraceWindow1;
// KpConsole KpTraceWindow2;
#endif

// -----------------------
EmuTt EmuTv;


// ----------------------- EmuTt implementation
EmuTt::EmuTt(void)
{
   m_lPrevThreadId = m_lMainThreadId = 0L; // GetCurrentThreadId();
   m_lKphp11ThreadId = 0L;
   m_bRCdone = False;
}


// -----------------------
HRESULT EmuTt::RequestRemoteCall(KpRcPars *pPars /* , DWORD lMainThreadId */, bool bOutputErrorMessages)
{
HRESULT retc=S_OK;
bool nop=False;
DWORD current_thread_id=0L;
int ii;

   EmuTv.m_bRCdone = False;

   KP_ASSERT(pPars != NULL, E_INVALIDARG, null, True);
   KP_ASSERTE(EmuTv.m_lKphp11ThreadId != 0L, KP_E_NO_FILE, null, False); // atsitinka po nul◊ÿimo siun—iant diag. msg.

   if(SUCCEEDED(retc)) pPars->m_iRetc = retc;

   if(SUCCEEDED(retc)) current_thread_id = GetCurrentThreadId();
   KP_ASSERT(current_thread_id != 0, KP_E_SYSTEM_ERROR, GetLastError(), True);

// gali b◊t uÿsilik“s timeoutintas praeitas ’ito threado i’kvietimas, elgtis kaip su svetimu
// if((m_lMainThreadId != 0L) && (m_lMainThreadId == current_thread_id) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, null, True, __FILE__, __LINE__, 0L, NULL);

// if(SUCCEEDED(retc)) PutLogMessage_("EmuTt::RRC() %d %d %d", pPars->iOpCode, m_lMainThreadId, current_thread_id);

// sulaukiam, kol pasibaigs ankstesnis RC iskvietimas
   if(SUCCEEDED(retc))
   {
ii = 0;
if(m_lMainThreadId!=0)
{
// PutLogMessage_("EmuTt::RequestRemoteCall(): current_thread_id: %ld laukiam m_lMainThreadId: %ld pPars->iOpCode: %d", current_thread_id, m_lMainThreadId, pPars->iOpCode);
      for(ii=0; (ii < KP_TIMEOUT_TIMEOUT/KPHP11_POLL_TIMEOUT) && (m_lMainThreadId != 0) && SUCCEEDED(retc); ii++)
         retc = KpSleep(KPHP11_POLL_TIMEOUT, HWND_DESKTOP);
// PutLogMessage_("EmuTt::RequestRemoteCall(): current_thread_id: %ld sulauk”m m_lMainThreadId: %ld", current_thread_id, m_lMainThreadId);
}
      if(m_lMainThreadId == 0L) m_lMainThreadId = current_thread_id; // lMainThreadId;
      else
      {
         retc = KP_E_TIMEOUT;
         if(bOutputErrorMessages) KP_ERROR(KP_E_TIMEOUT, null);
      }

      if((ii >= KP_TIMEOUT_TIMEOUT/KPHP11_POLL_TIMEOUT) && SUCCEEDED(retc))
      {
         retc = KP_E_TIMEOUT;
         if(bOutputErrorMessages) KP_ERROR(KP_E_TIMEOUT, null);
      }
   }

   if(SUCCEEDED(retc)) m_lMainThreadId = current_thread_id; // lMainThreadId;

// if(SUCCEEDED(retc)) PutLogMessage_("EmuTt::RequestRemoteCall(): kvie—iam RC, current_thread_id: %ld pPars->iOpCode: %d", current_thread_id, pPars->iOpCode);
// if(SUCCEEDED(retc)) PutLogMessage_("EmuTt::RRC() %d %d %d", pPars->iOpCode, m_lMainThreadId, current_thread_id);

   if(SUCCEEDED(retc)) switch(pPars->iOpCode)
   {
      case KP_RC_NOP:
         nop=True;
         break;

      case KP_RC_ENCT:
      case KP_RC_RAND:
      case KP_RC_XRAND:
      case KP_RC_REC_INI:
      case KP_RC_GET_INI_ELEM:
      case KP_RC_GET_INI_ELEM_IF_NOT_STOPPED:
      case KP_RC_SEND_INI:
      case KP_RC_SET_INI_ELEM:
      case KP_RC_ENCODE_ENTRY:
      case KP_RC_GET_VARIABLE:
      case KP_RC_SET_VARIABLE:
      case KP_RC_INIT_LICID:
      case KP_RC_UNPACK_LIC:
      case KP_RC_CALC_LIC_CODE:
      case KP_RC_RECALC_LIC_CODE:
      case KP_RC_CALC_INST_CODE:
      case KP_RC_UNPACK_INST_CODE:
      case KP_RC_CALC_INST_KEY:
      case KP_RC_CALC_REM_CODE:
      case KP_RC_UNPACK_REM_CODE:
      case KP_RC_INC_COMPID:
      case KP_RC_KEY_CHECK_INTERN:
      case KP_RC_TUX_DECODE:
      case KP_RC_TUX_HASH:
      case KP_RC_UNPACK_RID:
      case KP_RC_SAVE_REST_DAYS:
      case KP_RC_SAVE_REST_DAYS_AND_RC:
      case KP_RC_GET_REST_DAYS:
      case KP_RC_SAVE_LIC_HIGH:
      case KP_RC_GET_LIC_HIGH:
      case KP_RC_UNPACK_LIC_TMP:
      case KP_RC_ENCODE_PWD:
         nop = False;
         break;

      case KP_RC_ENCODE_ENTRY_AND_CALLBACK:
      case KP_RC_CALLBACK:
      case KP_RC_CALLBACK_AND_STORE_RETC:
      case KP_RC_KEY_CHECK_INTERN_AND_CALLBACK:
         nop=False;
         if(
            (pPars->enc.iCallBackIx<0) ||
            (pPars->enc.iCallBackIx>=KpHp11NumOfExtFun) // ||
//          (pPars->enc.pCallBackPars==NULL)
           )
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         break;

      case KP_RC_KEY_CHECK:
         retc=KpErrorProc.OutputErrorMessage(KP_E_OBSOLETE, null, True, __FILE__, __LINE__, 0L, NULL);
         break;

//    case <...>:
//       retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);
//       break;

      default:
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
   }

// if((!nop) && SUCCEEDED(retc)) if(EmuTv.m_lKphp11ThreadId==NULL)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if((!nop) && SUCCEEDED(retc)) if(pPars->iParBlSize>HP11_RC_MAX_PAR_BLK_SIZE)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

   if((!nop) && SUCCEEDED(retc))
      KP_ASSERTE(PostThreadMessage(EmuTv.m_lKphp11ThreadId, WM_KP_REMOTE_CALL, 0, (LPARAM)pPars), KP_E_SYSTEM_ERROR, GetLastError(), False);

#if FALSE // #ifdef Debug //
unsigned char str_buf[200];
if((!nop) && SUCCEEDED(retc))
{
sprintf((char *)str_buf, "main: WM_KP_REMOTE_CALL[%d] sent", pPars->iOpCode);
KP_TRACE(str_buf);
}
#endif

   if(FAILED(retc)) m_lMainThreadId=0L;

return(retc);
}


// -----------------------
HRESULT EmuTt::WaitForRemoteCallCompletion(KpRcPars *pPars, bool bCheckErrors /* void */ /* DWORD lMainThreadId */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
bool endfl=False;
MSG msg;
int retp;
UINT timeout_timer_id=0;
DWORD current_thread_id=0L;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

// if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdName(prod_name);

   if(SUCCEEDED(retc)) current_thread_id = GetCurrentThreadId();
   if((current_thread_id == 0L) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

int main_thread = m_lMainThreadId;
// if(SUCCEEDED(retc)) PutLogMessage_("EmuTt::WRCC() %d %d", main_thread /* m_lMainThreadId */, current_thread_id);

// semaforo gesinimas v”l EmuD_RCt::putw(), —ia jau gali b◊t nugesintas
   if((main_thread /* m_lMainThreadId */ != 0L) && (main_thread /* m_lMainThreadId */ != current_thread_id /* lMainThreadId */) && SUCCEEDED(retc))
   {
      PutLogMessage_("EmuTt::WRCC() err %d %d", main_thread /* m_lMainThreadId */, current_thread_id);
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

// if(SUCCEEDED(retc)) PutLogMessage_("EmuTt::WaitForRemoteCallCompletion(): laukiam, current_thread_id: %ld", current_thread_id);

   if(SUCCEEDED(retc))
   {
      timeout_timer_id = SetTimer(NULL, KP_TIMEOUT_TIMER, KPHP11_RC_TIMEOUT, NULL);
      if(!timeout_timer_id)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// KP_TRACE("WaitForRemoteCallCompletion");

   if(SUCCEEDED(retc)) do
   {
      if(EmuTv.m_bRCdone)
      {
         endfl = True;
         EmuTv.m_bRCdone = False;
      }

bool msg_ready = False;
      if((!endfl) && SUCCEEDED(retc))
      {
//       if(GetMessage(&msg, NULL, 0, 0)<0)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         msg_ready = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

         if(msg_ready && SUCCEEDED(retc))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            retp = LOWORD(msg.wParam);
         }
      }

      if((!endfl) && msg_ready && SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
         endfl=True;
         break;

      case WM_TIMER:
//       if(msg.wParam==KP_TIMEOUT_TIMER) // kazkodel taimerio id neperduoda
//       if((msg.hwnd==NULL) && (retp!=KPW_CONSOLE_REFRESH_TIMER))
         if(msg.wParam==timeout_timer_id)
         {
// XGecko kartais praryja WM_KP_REMOTE_CALL_DONE prane’im–, klaidos mest negalima
            KP_WARNING0(KP_E_TIMEOUT, null);
            if(pPars != NULL) PutLogMessage_("WFRCC %d", pPars->iOpCode);
            KP_STACK_DUMP;
            if(bCheckErrors) retc = KP_E_TIMEOUT;

// YYYY: Dvigubos sincronizacijos i’valant m_lMainThreadId daryt nei’eina -
//    kaÿkod”l kartais gr‘ÿta ‘ EmuD_RCt::putw() ir duoda klaid– d”l tu’—io m_lMainThreadId
//    failo kphp11rc.cpp eilut”je XXXX
//          if(m_lMainThreadId) // RC i’kvietimas i’ tikro dar nesibaig” - per m_lMainThreadId dviguba sinchronizacija
//             KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

            endfl = True;
            EmuTv.m_bRCdone = False;

// KP_TRACE("WaitForRemoteCallCompletion timeout");

         }
         break;

#if FALSE
      case WM_COMMAND:
PutLogMessage_("EmuTt::WaitForRemoteCallCompletion() WM_COMMAND: %d %ld", retp, msg.lParam);
         switch(retp)
         {
// jei —ia nepagaus - apdorojimas yra ir KpStaWindowProc()
         case KPST_ID_REST_DAYS_EXCEEDED:
            if(msg.lParam <= KPST_REST_DAYS_WARNING)
            {
               if(msg.lParam <= 0)
               {
static unsigned char str_buf[2000];
                  sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
                  KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
                  KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                  endfl = True;
                  retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
               }
               else
               {
                  if(theKpStAppPtr != NULL)
                  {
                     if(!theKpStAppPtr->m_iRestDaysWarningShowed)
                     {
                        switch(msg.lParam)
                        {
                        case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                        case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                        default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                        }
                     }
                     theKpStAppPtr->m_iRestDaysWarningShowed = True;
                  }
                  KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
               }
            }
            break;
         }
         break;
#endif

      case WM_KP_REMOTE_CALL_DONE:
         retc = msg.lParam;
         endfl = True;
         EmuTv.m_bRCdone = False;
// if(SUCCEEDED(retc)){ KP_TRACE("main: WM_KP_REMOTE_CALL_DONE received"); }
// PutLogMessage_("EmuTt::WaitForRemoteCallCompletion(): WM_KP_REMOTE_CALL_DONE received %d", current_thread_id);
         break;

      case WM_CHAR:
// KP_TRACE("keyboard message");
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
// KP_TRACE("KP_HP11_TOGGLE_CONSOLE keyboard message");
            if(lKphp11ThreadId!=0L)
               if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;
         }
         break;
      }

   } while((!endfl) && SUCCEEDED(retc));

//    if(!KillTimer(NULL, KP_TIMEOUT_TIMER))
   if(timeout_timer_id!=0)
   {
      if(!KillTimer(NULL, timeout_timer_id))
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
      timeout_timer_id=0;
   }

// i’kelta v”l atgal ‘ EmuD_RCt::putw()
// m_lMainThreadId=0L;

// PutLogMessage_("WaitForRemoteCallCompletion() %d %lx", bCheckErrors, retc);

return(retc);
}


// -----------------------
HRESULT EmuTt::ExecRemoteCall(KpRcPars *pPars /* , DWORD lMainThreadId */, bool bCheckErrors)
{
HRESULT retc=S_OK;

#ifdef Debug_RYt_putw
PutLogMessage_("ERC() .... %x %d %d", pPars, pPars->iOpCode, pPars->enc.iCallBackIx);
#endif

   if((pPars==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) pPars->m_iRetc=retc;
   if(SUCCEEDED(retc)) retc = RequestRemoteCall(pPars /* , lMainThreadId */, !bCheckErrors); // bCheckErrors rei’kia klaidas tikrinti, bet nei’vedin”ti prane’im÷
// PutLogMessage_("ExecRemoteCall() %lx", retc)
   if(SUCCEEDED(retc)) retc = WaitForRemoteCallCompletion(pPars, bCheckErrors /* lMainThreadId */);
   if(SUCCEEDED(retc)) retc = pPars->m_iRetc;

return(retc);
}


//----------------------------------- main procedure without starting of new thread
int APIENTRY EmuTt::KpHp11Main
            (
               HINSTANCE hInstance,
               HINSTANCE /* hPrevInstance */,
               LPSTR     /* lpCmdLine */,
               int       /* nCmdShow */,
               bool bOpenConsole
            )
{
HRESULT retc=S_OK;
KpHp11IdlePars *pPars;
DWORD retw;

   KP_NEW(pPars, KpHp11IdlePars);
   if(SUCCEEDED(retc))
   {
      pPars->hInstance=hInstance;
      pPars->bOpenConsole = bOpenConsole;
   }

   if(SUCCEEDED(retc)) retw=KpHp11Idle(pPars);
   else retw=RET_CODE_MAIN(retc);

return(retw);
}


//----------------------------------- start idle loop in new thread
HRESULT EmuTt::KpHp11CreateThread(HINSTANCE hInstance, bool bOpenConsole)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpHp11IdlePars *pPars = NULL;
HANDLE hh;
bool endfl = False;
MSG msg;
int retp;
UINT timeout_timer_id = 0;

   if((m_lKphp11ThreadId!=0L) || (lKphp11ThreadId!=0L) || (m_lMainThreadId!=0L))
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_lMainThreadId = GetCurrentThreadId();

   KP_NEW(pPars, KpHp11IdlePars);
   if(SUCCEEDED(retc))
   {
      pPars->hInstance = hInstance;
      pPars->bOpenConsole = bOpenConsole;
   }

   if(SUCCEEDED(retc))
   {
      hh = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         KpHp11Idle,          // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         pPars,               // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         (LPDWORD)&m_lKphp11ThreadId   // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      if(hh==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) lKphp11ThreadId = m_lKphp11ThreadId;
   else m_lKphp11ThreadId = 0L;

#ifdef Debug
// if(SUCCEEDED(retc)){ KP_TRACE("main: thread started"); }
#endif

// ----------------------------- wait for hp11 start message WM_KP_THREAD_STARTED
   if(SUCCEEDED(retc))
   {
      timeout_timer_id=SetTimer(NULL, KP_TIMEOUT_TIMER, KP_TIMEOUT_TIMEOUT, NULL);
      if(!timeout_timer_id)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// KP_TRACE("KpHp11CreateThread");

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      retp=LOWORD(msg.wParam);

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(LOWORD(retp))
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      case WM_CLOSE:
         endfl = True;
         break;

      case WM_TIMER:
//       if(msg.wParam == KP_TIMEOUT_TIMER) // kazkodel taimerio id neperduoda
//       if((msg.hwnd == NULL) && (retp != KPW_CONSOLE_REFRESH_TIMER))
         if(msg.wParam == timeout_timer_id)
         {
            retc = KpErrorProc.OutputErrorMessage(KP_E_TIMEOUT, null, True, __FILE__, __LINE__, 0L, NULL);
            endfl = True;
// KP_TRACE("KpHp11CreateThread timeout");
         }
         break;

      case WM_KP_THREAD_STARTED:
         retc = msg.lParam;
         endfl = True;
// if(SUCCEEDED(retc)){ KP_TRACE("main: start message WM_KP_THREAD_STARTED received"); }
         break;
      }

   } while((!endfl) && SUCCEEDED(retc));

//    if(!KillTimer(NULL, KP_TIMEOUT_TIMER))
   if(timeout_timer_id != 0)
   {
      if(!KillTimer(NULL, timeout_timer_id))
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
      timeout_timer_id = 0;
   }

   m_lMainThreadId = 0L;

   if(SUCCEEDED(retc)) Sleep(1000);

return(retc);
}


// ----------------------------------------
HRESULT EmuTt::StopThread(void)
{
HRESULT retc=S_OK;
int ii;

   if(m_lKphp11ThreadId != 0L)
   {
      for(ii = 0; ii < KP_TIMEOUT_TIMEOUT/100; ii++)
      {
         PostThreadMessage(m_lKphp11ThreadId, WM_QUIT, IDCANCEL, 0);
// PutLogMessage_("EmuTt::StopThread() thread: %d stabdom m_lKphp11ThreadId", m_lKphp11ThreadId);
         Sleep(100);
         if(m_lKphp11ThreadId == 0L) break;
      }
   }

return(retc);
}


// ------------------------ free local Win32 and remote hp11 thread functions

// ------------------- main idle loop - main function of hp11 thread
DWORD WINAPI KpHp11Idle(LPVOID lpParameter)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
KpHp11IdlePars *pPars=NULL;
MSG msg;
unsigned char ch;
short rc = True;
KpConsole *cur_wnd=NULL;
// int height;
// int width;
// HFONT hfont=NULL;
BOOL retw;
bool endfl = False;

#ifdef Debug
// unsigned char str_buf[100];
#endif

   if(lpParameter==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) pPars=(KpHp11IdlePars *)lpParameter;

#ifdef Debug
// if(SUCCEEDED(retc)) retc=WndPreg(&KpTraceWindow, TYP_Trace, pPars->hInstance, NULL, True);
// if(SUCCEEDED(retc)) retc=WndPreg(&KpTraceWindow1, TYP_Trace, pPars->hInstance, NULL, True);
// if(SUCCEEDED(retc)) retc=WndPreg(&KpTraceWindow2, TYP_Trace, pPars->hInstance, NULL, True);
#endif

   if(SUCCEEDED(retc)) retc = WndPreg(&EmuWv /* &EmuWp */, TYP_KpConsole, pPars->hInstance, NULL, pPars->bOpenConsole);

   if(SUCCEEDED(retc))
   {
      EmuWv.einit();
      EmuDv.plugdev(DEV_TT, TT_DEF_CSR, TT_DEF_INT, 0, NULL, &EmuWv, TERM_VT52);
      EmuDv.plugdev(DEV_MZ, MZ_DEF_CSR, MZ_DEF_INT, 0, (unsigned char *)"sy7.dsk", NULL, TERM_NO);
      EmuDv.plugdev(DEV_RC, RC_DEF_CSR, RC_DEF_INT, 0, NULL, NULL, TERM_NO);
      EmuDv.plugdev(DEV_RY, RY_DEF_CSR, RY_DEF_INT, 0, NULL, NULL, TERM_NO);

      EmuYv.loadsav((unsigned char *)"kphp11.bin");
      EmuPv.putrw(PC_IND, 0);
      EmuSv.status = Run;

      EmuMv.minit();

#ifdef Debug
// if(SUCCEEDED(retc)){ KP_TRACE("kphp11: thread started"); }
#endif

      if(EmuSv.errfl_gl && SUCCEEDED(retc)) retc=KP_E_SYSTEM_ERROR;

      if(SUCCEEDED(retc)) if(EmuTv.m_lMainThreadId==0L)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

/*-----------------------------------------------------*/
      if(SUCCEEDED(retc))
         if(!PostThreadMessage(EmuTv.m_lMainThreadId, WM_KP_THREAD_STARTED, 0, (LPARAM)retc))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            EmuSv.s_err("T: no connection to host", (unsigned char *)"", __FILE__, __LINE__);
#endif
         }

#ifdef Debug
// if(SUCCEEDED(retc)){ KP_TRACE("kphp11: start message WM_KP_THREAD_STARTED sent"); }
#endif

/*-----------------------------------------------------*/
      endfl = False;
      if(SUCCEEDED(retc)) do
      {
// --------------------------------------- keyboard interrupt
// ir kitus trukius apdorti cia, pries tai sukaupiant i eile
// blogai - uzsiciklina trukiai, su prioritetais gal pazaist reikia
// kai pataisysiu, ismest EmuDv.ddputw prie klaviaturos ivedimo zemiau
//       if(
//          ((EmuSv.status == Run) || (EmuSv.status == Wait)) &&
//          (SUCCEEDED(retc))
//         )
//       {
//          if(EmuDv.dkbhit())
//          {
//             if(!EmuDv.ddputw(DEV_TT, 0, TT_in_CSR, TT_ready))
//             {
////              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
//             }
//          }
//       }


// --------------------------------------- execute current instruction
         if(EmuSv.status == Run)
         {
            if((EmuSv.trfl) && ((EmuSv.intrfl) || (EmuPv.intlev <= 0)))
            {
               rc &= EmuSv.pr3();
            }
            if(rc) EmuPv.iexe();

            if(!rc) retc = KP_E_SYSTEM_ERROR;

// --------------------------------------- get Windows message
            retw = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
         }
         else
         {
            GetMessage(&msg, NULL, 0, 0);
            retw = True;
         }

// ---------------------------------------- process Windows message
         if(retw && SUCCEEDED(retc))
         {
//          if(msg.message != WM_QUIT)
            {
               TranslateMessage(&msg);

               switch(msg.message)
               {
#if FALSE
               case WM_KP_CREATE:
                  cur_wnd=(KpConsole *)msg.lParam;
                  if(cur_wnd==&EmuWv)
                  {
                     if(cur_wnd->m_hDisplayCtrl==NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                     if(SUCCEEDED(retc))
                     {
                        height=iaCtrlFntHghts[KPW_CONTROL_STYLE_COURIER]; // 6;
                        width=iaCtrlFntWdts[KPW_CONTROL_STYLE_COURIER]/100; // 4;
                        hfont=CreateFont
                           (
                              height,                     // int nHeight,               // logical height of font
                              width,                      // int nWidth,                // logical average character width
                              0,                          // int nEscapement,           // angle of escapement
                              0,                          // int nOrientation,          // base-line orientation angle
                              iaCtrlFntWghts[KPW_CONTROL_STYLE_COURIER], // int fnWeight,              // font weight
                              False,                      // DWORD fdwItalic,           // italic attribute flag
                              False,                      // DWORD fdwUnderline,        // underline attribute flag
                              False,                      // DWORD fdwStrikeOut,        // strikeout attribute flag
                              laCtrlCharSets[KPW_CONTROL_STYLE_COURIER], // DWORD fdwCharSet,          // character set identifier
                              OUT_DEFAULT_PRECIS,         // DWORD fdwOutputPrecision,  // output precision
                              CLIP_DEFAULT_PRECIS,        // DWORD fdwClipPrecision,    // clipping precision
                              DEFAULT_QUALITY,            // DWORD fdwQuality,          // output quality
                              DEFAULT_PITCH, // |FF_SWISS,     // DWORD fdwPitchAndFamily,   // pitch and family
                              "Courier" // "MonospaceLT"  // LPCTSTR lpszFace           // pointer to typeface name string
                           );
                        if(hfont==NULL)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     }


                     if(SUCCEEDED(retc))
                        if(!PostMessage(cur_wnd->m_hDisplayCtrl, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
                  break;
#endif

////           case WM_KEYFIRST:
//             case WM_KEYDOWN:
//                if(msg.wParam>=Spc) break;
               case WM_CHAR:
                  ch = (unsigned char)msg.wParam;
                  if(ch==KP_HP11_TOGGLE_CONSOLE)
                  {
                     if(EmuWv.m_hWndHandle==NULL) retc=EmuWv.Init(pPars->hInstance, NULL);
                     else retc=EmuWv.DestroyWindow();
                  }
                  else
                  {
                     retc=EmuWv.wkbtobuf(ch);
                  }

// /* if((msg.wParam<Spc) || (msg.wParam>=0177)) */ { char str_buf[100]; sprintf(str_buf, "%d", msg.wParam), KP_TRACE(str_buf); }

                  break;

               case WM_KP_REMOTE_CALL:
// KP_TRACE_("kphp11: WM_KP_REMOTE_CALL[%d] received", ((KpRcPars *)(msg.lParam))->iOpCode);
// PutLogMessage_("KpHp11Idle(): WM_KP_REMOTE_CALL[%d] received", ((KpRcPars *)(msg.lParam))->iOpCode);
                  if(SUCCEEDED(retc))
                     if(!EmuDv.ddputw(DEV_RC, 0, RC_ADDR1, (Word16Typ)(msg.lParam & 0xFFFF)))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                     if(!EmuDv.ddputw(DEV_RC, 0, RC_ADDR2, (Word16Typ)((msg.lParam >> 16) & 0xFFFF)))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                     if(!EmuDv.ddputw(DEV_RC, 0, RC_CSR, RC_ready))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                  break;

               case WM_TIMER:
                  if(theKpStAppPtr) if(msg.wParam == theKpStAppPtr->m_iRestMinsTimer)
                     PostThreadMessage(iKpMainThread, msg.message, msg.wParam, msg.lParam);
                  break;

               case WM_COMMAND:
                  switch(LOWORD(msg.wParam))
                  {
                  case IDCANCEL:
                     PostThreadMessage(iKpMainThread, msg.message, msg.wParam, msg.lParam);
                     endfl = True;
                     break;
                  }
                  break;

               case WM_QUIT:
// Kaÿkod”l buvo uÿkomentuotas? Gal tik standalone kphp11 reikia, embeddintiems ne?
//                PostThreadMessage(iKpMainThread, msg.message, msg.wParam, msg.lParam);
                  endfl = True;
                  break;

               default:
                  DispatchMessage(&msg);
                  break;
               }

// ---------------------------
#ifdef Debug
               if(SUCCEEDED(retc))
               {
                  switch(msg.message)
                  {
                  case WM_PAINT:
                  case WM_MOUSEFIRST:
                  case 0x0118:
                     break;
                  case WM_NCMOUSEMOVE:
// sprintf((char *)str_buf, "W    WM_NCMOUSEMOVE   %x %x", msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  case WM_CREATE:
// sprintf((char *)str_buf, "W    WM_CREATE        %x %x", msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  case WM_KP_CREATE:
// sprintf((char *)str_buf, "W    WM_KP_CREATE     %x %x", msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  case WM_INITDIALOG:
// sprintf((char *)str_buf, "W    WM_INITDIALOG    %x %x", msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  case WM_CLOSE:
// sprintf((char *)str_buf, "W    WM_CLOSE         %x %x", msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  case WM_CHAR:
// sprintf((char *)str_buf, "W    WM_CHAR          %c %x %x", msg.wParam, msg.wParam, msg.lParam); KP_TRACE(str_buf);
                     break;
//             case WM_KEYFIRST:
               case WM_KEYDOWN:
// sprintf((char *)str_buf, "W    WM_KEYDOWN       %c %x %x", msg.wParam, msg.wParam, msg.lParam); KP_TRACE(str_buf);
                     break;
                  default:
// sprintf((char *)str_buf, "W         %x          %x %x", msg.message, msg.wParam, msg.lParam); KP_TRACE2(str_buf);
                     break;
                  }
               }
#endif

// --------------------------- process keyboard input
               if(SUCCEEDED(retc))
               {
                  ch = Nul;
                  if(KpWndListObj.m_W_first != NULL) ch = EmuWv.wgetchar();
                  if(Nul != ch)
                  {
                     switch(EmuSv.status)
                     {
                     case Monitor:
                        EmuMv.process(ch);
                        break;

                     case Run:
                     case Wait:
/* !!!! trukis is klaviaturos */
                        if(
                           (ch == KP_HP11_BREAK) ||
                           (ch == KP_HP11_TOGGLE_TRACE) ||
                           (ch == KP_HP11_TOGGLE_TR_INT)
                          )
                        {
                           EmuMv.process(ch);
                        }
                        else
                        {
                           EmuDv.tokb(ch);
                           if(!EmuDv.ddputw(DEV_TT, 0, TT_in_CSR, TT_ready))
                           {
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                           }
                        }
                        break;

                     }
                  }
               }
            }
         }

      } while((!endfl) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

   if(EmuWv.m_hWndHandle!=NULL)
   {
      retc0 = EmuWv.DestroyWindow();
      if(SUCCEEDED(retc)) retc = retc0;
   }

   KP_DELETE(pPars);

// PutLogMessage_("KpHp11Idle() thread: %d stopped EmuTv.m_lKphp11ThreadId", EmuTv.m_lKphp11ThreadId);

   lKphp11ThreadId = EmuTv.m_lKphp11ThreadId = 0L;

return(RET_CODE_MAIN(retc));
}


// =================================================
// kai kurie daznesni KPHP11_RC iskvietimai

// ----------------------------------------
HRESULT EmuTt::GetHp11Variable(int *piVarPtr, int iHp11Address)
{
HRESULT retc=S_OK;
static KpRcPars rc_pars;
static int ret_val[3];

   if((piVarPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode=KP_RC_GET_VARIABLE;
      rc_pars.iParBlSize=sizeof(rc_pars);
      rc_pars.enc.pData = ret_val;
      rc_pars.enc.iDataLen = sizeof(int);
      rc_pars.enc.lCtrl=iHp11Address;

#ifdef Debug_RYt_putw
PutLogMessage_("GHV() ....>>>> %x %x", &rc_pars, ret_val);
#endif

      retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }

   if(SUCCEEDED(retc)) *piVarPtr=ret_val[0];

return(retc);
}


HRESULT EmuTt::GetHp11VariableLong(long *plVarPtr, int iHp11Address)
{
HRESULT retc=S_OK;
int low_word;
int high_word;

   KP_ASSERT(plVarPtr, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetHp11Variable(&low_word, iHp11Address);
   if(SUCCEEDED(retc)) retc = GetHp11Variable(&high_word, iHp11Address + 2);

   if(SUCCEEDED(retc)) *plVarPtr = (high_word << 16) | (low_word & 0xFFFF);

return(retc);
}


HRESULT EmuTt::SetHp11Variable(int iValue, int iHp11Address)
{
HRESULT retc=S_OK;
static KpRcPars rc_pars;
static int val[3];

   val[0]=iValue;

   rc_pars.iOpCode = KP_RC_SET_VARIABLE;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.enc.pData = val;
   rc_pars.enc.iDataLen = sizeof(iValue);
   rc_pars.enc.lCtrl = iHp11Address;

#ifdef Debug_RYt_putw
PutLogMessage_("SHV() .... %x %x", &rc_pars, val);
#endif

   retc=EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


// -------------------------------------------
HRESULT EmuTt::CallRCCallBack(KpCommonCallBackIxs  iCallBackIx, bool bCheckErrors)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;

   KP_ASSERT((iCallBackIx >= 0) && (iCallBackIx < KpHp11NumOfExtFun), E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_CALLBACK;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iCallBackIx = iCallBackIx;
      rc_pars.enc.pCallBackPars = NULL;

      retc = ExecRemoteCall(&rc_pars /* , lMainThreadId */, bCheckErrors);
   }

return(retc);
}


HRESULT EmuTt::CallRCCallBackRetC(KpCommonCallBackIxs  iCallBackIx, bool bCheckErrors)
{
static HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static KpRcPars rc_pars;

   retc = S_OK;
// PutLogMessage_("CallRCCallBackRetC() 1 %d %x", iCallBackIx, retc);

   KP_ASSERT((iCallBackIx > 0) && (iCallBackIx < KpHp11NumOfExtFun), E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_CALLBACK; // KP_RC_CALLBACK_AND_STORE_RETC;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iCallBackIx = iCallBackIx;
      rc_pars.enc.pCallBackPars = &retc;

// PutLogMessage_("CallRCCallBackRetC() 2 %d", rc_pars.enc.iCallBackIx);
      retc0 = ExecRemoteCall(&rc_pars /* , lMainThreadId */, bCheckErrors);
      if(SUCCEEDED(retc)) retc = retc0;
   }

return(retc);
}


