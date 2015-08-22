// ==================================================
// xmlgcs.cpp
// CSS generatorius
// pagal projekto stiliø sugeneruoja CSS komplektà:
//    tvxmlt.css - XML failams
//    tvxmlth.css - HTML failams
//    tvxmlthx.css - padidinto ðrifto HTML failams
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpsock.h"
#include "kpwindow.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"

#if Compiler != Watcom
using namespace std;
#endif

//---------------------------------------------
const unsigned char lpszProdName[] = "xmlgcs";
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 43);
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


//---------------------------------------------
HRESULT WriteTagStyleSingle
(
KpString sTagName,
int iTagIndex,
fstream *pfOutFile,
const /* unsigned */ char *lpszOutFileName,
XmlVersions iXmlVers,
int iSizeFactor
)
{
HRESULT retc=S_OK;

   if(((iTagIndex < 0) || (iTagIndex >= XC_TG_NumOfDictTags00) || (pfOutFile == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(XM_IS_VERS_HTML(iXmlVers)) *pfOutFile << "span.";
      *pfOutFile << sTagName << endl;
      *pfOutFile << "{" << endl;

      if(pfOutFile->fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if((iaTagFonts[iTagIndex] >= KPS_NumOfFontStyles00) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iaTagFonts[iTagIndex] >= 0)
   {
// --------------------------------------- font-family: Arial;
KPT_Typefaces typeface;
unsigned char *font_name = NULL;

      if((iaTagFonts[iTagIndex] >= KPS_NumOfFontStyles00) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         typeface = (KPT_Typefaces)aFontStyles[iaTagFonts[iTagIndex]].GetTypeface();
         if(typeface >= KPT_NumOfTypefaces0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
      }

      if((typeface > 0) && SUCCEEDED(retc))
      {
         retc = iaRtfFonts[typeface].GetFontName(&font_name);
         if(font_name)
         {
            *pfOutFile << "   font-family: " << font_name << ";" << endl;

            if(pfOutFile->fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
         }
      }

// --------------------------------------- font-size: 12pt;
int font_size;
int font_flags;

      if(SUCCEEDED(retc))
      {
         font_flags = aFontStyles[iaTagFonts[iTagIndex]].GetFontFlags();
         font_size = aFontStyles[iaTagFonts[iTagIndex]].GetFontSize();
         if(font_size > 0)
         {
// !!!! geriau naudoti <sup>
            *pfOutFile << "   font-size: " << dec <<
               font_size*iSizeFactor/(((font_flags & KPS_SuperFl) || (font_flags & KPS_SubFl))?26:20) << "pt;" << endl;

            if(pfOutFile->fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
         }
      }


// --------------------------------------- font: Bold; font: Normal; font: Italic; font: Superscript; font: Subscript;
// int font_flags;

#if FALSE
// MSHTML:
      if(SUCCEEDED(retc))
      {
//       font_flags = aFontStyles[iaTagFonts[iTagIndex]].GetFontFlags();
         if((font_flags & (KPS_BoldFl | KPS_ItalicFl | KPS_SuperFl | KPS_SubFl)) == 0)
         {
            *pfOutFile << "   font: Normal;" << endl;
         }
         else
         {
            if(font_flags & KPS_BoldFl) *pfOutFile << "   font: Bold;" << endl;
            if(font_flags & KPS_ItalicFl) *pfOutFile << "   font: Italic;" << endl;
            if(font_flags & KPS_SuperFl)
            {
               *pfOutFile << "   font: Normal;" << endl;
// !!!! geriau naudoti <sup>
//             *pfOutFile << "   vertical-align:top;" << endl;
               *pfOutFile << "   vertical-align:super;" << endl;
            }
            if(font_flags & KPS_SubFl) *pfOutFile << "   font: Subscript;" << endl;
         }

         if(pfOutFile->fail())
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
      }
#endif

// XGecko:
      if(SUCCEEDED(retc))
      {
//       font_flags = aFontStyles[iaTagFonts[iTagIndex]].GetFontFlags();
         if(font_flags & KPS_ItalicFl) *pfOutFile << "   font-style: Italic;" << endl;
//       else *pfOutFile << "   font-style: Normal;" << endl;

         if(font_flags & KPS_BoldFl) *pfOutFile << "   font-weight: Bold;" << endl;
         else *pfOutFile << "   font-weight: Normal;" << endl;

         if(font_flags & KPS_SuperFl)
         {
// !!!! geriau naudoti <sup>
            *pfOutFile << "   vertical-align: top;" << endl;
//          *pfOutFile << "   vertical-align: super;" << endl;
         }

         if(font_flags & KPS_SubFl) *pfOutFile << "   font: Subscript;" << endl; // !!!!

         if(pfOutFile->fail())
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
      }

// --------------------------------------- color: #006000;
KpColor font_color;

      if(SUCCEEDED(retc))
      {
         font_color = aFontStyles[iaTagFonts[iTagIndex]].GetColor();

         if(font_color != KpColorUndefined)
         {
            if((font_color < 0) || (font_color >= KpGmaxcc0))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
COLORREF rgb_color;
               rgb_color = ColorTable[font_color];
               rgb_color = RGB((rgb_color >> 16) & 0xFF, (rgb_color >> 8) & 0xFF, rgb_color & 0xFF);

//             *pfOutFile << "   color: #" << hex << rgb_color << ";" << endl;
char str_buf[20];
               sprintf(str_buf, "%06X", rgb_color);
               *pfOutFile << "   color: #" << str_buf << ";" << endl;

               if(pfOutFile->fail())
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
            }
         }
      }

// --------------------------------------- background-color: #006000;
// KpColor font_color;

      if(SUCCEEDED(retc))
      {
         font_color = aFontStyles[iaTagFonts[iTagIndex]].GetBackColor();

         if(font_color != KpColorUndefined)
         {
            if((font_color < 0) || (font_color >= KpGmaxcc0))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
COLORREF rgb_color;
               rgb_color = ColorTable[font_color];
               rgb_color = RGB((rgb_color >> 16) & 0xFF, (rgb_color >> 8) & 0xFF, rgb_color & 0xFF);

//             *pfOutFile << "   color: #" << hex << rgb_color << ";" << endl;
char str_buf[20];
               sprintf(str_buf, "%06X", rgb_color);
               *pfOutFile << "   background-color: #" << str_buf << ";" << endl;

               if(pfOutFile->fail())
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
            }
         }
      }

// --------------------------------------- white-space: nowrap;

      if(SUCCEEDED(retc))
//       if(
//          (strcmp(sTagName.ExtractValueA(), "fs") == 0) || (strcmp(sTagName.ExtractValueA(), "f") == 0) ||
//          (strcmp(sTagName.ExtractValueA(), "eq") == 0) || (strcmp(sTagName.ExtractValueA(), "el") == 0) ||
//          (strcmp(sTagName.ExtractValueA(), "img") == 0)
//         )

//       if((sTagName == "fs") || (sTagName == "f") || (sTagName == "eq") || (sTagName == "el") || (sTagName == "img"))

// visiems tekstiniams - taginam po vienà þodá
         if(baXmlDictTagsFreeText[iTagIndex])

         {
            *pfOutFile << "   white-space: nowrap;" << endl;

            if(pfOutFile->fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
         }


// --------------------------------------- cursor: hand;

      if(SUCCEEDED(retc))
//       if(
//          (strcmp(sTagName.ExtractValueA(), "hw") == 0) || (strcmp(sTagName.ExtractValueA(), "v") == 0) ||
//          (strcmp(sTagName.ExtractValueA(), "le") == 0) || (strcmp(sTagName.ExtractValueA(), "lc") == 0) ||
//          ...
//          (strcmp(sTagName.ExtractValueA(), "tw") == 0)
//          ...
//         )

// visiems ið leksiniø indeksø - pelës kursorius - nuoroda
         if(
            (strcmp(lpszaXmlTagIxNames[iTagIndex], "hw") == 0) || (strcmp(lpszaXmlTagIxNames[iTagIndex], "le") == 0) ||
            (strcmp(lpszaXmlTagIxNames[iTagIndex], "ic") == 0) || (strcmp(lpszaXmlTagIxNames[iTagIndex], "xr") == 0) ||

            (strcmp(lpszaXmlTagIxNames[iTagIndex], "tw") == 0) ||
            (strcmp(lpszaXmlTagIxNames[iTagIndex], "dc") == 0)
           )
         {
            *pfOutFile << "   cursor: pointer;" << endl;
            *pfOutFile << "   cursor: hand;" << endl;

            if(pfOutFile->fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
         }


// ---------------------------------------
   } // if((iaTagFonts[iTagIndex] >= 0) && SUCCEEDED(retc))

   if(SUCCEEDED(retc))
   {
      *pfOutFile << "}" << endl;
      *pfOutFile << endl;

      if(pfOutFile->fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
   }


return(retc);
}


//---------------------------------------------
HRESULT WriteCssFile
(
const /* unsigned */ char *lpszOutFileName,
XmlVersions iXmlVers,
int iSizeFactor // padaugintas ið 10
)
{
HRESULT retc=S_OK;
fstream out_file(lpszOutFileName, ios::out);
KpString tag_name;
int ii;

   if(SUCCEEDED(retc)) if(out_file.fail())
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      out_file << "<!-- " << (XM_IS_VERS_HTML(iXmlVers)?"HTML":"XML")
         << ((strstr(lpszOutFileName, "x.") !=  NULL)?" enlarged":"")
         << " file style table for dictionaries (" << lpszOutFileName << ") -->" << endl;
      out_file << endl;

      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
   }

   for(ii = 0; (ii < XC_TG_NumOfDictTags00) && SUCCEEDED(retc); ii+=2)
   {
// ---------------------------------------
int start_pos;
int end_pos;

      tag_name = (const char *)plpszaXmlttDictTags[ii];

      start_pos = tag_name.index("<") + 1;
//    if(start_pos < 0) start_pos = 0;

      end_pos = tag_name.index("/");
      if(end_pos < 0) end_pos = tag_name.index(">");
      if(end_pos < 0) end_pos = tag_name.index("\n");
      if(end_pos < 0) end_pos = tag_name.length()-1;
      if(end_pos < 0) end_pos = 0;
      if(end_pos > start_pos)
      {
         tag_name = tag_name.substr(start_pos, end_pos - start_pos);

         retc = WriteTagStyleSingle(tag_name, ii, &out_file, lpszOutFileName, iXmlVers, iSizeFactor);
         if((tag_name == "xr") && XM_IS_VERS_HTML(iXmlVers) /* (iXmlVers == XM_VERS_HTML) */ && SUCCEEDED(retc))
            retc = WriteTagStyleSingle(KpString("a"), ii, &out_file, lpszOutFileName, XM_VERS_XML10, iSizeFactor);
         if((tag_name == "img") && XM_IS_VERS_HTML(iXmlVers) /* (iXmlVers == XM_VERS_HTML) */ && SUCCEEDED(retc))
         {
            retc = WriteTagStyleSingle(KpString("img"), ii, &out_file, lpszOutFileName, XM_VERS_XML10, iSizeFactor);
            if(SUCCEEDED(retc)) retc = WriteTagStyleSingle(KpString("object"), ii, &out_file, lpszOutFileName, XM_VERS_XML10, iSizeFactor);
            if(SUCCEEDED(retc)) retc = WriteTagStyleSingle(KpString("embed"), ii, &out_file, lpszOutFileName, XM_VERS_XML10, iSizeFactor);
            if(SUCCEEDED(retc)) retc = WriteTagStyleSingle(KpString("iframe"), ii, &out_file, lpszOutFileName, XM_VERS_XML10, iSizeFactor);
         }

      } // if(end_pos > start_pos)

   } // for(ii = 0; ii < XC_TG_NumOfDictTags00; ii+=2)

   if(SUCCEEDED(retc))
   {
      out_file.close();
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszOutFileName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


//---------------------------------------------
int main(void)
{
HRESULT retc=S_OK;

   printf("\nXMLT/HTML stylesheets generator\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc)) retc = WriteCssFile("tvxmlt.css", XM_VERS_XML10, 10);
   if(SUCCEEDED(retc)) retc = WriteCssFile("tvxmlth.css", XM_VERS_HTML, 10);
   if(SUCCEEDED(retc)) retc = WriteCssFile("tvxmlthx.css", XM_VERS_HTML, 14);

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#if (Compiler == Watcom)
char str_buf[101];
cout << "Press any key:";
cin.getline(str_buf, 100);
#endif

return(RET_CODE_MAIN(retc));
}


