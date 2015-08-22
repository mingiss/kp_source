// ==================================================
// xmlp.cpp
// XML tag parameters
//


// ==================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
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
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"



// ==================================== class XmlParRec methods
HRESULT XmlParRec::InitMembers(void)
{
   m_lhOpenResult = S_OK;

   m_iValCtbl = 1;

   m_lpszParName[0] = Nul;
   m_lpszParValue[0] = Nul;
   m_iazIntParValue[0] = C_Nul;

return(m_lhOpenResult);
}


// -------------------------------------
XmlParRec::XmlParRec(void)
{
   m_lhOpenResult = InitMembers();
}


// -------------------------------------
XmlParRec::XmlParRec(const unsigned char *lpszParNam, const unsigned char *lpszParVal, const KpChar *iazIntParVal, int iValCtbl)
// void XmlParRec::Constructor(const unsigned char *lpszParNam, const unsigned char *lpszParVal, const KpChar *iazIntParVal)
{
   m_lhOpenResult = InitMembers();

   if((lpszParNam == NULL) && SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult = KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszParNam, True, __FILE__, __LINE__, 0L);

// PutLogMessage_("XmlParRec::XmlParRec() 1");
   if(SUCCEEDED(m_lhOpenResult))
   {
      if(strlen(lpszParNam) < TV_TAG_LEN) strcpy(m_lpszParName, lpszParNam);
      else
         m_lhOpenResult = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, lpszParNam, True, __FILE__, __LINE__, 0L);
   }

// PutLogMessage_("XmlParRec::XmlParRec() 2");
   if((iValCtbl < 0 ) || (iValCtbl >= KPT_Ctnum))
      m_lhOpenResult = KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszParNam, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(m_lhOpenResult)) m_iValCtbl = iValCtbl;

// PutLogMessage_("XmlParRec::XmlParRec() 3");
   if((lpszParVal != NULL) && SUCCEEDED(m_lhOpenResult))
   {
      if(strlen(lpszParVal) < MAX_XML_PAR_VAL_LEN) strcpy(m_lpszParValue, lpszParVal);
      else
      {
//       lpszParVal[min(MAX_XML_PAR_VAL_LEN, 20)] = Nul;
         m_lhOpenResult = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, lpszParVal, True, __FILE__, __LINE__, 0L);
      }
   }

// PutLogMessage_("XmlParRec::XmlParRec() 4");
   if((iazIntParVal != NULL) && SUCCEEDED(m_lhOpenResult))
   {
      if(TvKpStrLen(iazIntParVal) < MAX_XML_PAR_VAL_LEN) TvKpStrCpy(m_iazIntParValue, iazIntParVal);
      else
         m_lhOpenResult = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);
   }

// PutLogMessage_("XmlParRec::XmlParRec() 5");
   if((m_lpszParValue[0] == Nul) && (m_iazIntParValue[0] != C_Nul) && SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult = UniformValuesFromInt();


// PutLogMessage_("XmlParRec::XmlParRec() 6");
   if((m_lpszParValue[0] != Nul) && (m_iazIntParValue[0] == C_Nul) && SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult = UniformValuesFromStr();
// PutLogMessage_("XmlParRec::XmlParRec() 7");
}


// ----------------------
HRESULT XmlParRec::GetOpenResult(void) const
{
return(m_lhOpenResult);
}


//-----------------------------------
int XmlParRec::GetValCtbl(void) const
{
return(m_iValCtbl);
}


// ----------------------
HRESULT XmlParRec::UniformValuesFromStr(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
   {
      retc = KptStrEncode(m_iazIntParValue, m_lpszParValue, m_iValCtbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
         retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


HRESULT XmlParRec::UniformValuesFromInt(void)
{
HRESULT retc=S_OK;
KpChar *par_val_buf_i = NULL;

   KP_NEWA(par_val_buf_i, KpChar, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc))
   {
      TvKpStrCpy(par_val_buf_i, m_iazIntParValue);
      TvKpStrLat(par_val_buf_i);
      retc = KptStrDecode(m_lpszParValue, par_val_buf_i, 1);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
         retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

   KP_DELETEA(par_val_buf_i);

return(retc);
}


// ==================================== class XmlTagPars methods
HRESULT XmlTagPars::UniformValuesFromInt(void)
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = par_rec_ptr->UniformValuesFromInt();

return(retc);
}


HRESULT XmlTagPars::UniformValuesFromStr(void)
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = par_rec_ptr->UniformValuesFromStr();

return(retc);
}


HRESULT XmlTagPars::UniformValuesFromPars(bool bBreakLines)
{
HRESULT retc=S_OK;
XmlTagPars *par_ptr = NULL;
unsigned char *pntd;
int ll;
XmlParRec *par_rec_ptr = NULL;
XmlParRec *sub_par_rec_ptr = NULL;

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) pntd = par_rec_ptr->m_lpszParValue;

// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&par_ptr);
   if(SUCCEEDED(retc)) par_ptr = (XmlTagPars *)m_pFirstChild;

   while(par_ptr && SUCCEEDED(retc))
   {
      sub_par_rec_ptr = NULL;
      if(SUCCEEDED(retc)) sub_par_rec_ptr = (XmlParRec *)par_ptr->GetValue();
      KP_ASSERT(sub_par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(par_ptr->GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
      {
         ll = strlen(sub_par_rec_ptr->m_lpszParName);
         if((pntd - par_rec_ptr->m_lpszParValue) + ll + 4 + 4 + 10 >= MAX_XML_PAR_VAL_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         strcpy(pntd, bBreakLines?"   ":"");
         strcat(pntd, sub_par_rec_ptr->m_lpszParName);
         pntd += strlen(pntd);
         *pntd++ = ':';
         if(bBreakLines) *pntd++ = Spc; // ' ';
      }

      if(SUCCEEDED(retc))
      {
         ll = strlen(sub_par_rec_ptr->m_lpszParValue);
         if((pntd - par_rec_ptr->m_lpszParValue) + ll + 3 >= MAX_XML_PAR_VAL_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         strcpy(pntd, sub_par_rec_ptr->m_lpszParValue);
         pntd += ll;
         *pntd++ = ';';

         retc = par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
      }

      if(SUCCEEDED(retc))
      {
         if(par_ptr) *pntd++ = bBreakLines?Lf:Spc; // '\n' ' ';
         else if(bBreakLines) *pntd++ = Lf;
      }
   }

   if(SUCCEEDED(retc)) *pntd = Nul;

   if(SUCCEEDED(retc)) UniformValuesFromStr();

return(retc);
}


HRESULT XmlTagPars::TestValueConsistence(void) const
{
HRESULT retc = S_OK;
KpChar *par_val_buf_i = NULL;
unsigned char *par_val_buf = NULL;
XmlParRec *par_rec_ptr = NULL;

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   KP_NEWA(par_val_buf_i, KpChar, MAX_XML_PAR_VAL_LEN + 1);
   KP_NEWA(par_val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc))
   {
      TvKpStrCpy(par_val_buf_i, par_rec_ptr->m_iazIntParValue);
      TvKpStrLat(par_val_buf_i);
      retc = KptStrDecode(par_val_buf, par_val_buf_i, 1);
      if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
         retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(strcmp(par_rec_ptr->m_lpszParValue, par_val_buf) != 0)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   KP_DELETEA(par_val_buf_i);
   KP_DELETEA(par_val_buf);

return(retc);
}


// -------------------------------------
void XmlTagPars::Constructor(const unsigned char *lpszParNam, const unsigned char *lpszParVal, const KpChar *iazIntParVal, XmlTagPars * /* pFath */, int iValCtbl)
{
HRESULT retc = m_lhOpenResult; // S_OK;
XmlParRec *par_rec_ptr = NULL;

// if(SUCCEEDED(retc)) retc = InitMembers();

// PutLogMessage_("XmlTagPars::Constructor() 1");
   KP_NEW(par_rec_ptr, XmlParRec(lpszParNam, lpszParVal, iazIntParVal, iValCtbl));
   if(SUCCEEDED(retc)) retc = par_rec_ptr->GetOpenResult();

// PutLogMessage_("XmlTagPars::Constructor() 3");
// KpTreeEntry::Constructor() negerai – antrà kartà sukuria KpTreeEntry::m_lpRecord
// if(SUCCEEDED(retc)) retc = KpTreeEntry::Constructor(par_rec_ptr, sizeof(XmlParRec), pFath);
   if(SUCCEEDED(retc)) retc = SetNewValue(par_rec_ptr, sizeof(XmlParRec));

// PutLogMessage_("XmlTagPars::Constructor() 4");
   KP_DELETE(par_rec_ptr);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


//-----------------------------------
XmlTagPars::XmlTagPars(const unsigned char *lpszParNam, long lParVal, XmlTagPars *pFath, int iValCtbl)
{
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];

   sprintf((char *)par_val, "%ld", lParVal);
   Constructor(lpszParNam, par_val, NULL, pFath, iValCtbl);
}


XmlTagPars::XmlTagPars(const char *lpszParNam, long lParVal, XmlTagPars *pFath, int iValCtbl)
{
unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];

   sprintf((char *)par_val, "%ld", lParVal);
   Constructor((const unsigned char *)lpszParNam, par_val, NULL, pFath, iValCtbl);
}


//-----------------------------------
XmlTagPars::XmlTagPars(const unsigned char *lpszParNam, XmlTagPars *pParVal, XmlTagPars *pFath, int iValCtbl)
{
HRESULT retc = m_lhOpenResult; // S_OK;
XmlTagPars *first_child = NULL;

   Constructor(lpszParNam, (const unsigned char *)"", NULL, pFath, iValCtbl);

   KP_NEW(first_child, XmlTagPars(pParVal));
   if(SUCCEEDED(retc)) retc = first_child->GetOpenResult();

// if(SUCCEEDED(retc)) retc = first_child->SetFather(this);

// if(SUCCEEDED(retc)) retc = SetFirstChild(first_child);
   if(SUCCEEDED(retc)) retc = ConnectChild(first_child);
// if(SUCCEEDED(retc)) retc = AppendChild(first_child);

   if(SUCCEEDED(retc)) retc = UniformValuesFromPars(False);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


//-----------------------------------
XmlTagPars::XmlTagPars(const XmlTagPars *pSrc)
{
HRESULT retc = m_lhOpenResult; // S_OK;
static unsigned char par_nam[TV_TAG_LEN + 1];
static KpChar par_val[MAX_XML_PAR_VAL_LEN + 1];
XmlTagPars *next_brother_src = NULL;
XmlTagPars *next_brother_dst = NULL;
XmlTagPars *first_child_src = NULL;
XmlTagPars *first_child_dst = NULL;
XmlTagPars *father = NULL;

   if((pSrc==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   par_nam[0] = Nul;
   par_val[0] = C_Nul;
   if(SUCCEEDED(retc)) retc = pSrc->GetCurKpTextPar(par_nam, par_val);

// PutLogMessage_("XmlTagPars::XmlTagPars() 1 %s", par_nam);

// tëvo kopijuoti nereikia – gali susidubliuoti trinant pSrc tëvà
// naujai kuriamø tëvai prisijungs per ConnectChild()
// if(SUCCEEDED(retc)) retc = pSrc->GetFather((KpTreeEntry **)&father);
   if(SUCCEEDED(retc)) Constructor(par_nam, NULL, par_val, NULL); // father);

// PutLogMessage_("XmlTagPars::XmlTagPars() 2 %s %s", ((XmlParRec *)m_lpRecord)->m_lpszParName, ((XmlParRec *)m_lpRecord)->m_lpszParValue);

   first_child_src = NULL;
// if(SUCCEEDED(retc)) retc = pSrc->GetCurParPar(par_nam, &first_child_src);

// if(SUCCEEDED(retc)) retc = pSrc->GetFirstChild((KpTreeEntry **)&first_child_src);
   if(SUCCEEDED(retc)) first_child_src = (XmlTagPars *)pSrc->m_pFirstChild;

   if(first_child_src && SUCCEEDED(retc))
   {
      KP_NEW(first_child_dst, XmlTagPars(first_child_src));
      if(SUCCEEDED(retc)) retc = first_child_dst->GetOpenResult();
      if(FAILED(retc)) KP_DELETE(first_child_dst);

      if(SUCCEEDED(retc)) retc = ConnectChild(first_child_dst);
   }

   if(SUCCEEDED(retc)) retc=pSrc->GetNextBrother((KpTreeEntry **)&next_brother_src);
   if(next_brother_src && SUCCEEDED(retc))
   {
      KP_NEW(next_brother_dst, XmlTagPars(next_brother_src)); // recursion on brothers
      if(SUCCEEDED(retc)) retc = next_brother_dst->GetOpenResult();
      if(FAILED(retc)) KP_DELETE(next_brother_dst);

      if(SUCCEEDED(retc)) retc = ConnectBrother(next_brother_dst);
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}



// ----------------------
XmlTagPars::~XmlTagPars()
{
// PutLogMessage_("KpAlloc:KpTreeEntry::m_lpRecord %08x\t%08x\tdel[]\t%s\t%d", this, 0, __FILE__, __LINE__);
// KP_DELETE(m_lpRecord);
}


//-----------------------------------
int XmlTagPars::GetValCtbl(void) const
{
HRESULT retc = S_OK;
int ctbl = 1;
XmlParRec *par_rec_ptr = NULL;

   par_rec_ptr = (XmlParRec *)GetValue();
   if(par_rec_ptr != NULL)
   {
      KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) ctbl = par_rec_ptr->GetValCtbl();
   }

return(ctbl);
}


//-----------------------------------
HRESULT XmlTagPars::GetCurTextPar(unsigned char *lpszParNamBuf, unsigned char *lpszValBuf) const
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if((lpszParNamBuf==NULL) || (lpszValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszParNamBuf, par_rec_ptr->m_lpszParName);
      strcpy(lpszValBuf, par_rec_ptr->m_lpszParValue);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetCurKpTextPar(unsigned char *lpszParNamBuf, KpChar *iazIntValBuf) const
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if((lpszParNamBuf==NULL) || (iazIntValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszParNamBuf, par_rec_ptr->m_lpszParName);
      TvKpStrCpy(iazIntValBuf, par_rec_ptr->m_iazIntParValue);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetCurNumPar(unsigned char *lpszParNamBuf, long *plNumValBuf) const
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if((lpszParNamBuf==NULL) || (plNumValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszParNamBuf, par_rec_ptr->m_lpszParName);
      sscanf((const char *)par_rec_ptr->m_lpszParValue, "%ld", plNumValBuf);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetCurParPar(unsigned char *lpszParNamBuf, XmlTagPars **pValParPtr) const
{
HRESULT retc=S_OK;
XmlParRec *par_rec_ptr = NULL;

   if((lpszParNamBuf==NULL) || (pValParPtr==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(lpszParNamBuf, par_rec_ptr->m_lpszParName);
//    retc = GetFirstChild((KpTreeEntry **)pValParPtr);
      *pValParPtr = (XmlTagPars *)m_pFirstChild;
   }

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetTextPar(unsigned char *lpszParNamBuf, unsigned char *m_lpszValBuf, int iParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
int ii;

   if((lpszParNamBuf==NULL) || (m_lpszValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      par_ptr=this;
      for(ii=0; (ii<iParNum) && SUCCEEDED(retc); ii++)
      {
         retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
         if((par_ptr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) retc=par_ptr->GetCurTextPar(lpszParNamBuf, m_lpszValBuf);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetKpTextPar(unsigned char *lpszParNamBuf, KpChar *iazIntValBuf, int iParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
int ii;

   if((lpszParNamBuf==NULL) || (iazIntValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      par_ptr=this;
      for(ii=0; (ii<iParNum) && SUCCEEDED(retc); ii++)
      {
         retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
         if((par_ptr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) retc=par_ptr->GetCurKpTextPar(lpszParNamBuf, iazIntValBuf);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetNumPar(unsigned char *lpszParNamBuf, long *plNumValBuf, int iParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
int ii;

   if((lpszParNamBuf==NULL) || (plNumValBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      par_ptr=this;
      for(ii=0; (ii<iParNum) && SUCCEEDED(retc); ii++)
      {
         retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
         if((par_ptr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) retc=par_ptr->GetCurNumPar(lpszParNamBuf, plNumValBuf);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SeekTextPar(const char *lpszParNam, unsigned char *lpszValBuf, int *piParNum) const
{
return(SeekTextPar((const unsigned char *)lpszParNam, lpszValBuf, piParNum));
}

HRESULT XmlTagPars::SeekTextPar(const unsigned char *lpszParNam, unsigned char *lpszValBuf, int *piParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
static unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char test_par_nam[TV_TAG_LEN+1];
int par_num = 0;

   if((lpszParNam==NULL) || (lpszValBuf==NULL) /* || (piParNum == NULL) */)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(test_par_nam, lpszParNam);
      strlwr(test_par_nam);
   }

   if(SUCCEEDED(retc))
   {
      par_num = 0;
      par_ptr = this;
      while((par_ptr!=NULL) && SUCCEEDED(retc))
      {
         retc=par_ptr->GetCurTextPar(par_nam, lpszValBuf);
         if(SUCCEEDED(retc))
         {
            strlwr(par_nam);
            if(strcmp(par_nam, test_par_nam)==0) break;
            else
            {
               retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
               par_num++;
            }
         }
      }
   }

   if((par_ptr == NULL) && SUCCEEDED(retc)) retc = KP_E_KWD_NOT_FOUND;
   if((piParNum != NULL) && SUCCEEDED(retc)) *piParNum = par_num;

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SeekKpTextPar(const char *lpszParNam, KpChar *iazIntValBuf, int *piParNum) const
{
return(SeekKpTextPar((const unsigned char *)lpszParNam, iazIntValBuf, piParNum));
}

HRESULT XmlTagPars::SeekKpTextPar(const unsigned char *lpszParNam, KpChar *iazIntValBuf, int *piParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
static unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char test_par_nam[TV_TAG_LEN+1];

   if((lpszParNam==NULL) || (iazIntValBuf==NULL) || (piParNum==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(test_par_nam, lpszParNam);
      strlwr(test_par_nam);
   }

   if(SUCCEEDED(retc))
   {
      *piParNum=0;
      par_ptr=this;
      while((par_ptr!=NULL) && SUCCEEDED(retc))
      {
         retc=par_ptr->GetCurKpTextPar(par_nam, iazIntValBuf);
         if(SUCCEEDED(retc))
         {
            strlwr(par_nam);
            if(strcmp(par_nam, test_par_nam)==0) break;
            else
            {
               retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
               (*piParNum)++;
            }
         }
      }
   }

   if((par_ptr==NULL) && SUCCEEDED(retc)) retc=KP_E_KWD_NOT_FOUND;

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SeekNumPar(const char *lpszParNam, long *plNumValBuf, int *piParNum) const
{
return(SeekNumPar((const unsigned char *)lpszParNam, plNumValBuf, piParNum));
}

HRESULT XmlTagPars::SeekNumPar(const unsigned char *lpszParNam, long *plNumValBuf, int *piParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
static unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char test_par_nam[TV_TAG_LEN+1];

   if((lpszParNam==NULL) || (plNumValBuf==NULL) || (piParNum==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(test_par_nam, lpszParNam);
      strlwr(test_par_nam);
   }

   if(SUCCEEDED(retc))
   {
      *piParNum=0;
      par_ptr=this;
      while((par_ptr!=NULL) && SUCCEEDED(retc))
      {
         retc=par_ptr->GetCurNumPar(par_nam, plNumValBuf);
         if(SUCCEEDED(retc))
         {
            strlwr(par_nam);
            if(strcmp(par_nam, test_par_nam)==0) break;
            else
            {
               retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
               (*piParNum)++;
            }
         }
      }
   }

   if((par_ptr==NULL) && SUCCEEDED(retc)) retc=KP_E_KWD_NOT_FOUND;

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SeekParPar(const char *lpszParNam, XmlTagPars **pValParPtr, int *piParNum) const
{
HRESULT retc=S_OK;
const XmlTagPars *par_ptr;
static unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char test_par_nam[TV_TAG_LEN+1];

   if((lpszParNam==NULL) || (pValParPtr==NULL) || (piParNum==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(test_par_nam, lpszParNam);
      strlwr(test_par_nam);
   }

   if(SUCCEEDED(retc))
   {
      *piParNum=0;
      par_ptr=this;
      while((par_ptr!=NULL) && SUCCEEDED(retc))
      {
         retc=par_ptr->GetCurParPar(par_nam, pValParPtr);
         if(SUCCEEDED(retc))
         {
            strlwr(par_nam);
            if(strcmp(par_nam, test_par_nam)==0) break;
            else
            {
               retc=par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);
               (*piParNum)++;
            }
         }
      }
   }

   if((par_ptr==NULL) && SUCCEEDED(retc)) retc=KP_E_KWD_NOT_FOUND;

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SeekParPtr(const char *lpszParNam, XmlTagPars **pParPtr)
{
return(SeekParPtr((unsigned const char *)lpszParNam, pParPtr));
}

HRESULT XmlTagPars::SeekParPtr(const unsigned char *lpszParNam, XmlTagPars **pParPtr)
{
HRESULT retc=S_OK;
unsigned char par_nam[TV_TAG_LEN + 1];
unsigned char test_par_nam[TV_TAG_LEN + 1];

unsigned char *val_buf = null;
	KP_NEWA(val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   if(((lpszParNam==NULL) || (pParPtr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(test_par_nam, lpszParNam);
      strlwr(test_par_nam);
   }

   if(SUCCEEDED(retc))
   {
      *pParPtr=this;
      while((*pParPtr!=NULL) && SUCCEEDED(retc))
      {
         retc=(*pParPtr)->GetCurTextPar(par_nam, val_buf);
         if(SUCCEEDED(retc))
         {
            strlwr(par_nam);
            if(strcmp(par_nam, test_par_nam)==0) break;
            else retc=(*pParPtr)->GetNextBrother((KpTreeEntry **)pParPtr);
         }
      }
   }

   if((*pParPtr==NULL) && SUCCEEDED(retc)) retc = KP_E_KWD_NOT_FOUND;

   KP_DELETEA(val_buf);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::PointParPtr(int iParNum, XmlTagPars **pParPtr)
{
HRESULT retc=S_OK;
int ii;

   if((pParPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pParPtr=this;
      for(ii = 0; (ii < iParNum) && (*pParPtr!=NULL) && SUCCEEDED(retc); ii++)
         retc=(*pParPtr)->GetNextBrother((KpTreeEntry **)pParPtr);
   }
   if(SUCCEEDED(retc)) if(*pParPtr == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::GetParCnt(int *piParCnt) const
{
HRESULT retc=S_OK;
const XmlTagPars *tag_par;

   if((piParCnt == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piParCnt = 0;
      tag_par = this;
      while(tag_par && SUCCEEDED(retc))
      {
         (*piParCnt)++;
         retc=tag_par->GetNextBrother((KpTreeEntry **)&tag_par);
      }
   }

return(retc);
}


//-----------------------------------
#if FALSE
HRESULT XmlTagPars::AddPar(XmlTagPars *pNextPar)
{
HRESULT retc=S_OK;
XmlTagPars *tag_par_sav;
XmlTagPars *tag_par;

   if(pNextPar==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      tag_par_sav=this;
      do
      {
         retc=tag_par_sav->GetNextBrother((KpTreeEntry **)&tag_par);
         if(tag_par==NULL) break;
         tag_par_sav=tag_par;

      } while(SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc=tag_par_sav->ConnectBrother(pNextPar);
   }

return(retc);
}
#endif


//-----------------------------------
HRESULT XmlTagPars::AddTextPar(const unsigned char *lpszParNam, const unsigned char *lpszParVal)
{
HRESULT retc=S_OK;
XmlTagPars *tmp_par = NULL;
// XmlTagPars *father;

// if(SUCCEEDED(retc)) retc = GetFather((KpTreeEntry **)&father); // nereikia, nustatys AppendBrother()

   KP_NEW(tmp_par, XmlTagPars(lpszParNam, lpszParVal, NULL /* father */, GetValCtbl()));
   if(SUCCEEDED(retc)) retc = tmp_par->GetOpenResult();
   if(SUCCEEDED(retc)) retc = AppendBrother(tmp_par);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::AddKpTextPar(const unsigned char *lpszParNam, const KpChar *iazIntParVal)
{
HRESULT retc=S_OK;
XmlTagPars *tmp_par = NULL;
// XmlTagPars *father;

// if(SUCCEEDED(retc)) retc = GetFather((KpTreeEntry **)&father); // nereikia, nustatys AppendBrother()

   KP_NEW(tmp_par, XmlTagPars(lpszParNam, iazIntParVal, NULL /* father */));
   if(SUCCEEDED(retc)) retc = tmp_par->GetOpenResult();
   if(SUCCEEDED(retc)) retc = AppendBrother(tmp_par);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::AddNumPar(const unsigned char *lpszParNam, long lParVal)
{
HRESULT retc = S_OK;
XmlTagPars *tmp_par;
// XmlTagPars *father;

// if(SUCCEEDED(retc)) retc = GetFather((KpTreeEntry **)&father); // nereikia, nustatys AppendBrother()

   KP_NEW(tmp_par, XmlTagPars(lpszParNam, lParVal, NULL /* father */));
   if(SUCCEEDED(retc)) retc = tmp_par->GetOpenResult();
   if(SUCCEEDED(retc)) retc = AppendBrother(tmp_par);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::AddParPar(const unsigned char *lpszParNam, XmlTagPars *pParVal)
{
HRESULT retc = S_OK;
XmlTagPars *tmp_par = NULL;
// XmlTagPars *father;

// if(SUCCEEDED(retc)) retc = GetFather((KpTreeEntry **)&father); // nereikia, nustatys AppendBrother()

   KP_NEW(tmp_par, XmlTagPars(lpszParNam, pParVal, NULL /* father */));
   if(SUCCEEDED(retc)) retc = tmp_par->GetOpenResult();
   if(SUCCEEDED(retc)) retc = AppendBrother(tmp_par);

return(retc);
}


//-----------------------------------
#if FALSE
HRESULT CopyTagPars(XmlTagPars *pTagParsPtr, XmlTagPars **ppNewPars)
{
HRESULT retc=S_OK;
int par_cnt;
unsigned char *par_nam = NULL;
KpChar *par_val = NULL;
int ii;
XmlTagPars *next_par;

   if((ppNewPars==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *ppNewPars=NULL;

   if((pTagParsPtr != NULL) && SUCCEEDED(retc))
   {
      KP_NEWA(par_nam, unsigned char, TV_TAG_LEN+1);
      KP_NEWA(par_val, KpChar, MAX_XML_PAR_VAL_LEN + 1);

      if(SUCCEEDED(retc)) retc=pTagParsPtr->GetParCnt(&par_cnt);
      for(ii = 0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
      {
         retc = pTagParsPtr->GetKpTextPar(par_nam, par_val, ii);
         KP_NEW(next_par, XmlTagPars(par_nam, par_val));
         if(SUCCEEDED(retc)) retc = next_par->GetOpenResult();

         if(SUCCEEDED(retc))
         {
            if(*ppNewPars==NULL) *ppNewPars=next_par;
            else retc=(*ppNewPars)->AddPar(next_par);
         }
      }
   }

   KP_DELETEA(par_nam);
   KP_DELETEA(par_val);

return(retc);
}
#endif


//-----------------------------------
HRESULT XmlTagPars::SetParName(int iParNum, const unsigned char *lpszParName)
{
HRESULT retc=S_OK;
XmlTagPars *par_ptr = NULL;
XmlParRec *par_rec_ptr = NULL;

   if((lpszParName == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszParName) >= TV_TAG_LEN)
      retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = PointParPtr(iParNum, &par_ptr);
   if((par_ptr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)par_ptr->GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(par_ptr->GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) strcpy(par_rec_ptr->m_lpszParName, lpszParName);

return(retc);
}


//-----------------------------------
HRESULT XmlTagPars::SetTextPar(int iParNum, const unsigned char *lpszValue)
{
HRESULT retc=S_OK;
XmlTagPars *par_ptr = NULL;
XmlParRec *par_rec_ptr = NULL;

   if((lpszValue == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszValue) >= MAX_XML_PAR_VAL_LEN)
      retc = KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = PointParPtr(iParNum, &par_ptr);
   if((par_ptr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)par_ptr->GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(par_ptr->GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) strcpy(par_rec_ptr->m_lpszParValue, lpszValue);
#if FALSE
unsigned char str_buf[41];
strncpy(str_buf, lpszValue, 40);
str_buf[40] = Nul;
printf("------- %s [%s]", par_rec_ptr->m_lpszParName, str_buf);
strncpy(str_buf, par_rec_ptr->m_lpszParValue, 40);
str_buf[40] = Nul;
printf(" [%s] %x %x\n", str_buf, retc, par_rec_ptr);
#endif
   if(SUCCEEDED(retc)) retc = par_ptr->UniformValuesFromStr();

return(retc);
}


HRESULT XmlTagPars::SetKpTextPar(int iParNum, const KpChar *iazValue)
{
HRESULT retc = S_OK;
XmlTagPars *par_ptr = NULL;
XmlParRec *par_rec_ptr = NULL;

   if((iazValue == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(TvKpStrLen(iazValue) >= MAX_XML_PAR_VAL_LEN)
      retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = PointParPtr(iParNum, &par_ptr);
   if((par_ptr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) par_rec_ptr = (XmlParRec *)par_ptr->GetValue();
   KP_ASSERT(par_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(par_ptr->GetValSize() >= sizeof(XmlParRec), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) TvKpStrCpy(par_rec_ptr->m_iazIntParValue, iazValue);

   if(SUCCEEDED(retc)) retc = par_ptr->UniformValuesFromInt();

return(retc);
}


// ---------------------------------------
HRESULT DeletePar(XmlTagPars **pTagParsPtr, int iParNum)
{
HRESULT retc=S_OK;
XmlTagPars *cur_par = NULL;
XmlTagPars *prev_par = NULL;
XmlTagPars *next_par = NULL;
int ii;

   if((pTagParsPtr == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(*pTagParsPtr == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(iParNum > 0)
      {
//       if(SUCCEEDED(retc)) retc = pTagParsPtr->GetTextPar(par_nam, par_val, iParNum - 1);
         prev_par = *pTagParsPtr;
         for(ii = 0; (ii < iParNum - 1) && SUCCEEDED(retc); ii++)
         {
            retc = prev_par->GetNextBrother((KpTreeEntry **)&prev_par);
            if((prev_par == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         }
         if(SUCCEEDED(retc)) retc = prev_par->GetNextBrother((KpTreeEntry **)&cur_par);
         if((cur_par == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc = cur_par->GetNextBrother((KpTreeEntry **)&next_par);

         if(SUCCEEDED(retc)) retc = prev_par->ConnectBrother(next_par);

      } // if(iParNum > 0)
      else
      {
         cur_par = *pTagParsPtr;
         if(SUCCEEDED(retc)) retc = cur_par->GetNextBrother((KpTreeEntry **)&next_par);
         *pTagParsPtr = next_par;

      } // else // if(iParNum > 0)

      if(SUCCEEDED(retc)) retc = cur_par->SetNextBrother(NULL);
      KP_DELETE(cur_par);

   } // if(SUCCEEDED(retc))

return(retc);
}


// ---------------------------------------
HRESULT ParseStyleParameters(XmlTagPars **pTagParsPtr, const unsigned char *lpszStyleStr, XmlTagPars *pFath)
{
HRESULT retc=S_OK;
unsigned char *style_str = NULL;
unsigned char *pnts;
unsigned char *key_name;
unsigned char *key_val;
bool end_fl = False;

   if(((pTagParsPtr == NULL) || (lpszStyleStr == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(*pTagParsPtr != NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(style_str, unsigned char, strlen(lpszStyleStr) + 1);

   if(SUCCEEDED(retc))
   {
      end_fl = False;
      strcpy(style_str, lpszStyleStr);
      pnts = style_str;

      while((!end_fl) && SUCCEEDED(retc))
      {
         key_name = pnts;

         while((*pnts != ':') && (*pnts != ';') && /* (*pnts != '\'') && (*pnts != '\"') && */ (*pnts != '}') && (*pnts)) pnts++;

         key_val = pnts;
         switch(*pnts)
         {
         case ':':
            *pnts++ = Nul;
            key_val = pnts;
            while((*pnts != ';') && /* (*pnts != '\'') && (*pnts != '\"') && */ (*pnts != '}') && (*pnts)) pnts++;

            switch(*pnts)
            {
            case ';':
               *pnts++ = Nul;
               break;
//          case '\'':
//          case '\"': // parametrai gali bûti su kabutëm: mso-style-parent:"";
            case '}':
               *pnts++ = Nul;
               end_fl = True;
               break;
            case Nul:
               end_fl = True;
               break;
            default:
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               break;
            }
            break;
         case ';':
            *pnts++ = Nul;
            break;
         case '\'':
         case '\"':
         case '}':
            *pnts++ = Nul;
            end_fl = True;
            break;
         case Nul:
            end_fl = True;
            break;
         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            break;
         }

         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(key_name);
         if(SUCCEEDED(retc)) retc = SpcEolToSpc(key_name);

         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(key_val);
         if(SUCCEEDED(retc)) retc = SpcEolToSpc(key_val);

         if(((!end_fl) || key_name[0] || key_val[0]) && SUCCEEDED(retc))
         {
            if(*pTagParsPtr == NULL) KP_NEW(*pTagParsPtr, XmlTagPars(key_name, key_val, pFath))
            else retc = (*pTagParsPtr)->AddTextPar(key_name, key_val);
// cout << "ParseStyleParameters() :\"" << key_name << "\" \"" <<  key_val << "\"" << endl;

// if((strcmp(key_name, "font-weight") == 0) && (strcmp(key_val, "normal") == 0))
// {
// int ii = 1;
// }
         }

      } // while((!end_fl) && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

   KP_DELETEA(style_str);

return(retc);
}


// ---------------------------------------
HRESULT XmlTagPars::ScaleStylePars(int iFactor)
{
HRESULT retc=S_OK;
XmlTagPars *par_ptr;
unsigned char par_nam[TV_TAG_LEN + 1];

unsigned char *par_val = null;
	KP_NEWA(par_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

bool changed = False;

   par_ptr = this;

   while(par_ptr &&  SUCCEEDED(retc))
   {
// ----------------- skaitom parametrà
      if(SUCCEEDED(retc)) retc = par_ptr->GetCurTextPar(par_nam, par_val);
      if(SUCCEEDED(retc)) strlwr(par_nam);

#if FALSE
      if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(par_val);
//    if(SUCCEEDED(retc)) retc = RemoveSpaces(par_val);
      if(SUCCEEDED(retc)) retc = SpcEolToSpc(par_val);
#endif
      changed = False;

      if(SUCCEEDED(retc))
      {
         if((strcmp(par_nam, "border-top") == 0))
         {
            retc = ScaleParVal(par_nam, par_val, iFactor, XmlParFloatUnits /* XmlParPureInteger */, 1);
            changed = True;
         }
         else if(
            (strcmp(par_nam, "font-size") == 0) ||
            (strcmp(par_nam, "mso-bidi-font-size") == 0)
                )
         {
#ifdef Debug
static unsigned char par_val_sav[MAX_XML_PAR_VAL_LEN + 1];
strcpy(par_val_sav, par_val);
#endif
            retc = ScaleParVal(par_nam, par_val, iFactor, XmlParFloatUnits, 1);
            changed = True;
// KP_TRACE_3("ScaleStylePars: %s %s %s", par_nam, par_val_sav, par_val);
         }
         else if(
            (strcmp(par_nam, "margin-top") == 0) ||
            (strcmp(par_nam, "margin-bottom") == 0) ||
            (strcmp(par_nam, "margin-right") == 0) ||
            (strcmp(par_nam, "margin-left") == 0) ||
            (strcmp(par_nam, "mso-header-margin") == 0) ||
            (strcmp(par_nam, "mso-footer-margin") == 0) ||
            (strcmp(par_nam, "height") == 0) ||
            (strcmp(par_nam, "width") == 0) ||
            (strcmp(par_nam, "top") == 0) ||
            (strcmp(par_nam, "bottom") == 0) || // ???
            (strcmp(par_nam, "left") == 0) ||
            (strcmp(par_nam, "right") == 0) || // ???
            (strcmp(par_nam, "tab-interval") == 0)
               )
         {
            retc = ScaleParVal(par_nam, par_val, iFactor, XmlParFloatUnits, 1);
            changed = True;
         }
         else if(
            (strcmp(par_nam, "tab-stops") == 0) ||
            (strcmp(par_nam, "size") == 0) ||   // size: 38.0cm 666.25pt;
            (strcmp(par_nam, "margin") == 0)    // margin: 0cm 0cm 0cm 0cm;  margin: 0px;
               )
         {
            retc = ScaleParVal(par_nam, par_val, iFactor, XmlMultiParFloatUnits, -1);
            changed = True;
         }
         else if(
            (strcmp(par_nam, "padding") == 0) ||
            (strcmp(par_nam, "mso-padding-alt") == 0)
               )
         {
            retc = ScaleParVal(par_nam, par_val, iFactor, XmlMultiParFloatUnits, 4);
            changed = True;
         }

      } // if(SUCCEEDED(retc))

      if(changed && SUCCEEDED(retc)) retc = par_ptr->SetTextPar(0, par_val);

      if(SUCCEEDED(retc)) retc = par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);

   } // while(par_ptr &&  SUCCEEDED(retc))

   KP_DELETEA(par_val);

return(retc);
}


HRESULT ScaleParVal(const unsigned char *lpszParName, unsigned char *lpszParVal, int iFactor, XmlParTypes iParType, int iNumOfVals)
{
HRESULT retc=S_OK;
int ll;
long value;
double valf;
const unsigned char *pnts;
static unsigned char new_par[MAX_XML_PAR_VAL_LEN + 1];
const unsigned char *pntss;
static unsigned char par_word[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char new_word[MAX_XML_PAR_VAL_LEN + 1];
int val_cnt;
unsigned char delim;

   if((lpszParVal == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   val_cnt = 0;

   if(SUCCEEDED(retc)) if(strlen(lpszParVal) > 0) switch(iParType)
   {
   case XmlParPureInteger:
      if(!TvIsNumber(lpszParVal))
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszParVal, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
// !!! apvalint á didesnæ pusæ; jei buvo >= 1, o perskaièiavus liko 0, tada palikt 1
         sscanf((const char *)lpszParVal, "%ld", &value);
         value = (long)value * iFactor / 1000;
         sprintf((char *)lpszParVal, "%ld", value);
      }

      val_cnt = 1;
      break;

   case XmlParIntegerUnits:
   case XmlMultiParIntegerUnits:
      retc = KpErrorProc.OutputErrorMessage(E_NOTIMPL, lpszParVal, True, __FILE__, __LINE__, 0L);
      break;

   case XmlParFloatUnits:
   case XmlMultiParFloatUnits:
      pnts = lpszParVal;
      new_par[0] = Nul;

      while(*pnts && SUCCEEDED(retc))
      {
         retc = GetWord(&pnts, par_word, lpszSpcEol, &delim);

         if(SUCCEEDED(retc)) ll = strlen(par_word);
         if(SUCCEEDED(retc)) if(ll > 0) if(lpszParVal[ll - 1] != '%')
            if(TvIsFloatDigit(par_word[0]) /* && TvIsFloatDigit(par_word[1]) */)
         {
            sscanf((const char *)par_word, "%lf", &valf);
            valf = (long)valf * iFactor / 1000.;
            sprintf((char *)new_word, "%f", valf);

            pntss = par_word;
            while(TvIsFloatDigit(*pntss) && (*pntss)) pntss++;
            if(strlen(new_word) + strlen(pntss) >= MAX_XML_PAR_VAL_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszParVal, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               strcat(new_word, pntss);
               strcpy(par_word, new_word);
            }

            val_cnt++;
         }

         if(SUCCEEDED(retc)) if(strlen(new_par) + strlen(par_word) + 1 >= MAX_XML_PAR_VAL_LEN)
            retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszParVal, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            strcat(new_par, par_word);
            if(*pnts) strcat(new_par, " ");
         }

      } // while(*pnts && SUCCEEDED(retc))

      if(SUCCEEDED(retc)) strcpy(lpszParVal, new_par);

      break;
   }

   if(
      (
         ((val_cnt != iNumOfVals) && (iNumOfVals != -1)) ||
         (val_cnt < 1)
      ) && SUCCEEDED(retc)
     )
   {
static char str_buf[TV_TAG_LEN + MAX_XML_PAR_VAL_LEN + 100];
int ll;
      ll = strlen(lpszParVal);
      if(ll > 0) ll--;
      sprintf(str_buf, "%s=%s%s %d(%d)", lpszParName, lpszParVal, lpszParVal[ll]=='%'?"%":"", val_cnt, iNumOfVals);
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, str_buf, False, __FILE__, __LINE__, 0L);
   }

return(retc);
}
