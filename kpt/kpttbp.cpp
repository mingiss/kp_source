// ==================================================
// kpttbp.cpp
// Print code table


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpttucf.h"
#include "kpstring.h"
#include "kperr.h"

#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlu.h"
#include "htmt.h"
#include "kpttbp.h"


// ================================================== objects
KptTbp_tag *pKptTbp=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);

// ================================================== public methods of KptTbp_tag
KptTbp_tag::KptTbp_tag(int iKptTbl, const unsigned char *lpszOutFname)
{
   lhOpenResult=S_OK;
   pTagStack=NULL;
   lpOutFileObj=NULL;
   lpszTitle[0]=Nul;

   KpErrorProc.SetLPar(0L);

   if((iKptTbl<=0) || (iKptTbl>=KPT_Ctnum))
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(lhOpenResult)) iCtbl=iKptTbl;

   if(SUCCEEDED(lhOpenResult)) lhOpenResult=OpenFile(lpszOutFname);

   KP_NEW(pTagStack, TvXmlTagStack_tag(NULL, C_Nul, NULL, 0));
}


// --------------------------------------------------
KptTbp_tag::~KptTbp_tag(void)
{
TvXmlTagStack_tag *prev_stack_ptr;
int cur_tag;

   CloseFile(False);

   if(pTagStack!=NULL)
   {
      pTagStack->GetPrevTagPtr(&prev_stack_ptr);
      pTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, FALSE, __FILE__, __LINE__, 0L);

      KP_DELETE(pTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT KptTbp_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT KptTbp_tag::OpenFile(const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;
int buf_len;

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(lpOutFileObj, TvXmlFile_tag(lpszOutFname, (const unsigned char *)"wb", XL_FT_DataFile, 
         CreateNewUniFile, TV_XL_NUM_LEN, HTM_TG_FirstTag, plpszaHtmlTags, 
         XM_VERS_HTML401_TRANS, iaHtmNulCodeTables));
   if(FAILED(retc)) KP_DELETE(lpOutFileObj);

   if(SUCCEEDED(retc))
   {
      if(lpszaXmlCtblNames[iCtbl][0])
         strncpy(lpszTitle, lpszaXmlCtblNames[iCtbl], KP_MAX_FILE_LIN_WDT);
      else if(lpszaXmlCtblNamesWin[iCtbl][0])
         strncpy(lpszTitle, lpszaXmlCtblNamesWin[iCtbl], KP_MAX_FILE_LIN_WDT);
      else
         KP_ERROR(E_SYSTEM_ERROR, null);   

      lpszTitle[KP_MAX_FILE_LIN_WDT]=Nul;
      buf_len=strlen(lpszTitle);
      if(buf_len>0)
      {
         strncpy(lpszTitle+buf_len, ", ", KP_MAX_FILE_LIN_WDT-buf_len);
         lpszTitle[KP_MAX_FILE_LIN_WDT]=Nul;
         buf_len=strlen(lpszTitle);
      }
      strncpy(lpszTitle+buf_len, iaKptCtabExpl[iCtbl], KP_MAX_FILE_LIN_WDT-buf_len);
      lpszTitle[KP_MAX_FILE_LIN_WDT]=Nul;

      retc=PutHtmHat(lpOutFileObj, lpszTitle, NULL, (const unsigned char *)"kptt.css");
   }

return(retc);
}


// --------------------------------------------------
HRESULT KptTbp_tag::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(lpOutFileObj!=NULL)
   {
      retc=PutHtmTail(lpOutFileObj);

      retc0=lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT KptTbp_tag::Process(void)
{
HRESULT retc=S_OK;
XmlTagPars_tag *tag_pars=NULL;
XmlTagPars_tag *tag_pars_phon=NULL;
XmlTagPars_tag *tag_pars_numb=NULL;
XmlTagPars_tag *tag_pars_smnum=NULL;
XmlTagPars_tag *tag_pars_ctrl=NULL;
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
int ii, jj;
int out_ch;
unsigned char out_ch1;
Chars16 *out_tb;

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_BODY, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"heading"));
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P, tag_pars, False);
   KP_DELETE(tag_pars);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszTitle);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P_e, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

// -------------------------------
   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"border", 0L));

   if(SUCCEEDED(retc))
      retc=tag_pars->AddTextPar((unsigned char *)"align", (unsigned char *)"center");
   if(SUCCEEDED(retc))
      retc=tag_pars->AddNumPar((unsigned char *)"cellpadding", 2L);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE, tag_pars, False);

   KP_DELETE(tag_pars);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD, NULL, False);

   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"numb"));
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars, False);
   KP_DELETE(tag_pars);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_NBSP, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_NBSP, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD_e, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

   for(ii=0; ii<16; ii++)
   {
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD, NULL, False);

      KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"numb"));
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P, tag_pars, False);
      KP_DELETE(tag_pars);

      sprintf((char *)str_buf, "%02X&#160;&#160;", ii);
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(str_buf);

      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P_e, NULL, False);

      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD_e, NULL, False);
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);
   }

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR_e, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE_e, NULL, False);

// -------------------------------
   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"border", 0L));

   if(SUCCEEDED(retc))
      retc=tag_pars->AddTextPar((unsigned char *)"align", (unsigned char *)"center");
   if(SUCCEEDED(retc))
      retc=tag_pars->AddNumPar((unsigned char *)"cellpadding", 2L);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE, tag_pars, False);

   KP_DELETE(tag_pars);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR, NULL, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

   for(jj=0; jj<16; jj++)
   {
      KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"numb"));
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P, tag_pars, False);
      KP_DELETE(tag_pars);

      sprintf((char *)str_buf, "%02X", jj*16);
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(str_buf);

      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_P_e, NULL, False);
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);
   }

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD_e, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

// -------------------------------
   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"border", 2L));

   if(SUCCEEDED(retc))
      retc=tag_pars->AddTextPar((unsigned char *)"align", (unsigned char *)"center");
   if(SUCCEEDED(retc))
      retc=tag_pars->AddNumPar((unsigned char *)"cellpadding", 2L);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE, tag_pars, False);

   KP_DELETE(tag_pars);

   KP_NEW(tag_pars, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"glyph"));

   KP_NEW(tag_pars_phon, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"phon"));

   KP_NEW(tag_pars_ctrl, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"ctrl"));

   KP_NEW(tag_pars_smnum, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"smnum"));

   KP_NEW(tag_pars_numb, XmlTagPars_tag((unsigned char *)"class", (unsigned char *)"numb"));

   for(jj=0; jj<16; jj++)
   {
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR, NULL, False);

      for(ii=0; ii<16; ii++)
      {
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD, NULL, False);
   
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars_smnum, False);
         out_ch=jj*16+ii;
         if((out_ch<C_Spc) || (out_ch>=C_Del)) out_ch=C_Spc;
         sprintf((char *)str_buf, "%03d &#160;&#160;&#160;&#160;%c", jj*16+ii, out_ch);
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(str_buf);
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);

         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_BR, NULL, False);

         if(SUCCEEDED(retc)) 
         {
            out_ch=jj*16+ii;
            if(out_ch<KPT_Ctbsiz/2) out_tb=Ctptr8[iCtbl*2];
            else
            {
               out_tb=Ctptr8[iCtbl*2+1];
               out_ch-=KPT_Ctbsiz/2;
            }

            if(out_tb!=NULL) out_ch=out_tb[out_ch];
            else out_ch=C_Spc;

            switch(out_ch)
            {
                                   // ----------------------------
                                   // phonetic characters; vowels:

            case C_ph_a:           // low back unrounded; a, open a; italic C_a
                     
            case C_ph_a_inv:       // low back rounded; oa; inverted italic C_a
                     
            case C_ph_a_sh:        // low-mid back unrounded; short a; inverted C_v
            case C_ph_o_sh:        // low-mid back rounded; short o, open o; inverted C_c
//          case C_ph_o:           // mid back rounded?; o, closed o; C_o
                     
            case C_ph_u_sh:        // semi-high back rounded; short u, short open u; C_ypsilon
            case C_ph_w_sh:        // semi-high back rounded; short u, short open u, obsolete; C_omega
//          case C_ph_u:           // semi-high central rounded?; u, closed u; C_u
//          case C_ph_u_soft:      // high central rounded; soft u, iu, german C_u_Diaer; C_y,
                     
            case C_ph_e_sh:        // low-mid front unrounded; short e, open e; C_epsilon
            case C_ph_ae:          // low front unrounded?; e, open e; C_ae
//          case C_ph_e_cl:        // high central unrounded?; closed e, german e; C_e
            case C_ph_e_sh_inv:    // low-mid central unrounded; hard e; inverted C_epsilon
            case C_ph_e_inv:       // mid central unrounded; reduced e; inverted C_e
                     
            case C_ph_i_sh:        // semi-high front unrounded; short i, short open i; C_i without dot
//          case C_ph_i:           // high front unrounded?; i, closed i; C_i

                                   // ----------------------------
                                   // phonetic characters; consonants:

            case C_ph_sh:          // sh; C_f, C_int
            case C_ph_zh:          // zh; C_3
            case C_ph_tsh:         // tsh; C_t C_f, C_t C_int
            case C_ph_dzh:         // dzh; C_d C_3
            case C_ph_th_b:        // breath th; C_theta
            case C_ph_th_v:        // voiced th; C_delt_Mn, (C_delta_Minus)
            case C_ph_ng:          // nasal g; C_eta
            case C_ph_g:           // g; italic C_g

                                   // ----------------------------
                                   // additional phonetic characters:

            case C_ph_oe:          // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
            case C_ph_o_slash:     // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash; "o/"
                     
            case C_ph_a_l:         // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
            case C_ph_e_inv_l:     // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
            case C_ph_i_l:         // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
            case C_ph_o_l:         // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
            case C_ph_u_l:         // ; u long; C_u C_Colon
                     
            case C_ph_a_n:         // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
            case C_ph_a_str_n:     // ; straight a nasal; a~, C_a_Tilde
            case C_ph_e_n:         // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
            case C_ph_oe_n:        // ; oe nasal; oe~, C_oe C_TildeAcc
            case C_ph_o_n:         // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc
                     
            case C_ph_ch:          // german ch; C_c_Cedil

                                   // ----------------------------
                                   // diphtongs

            case C_ph_ai_d:        // C_a C_LigaLow C_i
            case C_ph_ae_d:        // C_a C_LigaLow C_e
            case C_ph_ao_d:        // C_a C_LigaLow C_o
            case C_ph_au_d:        // C_a C_LigaLow C_u
            case C_ph_ei_d:        // C_e C_LigaLow C_i
            case C_ph_eu_d:        // C_e C_LigaLow C_u
            case C_ph_ie_d:        // C_i C_LigaLow C_e
            case C_ph_oe_d:        // C_ph_o_sh C_LigaLow C_ph_o_slash
            case C_ph_oy_d:        // C_ph_o_sh C_LigaLow C_y
            case C_ph_uo_d:        // C_u C_LigaLow C_o

                                   // ----------------------------
                                   // breved phonetics

            case C_ph_i_Brev:      // ; j; C_i_Brev
            case C_ph_o_Brev:      //  C_o_Brev
            case C_ph_u_Brev:      //  C_u_Brev
                     
                                   // phonetic accents
                     
            case C_ph_acc:         // C_Apost
            case C_ph_acc_low:     // C_Comma
                     
                                   // ----------------------------
            case C_ph_uu_sh:       // phonetics: semi-high back rounded; short u, short open u; inverted C_Omega

               if(SUCCEEDED(retc))
               {
                  retc=KptCharDecode(&out_ch1, (Chars16)out_ch, 82);
                  if(retc==KP_E_UNKN_CHR)
                  {
                     retc=KpErrorProc.OutputErrorMessage(retc, plpszaXmlSpecCharTags[out_ch], False, __FILE__, __LINE__, 0L);
                     out_ch=C_Del;

                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_NBSP, NULL, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(out_ch, NULL, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);
                  }
                  else
                  {
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars_phon, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_NBSP, NULL, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(out_ch1, NULL, False);
                     if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);
                  }
               }
               break;

            case C_NBSP:
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars_ctrl, False);
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"NBSP");
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);
               break;

            case C_hyph:
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars_ctrl, False);
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"SHY");
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);
               break;

            default:
               if(out_ch==C_Del) out_ch=C_NBSP;
               if(out_ch==C_Unkn) out_ch=C_Del;
               if(out_ch<=C_Spc) out_ch=C_NBSP;

               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN, tag_pars, False);
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharExp(out_ch);
               if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_SPAN_e, NULL, False);
                  
               break;
            }
            
         }
         
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);
      }

      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR_e, NULL, False);
   }

   KP_DELETE(tag_pars);

   KP_DELETE(tag_pars_phon);

   KP_DELETE(tag_pars_ctrl);

   KP_DELETE(tag_pars_numb);

   KP_DELETE(tag_pars_smnum);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE_e, NULL, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TD_e, NULL, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(C_Lf, NULL, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TR_e, NULL, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_TABLE_e, NULL, False);

// -------------------------------
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(HTM_TG_BODY_e, NULL, False);
   
return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
unsigned char *l_argv[3];

   printf("\nPrint KPT code table\n\n");

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=(unsigned char *)argv[0];
      l_argv[1]=(unsigned char *)argv[1];
      l_argv[2]=(unsigned char *)argv[2];
   }
// #ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=3;
      l_argv[0]=(unsigned char *)"kpttbp";
//    l_argv[1]=(unsigned char *)"43";
//    l_argv[1]=(unsigned char *)"49";
      l_argv[1]=(unsigned char *)"80";
//    l_argv[2]=(unsigned char *)"D:/kp/source/kpt/dos773.htm";
//    l_argv[2]=(unsigned char *)"D:/kp/source/kpt/dos773p.htm";
      l_argv[2]=(unsigned char *)"D:/kp/source/kpt/Win_Acc.htm";
   }
// #endif

   if(l_argc==3)
   {
      KP_NEWO(pKptTbp, KptTbp_tag(atoi((char *)l_argv[1]), (unsigned char *)l_argv[2]));

      if(SUCCEEDED(retc)) retc = pKptTbp->Process();

      if(pKptTbp!=NULL)
      {
         retc0=pKptTbp->CloseFile(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc=retc0;
      }

      KP_DELETE(pKptTbp);
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>kpttbp.exe 43 outfile.htm\n");
      printf("                             ^\n");
      printf("                             |\n");
      printf("     KPT code table number --'\n");
   }

return(RET_CODE(retc));
}
