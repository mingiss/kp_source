// ==================================================
// xmlh.cpp
// XML tag stack
//


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#include <ctype.h>
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
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "tvxml.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlh.h"


//===================================== class TvXmlTagStack
// --------------------------------------------------
TvXmlTagStack::TvXmlTagStack
(
TvXmlTagStack *pPrevTag,
KpChar iCurTag,
TvXmlTagStack *pParalTag,
int iIndnt
)
{
   pPrevTagPtr=pPrevTag;

   iCurrentTag=iCurTag;
// if(((iCurTag<XC_FirstDictTag) || (iCurTag>=XC_LastDictTag)) && (iCurTag!=C_Nul))
//    lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   bFreeTextAvail=False;
   bPutClose=True;
   bOpen=False;
   pParalelTagPtr=pParalTag;
   iIndent=iIndnt;
   bOutFl=True;
   if(pPrevTagPtr!=NULL) pPrevTagPtr->GetOutFl(&bOutFl);
}


// --------------------------------------------------
TvXmlTagStack::~TvXmlTagStack(void)
{
HRESULT retc = S_OK;

   KP_DELETE(pPrevTagPtr);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetPrevTagPtr(TvXmlTagStack **ppTagPtr)
{
HRESULT retc=S_OK;

   if(ppTagPtr!=NULL) *ppTagPtr=pPrevTagPtr;
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::SetPrevTagPtr(TvXmlTagStack *pTagPtr)
{
   pPrevTagPtr=pTagPtr;
return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetCurTag(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag!=NULL) *piCurTag=iCurrentTag;
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if((iCurrentTag==C_Nul) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::SetCurTag(/* enum XmlDictChars */ KpChar iCurTag)
{
   iCurrentTag=iCurTag;
return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetPrevTag(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;
TvXmlTagStack *prev_entry;

   retc=GetPrevTagPtr(&prev_entry);
   if((prev_entry==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=prev_entry->GetCurTag(piCurTag);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetFreeTextAvail(bool *pbFrTxAv)
{
HRESULT retc=S_OK;

   if(pbFrTxAv!=NULL) *pbFrTxAv=bFreeTextAvail;
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::SetFreeTextAvail(bool bFrTxAv)
{
   bFreeTextAvail=bFrTxAv;
return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetPutClose(bool *pbPutCloseNeeded)
{
HRESULT retc=S_OK;

   if(pbPutCloseNeeded!=NULL) *pbPutCloseNeeded=bPutClose;
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::SetPutClose(bool bPutCloseNeeded)
{
   bPutClose=bPutCloseNeeded;
return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetOpen(bool *pbOpenFl)
{
HRESULT retc=S_OK;

   if(pbOpenFl!=NULL) *pbOpenFl=bOpen;
   else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::SetOpen(bool bOpenFl)
{
   bOpen=bOpenFl;
return(S_OK);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetParalPtr(TvXmlTagStack **ppParPtr)
{
HRESULT retc=S_OK;

   if(ppParPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *ppParPtr=pParalelTagPtr;

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlTagStack::GetIndent(int *piIndnt)
{
HRESULT retc=S_OK;

   if(piIndnt==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piIndnt=iIndent;

return(retc);
}


HRESULT TvXmlTagStack::SetOutFl(bool bOutFlag)
{
   bOutFl=bOutFlag;
return(S_OK);
}


HRESULT TvXmlTagStack::GetOutFl(bool *pbOutFlag)
{
   *pbOutFlag=bOutFl;
return(S_OK);
}


//===================================== free TvXmlTagStack functions
// --------------------------------------------------
HRESULT PushTag
(
TvXmlTagStack **ppStackTop,
KpChar iCurTag,
TvXmlTagStack *pParalTag,
int iIndnt
)
{
HRESULT retc=S_OK;
TvXmlTagStack *tag_ptr = NULL;

   KP_ASSERT(ppStackTop != NULL, E_INVALIDARG, null, True)

   KP_NEW(tag_ptr, TvXmlTagStack(*ppStackTop, iCurTag, pParalTag, iIndnt));
   if(tag_ptr!=NULL) *ppStackTop = tag_ptr;

return(retc);
}


// --------------------------------------------------
HRESULT PopTag(TvXmlTagStack **ppStackTop, KpChar *piCurTag)
{
HRESULT retc=S_OK;
HRESULT retc0;
TvXmlTagStack *tag_ptr;

   KP_ASSERT(ppStackTop != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(*ppStackTop != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      retc=GetStackTag(*ppStackTop, 0, piCurTag);
//    if(*piCurTag==C_Nul)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      retc0=(*ppStackTop)->GetPrevTagPtr(&tag_ptr);
      if(SUCCEEDED(retc)) retc=retc0;
      if(!SUCCEEDED(retc0)) tag_ptr=NULL;

      if((tag_ptr==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc0)) retc0=(*ppStackTop)->SetPrevTagPtr(NULL);
         if(SUCCEEDED(retc)) retc=retc0;

         KP_DELETE(*ppStackTop);
         *ppStackTop=tag_ptr;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TestTagStack(TvXmlTagStack *pStackTop, KpChar iChTag, bool *pbTagPres)
{
HRESULT retc=S_OK;
TvXmlTagStack *tag_ptr;
KpChar tag;

   *pbTagPres=False;

   tag_ptr=pStackTop;
   while((tag_ptr!=NULL) && (!*pbTagPres) && SUCCEEDED(retc))
   {
      retc=tag_ptr->GetCurTag(&tag);
      if(SUCCEEDED(retc))
      {
         *pbTagPres=(tag==iChTag);
         retc=tag_ptr->GetPrevTagPtr(&tag_ptr);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT GetGroupCount(TvXmlTagStack *pStackTop, int *piGrCnt, const KpChar *iazXmlGrTagsPtr)
{
HRESULT retc=S_OK;
TvXmlTagStack *tag_ptr;
KpChar tag;

   *piGrCnt=0;

   tag_ptr=pStackTop;
   while((tag_ptr!=NULL) && SUCCEEDED(retc))
   {
      retc=tag_ptr->GetCurTag(&tag);
      if(SUCCEEDED(retc))
      {
         if(TvKpStrChr(iazXmlGrTagsPtr, tag)!=NULL) (*piGrCnt)++;
         retc=tag_ptr->GetPrevTagPtr(&tag_ptr);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT GetGroupCountSpec(TvXmlTagStack *pStackTop, KpChar iGrTag, int *pGrCnt, const KpChar *iazXmlGrTagsPtr)
{
HRESULT retc=S_OK;
TvXmlTagStack *st_ptr;
KpChar tag;

   *pGrCnt=0;

// look for stack pointer of iGrTag
   st_ptr=pStackTop;
   while((st_ptr!=NULL) && SUCCEEDED(retc))
   {
      retc=st_ptr->GetCurTag(&tag);
      if(tag==iGrTag) break;
      else
         if(SUCCEEDED(retc))
            retc=st_ptr->GetPrevTagPtr(&st_ptr);
   }

   if((st_ptr!=NULL) && SUCCEEDED(retc))
   {
      retc=st_ptr->GetPrevTagPtr(&st_ptr);
      if(SUCCEEDED(retc)) retc=GetGroupCount(st_ptr, pGrCnt, iazXmlGrTagsPtr);
   }
// else retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT RemoveTagFromStack(TvXmlTagStack **ppStackTop, KpChar iChTag)
{
HRESULT retc=S_OK;
TvXmlTagStack *st_ptr;
TvXmlTagStack *prev_ptr;
TvXmlTagStack *prev_prev_ptr;
bool found;
KpChar tag_tmp;

   prev_prev_ptr=prev_ptr=st_ptr=(*ppStackTop);

   found=False;
   while(!found && (st_ptr!=NULL) && SUCCEEDED(retc))
   {
      retc=st_ptr->GetCurTag(&tag_tmp);
      found=((tag_tmp==iChTag) && SUCCEEDED(retc));

      if(SUCCEEDED(retc))
      {
         prev_prev_ptr=prev_ptr;
         prev_ptr=st_ptr;
         retc=st_ptr->GetPrevTagPtr(&st_ptr);
      }
   }

   if(found && SUCCEEDED(retc))
   {
      if(prev_prev_ptr!=prev_ptr) retc=prev_prev_ptr->SetPrevTagPtr(st_ptr);
      else *ppStackTop=st_ptr;
   }
   else
      if(SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT GetStackTag(TvXmlTagStack *pStackTop, int iLev, KpChar *piTag)
{
HRESULT retc=S_OK;
TvXmlTagStack *st_ptr;
int ii;

   *piTag=C_Nul;

   st_ptr=pStackTop;
   for(ii=0; (ii<iLev) && (st_ptr!=NULL) && SUCCEEDED(retc); ii++)
      retc=st_ptr->GetPrevTagPtr(&st_ptr);

   if((st_ptr!=NULL) && SUCCEEDED(retc))
      retc=st_ptr->GetCurTag(piTag);
// else
//    if(SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

return(retc);

}


