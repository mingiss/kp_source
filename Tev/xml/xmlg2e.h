// ==================================================
// xmlg2e.h
// VLTT SGML CTBL-80 to CTBL-43 converter
// definitions of main module
//

#ifndef xmlg2e_included
#define xmlg2e_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlG2E_tag: public XmlOI2_tag
{
public:
   XmlG2E_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlG2E_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(void);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlG2E_tag *pXmlG2E;

#endif
