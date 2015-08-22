// ==================================================
// kpt71tou8.h, Windows 1257 to UTF-8 converter
//


#ifndef kpt71tou8_included
#define kpt71tou8_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class Kpt71toU8_tag
{
   HRESULT m_lhOpenResult;

   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   TvXmlFile_tag *m_lpInFileObj; // file objects
   TvXmlFile_tag *m_lpOutFileObj;

public:
   Kpt71toU8_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~Kpt71toU8_tag(void);

   HRESULT GetOpenResult(void);        // Returns value of OpenResult -
                                       //    object creation error code

   HRESULT OpenFile(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFiles(bool bCheckFileExist);

   HRESULT Process(void);
};


// --------------------------------------------------
extern Kpt71toU8_tag *pKpt71toU8;

#endif
