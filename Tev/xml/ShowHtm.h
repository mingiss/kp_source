// ---------------------------------------
// ShowHtm.h
// bandymas daryti StartGrp meniu (o gal ir KpWindow Splash Bmp), dabar naudojam bendrà iBshl
// apibrëþimai
//

#ifndef ShowHtm_included
#define ShowHtm_included

// ------------------------------------------------
// atidaro 800x600 langà ekrano centre ir parodo lpszHtmFName per xGecko
// tipo atsklandà (.htm su nuoroda á .jar ar Flash failà)
// TODO: reiktø kaþkaip apjungt su iBsht
#define KP_SHOWXGECKO_DX 800
#define KP_SHOWXGECKO_DY 600

class ShowHtmFile: public KpFileSys
{
   unsigned char m_lpszFName[KP_MAX_FNAME_LEN + 1];
   FILE *m_lpInFileObj;

public:
   ShowHtmFile(const unsigned char *lpszInFileName, int iInitCtrlDX, int iInitCtrlDY);
   ~ShowHtmFile(void);

   virtual HRESULT OpenFiles
   (
      const unsigned char *lpszInFileName = null,
      XmlVersions iVersion = XM_VERS_HTML401_TRANS,
      HRESULT CreateLowLevelObj
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNew8File
   );
   virtual HRESULT CloseFiles(bool bCheckFileExist);
   virtual HRESULT SearchForEntry(void);
};

#define pShowHtmFile ((ShowHtmFile *)KpFileSysPtr)

extern HRESULT ShowHtmXGecko(const unsigned char *lpszHtmFName, // KpGeckoDialog **ppDlgPtr,
   HWND hParent = HWND_DESKTOP, int iGeckoX = 0, int iGeckoY = 0,
   int iGeckoDX = KP_SHOWXGECKO_DX, int iGeckoDY = KP_SHOWXGECKO_DY,
   const unsigned char *lpszWndName = (const unsigned char *)"",
   LPSTR lpszIcon = MAKEINTRESOURCE(KP_IDI_START_ICON) /* IDI_APPLICATION */);

extern BOOL CALLBACK ShowHtmXGeckoDialogProc(
   HWND hwndDlg,  // handle to dialog box
   UINT uMsg,     // message
   WPARAM wParam, // first message parameter
   LPARAM lParam  // second message parameter
   );

#endif // #ifndef ShowHtm_included
