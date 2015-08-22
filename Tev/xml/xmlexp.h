// ==================================================
// xmlexp.h, former xmlspt.h
// extracts compounds to separate entries (for electronic browsing)
// definitions of main module


#ifndef xmlexp_included
#define xmlexp_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlExp_tag: public XmlOI2_tag
{
public:
   XmlExp_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlExp_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(int iLevel);
};


// --------------------------------------------------
extern XmlExp_tag *pXmlExp;

#endif
