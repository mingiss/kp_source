// ==================================================
// tvxmlecm.h
// endings and suffixes skipper for searching in flex. languages
// endings joining utility definitions


#ifndef tvxmlecm_included
#define tvxmlecm_included


// --------------------------------------------------
#define TV_XE_INV_1_COL       40
#define TV_XE_INV_2_COL       20
#define TV_XE_INV_3_COL       20

#define TV_XE_COL_WDT         26
#define TV_XE_UNREG_COL_WDT   39
#define TV_XE_GRGR_COL_WDT    2

// prefix for generated *.CPP file name, all languages in theyr order,
// former TV_XE_CFNAM
#define KP_LNG_CFNAM  ("tvxmle")    

// --------------------------------------------------
class TvXmlEcm_tag
{
   FILE *lpOutFile;

   HRESULT lhOpenResult;

   unsigned int uiFId;     // language igentifier
   unsigned char lpszFName[KP_MAX_FNAME_LEN+1]; // file name

   const unsigned char **plpszaTGrFrm;
   const unsigned char *lpszTMnFrm;
   const unsigned char *lpszFrms;
   const unsigned char **plpszaPrefixTbl;
   const unsigned char **plpszaESkpTbl;
   const unsigned char **plpszaURgFrms;

   HRESULT CheckTables(void);

   HRESULT PutHat(void);

   HRESULT PutFullPrefixTbl(unsigned char *lpszFileName);
   HRESULT PutPrefixTbl(unsigned char *lpszFileName);

   HRESULT PutInvertedESkpTbl(unsigned char *lpszFileName);
   HRESULT PutCompactedESkpTbl(unsigned char *lpszFileName);

   HRESULT PutInvertedURgFrmsTbl(unsigned char *lpszFileName);
   HRESULT PutURgFrmsTbl(unsigned char *lpszFileName);

public:
   TvXmlEcm_tag
   (
      const unsigned int uiFileIdn,
      const unsigned char **plpszaToGrForm,
      const unsigned char *lpszToMainForm,
      const unsigned char *lpszForms,
      const unsigned char **plpszaPrefixTable,
      const unsigned char **plpszaEndSkipTable,
      const unsigned char **plpszaUnRegForms
   );                         // lpszFileName - secondary *.cpp file name to generate;
                              // for description of tables look file tvxmlel.cpp

   ~TvXmlEcm_tag();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT Process(void);

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};


#endif
