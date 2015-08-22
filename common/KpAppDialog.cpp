// KpAppDialog.cpp: Implementierungsdatei
// KpAppDialog.rc - example resource file
// dialog IDD_KPAPP_DIALOG must be created for each application
//

#include "stdafx.h"

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kpwindows.h"
#include "kperr.h"
#include "kpapp.h"
#include "resource.h"
// #include "pdfstart.h"
#include "KpAppDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld KpAppDialog 


//-------------------------------------------
KpAppDialog::KpAppDialog(int iCode1, int iCode2, int iCode3,
      HINSTANCE hInst,  // aktuelle Instanz
#if Envir==MSWin32Mfc
   CWnd* // pParent
#else
   HWND  // hParent
#endif      
//    = NULL
   )
#if Envir==MSWin32Mfc
   : CDialog(KpAppDialog::IDD, pParent)
#endif
{
#if Envir==MSWin32Mfc
   //{{AFX_DATA_INIT(KpAppDialog)
   m_Code1 = _T("");
   m_Code2 = _T("");
   m_Code3 = _T("");
   m_Key1 = _T("");
   m_Key2 = _T("");
   m_Key3 = _T("");
   //}}AFX_DATA_INIT
#else
   m_Code1[0]=Nul;
   m_Code2[0]=Nul;
   m_Code3[0]=Nul;
   m_Key1[0]=Nul;
   m_Key2[0]=Nul;
   m_Key3[0]=Nul;
#endif

   lhOpenResult=S_OK;

   m_hInstance=hInst;
   
   m_iCode1=iCode1;
   m_iCode2=iCode2;
   m_iCode3=iCode3;

   m_hDialogWindow=NULL;

#if Envir==MSWin32Mfc
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(&m_Code1, m_iCode1);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(&m_Code2, m_iCode2);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(&m_Code3, m_iCode3);
#else
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(m_Code1, m_iCode1);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(m_Code2, m_iCode2);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=FormatKeyHex(m_Code3, m_iCode3);
#endif
}


//-------------------------------------------
HRESULT KpAppDialog::GetOpenResult(void)
{
return(lhOpenResult);
}


//-------------------------------------------
void KpAppDialog::DoDataExchange(
#if Envir==MSWin32Mfc
   CDataExchange* pDX
#else
   void*
#endif   
   )
{
#if Envir==MSWin32Mfc
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(KpAppDialog)
   DDX_Text(pDX, IDC_EDIT1, m_Code1);
   DDX_Text(pDX, IDC_EDIT2, m_Code2);
   DDX_Text(pDX, IDC_EDIT3, m_Code3);
   DDX_Text(pDX, IDC_EDIT4, m_Key1);
   DDX_Text(pDX, IDC_EDIT5, m_Key2);
   DDX_Text(pDX, IDC_EDIT6, m_Key3);
   //}}AFX_DATA_MAP
#endif
}


#if Envir==MSWin32Mfc
BEGIN_MESSAGE_MAP(KpAppDialog, CDialog)
   //{{AFX_MSG_MAP(KpAppDialog)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten KpAppDialog 

//-------------------------------------------
BOOL KpAppDialog::OnInitDialog() 
{
#if Envir==MSWin32Mfc
   CDialog::OnInitDialog();
#endif
   
   // TODO: Zusätzliche Initialisierung hier einfügen

//--------------------------

   SetDlgItemText(IDC_EDIT1, (const char *)m_Code1);
   SetDlgItemText(IDC_EDIT2, (const char *)m_Code2);
   SetDlgItemText(IDC_EDIT3, (const char *)m_Code3);

   SetDlgItemText(IDC_EDIT7, "Jûsø registravimosi kodas:");
   SetDlgItemText(IDC_EDIT8, "Uþregistruokite produktà ir áveskite gautà raktà:");

//--------------------------

return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


//-------------------------------------------
#if Envir!=MSWin32Mfc
int KpAppDialog::DoModal(void)
{
int retw=IDOK;
HRESULT retc=S_OK;
// HWND hWnd;

//
// hWnd = CreateWindow(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
//    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, m_hInstance, NULL);
// if(hWnd==NULL) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//
// if(SUCCEEDED(retc))
// {
//   ShowWindow(hWnd, m_nCmdShow);
//   if(!UpdateWindow(hWnd))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// }

   if(SUCCEEDED(retc))
   {
//    retw=DialogBox(m_hInstance, (LPCTSTR)IDD_ABOUTBOX, 0 /* hWnd */, (DLGPROC)About);
//    retw=DialogBox(m_hInstance, "DIALOG_1", 0, KpAppDialogProc);
      retw=DialogBox(m_hInstance, (LPCTSTR)IDC_MAIN_DLG, 0, KpAppDialogProc);
      if(retw<0) // == -1
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(FAILED(retc) && (retw==IDOK)) retw=IDABORT;
   
return(retw);
}
#endif

   
//-------------------------------------------
#if Envir!=MSWin32Mfc
BOOL KpAppDialog::SetDlgItemText(int nIDDlgItem, LPCTSTR lpString)
{
return(::SetDlgItemText(m_hDialogWindow, nIDDlgItem, lpString));
}
#endif


//-------------------------------------------
void KpAppDialog::OnOK() 
{
   // TODO: Zusätzliche Prüfung hier einfügen
   
//--------------------------

// GetDlgItemText(IDC_EDIT4, &m_Key1, 5);
// GetDlgItemText(IDC_EDIT5, &m_Key2, 5);
// GetDlgItemText(IDC_EDIT6, &m_Key3, 5);
// m_szKeyRet1[4]=Nul;
// m_szKeyRet2[4]=Nul;
// m_szKeyRet3[4]=Nul;

//--------------------------

#if Envir==MSWin32Mfc
   CDialog::OnOK();
#endif
}

//-------------------------------------------
#if Envir!=MSWin32Mfc
BOOL KpAppDialog::DestroyWindow(void)
{
return(::DestroyWindow(m_hDialogWindow));
}
#endif


//-------------------------------------------
HRESULT KpAppDialog::GetData(int *piKeyRet1, int *piKeyRet2, int *piKeyRet3)
{
HRESULT retc=S_OK;

#if Envir==MSWin32Mfc
   if(SUCCEEDED(retc)) retc=ScanKeyHex(&m_Key1, piKeyRet1);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(&m_Key2, piKeyRet2);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(&m_Key3, piKeyRet3);
#else
   if(SUCCEEDED(retc)) retc=ScanKeyHex(m_Key1, piKeyRet1);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(m_Key2, piKeyRet2);
   if(SUCCEEDED(retc)) retc=ScanKeyHex(m_Key3, piKeyRet3);
#endif

return(retc);
}
 
