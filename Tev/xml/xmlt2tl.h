// ==================================================
// xmlt2tl.h
// extract level corresponding XMLT tags 
// definitions of main module
//


#ifndef xmlt3tl_included
#define xmlt3tl_included

#if (Envir!=MSWin32Con) && (Envir!=MSWin32ConMfc)
#error "Envir!=MSWin32Con"
#endif
                 
                 
// --------------------------------------------------
class XmlT2TL
{
   HRESULT m_lhOpenResult;

   long m_lEntryId;       // current processed dictionary entry id (<se id=...> value)

public:
   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlI *m_lpInFileObj;
   XmlI *m_lpOutFileObj;

   XmlT2TL(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -

   HRESULT OpenFiles(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT WriteHeader(const unsigned char *lpszLetId, const unsigned char *lpszFullLetId, const unsigned char *PageNo, int iBoxWdtconst, int iBoxVskip);
   HRESULT WriteTail(const unsigned char *lpszLetId, const unsigned char *iazLastMark);

   HRESULT Process(int iLevel);
};


// --------------------------------------------------
extern XmlT2TL *pXmlT2TL;

#endif
