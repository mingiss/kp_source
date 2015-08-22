// ---------------------------------------------
// kpapp.h
// apsaugota aplikacija, pasenes


#ifndef kpapp_included
#define kpapp_included


// ----------------------------------------------
#define MAX_LOADSTRING 100

//-------------------------------------------------------------------------
#if Envir==MSWin32
extern BOOL CALLBACK KpAppDialogProc
(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM /* lParam */  // second message parameter
);

// extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

// ----------------------------------- 
typedef struct
{
   int iBoundary;          // allign to 4 bytes boundary
   unsigned char acPattern[8];      // paieskai pakeitimui is isores .exe faile
   unsigned short sProdVer;// product & version (product 1, version 1.01)
   unsigned short sReserved; // sLicense;// license number
   long lStartOfPDF;       // PDF image inside of pdfstart.exe - up to end of the file
   unsigned char lpszPassword[KP_MAX_FNAME_LEN+1];
      // application dependent data - current password of PDF file in case of PdfStart

} KpAppStartData_tag; // former PdfStartData_tag; // project depending variable setup data


extern KpAppStartData_tag KpAppStartData; // application speciffic data


// ----------------------------------- 
class KpApp : public KpCommonApp
{
private:
   int m_iCompId;
   int m_iCodeRet1;
   int m_iCodeRet2;
   int m_iCodeRet3;

   TCHAR m_szTitle[MAX_LOADSTRING];       // Text der Titelzeile
   TCHAR m_szWindowClass[MAX_LOADSTRING]; // Text der Titelzeile


   HRESULT GetCompId(void);      // reads BIOS date, converts it and saves to m_iCompId
   HRESULT GetSavedCode(void);   // reads code from registry PdfStartData.sProdVer related value to m_iCodeRet1, m_iCodeRet2, m_iCodeRet3
                                 // does not output any error message
   HRESULT SaveCode(void);       // saves m_iCodeRet1, m_iCodeRet2, m_iCodeRet3 to registry according to PdfStartData.sProdVer
   HRESULT ProcessDialog(void);  // uses m_iCompId and PdfStartData.sProdVer to generate registration key
                                 // returns code entered by user to m_iCodeRet1, m_iCodeRet2, m_iCodeRet3
   HRESULT TestCode(void);       // tests code m_iCodeRet1, m_iCodeRet2, m_iCodeRet3 according to PdfStartData.sProdVer
                                 // does not output any error message
#if Envir==MSWin32
   HRESULT /* ATOM */ RegisterClass(HINSTANCE hInstance, TCHAR* szWindowClassName);
   virtual BOOL InitInstance(void) = 0;
#endif

public:

// parameters passed to WinMain()
   int m_nCmdShow;

   KpApp();                      // constructor

#if Envir==MSWin32
   HRESULT KpApp::Process(HINSTANCE hInstance, int nCmdShow);
                                 // emulates MFC CWinApp initialization task, calls KpApp::InitInstance()
                                 // must be called from WinMain()
                                 // hInstance and nCmdShow - parameters passed to WinMain()
#endif

   HRESULT InitApp(HINSTANCE hInstance);
                                 // must be called from derived KpApp::InitInstance()
                                 // actually checks application security
};


// ================================================== pointers of code to hide
extern void KpAppTop(void);
extern void KpAppBot(void);

extern void diskid32Top(void);
extern void diskid32Bot(void);

// ================================================== hardware specific
#define BIOS_DAT_SIZE 10 // 2003.02.11

extern HRESULT GetBIOSDate(unsigned char *lpszDatBuf);
// lpszDatBuf[BIOS_DAT_SIZE+1]

// extern HRESULT GetDiskInfo(int iDiskNo, long *plSerNum, unsigned char *lpszLabel);
// iDiskNo: 0 - default drive, 1 - A:, 2 - B:, 3 - C:, ...
// unsigned char lpszLabel[KP_DOS_FNAME_LEN+1];
extern HRESULT GetDiskInfo(const unsigned char *lpszVolName, long *plSerNum, unsigned char *lpszLabel);
// lpszVolName - "A:\\", "C:\\", "D:\\", ...
// plSerNum - loginio disko serijinis numeris, ne irenginio
// lpszLabel[KP_MAX_FNAME_LEN+1]

extern long getHardDriveComputerID(void);



// ================================================== math
extern HRESULT ScanKeyHex(const unsigned char *szKeyBuf, int *piKey);
#if Envir==MSWin32Mfc
extern HRESULT ScanKeyHex(const CString *sKeyBuf, int *piKey); // scans integer security key
#endif

extern HRESULT FormatKeyHex(unsigned char *lpszKeyBuf, int iKey);
#if Envir==MSWin32Mfc
extern HRESULT FormatKeyHex(CString *sKeyBuf, int iKey);      // converts integer security key to pseudo-hex string
#endif

extern int rand(int prev); // prev - saved previous value returned by rand()

#endif

