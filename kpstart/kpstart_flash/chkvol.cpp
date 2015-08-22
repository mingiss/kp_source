// ===================================================
// chkvol.cpp
// disko failu atitikimo sarasui tikrinimas
//


// ------------------------------------
#include "envir.h"

#include <stdio.h>
// #include <iostream.h>
#include <iostream>
// #include <fstream.h>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

using namespace std;

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "chkvol.h"

// ------------------------------------
const unsigned char lpszProdName[] = "chkvol";
KpErrorProc_tag KpErrorProc(True, 43);
int iProdVerGlob=0;
bool bServiceFl=False;

ChkVol ChkVolObj;

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
BOOL CALLBACK ChkVolDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw = FALSE;
int retp = 0;
bool endfl=False;
int cur_sel = 0;
HANDLE proc = 0;
unsigned char fname[KP_MAX_FNAME_LEN + 1];

   retp = LOWORD(wParam);
   endfl=False;

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"TEV atmintuko tikrinmas", CHKVOL_TITLE_X, CHKVOL_TITLE_Y, 1, KPW_CONTROL_STYLE_HEADING_3, 0, 0, 0);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"Pasirinkite tikrinamà atmintukà:", CHKVOL_PROMPT_X, CHKVOL_PROMPT_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, 0);

      if(SUCCEEDED(retc)) retc = KpCreateComboBox(hKpInstance, hwndDlg, &ChkVolObj.m_hDevBox,
         (const unsigned char *)"DevBox",
         CHKVOL_DEVBOX_DX, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]*CHKVOL_DEVBOX_NUM_OF_ENTRIES,
         CHKVOL_DEVBOX_X, CHKVOL_DEVBOX_Y,
         KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0L,
         ChkVolObj.m_pDevList, 0);

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, &ChkVolObj.m_hProcBut,
         CHKVOL_ID_PROCESS, (const unsigned char *)"Tikrinti", CHKVOL_PROCBUT_X, CHKVOL_PROCBUT_Y);

      break; // case WM_CREATE:

   case WM_COMMAND:
      switch(retp)
      {
      case IDOK:
KP_TRACE("ChkVolDialogProc: WM_COMMAND: IDOK");
         break;

      case IDCANCEL:
KP_TRACE("ChkVolDialogProc: WM_COMMAND: IDCANCEL");
         endfl=True;
         break;

      case CHKVOL_ID_PROCESS:
         if(SUCCEEDED(retc)) retc = ChkVolObj.CompareFnames();

#if FALSE // lyginti negalima - failas keiciasi po kiekvieno primontavimo uzrakintoj busenoj (NTFS particijos rezimu)
         if(SUCCEEDED(retc))
         {
            retc = ChkVolObj.CompareFile(CHKVOL_PART_FNAME, False);
            if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;
         }
#endif

         if((ChkVolObj.m_iCurVolType == Vt_TevUnLocked) && SUCCEEDED(retc))
         {
            cur_sel = ChkVolObj.m_iCurSel;

            strcpy(fname, lpszaLockActionKwds[Fl_ToFlash]); // "restore"
            strcat(fname, ".exe");
            retc = StartProcess(fname, KPST_CUR_DIR, NULL, &proc, SW_SHOWNORMAL); // SW_SHOW);
            if(SUCCEEDED(retc)) retc = WaitForProcessEnd(proc, 0);

            if(SUCCEEDED(retc)) retc = ChkVolObj.SetCurDev(cur_sel); // traukiant/kisant atmintuka nusimus selektinimas

            if(SUCCEEDED(retc)) retc = ChkVolObj.CompareFnames();

            if(SUCCEEDED(retc)) retc = ChkVolObj.SetCurDev(0); // selektinimas buvo nusimuses - nustatom i pradzia
         }

         if(SUCCEEDED(retc))
         {
unsigned char str_buf[200];
            strcpy(str_buf, "Atmintuko rinkmenø sàraðas ");
            strcat(str_buf, ChkVolObj.m_lpszFName);
            strcat(str_buf, " sukurtas");
            KpMsgOut(ChkVolObj.m_bMakeList? str_buf : (const unsigned char *)"Atmintuko rinkmenos nesugadintos", IDI_ASTERISK, KP_MB_BAIGTI);
         }
         retc = S_OK;

         break; // case CHKVOL_ID_PROCESS:
      }

      switch(HIWORD(wParam))
      {
      case LBN_SELCHANGE:
// ------------
         if(SUCCEEDED(retc))
         {
            cur_sel=SendMessage(ChkVolObj.m_hDevBox, CB_GETCURSEL, 0, 0);
            if(cur_sel==LB_ERR)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(((cur_sel<0) /* || (cur_sel>=????) */) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc)) retc = ChkVolObj.SetCurDev(cur_sel);

// KpMsgOut(m_lpszDev, IDI_ASTERISK, KP_MB_TESTI);

         break; // case LBN_SELCHANGE:
// ------------------

      default:
KP_TRACE("ChkVolDialogProc: WM_COMMAND");
         break;
      }

      break; // case WM_COMMAND:

   case WM_TIMER:
      if(SUCCEEDED(retc)) if(retp==ChkVolObj.m_iDevScanTimer) retc=ChkVolObj.UpdateDevList();
      break;

   case WM_CLOSE:
KP_TRACE("ChkVolDialogProc: WM_CLOSE");
      endfl=True;
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
      case IDABORT: retc = KP_E_CANCEL; break;
      case IDABORT:
KP_TRACE("ChkVolDialogProc: WM_QUIT: IDABORT");
         retc = KP_E_SYSTEM_ERROR;
         break;
      default:
KP_TRACE("ChkVolDialogProc: WM_QUIT");
         break;
      }
      endfl=True;
      break;

   default:
#ifdef Debug
char str_buf[100];
sprintf((char *)str_buf, "ChkVolDialogProc: %d", uMsg);
KP_TRACE(str_buf);

   case WM_NCMOUSEMOVE:
   case WM_NCHITTEST:
   case WM_SETCURSOR:
   case WM_NCPAINT:
   case WM_MOVE:
   case WM_WINDOWPOSCHANGING:
   case WM_NCACTIVATE:
   case WM_ACTIVATEAPP:
   case WM_SETFOCUS:
   case WM_ACTIVATE:
   case WM_GETMINMAXINFO:
   case WM_NCCREATE:
   case WM_NCCALCSIZE:
   case WM_PARENTNOTIFY:
   case WM_SIZE:
   case WM_SHOWWINDOW:
   case WM_QUERYDRAGICON:
   case WM_GETTEXT:
   case WM_ERASEBKGND:
   case WM_WINDOWPOSCHANGED:
   case WM_CTLCOLORLISTBOX:
   case WM_PAINT:
   case WM_KILLFOCUS:
   case WM_MOUSEMOVE:
   case WM_NCLBUTTONDOWN:

   case WM_SYSCOMMAND:
   case WM_DESTROY:
   case WM_NCDESTROY:
#endif
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// -----------------------------------------
ChkVol::ChkVol(void)
{

// m_lhOpenResult = S_OK;

   m_hDialogWindow = 0;
   m_hDevBox = 0;
   m_hProcBut = 0;

   m_bMakeList = False;

   m_iDevScanTimer = 0;

   m_iCurSel = 0;
   m_lpszDev[0] = Nul;
   m_iCurVolType = Vt_NoVol;
   m_lpszFName[0] = Nul;

   m_pDevList = NULL;
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = UpdateDevList();
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = SetCurDev(0);

// ------------------------
#ifdef Debug
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=KpTraceWindow.GetOpenResult();
#endif
}


ChkVol::~ChkVol(void)
{
   if(m_iDevScanTimer && m_hDialogWindow) if(!KillTimer(m_hDialogWindow, m_iDevScanTimer))
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   m_iDevScanTimer = 0;

   CloseWindow();
}


HRESULT ChkVol::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// ---------------------------------- open window
HRESULT ChkVol::OpenWindow(HINSTANCE hInst)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = "CHKVOL",
      wcx.lpfnWndProc   = (WNDPROC)ChkVolDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION);
      wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION);
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      m_hDialogWindow=CreateWindowEx
      (
         0L,        // DWORD dwExStyle,      // extended window style
         "CHKVOL",
         "Atmintuko tikrinimas", // "ChkVol", // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         CHKVOL_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
         CHKVOL_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
         CHKVOL_WND_DX, // int nWidth,           // window width
         CHKVOL_WND_DY, // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,       // HMENU hMenu,          // handle to menu, or child-window identifier
         hInst,
         NULL                    // LPVOID lpParam        // pointer to window-creation data
      );

      if(m_hDialogWindow==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }


   if(SUCCEEDED(retc)) ShowWindow(m_hDialogWindow, SW_SHOW);

   if(SUCCEEDED(retc))
   {
      m_iDevScanTimer = SetTimer(m_hDialogWindow, KP_POLL_TIMER, KP_POLL_TIMEOUT*4, NULL);
      if(!m_iDevScanTimer)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// ---------------------------------- close window
HRESULT ChkVol::CloseWindow(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

#ifdef Debug
   retc0=KpTraceWindow.DestroyWindow();
   if(SUCCEEDED(retc)) retc=retc0;
#endif

   if(m_hDevBox)
   {
      if(!DestroyWindow(m_hDevBox))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      m_hDevBox = 0;
   }

   if(m_hProcBut)
   {
      if(!DestroyWindow(m_hProcBut))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      m_hProcBut = 0;
   }


   if(m_hDialogWindow)
   {
      if(!DestroyWindow(m_hDialogWindow))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      m_hDialogWindow = 0;
   }

return(retc);
}


// ---------------------------------- dev list
HRESULT ChkVol::UpdateDevList(void)
{
HRESULT retc=S_OK;
int ii;
unsigned char drive_path[10];
static unsigned char list_entry[KP_MAX_FNAME_LEN + 100];
UINT drive_type;
KpTreeEntry *new_list = NULL;
int new_cnt = 0;
int cur_cnt = 0;
static unsigned char vol_name[KP_MAX_FNAME_LEN + 1];
TevAutorunPars vol_pars;

   strcpy(drive_path, "A:\\");

   for(ii='B' /* 'A'*/; (ii<='Z') && SUCCEEDED(retc); ii++)
   {
      drive_path[0]=ii;
      drive_type=GetDriveType((const char *)drive_path);
      if((drive_type==DRIVE_REMOVABLE) || (drive_type==DRIVE_CDROM)) // DRIVE_CDROM - cd8 formatuotiems atmintukams
      {
// --------------
         strcpy(list_entry, drive_path);
         list_entry[2] = Nul;

// --------------
         if(SUCCEEDED(retc)) if(GetVolumeInformation((const char *)drive_path, (char *)vol_name, KP_MAX_FNAME_LEN,
            NULL, NULL, NULL, NULL, 0))
         {
            strcat(list_entry, " ");
            strcat(list_entry, vol_name);
         }

// -----------------
         if(SUCCEEDED(retc))
         {
            retc = ParseTevAutorun(drive_path, &vol_pars);
            if(SUCCEEDED(retc)) if((vol_pars.m_iVolType < 0) || (vol_pars.m_iVolType >= VT_MaxVolType))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               strcat(list_entry, " [");
               strcat(list_entry, lpszaVolTypeKwds[vol_pars.m_iVolType]);
               strcat(list_entry, "]");
            }
         }

// -----------------
#if FALSE
         if(SUCCEEDED(retc)) switch(drive_type)
         {
         case DRIVE_REMOVABLE: strcat(list_entry, " [Removable]"); break;
         case DRIVE_CDROM: strcat(list_entry, " [CDROM]"); break;
         }
#endif

// ----------------
         if(SUCCEEDED(retc))
         {
            if(new_list == NULL)
            {
               KP_NEW(new_list, KpTreeEntry(list_entry, NULL));
            }
            else
               retc = new_list->PutToEnd(list_entry);
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      if(m_pDevList == NULL)
      {
         m_pDevList = new_list;
         new_list = NULL;
      }
      else
      {
         retc = new_list->CountEntries(&new_cnt, 0, NULL);
         if(SUCCEEDED(retc)) retc = m_pDevList->CountEntries(&cur_cnt, 0, NULL);
         if((new_cnt != cur_cnt) && SUCCEEDED(retc))
         {
            if(m_hDevBox == 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(!DestroyWindow(m_hDevBox))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               m_hDevBox = 0;
               KP_DELETE(m_pDevList);
               m_pDevList = new_list;
               new_list = NULL;
            }
            if(SUCCEEDED(retc)) retc = KpCreateComboBox(hKpInstance, m_hDialogWindow, &m_hDevBox,
               (const unsigned char *)"DevBox",
               CHKVOL_DEVBOX_DX, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]*CHKVOL_DEVBOX_NUM_OF_ENTRIES,
               CHKVOL_DEVBOX_X, CHKVOL_DEVBOX_Y,
               KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0L,
               m_pDevList, 0);

            if(SUCCEEDED(retc)) retc = SetCurDev(0);
         }
      }
   }

   KP_DELETE(new_list);

return(retc);
}


// ---------------------------------- set m_lpszDev currently selected device, m_pDevList should be allready initialized
HRESULT ChkVol::SetCurDev(int iCurSelection)
{
HRESULT retc=S_OK;
unsigned char *val_ptr;
int cur_sel = iCurSelection;
KpTreeEntry *list_entry_ptr = NULL;
unsigned char *pntd = NULL;
TevAutorunPars par_buf;

// ----------------------------------
   if((iCurSelection < 0) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) m_iCurSel = iCurSelection;

// ----------------------------------
   if((m_pDevList == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
      retc = m_pDevList->GetEntryPtr(&cur_sel, &list_entry_ptr, 0, NULL);
   if((list_entry_ptr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
   {
      val_ptr = (unsigned char *)list_entry_ptr->GetValue();
      if(val_ptr == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   m_lpszDev[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strncpy(m_lpszDev, val_ptr, KP_MAX_FNAME_LEN);
      m_lpszDev[KP_MAX_FNAME_LEN] = Nul;

      pntd = strchr(m_lpszDev, ':');
      if(pntd) *(pntd+1) = Nul;
   }

// ----------------------------------
   if(SUCCEEDED(retc)) retc = ParseTevAutorun(m_lpszDev, &par_buf);
   if(SUCCEEDED(retc))
   {
      m_iCurVolType = par_buf.m_iVolType;
      if((m_iCurVolType < 0) || (m_iCurVolType >= VT_MaxVolType))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszFName, lpszaVolTypeKwds[m_iCurVolType]);
      strcat(m_lpszFName, ".mcl");
   }

return(retc);
}


// ---------------------------------- enumerate files
HRESULT ChkVol::CompareFnamesSingleDir(const unsigned char *lpszDir, fstream *pMclFile)
{
HRESULT retc=S_OK;
unsigned char *enum_dir = NULL;
unsigned char *sub_dir = NULL;
WIN32_FIND_DATA file_enum_data;
HANDLE enum_handle = INVALID_HANDLE_VALUE;
DWORD retw;
int ll;
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
unsigned char *path;
unsigned char *name;
static unsigned char type[KP_MAX_FTYPE_LEN + 1];
static unsigned char test_str[KP_MAX_FNAME_LEN + 100 + 1];
static unsigned char in_str[KP_MAX_FNAME_LEN + 1];
static unsigned char str_buf[KP_MAX_FNAME_LEN + 300 + 1];


// ---------------------------
   if(((lpszDir == NULL) || (pMclFile == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszDir) >= KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(enum_dir, unsigned char, KP_MAX_FNAME_LEN + 100);

   KP_NEWA(sub_dir, unsigned char, KP_MAX_FNAME_LEN + 1);

   KP_NEWA(path, unsigned char, KP_MAX_FNAME_LEN + 1);

   KP_NEWA(name, unsigned char, KP_MAX_FNAME_LEN + 1);

// ---------------------------
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, lpszDir);
   if(SUCCEEDED(retc)) if(strcmp(path, ".") == 0) path[0] = Nul;

   if(SUCCEEDED(retc)) strcpy(enum_dir, lpszDir);

   if(SUCCEEDED(retc)) strcat(enum_dir, "\\*");


// --------------------------- start enumeration
   if(SUCCEEDED(retc))
   {
      enum_handle = FindFirstFile((const char *)enum_dir, &file_enum_data);
      if(enum_handle == INVALID_HANDLE_VALUE)
      {
         retc = KP_E_FILE_NOT_FOUND;
         retw = GetLastError();
         if(retw == ERROR_NOT_READY) KpMsgOut("Árenginyje nëra laikmenos", IDI_ERROR, KP_MB_BAIGTI);
         else retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, retw, True, __FILE__, __LINE__, 0L);
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, enum_dir, True, __FILE__, __LINE__, 0L);
      }
   }


// --------------------------- loop through files
   while(SUCCEEDED(retc))
   {

// KpMsgOut(file_enum_data.cFileName, IDI_ASTERISK, KP_MB_TESTI);


      if(SUCCEEDED(retc)) if((strcmp(file_enum_data.cFileName, ".") != 0) && (strcmp(file_enum_data.cFileName, "..") != 0))
      {
         ll = strlen(name);
         if(m_bMakeList)
         {
// --------------------------- write record
//          *pMclFile << lpszDir << "\t";
            *pMclFile << path << "\\";
            if(ll) *pMclFile << name << "\\";
            *pMclFile << file_enum_data.cFileName << " | ";
            if(file_enum_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) *pMclFile << -1;
            else *pMclFile << file_enum_data.nFileSizeLow;
            *pMclFile << endl;
            if(pMclFile->fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
         }
         else // if(m_bMakeList)
         {
// --------------------------- check entry
            strcpy(test_str, path);
            strcat(test_str, "\\");
            if(ll)
            {
               if(strlen(test_str) + ll + 1 >= KP_MAX_FNAME_LEN + 100)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  strcat(test_str, name);
                  strcat(test_str, "\\");
               }
            }
            if(SUCCEEDED(retc))
               if(strlen(test_str) + strlen(file_enum_data.cFileName) + 3 + MAX_LONG_DIGITS >= KP_MAX_FNAME_LEN + 100)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               strcat(test_str, file_enum_data.cFileName);
               if(file_enum_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ll = -1L;
               else ll = file_enum_data.nFileSizeLow;
               sprintf((char *)test_str + strlen(test_str), " | %ld", ll);
            }

// -----------------
            if(SUCCEEDED(retc))
            {
               pMclFile->getline((char *)in_str, KP_MAX_FNAME_LEN);
               in_str[KP_MAX_FNAME_LEN] = Nul;
               if(pMclFile->fail())
               {
                  if(pMclFile->eof())
                  {
                     strcpy(str_buf, "Atmintuke atsirado rinkmena ");
                     strcat(str_buf, test_str);
                     KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
                     retc = KP_E_FILE_NOT_FOUND;
                  }
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
               }
            }

// -----------------
            if(SUCCEEDED(retc))
               if(TvStrCmp(test_str, in_str, False, KP_LNG_LIT, False, 99, False) != 0)
                  if(TvStrCmp((const unsigned char *)file_enum_data.cFileName, (const unsigned char *)"fl.dat", False, KP_LNG_LIT, False, 99, False) != 0)
                  {
                     strcpy(str_buf, "Sugadinta atmintuko rinkmena ");
                     strcat(str_buf, test_str);
strcat(str_buf, " - ");
strcat(str_buf, in_str);
                     KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
                     retc = KP_E_FILE_NOT_FOUND;
                  }

         } // else // if(m_bMakeList)


// -------------------------- recursion on directories
         if((file_enum_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && SUCCEEDED(retc))
         {
            if(strlen(lpszDir) + strlen(file_enum_data.cFileName) + 2 >= KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               strcpy(sub_dir, lpszDir);
               strcat(sub_dir, "\\");
               strcat(sub_dir, file_enum_data.cFileName);

               retc = CompareFnamesSingleDir(sub_dir, pMclFile);
            }

         } // if((file_enum_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && SUCCEEDED(retc))

      } // if(SUCCEEDED(retc)) if((strcmp(file_enum_data.cFileName, ".") != 0) && (strcmp(file_enum_data.cFileName, "..") != 0))


// ------------------------- next file
      if(SUCCEEDED(retc)) if(!FindNextFile(enum_handle, &file_enum_data))
      {
         retw = GetLastError();
         if(retw == ERROR_NO_MORE_FILES) retc = KP_E_EOF;
         else retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, retw, True, __FILE__, __LINE__, 0L);
      }

   } // while(SUCCEEDED(retc))

// ---------------------------
   if(retc == KP_E_EOF) retc = S_OK;

// char str_buf[100];
// sprintf(str_buf, "%d", retw);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

// ---------------------------
   KP_DELETEA(name);
   KP_DELETEA(path);
   KP_DELETEA(sub_dir);
   KP_DELETEA(enum_dir);

return(retc);
}


// ---------------------------------- enumerate files
HRESULT ChkVol::CompareFnames(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
fstream mcl_file;
unsigned char *size_ptr = NULL;
unsigned char *time_ptr = NULL;
static unsigned char in_str[KP_MAX_FNAME_LEN + 1];
static unsigned char str_buf[KP_MAX_FNAME_LEN + 300 + 1];

// ---------------------------------- open file
   if(SUCCEEDED(retc))
   {
      mcl_file.open((const char *)m_lpszFName, m_bMakeList? ios_base::out : ios_base::in);
      if(mcl_file.fail())
      {
unsigned char str_buf[200];
         retc = KP_E_FILE_NOT_FOUND;
         strcpy(str_buf, "Neatpaþintas laikmenos tipas ");
         if((m_iCurVolType >= 0) && (m_iCurVolType < VT_MaxVolType))
            strcat(str_buf, lpszaVolTypeKwds[m_iCurVolType]);
         KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
//       retc = KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {

// ---------------------------------- enumerate files
         if(SUCCEEDED(retc)) retc = CompareFnamesSingleDir(m_lpszDev, &mcl_file);

// ---------------------------------- more files in the list?
         if(!m_bMakeList && SUCCEEDED(retc))
         {
            mcl_file.getline((char *)in_str, KP_MAX_FNAME_LEN);
            in_str[KP_MAX_FNAME_LEN] = Nul;
            if(!mcl_file.fail())
            {
               strcpy(str_buf, "Sugadinta atmintuko rinkmena ");
               strcat(str_buf, in_str);
               KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
               retc = KP_E_FILE_NOT_FOUND;
            }
         }

// --------------------------- close file
         mcl_file.close();
         if(m_bMakeList && mcl_file.fail())
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc = retc0;
         }

// ---------------------------

      } // else // if(mcl_file.fail()) // KP_E_FILE_NOT_FOUND

   } // if(SUCCEEDED(retc))

return(retc);
}



// ----------------------------------
HRESULT ChkVol::CompareFile(const unsigned char *lpszFileName, bool bRequirePresence)
{
HRESULT retc=S_OK;
fstream local_file;
fstream flash_file;
unsigned char local_byte;
unsigned char flash_byte;
unsigned char flash_fname[KP_MAX_FNAME_LEN + 1];
unsigned char str_buf[200];

   if((lpszFileName == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      local_file.open((const char *)lpszFileName, ios_base::in | ios_base::binary);
      if(local_file.fail())
      {
         retc = KP_E_FILE_NOT_FOUND;
         if(bRequirePresence) retc = KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         if(SUCCEEDED(retc))
            if(strlen(m_lpszDev) + strlen(lpszFileName) + 1 >= KP_MAX_FNAME_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            strcpy(flash_fname, m_lpszDev);
            strcat(flash_fname, "\\");
            strcat(flash_fname, lpszFileName);

            flash_file.open((const char *)flash_fname, ios_base::in | ios_base::binary);
            if(flash_file.fail())
            {
               retc = KP_E_FILE_NOT_FOUND;
               if(bRequirePresence) retc = KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);
            }
            else
            {
               while((!local_file.eof()) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc))
                  {
                     local_file.read((char *)&local_byte, 1);
                     if(!local_file.eof())
                        if(local_file.fail())
                           retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc))
                  {
                     flash_file.read((char *)&flash_byte, 1);
                     if(!local_file.eof())
                        if(flash_file.fail())
                        {
                           if(flash_file.eof())
                           {
                              retc = KP_E_FERROR;
                              strcpy(str_buf, "Sugadinta rinkmena ");
                              strcat(str_buf, lpszFileName);
                              KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
//                            retc = KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);
                           }
                           else
                              retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszFName, True, __FILE__, __LINE__, 0L);
                        }
                  }
                  if((!local_file.eof()) && SUCCEEDED(retc))
                     if(local_byte != flash_byte)
                     {
                        retc = KP_E_FERROR;
                        strcpy(str_buf, "Sugadinta rinkmena ");
                        strcat(str_buf, lpszFileName);
                        KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
//                      retc = KpErrorProc.OutputErrorMessage(retc, m_lpszFName, True, __FILE__, __LINE__, 0L);
                     }
               }

               if(SUCCEEDED(retc)) if(!flash_file.eof())
               {
                  retc = KP_E_FERROR;
                  strcpy(str_buf, "Sugadinta rinkmena ");
                  strcat(str_buf, lpszFileName);
                  KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
               }

               flash_file.close();

            } // else // if(flash_file.fail())

         } // if(SUCCEEDED(retc))

         local_file.close();

      } // else // if(local_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ----------------------------------
HRESULT ChkVol::DoEdit(void)
{
HRESULT retc=S_OK;
MSG msg;
int retp;
bool endfl=False;

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp=LOWORD(msg.wParam);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
KP_TRACE("WM_QUIT");
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
KP_TRACE("WM_CLOSE");
         endfl=True;
         break;

      case WM_COMMAND:
KP_TRACE("WM_COMMAND");
         switch(retp)
         {
         case IDOK:
            break;
         case IDCANCEL:
            if(msg.hwnd==m_hDialogWindow) endfl=True;
            break;
         } // switch(retp)
         break;

#ifdef Debug
      case WM_SETFONT:
      case 10001:
      case WM_SIZE:
      case WM_SYSKEYDOWN:
      case WM_SYSKEYUP:
      case WM_KEYUP:
      case WM_NCLBUTTONDOWN:
      case WM_PAINT:
      case WM_TIMER:
      case WM_MOUSEMOVE:
      case WM_NCMOUSEMOVE:
         break;

      default:
char str_buf[100];
sprintf((char *)str_buf, "DoEdit: %d", msg.message);
KP_TRACE(str_buf);
         break;
#endif

      } // switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));

return(retc);
}


// --------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
static unsigned char exe_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char name[KP_MAX_FNAME_LEN + 1];
static unsigned char type[KP_MAX_FTYPE_LEN + 1];
// static unsigned char vol_path[KP_MAX_FNAME_LEN+1];
// OPENFILENAME op_fn_str;
// unsigned char filters[100];
// unsigned char *pntd;
// static unsigned char cur_dir[KP_MAX_FNAME_LEN+1];
// const unsigned char *pnts;


// -------------------------------
   if(SUCCEEDED(retc)) retc = ChkVolObj.InitCommonApp(hInstance, lpCmdLine);
   if(SUCCEEDED(retc)) retc = ChkVolObj.GetOpenResult();

// ------------------------------- action
   if(SUCCEEDED(retc)) retc=GetAppName(exe_fname);
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, exe_fname);
   if(SUCCEEDED(retc)) TvStrLwrLat(name);
   if(SUCCEEDED(retc)) ChkVolObj.m_bMakeList = (strcmp(name, CHKVOL_MAKE_LIST_CMD) == 0);

// ChkVolObj.m_bMakeList = True;


// ------------------------------- open window
   if(SUCCEEDED(retc)) retc = ChkVolObj.OpenWindow(hInstance);


// ------------------------------- open window
   if(SUCCEEDED(retc)) retc = ChkVolObj.DoEdit();


#if FALSE
// ------------------------------- remember current directory
   if(SUCCEEDED(retc)) if(!GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir))
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
   cur_dir[KP_MAX_FNAME_LEN] = Nul;


// ------------------------------- choose disk
   if(SUCCEEDED(retc))
   {
      vol_path[0]=Nul;
   }

   if(SUCCEEDED(retc))
   {
      op_fn_str.lStructSize=sizeof(op_fn_str);
      op_fn_str.hwndOwner=HWND_DESKTOP;
      op_fn_str.hInstance=hInstance;

      strcpy(filters, "Atmintukai");
      pntd=filters+strlen(filters)+1;
      strcpy(pntd, CHKVOL_FLASH_FILE_FILTER);
      pntd+=strlen(pntd)+1;
      *(pntd++)=Nul;
      *(pntd++)=Nul;
      op_fn_str.lpstrFilter=(const char *)filters;

      op_fn_str.lpstrCustomFilter=NULL;
      op_fn_str.nMaxCustFilter=0;
      op_fn_str.nFilterIndex=1;
      op_fn_str.lpstrFile=(char *)vol_path;
      op_fn_str.nMaxFile=KP_MAX_FNAME_LEN;
      op_fn_str.lpstrFileTitle=NULL;
      op_fn_str.nMaxFileTitle=0;

      op_fn_str.lpstrInitialDir=NULL; // "\\"; // ".\\";

      op_fn_str.lpstrTitle="Pasirinkite kurá nors failà tkrinamame atmintuke";
      op_fn_str.Flags=0;

      op_fn_str.nFileOffset=0; // (WORD)strlen(op_fn_str.lpstrInitialDir);

      pnts=(const unsigned char *)strchr(op_fn_str.lpstrFile, '.');
      if(pnts!=NULL) op_fn_str.nFileExtension=pnts-(const unsigned char *)op_fn_str.lpstrFile+1;
      else op_fn_str.nFileExtension=(int)strlen(op_fn_str.lpstrFile);

      op_fn_str.lpstrDefExt=(const char *)CHKVOL_FLASH_FILE_FILTER+2; // "*";
      op_fn_str.lCustData=NULL;
      op_fn_str.lpfnHook=NULL;
      op_fn_str.lpTemplateName=NULL;


      if(!GetOpenFileName(&op_fn_str))
      {
         retc=KP_E_CANCEL;
//       retc=KpErrorProc.OutputErrorMessage(retc, CommDlgExtendedError(), True, __FILE__, __LINE__, 0L);
      }
   }


// ------------------------------- restore current directory
   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((const char *)cur_dir))
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);


// ---------------------------------- disk letter
   if(SUCCEEDED(retc)) retc = TvFnameSplit(ChkVolObj.m_lpszDev, path, name, type, vol_path);
#endif

// KpMsgOut(disk, IDI_ASTERISK, KP_MB_TESTI);

#if FALSE
// ---------------------------------- process
   if(SUCCEEDED(retc)) retc = ChkVolObj.CompareFnames();


// ----------------------------------
   if(SUCCEEDED(retc))
   {
unsigned char str_buf[200];
      strcpy(str_buf, "Atmintuko rinkmenø sàraðas ");
      strcat(str_buf, m_lpszFName);
      strcat(str_buf, " sukurtas");
      KpMsgOut(ChkVolObj.m_bMakeList? str_buf : "Atmintuko rinkmenos nesugadintos", IDI_ASTERISK, KP_MB_BAIGTI);
   }
#endif

// ------------------------------- close window
   if(SUCCEEDED(retc)) retc = ChkVolObj.CloseWindow();


return(RET_CODE_WIN(retc));
}
