//-------------------------------------------------------------------------
// kpcapp.h
// KpCommonApp definitions
// common aplikacija, windowsine
//

//-------------------------------------------------------------------------
#ifndef kpcapp_included
#define kpcapp_included

// ----------------------------------- 
// KpStdApp <-- KpCommonApp
class KpCommonApp               
   : public KpStdApp
#if Envir==MSWin32Mfc
   , public CWinApp
#endif 
{
public:
   HRESULT m_lhOpenResult;
   HINSTANCE m_hInstance;

private:
// #if (Envir==MSWin32)
   LPCSTR /* LPSTR */ m_lpCmdLine;
// #endif
public:
// #if (Envir==MSWin32)
   KpTreeEntry *m_plCmdLineArgs;
// #endif

   int m_iArgc;
   const unsigned char **m_plpszArgv;

private:
   HRESULT ParseCmdLine(void);

public:
   KpCommonApp(void);
   virtual ~KpCommonApp(void);
   HRESULT GetOpenResult(void);

   HRESULT InitCommonApp(HINSTANCE hInstance, LPCSTR /* LPSTR */ lpCmdLine);
                                 // must be called from derived KpApp::InitApp()
                                 // hInstance and lpCmdLine must be NULL for MFC applications
   HRESULT CloseCommonApp(void);
};

// extern KpCommonApp theApp; // actually must be object of application class, derived from KpCommonApp

#endif
