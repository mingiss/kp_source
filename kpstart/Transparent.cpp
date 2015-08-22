#include <stdio.h>
#include <windows.h>
#include <winuser.h>


BOOL CALLBACK KpTranspDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
bool endfl = FALSE;
int retp = LOWORD(wParam);
BOOL retw = FALSE;

   switch(uMsg)
   {
   case WM_CLOSE:
      endfl = TRUE;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      endfl = TRUE;
      break;

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDCANCEL:
      case IDOK:
         endfl = TRUE;
         break;
      }
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl)
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

return(retw);
}


// -----------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
// --------------------------
WNDCLASSEX wcx;

HBRUSH brush = CreateSolidBrush(GetSysColor(COLOR_DESKTOP));

   wcx.hInstance     = hInstance;
   wcx.lpszClassName = "KPTRANSP",
   wcx.lpfnWndProc   = (WNDPROC)KpTranspDialogProc;
   wcx.style         = CS_DBLCLKS;
   wcx.cbSize        = sizeof(WNDCLASSEX);
   wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
   wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
   wcx.hCursor       = LoadCursor(0, IDC_ARROW);
   wcx.lpszMenuName  = 0;
   wcx.cbClsExtra    = 0;
   wcx.cbWndExtra    = 0;
   wcx.hbrBackground = brush; // (HBRUSH)iaColorMap[KpShadowNorm];

   RegisterClassEx(&wcx);

// --------------------------
HDC dc = GetDC(HWND_DESKTOP);
HWND dlg_wnd = NULL;

   dlg_wnd = CreateWindowEx
   (
      WS_EX_LAYERED | /* WS_EX_TRANSPARENT | */ WS_EX_TOPMOST,               // DWORD dwExStyle,      // extended window style
      "KPTRANSP",
      "KpTransparent",   // LPCTSTR lpWindowName, // pointer to window name
      WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME,                  // DWORD dwStyle,        // window style
      0, // CW_USEDEFAULT // int x,               // horizontal position of window
      0, // CW_USEDEFAULT // int y,               // vertical position of window
      GetDeviceCaps(dc, HORZRES),                 // int nWidth,           // window width
      GetDeviceCaps(dc, VERTRES) - 20,                 // int nHeight,          // window height
      NULL, // HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
      0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
      hInstance,
      NULL    // LPVOID lpParam        // pointer to window-creation data
   );

// --------------------------
MSG msg;
int retp = 0;
bool endfl = FALSE;
// FILE *log_file = fopen("Transparent.log", "w");

// fprintf(log_file, "Pradzia\n"); 

   do
   {
      GetMessage(&msg, NULL, 0, 0);
// fprintf(log_file, "%d\n", msg.wParam); 

      TranslateMessage(&msg);
      DispatchMessage(&msg);

      retp = LOWORD(msg.wParam);

      switch(msg.message)
      {
      case WM_QUIT:
      case WM_CLOSE:
         endfl = TRUE;
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDCANCEL:
         case IDOK:
            endfl = TRUE;
            break;
         }
         break;
      }
      
   } while(!endfl);

   if(dlg_wnd != NULL) DestroyWindow(dlg_wnd);

// fclose(log_file);
   
return(retp /* RET_CODE_WIN(S_OK) */);
}
