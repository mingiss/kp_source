/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11w.cpp, former kphp11e.cpp                          */
/* DESCRIPTION:      Kphp11: Emuliatoriaus langas                             */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      MSWindows                                                */
/* SYSTEM_INTERFACE: MSWindows                                                */
/* USER_INTERFACE:   Graph                                                    */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

/*---------------------------------------------------- gen */
#define Lang 7 /* Cpp */
#define KpInc

#include "kpxe.h"
#include "kphp11e.h"
#include "resource.h"


/*---------------------------------------------------- var */
EmuWt EmuWv;
WndP  EmuWp((WndC *)&EmuWv);

/* ----------------------------------------- konstruktorius */
EmuWt::EmuWt()
  : WndT()
{
/*  einit(); */
}


/* ------------------------------------------ destruktorius */
EmuWt::~EmuWt()
//  : ~WndT()
{
}


LRESULT CALLBACK ewndproc(/* WndC */ cvoid *wndcpnt, UINT message, WPARAM wParam, LPARAM lParam)
{    
EmuWt *epnt;
int ii;

  epnt = (EmuWt *)wndcpnt;
  
  switch(message)
  {
//    case WM_CHAR:
//      epnt->wkbtobuf(wParam);
//      break;

//    case WM_MENUSELECT:
    case WM_COMMAND:
      switch(wParam)
      {
        case ID_FILE_LOADMEMORY:
          epnt->wputstr("Load memory\n");
          break;
        case ID_COMMANDS_RUN:
          epnt->wputstr("Run\n");
          break;
        case ID_ACCEL40003:
          epnt->wputstr("Load memory (accelerator)\n");
          break;
        default:
          return(DefWindowProc(epnt->hwOutWin,message,wParam,lParam));
          break;
      }
      break;

    default:
      return(DefWindowProc(epnt->hwOutWin,message,wParam,lParam));
      break;
  }

return (False);
}


BOOL CALLBACK d1_proc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
    case WM_PAINT:
//      UpdateWindow(EmuWv.hwOutWin);
      break;
  }
return(False);
}


/*--------------------------------------------------- init */
void EmuWt::einit(void)
{
HWND d1_hWnd;
LPCSTR lpsz_d1;
DLGPROC dlgpr;
int d1_hgt;
// WNDCLASS d1_wc;

  d1_hgt = (int) (D1_HGT * (GetDialogBaseUnits() >> BitsInWord) / BaseFactY);
  wInitEasyWin("kphp11", IDR_MENU1, d1_hgt, "Kphp11");

  lpsz_d1 = MAKEINTRESOURCE(IDD_DIALOG1);
  dlgpr = MakeProcInstance((FARPROC)d1_proc, hIns_tance); /* FreeProcInstance naudoti iseinant!!! */
  d1_hWnd = CreateDialog(hIns_tance, lpsz_d1, EmuWv.hwOutWin, dlgpr);

//  d1_hgt = 0;
//  if(GetClassInfo(hIns_tance, lpsz_d1, &d1_wc)) d1_hgt = d1_wc.??
// !!! - pries CreateDialog()
//  wInitEasyWin("kphp11", IDR_MENU1, d1_hgt, "Kphp11");

  if(d1_hWnd)
    {
    ShowWindow(d1_hWnd,SW_NORMAL);
    UpdateWindow(d1_hWnd);
    }

  wndsubproc = ewndproc;
  wbcolor(Green,Black,Black);
  wcrsor(True);
}
