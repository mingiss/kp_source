// ===================================================
// chkvol.h
// disko failu atitikimo sarasui tikrinimas
//

#ifndef chkvol_included
#define chkvol_included


// ------------------------------------
#define CHKVOL_MAKE_LIST_CMD ((const unsigned char *)"chkvol_make_list")
#define CHKVOL_PART_FNAME ((const unsigned char *)"part1i.bin")
#define CHKVOL_FLASH_FILE_FILTER "*.*"
// #define CHK_VOL_FNAME "chkvol.mcl"

#define CHKVOL_WND_MARGIN  (KPW_WND_MARGIN*2)
#define CHKVOL_CTRL_MARGIN KPW_WND_MARGIN

#define CHKVOL_TITLE_X     35
#define CHKVOL_TITLE_Y     CHKVOL_WND_MARGIN

#define CHKVOL_CTRL_X      50

#define CHKVOL_PROMPT_X    CHKVOL_TITLE_X
#define CHKVOL_PROMPT_Y    (CHKVOL_WND_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_HEADING_3] + (CHKVOL_CTRL_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) * 1)

#define CHKVOL_DEVBOX_X    CHKVOL_CTRL_X
#define CHKVOL_DEVBOX_Y    (CHKVOL_WND_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_HEADING_3] + (CHKVOL_CTRL_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) * 2)
#define CHKVOL_DEVBOX_DX   220
#define CHKVOL_DEVBOX_NUM_OF_ENTRIES 5

#define CHKVOL_PROCBUT_X   ((CHKVOL_WND_DX - iWndBorderWdt - KPW_BUTTON_WDT)/2)
#define CHKVOL_PROCBUT_Y   (CHKVOL_WND_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_HEADING_3] + (CHKVOL_CTRL_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) * 4)
#define CHKVOL_ID_PROCESS  131

#define CHKVOL_WND_X 200
#define CHKVOL_WND_Y 200
#define CHKVOL_WND_DX 320
#define CHKVOL_WND_DY      (iWndCaptionHgt + \
                           (CHKVOL_WND_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_HEADING_3] + (CHKVOL_CTRL_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) * 5) + \
                           CHKVOL_WND_MARGIN)

class ChkVol: public KpCommonApp
{
   HWND m_hDialogWindow;

public:
   HWND m_hDevBox;
   KpTreeEntry *m_pDevList;

   HWND m_hProcBut;

   bool m_bMakeList;

   int m_iCurSel;
/* static */ unsigned char m_lpszDev[KP_MAX_FNAME_LEN+1]; // currently selected device without slash "C:" // former m_lpszDir[], disk[]
   TvVolTypes m_iCurVolType;
   unsigned char m_lpszFName[KP_MAX_FNAME_LEN+1]; // current .mcl file name

   int m_iDevScanTimer;

private:

   HRESULT CompareFnamesSingleDir(const unsigned char *lpszDir, fstream *pMclFile);
      // lpszDir - apdorojamo pakatalogio kelias be slasho gale
      // recursive subroutine of CompareFnames()

public:
   ChkVol(void);
   ~ChkVol(void);
   HRESULT GetOpenResult(void);

   HRESULT OpenWindow(HINSTANCE hInst);
   HRESULT CloseWindow(void);

   HRESULT UpdateDevList(void);
   HRESULT SetCurDev(int iCurSelection); // former ResetCurDev(void);
      // set m_lpszDev
      // iCurSelection - position in m_pDevList
      // m_pDevList should be allready initialized

   HRESULT CompareFnames(void); // former Process(unsigned char *lpszDir);
      // in: m_lpszDev - disko raide su dvitaskiu be slasho

   HRESULT CompareFile(const unsigned char *lpszFileName, bool bRequirePresence);
      // lygina failo turini: lokalaus lpszFileName ir m_lpszDev\lpszFileName
      // bRequirePresence == True - isveda klaidos pranesima, jei failo neranda
      // bRequirePresence == False - pranesimo nera, tik klaidos kodas

   HRESULT DoEdit(void);
};

#endif
