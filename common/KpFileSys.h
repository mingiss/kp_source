// ---------------------------------------
// KpFileSys.h
// publishinimo fail� (knygos skyri�, �odyno lizd�) sistema - d�l lzdhst, arksht
// apibr��imai
//

#ifndef KpFileSys_included
#define KpFileSys_included

#ifndef iBshn_included
#error iBshn.h not included
#endif

// -----------------------------
// #if IBSH_PROJ == IBSH_PROJ_TEVT
// #define KP_GECKO_MAX_ANSWER   7 // max bito numeris baite
// #define KP_GECKO_MAX_ANSWER   3 // max bito numeris de�imtainiam skaitmeny
// #define KP_GECKO_MAX_ANSWER   9 // max de�imtainis skaitmuo
#define KP_FILESYS_MAX_ANSWER   (KPST_TXTCD_RADIX_REZ - 1) // 7 // max a�tuntainis skaitmuo // former KP_GECKO_MAX_ANSWER
#define KP_FILESYS_NUM_TASKS 100 // former KP_GECKO_NUM_TASKS
// #endif

#define KP_FILESYS_RESULT_BUF_LEN 200000 // i�skirdin�ti dinami�kai// former KPPUBDLG_RESULT_BUF_LEN, IBSH_RESULT_BUF_LEN, KPGECKO_RESULT_BUF_LEN, LZDSHT_RESULT_BUF_LEN, XMLN_RICH_BUF_LEN

// i�ankstinis fiktyvus apibr��imas
class XmlNode;
class KpPubDlg;

class KpFileSys // former KpGeckoFile // LzdShSearch ir ArkShFile motina
{
public:
   HRESULT m_lhOpenResult;

// ----------------
   volatile int m_iIndexFile; // main search and list display index file number
   int m_iCurIndexFile; // index file number according to keyword input method (keyboard/list selection)

// ----------------
public:
/* volatile */
#ifdef IBSHT_ARCHIVE
   XmlI
#else
   XmlO1
#endif
      *m_lpInFileObj;   // input file with dictionary for searching
                        // jei IBSHT_ARCHIVE, viso archyvo failas, atidaromas OpenFiles()
                        // je ne � kiekvienas naujas failas, atidarin�jamas SearchForEntry()

// output RAM file for output to RichEdit/HTML control
/* volatile */ 
#ifdef IBSH_RES_MODE_RTF
   TvRtfO
#else
#  if IBSH_PROJ == IBSH_PROJ_LZDSH
   XmlI // TvXmlFile_tag
#  else   
   XmlO1
#  endif
#endif
      *m_lpOutFileObj;


   HRESULT (*m_pKpInFileFactory) // former m_pKpFileFactory
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   );

   HRESULT (*m_pKpOutFileFactory)
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   );

// ----------------
   volatile long m_lCurEntryId;  // galima irasyti -1, norint atnaujinti visa vaizda ir inicializuoti listboxus

   /* volatile */ unsigned char m_lpszCurSearchWord[KP_MAX_FILE_LIN_WDT + 1]; // search word as entered by user
   /* volatile */ unsigned char m_lpszCurSearchKwd[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1]; // dar buvo i�dubliuotas � m_lpszHtmlFileName[]
                           // search word converted to index entry
                           // nustatyti � norim�, m_lCurEntryId = -1 ir kviesti SearchForEntry()
                           // iBshFileSys: �iuo metu rodomo failo vardas
                           // KP_MAX_FILE_LIN_WDT d�l theKpStAppPtr->GetIniCmdStr(); taip pat d�l iBshFileSys.m_lpszCurSearchWord[]
                           // dinami�kai pakei�iamas, kai KpGeckoStreamFactory() gauna nauj� fail� su pl�tiniu .htm*
   unsigned char m_lpszCurSearchKwdPrev[KP_MAX_FILE_LIN_WDT + 1];   // previous value of m_lpszCurSearchKwd
   volatile unsigned char m_lpszToSearch[KP_MAX_FILE_LIN_WDT + 1];        // zodis, pagal kuri ieskoma rodytino lizdo; former theDialog.m_lpszInpStr
   volatile unsigned char m_lpszLastSearchStr[KP_MAX_FILE_LIN_WDT + 1];   // paskutine ieskota eilute; former LzdShDlg_tag::m_lpszLastSearchStr

// -------------------
   /* volatile */ XmlNode *m_pCurEntry;   // dictionary entry currently viewed in LzdShDlg::m_NodList
                                          // former cur_entry local in iBshFileSys::SearchForEntry()
                                          // parallel to cur_entry in LzdShSearch::SearchForEntry()
                                          // buv. m_pResNode � ShowHtmFile rodomo HTML failo suparsintas turinys

   UniChar *m_pResBuf;
                     // search result converted to HTML or XHTML
                     // element� tipas UniChar ar unsigned char, priklausomai nuo m_iEncMode
                     // i�skiriamas dinami�kai m_pResBuf[KP_FILESYS_RESULT_BUF_LEN + 1]
// #define m_lpszResultFormatted ((iEncMode >= UC_Unicode16)?m_pResBuf:((unsigned char *)m_pResBuf))

// -------------------
// #if IBSH_PROJ == IBSH_PROJ_TEVT
   int m_iTaskNo; // dabartin�s u�duoties nr., i�trauktas i� m_lpszCurSearchKwd
   /* unsigned */ char m_aiAnswers[KP_FILESYS_NUM_TASKS];

private:
   int m_iMask; // atsakym� kodavimui

   unsigned char m_lpszUserName[KP_MAX_FILE_LIN_LEN + 1];
   unsigned char m_lpszUserSurName[KP_MAX_FILE_LIN_LEN + 1];

// #endif


// ----------------
public:
   /* volatile */ DWORD m_lThreadId;   // paie�kos threado id; jei 0 - paie�ka tam pa�iam threade, reikia kviesti SearchForEntry(), RedrawWindow() i� karto

   volatile int m_iSemBlocked;   // semaforo blokavimo gylis, 0 - semaforas laisvas // former LzdShSearch::m_bSemBlocked
                                 // >0, kai nieko negalima daryti su thread'ams jautriais objektais
private:
   volatile DWORD m_lSemBlockingThread; // semafora blokuojancio thread'o ID (GetCurrentThreadId())
                                        // reikia laukti, tik jei threadas kitas
public:
// -------------------------
// atkelti i� LzdShSearch
   volatile int m_iLevel;
   volatile int m_bAccFl;

   int m_iToHistListFlags;

   long m_lQuietTime;

   volatile unsigned char m_lpszToHistStr[KP_MAX_FILE_LIN_WDT+1];       // zodis, praejus LZDSH_TIME_TO_HIST pridetinas prie theDialog.m_HistList
   volatile unsigned char m_lpszPrevHistWord[KP_MAX_FILE_LIN_WDT+1];    // previous value stored to theDialog.m_HistList

   volatile bool m_bReactToSelFlag;

   unsigned char m_lpszClipBuf[KP_MAX_FILE_LIN_WDT + 1];

// ----------------
   KpFileSys(void);  // paveld�tos klas�s konstruktorius turi i�kviesti ProcessAnswer(0), kad susikurt� tu��ias rezultat� failas
   virtual ~KpFileSys();

   HRESULT GetOpenResult(void);

   virtual HRESULT OpenFiles
   (
      const unsigned char *lpszInFileName = null,
      XmlVersions iVersion = XM_VERS_HTML401_TRANS,
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
   ) = 0;
      // isijungia m_bSemBlocked semafora
      // KpFileFactory � kokiu �emo lygio formatu skaityti input failus � CreateNew8File ar CreateNewUniFile, i�saugoja � m_pKpInFileFactory
      // KpOutFileFactory � kokiu �emo lygio formatu ra�yti � i�vedimo bufer� � CreateNewBFile ar CreateNewUniBFile, i�saugoja � m_pKpOutFileFactory
   virtual HRESULT CloseFiles(bool bCheckFileExist) = 0; // isijungia m_bSemBlocked semafora

   HRESULT BlockSemaphore(void);    // waits until m_bSemBlocked==True, sets m_bSemBlocked to True
   HRESULT ReleaseSemaphore(void);  // sets m_bSemBlocked to False

   virtual HRESULT SearchForEntry(KpPubDlg *pDialogPtr, const unsigned char *lpszKeyWord = null,
      XmlO1 **pInFilePtr = NULL,
      unsigned char **pEntryImgPtr = NULL
      ) = 0;   // ie�ko einamojo lizdo/failo,
               // prie� tai galima nustatyti nauj� m_lpszCurSearchKwd arba �ra�yti m_lCurEntryId = -1, norint forsuoti atnaujinim�
               // jeigu nurodytas lpszKeyWord, tai tai padaro pats
   virtual HRESULT FormatEntry(XmlNode *pCurEntry, KpPubDlg *pDialogPtr) = 0; // outputs pCurEntry to m_lpOutFileObj // former CvtToRtf

// #if IBSH_PROJ == IBSH_PROJ_TEVT
   HRESULT ProcessAnswer(int iAnswNo); // nustato aiAnswers[m_iTaskNo], �ra�o rezultat� fail�, i�siun�ia prane�im� rezultat� serveriui
                                       // paveld�tos klas�s konstruktorius turi i�kviesti ProcessAnswer(0), kad susikurt� tu��ias rezultat� failas
   HRESULT SendAnswers(int iTaskNo);   // siun�ia tarpinius iTaskNo u�davinio rezultatus � server�
                                       // jei iTaskNo==0, siun�ia galutinius rezultatus
   HRESULT EncodeUserName(unsigned long *pulRezVal, const unsigned char *lpszName);

   HRESULT CalcTaskNo(void);  // i�traukia u�duoties nr. m_iTaskNo i� m_lpszCurSearchKwd
                              // nerado -  m_iTaskNo = -1;
// #endif

// ---------------------------------------------------
// sukuria nauj� sraut� skaitymui i� xGecko objekto
// i�kvie�iamas i� KpGeckoStreamFactory()
// �ia be jokios paie�kos, tiesiog i�orinis failas, su KpFileSys nesusij�s, galima i�kelti lauk
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr==Mingw
   virtual HRESULT CreateGeckoStream(const unsigned char *lpszFName, // i�gliaudytas failo vardas
                                     const unsigned char *lpszURI,   // pilnas URI, gautas i� xGecko objekto
                                     IInputStream **ppGeckoStream);  // gr��inamas naujai sukurtas srautas
#  endif
#endif

   virtual HRESULT GetReactToSel(bool *pbReactToSel);
   virtual HRESULT SetReactToSel(bool /* bReactToSel */){ return(S_OK); }

// -------------------------
// atkelti i� LzdShSearch
   virtual HRESULT SetToSearchStr(const unsigned char * /* lpszToSearchStr */, int /* iToHistListFlags */){ return(S_OK); }
   virtual HRESULT CalcOffsets(long /* lOffset */, long * /* plStartOffset */, long * /* plEndOffset */){ return(S_OK); }
   virtual HRESULT SearchAndDisplay(void){ return(S_OK); }
   virtual HRESULT DisplayResult(void){ return(S_OK); }
   virtual HRESULT ProcSearch(void){ return(S_OK); }
};



#endif // #ifndef KpFileSys_included
