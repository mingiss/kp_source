// ==================================================
// tvxmlrcr.h
// XML referencies corrector
// definitions of main module


#ifndef tvxmlrcr_included
#define tvxmlrcr_included


// --------------------------------------------------
class TvXmlRcr_tag: public XmlO2_tag
{
public:
   TvXmlRcr_tag(const unsigned char **plpszInFnames, int iNumOfInFiles, const unsigned char *lpszOutFname /* , long lMaxSeIxInit */);
                           // plpszInFnames[0] - main input file
                           // plpszInFnames[1..iNumOfInFiles-1] - additional files for references
   ~TvXmlRcr_tag(void);

   HRESULT Process(void);

};


// --------------------------------------------------
#if FALSE
class TvXmlFmse_tag: public XmlO2_tag
{
public:
   TvXmlFmse_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~TvXmlFmse_tag(void);

   HRESULT Process(long *plMaxSe);     // find max value of se index

};
#endif

#endif
