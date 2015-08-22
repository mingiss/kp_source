// ---------------------------
// lzdsh.cpp
// zodyno perziuros programa
// lzdshd.exe - WinLED Demo, zodynas vlzd2.xdb
// lzdshl.exe - WinLED Lengvai
// lzdshp.exe - WinLED Pro, zodynai vlz2.xdb, lvz2.xdb
//
// kopijuojant i distributyva pervadinti atsizvelgiant i lango skina:
// standartinis:
// lzdshd_sta.exe
// lzdshl_sta.exe
// lzdshp_sta.exe
//
// medinis:
// lzdshd_mahd.exe
// lzdshl_mahd.exe
// lzdshp_mahd.exe
//
// 2012.10.12 mp Invalid thread identifier, klaida_20121011_Mindaugas_Navickas
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#ifdef KP_USE_WXWIDGETS
#include "wx/app.h"
#include "wx/frame.h"
#include "wx/listbox.h"
#include "wx/sizer.h"
#endif

#ifdef IBSH_RES_MODE_MSHTML
#if CompilerGr==Mingw
#include "HTMLWindow.h"
#endif
#endif

#if CompilerGr==Mingw
// #include <pthread.h>
// #include "seh.h"
#endif

#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#ifdef KP_USE_TextGRAB
// #include "atlbase.h"
#include "tgsdkx.h"
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
#include "KpPubDlg.h"
#include "KpRtfDlg.h"
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr==Mingw
#include "KpGecko.h"
#  endif
#endif
#include "iBshl.h"
#include "lzdsh.h"
#include "lzdshl.h"
#include "lzdshr.h"
#include "lzdsht.h"
#include "lzdsho.h"
#include "lzdshh.h"
#include "lzdshv.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

#ifdef KP_USE_WXWIDGETS
// #error KP_USE_WXWIDGETS
#endif

#if KP_XGECKO_VER != 124
// #error lûþta su nauju XGecko (spaudinëjant nuorodas ðokinëjant po þodynus)
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "lzdsh";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl = False;

KpErrorProcClass KpErrorProc(True, 71);

#ifdef KP_USE_WXWIDGETS
IMPLEMENT_APP(LzdShApp)
#else
// LzdShApp theLzdShApp;
#endif



int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs + LZDSH_RC_NumOfRcIxs;

KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 + LZDSH_RC_NumOfRcIxs_1 + 1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,
   ResetRestDays_RC,

   RegSert_RC,
   UnRegSert_RC,

#ifdef LZDSHT_ENCODED
   WriteRtfFromImg,
   GetHwFromImg,
#endif

   NULL
};


// -----------------------------------------
// LzdShDlg theDialog;
// LzdShDlg *pDialogPtr = NULL;
// KpGeckoDialog *KpGeckoDialogPtr = NULL;

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
// wxDialog *pTestWindow = NULL;
// wxDialog TestWindow(NULL, 300, "TestWindow", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, "dialogBox");
#endif
#endif


// ----------------------------------
// LzdShOptDlg theOptDialog;
LzdShOptDlg *pOptDialog = NULL;

// ----------------------------------
LzdShHelpDlg *pHelpDialog = NULL;

// ----------------------------------
LzdShAboutDlg *pAboutDialog = NULL;

// ----------------------------------
// LzdShSearch theSearchThread;
// LzdShSearch *pLzdSearch = NULL;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
#ifdef KP_USE_WXWIDGETS
bool LzdShApp::OnInit()
#else
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#endif
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
#ifdef KP_USE_WXWIDGETS
bool retw = True;
#else
DWORD retw = EXIT_SUCCESS; // 0L; // True;
#endif
HCURSOR cur_sav=NULL;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
int num_of_lics=0;

   if(StackTop == NULL) StackTop = &nCmdShow;

#if FALSE // CompilerGr == Mingw
__seh_try // __try
#else
try
#endif
{

//-----------------
#ifdef KP_USE_WXWIDGETS
   KP_ASSERT(wxApp::OnInit(), KP_E_SYSTEM_ERROR, GetLastError(), True);
#endif

#ifdef KP_USE_WXWIDGETS
   theKpStAppPtr = &(wxGetApp());
#else
// theKpStAppPtr = &theLzdShApp;
   KP_NEW(theKpStAppPtr, LzdShApp());
#endif

//-----------------
   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetOpenResult();
#ifdef Debug
   if(SUCCEEDED(retc)) retc = KpTraceWindow.GetOpenResult();
#endif

//-----------------
   if(SUCCEEDED(retc))
   {
      cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      KP_ASSERT(cur_sav != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);
   }

   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);
// ----- iðorinis lzdshpn.ini dël lic. serverio adreso - pavojinga, galima nulauþt, pakiðant kità .ini
   if(SUCCEEDED(retc)) if(strstr(ini_fname, "lzdshpn") || strstr(ini_fname, "lzdshdn")) strcpy(ini_fname, "WinLED.ini");

   if(SUCCEEDED(retc))
      retc = theKpStAppPtr->InitStApp
      (
#ifdef KP_USE_WXWIDGETS
         wxGetInstance(),
#else
         hInstance,
#endif
         ini_fname,
#ifdef KP_USE_WXWIDGETS
         "",
#else
         lpCmdLine,
#endif
         KpStarterMode
      );

// -------------------------------------
#ifdef KP_USE_TextGRAB
   if(SUCCEEDED(retc))
   {
      retc = CoInitialize(NULL);
      if(FAILED(retc)) KP_ERROR(retc, GetLastError());
   }
#endif

// -------------------------------------
LzdShSearch *lzdsh_search = NULL;

// if(SUCCEEDED(retc))
// {
//    KpGeckoFilePtr = (KpGeckoFile *) new LzdShSearch();
//    KpFileSysPtr = (KpFileSys *) new LzdShSearch;
//    pLzdSearch = new LzdShSearch;
// }

   KP_NEWO(lzdsh_search, LzdShSearch);

// if(SUCCEEDED(retc)) theKpStAppPtr->m_pGrpKpFileSys = (KpFileSys *)lzdsh_search;

// KP_ASSERT(pLzdSearch != NULL, KP_E_OUTOFMEM, null, True);
// KP_ASSERT(theKpStAppPtr->m_pGrpKpFileSys != NULL, KP_E_OUTOFMEM, null, True);
// KP_ASSERT(lzdsh_search != NULL, KP_E_OUTOFMEM, null, True);

// if(SUCCEEDED(retc)) retc = pLzdSearch->GetOpenResult();
// if(SUCCEEDED(retc)) retc = theKpStAppPtr->m_pGrpKpFileSys->GetOpenResult();
// if(SUCCEEDED(retc)) retc = lzdsh_search->GetOpenResult();

// -------------------------------------
LzdShDlg *lzdsh_dlg = NULL;
   if(SUCCEEDED(retc))
   {
//    KpGeckoDialogPtr = (KpGeckoDialog *) new LzdShDlg;
//    KpPubDlgPtr = (KpPubDlg *) new LzdShDlg;
//    pDialogPtr = new LzdShDlg(theKpStAppPtr->m_pGrpKpFileSys);
   }

   KP_NEWO(lzdsh_dlg, LzdShDlg(lzdsh_search));

   if(SUCCEEDED(retc)) theKpStAppPtr->m_pGrpKpPubDlg = lzdsh_dlg;

// KP_ASSERT(lzdsh_dlg != NULL, KP_E_OUTOFMEM, null, True);
// if(SUCCEEDED(retc)) retc = lzdsh_dlg->GetOpenResult();

   KP_ASSERT(lzdsh_dlg->m_pKpFileSys != NULL, E_POINTER, null, True);

//-----------------
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->InitDisplay();
#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
#ifndef LZDSHT_DISPLAY_SEARCH_THREAD
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->InitThreadDisplay();
#endif
#endif

// -------------------------------------
   KP_NEWO(pOptDialog, LzdShOptDlg(lzdsh_dlg));

   KP_NEWO(pHelpDialog, LzdShHelpDlg());

   KP_NEWO(pAboutDialog, LzdShAboutDlg());

//-----------------
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->InitDictList();

   if(SUCCEEDED(retc)) retc = lzdsh_dlg->OpenWindow(hKpInstance);

#ifdef KP_USE_WXWIDGETS
   if(SUCCEEDED(retc))
   {
      KP_ASSERT(lzdsh_dlg->m_hDialogWindow != NULL, E_POINTER, null, True);
      wxCommandEvent event(0, wxID_OPEN);
      lzdsh_dlg->m_hDialogWindow->LzdShDialogProc(event);
   }
#endif

#ifndef KP_USE_WXWIDGETS

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
#if FALSE
wxPoint *pos = NULL;
KP_NEW(pos, wxPoint(200, 200));
wxSize *size = NULL;
KP_NEW(size, wxSize(200, 200));
wxString title = "TestWindow";
KP_NEW(pTestWindow, wxDialog(
                        NULL, 300,
                        title)); // ,
                        // *pos,
                        // *size,
                        // wxDEFAULT_DIALOG_STYLE);
KP_DELETE(pos);
KP_DELETE(size);
#endif
#endif
#endif

#if FALSE
   if(SUCCEEDED(retc))
   {
// fontai jau nusistate statiskai - velu keisti
      switch(iWindowsVersion)
      {
      case WinUnkn:
      case Win95:
      case Win95OSR2:
      case Win98:
      case Win98SE:
      case WinCE:
      case WinME:
         iMainFontSize=22;
         break;
      case WinNT40:
         iMainFontSize=16;
         break;
      case Win2000:
      case WinXP:
      default:
         iMainFontSize=22;
         break;
      }
   }
#endif

// --------------------
// if(SUCCEEDED(retc)) retc = pLzdSearch->OpenFiles(); // perkelta á ChangeDict()

// if(SUCCEEDED(retc)) retc = lzdsh_dlg->ChangeDict(lzdsh_dlg->m_iCurDictEntry, False); // iðkelta á LzdShDialogProc WM_CREATE

#ifdef LZDSH_EDITOR_BUILD
   if(SUCCEEDED(retc)) retc=LoadXmltTreeBitmaps();
#endif

#ifdef LZDSHT_FULL_LIST
// if(SUCCEEDED(retc)) retc = lzdsh_dlg->UpdateList(0L); // jau iðkvietë ChangeDict()
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->SelectList(0L);
#endif

// --------------------
   if(SUCCEEDED(retc)) retc = lzdsh_search->InitLzdShSearch();

   if(SUCCEEDED(retc)) retc = lzdsh_search->LzdShCreateThread(hKpInstance);

// ------------------- ieskom m_InpEdit esancio þodþio naujai pasirinktam þodyne
   if(SUCCEEDED(retc)) lzdsh_dlg->m_bKbdInput = True;
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->ProcessInput(LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER);

   if(cur_sav != NULL) SetCursor(cur_sav);
   cur_sav = NULL;

   if(SUCCEEDED(retc)) retw /* retc */ = lzdsh_dlg->DoEdit();

//-----------------
// if(SUCCEEDED(retc))
   {
      cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      if(cur_sav==NULL)
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

   if(lzdsh_search != NULL) if(lzdsh_search->m_lThreadId != 0L)
   {
//-----------------
      KP_ASSERT00(PostThreadMessage(lzdsh_search->m_lThreadId, WM_QUIT, 0, 0), KP_E_SYSTEM_ERROR, GetLastError(), False);

      Sleep(500);
//    retc0 = KpSleep(500, HWND_DESKTOP /* lzdsh_dlg->m_hDialogWindow */);
//    if(SUCCEEDED(retc)) retc = retc0;

   }

//-----------------
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->FinitDisplay();
#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
#ifndef LZDSHT_DISPLAY_SEARCH_THREAD
   if(SUCCEEDED(retc)) retc = lzdsh_dlg->FinitThreadDisplay();
#endif
#endif

//-----------------
#if FALSE
   retc0 = EmuWv.DestroyWindow();
   if(SUCCEEDED(retc)) retc = retc0;

#ifdef Debug
   retc0 = KpTraceWindow.DestroyWindow();
   if(SUCCEEDED(retc)) retc = retc0;
#endif
#endif

   if(theKpStAppPtr != NULL)
   {
      retc0 = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);
      if(SUCCEEDED(retc)) retc = retc0;
   }

   if(cur_sav != NULL) SetCursor(cur_sav);
   cur_sav = NULL;

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
#if FALSE
if(pTestWindow) pTestWindow->Destroy();
KP_DELETE(pTestWindow);
#endif
// TestWindow.Destroy();
#endif
#endif

#endif // #ifndef KP_USE_WXWIDGETS

// KP_DELETE(pLzdSearch);
// if(theKpStAppPtr != NULL) KP_DELETE(theKpStAppPtr->m_pGrpKpFileSys);
// KpGeckoFilePtr = NULL;
// KpFileSysPtr = NULL;
   lzdsh_search = NULL;

   KP_DELETE(pOptDialog);

   KP_DELETE(pHelpDialog);

   KP_DELETE(pAboutDialog);

// KP_DELETE(pDialogPtr);
// KpGeckoDialogPtr = NULL;
// KpPubDlgPtr = NULL;
   if(theKpStAppPtr != NULL)
   {
#if TRUE // FALSE // delete theKpStAppPtr iðtrins
//    KP_DELETE(theKpStAppPtr->m_pGrpKpPubDlg); // kaþko lûþta Windows XP
#endif
   }

   KP_DELETE(theKpStAppPtr);

   lzdsh_dlg = NULL;

// --------------------------
#ifdef KP_USE_TextGRAB
// reikëtø tik CoInitialize() sëkmës atveju
   CoUninitialize();
#endif

/* if(FAILED(retc)) */ retw = RET_CODE_WIN(retc);

KP_TRACE("iseinu is OnInit()");

}
#if FALSE // CompilerGr == Mingw
#if FALSE
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_ACCESS_VIOLATION)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_MEMORY_FAULT
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_DATATYPE_MISALIGNMENT)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_MEMORY_FAULT
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_BREAKPOINT)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_SINGLE_STEP)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_ARRAY_BOUNDS_EXCEEDED)) KP_ERROR(KP_E_BUFFER_OVERFLOW, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_DENORMAL_OPERAND)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO)) KP_ERROR(KP_E_DIV_ZERO, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_INEXACT_RESULT)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_INVALID_OPERATION)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_OVERFLOW)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_ARITHM_OVERFL
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_STACK_CHECK)) KP_ERROR(KP_E_OUTOFMEM, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_FLT_UNDERFLOW)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_ARITHM_OVERFL
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_INT_OVERFLOW)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_ARITHM_OVERFL
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_PRIV_INSTRUCTION)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_IN_PAGE_ERROR)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_MEMORY_FAULT
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_ILLEGAL_INSTRUCTION)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_NONCONTINUABLE_EXCEPTION)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_STACK_OVERFLOW)) KP_ERROR(KP_E_OUTOFMEM, null)
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_INVALID_DISPOSITION)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_MEMORY_FAULT
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_GUARD_PAGE)) KP_ERROR(KP_E_SYSTEM_ERROR, null) // KP_E_MEMORY_FAULT
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), EXCEPTION_INVALID_HANDLE)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
#endif
__seh_except /* __except */(KpExceptionFilter(GetExceptionCode(), 0)) KP_ERROR(KP_E_SYSTEM_ERROR, null)
__seh_end_except
#else
catch(const char *msg) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)msg)
catch(int sig){ unsigned char out_str[100]; sprintf((char *)out_str, "sig: %d", sig); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::bad_alloc& ba){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::bad_alloc&: %s", ba.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception& ex){ unsigned char out_str[1000]; sprintf((char *)out_str, "std::exception&: %s", ex.what()); KP_ERROR(KP_E_SYSTEM_ERROR, out_str); }
catch(const std::exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::exception*")
// catch(const Exception& ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception&")
// catch(const Exception *ex) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"std::Exception*")
catch(const EXCEPTION_DEBUG_INFO& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO&")
catch(const EXCEPTION_DEBUG_INFO *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_DEBUG_INFO*")
catch(const EXCEPTION_RECORD& p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD&")
catch(const EXCEPTION_RECORD *p) KP_ERROR(KP_E_SYSTEM_ERROR, (unsigned char *)"EXCEPTION_RECORD*")
catch(...) KP_ERROR(KP_E_SYSTEM_ERROR, null);
#endif

return(retw);
}
