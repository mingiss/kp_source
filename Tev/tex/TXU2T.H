// ==================================================
// txtu2t.h
// converting Unicode TEX file to plain text ASCII file with TEX-like spec. character encoding
// definitions of main module
//


#ifndef txtu2t_included
#define txtu2t_included

// --------------------------------------------------
class TxU2T_tag
{
   HRESULT lhOpenResult;

   unsigned char lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char lpszOutFileName[KP_MAX_FNAME_LEN+1];

   UcFile_tag *lpInFileObj;
   ofstream *lpOutFileObj;

public:
   TxU2T_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~TxU2T_tag(void);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
   HRESULT Process(void);
};


// --------------------------------------------------
extern TxU2T_tag *pTxU2T;

#endif
