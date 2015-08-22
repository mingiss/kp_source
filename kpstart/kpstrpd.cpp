// ---------------------------
// kpstrpd.cpp; Pradzia_<...>.exe
// flash'o paleidejas - paleidzia programa, kurios failo vardas tarp Pradzia_ ir .exe
// spec. zenklu kodavimas: (b) = '\'
//                         (u) = '_'
//                         (a) = '@'
//                         (d) = '.'
//                         (q) = '\"'
//                         (p) = '\''
//                         _   = ' '
//                         (f) = atmintuko flash dalies árenginio vardas su sleðu
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>
#include <string>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
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
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"


// -----------------------------------------
#define KPSTRPD_PREFIX ((const unsigned char *)"pradzia_")

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstrpd";
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;
int iUpdNumGlob = -1;

class Kpstrpd : public KpStApp
{
public:
   HRESULT GetIniFileName(const unsigned char *lpszProgPath/* ne daugiau [KP_MAX_FNAME_LEN + 1] */, unsigned char *lpszIniFname/* ne maþiau [KP_MAX_FNAME_LEN + 1] */);
   HRESULT ExtractCmdStr(const unsigned char *lpszProgPath/* ne daugiau [KP_MAX_FNAME_LEN + 1] */, unsigned char *lpszCmdStr/* ne maþiau [KP_MAX_FNAME_LEN + 1] */);
}
theApp;

#if FALSE
int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};
#endif

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 + 1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,
   ResetRestDays_RC,

   RegSert_RC,
   UnRegSert_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ----------------------------------
HRESULT Kpstrpd::GetIniFileName(const unsigned char *lpszProgFname, unsigned char *lpszIniFname)
{
HRESULT retc = S_OK;
const unsigned char *pnts = null;
const unsigned char *pnts1 = null;
unsigned char *pntd = null;

   if(SUCCEEDED(retc))
   {
      pnts = strstr(lpszProgFname, ".exe");
      if(pnts == null) pnts = strstr(lpszProgFname, ".bin");
      KP_ASSERT(pnts, E_INVALIDARG, null, True);
   }

   if(SUCCEEDED(retc))
   {
      pnts1 = pnts;
      do
      {
         if((*pnts1 == '\\') || (pnts1 == lpszProgFname)) break;
         --pnts1;

      } while True;
   }
   if(SUCCEEDED(retc)) if(*pnts1 == '\\') pnts1++;

   if(SUCCEEDED(retc))
   {
      pntd = lpszIniFname;
      while(pnts1 < pnts) *pntd++ = *pnts1++;

      strcpy(pntd, ".ini");
   }

return(retc);
}


// ----------------------------------
HRESULT Kpstrpd::ExtractCmdStr(const unsigned char *lpszProgPath, unsigned char *lpszCmdStr)
{
HRESULT retc = S_OK;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
bool end_fl = False;

   KP_ASSERT(lpszProgPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszCmdStr, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszProgPath;
      pntd = lpszCmdStr;
      end_fl = False;

      do
      {
         if(*pnts == Nul) end_fl = True;

         if((!end_fl) && SUCCEEDED(retc))
            if(strstr(pnts, ".exe") == pnts) end_fl = True;
         if((!end_fl) && SUCCEEDED(retc))
            if(strstr(pnts, ".bin") == pnts) end_fl = True;

         if((!end_fl) && SUCCEEDED(retc))
         {
            if(strstr(pnts, "(b)") == pnts){ pnts += strlen("(b)"); *pntd++ = '\\';}
            else if(strstr(pnts, "(u)") == pnts){ pnts += strlen("(u)"); *pntd++ = '_';}
            else if(strstr(pnts, "(a)") == pnts){ pnts += strlen("(a)"); *pntd++ = '@';}
            else if(strstr(pnts, "(d)") == pnts){ pnts += strlen("(d)"); *pntd++ = '.';}
            else if(strstr(pnts, "(q)") == pnts){ pnts += strlen("(q)"); *pntd++ = '\"';}
            else if(strstr(pnts, "(p)") == pnts){ pnts += strlen("(p)"); *pntd++ = '\'';}
            else if(*pnts == '_'){ pnts++; *pntd++ = Spc;} // ' '
            else if(strstr(pnts, "(f)") == pnts)
            {
               pnts += strlen("(f)");
               strcpy(pntd, m_lpszFlashDevName);
               pntd += strlen(m_lpszFlashDevName);
               *pntd++ = '\\';
            }
            else *pntd++ = *pnts++;
         }

      } while((!end_fl) && SUCCEEDED(retc));

      *pntd = Nul;

   } // if(SUCCEEDED(retc))

return(retc);
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char cmd_str[KP_MAX_FNAME_LEN + 1];
static unsigned char prog_fname[KP_MAX_FNAME_LEN * 2 + 100];
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
unsigned char *pntdd = NULL;
DWORD ll;
bool setup_perf = False;
Kpstrpd *app_ptr = NULL;
unsigned char ini_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];

// --------------------------------
   strcpy(ini_fname, "kpstart.ini");
   cmd_str[0] = Nul;

// -------------------------------
   app_ptr = (&theApp);
   theKpStAppPtr = static_cast<KpStApp *> (&theApp);

   if(SUCCEEDED(retc)) retc = app_ptr->GetOpenResult();

// --------------------------------
   if(SUCCEEDED(retc)) retc = GetAppName(prog_fname);

   if(SUCCEEDED(retc))
   {
      pntd = strstr(prog_fname, KPSTRPD_PREFIX);
      KP_ASSERT(pntd, E_INVALIDARG, prog_fname,
#ifdef Debug
         False);
#else
         True);
#endif
   }

// --------------------------------
   if(pntd && SUCCEEDED(retc))
   {
// prog_fname - paleidimo kelias su '\\' gale
      *pntd = Nul;
//    if(pntd > prog_fname) if(*(pntd - 1) == '\\') *(pntd - 1) = Nul;

// paleidimo komandos galas --> cmd_str
      pnts = pntd + strlen(KPSTRPD_PREFIX);

// ------------------------------- pirmà kartà – dar be m_lpszFlashDevName
      if(SUCCEEDED(retc)) retc = app_ptr->ExtractCmdStr(pnts, cmd_str);

// ------------------------------- ieðkom pririðto atmintuko, bus nustatytas m_lpszFlashDevName
      if(SUCCEEDED(retc)) retc = app_ptr->GetIniFileName(cmd_str, ini_fname);

   } // if(pntd && SUCCEEDED(retc))

   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStrpdMode);

// ------------------------------- dar kartà – dabar jau su nustatytu m_lpszFlashDevName
   if(cmd_str[0] && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = app_ptr->ExtractCmdStr(pnts, cmd_str);

// ---------------------------------------------
// sulipdom su paleidimo komandos pradþia
      if(SUCCEEDED(retc)) if(strstr(pnts, "(f)") == null) // jei yra m_lpszFlashDevName, tada kelias absoliutus, lipdyti nereikia
      {
         strcat(prog_fname, cmd_str);
         strcpy(cmd_str, prog_fname);
      }
      if(SUCCEEDED(retc)) strcpy(prog_fname, cmd_str);

// -------------------------------- TUX IPA per anksti nusistato cur. dir. – nepavyksta teisingai iðgauti GetAppName()
//                      GetCommandLine() dar su pakatalogiu, o GetFullPathName() generuoja jau ið to pakatalogio vidaus
//                      dabar turëtø bût jau gerai – prilipdëm paleidimo komandos pradþià, einamasis katalogas neturëtø átakoti
//                      GetFullPathName() jau kaip ir nereikëtø – ir taip jau pilnas
      if(SUCCEEDED(retc))
      {
         ll = GetFullPathName((const char *)cmd_str, KP_MAX_FNAME_LEN, (char *)prog_fname, NULL);
         if(!ll) retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
         else if(ll >= KP_MAX_FNAME_LEN)
            retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      }

// --------------------------------
// nukerpam failo vardà - paliekam tik kelià --> cmd_str
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_str, prog_fname); // atgal á cmd_str - dabar èia bus paleidimo kelias
         pntd = cmd_str;
         do
         {
            pntdd = strchr(pntd + 1, '\\');
            if(pntdd) pntd = pntdd;
         } while(pntdd);
         *pntd = Nul;
      }

// --------------------------------
   } // if(cmd_str[0])

// --------------------------------
// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
// cur_dir – ne darbinis, o kpstrpd.exe paleidimo katalogas
// jau turëjom prog_fname, sugadinom – gal atsimint? Tik buvo su sleðu gale.
   if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, False);

// --------------------------------
// setupà vykdyti nuo paleidþiamos programos katalogo – ten guli visi diegimo failai
   if(SUCCEEDED(retc)) retc = ProcessSetup(/* cur_dir */ cmd_str, &setup_perf);

// --------------------------------
#if FALSE // gal nereikia – na, neásiraðys kai kas á registrà – bet nors ið principo veiks
   if(SUCCEEDED(retc)) if((iWindowsVersion >= WinVistaC) && IsUserAdmin())
   {
      if(setup_perf) KpMsgOut(KP_MSG_NOW_NOT_ADMIN, IDI_ASTERISK, KP_MB_TESTI);
      else KpMsgOut(KP_MSG_NOT_ADMIN, IDI_ERROR, KP_MB_TESTI);
      retc = KP_E_ACCESS_DENIED;
   }
#endif

// TODO !!! KpMsgOutF_0(cmd_str); // cmd_str nukirpti failo vardà gale – palikti tik path – sunku atsekt,
//    kai path su tarpais, veikia ir taip

// TODO !!! prog_fname - jei exe'ko failas aprëmintas kabutëmis (kai yra tarpø – IPA atmintukai – pradþioje
//    pridedant pilnà kelià, pirmà kabutæ iðkelti á prieká)

// pridedam darbiná kataloga kaip parametrà
#ifndef DONT_APPEND_CUR_DIR
   if(cur_dir[0] /* cmd_str[0] */ && SUCCEEDED(retc))
   {
      strcat(prog_fname, " \"");
      strcat(prog_fname, cur_dir);  // kodël kpstrpd paleidimo katalogà, o ne programos paleidimo katalogà (cmd_str)?
                                    // turbût èia kai paleidþiamas kpstart.exe yra atmintuke, o darbiná katalogà reikia nustatyt ið 
                                    //    CDROM-inës dalies, ten kur .pdf, ið ten paleidþiamas ir kpstrpd.exe  
      strcat(prog_fname, "\\\"");

   } // if(cmd_str[0] && SUCCEEDED(retc))
#endif
   
   if(SUCCEEDED(retc)) retc = StartProcess(prog_fname /* cmd_str */, cmd_str /* KPST_CUR_DIR */, NULL, NULL, SW_SHOWNORMAL);

// /* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();
   /* if(SUCCEEDED(retc)) */ retc0 = app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0;

return(RET_CODE_WIN(retc));
}
