// ==================================================
// xmlrpt.h
// XML tag extractor
// definitions of main module


#ifndef xmlrpt_included
#define xmlrpt_included


// --------------------------------------------------
// #define RP_OUT_FILE_UTF8
#define RP_CODE_TABLE TV_MAIN_SGM_CTBL // Windows lithuanian accented

#define RP_MAX_TAGS 20


// --------------------------------------------------
class XmlRpt_tag
{
   unsigned char lpszInFName[KP_MAX_FNAME_LEN+1];
   unsigned char lpszOutFName[KP_MAX_FNAME_LEN+1];

   XmlO1_tag *lpInFileObj;

#ifdef RP_OUT_FILE_UTF8
   UcFile_tag *lpOutFile;
#else
   TvXml8File_tag *lpOutFile;
#endif

   HRESULT lhOpenResult;

   KpChar aiXmlTgArr[RP_MAX_TAGS+1][RP_MAX_TAGS+1]; // aiXmlTgArr[ii] - all tags of ii'th tab position
   KpChar aiValSavArr[RP_MAX_TAGS+1][KP_MAX_FILE_LIN_LEN+1]; // array of current tag values
   KpChar aiValSavPtr[RP_MAX_TAGS+1];  // pointers to aiValSavArr[]
   KpChar aiPrevValSavArr[RP_MAX_TAGS+1][KP_MAX_FILE_LIN_LEN+1]; // array of previous saved ambiguous tag group
                                                              //    values for further output with new rest tags
   KpChar aiXmlDeclArr[RP_MAX_TAGS+1];  // array of declined tags - tags, which contents are not processed

   long lEntryId;

   bool bFirstFl;
   int iTabPos;
   int iTabPosSav;
   int iNumOfTabPos;

public:
   XmlRpt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlRpt_tag();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT DeclineXmlTag(const unsigned char *lpszTag); // put parameter like "-eg" to declined tags array aiXmlDeclArr
   HRESULT AcceptXmlTag(const unsigned char *lpszTag);  // put parameters "tw" or "hw/v/scw" to aiXmlTgArr

   HRESULT PutSeId(void);
   HRESULT PutChar(KpChar iInChar);
   HRESULT PutStrInt(const KpChar *iazOutStr);
   HRESULT ProcessPrevVals(void);
   HRESULT Process(void);

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};





#endif
