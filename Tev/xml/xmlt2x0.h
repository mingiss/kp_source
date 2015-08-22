// ==================================================
// xmlt2x0.h, former lvzt2x.h
// converting XML dictionary to (LVZ03) TeX file
// definitions of main module
//


#ifndef xmlt2x0_included
#define xmlt2x0_included

#if (Envir!=MSWin32Con) && (Envir!=MSWin32ConMfc)
#error "Envir!=MSWin32Con"
#endif


// --------------------------------------------------
class XmlT2X0
{
public:
   TvXmlTagStack *m_pTagStack;   // XML tag stack ptr

   bool m_bTagOutFormat;  // output in tagged format

   KpChar m_iaLastHw[TV_XL_MAX_IX_LEN+1];

   long m_lEntryId;       // current processed dictionary entry id (<se id=...> value)

   HRESULT m_lhOpenResult;

   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlI *m_lpInFileObj;
   TvTexFile *m_lpOutFileObj;

   void XmlT2X0_constructor(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bTagFormat);
   virtual ~XmlT2X0(void);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   virtual HRESULT OpenFilesLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname) = 0;

   HRESULT OpenFiles(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT WriteHeader(const unsigned char *lpszLetId, const unsigned char *lpszFullLetId, const unsigned char *PageNo, int iBoxWdtconst, int iBoxVskip);
   HRESULT WriteTail(const unsigned char *lpszLetId, const unsigned char *iazLastMark);

};

//----------------------------
extern unsigned char caXmlT2XIxLangs[XL_IX_NumOfIndexes0];

#endif
