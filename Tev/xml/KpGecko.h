// ---------------------------------------
// KpGecko.h
// dialogas su tux_gecko langu
// apibrëşimai
//

#ifndef KpGecko_included
#define KpGecko_included

#ifndef iBshn_included
#error iBshn.h not included
#endif

#if CompilerGr == Mingw

// #define TEST_GECKO_OVERLAPPED_WINDOW

// -----------------------------
// TODO: iğkelti á lpszaStartSelKwds

#if KP_XGECKO_VER == 124 // "1.2.4"
#define KPGECKO_TUX_PROC_URL ((const unsigned char *)"tux:proc")
#define KPGECKO_TUX_EXIT_URL ((const unsigned char *)"tux:exit")
#endif

#if KP_XGECKO_VER == 130 // "1.3.0"
#define KPGECKO_TUX_PROC_URL ((const unsigned char *)"tux:///proc")
#define KPGECKO_TUX_EXIT_URL ((const unsigned char *)"tux:///exit")
#endif


// -----------------------------
#if KP_XGECKO_VER == 124 // "1.2.4"
// #if LZDSH_OUT_VERS == XML_VERS_HTML_TAGE // XML_VERS_HTML401_TRANS
#define KPGECKO_TUX_ENTRY_FILE_NAME_HTML ((const unsigned char *)"tux:entry.html") // former LZDSH_TUX_ENTRY_FILE_NAME
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_HTML (L"tux:entry.html") // former LZDSH_TUX_ENTRY_FILE_NAME_WIDE
// #endif
// #if LZDSH_OUT_VERS == XML_VERS_XHTML_TAGE // XML_VERS_XHTML
#define KPGECKO_TUX_ENTRY_FILE_NAME_XHTML ((const unsigned char *)"tux:entry.xhtml") // former LZDSH_TUX_ENTRY_FILE_NAME
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XHTML (L"tux:entry.xhtml") // former LZDSH_TUX_ENTRY_FILE_NAME_WIDE
// #endif
// #if LZDSH_OUT_VERS == XML_VERS_XML10
#define KPGECKO_TUX_ENTRY_FILE_NAME_XML ((const unsigned char *)"tux:entry.xml") // former LZDSH_TUX_ENTRY_FILE_NAME
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XML (L"tux:entry.xml") // former LZDSH_TUX_ENTRY_FILE_NAME_WIDE
// #endif
#endif

#if KP_XGECKO_VER == 130 // "1.3.0"
#define KPGECKO_TUX_ENTRY_FILE_NAME_HTML ((const unsigned char *)"tux:///entry.html")
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_HTML (L"tux:///entry.html")
#define KPGECKO_TUX_ENTRY_FILE_NAME_XHTML ((const unsigned char *)"tux:///entry.xhtml")
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XHTML (L"tux:///entry.xhtml")
#define KPGECKO_TUX_ENTRY_FILE_NAME_XML ((const unsigned char *)"tux:///entry.xml")
#define KPGECKO_TUX_ENTRY_FILE_NAME_WIDE_XML (L"tux:///entry.xml")
#endif

// dar kai kas faile tvxml.h

// -----------------------------
struct XKpGeckoStream : IInputStream // former XLzdshtStream, XLzdshlStream
{
// Atidaromas vienas iğ failø, ieğkoti, kuris ne NULL
   FILE *m_file;
   XmlO1 *m_XmlO1_file;
   unsigned char *m_lpszFileBuf; // darbinis RAM failo buferis, destruktoriuj reikia sunaikint
         
   unsigned char m_lpszURI[KP_MAX_FNAME_LEN+1];
   bool m_bInline;
   long m_lResultPtr; // former m_iResultPtr 
                      // einamojo baito numeris per XKpGeckoStream skaitomame m_lpszResultFormatted[], m_lpszFileBuf[] (jei m_lpszFileBuf != null) arba m_lpszURI[] (jei m_bInline) masyve 
                      // (baito numeris, ne masyvo elemento)
   long m_lBufSize; // m_lpszFileBuf[] ilgis buferinio streamo atveju

   XKpGeckoStream(FILE *a_file, const unsigned char *lpszURI, bool bInline = False); // jei bInline == True, siunèiami duomenys nurodyti tiesiai buferyje lpszURI[KP_MAX_FNAME_LEN + 1]
   XKpGeckoStream(XmlO1 *XmlO1_file, const unsigned char *lpszURI, unsigned char *lpszFileBuf = null); // lpszFileBuf – darbinis RAM failo buferis, destruktoriuj reikia sunaikint
   XKpGeckoStream(unsigned char *lpszFileBuf, const unsigned char *lpszURI, long lFileBufSize); // streamo atidarymas iğ buferio atminty, lpszFileBuf – buferio adresas, destruktoriuj reikia sunaikint
   ~XKpGeckoStream(void);

  // Skaitymo metodas, privalomas
  // Srauto pabaigos atveju reiketu grazinti 0,
  // fread() tai daro automatiskai
   int read(char *a_buffer, int size);
};


// -----------------------------
// Gecko komponentas
class XKpGecko // former XLzdshlGecko
   : public XGecko
{
// I cia ateis visi paspaudimo ivykiai
// Visas tekstas eina kaip unikodas

// Eventas ir jo turinys bus istrinti sitam metodui pasibaigus
// Norint issaugoti kuri nors STRINGa jo nekopijuojant, reiktu daryti kazka tokio:
// wchar_t *stringas = event->attributes[n];  << paimam pointerio kopija
// event->attributes[n] = 0;                  << pasalinam pointeri is masyvo
// ... panaudojam stringa ...
// delete [] stringas;                        << kai stringas nereikalingass, ji istrinam
// Jei ivyki apdorojome, graziname 1
// Priesingu atveju - 0
   long onDOMEvent(XGeckoDOMEvent *event); // pelës paspaudimø apdorojimas, turi bûti apibrëştas aplikacijos lygmenyje
};


// -----------------------------
class KpGeckoDialog : public KpPubDlg
{
private:
   XGeckoInit *m_pGeckoInit;

public:
   KpGeckoDialog(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers = IBSH_OUT_VERS, UC_Modes iEncMode = UC_PlainText,
      const unsigned char *lpszCaption = IBSH_WND_CAPTION,
      int iWndDXmin = IBSH_DEF_WND_MIN_DX, int iWndDXmax = IBSH_DEF_WND_MAX_DX, int iWndDYmin = IBSH_DEF_WND_MIN_DY, int iWndDYmax = IBSH_DEF_WND_MAX_DY,
      int iWndSoftBorderWdt = IBSH_WND_SOFT_BORDER_WDT, int iWndSoftCaptHgt = IBSH_WND_SOFT_CAPTION_HGT, int iWndHardBorderWdt = IBSH_WND_BORDER_WDT, int iWndHardCaptHgt = IBSH_WND_CAPTION_HGT,
      int iScrX = IBSH_DEF_SRC_X, int iScrY = IBSH_DEF_SRC_Y, int iScrDX = IBSH_DEF_SRC_DX, int iScrDY = IBSH_DEF_SRC_DY,
      int iResDXenl = IBSH_RES_DX_ENL, int iResDYenl = IBSH_RES_DY_ENL,
      DWORD dwStyle = IBSH_WND_STYLE, int iInitWndX = IBSH_DEF_WND_X, int iInitWndY = IBSH_DEF_WND_Y, int iInitWndDX = IBSH_DEF_WND_DX, int iInitWndDY = IBSH_DEF_WND_DY);
   virtual ~KpGeckoDialog();

   virtual HRESULT InitGecko(void); // konstruktoriaus tæsinys, iğkvieèiamas tam threade, kuriame po to bus rodomas vaizdas
   virtual HRESULT CreateResCtrl(int iXpos, int iYpos, int iWdt, int iHgt, HWND hParent); // sukuria m_ResCtrl
   virtual HRESULT OpenWindowLocal(void); // former CompleteOpenWindow()

   virtual void FinitGecko(void); // destruktoriaus pradşia, iğkvieèiama tam threade, kuriame buvo iğkviestas InitGecko()

   virtual HRESULT RedrawWindowLocal(void);

   virtual HRESULT DisplayResult(void);   // paleidşia failo krovimà á m_ResCtrl // former Load()
                                          // isijungia m_bSemBlocked semafora
                                          // iğkvieèia DisplayResultCommon()
};

// -----------------------------
extern KpGeckoDialog *KpGeckoDialogPtr; // reikia dël KpGeckoStreamFactory(), neiğeina padaryt nestatiğkai – reiğkia tik vienas KpGecko per aplikacijà

extern IInputStream *KpGeckoStreamFactory(const char *a_URL); // former LzdshtStreamFactory

// -----------------------------
// Clipboard'o filtras
// apibrëşti aplikacijos lygmenyje
// Grazinamos reiksmes:
// XGecko::CLIPBOARD_ALLOW  - leisti kopijavimo operacija
// XGecko::CLIPBOARD_MODIFY - leisti kopijavimo operacija, nurodant nauja clipboard teksta
// XGecko::CLIPBOARD_DENY   - neleisti operacijos

// IString yra interfeisas, uz kurio slepiasi XGeckoString, kuris yra
// mozillos stringo nsEmbedString wrapperis. Tokiu budu nereikia daryti papildomu
// stringo kopiju. IString metodai:
// getData()    - gauti unikodini stringa
// length()     - gauti stringo ilgi
// setData()    - nustatyti stringa
extern int clipboardFilter(IString *dst, const IString *src);

#endif // #if CompilerGr == Mingw

#endif // #ifndef KpGecko_included
