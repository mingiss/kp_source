// ---------------------------------------------
// kpapp.cpp
// apsaugota aplikacija  
// pasenes, naudojamas tik pdfstart, pdfstarw, perkelta i kpstap.cpp
//

// ================================================== definitions
#include "stdafx.h"

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindows.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpapp.h"
#include "resource.h"
#include "KpAppDialog.h"


//-------------------------------------------------------------------------
KpApp::KpApp()
{
   m_nCmdShow=SW_SHOWNORMAL;

   m_szTitle[0]=Nul;
   m_szWindowClass[0]=Nul;

   m_iCompId=0;
   m_iCodeRet1=0;
   m_iCodeRet2=0;
   m_iCodeRet3=0;
}


//-------------------------------------------------------------------------
//  FUNKTION: RegisterClass()
//
//  AUFGABE: Registriert die Fensterklasse.
//
//  KOMMENTARE:
//
//    Diese Funktion und ihre Verwendung sind nur notwendig, wenn dieser Code
//    mit Win32-Systemen vor der 'RegisterClassEx'-Funktion kompatibel sein soll,
//    die zu Windows 95 hinzugefügt wurde. Es ist wichtig diese Funktion aufzurufen,
//    damit der Anwendung kleine Symbole mit den richtigen Proportionen zugewiesen
//    werden.
//
#if Envir==MSWin32
HRESULT /* ATOM */ KpApp::RegisterClass(HINSTANCE hInstance, TCHAR* szWindowClassName)
{
WNDCLASSEX wcex;
HRESULT retc=S_OK;

   wcex.cbSize        = sizeof(WNDCLASSEX); 

   wcex.style         = CS_HREDRAW | CS_VREDRAW;

// wcex.lpfnWndProc   = (WNDPROC)WndProc;
   wcex.lpfnWndProc   = (WNDPROC)KpAppDialogProc;

   wcex.cbClsExtra    = 0;
   wcex.cbWndExtra    = 0;
   wcex.hInstance     = hInstance;
   
   wcex.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_PDFSTARW);
   if(wcex.hIcon==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {   
      wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
      if(wcex.hCursor==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   
   if(SUCCEEDED(retc))
   {   
      wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
      wcex.lpszMenuName  = (LPCSTR)IDC_PDFSTARW;

      wcex.lpszClassName = szWindowClassName;

      wcex.hIconSm       = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
      if(wcex.hIconSm==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {   
      if(::RegisterClassEx(&wcex)==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL);
   }
   
return(retc);
}
#endif


//-------------------------------------------------------------------------
#if Envir==MSWin32
BOOL CALLBACK KpAppDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM /* lParam */  // second message parameter
)
{
// HDC hdc;
// PAINTSTRUCT ps;
// // RECT rt;
// BOOL retw=TRUE;
BOOL retw=FALSE;

   switch(uMsg) 
   {
      case WM_INITDIALOG:
         retw=TRUE;
         break;
         
      case WM_COMMAND:
         if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
         {
            EndDialog(hwndDlg, LOWORD(wParam)); // !!! kelti i KpAppDialog::DestroyWindow()
            retw=TRUE;
         }
         break;
                        
//    case WM_PAINT:
//       hdc = BeginPaint (hwndDlg, &ps);
// // ZU ERLEDIGEN: Hier beliebigen Code zum Zeichnen hinzufügen...
// //    GetClientRect(hWnd, &rt);
// //    DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
//       EndPaint(hwndDlg, &ps);
//       break;

//    case WM_DESTROY:
//       retw=EndDialog(hwndDlg, TRUE);
//       break;

//    default:
//       retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
//       break;

   }
   
return(retw);
}
#endif


//
//  FUNKTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  AUFGABE:  Verarbeitet Nachrichten für das Hauptfenster.
//
//  WM_COMMAND  - Anwendungsmenü verarbeiten
//  WM_PAINT    - Hauptfenster darstellen
//  WM_DESTROY  - Beendigungsnachricht ausgeben und zurückkehren
//
//
// #if Envir==MSWin32
// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
// int wmId;
// int wmEvent;

// PAINTSTRUCT ps;
// HDC hdc;
// TCHAR szHello[MAX_LOADSTRING];

// RECT rt;

// LRESULT retw=0;
   
// LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

// switch(message) 
// {
//    case WM_COMMAND:
//       wmId=LOWORD(wParam); 
//       wmEvent=HIWORD(wParam); 

// Menüauswahlen analysieren:
//       switch(wmId) 
//       {
//          case IDM_ABOUT:
//             DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
//             break;
//          case IDM_EXIT:
//             DestroyWindow(hWnd);
//             break;
//          default:
//             retw=DefWindowProc(hWnd, message, wParam, lParam);
//             break;
//       }
//       break;
//    case WM_PAINT:
//       hdc = BeginPaint (hWnd, &ps);
// ZU ERLEDIGEN: Hier beliebigen Code zum Zeichnen hinzufügen...
//       GetClientRect(hWnd, &rt);
//       DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
//       EndPaint(hWnd, &ps);
//       break;
//    case WM_DESTROY:
//       PostQuitMessage(0);
//       break;
//    default:
//       retw=DefWindowProc( hWnd, message, wParam, lParam );
//       break;
// }

// return(retw);
// }
// #endif


// // Nachrichtenbehandlungsroutine für "Info"-Feld.
// #if Envir==MSWin32
// LRESULT CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
// {
//         switch( message )
//         {
//                 case WM_INITDIALOG:
//                                 return TRUE;
// 
//                 case WM_COMMAND:
//                         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
//                         {
//                                 EndDialog(hDlg, LOWORD(wParam));
//                                 return TRUE;
//                         }
//                         break;
//         }
//     return FALSE;
// }
// #endif


//-------------------------------------------------------------------------
#if Envir==MSWin32
HRESULT KpApp::Process(HINSTANCE hInstance, int nCmdShow)
{
HRESULT retc=S_OK;

   m_hInstance=hInstance; // Instanzzugriffsnummer in unserer globalen Variable speichern
   m_nCmdShow=nCmdShow;
   
// Globale Zeichenfolgen initialisieren
   if(LoadString(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL);

// LoadString(hInstance, IDC_PDFSTARW, m_szWindowClass, MAX_LOADSTRING);

   if(SUCCEEDED(retc))
      if(LoadString(hInstance, IDC_MAIN_DLG, m_szWindowClass, MAX_LOADSTRING)==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=RegisterClass(hInstance, m_szWindowClass);

// Initialisierung der Anwendung durchführen:
   if(SUCCEEDED(retc)) if(!InitInstance()) retc=KP_E_SYSTEM_ERROR;

return(retc);
}
#endif


//-------------------------------------------------------------------------
HRESULT KpApp::InitApp(HINSTANCE hInstance)
{
HRESULT retc=S_OK;

   InitCommonApp(hInstance);

#if 0
   retc=GetCompId();

   if(SUCCEEDED(retc))
   {
      retc=GetSavedCode();
      if(SUCCEEDED(retc)) retc=TestCode();
      if(FAILED(retc))
#endif   
         retc=ProcessDialog();
#if 0
   }

   if(SUCCEEDED(retc)) retc=TestCode();
   if(SUCCEEDED(retc))
      retc=SaveCode();
   else
   {
      if(retc==KP_E_ILL_CODE) KpMsgOut((const unsigned char *)"Blogas registracijos kodas");
   }
#endif

return(retc);
}


// ------------------------------
HRESULT KpApp::ProcessDialog(void)
{
HRESULT retc=S_OK;
KpAppDialog *dlg_ptr=NULL;
int nResponse;
int comp_id_1;

   comp_id_1=rand(m_iCompId);

   KP_NEW(dlg_ptr, KpAppDialog(comp_id_1, (KpAppStartData.sProdVer^comp_id_1)&0xFFFF, 0 /* (PdfStartData.sLicense^comp_id_1)&0xFFFF */,
                  m_hInstance));

   if(SUCCEEDED(retc)) retc=dlg_ptr->GetOpenResult();

   if(SUCCEEDED(retc))
   {
//    m_pMainWnd=dlg_ptr;
//    pMainWindow=dlg_ptr;
      nResponse=dlg_ptr->DoModal();
      if(nResponse==IDOK)
      {
         retc=dlg_ptr->GetData(&m_iCodeRet1, &m_iCodeRet2, &m_iCodeRet3);
         
         dlg_ptr->DestroyWindow();
         KP_DELETE(dlg_ptr);
         Sleep(100);
      }
      else if(nResponse==IDCANCEL)
      {
         dlg_ptr->DestroyWindow();
         KP_DELETE(dlg_ptr);
         Sleep(100);

         retc=KP_E_CANCEL;
      }
   }

   KP_DELETE(dlg_ptr);

return(retc);
}


// -------------------------------
void KpAppTop(void){}


// ------------------------------
HRESULT KpApp::GetCompId(void)
{
HRESULT retc=S_OK;

   m_iCompId=0;

#if FALSE
unsigned char dat_buf[BIOS_DAT_SIZE+1];
unsigned char *pntd;

   retc=GetBIOSDate(dat_buf);
   if(SUCCEEDED(retc))
   {
// KpMsgOut(dat_buf);
      pntd=dat_buf;
      while(*pntd)
      {
         if(*pntd=='.') *pntd=Nul;
         pntd++;
      }
      m_iCompId=(atoi((const char *)dat_buf)-1981)*12*31+
                 atoi((const char *)dat_buf+5)*31+
                 atoi((const char *)dat_buf+8);
   }
#endif

#if FALSE
long ser_num;
unsigned char disk_label_buf[KP_MAX_FNAME_LEN+1];

   retc=GetDiskInfo((unsigned char *)"C:\\", &ser_num, disk_label_buf);
   
   if(SUCCEEDED(retc)) m_iCompId=ser_num & 0xFFFF;

#endif



#if TRUE
   long id = getHardDriveComputerID();
   m_iCompId=id & 0xFFFF;
#endif


//  m_iCompId=1;


unsigned char out_str[100];
sprintf((char *)out_str, "%ld", m_iCompId);
KpMsgOut(out_str);

return(retc);
}


// ------------------------------
HRESULT KpApp::GetSavedCode(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey;
DWORD dwBufLen;
DWORD dwValType;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];

   m_iCodeRet1=0;
   m_iCodeRet2=0;
   m_iCodeRet3=0;

   code_buf[0]=Nul;
   sprintf((char *)key_name,
      "Software\\Tev\\p%02d_v%01d.%02d",
      KpAppStartData.sProdVer/1000,
      (KpAppStartData.sProdVer/100) % 10,
      KpAppStartData.sProdVer % 100);

   retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
      (LPCTSTR)key_name,
      0, KEY_QUERY_VALUE, &hKey );
   if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;

   if(SUCCEEDED(retc))
   {
      dwBufLen=KP_MAX_FILE_LIN_WDT;
      retw=RegQueryValueEx(hKey, 
         "RegCode",
         NULL, &dwValType,
         (LPBYTE)code_buf, &dwBufLen);
      if(retw==ERROR_SUCCESS) code_buf[dwBufLen]=Nul;
      else retc=KP_E_KWD_NOT_FOUND;
   }

   if(SUCCEEDED(retc))
      if(strlen(code_buf) != 4 + 1 + 4 /* + 1 + 4 */)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc))
      if((code_buf[4]!='-') /* || (code_buf[9]!='-') */)
         retc=KP_E_ILL_CODE;

   if(SUCCEEDED(retc)){ code_buf[4]=Nul; /* code_buf[9]=Nul; */}

   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf, &m_iCodeRet1); // outputs error messages !!!
   if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+5, &m_iCodeRet2);
// if(SUCCEEDED(retc)) retc=ScanKeyHex(code_buf+10, &m_iCodeRet3);

return(retc);
}


// ------------------------------
HRESULT KpApp::SaveCode(void)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
unsigned char code_buf[KP_MAX_FILE_LIN_WDT+1];
DWORD dwDisposition;

   retc=FormatKeyHex(code_buf, m_iCodeRet1);
   if(SUCCEEDED(retc))
   {
      code_buf[4]='-';
      retc=FormatKeyHex(code_buf+5, m_iCodeRet2);
   }
   code_buf[9]=Nul;
/*
   if(SUCCEEDED(retc))
   {
      code_buf[9]='-';
      retc=FormatKeyHex(code_buf+10, m_iCodeRet3);
   }
   code_buf[14]=Nul;
*/

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\Tev\\p%02d_v%01d.%02d",
         KpAppStartData.sProdVer/1000,
         (KpAppStartData.sProdVer/100) % 10,
         KpAppStartData.sProdVer % 100);

      retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition);
      
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      retw=RegSetValueEx(hKey,
         "RegCode",
         0, REG_SZ,
         code_buf,
         strlen(code_buf));
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// ------------------------------
HRESULT KpApp::TestCode(void)
{
HRESULT retc=S_OK;
int comp_id_1;

   comp_id_1=rand(m_iCompId);

   if((m_iCodeRet1!=rand(comp_id_1)) ||
      (m_iCodeRet2!=rand((KpAppStartData.sProdVer^comp_id_1)&0xFFFF))
/* || (m_iCodeRet3!=rand((KpAppStartData.sLicense^comp_id_1)&0xFFFF)) */)
      retc=KP_E_ILL_CODE;

return(retc);
}


//----------------------------------------
void PackBIOSDate(unsigned char *lpszOutBuf, 
                  const unsigned char *lpszInBuf)
{
unsigned char *pntd;

   pntd=lpszOutBuf;
   if(atoi((const char *)lpszInBuf+6)>81)
   {
      (*pntd++)='1';
      (*pntd++)='9';
   }
   else
   {
      (*pntd++)='2';
      (*pntd++)='0';
   }
   (*pntd++)=lpszInBuf[6];
   (*pntd++)=lpszInBuf[7];
   (*pntd++)='.';
   (*pntd++)=lpszInBuf[0];
   (*pntd++)=lpszInBuf[1];
   (*pntd++)='.';
   (*pntd++)=lpszInBuf[3];
   (*pntd++)=lpszInBuf[4];
   (*pntd++)=Nul;
}


HRESULT GetBIOSDate(unsigned char *lpszDatBuf)
{
HRESULT retc=S_OK;
LONG retw=ERROR_SUCCESS;
MSWin32Version win_ver;
unsigned char str_buf[BIOS_DAT_SIZE+1];
#if (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HKEY hKey;
char szBiosDate[80+1];
DWORD dwBufLen;
#endif

   strcpy(lpszDatBuf, "XXXX.XX.XX");

#if (Envir==MSDos) || (Envir==MSDosCon)

   strncpy(str_buf, (char *)0xffff5, 8);
   str_buf[8]=0;
   PackBIOSDate(lpszDatBuf, str_buf);

#elif (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
   
   if(SUCCEEDED(retc)) win_ver=iWindowsVersion;

   if(SUCCEEDED(retc)) switch(win_ver)
   {
   case Win95:
   case Win98:
   case WinCE:    // ???
   case WinME:    // ???

      strncpy(str_buf, (char *)0xffff5, 8);
      str_buf[8]=0;
      PackBIOSDate(lpszDatBuf, str_buf);

      break;

   case WinNT40:
   case Win2000:
   case WinXP:    // ???

      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
         "HARDWARE\\DESCRIPTION\\System",
         0, KEY_QUERY_VALUE, &hKey );
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {  
         dwBufLen=80;
         retw=RegQueryValueEx(hKey, "SystemBiosDate", NULL, NULL,
            (LPBYTE) szBiosDate, &dwBufLen);
         if(retw==ERROR_SUCCESS) szBiosDate[dwBufLen]=Nul;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         RegCloseKey(hKey);
      }

      if(SUCCEEDED(retc))
      {
         PackBIOSDate(lpszDatBuf, (const unsigned char *)szBiosDate);
      }
      break;

   default:
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKNOWN_SYSTEM, null, True, __FILE__, __LINE__, 0L);
      break;
   }

#else

   if(SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKNOWN_SYSTEM, null, True, __FILE__, __LINE__, 0L);

#endif

return(retc);
}


//-------------------------------------------- get disk serial number and label
HRESULT GetDiskInfo(const unsigned char *lpszVolName, long *plSerNum, unsigned char *lpszLabel)
{
HRESULT retc=S_OK;

   lpszLabel[0]=Nul;
   *plSerNum=0L;

#if FALSE

unsigned char str_buf[100];
short disk_no; 
union
{
   struct
   {
      short midInfoLevel;                // information level
      long midSerialNum;                 // serial number
      unsigned char midVolLabel[11];     // ASCII volume label
      unsigned char midFileSysType[8];   // file system type
   } main;
   short loc;
} MediaID;

long r_ebp=0;
short r_bp=0;
short r_ss=0;

   lpszLabel[0]=Nul;
   *plSerNum=0L;

   MediaID.main.midSerialNum=0;
   MediaID.main.midVolLabel[0]=Nul;

   disk_no=iDiskNo;
   MediaID.main.midInfoLevel=0;

   _asm
   {
      push  ax
      push  bx
      push  cx
      push  dx
      push  ds

      mov   bx, disk_no
      mov   ch, 08h              ;DeviceCat
      mov   cl, 66h              ;Get Media ID

;     mov   dx, seg MediaID
      mov   dx, ss
      mov   ds, dx

;     mov   dx, offset MediaID   ;ds:dx points to MID structure
      mov   dx, bp
      sub   dx, 88h              ; offset of MediaID !!!

      mov   ax, 440Dh            ;IOCTL for block device
      int   21h

      jnc   GetDiskInfo_success
      mov   retc, 80040306h     ; KP_E_SYSTEM_ERROR !!!
   
GetDiskInfo_success:
      pop   ds
      pop   dx
      pop   cx
      pop   bx
      pop   ax



      mov   r_ebp, ebp
      mov   r_bp, bp
      mov   r_ss, ss
   }

   if(FAILED(retc))
      retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);


BOOL SetVolumeLabel(
  LPCTSTR lpRootPathName,  // pointer to name of root directory for 
                           // volume
  LPCTSTR lpVolumeName   // name for the volume
);
 



   sprintf((char *)str_buf, "ebp: %x bp: %x ss: %x ss:bp: %x", r_ebp, r_bp, r_ss, (r_ss<<8)+r_bp);
   KpMsgOut(str_buf);



   sprintf((char *)str_buf, "ser_no: %d", MediaID.main.midSerialNum);
   KpMsgOut(str_buf);

   strncpy(str_buf, MediaID.main.midVolLabel, 11);
   str_buf[11]=Nul;
   KpMsgOut(str_buf);


// ------------------------------------
char vol_name[20+1];
unsigned long ser_no;

   if(GetVolumeInformation("e:\\", vol_name, 20, &ser_no, &max_fn_len, &sys_fl, fs_name, 100)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

#endif

unsigned long max_fn_len;
unsigned long sys_fl;
char fs_name[KP_MAX_FNAME_LEN+1];

   if(GetVolumeInformation((const char *)lpszVolName, (char *)lpszLabel, KP_MAX_FNAME_LEN, (unsigned long *)plSerNum, &max_fn_len, &sys_fl, fs_name, KP_MAX_FNAME_LEN)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL  );

return(retc);
}


//-------------------------------------------- pseudo random generator
int rand(int prev)
{
return((prev*30497L+22571) % 65536);
}

//------------------- converts integer security key to pseudo-hex string
HRESULT FormatKeyHex(unsigned char *szKeyBuf, int iKey)
{
HRESULT retc=S_OK;
unsigned char *pntd;

   sprintf((char *)szKeyBuf, "%04X", iKey);

   pntd=szKeyBuf;
   while(*pntd)
   {
      switch(*pntd)
      {
      case '0':
         *pntd='K';
         break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         break;
      case 'A':
         *pntd='L';
         break;
      case 'B':
         *pntd='N';
         break;
      case 'C':
         *pntd='P';
         break;
      case 'D':
         *pntd='S';
         break;
      case 'E':
//       *pntd='E';
         break;
      case 'F':
         *pntd='U';
         break;
      }

      pntd++;
   }

return(retc);
}

#if Envir==MSWin32Mfc
HRESULT FormatKeyHex(CString *sKey, int iKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[MAX_LONG_DIGITS+1];

   if(sKey==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=FormatKeyHex(key_buf, iKey);
   if(SUCCEEDED(retc)) *sKey=key_buf;

return(retc);
}
#endif


HRESULT ScanKeyHex(const unsigned char *szKeyBuf, int *piKey)
{
HRESULT retc=S_OK;
unsigned char key_buf[5];
unsigned char *pntd;

   if(szKeyBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(strlen(szKeyBuf)>4)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      strncpy(key_buf, szKeyBuf, 4);
      key_buf[4]=Nul;

      pntd=key_buf;
      while(*pntd)
      {
         switch(*pntd)
         {
         case 'K':
            *pntd='0';
            break;
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
            break;
         case 'L':
            *pntd='A';
            break;
         case 'N':
            *pntd='B';
            break;
         case 'P':
            *pntd='C';
            break;
         case 'S':
            *pntd='D';
            break;
         case 'E':
//          *pntd='E';
            break;
         case 'U':
            *pntd='F';
            break;
         default:
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            break;
         }

         pntd++;
      }

      sscanf((const char *)key_buf, "%x", piKey);
   }

return(retc);
}

#if Envir==MSWin32Mfc
HRESULT ScanKeyHex(const CString *sKey, int *piKey)
{
HRESULT retc=S_OK;
unsigned char *buf_ptr;

   if((sKey==NULL) || (piKey==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(buf_ptr, unsigned char, sKey->GetLength() + 1);

   if(SUCCEEDED(retc)) strcpy(buf_ptr, *sKey);

   if(SUCCEEDED(retc)) retc=ScanKeyHex(buf_ptr, piKey);

return(retc);
}
#endif


// -------------------------------
void KpAppBot(void){}

