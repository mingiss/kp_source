// ==================================================
// tvrtf.h
// RTF definitions


#ifndef tvrtf_included
#define tvrtf_included

// spec. chars in input file
#define RC_KeywordStart ('\\')
#define RT_FieldStart ('{')
#define RT_FieldEnd ('}')

// returned control characters
#define RC_NewPar    C_Lf  // ('\n')
#define RC_LineBreak C_break  // C_Cr  // ('\r')
#define RC_PageBreak C_Ff  // ('\f')
#define RC_CellDelim C_Ht  // ('\t')
#define RC_RowDelim  C_Vt  // ('\v')
#define RC_TblDelim  C_Ff  // ('\f') // ??? conflict with RC_PageBreak


#define RT_MAX_NUM_OF_FONTS   3000     // Size of font table
#define RT_FONT_UNDEFINED     (-1)
#define RT_FONT_NAME_LENGTH   KP_MAX_FNAME_LEN  // max length of font name

#define RT_NO_VALUE           (-1)     // undefined numeric value of the keyword 

#define RT_MAX_NUM_OF_RTF_CTBLS  256   // Size of RTF to Kpt code table
                                       //    conversion array
#define RT_NoCodeTable        (-1)     // Value for undefined font table entry
#define RT_UnknownCodeTable   (-2)     // unknown RTF code table


typedef enum
{
   RT_TG_Rtf,
   RT_TG_FontTbl,
   RT_TG_Font,       // "f"
   RT_TG_CharSet,
   RT_TG_ColorTbl,
   RT_TG_StyleSheet,
   RT_TG_RevTbl,
   RT_TG_Info,
   RT_TG_PnsecLvl,
   RT_TG_Par,
   RT_TG_Cell,
   RT_TG_Row,
   RT_TG_SpecChr,    // "\'"
   RT_TG_Field,
   RT_TG_LQuote,
   RT_TG_RQuote,
   RT_TG_LDblQuote,
   RT_TG_RDblQuote,
   RT_TG_Caps,
   RT_TG_Ansi,
   RT_TG_AnsiCpg,
   RT_TG_Uc,
   RT_TG_Deff,
   RT_TG_DefLang,
   RT_TG_DefLangFe,
   RT_TG_FRoman,
   RT_TG_FSwiss,
   RT_TG_FModern,
   RT_TG_FNil,
   RT_TG_Fprq,
   RT_TG_Ast,
   RT_TG_Panose,
   RT_TG_FAlt,
   RT_TG_ListTable,
   RT_TG_List,
   RT_TG_ListTemplateId,
   RT_TG_ListSimple,
   RT_TG_ListLevel,
   RT_TG_LevelNfc,
   RT_TG_LevelNfcn,
   RT_TG_LevelJc,
   RT_TG_LevelJcn,
   RT_TG_LevelFollow,
   RT_TG_LevelStartAt,
   RT_TG_LevelSpace,
   RT_TG_LevelIndent,
   RT_TG_LevelText,
   RT_TG_ListOverrideTable,
   RT_TG_PaperW,
   RT_TG_PaperH,
   RT_TG_WidowCtrl,
   RT_TG_Ftnbj,
   RT_TG_AendDoc,
   RT_TG_NoxLatToYen,

   RT_TG_expshrtn,
   RT_TG_noultrlspc,
   RT_TG_dntblnsbdb,
   RT_TG_nospaceforul,
   RT_TG_hyphcaps,
   RT_TG_formshade,
   RT_TG_horzdoc,
   RT_TG_dghspace,
   RT_TG_dgvspace,
   RT_TG_dghorigin,
   RT_TG_dgvorigin,
   RT_TG_dghshow,
   RT_TG_dgvshow,
   RT_TG_jexpand,
   RT_TG_viewkind,
   RT_TG_viewscale,
   RT_TG_pgbrdrhead,
   RT_TG_pgbrdrfoot,
   RT_TG_nolnhtadjtbl,
   RT_TG_fet,
   RT_TG_sectd,
   RT_TG_linex,
   RT_TG_endnhere,
   RT_TG_sectdefaultcl,
   RT_TG_header,
   RT_TG_pard,
   RT_TG_plain,
   RT_TG_s,
   RT_TG_ql,
   RT_TG_li,
   RT_TG_ri,
   RT_TG_widctlpar,
   RT_TG_tqc,
   RT_TG_tx,
   RT_TG_tqr,
   RT_TG_aspalpha,
   RT_TG_aspnum,
   RT_TG_faauto,
   RT_TG_adjustright,
   RT_TG_rin,
   RT_TG_lin,
   RT_TG_itap,
   RT_TG_fs,
   RT_TG_lang,
   RT_TG_langfe,
   RT_TG_cgrid,
   RT_TG_landnp,
   RT_TG_langfenp,
   RT_TG_tab,
   RT_TG_fldinst,
   RT_TG_cs,
   RT_TG_fldrslt,
   RT_TG_noproof,
   RT_TG_footer,
   RT_TG_langnp,
   RT_TG_b,
   RT_TG_cf,
   RT_TG_qc,
   RT_TG_keepn,
   RT_TG_outlinelevel,
   RT_TG_highlight,
   RT_TG_i,
   RT_TG_scaps,
   RT_TG_sect,
   RT_TG_sbknone,
   RT_TG_cols,
   RT_TG_colno,
   RT_TG_colw,
   RT_TG_colsr,
   RT_TG_endash,
   RT_TG_pntext,
   RT_TG_hich,
   RT_TG_af,
   RT_TG_dbch,
   RT_TG_loch,
   RT_TG_fi,
   RT_TG_jclisttab,
   RT_TG_pn,
   RT_TG_pnlvlbody,
   RT_TG_ilvl,
   RT_TG_ls,
   RT_TG_pnrnot,
   RT_TG_pnlcrm,
   RT_TG_pni,
   RT_TG_pncf,
   RT_TG_pnstart,
   RT_TG_pnindent,
   RT_TG_pnsp,
   RT_TG_pnhang,
   RT_TG_pntxta,
   RT_TG_trowd,
   RT_TG_trgaph,
   RT_TG_trrh,
   RT_TG_trleft,
   RT_TG_trftsWidth,
   RT_TG_trpaddl,
   RT_TG_trpaddr,
   RT_TG_trpaddfl,
   RT_TG_trpaddfr,
   RT_TG_clvertalt,
   RT_TG_clbrdrt,
   RT_TG_brdrnone,
   RT_TG_clbrdrl,
   RT_TG_clbrdrb,
   RT_TG_clbrdrr,
   RT_TG_clbrdrtb,
   RT_TG_clftsWidth,
   RT_TG_clwWidth,
   RT_TG_cellx,
   RT_TG_cl,
   RT_TG_brdrs,
   RT_TG_brdrw,
   RT_TG_cltxlrtb,
   RT_TG_qr,
   RT_TG_intbl,
   RT_TG_sl,
   RT_TG_slmult,
   RT_TG_qj,
   RT_TG_ul,
   RT_TG_ulnone,
   RT_TG_dn,
   RT_TG_sub,
   RT_TG_Nil,        // ""
   RT_TG_object,
   RT_TG_objemb,
   RT_TG_objw,
   RT_TG_objh,
   RT_TG_objclass,
   RT_TG_objdata,
   RT_TG_result,
   RT_TG_shppict,
   RT_TG_pict,
   RT_TG_picprop,
   RT_TG_shplid,
   RT_TG_sp,
   RT_TG_sn,
   RT_TG_sv,
   RT_TG_picscalex,
   RT_TG_picscaley,
   RT_TG_piccropl,
   RT_TG_piccropr,
   RT_TG_piccropt,
   RT_TG_piccropb,
   RT_TG_picw,
   RT_TG_pich,
   RT_TG_picwgoal,
   RT_TG_pichgoal,
   RT_TG_pngblip,
   RT_TG_bliptag,
   RT_TG_blipuid,
   RT_TG_blipupi,
   RT_TG_nonshppict,
   RT_TG_wmetafile,
   RT_TG_super,
   RT_TG_line,
   RT_TG_listtext,
   RT_TG_u,
   RT_TG_strike,
   RT_TG_NBSP,
   RT_TG_v,           // hidden font
   RT_TG_flddirty,
   RT_TG_trqr,
   RT_TG_trbrdrt,
   RT_TG_trbrdrl,
   RT_TG_trbrdrb,
   RT_TG_trbrdrr,
   RT_TG_trbrdrh,
   RT_TG_trbrdrv,
   RT_TG_trftsWidthB,
   RT_TG_trwWidthB,
   RT_TG_trftsWidthA,
   RT_TG_trwWidthA,
   RT_TG_nowidctlpar,
   RT_TG_shad,
   RT_TG_pndec,
   RT_TG_fscript,
   RT_TG_fdecor,
   RT_TG_trwWidth,
   RT_TG_pnucltr,
   RT_TG_pntxtb,
   RT_TG_emdash,
   RT_TG_pgwsxn,
   RT_TG_pghsxn,
   RT_TG_marglsxn,
   RT_TG_margrsxn,
   RT_TG_margtsxn,
   RT_TG_margbsxn,
   RT_TG_psz,
   RT_TG_headery,
   RT_TG_footery,
   RT_TG_fldedit,

   RT_TG_pnlvlcont,
   RT_TG_pnlvlblt,
   RT_TG_pnf,

   RT_TG_xxx,              // only for testing

   RT_TG_left_curly,       // "{"
   RT_TG_right_curly,      // "}"

   RT_TG_opt_hyph,         // "-"

   RT_TG_deftab,

   RT_TG_red,
   RT_TG_green,
   RT_TG_blue,

   RT_TG_nosupersub,

   RT_TG_stylesheet,
   RT_TG_snext,
   RT_TG_additive,
   RT_TG_sbasedon,

   RT_TG_margl,
   RT_TG_margr,
   RT_TG_margt,
   RT_TG_margb,
   RT_TG_margmirror,
   RT_TG_dgmargins,
   RT_TG_dgmargin,
   RT_TG_lndscpsxn,
   RT_TG_titlepg,
   RT_TG_sectlinegrid,

   RT_TG_nestcell,
   RT_TG_nonesttables,
   RT_TG_nesttableprops,
   RT_TG_nestrow,

   RT_TG_footerf,

   RT_TG_revised,
   RT_TG_revauth,
   RT_TG_revdttm,
   RT_TG_deleted,

   RT_TG_hyphhotz,
   RT_TG_hyphauto,
   RT_TG_viewzk,
   RT_TG_bdrrlswsix,
   RT_TG_pgnrestart,
   RT_TG_colsx,
   RT_TG_expnd,
   RT_TG_expndtw,
   
   RT_TG_page,

   RT_TG_sb,
   RT_TG_sa,
   RT_TG_kerning,

   RT_TG_xe,

   RT_TG_splytwnine,
   RT_TG_ftnlytwnine,
   RT_TG_htmautsp,
   RT_TG_useltbaln,
   RT_TG_alntblind,
   RT_TG_lytcalctblwd,
   RT_TG_lyttblrtgr,
   RT_TG_lnbrkrule,
   RT_TG_trqc,

   RT_TG_datafield,

   RT_TG_c,
   RT_TG_z,

   RT_TG_tldot,

   RT_TG_charscalex,

   RT_TG_bkmkstart,
   RT_TG_bkmkend,

   RT_TG_userprops,  // equations
   RT_TG_propname,
   RT_TG_proptype,
   RT_TG_staticval,

   RT_TG_brdrb,
   RT_TG_brsp,
   
   RT_TG_tdfrmtxtLeft,
   RT_TG_tdfrmtxtRight,
   RT_TG_tpvpara,
   RT_TG_tphmrg,
   RT_TG_tposy,

   RT_TG_column,

   RT_TG_atrfstart,
   RT_TG_atrfend,
   RT_TG_atnid,
   RT_TG_atnauthor,
   RT_TG_chatn,
   RT_TG_annotation,
   RT_TG_atnref,

   RT_TG_NumOfTags00

} RT_TagIds;


#define RT_TG_NumOfTags21 RT_TG_NumOfTags00


//-------------------------------------------- FieldDescriptor_tag, FontDescriptor_tag
typedef enum
{
   RT_TT_Unknown,
   RT_TT_Text,
   RT_TT_FontTable,
   RT_TT_FontDefinition,
   RT_TT_FontDefinitionSubfield,
   RT_TT_RTF_Field, // former RT_TT_Field, RT_TT_SymField
   RT_TT_Table,

   RT_TT_NumOfFieldTypes

} RT_FieldTypes;


typedef enum
{
   RT_TT_RTF_FieldUnknown,
   RT_TT_RTF_SymField,
   RT_TT_RTF_HypField,

   RT_TT_RTF_NumOfFieldTypes

} RT_RTF_FieldTypes;
          

typedef enum
{
   RT_PR_LeftPar,
   RT_PR_RightPar,

   RT_PR_NumOfPars

} RT_Parentheses;


typedef enum
{
   VT_CapsUndefined,
   VT_ToUpper,
   VT_ToLower,
   VT_SmCaps,

   VT_NumOfCapsIds

} CapsIndicators;


// --------------------------------------------------
typedef class RT_FontDescriptor_tag
{
   bool bLastEntry;              // last entry of array (first entry after the last significant entry)
   bool bDefined;                // Font defined
   int iRtfCodeTable;            // Code table in RTF notification
   int iKptCodeTable;            // Code table in Kpt notification
   unsigned char szFontName[RT_FONT_NAME_LENGTH+1];

   RT_TagIds iFontType; // former iFontTypeFace // font typeface: RT_TG_FNil, RT_TG_FRoman, RT_TG_FSwiss, RT_TG_FModern

public:
   RT_FontDescriptor_tag(void);
   RT_FontDescriptor_tag(bool bLast, bool bDefFl, const /* unsigned */ char *lpszName, int iRCTbl, int iKptCTbl, RT_TagIds iFntType);

   HRESULT SetLast(bool bLast);     // set/reset last entry flag
   HRESULT IsLast(bool *pbLast);    // check whether end of array reached

   HRESULT SetDefined(bool bDefFl);    // Sets/resets font definition flag
   HRESULT IsDefined(bool *pbDefFl);   // Tests whether font is defined

   HRESULT SetRtfCodeTable(int iRCTbl); // Sets font iRtfCodeTable, calculates iKptCodeTable
   HRESULT GetRtfCodeTable(int *piRCTbl);  // Gets RTF font coding table number, former GetCodeTable()

   HRESULT SetKptCodeTable(int iKpCTbl); // Sets font iKptCodeTable
   HRESULT GetKptCodeTable(int *piKpCTbl);  // Gets Kpt font coding table number, former GetCodeTable()

   HRESULT SetFontName(const unsigned char *lpszName);
   HRESULT SetFontName(const char *lpszName);
                                       // sets font name, lpszName can be deleted after call
   HRESULT PutCharToName(const unsigned char ucCh);
                                       // concatenates char to font name property
   HRESULT GetFontName(unsigned char **plpszNamePtr);
                                       // returns pointer to font name

   HRESULT SetFontType(RT_TagIds iType);     // former SetTypeFace() // get/set font type
   HRESULT GetFontType(RT_TagIds *piType);   // former GetTypeFace()

} RT_FontDescriptor;


// --------------------------------------------------
typedef class RT_FieldDescriptor_tag
{
   RT_FieldTypes iFieldType;           // Type of current field
   RT_RTF_FieldTypes iRTFieldType;     // Subtype of current field RT_TT_RTF_Field
   RT_FieldDescriptor_tag *pParentField;  // Pointer to previous field. NULL - the first level
                                       //    of the file

   int iFont;                          // Current font number (index in font table)
                                       //    (0 ... RT_MAX_NUM_OF_FONTS or
                                       //    RT_FONT_UNDEFINED)
   
   bool bBoldFl;                       // bold flag
   bool bItFl;                         // italic flag
   bool bHiddenFl;                     // hidden text flag
   bool m_bSubFl;                      // subscript flag
   bool m_bSuperFl;                    // superscript flag
   CapsIndicators iCapsInd;            // CAPS indicator
   bool bXrefFl;                       // reference flag

   long lTblWdt;                       // table field parameters
   int iNumOfTblCls;

public:
   RT_FieldDescriptor_tag(RT_FieldDescriptor_tag *pPField);
   ~RT_FieldDescriptor_tag(void);

   HRESULT SetFieldType(RT_FieldTypes iFieldTp); // Set type of the RTF field
   HRESULT GetFieldType(RT_FieldTypes *piFieldTp); // Get type of current RTF field

   HRESULT SetRTFieldType(RT_RTF_FieldTypes iFieldTp); // Set subtype of the RTF field 
   HRESULT GetRTFieldType(RT_RTF_FieldTypes *piFieldTp); // Get subtype of current RTF field

   HRESULT SetTablePars(long lTableWidth, int iNumOfCols);
   HRESULT GetTablePars(long *plTableWidth, int *piNumOfCols);
                                                // get/set table field parameters

   HRESULT SetParField(RT_FieldDescriptor_tag *pParField);
                                                // Set ponter to parrent field
   HRESULT GetParField(RT_FieldDescriptor_tag **ppParField);
                                                // Get ponter to parrent field

   HRESULT GetFont(int *piFnt);        // Get current field font number
   HRESULT SetFont(int iFnt);          // Set current field font number

   HRESULT SetBold(bool bBoldF);
   HRESULT GetBold(bool *pbBoldF);
   HRESULT SetIt(bool bItF);
   HRESULT GetIt(bool *pbItF);
   HRESULT SetHidden(bool bHiddenF);
   HRESULT GetHidden(bool *pbHiddenF);
   HRESULT SetSub(bool bSubF);    // ar superscript
   HRESULT GetSub(bool *pbSubF);
   HRESULT SetSuper(bool bSuperF);  // ar subscript
   HRESULT GetSuper(bool *pbSuperF);

   HRESULT SetXref(bool bXrefF);
   HRESULT GetXref(bool *pbXrefF);

   HRESULT GetCaps(CapsIndicators *piCpsInd);  // get/set CAPS indicator
   HRESULT SetCaps(CapsIndicators iCpsInd);

   HRESULT GetFieldFlags(int *piFieldFlags); // compose field style flags corresponding to KPS_FontStyle.iFontFlags

} RT_FieldDescriptor;


// --------------------------------------------------
typedef class TvRtfIO_tag
{
public:
   HRESULT lhOpenResult;

// TvXml8File_tag *lpfRtfFile;
   KpFile *lpfRtfFile;
   
   RT_FontDescriptor_tag *pFonts;      // Pointer to font table of up to RT_MAX_NUM_OF_FONTS entries
                                       //    if count of entries <RT_MAX_NUM_OF_FONTS, last entry
                                       //       must be marked with bLastEntry=True
                                       //    managed internaly by TvRtfI_tag
                                       //    managed externaly by user application in case of TvRtfO_tag

   int iNumOfFonts;

   int iStdWinFontIndex;               // index of font with standard Windows coding
   int iCEFontIndex;                   // index of font with CE coding
   int iPhonFontIndex;                 // index of font with basic phonetic coding
   int iLTFontIndex;                   // index of font with LT 1257 coding
   int iLTAccFontIndex;                // index of font with LT accented coding
   int iSymbolFontIndex;               // index of SYMBOL font

   RT_FieldDescriptor_tag *pCurrentField; // pointer to RTF fields stack top

   unsigned char m_lpszTextVal[TV_TAG_LEN+1]; // text value of current RT_TT_RTF_HypField field

   int iFldDepth;                // current count of open fields

   TvRtfIO_tag(void);
   ~TvRtfIO_tag(void);

   HRESULT GetOpenResult(void);   // Returns value of OpenResult -
                                          //   object creation error code
   HRESULT Reset(void);

   HRESULT GetFieldType(RT_FieldTypes *piFieldTp); // Get type of current field
   HRESULT SetRTFieldType(RT_RTF_FieldTypes iRTFieldType); // sets RTF field type for all top RT_TT_RTF_Field fields

   HRESULT SetXref(bool bXrefF);

   HRESULT GetFieldFlags(int *piFieldFlags); // compose field style flags corresponding to KPS_FontStyle.iFontFlags

   HRESULT SetFont(int iFnt);

   HRESULT PushField(RT_FieldTypes *piFieldType, int *piCurFont);
                                 // Creates new field definitions, puts them to the
                                 //    top of the record.
                                 // Output:
                                 //    *piFieldType, *piCurFont - current field type
                                 //       and font - may be changed during ProcessKeyword()
                                 //    Uses pCurrentField

   HRESULT PopField(RT_FieldTypes *piFieldType, int *piCurFont);
                                 // Returns back parrent field definitions, deletes
                                 //    current field from top of the record.
                                 // Output:
                                 //    *piFieldType, *piCurFont - current field type
                                 //       and font - may be changed during ProcessKeyword()
                                 //    Uses pCurrentField
   int GetFldDepth(void);

} TvRtfIO;


// --------------------------------------------------
extern unsigned char *plpszaRtfTagTable[RT_TG_NumOfTags00+1];
extern unsigned char *lpszaRtfFieldTypesTags[RT_TT_RTF_NumOfFieldTypes+1];
          
extern unsigned char lpszRtfCtrlChars[];
extern unsigned char lpszRtfCtrlsAndSpaces[];
extern unsigned char lpszRtfListDelims[];
extern unsigned char lpszRtfCtrlsSpacesAndDelims[];

extern unsigned char lpszRtfProcSpcs[];
extern unsigned char lpszRtfProcSpcEol[];
extern unsigned char lpszRtfProcTabDelims[];  // RC_CellDelim, RC_RowDelim, RC_TblDelim

// Kpt codetables equivalents for \lang \langfe \langnp \langfenp \deflang \deflangfe
// used for switching to codepages different from RTF:1033/Kpt:74
// \fcharset0 (or \fcharset186 ?) is used for such Unicode fonts
// for oldstyle 8-bit fonts use \fcharset from iRtf2KptCTblArr[] and \lang*1033 codepage
extern int iaKpt2RtfLangCodesArr[KPT_Ctnum]; 

// Kpt codetables equivalents for \fcharset
// used in old style 8-bit fonts, RTF code page \lang* should be 1033 in that case (\lang*1033)
// former iRtf2KptCTbl[] !!! do not use directly, use ConvertRtf2KptCTbl()
extern int iRtf2KptCTblArr[RT_MAX_NUM_OF_RTF_CTBLS];
extern int ConvertRtf2KptCTbl(int iRtfCTbl); // use iaXmlFonts[] instead

extern HRESULT CvtToRtfCtlStr(unsigned char *lpszOutStr, const unsigned char *lpszInStr, int iBufLen);
            // converts characters from upper part of codetable to \' commands

#endif
