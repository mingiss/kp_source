// -----------------------------------------
// kpstapa.h fail� archyvas KpStArc
//


#ifndef kpstapa_included
#define kpstapa_included

#define KPSTAPA_GRP_PATH ((const unsigned char *)"files_obj")

struct KpStArcDirEntry
{
   unsigned char m_lpszFileName[KP_MAX_FNAME_LEN + 1]; // "" � katalogo galas
   long m_lFileStart;  
   long m_lFileLen;
};

class KpStArc
{
   HRESULT m_lhOpenResult;
   unsigned char m_lpszObjFileName[KP_MAX_FNAME_LEN + 1]; // .tev objekto failo vardas
   long m_lStartPos; // archyvo buferio prad�ios adresas faile m_lpszObjFileName 
   long m_lLength; // archyvo buferio ilgis
   long m_lDirEnd; // katalogo galas
   long m_lContentsStart; // fail� turini� prad�ia

//    m_lStartPos --------------> +--------------------------------------------------------+
//                                | katalogas, KpStArcDirEntry �ra�ai, auga pirmyn         |
//    m_lDirEnd ----------------> +--------------------------------------------------------+
//                                | ... laisva vieta                                       |
//    m_lContentsStart ---------> +--------------------------------------------------------+
//                                | fail� turini� sritis, auga dekrementi�kai, kaip stekas |
//    m_lStartPos + m_lLength --> +--------------------------------------------------------+
//    
   
public:
   KpStArc(const unsigned char *lpszObjFileName, long lStartPos, long lLength); // po konstruktoriaus b�tinai reikia OpenArc() arba FormatArc()
   HRESULT GetOpenResult(void); // gr��ina m_lhOpenResult
   
   HRESULT FormatArc(void); // sukuria nauj� archyv� � i�trina archyvo srit� ir u�pildo pointerius
   HRESULT LookupArc(void); // atidaro egzistuojant� archyv� � perskaito archyvo katalog� ir u�pildo pointerius m_lDirEnd ir m_lContentsStart

   HRESULT AppendFolder(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath);   // prideda pakatalogio lpszSrcPath failus prie archyvo, 
                                                                                                // i� fail� keli� atima prie�d�l� lpszBasePath, paprastai "files_obj"
                                                                                                // numeta ir sle�� po lpszBasePath  
   HRESULT AppendFile(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath); // prideda fail� lpszSrcPath prie archyvo, 
                                                                                            // failo keliui numeta prie�d�l� lpszBasePath, paprastai "files_obj
                                                                                            // numeta ir sle�� po lpszBasePath  
   HRESULT ExtractFiles(const unsigned char *lpszBasePath); // i�traukia archyvo failus ir �ra�o � katalog� lpszBasePath

   HRESULT DelFiles(const unsigned char *lpszBasePath); // i�trina failus kataloge lpszBasePath pagal archyvo kataloge esan�ius fail� pavadinim� s�ra��
};


#endif
