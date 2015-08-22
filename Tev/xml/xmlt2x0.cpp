// ==================================================
// xmlt2x0.cpp, former lvzt2x.cpp
// converting XML dictionary to (LVZ03) TeX file
// common methods of parent class
//


// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

// #include <iostream.h>
#include <iostream>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlsty.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmlt2x0.h"


#if Envir!=MSWin32Con
#error Envir!=MSWin32Con
#endif


// ================================================== public methods of XmlT2X0
void XmlT2X0::XmlT2X0_constructor(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bTagFormat)
{
   m_lhOpenResult=S_OK;

   m_lEntryId=0L;
   KpErrorProc.SetLPar(0L);

   m_bTagOutFormat=bTagFormat;

   m_iaLastHw[0]=C_Nul;

// --------------------------
   m_lpszInFileName[0]=Nul;
   m_lpInFileObj=NULL;

   m_lpszOutFileName[0]=Nul;
   m_lpOutFileObj=NULL;

// --------------------------
   m_pTagStack=NULL;
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_pTagStack = new TvXmlTagStack(NULL, C_Nul, NULL, 0);
      if(m_pTagStack==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

// --------------------------
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=OpenFilesLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlT2X0::~XmlT2X0(void)
{
TvXmlTagStack *prev_stack_ptr;
KpChar cur_tag;

   CloseFiles(False);

   if(m_pTagStack!=NULL)
   {
      m_pTagStack->GetPrevTagPtr(&prev_stack_ptr);
      m_pTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      KP_DELETE(m_pTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT XmlT2X0::OpenFiles(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

// --------------------------------------------------
   if((lpszInFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszInFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszInFileName, lpszInFname);
      m_lpInFileObj = new XmlI(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, True, True);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

// --------------------------
   if((lpszOutFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszOutFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszOutFileName, lpszOutFname);
      m_lpOutFileObj = new TvTexFile(m_lpszOutFileName, (const unsigned char *)"w", iNumOfTexTagsLocal);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2X0::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(m_lpOutFileObj!=NULL)
   {
      retc0=m_lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(m_lpInFileObj!=NULL)
   {
      KP_DELETE(m_lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2X0::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlT2X0::WriteHeader(const unsigned char *lpszLetId, const unsigned char *lpszFullLetId, const unsigned char *PageNo, int iBoxWdt, int iBoxVskip)
{
HRESULT retc=S_OK;
unsigned char str_buf[20];
const unsigned char *pnts;
KpChar out_ch;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_Project, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszXmlT2X_ProjName, False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_Publisher, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"TEV\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_Stage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"200\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_Pages, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_TID, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"xmlt2x\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"---------------------------------------\n", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"öitas failas sugeneruotas automati÷kai\n", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszXmlT2X_OrigPrompt, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_theraide, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);

// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszLetId, False);
   if(SUCCEEDED(retc))
   {
      pnts=lpszLetId;
      while((*pnts) && SUCCEEDED(retc))
      {
         if(*pnts==Spc) retc=m_lpOutFileObj->PutCharProc(C_NBSP, TexNoType, False, LAST_WORD_LEN);
         else
         {
            retc=KptCharEncode(&out_ch, *pnts, 50);
            if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(out_ch, TexNoType, False, LAST_WORD_LEN);
         }
         pnts++;
      }
   }

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_hboxup, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"#1", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_hbox, TexNoType, False, LAST_WORD_LEN);
   sprintf((char *)str_buf, "to %dcm", iBoxWdt);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(str_buf, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"#1", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_nuleisti, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);
   sprintf((char *)str_buf, "%d.%02dmm", iBoxVskip/100, iBoxVskip%100);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(str_buf, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_input, TexNoType, False, LAST_WORD_LEN);
//// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"init.sty", False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_input, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszTexStyleName, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_VIEW, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_HPROOF, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_CRC, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_firstpage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(PageNo, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_pageno, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_firstpage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if((!bDoubleColumns) && SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_begindoublecolumns, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_raide, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszFullLetId, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(m_bTagOutFormat && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_settabs, TexNoType, False, LAST_WORD_LEN);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, " %d ", XN_TABS_PER_COL);
         retc=m_lpOutFileObj->PutStr(str_buf, False);
      }
      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_columns, TexNoType, False, LAST_WORD_LEN);
      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_plus, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_SP_Amp, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_SP_Amp, TexNoType, False, LAST_WORD_LEN);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2X0::WriteTail(const unsigned char *lpszLetIdLat, const unsigned char *lpszLastMark)
{
HRESULT retc=S_OK;
int last_char=C_Nul;
int char_pos=0;
const KpChar *pnts;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

// if(m_bTagOutFormat && SUCCEEDED(retc))
// {
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_cr, TexNoType, False, LAST_WORD_LEN);
//
////  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_break, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);
// }


// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_zmark, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc((KpChar)TX_TG_endfile, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);

// if(TvIntStrLen(lpszLastMark)==0)
   if(strlen(lpszLastMark)==0)
   {
//    if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutIntStrProc(m_iaLastHw, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=PutTexIntStr(m_lpOutFileObj, m_iaLastHw, &last_char, XC_Dict, NULL, m_bTagOutFormat, &char_pos, 0, TvIntStrLen(m_iaLastHw), LAST_WORD_LEN);
      pnts=m_iaLastHw;
      if(SUCCEEDED(retc)) if(pnts) while(*pnts)
         retc=m_lpOutFileObj->PutCharProc(CvtToTex(*pnts++), TexNoType, False, LAST_WORD_LEN);
   }
   else
      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszLastMark, False);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszLetIdLat, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);

//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_input, TexNoType, False, LAST_WORD_LEN);
//// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Spc, False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszXmlT2X_AppPref, False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr(lpszLetIdLat, False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)".app", False);
//// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);
//
//   if((!bDoubleColumns) && SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(TX_CH_CommentStart, False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_enddoublecolumns, TexNoType, False, LAST_WORD_LEN);
//// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
//   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);

// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(TX_TG_end, TexNoType, False, LAST_WORD_LEN);
//// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutStr((const unsigned char *)"\n", False);
// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutChar(Lf, True);

return(retc);
}
