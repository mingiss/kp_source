// -----------------------------------------
// kpstapa.h failø archyvas KpStArc
//


#ifndef kpstapa_included
#define kpstapa_included

#define KPSTAPA_GRP_PATH ((const unsigned char *)"files_obj")

struct KpStArcDirEntry
{
   unsigned char m_lpszFileName[KP_MAX_FNAME_LEN + 1]; // "" – katalogo galas
   long m_lFileStart;  
   long m_lFileLen;
};

class KpStArc
{
   HRESULT m_lhOpenResult;
   unsigned char m_lpszObjFileName[KP_MAX_FNAME_LEN + 1]; // .tev objekto failo vardas
   long m_lStartPos; // archyvo buferio pradþios adresas faile m_lpszObjFileName 
   long m_lLength; // archyvo buferio ilgis
   long m_lDirEnd; // katalogo galas
   long m_lContentsStart; // failø turiniø pradþia

//    m_lStartPos --------------> +--------------------------------------------------------+
//                                | katalogas, KpStArcDirEntry áraðai, auga pirmyn         |
//    m_lDirEnd ----------------> +--------------------------------------------------------+
//                                | ... laisva vieta                                       |
//    m_lContentsStart ---------> +--------------------------------------------------------+
//                                | failø turiniø sritis, auga dekrementiðkai, kaip stekas |
//    m_lStartPos + m_lLength --> +--------------------------------------------------------+
//    
   
public:
   KpStArc(const unsigned char *lpszObjFileName, long lStartPos, long lLength); // po konstruktoriaus bûtinai reikia OpenArc() arba FormatArc()
   HRESULT GetOpenResult(void); // gràþina m_lhOpenResult
   
   HRESULT FormatArc(void); // sukuria naujà archyvà – iðtrina archyvo sritá ir uþpildo pointerius
   HRESULT LookupArc(void); // atidaro egzistuojantá archyvà – perskaito archyvo katalogà ir uþpildo pointerius m_lDirEnd ir m_lContentsStart

   HRESULT AppendFolder(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath);   // prideda pakatalogio lpszSrcPath failus prie archyvo, 
                                                                                                // ið failø keliø atima prieðdëlá lpszBasePath, paprastai "files_obj"
                                                                                                // numeta ir sleðà po lpszBasePath  
   HRESULT AppendFile(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath); // prideda failà lpszSrcPath prie archyvo, 
                                                                                            // failo keliui numeta prieðdëlá lpszBasePath, paprastai "files_obj
                                                                                            // numeta ir sleðà po lpszBasePath  
   HRESULT ExtractFiles(const unsigned char *lpszBasePath); // iðtraukia archyvo failus ir áraðo á katalogà lpszBasePath

   HRESULT DelFiles(const unsigned char *lpszBasePath); // iðtrina failus kataloge lpszBasePath pagal archyvo kataloge esanèius failø pavadinimø sàraðà
};


#endif
