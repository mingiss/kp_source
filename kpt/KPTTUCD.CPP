// ==================================================
// kpttucd.cpp
// Generator of Unicode character codes for Kpt codeset


// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <windows.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xml8.h"
#include "kpttucd.h"


// ================================================== objects
KpttUcd_tag *pKpttUcd=NULL;

KpErrorProcClass KpErrorProc(TRUE, 43);
bool bServiceFl=False;

const unsigned char lpszProdName[] = "kpttucd";


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ================================================== KpErrorProc_tag local functions
// --------------------------------------------------
HRESULT KpErrorProcClass::FormatErrorMessage
(
   const HRESULT lhRetc,
   unsigned char *lpszMsg
)
{
return(FormatErrorMessageMain(lhRetc, lpszMsg));
}


// ================================================== private methods of KpttUcd_tag
// ================================================== public methods of KpttUcd_tag
// --------------------------------------------------
KpttUcd_tag::KpttUcd_tag
(
const unsigned char *lpszInFileName,
const unsigned char *lpszOutFileName,
UC_Modes iUcMode
)
{
   lhOpenResult=S_OK;

   lpInFile=NULL;
   lpOutFile=NULL;

   strncpy((char *)lpszInFName, (const char *)lpszInFileName, KP_MAX_FNAME_LEN);
   lpszInFName[KP_MAX_FNAME_LEN]=Nul;

   strncpy((char *)lpszOutFName, (const char *)lpszOutFileName, KP_MAX_FNAME_LEN);
   lpszOutFName[KP_MAX_FNAME_LEN]=Nul;

   KP_NEWO(lpInFile, UcFile_tag(lpszInFName, iUcMode, (const unsigned char *)"r", CreateNew8File, True));

   if(SUCCEEDED(lhOpenResult))
   {
      lpOutFile=fopen((const char *)lpszOutFName, "w");
      if(lpOutFile==NULL)
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszOutFName, TRUE, __FILE__, __LINE__, 0L);
   }
}


// --------------------------------------------------
KpttUcd_tag::~KpttUcd_tag(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::ProcessContents(bool bJava)
{
HRESULT retc = S_OK;
unsigned long ll, kk;
bool skip_qt;
bool new_line;

   if((lpInFile==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   skip_qt=False;
   new_line = True;

   do
   {
      if(new_line)
      {
         do
         {
            retc = lpInFile->GetChar(&ll);
         } while((TvStrChr(lpszSpaces, ll) != null) && SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc = lpInFile->UnGetChar(ll);

         if((ll != C_Lf) && (ll != '/')) // tuðèia eilutë, komentaras
         {
            fputs("   ", lpOutFile);
         
            if(bJava)
            { 
               fputs("   ", lpOutFile);
               if(ll == C_C) // 'C' // C_..., ne 0x... 
               {
                  fputs("KpChar.", lpOutFile);
                  do
                  {
                     retc = lpInFile->GetChar(&ll);
                     if((ll == C_Comma) && SUCCEEDED(retc)) fputs(".ordinal()", lpOutFile); // ','
                     if(SUCCEEDED(retc)) fputc(ll, lpOutFile);
                  } while((ll != C_Comma) && (ll != C_Lpar) && SUCCEEDED(retc)); // ',' // C_0, // '(' // CH_LTCOD(
               }
            }
         }
      
         new_line = False;
      }
   
      retc = lpInFile->GetChar(&ll);

      if(skip_qt && (ll=='\"') && SUCCEEDED(retc))
      {
         retc=lpInFile->GetChar(&kk);
         if(SUCCEEDED(retc))
         {
            if((kk==Cr) || (kk==Lf))
            {
               ll=kk;
               skip_qt=False;
            }
            else if(kk=='\"') ll=kk;
            else retc=lpInFile->UnGetChar(kk);
         }
      }

      if((ll==Lf) && SUCCEEDED(retc))
      {
         retc=lpInFile->GetChar(&kk);
         if(SUCCEEDED(retc))
         {
            if(kk=='\"') skip_qt=True;
            else retc=lpInFile->UnGetChar(kk);
         }

         new_line = True;
      }

      if(SUCCEEDED(retc))
      {
         if(ll>=KPT_FirstKptChar) fprintf(lpOutFile, "0x%04lX", ll);
         else
         {
            if(ll=='\r')
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
            putc(ll, lpOutFile);
         }

         if(feof(lpOutFile) || ferror(lpOutFile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFName, TRUE, __FILE__, __LINE__, 0L);
      }

   } while(SUCCEEDED(retc));

   if(retc==KP_E_EOF) retc = S_OK;

// if(SUCCEEDED(retc))
//    if(ll!='\n')
//       retc=KpErrorProc.OutputErrorMessage(TV_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::ProcessCpp(void)
{
HRESULT retc = S_OK;

   if((lpInFile==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   fprintf(lpOutFile, "// -----------------------------------------------------\n");
   fprintf(lpOutFile, "// This file is automatically generated - do not change\n");
   fprintf(lpOutFile, "// original source Unicode UTF-16 file - kpttu16.txt\n\n");

   fprintf(lpOutFile, "// ===================================================\n");
   fprintf(lpOutFile, "//  kpttuc.cpp\n");
   fprintf(lpOutFile, "//  Kpt style character Unicode codes\n");
   fprintf(lpOutFile, "//\n\n\n");

   
   fprintf(lpOutFile, "// -----------------------\n");
   fprintf(lpOutFile, "#include \"stdafx.h\"\n\n");

   fprintf(lpOutFile, "#include \"envir.h\"\n\n");

   fprintf(lpOutFile, "#if CompilerGr==Msvc\n");
   fprintf(lpOutFile, "#include <afx.h>\n");
   fprintf(lpOutFile, "#endif\n");
   fprintf(lpOutFile, "#include <string>\n");
   fprintf(lpOutFile, "#include <stdio.h>\n");
   fprintf(lpOutFile, "#include <fstream>\n");
   fprintf(lpOutFile, "#if OsGr==MSWin\n");
   fprintf(lpOutFile, "#include <windows.h>\n");
   fprintf(lpOutFile, "#endif\n\n");

   fprintf(lpOutFile, "#if (Compiler != Watcom) || (__WATCOMC__ > 1201)\n");
   fprintf(lpOutFile, "using namespace std;\n");
   fprintf(lpOutFile, "#endif\n\n");

   fprintf(lpOutFile, "#include \"kpstdlib.h\"\n");
   fprintf(lpOutFile, "#include \"kptt.h\"\n\n\n");


   fprintf(lpOutFile, "// -----------------------\n");
   fprintf(lpOutFile, "UniChar iaUniChars[C_CharArrSize44] =\n");
   fprintf(lpOutFile, "{\n");

   retc = ProcessContents(False);

   fprintf(lpOutFile, "};\n");

return(retc);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::ProcessJava(void)
{
HRESULT retc=S_OK;

   if((lpInFile==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   fprintf(lpOutFile, "// -----------------------------------------------------\n");
   fprintf(lpOutFile, "// This file is automatically generated - do not change\n");
   fprintf(lpOutFile, "// original source Unicode UTF-16 file - kpttu16.txt\n\n");

   fprintf(lpOutFile, "package kplib.kpt;\n\n");

   fprintf(lpOutFile, "import kplib_and.common.kperr.KpError;\n");

   fprintf(lpOutFile, "public class UniChars\n");
   fprintf(lpOutFile, "{\n");
   fprintf(lpOutFile, "   public static int m_iaUniChars[] =\n");
   fprintf(lpOutFile, "   {\n");

   retc = ProcessContents(True);

   fprintf(lpOutFile, "   };\n\n");
   
   fprintf(lpOutFile, "   public static void CheckData() throws ArrayIndexOutOfBoundsException\n");
   fprintf(lpOutFile, "   {\n");
   fprintf(lpOutFile, "      KpError.SetPlace(\"UniChars.CheckData() 0\");\n");
   fprintf(lpOutFile, "      if(m_iaUniChars.length != KpChar.C_CharSize0.ordinal()){ KpError.SetPlace(\"UniChars.CheckData() 1: \" + m_iaUniChars.length + \" \" + KpChar.C_CharSize0.ordinal()); throw(new ArrayIndexOutOfBoundsException()); }\n");
   fprintf(lpOutFile, "   }\n");
   fprintf(lpOutFile, "}\n");

return(retc);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::ProcessJavaRevContents(void)
{
HRESULT retc = S_OK;
unsigned long ll;
int kk;

   if((lpInFile==NULL) || (lpOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   kk = C_Nul;
   do
   {
      do
      {
         retc = lpInFile->GetChar(&ll);
      } while((ll != '/') && SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc = lpInFile->GetChar(&ll);
      if((ll == '/') && SUCCEEDED(retc))
      {      
         do
         {
            retc = lpInFile->GetChar(&ll);
         } while((TvStrChr(lpszSpaces, ll) != null) && SUCCEEDED(retc));

         if((ll == C_C) && SUCCEEDED(retc)) // 'C' 
         {
            KP_ASSERT(kk < C_CharSize0, KP_E_SYSTEM_ERROR, null, True);

            if(SUCCEEDED(retc))
            {
//             fprintf(lpOutFile, "      {0x%04x, %d, ", iaUniChars[kk], kk);
               fprintf(lpOutFile, "0x%04x\t%d\t", iaUniChars[kk], kk);

               kk++;
               do
               {
                  fputc(ll, lpOutFile);
                  retc = lpInFile->GetChar(&ll);
               } while((ll != C_Comma) && (TvStrChr(lpszSpcEol, ll) == null) && SUCCEEDED(retc));
               if(SUCCEEDED(retc)) retc = lpInFile->UnGetChar(ll);
      
//             fputs("},\n", lpOutFile);
               fputs("\n", lpOutFile);
      
               do
               {
                  retc = lpInFile->GetChar(&ll);
               } while((ll != C_Lf) && SUCCEEDED(retc)); // '\n'
            }
         }
      }

      if(SUCCEEDED(retc))
         if(feof(lpOutFile) || ferror(lpOutFile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFName, TRUE, __FILE__, __LINE__, 0L);

   } while(SUCCEEDED(retc));

   if(retc==KP_E_EOF) retc = S_OK;

   KP_ASSERT(kk == C_CharSize0, KP_E_SYSTEM_ERROR, null, True);

return(retc);
}


// --------------------------------------------------
HRESULT KpttUcd_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   KP_DELETE(lpInFile);

   if(lpOutFile!=NULL)
   {
      if(fclose(lpOutFile)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszOutFName, TRUE, __FILE__, __LINE__, 0L);
      lpOutFile=NULL;
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------------------
HRESULT ProcessJavaRev(fstream *InFile, fstream *OutFile)
{
HRESULT retc = S_OK;
static unsigned char in_str[KP_MAX_FILE_LIN_LEN + 1];
unsigned char **in_words = NULL;
int word_cnt = 0;

   KP_ASSERT(InFile != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(OutFile != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      *OutFile << "// -----------------------------------------------------" << endl;
      *OutFile << "// This file is automatically generated - do not change" << endl;
      *OutFile << "// original source Unicode UTF-16 file - kpttu16.txt" << endl << endl;

      *OutFile << "package kplib.kpt;" << endl << endl;

      *OutFile << "import java.util.zip.DataFormatException;" << endl;
      *OutFile << "import kplib.common.kpstring.KpString;" << endl;
      *OutFile << "import kplib.kpt.KpChar;" << endl;
      *OutFile << "import kplib_and.common.kperr.KpError;" << endl << endl;

      *OutFile << "public class UniCharsRev" << endl;
      *OutFile << "{" << endl;
      *OutFile << "   public static int KPTTUCD_REV_WORD_CNT = 3;" << endl << endl;

//    *OutFile << "   public static int m_iaUniCharsRev[][" << KPTTUCD_REV_WORD_CNT << "] =" << endl;
      *OutFile << "   public static UniCharsRevElem m_aUniCharsRev[] =" << endl;
      *OutFile << "   {" << endl;

      KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
   }      

   if(SUCCEEDED(retc)) while(!InFile->eof() && SUCCEEDED(retc))
   {
      InFile->getline(in_str, KP_MAX_FILE_LIN_LEN);
      KP_ASSERT(!InFile->fail() || InFile->eof(), KP_E_FERROR, null, True);

      if(!InFile->eof() && SUCCEEDED(retc))
      {
         word_cnt = 0;
         KP_ASSERT(in_words == NULL, KP_E_SYSTEM_ERROR, null, True);
         
         if(SUCCEEDED(retc)) retc = SplitStrings(&in_words, &word_cnt, in_str, lpszSpaces, False);
         KP_ASSERT(in_words, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(word_cnt == KPTTUCD_REV_WORD_CNT, KP_E_FILE_FORMAT, in_str, True); 
         
         if(SUCCEEDED(retc)) *OutFile << "      new UniCharsRevElem((char)" << in_words[0] << ", " << in_words[1] << ", KpChar." << in_words[2] << ")," << endl;       
         KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
      }
      
      KP_DELETEA(in_words);
   } 

   if(SUCCEEDED(retc))
   {
      *OutFile <<   "   };" << endl << endl;

      *OutFile <<   "   public static void CheckData() throws ArrayIndexOutOfBoundsException, DataFormatException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "      KpError.SetPlace(\"UniCharsRev.CheckData() 0\");" << endl;
      *OutFile <<   "      if(m_aUniCharsRev.length != KpChar.C_CharSize0.ordinal()){ KpError.SetPlace(\"UniCharsRev.CheckData() 1\"); throw(new ArrayIndexOutOfBoundsException()); }" << endl << endl;

      *OutFile <<   "      for(int ii = 0; ii < m_aUniCharsRev.length; ii ++)" << endl;
      *OutFile <<   "     	 if(m_aUniCharsRev[ii].m_iOrdNum != m_aUniCharsRev[ii].m_KpCharEquiv.ordinal())" << endl;
      *OutFile <<   "      	    { KpError.SetPlace(\"UniCharsRev.CheckData() 2: \" + m_aUniCharsRev[ii].m_iOrdNum + \" \" + m_aUniCharsRev[ii].m_KpCharEquiv.ordinal()); throw(new DataFormatException()); }" << endl;
      *OutFile <<   "   }" << endl << endl;

      *OutFile <<   "   public static KpChar Decode(char cInCh)" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "   int cur_ix_min = 0;" << endl;
      *OutFile <<   "   int cur_ix_max = m_aUniCharsRev.length - 1;" << endl << endl;
   
      *OutFile <<   "   int cur_ix = cur_ix_min;" << endl;
      *OutFile <<   "      while(cur_ix_min < cur_ix_max)" << endl;
      *OutFile <<   "      {" << endl;
      *OutFile <<   "         cur_ix = cur_ix_min + (cur_ix_max - cur_ix_min) / 2;" << endl;
      *OutFile <<   "         if(cInCh > m_aUniCharsRev[cur_ix].m_cChar)" << endl;
      *OutFile <<   "         {" << endl;
      *OutFile <<   "            if(cur_ix_max <= cur_ix_min + 1) cur_ix_max = cur_ix;" << endl;
      *OutFile <<   "            cur_ix_min = cur_ix;" << endl;
      *OutFile <<   "         }" << endl;
      *OutFile <<   "         else if(cInCh < m_aUniCharsRev[cur_ix].m_cChar)" << endl;
      *OutFile <<   "         {" << endl;
      *OutFile <<   "            cur_ix_max = cur_ix;" << endl;
      *OutFile <<   "         }" << endl;
      *OutFile <<   "         else // if(cInCh == m_aUniCharsRev[cur_ix].m_cChar)" << endl;
      *OutFile <<   "         {" << endl;
      *OutFile <<   "            cur_ix_min = cur_ix;" << endl;
      *OutFile <<   "            cur_ix_max = cur_ix;" << endl;
      *OutFile <<   "         }" << endl;
      *OutFile <<   "      }" << endl << endl;
            
      *OutFile <<   "   return(m_aUniCharsRev[cur_ix].m_KpCharEquiv);" << endl;
      *OutFile <<   "   }" << endl;
      *OutFile <<   "}" << endl;

      KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
   } 
   
return(retc);
}


// --------------------------------------------------------------
HRESULT ProcessJavaKpCharWgt(fstream *InFile, fstream *OutFile)
{
HRESULT retc = S_OK;
static unsigned char in_str[KP_MAX_FILE_LIN_LEN + 1];
const unsigned char *pnts = null;
unsigned char *pntd = null;

   KP_ASSERT(InFile != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(OutFile != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      *OutFile << "// -----------------------------------------------------" << endl;
      *OutFile << "// This file is automatically generated - do not change" << endl;
      *OutFile << "// original source Unicode UTF-16 file - kpttu16.txt" << endl << endl;

      *OutFile << "package kplib.kpt;" << endl << endl;

      *OutFile << "import kplib.kpt.KpChar;" << endl;
      *OutFile << "import kplib_and.common.kperr.KpError;" << endl << endl;

      *OutFile << "public class KpCharWgt" << endl;
      *OutFile << "{" << endl;
      *OutFile << "   static KpCharWgtElem m_aKpCharWgt[] =" << endl;
      *OutFile << "   {" << endl;

      KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
   }      

   if(SUCCEEDED(retc)) while(!InFile->eof() && SUCCEEDED(retc))
   {
      InFile->getline(in_str, KP_MAX_FILE_LIN_LEN);
      KP_ASSERT(!InFile->fail() || InFile->eof(), KP_E_FERROR, null, True);

      if(!InFile->eof() && SUCCEEDED(retc))
      {
         pnts = in_str;
         while(strchr(lpszSpaces, *pnts) != null) pnts++;
         
         if((pnts[0] != '/') && (pnts[1] != '/'))
         {
            pntd = strchr(in_str, '(');
//          KP_ASSERT(pntd != null, KP_E_FILE_FORMAT, null, True);
            if((pntd != null) && SUCCEEDED(retc)) // eliminuojam tuðèias eilutes
            {
               *pntd++ = C_Nul;
            
               *OutFile << "      new " << pnts << "(KpChar." << pntd << endl;              
               KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
            }
         }
      }
   } 
   
   if(SUCCEEDED(retc))
   {
      *OutFile <<   "   };" << endl << endl;

      *OutFile <<   "   public static void CheckData() throws ArrayIndexOutOfBoundsException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "      KpError.SetPlace(\"KpCharWgt.CheckData() 0\");" << endl;
      *OutFile <<   "      if(m_aKpCharWgt.length != KpChar.C_CharSize0.ordinal()){ KpError.SetPlace(\"KpCharWgt.CheckData() 1\"); throw(new ArrayIndexOutOfBoundsException()); }" << endl;
      *OutFile <<   "   }" << endl << endl;

      *OutFile <<   "   public static int GetWgt(KpChar Chr) throws ArrayIndexOutOfBoundsException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "   int ii = Chr.ordinal();" << endl << endl;
   
      *OutFile <<   "      if((ii >= m_aKpCharWgt.length) || (ii < 0)){ KpError.SetPlace(\"KpCharWgt.GetWgt() 1\"); throw(new ArrayIndexOutOfBoundsException()); }" << endl << endl;
   
      *OutFile <<   "   return(m_aKpCharWgt[ii].m_iWeight);" << endl;
      *OutFile <<   "   }" << endl << endl;

      *OutFile <<   "// simbolio svoris, ignoruojant didþiàsias raides" << endl;
      *OutFile <<   "   public static int ToLowWgt(KpChar Chr) throws ArrayIndexOutOfBoundsException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "   int wgt = GetWgt(Chr);" << endl;
      *OutFile <<   "   return(wgt - wgt % 1000 + wgt % 100);" << endl;
      *OutFile <<   "   }" << endl << endl;
   
      *OutFile <<   "// simbolio svoris, sulyginant vienodo svorio liet. diakritines raides" << endl;   
      *OutFile <<   "   public static int RoundChWgt(KpChar Chr) throws ArrayIndexOutOfBoundsException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "   int wgt = GetWgt(Chr);" << endl;
      *OutFile <<   "   return(wgt - wgt % 100);" << endl;
      *OutFile <<   "   }" << endl << endl;

      *OutFile <<   "// simbolio svoris, sulyginant vienodo svorio liet. diakritines raides ir ignoruojant didþiàsias raides" << endl;
      *OutFile <<   "   public static int ToLowRoundChWgt(KpChar Chr) throws ArrayIndexOutOfBoundsException" << endl;
      *OutFile <<   "   {" << endl;
      *OutFile <<   "   int wgt = GetWgt(Chr);" << endl;
      *OutFile <<   "   return(wgt - wgt % 1000);" << endl;
      *OutFile <<   "   }" << endl;
      *OutFile <<   "}" << endl;

      KP_ASSERT(!OutFile->fail(), KP_E_FERROR, null, True);
   } 
   
return(retc);
}


// ================================================== main
//---------------------------------------------
int main(void)
{
HRESULT retc = S_OK;
HRESULT retc0;
static unsigned char dest_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char src_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_line[KP_MAX_FNAME_LEN * 2 + 100];
fstream in_file;
fstream out_file;

   printf("\nUnicode charset generator\n\n");

// ------------------------------------------------------
   if(SUCCEEDED(retc))
   {
//    strcpy(src_fname, "/home/kp/source/kpt/kpttu16.txt");
      strcpy(src_fname, "F:/kp/source/kpt/kpttu16.txt");
   }
   
// ------------------------------------------------------
   if(SUCCEEDED(retc))
   {
//    strcpy(dest_fname, "/home/kp/source/kpt/kpttuc.cpp");
      strcpy(dest_fname, "F:/kp/source/kpt/kpttuc.cpp");

      KP_NEWO(pKpttUcd, KpttUcd_tag(src_fname, dest_fname, UC_UTF_16));
   
      if(SUCCEEDED(retc)) retc = pKpttUcd->ProcessCpp();

      if(pKpttUcd!=NULL)
      {
         retc0 = pKpttUcd->CloseFiles(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc = retc0;
      }

      KP_DELETE(pKpttUcd);
   }

// ------------------------------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(dest_fname, "F:/kp/source/eclipse_workspace/kplib/src/kplib/kpt/UniChars.java");
//    strcpy(dest_fname, "F:/kp/source/eclipse_workspace/lzdshp_and/src/kplib/kpt/UniChars.java");

      KP_NEWO(pKpttUcd, KpttUcd_tag(src_fname, dest_fname, UC_UTF_16));
   
      if(SUCCEEDED(retc)) retc = pKpttUcd->ProcessJava();
      
      if(pKpttUcd!=NULL)
      {
         retc0 = pKpttUcd->CloseFiles(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc = retc0;
      }

      KP_DELETE(pKpttUcd);
   }

// ============================================================================
// ------------------------------------------------------ gaminam kodø masyvà inversinei UniChar á KpChar perkodavimo lentelei
   if(SUCCEEDED(retc)) 
   {
      strcpy(dest_fname, "F:/kp/source/eclipse_workspace/kplib/src/kplib/kpt/UniCharsRev.txt");
//    strcpy(dest_fname, "F:/kp/source/eclipse_workspace/lzdshp_and/src/kplib/kpt/UniCharsRev.txt");

      KP_NEWO(pKpttUcd, KpttUcd_tag(src_fname, dest_fname, UC_UTF_16));

      if(SUCCEEDED(retc)) retc = pKpttUcd->ProcessJavaRevContents();
      
      if(pKpttUcd!=NULL)
      {
         retc0 = pKpttUcd->CloseFiles(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc = retc0;
      }

      KP_DELETE(pKpttUcd);
   }

// ------------------------------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(cmd_line, "sort < ");
      strcat(cmd_line, dest_fname);
      strcat(cmd_line, " > ");
      strcat(cmd_line, dest_fname);
      strcpy(cmd_line + strlen(cmd_line) - 4, "_1.txt");
      
      system((const char *)cmd_line);
   }

// ------------------------------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(src_fname, "F:/kp/source/eclipse_workspace/kplib/src/kplib/kpt/UniCharsRev_1.txt");
//    strcpy(src_fname, "F:/kp/source/eclipse_workspace/lzdshp_and/src/kplib/kpt/UniCharsRev_1.txt");

      strcpy(dest_fname, "F:/kp/source/eclipse_workspace/kplib/src/kplib/kpt/UniCharsRev.java");
//    strcpy(dest_fname, "F:/kp/source/eclipse_workspace/lzdshp_and/src/kplib/kpt/UniCharsRev.java");
   }

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)src_fname, ios::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, src_fname, True); 

      if(SUCCEEDED(retc))
      {
         out_file.open((const char *)dest_fname, ios::out);
         KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, dest_fname, True);

         if(SUCCEEDED(retc))
         {
            retc = ProcessJavaRev(&in_file, &out_file);
   
            out_file.close();
            KP_ASSERT(!out_file.fail(), KP_E_FERROR, dest_fname, True);
         }
         
         in_file.close();
      }
   }
         
// ------------------------------------------------------ gaminam KpCharWgt.java
   if(SUCCEEDED(retc))
   {
      strcpy(src_fname, "F:/kp/source/kpt/KpCharWgt.cpp");

      strcpy(dest_fname, "F:/kp/source/eclipse_workspace/kplib/src/kplib/kpt/KpCharWgt.java");
//    strcpy(dest_fname, "F:/kp/source/eclipse_workspace/lzdshp_and/src/kplib/kpt/KpCharWgt.java");
   }

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)src_fname, ios::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, src_fname, True); 

      if(SUCCEEDED(retc))
      {
         out_file.open((const char *)dest_fname, ios::out);
         KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, dest_fname, True);

         if(SUCCEEDED(retc))
         {
            retc = ProcessJavaKpCharWgt(&in_file, &out_file);
   
            out_file.close();
            KP_ASSERT(!out_file.fail(), KP_E_FERROR, dest_fname, True);
         }
         
         in_file.close();
      }
   }
         
system("pause");

return(RET_CODE_MAIN(retc));
}
