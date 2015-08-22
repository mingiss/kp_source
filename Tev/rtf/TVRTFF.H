// ==================================================
// tvrtff.h
// RTF file formatting according to C formatting rules
// definitions of main module


#ifndef tvrtff_included
#define tvrtff_included


// --------------------------------------------------
class TvRtfFm_tag
{
   TvRtfI_tag *lpRtfInputFileObj;
   TvRtfO_tag *lpRtfOutputFileObj;

   HRESULT PurgeInputFile(void);
   HRESULT CloseOutputFile(bool bCheckFileExist);

   HRESULT FormatRtf(void);      // Converts input RTF file to C-style indented RTF
                                 //    text. Files must be opened, does not close files.

   HRESULT FillStr(unsigned char *lpszOutStr, const unsigned char *lpszFillStr, const int iCount);
                                 // Fills string with repeated iCount times string
                                 //    lpszFillStr. Does not test any memory limits.
public:
   TvRtfFm_tag();
   ~TvRtfFm_tag();

   HRESULT Process(const unsigned char *lpszInfname, const unsigned char *lpszOutfname);
                                 // Main class access point
};


#endif
