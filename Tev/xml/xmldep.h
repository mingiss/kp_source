// ==================================================
// xmldep.h
// deleting empty tags from XML dictionary
// definitions of main module
//


#ifndef xmldep_included
#define xmldep_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif
                 
                 
// --------------------------------------------------
class XmlDep_tag: public XmlOI2_tag
{         
public:   
   XmlDep_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlDep_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(void);
};


// --------------------------------------------------
extern XmlDep_tag *pXmlDep;

#endif
