// ----------------------------
// kpcapp.cpp
// KpCommonApp implementation
//

#include "stdafx.h"

#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpcapp.h"


#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
// #error (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
#if (Envir!=MSWin32Con) // && (Envir != MSWin32ConMfc)
#error (Envir!=MSWin32) && (Envir!=MSWin32Mfc) && (Envir!=MSWin32Con)
#endif
#endif


//-------------------------------------------------------------------------
#ifdef Debug
#if (Envir==MSWin32)
KpConsole KpTraceWindow;
#endif
#endif


//-------------------------------------------------------------------------
KpCommonApp::KpCommonApp(void)
{
   m_lhOpenResult = S_OK;
   m_hInstance = NULL;

// #if (Envir==MSWin32)
   m_plCmdLineArgs = NULL;
   m_lpCmdLine = NULL;
// #endif

   m_iArgc = 0;
   m_plpszArgv = NULL;
#if FALSE
   KP_NEWCA(m_plpszArgv, unsigned char *, 1);
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_plpszArgv[0] = NULL;
      KP_NEWCA(m_plpszArgv[0], unsigned char, KP_MAX_FNAME_LEN + 1);
   }
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_iArgc = 0;
      m_lhOpenResult = GetAppName(m_plpszArgv[0]);
   }
#endif

#ifdef Envir
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = KpErrorProc.SetMsgList(KP_TRACE_WINDOW);
#endif
#endif

}


// ----------------------
KpCommonApp::~KpCommonApp(void)
{
HRESULT retc = S_OK;

// for(ii = 0; ii < iArgc; ii ++) KP_DELETEA(plpszArgv[ii]); // trint nereikia – juos iðtrins KpTree destruktorius
   KP_DELETEA(m_plpszArgv);

// #if (Envir==MSWin32)
   KP_DELETE(m_plCmdLineArgs);
// #endif

   /* retc = */ KpFinitWindows();
}


// ----------------------
HRESULT KpCommonApp::GetOpenResult(void)
{
return(m_lhOpenResult);
}


//-------------------------------------------------------------------------
HRESULT KpCommonApp::InitCommonApp(HINSTANCE hInstance, LPCSTR
// #if Envir==MSWin32
lpCmdLine
// #endif
)
{
HRESULT retc=S_OK;
HINSTANCE hinst=NULL;
// static unsigned char full_path[KP_MAX_FNAME_LEN+1];

   if(StackTop == NULL) StackTop = &lpCmdLine;

// ---------------------------------------------
// nustatom darbiná katalogà
// TUX_XFS trukdo
#if FALSE // #if TRUE //
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);

   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, full_path, False, __FILE__, __LINE__, 0L);
   }
#endif

// ---------------------------------------------
// #if Envir==MSWin32
   m_lpCmdLine=lpCmdLine;
// #endif

   if(SUCCEEDED(retc)) retc=ParseCmdLine();

   hinst=hInstance;
   if(hinst==NULL) hinst=GetModuleHandle(NULL);

   if(m_hInstance==NULL)
   {
      if(SUCCEEDED(retc)) retc=KpInitWindows(hinst);

#ifdef Debug
#if (Envir==MSWin32)
      if(SUCCEEDED(retc)) retc=WndPreg(KP_TRACE_WINDOW, TYP_Trace, hinst, NULL, True);
      if(SUCCEEDED(retc)) SetWindowPos(KpTraceWindow.m_hWndHandle, HWND_TOP, 100, 100, 900, 600, SWP_NOMOVE | SWP_NOSIZE);
#endif
#endif
   }
   m_hInstance=hinst;

   if(SUCCEEDED(retc)) retc=GetOpenResult();

return(retc);
}


//-------------------------------------------------------------------------
HRESULT KpCommonApp::CloseCommonApp(void)
{
HRESULT retc=S_OK;

   retc = KpFinitWindows();

return(retc);
}


// ---------------------
HRESULT KpCommonApp::ParseCmdLine(void)
{
HRESULT retc=S_OK;

unsigned char *cmd_sav=NULL;
const unsigned char *pnts;
unsigned char *pnt_spc;
unsigned char *pnt_quote;
unsigned char *pnt_delim;
bool inside_quotes=False;
int ii;
KpTreeEntry *entry_ptr;

#if (Envir!=MSWin32)
// if(SUCCEEDED(retc)) retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, False, __FILE__, __LINE__, 0L); // lzdenc.cpp reikalinga - suformuoja windowsine cmd eilute specialiai
#endif

// -------------------------------
   KP_DELETE(m_plCmdLineArgs);

   if(m_lpCmdLine!=NULL)
   {
      KP_NEWA(cmd_sav, unsigned char, strlen(m_lpCmdLine) + 1);

      if(SUCCEEDED(retc))
      {
         strcpy(cmd_sav, m_lpCmdLine);
         pnts=cmd_sav;
         pnt_spc=NULL;
         do
         {
            pnt_spc=NULL;
            if(!inside_quotes) pnt_spc=strchr(pnts, Spc);

            pnt_quote=NULL;
            pnt_quote=strchr(pnts, C_Quote); // '\"'

            pnt_delim=pnt_spc;
            if((pnt_delim==NULL) || ((pnt_quote!=NULL) && (pnt_quote<pnt_delim)))
            {
               pnt_delim=pnt_quote;
               inside_quotes=!inside_quotes;
            }

            if(pnt_delim!=NULL) *pnt_delim=Nul;

            if(strlen(pnts)>0)
            {
               if(m_plCmdLineArgs == NULL) KP_NEW(m_plCmdLineArgs, KpTreeEntry(pnts, NULL))
               else retc = m_plCmdLineArgs->PutToEnd(pnts);
            }

            if(pnt_delim!=NULL) pnts=pnt_delim+1;
            else pnts+=strlen(pnts);

         } while((strlen(pnts)>0) && SUCCEEDED(retc));

      } // if(SUCCEEDED(retc))

   } // if(m_lpCmdLine!=NULL)

   KP_DELETEA(cmd_sav);

// -------------------------------
   m_iArgc = 0;
   KP_DELETEA(m_plpszArgv);

   if(m_plCmdLineArgs && SUCCEEDED(retc))
   {
      ii = 0;
      if(SUCCEEDED(retc)) retc = m_plCmdLineArgs->CountEntries(&ii, 0, NULL);
      KP_NEWA(m_plpszArgv, const unsigned char *, ii);
      if(SUCCEEDED(retc))
      {
         m_iArgc = ii;
         for(ii = 0; ii < m_iArgc; ii++) m_plpszArgv[ii] = NULL;

         entry_ptr = m_plCmdLineArgs;
         for(ii = 0; (ii < m_iArgc) && SUCCEEDED(retc); ii++)
         {
            if(entry_ptr == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               m_plpszArgv[ii] = (const unsigned char *)entry_ptr->GetValue();
//             retc = entry_ptr->GetFirstChild(&entry_ptr);
               entry_ptr = entry_ptr->m_pFirstChild;
            }
         }
      }
   }

return(retc);
}


