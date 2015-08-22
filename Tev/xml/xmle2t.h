// ==================================================
// xmle2t.h
// VLTT SGML CTBL-43 to XMLT converter
// definitions of main module
//

#ifndef xmle2t_included
#define xmle2t_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlE2T_tag: public XmlOI2_tag
{
public:
   XmlE2T_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlE2T_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFilesLocal(bool bCheckFileExist);

   HRESULT Process(bool bInsDelim);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlE2T_tag *pXmlE2T;

#endif
