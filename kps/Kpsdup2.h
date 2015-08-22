// ---------------------
// kpsdup2.h
// copy images of files
// definitions
//

#ifndef kpsdup2_included
#define kpsdup2_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

class KpsDup2_tag
{
private:

   HRESULT lhOpenResult;
   unsigned char m_szInFileName[KP_MAX_FNAME_LEN+1];
   unsigned char m_szOutFileName[KP_MAX_FNAME_LEN+1];
   FILE *m_pInFile;
   FILE *m_pOutFile;
   long m_lInStart;
   long m_lBytCnt;
   long m_lOutStart;
   long m_lOutLength;   // outfile length before

public:
   KpsDup2_tag
   (
      const unsigned char *szInFile,
      const unsigned char *szOutFile,
      long lInStart,
      long lBytCnt,
      long lOutStart
   );
   ~KpsDup2_tag();
   HRESULT GetOpenResult(void);

   HRESULT CloseFile(bool bCheckFileExist);

   HRESULT Process(void);
};

#endif
