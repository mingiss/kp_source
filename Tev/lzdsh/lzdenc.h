// --------------------
// lzdenc.h
// zodyno xml uzkodavimas
//


#ifndef lzdenc_included
#define lzdenc_included

// #define LZDENC_WEAK_CODED // apibrëþiamas lzdencw.exe projekto parametruose

// --------------------
class LzdEnc_tag: public KpStApp
{
   HRESULT m_lhOpenResult;

   FILE *m_lpXmlFileObj;
   FILE *m_lpXdbFileObj;
   FILE *m_lpSeIxFileObj;
   
public:      
   unsigned char m_lpszXmlFileName[KP_MAX_FNAME_LEN+1];
   unsigned char m_lpszXdbFileName[KP_MAX_FNAME_LEN+1];
   unsigned char m_lpszSeIxFileName[KP_MAX_FNAME_LEN+1];
   
   LzdEnc_tag(const unsigned char *lpszFname);
   ~LzdEnc_tag();
   HRESULT GetOpenResult(void);
   HRESULT CloseFiles(bool bCheckFileExist);

   HRESULT EncodeEntry(unsigned char *pcEncodeBuf, long lBufLen, long lEntryId);
         // pcEncodeBuf - islygintas i virsu iki kartotinio 4 baitams ilgio

   HRESULT Process(void);
};

#endif // #ifndef lzdenc_included
