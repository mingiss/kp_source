#if !defined(AFX_KPAPPDIALOG_H__37943B01_088A_11D8_9E09_004095201DED__INCLUDED_)
#define AFX_KPAPPDIALOG_H__37943B01_088A_11D8_9E09_004095201DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KpAppDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld KpAppDialog 

class KpAppDialog
#if Envir==MSWin32Mfc
 : public CDialog
#endif
{
   HRESULT lhOpenResult;

   HINSTANCE m_hInstance;        // aktuelle Instanz

   int m_iCode1;
   int m_iCode2;
   int m_iCode3;

#if Envir!=MSWin32Mfc
   HWND m_hDialogWindow;
#endif      

#if Envir==MSWin32Mfc
// Dialogfelddaten
   //{{AFX_DATA(KpAppDialog)
   enum { IDD = IDD_KPAPP_DIALOG };
   CString  m_Code1;
   CString  m_Code2;
   CString  m_Code3;
   CString  m_Key1;
   CString  m_Key2;
   CString  m_Key3;
   //}}AFX_DATA
#else
   unsigned char m_Code1[KP_KWD_LEN];
   unsigned char m_Code2[KP_KWD_LEN];
   unsigned char m_Code3[KP_KWD_LEN];
   unsigned char m_Key1[KP_KWD_LEN];
   unsigned char m_Key2[KP_KWD_LEN];
   unsigned char m_Key3[KP_KWD_LEN];
#endif

public:

// Konstruktion
   KpAppDialog(int iCode1, int iCode2, int iCode3,  // Standard-Konstruktor
      HINSTANCE hInst,  // aktuelle Instanz
#if Envir==MSWin32Mfc
      CWnd* // pParent
#else
      HWND  // hParent
#endif      
      = NULL);

   HRESULT GetOpenResult(void); // collected errors from lhOpenResult

#if Envir==MSWin32Mfc
// Überschreibungen
   // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
   //{{AFX_VIRTUAL(KpAppDialog)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
   //}}AFX_VIRTUAL
#else   
   void DoDataExchange(void*);
#endif

#if Envir!=MSWin32Mfc
   int  DoModal(void);
   BOOL DestroyWindow(void);
   BOOL SetDlgItemText(int nIDDlgItem, LPCTSTR lpString);
#endif

   HRESULT GetData(int *piKey1, int *piKey2, int *piKey3);

// Implementierung
protected:

#if Envir==MSWin32Mfc
   // Generierte Nachrichtenzuordnungsfunktionen
   //{{AFX_MSG(KpAppDialog)
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
#else
   BOOL OnInitDialog(void);
   void OnOK();
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_KPAPPDIALOG_H__37943B01_088A_11D8_9E09_004095201DED__INCLUDED_

