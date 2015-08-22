// ==================================================
// kptree.cpp
// realization of KpTreeEntry
//


// ======================================= definitions
#include "envir.h"

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvxml.h"



// ========================================
// ----------------------
KpTreeEntry::KpTreeEntry(void)
{
   Constructor("", 1, NULL);
}


// ----------------------
KpTreeEntry::KpTreeEntry(KpTreeEntry *pFath)
{
   Constructor("", 1, pFath);
}


// ----------------------
KpTreeEntry::KpTreeEntry(const void *lpRecord, int iSize, KpTreeEntry *pFath, KpRecType iRecType)
{
   Constructor(lpRecord, iSize, pFath, iRecType);
}


// ----------------------
KpTreeEntry::KpTreeEntry(const unsigned char *lpszString, KpTreeEntry *pFath)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   KP_ASSERT(lpszString != null, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = Constructor(lpszString, strlen(lpszString) + 1, pFath, KpRecType_Text);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------
KpTreeEntry::KpTreeEntry(const char *lpszString, KpTreeEntry *pFath)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   KP_ASSERT(lpszString != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = Constructor(lpszString, strlen(lpszString) + 1, pFath, KpRecType_Text);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------
KpTreeEntry::KpTreeEntry(const KpChar *iazKpStr, KpTreeEntry *pFath)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   KP_ASSERT(iazKpStr != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = Constructor(iazKpStr, (TvKpStrLen(iazKpStr) + 1) * sizeof(*iazKpStr), pFath, KpRecType_KpText);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------
HRESULT KpTreeEntry::Constructor(const void *lpRecord, int iSize, KpTreeEntry *pFath, KpRecType iRecType)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   m_lpRecord = NULL;
   m_iRecSize = 0;
   m_iRecType = iRecType;

   m_pFirstChild = NULL;
   m_pPrevBrother = NULL;
   m_pNextBrother = NULL;
// m_pFather = NULL;
   m_pFather = pFath;

   m_iStatus = KpNodeVisible | KpNodeHasChildren | KpNodeExpanded; // KpHighChildlessNode;

   if(lpRecord == NULL)
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_iRecSize = iSize + 1;
// PutLogMessage_("KpTreeEntry::Constructor() 1 %d", m_iRecSize)
      KP_NEWA(m_lpRecord, unsigned char, m_iRecSize);
// PutLogMessage_("KpTreeEntry::Constructor() 2 %x", m_lpRecord)

      if(SUCCEEDED(retc)) memcpy(m_lpRecord, lpRecord, m_iRecSize - 1);

// PutLogMessage_("KpTreeEntry::Constructor() 3")

      if(SUCCEEDED(retc)) m_lpRecord[m_iRecSize - 1] = Nul;
// PutLogMessage_("KpTreeEntry::Constructor() 4")
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::GetOpenResult(void) const
{
return(m_lhOpenResult);
}


// ----------------------
KpTreeEntry::~KpTreeEntry()
{
HRESULT retc = S_OK;
KpTreeEntry *next_br = NULL;

// while(m_pFirstChild && SUCCEEDED(retc))
// {
//    retc=m_pFirstChild->GetNextBrother(&next_br);
////    if(SUCCEEDED(retc)) retc=pFirstChild->SetNextBrother(NULL);
//    KP_DELETE(m_pFirstChild);
//    if(next_br) next_br->SetPrevBrother(NULL);
//    if(SUCCEEDED(retc)) retc=SetFirstChild(next_br);
// }

// PutLogMessage_("KpTreeEntry::~KpTreeEntry() 1");
   while((m_pNextBrother != NULL) && SUCCEEDED(retc))
   {
      next_br = NULL;
      retc = m_pNextBrother->GetNextBrother(&next_br);
      if(SUCCEEDED(retc)) retc = m_pNextBrother->SetNextBrother(NULL);
      if(SUCCEEDED(retc)) retc = m_pNextBrother->SetPrevBrother(NULL);

// PutLogMessage_("KpTreeEntry::~KpTreeEntry() 2");
      if(SUCCEEDED(retc)) KP_DELETE(m_pNextBrother);
      if((next_br != NULL) && SUCCEEDED(retc)) retc = next_br->SetPrevBrother(this);
      if(SUCCEEDED(retc)) retc = SetNextBrother(next_br);
   }

   KP_DELETE(m_pFirstChild);

	KP_DELETEA(m_lpRecord);
}


// ----------------------
HRESULT KpTreeEntry::PutToEnd(const void *lpRecord, int iSize, KpRecType iRecType)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_entry=this;
KpTreeEntry *next_entry;

   if(SUCCEEDED(retc)) do
   {
//    retc = cur_entry->GetFirstChild(&next_entry);
      next_entry = cur_entry->m_pFirstChild;

      if((next_entry!=NULL) && SUCCEEDED(retc)) cur_entry=next_entry;
   } while((next_entry!=NULL) && SUCCEEDED(retc));

   KP_NEWO(next_entry, KpTreeEntry(lpRecord, iSize, cur_entry, iRecType));
   if(FAILED(retc)) KP_DELETE(next_entry);

// if(next_entry && SUCCEEDED(retc)) retc=next_entry->SetFather(cur_entry);
   if(SUCCEEDED(retc)) retc=cur_entry->SetFirstChild(next_entry);

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::PutToEnd(const unsigned char *lpszString)
{
HRESULT retc = S_OK;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=PutToEnd(lpszString, strlen(lpszString)+1, KpRecType_Text);

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::PutToEnd(const char *lpszString)
{
HRESULT retc = S_OK;

   if(lpszString==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=PutToEnd(lpszString, strlen(lpszString)+1, KpRecType_Text);

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::PutToEnd(const KpChar *iazKpStr)
{
HRESULT retc = S_OK;

   KP_ASSERT(iazKpStr != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = PutToEnd(iazKpStr, (TvKpStrLen(iazKpStr) + 1) * sizeof(*iazKpStr), KpRecType_KpText);

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::GetFather(KpTreeEntry **ppFath) const
{
HRESULT retc=S_OK;

   if(ppFath==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppFath=m_pFather;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::SetFather0(KpTreeEntry *pFath)
{
HRESULT retc=S_OK;

   m_pFather=pFath;

// recursion
   if(m_pNextBrother!=NULL) retc=m_pNextBrother->SetFather0(pFath);

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::SetFather(KpTreeEntry *pFath)
{
HRESULT retc=S_OK;

// if((pFath==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((m_pPrevBrother!=NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=SetFather0(pFath);

return(retc);
}


//-----------------------------------
#if FALSE
HRESULT KpTreeEntry::GetFirstChild(KpTreeEntry **ppChild) const
{
HRESULT retc=S_OK;

   if(ppChild==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppChild=m_pFirstChild;

return(retc);
}
#endif


//-----------------------------------
// former HRESULT KpTreeEntry::SetNextEntry(RecListEntry *pNextEntry)
HRESULT KpTreeEntry::SetFirstChild(KpTreeEntry *pChild)
{
HRESULT retc=S_OK;
KpTreeEntry *father=NULL;
KpTreeEntry *prev_brother=NULL;

// if(pChild==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

// if((m_pFirstChild!=NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if((pChild!=NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=pChild->GetFather(&father);
      if((father!=this) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pChild->GetPrevBrother(&prev_brother);
      if((prev_brother!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) m_pFirstChild=pChild;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::ConnectChild(KpTreeEntry *pChild)
{
HRESULT retc=S_OK;

   if((pChild != NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = pChild->SetPrevBrother(NULL);
      if(SUCCEEDED(retc)) retc = pChild->SetFather(this);
   }

   if(SUCCEEDED(retc)) retc = SetFirstChild(pChild);

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::GetPrevBrother(KpTreeEntry **ppPrevBr) const
{
HRESULT retc=S_OK;

   if(ppPrevBr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppPrevBr=m_pPrevBrother;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::SetPrevBrother(KpTreeEntry *pPrevBr)
{
HRESULT retc=S_OK;
KpTreeEntry *father=NULL;

   if((pPrevBr!=NULL) && SUCCEEDED(retc))
   {
      retc=pPrevBr->GetFather(&father);
      if((father!=m_pFather) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) m_pPrevBrother=pPrevBr;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::GetNextBrother(KpTreeEntry **ppNextBr) const
{
HRESULT retc=S_OK;

   if(ppNextBr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *ppNextBr=m_pNextBrother;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::SetNextBrother(KpTreeEntry *pNextBr)
{
HRESULT retc=S_OK;
KpTreeEntry *father=NULL;

   if((pNextBr!=NULL) && SUCCEEDED(retc))
   {
      retc=pNextBr->GetFather(&father);
      if((father!=m_pFather) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) m_pNextBrother=pNextBr;

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::ConnectBrother(KpTreeEntry *pNextBr)
{
HRESULT retc=S_OK;

// if((pNextBr==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if((m_pNextBrother != NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);


   if((pNextBr!=NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=pNextBr->SetPrevBrother(NULL);
      if(SUCCEEDED(retc)) retc=pNextBr->SetFather(m_pFather);
      if(SUCCEEDED(retc)) retc=pNextBr->SetPrevBrother(this);
   }

   if(SUCCEEDED(retc)) retc=SetNextBrother(pNextBr);

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::InsertChild(KpTreeEntry *pChild)
{
HRESULT retc=S_OK;
KpTreeEntry *prev_brother;
KpTreeEntry *next_brother;

   if(pChild==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pChild->SetFather(this);

   if(SUCCEEDED(retc))
   {
      retc=pChild->GetPrevBrother(&prev_brother);
      if(SUCCEEDED(retc)) retc=pChild->GetNextBrother(&next_brother);
      if(((prev_brother!=NULL) || (next_brother!=NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) retc=pChild->ConnectBrother(m_pFirstChild);
   if(SUCCEEDED(retc)) retc=ConnectChild(pChild);

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::AppendChild(KpTreeEntry *pChild)
{
HRESULT retc=S_OK;
KpTreeEntry *prev_brother;
KpTreeEntry *cur_brother;
KpTreeEntry *next_brother;

   KP_ASSERT(pChild != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = pChild->SetFather(this);

   if(SUCCEEDED(retc))
   {
      retc = pChild->GetPrevBrother(&prev_brother);
      if(SUCCEEDED(retc)) retc = pChild->GetNextBrother(&next_brother);
      if(((prev_brother != NULL) || (next_brother != NULL)) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      if(m_pFirstChild == NULL) retc = ConnectChild(pChild);
      else
      {
         next_brother = m_pFirstChild;
         do
         {
            cur_brother = next_brother;
            retc = cur_brother->GetNextBrother(&next_brother);
         } while((next_brother != NULL) && SUCCEEDED(retc));

         if(SUCCEEDED(retc)) retc = cur_brother->ConnectBrother(pChild);
      }
   }

return(retc);
}


//-----------------------------------
HRESULT KpTreeEntry::AppendBrother(KpTreeEntry *pBrother)
{
HRESULT retc=S_OK;
KpTreeEntry *prev_brother;
KpTreeEntry *cur_brother;
KpTreeEntry *next_brother;

   if(pBrother==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) retc=pBrother->SetFather(m_pFather); // nereikia, nustatys ConnectBrother()

   if(SUCCEEDED(retc))
   {
      retc=pBrother->GetPrevBrother(&prev_brother);
      if(SUCCEEDED(retc)) retc=pBrother->GetNextBrother(&next_brother);
      if(((prev_brother!=NULL) || (next_brother!=NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      next_brother=this;
      do
      {
         cur_brother=next_brother;
         retc=cur_brother->GetNextBrother(&next_brother);
      } while((next_brother!=NULL) && SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc=cur_brother->ConnectBrother(pBrother);
   }

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::SearchTreeEntry(const void *pPattern, CompareFuncPtr pfCompare, KpTreeEntry **ppEntryPtr, KpTreeEntry **ppFatherPtr)
{
HRESULT retc=S_OK;
KpTreeEntry *list_ptr = NULL;

   if((ppEntryPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(ppFatherPtr && SUCCEEDED(retc)) *ppFatherPtr=NULL;

   if(SUCCEEDED(retc))
   {
      *ppEntryPtr = NULL;
      list_ptr = this;
      while((list_ptr != NULL) && SUCCEEDED(retc))
      {
         if(pfCompare(list_ptr->GetValue(), pPattern)==0)
         {
            *ppEntryPtr = list_ptr;
            break;
         }
         if(ppFatherPtr) *ppFatherPtr = list_ptr;

         if((list_ptr->m_pFirstChild != NULL) && SUCCEEDED(retc)) retc = list_ptr->m_pFirstChild->SearchTreeEntry(pPattern, pfCompare, ppEntryPtr, ppFatherPtr);
         if((*ppEntryPtr != NULL) && SUCCEEDED(retc)) break;

         if(SUCCEEDED(retc)) list_ptr = list_ptr->m_pNextBrother;
      }
   }

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::GetEntryPtr(int *piSel, KpTreeEntry **ppEntryPtr, int iLevel /* KpWndType iWndType */, const KpTreeEntry *pCurGrandFather)
{
HRESULT retc=S_OK;
KpTreeEntry *loop_brother;
KpTreeEntry *first_child;
// KpNodeStatus status = KpHighLevelNode;
int status = 0;

   if(
      (
         (ppEntryPtr==NULL) ||
         (piSel==NULL) ||
//       ((iWndType!=TYP_ListBoxTree) && (iWndType!=TYP_ListBoxTreeInverted))
         (iLevel<0) || (iLevel>=KpNodeNumOfLevels)
       ) &&
       SUCCEEDED(retc)
      )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *ppEntryPtr = NULL;

   loop_brother=this;
   if(loop_brother && SUCCEEDED(retc)) do
   {
//    status = (KpNodeStatus)(loop_brother->m_iStatus & (~KpLowLevelNode));
      status = loop_brother->m_iStatus >> (KpNodeLevelShift * iLevel);

      if(
#if FALSE
         (
            ((iWndType==TYP_ListBoxTree) && (!(loop_brother->m_iStatus & KpLowLevelNode))) ||
            (
               (iWndType==TYP_ListBoxTreeInverted) &&
               (
                  (loop_brother->m_iStatus & KpLowLevelNode) ||
                  (loop_brother == this)
               )
            )
         ) &&
#else
//       ((status & KpNodeVisible) != 0) &&
#endif
         SUCCEEDED(retc)
        )
      {
#if FALSE
         if(
            ((iWndType==TYP_ListBoxTree) && (!(loop_brother->m_iStatus & KpLowLevelNode))) ||
            ((iWndType==TYP_ListBoxTreeInverted) && (loop_brother->m_iStatus & KpLowLevelNode))
           )
#else
         if((status & KpNodeVisible) != 0)
#endif
            (*piSel)--;

//       if((*piSel)-- == 0)
         if(*piSel == (-1))
         {
            *ppEntryPtr = loop_brother;
            break;
         }
         else
         {
// recursion through children of children
            if(
            /* (status==KpHighExpandedNode) */ (status & KpNodeExpanded) &&
               (((status & KpNodeVisible) != 0) || (loop_brother==pCurGrandFather)) &&
               SUCCEEDED(retc)
              )
            {
//             retc = loop_brother->GetFirstChild(&first_child);
               first_child = loop_brother->m_pFirstChild;

               if((first_child!=NULL) && SUCCEEDED(retc))
                  retc=first_child->GetEntryPtr(piSel, ppEntryPtr, iLevel /* iWndType */, pCurGrandFather);
            }
         }
      }

      if(SUCCEEDED(retc))
      {
         if(loop_brother==pCurGrandFather) loop_brother = NULL;
         else retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);
      }

   } while(loop_brother && (*piSel>=0) && SUCCEEDED(retc));

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->GetEntryPtr(piSel, ppEntryPtr, iLevel /* iWndType */, pCurGrandFather);

return(retc);
}

#if FALSE
HRESULT KpTreeEntry::GetEntryPtr(int iSel, KpTreeEntry **ppEntryPtr, KpTreeEntry **ppFatherPtr)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_ptr;
KpTreeEntry *next_entry;
int ii;

   if(ppEntryPtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(ppFatherPtr) *ppFatherPtr=NULL;

   if(SUCCEEDED(retc))
   {
      cur_ptr=this;
      for(ii=0; (ii<iSel) && (cur_ptr!=NULL) && SUCCEEDED(retc); ii++)
      {
         if(ppFatherPtr) *ppFatherPtr=cur_ptr;

//       retc = cur_ptr->GetFirstChild(&next_entry);
         next_entry = cur_ptr->m_pFirstChild;

         if(SUCCEEDED(retc)) cur_ptr = next_entry;
      }

      *ppEntryPtr=cur_ptr;
   }

return(retc);
}
#endif

// ----------------------
HRESULT KpTreeEntry::DeleteChild(void)
{
HRESULT retc=S_OK;
KpTreeEntry *child_child_ptr=NULL;

   if(m_pFirstChild)
   {
//    if(SUCCEEDED(retc)) retc = m_pFirstChild->GetFirstChild(&child_child_ptr);
      if(SUCCEEDED(retc)) child_child_ptr = m_pFirstChild->m_pFirstChild;

      if(SUCCEEDED(retc)) retc=m_pFirstChild->SetFirstChild(NULL);
      if(SUCCEEDED(retc))
      {
         KP_DELETE(m_pFirstChild);
         m_pFirstChild = child_child_ptr;
      }
      if(m_pFirstChild && SUCCEEDED(retc)) retc = m_pFirstChild->SetFather(this);
   }

return(retc);
}


// ----------------------
HRESULT DeleteKpTreeEntry(KpTreeEntry *pEntryPtr)
{
HRESULT retc = S_OK;

   KP_ASSERT(pEntryPtr != NULL, E_POINTER, null, True);

KpTreeEntry *next_brother = NULL;
   if(SUCCEEDED(retc)) retc = pEntryPtr->GetNextBrother(&next_brother);

KpTreeEntry *prev_brother = NULL;
   if(SUCCEEDED(retc)) retc = pEntryPtr->GetPrevBrother(&prev_brother);

KpTreeEntry *father = NULL;
   if(SUCCEEDED(retc)) retc = pEntryPtr->GetFather(&father);

   if((next_brother != NULL) && SUCCEEDED(retc)) retc = next_brother->SetPrevBrother(prev_brother);
   if((prev_brother != NULL) && SUCCEEDED(retc)) retc = prev_brother->SetNextBrother(next_brother);

// pirmas vaikas – nustatom naujà tëvo pirmà vaikà
   if((prev_brother == NULL) && (father != NULL) && SUCCEEDED(retc)) retc = father->SetFirstChild(next_brother);

   if(SUCCEEDED(retc)) retc = pEntryPtr->SetNextBrother(NULL);
   if(SUCCEEDED(retc)) retc = pEntryPtr->SetPrevBrother(NULL);
   KP_DELETE(pEntryPtr);

return(retc);
}


// ----------------------
KpRecType KpTreeEntry::GetRecType(void) const
{
return(m_iRecType);
}


// ----------------------
void *KpTreeEntry::GetValue(void) const
{
return(m_lpRecord);
}


// ----------------------
int KpTreeEntry::GetValSize(void) const
{
int size = m_iRecSize;
   
   if(size > 0) size--;
    
return(size);
}


// ----------------------
HRESULT KpTreeEntry::SetValue(const void *pValue, int iValSize)
{
HRESULT retc=S_OK;

   KP_ASSERT(pValue != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(iValSize >= 0, E_INVALIDARG, null, True);
   
   KP_ASSERT(iValSize < m_iRecSize, KP_E_BUFFER_OVERFLOW, null, True); // vienas baitas gale nuliui

   if(SUCCEEDED(retc))
   {
      memcpy(m_lpRecord, pValue, iValSize);
      m_lpRecord[iValSize] = Nul;
   }

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::SetNewValue(const void *pValue, int iValSize)
{
HRESULT retc=S_OK;

   if(pValue == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      KP_DELETEA(m_lpRecord);

      m_iRecSize = iValSize + 1;
      KP_NEWA(m_lpRecord, unsigned char, m_iRecSize);

      if(FAILED(retc)) m_iRecSize = 0;
   }

   if(SUCCEEDED(retc)) retc = SetValue(pValue, iValSize);

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::SetNewValue(const unsigned char *lpszValue)
{
HRESULT retc=S_OK;

   if(lpszValue==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = SetNewValue(lpszValue, strlen(lpszValue) + 1);

   if(SUCCEEDED(retc)) m_iRecType = KpRecType_Text;
   else m_iRecType = KpRecType_Unknown;

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::SetNewValue(const KpTextBmp *pValue)
{
HRESULT retc=S_OK;

   if(pValue==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = SetNewValue(pValue, sizeof(KpTextBmp));

   if(SUCCEEDED(retc)) m_iRecType = KpRecType_TextBmp;
   else m_iRecType = KpRecType_Unknown;

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::SetNewValue(const KpBmpBmp *pValue)
{
HRESULT retc=S_OK;

   if(pValue==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = SetNewValue(pValue, sizeof(KpTextBmp));

   if(SUCCEEDED(retc)) m_iRecType = KpRecType_BmpBmp;
   else m_iRecType = KpRecType_Unknown;

return(retc);
}


// ----------------------
HRESULT KpTreeEntry::CountEntries(int *piCnt,  int iLevel /* KpWndType iWndType */, KpTreeEntry *pCurGrandFather)
{
HRESULT retc=S_OK;
KpTreeEntry *loop_brother;
KpTreeEntry *first_child;
// KpNodeStatus status = KpHighLevelNode;
int status = 0;

   if(
      (
         (piCnt==NULL) ||
//       ((iWndType!=TYP_ListBoxTree) && (iWndType!=TYP_ListBoxTreeInverted))
         (iLevel<0) || (iLevel>=KpNodeNumOfLevels)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   loop_brother=this;
   if(loop_brother && SUCCEEDED(retc)) do
   {
//    status = (KpNodeStatus)(loop_brother->m_iStatus & (~KpLowLevelNode));
      status = loop_brother->m_iStatus >> (KpNodeLevelShift * iLevel);

      if(
#if FALSE
         (
            ((iWndType==TYP_ListBoxTree) && (!(loop_brother->m_iStatus & KpLowLevelNode))) ||
            (
               (iWndType==TYP_ListBoxTreeInverted) &&
               (
                  (loop_brother->m_iStatus & KpLowLevelNode) ||
                  (loop_brother == this)
               )
            )
         ) &&
#else
//       ((status & KpNodeVisible) != 0) &&
#endif
         SUCCEEDED(retc)
        )
      {
#if FALSE
         if(
            ((iWndType==TYP_ListBoxTree) && (!(loop_brother->m_iStatus & KpLowLevelNode))) ||
            ((iWndType==TYP_ListBoxTreeInverted) && (loop_brother->m_iStatus & KpLowLevelNode))
           )
#else
         if((status & KpNodeVisible) != 0)
#endif
            (*piCnt)++;

// recursion through children of children
         if(
         /* (status==KpHighExpandedNode) */ (status & KpNodeExpanded) &&
            (((status & KpNodeVisible) != 0) || (loop_brother==pCurGrandFather)) &&
            SUCCEEDED(retc)
           )
         {
//          retc = loop_brother->GetFirstChild(&first_child);
            first_child = loop_brother->m_pFirstChild;

            if((first_child!=NULL) && SUCCEEDED(retc))
               retc=first_child->CountEntries(piCnt, iLevel /* iWndType */, pCurGrandFather);
         }
      }

      if(SUCCEEDED(retc))
      {
         if(loop_brother==pCurGrandFather) loop_brother = NULL;
         else retc=loop_brother->GetNextBrother(&loop_brother);
      }

   } while(loop_brother && SUCCEEDED(retc));

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->CountEntries(piCnt, iLevel /* iWndType */, pCurGrandFather);

return(retc);
}

#if FALSE
int KpTreeEntry::CountEntries(void)
{
HRESULT retc=S_OK;
int cnt;
KpTreeEntry *next;
KpTreeEntry *next_entry;

   cnt=1;
   next=m_pFirstChild;

   while(next && SUCCEEDED(retc))
   {
      cnt++;

//    retc = next->GetFirstChild(&next_entry);
      next_entry = next->m_pFirstChild;

      if(SUCCEEDED(retc)) next = next_entry;
   }

return(cnt);
}
#endif

// ----------------------
#if FALSE
int CountRecListEntries(RecListEntry *list_ptr)
{
int cnt;
RecListEntry *cur_entry;

   cnt=0;
   cur_entry=list_ptr;

   while(cur_entry)
   {
      cnt++;
      cur_entry=cur_entry->GetNextEntry();
   }

return(cnt);
}
#endif


// ----------------------
HRESULT KpTreeEntry::Sort(CompareFuncPtr pfCompare)
{
HRESULT retc=S_OK;
KpTreeEntry *pt1;
KpTreeEntry *pt2;
KpTreeEntry *next_entry;

   pt1=this;
   while((pt1!=NULL) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = pt1->GetFirstChild(&pt2);
      if(SUCCEEDED(retc)) pt2 = pt1->m_pFirstChild;

      while((pt2!=NULL) && SUCCEEDED(retc))
      {
         if((*pfCompare)(pt1->GetValue(), pt2->GetValue())>0)
            retc=ChangeKpTreeNodes(pt1, pt2);

//       if(SUCCEEDED(retc)) retc = pt2->GetFirstChild(&next_entry);
         if(SUCCEEDED(retc)) next_entry = pt2->m_pFirstChild;

         if(SUCCEEDED(retc)) pt2 = next_entry;
      }
//    if(SUCCEEDED(retc)) retc = pt1->GetFirstChild(&next_entry);
      if(SUCCEEDED(retc)) next_entry = pt1->m_pFirstChild;

      if(SUCCEEDED(retc)) pt1 = next_entry;
   }

return(retc);
}


HRESULT KpTreeEntry::SortPtr(ComparePtrFuncPtr pfCompare)
{
HRESULT retc=S_OK;
KpTreeEntry *pt1;
KpTreeEntry *pt2;
KpTreeEntry *next_entry;
void *val_ptr_1;
void *val_ptr_2;

   pt1=this;
   while((pt1!=NULL) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = pt1->GetFirstChild(&pt2);
      if(SUCCEEDED(retc)) pt2 = pt1->m_pFirstChild;

      while((pt2!=NULL) && SUCCEEDED(retc))
      {
         val_ptr_1 = pt1->GetValue();
         val_ptr_2 = pt2->GetValue();
         if((*pfCompare)(&val_ptr_1, &val_ptr_2)>0)
            retc=ChangeKpTreeNodes(pt1, pt2);

//       if(SUCCEEDED(retc)) retc = pt2->GetFirstChild(&next_entry);
         if(SUCCEEDED(retc)) next_entry = pt2->m_pFirstChild;

         if(SUCCEEDED(retc)) pt2 = next_entry;
      }
//    if(SUCCEEDED(retc)) retc = pt1->GetFirstChild(&next_entry);
      if(SUCCEEDED(retc)) next_entry = pt1->m_pFirstChild;

      if(SUCCEEDED(retc)) pt1 = next_entry;
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpTreeEntry::TestNodeLoop(KpTreeEntry **apNodesArray, int *piNumOfNodes)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_node;
KpTreeEntry *loop_brother;
int ii;

// if(test_cnt==6301)
// test_cnt=6301;
// if(iNumOfNodes==29000)
// iNumOfNodes=29000;

// printf("_____ %6d %6d %12x\n", test_cnt++, iNumOfNodes, this);

   if(((apNodesArray == NULL) || (piNumOfNodes == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      for(ii=0; ((ii < *piNumOfNodes) && SUCCEEDED(retc)); ii++)
      {
         if(apNodesArray[ii]==loop_brother)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      }

      if((*piNumOfNodes>=XL_ND_MaxNumOfNodes) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) apNodesArray[(*piNumOfNodes)++]=loop_brother;

//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild(&cur_node);
      if(SUCCEEDED(retc)) cur_node = loop_brother->m_pFirstChild;

// recursion through children of children first
      if((cur_node!=NULL) && SUCCEEDED(retc)) retc=cur_node->TestNodeLoop(apNodesArray, piNumOfNodes);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->TestNodeLoop();

return(retc);
}


// --------------------------------------------------
HRESULT KpTreeEntry::TestNode(void)
{
HRESULT retc=S_OK;
int num_of_nodes = 0;
KpTreeEntry **nodes_array = NULL;

// iNumOfNodes=0;

   KP_NEWA(nodes_array /* iaNodesArray */, KpTreeEntry *, XL_ND_MaxNumOfNodes);

   if(SUCCEEDED(retc)) retc = TestNodeLoop(nodes_array, &num_of_nodes);

   KP_DELETEA(nodes_array);

return(retc);
}


// --------------------------------------------------
HRESULT KpTreeEntry::FormListBox(HWND hListBox)
{
HRESULT retc=S_OK;
KpTreeEntry *loop_brother = NULL;
KpTreeEntry *first_child = NULL;
const unsigned char *cur_str;
int retv;

   loop_brother=this;
   while(loop_brother && SUCCEEDED(retc))
   {
      cur_str=(const unsigned char *)loop_brother->GetValue();
      if(cur_str==NULL) cur_str = (const unsigned char *)"";

      retv=SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)cur_str);
      switch(retv)
      {
      case CB_ERR:
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      case CB_ERRSPACE:
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      }

// recursion through children of children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) first_child = loop_brother->m_pFirstChild;

      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->FormListBox(hListBox);

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->FormListBox(hListBox);

return(retc);
}


// --------------------------------------------------
HRESULT KpTreeEntry::InitNodeStatus(void)
{
HRESULT retc = S_OK;
KpTreeEntry *first_child=NULL;
KpTreeEntry *loop_brother=NULL;

// loop on brothers
   loop_brother=this;
   while(loop_brother && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) first_child = loop_brother->m_pFirstChild;

      if(SUCCEEDED(retc)) loop_brother->m_iStatus = 0;

#if FALSE
      if(SUCCEEDED(retc))
      {
         if(first_child) loop_brother->m_iStatus = KpHighExpandedNode;
         else loop_brother->m_iStatus = KpHighChildlessNode;
      }
#else
      if(SUCCEEDED(retc)) for(int ii=0; ii<KpNodeNumOfLevels; ii++)
      {
         loop_brother->m_iStatus |= KpNodeVisible << (KpNodeLevelShift * ii);
         if(first_child) loop_brother->m_iStatus |= (KpNodeHasChildren | KpNodeExpanded) << (KpNodeLevelShift * ii);
      }
#endif

// recursion on children
      if(first_child && SUCCEEDED(retc)) retc=first_child->InitNodeStatus();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpTreeEntry::Deselect(void)
{
HRESULT retc = S_OK;
KpTreeEntry *first_child=NULL;
KpTreeEntry *loop_brother=NULL;

// loop on brothers
// ðiaip nereikëtø – chekboxiniai listai linijiniai (StartGrp)
   loop_brother = this;
   while(loop_brother && SUCCEEDED(retc))
   {
      KP_ASSERT(m_iRecType == KpRecType_TextChk, E_UNEXPECTED, null, True);

// recursion on children
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) first_child = loop_brother->m_pFirstChild;

      if((first_child != NULL) && SUCCEEDED(retc)) retc = first_child->Deselect();

KpTextChk *val_ptr = NULL;
      if(SUCCEEDED(retc)) val_ptr = (KpTextChk *)loop_brother->GetValue();
      KP_ASSERT(val_ptr != NULL, E_POINTER, null, True);
      KP_ASSERT(loop_brother->GetValSize() >= sizeof(KpTextChk), KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) val_ptr->m_bChecked = False;

      if(SUCCEEDED(retc)) retc = loop_brother->GetNextBrother(&loop_brother);
   }

return(retc);
}




// =======================================
// ----------------------
HRESULT ChangeKpTreeNodes(KpTreeEntry *pNode1, KpTreeEntry *pNode2)
{
HRESULT retc=S_OK;
KpTreeEntry *temp=NULL;

   if((pNode1 == NULL) || (pNode2 == NULL))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   KP_NEW(temp, KpTreeEntry(pNode1->GetValue(), pNode1->GetValSize(), NULL));
   if(SUCCEEDED(retc)) retc = temp->GetOpenResult();

// if(SUCCEEDED(retc)) retc=CopyKpTreeNode(temp, pNode1);
   if(SUCCEEDED(retc)) retc=CopyKpTreeNode(pNode1, pNode2);
   if(SUCCEEDED(retc)) retc=CopyKpTreeNode(pNode2, temp);

   KP_DELETE(temp);

return(retc);
}


// ----------------------
HRESULT CopyKpTreeNode(KpTreeEntry *pNodeDst, /* const */ KpTreeEntry *pNodeSrc)
{
HRESULT retc=S_OK;
int size;

   if((pNodeDst==NULL) || (pNodeSrc==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      size = pNodeSrc->GetValSize();
      if(size > pNodeDst->GetValSize())
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      retc=pNodeDst->SetValue(pNodeSrc->GetValue(), size);

   if(SUCCEEDED(retc))
   {
      pNodeDst->m_iRecType = pNodeSrc->m_iRecType;
      pNodeDst->m_iStatus = pNodeSrc->m_iStatus;
   }

return(retc);
}


// ----------------------
HRESULT CopyKpTreeNodeAllocate(KpTreeEntry *pNodeDst, /* const */ KpTreeEntry *pNodeSrc)
{
HRESULT retc = S_OK;
KpTreeEntry *father = NULL;

   if((pNodeDst==NULL) || (pNodeSrc==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) KP_DELETEA(pNodeDst->m_lpRecord);

   if(SUCCEEDED(retc)) retc = pNodeDst->GetFather(&father);
   if(SUCCEEDED(retc))
   {
      pNodeDst->Constructor(pNodeSrc->GetValue(), pNodeSrc->GetValSize(), father);
      retc = pNodeDst->GetOpenResult();
   }

   if(SUCCEEDED(retc))
   {
      pNodeDst->m_iRecType = pNodeSrc->m_iRecType;
      pNodeDst->m_iStatus = pNodeSrc->m_iStatus;
   }

return(retc);
}


// -----------------------------------------
KpTextChk::KpTextChk()
{
   m_lpszText[0] = Nul;
   m_iazText[0] = C_Nul;
   m_bChecked = True; // varniukë paþymëta
}


// -----------------------------------------
HRESULT CountStrListFullLength(int *piFullContLen, /* const */ KpTreeEntry *pList)
{
HRESULT retc = S_OK;

   KP_ASSERT(piFullContLen != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) *piFullContLen = 0;

KpTreeEntry *cur_node = pList;
   while((cur_node != NULL) && SUCCEEDED(retc))
   {
unsigned char *val_buf = (unsigned char *)cur_node->GetValue();
      KP_ASSERT(val_buf != null, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) *piFullContLen += strlen(val_buf);

//    if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild(&cur_node);
      if(SUCCEEDED(retc)) cur_node = cur_node->m_pFirstChild;
   }

return(retc);
}


// -----------------------------------------
HRESULT CountKpCharListFullLength(int *piFullContLen, /* const */ KpTreeEntry *pList)
{
HRESULT retc = S_OK;

   KP_ASSERT(piFullContLen != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) *piFullContLen = 0;

KpTreeEntry *cur_node = pList;
   while((cur_node != NULL) && SUCCEEDED(retc))
   {
KpChar *val_buf = (KpChar *)cur_node->GetValue();
      KP_ASSERT(val_buf != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) *piFullContLen += TvKpStrLen(val_buf);

//    if(SUCCEEDED(retc)) retc = cur_node->GetFirstChild(&cur_node);
      if(SUCCEEDED(retc)) cur_node = cur_node->m_pFirstChild;
   }

return(retc);
}
