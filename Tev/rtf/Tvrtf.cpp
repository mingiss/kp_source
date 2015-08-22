// ==================================================
// tvrtf.cpp
// RTF file, field and font descriptor clases


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvrtf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "xmlsty.h"

unsigned char *plpszaRtfTagTable[RT_TG_NumOfTags21+1]=
{
   (unsigned char *)"rtf",
   (unsigned char *)"fonttbl",
   (unsigned char *)"f",
   (unsigned char *)"fcharset",
   (unsigned char *)"colortbl",
   (unsigned char *)"stylesheet",
   (unsigned char *)"revtbl",
   (unsigned char *)"info",
   (unsigned char *)"pnseclvl",
   (unsigned char *)"par",
   (unsigned char *)"cell",
   (unsigned char *)"row",
   (unsigned char *)"\'",
   (unsigned char *)"field",
   (unsigned char *)"lquote",
   (unsigned char *)"rquote",
   (unsigned char *)"ldblquote",
   (unsigned char *)"rdblquote",
   (unsigned char *)"caps",
   (unsigned char *)"ansi",
   (unsigned char *)"ansicpg",
   (unsigned char *)"uc",
   (unsigned char *)"deff",
   (unsigned char *)"deflang",
   (unsigned char *)"deflangfe",
   (unsigned char *)"froman",
   (unsigned char *)"fswiss",
   (unsigned char *)"fmodern",
   (unsigned char *)"fnil",
   (unsigned char *)"fprq",
   (unsigned char *)"*",
   (unsigned char *)"panose",
   (unsigned char *)"falt",
   (unsigned char *)"listtable",
   (unsigned char *)"list",
   (unsigned char *)"listtemplateid",
   (unsigned char *)"listsimple",
   (unsigned char *)"listlevel",
   (unsigned char *)"levelnfc",
   (unsigned char *)"levelnfcn",
   (unsigned char *)"leveljc",
   (unsigned char *)"leveljcn",
   (unsigned char *)"levelfollow",
   (unsigned char *)"levelstartat",
   (unsigned char *)"levelspace",
   (unsigned char *)"levelindent",
   (unsigned char *)"leveltext",
   (unsigned char *)"listoverridetable",
   (unsigned char *)"paperw",
   (unsigned char *)"paperh",
   (unsigned char *)"widowctrl",
   (unsigned char *)"ftnbj",
   (unsigned char *)"aenddoc",
   (unsigned char *)"noxlattoyen",

   (unsigned char *)"expshrtn",
   (unsigned char *)"noultrlspc",
   (unsigned char *)"dntblnsbdb",
   (unsigned char *)"nospaceforul",
   (unsigned char *)"hyphcaps",
   (unsigned char *)"formshade",
   (unsigned char *)"horzdoc",
   (unsigned char *)"dghspace",
   (unsigned char *)"dgvspace",
   (unsigned char *)"dghorigin",
   (unsigned char *)"dgvorigin",
   (unsigned char *)"dghshow",
   (unsigned char *)"dgvshow",
   (unsigned char *)"jexpand",
   (unsigned char *)"viewkind",
   (unsigned char *)"viewscale",
   (unsigned char *)"pgbrdrhead",
   (unsigned char *)"pgbrdrfoot",
   (unsigned char *)"nolnhtadjtbl",
   (unsigned char *)"fet",
   (unsigned char *)"sectd",
   (unsigned char *)"linex",
   (unsigned char *)"endnhere",
   (unsigned char *)"sectdefaultcl",
   (unsigned char *)"header",
   (unsigned char *)"pard",
   (unsigned char *)"plain",
   (unsigned char *)"s",
   (unsigned char *)"ql",
   (unsigned char *)"li",
   (unsigned char *)"ri",
   (unsigned char *)"widctlpar",
   (unsigned char *)"tqc",
   (unsigned char *)"tx",
   (unsigned char *)"tqr",
   (unsigned char *)"aspalpha",
   (unsigned char *)"aspnum",
   (unsigned char *)"faauto",
   (unsigned char *)"adjustright",
   (unsigned char *)"rin",
   (unsigned char *)"lin",
   (unsigned char *)"itap",
   (unsigned char *)"fs",        // font size
   (unsigned char *)"lang",
   (unsigned char *)"langfe",
   (unsigned char *)"cgrid",
   (unsigned char *)"landnp",
   (unsigned char *)"langfenp",
   (unsigned char *)"tab",
   (unsigned char *)"fldinst",
   (unsigned char *)"cs",
   (unsigned char *)"fldrslt",
   (unsigned char *)"noproof",
   (unsigned char *)"footer",
   (unsigned char *)"langnp",
   (unsigned char *)"b",
   (unsigned char *)"cf",        // fono spalva
   (unsigned char *)"qc",
   (unsigned char *)"keepn",
   (unsigned char *)"outlinelevel",
   (unsigned char *)"highlight",
   (unsigned char *)"i",
   (unsigned char *)"scaps",
   (unsigned char *)"sect",
   (unsigned char *)"sbknone",
   (unsigned char *)"cols",
   (unsigned char *)"colno",
   (unsigned char *)"colw",
   (unsigned char *)"colsr",
   (unsigned char *)"endash",
   (unsigned char *)"pntext",
   (unsigned char *)"hich",
   (unsigned char *)"af",
   (unsigned char *)"dbch",
   (unsigned char *)"loch",
   (unsigned char *)"fi",
   (unsigned char *)"jclisttab",
   (unsigned char *)"pn",
   (unsigned char *)"pnlvlbody",
   (unsigned char *)"ilvl",
   (unsigned char *)"ls",
   (unsigned char *)"pnrnot",
   (unsigned char *)"pnlcrm",
   (unsigned char *)"pni",
   (unsigned char *)"pncf",
   (unsigned char *)"pnstart",
   (unsigned char *)"pnindent",
   (unsigned char *)"pnsp",
   (unsigned char *)"pnhang",
   (unsigned char *)"pntxta",
   (unsigned char *)"trowd",
   (unsigned char *)"trgaph",
   (unsigned char *)"trrh",
   (unsigned char *)"trleft",
   (unsigned char *)"trftsWidth",
   (unsigned char *)"trpaddl",
   (unsigned char *)"trpaddr",
   (unsigned char *)"trpaddfl",
   (unsigned char *)"trpaddfr",
   (unsigned char *)"clvertalt",
   (unsigned char *)"clbrdrt",
   (unsigned char *)"brdrnone",
   (unsigned char *)"clbrdrl",
   (unsigned char *)"clbrdrb",
   (unsigned char *)"clbrdrr",
   (unsigned char *)"clbrdrtb",
   (unsigned char *)"clftsWidth",
   (unsigned char *)"clwWidth",
   (unsigned char *)"cellx",
   (unsigned char *)"cl",
   (unsigned char *)"brdrs",
   (unsigned char *)"brdrw",
   (unsigned char *)"cltxlrtb",
   (unsigned char *)"qr",
   (unsigned char *)"intbl",
   (unsigned char *)"sl",
   (unsigned char *)"slmult",
   (unsigned char *)"qj",
   (unsigned char *)"ul",
   (unsigned char *)"ulnone",
   (unsigned char *)"dn",
   (unsigned char *)"sub",
   (unsigned char *)"",       // RT_TG_Nil
   (unsigned char *)"object",
   (unsigned char *)"objemb",
   (unsigned char *)"objw",
   (unsigned char *)"objh",
   (unsigned char *)"objclass",
   (unsigned char *)"objdata",
   (unsigned char *)"result",
   (unsigned char *)"shppict",
   (unsigned char *)"pict",
   (unsigned char *)"picprop",
   (unsigned char *)"shplid",
   (unsigned char *)"sp",
   (unsigned char *)"sn",
   (unsigned char *)"sv",
   (unsigned char *)"picscalex",
   (unsigned char *)"picscaley",
   (unsigned char *)"piccropl",
   (unsigned char *)"piccropr",
   (unsigned char *)"piccropt",
   (unsigned char *)"piccropb",
   (unsigned char *)"picw",
   (unsigned char *)"pich",
   (unsigned char *)"picwgoal",
   (unsigned char *)"pichgoal",
   (unsigned char *)"pngblip",
   (unsigned char *)"bliptag",
   (unsigned char *)"blipuid",
   (unsigned char *)"blipupi",
   (unsigned char *)"nonshppict",
   (unsigned char *)"wmetafile",
   (unsigned char *)"super",
   (unsigned char *)"line",
   (unsigned char *)"listtext",
   (unsigned char *)"u",         // unicode character
   (unsigned char *)"strike",
   (unsigned char *)"~",
   (unsigned char *)"v",
   (unsigned char *)"flddirty",
   (unsigned char *)"trqr",
   (unsigned char *)"trbrdrt",
   (unsigned char *)"trbrdrl",
   (unsigned char *)"trbrdrb",
   (unsigned char *)"trbrdrr",
   (unsigned char *)"trbrdrh",
   (unsigned char *)"trbrdrv",
   (unsigned char *)"trftsWidthB",
   (unsigned char *)"trwWidthB",
   (unsigned char *)"trftsWidthA",
   (unsigned char *)"trwWidthA",
   (unsigned char *)"nowidctlpar",
   (unsigned char *)"shad",
   (unsigned char *)"pndec",
   (unsigned char *)"fscript",
   (unsigned char *)"fdecor",
   (unsigned char *)"trwWidth",

   (unsigned char *)"pnucltr",
   (unsigned char *)"pntxtb",
   (unsigned char *)"emdash",
   (unsigned char *)"pgwsxn",
   (unsigned char *)"pghsxn",
   (unsigned char *)"marglsxn",
   (unsigned char *)"margrsxn",
   (unsigned char *)"margtsxn",
   (unsigned char *)"margbsxn",
   (unsigned char *)"psz",
   (unsigned char *)"headery",
   (unsigned char *)"footery",
   (unsigned char *)"fldedit",

   (unsigned char *)"pnlvlcont",
   (unsigned char *)"pnlvlblt",
   (unsigned char *)"pnf",

   (unsigned char *)"xxx",

   (unsigned char *)"{", // RT_TG_left_curly
   (unsigned char *)"}", // RT_TG_right_curly

   (unsigned char *)"-", // RT_TG_opt_hyph

   (unsigned char *)"deftab",

   (unsigned char *)"red",
   (unsigned char *)"green",
   (unsigned char *)"blue",

   (unsigned char *)"nosupersub",

   (unsigned char *)"stylesheet",
   (unsigned char *)"snext",
   (unsigned char *)"additive",
   (unsigned char *)"sbasedon",

   (unsigned char *)"margl",
   (unsigned char *)"margr",
   (unsigned char *)"margt",
   (unsigned char *)"margb",
   (unsigned char *)"margmirror",
   (unsigned char *)"dgmargins",
   (unsigned char *)"dgmargin",
   (unsigned char *)"lndscpsxn",
   (unsigned char *)"titlepg",
   (unsigned char *)"sectlinegrid",

   (unsigned char *)"nestcell",
   (unsigned char *)"nonesttables",
   (unsigned char *)"nesttableprops",
   (unsigned char *)"nestrow",

   (unsigned char *)"footerf",

   (unsigned char *)"revised",
   (unsigned char *)"revauth",
   (unsigned char *)"revdttm",
   (unsigned char *)"deleted",

   (unsigned char *)"hyphhotz",
   (unsigned char *)"hyphauto",
   (unsigned char *)"viewzk",
   (unsigned char *)"bdrrlswsix",
   (unsigned char *)"pgnrestart",
   (unsigned char *)"colsx",
   (unsigned char *)"expnd",
   (unsigned char *)"expndtw",

   (unsigned char *)"page",

   (unsigned char *)"sb",
   (unsigned char *)"sa",
   (unsigned char *)"kerning",

   (unsigned char *)"xe",

   (unsigned char *)"splytwnine",
   (unsigned char *)"ftnlytwnine",
   (unsigned char *)"htmautsp",
   (unsigned char *)"useltbaln",
   (unsigned char *)"alntblind",
   (unsigned char *)"lytcalctblwd",
   (unsigned char *)"lyttblrtgr",
   (unsigned char *)"lnbrkrule",
   (unsigned char *)"trqc",

   (unsigned char *)"datafield",

   (unsigned char *)"c",
   (unsigned char *)"z",

   (unsigned char *)"tldot",

   (unsigned char *)"charscalex",

   (unsigned char *)"bkmkstart",
   (unsigned char *)"bkmkend",

   (unsigned char *)"userprops",
   (unsigned char *)"propname",
   (unsigned char *)"proptype",
   (unsigned char *)"staticval",

   (unsigned char *)"brdrb",
   (unsigned char *)"brsp",

   (unsigned char *)"tdfrmtxtLeft",
   (unsigned char *)"tdfrmtxtRight",
   (unsigned char *)"tpvpara",
   (unsigned char *)"tphmrg",
   (unsigned char *)"tposy",

   (unsigned char *)"column",

   (unsigned char *)"atrfstart",
   (unsigned char *)"atrfend",
   (unsigned char *)"atnid",
   (unsigned char *)"atnauthor",
   (unsigned char *)"chatn",
   (unsigned char *)"annotation",
   (unsigned char *)"atnref",

   NULL
};


unsigned char *lpszaRtfFieldTypesTags[RT_TT_RTF_NumOfFieldTypes+1] =
{
   (unsigned char *)"",
   (unsigned char *)"SYMBOL",
   (unsigned char *)"HYPERLINK",

   NULL
};


unsigned char lpszRtfCtrlChars[] =   "{}\\";
unsigned char lpszRtfCtrlsAndSpaces[] = "{}\\ \t\r\n\f";
unsigned char lpszRtfListDelims[] = ",;";
unsigned char lpszRtfCtrlsSpacesAndDelims[] = "{}\\ \t\r\n\f,;"; // "{}\\ \t\r\n\f,;-";

unsigned char lpszRtfProcSpcs[] = " ";
unsigned char lpszRtfProcSpcEol[] = " \r\n";
unsigned char lpszRtfProcTabDelims[] = "\t\v\f";


// ================================================== methods of RT_FontDescriptor_tag
// --------------------------------------------------
RT_FontDescriptor_tag::RT_FontDescriptor_tag(void)
{
   bLastEntry=False;
   bDefined=False;
   iRtfCodeTable=RT_NoCodeTable;
// iKptCodeTable=KPT_NoCodeTable;
// szFontName[0]=Nul;
   iFontType=RT_TG_FNil;
}


// --------------------------------------------------
RT_FontDescriptor_tag::RT_FontDescriptor_tag(bool bLast, bool bDefFl, const /* unsigned */ char *lpszName, int iRCTbl, int iKpCTbl, RT_TagIds iFntType)
{
   RT_FontDescriptor_tag();
   SetLast(bLast);
   SetDefined(bDefFl);
   SetFontName((const unsigned char *)lpszName);
   SetRtfCodeTable(iRCTbl);
   SetKptCodeTable(iKpCTbl);
   SetFontType(iFntType);
}


// --------------------------------------------------
HRESULT RT_FontDescriptor_tag::SetLast(bool bLast)
{
   bLastEntry=bLast;

return(S_OK);
}


// --------------------------------------------------
HRESULT const RT_FontDescriptor_tag::IsLast(bool *pbLast)
{
   *pbLast=bLastEntry;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FontDescriptor_tag::SetDefined(bool bDefFl)
{
   bDefined=bDefFl;

return(S_OK);
}


// --------------------------------------------------
HRESULT const RT_FontDescriptor_tag::IsDefined(bool *pbDefFl)
{
   *pbDefFl=bDefined;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FontDescriptor_tag::SetRtfCodeTable(int iRCTbl)
{
HRESULT retc=S_OK;

   if((iRCTbl>=0) && (iRCTbl<RT_MAX_NUM_OF_RTF_CTBLS))
   {
      iRtfCodeTable=iRCTbl;
      retc=SetKptCodeTable(ConvertRtf2KptCTbl(iRCTbl));
   }
   else if((iRCTbl==RT_NoCodeTable) || (iRCTbl==RT_UnknownCodeTable))
   {
      iRtfCodeTable=iRCTbl;
      retc=SetKptCodeTable(KPT_NoCodeTable);
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT const RT_FontDescriptor_tag::GetRtfCodeTable(int *piRCTbl)
{
   *piRCTbl=iRtfCodeTable;

return(S_OK);
}


// --------------------------------------------------
#if FALSE
HRESULT RT_FontDescriptor_tag::SetKptCodeTable(int iKpCTbl)
{
HRESULT retc=S_OK;

   if(((iKpCTbl>0) && (iKpCTbl<KPT_Ctnum)) || (iKpCTbl==KPT_NoCodeTable))
      iKptCodeTable=iKpCTbl;
   else
   {
      iKptCodeTable=KPT_NoCodeTable;
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}
#endif


// --------------------------------------------------
#if FALSE
HRESULT const RT_FontDescriptor_tag::GetKptCodeTable(int *piKpCTbl)
{
   *piKpCTbl=iKptCodeTable;

return(S_OK);
}
#endif


// --------------------------------------------------
HRESULT RT_FontDescriptor_tag::SetFontType(RT_TagIds iType)
{
HRESULT retc=S_OK;

   if((iType!=RT_TG_FNil) && (iType!=RT_TG_FRoman) && (iType!=RT_TG_FSwiss) && (iType!=RT_TG_FModern))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) iFontType=iType;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FontDescriptor_tag::GetFontType(RT_TagIds *piType)
{
   *piType=iFontType;

return(S_OK);
}


// ================================================== methods of FieldDescriptor_tag
// --------------------------------------------------
RT_FieldDescriptor_tag::RT_FieldDescriptor_tag(RT_FieldDescriptor_tag *pPField)
{
   iFieldType=RT_TT_Unknown;
   iRTFieldType=RT_TT_RTF_FieldUnknown;
   pParentField=pPField;
   iFont=RT_FONT_UNDEFINED;
   bBoldFl=False;
   bItFl=False;
   m_bSubFl=False;
   m_bSuperFl=False;
   bHiddenFl=False;
   bXrefFl=False;
   iCapsInd=VT_CapsUndefined;
   lTblWdt=0L;
   iNumOfTblCls=0;
}


// --------------------------------------------------
RT_FieldDescriptor_tag::~RT_FieldDescriptor_tag(void)
{
HRESULT retc = S_OK;

   KP_DELETE(pParentField);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetFieldType(RT_FieldTypes iFieldTp)
{
HRESULT retc=S_OK;

   if(iFieldTp<RT_TT_NumOfFieldTypes) iFieldType=iFieldTp;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetFieldType(RT_FieldTypes *piFieldTp)
{
HRESULT retc=S_OK;

   if(piFieldTp==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piFieldTp=iFieldType;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetRTFieldType(RT_RTF_FieldTypes iFieldTp)
{
HRESULT retc=S_OK;

   if(iFieldTp<RT_TT_RTF_NumOfFieldTypes) iRTFieldType=iFieldTp;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetRTFieldType(RT_RTF_FieldTypes *piFieldTp)
{
HRESULT retc=S_OK;

   if(piFieldTp==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piFieldTp=iRTFieldType;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetFieldFlags(int *piFieldFlags)
{
HRESULT retc=S_OK;
int flags=KPS_FlagsUndef;
bool flag;
CapsIndicators caps;

   if(piFieldFlags==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetBold(&flag);
   if(SUCCEEDED(retc))
   {
      if(flag) flags|=KPS_BoldFl;
      else flags|=KPS_NoBoldFl;
   }

   if(SUCCEEDED(retc)) retc=GetIt(&flag);
   if(SUCCEEDED(retc))
   {
      if(flag) flags|=KPS_ItalicFl;
      else flags|=KPS_NoItalicFl;
   }

   if(SUCCEEDED(retc)) retc=GetHidden(&flag);
   if(SUCCEEDED(retc))
   {
      if(flag) flags|=KPS_HiddenFl;
      else flags|=KPS_NoHiddenFl;
   }


   if(SUCCEEDED(retc)) retc=GetCaps(&caps);
   if(SUCCEEDED(retc)) switch(caps)
   {
   case VT_CapsUndefined:  flags|=KPS_NoAnyCapsFl; break;
   case VT_ToUpper:        flags|=KPS_CapsFl; break;
   case VT_ToLower:        flags|=KPS_LCaseFl; break;
   case VT_SmCaps:         flags|=KPS_SmCapsFl; break;
   }

   if(SUCCEEDED(retc)) *piFieldFlags=flags;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetTablePars(long lTableWidth, int iNumOfCols)
{

   lTblWdt=lTableWidth;
   iNumOfTblCls=iNumOfCols;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetTablePars(long *plTableWidth, int *piNumOfCols)
{

      *plTableWidth=lTblWdt;
      *piNumOfCols=iNumOfTblCls;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetParField(RT_FieldDescriptor_tag *pParField)
{
   pParentField=pParField;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetParField(RT_FieldDescriptor_tag **ppParField)
{
   *ppParField=pParentField;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetFont(int *piFnt)
{
   *piFnt=iFont;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetFont(int iFnt)
{
HRESULT retc=S_OK;

   if(((iFnt<0) || (iFnt>=RT_MAX_NUM_OF_FONTS)) && (iFnt!=RT_FONT_UNDEFINED))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) iFont=iFnt;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetCaps(CapsIndicators iCapsId)
{
HRESULT retc=S_OK;

   if(iCapsId<VT_NumOfCapsIds) iCapsInd=iCapsId;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetCaps(CapsIndicators *piCapsId)
{
HRESULT retc=S_OK;

   if(piCapsId==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *piCapsId=iCapsInd;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetBold(bool bBoldF)
{
   bBoldFl=bBoldF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetBold(bool *pbBoldF)
{
HRESULT retc=S_OK;

   if(pbBoldF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbBoldF=bBoldFl;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetIt(bool bItF)
{
   bItFl=bItF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetIt(bool *pbItF)
{
HRESULT retc=S_OK;

   if(pbItF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbItF=bItFl;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetHidden(bool bHiddenF)
{
   bHiddenFl=bHiddenF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetHidden(bool *pbHiddenF)
{
HRESULT retc=S_OK;

   if(pbHiddenF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbHiddenF=bHiddenFl;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetXref(bool bXrefF)
{
   bXrefFl=bXrefF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetXref(bool *pbXrefF)
{
HRESULT retc=S_OK;

   if(pbXrefF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbXrefF=bXrefFl;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetSub(bool bSubF)
{
   m_bSubFl=bSubF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetSub(bool *pbSubF)
{
HRESULT retc=S_OK;

   if(pbSubF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbSubF=m_bSubFl;

return(retc);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::SetSuper(bool bSuperF)
{
   m_bSuperFl=bSuperF;

return(S_OK);
}


// --------------------------------------------------
HRESULT RT_FieldDescriptor_tag::GetSuper(bool *pbSuperF)
{
HRESULT retc=S_OK;

   if(pbSuperF==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   else
      *pbSuperF=m_bSuperFl;

return(retc);
}


// --------------------------------------------------
TvRtfIO::TvRtfIO(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   m_lhOpenResult = S_OK;
   lpfRtfFile=NULL;
   pFonts=NULL;
   iNumOfFonts=0;

   iLTFontIndex=RT_FONT_UNDEFINED;
   iLTAccFontIndex=RT_FONT_UNDEFINED;
   iSymbolFontIndex=RT_FONT_UNDEFINED;
   iStdWinFontIndex=RT_FONT_UNDEFINED;
   iCEFontIndex=RT_FONT_UNDEFINED;

   pCurrentField = NULL;
   KP_NEW(pCurrentField, RT_FieldDescriptor_tag(NULL));

   iFldDepth = 0;

   m_lpszTextVal[0] = Nul;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// --------------------------------------------------
TvRtfIO::~TvRtfIO(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
RT_FieldDescriptor_tag *par_f;

   if(pCurrentField!=NULL)
   {
      retc0 = pCurrentField->GetParField(&par_f);
      if((par_f != NULL) && SUCCEEDED(retc0))
         KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      KP_DELETE(pCurrentField);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if((iFldDepth!=0) && SUCCEEDED(retc0))
      retc0=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT TvRtfIO::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// -------------------------------
HRESULT TvRtfIO::Reset(void)
{
HRESULT retc=S_OK;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      retc=lpfRtfFile->Reset();

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::GetFieldType(RT_FieldTypes *piFieldTp)
{
HRESULT retc=S_OK;

   if((pCurrentField==NULL) || (piFieldTp==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->GetFieldType(piFieldTp);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::SetRTFieldType(RT_RTF_FieldTypes iRTFieldType)
{
HRESULT retc=S_OK;
RT_FieldDescriptor_tag *field_ptr;
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;

   field_ptr=pCurrentField;
   do
   {
      if(field_ptr && SUCCEEDED(retc))
      {
         retc=field_ptr->GetFieldType(&field_type);
         if((field_type==RT_TT_RTF_Field) && SUCCEEDED(retc))
         {
            retc=field_ptr->GetRTFieldType(&rtf_field_type);
//          if((rtf_field_type!=RT_TT_RTF_FieldUnknown) && (rtf_field_type!=RT_TT_RTF_HypField) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               if(rtf_field_type==RT_TT_RTF_FieldUnknown)
                  retc=field_ptr->SetRTFieldType(iRTFieldType);
               else break;
            }
         }

         if(SUCCEEDED(retc)) retc=field_ptr->GetParField(&field_ptr);
      }

   } while (field_ptr && (field_type==RT_TT_RTF_Field) && SUCCEEDED(retc));

return(retc);
}




// --------------------------------------------------
HRESULT TvRtfIO::SetXref(bool bXrefF)
{
HRESULT retc=S_OK;
RT_FieldDescriptor_tag *field_ptr;
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;

   field_ptr=pCurrentField;
   do
   {
      if(field_ptr && SUCCEEDED(retc))
      {
         retc=field_ptr->GetFieldType(&field_type);
         if((field_type==RT_TT_RTF_Field) && SUCCEEDED(retc))
         {
            retc=field_ptr->GetRTFieldType(&rtf_field_type);
            if(SUCCEEDED(retc))
            {
//             if(rtf_field_type==RT_TT_RTF_HypField)
                  retc=field_ptr->SetXref(bXrefF);
//             else break;
            }
         }

         if(SUCCEEDED(retc)) retc=field_ptr->GetParField(&field_ptr);
      }

   } while (field_ptr && (field_type==RT_TT_RTF_Field) && SUCCEEDED(retc));

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::GetFieldFlags(int *piFieldFlags)
{
HRESULT retc=S_OK;

   if((pCurrentField==NULL) || (piFieldFlags==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->GetFieldFlags(piFieldFlags);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::SetFont(int iFnt)
{
HRESULT retc=S_OK;
bool font_defined;
// int rtf_tbl;
UC_Modes enc_mode;
int ctbl;
int kpt_tbl;

   if(((iFnt<0) || (iFnt>=RT_MAX_NUM_OF_FONTS) || (iFnt>iNumOfFonts)) && (iFnt!=RT_FONT_UNDEFINED))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((pFonts==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if((iFnt!=RT_FONT_UNDEFINED) && SUCCEEDED(retc))
   {
      retc=pFonts[iFnt].IsDefined(&font_defined);
      if((!font_defined) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) retc=pCurrentField->SetFont(iFnt);

   if(SUCCEEDED(retc))
   {
      if(iFnt!=RT_FONT_UNDEFINED)
      {
//       retc=pFonts[iFnt].GetRtfCodeTable(&rtf_tbl);
//       if(SUCCEEDED(retc))
//       {
//          kpt_tbl=ConvertRtf2KptCTbl(rtf_tbl);
//          if(kpt_tbl==KPT_NoCodeTable) kpt_tbl=1;
//       }
//       else kpt_tbl=1;

//       retc=iaTypefaces[iFnt].GetKptCodeTable(&kpt_tbl);

         retc=pFonts[iFnt].GetKptCodeTable(&kpt_tbl);
      }
      else kpt_tbl=1;
   }
   if(SUCCEEDED(retc)) retc=lpfRtfFile->GetEncoding(&enc_mode, &ctbl);
   if(SUCCEEDED(retc)) retc=lpfRtfFile->SetEncoding(enc_mode, kpt_tbl);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::PushField(RT_FieldTypes *piFieldType, int *piCurFont)
{
HRESULT retc=S_OK;
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;
RT_FieldDescriptor_tag *par_field;
int cur_font;
bool bold_fl;
bool it_fl;
CapsIndicators caps_ind;
long tb_wdt;
int col_num;
bool hid_fl;
bool xr_fl;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(&cur_font);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetBold(&bold_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetIt(&it_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetCaps(&caps_ind);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetHidden(&hid_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetXref(&xr_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetTablePars(&tb_wdt, &col_num);

   if(SUCCEEDED(retc))
   {
      par_field = pCurrentField;
      pCurrentField = NULL;
      KP_NEW(pCurrentField, RT_FieldDescriptor_tag(par_field));
      if(pCurrentField == NULL) pCurrentField = par_field;
   }

   if(SUCCEEDED(retc))
   {
      switch(field_type)
      {
      case RT_TT_Unknown:   field_type=RT_TT_Text; break;
      case RT_TT_Text:      field_type=RT_TT_Text; break;
      case RT_TT_Table:
         field_type=RT_TT_Table;
//       retc=pCurrentField->SetTablePars(tb_wdt, col_num);
         break;
      case RT_TT_FontTable: field_type=RT_TT_FontDefinition; break;
      case RT_TT_FontDefinition: field_type=RT_TT_FontDefinitionSubfield; break;
      }
      if(SUCCEEDED(retc)) retc=pCurrentField->SetFieldType(field_type);
   }
   if(SUCCEEDED(retc)) retc=pCurrentField->SetRTFieldType(rtf_field_type);

   if(SUCCEEDED(retc)) retc=SetFont(cur_font);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetBold(bold_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetIt(it_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetCaps(caps_ind);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetHidden(hid_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetXref(xr_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetTablePars(tb_wdt, col_num);

   if(SUCCEEDED(retc))
   {
      *piFieldType=field_type;
      *piCurFont=cur_font;
   }

   iFldDepth+=1;

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfIO::PopField(RT_FieldTypes *piFieldType, int *piCurFont)
{
HRESULT retc=S_OK;
RT_FieldDescriptor_tag *par_field;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->GetParField(&par_field);
   if((par_field==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->SetParField(NULL);
   if(SUCCEEDED(retc))
   {
      KP_DELETE(pCurrentField);
      pCurrentField = par_field;
   }

   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(piFieldType);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(piCurFont);
   if(SUCCEEDED(retc)) retc=SetFont(*piCurFont);

   if(iFldDepth>0) iFldDepth-=1;
   else if(SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
int TvRtfIO::GetFldDepth(void)
{
return(iFldDepth);
}


// =================================================
HRESULT CvtToRtfCtlStr(unsigned char *lpszOutStr, const unsigned char *lpszInStr, int iBufLen)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;

   if((lpszOutStr==NULL) || (lpszInStr==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszInStr;
      pntd=lpszOutStr;

      while((*pnts) && SUCCEEDED(retc))
      {
         if(*pnts<Clatsiz)
         {
            if(pntd-lpszOutStr>=iBufLen-1)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) *(pntd++)=(*pnts++);
         }
         else
         {
            if(pntd-lpszOutStr>=iBufLen-(5+strlen(plpszaRtfTagTable[RT_TG_SpecChr])))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               *(pntd++)=RT_FieldStart;
               *(pntd++)=RC_KeywordStart;
               strcpy(pntd, plpszaRtfTagTable[RT_TG_SpecChr]);
               pntd+=strlen(plpszaRtfTagTable[RT_TG_SpecChr]);
               sprintf((char *)pntd, "%02X", *pnts++);
               pntd+=2;
               *(pntd++)=RT_FieldEnd;
            }
         }
      }
   }

   *pntd=Nul;

return(retc);
}


// =================================================
const unsigned char *rtf_head_rtf = { (const unsigned char *)
"{\\rtf1"
"{\\fonttbl"
   "{\\f0\\froman\\fcharset1\\fprq2 %s;}" // DEFAULT_CHARSET
"}"
"{\\stylesheet"
   "{\\f0 Normal;}"
   "{\\*\\cs10\\f0 \\additive Default Paragraph Font;}"
   "{\\s99\\f0 Ctrlstyle;}"
"}"
//   {
//      \colortbl;\red0\green0\blue0;\red0\green0\blue255;\red0\green255\blue255;\red0\green255\blue0;\red255\green0\blue255;\red255\green0\blue0;\red255\green255\blue0;\red255\green255\blue255;
//      \red0\green0\blue128;\red0\green128\blue128;\red0\green128\blue0;\red128\green0\blue128;\red128\green0\blue0;\red128\green128\blue0;\red128\green128\blue128;\red192\green192\blue192;
//   }
"{\\s99\\pard\\plain\\f0{"};
const unsigned char *uni_fmt = {(const unsigned char *)"\\u%d\\\'3f"};
const unsigned char *rtf_tail_rtf = {(const unsigned char *)"}}}"};

HRESULT RtUnicodeToRtf(unsigned char *lpszRtfBuf, const UniChar *sUniText, int iRtfBufSize, const unsigned char *lpszTypeFace)
{
HRESULT retc=S_OK;
const UniChar *pnts;
unsigned char *pntd;

   if(((lpszRtfBuf==NULL) || (sUniText == NULL) || (lpszTypeFace==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((strlen(rtf_head_rtf) + strlen(lpszTypeFace) + 1) >= iRtfBufSize)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)lpszRtfBuf, (const char *)rtf_head_rtf, lpszTypeFace);

      pnts = sUniText;
      pntd = lpszRtfBuf + strlen(lpszRtfBuf);

      while(*pnts && SUCCEEDED(retc))
      {
         if(*pnts < KPT_FirstKptChar)
         {
            if((pntd - lpszRtfBuf + 1) >= iRtfBufSize)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) *pntd++ = (unsigned char)*pnts;
         }
         else
         {
            if((pntd - lpszRtfBuf + strlen(uni_fmt) + MAX_LONG_DIGITS + 1) >= iRtfBufSize)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               sprintf((char *)pntd, (const char *)uni_fmt, *pnts);
               pntd += strlen(pntd);
            }
         }

         pnts++;
      }
   }

   if(SUCCEEDED(retc))
      if((pntd - lpszRtfBuf + strlen(rtf_tail_rtf) + 1) >= iRtfBufSize)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) strcpy(pntd, rtf_tail_rtf);

return(retc);
}

