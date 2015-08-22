// ==================================================
// xmln.cpp
// XML dictionary entry node
//

// ==================================== definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <iostream>
#if Compiler != Watcom
#include <sstream>
#endif
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
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
#include "kpctypp.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlsty.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "xmlg.h"
#include "tvxmls.h"
#include "xmlsty.h"


#if Compiler != Watcom
using namespace std;
#endif

//==================================== class XmlNode methods

//----------------------------------- constructors
void XmlNode::Constructor
(
KpChar iTag, const XmlTagPars *pPars,
const KpChar *lpazText, const XmlTagPars *pContPars,
const unsigned char *lpszIndent,
KpChar iFirstTag, const unsigned char * const *plpszaTags
)
{
HRESULT retc = m_lhOpenResult; // S_OK;

// m_lhOpenResult = S_OK; // reikia palikt, koks gráþo ið KpTreeEntry::Constructor()

// -----------
   m_plpszaTags = NULL;
   m_iFirstTag = C_Nul;
   m_iLastTag = C_Nul;

   if((plpszaTags == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_plpszaTags = plpszaTags;
      m_iLastTag = m_iFirstTag = iFirstTag;
      GetLastTag(); // nustato m_iLastTag nuo paskutinës m_iLastTag reikðmës, dabar - m_iFirstTag
   }

// -----------
   m_iNodeTag = (KpChar)XC_Nul;

   if(SUCCEEDED(retc))
      if(
         (!(
            ((iTag >= m_iFirstTag /* XC_FirstDictTag */) && /* (!CheckLastTag(iTag)) */ (iTag < m_iLastTag /* XC_LastDictTag */)) ||
            ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
         )) &&
         (iTag != C_Nul)
        )
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, iTag);
   if(SUCCEEDED(retc)) m_iNodeTag = iTag;

// -----------
// tag pars
   m_pTagPars = NULL;
// if(SUCCEEDED(retc)) retc = CopyTagPars(pPars, &m_pTagPars);
   if(pPars && SUCCEEDED(retc)) KP_NEWO(m_pTagPars, XmlTagPars(pPars));

// relatives
//    moved to KpTreeEntry::Constructor()
// m_pFirstChild=NULL;
// m_pPrevBrother=NULL;
// m_pNextBrother=NULL;
// m_pFather=pFath;

// -----------
// text contents
   m_lpaizContents = NULL;
   if(SUCCEEDED(retc)) retc = SetContents(lpazText);

   m_pContPars = NULL;
// if(SUCCEEDED(retc)) retc=CopyTagPars(pContPars, &m_pContPars);
   if(pContPars && SUCCEEDED(retc)) KP_NEWO(m_pContPars, XmlTagPars(pContPars));

// -----------
// indent
   m_lpszNodeIndent = NULL;
   if(SUCCEEDED(retc)) retc = SetIndent(lpszIndent);

// iNumOfNodes=0;
// KP_NEWCA(iaNodesArray, (XmlNode *), XL_ND_MaxNumOfNodes);

   m_iPrevOutTag = (KpChar)XC_Nul;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


//-----------------------------------
XmlNode::XmlNode
(
KpChar iTag, const XmlTagPars *pPars,
const KpChar *lpazText, const XmlTagPars *pContPars,
const unsigned char *lpszIndent,
KpChar iFirstTag, const unsigned char * const *plpszaTags,
XmlNode *pFath
) : KpTreeEntry(pFath)
{
Constructor(iTag, pPars, lpazText, pContPars, lpszIndent, iFirstTag, plpszaTags);
}


//----------------------------------- copy constructors
void XmlNode::Constructor(/* const */ XmlNode *pSource, XmlNode *pFath, int iLevel, const XmlNode *pCurGrandFather)
{
HRESULT retc = m_lhOpenResult; // S_OK;
KpChar cur_tag = (KpChar)XC_Nul;
XmlTagPars *tag_pars_src = NULL;
XmlTagPars *tag_pars_dst = NULL;
XmlTagPars *cont_pars_src = NULL;
XmlTagPars *cont_pars_dst = NULL;
KpChar *contents = NULL;
unsigned char *indent = NULL;
/* const */ XmlNode *loop_brother_src = NULL; // GetNodeTag() ne const, nes CheckLastTag() ne const
XmlNode *loop_brother_dst = NULL;
XmlNode *next_brother_dst = NULL;
XmlNode *first_child_src = NULL;
XmlNode *first_child_dst = NULL;
int status = 0;

   m_iNodeTag = (KpChar)XC_Nul;
   m_pTagPars = NULL;
   m_lpaizContents = NULL;
   m_pContPars = NULL;
   m_lpszNodeIndent = NULL;
   m_iPrevOutTag = (KpChar)XC_Nul;

   if((pSource==NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   loop_brother_src = pSource;
   loop_brother_dst = this;

// loop on brothers
   while((loop_brother_src!=NULL) && SUCCEEDED(retc))
   {
      tag_pars_dst = NULL;
      cur_tag = (KpChar)XC_Nul;
      contents = NULL;
      cont_pars_dst = NULL;
      indent = NULL;

      status = KpNodeVisible | KpNodeHasChildren | KpNodeExpanded;
      if(iLevel >= 0) status = loop_brother_src->m_iStatus >> (KpNodeLevelShift * iLevel);

#if FALSE // #ifdef Debug
loop_brother_src->GetNodeTag(&cur_tag);
if((cur_tag==XC_HeadWordGroup) || (cur_tag==XC_StEntry) || (cur_tag==XC_ExampleGroup))
status = KpNodeVisible | KpNodeHasChildren | KpNodeExpanded;
#endif

      if(((status & KpNodeVisible) || (loop_brother_src==pCurGrandFather /* pSource */)) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=loop_brother_src->GetNodeTag(&cur_tag);
         if(SUCCEEDED(retc)) retc=loop_brother_src->GetContentsPtr(&contents);
         if(SUCCEEDED(retc)) retc=loop_brother_src->GetIndentPtr(&indent);

         if(SUCCEEDED(retc)) retc=loop_brother_src->GetTagParsPtr(&tag_pars_src);
         if((tag_pars_src != NULL) && SUCCEEDED(retc))
         {
            KP_NEWO(tag_pars_dst, XmlTagPars(tag_pars_src));
            if(FAILED(retc)) KP_DELETE(tag_pars_dst);
         }

         if(SUCCEEDED(retc)) retc=loop_brother_src->GetContParsPtr(&cont_pars_src);
         if((cont_pars_src != NULL) && SUCCEEDED(retc))
         {
            KP_NEWO(cont_pars_dst, XmlTagPars(cont_pars_src));
            if(FAILED(retc)) KP_DELETE(cont_pars_dst);
         }

         if(SUCCEEDED(retc))
         {
            if(loop_brother_src==pSource) // (loop_brother_dst == this)
            {
               loop_brother_dst->Constructor(cur_tag, tag_pars_dst, contents, cont_pars_dst, indent, loop_brother_src->GetFirstTag(), loop_brother_src->GetTagsArrPtr());
               if(SUCCEEDED(retc)) retc = loop_brother_dst->GetOpenResult();
               if(SUCCEEDED(retc))
                  retc = CopyKpTreeNodeAllocate((KpTreeEntry *)loop_brother_dst, (KpTreeEntry *)pSource);
            }
            else if(status & KpNodeVisible)
            {
               KP_NEWO(next_brother_dst, XmlNode(cur_tag, tag_pars_dst, contents, cont_pars_dst, indent, loop_brother_src->GetFirstTag(), loop_brother_src->GetTagsArrPtr(), pFath));
               if(SUCCEEDED(retc)) CopyKpTreeNodeAllocate((KpTreeEntry *)next_brother_dst, (KpTreeEntry *)loop_brother_src);

               if(SUCCEEDED(retc)) retc = loop_brother_dst->ConnectBrother(next_brother_dst);
               loop_brother_dst = next_brother_dst; next_brother_dst = NULL;
            }
         }

         KP_DELETE(tag_pars_dst);
         KP_DELETE(cont_pars_dst);

//       if(SUCCEEDED(retc)) retc = loop_brother_src->GetFirstChild((KpTreeEntry **)&first_child_src);
         if(SUCCEEDED(retc)) first_child_src = (XmlNode *)loop_brother_src->m_pFirstChild;
         if(first_child_src && SUCCEEDED(retc))
         {
            status = KpNodeVisible | KpNodeHasChildren | KpNodeExpanded;
            if(iLevel >= 0) status = first_child_src->m_iStatus >> (KpNodeLevelShift * iLevel);

#if FALSE // #ifdef Debug
first_child_src->GetNodeTag(&cur_tag);
if((cur_tag==XC_HeadWordGroup) || (cur_tag==XC_StEntry) || (cur_tag==XC_ExampleGroup))
status = KpNodeVisible | KpNodeHasChildren | KpNodeExpanded;
#endif
            if(
               (
                  (status & KpNodeVisible) ||   // gal reiktu kiekvieno mazgo pirma vaika itraukti visada, net jei ir neatitinka iLevel?
                                                // dabar, kai neitraukiam pirmo - dingsta ir visi like, nors, galbut, ir atitinka iLevel
                                                // dingsta ir visi tinkami broliai, esantys uz netinkamo
                                                // nors toks elgesys tinka - sitas konstruktorius naudojamas tik zemo lygmens tagu
                                                //    isskyrimui, o Lizdyne jie visada yra mazgo pradzioje
                  (loop_brother_src==pCurGrandFather /* pSource */)
               ) &&
               SUCCEEDED(retc)
              )
            {
               KP_NEWO(first_child_dst, XmlNode(first_child_src, loop_brother_dst, iLevel, pCurGrandFather));

               if(SUCCEEDED(retc)) retc = loop_brother_dst->ConnectChild(first_child_dst);
               first_child_dst = NULL;
            }

         } // if(first_child_src && SUCCEEDED(retc))

      } // if(((status & KpNodeVisible) || (loop_brother_src==pCurGrandFather /* pSource */)) && SUCCEEDED(retc))

      if(SUCCEEDED(retc))
      {
         if(loop_brother_src==pCurGrandFather) loop_brother_src = NULL; // senelis tik pats vienas, broliu nereikia
         else
            retc = loop_brother_src->GetNextBrother((KpTreeEntry **)&loop_brother_src);
      }

   } //  while((loop_brother_src!=NULL) && SUCCEEDED(retc));

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


XmlNode::XmlNode(/* const */ XmlNode *pSource, XmlNode *pFath, int iLevel, const XmlNode *pCurGrandFather) : KpTreeEntry(pFath)
{
   Constructor(pSource, pFath, iLevel, pCurGrandFather);
}


XmlNode::XmlNode(/* const */ XmlNode *pSource, XmlNode *pFath) : KpTreeEntry(pFath)
{
   Constructor(pSource, pFath, -1, pFath);
}


//-----------------------------------
XmlNode::~XmlNode()
{
HRESULT retc = S_OK;

   KP_DELETE(m_pTagPars);
   KP_DELETEA(m_lpaizContents);
   KP_DELETE(m_pContPars);
   KP_DELETEA(m_lpszNodeIndent);
}


//====================================
KpChar XmlNode::GetLastTag(void)
{
HRESULT retc = S_OK;
const unsigned char * const *pntss;

   if((m_plpszaTags == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
//    pntss = m_plpszaTags;
      pntss = m_plpszaTags + (m_iLastTag - m_iFirstTag); // tagø gali tik daugëti - pradedam nuo paskutinio
      while(*pntss) pntss++;
      m_iLastTag = (KpChar)(m_iFirstTag + (pntss - m_plpszaTags));
   }

// return(retc);
return(m_iLastTag);
}


bool XmlNode::CheckLastTag(KpChar iTag)
{
bool retv = False;

   if(iTag >= m_iLastTag)
      if(iTag >= GetLastTag()) retv = True;

return(retv);
}


//====================================
HRESULT XmlNode::GetNodeTag(KpChar *piTag) // const
{
HRESULT retc=S_OK;

   if(piTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *piTag = m_iNodeTag;
// if(
//    (!(
//       ((m_iNodeTag >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(m_iNodeTag)) /* (m_iNodeTag < XC_LastDictTag) */) ||
//       ((m_iNodeTag >= XL_FirstSysTag) && (m_iNodeTag < XL_LastSysTag))
//    )) &&
//    SUCCEEDED(retc)
//   )
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::SetNodeTag(KpChar iTag)
{
HRESULT retc=S_OK;

   if(
      (!(
         ((iTag >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(iTag)) /* (iTag < XC_LastDictTag) */) ||
         ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
      )) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) m_iNodeTag=iTag;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetTagParsPtr(XmlTagPars **ppTagPars) const
{
HRESULT retc=S_OK;

   if(ppTagPars==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppTagPars=m_pTagPars;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetContParsPtr(XmlTagPars **ppContPars) const
{
HRESULT retc=S_OK;

   if(ppContPars==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppContPars=m_pContPars;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::SetTagParsPtr(XmlTagPars *pTagParsPar)
{
HRESULT retc=S_OK;

// KP_ASSERT(if(m_pTagPars == NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_DELETE(m_pTagPars);

   if(SUCCEEDED(retc)) m_pTagPars = pTagParsPar;

return(retc);
}


HRESULT XmlNode::SetTagParsPtrSimple(XmlTagPars *pTagParsPar)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) m_pTagPars = pTagParsPar;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::CreateTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText, XmlNode **pTextNodePtr)
{
HRESULT retc=S_OK;
XmlNode *text_node=NULL;

   if(
      (
         (pTextNodePtr==NULL) ||
         (!(
            ((iTag >= m_iFirstTag) && (!CheckLastTag(iTag))) ||
            ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
         ))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
	{
      KP_NEWO(*pTextNodePtr, XmlNode(iTag, pTagPars, NULL, NULL, m_lpszNodeIndent, m_iFirstTag, m_plpszaTags, NULL));
      if(FAILED(retc)) KP_DELETE(*pTextNodePtr);
   }

   if((piText!=NULL) && SUCCEEDED(retc)) if(TvKpStrLen(piText)!=0)
   {
      KP_NEWO(text_node, XmlNode((KpChar)XL_Text, NULL, piText, NULL, m_lpszNodeIndent, XC_FirstDictTag, plpszaXmlttDictTagsFull, *pTextNodePtr));
      if(FAILED(retc)) KP_DELETE(text_node);

      if(SUCCEEDED(retc))
      {
         retc = (*pTextNodePtr)->InsertChild(text_node);
         if(FAILED(retc)) KP_DELETE(text_node);
      }
   }

   text_node=NULL;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::InsertTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText)
{
HRESULT retc=S_OK;
XmlNode *new_node=NULL;

   if(
      (
         (!(
            ((iTag >= m_iFirstTag) && (!CheckLastTag(iTag))) ||
            ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
         ))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=CreateTextTag(iTag, pTagPars, piText, &new_node);

   if(SUCCEEDED(retc))
   {
      retc = InsertChild(new_node);
      if(FAILED(retc)) KP_DELETE(new_node);
   }

   new_node=NULL;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::AppendTextTag(KpChar iTag, XmlTagPars *pTagPars, KpChar *piText)
{
HRESULT retc=S_OK;
XmlNode *new_node=NULL;

   if(
      (
         (!(
            ((iTag >= m_iFirstTag) && (!CheckLastTag(iTag))) ||
            ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
         ))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=CreateTextTag(iTag, pTagPars, piText, &new_node);

   if(SUCCEEDED(retc))
   {
      retc = AppendChild(new_node);
      if(FAILED(retc)) KP_DELETE(new_node);
   }

   new_node=NULL;

return(retc);
}


HRESULT XmlNode::AppendTextTag(KpChar iTag, XmlTagPars *pTagPars, const unsigned char *lpszText, int iCtbl)
{
HRESULT retc=S_OK;
KpChar *val_buf = NULL;
int ll;

   KP_ASSERT(lpszText, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      ll = strlen(lpszText);
      KP_NEWA(val_buf, KpChar, ll + 1);
   }

   if(SUCCEEDED(retc))
   {
      retc = KptStrEncode(val_buf, lpszText, iCtbl);
      if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF)) KP_WARNING(retc, null);
   }

   if(SUCCEEDED(retc))
   {
      val_buf[ll] = C_Nul;
      retc = AppendTextTag(iTag, pTagPars, val_buf);
   }

   KP_DELETEA(val_buf);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::CreateNewChild(KpChar iTag, XmlTagPars *pPars, XmlNode **ppNewChild)
{
HRESULT retc = S_OK;
unsigned char *indent = NULL;
int ind_len;

// printf("stack size CreateNewChild(): %ld\n", (long)((char *)StackTop-(char *)(&ppNewChild)));

   if(
      (
         (ppNewChild==NULL) ||
         (!(
            ((iTag >= m_iFirstTag) && (!CheckLastTag(iTag))) ||
            ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
         ))
      ) &&
      SUCCEEDED(retc)
     )
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// indent
   if(SUCCEEDED(retc))
   {
      ind_len = 0;
      if(m_lpszNodeIndent != NULL) ind_len = strlen(m_lpszNodeIndent);

      KP_NEWA(indent, unsigned char, ind_len + 1 + XN_POS_PER_INDENT);
   }

   if(SUCCEEDED(retc))
   {
      if(m_lpszNodeIndent != NULL) strcpy(indent, m_lpszNodeIndent);
      else indent[0] = Nul;
   }

// if((TvKpStrChr(uiazXmlGrTags, iTag)!=NULL) && SUCCEEDED(retc))
//    strcat(indent, "   "); // XN_POS_PER_INDENT

// if((iTag >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(iTag)) /* (iTag < XC_LastDictTag) */ && SUCCEEDED(retc))
//    if(TvStrChr(m_plpszaTags /* plpszaXmlttDictTags */[(iTag|1) - m_iFirstTag /* XC_FirstDictTag */], C_Lf)!=NULL) // '\n'
//       strcat(indent, "   "); // XN_POS_PER_INDENT

   if(SUCCEEDED(retc)) strcat(indent, "   "); // XN_POS_PER_INDENT

// output
   KP_NEWO(*ppNewChild, XmlNode(iTag, pPars, NULL, NULL, indent, m_iFirstTag, m_plpszaTags, this));
// printf("free mem: %ld\n", (long)((char *)(*ppNewChild) - (char *)StackTop));

   if(SUCCEEDED(retc)) retc = AppendChild(*ppNewChild);

   KP_DELETEA(indent);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::SetContents(const KpChar *lpazTextBuf)
{
HRESULT retc=S_OK;
int buf_len;

   KP_DELETEA(m_lpaizContents);

   if((lpazTextBuf!=NULL) && SUCCEEDED(retc)) if(lpazTextBuf[0]!=C_Nul)
   {
      if(m_iNodeTag!=XL_Text)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         buf_len = TvKpStrLen(lpazTextBuf)+1;
         KP_NEWA(m_lpaizContents, KpChar, buf_len);
       }

      if(SUCCEEDED(retc)) TvKpStrCpy(m_lpaizContents, lpazTextBuf);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetContentsPtr(KpChar **pplpszTextBufPtr) const
{
HRESULT retc=S_OK;

   if(pplpszTextBufPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pplpszTextBufPtr = m_lpaizContents;

return(retc);
}


// int test_cnt=0;

//-----------------------------------
HRESULT XmlNode::SetIndent(const unsigned char *lpszIndentStrBuf)
{
HRESULT retc=S_OK;
int buf_len;

   KP_DELETEA(m_lpszNodeIndent);

   if((lpszIndentStrBuf!=NULL) && SUCCEEDED(retc)) if(lpszIndentStrBuf[0]!=C_Nul)
   {
      buf_len = strlen(lpszIndentStrBuf) + 1;
      KP_NEWA(m_lpszNodeIndent, unsigned char, buf_len);

      if(SUCCEEDED(retc)) strcpy(m_lpszNodeIndent, lpszIndentStrBuf);
   }

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetIndentPtr(unsigned char **pplpszIndentStrBuf) const
{
HRESULT retc=S_OK;

   if(pplpszIndentStrBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pplpszIndentStrBuf = m_lpszNodeIndent;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::ExtractSubNodes(XmlNode **ppChildCatsBr, KpChar iSubTag)
{
HRESULT retc=S_OK;
XmlNode *first_child;
XmlNode *loop_brother;
XmlNode *father;
XmlNode *prev_brother;
XmlNode *cat_child_start;
XmlNode *child_tail;
KpChar cur_tag;

// if(((iSubTag < m_iFirstTag) || CheckLastTag(iSubTag)) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && (*ppChildCatsBr==NULL) && SUCCEEDED(retc))
// {
      if(SUCCEEDED(retc))
      {
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)loop_brother->m_pFirstChild;
      }

// no loop - go directly to <hg> and its first level subnodes
   if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag!=XC_HeadWordGroup) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
   if((first_child!=NULL) && SUCCEEDED(retc))
   {
      loop_brother=first_child;
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;
   }



// -----------------
      if(SUCCEEDED(retc))
      {
         if(iSubTag==XC_TrWord)
         {
            father=first_child;
            if(father!=NULL) retc=father->GetNodeTag(&cur_tag);
// up to first <tg> and process its subnodes; rest <tg>'s remain not processed
            while(
                  (cur_tag!=XC_TranslGroup) &&
                  (father!=NULL) &&
                  SUCCEEDED(retc)
                 )
            {
               retc=father->GetNextBrother((KpTreeEntry **)&father);
               if((father!=NULL) && SUCCEEDED(retc)) retc=father->GetNodeTag(&cur_tag);
            }

            if(SUCCEEDED(retc))
            {
               first_child=NULL;
               if(father!=NULL)
               {
//                retc = father->GetFirstChild((KpTreeEntry **)&first_child);
                  first_child = (XmlNode *)father->m_pFirstChild;
               }
            }
         }
         else father=loop_brother;
      }

// -----------------
      if(SUCCEEDED(retc))
      {
         cat_child_start=first_child;
         if(cat_child_start!=NULL)
            retc=cat_child_start->GetNodeTag(&cur_tag);
      }
      while(
            (
               (TvKpStrChr(uiazXmlCtgGrTags, cur_tag)==NULL) ||
               (iSubTag!=XC_CtgGroup)
            ) &&
            (
               (cur_tag!=XC_TranslGroup) ||
               (iSubTag!=XC_TranslGroup)
            ) &&
            (
//             (cur_tag!=XC_TrWord) ||
               (iSubTag!=XC_TrWord)
            ) &&
            (cat_child_start!=NULL) &&
            SUCCEEDED(retc)
           )
      {
         retc=cat_child_start->GetNextBrother((KpTreeEntry **)&cat_child_start);
         if((cat_child_start!=NULL) && SUCCEEDED(retc))
            retc=cat_child_start->GetNodeTag(&cur_tag);
      }

// -----------------
      child_tail=cat_child_start;
      while(
            (
               (
                  (TvKpStrChr(uiazXmlCtgGrTags, cur_tag)!=NULL) &&
                  (iSubTag==XC_CtgGroup)
               ) ||
               (
                  (cur_tag==XC_TranslGroup) &&
                  (iSubTag==XC_TranslGroup)
               ) ||
               (
//                (cur_tag==XC_TrWord) &&
                  (iSubTag==XC_TrWord)
               )
            ) &&
            (child_tail!=NULL) &&
            SUCCEEDED(retc)
           )
      {
         retc=child_tail->GetNextBrother((KpTreeEntry **)&child_tail);
         if((child_tail!=NULL) && SUCCEEDED(retc))
            retc=child_tail->GetNodeTag(&cur_tag);
      }

// -----------------
      if((cat_child_start!=NULL) && SUCCEEDED(retc))
      {
         *ppChildCatsBr=cat_child_start;

         retc=child_tail->GetPrevBrother((KpTreeEntry **)&prev_brother);
         if((prev_brother!=NULL) && SUCCEEDED(retc))
            retc=prev_brother->SetNextBrother(NULL);

         retc=cat_child_start->GetPrevBrother((KpTreeEntry **)&prev_brother);
         if(SUCCEEDED(retc))
         {
            if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(child_tail);
            else retc=father->ConnectChild(child_tail);
         }

         if(SUCCEEDED(retc)) retc=cat_child_start->SetPrevBrother(NULL);
      }

// recursion on children
//    if((first_child!=NULL) && (*ppChildCatsBr==NULL) && SUCCEEDED(retc))
//       retc=first_child->ExtractSubNodes(ppChildCatsBr, iSubTag);

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

// } // while((loop_brother!=NULL) && (*ppChildCatsBr!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteNode(lpOutFile);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::SkipBrothersToTag(XmlNode **ppFirstOccurence, KpChar iTag)
{
HRESULT retc=S_OK;
XmlNode *child_rest;
KpChar cur_tag;

// if(((iTag < m_iFirstTag) || CheckLastTag(iTag)) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   child_rest=this;

   if(SUCCEEDED(retc)) do
   {
      if((child_rest!=NULL) && SUCCEEDED(retc))
      {
         retc=child_rest->GetNodeTag(&cur_tag);
         if((cur_tag!=iTag) && SUCCEEDED(retc))
            retc=child_rest->GetNextBrother((KpTreeEntry **)&child_rest); // skip next not iTag tags
      }
   } while((cur_tag!=iTag) && (child_rest!=NULL) && SUCCEEDED(retc));

   *ppFirstOccurence=child_rest;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::InvertNode(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
XmlNode *entry_subnodes;
XmlNode *entry_subnodes_last;
XmlNode *entry_subnodes_rest;
KpChar entry_tag;
XmlNode *transl_group;
XmlNode *transl_subnodes;
XmlNode *transl_subnodes_last;
XmlNode *transl_subnodes_rest;
KpChar cur_tag;
bool end_fl;
const KpChar *pnti;
const KpChar *hw_ix;

// loop on brothers
   loop_brother=this;

   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&entry_tag);
      hw_ix=TvKpStrChr(uiazXmlHwGrTags, entry_tag);
      if((hw_ix!=NULL) && SUCCEEDED(retc))
      {
// extract <hw> & Co
         entry_subnodes=entry_subnodes_last=entry_subnodes_rest=NULL;
         if((loop_brother!=NULL) && SUCCEEDED(retc))
         {
//          retc = loop_brother->GetFirstChild((KpTreeEntry **)&entry_subnodes_rest);
            entry_subnodes_rest = (XmlNode *)loop_brother->m_pFirstChild;
         }

         do
         {
            end_fl=False;
            if((entry_subnodes_rest!=NULL) && SUCCEEDED(retc))
            {
               retc=entry_subnodes_rest->GetNodeTag(&cur_tag);
               if(SUCCEEDED(retc))
                  end_fl=(TvKpStrChr(uiazXmlNodeGrTags, cur_tag)!=NULL);
               if((!end_fl) && SUCCEEDED(retc))
               {
                  if(entry_subnodes==NULL)
                     entry_subnodes=entry_subnodes_rest;
                  entry_subnodes_last=entry_subnodes_rest;
                  retc=entry_subnodes_rest->GetNextBrother((KpTreeEntry **)&entry_subnodes_rest);
               }
            }
         } while((!end_fl) && (entry_subnodes_rest!=NULL) && SUCCEEDED(retc));

// cut extracted <hw> chains
         if((loop_brother!=NULL) && SUCCEEDED(retc))
            retc=loop_brother->ConnectChild(entry_subnodes_rest);
         if((entry_subnodes_last!=NULL) && SUCCEEDED(retc))
            retc=entry_subnodes_last->SetNextBrother(NULL);

// map <hw> like tags
// !!! neveikia
         if((entry_subnodes!=NULL) && SUCCEEDED(retc))
         {
            pnti=uiazXmlHwTags;
            while((*pnti) && SUCCEEDED(retc))
               retc=entry_subnodes->MapTags(*pnti++, (KpChar)XC_TrWord);
         }
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_PartOfSpeechSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_PartOfSpeechDst, (KpChar)XC_PartOfSpeechSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_PartOfSpeechDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_FormGroupSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_FormGroupDst, (KpChar)XC_FormGroupSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_FormGroupDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_FormSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_FormDst, (KpChar)XC_FormSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_FormDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ExplSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ExplDst, (KpChar)XC_ExplSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_ExplDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_CtrlSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_CtrlDst, (KpChar)XC_CtrlSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_CtrlDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ContextSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ContextDst, (KpChar)XC_ContextSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_ContextDst);

         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ModCpdSrc, (KpChar)XC_Nul);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_ModCpdDst, (KpChar)XC_ModCpdSrc);
         if(SUCCEEDED(retc)) retc=entry_subnodes->MapTags((KpChar)XC_Nul, (KpChar)XC_ModCpdDst);


// preparing for extraction of <tw> & Co
         transl_group=NULL;
         if((cur_tag==XC_TranslGroup) && SUCCEEDED(retc))
            transl_group=entry_subnodes_rest;

// create new <tg> if not present
         if((transl_group==NULL) && SUCCEEDED(retc))
         {
            KP_NEWO(transl_group, XmlNode((KpChar)XC_TranslGroup, NULL, NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));
            if((loop_brother != NULL) && SUCCEEDED(retc)) retc = loop_brother->InsertChild(transl_group);
            if(SUCCEEDED(retc)) entry_subnodes_rest = transl_group;
         }

// extract <tw> & Co
         transl_subnodes=transl_subnodes_last=transl_subnodes_rest=NULL;
         if((transl_group!=NULL) && SUCCEEDED(retc))
         {
//          retc = transl_group->GetFirstChild((KpTreeEntry **)&transl_subnodes_rest);
            transl_subnodes_rest = (XmlNode *)transl_group->m_pFirstChild;

            do
            {
               end_fl=False;
               if((transl_subnodes_rest!=NULL) && SUCCEEDED(retc))
               {
                  retc=transl_subnodes_rest->GetNodeTag(&cur_tag);
                  if(SUCCEEDED(retc))
                     end_fl=(TvKpStrChr(uiazXmlNodeGrTags, cur_tag)!=NULL);
                  if((!end_fl) && SUCCEEDED(retc))
                  {
                     if(transl_subnodes==NULL)
                        transl_subnodes=transl_subnodes_rest;
                     transl_subnodes_last=transl_subnodes_rest;
                     retc=transl_subnodes_rest->GetNextBrother((KpTreeEntry **)&transl_subnodes_rest);
                  }
               }
            } while((!end_fl) && (transl_subnodes_rest!=NULL) && SUCCEEDED(retc));
         }

// cut extracted <tw> chains
         if((transl_subnodes_last!=NULL) && SUCCEEDED(retc))
            retc=transl_subnodes_last->SetNextBrother(NULL);
         if((transl_group!=NULL) && SUCCEEDED(retc))
            retc=transl_group->ConnectChild(transl_subnodes_rest);


// map <tw> tags
// !!! neveikia
         if((transl_subnodes!=NULL) && SUCCEEDED(retc))
            retc=transl_subnodes->MapTags((KpChar)XC_TrWord, uiazXmlHwInvTags[hw_ix-uiazXmlHwGrTags]);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_PartOfSpeechDst, (KpChar)XC_PartOfSpeechSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_FormGroupDst, (KpChar)XC_FormGroupSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_FormDst, (KpChar)XC_FormSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_ExplDst, (KpChar)XC_ExplSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_CtrlDst, (KpChar)XC_CtrlSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_ContextDst, (KpChar)XC_ContextSrc);
         if(SUCCEEDED(retc)) retc=transl_subnodes->MapTags((KpChar)XC_ModCpdDst, (KpChar)XC_ModCpdSrc);

// swap subnodes
         if((loop_brother==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            if(transl_subnodes!=NULL)
            {
               if(SUCCEEDED(retc))
                  retc=loop_brother->ConnectChild(transl_subnodes);
               if((transl_subnodes_last==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  retc=transl_subnodes_last->ConnectBrother(entry_subnodes_rest);
            }
            else retc=loop_brother->ConnectChild(entry_subnodes_rest);
         }

         if((transl_group==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            if(entry_subnodes!=NULL)
            {
               if(SUCCEEDED(retc))
                  retc=transl_group->ConnectChild(entry_subnodes);
               if((entry_subnodes_last==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  retc=entry_subnodes_last->ConnectBrother(transl_subnodes_rest);
            }
            else retc=transl_group->ConnectChild(entry_subnodes_rest);
         }

      } // if((hw_ix!=NULL) && SUCCEEDED(retc))

// recursion through children of children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child != NULL) && SUCCEEDED(retc)) retc = first_child->InvertNode();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->InvertNode();

return(retc);
}


//==================================
HRESULT EncloseToGroup(XmlNode **ppFirstOccurence, KpChar iGrTag)
{
HRESULT retc=S_OK;
XmlNode *new_node;

   if((ppFirstOccurence == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(*ppFirstOccurence == NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if((iGrTag < (*ppFirstOccurence)->GetFirstTag() /* m_iFirstTag */) || (*ppFirstOccurence)->CheckLastTag(iGrTag))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWO(new_node, XmlNode(iGrTag, NULL, NULL, NULL, (const unsigned char *)"", (*ppFirstOccurence)->GetFirstTag(), (*ppFirstOccurence)->GetTagsArrPtr(), NULL));

   if(SUCCEEDED(retc)) retc = new_node->ConnectChild(*ppFirstOccurence);
   if(SUCCEEDED(retc)) *ppFirstOccurence = new_node;

return(retc);
}


//==================================
// int read_node_cnt=0;

HRESULT XmlNode::ReadNode(XmlO1 /* XmlI */ *lpInFile)
{
HRESULT retc=S_OK;
XmlNode *cur_node = NULL;
XmlTagPars *tag_pars = NULL;
KpChar in_ch;
bool end_fl;
KpChar first_tag;
KpChar last_tag;
const unsigned char * const *tag_names;

// KP_TRACE_1("ReadNode: %s", m_plpszaTags[m_iNodeTag - m_iFirstTag]);

   if((lpInFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// printf("--- count:%d stack size: %ld\n", read_node_cnt++, (long)((char *)StackTop-(char *)(&lpInFile)));
// if(read_node_cnt==16918)
// read_node_cnt=16918;

   if(SUCCEEDED(retc))
   {
      if((m_iNodeTag >= m_iFirstTag) && (m_iNodeTag < m_iLastTag) /* (!CheckLastTag(m_iNodeTag)) */)
      {
         first_tag = m_iFirstTag;
         last_tag = m_iLastTag;
         tag_names = m_plpszaTags;
      }
      else if((m_iNodeTag >= XL_FirstSysTag) && (m_iNodeTag < XL_LastSysTag))
      {
         first_tag = XL_FirstSysTag;
         last_tag = XL_LastSysTag;
         tag_names = plpszaXmlSysTags;
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }


// loop through contents
   if(SUCCEEDED(retc))
      if(strcmp((const char *)tag_names /* m_plpszaTags */ /* plpszaXmlttDictTagsFull */[(m_iNodeTag&(~1)) + 1 -
                                 first_tag /* m_iFirstTag */ /* XC_FirstDictTag */], "")!=0)
         do
   {
// enter next char
      if(SUCCEEDED(retc)) do
      {
         end_fl = True;
         if(tag_pars!=NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) do
         {
            KP_DELETE(tag_pars);
            
            retc = lpInFile->GetCharProc(&in_ch, &tag_pars,
               XL_IX_DefDataFile, False,
               (m_iNodeTag != XC_CodeExample) && (m_iNodeTag != XC_Special) &&
               (m_iNodeTag != HTM_TG_SCRIPT) && (m_iNodeTag != HTM_TG_PRE) && (m_iNodeTag != HTM_TG_CODE));
         } while((in_ch == C_Cr) && SUCCEEDED(retc)); // Cr metam bet kokiu atveju – xGecko lauþia eilutæ

#ifdef Debug
// if(in_ch==XC_Symb)
// in_ch=XC_Symb;

if(in_ch==(KpChar)XC_Nul)
in_ch=(KpChar)XC_Nul;

if(in_ch==C_Lf)
in_ch=C_Lf;
#endif

         if((TvStrChr(lpszSpcEol, in_ch) != NULL) && SUCCEEDED(retc))
            retc = XmltTestEmbedded(in_ch, m_iNodeTag, &end_fl);

// KP_TRACE_4("ReadNode: m_iNodeTag:%d, in_ch: %d %c, embed:%d", m_iNodeTag, in_ch, in_ch, end_fl);

      } while(!end_fl);

      if((in_ch != (m_iNodeTag|0x01)) && SUCCEEDED(retc))
      {
// enter subnode
         if(
            ((in_ch >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(in_ch)) /* (in_ch < XC_LastDictTag) */) ||
            ((in_ch >= XL_FirstSysTag) && (in_ch < XL_LastSysTag))
           )
         {
            if((in_ch&0x01)!=0)
               retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, GetTagName(in_ch - 1, m_plpszaTags, XC_FirstDictTag, XC_LastDictTag), True, __FILE__, __LINE__, in_ch);
// create new node
            cur_node = NULL; // !!!!???? KP_DELETE(cur_node);
            if(SUCCEEDED(retc)) retc = CreateNewChild(in_ch, tag_pars, &cur_node);

            if((in_ch == XC_Break) && SUCCEEDED(retc))
               retc = lpInFile->SkipSpaces(XL_IX_DefDataFile);

// printf("tag = %d\n", in_ch);

// if(in_ch==XC_MngGroup)
// in_ch=XC_MngGroup;

            if(SUCCEEDED(retc)) retc = cur_node->ReadNode(lpInFile);
         }
// enter text
         else
         {
            if(SUCCEEDED(retc)) retc = lpInFile->UnGetCharProc(in_ch, tag_pars
                                                      , XL_IX_DefDataFile
                                                      );

            if(SUCCEEDED(retc)) retc = ReadText(lpInFile);
#if FALSE // #ifdef Debug
static unsigned char str_buf[1000];
KptStrDecode(str_buf, m_lpaizContents, 71);
KP_TRACE_2("ReadNode: %s: %s", m_plpszaTags[m_iNodeTag - m_iFirstTag], str_buf);
#endif
         }
      }

      KP_DELETE(tag_pars);

   } while((in_ch != (m_iNodeTag|0x01)) && SUCCEEDED(retc));

return(retc);
}


HRESULT XmlNode::ReadNode(XmlI *lpInFile)
{
HRESULT retc=S_OK;

   if((lpInFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = ReadNode(lpInFile->FilePtr);

return(retc);
}


//-----------------------------------
HRESULT ReadEntry(XmlNode **ppNodePtr, XmlO1 *lpInFile, bool bExact, KpChar iFirstTag, const unsigned char * const *plpszaTags)
{
HRESULT retc=S_OK;
XmlTagPars *tag_pars = NULL;
KpChar in_ch;
long entr_id;
int par_num;

   if((ppNodePtr == NULL) || (lpInFile == NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(*ppNodePtr != NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc = lpInFile->GetCharProc(&in_ch, &tag_pars,
         XL_IX_DefDataFile,
         bExact, !bExact);

#if TRUE // #if FALSE // Kodël iðmesta? Pvz., arksh.exe ið MikoView reikia su XmlNode::ReadEntry() skaityt kelis XmlNode ið eilës
                      //    (praleist <!DOCTYPE ...> lizdà) – reikia praleidinët tarpus tarp lizdø
   if(!bExact) while((in_ch==C_Spc) && SUCCEEDED(retc))
   {
      KP_DELETE(tag_pars);
      if(SUCCEEDED(retc)) retc = lpInFile->GetCharProc(&in_ch, &tag_pars, XL_IX_DefDataFile, bExact, !bExact);
   }
#endif

   if(SUCCEEDED(retc)) if((in_ch != XC_StEntry) && (in_ch != XC_NrtEntry) && (iFirstTag == XC_FirstDictTag))
      retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      entr_id = 0L;
      if(tag_pars != NULL) retc = tag_pars->SeekNumPar("id", &entr_id, &par_num);
      if(retc == KP_E_KWD_NOT_FOUND)
      {
         retc = S_OK;
         entr_id = 0L;
      }
      KpErrorProc.SetLPar(entr_id);

      KP_NEWO(*ppNodePtr, XmlNode(in_ch, tag_pars, NULL, NULL, (const unsigned char *)"", iFirstTag, plpszaTags, NULL));
   }
   KP_DELETE(tag_pars);

   if(SUCCEEDED(retc)) retc = (*ppNodePtr)->ReadNode(lpInFile);

   if(SUCCEEDED(retc)) retc = (*ppNodePtr)->ParseStyleContents(XC_Nul);
   if(SUCCEEDED(retc)) retc = (*ppNodePtr)->FormatStyleContents(XC_Nul);

return(retc);
}


HRESULT ReadEntry(XmlNode **ppNodePtr, XmlI *lpInFile, bool bExact, KpChar iFirstTag, const unsigned char * const *plpszaTags)
{
HRESULT retc=S_OK;

   if((lpInFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = ReadEntry(ppNodePtr, lpInFile->FilePtr, bExact, iFirstTag, plpszaTags);

return(retc);
}


//-----------------------------------
HRESULT ReadXmlFile(XmlNode **ppNodePtr, XmlO1 *lpInFile, KpChar iFirstTag, const unsigned char * const *plpszaTags)
{
HRESULT retc = S_OK;

   KP_ASSERT(ppNodePtr != NULL, E_INVALIDARG, null, True);
// KP_ASSERT(lpInFile != NULL, E_INVALIDARG, null, True);
// KP_ASSERT(lpInFile->m_fFiles[XL_IX_DefDataFile] != NULL, KP_E_NO_FILE, null, True);
// KP_ASSERT(lpInFile->m_fFiles[XL_IX_DefDataFile]->m_lpLowLevelFile != NULL, KP_E_NO_FILE, null, True);

   if(SUCCEEDED(retc)) while(/* !feof(lpInFile->m_fFiles[XL_IX_DefDataFile]->m_lpLowLevelFile) && */ SUCCEEDED(retc))
   {
XmlNode *cur_node = NULL;
      if(SUCCEEDED(retc)) retc = ReadEntry(&cur_node, lpInFile, False, iFirstTag, plpszaTags);
      if(SUCCEEDED(retc))
      {
         if(*ppNodePtr == NULL) *ppNodePtr = cur_node;
         else (*ppNodePtr)-> AppendBrother(cur_node);
      }
   }
   if(retc == KP_E_EOF) retc = S_OK;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::ReadText(XmlO1 /* XmlI */ *lpInFile)
{
HRESULT retc=S_OK;
XmlNode *cur_node = NULL;
KpChar *tag_buf = NULL;
KpChar *tag_buf_ptr = NULL;
XmlTagPars *tag_pars = NULL;
KpChar in_ch;
XmlVersions vers;

   if((lpInFile == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// create new node
   if(SUCCEEDED(retc)) retc = CreateNewChild((KpChar)XL_Text, NULL, &cur_node);

// allocate working space
   KP_NEWA(tag_buf, KpChar, TV_XM_MAX_TAG_CONTENTS_WDT + 2);

   if(SUCCEEDED(retc)) retc = lpInFile->GetVersion(&vers);

// read free text to tag_buf
   tag_buf_ptr = tag_buf;
   if(SUCCEEDED(retc)) do
   {
      if(tag_pars != NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if((tag_buf_ptr - tag_buf >= TV_XM_MAX_TAG_CONTENTS_WDT) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) do
      {
         KP_DELETE(tag_pars);
         
         retc = lpInFile->GetCharProc(&in_ch, &tag_pars,
            XL_IX_DefDataFile, False,
            (m_iNodeTag != XC_CodeExample) && (m_iNodeTag != XC_CodeExampleInline) && (m_iNodeTag != XC_Special) &&
            (m_iNodeTag != HTM_TG_SCRIPT) && (m_iNodeTag != HTM_TG_PRE) && (m_iNodeTag != HTM_TG_CODE));
      } while((in_ch == C_Cr) && SUCCEEDED(retc)); // Cr metam bet kokiu atveju – xGecko lauþia eilutæ

      if(SUCCEEDED(retc))
      {
         if(
            !(
               ((in_ch >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(in_ch)) /* (in_ch < XC_LastDictTag) */) ||
               ((in_ch >= XL_FirstSysTag) && (in_ch < XL_LastSysTag))
            )
           )
         {
            if(
            /* (m_iNodeTag != XC_CodeExample) && (m_iNodeTag != XC_CodeExampleInline) && */
               (m_iNodeTag != XC_Special) &&
               (m_iNodeTag != HTM_TG_SCRIPT) && (m_iNodeTag != HTM_TG_PRE) && (m_iNodeTag != HTM_TG_CODE) &&
               ((m_iNodeTag < XG_FirstGrpTag) || (m_iNodeTag >= XG_LastGrpTag)) &&
               (!XM_IS_VERS_HTML(vers))
              ) switch(in_ch)
            {
            case NS_CTRL_START:   // '$'
               KP_DELETE(tag_pars);

               if(SUCCEEDED(retc)) do
               {
                  retc = lpInFile->GetCharProc(&in_ch, &tag_pars,
                     XL_IX_DefDataFile, False,
                     (m_iNodeTag != XC_CodeExample) && (m_iNodeTag != XC_CodeExampleInline) && (m_iNodeTag != XC_Special) &&
                     (m_iNodeTag != HTM_TG_SCRIPT) && (m_iNodeTag != HTM_TG_PRE) && (m_iNodeTag != HTM_TG_CODE));
               } while((in_ch == C_Cr) && SUCCEEDED(retc)); // Cr metam bet kokiu atveju – xGecko lauþia eilutæ

               switch(in_ch)
               {
                  case NS_CTRL_START:  // '$' itself
                  case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//                case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
                  case C_Numb:         // '#' itself, single '#' --> C_QemSpc
                  case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD

#if FALSE // ðituos dar palikti vidiniam formate su $ prieðdëliu
                  case C_Lbrack:       // '[' itself, single '[' --> \rm
                  case C_Rbrack:       // ']' itself, single ']' --> end of \rm
                  case C_Lcurl:        // '{' itself, single '{' --> \bf
                  case C_Rcurl:        // '}' itself, single '}' --> end of \bf
#endif
                     break;

                  case C_Bpoint: in_ch = C_hBpoint; // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
                     break;
// formatting symbols
                  case C_Underl: in_ch = C_NBSP; break;    // "$_" --> C_NBSP
                  case C_At:     in_ch = C_Ff; break;      // "$@" --> C_Ff
                  case C_Circ:   in_ch = C_hbreak; break;  // "$^" --> C_hbreak
                  case C_Point:  in_ch = C_NullSpc; break; // "$." --> C_NullSpc, \Null

                  default:
                     *(tag_buf_ptr++) = NS_CTRL_START;   // paliekam '$'
                     break;
               }
               break;

            case C_Lslash: in_ch = C_hyph; break; // '\\'
            case C_Numb: in_ch = C_QemSpc; break; // '#'

//          case C_Bpoint: in_ch = DOUBLE_ENTRIES_KPCHAR; break; // DOUBLE_ENTRIES_KPCHAR ir yra C_Bpoint

            case TV_XM_CompDelim: in_ch = TV_KP_CompDelim; break;  // C_Vertl, '|'  --> C_Dvertl, TX_TG_BD
            }

            *(tag_buf_ptr++)=(KpChar)in_ch;
         }
         else retc = lpInFile->UnGetCharProc(in_ch, tag_pars
                                    , XL_IX_DefDataFile
                                    );
      }

      KP_DELETE(tag_pars);

   } while(
            (!(
               ((in_ch >= m_iFirstTag /* XC_FirstDictTag */) && (!CheckLastTag(in_ch)) /* (in_ch < XC_LastDictTag) */) ||
               ((in_ch >= XL_FirstSysTag) && (in_ch < XL_LastSysTag))
            )) &&
            SUCCEEDED(retc)
          );

   if(/* tag_buf_ptr && */ SUCCEEDED(retc)) *tag_buf_ptr = C_Nul;

// put data to child node
   if(SUCCEEDED(retc)) retc=cur_node->SetContents(tag_buf);

   KP_DELETEA(tag_buf);

return(retc);
}


HRESULT XmlNode::ReadText(XmlI *lpInFile)
{
HRESULT retc=S_OK;

   if((lpInFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = ReadText(lpInFile->FilePtr);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::PutTag(KpChar iTag, XmlTagPars *pTagParsObj, XmlO1 /* XmlI */ *lpOutFileObj)
{
HRESULT retc=S_OK;
int ch_pos;
unsigned char *indent=NULL;
XmlVersions vers;
// const unsigned char *base_indent = NULL;

   if(
      (!(
         ((iTag >= m_iFirstTag) && (!CheckLastTag(iTag))) ||
         ((iTag >= XL_FirstSysTag) && (iTag < XL_LastSysTag))
      )) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
// if(SUCCEEDED(retc)) if(lpOutFileObj->FilePtr == NULL)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
// if(SUCCEEDED(retc)) if(lpOutFileObj->FilePtr->fFiles[XL_IX_DataFile] == NULL)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->GetCharPos(&ch_pos
                                                , XL_IX_DefDataFile
                                                );

   if(SUCCEEDED(retc)) retc = lpOutFileObj->GetVersion(&vers);
   if(
      (
         ((!XM_IS_VERS_HTML(vers)) /* ((vers < XM_VERS_HTML) || (vers >= XM_VERS_XML)) */ && (TvKpStrChr(uiazXmlGrTags, iTag) != NULL)) ||
         (XM_IS_VERS_HTML(vers) && (TvKpStrChr(uiazHtmlGrTags, iTag) != NULL)) ||
         (TvKpStrChr(uiazSysGrTags, iTag) != NULL)
      ) &&
      (ch_pos>0) &&
      SUCCEEDED(retc)
     )
   {
//    retc=lpOutFileObj->PutCharProc(C_Lf, NULL
//                                     , XL_IX_DefDataFile
//                                     ); // '\n'
      retc=lpOutFileObj->m_fFiles[XL_IX_DefDataFile]->PutChar(C_Lf, True);
   }
// if(SUCCEEDED(retc)) retc = lpOutFileObj->GetBaseIndent(&base_indent);
// if(SUCCEEDED(retc)) if(base_indent == NULL)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_lpszNodeIndent != NULL) KP_NEWA(indent, unsigned char, strlen(m_lpszNodeIndent) + 3 + 1) // strlen(base_indent) + 1]; // strlen(lpOutFileObj->FilePtr->fFiles[XL_IX_DataFile]->m_lpszBaseIndentStr)+1];
      else KP_NEWA(indent, unsigned char, 3 + 1); // strlen(base_indent)+1]; // strlen(lpOutFileObj->FilePtr->fFiles[XL_IX_DataFile]->m_lpszBaseIndentStr)+1];
   }

   if(SUCCEEDED(retc))
   {
      if(m_lpszNodeIndent != NULL) strcpy(indent, m_lpszNodeIndent);
      else indent[0]=Nul;

      retc=lpOutFileObj->SetIndent(indent
                                    , XL_IX_DefDataFile
                                    );
   }

// if(SUCCEEDED(retc)) retc=lpOutFileObj->GetCharPos(&ch_pos);

// put indent charz
// if((ch_pos==0) && (m_lpszNodeIndent != NULL) && SUCCEEDED(retc))
//    retc=lpOutFileObj->PutStr(m_lpszNodeIndent);

// PutLogMessage_("XmlNode::PutTag() 1");
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(iTag, pTagParsObj
                                                         , XL_IX_DefDataFile
                                                         );

// PutLogMessage_("XmlNode::PutTag() 2");
   if(SUCCEEDED(retc))
   {
      if(((iTag & 0x01)==0) && (strlen(indent)>0)) strcat(indent, "   "); // base_indent); // lpOutFileObj->FilePtr->fFiles[XL_IX_DataFile]->m_lpszBaseIndentStr);
      retc=lpOutFileObj->SetIndent(indent
                                    , XL_IX_DefDataFile
                                    );
   }

   KP_DELETEA(indent);

return(retc);
}


HRESULT XmlNode::PutTag(KpChar iTag, XmlTagPars *pTagParsObj, XmlI *lpOutFileObj)
{
HRESULT retc=S_OK;

   if((lpOutFileObj == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = PutTag(iTag, pTagParsObj, lpOutFileObj->FilePtr);

return(retc);
}


HRESULT XmlNode::PutKpStr(KpChar *iaStr, XmlO1 *lpOutFile)
{
HRESULT retc=S_OK;
KpChar *pnts = NULL;
XmlVersions vers;

   if(((iaStr == NULL) || (lpOutFile == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = lpOutFile->GetVersion(&vers);

   if(SUCCEEDED(retc))
   {
      pnts = iaStr;
      while((*pnts) && SUCCEEDED(retc))
      {
         if(XM_IS_VERS_HTML(vers)) retc = lpOutFile->PutCharProc(*pnts, NULL, XL_IX_DefDataFile);
         else switch(*pnts)
         {
         case NS_CTRL_START:  // '$'
            switch(*(pnts+1))
            {
            case 'f':
            case 's':
            case 'u':
            case 'q':
               if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(*pnts, NULL, XL_IX_DefDataFile);
               break;
            default:
#if FALSE // kol kas neiðeina - reikia atsiþvelgti á tëvo tagà - <sl> ignoruoti formatavimà
               if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
#endif
               if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(*pnts, NULL, XL_IX_DefDataFile);
               break;
            }
            break;

#if FALSE // kol kas neiðeina - reikia atsiþvelgti á tëvo tagà - <sl> ignoruoti formatavimà
         case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//       case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
         case C_Numb:         // '#' itself, single '#' --> C_QemSpc
         case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD
         case C_Bpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
#endif

#if FALSE // ðituos dar palikti vidiniam formate su $ prieðdëliu
         case C_Lbrack:       // '[' itself, single '[' --> \rm
         case C_Rbrack:       // ']' itself, single ']' --> end of \rm
         case C_Lcurl:        // '{' itself, single '{' --> \bf
         case C_Rcurl:        // '}' itself, single '}' --> end of \bf
#endif
#if FALSE
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(*pnts, NULL, XL_IX_DefDataFile);
            break;
#endif

         case C_hBpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Bpoint, NULL, XL_IX_DefDataFile);
            break;
         case C_NBSP: // C_NBSP --> "$_"
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Underl, NULL, XL_IX_DefDataFile);
            break;
         case C_Ff: // C_Ff --> "$@"
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_At, NULL, XL_IX_DefDataFile);
            break;
         case C_hbreak: // C_hbreak --> "$^"
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Circ, NULL, XL_IX_DefDataFile);
            break;
         case C_NullSpc: // C_NullSpc, \Null --> "$."
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(NS_CTRL_START, NULL, XL_IX_DefDataFile);
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Point, NULL, XL_IX_DefDataFile);
            break;
         case C_hyph: // '\\'
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Lslash, NULL, XL_IX_DefDataFile);
            break;
         case C_QemSpc: // '#'
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(C_Numb, NULL, XL_IX_DefDataFile);
            break;
         default:
            if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(*pnts, NULL, XL_IX_DefDataFile);
            break;
         }

         pnts++;

      } // while(*pnts)

   } // if(SUCCEEDED(retc))

return(retc);
}


//-----------------------------------
// int write_node_depth = 0;
// int write_node_cnt = 0;
HRESULT XmlNode::WriteNode(XmlO1 /* XmlI */ *lpOutFile)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
XmlTagPars *tag_pars;
KpChar *cont_ptr=NULL;
KpChar cur_tag;
XmlNode *prev_brother=NULL;
XmlNode *next_brother=NULL;
XmlVersions file_vers;

// PutLogMessage_("XmlNode::WriteNode() in %5d %5d %8x: %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x", ++write_node_cnt, ++write_node_depth, &retc + 1, *(&retc + 1), *(&retc + 2), *(&retc + 3), *(&retc + 4), *(&retc + 5), *(&retc + 6), *(&retc + 7), *(&retc + 8), *(&retc + 9), *(&retc + 10));

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
      if(SUCCEEDED(retc)) retc=loop_brother->GetPrevBrother((KpTreeEntry **)&prev_brother);
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);

//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
         if((first_child!=NULL) || (cur_tag!=XL_Text))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=lpOutFile->GetVersion(&file_vers);

// PutLogMessage_("XmlNode::WriteNode() 1");
      if(
         (
            (cur_tag!=XL_Text) ||
            (
               (
                  (prev_brother!=NULL) || (next_brother!=NULL)
               ) &&
               (file_vers < XM_VERS_HTML) // ==XM_VERS_SGML_TAGE
            )
         ) &&
         ((cur_tag!=XC_Symb) || (file_vers < XM_VERS_HTML)) && // ==XM_VERS_SGML_TAGE
         SUCCEEDED(retc)
        )
         retc=loop_brother->PutTag(cur_tag, tag_pars, lpOutFile);
// PutLogMessage_("XmlNode::WriteNode() 2");

// recursion on children
// #ifndef DebugStartGrp
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->WriteNode(lpOutFile);
// #endif

      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XL_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       if(((prev_brother!=NULL) || (next_brother!=NULL)) &&
//             (file_vers==XM_VERS_SGML_TAGE) && SUCCEEDED(retc))
//          retc=lpOutFile->PutCharProc(cur_tag, NULL);

//       if(SUCCEEDED(retc)) retc = lpOutFile->PutKpStr(cont_ptr, XL_IX_DefDataFile);
         if(SUCCEEDED(retc)) retc = PutKpStr(cont_ptr, lpOutFile);
#if FALSE // #ifdef Debug
{
unsigned char *out_buf = null;
KP_NEWA(out_buf, unsigned char, TvKpStrLen(cont_ptr) + 100 + 1);
KptStrDecode(out_buf, cont_ptr, 43);
out_buf[100] = Nul;
KP_TRACE_4("%d %d %d >>>%s<<<", TvKpStrLen(cont_ptr), strlen(out_buf), cont_ptr[0], out_buf);
KP_DELETEA(out_buf);
}
#endif

//       if(((prev_brother!=NULL) || (next_brother!=NULL)) &&
//             (file_vers==XM_VERS_SGML_TAGE) && SUCCEEDED(retc))
//          retc=lpOutFile->PutCharProc(cur_tag | 0x01, NULL);
      }

      if(
         (
            (cur_tag!=XL_Text) ||
            (
               (
                  (prev_brother!=NULL) || (next_brother!=NULL)
               ) &&
               (file_vers < XM_VERS_HTML) // ==XM_VERS_SGML_TAGE
            )
         ) &&
         ((cur_tag!=XC_Symb) || (file_vers < XM_VERS_HTML)) && // ==XM_VERS_SGML_TAGE
         SUCCEEDED(retc)
        )
         retc=loop_brother->PutTag((KpChar)(cur_tag|0x01), NULL, lpOutFile);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteNode(lpOutFile);

// PutLogMessage_("XmlNode::WriteNode() ou %5d %5d %8x: %8x %8x %8x %8x %8x %8x %8x %8x %8x %8x", write_node_cnt, write_node_depth--, &retc + 1, *(&retc + 1), *(&retc + 2), *(&retc + 3), *(&retc + 4), *(&retc + 5), *(&retc + 6), *(&retc + 7), *(&retc + 8), *(&retc + 9), *(&retc + 10));

return(retc);
}


HRESULT XmlNode::WriteNode(XmlI *lpOutFile)
{
HRESULT retc=S_OK;

   if((lpOutFile == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = WriteNode(lpOutFile->FilePtr);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::WriteEmbeddedCompounds(KpChar *lpaiBasePtr, XmlI *lpOutFile, long *plEntryId, bool /* bOutFl */)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *child_brother = NULL;
KpChar cur_tag;
XmlNode *prev_brother = NULL;
XmlNode *next_brother = NULL;
XmlTagPars *tag_pars = NULL;
unsigned char *indent_ptr = NULL;
int ii;
bool written;

   if(((lpOutFile==NULL) || (plEntryId==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&child_brother);
      if(SUCCEEDED(retc)) child_brother = (XmlNode *)loop_brother->m_pFirstChild;

      while((child_brother!=NULL) && SUCCEEDED(retc))
      {
// recursion on children
         if(SUCCEEDED(retc)) retc=child_brother->WriteEmbeddedCompounds(lpaiBasePtr, lpOutFile, plEntryId, False);

         if((child_brother!=NULL) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=child_brother->GetPrevBrother((KpTreeEntry **)&prev_brother);
            if(SUCCEEDED(retc)) retc=child_brother->GetNextBrother((KpTreeEntry **)&next_brother);

            if(SUCCEEDED(retc)) retc=child_brother->GetNodeTag(&cur_tag);

            if((TvKpStrChr(uiazXmlCpdGrTags, cur_tag)!=NULL) && SUCCEEDED(retc))
            {
               retc=child_brother->SetNodeTag((KpChar)XC_HeadWordGroup);
               if(SUCCEEDED(retc))
                  retc=child_brother->SetNextBrother(NULL);

               if(SUCCEEDED(retc)) do
               {
                  retc=child_brother->GetIndentPtr(&indent_ptr);
                  if(SUCCEEDED(retc)) ii=strlen(indent_ptr);
                  if((ii>XN_POS_PER_INDENT) && SUCCEEDED(retc))
                     retc=child_brother->ReduceIndent();
               } while((ii>XN_POS_PER_INDENT) && SUCCEEDED(retc));

// increase entry id
               if(SUCCEEDED(retc))
               {
                  (*plEntryId)++;
                  KpErrorProc.SetLPar(*plEntryId);
               }
// create <se> tag pars
               KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"id", *plEntryId, NULL));

               if(SUCCEEDED(retc)) retc=child_brother->MapTags((KpChar)XC_CompoundWord, (KpChar)XC_HeadWord);
//             if(SUCCEEDED(retc)) retc=child_brother->MapTags((KpChar)XC_Struct, (KpChar)XC_HeadWord);
//             if(SUCCEEDED(retc)) retc=child_brother->MapTags((KpChar)XC_OblStruct, (KpChar)XC_HeadWord);
//             if(SUCCEEDED(retc)) retc=child_brother->MapTags((KpChar)XC_SrcWord, (KpChar)XC_HeadWord);
               if(SUCCEEDED(retc)) retc=child_brother->MapTags((KpChar)XC_Derivative, (KpChar)XC_HeadWord);

               if(SUCCEEDED(retc)) retc=child_brother->SubstBase(lpaiBasePtr, True);

               if(SUCCEEDED(retc)) retc=child_brother->SubstBase(lpaiBasePtr, False);
               if(SUCCEEDED(retc)) retc=child_brother->DelCompDelim();

               written=False;
               if(SUCCEEDED(retc)) retc=child_brother->WriteGroupVariants(child_brother, lpOutFile, plEntryId, &written, True);
               if((!written) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)XC_StEntry, tag_pars);
                  if(SUCCEEDED(retc)) retc=child_brother->WriteNode(lpOutFile);
                  if(SUCCEEDED(retc)) retc=lpOutFile->SetIndent((const unsigned char *)"");
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)XC_StEntry_e, NULL);
               }

               KP_DELETE(tag_pars);

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL)
                     retc=prev_brother->ConnectBrother(next_brother);
                  else retc=loop_brother->ConnectChild(next_brother);
               }

               if(SUCCEEDED(retc)) retc = child_brother->SetNextBrother(NULL);
               if(SUCCEEDED(retc)) KP_DELETE(child_brother);
            }

            child_brother = next_brother;

         } // if((child_brother!=NULL) && SUCCEEDED(retc))

      } // while((child_brother!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteEmbeddedCompounds(lpOutFile);

return(retc);
}


// --------------------------------------------------
#if FALSE
HRESULT XmlNode::WriteEmbeddedCompounds(const KpChar *lpaiBasePtr, XmlI *lpOutFile, long *plEntryId, bool bOutFl)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *cur_node = NULL;
XmlNode *prev_brother = NULL;
XmlNode *next_brother = NULL;
XmlTagPars *tag_pars = NULL;
// XmlTagPars *prev_pars = NULL;
KpChar cur_tag;
KpChar node_tag;
int red_cnt;
int ii;
unsigned char *indent_ptr = NULL;
bool found;
bool written;
// unsigned char *base_indent = NULL;

   if(((lpaiBasePtr==NULL) || (lpOutFile==NULL) || (plEntryId==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(((lpOutFile==NULL) || (plEntryId==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild(&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if((cur_node!=NULL) && SUCCEEDED(retc))
            retc=cur_node->WriteEmbeddedCompounds(lpaiBasePtr, lpOutFile, plEntryId, False);

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother(&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
         if(SUCCEEDED(retc))
         {
            if(
               (cur_tag==XC_CompoundGroup) ||
               (cur_tag==XC_DerivGroup)
              )
            {
// tag matched - recurse extraction
               retc=cur_node->WriteEmbeddedCompounds(lpaiBasePtr, lpOutFile, plEntryId, True);

// delete subnode
               if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
               KP_DELETE(cur_node);

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(next_brother);
                  }
               }
            }
         }

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother(&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteEmbeddedCompounds(iTag);

// ----------------------- output node
   if(bOutFl && SUCCEEDED(retc))
   {
// increase entry id
      if(SUCCEEDED(retc))
      {
         (*plEntryId)++;
         KpErrorProc.SetLPar(*plEntryId);
      }

      KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"id", *plEntryId));

      if(SUCCEEDED(retc)) retc = GetNodeTag(&node_tag);

      if(SUCCEEDED(retc))
      {
         if((node_tag == XC_CompoundGroup) || (node_tag==XC_DerivGroup))
         {
// replace headwords
//          if(SUCCEEDED(retc)) retc = GetFirstChild(&cur_node);
            if(SUCCEEDED(retc)) cur_node = m_pFirstChild;
            found=False;
            while(cur_node && SUCCEEDED(retc))
            {
               retc=cur_node->GetNodeTag(&cur_tag);

               if(
                  (
                     ((node_tag==XC_CompoundGroup) && (cur_tag==XC_CompoundWord)) ||
                     ((node_tag==XC_DerivGroup) && (cur_tag==XC_Derivative))
                  ) &&
                  SUCCEEDED(retc)
               )
               {
                  retc=cur_node->SetNodeTag(found?XC_Variant:XC_HeadWord);
                  found=True;
               }

               if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother(&cur_node);

            } // while(cur_node && SUCCEEDED(retc))

            if((!found) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

// replace node tag
            if(SUCCEEDED(retc)) retc=SetNodeTag(XC_HeadWordGroup);

// reduce indent
            if(SUCCEEDED(retc)) retc = GetIndentPtr(&indent_ptr);
//          if(SUCCEEDED(retc)) retc=lpOutFile->GetBaseIndent(&base_indent);
//          if(SUCCEEDED(retc)) if(base_indent == NULL)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               red_cnt = strlen(indent_ptr) / XN_POS_PER_INDENT - 1; // strlen(base_indent) - 1;
               for(ii = 0; (ii < red_cnt) && SUCCEEDED(retc); ii++)
                  retc = ReduceIndent();
            }

// write entry
            written=False;
            if(SUCCEEDED(retc)) retc=this->WriteGroupVariants(this, lpOutFile, plEntryId, &written, True);
            if((!written) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(XC_StEntry, tag_pars);
               if(SUCCEEDED(retc)) retc=WriteNode(lpOutFile);
               if(SUCCEEDED(retc)) retc=lpOutFile->SetIndent((const unsigned char *)"");
               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(XC_StEntry_e, NULL);
            }

// !!!
// delete subnode
               if(SUCCEEDED(retc)) retc = SetNextBrother(NULL);
               KP_DELETE(this); // !!!!

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc = loop_brother->ConnectChild(next_brother);
                  }
               }

// !!!!

            KP_DELETE(tag_pars);
         }
         else // if((node_tag==XC_CompoundGroup) || (node_tag==XC_DerivGroup))
         {
// XC_StEntry
            if((node_tag!=XC_StEntry) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// set entry id
#if FALSE
            if(SUCCEEDED(retc)) retc = GetTagParsPtr(&prev_pars);
            KP_ASSERT(prev_pars != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_DELETE(prev_pars);
#endif

            if(SUCCEEDED(retc))
            {
               retc = SetTagParsPtr(tag_pars);
               if(FAILED(retc)) KP_DELETE(tag_pars);
            }

            if(SUCCEEDED(retc)) retc=SubstBase(lpaiBasePtr, False);
            if(SUCCEEDED(retc)) retc=DelCompDelim();

// write entry
            written=False;
            if(SUCCEEDED(retc)) retc=this->WriteGroupVariants(this, lpOutFile, plEntryId, &written, False);
            if((!written) && SUCCEEDED(retc)) retc=WriteNode(lpOutFile);

         } // else // if((node_tag==XC_CompoundGroup) || (node_tag==XC_DerivGroup))

      } // if(SUCCEEDED(retc))

   } // if(bOutFl && SUCCEEDED(retc))

return(retc);
}
#endif


// --------------------------------------------------
HRESULT XmlNode::WriteGroupVariants(XmlNode *pMainNode, XmlI *lpOutFile, long *plEntryId, bool *pbWritten, bool bEncloseToSe)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *child_brother;
KpChar cur_tag;
KpChar next_tag;
XmlNode *prev_brother;
XmlNode *next_brother;
XmlNode *rest_tail;
XmlNode *rest_variants;
XmlNode *last_variant;
bool found;
XmlTagPars *tag_pars=NULL;

   if(((pMainNode==NULL) || (lpOutFile==NULL) || (plEntryId==NULL) || (pbWritten==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&child_brother);
      if(SUCCEEDED(retc)) child_brother = (XmlNode *)loop_brother->m_pFirstChild;

      while((child_brother!=NULL) && (!(*pbWritten)) && SUCCEEDED(retc))
      {
// recursion on children
         if(SUCCEEDED(retc)) retc=child_brother->WriteGroupVariants(pMainNode, lpOutFile, plEntryId, pbWritten, bEncloseToSe);

         if((child_brother!=NULL) && (!(*pbWritten)) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=child_brother->GetPrevBrother((KpTreeEntry **)&prev_brother);
            if(SUCCEEDED(retc)) retc=child_brother->GetNextBrother((KpTreeEntry **)&next_brother);

            if(SUCCEEDED(retc)) retc=child_brother->GetNodeTag(&cur_tag);
            next_tag=(KpChar)XC_Nul;
            if((next_brother!=NULL) && SUCCEEDED(retc))
               retc=next_brother->GetNodeTag(&next_tag);

            if(
               (TvKpStrChr(uiazXmlVariantTags, cur_tag)!=NULL) &&
               (TvKpStrChr(uiazXmlVariantTags, next_tag)!=NULL) &&
               SUCCEEDED(retc)
              )
            {
               *pbWritten=True;

               rest_variants=rest_tail=child_brother;
               found=False;
               do
               {
                  if(SUCCEEDED(retc)) retc=rest_tail->GetNextBrother((KpTreeEntry **)&rest_tail);
                  if((rest_tail!=NULL) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc=rest_tail->GetNodeTag(&cur_tag);
                     if((TvKpStrChr(uiazXmlVariantTags, cur_tag)==NULL) && SUCCEEDED(retc))
                        found=True;
                  }
               } while((rest_tail!=NULL) && (!found) && SUCCEEDED(retc));

               if((rest_tail!=NULL) && SUCCEEDED(retc))
               {
                  retc=rest_tail->GetPrevBrother((KpTreeEntry **)&last_variant);
                  if(SUCCEEDED(retc)) retc=rest_tail->SetPrevBrother(NULL);
               }
               if((last_variant!=NULL) && SUCCEEDED(retc)) // nulis buna, kai variantai tarp skliaustu
                  retc=last_variant->SetNextBrother(NULL);

               while((rest_variants!=NULL) && SUCCEEDED(retc))
               {
                  child_brother=rest_variants;
                  retc=rest_variants->GetNextBrother((KpTreeEntry **)&rest_variants);
                  if((rest_variants!=NULL) && SUCCEEDED(retc))
                     retc=rest_variants->SetPrevBrother(NULL);

                  if(SUCCEEDED(retc))
                  {
                     if(prev_brother!=NULL)
                        retc=prev_brother->ConnectBrother(child_brother);
                     else retc=loop_brother->ConnectChild(child_brother);
                  }
                  if(SUCCEEDED(retc))
                     retc=child_brother->ConnectBrother(rest_tail);

// increase entry id
                  if(SUCCEEDED(retc))
                  {
                     (*plEntryId)++;
                     KpErrorProc.SetLPar(*plEntryId);
                  }
// create <se> tag pars
                  KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"id", *plEntryId, NULL));

                  if(bEncloseToSe && SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)XC_StEntry, tag_pars);

                  if((!bEncloseToSe) && SUCCEEDED(retc))
                  {
                     retc=pMainNode->GetNodeTag(&cur_tag);
                     if((cur_tag!=XC_StEntry) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                     if(SUCCEEDED(retc)) retc=pMainNode->SetTagParsPtr(tag_pars);
                     tag_pars=NULL;
                  }

                  if(SUCCEEDED(retc)) retc=pMainNode->WriteNode(lpOutFile);

                  if(bEncloseToSe && SUCCEEDED(retc)) retc=lpOutFile->SetIndent((const unsigned char *)"");
                  if(bEncloseToSe && SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)XC_StEntry_e, NULL);

                  KP_DELETE(tag_pars);

                  if((rest_variants!=NULL) && SUCCEEDED(retc))
                  {
                     retc = child_brother->SetNextBrother(NULL);
                     if(SUCCEEDED(retc)) KP_DELETE(child_brother);
                  }

               } // while((rest_variants!=NULL) && SUCCEEDED(retc))

            } // if((TvKpStrChr(uiazXmlVariantTags, cur_tag)!=NULL) &&

            child_brother=next_brother;

         } // if((child_brother!=NULL) && (!(*pbWritten)) && SUCCEEDED(retc))

      } // while((child_brother!=NULL) && (!(*pbWritten)) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->WriteEmbeddedCompounds(lpOutFile);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::WriteNodeWithSubNode(XmlNode *pCatSubNode, XmlI *lpOutFile)
{
HRESULT retc=S_OK;
XmlNode *cur_subnode;
XmlNode *cur_child;
XmlNode *next_child;
XmlNode *last_cat_sub;
XmlNode *next_cat_sub;
KpChar cur_tag;

   if(pCatSubNode==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      last_cat_sub=pCatSubNode;
      do
      {
         retc=last_cat_sub->GetNextBrother((KpTreeEntry **)&next_cat_sub);
         if((next_cat_sub!=NULL) && SUCCEEDED(retc))
            last_cat_sub=next_cat_sub;
      } while((next_cat_sub!=NULL) && SUCCEEDED(retc));
   }

// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_subnode);
   if(SUCCEEDED(retc)) cur_subnode = (XmlNode *)m_pFirstChild;

   if((cur_subnode==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=cur_subnode->GetNodeTag(&cur_tag);
   if((cur_tag!=XC_HeadWordGroup) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   cur_child=NULL;
// if(SUCCEEDED(retc)) retc = cur_subnode->GetFirstChild((KpTreeEntry **)&next_child);
   if(SUCCEEDED(retc)) next_child = (XmlNode *)cur_subnode->m_pFirstChild;

   while((next_child!=NULL) && SUCCEEDED(retc))
   {
      retc=next_child->GetNodeTag(&cur_tag);
      if((TvKpStrChr(uiazXmlHwGrTags, cur_tag)==NULL) && SUCCEEDED(retc))
      {
         cur_child=next_child;
         retc=next_child->GetNextBrother((KpTreeEntry **)&next_child);
      }
      else break;
   }

   if(SUCCEEDED(retc))
   {
      if(cur_child!=NULL) retc=cur_child->ConnectBrother(pCatSubNode);
      else retc=cur_subnode->ConnectChild(pCatSubNode);
   }

   if(SUCCEEDED(retc)) retc=last_cat_sub->ConnectBrother(next_child);

   if(SUCCEEDED(retc)) retc=WriteNode(lpOutFile);

   if(SUCCEEDED(retc))
   {
      if(cur_child!=NULL) retc=cur_child->ConnectBrother(next_child);
      else retc=cur_subnode->ConnectChild(next_child);
   }

   if(SUCCEEDED(retc)) retc=pCatSubNode->SetPrevBrother(NULL);
   if(SUCCEEDED(retc)) retc=last_cat_sub->SetNextBrother(NULL);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::WriteNodeDupCats(XmlI *lpOutFile)
{
HRESULT retc=S_OK;
XmlNode *child_cat_brothers;
XmlNode *cur_cat_child;
XmlNode *first_child;

   child_cat_brothers=NULL;
   retc=ExtractSubNodes(&child_cat_brothers, (KpChar)XC_CtgGroup);

   cur_cat_child=child_cat_brothers;
   while((cur_cat_child!=NULL) && SUCCEEDED(retc))
   {
//    retc = cur_cat_child->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)cur_cat_child->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=WriteNodeWithSubNode(first_child, lpOutFile);

      if(SUCCEEDED(retc)) retc=cur_cat_child->GetNextBrother((KpTreeEntry **)&cur_cat_child);
   }

   if((child_cat_brothers==NULL) && SUCCEEDED(retc)) retc=WriteNode(lpOutFile);

   KP_DELETE(child_cat_brothers);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::WriteNodeDupTrGroups(XmlI *lpOutFile)
{
HRESULT retc=S_OK;
XmlNode *child_tg_brothers;
XmlNode *cur_tg_child;
XmlNode *prev_brother;
XmlNode *next_brother;

   child_tg_brothers=NULL;
   retc=ExtractSubNodes(&child_tg_brothers, (KpChar)XC_TranslGroup);

   cur_tg_child=child_tg_brothers;
   while((cur_tg_child!=NULL) && SUCCEEDED(retc))
   {
      retc=cur_tg_child->GetPrevBrother((KpTreeEntry **)&prev_brother);
      if(SUCCEEDED(retc)) retc=cur_tg_child->GetNextBrother((KpTreeEntry **)&next_brother);

      if(SUCCEEDED(retc)) retc=cur_tg_child->SetPrevBrother(NULL);
      if(SUCCEEDED(retc)) retc=cur_tg_child->SetNextBrother(NULL);

      if(SUCCEEDED(retc)) retc=WriteNodeWithSubNode(cur_tg_child, lpOutFile);

      if(SUCCEEDED(retc)) retc=cur_tg_child->SetPrevBrother(prev_brother);
      if(SUCCEEDED(retc)) retc=cur_tg_child->SetNextBrother(next_brother);

      if(SUCCEEDED(retc)) retc=cur_tg_child->GetNextBrother((KpTreeEntry **)&cur_tg_child);
   }

   if((child_tg_brothers==NULL) && SUCCEEDED(retc)) retc=WriteNode(lpOutFile);

   KP_DELETE(child_tg_brothers);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::WriteNodeDupTrWords(XmlI *lpOutFile)
{
HRESULT retc=S_OK;
XmlNode *child_tw_brothers;
XmlNode *child_start;
XmlNode *child_end;
XmlNode *child_rest;

   child_tw_brothers=NULL;
   retc=ExtractSubNodes(&child_tw_brothers, (KpChar)XC_TrWord);

   child_rest=child_start=child_tw_brothers;

   if((child_rest!=NULL) && SUCCEEDED(retc))
      retc=child_rest->SkipBrothersToTag(&child_rest, (KpChar)XC_TrWord); // skip next not <tw> tags

   do
   {
      if((child_rest!=NULL) && SUCCEEDED(retc))
         retc=child_rest->GetNextBrother((KpTreeEntry **)&child_rest); // skip first <tw>

      if((child_rest!=NULL) && SUCCEEDED(retc))
         retc=child_rest->SkipBrothersToTag(&child_rest, (KpChar)XC_TrWord); // skip next not <tw> tags

      if((child_rest!=NULL) && SUCCEEDED(retc))
      {
         retc=child_rest->GetPrevBrother((KpTreeEntry **)&child_end); // last brother
         if((child_end==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=child_end->SetNextBrother(NULL); // break chain
         if(SUCCEEDED(retc)) retc=child_rest->SetPrevBrother(NULL);
      }

      if(SUCCEEDED(retc)) retc=EncloseToGroup(&child_start, (KpChar)XC_TranslGroup);
      if(SUCCEEDED(retc)) retc=DelEmptyTags();
      if(SUCCEEDED(retc)) retc=WriteNodeWithSubNode(child_start, lpOutFile);

      if(child_start && SUCCEEDED(retc))
      {
         retc = child_start->SetNextBrother(NULL);
         if(SUCCEEDED(retc))
         {
            KP_DELETE(child_start);
            child_start = child_rest;
         }
      }

   } while((child_start!=NULL) && SUCCEEDED(retc));

   if((child_tw_brothers==NULL) && SUCCEEDED(retc)) retc=WriteNode(lpOutFile);

return(retc);
}


// ==================================================
// --------------------------------------------------
HRESULT XmlNode::DelEmptyTags(void)
{
HRESULT retc = S_OK;
XmlNode *cur_node = NULL;
KpChar cur_tag;
XmlNode *prev_brother = NULL;
XmlNode *next_brother = NULL;
XmlNode *first_child = NULL;
XmlNode *loop_brother = NULL;
KpChar *text_buf_ptr = NULL;
const KpChar *pnti = NULL;
KpChar prev_tag;
KpChar first_tag;
KpChar last_tag;
const unsigned char * const *tag_names = NULL;

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {

// if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
// printf("=== %d %s\n", cur_tag, m_plpszaTags /* plpszaXmlttDictTags */[cur_tag - m_iFirstTag /* XC_FirstDictTag */]);

      prev_brother=NULL;
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&prev_tag);

// recursion through children of children first
      while((cur_node!=NULL) && SUCCEEDED(retc))
      {

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
// printf("--- %d %s\n", cur_tag, m_plpszaTags /* plpszaXmlttDictTags */[cur_tag - m_iFirstTag /* XC_FirstDictTag */]);

//       if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild(&first_child);
//       if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->DelEmptyTags();
         if(SUCCEEDED(retc)) retc=cur_node->DelEmptyTags();

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

//       if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;
// #ifdef Debug
// if(
// (first_child==NULL) &&
// (strlen(m_plpszaTags /* plpszaXmlttDictTags */[cur_tag + 1 - m_iFirstTag /* XC_FirstDictTag */])==0) &&
// (cur_tag!=XC_Equiation)
// )
// first_child=NULL;
// #endif

         if(SUCCEEDED(retc))
         {
            if((cur_tag >= m_iFirstTag) && (cur_tag < m_iLastTag) /* (!CheckLastTag(cur_tag)) */)
            {
               first_tag = m_iFirstTag;
               last_tag = m_iLastTag;
               tag_names = m_plpszaTags;
            }
            else if((cur_tag >= XL_FirstSysTag) && (cur_tag < XL_LastSysTag))
            {
               first_tag = XL_FirstSysTag;
               last_tag = XL_LastSysTag;
               tag_names = plpszaXmlSysTags;
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         }

         if(
            (first_child==NULL) &&
//          (strlen(m_plpszaTags /* plpszaXmlttDictTags */[cur_tag + 1 - m_iFirstTag /* XC_FirstDictTag */])>0) && // not single tag
            (strstr(tag_names /* m_plpszaTags */ /* plpszaXmlttDictTags */[cur_tag -
                        first_tag /* m_iFirstTag */ /* XC_FirstDictTag */], "/>") == NULL) && // not single tag
            SUCCEEDED(retc)
           )
         {
// no children - test text contents
            retc=cur_node->GetContentsPtr(&text_buf_ptr);
            if((text_buf_ptr!=NULL) && SUCCEEDED(retc))
            {
               pnti=text_buf_ptr;
//             while((TvStrChr(lpszSpaces, *pnti)!=NULL) && (*pnti!=C_Nul)) pnti++;
               if((TvKpStrLen(pnti)==0) /* && (prev_tag!=XC_PunctMark) */)
                  text_buf_ptr=NULL;
            }

// no text contents - delete node
//          if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
            if((text_buf_ptr==NULL) && (TvKpStrChr(uiazXmlSingleTags, cur_tag)==NULL) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
               KP_DELETE(cur_node);

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(next_brother);
                  }
               }
            }
         }

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelEmptyTags();

return(retc);
}


// int del_cnt=0;

// --------------------------------------------------
HRESULT XmlNode::DelTags(KpChar iTag)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
KpChar cur_tag;

// if(((iTag < m_iFirstTag) || CheckLastTag(iTag)) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// printf("==== %d %x\n", del_cnt++, this);
// retc=TestNode();

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if((cur_node!=NULL) && SUCCEEDED(retc))
            retc=cur_node->DelTags(iTag);

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
         if((cur_tag==iTag) && SUCCEEDED(retc))
         {
// tag matched - delete subnode
            if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
            KP_DELETE(cur_node);

            if(SUCCEEDED(retc))
            {
               if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
               else
               {
// first child deleted - update first child
                  retc=loop_brother->ConnectChild(next_brother);
               }
            }

         } // if((cur_tag==iTag) && SUCCEEDED(retc))

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelTags(iTag);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::DelTagsByValue(KpChar iTag, const unsigned char *lpszValue, bool *pbFoundFl)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_node=NULL;
XmlNode *prev_brother=NULL;
XmlNode *next_brother=NULL;
XmlNode *first_child=NULL;
KpChar cur_tag;
unsigned char *str_buf;
KpChar *val_buf;
bool found_fl=False;
KpChar *contents_ptr;
int ll;

   if((
//     (iTag < m_iFirstTag) || CheckLastTag(iTag) ||
       (pbFoundFl==NULL)
       ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if((cur_node!=NULL) && SUCCEEDED(retc))
            retc=cur_node->DelTagsByValue(iTag, lpszValue, pbFoundFl);

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
         if((cur_tag==iTag) && SUCCEEDED(retc))
         {
            found_fl=False;
//          if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
            if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

            if((first_child!=NULL) && SUCCEEDED(retc))
            {
               retc=first_child->GetNodeTag(&cur_tag);
               if(SUCCEEDED(retc))
               {
                  if(cur_tag!=XL_Text)
                  {
                     found_fl=True;
                     if(lpszValue!=NULL)
                        if(strlen(lpszValue)>0)
                           found_fl=False;
                  }
                  else
                  {
                     if(SUCCEEDED(retc)) retc=first_child->GetContentsPtr(&contents_ptr);
                     if((contents_ptr==NULL) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

                     str_buf = NULL;
                     val_buf = NULL;

                     if(SUCCEEDED(retc))
                     {
                        ll = TvKpStrLen(contents_ptr);
                        KP_NEWA(str_buf, unsigned char, ll + 1);
                     }

                     KP_NEWA(val_buf, KpChar, ll + 1);

                     if(SUCCEEDED(retc))
                     {
                        TvKpStrCpy(val_buf, contents_ptr);
                        TvKpStrLat(val_buf);
                        retc=KptStrDecode(str_buf, val_buf, 1);
                     }

                     if((lpszValue!=NULL) && SUCCEEDED(retc))
                     {
                        if(strlen(lpszValue)>0)
                           if(strcmp(str_buf, lpszValue)==0) found_fl=True;
                     }

                     KP_DELETEA(val_buf);
                     KP_DELETEA(str_buf);

                  } // else // if(cur_tag!=XL_Text)

               } // if(SUCCEEDED(retc))

            } // if((first_child!=NULL) && SUCCEEDED(retc))

            if(found_fl && SUCCEEDED(retc))
            {
               *pbFoundFl=True;

// tag matched - delete subnode
               if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
               KP_DELETE(cur_node);

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(next_brother);
                  }
               }

            } // if(found_fl && SUCCEEDED(retc))

         } // if((cur_tag==iTag) && SUCCEEDED(retc))

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelTags(iTag);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::MapTags(KpChar iFromTag, KpChar iToTag)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
KpChar cur_tag;

// if(
//    (
//       (!(
//          ((iFromTag >= m_iFirstTag) && (!CheckLastTag(iFromTag))) ||
//          ((iFromTag >= XL_FirstSysTag) && (iFromTag < XL_LastSysTag))
//       )) ||
//       (!(
//          ((iToTag >= m_iFirstTag) && (!CheckLastTag(iToTag))) ||
//          ((iToTag >= XL_FirstSysTag) && (iToTag < XL_LastSysTag))
//       ))
//    ) &&
//    SUCCEEDED(retc)
//   )
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
// change tag
      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
      if((cur_tag==iFromTag) && SUCCEEDED(retc)) retc=loop_brother->SetNodeTag(iToTag);

// recursion through children
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=first_child->MapTags(iFromTag, iToTag);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->MapTags(iTag);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::ReduceIndent(void)
{
HRESULT retc = S_OK;
int ind_len;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
unsigned char *indent_ptr = null;
// unsigned char *base_indent = NULL;

#if FALSE
   if(SUCCEEDED(retc)) if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = lpOutFileObj->GetBaseIndent(&base_indent);
   if(SUCCEEDED(retc)) if(base_indent == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif

// loop on brothers
   loop_brother = this;
   while((loop_brother != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = loop_brother->GetIndentPtr(&indent_ptr);

      if(indent_ptr != NULL)
      {
         ind_len = strlen(indent_ptr) - XN_POS_PER_INDENT; // strlen(base_indent);
         if(ind_len < 0) ind_len = 0;
         indent_ptr[ind_len] = Nul;
      }

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child != NULL) && SUCCEEDED(retc)) retc = first_child->ReduceIndent();

      if(SUCCEEDED(retc)) retc = loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother != NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->ReduceIndent();

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::IncreaseIndent(void)
{
HRESULT retc = S_OK;
int ind_len;
unsigned char *new_indent = NULL;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
unsigned char *indent_ptr = null;
// unsigned char *base_indent = NULL;

#if FALSE
   if(SUCCEEDED(retc)) if(lpOutFileObj == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = lpOutFileObj->GetBaseIndent(&base_indent);
   if(SUCCEEDED(retc)) if(base_indent == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif

// loop on brothers
   loop_brother = this;
   while((loop_brother != NULL) && SUCCEEDED(retc))
   {
      retc = loop_brother->GetIndentPtr(&indent_ptr);

      ind_len = XN_POS_PER_INDENT; // strlen(base_indent);
      if(indent_ptr != NULL) ind_len += strlen(indent_ptr);

      KP_NEWA(new_indent, unsigned char, ind_len + 1);

      if(SUCCEEDED(retc))
      {
         strcpy(new_indent, "   "); // XN_POS_PER_INDENT // base_indent);
         if(indent_ptr != NULL) strcat(new_indent, indent_ptr);
         retc = loop_brother->SetIndent(new_indent);
      }

      KP_DELETEA(new_indent);

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child != NULL) && SUCCEEDED(retc)) retc = first_child->IncreaseIndent();

      if(SUCCEEDED(retc)) retc = loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother != NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc=pNextBrother->IncreaseIndent();

return(retc);
}


//-----------------------------------
HRESULT XmlNode::ReduceIndentNested(void)
{
HRESULT retc = S_OK;
int ind_len;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
unsigned char *indent_ptr = null;
// const unsigned char *base_indent = NULL;

#if FALSE
   if(SUCCEEDED(retc)) if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = lpOutFileObj->GetBaseIndent(&base_indent);
   if(SUCCEEDED(retc)) if(base_indent == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif

// loop on brothers
   loop_brother = this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc = loop_brother->GetIndentPtr(&indent_ptr);

      if(indent_ptr!=NULL)
      {
         ind_len=strlen(indent_ptr)-XN_POS_PER_INDENT; // strlen(base_indent);
         if(ind_len<0) ind_len=0;
         indent_ptr[ind_len]=Nul;
      }

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->ReduceIndent();

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->ReduceIndent();

return(retc);
}


// ================================================== dictionary inverting functions
// --------------------------------------------------
HRESULT XmlNode::DelUnmatchedCtgs(KpChar *piPsPtr)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
XmlNode *first_child;
XmlNode *next_child;
XmlNode *last_child;
KpChar node_tag;
KpChar *pnti;
bool found_fl;
XmlNode *loop_brother;

   if((
//       (piPsPtr[...] < m_iFirstTag) || CheckLastTag(piPsPtr[...]) ||
         (piPsPtr==NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      pnti=piPsPtr;
      while((TvStrChr(lpszSpaces, *pnti)!=NULL) && (*pnti!=C_Nul)) pnti++;
      if(TvKpStrLen(pnti)!=0)
      {
         prev_brother=NULL;
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
         cur_node = (XmlNode *)loop_brother->m_pFirstChild;

         while((cur_node!=NULL) && SUCCEEDED(retc))
         {
// continue recursion on children
            if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->DelUnmatchedCtgs(piPsPtr);

            retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

            if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&node_tag);
            if((node_tag==XC_CtgGroup) && SUCCEEDED(retc))
            {
// search gram. form of category
               retc=cur_node->TestChildContents((KpChar)XC_PartOfSpeechSrc, pnti, &found_fl);
               if(SUCCEEDED(retc))
               {
                  if(found_fl)
                  {
// delete very external XC_CtgGroup tag, extract contents
//                   retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
                     first_child = (XmlNode *)cur_node->m_pFirstChild;

                     if(SUCCEEDED(retc))
                     {
                        if(first_child!=NULL)
                        {
                           last_child=first_child;
                           do
                           {
                              retc=last_child->GetNextBrother((KpTreeEntry **)&next_child);
                              if((next_child!=NULL) && SUCCEEDED(retc)) last_child=next_child;
                           } while((next_child!=NULL) && SUCCEEDED(retc));

                           if(SUCCEEDED(retc)) retc=first_child->ReduceIndent();

                           if(SUCCEEDED(retc))
                              retc=last_child->ConnectBrother(next_brother);

                           if(SUCCEEDED(retc))
                           {
                              if(prev_brother!=NULL)
                               retc=prev_brother->ConnectBrother(first_child);
                              else retc=loop_brother->ConnectChild(first_child);
                           }

                           retc0=cur_node->SetFirstChild(NULL);
                           if(SUCCEEDED(retc)) retc=retc0;
                           if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
                           if(SUCCEEDED(retc))
                           {
                              KP_DELETE(cur_node);
                              cur_node = last_child;
                           }
                        }
                        else
                        {
                           if(SUCCEEDED(retc))
                           {
                              if(prev_brother!=NULL)
                                 retc=prev_brother->ConnectBrother(next_brother);
                              else retc=loop_brother->ConnectChild(next_brother);
                           }

                           if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
                           if(SUCCEEDED(retc))
                           {
                              KP_DELETE(cur_node);
                              cur_node = prev_brother;
                           }
                        }
                     }
                  }
                  else
                  {
// delete current category node
                     if(SUCCEEDED(retc))
                     {
                        if(prev_brother!=NULL)
                           retc=prev_brother->ConnectBrother(next_brother);
                        else retc=loop_brother->ConnectChild(next_brother);
                     }
                     if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
                     if(SUCCEEDED(retc))
                     {
                        KP_DELETE(cur_node);
                        cur_node = prev_brother;
                     }
                  }
               }
            }

            prev_brother=cur_node;
            cur_node=next_brother;
         }

      } // if(TvKpStrLen(pnti)==0) text_buf_ptr=NULL;

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild(&first_child);
//    if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->DelUnmatchedCtgs(piPsPtr);

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelUnmatchedCtgs(piPsPtr);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::Hw2Tw(void)
{
HRESULT retc = S_OK;
XmlNode *cur_node = NULL;
XmlNode *next_brother = NULL;
XmlNode *new_node = NULL;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
KpChar node_tag;
KpChar child_tag;
unsigned char *indent_ptr = null;
bool example_fl, usage_fl, idiom_fl, compound_fl, struct_fl, obl_struct_fl, deriv_fl, src_word_fl;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc)) // !!! ??? ar ne dvigubas ciklas?
// if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
// enclose first free tags of headword containing group tags to XC_TranslGroup
      retc=loop_brother->GetNodeTag(&node_tag);
      if((TvKpStrChr(uiazXmlHwGrTags, node_tag)!=NULL) && SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child!=NULL) && SUCCEEDED(retc))
         {
            retc=first_child->GetNodeTag(&child_tag);
            if((TvKpStrChr(uiazXmlGrTags, child_tag)==NULL) && SUCCEEDED(retc))
            {
// first tag is not group tag - proceed
               example_fl = usage_fl = idiom_fl = compound_fl = struct_fl = obl_struct_fl = deriv_fl = src_word_fl = False;
               retc = first_child->GetIndentPtr(&indent_ptr);
               KP_NEWO(new_node, XmlNode((KpChar)XC_TranslGroup, NULL, NULL, NULL, indent_ptr, XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));

               cur_node = first_child;
               while((TvKpStrChr(uiazXmlGrTags, child_tag) == NULL) && (cur_node != NULL) && SUCCEEDED(retc))
               {
// collect all nongroup tags to new_node
                  if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

                  if(SUCCEEDED(retc)) retc=cur_node->SetPrevBrother(NULL);
                  if(SUCCEEDED(retc)) retc=cur_node->SetNextBrother(NULL);

                  if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&child_tag);

// store example & co tags for further insertion of empty tag
                  if(SUCCEEDED(retc)) switch(child_tag)
                  {
                     case XC_Example: example_fl=True; break;
                     case XC_Usage: usage_fl=True; break;
                     case XC_Idiom: idiom_fl=True; break;
                     case XC_CompoundWord: compound_fl=True; break;
                     case XC_Struct: struct_fl=True; break;
                     case XC_OblStruct: obl_struct_fl=True; break;
                     case XC_Derivative: deriv_fl=True; break;
                     case XC_SrcWord: src_word_fl=True; break;
                  }

                  if((TvKpStrChr(uiazXmlHwTags, child_tag)!=NULL) && SUCCEEDED(retc))
                     retc=cur_node->SetNodeTag((KpChar)XC_TrWord);

                  if(SUCCEEDED(retc)) retc=new_node->AppendChild(cur_node);

                  cur_node=next_brother;
                  if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&child_tag);
               }
// first group tag or end of children reached

// delete all processed tags
               if(SUCCEEDED(retc)) retc=loop_brother->SetFirstChild(cur_node);

// insert created XC_TranslGroup to pCurEntry
               if(SUCCEEDED(retc))
               {
                  retc = loop_brother->InsertChild(new_node);
                  if(FAILED(retc)) KP_DELETE(new_node);
               }

// insert stored empty tags
               if(example_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_Example, NULL, NULL);
               if(usage_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_Usage, NULL, NULL);
               if(idiom_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_Idiom, NULL, NULL);
               if(compound_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_CompoundWord, NULL, NULL);
               if(struct_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_Struct, NULL, NULL);
               if(obl_struct_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_OblStruct, NULL, NULL);
               if(deriv_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_Derivative, NULL, NULL);
               if(src_word_fl && SUCCEEDED(retc)) retc=loop_brother->InsertTextTag((KpChar)XC_SrcWord, NULL, NULL);

            } // if((TvKpStrChr(uiazXmlGrTags, child_tag)==NULL) && SUCCEEDED(retc))

         } // if((cur_node!=NULL) && SUCCEEDED(retc))

      } // if(IsHwGroupTag(node_tag) && SUCCEEDED(retc))

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->Hw2Tw();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->Hw2Tw();

return(retc);
}


// --------------------------------------------------
KpChar null_hw[] = {C_Nul};

HRESULT XmlNode::GetHw(KpChar **plpiazHwPtrPtr) // const
{
HRESULT retc = S_OK;
KpChar child_tag;
KpChar cur_tag;
XmlNode *child_child = NULL;
XmlNode *next_brother = NULL;
/* const */ XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;

   if(plpiazHwPtrPtr == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother = this;
   while((loop_brother!=NULL) && (*plpiazHwPtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc = loop_brother->GetNodeTag(&cur_tag);
      if(
         (
//          (cur_tag==XC_Base) ||
//          (cur_tag==XC_HBase) ||
            ((cur_tag==XC_HeadWord) /* && (*plpiazHwPtrPtr==NULL) */)
         ) &&
         SUCCEEDED(retc)
        )
      {
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if(SUCCEEDED(retc))
         {
            if(first_child==NULL)
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
               *plpiazHwPtrPtr=(KpChar *)null_hw;
            }
            else
            {
               if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&child_tag);

//             if(SUCCEEDED(retc)) retc = first_child->GetFirstChild((KpTreeEntry **)&child_child);
               if(SUCCEEDED(retc)) child_child = (XmlNode *)first_child->m_pFirstChild;

               if(SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&next_brother);
               if(SUCCEEDED(retc)) retc=first_child->GetContentsPtr(plpiazHwPtrPtr);
               if(
                  (
//                   (child_tag!=XL_Text) ||
//                   (child_child!=NULL) ||
//                   (next_brother!=NULL) ||
                     (*plpiazHwPtrPtr==NULL)
                  ) &&
                  SUCCEEDED(retc)
                 )
               {
                  if(child_child==NULL)
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
                     *plpiazHwPtrPtr=(KpChar *)null_hw;
                  }
                  else
                  {
                     if(SUCCEEDED(retc)) retc=child_child->GetNodeTag(&child_tag);
                     if(SUCCEEDED(retc)) retc=child_child->GetNextBrother((KpTreeEntry **)&next_brother);
                     if(SUCCEEDED(retc)) retc=child_child->GetContentsPtr(plpiazHwPtrPtr);

//                   if(SUCCEEDED(retc)) retc = child_child->GetFirstChild((KpTreeEntry **)&child_child);
                     if(SUCCEEDED(retc)) child_child = (XmlNode *)child_child->m_pFirstChild;

                     if(
                        (
                           (child_tag!=XL_Text) ||
                           (child_child!=NULL) ||
//                         (next_brother!=NULL) ||
                           (*plpiazHwPtrPtr==NULL)
                        ) &&
                        SUCCEEDED(retc)
                       )
                     {
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
                        *plpiazHwPtrPtr=(KpChar *)null_hw;
                     }
                  }
               }
            }
         }
      }

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->GetHw(plpiazHwPtrPtr);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->GetHw(plpiazHwPtrPtr);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::GetBase(KpChar **plpiazBasePtrPtr) // const
{
HRESULT retc=S_OK;
KpChar child_tag;
KpChar cur_tag;
XmlNode *child_child;
XmlNode *next_brother;
/* const */ XmlNode *loop_brother;
XmlNode *first_child;

   if(plpiazBasePtrPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc = loop_brother->GetNodeTag(&cur_tag);
      if(
         (
            (cur_tag==XC_Base) ||
            (cur_tag==XC_HBase) ||
            ((cur_tag==XC_HeadWord) && (*plpiazBasePtrPtr==NULL))
         ) &&
         SUCCEEDED(retc)
        )
      {
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&child_tag);

//       if(SUCCEEDED(retc)) retc = first_child->GetFirstChild((KpTreeEntry **)&child_child);
         if(SUCCEEDED(retc)) child_child = (XmlNode *)first_child->m_pFirstChild;

         if(SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc=first_child->GetContentsPtr(plpiazBasePtrPtr);
         if(
            (
               (child_tag!=XL_Text) ||
               (child_child!=NULL) ||
//             (next_brother!=NULL) ||
               (*plpiazBasePtrPtr==NULL)
            ) &&
            SUCCEEDED(retc)
           )
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->GetBase(plpiazBasePtrPtr);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->GetBase(plpiazBasePtrPtr);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::TestText(const KpChar *lpiazTestText, bool *pbTextPresent)
{
HRESULT retc = S_OK;
KpChar *new_cont = NULL;
XmlNode *loop_brother = NULL;
XmlNode *next_brother = NULL;
XmlNode *first_child = NULL;
KpChar cur_tag;
KpChar *contents_ptr = NULL;

   if((lpiazTestText==NULL) && (pbTextPresent==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && (!(*pbTextPresent)) && SUCCEEDED(retc))
   {
      if(TvKpStrLen(lpiazTestText)!=0)
      {
         retc=loop_brother->GetNodeTag(&cur_tag);
         if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&contents_ptr);
         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);

//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if(SUCCEEDED(retc))
         {
            if(cur_tag==XL_Text)
            {
               if(
                  (contents_ptr==NULL) ||
//                (next_brother!=NULL) ||
                  (first_child!=NULL)
                 )
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
                  if(TvKpStrStr(contents_ptr, lpiazTestText)!=NULL)
                     *pbTextPresent=True;
            }
         }
      }

// continue recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->TestText(lpiazTestText, pbTextPresent);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
   }

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->TestText(lpiazTestText, pbTextPresent);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::TestQuery(KpChar iSearchTag, unsigned char *lpszMinValue, unsigned char *lpszMaxValue, bool *pbFoundFl)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *first_child = NULL;
KpChar *contents_ptr = NULL;
KpChar cur_tag;
bool found_fl;
unsigned char *str_buf = NULL;
KpChar *val_buf = NULL;
int ll;

   if((
//     (iSearchTag < m_iFirstTag) || CheckLastTag(iSearchTag) ||
       (pbFoundFl==NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && (!(*pbFoundFl)) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if((cur_tag==iSearchTag) && SUCCEEDED(retc))
      {
         found_fl=True;
//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child!=NULL) && SUCCEEDED(retc))
         {
            retc=first_child->GetNodeTag(&cur_tag);
            if(SUCCEEDED(retc))
            {
               if(cur_tag!=XL_Text)
               {
                  if(lpszMinValue!=NULL)
                     if(strlen(lpszMinValue)>0)
                        found_fl=False;
                  if(lpszMaxValue!=NULL)
                     if(strlen(lpszMaxValue)>0)
                        found_fl=False;
               }
               else
               {
                  if(SUCCEEDED(retc)) retc=first_child->GetContentsPtr(&contents_ptr);
                  if((contents_ptr==NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

                  str_buf=NULL;
                  val_buf=NULL;

                  if(SUCCEEDED(retc))
                  {
                     ll = TvKpStrLen(contents_ptr);
                     KP_NEWA(str_buf, unsigned char, ll + 1);
                  }

                  KP_NEWA(val_buf, KpChar, ll+1);

                  if(SUCCEEDED(retc))
                  {
                     TvKpStrCpy(val_buf, contents_ptr);
                     TvKpStrLat(val_buf);
                     retc=KptStrDecode(str_buf, val_buf, 1);
                  }

                  if((lpszMinValue!=NULL) && SUCCEEDED(retc))
                  {
                     if(strlen(lpszMinValue)>0)
                        if(strcmp(str_buf, lpszMinValue)<0) found_fl=False;
                  }

                  if((lpszMaxValue!=NULL) && SUCCEEDED(retc))
                  {
                     if(strlen(lpszMaxValue)>0)
                        if(strcmp(str_buf, lpszMaxValue)>0) found_fl=False;
                  }

                  KP_DELETEA(val_buf);
                  KP_DELETEA(str_buf);

               } // else // if(cur_tag!=XL_Text)

            } // if(SUCCEEDED(retc))

         } // if((first_child!=NULL) && SUCCEEDED(retc))

         if(found_fl && SUCCEEDED(retc)) *pbFoundFl=True;

      } // if((cur_tag==iSearchTag) && SUCCEEDED(retc))

      if(!(*pbFoundFl))
      {
// continue recursion on children
//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->TestQuery(iSearchTag, lpszMinValue, lpszMaxValue, pbFoundFl);

         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
      }
   }

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->TestQuery(iSearchTag, lpszMinValue, lpszMaxValue, pbFoundFl);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::SearchChildSubNode(KpChar iSearchTag, XmlNode **ppSubNode)
{
HRESULT retc = S_OK;
XmlNode *first_child = (XmlNode *)m_pFirstChild;

   if(first_child != NULL) retc = first_child->SearchSubNode(iSearchTag, ppSubNode);

return(retc);
}


HRESULT XmlNode::SearchSubNode(KpChar iSearchTag, XmlNode **ppSubNode)
{
HRESULT retc = S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
KpChar cur_tag;

   if((
//     (iSearchTag < m_iFirstTag) || CheckLastTag(iSearchTag) ||
       (ppSubNode==NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   loop_brother = this; // (XmlNode *)m_pFirstChild; // = this;

// loop on brothers
   while((loop_brother!=NULL) && (*ppSubNode==NULL) && SUCCEEDED(retc))
   {
      retc = loop_brother->GetNodeTag(&cur_tag);
      if((cur_tag==iSearchTag) && SUCCEEDED(retc))
         *ppSubNode=loop_brother;

      if(*ppSubNode==NULL)
      {
// continue recursion on children
//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->SearchSubNode(iSearchTag, ppSubNode);

         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
      }
   }

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->SearchSubNode(iSearchTag, ppSubNode);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::DeleteUnmatchedSubNodes(KpChar iSearchTag, unsigned char *lpszMinValue, unsigned char *lpszMaxValue)
{
HRESULT retc=S_OK;
XmlNode *hg_node;
XmlNode *loop_brother;
XmlNode *next_brother;
XmlNode *prev_brother;
bool found_fl;
KpChar cur_tag;

// if(((iSearchTag < m_iFirstTag) || CheckLastTag(iSearchTag)) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// go to <hg> node
// hg_node=NULL;
// retc=SearchSubNode(XC_HeadWordGroup, &hg_node);
   hg_node=this;

   if((hg_node!=NULL) && SUCCEEDED(retc))
   {
//    retc = hg_node->GetFirstChild((KpTreeEntry **)&loop_brother);
      loop_brother = (XmlNode *)hg_node->m_pFirstChild;

// loop on brothers
      while((loop_brother!=NULL) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);

         if(SUCCEEDED(retc))
         {
            if(
               (TvKpStrChr(uiazXmlGrTags, cur_tag)!=NULL) &&
               (cur_tag!=XC_TranslGroup)
              )
            {
// TestQuery() tests all brothers - cut rest brothers
               if(SUCCEEDED(retc)) retc=loop_brother->SetNextBrother(NULL);

               if(SUCCEEDED(retc))
               {
                  found_fl=False;
                  retc=loop_brother->TestQuery(iSearchTag, lpszMinValue, lpszMaxValue, &found_fl);
               }

// restore cut rest brothers
               if(SUCCEEDED(retc)) retc=loop_brother->SetNextBrother(next_brother);

               if(SUCCEEDED(retc))
               {
                  if(!found_fl)
                  {
                     retc=loop_brother->GetPrevBrother((KpTreeEntry **)&prev_brother);
                     if(SUCCEEDED(retc))
                     {
                        if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                        else retc=hg_node->ConnectChild(next_brother);
                     }

                     if(SUCCEEDED(retc)) retc=loop_brother->SetNextBrother(NULL);
                     if(SUCCEEDED(retc)) retc=loop_brother->SetPrevBrother(NULL);
                     KP_DELETE(loop_brother);

                  } // if(!found_fl)
                  else
                  {
                     prev_brother=loop_brother;

// continue recursion on children
                     if(SUCCEEDED(retc)) retc=loop_brother->DeleteUnmatchedSubNodes(iSearchTag, lpszMinValue, lpszMaxValue);
                  }

               } // if(SUCCEEDED(retc))

            } // if((TvKpStrChr(uiazXmlGrTags, iTag)!=NULL) ...
            else
            {
               prev_brother=loop_brother;

// continue recursion on children
//             if(SUCCEEDED(retc)) retc=loop_brother->DeleteUnmatchedSubNodes(iSearchTag, lpszMinValue, lpszMaxValue);
            }

         } // if(SUCCEEDED(retc))

         loop_brother=next_brother;
      }
   }

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DeleteUnmatchedSubNodes(iSearchTag, lpszMinValue, lpszMaxValue);

return(retc);
}


// --------------------------------------------------
const KpChar iazNull[]={C_Nul};
HRESULT XmlNode::SubstText(const KpChar *lpiazFromText, const KpChar *lpiazToText, bool bOnlyHw)
{
HRESULT retc = S_OK;
const KpChar *to_text_ptr = NULL;
const KpChar *base_end = NULL;
KpChar *pnti = NULL;
KpChar *new_cont = NULL;
KpChar *out_ptr = NULL;
XmlNode *loop_brother = NULL;
XmlNode *next_brother = NULL;
XmlNode *first_child = NULL;
KpChar cur_tag;
KpChar *contents_ptr = NULL;
static const KpChar comp_delim[]={(KpChar)TV_XM_CompDelim, C_Nul}; // '|'
int from_text_len;

   if(lpiazFromText==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) from_text_len=TvKpStrLen(lpiazFromText);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(
         (
            (cur_tag==XC_StEntry) ||
            (cur_tag==XC_HeadWordGroup) ||
            (cur_tag==XC_HeadWord) ||
            (cur_tag==XL_Text) ||
            (!bOnlyHw)
         ) &&
         SUCCEEDED(retc)
        )
      {
         to_text_ptr=lpiazToText;
         if(to_text_ptr==NULL) to_text_ptr=iazNull;

//       if(to_text_ptr!=NULL)
         {
//          while((TvStrChr(lpszSpaces, *to_text_ptr)!=NULL) && (*to_text_ptr!=C_Nul)) to_text_ptr++;
//          if(TvKpStrLen(to_text_ptr)!=0)
            {
               if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&contents_ptr);
               if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);

//             if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
               if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

               if(SUCCEEDED(retc))
               {
                  if(cur_tag==XL_Text)
                  {
                     if(
                           (contents_ptr==NULL) ||
//                         (next_brother!=NULL) ||
                           (first_child!=NULL)
                       )
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc)) do
                     {
                        retc=loop_brother->GetContentsPtr(&contents_ptr);

                        pnti=NULL;

                        if((contents_ptr!=NULL) && SUCCEEDED(retc))
                        {
                           pnti=(KpChar *)TvKpStrStr(contents_ptr, lpiazFromText);
                           if(pnti!=NULL)
                           {
                              *pnti = C_Nul;

                              KP_NEWA(new_cont, KpChar,
                                             TvKpStrLen(contents_ptr) +
                                             TvKpStrLen(to_text_ptr) +
                                             TvKpStrLen(pnti+from_text_len) +
                                             1 + 1);

                              if(SUCCEEDED(retc))
                              {
                                 TvKpStrCpy(new_cont, contents_ptr);

                                 out_ptr = new_cont + TvKpStrLen(contents_ptr);
                                 base_end=TvKpStrChr(to_text_ptr, (KpChar)TV_XM_CompDelim); // '|'
                                 if(base_end == NULL) base_end=TvKpStrChr(to_text_ptr, DOUBLE_ENTRIES_KPCHAR); // C_Bpoint
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
KptStrDecode(str_buf, to_text_ptr, 71);
KP_TRACE(str_buf);
#endif
                                 if(base_end!=NULL)
                                 {
                                    TvKpStrNCpy(out_ptr, to_text_ptr, base_end-to_text_ptr);
                                    out_ptr[base_end-to_text_ptr]=C_Nul;
                                 }
                                 else TvKpStrCat(new_cont, to_text_ptr);

                                 if(bOnlyHw) TvKpStrCat(new_cont, comp_delim);

                                 TvKpStrCat(new_cont, pnti+from_text_len);

                                 retc=loop_brother->SetContents(new_cont);
                              }

                              KP_DELETEA(new_cont);
                           }
                        }

                     } while((pnti!=NULL) && SUCCEEDED(retc));

                  } // if(cur_tag==XL_Text)
                  else
                     if(contents_ptr != NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
               }

            } // if(TvKpStrLen(pnti)!=0)

         } // if(to_text_ptr!=NULL)

// continue recursion on children
//       if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

         if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->SubstText(lpiazFromText, to_text_ptr, bOnlyHw);
      }

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// continue recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->SubstText(lpiazFromText, lpiazToText, bOnlyHw);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::SubstBase(const KpChar *lpiazBasePtr, bool bOnlyHw)
{
HRESULT retc=S_OK;
static const KpChar base_char[]={(KpChar)TV_XM_CompBaseChar, C_Nul}; // '~'
static const KpChar base_char_null_sp[]={(KpChar)TV_XM_CompBaseChar, (KpChar)NS_CTRL_START, C_Point, C_Nul}; // "~$." // '~' '$' '.'

   if(SUCCEEDED(retc)) retc=SubstText(base_char_null_sp, lpiazBasePtr, bOnlyHw);
   if(SUCCEEDED(retc)) retc=SubstText(base_char, lpiazBasePtr, bOnlyHw);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::DelCompDelim(void)
{
HRESULT retc=S_OK;
static const KpChar base_char[]={(KpChar)TV_XM_CompBaseChar, C_Nul}; // '~'
static const KpChar comp_delim[]={(KpChar)TV_XM_CompDelim, C_Nul}; // '|'
static const KpChar null_char[]={C_Nul};
bool ch_pres_fl;

   ch_pres_fl=False;
   retc=TestText(base_char, &ch_pres_fl);

   if((!ch_pres_fl) && SUCCEEDED(retc))
      retc=SubstText(comp_delim, null_char, False /* True */);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::EncloseCtg(int iCtgNum)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;
XmlNode *new_node=NULL;
XmlNode *first_child=NULL;
XmlNode *prev_brother=NULL;
XmlTagPars *tag_pars=NULL;
KpChar cur_tag;
unsigned char ctg_num_str[20];
unsigned char *cur_indent=NULL;

   if((m_iNodeTag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// first <hg> ---> cur_node
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(cur_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }
   if(SUCCEEDED(retc)) retc=cur_node->GetIndentPtr(&cur_indent);

// <hg> contents --> first_child
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag==XC_HeadWord) && SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&first_child);
   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// create parameter num="iCtgNum"
   if(SUCCEEDED(retc)) retc = FormatRoman(ctg_num_str, iCtgNum);
   KP_NEWO(tag_pars, XmlTagPars((const unsigned char *)"num", ctg_num_str, NULL));

// new <s1> --> new_node
   KP_NEWO(new_node, XmlNode((KpChar)XC_CtgGroup, tag_pars, NULL, NULL, cur_indent, XC_FirstDictTag, plpszaXmlttDictTagsFull, cur_node));

// enclose contents to <s1>
   if(SUCCEEDED(retc)) retc=first_child->GetPrevBrother((KpTreeEntry **)&prev_brother);
   if(SUCCEEDED(retc))
   {
      if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(new_node);
      else retc=cur_node->ConnectChild(new_node);
   }
   if(SUCCEEDED(retc)) retc = new_node->ConnectChild(first_child);

   if(SUCCEEDED(retc)) retc = new_node->IncreaseIndent();

   KP_DELETE(tag_pars);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::EncloseMng(int iMngNum)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;
XmlNode *new_node=NULL;
XmlNode *first_child=NULL;
XmlNode *prev_brother=NULL;
XmlTagPars *tag_pars=NULL;
KpChar cur_tag;
unsigned char *cur_indent=NULL;

   if((m_iNodeTag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// first <hg> ---> cur_node
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(cur_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }
   if(SUCCEEDED(retc)) retc=cur_node->GetIndentPtr(&cur_indent);

// <hg> contents --> first_child
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag==XC_HeadWord) && SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&first_child);
   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag==XC_PartOfSpeechSrc) && SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&first_child);
   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// create parameter num="iMngNum"
   KP_NEWO(tag_pars, XmlTagPars((const unsigned char *)"num", iMngNum, NULL));

// new <s2> --> new_node
   KP_NEWO(new_node, XmlNode((KpChar)XC_MngGroup, tag_pars, NULL, NULL, cur_indent, XC_FirstDictTag, plpszaXmlttDictTagsFull, cur_node));

// enclose contents to <s2>
   if(SUCCEEDED(retc)) retc=first_child->GetPrevBrother((KpTreeEntry **)&prev_brother);
   if(SUCCEEDED(retc))
   {
      if(prev_brother != NULL) retc = prev_brother->ConnectBrother(new_node);
      else retc = cur_node->ConnectChild(new_node);
   }
   if(SUCCEEDED(retc)) retc = new_node->ConnectChild(first_child);

   if(SUCCEEDED(retc)) retc = new_node->IncreaseIndent();

   KP_DELETE(tag_pars);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::EncloseLastCtgToMng(int iMngNum)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;
XmlNode *new_node=NULL;
XmlNode *first_child=NULL;
XmlNode *cur_child=NULL;
XmlNode *last_ctg_node=NULL;
XmlNode *prev_brother=NULL;
XmlTagPars *tag_pars=NULL;
KpChar cur_tag;
unsigned char *cur_indent=NULL;

   if((m_iNodeTag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// first <hg> ---> cur_node
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(cur_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }
   if(SUCCEEDED(retc)) retc=cur_node->GetIndentPtr(&cur_indent);

// <hg> contents --> first_child
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag==XC_HeadWord) && SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&first_child);
   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
   if((cur_tag==XC_PartOfSpeechSrc) && SUCCEEDED(retc)) retc=first_child->GetNextBrother((KpTreeEntry **)&first_child);
   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// find last <s1> if present
   cur_child=first_child;
   last_ctg_node=NULL;
   while((cur_child!=NULL) && SUCCEEDED(retc))
   {
      if((cur_child!=NULL))
      {
         retc=cur_child->GetNodeTag(&cur_tag);
         if((cur_tag==XC_CtgGroup) && SUCCEEDED(retc)) last_ctg_node=cur_child;
      }
      if(SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&cur_child);
   }
   if(SUCCEEDED(retc))
   {
// first node to enclose --> cur_child
      if(last_ctg_node!=NULL)
      {
//       retc = last_ctg_node->GetFirstChild((KpTreeEntry **)&cur_child);
         cur_child = (XmlNode *)last_ctg_node->m_pFirstChild;

         if(SUCCEEDED(retc)) retc=last_ctg_node->GetIndentPtr(&cur_indent);
         if((cur_child==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);
         if((cur_tag==XC_PartOfSpeechSrc) && SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&cur_child);
      }
      else cur_child=first_child;
   }
   if((cur_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
// call to EncloseLastCtgToMng() only for active categories
   if(last_ctg_node==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// create parameter num="iMngNum"
   KP_NEWO(tag_pars, XmlTagPars((const unsigned char *)"num", iMngNum, NULL));

// new <s2> --> new_node
   KP_NEWO(new_node, XmlNode((KpChar)XC_MngGroup, tag_pars, NULL, NULL, cur_indent, XC_FirstDictTag, plpszaXmlttDictTagsFull, NULL));

// enclose contents to <s2>
   if(SUCCEEDED(retc)) retc = new_node->ConnectChild(cur_child);
   if(SUCCEEDED(retc))
   {
      prev_brother=NULL;
      if((cur_child!=NULL) && SUCCEEDED(retc)) retc=cur_child->GetPrevBrother((KpTreeEntry **)&prev_brother);
      if(SUCCEEDED(retc))
      {
         if((prev_brother==NULL) && SUCCEEDED(retc))
         {
// insert new <s2> to last <s1>
            if(last_ctg_node != NULL) retc = last_ctg_node->ConnectChild(new_node);
// insert new <s2> to <hg>
            else retc = cur_node->ConnectChild(new_node);
         }
         else
         {
            retc = prev_brother->ConnectBrother(new_node);
            if((cur_child!=NULL) && SUCCEEDED(retc)) retc=cur_child->SetPrevBrother(NULL);
         }
      }
   }

   if(SUCCEEDED(retc)) retc = new_node->IncreaseIndent();

   KP_DELETE(tag_pars);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::AppendCtg(XmlNode *pSubEntry)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;
XmlNode *src_node=NULL;
XmlNode *first_child=NULL;
KpChar cur_tag;

   if((m_iNodeTag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if((pSubEntry==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// first <hg> ---> cur_node
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(cur_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }

// <hg> contents --> first_child, test it
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
// if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
// if((cur_tag!=XC_CtgGroup) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// source <s1> --> src_node
   src_node=pSubEntry;
   if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
   if((cur_tag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) retc = src_node->GetFirstChild((KpTreeEntry **)&src_node);
   if(SUCCEEDED(retc)) src_node = (XmlNode *)src_node->m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(src_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=src_node->GetNextBrother((KpTreeEntry **)&src_node);
   }

// if(SUCCEEDED(retc)) retc = src_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)src_node->m_pFirstChild;

   if(SUCCEEDED(retc)) retc = src_node->SetFirstChild(NULL);
   KP_DELETE(pSubEntry);
   src_node = first_child;

   while(SUCCEEDED(retc))
   {
      if(src_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_CtgGroup) && SUCCEEDED(retc)) break;
      if(SUCCEEDED(retc)) retc=src_node->GetNextBrother((KpTreeEntry **)&src_node);
   }

// append source <s1> into this <hg>
   if(SUCCEEDED(retc)) retc=src_node->SetPrevBrother(NULL);
   if(SUCCEEDED(retc)) retc=cur_node->AppendChild(src_node);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::AppendMng(XmlNode *pSubEntry)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;
XmlNode *src_node=NULL;
XmlNode *first_child=NULL;
XmlNode *cur_child=NULL;
XmlNode *last_ctg_node=NULL;
KpChar cur_tag;

   if((m_iNodeTag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if((pSubEntry==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// first <hg> ---> cur_node
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(cur_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);
   }

// <hg> contents --> first_child
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// find last <s1> if present
   cur_child=first_child;
   last_ctg_node=NULL;
   while((cur_child!=NULL) && SUCCEEDED(retc))
   {
      if((cur_child!=NULL))
      {
         retc=cur_child->GetNodeTag(&cur_tag);
         if((cur_tag==XC_CtgGroup) && SUCCEEDED(retc)) last_ctg_node=cur_child;
      }
      if(SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&cur_child);
   }

// dest node --> cur_node
   if((last_ctg_node!=NULL) && SUCCEEDED(retc)) cur_node=last_ctg_node;
   if((cur_node==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// dest node contents --> first_child, test it
// if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

   if((first_child==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
// if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&cur_tag);
// if((cur_tag!=XC_MngGroup) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// source <s2> --> src_node
   src_node=pSubEntry;
   if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
   if((cur_tag!=XC_StEntry) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) retc = src_node->GetFirstChild((KpTreeEntry **)&src_node);
   if(SUCCEEDED(retc)) src_node = (XmlNode *)src_node->m_pFirstChild;

   while(SUCCEEDED(retc))
   {
      if(src_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc)) break;

      if(SUCCEEDED(retc)) retc=src_node->GetNextBrother((KpTreeEntry **)&src_node);
   }

// if(SUCCEEDED(retc)) retc = src_node->GetFirstChild((KpTreeEntry **)&first_child);
   if(SUCCEEDED(retc)) first_child = (XmlNode *)src_node->m_pFirstChild;

   if(SUCCEEDED(retc)) retc = src_node->SetFirstChild(NULL);
   KP_DELETE(pSubEntry);
   src_node = first_child;

   while(SUCCEEDED(retc))
   {
      if(src_node==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=src_node->GetNodeTag(&cur_tag);
      if((cur_tag==XC_MngGroup) && SUCCEEDED(retc)) break;
      if(SUCCEEDED(retc)) retc=src_node->GetNextBrother((KpTreeEntry **)&src_node);
   }

// append source <s2> into dest node (this <hg> or last <s1>)
   if(SUCCEEDED(retc)) retc=src_node->SetPrevBrother(NULL);
   if(SUCCEEDED(retc)) retc=cur_node->AppendChild(src_node);

   if((last_ctg_node!=NULL) && SUCCEEDED(retc)) retc=src_node->IncreaseIndent();

return(retc);
}


//-----------------------------------
// derint su GenTexDelimStr()
// derint su GenXmlDelimStr
HRESULT XmlNode::SkipDelimCtrlChars(unsigned char **ppcDelimPtr)
{
HRESULT retc=S_OK;
int ii;

   if((ppcDelimPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(*ppcDelimPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(**ppcDelimPtr==NS_CTRL_START)   // '$'
      {
         (*ppcDelimPtr)++;
         switch(*((*ppcDelimPtr)++))
         {
// font style
         case 'f':
            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(**ppcDelimPtr)); ii++) (*ppcDelimPtr)++;
            break;

// paragraph style
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(**ppcDelimPtr)); ii++) (*ppcDelimPtr)++;
            break;

         case 'u':
            for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((KpChar)(**ppcDelimPtr))); ii++) (*ppcDelimPtr)++;
            break;

// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(**ppcDelimPtr)); ii++) (*ppcDelimPtr)++;
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            break;
         }
      }
   }

return(retc);
}


//-----------------------------------
// iazOutBuf[KP_MAX_FILE_LIN_LEN+1]
// lpszFormatStr - formato eilute is lpszXmlTagDelimiters[][]
// derint su SkipDelimCtrlChars()
// derint su GenTexDelimStr()
HRESULT XmlNode::GenXmlDelimStr(KpChar *iazOutBuf, const unsigned char *lpszFormatStr, XmlVersions iXmlVers)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
KpChar *pntd;
bool font_changed=False;
unsigned int uni_code;
int ii;
KpChar i_char;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];

   if((lpszFormatStr==NULL) || (iazOutBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszFormatStr)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pntd=iazOutBuf;
   pnts=lpszFormatStr;

   while((*pnts) && SUCCEEDED(retc))
   {
      if(*pnts==NS_CTRL_START)   // '$'
      {
         pnts++;
         switch(*pnts++)
         {
// font style - skip
         case 'f':
            if(XM_IS_VERS_HTML(iXmlVers))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_STY_NO_WDT]=Nul;

               ii = 0;
               if(sscanf((const char *)sty_buf, "%d", &ii) != 1)
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
               if(((ii<0) || (ii >= KPS_NumOfFontStyles00)) && SUCCEEDED(retc))
               {
#if FALSE // #if TRUE
ii = 0;
KpMsgOut(lpszFormatStr, IDI_ASTERISK, KP_MB_TESTI);
#else
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
#endif
               }
               if(SUCCEEDED(retc))
               {
                  ii = aFontStyles[ii].GetFontFlags();
                  if(ii & KPS_BoldFl) *pntd++ = HTM_TG_B;
                  if(ii & KPS_ItalicFl) *pntd++ = HTM_TG_I;
               }
            }

            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

// paragraph style - skip
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

// unicode character
         case 'u':
            if((((pntd-iazOutBuf)+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_UNI_CODE_WDT]=Nul;
               uni_code=(unsigned int)(-1);
               sscanf((char *)sty_buf, "%x", &uni_code);

               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((KpChar)(*pnts))); ii++) pnts++;

               if((uni_code>=KPT_UniPrivateStart) && (uni_code<=KPT_UniPrivateEnd))
                  i_char=(KpChar)(uni_code-KPT_UniPrivateStart);
               else
               {
                  for(i_char=C_Nul; i_char<C_CharSize0; i_char=(KpChar)(i_char+1))
                     if(iaUniChars[i_char]==uni_code) break;
               }

               if(((i_char<0) || (i_char>=C_CharSize0)) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) *(pntd++)=i_char;
            break;

// condensed font - skip
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            break;
         }
      }
      else
      {
         if((((pntd-iazOutBuf)+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            retc=KptCharEncode((KpChar *)pntd++, *pnts++, iDelimCtbl /* NS_DELIM_CTBL */ /* code_table */);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         }
      }
   }

   if(SUCCEEDED(retc)) *pntd=C_Nul;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::ExpParDelimStr(unsigned char *lpszOutBuf, const unsigned char *lpszInFormDelimStr, KpChar iCurTag, XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;
unsigned char *val_buf = NULL;
unsigned char *val_buf_buf = NULL;
long tag_val;
int par_num;
int ii;

// if(((iCurTag < m_iFirstTag) || CheckLastTag(iCurTag)) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc)) switch(iCurTag)
   {
   case XC_CtgGroup:
      if(pTagPars==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=pTagPars->SeekTextPar("num", val_buf, &par_num);
      if(bS1toS2 && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=ScanRoman(val_buf, &ii);
         if(SUCCEEDED(retc)) sprintf((char *)val_buf, "%d", ii);
      }
      if(((strlen(lpszInFormDelimStr)+strlen(val_buf))>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) sprintf((char *)lpszOutBuf, (const char *)lpszInFormDelimStr, val_buf);
      break;
   case XC_MngNearGroup:
      if(pTagPars==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=pTagPars->SeekTextPar("num", val_buf, &par_num);
      if(((strlen(lpszInFormDelimStr)+strlen(val_buf))>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) sprintf((char *)lpszOutBuf, (const char *)lpszInFormDelimStr, val_buf);
      break;
   case XC_MngGroup:
   case XC_CpdMngGroup:
   case XC_IdMngGroup:
      if(pTagPars==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=pTagPars->SeekNumPar("num", &tag_val, &par_num);
      if(((strlen(lpszInFormDelimStr)+MAX_LONG_DIGITS)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) sprintf((char *)lpszOutBuf, (const char *)lpszInFormDelimStr, tag_val);
      break;
   case XC_Enum:
      val_buf=(unsigned char *)"";
      if(pTagPars != NULL)
      {
         retc = pTagPars->SeekTextPar("num", val_buf, &par_num);
         if(retc == KP_E_KWD_NOT_FOUND)
         {
            retc = S_OK;
            val_buf = (unsigned char *)"";
         }
      }
      KP_NEWA(val_buf_buf, unsigned char, strlen(val_buf) + 2);
  	   if(SUCCEEDED(retc)) strcpy(val_buf_buf, val_buf);

      if(SUCCEEDED(retc)) if(strlen(val_buf_buf)>0) strcat(val_buf_buf, " ");
      if(((strlen(lpszInFormDelimStr)+strlen(val_buf_buf))>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) sprintf((char *)lpszOutBuf, (const char *)lpszInFormDelimStr, val_buf_buf);
      KP_DELETEA(val_buf_buf);
      break;
   default:
      if((strlen(lpszInFormDelimStr)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) strcpy(lpszOutBuf, lpszInFormDelimStr);
      break;
   }

   KP_DELETEA(val_buf);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::CheckLevel(int iLevel, bool *pbDelFl)
{
HRESULT retc = S_OK;
XmlNode *cur_node = NULL;
XmlNode *contents_node = NULL;
KpChar cur_tag;
KpChar *contents = NULL;
unsigned char cont_txt[TV_TAG_LEN+1];
int ll;
bool level_present;
bool level_corresponds;
bool garbage_level;
int level;

   if(pbDelFl==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_node);
   if(SUCCEEDED(retc)) cur_node = (XmlNode *)m_pFirstChild;

   level_present=False;
   level_corresponds=False;
   garbage_level=False;

   if(SUCCEEDED(retc))
   {
      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);

         if((cur_tag==XC_Level) && SUCCEEDED(retc))
         {
            level_present=True;

//          retc = cur_node->GetFirstChild((KpTreeEntry **)&contents_node);
            contents_node = (XmlNode *)cur_node->m_pFirstChild;

            if(contents_node==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc=contents_node->GetNodeTag(&cur_tag);
            if((cur_tag!=XL_Text) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            contents=NULL;
            if(SUCCEEDED(retc)) retc = contents_node->GetContentsPtr(&contents);
            if((contents==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               ll=TvKpStrLen(contents);
               if(ll>TV_TAG_LEN)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) retc=KptStrDecode(cont_txt, contents, 1);
            if(SUCCEEDED(retc))
            {
               sscanf((const char *)cont_txt, "%d", &level);
               if(level==iLevel) level_corresponds=True;
               if(level>=LevelGarbage) garbage_level=True;
            }

         } // if((cur_tag==XC_Level) && SUCCEEDED(retc))

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&cur_node);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))


   if(SUCCEEDED(retc))
      *pbDelFl=(level_present && ((!level_corresponds) || garbage_level));

return(retc);
}


//-----------------------------------
HRESULT XmlNode::SupressToLevel(int iLevel)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
KpChar cur_tag;
bool del_fl;

// printf("==== %d %x\n", del_cnt++, this);
// retc=TestNode();

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if((cur_node!=NULL) && SUCCEEDED(retc))
            retc=cur_node->SupressToLevel(iLevel);

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);

         del_fl=False;
         if(SUCCEEDED(retc)) retc=cur_node->CheckLevel(iLevel, &del_fl);

         if(del_fl && SUCCEEDED(retc))
         {
// subnode does not correspond to level specified - delete
            if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
            KP_DELETE(cur_node);

            if(SUCCEEDED(retc))
            {
               if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
               else
               {
// first child deleted - update first child
                  retc = loop_brother->ConnectChild(next_brother);
               }
            }
         }

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->SupressToLevel(iLevel);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::ProcessLevel(int iLevel, bool bBeforePrint)
{
HRESULT retc=S_OK;

// ------------------------- process level
   if(SUCCEEDED(retc)) retc=SupressToLevel(iLevel);

   if(SUCCEEDED(retc)) retc=DelLevelTags(iLevel);

   if(bBeforePrint && SUCCEEDED(retc)) retc=DelTags((KpChar)XC_Level);
   if(bBeforePrint && SUCCEEDED(retc)) retc=UpLevelGroups();

   if(SUCCEEDED(retc)) retc=DelEmptyTags();

   if(SUCCEEDED(retc)) retc=UpCtgMng();
   if(SUCCEEDED(retc)) retc=RenumCtgMng();

// ------------------------- delete author remarks
   if(SUCCEEDED(retc)) retc=DelTags((KpChar)XC_TechNote);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::DelLevelTags(int iLevel)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
KpChar cur_tag;

// printf("==== %d %x\n", del_cnt++, this);
// retc=TestNode();

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if((cur_node!=NULL) && SUCCEEDED(retc))
            retc=cur_node->DelLevelTags(iLevel);

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
         if(SUCCEEDED(retc))
         {
//          if(!baLevelTags[(cur_tag - m_iFirstTag /* XC_FirstDictTag */)/2][iLevel])
            if(!TestTagLevel(cur_tag, iLevel))
            {
// tag matched - delete subnode
               if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);
               KP_DELETE(cur_node);

               if(SUCCEEDED(retc))
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(next_brother);
                  }
               }
            }
         }

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelLevelTags(iLevel);

return(retc);
}


// --------------------------------------------------
#if FALSE
HRESULT XmlNode::EncloseTextToTx(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
XmlNode *next_brother;
XmlNode *new_child;
KpChar cur_tag;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;

      // recursion through children of children first
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->EncloseTextToTx();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);
      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
      if(
         (cur_tag==XL_Text) &&
         ((next_brother!=NULL) || (loop_brother!=this)) &&
         SUCCEEDED(retc)
        )
      {
         KP_NEWO(new_child, XmlNode(XL_TextExpr, NULL, NULL, NULL, (const unsigned char *)"", loop_brother)); // !!! set indent eaqual to that of loop_brother
         if(FAILED(retc)) KP_DELETE(new_child);

         if(SUCCEEDED(retc)) retc=new_child->ConnectChild(first_child);
         if(SUCCEEDED(retc)) retc=loop_brother->SetFirstChild(new_child);
      }

      loop_brother=next_brother;

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->EncloseTextToTx();

return(retc);
}
#endif


// --------------------------------------------------
HRESULT XmlNode::CreateDelimNode(XmlNode **ppDelimNodePtr, KpChar iCurTag, KpChar iNextTag, XmlTagPars *pTagPars,
// KpChar iFirstTag, KpChar iLastTag,
XmlVersions iXmlVers)
{
HRESULT retc=S_OK;
XmlNode *delim_contents;
KpChar i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
static unsigned char delim_buf[MAX_XML_PAR_VAL_LEN + 1];
const unsigned char *delim_ptr;
static unsigned char val_buf[MAX_XML_PAR_VAL_LEN + 1];
long par_val;
int par_num;

   if(
      (
//       (iCurTag < m_iFirstTag /* iFirstTag */) || CheckLastTag(iCurTag) /* (iCurTag >= iLastTag) */ ||
//       (iNextTag < m_iFirstTag /* iFirstTag */) || CheckLastTag(iNextTag) /* (iNextTag >= iLastTag) */ ||
         (ppDelimNodePtr==NULL)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
//    delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(iCurTag - m_iFirstTag /* iFirstTag */)/2][(iNextTag - m_iFirstTag /* iFirstTag */)/2];
      delim_ptr = GetTagDelimiter(iCurTag, iNextTag);

//    if(delim_ptr==NULL) delim_ptr=(const unsigned char *)"";
      if(delim_ptr) if(strcmp(delim_ptr, "") == 0) delim_ptr = NULL;

      delim_buf[0] = Nul;
      if(delim_ptr)
      {
         if(pTagPars == NULL)
         {
//          retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L);
            strncpy(delim_buf, delim_ptr, KP_MAX_FILE_LIN_LEN);
         }
         else
         {
#if FALSE // #if TRUE //
static unsigned char nam_buf[KP_MAX_FILE_LIN_LEN+1];
stringstream str_stream;
if(SUCCEEDED(pTagPars->GetTextPar(nam_buf, val_buf, 0)))
{
str_stream << iNextTag << " " << nam_buf << " " << val_buf;
KpMsgOut(KpString(str_stream.str()), IDI_ASTERISK, KP_MB_TESTI);
}
#endif

// KpMsgOut(delim_ptr, IDI_ASTERISK, KP_MB_TESTI);

            switch(iNextTag)
            {
            case XC_MngGroup:
            case XC_CpdMngGroup:
            case XC_IdMngGroup:
               retc = pTagPars->SeekNumPar("num", &par_val, &par_num);
               if(SUCCEEDED(retc))
                  if(strlen(delim_ptr) + MAX_LONG_DIGITS >= KP_MAX_FILE_LIN_LEN)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  sprintf((char *)delim_buf, (const char *)delim_ptr, par_val);
               break;

            case XC_CtgGroup:
            case XC_MngNearGroup:
               retc = pTagPars->SeekTextPar("num", val_buf, &par_num);
               if(SUCCEEDED(retc))
                  if(strlen(delim_ptr) + strlen(val_buf) >= KP_MAX_FILE_LIN_LEN)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  sprintf((char *)delim_buf, (const char *)delim_ptr, val_buf);
               break;

            default:
               strncpy(delim_buf, delim_ptr, KP_MAX_FILE_LIN_LEN);
               break;

            } // switch(iNextTag)

         } // else // if(pTagPars == NULL)

      } // if(delim_ptr)

      delim_buf[KP_MAX_FILE_LIN_LEN] = Nul;

      if(delim_buf[0] /* delim_ptr */) retc=GenXmlDelimStr(i_delim_buf, delim_buf, iXmlVers);
//    if(strcmp(delim_ptr, " ")==0){ i_delim_buf[0]=C_NBSP; i_delim_buf[1]=C_Nul;} // reikia exploreriui, nerodo pavienio tarpo
   }

#if FALSE
// if((iCurTag == XC_TrWord) /* && (iNextTag == XC_Parenth) */)
{
stringstream str_stream;
str_stream << m_plpszaTags /* plpszaXmlttDictTags */[iCurTag - m_iFirstTag /* iFirstTag */] << " " << m_plpszaTags /* plpszaXmlttDictTags */[iNextTag - m_iFirstTag /* iFirstTag */]; // iCurTag; // iNextTag;
KpMsgOut(KpString(str_stream.str()), IDI_ASTERISK, KP_MB_TESTI);
}
#endif

#if FALSE // #if TRUE
if(delim_buf[0])
{
// KptStrDecode(delim_buf, i_delim_buf, 71);
KpChar *pnts = i_delim_buf;
unsigned char *pntd = delim_buf;
*pntd++ = '>'; *pntd++ = '>'; *pntd++ = '>';
while(*pnts)
{
if(*pnts >= C_Spc) KptCharDecode(pntd++, *pnts, 71);
else
{
sprintf((char *)pntd, "<%02x>", *pnts);
pntd += strlen(pntd);
}
pnts++;
}
*pntd++ = '<'; *pntd++ = '<'; *pntd++ = '<'; *pntd++ = Nul;
KpMsgOut(delim_buf, IDI_ASTERISK, KP_MB_TESTI); // delim_ptr
}
#endif

   if(SUCCEEDED(retc)) *ppDelimNodePtr = NULL;

   if(delim_buf[0] /* delim_ptr */ && SUCCEEDED(retc))
   {
      delim_contents = NULL;

// !!! set indent eaqual to that of cur_child
      KP_NEWO(*ppDelimNodePtr, XmlNode((KpChar)XC_PunctMark, NULL, NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, NULL));

// !!! set indent eaqual to that of cur_child
      KP_NEWO(delim_contents, XmlNode((KpChar)XL_Text, NULL, NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, *ppDelimNodePtr));
      if(SUCCEEDED(retc)) retc = delim_contents->SetContents((const KpChar *)i_delim_buf);

      if(SUCCEEDED(retc))
      {
         retc = (*ppDelimNodePtr)->ConnectChild(delim_contents);
         if(SUCCEEDED(retc)) delim_contents = NULL;
      }

      KP_DELETE(delim_contents);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::InsertDelimiters(/* KpChar iFirstTag, KpChar iLastTag, */ XmlVersions iXmlVers)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_child;
XmlNode *next_brother;
XmlNode *delim_child;
KpChar cur_tag;
KpChar next_tag;
XmlTagPars *tag_pars = NULL;

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

      if((cur_child!=NULL) && SUCCEEDED(retc))
      {
// -------------------------- delimiter before first child
         if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);
         if(SUCCEEDED(retc)) retc=cur_child->GetTagParsPtr(&tag_pars);

         delim_child=NULL;
         if(SUCCEEDED(retc))
         {
            retc=CreateDelimNode(&delim_child, (KpChar)XC_Nul, cur_tag, tag_pars, iXmlVers);
            if(FAILED(retc)) delim_child=NULL;
         }

         if(delim_child && SUCCEEDED(retc))
         {
            retc = loop_brother->ConnectChild(delim_child);
            if(SUCCEEDED(retc)) retc = delim_child->ConnectBrother(cur_child);
            if(SUCCEEDED(retc)) delim_child = NULL;
         }

         KP_DELETE(delim_child);

      } // if((cur_child!=NULL) && SUCCEEDED(retc))

// -------------------------- loop through next children
      while((cur_child!=NULL) && SUCCEEDED(retc))
      {
// recursion through children of children first
         retc=cur_child->InsertDelimiters(iXmlVers);

         if(SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);
         next_tag=(KpChar)XC_Nul;
         tag_pars=NULL;
         if((next_brother!=NULL) && SUCCEEDED(retc))
         {
            retc=next_brother->GetNodeTag(&next_tag);
            if(SUCCEEDED(retc)) retc=next_brother->GetTagParsPtr(&tag_pars);
         }

// if((cur_tag==XC_Example) && (next_tag==XC_TranslGroup))
// cur_tag=XC_Example;

         delim_child=NULL;
         if(SUCCEEDED(retc))
         {
            retc=CreateDelimNode(&delim_child, cur_tag, next_tag, tag_pars, iXmlVers);
            if(FAILED(retc)) delim_child=NULL;
         }

         if(delim_child && SUCCEEDED(retc))
         {
            retc=delim_child->ConnectBrother(next_brother);
            if(SUCCEEDED(retc)) retc=cur_child->ConnectBrother(delim_child);
            if(SUCCEEDED(retc)) delim_child=NULL;
         }

         KP_DELETE(delim_child);

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->InsertDelimiters();

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::FindNode(KpChar iTag, XmlNode **pSubNodePtr)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_child;
KpChar cur_tag;

   if((
//       (iTag < m_iFirstTag) || CheckLastTag(iTag) ||
         (pSubNodePtr==NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(*pSubNodePtr!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   if(SUCCEEDED(retc)) while((loop_brother!=NULL) && (*pSubNodePtr==NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);

      if((cur_tag==iTag) && SUCCEEDED(retc)) *pSubNodePtr=loop_brother;


      if(SUCCEEDED(retc))
         if(*pSubNodePtr==NULL)
         {
//          retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
            cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// recursion through children of children first
            if((cur_child!=NULL) && SUCCEEDED(retc))
               retc=cur_child->FindNode(iTag, pSubNodePtr);

            if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
         }

   } // while((loop_brother!=NULL) && (*pSubNodePtr==C_Nul) && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::FindNextNode(KpChar iTag, XmlNode **pSubNodePtr, XmlNode *pPrevNode, bool *bPrevSkippedPtr)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_child;
KpChar cur_tag;

   if((
//       (iTag < m_iFirstTag) || CheckLastTag(iTag) ||
         (pSubNodePtr==NULL) || (bPrevSkippedPtr==NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(*pSubNodePtr!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   if(SUCCEEDED(retc)) while((loop_brother!=NULL) && (*pSubNodePtr==NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);

      if((cur_tag==iTag) && SUCCEEDED(retc))
      {
         if((*bPrevSkippedPtr) || (pPrevNode==NULL)) *pSubNodePtr=loop_brother;
         else if(pPrevNode==loop_brother) *bPrevSkippedPtr=True;
      }


      if(SUCCEEDED(retc))
         if(*pSubNodePtr==NULL)
         {
//          retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
            cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// recursion through children of children first
            if((cur_child!=NULL) && SUCCEEDED(retc))
               retc=cur_child->FindNextNode(iTag, pSubNodePtr, pPrevNode, bPrevSkippedPtr);

            if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
         }

   } // while((loop_brother!=NULL) && (*pSubNodePtr==C_Nul) && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::ClearAccents(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar *cont_ptr=NULL;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;

      // recursion through children of children first
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->ClearAccents();

      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((cont_ptr!=NULL) && SUCCEEDED(retc)) TvKpStrClearAccents(cont_ptr);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelLevelTags(iLevel);

return(retc);
}


// --------------------------------------------------
// KpChar TV_XM_CompBaseSpcIStr[]={TV_XM_CompBaseChar, C_Spc, C_Nul}; // "~ " // '~', Spc
HRESULT XmlNode::TestTilde(bool *bTildeFl)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar *cont_ptr=NULL;
const KpChar *cont_ptr_1=NULL;

   if((bTildeFl==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(!*bTildeFl)
   {
// loop on brothers
      loop_brother=this;
      while((loop_brother!=NULL) && (!*bTildeFl) && SUCCEEDED(retc))
      {
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)loop_brother->m_pFirstChild;

         // recursion through children of children first
         if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->TestTilde(bTildeFl);

         if(SUCCEEDED(retc)) if(!*bTildeFl)
         {
            if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
            if((cont_ptr!=NULL) && SUCCEEDED(retc))
            {
               cont_ptr_1=TvKpStrChr(cont_ptr, (KpChar)TV_XM_CompBaseChar); // '~'
               if(cont_ptr_1!=NULL)
               {
//                if(TvKpStrStr(cont_ptr, TV_XM_CompBaseSpcIStr)==NULL)
                  if((*(cont_ptr_1+1)!=C_Spc) && (*(cont_ptr_1+1)!=C_Nul))
                     *bTildeFl=True;
               }
            }
         }

         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

      } // while((loop_brother!=NULL) && SUCCEEDED(retc))

   } // if(!*bTildeFl)

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelLevelTags(iLevel);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::DelVert(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar *cont_ptr=NULL;
const KpChar *pnts=NULL;
KpChar *pntd=NULL;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;

      // recursion through children of children first
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->DelVert();

      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         pnts=pntd=cont_ptr;
         while(*pnts)
         {
            if(*pnts!=(KpChar)TV_XM_CompDelim) (*pntd++)=(*pnts); // '|'
            pnts++;
         }
         *pntd=C_Nul;
      }

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->DelLevelTags(iLevel);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::UpLevelGroups(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
XmlNode *next_brother_1;
XmlNode *first_child;
KpChar cur_tag;

// printf("==== %d %x\n", del_cnt++, this);
// retc=TestNode();

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if(SUCCEEDED(retc)) retc=cur_node->UpLevelGroups();

         if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc=cur_node->GetNodeTag(&cur_tag);
         if((cur_tag==XC_LevelGroup) && SUCCEEDED(retc))
         {
//          if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
            if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

            if(SUCCEEDED(retc)) retc=cur_node->SetFirstChild(NULL);
            if(SUCCEEDED(retc)) retc=cur_node->SetNextBrother(NULL);
            KP_DELETE(cur_node);

            if(SUCCEEDED(retc))
            {
               if(first_child!=NULL)
               {
                  if(SUCCEEDED(retc)) retc=first_child->SetFather0(loop_brother);

                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(first_child);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(first_child);
                  }

                  cur_node=first_child;
                  if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother_1);
                  while(next_brother_1 && SUCCEEDED(retc))
                  {
                     cur_node=next_brother_1;
                     if(SUCCEEDED(retc)) retc=cur_node->GetNextBrother((KpTreeEntry **)&next_brother_1);
                  }

                  if(SUCCEEDED(retc)) retc=cur_node->ConnectBrother(next_brother);

                  next_brother=first_child;
               }
               else
               {
                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(next_brother);
                  }
               }
            }
         }

         cur_node=next_brother;
         if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->UpLevelGroups();

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::UpCtgMng(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_node;
XmlNode *prev_brother;
XmlNode *next_brother;
XmlNode *next_brother_1;
XmlNode *first_child;
KpChar cur_tag;
KpChar next_tag;
KpChar prev_tag;

// printf("==== %d %x\n", del_cnt++, this);
// retc=TestNode();

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      prev_brother=NULL;
      prev_tag=(KpChar)XC_Nul;

//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_node);
      cur_node = (XmlNode *)loop_brother->m_pFirstChild;

      while((cur_node!=NULL) && SUCCEEDED(retc))
      {
      // recursion through children of children first
         if(SUCCEEDED(retc)) retc=cur_node->UpCtgMng();

         if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&next_brother);

         if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
         next_tag = (KpChar)XC_Nul;
         if(next_brother && SUCCEEDED(retc))
         {
            retc = next_brother->GetNodeTag(&next_tag);
            if((next_tag == XC_UsNoteDst) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = next_brother->GetNextBrother((KpTreeEntry **)&next_brother_1);
               if(next_brother_1 && SUCCEEDED(retc)) retc = next_brother_1->GetNodeTag(&next_tag);
            }
         }
         if(
            ((cur_tag==XC_CtgGroup) || (cur_tag==XC_MngGroup) || (cur_tag==XC_MngNearGroup)) &&
            (cur_tag!=prev_tag) && (cur_tag!=next_tag) &&
            SUCCEEDED(retc)
           )
         {
//          if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
            if(SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

            if(SUCCEEDED(retc)) retc=cur_node->SetFirstChild(NULL);
            if(SUCCEEDED(retc)) retc=cur_node->SetNextBrother(NULL);
            KP_DELETE(cur_node);

            if(SUCCEEDED(retc))
            {
               if(first_child!=NULL)
               {
                  if(SUCCEEDED(retc)) retc=first_child->SetFather0(loop_brother);

                  if(prev_brother!=NULL) retc=prev_brother->ConnectBrother(first_child);
                  else
                  {
// first child deleted - update first child
                     retc=loop_brother->ConnectChild(first_child);
                  }

                  cur_node = first_child;
                  if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&next_brother_1);
                  while(next_brother_1 && SUCCEEDED(retc))
                  {
                     cur_node = next_brother_1;
                     if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&next_brother_1);
                  }

                  if(SUCCEEDED(retc)) retc = cur_node->ConnectBrother(next_brother);

                  next_brother = first_child;
               }
               else
               {
                  if(prev_brother!=NULL) retc = prev_brother->ConnectBrother(next_brother);
                  else
                  {
// first child deleted - update first child
                     retc = loop_brother->ConnectChild(next_brother);
                  }
               }
            }
         }

         cur_node = next_brother;
         if(cur_tag != XC_UsNoteDst) prev_tag = cur_tag;
         if((cur_node != NULL) && SUCCEEDED(retc)) retc = cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);

      } // while((cur_node!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->UpLevelGroups();

return(retc);
}


// --------------------------------------------------
HRESULT GetNextWord(KpChar *iazPrevTextBuf, KpChar *iazCurWordBuf, KpChar *iazRestTextBuf)
{
HRESULT retc=S_OK;
const KpChar *pnts;
KpChar *pntd;

   TvKpStrCat(iazPrevTextBuf, iazCurWordBuf);
   iazCurWordBuf[0]=C_Nul;

   pnts=iazRestTextBuf;

   pntd=iazPrevTextBuf+TvKpStrLen(iazPrevTextBuf);
   while((!TvIsAlpha((KpChar)*pnts)) && (*pnts)) *(pntd++)=(*pnts++);
   *pntd=C_Nul;

   pntd=iazCurWordBuf;
   while(TvIsAlpha((KpChar)*pnts) || (*pnts==(KpChar)TV_XM_CompDelim)) *(pntd++)=(*pnts++); // '|'
   *pntd=C_Nul;

   pntd=iazRestTextBuf;
   while(*pnts) *(pntd++)=(*pnts++);
   *pntd=C_Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TestTemplateGramSingle(const KpChar *iazTestWord, const unsigned char *lpszTemplate, EC_Types iEncoding, int iLang)
{
HRESULT retc=S_OK;
unsigned char test_word[TV_XL_MAX_IX_LEN+1];
KpChar i_text_buf[TV_XL_MAX_IX_LEN+1];
unsigned char template_buf[TV_XL_MAX_IX_LEN+1];
int chr_cnt;
int ctbl;

   if(SUCCEEDED(retc)) retc=KpCharToIndexEntry(test_word, (const KpChar *)iazTestWord, TvKpStrLen(iazTestWord), TV_XL_MAX_IX_LEN, iLang, iEncoding);
   if(SUCCEEDED(retc)) TvStrLwr(test_word, (iEncoding<KPT_Ctnum)?iEncoding:1);

   if(SUCCEEDED(retc))
   {
      strncpy(template_buf, lpszTemplate, TV_XL_MAX_IX_LEN);
      template_buf[TV_XL_MAX_IX_LEN] = Nul;
      chr_cnt = strlen(template_buf);

      ctbl=1;
//    if(iEncoding<EC_First_Type) ctbl=iEncoding;
      if(iEncoding<KPT_Ctnum) ctbl=iEncoding;

      retc=KptStrEncode(i_text_buf, template_buf, ctbl);
   }
   if(SUCCEEDED(retc)) retc=KpCharToIndexEntry(template_buf, (const KpChar *)i_text_buf, chr_cnt, TV_XL_MAX_IX_LEN, iLang, iEncoding);
   if(SUCCEEDED(retc)) TvStrLwr(template_buf, (iEncoding<KPT_Ctnum)?iEncoding:1);

#if FALSE // #ifdef Debug
unsigned char str_buf[2*TV_XL_MAX_IX_LEN+100];
strcpy(str_buf, "~~~~~~~~~> ");
strcat(str_buf, test_word);
strcat(str_buf, " ");
strcat(str_buf, template_buf);
KP_TRACE(str_buf);
#endif

   if(SUCCEEDED(retc)) if(strcmp(test_word, template_buf)!=0) retc=KP_E_KWD_NOT_FOUND;

return(retc);
}


// --------------------------------------------------
HRESULT TestTemplateGram(const KpChar *iazTestWord, const unsigned char *lpszTemplate, EC_Types iEncoding)
{
HRESULT retc=S_OK;

   retc=TestTemplateGramSingle(iazTestWord, lpszTemplate, iEncoding, KP_LNG_LIT);
   if(retc==KP_E_KWD_NOT_FOUND)
      retc=TestTemplateGramSingle(iazTestWord, lpszTemplate, iEncoding, KP_LNG_ENG);
   if(retc==KP_E_KWD_NOT_FOUND)
      retc=TestTemplateGramSingle(iazTestWord, lpszTemplate, iEncoding, KP_LNG_GER);

return(retc);
}


// --------------------------------------------------
HRESULT TestTemplate(const KpChar *iazTestWord, const unsigned char *lpszTemplate, EC_Types iEncoding)
{
HRESULT retc=S_OK;
unsigned char test_word[TV_XL_MAX_IX_LEN+1];
KpChar i_text_buf[TV_XL_MAX_IX_LEN+1];
unsigned char templ[TV_XL_MAX_IX_LEN+1];
KpChar i_templ[TV_XL_MAX_IX_LEN+1];
int chr_cnt;
int ctbl;

// ------------- test word
   if(SUCCEEDED(retc))
   {
      ctbl=1;
//    if(iEncoding<EC_First_Type) ctbl=iEncoding;
      if(iEncoding<KPT_Ctnum) ctbl=iEncoding;

      TvKpStrNCpy(i_text_buf, iazTestWord, TV_XL_MAX_IX_LEN);
      i_text_buf[TV_XL_MAX_IX_LEN]=C_Nul;

//    TvClearAccents(i_text_buf);
      TvKpStrLat(i_text_buf);

      TvKpStrLwr(i_text_buf);

      retc=KptStrDecode(test_word, i_text_buf, ctbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(retc, test_word, False, __FILE__, __LINE__, 0L);
#else
         retc=S_OK;
#endif
      }
   }

// ------------- templ
   if(SUCCEEDED(retc))
   {
      strncpy(templ, lpszTemplate, TV_XL_MAX_IX_LEN);
      templ[TV_XL_MAX_IX_LEN]=Nul;
      chr_cnt=strlen(templ);
      retc=KptStrEncode(i_templ, templ, ctbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(retc, test_word, False, __FILE__, __LINE__, 0L);
#else
         retc=S_OK;
#endif
      }
   }
   if(SUCCEEDED(retc))
   {
      i_templ[chr_cnt]=C_Nul;

//    TvClearAccents(i_templ);
      TvKpStrLat(i_templ);

      TvKpStrLwr(i_templ);

      retc=KptStrDecode(templ, i_templ, ctbl);
      if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(retc, test_word, False, __FILE__, __LINE__, 0L);
#else
         retc=S_OK;
#endif
      }
   }

// --------------------
   if(SUCCEEDED(retc))
   {
      templ[chr_cnt]=Nul;
      test_word[chr_cnt]=Nul;

      if(strcmp(test_word, templ)!=0) retc=KP_E_KWD_NOT_FOUND;
   }

#if FALSE
KP_TRACE("-------------------");
KP_TRACE(templ);
KP_TRACE(test_word);
#endif

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::MarcHighlightedGram(const unsigned char *lpszTemplate, EC_Types iEncoding)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
XmlNode *prev_brother=NULL;
XmlNode *test_child=NULL;
XmlNode *prev_text_child=NULL;
XmlNode *hilight_child=NULL;
XmlNode *cur_word_child=NULL;
KpChar cur_tag;
KpChar *cont_ptr=NULL;
KpChar *prev_text=NULL;
KpChar *cur_word=NULL;
KpChar *rest_text=NULL;
int len;

   if((lpszTemplate==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc)) if(strlen(lpszTemplate)>0)
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// -------------------------- loop through next children
      while((cur_child!=NULL) && SUCCEEDED(retc))
      {
// recursion through children of children first
         if((cur_child!=NULL) && SUCCEEDED(retc))
            retc=cur_child->MarcHighlightedGram(lpszTemplate, iEncoding);

         if(SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);

         if(SUCCEEDED(retc))
         {
            if(cur_tag==XL_Text)
            {
               if(SUCCEEDED(retc))
               {
//                retc = cur_child->GetFirstChild((KpTreeEntry **)&test_child);
                  test_child = (XmlNode *)cur_child->m_pFirstChild;

                  if((test_child!=NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               }

               cont_ptr=NULL;
               if(SUCCEEDED(retc))
               {
                  retc=cur_child->GetContentsPtr(&cont_ptr);
                  if((cont_ptr==NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  if(cont_ptr!=NULL)
                  {
                     len = TvKpStrLen(cont_ptr);
                     KP_NEWA(prev_text, KpChar, len + 1);
                     KP_NEWA(cur_word, KpChar, len + 1);
                     KP_NEWA(rest_text, KpChar, len + 1);

                     if(SUCCEEDED(retc))
                     {
                        prev_text[0]=C_Nul;
                        cur_word[0]=C_Nul;
                        TvKpStrCpy(rest_text, cont_ptr);
                     }

                     if(SUCCEEDED(retc)) while((TvKpStrLen(rest_text)>0) && SUCCEEDED(retc))
                     {
                        retc=GetNextWord(prev_text, cur_word, rest_text);
                        if(SUCCEEDED(retc))
                        {
                           if(TvKpStrLen(cur_word)!=0)
                           {
                              retc=TestTemplateGram(cur_word, lpszTemplate, iEncoding);
                              if(retc==KP_E_KWD_NOT_FOUND)
                              {
                                 retc=S_OK;
                                 if(TvKpStrLen(rest_text)==0)
                                    cur_child=next_brother;
                              }
                              else if(SUCCEEDED(retc))
                              {
                                 retc=cur_child->GetPrevBrother((KpTreeEntry **)&prev_brother);

                                 if(SUCCEEDED(retc)) retc = cur_child->SetNextBrother(NULL);
                                 if(SUCCEEDED(retc)) retc = cur_child->SetPrevBrother(NULL);
                                 KP_DELETE(cur_child);
//------------
                                 prev_text_child=NULL;
                                 if(SUCCEEDED(retc)) if(TvKpStrLen(prev_text)>0)
                                 {
                                    KP_NEWO(prev_text_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)prev_text, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));

                                    if(SUCCEEDED(retc))
                                    {
                                       if(prev_brother!=NULL)
                                          retc=prev_brother->ConnectBrother(prev_text_child);
                                       else
                                          retc=loop_brother->ConnectChild(prev_text_child);
                                    }
                                 }
// ---------------
                                 hilight_child=NULL;
                                 cur_word_child=NULL;
                                 KP_NEWO(hilight_child, XmlNode((KpChar)XC_HiLight, NULL, (const KpChar *)NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));
                                 KP_NEWO(cur_word_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)cur_word, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, hilight_child));
                                 if(SUCCEEDED(retc)) retc = hilight_child->ConnectChild(cur_word_child);
                                 if(SUCCEEDED(retc))
                                 {
                                    if(prev_text_child != NULL)
                                       retc = prev_text_child->ConnectBrother(hilight_child);
                                    else if(prev_brother != NULL)
                                       retc = prev_brother->ConnectBrother(hilight_child);
                                    else
                                       retc = loop_brother->ConnectChild(hilight_child);
                                 }
// ---------------

                                 cur_child = next_brother;

                                 if(SUCCEEDED(retc)) if(TvKpStrLen(rest_text) > 0)
                                 {
                                    cur_child = NULL;
                                    KP_NEWO(cur_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)rest_text, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));
                                 }

                                 if(SUCCEEDED(retc)) retc = hilight_child->ConnectBrother(cur_child);
// --------------
                                 rest_text[0]=C_Nul; // iseiti is ciklo

                                 prev_text_child=NULL;
                                 hilight_child=NULL;
                                 cur_word_child=NULL;

                              } // else // if(retc==KP_E_KWD_NOT_FOUND)

                           }
                           else // if(TvKpStrLen(cur_word!=0))
                           {
                              cur_child=next_brother;
                              if(TvKpStrLen(rest_text)!=0)
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
                           }

                        } // if(SUCCEEDED(retc))

                     } // while((TvKpStrLen(rest_text)>0) && SUCCEEDED(retc))

                     KP_DELETEA(prev_text);
                     KP_DELETEA(cur_word);
                     KP_DELETEA(rest_text);
                  }
                  else // if(cont_ptr!=NULL)
                     cur_child=next_brother;

               } // if(SUCCEEDED(retc))
            }
            else // if(cur_tag==XL_Text)
               cur_child=next_brother;

         } // if(SUCCEEDED(retc))

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->MarcHighlightedGram();

return(retc);
}


// --------------------------------------------------
// int iMarcHighlighted_cnt = 0;

HRESULT XmlNode::MarcHighlighted(const unsigned char *lpszTemplate, EC_Types iEncoding)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
XmlNode *prev_brother=NULL;
XmlNode *test_child=NULL;
XmlNode *prev_text_child=NULL;
XmlNode *hilight_child=NULL;
XmlNode *cur_word_child=NULL;
KpChar cur_tag;
KpChar *cont_ptr=NULL;
KpChar *prev_text=NULL;
KpChar *cur_word=NULL;
KpChar *rest_text=NULL;
int len;

// if(iMarcHighlighted_cnt == 0) KP_TRACE("MarcHighlighted pradzia");
// iMarcHighlighted_cnt++;

   if((lpszTemplate==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
// while((loop_brother!=NULL) && SUCCEEDED(retc))
   if((loop_brother!=NULL) && SUCCEEDED(retc)) if(strlen(lpszTemplate)>0)
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// -------------------------- loop through next children
      while((cur_child!=NULL) && SUCCEEDED(retc))
      {
// recursion through children of children first
         if((cur_child!=NULL) && SUCCEEDED(retc))
            retc=cur_child->MarcHighlighted(lpszTemplate, iEncoding);

         if(SUCCEEDED(retc)) retc=cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);

         if(SUCCEEDED(retc))
         {
            if(cur_tag==XL_Text)
            {
               if(SUCCEEDED(retc))
               {
//                retc = cur_child->GetFirstChild((KpTreeEntry **)&test_child);
                  test_child = (XmlNode *)cur_child->m_pFirstChild;

                  if((test_child!=NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               }

               cont_ptr=NULL;
               if(SUCCEEDED(retc))
               {
                  retc=cur_child->GetContentsPtr(&cont_ptr);
                  if((cont_ptr==NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  if(cont_ptr!=NULL)
                  {
                     len = TvKpStrLen(cont_ptr);
                     KP_NEWA(prev_text, KpChar, len + 1);
                     KP_NEWA(cur_word, KpChar, len + 1);
                     KP_NEWA(rest_text, KpChar, len + 1);

                     if(SUCCEEDED(retc))
                     {
                        prev_text[0]=C_Nul;
                        cur_word[0]=C_Nul;
                        TvKpStrCpy(rest_text, cont_ptr);
                     }

                     if(SUCCEEDED(retc)) while((TvKpStrLen(rest_text)>0) && SUCCEEDED(retc))
                     {
                        retc=GetNextWord(prev_text, cur_word, rest_text);
                        if(SUCCEEDED(retc))
                        {
                           if(TvKpStrLen(cur_word)!=0)
                           {
                              retc=TestTemplate(cur_word, lpszTemplate, iEncoding);
                              if(retc==KP_E_KWD_NOT_FOUND)
                              {
                                 retc=S_OK;
                                 if(TvKpStrLen(rest_text)==0)
                                    cur_child=next_brother;
                              }
                              else if(SUCCEEDED(retc))
                              {
                                 retc=cur_child->GetPrevBrother((KpTreeEntry **)&prev_brother);

                                 if(SUCCEEDED(retc)) retc=cur_child->SetNextBrother(NULL);
                                 if(SUCCEEDED(retc)) retc=cur_child->SetPrevBrother(NULL);
                                 KP_DELETE(cur_child);
//------------
                                 prev_text_child = NULL;
                                 if(SUCCEEDED(retc)) if(TvKpStrLen(prev_text)>0)
                                 {
                                    KP_NEWO(prev_text_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)prev_text, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));

                                    if(SUCCEEDED(retc))
                                    {
                                       if(prev_brother!=NULL)
                                          retc=prev_brother->ConnectBrother(prev_text_child);
                                       else
                                          retc=loop_brother->ConnectChild(prev_text_child);
                                    }
                                 }
// ---------------
                                 hilight_child=NULL;
                                 cur_word_child=NULL;
                                 KP_NEWO(hilight_child, XmlNode((KpChar)XC_HiLight, NULL, (const KpChar *)NULL, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));
                                 KP_NEWO(cur_word_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)cur_word, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, hilight_child));
                                 if(SUCCEEDED(retc)) retc = hilight_child->ConnectChild(cur_word_child);
                                 if(SUCCEEDED(retc))
                                 {
                                    if(prev_text_child != NULL)
                                       retc = prev_text_child->ConnectBrother(hilight_child);
                                    else if(prev_brother != NULL)
                                       retc = prev_brother->ConnectBrother(hilight_child);
                                    else
                                       retc = loop_brother->ConnectChild(hilight_child);
                                 }
// ---------------

                                 cur_child = next_brother;

                                 if(SUCCEEDED(retc)) if(TvKpStrLen(rest_text)>0)
                                 {
                                    cur_child = NULL;
                                    KP_NEWO(cur_child, XmlNode((KpChar)XL_Text, NULL, (const KpChar *)rest_text, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, loop_brother));
                                 }

                                 if(SUCCEEDED(retc)) retc = hilight_child->ConnectBrother(cur_child);
// --------------
                                 rest_text[0] = C_Nul; // iseiti is ciklo

                                 prev_text_child = NULL;
                                 hilight_child = NULL;
                                 cur_word_child = NULL;

                              } // else // if(retc==KP_E_KWD_NOT_FOUND)

                           }
                           else // if(TvKpStrLen(cur_word!=0))
                           {
                              cur_child=next_brother;
                              if(TvKpStrLen(rest_text)!=0)
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
                           }

                        } // if(SUCCEEDED(retc))


// KP_TRACE("MarcHighlighted pries Sleep");
// MarcHighlighted() letina lzdsh scrolinima search liste, bet sitas Sleep() vis tiek nepadeda,
//    WM_TIMER pranesimai praeina, bet scrollbaras vis tiek stabcioja
// Sleep(1);
// KP_TRACE("MarcHighlighted po Sleep");

                     } // while((TvKpStrLen(rest_text)>0) && SUCCEEDED(retc))

                     KP_DELETEA(prev_text);
                     KP_DELETEA(cur_word);
                     KP_DELETEA(rest_text);
                  }
                  else // if(cont_ptr!=NULL)
                     cur_child=next_brother;

               } // if(SUCCEEDED(retc))
            }
            else // if(cur_tag==XL_Text)
               cur_child=next_brother;

         } // if(SUCCEEDED(retc))

//       Sleep(100); // if(SUCCEEDED(retc)) retc = KpSleep(10, NULL);

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->MarcHighlighted();

// iMarcHighlighted_cnt--;
// if(iMarcHighlighted_cnt == 0) KP_TRACE("MarcHighlighted galas");

return(retc);
}


// --------------------------------------------------
#ifdef Debug
int cx_inc=1;
#endif
const KpChar iazSpc[]={C_Spc, C_Nul};
// apjungia gretimas nuorodas tuo paciu href-u
HRESULT XmlNode::ConcatXrs(void /* XmlNode *pCurEntry */)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;

XmlNode *loop_brother=NULL;
XmlNode *next_brother=NULL;
XmlNode *next_next_brother=NULL;
XmlNode *next_next_next_brother=NULL;

XmlNode *first_child=NULL;
XmlNode *next_child=NULL;
XmlNode *next_next_child=NULL;

XmlNode *prev_brother=NULL;
XmlNode *sup_node=NULL;
XmlNode *text_node=NULL;
XmlTagPars *tag_pars=NULL;

KpChar *val_buf = NULL;
   KP_NEWA(val_buf, KpChar, MAX_XML_PAR_VAL_LEN + 1);
KpChar *next_val_buf = NULL;
   KP_NEWA(next_val_buf, KpChar, MAX_XML_PAR_VAL_LEN + 1);

KpChar cur_tag=C_Nul;
KpChar next_tag=C_Nul;
KpChar next_next_tag=C_Nul;

KpChar *first_cont=NULL;
KpChar *next_cont=NULL;
KpChar *next_next_cont=NULL;

KpChar *new_cont = NULL;
KpChar *buf_ptr = NULL;

int par_num;
int ll;

// if((pCurEntry==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      cur_node=this; // pCurEntry;

//    retc = cur_node->GetFirstChild((KpTreeEntry **)&loop_brother);
      loop_brother = (XmlNode *)cur_node->m_pFirstChild;

// loop on brothers
      while((loop_brother!=NULL) && SUCCEEDED(retc))
      {
// #ifdef Debug
// printf("%d %x %x\n", cx_inc++, cur_node, loop_brother, cur_tag);
// fflush(stdout);
// if(cx_inc==587)
// cx_inc=587;
// #endif

// recursion on children
         if(SUCCEEDED(retc)) retc=loop_brother->ConcatXrs();

         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);
         next_next_brother=NULL;
         if((next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_brother->GetNextBrother((KpTreeEntry **)&next_next_brother);
         next_next_next_brother=NULL;
         if((next_next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_next_brother->GetNextBrother((KpTreeEntry **)&next_next_next_brother);

         if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
// #ifdef Debug
// printf("%d %x %x %d\n", cx_inc++, cur_node, loop_brother, cur_tag);
// fflush(stdout);
// if(cx_inc==587)
// cx_inc=587;
// #endif
         next_tag=(KpChar)XC_Nul;
         if((next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_brother->GetNodeTag(&next_tag);
         next_next_tag=(KpChar)XC_Nul;
         if((next_next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_next_brother->GetNodeTag(&next_next_tag);

// ------------------------------ <xr> <tx> <xr>
         if(
            (cur_tag==XC_Reference) &&
            (next_tag==XL_Text) &&
            (next_next_tag==XC_Reference) &&
            SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
            if((tag_pars!=NULL) && SUCCEEDED(retc))
            {
               retc=tag_pars->SeekKpTextPar("href", val_buf, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
               else if(SUCCEEDED(retc))
               {
                  retc=next_next_brother->GetTagParsPtr(&tag_pars);
                  if((tag_pars!=NULL) && SUCCEEDED(retc))
                  {
                     retc=tag_pars->SeekKpTextPar("href", next_val_buf, &par_num);
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else if(SUCCEEDED(retc))
                     {
// ar sutampa abieju <xr> tago nuorodos parametras?
                        if(TvKpStrCmp(val_buf, next_val_buf)==0)
                        {
// pirmo <xr> tekstas

//                         if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
                           if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

                           if((first_child==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc))
                              retc=first_child->GetContentsPtr(&first_cont);
                           if((first_cont==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
// tarpinio <tx> tekstas
                           if(SUCCEEDED(retc))
                              retc=next_brother->GetContentsPtr(&next_cont);
                           if((next_cont==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
// antro <xr> tekstas
//                         if(SUCCEEDED(retc)) retc = next_next_brother->GetFirstChild((KpTreeEntry **)&next_next_child);
                           if(SUCCEEDED(retc)) next_next_child = (XmlNode *)next_next_brother->m_pFirstChild;

                           if((next_next_child==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc))
                              retc=next_next_child->GetContentsPtr(&next_next_cont);
                           if((next_next_cont==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// ar tarpinis textas - tarpai?
                           KP_NEWA(buf_ptr, KpChar, TvKpStrLen(next_cont) + 1);
                           if(SUCCEEDED(retc)) TvKpStrCpy(buf_ptr, next_cont);
                           if(SUCCEEDED(retc)) retc = CutInitTrailSpcsKp(buf_ptr);

//                         if(SUCCEEDED(retc)) if(TvKpStrCmp(next_cont, iazSpc)==0)
                           if(SUCCEEDED(retc)) if(TvKpStrLen(buf_ptr)==0)
                           {
// sujungiam visus tekstus
                              if(SUCCEEDED(retc))
                              {
                                 ll = TvKpStrLen(first_cont) + TvKpStrLen(/* next_cont */ iazSpc) + TvKpStrLen(next_next_cont) + 1;
                                 KP_NEWA(new_cont, KpChar, ll);
                              }
                              if(SUCCEEDED(retc))
                              {
                                 TvKpStrCpy(new_cont, first_cont);
                                 TvKpStrCat(new_cont, /* next_cont */ iazSpc);
                                 TvKpStrCat(new_cont, next_next_cont);
// pirmam <xr> nustatom apjungta teksta
                                 retc=first_child->SetContents(new_cont);
                              }
                              KP_DELETEA(new_cont);
// apjungiam/ismetam tarpinius mazgus
                              if(SUCCEEDED(retc))
                                 retc=loop_brother->SetNextBrother(next_next_next_brother);
                              if((next_next_next_brother!=NULL) && SUCCEEDED(retc))
                                 retc=next_next_next_brother->SetPrevBrother(loop_brother);

                              if((next_brother!=NULL) && SUCCEEDED(retc))
                              {
                                 retc=next_brother->SetPrevBrother(NULL);
                                 if(SUCCEEDED(retc))
                                    retc=next_brother->SetNextBrother(NULL);
                                 KP_DELETE(next_brother);
                              }

                              if((next_next_brother!=NULL) && SUCCEEDED(retc))
                              {
                                 retc=next_next_brother->SetPrevBrother(NULL);
                                 if(SUCCEEDED(retc))
                                    retc=next_next_brother->SetNextBrother(NULL);
                                 KP_DELETE(next_next_brother);
                              }

//                            next_brother=next_next_next_brother;
                              next_brother=loop_brother;

                           } // if(TvKpStrCmp(next_cont, iazSpc)==0)

                           KP_DELETEA(buf_ptr);

                        } // if(TvKpStrCmp(val_buf, next_val_buf)==0)

                     } // else // if(retc==KP_E_KWD_NOT_FOUND) // retc=tag_pars->SeekKpTextPar("href", next_val_buf, &par_num);

                  } // if((tag_pars!=NULL) && SUCCEEDED(retc)) // retc=next_next_brother->GetTagParsPtr(&tag_pars);

               } // else // if(retc==KP_E_KWD_NOT_FOUND) // retc=tag_pars->SeekKpTextPar("href", val_buf, &par_num);

            } // if((tag_pars!=NULL) && SUCCEEDED(retc))

         } // if((cur_tag==XC_Reference) && (next_tag==XL_Text) && (next_next_tag==XC_Reference) && SUCCEEDED(retc))

// ------------------------------ <xr> <xr>
         if(
            (cur_tag==XC_Reference) &&
            (next_tag==XC_Reference) &&
            SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
            if((tag_pars!=NULL) && SUCCEEDED(retc))
            {
               retc=tag_pars->SeekKpTextPar("href", val_buf, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
               else if(SUCCEEDED(retc))
               {
                  retc=next_brother->GetTagParsPtr(&tag_pars);
                  if((tag_pars!=NULL) && SUCCEEDED(retc))
                  {
                     retc=tag_pars->SeekKpTextPar("href", next_val_buf, &par_num);
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else if(SUCCEEDED(retc))
                     {
// ar sutampa abieju <xr> tago nuorodos parametras?
                        if(TvKpStrCmp(val_buf, next_val_buf)==0)
                        {
// pirmo <xr> tekstas
//                         if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
                           if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

                           if((first_child==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc))
                              retc=first_child->GetContentsPtr(&first_cont);
                           if((first_cont==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
// antro <xr> tekstas
//                         if(SUCCEEDED(retc)) retc = next_brother->GetFirstChild((KpTreeEntry **)&next_child);
                           if(SUCCEEDED(retc)) next_child = (XmlNode *)next_brother->m_pFirstChild;

                           if((next_child==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                           if(SUCCEEDED(retc))
                              retc=next_child->GetContentsPtr(&next_cont);
                           if((next_cont==NULL) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// ar tarpinis textas vienas tarpas?
// sujungiam visus tekstus
                           if(SUCCEEDED(retc))
                           {
                              ll = TvKpStrLen(first_cont) + TvKpStrLen(next_cont) + 1;
                              KP_NEWA(new_cont, KpChar, ll);
                           }
                           if(SUCCEEDED(retc))
                           {
                              TvKpStrCpy(new_cont, first_cont);
                              TvKpStrCat(new_cont, next_cont);
// pirmam <xr> nustatom apjungta teksta
                              retc=first_child->SetContents(new_cont);
                           }
                           KP_DELETEA(new_cont);
// apjungiam/ismetam tarpinius mazgus
                           if(SUCCEEDED(retc))
                              retc=loop_brother->SetNextBrother(next_next_brother);
                           if((next_next_brother!=NULL) && SUCCEEDED(retc))
                              retc=next_next_brother->SetPrevBrother(loop_brother);

                           if((next_brother!=NULL) && SUCCEEDED(retc))
                           {
                              retc=next_brother->SetPrevBrother(NULL);
                              if(SUCCEEDED(retc))
                                 retc=next_brother->SetNextBrother(NULL);
                              KP_DELETE(next_brother);
                           }

//                         next_brother=next_next_brother;
                           next_brother=loop_brother;

                        } // if(TvKpStrCmp(val_buf, next_val_buf)==0)

                     } // else // if(retc==KP_E_KWD_NOT_FOUND) // retc=tag_pars->SeekKpTextPar("href", next_val_buf, &par_num);

                  } // if((tag_pars!=NULL) && SUCCEEDED(retc)) // retc=next_next_brother->GetTagParsPtr(&tag_pars);

               } // else // if(retc==KP_E_KWD_NOT_FOUND) // retc=tag_pars->SeekKpTextPar("href", val_buf, &par_num);

            } // if((tag_pars!=NULL) && SUCCEEDED(retc))

         } // if((cur_tag==XC_Reference) && (next_next_tag==XC_Reference) && SUCCEEDED(retc))

// -----------------
         loop_brother=next_brother;
      }
   }

   KP_DELETEA(val_buf);
   KP_DELETEA(next_val_buf);

return(retc);
}


// --------------------------------------------------
// apjungia gretimus <tx> laukus
HRESULT XmlNode::ConcatTxs(void)
{
HRESULT retc=S_OK;
XmlNode *cur_node=NULL;

XmlNode *loop_brother=NULL;
XmlNode *next_brother=NULL;
XmlNode *next_next_brother=NULL;

KpChar cur_tag=C_Nul;
KpChar next_tag=C_Nul;
KpChar next_next_tag=C_Nul;

KpChar *first_cont=NULL;
KpChar *next_cont=NULL;

KpChar *new_cont=NULL;

int ll;
int ii;

// if((pCurEntry==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      cur_node=this; // pCurEntry;

//    retc = cur_node->GetFirstChild((KpTreeEntry **)&loop_brother);
      loop_brother = (XmlNode *)cur_node->m_pFirstChild;

// loop on brothers
      while((loop_brother!=NULL) && SUCCEEDED(retc))
      {
// recursion on children
         if(SUCCEEDED(retc)) retc=loop_brother->ConcatTxs();

         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);
         next_next_brother=NULL;
         if((next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_brother->GetNextBrother((KpTreeEntry **)&next_next_brother);

         if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
         next_tag=(KpChar)XC_Nul;
         if((next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_brother->GetNodeTag(&next_tag);
         next_next_tag=(KpChar)XC_Nul;
         if((next_next_brother!=NULL) && SUCCEEDED(retc))
            retc=next_next_brother->GetNodeTag(&next_next_tag);

// ------------------------------ <tx> <tx>
         if(
            (cur_tag==XL_Text) &&
            (next_tag==XL_Text) &&
            SUCCEEDED(retc)
           )
         {
// pirmo <tx> tekstas
            if(SUCCEEDED(retc))
               retc=loop_brother->GetContentsPtr(&first_cont);
            if((first_cont==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
// antro <tx> tekstas
            if(SUCCEEDED(retc))
               retc=next_brother->GetContentsPtr(&next_cont);
            if((next_cont==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

// sujungiam abu tekstus
            if(SUCCEEDED(retc))
            {
               ii = TvKpStrLen(first_cont);
               ll = ii + TvKpStrLen(next_cont) + 1;
               KP_NEWA(new_cont, KpChar, ll);
            }
            if(SUCCEEDED(retc))
            {
               TvKpStrCpy(new_cont, first_cont);
               if((ii>0) && SUCCEEDED(retc))
                  if((first_cont[ii-1]==C_Spc) && (next_cont[0]==C_Spc))
                     next_cont++;
               TvKpStrCat(new_cont, next_cont);
// pirmam <tx> nustatom apjungta teksta
               retc=loop_brother->SetContents(new_cont);
            }
            KP_DELETEA(new_cont);
// apjungiam/ismetam tarpinius mazgus
            if(SUCCEEDED(retc))
               retc=loop_brother->SetNextBrother(next_next_brother);
            if((next_next_brother!=NULL) && SUCCEEDED(retc))
               retc=next_next_brother->SetPrevBrother(loop_brother);

            if((next_brother!=NULL) && SUCCEEDED(retc))
            {
               retc=next_brother->SetPrevBrother(NULL);
               if(SUCCEEDED(retc)) retc = next_brother->SetNextBrother(NULL);
               KP_DELETE(next_brother);
            }

//          next_brother=next_next_brother;
            next_brother=loop_brother;

         } // if((cur_tag==XL_Text) && (next_next_tag==XL_Text) && SUCCEEDED(retc))

// -----------------
         loop_brother=next_brother;
      }
   }

return(retc);
}


// --------------------------------------------------
TvRtfO *SetTagHeadings_rtf_file = NULL;
unsigned char SetTagHeadings_rtf_file_buf[XMLN_RICH_BUF_LEN+1] = {Nul};
KpChar SetTagHeadings_node_suff[XL_ND_MaxNumOfNodes*2+2] = {C_Nul};

HRESULT XmlNode::SetTagHeadings_loop(int iNumOfParStyles, HWND hRtfWnd)
{
HRESULT retc = S_OK;
XmlNode *father=NULL;
XmlNode *prev_brother=NULL;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
XmlNode *next_brother=NULL;
KpChar cur_tag;
KpChar father_tag;
KpBmpBmp /* KpTextBmp */ text_bmp;

KpBmpBmp *value;
XmlNode *sub_node = NULL;
XmlNode *sub_node_br = NULL;
XmlNode *cur_node_father = NULL;
XmlNode *sub_node_father = NULL;
static unsigned char ctrl_txt[XMLN_RICH_BUF_LEN+1] = {Nul};
// static unsigned char prev_rtf_txt[XMLN_RICH_BUF_LEN+1] = {Nul};
static unsigned char prev_ctrl_txt[XMLN_RICH_BUF_LEN+1] = {Nul};
int ii = 0;
HDC hdc = 0;
HDC hdc_mem = 0;
HBITMAP new_bmp = 0;
HBITMAP old_bmp = 0;
const static KpChar null_str[2] = {C_NBSP /* C_QemSpc */ /* C_NullSpc */, C_Nul};
const static KpChar spc_str[3] = {C_Spc, C_NBSP, C_Nul};
int retv;


// ------------------------------ loop on brothers
   loop_brother=this;
   while(loop_brother && SUCCEEDED(retc))
   {
      ii = TvKpStrLen(SetTagHeadings_node_suff);
      if(ii < XL_ND_MaxNumOfNodes*2-1)
      {
//       if(ii>0) TvKpStrCpy(SetTagHeadings_node_suff+ii-1, spc_str);
//       else TvKpStrCpy(SetTagHeadings_node_suff, spc_str);

         TvKpStrCat(SetTagHeadings_node_suff, spc_str);
      }

// KP_TRACE("1. -----------------"); KP_TRACE(rtf_file_buf);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
//    if(((cur_tag < m_iFirstTag /* XC_FirstDictTag */) || CheckLastTag(cur_tag) /* (cur_tag >= XC_LastDictTag) */) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

//    text_bmp.m_lpszText[0] = Nul;
      text_bmp.m_hBmp = 0;
      text_bmp.m_hTextBmp = 0;

      if(SUCCEEDED(retc))
      {
//       strncpy(text_bmp.m_lpszText, m_plpszaTags /* plpszaSgmDictTags */[cur_tag - m_iFirstTag /* XC_FirstDictTag */], KP_MAX_FILE_LIN_WDT);
//       text_bmp.m_lpszText[KP_MAX_FILE_LIN_WDT] = Nul;

         text_bmp.m_hBmp =
//          hNodeBitmaps[cur_tag - m_iFirstTag /* XC_FirstDictTag */];
            GetNodeBitmap(cur_tag);

      }


//------------------------------------ RTF teksto paveiksliuku nustatymas
      sub_node = NULL;

// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//    if(loop_brother && SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
//    if(loop_brother && SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      KP_NEWO(sub_node, XmlNode(loop_brother, NULL, 0, loop_brother));

// <tx> apskliaudziam i tevo taga
      if((cur_tag == XL_Text) && SUCCEEDED(retc))
      {
         retc = loop_brother->GetFather((KpTreeEntry **)&cur_node_father);
         if(cur_node_father && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = cur_node_father->GetNodeTag(&father_tag);

            sub_node_father = NULL;
            KP_NEWO(sub_node_father, XmlNode((KpChar)father_tag, NULL, NULL, NULL, (const unsigned char *)"",
                  cur_node_father->GetFirstTag(), cur_node_father->GetTagsArrPtr(), NULL));
            if(SUCCEEDED(retc)) retc = sub_node_father->ConnectChild(sub_node);
            if(SUCCEEDED(retc)) sub_node = sub_node_father;
         }
      }

// pradzioj pridedam tuscia <tx>, kad nebutu bereikalingu prefiksu/skirtuku
      sub_node_br = NULL;
      KP_NEWO(sub_node_br, XmlNode((KpChar)XL_Text, NULL, null_str, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, NULL));
      if(SUCCEEDED(retc)) retc = sub_node_br->ConnectBrother(sub_node);
      if(SUCCEEDED(retc)) sub_node = sub_node_br;

      new_bmp = 0;

// gale pridedam uodega is tarpu - kad skirtusi kiekvieno tago tekstai lange
      sub_node_br = NULL;
      KP_NEWO(sub_node_br, XmlNode((KpChar)XL_Text, NULL, SetTagHeadings_node_suff, NULL, (const unsigned char *)"", XC_FirstDictTag, plpszaXmlttDictTagsFull, NULL));
      if(SUCCEEDED(retc)) retc = sub_node->AppendBrother(sub_node_br);


      if(SUCCEEDED(retc)) if((hRtfWnd!=NULL) && sub_node)
      {
// atsimenam praejusi teksta
// KP_TRACE("2. -----------------"); KP_TRACE(rtf_file_buf);
//       prev_rtf_txt[0] = Nul;
//       if(SUCCEEDED(retc)) strcpy(prev_rtf_txt, SetTagHeadings_rtf_file_buf);
         prev_ctrl_txt[0] = Nul;
         if(SUCCEEDED(retc))
         {
            retv=SendMessage(hRtfWnd, WM_GETTEXT,
                     (WPARAM)XMLN_RICH_BUF_LEN, (LPARAM)prev_ctrl_txt);
            if((!retv) && SUCCEEDED(retc)) prev_ctrl_txt[0] = Nul;
         }

// isvedam RTF
         if(SUCCEEDED(retc)) retc=SetTagHeadings_rtf_file->Reset();

// KP_TRACE("3. -----------------"); KP_TRACE(rtf_file_buf);

#     if FALSE
         if(sub_node && SUCCEEDED(retc)) retc=sub_node->WriteNode(theSearchThread.m_lpRtfTestOutFileObj);
#     else
         if(SUCCEEDED(retc)) retc=SetTagHeadings_rtf_file->WriteHeader(ColorTable, KpGmaxcc0);

         if(sub_node && SUCCEEDED(retc))
            retc=sub_node->WriteRtf(SetTagHeadings_rtf_file, (KpChar)XC_Dict,
               (KpChar)XC_Nul, iNumOfParStyles, SetTagHeadings_rtf_file->GetFldDepth());

         if(SUCCEEDED(retc)) retc=SetTagHeadings_rtf_file->WriteTail();
#     endif

#ifdef Debug
// KpMsgOut("pries", IDI_ASTERISK, KP_MB_TESTI);
#endif

#ifdef Debug
FILE *out_file=NULL;
out_file=fopen("SetTagHeadings_loop.rtf", "r");
if(out_file) fclose(out_file);
else
{
out_file=fopen("SetTagHeadings_loop.rtf", "w");
fputs((const char *)SetTagHeadings_rtf_file_buf, out_file);
fclose(out_file);
}
#endif

#     if FALSE
         if(SUCCEEDED(retc)) retc=theSearchThread.DisplayRtfTestResult();
#     else
         if(SUCCEEDED(retc))
         {
            retv=SendMessage(hRtfWnd, WM_SETTEXT, 0, (LPARAM)SetTagHeadings_rtf_file_buf);
            if((retv==CB_ERR) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            if((/* (retv==FALSE) || */ (retv==LB_ERRSPACE) || (retv==CB_ERRSPACE)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#        ifdef Debug
            if((!retv) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#        endif
         }
#     endif

#ifdef Debug
// Sleep(500);
#endif
#ifdef Debug
// KpMsgOut("po", IDI_ASTERISK, KP_MB_TESTI);
#endif

// laukiam, kol tekstas atsiras
#     if FALSE
         if(SUCCEEDED(retc)) KpSleep(100, HWND_DESKTOP);
#     else
         ii = 0;
         if(/* strcmp(prev_rtf_txt, SetTagHeadings_rtf_file_buf) && */ SUCCEEDED(retc)) do
         {
//          if(SUCCEEDED(retc)) Sleep(3);
            if(SUCCEEDED(retc)) KpSleep(3, HWND_DESKTOP);
//          if(SUCCEEDED(retc)) KpSleep(100, HWND_DESKTOP);

            ctrl_txt[0] = Nul;
            if(SUCCEEDED(retc))
               retv=SendMessage(hRtfWnd, WM_GETTEXT, (WPARAM)XMLN_RICH_BUF_LEN, (LPARAM)ctrl_txt);
#        ifdef Debug
            if((!retv) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#        endif
            ii++;

         } while(
                  (ii<30) &&
                  (!strcmp(ctrl_txt, prev_ctrl_txt /* lpszRtfTextBuf */)) &&
                  SUCCEEDED(retc)
                );

#        ifdef Debug
char str_buf[100];
if(ii>=30)
{
sprintf(str_buf, "-------------------------- XmlNode::SetTagHeadings: %d", ii);
KP_TRACE(str_buf);
// KP_TRACE(prev_rtf_txt);
// KP_TRACE(prev_ctrl_txt);
sprintf(str_buf, ">>>%s<<<", prev_ctrl_txt);
KP_TRACE(str_buf);
KP_TRACE("-----------------");
// KP_TRACE(SetTagHeadings_rtf_file_buf);
// KP_TRACE(ctrl_txt);
sprintf(str_buf, ">>>%s<<<", ctrl_txt);
KP_TRACE(str_buf);
}
#        endif


#     endif

// KP_TRACE("4. -----------------"); KP_TRACE(rtf_file_buf);

//       if(SUCCEEDED(retc)) retc=theSearchThread.m_lpRtfTestOutFileObj->Reset();
////     if(SUCCEEDED(retc)) memset(theSearchThread.m_lpszRtfTestResultRtfText, Nul, LZDSHT_RICH_BUF_LEN);

// bandom grabint paveiksliuka

         hdc = 0;
         if(SUCCEEDED(retc))
         {
            hdc = GetDC(hRtfWnd);
            if(hdc == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         hdc_mem = 0;
         if(SUCCEEDED(retc))
         {
            hdc_mem = CreateCompatibleDC(hdc);
            if(hdc_mem == 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         if(hdc_mem && SUCCEEDED(retc))
         {
            new_bmp = CreateCompatibleBitmap(hdc, rtf_grab_dx, rtf_grab_dy);
            if(new_bmp == 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         old_bmp = 0;
         if(hdc_mem && new_bmp && SUCCEEDED(retc))
         {
            old_bmp = (HBITMAP)SelectObject(hdc_mem, new_bmp);
            if(old_bmp == 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         if(hdc_mem && hdc && SUCCEEDED(retc))
            if(!BitBlt(hdc_mem,
                  0, 0, rtf_grab_dx, rtf_grab_dy,
                  hdc, rtf_grab_margin_x, rtf_grab_margin_y, SRCCOPY))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(hdc_mem && old_bmp && SUCCEEDED(retc))
            if(SelectObject(hdc_mem, old_bmp) == 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

      } // if(SUCCEEDED(retc)) if((hRtfWnd!=NULL) && sub_node)

      KP_DELETE(sub_node);

      if(SUCCEEDED(retc)) text_bmp.m_hTextBmp = new_bmp;


//------------------------------------
      if(SUCCEEDED(retc)) if(loop_brother->GetRecType() == KpRecType_BmpBmp)
      {
         value = (KpBmpBmp *)loop_brother->GetValue();
         KP_ASSERT(value != NULL, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(loop_brother->GetValSize() >= sizeof(KpBmpBmp), KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
         {
            if(value->m_hTextBmp != NULL) DeleteObject(value->m_hTextBmp);
            value->m_hTextBmp = 0;
         }
      }
      if(SUCCEEDED(retc)) retc=loop_brother->SetNewValue(&text_bmp);

// recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      if(first_child && SUCCEEDED(retc)) retc=first_child->SetTagHeadings_loop(iNumOfParStyles, hRtfWnd);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&next_brother);
      loop_brother=next_brother;

// KP_TRACE("5. -----------------"); KP_TRACE(rtf_file_buf);

   } // while(loop_brother && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::InitNodeStatus(void)
{
HRESULT retc = S_OK;
XmlNode *first_child=NULL;
XmlNode *loop_brother=NULL;
XmlNode *child_brother=NULL;
bool group_children = False;
bool single_value = False;
KpChar cur_tag;
KpChar child_tag;

// loop on brothers
   loop_brother=this;
   while(loop_brother && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;

      group_children = False;
      if(SUCCEEDED(retc)) retc=loop_brother->TestGroupChildren(&group_children);

      single_value = False;
      if(first_child && SUCCEEDED(retc))
      {
         retc = first_child->GetNodeTag(&child_tag);
         if((child_tag == XL_Text) && SUCCEEDED(retc))
         {
            retc=first_child->GetNextBrother((KpTreeEntry **)&child_brother);
            if((child_brother == NULL) && SUCCEEDED(retc)) single_value = True;
         }
      }

      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
//    if(((cur_tag < m_iFirstTag /* XC_FirstDictTag */) || CheckLastTag(cur_tag) /* (cur_tag >= XC_LastDictTag) */) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) loop_brother->m_iStatus = 0;

#if FALSE
#else
      if(SUCCEEDED(retc))
      {
         if(first_child) loop_brother->m_iStatus |= KpNodeHasChildren | (single_value?0:KpNodeExpanded); // low level children
         if(group_children) loop_brother->m_iStatus |= (KpNodeHasChildren | KpNodeExpanded) * KpNodeLevelFactor; // high level children
      }
#endif

      if(SUCCEEDED(retc))
         if(TvKpStrChr(uiazXmlGrTags, cur_tag)!=NULL)
#if FALSE
         {
            if(group_children) loop_brother->m_iStatus = KpHighExpandedNode;
//          else loop_brother->m_iStatus = KpHighChildlessNode;
            else if(first_child) loop_brother->m_iStatus = KpLowExpandedNode;
            else loop_brother->m_iStatus = KpLowChildlessNode;
         }
#else
            loop_brother->m_iStatus |= KpNodeVisible * KpNodeLevelFactor; // high level node
#endif
         else
#if FALSE
         {
            if(first_child) loop_brother->m_iStatus = KpLowExpandedNode;
            else loop_brother->m_iStatus = KpLowChildlessNode;
         }
#else
            loop_brother->m_iStatus |= KpNodeVisible; // low level node
#endif

// recursion on children
      if(first_child && SUCCEEDED(retc)) retc=first_child->InitNodeStatus();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::TestGroupChildren(bool *bHasGroupChildren)
{
HRESULT retc = S_OK;
XmlNode *cur_child=NULL;
KpChar cur_tag;

   if((bHasGroupChildren==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *bHasGroupChildren = False;

// loop on children
// if(SUCCEEDED(retc)) retc = GetFirstChild((KpTreeEntry **)&cur_child);
   if(SUCCEEDED(retc)) cur_child = (XmlNode *)m_pFirstChild;

   if(SUCCEEDED(retc)) while(cur_child && (!(*bHasGroupChildren)) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=cur_child->GetNodeTag(&cur_tag);
//    if(((cur_tag < m_iFirstTag /* XC_FirstDictTag */) || CheckLastTag(cur_tag) /* (cur_tag >= XC_LastDictTag)*/) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) *bHasGroupChildren |= (TvKpStrChr(uiazXmlGrTags, cur_tag)!=NULL);

      if(SUCCEEDED(retc)) if(!(*bHasGroupChildren))
         retc=cur_child->GetNextBrother((KpTreeEntry **)&cur_child);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::TestNotSignificant(bool *bEmpty, KpChar *iSkipTagArr)
{
HRESULT retc = S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar cur_tag;

   if((
//       (iSkipTagArr[...] < m_iFirstTag) || CheckLastTag(iSkipTagArr[...]) ||
         (iSkipTagArr == NULL) || (bEmpty == NULL)
      ) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      // recursion through children of children first
      if(*bEmpty && SUCCEEDED(retc))
      {
//       retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)loop_brother->m_pFirstChild;
      }
      if((first_child!=NULL) && *bEmpty && SUCCEEDED(retc)) retc=first_child->TestNotSignificant(bEmpty, iSkipTagArr);

      if(*bEmpty && SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
      if(*bEmpty &&
         (cur_tag != XC_LevelGroup) &&
         (cur_tag != XC_Level) &&
         (cur_tag != XC_FwNote) &&
         (cur_tag != XC_TechNote) &&
         (cur_tag != XC_StEntry) &&
         (cur_tag != XC_Paragraph) &&
         (cur_tag != XL_Text) &&
         (cur_tag != XC_PunctMark) &&
         (TvKpStrChr(iSkipTagArr, cur_tag) == NULL) &&
         SUCCEEDED(retc))
            *bEmpty = False;

      if(*bEmpty && SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

      if(!(*bEmpty)) break;

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->TestNotSignificant(bEmpty, iSkipTagArr);

return(retc);
}


// --------------------------------------------------------
HRESULT XmlNode::Hyphenate(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
XmlNode *prev_brother=NULL;
XmlNode *test_child=NULL;
KpChar cur_tag;
KpChar father_tag;
KpChar *cont_ptr=NULL;
static KpChar new_cont[KP_MAX_FILE_LIN_LEN+1];

// loop on brothers
   loop_brother = this;
// while((loop_brother != NULL) && SUCCEEDED(retc))
   if((loop_brother != NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

      if(SUCCEEDED(retc)) retc = loop_brother->GetNodeTag(&father_tag);

// -------------------------- loop through next children
      while((cur_child != NULL) && SUCCEEDED(retc))
      {

// recursion through children of children first
         if(SUCCEEDED(retc)) retc = cur_child->Hyphenate();

         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

         if((cur_tag == XL_Text) && (GetTagLang(father_tag) == KP_LNG_LIT) && SUCCEEDED(retc))  // kalba nesuveikia, jeigu tëvas giliau
         {                                                                                      // taip pat AKLZENLT kalbos atbulos
            if(SUCCEEDED(retc))
            {
//             retc = cur_child->GetFirstChild((KpTreeEntry **)&test_child);
               test_child = (XmlNode *)cur_child->m_pFirstChild;

               if((test_child!=NULL) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            cont_ptr = NULL;
            if(SUCCEEDED(retc))
            {
               retc = cur_child->GetContentsPtr(&cont_ptr);
               if((cont_ptr == NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) if(TvKpStrLen(cont_ptr) >= KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) TvKpStrCpy(new_cont, cont_ptr);

            if(SUCCEEDED(retc)) retc = KpStrHyphenate(new_cont);

            if(SUCCEEDED(retc)) retc = cur_child->SetContents(new_cont);

         } // if(cur_tag==XL_Text)

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->Hyphenate();

return(retc);
}


// --------------------------------------------------------
#if TRUE // #ifdef Debug
HRESULT XmlNode::TraceContents(const unsigned char *lpszIndent)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *cur_child = NULL;
KpChar cur_tag;
const unsigned char *tag_ptr = NULL;
KpChar *cont_ptr = NULL;
unsigned char *str_ptr = NULL;
int str_len;

// loop on brothers
   loop_brother = this;
   while((loop_brother != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = loop_brother->GetNodeTag(&cur_tag);
      if((cur_tag != XL_Text) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) tag_ptr = GetTagName(cur_tag);
         if(tag_ptr && SUCCEEDED(retc))
         {
            str_len = 0;
            if(lpszIndent && SUCCEEDED(retc)) str_len += strlen(lpszIndent);
            if(SUCCEEDED(retc)) str_len += strlen(tag_ptr);
            KP_NEWA(str_ptr, unsigned char, str_len + 1);
            if(str_ptr != null)
            {
               if(SUCCEEDED(retc)) str_ptr[0] = Nul;
               if(lpszIndent && SUCCEEDED(retc)) strcat(str_ptr, lpszIndent);
               if(SUCCEEDED(retc)) str_len = strlen(str_ptr);
               if(SUCCEEDED(retc)) strcat(str_ptr, tag_ptr);

               if(SUCCEEDED(retc)) retc = SpcEolToSpc(str_ptr + str_len);

//             if(SUCCEEDED(retc)) KP_TRACE(str_ptr);
               if(SUCCEEDED(retc)) PutLogMessage_(str_ptr);

               KP_DELETEA(str_ptr);
            }
         }
      }

      cont_ptr = NULL;
      if(SUCCEEDED(retc)) retc = loop_brother->GetContentsPtr(&cont_ptr);
      if(cont_ptr && SUCCEEDED(retc))
      {
         str_len = 0;
         if(lpszIndent && SUCCEEDED(retc)) str_len += strlen(lpszIndent);
         if(SUCCEEDED(retc)) str_len += 3;
         if(SUCCEEDED(retc)) str_len += TvKpStrLen(cont_ptr);
         KP_NEWA(str_ptr, unsigned char, str_len + 1);
         if(str_ptr != null)
         {
            if(SUCCEEDED(retc)) str_ptr[0] = Nul;
//          if(SUCCEEDED(retc)) strcat(str_ptr, "   ");
            if(lpszIndent && SUCCEEDED(retc)) strcat(str_ptr, lpszIndent);
            if(SUCCEEDED(retc)) str_len = strlen(str_ptr);

            /* retc = */ KptStrDecode(str_ptr + str_len, cont_ptr, TV_MAIN_CTBL);
//          if(SUCCEEDED(retc)) KP_TRACE(str_ptr);
            if(SUCCEEDED(retc)) PutLogMessage_(str_ptr);

            KP_DELETEA(str_ptr);
         }
      }

// recursion through children of children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      if(SUCCEEDED(retc)) cur_child = (XmlNode *)loop_brother->m_pFirstChild;

      if(cur_child && SUCCEEDED(retc))
      {
         str_len = 0;
         if(lpszIndent) str_len = strlen(lpszIndent);
         KP_NEWA(str_ptr, unsigned char, str_len + 3 + 1);
         if(str_ptr != null)
         {
            strcpy(str_ptr, lpszIndent);
            strcat(str_ptr, "   ");
         }

         if(SUCCEEDED(retc)) retc = cur_child->TraceContents(str_ptr);

         KP_DELETEA(str_ptr);
      }

      if((cur_tag != XL_Text) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) tag_ptr = GetTagName(cur_tag + 1);
         if(tag_ptr && SUCCEEDED(retc))
         {
            str_len = 0;
            if(lpszIndent && SUCCEEDED(retc)) str_len += strlen(lpszIndent);
            if(SUCCEEDED(retc)) str_len += strlen(tag_ptr);
            KP_NEWA(str_ptr, unsigned char, str_len + 1);
            if(str_ptr)
            {
               if(SUCCEEDED(retc)) str_ptr[0] = Nul;
               if(lpszIndent && SUCCEEDED(retc)) strcat(str_ptr, lpszIndent);
               if(SUCCEEDED(retc)) str_len = strlen(str_ptr);
               if(SUCCEEDED(retc)) strcat(str_ptr, tag_ptr);

               if(SUCCEEDED(retc)) retc = SpcEolToSpc(str_ptr + str_len);

//             if(SUCCEEDED(retc)) KP_TRACE(str_ptr);
               if(SUCCEEDED(retc)) PutLogMessage_(str_ptr);

               KP_DELETEA(str_ptr);
            }
         }
      }

      if(SUCCEEDED(retc)) retc = loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->TraceContents();

return(retc);
}
#endif


// --------------------------------------------------------
HRESULT XmlNode::ExtractContents(KpChar **lppazTextPtr)
{
HRESULT retc = S_OK;

   KP_ASSERT(lppazTextPtr != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) *lppazTextPtr = NULL;

XmlNode *cur_child = NULL;
   if(SUCCEEDED(retc)) retc = SearchChildSubNode(XL_Text, &cur_child);

   if((cur_child != NULL) && SUCCEEDED(retc)) retc = cur_child->GetContentsPtr(lppazTextPtr);

return(retc);
}


// --------------------------------------------------------
HRESULT XmlNode::ExtractSubnodeContents(KpChar iTag, KpChar **lppazTextPtr)
{
HRESULT retc = S_OK;

   KP_ASSERT(lppazTextPtr != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) *lppazTextPtr = NULL;

XmlNode *cur_child = NULL;
   if(SUCCEEDED(retc)) retc = SearchChildSubNode(iTag, &cur_child);

   if(cur_child != NULL) retc = cur_child->ExtractContents(lppazTextPtr);

return(retc);
}


// --------------------------------------------------------
HRESULT XmlNode::ExtractSubnodeContentsStr(KpChar iTag, unsigned char **plpszTextBufPtr, int iCtbl)
{
HRESULT retc = S_OK;

   KP_ASSERT(plpszTextBufPtr != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) *plpszTextBufPtr = null;

KpChar *cont_ptr = NULL;
   if(SUCCEEDED(retc)) retc = ExtractSubnodeContents(iTag, &cont_ptr);

   if((cont_ptr != NULL) && SUCCEEDED(retc))
   {
      KP_NEWA(*plpszTextBufPtr, unsigned char, TvKpStrLen(cont_ptr) + 1);

      if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(*plpszTextBufPtr, cont_ptr, iCtbl);
   }

return(retc);
}

