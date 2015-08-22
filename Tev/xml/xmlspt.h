// ==================================================
// xmlspt.h, former vlzspt.h, obsolete, use xmlexp.h
// Dictionary XML file nodes splitter
// splits derivatives, compounds and collocations to different nodes
// definitions of main module
//


#ifndef xmlspt_included
#define xmlspt_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlSpt_tag: public XmlOI2_tag
{
   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

public:
   XmlSpt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlSpt_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(int iLevel);
};


// --------------------------------------------------
extern XmlSpt_tag *pXmlSpt;

#endif
