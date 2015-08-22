// ==================================================
// xmlnh.cpp
// HTML file node functions
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
#include <fstream>
#include <ctype.h>
#if OsGr==MSWin
#include <windows.h>
#include <time.h>
#endif
#include <richedit.h>
#include <Richole.h>

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
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
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
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlsty.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "tvxmls.h"




//-----------------------------------
HRESULT XmlNode::CvtToBmps(const unsigned char *lpszInFileName, const unsigned char *lpszOutFileName, int *piBgrWdt, int *piBgrHgt)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
// XmlNode *prev_brother=NULL;
KpChar father_tag;
KpChar cur_tag;
XmlTagPars *tag_pars = NULL;
int par_num;
KpBmpData *bmp_pars = NULL;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char new_par_val[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char cont_str[MAX_XML_PAR_VAL_LEN + 1];
static KpChar contents[MAX_XML_PAR_VAL_LEN + 1];

static unsigned char file_disk[KP_MAX_FNAME_LEN+1];
static unsigned char file_path[KP_MAX_FNAME_LEN+1];
static unsigned char file_name[KP_MAX_FNAME_LEN+1];
static unsigned char file_type[KP_MAX_FTYPE_LEN+1];

static unsigned char src_file_name[MAX_XML_PAR_VAL_LEN + KP_MAX_FNAME_LEN + 1];
static unsigned char src_full_path[KP_MAX_FNAME_LEN+1];
static unsigned char src_full_file_name[KP_MAX_FNAME_LEN+1];

static unsigned char dst_file_name[KP_MAX_FNAME_LEN+1];
static unsigned char dst_full_path[KP_MAX_FNAME_LEN+1];
static unsigned char dst_full_file_name[KP_MAX_FNAME_LEN+1];

static unsigned char cvt_cmd[KP_MAX_FNAME_LEN*2+100];

   if(((lpszInFileName == NULL) || (lpszOutFileName == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother = this;
// while((loop_brother != NULL) && SUCCEEDED(retc))
   if((loop_brother != NULL) && SUCCEEDED(retc))
   {
// -------------------------- <body background="..."> keliam į pirmą <body> vaiką <img src="...">
      if(SUCCEEDED(retc)) retc = loop_brother->GetNodeTag(&father_tag);
      if((father_tag == HTM_TG_BODY) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = loop_brother->GetTagParsPtr(&tag_pars);
         if(SUCCEEDED(retc)) retc = tag_pars->SeekTextPar("background", src_file_name, &par_num);
         if(SUCCEEDED(retc)) retc = DeletePar(&tag_pars, par_num);
         if(SUCCEEDED(retc)) retc = loop_brother->SetTagParsPtrSimple(tag_pars);

         tag_pars = NULL;
         KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"id", (const unsigned char *)"background", NULL));
         if(SUCCEEDED(retc)) retc = tag_pars->AddTextPar((const unsigned char *)"src", src_file_name);

         KP_NEW(cur_child, XmlNode((KpChar)HTM_TG_IMG, tag_pars, NULL, NULL, (const unsigned char *)"", HTM_TG_FirstTag, plpszaHtmlTags, loop_brother));

         KP_DELETE(tag_pars);

         if(SUCCEEDED(retc)) retc = loop_brother->InsertChild(cur_child);

      } // if((father_tag == HTM_TG_BODY) && SUCCEEDED(retc))

// -------------------------- loop through next children
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

//    prev_brother = NULL;

      while((cur_child != NULL) && SUCCEEDED(retc))
      {

// recursion through children of children first
         if(SUCCEEDED(retc)) retc = cur_child->CvtToBmps(lpszInFileName, lpszOutFileName, piBgrWdt, piBgrHgt);

// ---------------
         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

// ----------------- <img> failų konvertavimas
         if(((cur_tag == HTM_TG_IMG) /* || (cur_tag == HTM_TG_BODY) */) && SUCCEEDED(retc))
         {
// ----------------- skaitom parametrą
            retc = cur_child->GetTagParsPtr(&tag_pars);
            if(tag_pars &&  SUCCEEDED(retc))
            {
//             switch(cur_tag)
               {
            /* case HTM_TG_IMG: */ retc = tag_pars->SeekTextPar("src", src_file_name, &par_num); // break;
//             case HTM_TG_BODY: retc = tag_pars->SeekTextPar("background", src_file_name, &par_num); break;
//             default:
//                retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//                break;
               }

               if(SUCCEEDED(retc)) if(strlen(src_file_name) >= KP_MAX_FNAME_LEN)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, src_file_name, True, __FILE__, __LINE__, 0L);

// ----------------- keičiam parametrą
#if FALSE // paliekam tą patį, iš .bmp trauksim tik dydį
               if(SUCCEEDED(retc))
                  retc = TvFnameSplit(file_disk, file_path, file_name, file_type, src_file_name);

               if(SUCCEEDED(retc))
               {
                  strcpy(dst_file_name, file_disk);
                  strcat(dst_file_name, file_path);
                  strcat(dst_file_name, "/"); // "\\");
                  strcat(dst_file_name, file_name);
//                strcat(dst_file_name, ".bmp"); // paliekam tą patį, iš .bmp trauksim tik dydį
                  strcat(dst_file_name, ".");
                  strcat(dst_file_name, file_type);

                  if(strlen(dst_file_name) >= KP_MAX_FILE_LIN_LEN)
                     retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, dst_file_name, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
                  retc = tag_pars->SetTextPar(par_num, dst_file_name);
#else
               if(SUCCEEDED(retc)) strcpy(dst_file_name, src_file_name);
#endif

// cout << plpszaHtmlTags[cur_tag - HTM_TG_FirstTag];
// if(SUCCEEDED(retc)) cout << ": " << src_file_name << " --> " << dst_file_name;
// cout << endl;

// ----------------- pilnas src. failo vardas
               if(SUCCEEDED(retc))
                  retc = TvFnameSplit(file_disk, file_path, file_name, file_type, lpszInFileName);
               if(SUCCEEDED(retc))
               {
                  strcpy(src_full_path, file_disk);
                  strcat(src_full_path, file_path);
               }

               if(SUCCEEDED(retc))
               {
                  if(src_file_name[0] == '.') // kelias nuo aktyvaus katalogo
                  {
                     if((src_file_name[1] != '\\') && (src_file_name[1] != '/'))
                        retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, src_file_name, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                     {
                        strcpy(src_full_file_name, src_full_path);
                        strcat(src_full_file_name, src_file_name+1);
                     }
                  }
                  else if((src_file_name[0] != '\\') && (src_file_name[0] != '/') && (src_file_name[1] != ':')) // santykinis kelias
                  {
                     strcpy(src_full_file_name, src_full_path);
                     strcat(src_full_file_name, "\\"); // "/");
                     strcat(src_full_file_name, src_file_name);
                  }
                  else // absoliutus kelias
                     strcpy(src_full_file_name, src_file_name);
               }

// --------------- pilnas dest. failo vardas
               if(SUCCEEDED(retc))
                  retc = TvFnameSplit(file_disk, file_path, file_name, file_type, lpszOutFileName);
               if(SUCCEEDED(retc))
               {
                  strcpy(dst_full_path, file_disk);
                  strcat(dst_full_path, file_path);
               }

               if(SUCCEEDED(retc))
               {
                  if(dst_file_name[0] == '.') // kelias nuo aktyvaus katalogo
                  {
                     if((dst_file_name[1] != '\\') && (dst_file_name[1] != '/'))
                        retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, dst_file_name, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                     {
                        strcpy(dst_full_file_name, dst_full_path);
                        strcat(dst_full_file_name, dst_file_name+1);
                     }
                  }
                  else if((dst_file_name[0] != '\\') && (dst_file_name[0] != '/') && (dst_file_name[1] != ':')) // santykinis kelias
                  {
                     strcpy(dst_full_file_name, dst_full_path);
                     strcat(dst_full_file_name, "\\"); // "/");
                     strcat(dst_full_file_name, dst_file_name);
                  }
                  else // absoliutus kelias
                     strcpy(dst_full_file_name, dst_file_name);
               }

// cout << plpszaHtmlTags[cur_tag - HTM_TG_FirstTag];
// if(SUCCEEDED(retc)) cout << ": " << src_full_file_name << " --> " << dst_full_file_name;
// cout << endl;

// ------------------------ kopijuojam paveikslą
               if(SUCCEEDED(retc)) retc = ConvertSlashes(src_full_file_name, '\\');
               if(SUCCEEDED(retc)) retc = ConvertSlashes(dst_full_file_name, '\\');

               if(SUCCEEDED(retc)) retc = CreatePath(dst_full_file_name, True);

               if(SUCCEEDED(retc))
               {
                  strcpy(cvt_cmd, "copy ");
                  strcat(cvt_cmd, src_full_file_name);
                  strcat(cvt_cmd, " ");
                  strcat(cvt_cmd, dst_full_file_name);

                  system((const char *)cvt_cmd);
               }

// ------------------------ konvertuojam į .BMP
               if(SUCCEEDED(retc))
                  retc = TvFnameSplit(file_disk, file_path, file_name, file_type, dst_full_file_name);

               if(SUCCEEDED(retc))
               {
                  strcpy(dst_full_file_name, file_disk);
                  strcat(dst_full_file_name, file_path);
                  strcat(dst_full_file_name, "\\"); // "/");
                  strcat(dst_full_file_name, file_name);
                  strcat(dst_full_file_name, ".bmp");

                  strcpy(cvt_cmd, "cvt_img ");
                  strcat(cvt_cmd, src_full_file_name);
                  strcat(cvt_cmd, " ");
                  strcat(cvt_cmd, dst_full_file_name);

                  system((const char *)cvt_cmd);
               }

// ----------------- nustatom dimensijas
               KP_NEW(bmp_pars, KpBmpData);

               if(SUCCEEDED(retc))
                  retc = bmp_pars->LoadImageFromFile(dst_full_file_name);

               if(SUCCEEDED(retc))
               {
                  sprintf((char *)new_par_val, "%d", bmp_pars->m_iBmpWdt);
                  par_val[0] = Nul;
                  retc = tag_pars->SeekTextPar("width", par_val, &par_num);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_val, new_par_val) != 0)
                        KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, par_val, True, __FILE__, __LINE__, 0L);
                     retc = tag_pars->SetTextPar(par_num, new_par_val);
                  }
                  else retc = tag_pars->AddTextPar((const unsigned char *)"width", new_par_val);
               }

               if(SUCCEEDED(retc))
               {
                  sprintf((char *)new_par_val, "%d", bmp_pars->m_iBmpHgt);
                  par_val[0] = Nul;
                  retc = tag_pars->SeekTextPar("height", par_val, &par_num);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_val, new_par_val) != 0)
                        KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, par_val, True, __FILE__, __LINE__, 0L);
                     retc = tag_pars->SetTextPar(par_num, new_par_val);
                  }
                  else retc = tag_pars->AddTextPar((const unsigned char *)"height", new_par_val);
               }

               if((piBgrWdt || piBgrHgt) && SUCCEEDED(retc))
               {
                  retc = tag_pars->SeekTextPar("id", par_val, &par_num);
                  if(SUCCEEDED(retc))
                  {
                     strlwr(par_val);
                     if(strcmp(par_val, "background") == 0)
                     {
                        if(piBgrWdt && SUCCEEDED(retc)) *piBgrWdt = bmp_pars->m_iBmpWdt;
                        if(piBgrHgt && SUCCEEDED(retc)) *piBgrHgt = bmp_pars->m_iBmpHgt;
                     }
                  }
                  retc = S_OK;
               }

               KP_DELETE(bmp_pars);

               retc = S_OK;

            } // if(tag_pars &&  SUCCEEDED(retc))

         } // if(((cur_tag == HTM_TG_IMG) || (cur_tag == HTM_TG_BODY)) && SUCCEEDED(retc))

//       prev_brother = cur_child;
         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

// ----------------- <style> fonui įterpimas
// <style>
// body { background-color: transparent; margin: 0px; padding: 0px; height: 100%; border-top: 1px transparent solid; margin-top: -1px; z-index:0; position:relative; }
// img#background { height: 600; width: 800; z-index: -1; position:absolute; color: white; }
// </style>
//    if(SUCCEEDED(retc)) retc = loop_brother->GetNodeTag(&father_tag); // jau ištraukta
      if((father_tag == HTM_TG_HEAD) && SUCCEEDED(retc))
      {
//       sprintf((char *)cont_str, "\nbody { background-color: transparent; margin: 0px; padding: 0px; height: 100%%; border-top: 1px transparent solid; margin-top: -1px; z-index:0; position:relative; }\nimg#background { height: %d; width: %d; z-index: -1; position:absolute; color: white; }\n",
//          piBgrWdt?*piBgrWdt:600, piBgrHgt?*piBgrHgt:800);   // <img id="background"> tagas jau turi būti perskaitytas
//                                                             // arba ištrauktas anksčiau su GetBgrDim()
//                                                             // neišeina – išmatavimų į stilių nededam iš vis:
         sprintf((char *)cont_str, "\nbody { background-color: transparent; margin: 0px; padding: 0px; height: 100%%; border-top: 1px transparent solid; margin-top: -1px; z-index:0; position:relative; }\nimg#background { z-index: -1; position:absolute; color: white; }\n");
         if(SUCCEEDED(retc)) retc = KptStrEncode(contents, cont_str, 1);

//       KP_NEW(cur_child, XmlNode(HTM_TG_STYLE, NULL, contents, NULL, "", HTM_TG_FirstTag, plpszaHtmlTags, loop_brother));

         if(SUCCEEDED(retc)) retc = loop_brother->AppendTextTag(HTM_TG_STYLE, NULL, contents);
      }

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->CvtToBmps(lpszInFileName, lpszOutFileName, piBgrWdt, piBgrHgt);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetBgrDim(int *piBgrWdt, int *piBgrHgt)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
KpChar cur_tag;
XmlTagPars *tag_pars;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
int par_num;

   if(((piBgrWdt == NULL) || (piBgrHgt == NULL)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// loop on brothers
   loop_brother = this;
// while((loop_brother != NULL) && SUCCEEDED(retc))
   if((loop_brother != NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// -------------------------- loop through next children
      while((cur_child != NULL) && SUCCEEDED(retc))
      {

// recursion through children of children first
         if(SUCCEEDED(retc)) retc = cur_child->GetBgrDim(piBgrWdt, piBgrHgt);

// ---------------
         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

//       if((cur_tag == HTM_TG_BODY) && SUCCEEDED(retc))
         if((cur_tag == HTM_TG_IMG) && SUCCEEDED(retc))
         {
// ----------------- skaitom parametrą
            retc = cur_child->GetTagParsPtr(&tag_pars);
            if(tag_pars &&  SUCCEEDED(retc))
            {
               retc = tag_pars->SeekTextPar("id", par_val, &par_num);
               if(SUCCEEDED(retc))
               {
                  strlwr(par_val);
                  if(strcmp(par_val, "background") == 0)
                  {
// !!! patikrint, ar parametrai su px gale, skanuot į float, įvertint sveiką dalį
                     retc = tag_pars->SeekTextPar("width", par_val, &par_num);
                     if(SUCCEEDED(retc))
                     {
                        if(!TvIsNumber(par_val))
                           retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, par_val, False, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) sscanf((const char *)par_val, "%d", piBgrWdt);
                     }
                     retc = S_OK;

                     retc = tag_pars->SeekTextPar("height", par_val, &par_num);
                     if(SUCCEEDED(retc))
                     {
                        if(!TvIsNumber(par_val))
                           retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, par_val, False, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) sscanf((const char *)par_val, "%d", piBgrHgt);
                     }
                     retc = S_OK;

                  } // if(strcmp(par_val, "background") == 0)

               } // if(SUCCEEDED(retc)) // retc = tag_pars->SeekTextPar("id", par_val, &par_num);

               retc = S_OK;

            } // if(tag_pars &&  SUCCEEDED(retc))

         } // if((cur_tag == HTM_TG_BODY) && SUCCEEDED(retc))

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->GetBgrDim(piBgrWdt, piBgrHgt);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::Scale(int iFactor, KpChar iGrandFatherTag)
{
HRESULT retc=S_OK;
XmlNode *loop_brother = NULL;
XmlNode *cur_child = NULL;
XmlNode *next_brother = NULL;
KpChar cur_tag;
KpChar father_tag;
XmlTagPars *par_ptr;
XmlTagPars *par_pars;
static unsigned char par_nam[TV_TAG_LEN + 1];
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
bool changed = False;

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
         if(SUCCEEDED(retc)) retc = cur_child->Scale(iFactor, father_tag);

// ---------------
         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

         if(
//          (
//          /* (cur_tag == HTM_TG_BODY) || */
//             (cur_tag == HTM_TG_IMG) ||
//             (cur_tag == HTM_TG_TABLE) || (cur_tag == HTM_TG_TR) || (cur_tag == HTM_TG_TD)
//          ) &&
            SUCCEEDED(retc)
           )
         {
// ----------------- skaitom parametrą
            retc = cur_child->GetTagParsPtr(&par_ptr);
            while(par_ptr &&  SUCCEEDED(retc))
            {
// ----------------- skaitom parametrą
               if(SUCCEEDED(retc)) retc = par_ptr->GetCurTextPar(par_nam, par_val);
               if(SUCCEEDED(retc)) strlwr(par_nam);

// parametrai su tiesioginiais matmenim
#if FALSE
               if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(par_val);
//             if(SUCCEEDED(retc)) retc = RemoveSpaces(par_val);
               if(SUCCEEDED(retc)) retc = SpcEolToSpc(par_val);
#endif
               changed = False;

               if(SUCCEEDED(retc))
               {
                  if((strcmp(par_nam, "width") == 0) || (strcmp(par_nam, "height") == 0))
                  {
// PutLogMessage_2(">>> %s %s", par_nam, par_val);

                     retc = ScaleParVal(par_nam, par_val, iFactor, XmlParFloatUnits /* XmlParPureInteger */, 1);
                     changed = True;
                  }

               } // if(SUCCEEDED(retc))

               if(changed && SUCCEEDED(retc)) retc = par_ptr->SetTextPar(0, par_val);

// parametras style

               par_pars = NULL;
               if(SUCCEEDED(retc)) if(strcmp(par_nam, "style") == 0)
               {
                  retc = par_ptr->GetCurParPar(par_nam, &par_pars);
                  if((par_pars == NULL) && SUCCEEDED(retc))
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, par_val, True, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc)) retc = par_pars->ScaleStylePars(iFactor);

                  if(SUCCEEDED(retc)) retc = par_ptr->UniformValuesFromPars(False);
               }

               if(SUCCEEDED(retc)) retc = par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);

            } // while(par_ptr &&  SUCCEEDED(retc))

         } // if((/* (cur_tag == HTM_TG_BODY) || */ (cur_tag == HTM_TG_IMG)) && SUCCEEDED(retc))

// -------------------------- <style>
         if(
            (
               ((father_tag == HTM_TG_STYLE) && (cur_tag == XL_Text)) ||
               ((iGrandFatherTag == HTM_TG_STYLE) && (father_tag == XL_Comment) && (cur_tag == XL_Text))
            ) && SUCCEEDED(retc))
         {
// ----------------- skaitom turinį
            retc = cur_child->GetContParsPtr(&par_ptr);
            while(par_ptr &&  SUCCEEDED(retc))
            {
// ----------------- skaitom parametrą
               par_pars = NULL;
               retc = par_ptr->GetCurParPar(par_nam, &par_pars);
               if((par_pars == NULL) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, par_val, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc = par_pars->ScaleStylePars(iFactor);

               if(SUCCEEDED(retc)) retc = par_ptr->UniformValuesFromPars(True);

               if(SUCCEEDED(retc)) retc = par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);

            } // while(par_ptr &&  SUCCEEDED(retc))

         } // if((cur_tag == HTM_TG_STYLE) && SUCCEEDED(retc))

// -------------------------- <input>
         if((cur_tag == HTM_TG_INPUT) && SUCCEEDED(retc))
         {
// ----------------- skaitom parametrą
            retc = cur_child->GetTagParsPtr(&par_ptr);
            while(par_ptr &&  SUCCEEDED(retc))
            {
// ----------------- skaitom parametrą
               if(SUCCEEDED(retc)) retc = par_ptr->GetCurTextPar(par_nam, par_val);
               if(SUCCEEDED(retc)) strlwr(par_nam);

               if(SUCCEEDED(retc)) if(strcmp(par_nam, "size") == 0)
               {
                  retc = ScaleParVal(par_nam, par_val, iFactor, XmlParFloatUnits /* XmlParPureInteger */, 1);
                  if(SUCCEEDED(retc)) retc = par_ptr->SetTextPar(0, par_val);

               } // if(SUCCEEDED(retc)) if(strcmp(par_nam, "size") == 0)

               if(SUCCEEDED(retc)) retc = par_ptr->GetNextBrother((KpTreeEntry **)&par_ptr);

            } // while(par_ptr &&  SUCCEEDED(retc))

         } // if((cur_tag == HTM_TG_INPUT) && SUCCEEDED(retc))

// ------------------
         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->Scale(iFactor);

return(retc);
}


// int depth = 0;

// --------------------------------------------------------
HRESULT XmlNode::ParseStyleContents(KpChar iGrandFatherTag)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
KpChar cur_tag;
KpChar father_tag;
// XmlNode *test_child=NULL;
unsigned char *style_str = NULL;
KpChar *cont_ptr = NULL;
bool end_fl = False;
XmlTagPars *sub_pars = NULL;
unsigned char *pnts;
unsigned char *key_name;

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
         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

// cout << GetTagName(father_tag, m_plpszaTags) << " " << GetTagName(cur_tag, m_plpszaTags) << endl;
// if(strcmp(GetTagName(cur_tag, m_plpszaTags), "<o:idmap/>") == 0)
// retc = S_OK;

// recursion through children of children first
// cout << "ParseStyleContents() " << depth++ << endl;
         if(SUCCEEDED(retc)) retc = cur_child->ParseStyleContents(father_tag);
// depth--;

// if((father_tag == XL_Comment) && (cur_tag == XL_Text))
// retc = S_OK;

         if(
            (
               ((father_tag == HTM_TG_STYLE) && (cur_tag == XL_Text)) ||
               ((iGrandFatherTag == HTM_TG_STYLE) && (father_tag == XL_Comment) && (cur_tag == XL_Text))
            ) && SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc)) if(cur_child->m_pContPars) // GetContParsPtr()
            {
//             retc = KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, null, True, __FILE__, __LINE__, 0L);
               KP_DELETE(cur_child->m_pContPars);
            }
#if FALSE
            if(SUCCEEDED(retc))
            {
//             retc = cur_child->GetFirstChild((KpTreeEntry **)&cur_child);
               cur_child = (XmlNode *)cur_child->m_pFirstChild;

               if((test_child!=NULL) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }
#endif
            cont_ptr = NULL;
            if(SUCCEEDED(retc))
            {
               retc = cur_child->GetContentsPtr(&cont_ptr);
               if((cont_ptr == NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }
//          if(SUCCEEDED(retc)) if(TvKpStrLen(cont_ptr) >= KP_MAX_FILE_LIN_LEN)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            KP_NEWA(style_str, unsigned char, TvKpStrLen(cont_ptr) + 1);

            if(SUCCEEDED(retc))
            {
               retc = KptStrDecode(style_str, cont_ptr, 1);
               if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               end_fl = False;
               pnts = style_str;

               while((!end_fl) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc))
                  {
// key_name
                     key_name = pnts;

                     while((*pnts != '{') && (*pnts)) pnts++;
                     if((*pnts == Nul) && SUCCEEDED(retc))
                     {
                        end_fl = True; // tik laikinai - dar patikrint, ar key_name ne tuščias
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, style_str, True, __FILE__, __LINE__, 0L);
                     }
                  }

// key_val -> sub_pars
                  if(SUCCEEDED(retc))
                  {
                     if(*pnts) *pnts++ = Nul;
//                   key_val = pnts;
                  }
                  sub_pars = NULL;
// cout << "ParseStyleContents() \"" << pnts << "\"" << endl;
                  if((!end_fl) && SUCCEEDED(retc))
                     retc = ParseStyleParameters(&sub_pars, pnts /* key_val */, NULL);

                  if((!end_fl) && SUCCEEDED(retc))
                  {
                     while((*pnts != '}') && (*pnts)) pnts++;
                     if((*pnts == Nul) && SUCCEEDED(retc))
                     {
                        end_fl = True;
                        retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, style_str, True, __FILE__, __LINE__, 0L);
                     }
                     if((*pnts) && SUCCEEDED(retc)) pnts++;
                  }

// key_name?
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(key_name);
                  if(SUCCEEDED(retc)) retc = SpcEolToSpc(key_name);
                  if(SUCCEEDED(retc)) if(key_name[0]) end_fl = False;

                  if((!end_fl) && SUCCEEDED(retc))
                  {
                     if(cur_child->m_pContPars == NULL)
                        KP_NEWO(cur_child->m_pContPars, XmlTagPars(key_name, sub_pars, NULL))
                     else retc = cur_child->m_pContPars->AddParPar(key_name, sub_pars);
                  }

                  KP_DELETE(sub_pars);

               } // while((!end_fl) && SUCCEEDED(retc))

            } // if(SUCCEEDED(retc))

            KP_DELETEA(style_str);

         } // if((father_tag == HTM_TG_STYLE) && (cur_tag == XL_Text) && SUCCEEDED(retc))

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->ParseStyleContents(father_tag);

return(retc);
}


// --------------------------------------------------------
HRESULT XmlNode::FormatStyleContents(KpChar iGrandFatherTag)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *cur_child=NULL;
XmlNode *next_brother=NULL;
KpChar cur_tag;
KpChar father_tag;
int cont_buf_len = 0;
unsigned char par_name[TV_TAG_LEN+1];
static KpChar i_val_buf[MAX_XML_PAR_VAL_LEN + 1];
KpChar *i_cont_buf = NULL;
XmlTagPars *cont_pars = NULL;
XmlTagPars *cur_pars = NULL;
int cont_len = 0;
KpChar *pnti = NULL;

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
         if(SUCCEEDED(retc)) retc = cur_child->FormatStyleContents(father_tag);

         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

         if(
            (
               ((father_tag == HTM_TG_STYLE) && (cur_tag == XL_Text)) ||
               ((iGrandFatherTag == HTM_TG_STYLE) && (father_tag == XL_Comment) && (cur_tag == XL_Text))
            ) && SUCCEEDED(retc)
           )
         {
#if FALSE
            if(SUCCEEDED(retc))
            {
//             retc = cur_child->GetFirstChild((KpTreeEntry **)&test_child);
               test_child = (XmlNode *)cur_child->m_pFirstChild;

               if((test_child!=NULL) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }
#endif
            if(SUCCEEDED(retc)) // if(cur_child->m_lpaizContents != NULL) // GetContentsPtr()
               KP_DELETEA(cur_child->m_lpaizContents);

// ------------- formatuojam ir skaičiuojam visų stiliaus elementų ilgį
            cont_len = 0;

            cont_pars = NULL;
            if(SUCCEEDED(retc))
            {
               retc = cur_child->GetContParsPtr(&cont_pars);
               if((cont_pars == NULL) && SUCCEEDED(retc))
                  retc = KpErrorProc.OutputErrorMessage(E_UNEXPECTED, null, True, __FILE__, __LINE__, 0L);
            }

            cur_pars = cont_pars;
            while(cur_pars && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = cur_pars->UniformValuesFromPars(True);

               if(SUCCEEDED(retc))
                  retc = cur_pars->GetCurKpTextPar(par_name, i_val_buf);

               if(SUCCEEDED(retc))
               {
                  cont_len += strlen(par_name) + 5 + TvKpStrLen(i_val_buf) + 5 + 1;

                  retc = cur_pars->GetNextBrother((KpTreeEntry **)&cur_pars);
               }
            }

// -------------- apjungiam stiliaus elementus
            KP_NEWA(i_cont_buf, KpChar, cont_len + 2 + 1 + 100);

            if(SUCCEEDED(retc))
            {
               i_cont_buf[0] = C_Lf;
               i_cont_buf[1] = C_Nul;

               pnti = i_cont_buf + TvKpStrLen(i_cont_buf);
            }

            cur_pars = cont_pars;
            while(cur_pars && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  retc = cur_pars->GetCurKpTextPar(par_name, i_val_buf);

               if(SUCCEEDED(retc))
               {
                  pnti += TvKpStrLen(pnti);
                  retc = KptStrEncode(pnti, par_name, 1);
                  if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
                     retc = KpErrorProc.OutputErrorMessage(retc, par_name, False, __FILE__, __LINE__, 0L);
               }

               if(SUCCEEDED(retc))
               {
                  pnti += TvKpStrLen(pnti);
                  retc = KptStrEncode(pnti, (const unsigned char *)"\n{\n", 1);
//                if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
//                   retc = KpErrorProc.OutputErrorMessage(retc, par_name, False, __FILE__, __LINE__, 0L);
               }

               if(SUCCEEDED(retc))
               {
                  TvKpStrCat(pnti, i_val_buf);

                  pnti += TvKpStrLen(pnti);
                  retc = KptStrEncode(pnti, (const unsigned char *)"}\n\n", 1);
//                if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
//                   retc = KpErrorProc.OutputErrorMessage(retc, par_name, False, __FILE__, __LINE__, 0L);
               }

               if(SUCCEEDED(retc)) retc = cur_pars->GetNextBrother((KpTreeEntry **)&cur_pars);

            } // while(cur_pars && SUCCEEDED(retc))

            if(SUCCEEDED(retc)) retc = cur_child->SetContents(i_cont_buf);

            KP_DELETEA(i_cont_buf);

         } // if((father_tag == HTM_TG_STYLE) && (cur_tag == XL_Text) && SUCCEEDED(retc))

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->FormatStyleContents(iGrandFatherTag);

return(retc);
}
