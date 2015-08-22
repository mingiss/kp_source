// -----------------------------------------
// iBsht.h
// el. knygø perþiûros programa
// koduota failø sistema
// paprasta failo paieðka viename hx indexe
//

#ifndef iBsht_included
#define iBsht_included

// ---------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// -----------------------------
class iBshFileSys : public KpFileSys
{
private:
   unsigned char m_lpszFtype[KP_MAX_FILE_LIN_WDT /* KP_MAX_FNAME_LEN */ + 1];
public:
   bool m_bGeckoShowFl;   // ar pradiná failà rodyti per xGecko (htm, etc.), jei ne – iðtraukti á Temp ir iðkviesti viewerá
   bool m_bXmlEncodeFl;   // ar failà analizuoti XML parseriu, jei ne – praleidþiam skaidriai (binariniai failai, paveikslai ir kt.)

// -----------------------
   iBshFileSys(const unsigned char *lpszFirstEntryFileName = IBSHT_FIRST_ENTRY);
   virtual ~iBshFileSys(void);

   HRESULT OpenFiles // atidaro archyvo failà m_lpInFileObj (jei IBSHT_ARCHIVE), atidaro buferiná iðvedimo failà m_lpInFileObj --> m_pResBuf
   (
      const unsigned char *lpszInFileName = null,
      XmlVersions iVersion = XM_VERS_XHTML, // XM_VERS_HTML401_TRANS,
      HRESULT KpInFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNew8File,
      HRESULT KpOutFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNewUniBFile
   ); // isijungia m_bSemBlocked semafora
      // KpFileFactory – kokiu þemo lygio formatu skaityti input failus – CreateNew8File ar CreateNewUniFile
   HRESULT CloseFiles(bool bCheckFileExist); // isijungia m_bSemBlocked semafora

   HRESULT ExtractFileType(); // iðtraukia m_lpszFtype ið m_lpszCurSearchKwd, nustato m_bGeckoShowFl

   HRESULT SearchForEntry
   (
      KpPubDlg *pDialogPtr,
      const unsigned char *lpszFileName = null,
      XmlO1 **pInFilePtr = NULL,
      unsigned char **pEntryImgPtr = NULL
   );       // ieðko einamojo lizdo/failo,
            // prieð tai galima nustatyti naujà m_lpszCurSearchKwd arba áraðyti m_lCurEntryId = -1, norint forsuoti atnaujinimà
            // jeigu nurodytas lpszKeyWord, tai tai padaro pats
            // isijungia m_bSemBlocked semafora
            // nustato archyvà á failo pradþià, perskaito failà á laikinà XmlNode (iðkvieèia ReadEntry()),
            // suformuoja HTML buferá pDialogPtr->m_pResBuf[] ir perkelia já á Gecko (iðkvieèia FormatEntry()),
            // laikinà XmlNode iðtrina
            // parametrai iðkvieèiant ið KpFileSys::CreateGeckoStream dvejetainiams objektams (m_bXmlEncodeFl == False):
            // pInFilePtr – skaitomo failo objektas, po panaudojimo reikia sunaikinti
            // pEntryImgPtr - skaitomo failo turinio buferis, po panaudojimo reikia sunaikinti

   HRESULT FormatEntry(XmlNode *pCurEntry, KpPubDlg *pDialogPtr); // outputs pCurEntry to m_lpOutFileObj // former CvtToRtf
            // paskaièiuoja zoominimo koeficientà pDialogPtr->m_iFact
            // pakoreguoja iðvedamo failo JavaScriptà ir stilius (pCurEntry->SetCtrls())
            // suformuoja HTML buferá pDialogPtr->m_pResBuf[] (pCurEntry->WriteNode())
            // iðkvieèia DisplayResult() ir pDialogPtr->RedrawWindow()

   HRESULT CvtIndexEntry(unsigned char *lpscKwd); // konvertuoja pai­kos frazµ pagal arksh indekso taisykles ¢ keiÍia '\\' ß '/'
};


#endif // #ifndef iBsht_included
