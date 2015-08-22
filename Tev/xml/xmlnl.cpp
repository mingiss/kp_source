// ==================================================
// xmlnl.cpp
// XML dictionary entry node
// possibly local defined functions
//

// ==================================== definitions
#include "envir.h"
#include "iBshn.h"

#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <stdio.h>
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
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlsty.h"
#include "KpFileSys.h"
#include "xmln.h"


// --------------------------------------------------
HRESULT XmlNode::CreateGrpCounters(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *cur_child;
XmlTagPars *p_pars;
KpChar cur_tag;
int grp_cnt=0;
KpChar grp_tag=C_Nul;

unsigned char *val_buf = null;
   KP_NEWA(val_buf, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

unsigned char *new_val = null;
   KP_NEWA(new_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

int par_num;
bool found;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

      // recursion through children of children first
      if((cur_child!=NULL) && SUCCEEDED(retc))
         retc=cur_child->CreateGrpCounters();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);

      if(
         (
            (cur_tag==XC_CtgGroup) ||
            (cur_tag==XC_MngGroup) || (cur_tag==XC_CpdMngGroup) || (cur_tag==XC_IdMngGroup) ||
            (cur_tag==XC_MngNearGroup)
         ) &&
         SUCCEEDED(retc)
        )
      {
         if((grp_tag!=C_Nul) && (grp_tag!=cur_tag))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         found=False;
         val_buf[0]=Nul;
         if(SUCCEEDED(retc))
         {
            grp_tag=cur_tag;
            grp_cnt++;

            p_pars=NULL;
            retc=GetTagParsPtr(&p_pars);
         }
         if(SUCCEEDED(retc))
         {
            if(p_pars==NULL) found=False;
            else
            {
               retc=p_pars->SeekTextPar("num", val_buf, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
               {
                  retc=S_OK;
                  found=False;
                  val_buf[0]=Nul;
               }
               else if(SUCCEEDED(retc)) found=True;
            }
         }

// format ordinary number
         if(SUCCEEDED(retc))
         {
            switch(grp_tag)
            {
               case XC_CtgGroup:
                  FormatRoman(new_val, grp_cnt);
                  break;
               case XC_MngGroup:
               case XC_CpdMngGroup:
               case XC_IdMngGroup:
                  sprintf((char *)new_val, "%d", grp_cnt);
                  break;
               case XC_MngNearGroup:
                  new_val[0]='a'-1+grp_cnt;
                  new_val[1]=Nul;
                  break;
            }
         }

         if(SUCCEEDED(retc))
         {
            if(found)
            {
// check existing number
               if(strcmp(new_val, val_buf)!=0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
            }
            else if(SUCCEEDED(retc))
            {
// create new number
               if(p_pars==NULL)
               {
                  KP_NEWO(p_pars, XmlTagPars((const unsigned char *)"num", new_val, NULL));

                  if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(p_pars);
               }
               else retc=p_pars->AddTextPar((const unsigned char *)"num", new_val);
            }

         } // if(SUCCEEDED(retc))

      } // if(((cur_tag==XC_CtgGroup) || (cur_tag==XC_MngGroup) || ...

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

   KP_DELETEA(val_buf);
   KP_DELETEA(new_val);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::RenumCtgMng(void)
{
HRESULT retc=S_OK;
XmlNode *loop_brother;
XmlNode *first_child;
KpChar cur_tag;
int ctg_num=0;
int mng_num=0;
int cpd_mng_num=0;
int id_mng_num=0;
int mngnear_num=0;
XmlTagPars *tag_pars=NULL;
unsigned char str_buf[KP_KWD_LEN+1];

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      first_child = (XmlNode *)loop_brother->m_pFirstChild;

      // recursion through children of children first
      if((first_child!=NULL) && SUCCEEDED(retc)) retc=first_child->RenumCtgMng();

      if(SUCCEEDED(retc)) retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) switch(cur_tag)
      {
      case XC_CtgGroup:
         if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       KP_DELETE(tag_pars);

         if(((mng_num!=0) || (cpd_mng_num!=0) || (id_mng_num!=0) || (mngnear_num!=0)) &&
               SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=FormatRoman(str_buf, ++ctg_num);
         KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"num", str_buf, NULL));
         if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(tag_pars);
         tag_pars=NULL;
         break;

      case XC_MngGroup:
         if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       KP_DELETE(tag_pars);

         if(((ctg_num!=0) || (cpd_mng_num!=0) || (id_mng_num!=0) || (mngnear_num!=0)) &&
               SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"num", ++mng_num, NULL));
         if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(tag_pars);
         tag_pars=NULL;
         break;

      case XC_CpdMngGroup:
         if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       KP_DELETE(tag_pars);

         if(((ctg_num!=0) || (mng_num!=0) || (id_mng_num!=0) || (mngnear_num!=0)) &&
               SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"num", ++cpd_mng_num, NULL));
         if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(tag_pars);
         tag_pars=NULL;
         break;

      case XC_IdMngGroup:
         if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       KP_DELETE(tag_pars);

         if(((ctg_num!=0) || (mng_num!=0) || (cpd_mng_num!=0) || (mngnear_num!=0)) &&
               SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"num", ++id_mng_num, NULL));
         if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(tag_pars);
         tag_pars=NULL;
         break;

      case XC_MngNearGroup:
         if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);
         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//       KP_DELETE(tag_pars);

         if(((ctg_num!=0) || (mng_num!=0) || (cpd_mng_num!=0) || (id_mng_num!=0)) &&
               SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            mngnear_num++;
            str_buf[0]='a'+mngnear_num-1;
            str_buf[1]=Nul;

            KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"num", str_buf, NULL));
         }
         if(SUCCEEDED(retc)) retc=loop_brother->SetTagParsPtr(tag_pars);
         tag_pars=NULL;
         break;
      }

      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->RenumCtgMng(iLevel);

return(retc);
}
