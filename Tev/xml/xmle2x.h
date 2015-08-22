// ==================================================
// xmle2x.h
// LVTT SGML CTBL-43 to TEX converter
// definitions of main module
//

#ifndef xmle2x_included
#define xmle2x_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
#if FALSE
class XmlE2X: public XmlOI2
{
public:
   XmlE2X(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlE2X(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFilesLocal(bool bCheckFileExist);

   HRESULT Process(bool bInsDelim);
};
#endif

class XmlE2X: public XmlT2X0
{
#if FALSE
   HRESULT m_lhOpenResult;

   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlI_tag *m_lpInFileObj;
   TvTexFile_tag *m_lpOutFileObj;

   TvXmlTagStack_tag *m_pTagStack;   // XML tag stack ptr

   long m_lEntryId;       // current processed dictionary entry id (<se id=...> value)

   KpChar m_iaLastHw[TV_XL_MAX_IX_LEN+1];

#endif
public:
   XmlE2X(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

#if FALSE
   ~XmlE2X(void);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT WriteHeader(const unsigned char *lpszLetId, const unsigned char *lpszFullLetId, const unsigned char *PageNo, int iBoxWdtconst, int iBoxVskip);
   HRESULT WriteTail(const unsigned char *lpszLetId, const unsigned char *iazLastMark);
#endif
   HRESULT OpenFilesLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT LocalEntryProc(XmlNode *pCurEntry); // local entry processing, defined in local ...e2x.cpp file

   HRESULT Process(void);
                                 // piazFromHw and piazToHw output boundaries in lowercase
};


// --------------------------------------------------
extern XmlE2X *pXmlE2X;

#endif
