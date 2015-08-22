// ---------------------------
// kpstresq.cpp
// AcroRead60 rezultatu gelbejimas is My Documents/rezultatai.txt
//
// pervadinti i resq.exe
// start.ini kopijuoti i resq.ini
// resq.ini faile istrinti prologo .bmp failo varda
// prijungia glob.js 
// prijungia rezultatai.txt is lokalaus resq.exe katalogo (is kurio paleidziama resq.exe) 
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperrno.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstmsg.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"
#include "kpstart.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
const unsigned char lpszProdName[] = "kpresq"; 
int iProdVerGlob=0;
KpErrorProcClass KpErrorProc(True, 71);
KpStartApp theApp;
bool bServiceFl=False;
int iUpdNumGlob = -1;
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[]={"c:\\arkim\\rezultatai\\kpstart.log"};
#endif

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,
   
   CheckResRequest_RC,
   CheckRelRequest_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK; 
static unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
static unsigned char msg_buf[KP_MAX_FNAME_LEN+200+1];
int msg_len = 0;
DWORD ll;
// FILE *js_file = NULL;
// FILE *js_log_file = NULL;
// FILE *js_sav_file = NULL;
// static unsigned char js_fname[KP_MAX_FNAME_LEN+1];
// static unsigned char js_log_fname[KP_MAX_FNAME_LEN+1];
// static unsigned char js_sav_fname[KP_MAX_FNAME_LEN+1];
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
// bool cur_js_extracted = False;
static unsigned char in_line[KP_MAX_FILE_LIN_LEN+1];
// unsigned char **words=NULL;
// int word_cnt;
// unsigned char rez_var[KP_MAX_FNAME_LEN+1];
// unsigned char *pntd;
bool data_ok=False;
static unsigned char arc_file_name[KP_MAX_FNAME_LEN+1];
static unsigned char rez_file_name[KP_MAX_FNAME_LEN+1];
FILE *arc_file = NULL;
FILE *rez_file = NULL;
bool cur_rez_extracted = False;
unsigned char dat_fname[KP_MAX_FNAME_LEN+1];
unsigned char svr_dat_fname[KP_MAX_FNAME_LEN+100];
unsigned char *contents_ptr = NULL;
long file_len;
FILE *dat_file = NULL;
 

// theKpStAppPtr = static_cast<KpStApp *> (&theApp);
   theKpStAppPtr = (&theApp);
   
// ------------------------------- 
   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode);

// -------------------------------
   if(SUCCEEDED(retc)) retc = theApp.GetIniRezFName(dat_fname);

// -------------------------------
// per glob.js rezultatø jau neperduodam
#if FALSE
   if(SUCCEEDED(retc)) retc=theApp.GetIniRezVar(rez_var);

// -------------------------------
   if(SUCCEEDED(retc))
   {
      theApp.m_PdfParBuf[0]=Nul;
      CutInitTrailSpcs(rez_var);
      pntd=rez_var+strlen(rez_var);
      while(pntd>rez_var)
      {
         if(TvStrChr(lpszWordDelims, (KpChar)*(pntd-1))!=NULL) pntd--;
         else break;
      }             
      *pntd=Nul;
      
      words = NULL;
      retc = SplitStrings(&words, &word_cnt, rez_var, lpszWordDelims, False);
   }
   
// ---------------------------------------- glob.*
   if(SUCCEEDED(retc)) retc=theApp.GetGlobalJsName(js_fname);
   if(SUCCEEDED(retc)) retc=CreatePath(js_fname, False);
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, js_fname);

// ---------------------------------------- glob.log
   if(SUCCEEDED(retc))
   {
      strcpy(js_log_fname, disk);
      strcat(js_log_fname, path);
      strcat(js_log_fname, "\\");
      strcat(js_log_fname, name);
      strcat(js_log_fname, HIST_FILE_TYPE);

      js_log_file=fopen((const char *)js_log_fname, "r");
      if(js_log_file!=NULL)
      {
         do
         {
            cur_js_extracted = False;
            js_file = NULL;
            if(SUCCEEDED(retc))
            {
               js_file = fopen((const char *)js_fname, "w");
               if(!js_file)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) do
            {
               if(SUCCEEDED(retc))
               {
                  fgets((char *)in_line, KP_MAX_FILE_LIN_LEN, js_log_file);
                  if(ferror(js_log_file))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) if(feof(js_log_file)) cur_js_extracted = True;

               if((!cur_js_extracted) && SUCCEEDED(retc))
               {
                  if(strstr(in_line, "---") != NULL) cur_js_extracted = True;
                  else
                  {
                     fputs((const char *)in_line, js_file);
                     if(ferror(js_file))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
                  }
               }
            
            } while((!cur_js_extracted) && SUCCEEDED(retc));

            if(js_file /* && SUCCEEDED(retc) */)
               if(fclose(js_file))
               {
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc)) retc = retc0;
               }
            js_file = NULL;      
                  
            if(SUCCEEDED(retc))
               retc = theApp.GetPdfPars(theApp.m_PdfParBuf, KP_MAX_FILE_LIN_LEN, (const unsigned char **)words, &data_ok);

// KpMsgOut(theApp.m_PdfParBuf, IDI_ASTERISK, KP_MB_TESTI);

            if(/* data_ok && */ SUCCEEDED(retc))
               if(strlen(theApp.m_PdfParBuf)>0)
                  /* retc = */ theApp.WriteDataFile(theApp.m_PdfParBuf, NULL, NULL, False, False);

         } while((!feof(js_log_file)) && SUCCEEDED(retc));
         
         /* if(SUCCEEDED(retc)) */ if(fclose(js_log_file))
         {
            /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);
         }
         js_log_file = NULL; 
         
      } // if(js_log_file!=NULL)
      
      retc = S_OK; // toliau ieskosim nekreipdami demesio i nieka
   
   } // if(SUCCEEDED(retc))
   

// ---------------------------------------- glob.sav
   if(SUCCEEDED(retc))
   {
      strcpy(js_sav_fname, disk);
      strcat(js_sav_fname, path);
      strcat(js_sav_fname, "\\");
      strcat(js_sav_fname, name);
      strcat(js_sav_fname, SAV_FILE_TYPE);

      if(SUCCEEDED(retc))
         if(!CopyFile((const char *)js_sav_fname, (const char *)js_fname, False))
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
         retc = theApp.GetPdfPars(theApp.m_PdfParBuf, KP_MAX_FILE_LIN_LEN, (const unsigned char **)words, &data_ok);

      if(/* data_ok && */ SUCCEEDED(retc))
         if(strlen(theApp.m_PdfParBuf)>0)
            /* retc = */ theApp.WriteDataFile(theApp.m_PdfParBuf, NULL, NULL, False, False);

// trinam glob.js
      if(SUCCEEDED(retc))
      {
         js_file = NULL;
         js_file = fopen((const char *)js_fname, "w");
         if(!js_file)
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);
         
         if(js_file) if(fclose(js_file))
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc = retc0;
         }
         js_file = NULL;
      }

      retc = S_OK; // rezultatai.log dorosim, net jei ir klaida
   
   } // if(SUCCEEDED(retc))

#endif


// ---------------------------------------- rezultatai.log
   if(SUCCEEDED(retc)) retc=GetLocalPath(rez_file_name, KP_My_Documents); 
   if(SUCCEEDED(retc))
   {
      strcpy(arc_file_name, rez_file_name);
      strcat(rez_file_name, KPST_REZ_FILE_NAME);
      strcat(arc_file_name, KPST_REZ_LOG_FILE_NAME);
   
      arc_file=fopen((const char *)arc_file_name, "r");
      if(arc_file!=NULL)
      {
         do
         {
            cur_rez_extracted = False;
            rez_file = NULL;
            if(SUCCEEDED(retc))
            {
               rez_file = fopen((const char *)rez_file_name, "w");
               if(!rez_file)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) do
            {
               if(SUCCEEDED(retc))
               {
                  fgets((char *)in_line, KP_MAX_FILE_LIN_LEN, arc_file);
                  if(ferror(arc_file))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) if(feof(arc_file)) cur_rez_extracted = True;

               if((!cur_rez_extracted) && SUCCEEDED(retc))
               {
//                if(strlen(in_line)!=0)
                  if((in_line[0] != '\r') && (in_line[0] != '\n')) 
                  {
// KpMsgOut(in_line, IDI_ASTERISK, KP_MB_TESTI);
                     fputs((const char *)in_line, rez_file);
                     if(ferror(rez_file))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
                     cur_rez_extracted = True;
                  }
               }
            
            } while((!cur_rez_extracted) && SUCCEEDED(retc));

            if(rez_file /* && SUCCEEDED(retc) */)
               if(fclose(rez_file))
               {
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc)) retc = retc0;
               }
            rez_file = NULL;      

            if(SUCCEEDED(retc))
               retc = theApp.GetFilePars(theApp.m_FileDataBuf, KP_MAX_FILE_LIN_LEN, &data_ok, KP_My_Documents);

            if(/* data_ok && */ SUCCEEDED(retc))
               if(strlen(theApp.m_FileDataBuf)>0)
                  /* retc = */ theApp.WriteDataFile(theApp.m_FileDataBuf, NULL, NULL, False, False);

         } while((!feof(arc_file)) && SUCCEEDED(retc));
         
         /* if(SUCCEEDED(retc)) */ if(fclose(arc_file))
         {
            /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);
         }
         arc_file = NULL; 
         
      } // if(arc_file!=NULL)
      
      if(SUCCEEDED(retc))
         if(!DeleteFile((const char *)rez_file_name))
            /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

      retc = S_OK; // toliau ieskosim nekreipdami demesio i nieka
   
   } // if(SUCCEEDED(retc))


// ----------------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(msg_buf, "Nukopijuokite failà rezultatai.txt á ");
      msg_len = strlen(msg_buf);
      
//    retc=GetLocalPath(msg_buf+strlen(msg_buf), KP_LocalDir);
      ll = GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)(msg_buf + msg_len), NULL);
      if(!ll) 
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      else if(ll >= KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
   {
      msg_buf[msg_len + KP_MAX_FNAME_LEN] = Nul;
      KpMsgOut(msg_buf, IDI_ASTERISK, KP_MB_TESTI);
   }


// ---------------------------------- èia bus prijungti paskutinis lokalus rezultatai.txt
   /* if(SUCCEEDED(retc)) */ retc0 = theApp.CloseStApp(retc, KP_LocalDir);  if(SUCCEEDED(retc)) retc=retc0;


// ---------------------  sprendimai_bebras_b.dat – prijungiam serverio rezultatus
   retc = S_OK; // èia tam atvejui, jei neturim rezultatai.txt ir theApp.CloseStApp() duoda klaidà "rezultatø rasti nepavyko" 
// if(SUCCEEDED(retc)) retc = theApp.GetIniRezFName(dat_fname);

   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, dat_fname);

   if(SUCCEEDED(retc))
   {
      strcpy(svr_dat_fname, disk);
      strcat(svr_dat_fname, path);
      strcat(svr_dat_fname, "\\sprendimai_");
      strcat(svr_dat_fname, name);
      strcat(svr_dat_fname, ".");
      strcat(svr_dat_fname, type);

      retc = ReadFileContents(svr_dat_fname, &contents_ptr, &file_len, False, True);

      if(contents_ptr && SUCCEEDED(retc))
      {
         dat_file = fopen((const char *)dat_fname, "ab");
         KP_ASSERT(dat_file, KP_E_DIR_ERROR, dat_fname, True);
         
         if(SUCCEEDED(retc)) if(fwrite(contents_ptr, 1, file_len, dat_file) != file_len) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

         if(dat_file) fclose(dat_file);
         dat_file = NULL;
      }

      retc = S_OK;
   }      
   
   KP_DELETEA(contents_ptr);


// ------------------------------------
// KP_DELETEA(words);

return(RET_CODE_WIN(retc));
}
