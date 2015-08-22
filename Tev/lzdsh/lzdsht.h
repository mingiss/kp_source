// -----------------------------------------
// lzdsht.h
// zodyno perziuros programa
// paieskos thread'as
//

#ifndef lzdsht_included
#define lzdsht_included


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef lzdshn_included
#error lzdshn.h not included
#endif

#ifndef lzdsh_included
#error lzdsh.h not included
#endif

// -----------------------------
#define LZDSH_POLL_TIMEOUT 200 // KP_POLL_TIMEOUT
#define LZDSH_REACT_TIMEOUT 1000 // reagavimo á paþymëtà tekstà taimeris
#define LZDSH_TIME_TO_HIST 2000

// #define LZDSH_STY_LINE_SPACING_CMD XML_STY_LINE_SPACING_CMD
#define LZDSH_STY_LINE_SPACING_SMALL_CMD "\\sl-280" // "\\sl-260" //
#define LZDSH_STY_LINE_SPACING_BIG_CMD "\\sl-330"

// --------------- KpFileSys::m_iToHistListFlags reikðmës
#define LZDSH_HIST_NONE          0  // apie m_HistList pildymà þiniø nëra, kol kas nepildom

#define LZDSH_HIST_DEPENDENT     1  // á m_HistList tik jei m_CurList != m_HistList
#define LZDSH_HIST_INDEPENDENT   2  // á m_HistList besàlygiðkai (net jei ir m_CurList==m_HistList)

#define LZDSH_HIST_TIMER         4  // á m_HistList po 2 sec.
#define LZDSH_HIST_IMMEDIATELY   8  // á m_HistList ið karto

#define LZDSH_HIST_FORCED_NONE  16  // m_HistList nepildomas; naudojamas spaudinëjant mygtukus LZDSH_ID_BACK/LZDSH_ID_FORWARD
// -----------------------------
extern const unsigned char lpszLzdshParStySmall[];
extern const unsigned char lpszLzdshParStyBig[];

#ifdef LZDSH_RES_CODING_UTF8
#define LzdshtResLen strlen
#else
#define LzdshtResLen wcslen
#endif

// -----------------------------
class LzdShSearch: public KpFileSys
{
public:
#ifdef LZDSH_EDITOR_BUILD
#  ifdef Debug
// volatile unsigned char m_lpszTestRtfText[LZDSHT_RESULT_BUF_LEN+1]; // former m_lpszRtfTestResultRtfText
#  endif
#endif

#ifdef LZDSH_EDITOR_BUILD
#  ifdef Debug
// volatile TvRtfO_tag *m_lpRtfTestOutFileObj;
#  endif

   volatile XmlNode *m_pCurNode;   // entry node currently viewed in LzdShDlg::m_TagList, subnode of m_pCurEntry
#endif

public:
#ifdef LZDSH_EDITOR_BUILD
   volatile bool m_bRefreshCurNodeHead;   // galima irasyti True, norint atnaujinti siuo metu
                                          //    LzdShDlg_tag::m_NodList selektinto mazgo antrastes
                                          // vietoj WM_LZDSH_SET_TAG_HEADINGS_CURRENT
                                          // !!! nesuveiks keiciant mazgo selektinima - taimerio trukis
                                          //    ateis, kai mazgas jau bus pasikeites
   volatile bool m_bRefreshDisplay;       // galima irasyti True, norint atnaujinti siuo metu
                                          //    LzdShDlg_tag::m_NodList selektinto mazgo rezultato
                                          //    vaizda m_ResRichEdit
#endif

#ifdef KP_USE_TextGRAB
// CComPtr<ITextGRABSDK>   spITextGRABSDK;
   ITextGRABSDK   *m_pITextGRABSDK;
#endif
   LzdShSearch(void);
   ~LzdShSearch(void);

   HRESULT InitLzdShSearch(void); // inicializacijos darbai, kuriems reikia pilnesnio sistemos funkcionalumo, negu konstruktoriui (klaidø praneðimai etc.)

   HRESULT OpenFiles // atidaro archyvo failà m_lpInFileObj (jei IBSHT_ARCHIVE), atidaro buferiná iðvedimo failà m_lpInFileObj --> m_pResBuf
   (
      const unsigned char *lpszInFileName = null,
      XmlVersions iVersion = XM_VERS_XHTML, // XM_VERS_HTML401_TRANS,
      HRESULT KpInFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNew8File,
      HRESULT KpOutFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNewUniBFile
   ); // isijungia m_bSemBlocked semafora
      // KpFileFactory – kokiu þemo lygio formatu skaityti input failus – CreateNew8File ar CreateNewUniFile
   HRESULT CloseFiles(bool bCheckFileExist); // isijungia m_bSemBlocked semafora

   HRESULT LzdShCreateThread(HINSTANCE hInstance);

   virtual HRESULT SetToSearchStr(const unsigned char *lpszToSearchStr, int iToHistListFlags);
                                    // sets value of m_lpszToSearch; former SetInpStr()
                                    // isijungia m_bSemBlocked semafora
                                    // iToHistListFlags - nustato m_iToHistListFlags

   virtual HRESULT CalcOffsets(long lOffset, long *plStartOffset, long *plEndOffset);

   virtual HRESULT SearchAndDisplay(void); // isijungia m_bSemBlocked semafora
            // pasitikrina, ar reikia ieðkoti, tada SearchForEntry() (kuris savo ruoþtu iðkvieèia DisplayResult())

   HRESULT CvtToKwd(/* int iLang */);

   virtual HRESULT SearchForEntry
   (
      KpPubDlg *pDialogPtrPar,
      const unsigned char *lpszEntryName = null,
      XmlO1 **pInFilePtr = NULL,
      unsigned char **pEntryImgPtr = NULL
   );       // ieðko einamojo lizdo/failo,
            // prieð tai galima nustatyti naujà m_lpszCurSearchKwd arba áraðyti m_lCurEntryId = -1, norint forsuoti atnaujinimà
            // jeigu nurodytas lpszKeyWord, tai tai padaro pats
            // isijungia m_bSemBlocked semafora
            // nustato failà á lizdo pradþià, perskaito lizdà á laikinà XmlNode (iðkvieèia ReadEntry()),
            // suformuoja RTF/HTML buferá pDialogPtrPar->m_pResBuf[] (iðkvieèia FormatEntry()),
            // laikinà XmlNode iðtrina

#ifdef LZDSHT_ENCODED
// isveda uzkoduota XML-ini lizda masyve i RTF, i m_lpOutFileObj
// iskviecia kphp11 RC, sis savo ruoztu - WriteRtfFromImg()
   HRESULT WriteRtfFromEncImg(unsigned char *caEntryImg, long lEntryLength, long lEntryId);

// istraukia HW is uzkoduoto XML-inio lizdo masyve
// iskviecia kphp11 RC, sis savo ruoztu - GetHwFromImg()
// *piazHwPtr - grazinamas naujai sukurto hw teksto 16-bitu eilutes adresas,
//    NULL - lizdas be hw
//    jei ne NULL, po panaudojimo turi buti sunaikintas su delete []
   HRESULT GetHwFromEncImg(KpChar **piazHwPtr, unsigned char *caEntryImg, long lEntryLength, long lEntryId);
#endif

#if FALSE
   HRESULT StrCatToResultRtf(unsigned char *lpszInStr);
   HRESULT StrCatToResultRtf(char *lpszInStr);
   HRESULT ChrCatToResultRtf(unsigned char ucChar);

   HRESULT CvtResultToRtf(void);
#endif

   HRESULT FormatEntry(XmlNode *pCurEntry, KpPubDlg *pDialogPtrPar); // outputs pCurEntry to m_lpOutFileObj // former CvtToRtf
         // pakoreguoja iðvedamo lizdo turiná (pCurEntry->ClearAccents(), pCurEntry->ProcessLevel(), pCurEntry->MarcHighlighted())
         // suformuoja RTF/HTML buferá pDialogPtrPar->m_pResBuf[] (pCurEntry->WriteRtf()/pCurEntry->WriteNode())
         // iðkvieèia DisplayResult()

#if TRUE // #ifdef IBSH_RES_MODE_RTF
   virtual HRESULT DisplayResult(void); // isijungia m_bSemBlocked semafora
      // paleidþia RTF/HTML buferio lzdsh_dlg->m_pResBuf[] ákëlimà á browserá (KpSetCtrlRtfText()/KpGeckoDialog::Load())
      // iðtrina lzdsh_dlg->m_pResBuf[] turiná
#endif
#ifdef LZDSH_EDITOR_BUILD
#ifdef Debug
// HRESULT DisplayRtfTestResult(void);
#endif
#endif

   virtual HRESULT ProcSearch(void); // mygtuko LZDSH_ID_SEARCH procedura // isijungia m_bSemBlocked semafora
   HRESULT AppendSearchResults(int iLang, /* unsigned char *lpszUpdatedInpStr, */ KpTreeEntry **ppAppendList);
         // lpszUpdatedInpStr[KP_MAX_FILE_LIN_WDT+1] - buffer for new value of m_lpszInpStr

   virtual HRESULT GetReactToSel(bool *pbReactToSel);
   virtual HRESULT SetReactToSel(bool bReactToSel);
};

// extern LzdShSearch theSearchThread;
// #define pLzdSearch ((LzdShSearch *)KpGeckoFilePtr)
// #define pLzdSearch ((LzdShSearch *)KpFileSysPtr)
// #define theSearchThread (*pLzdSearch)
// extern LzdShSearch *pLzdSearch;
// #define pLzdSearch (theKpStAppPtr->m_pGrpKpPubDlg->m_pKpFileSys)

// lzdsh_search inicializavimas; prieð tai turi bûti LZDSH_DLG_PTR_INIT
#define LZDSH_SEARCH_PTR_INIT \
KpFileSys *lzdsh_search = NULL; \
   if(SUCCEEDED(retc)) lzdsh_search = lzdsh_dlg->m_pKpFileSys; \
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

extern DWORD WINAPI LzdShSearchIdle(LPVOID lpParameter);

#endif

extern KpChar *NormalizeHeadword(KpChar *piazOutStr, const KpChar *piazInStr); // removes spec. shars from headword, substitutes headword base
// veliau ismest - turi buti geras jau faile

//--------------------------------
#ifdef LZDSHT_ENCODED
typedef struct
{
   unsigned char *m_lpszEntryImg; // XML-inis lizdo tekstas, Nul terminatorius gali buti susigadines
   long m_lEntryLength;    // lizdo teksto ilgis
   KpChar **m_piazHwPtr;  // pointeris i lauka, kuriame irasomas naujai sukurto
                           //    hw teksto 16-bitu eilutes adresas,
                           //    grazina NULL - lizdas be hw
                           //    jei grazino ne NULL, po panaudojimo iskvieciancioje programoje
                           //    turi buti sunaikintas su delete []
                           //    WriteRtfFromImg() nenaudojamas
} GetHwFromImgPars;
#endif

//--------------------------------
// isveda XML-inio lizdo teksta is masyvo i RTF, i lzdsh_search->m_lpOutFileObj
// kphp11 RC callback-as
// pPars - pointeris i GetHwFromImgPars
// naudoja FormatEntry()
#ifdef LZDSHT_ENCODED
extern HRESULT WriteRtfFromImg(void *pPars);
#endif

//--------------------------------
// istraukia HW is XML-inio lizdo teksto masyve
// kphp11 RC callback-as
// pPars - pointeris i GetHwFromImgPars
#ifdef LZDSHT_ENCODED
extern HRESULT GetHwFromImg(void *pPars);
#endif

// --------------------------
typedef enum
{
   LZDSH_Undefined=(-1),

   LZDSH_FirstPar=KPP_FIRST_PAR_STYLE, //  41
   LZDSH_OrdPar,                       //  42

   LZDSH_LastParStyle,                 //  43

} LZDSH_ParStyle;

#define LZDSH_NUM_OF_PAR_STYLES (LZDSH_LastParStyle-KPP_FIRST_PAR_STYLE)

extern const unsigned char *lpszaParStyNames[LZDSH_NUM_OF_PAR_STYLES];
extern const int iaBasedOn[LZDSH_NUM_OF_PAR_STYLES];

// extern int LsdShCompareListEntries(const void *val_1, const void *val_2);

