// ==================================================
// xmlg2t.h, former lvzg2t.h
// LVZ SGML Tage to XML dictionary converter
// definitions of main module


#ifndef xmlg2t_included
#define xmlg2t_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlG2T: public XmlOI2
{
public:
   XmlG2T(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(bool bTrimSpaces);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlG2T *pXmlG2T;

#endif
