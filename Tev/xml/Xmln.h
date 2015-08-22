// ==================================================
// xmln.h
// XML dictionary entry node
//


#ifndef xmln_included
#define xmln_included


//----------------------------
// indent steps
#define XN_POS_PER_INDENT 3

// tabulators for Tagged output
#define XN_TABS_PER_COL 20
#define XN_POS_PER_TAB 3      // 2.5
#define XN_POS_PER_COL 50
#define XN_VAL_START_TAB 5    // tab position for text value following tag text

#define XMLN_RICH_BUF_LEN 200000 // length of memory buffer used to format RTF text for output (LZDSH)

// -------------------------------------------
// tagø perdarymui á dinaminius, santykinius nuo m_iFirstTag
// naudojau absoliuèius/statiðkus:
//    XC_FirstDictTag            --> m_iFirstTag                                 xmln.cpp, xmlnr.cpp, (xmlnxo.cpp)
//    XC_LastDictTag             --> m_iLastTag, CheckLastTag(), GetLastTag()    xmln.cpp, (xmlnxo.cpp)
//    iFirstTag                  --> m_iFirstTag, metodø parametrus naikinti     xmln.cpp, xmlnx.cpp, kas nustato?
//    iLastTag                   --> m_iLastTag, CheckLastTag(), GetLastTag()    xmln.cpp, xmlnx.cpp
//    plpszaXmlttDictTags[]      --> m_plpszaTags                                xmln.cpp
//    plpszaXmlttDictTagsFull[]  --> m_plpszaTags                                xmln.cpp
//   (plpszaSgmDictTags[])       --> m_plpszaTags                                xmln.cpp
//    lpszXmlTagDelimiters[][]   --> GetTagDelimiter()                           xmln.cpp, xmlnr.cpp, xmlnx.cpp, (xmlnxo.cpp)
//    baLevelTags[]              --> TestTagLevel()                              xmln.cpp
//    iaXml2Tex[]                --> GetXml2Tex()                                xmlnx.cpp, (xmlnxo.cpp)
//    plpszaDictTagOutNames[] (plpszaTagOutNames[])  --> GetTagOutName()                             xmlnx.cpp, (xmlnxo.cpp)
//    iaTagFonts[]               --> GetTagFont()                                xmlnr.cpp
//    uiazXmlParGrTags[]         --> GetXmlParGrTag()                            xmlnx.cpp
//    baXmlDictTagsFreeText[]    --> TestTagFreeText()                           xmlnx.cpp
//    hNodeBitmaps[]             --> GetNodeBitmap()                             xmln.cpp
// TODO dar patikrint:
//   (XC_...) priskyrimus patikrint, lyginimø nereikia                           xmln.cpp, xmlnl.cpp, xmlnr.cpp, xmlnx.cpp, (xmlnxo.cpp)
//    m_iPrevOutTag priskiriu absoliuèias XC_... reikðmes, turëtø kaþkaip priklausyti nuo failo tipo (XMLT/HTML)
//


// ==================================== class for XML tag parameters
class XmlNode : public KpTreeEntry
{
// HRESULT lhOpenResult; // moved to KpTreeEntry::m_lhOpenResult

// XmlNode *pFirstChild; // moved to KpTreeEntry::m_pFirstChild
// XmlNode *pPrevBrother; // moved to KpTreeEntry::m_pPrevBrother
// XmlNode *pNextBrother; // moved to KpTreeEntry::m_pNextBrother
// XmlNode *pFather; // moved to KpTreeEntry::m_pFather

// ---------------------------
// TODO: kelti i RecListEntry_tag::m_lpRecord

   KpChar m_iNodeTag;

   const unsigned char * const *m_plpszaTags; // pointeris á tagø vardø masyvà, pvz., plpszaXmlttDictTagsFull[]
                                       // gali bûti dinamiðkai besipildantis skaitant failà
                                       // const, nes XmlNode nekeièia, gali pasikeisti tik ið iðorës, failo skaitymo metu
   KpChar m_iFirstTag; // simbolio kodas, atitinkantis m_plpszaTags[0]
   KpChar m_iLastTag; // surandamas dinamiðkai pagal dabartiná m_plpszaTags[] turiná, þr. GetLastTag()

   XmlTagPars *m_pTagPars;   // tag parameter

   KpChar *m_lpaizContents;   // text contents - null-terminated KpChar string,
                              //    only for iNodeTag==XC_Text, no subtags allowed
                              // gal kelt á KpTreeEntry::m_lpRecord?

   XmlTagPars *m_pContPars; // structured contents of tag <style>

   unsigned char *m_lpszNodeIndent;  // cumulative indent of current node, only spaces, no \n in top of the strig

   KpChar m_iPrevOutTag;  // previous tag for RTF/TEX output
// -----------------------------


// constructors
   void Constructor
   (
      KpChar iTag, const XmlTagPars *pPars,
      const KpChar *lpazTextContents,  const XmlTagPars *pContPars,
      const unsigned char *lpszIndent, // XmlNode *pFath,
      KpChar iFirstTag, const unsigned char * const *plpszaTags    // plpszaTags[] masyvas nestatinis, pvz., HTML atveju nauji tagai pildosi
   );                                                       // dinamiðkai skaitant failà,
                                                            // paskutinio tago ieðkoti kiekvienà kartà ið naujo - GetLastTag()
public:
   XmlNode
   (
      KpChar iTag, const XmlTagPars *pPars,
      const KpChar *lpazTextContents,  const XmlTagPars *pContPars,
      const unsigned char *lpszIndent,
      KpChar iFirstTag, const unsigned char * const *plpszaTags,
      XmlNode *pFath
   );
                   // pPars, lpazTextContents and lpszIndent can be deleted after XmlNode()
                   // pPars, lpazTextContents and lpszIndent can be NULL

// copy constructors
private:
   void Constructor(/* const */ XmlNode *pSource, XmlNode *pFath, int iLevel, const XmlNode *pCurGrandFather);
                  // iLevel - copy only nodes visible in that level (specified in m_iStatus)
                  // iLevel == -1 - copy nodes of all levels
                  // pCurGrandFather == pSource in initial call, copied through recursion calls, this node will be copied independing on level
                  // pFath - current father in recursion calls, NULL for copying from root entry
public:
   XmlNode(/* const */ XmlNode *pSource, XmlNode *pFath);
   XmlNode(/* const */ XmlNode *pSource, XmlNode *pFath, int iLevel, const XmlNode *pCurGrandFather);
                  // copy constructor, extracting only nodes, visible in certain level,
                  //    corresponding to m_iStatus flags
                  // pCurGrandFather should be set equal to pSource (to keep track to the root node through recursion)
                  // does not copy brothers of *pSource (*pCurGrandFather)

   virtual ~XmlNode(); // removes all childs with subchilds and lpazContents

// HRESULT GetOpenResult(void);  // Returns value of lhOpenResult - object creation error code

   HRESULT GetNodeTag(KpChar *piTag) /* const */; // iðkvieèia CheckLastTag(), ji ne const
   HRESULT SetNodeTag(KpChar iTag);

   const unsigned char * const *GetTagsArrPtr(void) const {return(m_plpszaTags);}
   KpChar GetFirstTag(void) const {return(m_iFirstTag);}

   KpChar GetLastTag(void);   // skanuoja m_plpszaTags[] ir uþpildo m_iLastTag;
                              // m_iFirstTag jau turi bûti nustatytas, o m_iLastTag turi bûti didesnis uþ m_iFirstTag -
                              // rodyti á m_plpszaTags[] elementà
   bool CheckLastTag(KpChar iTag);  // dinamiðkai tikrina, ar iTag neiðlipa uþ m_iLastTag; False - neiðlipa (iTag >= m_iLastTag)
                                    // jei iðlipa uþ dabartinës m_iLastTag reikðmës, iðkvieèia GetLastTag()

   HRESULT GetTagParsPtr(XmlTagPars **ppTagPars) const; // gràþina m_pTagPars reikðmæ
   HRESULT SetTagParsPtr(XmlTagPars *pTagParsPar); // nustato m_pTagPars reikðmæ, iðtrina prieð tai buvusius parametrus
   HRESULT SetTagParsPtrSimple(XmlTagPars *pTagParsPar); // prieð tai buvusiø parametrø *m_pTagPars netrina,
      // tiesiog uþkloja naujà pointerá ant virðaus, naudojamas, kai koreguojami dabartiniai mazgo parametrai -
      // pvz., iðtrinamas pirmas ið parametrø ir reikia tiesiog paslinkti pointerá
      // *pTagParsPar po gráþimo trinti negalima

// HRESULT GetFather(XmlNode **ppFath);  // moved to KpTreeEntry
// HRESULT SetFather0(XmlNode *pFath);   // moved to KpTreeEntry
// HRESULT SetFather(XmlNode *pFath);    // moved to KpTreeEntry

// HRESULT GetFirstChild(XmlNode **ppChild); // moved to KpTreeEntry
// HRESULT SetFirstChild(XmlNode *pChild); // moved to KpTreeEntry

// HRESULT ConnectChild(XmlNode *pChild); // moved to KpTreeEntry

// HRESULT GetPrevBrother(XmlNode **ppPrevBr); // moved to KpTreeEntry
// HRESULT SetPrevBrother(XmlNode *pPrevBr); // moved to KpTreeEntry

// HRESULT GetNextBrother(XmlNode **ppNextBr); // moved to KpTreeEntry
// HRESULT SetNextBrother(XmlNode *pNextBr); // moved to KpTreeEntry

// HRESULT ConnectBrother(XmlNode *pNextBr); // moved to KpTreeEntry

   HRESULT CreateTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText, XmlNode **pTextNodePtr); // used in AppendChild()
   HRESULT CreateTextTag(KpChar iTag, XmlTagPars *pTagPars, const unsigned char *lpszText, int iCtbl, XmlNode **pTextNodePtr);

// HRESULT InsertChild(XmlNode *pChild); // moved to KpTreeEntry
   HRESULT InsertTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText);
   HRESULT InsertTextTag(KpChar iTag, XmlTagPars *pTagPars, const unsigned char *lpszText, int iCtbl);
                                             // inserts child - simple text tag,
                                             //    uses CreateTextTag(), InsertChild()
// HRESULT AppendChild(XmlNode *pChild); // moved to KpTreeEntry
   HRESULT AppendTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText);
   HRESULT AppendTextTag(KpChar iTag, XmlTagPars *pTagPars, const unsigned char *lpszText, int iCtbl);
   HRESULT AppendTextTag(KpChar iTag, XmlTagPars *pTagPars, const char *lpszText, int iCtbl)
               { return(AppendTextTag(iTag, pTagPars, (const unsigned char *)lpszText, iCtbl)); }
                                             // appends child - simple text tag,
                                             //    uses CreateTextTag(), AppendChild()
   HRESULT CreateNewChild(KpChar iNodeTag, XmlTagPars *pTagPars, XmlNode **ppNewChild);
                                             // appends new child after the LAST cild
                                             //    pTagPars can be deleted after CreateNewChild()

   HRESULT SetContents(const KpChar *lpazTextBuf); // sukuria *m_lpaizContents
                                             // lpazTextBuf can be deleted after SetContents()
   HRESULT GetContentsPtr(KpChar **lppazTextPtr) const; // gràþina m_lpaizContents reikðmæ
                     // *lppazTextPtr naikinti negalima

   HRESULT ExtractContents(KpChar **lppazTextPtr) /* const */;
                     // gràþina pirmo XL_Text reikðmës pointerá – vaiko m_lpaizContents reikðmæ;
                     // klaidos praneðimo neiðveda, jei neranda, gràþina NULL
                     // *lppazTextPtr naikinti negalima

   HRESULT ExtractSubnodeContents(KpChar iTag, KpChar **lppazTextPtr) /* const */;
                     // gràþina pirmo vaiko iTag reikðmæ (iðkvieèia SearchSubNode() ir ExtractContents())
                     // *lppazTextPtr naikinti negalima

   HRESULT ExtractSubnodeContentsStr(KpChar iTag, unsigned char **plpszTextBufPtr, int iCtbl = TV_MAIN_CTBL) /* const */;
                     // gràþina pirmo vaiko iTag char reikðmæ – sukuria buferá *plpszTextBufPtr,
                     // *plpszTextBufPtr po panaudojimo reikia trint
                     // (iðkvieèia ExtractSubnodeContents() ir KptStrDecode())

   HRESULT GetContParsPtr(XmlTagPars **ppContPars) const; // gràþina m_pContPars reikðmæ

   HRESULT SetIndent(const unsigned char *plpszIndentStrBuf);
                                             // plpszIndentStrBuf can be deleted after successfull SetIndent()
   HRESULT GetIndentPtr(unsigned char **pplpszIndentStrPtr) const;

   HRESULT ReduceIndent(void);               // reduces indent for brothers and children
   HRESULT IncreaseIndent(void);             // increases indent for brothers and children
   HRESULT ReduceIndentNested(void);         // reduces indent for children only

   HRESULT SetTagHeadings(int iNumOfParStyles, HWND hParent); // main external entry; iðkeltas á KpRichEd.cpp
private:
   HRESULT SetTagHeadings_loop(int iNumOfParStyles, HWND hRtfWnd); // local recursive function used by SetTagHeadings
public:         // fills text headings KpTreeEntry::m_lpRecord for node tags
                // hRtfWnd - invisible fictive RTF window used to form RTF images

   HRESULT InitNodeStatus(void); // redefinition of KpTreeEntry::InitNodeStatus
   HRESULT TestGroupChildren(bool *bHasGroupChildren); // former TestVisibleChildren() // tests whether node has children to be displayed in high level (group tag nodes)

   HRESULT ExtractSubNodes(XmlNode **ppChildCatsBr, KpChar iSubTag);
                                             // extracts categories or meaning tags from node
                                             // *ppChildCatsBr must be NULL on entering
                                             // possible iSubTag values:
                                             //    XC_CtgGroup (for all categories and meanings)
                                             //    XC_TranslGroup
                                             //    XC_TrWord

   HRESULT SkipBrothersToTag(XmlNode **ppFirstOccurence, KpChar iTag);
                                             // searches sequentially brothers up to
                                             //    iTag-brother; NULL means no iTag-brother
                                             //    found

   HRESULT ClearAccents(void); // converts text contents to unaccented letters

   HRESULT RenumCtgMng(void); // pernumeruoja kategorijas ir reiksmes po mazgu ismetimo
   HRESULT UpCtgMng(void);    // isnaikina pavienes kategorijas/reiksmes (uzkelia i aukstesni lygmeni)

// ------------------------------------------------
   HRESULT ReadNode(XmlI *lpInFile);     // create next child
   HRESULT ReadText(XmlI *lpInFile);     // create next child XC_Text with free text

   HRESULT WriteNode(XmlI *lpOutFile);   // output node and all brothers to lpOutFile
   HRESULT PutTag(KpChar iTag, XmlTagPars *pTagParsObj, XmlI *lpOutFileObj);
                                         // puts tag with necessary indent, does not touch the tag stack

// ------------------------------------------------
   HRESULT ReadNode(XmlO1 *lpInFile);
   HRESULT ReadText(XmlO1 *lpInFile);

   HRESULT WriteNode(XmlO1 *lpOutFile);
   HRESULT PutTag(KpChar iTag, XmlTagPars *pTagParsObj, XmlO1 *lpOutFileObj);
   HRESULT PutKpStr(KpChar *iaStr, XmlO1 *lpOutFile);

// ------------------------------------------------
// splits node to several nodes for each embedded compound, derivative or structure,
//    writes them to output file, used before node inverting or for e-dict's
   HRESULT WriteEmbeddedCompounds(KpChar *lpaiBasePtr, XmlI *lpOutFile, long *plEntryId, bool bOutFl);
         // plEntryId - pointer to entries ID counter
         // if bOutFl==True, writes "this" node to lpOutFile (for recursions)

   HRESULT WriteGroupVariants(XmlNode *pMainNode, XmlI *lpOutFile, long *plEntryId, bool *pbWritten, bool bEncloseToSe);
         // writes node repeating with all variants of sequential group af headword variants
         // pMainNode - pointer to whole node for output
         // pbWritten - should be False on entering
         // bEncloseToSe - pMainNode has no enveloping <se> tags, must be enclosed to <se> node as a subnode

   HRESULT WriteNodeWithSubNode(XmlNode *pCatSubNode, XmlI *lpOutFile);

   HRESULT WriteNodeDupCats(XmlI *lpOutFile);

   HRESULT WriteNodeDupTrGroups(XmlI *lpOutFile);

   HRESULT WriteNodeDupTrWords(XmlI *lpOutFile);

// ------------------------------------------------
// skips control sequences "$..." in delimiters
   HRESULT SkipDelimCtrlChars(unsigned char **ppcDelimPtr);
// converts delimiter string to KpChar string, iazOutBuf[KP_MAX_FILE_LIN_LEN+1]
   HRESULT GenXmlDelimStr(KpChar *iazOutBuf, const unsigned char *lpszFormatStr, XmlVersions iXmlVers);

   HRESULT CreateDelimNode(XmlNode **ppDelimNodePtr, KpChar iCurTag, KpChar iNextTag, XmlTagPars *pTagPars,
//    KpChar iFirstTag, KpChar iLastTag,
      XmlVersions iXmlVers); // internal function used in InsertDelimiters
   HRESULT InsertDelimiters(// KpChar iFirstTag, KpChar iLastTag,
      XmlVersions iXmlVers); // inserts XC_PunctMark tag nodes, corresponding to current style

// supersedes format specifiers with real parameters - sprintf()
// lpszOutBuf must be not shorter than [KP_MAX_FILE_LIN_LEN+1]
   HRESULT ExpParDelimStr(unsigned char *lpszOutBuf, const unsigned char *lpszInFormDelimStr, KpChar iCurTag, XmlTagPars *pTagPars);

// ---------------------------- RTF
   HRESULT GenRtfFontAttr(/* TvRtfO *lpOutFile, */ unsigned char *lpszOutBuf, KPS_FontStyles iFontStyle);
                                 // lpszOutBuf[KP_MAX_FILE_LIN_LEN+1]
   HRESULT GenRtfFontAttrStr(TvRtfO *lpOutFile, KpChar *lpiaOutBuf, const unsigned char *lpszFormatStr, bool *pbParStyleFlg, int iNumOfParStyles, int iBaseDepth);
                                 // lpiaOutBuf[KP_MAX_FILE_LIN_LEN+1]
                                 // lpszFormatStr - formato eilute is lpszXmlTagDelimiters[][]
                                 // *pbParStyleFlg - paragraph style flag - no closing parentheses needed
                                 // iBaseDepth - base depth level of RTF fields
   HRESULT PutRtfFontAttr(TvRtfO *lpOutFile, KPS_FontStyles iFontStyle);
   HRESULT PutRtfIntStr(TvRtfO *lpOutFile, const KpChar *iaOutStr, bool *pbParStyleFlg, int iNumOfParStyles, int iBaseDepth);
   HRESULT WriteRtf(TvRtfO *lpOutFile, KpChar iFatherTag,
      /* KpChar iFirstTag, */ KpChar iPrevTag, int iNumOfParStyles, int iBaseDepth);
                                 // output node as RTF file segment
                                 // iBaseDepth - base depth level of RTF fields

// ---------------------------- TeX
// bTagFormat - for tagged output format
// *piCurCharPos - internal buffer for current char. pos. processing
// *piCurCharPos must be cleared before call of WriteTex()
// iLastWordPos - position for \lastwordinpar
// iNumOfChars - count of characters in whole node (paragtraph), calculated by CountCharactersTex()
// iLastWordRest - parameter for \lastwordinpar by output of C_sbreak, usually LAST_WORD_LEN

   HRESULT PutTexChar(TvTexFile *lpOutFile, KpChar iOutChar, KpChar *piLastChar, bool bTestLastChar, KpChar iFatherTag, int *piCurCharPos, int iLastWordPos, int iLastWordRest, KpChar *piDelayedChar
                     // , KpChar iFirstTag, KpChar iLastTag
                     );                   // bTestLastChar==True  - test *piLastChar and iOutChar for duplicated punctuators
                                 // piDelayedChar - pointer to place character for later output
                                 // if piDelayedChar==NULL, ordinary character will be output immediatelly
   HRESULT PutTexIntStr(TvTexFile *lpOutFile, const KpChar *iaOutStr, KpChar *piLastChar, KpChar iFatherTag, XmlNode *pnCurNode, bool bTagFormat, int *piCurCharPos, int iLastWordPos, int iNumOfChars, int iLastWordRest
                        // , KpChar iFirstTag, KpChar iLastTag
                        ); // former PutTexIntStr
   HRESULT MoveTwo(TvTexFile *lpOutFile, KpChar *piLastChar, KpChar iFatherTag, int *piCurCharPos, int iLastWordPos, int iLastWordRest,
                        // KpChar iFirstTag, KpChar iLastTag,
                        bool test_last_char); // pagalbine PutTexIntStr() funkcija

   HRESULT FlushSpaces(TvTexFile *lpOutFile, bool bSkipLineOnSpace, KpChar *piLastChar, int iLastWordRest, int *piCurCharPos, int iLastWordPos);

   HRESULT CloseField(TvTexFile *lpOutFile, bool bFlushFl, bool bSkipLineOnSpace, KpChar *piLastChar, int iLastWordRest, int *piCurCharPos, int iLastWordPos);

   HRESULT GenTexDelimStr(KpChar *iazOutBuf, const unsigned char *lpszFormatStr); // iazOutBuf[KP_MAX_FILE_LIN_LEN+1]

// delimiter string for WriteTex()
   HRESULT WriteTexDelim(TvTexFile *lpOutFile, const unsigned char *lpszDelimStr, KpChar *piLastChar, int *piCurCharPos, int iLastWordPos, int iLastWordRest, int iNumOfChars
                        // , KpChar iFirstTag, KpChar iLastTag
                        );

// destroys m_iPrevOutTag
   HRESULT WriteTex(TvTexFile *lpOutFile, int *piCurCharPos, int iLastWordPos, int iLastWordRest, int iNumOfChars, KpChar iFatherTag,
                        // KpChar iFirstTag, KpChar iLastTag,
                        KpChar iPrevTag, KpChar *piLastChar, bool bTagFormat);

// returns count of characters in node (*piNumOfChars)
// *piNumOfChars must be cleared before call of CountCharacters()
// destroys m_iPrevOutTag
   HRESULT CountCharactersTex(int *piNumOfChars, /* KpChar iFirstTag, */ KpChar iPrevTag, bool bTagFormat);

// returns position of first char of last word where \lastwordinpar must be inserted
//    (*piLastWordPos) and rest length of the last word after LAST_WORD_LEN - parameter for
//    \lastwordinpar macro (*piLastWordRest)
// iNumOfChars - count of chars in node calculated previuosly using CountCharacters()
// *piCurCharPos - internal buffer for current char. pos. processing
// *piLastWordPos and *piCurCharPos must be cleared before call of GetLastWordPos()
// *piLastWordRest must be initialized to LAST_WORD_LEN before call of GetLastWordPos()
// destroys m_iPrevOutTag
   HRESULT GetLastWordPosTex(int *piLastWordPos, int *piLastWordRest, int *piCurCharPos, int iNumOfChars,
               /* KpChar iFirstTag, */ KpChar iPrevTag, bool bTagFormat);
// \lastwordinpar paskutineje pastraipos eiluteje palieka nemaziau, kaip <n> zodzio "cccccc"
//    raidziu; galimi variantai tokie:
//    \lastwordinpar{n}{aaaaaa bbbbbb cccccc~dddddd~eeeeee}
//    \lastwordinpar{n}{aaaaaa bbbbbb cccccc}
//    \lastwordinpar{n}{cccccc}

// counts length of delimiter string taking into account control sequences "$..."
   int DelimStrLenTex(const unsigned char *lpszDelimPtr, KpChar iCurTag, XmlTagPars *pTagPars);

// counts length of tag contents string taking into account control sequences "$..."
   int XmlnKpStrLen(const KpChar *piValPtr);

// ----------------------------- HTML
   HRESULT CvtToBmps(const unsigned char *lpszInFileName, const unsigned char *lpszOutFileName, int *piBgrWdt = NULL, int *piBgrHgt = NULL);
// konvertuoja <img src="..."> ir <body background="..."> parametrø failø tipus á .bmp
// konvertuoja paèius failus á .bmp, katalogø kelius iðsitraukia ið lpszInFileName ir lpszOutFileName
// konvertavimui naudoja cvt_img.exe, kuris yra kopija ið ImageMagick convert.exe, turi bûti prieinamam kataloge
// *piBgrWdt ir *piBgrHgt uþpildo <body width="..." height="..."> reikðmëmis, jei ne NULL, þr. GetBgrDim()
// *piBgrWdt ir *piBgrHgt reikia iðvalyti prieð iðkvieèiant

   HRESULT GetBgrDim(int *piBgrWdt, int *piBgrHgt);
// *piBgrWdt ir *piBgrHgt uþpildo <body width="..." height="..."> reikðmëmis
// *piBgrWdt ir *piBgrHgt reikia iðvalyti prieð iðkvieèiant

   HRESULT Scale(int iFactor, KpChar iGrandFatherTag);
// perskaièiuoja visus <body width="..." height="..."> ir <img width="..." height="...">
// parametrams style iðkvieèia m_pParValuePar->ScaleStylePars()
// iFactor - koeficientas, padaugintas ið 1000

// ----------------------------
   HRESULT DelEmptyTags(void);
   HRESULT DelTags(KpChar iTag);    // deletes subnodes of certain tags
   HRESULT DelTagsByValue(KpChar iTag, const unsigned char *lpszValue, bool *pbFoundFl);
                     // *pbFoundFl must be False on entering to function
   HRESULT MapTags(KpChar iFromTag, KpChar iToTag);      // changes all tags iFromTag to iToTag

   HRESULT TestText(const KpChar *lpiazTestText, bool *pbTextPresent);
                     // test presence of text fragment lpiazTestText in node contents
                     // *pbTextPresent must be False on entering to function

   HRESULT SubstText(const KpChar *lpiazFromText, const KpChar *lpiazToText, bool bOnlyHw);
                                    // replaces occurencies of lpiazFromText in contents of
                                    //    the node to lpiazToText, lpiazToText can be NULL
                                    // if bOnlyHw==True replaces only <hw>-like fields,
                                    //    inserts additional '|' after inserted lpiazToText

   HRESULT DelCompDelim(void);

   HRESULT TestQuery(KpChar iSearchTag, unsigned char *lpszMinValue, unsigned char *lpszMaxValue, bool *pbFoundFl);
                     // tests, whether contents at least of one tag iSearchTag of the
                     // node are >=lpszMinValue and <=lpszMaxValue
                     // *pbFoundFl must be False on entering to function

   HRESULT SearchSubNode(KpChar iSearchTag, XmlNode **ppSubNode);
                     // searches node of tag iSearchTag
                     // *ppSubNode must be set to NULL on entering
                     // if not found, *ppSubNode will be returned unchanged - as NULL
                     // pradeda nuo paties this, ne nuo vaikø – randa ir jaunesnius brolius
   HRESULT SearchChildSubNode(KpChar iSearchTag, XmlNode **ppSubNode);
                     // pradeda nuo pirmo vaiko – randa tik vaikus

   HRESULT DeleteUnmatchedSubNodes(KpChar iSearchTag, unsigned char *lpszMinValue, unsigned char *lpszMaxValue);
                     // loops through subnodes of node <hg> and deletes all subnodes not
                     // satisfying query conditions, uses TestQuery()

   HRESULT CheckLevel(int iLevel, bool *pbDelFl); // tests whether node is to be deleted according to values of <lv> tags
   HRESULT SupressToLevel(int iLevel);    // deletes all tags according to values of <lv> tags
   HRESULT DelLevelTags(int iLevel); // removes group tags not corresponding to level specified according to baLevelTags[][]
   HRESULT UpLevelGroups(void);  // LevelGroup turinius istraukia i aukstesni lygmeni
                                 // (kad apskliaudimas i LevelGroup nenumustu skiruku veikimo)

   HRESULT ProcessLevel(int iLevel, bool bBeforePrint);   // processes all necessary level operations:
                                       //    SupressToLevel(iLevel);
                                       //    DelLevelTags(iLevel);
                                       //    DelTags(XC_Level); // if bBeforePrint
                                       //    UpLevelGroups(); // if bBeforePrint
                                       //    DelEmptyTags();
                                       //    UpCtgMng(void);
                                       //    RenumCtgMng();
                                       //    DelTags(XC_TechNote);


// HRESULT EncloseTextToTx(void); // text values of nodes consisting of text and additional subnodes
                                  //   encloses to XC_TextExpr


   HRESULT TestTilde(bool *bTildeFl);  // checks presence of '~' - TV_XM_CompBaseChar
                                       // recursive without initialisation - *bTildeFl
                                       //    should be False on entering

   HRESULT DelVert(void);  // eliminates '|' - TV_XM_CompDelim

   HRESULT TestNotSignificant(bool *bEmpty, KpChar *iSkipTagArr);
      // tests for presence of significant tags - is node worth for output?
      // *bEmpty should be True on entering
      // iSkipTag - additional tag not to be taket into account

// ---------------------------- dictionary inverting functions
   HRESULT TestChildContents(KpChar iTestTag, KpChar *lpiazTestValue, bool *pFoundFlg);
                     // tests matching of tag contents
                     // must be defined in user application
                     // used by DelUnmatchedCtgs
   HRESULT DelUnmatchedCtgs(KpChar *lpiazPsPtr);
                     // delete gram. categories unmatched to lpiazPsPtr as value of XC_GramForm tag

   HRESULT InsertHw
   (
      const unsigned char *lpszDictStId, long lEntrId,
      KpChar *piHwPtr, KpChar *piVarPtr,
      KpChar *piPsPtr, KpChar *piTwPtr
   );                // insertc additional <hw>, <v>, <ps> and <tg><tw>...</tw></tg> at the start of dict. entry
                     // lpszDictStId and lEntrId are used for tag <st> generation
                     // not implemented yet ???

   HRESULT Hw2Tw(void); // inverts <hw> like tags to <tw>, enclosing them to <tg>
                        //    defined in user application

   HRESULT GetHw(KpChar **plpiazHwPtrPtr) /* const */; // iðkvieèia GetNodeTag(), ji ne const
                                    // *plpiazHwPtrPtr must be NULL on entering,
                                    //    returns only pointer, cannnot be deleted
                                    //    NULL means no headword in node
   HRESULT GetBase(KpChar **plpiazBasePtrPtr) /* const */; // iðkvieèia GetNodeTag(), ji ne const
                                    // *plpiazBasePtrPtr must be NULL on entering,
                                    //    returns only pointer, cannnot be deleted
                                    //    usually returns full <hw> field, including '|'
                                    //       character
   HRESULT SubstBase(const KpChar *lpiazBasePtr, bool bOnlyHw);
                                    // replaces '~' with base root, lpiazBasePtr may contain
                                    //    full <hw> with base root delimited by '|'
                                    // if bOnlyHw==True replaces only <hw>-like fields,
                                    //    inserts additional '|' in between

   HRESULT EncloseCtg(int iCtgNum); // enclose contents of <hg> into <s1>
   HRESULT EncloseMng(int iMngNum); // enclose contents of <hg> into <s2>
   HRESULT EncloseLastCtgToMng(int iMngNum); // enclose contents of last <s1> into <s2>
   HRESULT AppendCtg(XmlNode *pSubEntry);
                                    // concatenates new <s1> containing entry pSubEntry to this node <hg>
                                    //    deletes tags of pSubEntry outside of <s1>
                                    //    pSubEntry cannot be deleted after successfull AppendCtg()
                                    // free function, can be called from outside of the object ???
   HRESULT AppendMng(XmlNode *pSubEntry);
                                    // concatenates new <s2> containing entry pSubEntry to this node <hg> or top <s1>
                                    //    deletes tags of pSubEntry outside of <s2>
                                    //    pSubEntry cannot be deleted after successfull AppendCtg()
                                    // free function, can be called from outside of the object ???

   HRESULT CreateGrpCounters(void); // sukuria XC_CtgGroup, XC_MngGroup ir Co bei XC_MngNearGroup numerius

   HRESULT FindNode(KpChar iTag, XmlNode **pSubNodePtr); // finds first occurence of iTag
                                                         // *pSubNodePtr should be NULL on entering
   HRESULT FindNextNode(KpChar iTag, XmlNode **pSubNodePtr, XmlNode *pPrevNode, bool *bPrevSkippedPtr);
                                                         // finds next occurence of iTag
                                                         // *pSubNodePtr should be NULL on entering
                                                         // if pPrevNode==NULL - finds first
                                                         // *bPrevSkippedPtr - common temporary variable for recursing functions
                                                         //    should be False on entering

// ---------------------------------
   HRESULT InvertNode(void);        // new generation of node inverter
                                    // node must not have categories, meanings and
                                    // duplicated <tg>'s (use WriteNodeDupCats(),
                                    // WriteNodeDupTrGroups() and WriteNodeDupTrWords()

// ---------------------------------
   HRESULT ReplaceLists(void);      // konvertuoja vidinius Lizdyno sarasus i teksta

// ---------------------------------
   HRESULT MarcHighlighted(const unsigned char *lpszTemplate, EC_Types iEncoding); // encloses corresponding to lpszTemplate words into <hl> tags
   HRESULT MarcHighlightedGram(const unsigned char *lpszTemplate, EC_Types iEncoding); // like MarcHighlighted(), but words are tested for exact equivalence of normalized grammar forms


// ---------------------------------
   HRESULT ConcatXrs(void);   // apjungia gretimas nuorodas tuo paciu href-u
   HRESULT ConcatTxs(void);   // apjungia gretimus XC_Text laukus

// ---------------------------------
   HRESULT Hyphenate(void);   // skiemenuoja

// ---------------------------------
   HRESULT ParseStyleContents(KpChar iGrandFatherTag); // skanuoja <style> tagø turinius *m_lpaizContents ir suformuoja *m_pContPars (atvirkðèiai FormatStyleContents())
   HRESULT FormatStyleContents(KpChar iGrandFatherTag);  // generuoja <style> tagø turinius *m_lpaizContents ið *m_pContPars (atvirkðèiai ParseStyleContents())

// --------------------------------- iBSh arksh
   HRESULT AppendScript(void); // prideda JavaScript; turi bûti apibrëþta aplikacijos lygmeny
   HRESULT SetCtrls(KpFileSys *KpFileSysPtr); // nustato pradines mygtukø reikðmes, atsiþvelgiant á KpGeckoFilePtr->aiAnswers[];
                                                 // apibrëþiama lokaliai aplikacijoje
   HRESULT CorrectLinks(void); // prideda nuorodoms prieðdëlá "tux:"

// -------------------------
#if TRUE // #ifdef Debug
   HRESULT TraceContents (const unsigned char *lpszIndent = (const unsigned char *)"");
#else
   HRESULT TraceContents (const unsigned char * = (const unsigned char *)"") { return(S_OK); };
#endif
};

// -------------------------------------------
// XmlNode::SetTagHeadings_loop() ir XmlNode::SetTagHeadings() (KpRichEd.cpp) konstantos ir laukai
#define rtf_grab_margin_x 5
#define rtf_grab_margin_y 5
#define rtf_grab_dx 500
#define rtf_grab_dy rtf_grab_ctrl_dy
#define rtf_grab_ctrl_margin 10
#define rtf_grab_ctrl_x  rtf_grab_ctrl_margin
#define rtf_grab_ctrl_y  rtf_grab_ctrl_margin
#define rtf_grab_ctrl_dx (rtf_grab_margin_x+rtf_grab_dx+KPW_SCROLLBAR_WDT)
#define rtf_grab_ctrl_dy (rtf_grab_margin_y+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define rtf_grab_wnd_margin_x 20
#define rtf_grab_wnd_margin_y 50

extern TvRtfO *SetTagHeadings_rtf_file;
extern unsigned char SetTagHeadings_rtf_file_buf[XMLN_RICH_BUF_LEN+1];
extern KpChar SetTagHeadings_node_suff[XL_ND_MaxNumOfNodes*2+2];

// -------------------------------------------
extern HRESULT ReadEntry(XmlNode **ppNodePtr, XmlI *lpInFile, bool bExact, KpChar iFirstTag = XC_FirstDictTag, const unsigned char * const *plpszaTags = plpszaXmlttDictTagsFull);
extern HRESULT ReadEntry(XmlNode **ppNodePtr, XmlO1 *lpInFile, bool bExact, KpChar iFirstTag = XC_FirstDictTag, const unsigned char * const *plpszaTags = plpszaXmlttDictTagsFull);
                                    // reads whole entry to new created node
                                    // *ppNodePtr after use must be deleted by
                                    //    caller application
                                    // if bExact==True - does not skip initial spaces

extern HRESULT ReadXmlFile(XmlNode **ppNodePtr, XmlO1 *lpInFile, KpChar iFirstTag = XC_FirstDictTag, const unsigned char * const *plpszaTags = plpszaXmlttDictTagsFull);
                                    // skaito visà XML/XHTML/HTML failà – kartoja ReadEntry(), kol pasibaigia failas


// -------------------------------------------
extern HRESULT EncloseToGroup(XmlNode **ppFirstOccurence, KpChar iGrTag);
                                    // creates new node of group tag iGrTag and
                                    //    encloses *ppFirstOccurence to it as a child
                                    //    returns new created node as *ppFirstOccurence

extern HRESULT GetNextWord(KpChar *iazPrevTextBuf, KpChar *iazCurWordBuf, KpChar *iazRestTextBuf); // pagalbine del MarcHighlighted() ir MarcHighlightedGram()
extern HRESULT TestTemplateGramSingle(const KpChar *iazTestWord, const unsigned char *lpszTemplate, EC_Types iEncoding, int iLang); // pagalbine del MarcHighlightedGram()
extern HRESULT TestTemplateGram(const KpChar *iazTestWord, const unsigned char *lpszTemplate, EC_Types iEncoding); // pagalbine del MarcHighlightedGram()

// -------------------------------------------
extern const KpChar lpiazNotFound[];     // used in InsertHw(), must be defined in user application

//-------------------------------------------- RTF definition arays
extern /* const */ RT_FontDescriptor_tag iaRtfFonts[KPT_NumOfTypefaces0+1];
                                       // const neleidzia iskviesti IsDefined() ir co.

//-------------------------------------------- TeX definition arays
extern const KpChar iaTex2XmlTags[/* (VL_TG_NumOfTags+1)*2 */];  // array of XML tags, enclosing Tex
                                                        //    command parameter
                                                        // first collumn - starting tag,
                                                        //    (XC_TG_NoTag - no conversion)
                                                        // second - tag after text
                                                        //    (XC_TG_NoTag - no tag needed
                                                        //    after parameter)

extern const KpChar iaXml2Tex[XC_TG_NumOfDictTags00+1];   // array of TeX commands,
                                                 // corresponding each XMLT tag

//-------------------------------------------- converts output character to TEX tag
extern KpChar CvtToTex(KpChar iInCh);

#endif
