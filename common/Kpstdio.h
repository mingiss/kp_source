// ==================================================
// kpstdio.h
// I/O definitions for KP C++ projects
//

#ifndef kpstdio_included
#define kpstdio_included


// ==================================================
#if Compiler==Watcom
#define unlink(fn) (DeleteFile(fn) == 0);
#endif


// ==================================================
#define KPIO_DIR_ACCESS_FILE_SIZE_EQ 1000 // failo trynimo laiko ekvivalentinis rašomo failo dydis kilobaitais
                                          // failo trynimą įvertinam kaip 1000 KB failo rašymą
                                          // naudojamas KpDeleteFolderContents() ir StartSelDialogProc()

// ==================================================
extern HRESULT TvFnameSplit               // splits lpszFullName to file name and file
(                                         //    type parts lpszFNameBuf, lpszFTypeBuf.
   unsigned char *lpszDiskBuf,
   unsigned char *lpszPathBuf,            // lpszDiskBuf, lpszPathBuf and lpszFNameBuf
   unsigned char *lpszFNameBuf,           //    must be not shorter than
   unsigned char *lpszFTypeBuf,           //    KP_MAX_FNAME_LEN+1 bytes, lpszFTypeBuf
   const unsigned char *lpszFullName      //    - not shorter than KP_MAX_FTYPE_LEN+1
);

// ================================================== TvUniFname_tag
#if (Lang==Cpp)
class TvUniFnameClass
{
   int iCallCnt;

public:
   TvUniFnameClass();

   HRESULT Generate(unsigned char *lpszFNameBuf);
                                          // Generates unique temporary file name
                                          // lpszFNameBuf must be not shorter than
                                          //    KP_MAX_FNAME_LEN+1 bytes

   HRESULT RandInt(long *piVal); // generates unique integer
};

extern TvUniFnameClass TvUniFname;
#endif


// ----------------------------
#define KP_WIN_UNICODE_FNAME_PREFIX ((const unsigned char *)"\\\\?\\UNC\\")


// ================================================== MBR, partition table structures
struct PartitionEntry
{
   unsigned char m_cStatus;               // 0x0000[0x0001]    = 0x80 - bootable, 0x00 - non-bootable
   unsigned char m_cStartCylinder;        // 0x0001[0x0001]
   unsigned char m_cStartHead;            // 0x0002[0x0001]
   unsigned char m_cStartSector;          // 0x0003[0x0001]
/* PartTypes */ unsigned char m_cPartType;// 0x0004[0x0001]    = PartTypes
   unsigned char m_cLastCylinder;         // 0x0005[0x0001]
   unsigned char m_cLastHead;             // 0x0006[0x0001]
   unsigned char m_cLastSector;           // 0x0007[0x0001]
   unsigned int m_iStartAbsSector;        // 0x0008[0x0004]
   unsigned int m_iNumOfSectors;          // 0x000C[0x0004]
};

struct MBR_Record
{
   unsigned char m_caCodeArea[0x01B8];    // 0x0000[0x01B8]
   unsigned int m_iDiskSignature;         // 0x01B8[0x0004]    = ???
   unsigned short m_sNulls;               // 0x01BC[0x0002]    = 0x0000

// PartitionEntry m_PartTable[4];         // 0x01BE[0x0010 * 4]
   unsigned char m_PartTable[4][sizeof(PartitionEntry)];

   unsigned short m_sPTabSignature;       // 0x01FE[0x0002]    = 0xAA55
};

extern unsigned char *lpszaPartTypeNames[KPT_Ctbsiz /* PartitionEntry.m_cPartType */];




// =================================================== Wndw - for kpx compatibility
typedef enum
{
   Norm_scroll,
   Ask_scroll,
   No_scroll,

   W_scmnum

} W_scmodes;


class Wndw // W_winstr
{
   int xxn, yyn, dxn, dyn;    /* krastai */
   int curx, cury;            /* einamosios koord. */
   Cttabs ctb;                /* spalvu lenteles nr. */
   KpColor /* Colors */ col, bcol; /* spalvos */
   int winvf, wmrkf, wblnkf;  /* inv., mrk., blnk. veliaveles */
   int lfcnt;                 /* eiluciu skaitliukas */
   W_scmodes scmode;          /* skrolinimo budas */
   int idn;                   /* identif. */
   struct C_wpst far *savpnt; /* issaugojimo buferis */
public:
   struct W_winstr *prewwin;  /* sarasui */
};


// =================================================== File - for kpx compatibility
class File
{
public:
   FILE *fp;          /* TC failas */
private:
   int fwfl;          /* file for output flag */
   int devfl;         /* device flag */
   Wndw *conwn;       /* con - window adresas, ne - Null */
   unsigned char chuge *vbufp;  /* setvbuf buferio adresas */
   int  buffl;        /* ar pakrautas buferis? */
public:
   long filpnt;       /* rodykle faile */
   long filelen;      /* failo ilgis */
private:
   unsigned char fn[Fnsiz];    /* failo vardas */
   unsigned char tmpfn[Fnsiz]; /* laikinas failo vardas */

public:
   void cfclr(void);
   FILE *cfopen(const unsigned char *fnam, const unsigned char *mode, Wndw *wn);
   FILE *cvfopen(const unsigned char *fnam, const unsigned char *mode, Wndw *wn);
   int cfpurge(void);
   int cvfpurge(void);
   void cfstat(const unsigned char *mode, Wndw *wn);
   int cfseek(long offset);
   int cwfseek(long offset);
   int cfgetc(void);
/* eilutes ivedimas is failo; '\n' neiveda */
   unsigned char *cfgetss(unsigned char *buf, int maxnum);
   bool cfeof(void) { return(feof(fp) != 0); }
};


// ================================================== FILE text I/O
extern unsigned char *fgetss cargs((unsigned char *buf, int maxnum, FILE *fil));
                                        /* eilutes ivedimas is failo; '\n' neiveda */
extern int fputss cargs((const unsigned char *buf, FILE *fil));
                                        /* eilutes isvedimas i faila; prideda '\n' */

extern HRESULT TvPutSN
(
   FILE *pfOutFile,
   const unsigned char *lpszOutString,
   const int iOutWdt
);                                        // Output of text string, adding trailing
                                          //    spaces up to width iOutWdt

// splits text buffer to lines
// does not output any messages - used by KpErrorProc_tag itself
extern HRESULT SplitToLines(unsigned char *lpszTextBuf, int iLineWdt, int iBufLen);

//------------------------------
extern HRESULT CheckFile(const unsigned char *lpszFileName);
   // checks file presence, returns KP_E_DIR_ERROR if absent
extern HRESULT CheckEmpty(const unsigned char *lpszFileName);
   // checks file presence, creates empty, if absent

// ----------------------------
extern HRESULT KpGetFileSizeFile(FILE *pInFile, long *plFileSize); // former GetFileSize()
   // calculates file size in bytes
   // restores file current position to start position

extern HRESULT KpGetFileSizeName(const unsigned char *lpszFileName, long *plFileSize, bool bOutputErrorMessages = True);
   // calculates file size in bytes

// ----------------------------
extern HRESULT ReadFileContents(const unsigned char *lpszFileName, unsigned char **plpszFileContPtr, long *plFileLen, bool bCheckFileNotFound, bool bBinary);
   // allocates buffer *plpszFileContPtr and reads file contents to it
   // buferį iššskiria vienu baitu didesnį – kad tilptų galinis Nul
   // caller must destroy that allocation after use (delete [] plpszFileContPtr)
   // returns KP_E_FILE_NOT_FOUND if file is not present, no buffer allocation is performed in that case
   // bCheckFileNotFound == True - išveda pranešimą
   // priraso Nul gale *plpszFileContPtr

extern HRESULT ReadFileContentsNalloc(const unsigned char *lpszFileName, unsigned char *lpszFileContPtr, long *plFileLen, bool bCheckFileNotFound, bool bBinary); 
   // kaip ReadFileContents(), tik failą skaito į kvietėjo buferį
   // *plFileLen turi būti užpildytas buferio lpszFileContPtr ilgiu
   // bCheckFileNotFound == True - išveda pranešimą
   // priraso Nul gale lpszFileContPtr
      
// ----------------------------
extern HRESULT ReadStrArr(const unsigned char *lpszFileName, unsigned char **plpszStrContents, int *piArrSize, 
                  const unsigned char *lpszPrefix = (const unsigned char *)"");
   // perskaito failo eilutes, išskiria kiekvienai vietą, adresus užpildo į plpszStrContents
   // in: piArrSize - plpszStrContents dydis
   //    lpszPrefix - prideda prieš kiekvieną perkaitytą eilutę
   // out: piArrSize - perskaitytų eilučių skaičius
   // grąžina KP_E_BUFFER_OVERFLOW, jeigu plpszStrContents persipildo
   

// ----------------------------
extern HRESULT MakeWordListFile(const unsigned char *lpszFileName);
   // pagamina failo visų žodžių sąrašą po žodį vienoj eilutėj,
   // failą *.lst, kur visi tarpai sutraukti ir pakeisti eilučių pabaigom

// ----------------------------
extern int CountFileLines(const unsigned char *lpszFileName);
   // suskaičiuoja teksto eilutes. Paskutinę netuščią irgi prideda, nors ir be CR/LF

// ----------------------------
extern HRESULT CreatePath(const unsigned char *lpszPathName, bool bPutErrorMsg);
   // creates all subdirectories of specified path
   // if path consists of directories only, must be terminated with "\"

// ----------------------------
extern HRESULT KpCountFolderFileSizeCnt(const unsigned char *lpszPath, int *piCount = NULL, long *plSize = NULL); 
   // lpszPath be slešo gale 
   // visų failų ir pakatalogių skaičius
   // *plSize - suminis visų failų dydis kilobaitais

// ----------------------------
extern HRESULT KpDeleteFolderContents(const unsigned char *lpszPath, 
   HWND hProgressWnd = NULL, 
   time_t iStartTime = 0, long lFullSize = 0L, long *plProcessedSize = NULL, long *plUsbSpeed = NULL);

// ----------------------------
extern HRESULT KpCopyFolder(const unsigned char *lpszSrcPath, const unsigned char *lpszDstPath, 
   HWND hProgressWnd = NULL, 
   time_t iStartTime = 0, long lFullSize = 0L, long *plProcessedSize = NULL, long *plUsbSpeed = NULL,
   bool bOutMsg = True // ar išvedinėti klaidų pranešimus
   );

// ----------------------------
extern HRESULT KpDirFile(const unsigned char *lpszInitPath, const unsigned char *lpszSrcPath, fstream *pLogFile, bool bOutMsg, bool bEncode = False); // lpszSrcPath pilnas, be slešo gale
extern HRESULT KpDir(const unsigned char *lpszSrcPath, fstream *pLogFile, bool bOutMsg, bool bEncode = False);
extern HRESULT KpDir(const unsigned char *lpszSrcPath, const unsigned char *lpszLogFile, bool bOutMsg, bool bEncode = False);
   
// ----------------------------
extern HRESULT ConvertSlashes(unsigned char *lpszPath, unsigned char cSlash); // suvienodina '\\' ir '/' slešus

// ------------------- set file creation date, klaidų pranešimų neišveda
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
extern HRESULT ChFileTimeCrtd(const unsigned char* lpszFName, const SYSTEMTIME *ptt);
#endif

// ------------------- get file creation date
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
extern HRESULT KpGetFileCrTime(const unsigned char* lpszFName, SYSTEMTIME *pCrTime, SYSTEMTIME *pWrTime = NULL); 
                     // pCrTime - file creation time
                     // pWrTime - last write time
#endif                                                                                                            



// ==================================== interface to common low level file class
// atkelta iš xmlf.h
typedef enum
{
   XL_FT_Undefined = (-1),
   XL_FT_DataFile,      // XML data file
   XL_FT_MainIxFile,    // main index file with pointers to XML data file byte positions
   XL_FT_IxFile,        // ordinary index file bound with main index file
   XL_FT_ReportFile,    // report file about index conversions

   XL_FT_NumOfFTypes

} XL_FileTypes;


class KpFile // former TvXmlFile0 // žemo lygio failo interfeisas, naudojamas pakišimui po aukštesnio lygio failais (TvXmlFile, UcFile)
{                                 // naudojamas įvedimui iš įvairių Unicode formatų, taip pat iš atminties buferio
public:
   unsigned char m_lpszFName[KP_MAX_FNAME_LEN + 1]; // file name
   unsigned char m_lpszFMode[KP_KWD_LEN /* TV_TAG_LEN */ + 1];       // file open mode (like fopen())
   bool m_bBinFlg;
   
   HRESULT m_lhOpenResult;

   UC_Modes m_iEncMode;
   int m_iCodeTable;       // 0 means no code table
   bool m_bMapToPrivate; // mapping to user defined unicode characters flag (affects only Unicode files)
   
// ------------------------------------- file open
   HRESULT Constructor
   (
      const unsigned char *lpszFileName,
      const unsigned char *lpszMode,
      XL_FileTypes uiFileType,
      bool bMapToPrivate
   ); // common initialisation of properties, must be called from very begin of derived class constructor

   HRESULT GetOpenResult(void);
                                 // Returns value of OpenResult -
                                 //    object creation error code

   virtual HRESULT GetRawFilePtr(FILE **lppFilePtrPtr, bool bCheckError) = 0;
                                 // returns pointer to FILE object of currently opened file;
                                 //    it can be used for direct binary file operations
                                 // bCheckError - False used for supressing of error messages
                                 //    in RAM files (xmlb.cpp)

   virtual HRESULT CloseFile(bool bCheckFileExist) = 0;
                                 // Closes current Xml file
                                 //   this call makes sence only for result code retrieving,
                                 //   after CloseFile() no other calls except ~TvXmlFile
                                 //   are acceptable
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   virtual HRESULT VirtDestruct(void) = 0;
                                 // explicit destructor of derived class;
                                 // must be called from parent class before
                                 //    destroying of the object

// -------------------------------------
// get/set current code table for lowlevel file
// get/set file encoding parameters
   HRESULT GetEncoding(UC_Modes *piEncodingMode, int *piCodeTable);
   HRESULT SetEncoding(UC_Modes iEncodingMode, int iCodeTable);


// ------------------------------------- text output
   virtual HRESULT PutChar(KpChar iOutch, bool bCheckErrors) = 0;
                                 // Put character to file
                                 // if bCheckErrors=False, no error message
                                 //    will be output in case of nonexisting
                                 //    output equivalent, TV_E_UNKN_CHR
                                 //    is returned in this case


   virtual HRESULT GetCharPos(int *piCharPos) = 0;    // Current character position from beginning of the line
   virtual HRESULT GetCharNum(long *plCharNum) = 0;   // Current char position from beginning of the file

   virtual HRESULT Reset(void)=0;
                                 // RAM file: resets buffer pointer and clears the buffer (first character)
                                 // fictive call for ordinary files

   HRESULT PutStr(const unsigned char *lpszOutStr, bool bCheckErrors); // output of 7-bit or Kpt encoded 8-bit string
   HRESULT PutStrCtbl(const unsigned char *lpszOutStr, bool bCheckErrors, int iCtbl);
                                       // Put 8-bit string to file, 
                                       // iCtbl - kpt codetable number of the string
   HRESULT PutKpStr(const KpChar *lpaizOutStr, bool bCheckErrors); // former PutIntStr
   
   HRESULT PutKpStr(const KpChar *lpaizOutStr, bool bCheckErrors, int iCTbl); // former PutIntStr
                                       // output of 16-bit Kpt string, sets temporary encoding according to iCTbl

// ------------------------------------- text input
   virtual HRESULT GetChar(KpChar *piInch) = 0;  // Gets current char. from file

   virtual HRESULT Fseek(long lOffset, int iOrigin) = 0; // analog of fseek();
   
};

// --------------------------------------------------
typedef HRESULT XmlfLowLevelCrFun
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
);

typedef HRESULT (*XmlfLowLevelCrFunPtr)
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
);


// ===================================================== iostream
// #define setw width

#if Compiler==Mingw
#define ios std::ios_base
// #define KpInStream std::istream
#define KpOutStream std::ostream // suderinamumui su cout
#define KpFStream std::fstream
#define endl std::endl
#else
#define ios_base ios
// #define KpInStream istream
#define KpOutStream ostream
#define KpFStream fstream
#endif

class KpInStream : public // suderinamumui su cin
#if Compiler==Mingw
std::
#endif
   istream
// fstream
{
public:
#if FALSE
   KpInStream(const char *s, ios /* ios_base */::openmode mode) :
// #if Compiler==Mingw
//    std::
// #endif
//       fstream(s, mode)
            {
// #if Compiler==Mingw
//             std::
// #endif
//                fstream::open(s, mode);

// filebuf fb;
//   fb.open (s, mode);
// /* istream */ is(&fb);
                        }
#endif

#if Compiler != Mingw // nesuveikia std::istream(is) - privatus konstruktorius: `std::ios_base::ios_base(const std::ios_base&)' is private
   KpInStream(istream is) :
#if Compiler == Mingw
      std::
#endif
         istream(is) {}
#endif

#if Compiler == Mingw
   KpInStream(
#if Compiler == Mingw
      std::
#endif
         filebuf * fb) :
#if Compiler == Mingw
            std::
#endif
               istream(fb) {}
#endif

   HRESULT GetWord(KpString *pWordBuf, const unsigned char *lpszDelims, unsigned char *pcDelim); // grąžina sutiktą skirtuką į *pcDelim
};


// ================================================== debug
extern HRESULT GetLogFileName(unsigned char *lpszLogFName);
// unsigned char lpszLogFName[KP_MAX_FNAME_LEN+1]; - buferis log failo vardo grąžinimui

extern HRESULT DelLogFile(void);

extern HRESULT PutLogDate(fstream *poutFile);
// išveda log pranešimo pradžią - datą etc.

extern HRESULT CopyLogToDesktop(void);

extern HRESULT DecodeXfsLog(const unsigned char *lpszLogFname, fstream *pOutFile, bool bOutMsg);
extern HRESULT EncodeLogBuf(unsigned char *pBuffer, int iDataLen);
extern HRESULT EncodeLogBase64(const unsigned char *lpszFname, fstream *pOutFile);

extern HRESULT PutEncodedLogMsg(const unsigned char *lpszMsg, fstream *pOutFile); // išveda tekstą į failą, gal būt, užkoduodamas; jokių tarnybinių prefiksų neprideda 

extern HRESULT PutLogMessage(const unsigned char *lpszMsg, unsigned char *lpszLogFName = NULL);
extern HRESULT PutLogMessage(const char *lpszMsg, unsigned char *lpszLogFName = NULL);
extern HRESULT PutLogMessage(const KpChar *iazMsg, unsigned char *lpszLogFName = NULL);
// prijungia pranešimą prie log failo
// papildomų klaidų pranešimų neišvedinėja (naudojamas klaidų išvedime)
// grąžina klaidos kodą
// unsigned char lpszLogFName[KP_MAX_FNAME_LEN + 1]; - buferis log failo vardo grąžinimui; gali būti NULL // buvo su pilnu keliu iki TempKat, DOS-like, dabar – tik failo vardas su prievardžiu // former - lpszAppName[], buferis aplikacijos vardo grąžinimui

#define PutLogMessage_(...) {{char *plm_buf_ptr = new char[10000]; if(plm_buf_ptr != NULL){ sprintf(plm_buf_ptr, (const char *)__VA_ARGS__); /* KP_ASSERT_(strlen(plm_buf_ptr) < 10000, KP_E_BUFFER_OVERFLOW); */ if(strlen(plm_buf_ptr) >= 10000) PutLogMessage("PutLogMessage_(): Buffer overflow", NULL); PutLogMessage(plm_buf_ptr, NULL); delete [] plm_buf_ptr; } }}
// __VA_ARGS__ ne visiems veikia
// #define PutLogMessage_0(str) {{PutLogMessage(str, NULL);}}
// #define PutLogMessage_1(fmt, par1) {{static char str_buf[2000]; sprintf(str_buf, fmt, par1); PutLogMessage(str_buf, NULL);}}
// #define PutLogMessage_2(fmt, par1, par2) {{static char str_buf[2000]; sprintf(str_buf, fmt, par1, par2); PutLogMessage(str_buf, NULL);}}
// #define PutLogMessage_3(fmt, par1, par2, par3) {{static char str_buf[2000]; sprintf(str_buf, fmt, par1, par2, par3); PutLogMessage(str_buf, NULL);}}
// #define PutLogMessage_4(fmt, par1, par2, par3, par4) {{static char str_buf[2000]; sprintf(str_buf, fmt, par1, par2, par3, par4); PutLogMessage(str_buf, NULL);}}
// #define PutLogMessage_5(fmt, par1, par2, par3, par4, par5) {{static char str_buf[2000]; sprintf(str_buf, fmt, par1, par2, par3, par4, par5); PutLogMessage(str_buf, NULL);}}

#if Envir==MSWin32
#ifdef Debug
#define KP_TRACE0(str) {{ KpTraceWindow.AddString(str); /* Sleep(100); */ }}
#define KP_TRACE1(str) {{ KpTraceWindow1.AddString(str); /* Sleep(100); */ }}
#define KP_TRACE2(str) {{ KpTraceWindow2.AddString(str); /* Sleep(100); */ }}
#else
#define KP_TRACE0(str)
#define KP_TRACE1(str)
#define KP_TRACE2(str)
#endif
#endif

#if Envir==MSWin32Mfc
#define KP_TRACE0(str) {{TRACE((const char *)str)}}
#define KP_TRACE1(str) {{TRACE((const char *)str)}}
#define KP_TRACE2(str) {{TRACE((const char *)str)}}
#endif

#if (Envir==MSWin32Con) || (Envir==MSWin32ConMfc)
#ifdef Debug
#define KP_TRACE0(str) {{printf((const char *)str); printf("\n");}}
#define KP_TRACE1(str) {{printf((const char *)str); printf("\n");}}
#define KP_TRACE2(str) {{printf((const char *)str); printf("\n");}}
#else
#define KP_TRACE0(str)
#define KP_TRACE1(str)
#define KP_TRACE2(str)
#endif
#endif

#ifdef Logging
// #define KP_TRACE(str) {KP_TRACE0(str); if(theKpStdAppPtr) if(theKpStdAppPtr->m_pLogFile){ fprintf(theKpStdAppPtr->m_pLogFile, (const char *)str); fprintf(theKpStdAppPtr->m_pLogFile, "\n");}}
#define KP_TRACE(str) {{ KP_TRACE0(str); PutLogMessage(str, NULL); }}
#else
#define KP_TRACE(str) KP_TRACE0(str)
#endif

#undef KP_TRACING_LOGGING
#ifdef Debug
#define KP_TRACING_LOGGING
#endif
#ifdef Logging
#define KP_TRACING_LOGGING
#endif

#ifdef KP_TRACING_LOGGING
#define KP_TRACE_(...) {{ char *trc_buf_ptr = new char[10000]; if(trc_buf_ptr != NULL){ sprintf(trc_buf_ptr, (const char *)__VA_ARGS__); KP_TRACE(trc_buf_ptr); delete [] trc_buf_ptr; } }}
// #define KP_TRACE_1(fmt, par1) {char str_buf[200]; sprintf(str_buf, fmt, par1); KP_TRACE(str_buf);}
// #define KP_TRACE_2(fmt, par1, par2) {char str_buf[200]; sprintf(str_buf, fmt, par1, par2); KP_TRACE(str_buf);}
// #define KP_TRACE_3(fmt, par1, par2, par3) {char str_buf[200]; sprintf(str_buf, fmt, par1, par2, par3); KP_TRACE(str_buf);}
// #define KP_TRACE_4(fmt, par1, par2, par3, par4) {char str_buf[200]; sprintf(str_buf, fmt, par1, par2, par3, par4); KP_TRACE(str_buf);}
// #define KP_TRACE_5(fmt, par1, par2, par3, par4, par5) {char str_buf[300]; sprintf(str_buf, fmt, par1, par2, par3, par4, par5); KP_TRACE(str_buf);}
#else
#define KP_TRACE_(...)
// #define KP_TRACE_1(fmt, par1)
// #define KP_TRACE_2(fmt, par1, par2)
// #define KP_TRACE_3(fmt, par1, par2, par3)
// #define KP_TRACE_4(fmt, par1, par2, par3, par4)
// #define KP_TRACE_5(fmt, par1, par2, par3, par4, par5)
#endif

// ------------------------------------------
#endif // #ifndef kpstdio_included
