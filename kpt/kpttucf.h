// ==================================================
// kpttucf.h
// Definitions for Unicode files


#ifndef kpttucf_included
#define kpttucf_included

#define KPTTUCF_XMLF_FILE  // UcFile.lpFile KpFile* instead of FILE* // duoda klaidą

// --------------------------------------------------
class UcFile // former UcFile_tag
{
public:
   unsigned char lpszFName[KP_MAX_FNAME_LEN+1];

#ifdef KPTTUCF_XMLF_FILE
   KpFile *lpFile;
private:
#else
   FILE *lpFile;
#endif

   HRESULT m_lhOpenResult;
   UC_Modes m_iUcMode;
   int m_iFMode;
   int m_iCharPos;   // Current character position from beginning of the line
   long m_lCharNum;  // Current char position from beginning of the file

   unsigned char m_cUnGetChLowBuf;
   bool m_bUnGetChLowFl;

   unsigned long m_lUnGetChBuf;
   bool m_bUnGetChFl;

   KpChar iUnGetChProcBuf;
   bool bUnGetChProcFl;

public:
   UcFile
   (
      const unsigned char *lpszFileName,
      UC_Modes iUnicMode,
      const unsigned char *lpszMode,
      XmlfLowLevelCrFunPtr CreateLowLevelObj,
      bool bMapToPrivate
   );  // opens file lpszFileName in coding iUnicMode for read/write (according to lpszMode)

   ~UcFile();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT GetRawFilePtr(FILE **lppFilePtrPtr);
                                 // returns pointer to FILE object of currently opened file;
                                 //    it can be used for direct binary file operations

   HRESULT CloseFile(bool bCheckFileExist);
                                 // Closes input/output file. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

//----------------------------- raw file level
   HRESULT GetCharLow(unsigned char *pcChar); // gets character from lpFile
   HRESULT GetCharLow(int *piChar);
   HRESULT GetCharLow(unsigned long *plChar);
   HRESULT UnGetCharLow(unsigned char cChar);
   HRESULT PutCharLow(unsigned char cChar);
   HRESULT PutCharLow(int iChar);
   HRESULT PutCharLow(unsigned long lChar);


// --------------------------- unicode level
   HRESULT GetChar(unsigned long *plInCh); // gets Unicode character

   HRESULT UnGetChar(unsigned long lChar);

   HRESULT PutChar(unsigned long lOutCh);  // puts Unicode character

   HRESULT GetCharPos(int *piCharPos);    // Current character position from beginning of the line
   HRESULT GetCharNum(long *plCharNum);   // Current char position from beginning of the file

// --------------------------- kp level
   HRESULT GetCharProc(KpChar *piInCh);  // gets Unicode character and converts it to Kpt

   HRESULT GetIntStr(KpChar *lpaizInBuf, int iBufSize);
                                          // gets line of Unicode characters and converts it to Kpt string

   HRESULT UnGetCharProc(KpChar iChar); // like ungetc()

   HRESULT PutCharProc(KpChar iOutCh, bool bCheckFlg, bool bMapToPrivate);
                                 // puts Kpt character in Unicode coding
                                 // if bCheckFlg==False, no error message
                                 //    will be output in case of nonexisting
                                 //    Unicode equivalent, TV_E_UNKN_CHR
                                 //    is returned in this case
                                 // if bMapToPrivate==True, unmapped Kpt characters
                                 //    will be output as private area Unicode characters,
                                 //    no TV_E_UNKN_CHR error wil be produced

   HRESULT PutStrProc(const unsigned char *lpszOutStr, bool bMapToPrivate);  // puts string to Unicode file

   HRESULT Ftell(long *plOffset);  // like ftell()

   HRESULT Fseek(long lOffset, int iOrigin);  // like fseek()

   HRESULT Fscanf(const char *lpszFormat, void *pValue);  // like fscanf()

   HRESULT Fread(void *pvBufPtr, int iBytCnt); // like fread(pvBufPtr, 1, iBytCnt, ... )

   HRESULT Fwrite(const void *lpBuffer, int iByteCount);  // like fwrite(lpBuffer, 1, iByteCount, ...)
};

extern HRESULT EncodeUnicodeChar(unsigned char *lpcOutChars, int *piByteCount, long lInCh, UC_Modes iUcMode);
extern HRESULT EncodeUnicodeKpChar(unsigned char *lpcOutChars, int *piByteCount, KpChar iInCh, UC_Modes iUcMode);
// encodes unichode char to output char array for output to unicode file
// realizuota tik iUcMode==UC_UTF_8
// does not output any error messages
// lpcOutChars[4+1]
// adds Nul to the end
// piByteCount can be NULL, tures prasme tik UTF-16 (tada buna nuliniai baitai viduj)
extern HRESULT EncodeUnicodeKpStr(unsigned char *lpszOutStr, int iBufSize, const KpChar *iazInStr, UC_Modes iUcMode);
// realizuota tik iUcMode==UC_UTF_8
// does not output any error messages
// lpszOutStr[iBufSize+1]

extern HRESULT GetCharLowStat(int *piChar, UcFile *pUcFile, const unsigned char **ppStrPtr);
// skaito viena baita is pUcFile
// calbackas del GetEncodeUniChar(), failinis variantas
// faktiskai isorinis UcFile::GetCharLow() iskvietimas
// naudoja UcFile::GetChar()
// ppStrPtr = NULL

extern HRESULT GetCharStr(int *piChar, UcFile *pUcFile, const unsigned char **ppStrPtr);
// skaito viena baita is **ppStrPtr, inkrementuoja *ppStrPtr
// calbackas del GetEncodeUniChar(), teksto eilutes variantas
// pUcFile = NULL

extern HRESULT GetEncodeUniChar(unsigned long *plInCh, HRESULT (*GetCharLowCallBack)(int *, UcFile *, const unsigned char **), UcFile *pUcFile, const unsigned char **ppStrPtr, UC_Modes iUcMode);
// skaityti viena Unicode simboli
// realizuota tik iUcMode==UC_UTF_8
// vidine funkcija, naudojama UcFile::GetChar() ir DecodeKpStrUnicode()
// GetCharLowCallBack gali buti  GetCharLowStat() ar GetCharStr() - priklausomai is failo (UcFile::GetChar()) ar 
//    eilutes (DecodeKpStrUnicode()) skaitomas Unicode srautas 

extern HRESULT GetEncodeKpUniChar(KpChar *piInCh, HRESULT (*GetCharLowCallBack)(int *, UcFile *, const unsigned char **), UcFile *pUcFile, const unsigned char **ppStrPtr, UC_Modes iUcMode);
// iskviecia GetEncodeUniChar(), tik perkoduoja i KpChar

extern HRESULT DecodeKpStrUnicode(KpChar *iazOutStr, int iBufSize, const unsigned char *lpszInStr, UC_Modes iUcMode);
// realizuota tik iUcMode==UC_UTF_8
// lpszInStr sisip baigiasi Nul, kaip bus, kai iUcMode==UC_UTF_16 - nezinau
// iazOutStr[iBufSize+1] 
// does not output any error messages

#endif
