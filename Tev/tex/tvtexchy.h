// ==================================================
// tvtexchy.h
// Convert TeX hyphenation table adding all accented combinations
// definitions



#ifndef tvtexchy_included
#define tvtexchy_included

// --------------------------------------------------
#define TX_CHY_NumOfTags0 (TX_CHY_LastTag-TX_CHY_FirstTag)
#define TX_CHY_NumOfTags1 TX_CHY_NumOfTags0

typedef enum
{
   TX_CHY_Unknown,

   TX_CHY_FirstTag   =TX_FirstUserTagCode,

   TX_CHY_x    /* 12000 */       =TX_FirstUserTagCode,      
   TX_CHY_n,   // 12001    patterns with diaeresis
   TX_CHY_c,   // 12002    duplicated pattern for alternative german font - ignore contents
   TX_CHY_3,   // 12003    C_ss
   TX_CHY_9,   // 12004    C_ss

   TX_CHY_LastTag

} TX_CHY_TagIds;


// --------------------------------------------------
class TvTexChy_tag
{
   HRESULT lhOpenResult;

   unsigned char lpszInFName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char lpszOutFName[KP_MAX_FNAME_LEN+1];

   bool bLtFl;
   int iInKptTbl;
   int iOutKptTbl;

   TvTexFile_tag *lpInFileObj;
   TvTexFile_tag *lpOutFileObj;

   KpChar iazWordBuf[KP_KWD_LEN+1];


   HRESULT GetChar(KpChar *piInCh);
   HRESULT PutChar(KpChar iOutCh);

   HRESULT PutWord(void);
   HRESULT ProcessWord(void);
   HRESULT PutCharProc(KpChar iOutCh);

public:
   TvTexChy_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bLtFlag, int iInTbl, int iOutTbl);
   ~TvTexChy_tag(void);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT Process(void);
};


#endif
