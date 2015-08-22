// ---------------------------
// StartSel.cpp
// Keliø programø paleidimas ið meniu
// Pradzia.exe, Papildomos funkcijos.exe
//

// #define KPSTSEL_DONT_ASK_MIKO_LIC // nereikalauti ávesti MIKO lic. kodo

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>
#include <string>

#include <b64/encode.h>
#include <b64/decode.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpmsg.h"
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
#include "StartSel.h"
#include "StartSel_en.h"
#include "StartSel_lt.h"
#include "StartSel_pl_1250.h"
#include "StartSel_pl_1257.h"
#include "StartSel_ru.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "StartSel"; 
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;    
StartSel StartSelObj;

// -----------------------------------------
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8+1]=
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
COLORREF KpColorSchemeLocal[KpNumOfShadows3]={ // KpColorScheme[KpNumOfShadows2]={
RGB(251,249,241), // RGB(255,247,239), // RGB(208,199,178), // RGB(249,239,214), // RGB_Lightyellow,
RGB_White, // RGB(255,244,218)
RGB(99,6,0), // RGB(132,6,0), // RGB_Brown,
RGB_Black,
RGB(250,244,234), // RGB(249,239,214), // RGB_Lightyellow,
RGB_White,
RGB(190,130,79),
RGB_Blue,
};


// ------------------------------------ StartSel.exe praneðimai
const unsigned char *lpszaStartSelMessages[NumOfStartSelMessages_2][KpNumOfLangs_2] =
{
STARTSEL_MSG_NOT_ADMIN_EN,              STARTSEL_MSG_NOT_ADMIN_LT,              STARTSEL_MSG_NOT_ADMIN_PL_1250,              STARTSEL_MSG_NOT_ADMIN_PL_1257,              STARTSEL_MSG_NOT_ADMIN_RU,              STARTSEL_MSG_NOT_ADMIN_RU,              // "Ðiam veiksmui turite bûti prisijungæs administratorium.")
STARTSEL_MSG_SURE_RESTORING_EN,         STARTSEL_MSG_SURE_RESTORING_LT,         STARTSEL_MSG_SURE_RESTORING_PL_1250,         STARTSEL_MSG_SURE_RESTORING_PL_1257,         STARTSEL_MSG_SURE_RESTORING_RU,         STARTSEL_MSG_SURE_RESTORING_RU,         // "Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi katalogø „Mano_...” failai ir naudotojo duomenys.\n \nAr sutinkate?")
STARTSEL_MSG_RESTORING_EN,              STARTSEL_MSG_RESTORING_LT,              STARTSEL_MSG_RESTORING_PL_1250,              STARTSEL_MSG_RESTORING_PL_1257,              STARTSEL_MSG_RESTORING_RU,              STARTSEL_MSG_RESTORING_RU,              // "Atstatomas failas...")
STARTSEL_MSG_RESTORING_FILE_EN,         STARTSEL_MSG_RESTORING_FILE_LT,         STARTSEL_MSG_RESTORING_FILE_PL_1250,         STARTSEL_MSG_RESTORING_FILE_PL_1257,         STARTSEL_MSG_RESTORING_FILE_RU,         STARTSEL_MSG_RESTORING_FILE_RU,         // "Atstatomas failas %s.%s...")
STARTSEL_MSG_RESTORED_EN,               STARTSEL_MSG_RESTORED_LT,               STARTSEL_MSG_RESTORED_PL_1250,               STARTSEL_MSG_RESTORED_PL_1257,               STARTSEL_MSG_RESTORED_RU,               STARTSEL_MSG_RESTORED_RU,               // "Pradiniai duomenys sëkmingai atstatyti.")
STARTSEL_MSG_ARC_EXIST_EN,              STARTSEL_MSG_ARC_EXIST_LT,              STARTSEL_MSG_ARC_EXIST_PL_1250,              STARTSEL_MSG_ARC_EXIST_PL_1257,              STARTSEL_MSG_ARC_EXIST_RU,              STARTSEL_MSG_ARC_EXIST_RU,              // "Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
STARTSEL_MSG_ARC_CREATED_EN,            STARTSEL_MSG_ARC_CREATED_LT,            STARTSEL_MSG_ARC_CREATED_PL_1250,            STARTSEL_MSG_ARC_CREATED_PL_1257,            STARTSEL_MSG_ARC_CREATED_RU,            STARTSEL_MSG_ARC_CREATED_RU,            // "Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
STARTSEL_MSG_LOW_DISK_SPACE_EN,         STARTSEL_MSG_LOW_DISK_SPACE_LT,         STARTSEL_MSG_LOW_DISK_SPACE_PL_1250,         STARTSEL_MSG_LOW_DISK_SPACE_PL_1257,         STARTSEL_MSG_LOW_DISK_SPACE_RU,         STARTSEL_MSG_LOW_DISK_SPACE_RU,         // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
STARTSEL_MSG_DIR_ACCESS_ERROR_EN,       STARTSEL_MSG_DIR_ACCESS_ERROR_LT,       STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1250,       STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1257,       STARTSEL_MSG_DIR_ACCESS_ERROR_RU,       STARTSEL_MSG_DIR_ACCESS_ERROR_RU,       // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
STARTSEL_MSG_NO_ARC_EN,                 STARTSEL_MSG_NO_ARC_LT,                 STARTSEL_MSG_NO_ARC_PL_1250,                 STARTSEL_MSG_NO_ARC_PL_1257,                 STARTSEL_MSG_NO_ARC_RU,                 STARTSEL_MSG_NO_ARC_RU,                 // "Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
STARTSEL_MSG_ARC_FOUND_EN,              STARTSEL_MSG_ARC_FOUND_LT,              STARTSEL_MSG_ARC_FOUND_PL_1250,              STARTSEL_MSG_ARC_FOUND_PL_1257,              STARTSEL_MSG_ARC_FOUND_RU,              STARTSEL_MSG_ARC_FOUND_RU,              // "Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
STARTSEL_MSG_ARC_RESTORED_EN,           STARTSEL_MSG_ARC_RESTORED_LT,           STARTSEL_MSG_ARC_RESTORED_PL_1250,           STARTSEL_MSG_ARC_RESTORED_PL_1257,           STARTSEL_MSG_ARC_RESTORED_RU,           STARTSEL_MSG_ARC_RESTORED_RU,           // "Atsarginë kopija sëkmingai atstatyta.")
STARTSEL_MSG_LOW_FLASH_SPACE_EN,        STARTSEL_MSG_LOW_FLASH_SPACE_LT,        STARTSEL_MSG_LOW_FLASH_SPACE_PL_1250,        STARTSEL_MSG_LOW_FLASH_SPACE_PL_1257,        STARTSEL_MSG_LOW_FLASH_SPACE_RU,        STARTSEL_MSG_LOW_FLASH_SPACE_RU,        // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
STARTSEL_MSG_FLASH_ACCESS_ERROR_EN,     STARTSEL_MSG_FLASH_ACCESS_ERROR_LT,     STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1250,     STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1257,     STARTSEL_MSG_FLASH_ACCESS_ERROR_RU,     STARTSEL_MSG_FLASH_ACCESS_ERROR_RU,     // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_EN, STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT, STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1250, STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1257, STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_RU, STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_RU, // "Uþverkite visus MIKO knygos failus.")
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -------------------------------------------
StartSel::StartSel(void)
{
   ClearMembers();
}


// -------------------------------------------
StartSel::~StartSel()
{
int ii;

   KP_DELETE(m_BackgroundBmpPars);

   for(ii = 0; ii < MAX_NUM_START_ITEMS; ii++)
   {
      KP_DELETE(m_pButtonBmpPars[ii]);

      KP_DELETE(m_pButHlBmpPars[ii]);

      KP_DELETE(m_pButSelBmpPars[ii]);
   } 
}


// -------------------------------------------
void StartSel::ClearMembers(void)
{
int ii;

   m_bMikoPapFun = False;
   m_hDialogWindow = NULL;
   m_BackgroundBmpPars = NULL;
   m_lpszBackground[0] = Nul;

   m_iItemsCount = 0;
   
   m_iHorMargin = START_SEL_WND_MARGIN;
   m_iVertMargin = START_SEL_WND_MARGIN;
   m_iButMargin = START_SEL_BUT_MARGIN;

   for(ii = 0; ii < MAX_NUM_START_ITEMS; ii++)
   {
      m_iItemTypes[ii] = NoStartSelIx;
      m_alpszItems[ii][0] = Nul;
      m_alpszButtonsHighlight[ii][0] = Nul;
      m_alpszButtonsSelected[ii][0] = Nul;
      m_pButtonBmpPars[ii] = NULL;
      m_pButHlBmpPars[ii] = NULL;
      m_pButSelBmpPars[ii] = NULL;
      m_hButtonCtrls[ii] = NULL;

      m_iActionTypes[ii] = NoStartSelIx;
      m_alpszActions[ii][0] = Nul;
   }

   m_bInProgress = False;
}

   
// -------------------------------------------
#if TRUE // #ifdef Debug
HRESULT StartSel::DumpMembers(void)
{
HRESULT retc=S_OK;
int ii;

   KP_ASSERT(m_iItemsCount < MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      PutLogMessage_ /* KP_TRACE */("------------------------------");
      PutLogMessage_ /* KP_TRACE_2 */("%s: %s", lpszaStartSelKwds[MainBackgroundIx], m_lpszBackground);
   }
   
   if(SUCCEEDED(retc)) for(ii = 0; ii < m_iItemsCount; ii++)
   {
      PutLogMessage_ /* KP_TRACE_3 */("%s[%d]: %s  action: %s  pars: %s", lpszaStartSelKwds[ButtonImageIx], ii, m_alpszItems[ii], lpszaStartSelKwds[m_iActionTypes[ii]], m_alpszActions[ii]);
//    PutLogMessage_ /* KP_TRACE_3 */("%s[%d]: %s", lpszaStartSelKwds[StartActionIx], ii, m_alpszActions[ii]);
   }

return(retc);
}
#endif

   
// -------------------------------------------
HRESULT StartSel::ParseStartSelCfgLine(const unsigned char *lpszCfgLine, const unsigned char *lpszCfgFname)
{
HRESULT retc = S_OK;
static unsigned char in_str[KP_MAX_FILE_LIN_LEN + 1];
unsigned char *val_ptr = NULL;
StartSelKwdIxs kwd_ix;
unsigned char *pnts = NULL;
int ii;

   KP_ASSERT(lpszCfgLine != null, E_INVALIDARG, null, True); 
   KP_ASSERT(strlen(lpszCfgLine) < KP_MAX_FILE_LIN_LEN, KP_E_BUFFER_OVERFLOW, null, True); 

   if(SUCCEEDED(retc)) strcpy(in_str, lpszCfgLine);
   
   if(SUCCEEDED(retc))
   {
      val_ptr = strchr(in_str, '=');
      if(val_ptr == NULL)
      {
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
         if(SUCCEEDED(retc)) if((in_str[0] != ';') && (in_str[0] != Nul))
            retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str /* fname */, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         *val_ptr++ = Nul;
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(val_ptr);

         kwd_ix = NoStartSelIx;
         if(SUCCEEDED(retc))
         {
            retc = GetKwrdIndex((int *)(&kwd_ix), in_str, lpszaStartSelKwds, -1, False, True);
            if(retc == KP_E_KWD_NOT_FOUND)
            {
            /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
               retc = S_OK;
            }
            else if(SUCCEEDED(retc))
            {
               if((kwd_ix == EditUserDataIx) || (kwd_ix == SaveCopyActionIx) || 
                  (kwd_ix == RestoreCopyActionIx) || (kwd_ix == RestoreActionIx))
                     m_bMikoPapFun = True;                  
            
               switch(kwd_ix)
               {
               case PaletteIx:
                  pnts = val_ptr;
                  ii = 0;
                  while(*pnts && SUCCEEDED(retc))
                  {
                     while(*pnts && (!TvIsHexDigit(*pnts))) pnts++;
                     if(*pnts)
                     {
                        KP_ASSERT(sscanf((const char *)pnts, "%lx", &(KpColorSchemeLocal[ii])) == 1, KP_E_FILE_FORMAT, pnts, True);
                        KP_ASSERT(ii < MAX_NUM_START_ITEMS, KP_E_FILE_FORMAT, val_ptr, True);
                        if(SUCCEEDED(retc))
                        { 
                           ii++;                              
                           while(*pnts && TvIsHexDigit(*pnts)) pnts++;
                        }
                     }
                  }
                  break;

               case MainBackgroundIx:
                  KP_ASSERT(strlen(val_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, val_ptr, True);
                  KP_ASSERT(m_lpszBackground[0] == Nul, KP_E_DOUBLE_CALL, val_ptr, True);

                  if(SUCCEEDED(retc)) strcpy(m_lpszBackground, val_ptr);
                  break;

               case ButtonImageIx:
               case ButtonTextIx:
                  if((m_iItemsCount == 0) && SUCCEEDED(retc)) m_iItemsCount++;

                  KP_ASSERT(m_iItemsCount <= MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc)) if(m_alpszItems[m_iItemsCount - 1][0])
                  {
                     KP_ASSERT(m_iItemsCount < MAX_NUM_START_ITEMS, KP_E_BUFFER_OVERFLOW, val_ptr, True);
                     if(SUCCEEDED(retc)) m_iItemsCount++;
                  }               

                  KP_ASSERT(strlen(val_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, val_ptr, True);

                  if(SUCCEEDED(retc))
                  {
                     m_iItemTypes[m_iItemsCount - 1] = kwd_ix; // ButtonImageIx;
                     strcpy(m_alpszItems[m_iItemsCount - 1], val_ptr);
                  }
                  
                  break;

               case ButtonHighlightIx:
                  KP_ASSERT(m_iItemsCount > 0, KP_E_FILE_FORMAT, lpszCfgFname /* START_SEL_CFG_FNAME */, True);
                  KP_ASSERT(m_iItemsCount <= MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT(strlen(val_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, val_ptr, True);
                  KP_ASSERT(m_alpszButtonsHighlight[m_iItemsCount - 1][0] == Nul, KP_E_FILE_FORMAT, lpszCfgFname /* START_SEL_CFG_FNAME */, True);
                  
                  if(SUCCEEDED(retc)) strcpy(m_alpszButtonsHighlight[m_iItemsCount - 1], val_ptr);
                  
                  break;

               case ButtonSelectedIx:
                  KP_ASSERT(m_iItemsCount > 0, KP_E_FILE_FORMAT, lpszCfgFname /* START_SEL_CFG_FNAME */, True);
                  KP_ASSERT(m_iItemsCount <= MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT(strlen(val_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, val_ptr, True);
                  KP_ASSERT(m_alpszButtonsSelected[m_iItemsCount - 1][0] == Nul, KP_E_FILE_FORMAT, lpszCfgFname /* START_SEL_CFG_FNAME */, True);
                  
                  if(SUCCEEDED(retc)) strcpy(m_alpszButtonsSelected[m_iItemsCount - 1], val_ptr);
                  
                  break;

               case StartActionIx:
               case StartAndCloseActionIx:
               case StartAdminActionIx:
               case OpenActionIx:
               case EditUserDataIx:
               case SaveCopyActionIx:
               case RestoreCopyActionIx:
               case RestoreActionIx:
               case DiagMsgIx:
                  if((m_iItemsCount == 0) && SUCCEEDED(retc)) m_iItemsCount++;
                  
                  KP_ASSERT(m_iItemsCount <= MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc)) if(m_alpszActions[m_iItemsCount - 1][0])
                  {
                     KP_ASSERT(m_iItemsCount < MAX_NUM_START_ITEMS, KP_E_BUFFER_OVERFLOW, val_ptr, True);
                     if(SUCCEEDED(retc)) m_iItemsCount++;
                  }               

                  KP_ASSERT(strlen(val_ptr) < KP_MAX_FILE_LIN_LEN /* KP_MAX_FNAME_LEN */, KP_E_BUFFER_OVERFLOW, val_ptr, True);

                  if(SUCCEEDED(retc))
                  { 
                     m_iActionTypes[m_iItemsCount - 1] = kwd_ix;
                     strcpy(m_alpszActions[m_iItemsCount - 1], val_ptr);
                  }
                  
                  break;

               case HorMarginIx:
                  sscanf((const char *)val_ptr, "%d", &m_iHorMargin);
                  break;
               case VertMarginIx:
                  sscanf((const char *)val_ptr, "%d", &m_iVertMargin);
                  break;
               case ButMarginIx:
                  sscanf((const char *)val_ptr, "%d", &m_iButMargin);
                  break;
               
               } // switch(kwd_ix)
               
            } // else // if(retc == KP_E_KWD_NOT_FOUND)

         } // if(SUCCEEDED(retc))

      } // else // if(val_ptr == NULL)
   
   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT StartSel::ParseStartSelCfg(void)
{
HRESULT retc = S_OK;
KpFStream ini_file;
static unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];
static unsigned char cfg_fname[KP_MAX_FNAME_LEN + 1];

// --------------------
   ClearMembers();

// --------------------
   if(SUCCEEDED(retc)) retc = CalcGrpCfgFName();

   if(SUCCEEDED(retc))
   {
      strcpy(cfg_fname, m_lpszGrpCfgFName);
      
      ini_file.open((const char *)cfg_fname /* START_SEL_CFG_FNAME */, ios::in);
      if(ini_file.fail())
         retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, cfg_fname /* START_SEL_CFG_FNAME */, True, __FILE__, __LINE__, 0L, NULL);
   }
      
// --------------------
   if(SUCCEEDED(retc))
   {
      do
      {
         ini_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
         if(ini_file.eof() && SUCCEEDED(retc)) retc = KP_E_EOF;
         if(SUCCEEDED(retc)) if(ini_file.fail())
         {
            retc = KP_E_FERROR;
            KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc)) retc = ParseStartSelCfgLine(in_str, cfg_fname);

      } while(SUCCEEDED(retc));

      if(retc == KP_E_EOF) retc = S_OK;

      ini_file.close();

   } // if(SUCCEEDED(retc)) // if(ini_file.fail())

return(retc);
}


// ----------------------------------
HRESULT StartSel::OpenWindow(void)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;
int win_x = 200;
int win_y = 200;
int win_dx = 200;
int win_dy = 100;
HDC hdc;
int ii;

   if(SUCCEEDED(retc))                               
      if(m_hInstance==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// -------------------------------
   if(SUCCEEDED(retc))
   {
      hdc=GetDC(HWND_DESKTOP);
      if(hdc==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// -------------------------------
   KP_NEW(m_BackgroundBmpPars, KpBmpData());

   if(SUCCEEDED(retc)) retc = m_BackgroundBmpPars->LoadImageFromFile(m_lpszBackground);

   for(ii = 0; (ii < m_iItemsCount) && SUCCEEDED(retc); ii++)
   {
      if(m_iItemTypes[ii] == ButtonImageIx)
      {
         m_pButtonBmpPars[ii] = NULL;
         KP_NEW(m_pButtonBmpPars[ii], KpBmpData());
      
         if(SUCCEEDED(retc)) retc = m_pButtonBmpPars[ii]->LoadImageFromFile(m_alpszItems[ii]);

         m_pButHlBmpPars[ii] = NULL;
         KP_NEW(m_pButHlBmpPars[ii], KpBmpData());
      
         if(SUCCEEDED(retc)) retc = m_pButHlBmpPars[ii]->LoadImageFromFile(m_alpszButtonsHighlight[ii][0]?m_alpszButtonsHighlight[ii]:m_alpszItems[ii]);

         m_pButSelBmpPars[ii] = NULL;
         KP_NEW(m_pButSelBmpPars[ii], KpBmpData());
      
         if(SUCCEEDED(retc)) retc = m_pButSelBmpPars[ii]->LoadImageFromFile(m_alpszButtonsSelected[ii][0]?m_alpszButtonsSelected[ii]:m_alpszItems[ii]);
      }
   }

// -------------------------------
   if(m_hDialogWindow == NULL)
   {
      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = m_hInstance;
         wcx.lpszClassName = "STARTSEL",
         wcx.lpfnWndProc   = (WNDPROC)StartSelDialogProc;      
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_MAIN_ICON /* KP_IDI_STARTSEL_ICON */ /* KP_IDI_ARKIM_ICON */ /* KP_IDI_START_ICON */ /* IDI_APPLICATION */));
         wcx.hIconSm       = LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_MAIN_ICON /* KP_IDI_STARTSEL_ICON */ /* KP_IDI_ARKIM_ICON */ /* KP_IDI_START_ICON */ /* IDI_APPLICATION */));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;                
         wcx.cbClsExtra    = 0;                  
         wcx.cbWndExtra    = 0;                  
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;
   
         if(!RegisterClassEx(&wcx))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
      }
   
      if(SUCCEEDED(retc))
      {             
         win_dx = m_BackgroundBmpPars->m_iBmpWdt + 2*iWndBorderWdt; // 200;
         win_dy = m_BackgroundBmpPars->m_iBmpHgt + iWndCaptionHgt + 2*iWndBorderWdt; // 100;

         win_x = (GetDeviceCaps(hdc, HORZRES) - win_dx)/2;
         win_y = (GetDeviceCaps(hdc, VERTRES) - win_dy)/2;

         m_hDialogWindow=CreateWindowEx
         (
            0,                      // DWORD dwExStyle,      // extended window style
            "STARTSEL",
            "", // "StartSel", // LPCTSTR lpWindowName, // pointer to window name
            WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            win_x, // CW_USEDEFAULT, // int x,               // horizontal position of window
            win_y, // CW_USEDEFAULT, // int y,               // vertical position of window
            win_dx,         // int nWidth,           // window width               
            win_dy,         // int nHeight,          // window height               
            HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
            0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
            m_hInstance,    
            NULL // m_BackgroundBmpPars // LPVOID lpParam        // pointer to window-creation data
         );
   
         if(m_hDialogWindow == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


// -----------------------------------------
HRESULT UnderlinesToSpaces(unsigned char *lpszStr)
{
HRESULT retc = S_OK;
unsigned char *pntd = null;

   KP_ASSERT(lpszStr, E_INVALIDARG, null, True);
   
   if(SUCCEEDED(retc))
   {
      pntd = lpszStr;
      while(*pntd)
      {
         if(*pntd == '_') *pntd = Spc;
         pntd++;
      }
   }
   
return(retc);   
}


// -----------------------------------------
HRESULT GetArcPath(unsigned char *lpszArcDirBuf) // lpszArcDirBuf[KP_MAX_FNAME_LEN + 1]
{
HRESULT retc = S_OK;
static unsigned char vol_name[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszArcDirBuf, E_INVALIDARG, null, True);
   
   if(SUCCEEDED(retc)) retc = GetLocalPath(lpszArcDirBuf, KP_My_Documents, True);
   
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniVolName(vol_name);
   
   KP_ASSERT(strlen(lpszArcDirBuf) + strlen(STARTSEL_ARC_LOC) + 1 + strlen(vol_name) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) 
   {
      strcat(lpszArcDirBuf, STARTSEL_ARC_LOC);
      strcat(lpszArcDirBuf, "\\");
      strcat(lpszArcDirBuf, vol_name);
   }

return(retc);   
}


// ----------------------------------
HRESULT StartSel::PerformAction(int iActNum, bool *pbEndFl, bool *pbCloseWindow)
{ 
HRESULT retc = S_OK;
static unsigned char ini_fname_sav[KP_MAX_FNAME_LEN + 1];
static unsigned char action_buf_exp[KP_MAX_FILE_LIN_LEN + 1]; // m_alpszActions su iðplëstais {user} atitikmenimis á theKpStAppPtr->m_lpszFlashDevName // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 1];
static unsigned char vol_name[KP_MAX_FNAME_LEN + 1];
static unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
static unsigned char wnd_name[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char ftype[KP_MAX_FTYPE_LEN + 1];
HCURSOR cur_sav = NULL;
static unsigned char action_buf_tmp[KP_MAX_FILE_LIN_LEN + 1]; // darbinë action_buf_exp kopija sudëtiniø daliø skaidymui // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 1];
static unsigned char action_buf_tmp_arc[KP_MAX_FILE_LIN_LEN + 1]; // darbinë m_alpszActions (su dar neiðskaidytais {user}) kopija sudëtiniø daliø skaidymui // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 1];
unsigned char *rest_ptr = NULL;
unsigned char *src_ptr = NULL;
unsigned char *dst_ptr = NULL;
static unsigned char user_pwd_sav[KP_KWD_LEN + 1];
static unsigned char user_data_sav[KP_MAX_FILE_LIN_WDT + 1];
HANDLE proc_id;
DWORD exit_code;
static unsigned char arc_dir[KP_MAX_FNAME_LEN + 1]; // archyvo vieta MyDocuments\TEV_arc\MaTau56m
DWORD attr;
long retv = ERROR_SUCCESS;
SYSTEMTIME cr_time;
static unsigned char str_buf[KP_MAX_FILE_LIN_LEN + 200]; // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 200];
long full_size; // kilobaitais
int cnt;
long file_size; // baitais
long usb_speed;
HWND prog_wnd = NULL;
unsigned char *rest_arc_ptr = NULL;
time_t start_time;
time_t cur_time;
long processed_size; // kilobaitais
static unsigned char action_single_arc_expanded[KP_MAX_FILE_LIN_LEN + 1]; // vieno action_buf_tmp_arc elemento kopija su {user} iðskleistu á arc_dir // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 1];
// static unsigned char start_dir[KP_MAX_FILE_LIN_LEN + 1] // ilgesnis dël m_alpszActions // [KP_MAX_FNAME_LEN + 1];
BOOL cancel = False;
long flash_id_sav;
static unsigned char puk_sav[KP_KWD_LEN+1];
fstream in_file;
base64::encoder E;
   
   KP_ASSERT(iActNum < MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);
// KP_ASSERT(pbEndFl != NULL, E_INVALIDARG, null, True); 
// KP_ASSERT(pbCloseWindow != NULL, E_INVALIDARG, null, True); 

// iðsaugojam einamàjá .ini failo vardà
   if(SUCCEEDED(retc)) strcpy(ini_fname_sav, theKpStAppPtr->m_lpszIniFName);

// ------------- ieðkom atmintuko disko vardo failø vardø korekcijai
// ------------- Taip pat PUK-o
   if(SUCCEEDED(retc)) strcpy(action_buf_exp, StartSelObj.m_alpszActions[iActNum]);
   if(SUCCEEDED(retc)) if(strstr(action_buf_exp, KPST_FNAME_SHORTCUT_USER) || // "{user}"
                           strstr(action_buf_exp, KPST_FNAME_SHORTCUT_TEMP) || // "{temp}"
                           (StartSelObj.m_iActionTypes[iActNum] == RestoreActionIx) ||
                           (StartSelObj.m_iActionTypes[iActNum] == RestoreCopyActionIx))
   {
// m_Ini.m_lpszVolName - atmintuko pririðimo .ini failo vardas (projekto vardas)
// perraðom á m_lpszIniFName – dabar jis einamasis .ini failo vardas
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniVolName(vol_name);
      if(SUCCEEDED(retc))
      {
         strcpy(theKpStAppPtr->m_lpszIniFName, vol_name); 
         if(strlen(theKpStAppPtr->m_lpszIniFName) >= KP_MAX_FNAME_LEN - 4) // strlen(KPST_INI_FILE_TYPE) // ".ini") 
            KP_ERROR(KP_E_BUFFER_OVERFLOW, null); 
         if(SUCCEEDED(retc)) strcat(theKpStAppPtr->m_lpszIniFName, KPST_INI_FILE_TYPE);
      }
// ieðkom atmintuko su .ini failu su einamuoju vardu, pakeliui bus uþpildytas theKpStAppPtr->m_lpszFlashDevName                 
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->TestFlash();

// atstatom teisingà vol_name (nes produkto .ini rodo á kità – .dat failo vardà Tadui, pvz., MaTau5e.ini - MaTau5m.ini)
// be to startsel.ini reikia MaTau56m, o ne MaTau5m ar MaTau5e
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniVolName(vol_name);
// geriau atstatom visà einamàjá .ini failà su jo vardu - negalima, dar reikës PUK-o
//    if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, ini_fname_sav);
//    if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();
            
// ----------------------------- {user} (theKpStAppPtr->m_lpszFlashDevName) --> action_buf_exp
      if(SUCCEEDED(retc)) retc = KpExpandMacro(action_buf_exp, KP_MAX_FILE_LIN_LEN,
                           KPST_FNAME_SHORTCUT_USER, theKpStAppPtr->m_lpszFlashDevName); 

// ----------------------------- {temp}
      if(SUCCEEDED(retc)) retc = GetLocalPath(fname, KP_Temp_Dir, False);
      if(SUCCEEDED(retc)) retc = KpExpandMacro(action_buf_exp, KP_MAX_FILE_LIN_LEN,
                           KPST_FNAME_SHORTCUT_TEMP, fname); 

   } // if(strstr(action_buf_exp, KPST_FNAME_SHORTCUT_USER)) // "{user}"))

// ----------------------
   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name); 
   if(SUCCEEDED(retc)) retc = GetIniWndName(wnd_name); 

// ----------------------
   if(SUCCEEDED(retc)) switch(StartSelObj.m_iActionTypes[iActNum])
   {
// ==============================
   case StartAdminActionIx:
//    retc = TestAdmin(&bAdminFl);
      if(!bAdminFl)
      {
         KpMsgOut(STARTSEL_MSG_NOT_ADMIN, IDI_WARNING, KP_MB_GERAI);
         break;
      }
   case StartActionIx:
   case StartAndCloseActionIx:
#if FALSE
      if(SUCCEEDED(retc))
      {
         strcpy(start_dir, action_buf_exp);
         retc = GetCmdPath(start_dir, True);
      }
#endif

      if(SUCCEEDED(retc))
         retc = StartProcess(action_buf_exp, KPST_CUR_DIR /* start_dir */, NULL, NULL, SW_SHOWNORMAL, // SW_SHOWDEFAULT);
                                 False, False);
                                 
      if(StartSelObj.m_iActionTypes[iActNum] == StartAndCloseActionIx)
      {
         if(pbEndFl != NULL) *pbEndFl = True;
         if(pbCloseWindow != NULL) *pbCloseWindow = True;
      }
      break;
            
// ==============================
   case OpenActionIx:
#if FALSE
      if(SUCCEEDED(retc))
      {
         strcpy(start_dir, action_buf_exp);
         retc = GetCmdPath(start_dir, True);
      }
#endif
      if(SUCCEEDED(retc))
         retc = StartCmdProcess(action_buf_exp, KPST_CUR_DIR /* start_dir */, NULL, NULL, True, SW_SHOWNORMAL, // SW_SHOWDEFAULT);
                                 False, False);

#if FALSE
//    if(StartSelObj.m_iActionTypes[iActNum] == OpenAndCloseActionIx)
      {
         if(pbEndFl != NULL) *pbEndFl = True;
         if(pbCloseWindow != NULL) *pbCloseWindow = True;
      }
#endif
      break;
            
// ==============================
   case EditUserDataIx:

// --------------- pakeièiam kursoriø á laikrodukà
      if(SUCCEEDED(retc))
      {
         cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
         KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
            
// ------------ skanuojam parametrus
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;
      }
         
      if(SUCCEEDED(retc)) do
      {          
// ------- analizuojam komandos parametrø grupes (skirtukai ';')
         if(SUCCEEDED(retc))
         {
            src_ptr = rest_ptr;
                       
            rest_ptr = strchr(rest_ptr, ';');
            if(rest_ptr) *rest_ptr++ = Nul;
         }
         
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            dst_ptr = strchr(src_ptr, ',');
            if(dst_ptr)
            {
// ------------- perkeliam user data ið vieno .ini á kità
               if(SUCCEEDED(retc)) *dst_ptr++ = Nul;
   
               if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(dst_ptr);

               KP_ASSERT(strstr(src_ptr, KPST_INI_FILE_TYPE), E_INVALIDARG, src_ptr, True);
               KP_ASSERT(strstr(dst_ptr, KPST_INI_FILE_TYPE), E_INVALIDARG, dst_ptr, True);

// ----------------- iðsaugojam einamàjá .ini failo vardà
//             if(SUCCEEDED(retc)) strcpy(ini_fname_sav, theKpStAppPtr->m_lpszIniFName); // jau iðsaugotas
// ---------------- skaitom src .ini
               KP_ASSERT(strlen(src_ptr) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True); 
               if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, src_ptr); 
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

// ---------------- atsimenam user data
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniUserPwd(user_pwd_sav);
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniUserData(user_data_sav);

// ---------------- skaitom dst .ini
               KP_ASSERT(strlen(dst_ptr) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True); 
               if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, dst_ptr); 
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

// ---------------- nustatom user data
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserPwd(user_pwd_sav);
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserData(user_data_sav);

// ---------------- raðom dst .ini atgal
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIni();

// ------------ atstatom einamàjá .ini failà // atstatysim vëliau
//             if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, ini_fname_sav);
//             if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

            }
            else // if(dst_ptr) 
            {
#ifndef KPSTSEL_DONT_ASK_MIKO_LIC
               if(SUCCEEDED(retc)) retc = StartSelObj.AskUserPUK();
#endif
// --------------------- redaguojam .ini
//             KP_ASSERT(strstr(src_ptr, "kpstedp.exe"), E_INVALIDARG, src_ptr, True);
               KP_ASSERT(strstr(src_ptr, KPST_INI_FILE_TYPE), E_INVALIDARG, src_ptr, True);

               if(SUCCEEDED(retc))
                  retc = StartProcess(src_ptr, KPST_CUR_DIR /* start_dir */, NULL, &proc_id, SW_SHOWNORMAL); // SW_SHOWDEFAULT);
               KP_ASSERT(proc_id, KP_E_SYSTEM_ERROR, GetLastError(), True);
                     
// -------------------- laukiam kol pabaigs
               if(SUCCEEDED(retc)) do
               {
                  KpSleep(500);
                  KP_ASSERT(GetExitCodeProcess(proc_id, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);

               } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));

            } // else // if(dst_ptr)
                  
         } // if(SUCCEEDED(retc)) if(src_ptr[0])
            
      } while(rest_ptr && SUCCEEDED(retc));

      if(retc == KP_E_CANCEL) retc = S_OK;

      break;
            
// ==============================
   case SaveCopyActionIx:
// ----- sugeneruojam archyvo vietos katalogo vardà 
      if(SUCCEEDED(retc)) retc = GetArcPath(arc_dir);
            
// ----- tikrinam, gal jau yra iðsaugota  
      if(SUCCEEDED(retc))
      {
         attr = GetFileAttributes((const char *)arc_dir);
         if(attr == INVALID_FILE_ATTRIBUTES)
         {
            retv = GetLastError();
            if((retv != ERROR_FILE_NOT_FOUND) && (retv != ERROR_PATH_NOT_FOUND) && (retv != ERROR_NO_MORE_FILES)) 
               KP_ERROR(KP_E_FERROR, retv);
         }
         else
         {
            if((attr & FILE_ATTRIBUTE_DIRECTORY) == 0) KP_ERROR(KP_E_SYSTEM_ERROR, null)
            else
            {
               retc = KpGetFileCrTime(arc_dir, &cr_time);
               if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK; // turëtø nerasti jau GetFileAttributes()
               else if(SUCCEEDED(retc))
               {
                  switch(iMsgLangOff)
                  {
                  case KpLangEn:       sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_EXIST, cr_time.wMonth, cr_time.wDay, cr_time.wYear); break;
                  case KpLangPl_1250: 
                  case KpLangPl_1257:  
                  case KpLangRu_1251:
                  case KpLangRu_0:     sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_EXIST, cr_time.wDay, cr_time.wMonth, cr_time.wYear); break;
                  case KpLangLt:
                  default:             sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_EXIST, cr_time.wYear, cr_time.wMonth, cr_time.wDay); break;
                  }
                  retc = KpMsgOut(str_buf, IDI_WARNING, KP_MB_TAIP_NE);
               }
            }
         }
      }
            
// --------------- pakeièiam kursoriø á laikrodukà
      if(SUCCEEDED(retc))
      {
         cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
         KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
            
// =================================================
// ------------ skaièiuojam failø dydþius
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;
         full_size = 0L;
      }
         
      if(SUCCEEDED(retc)) do
      {          
// ------- analizuojam komandos parametrø grupes (skirtukai ';')
         src_ptr = rest_ptr;
                       
         rest_ptr = strchr(rest_ptr, ';');
         if(rest_ptr) *rest_ptr++ = Nul;
         
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            attr = GetFileAttributes((const char *)src_ptr);
            if(attr == INVALID_FILE_ATTRIBUTES)
            {
               KP_WARNING(KP_E_FERROR, src_ptr);
               KP_ERROR(KP_E_FERROR, GetLastError());
            }

            if(SUCCEEDED(retc))
            {
               if(attr & FILE_ATTRIBUTE_DIRECTORY) // katalogas
               {
                  retc = KpCountFolderFileSizeCnt(src_ptr, &cnt, &file_size);
                  full_size += file_size + (cnt + 1) * KPIO_DIR_ACCESS_FILE_SIZE_EQ;
               }
               else // paprastas failas
               {
                  retc = KpGetFileSizeName(src_ptr, &file_size);
                  if(SUCCEEDED(retc))
                  { 
                     file_size /= 1000;
                     if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ; 
                     full_size += file_size;
                  }
               }
            }
         
         } // if(SUCCEEDED(retc)) if(src_ptr[0])                        
         
      } while(rest_ptr && SUCCEEDED(retc));

// ------------ slankiklis
      usb_speed = KP_USB2_SPEED;
      if(SUCCEEDED(retc)) retc = KpCreateProgressWnd(&prog_wnd, KP_MSG_COPYING /* STARTSEL_MSG_SAVING */, Maxint /* (int)(full_size / usb_speed) */, full_size);
      KP_ASSERT(prog_wnd, KP_E_SYSTEM_ERROR, null, True);

// =================================================
// ------------ dabar jau vykdom
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;

         strcpy(action_buf_tmp_arc, StartSelObj.m_alpszActions[iActNum]);
         rest_arc_ptr = action_buf_tmp_arc;

         time(&start_time);
         processed_size = 0L;
      }
      
      if(SUCCEEDED(retc)) do
      {          
// ------------------------ perduodam praneðimus slankiklio langui
         if(SUCCEEDED(retc)) retc = KpProcMsgSimple();

// ------- analizuojam komandos parametrø grupes (skirtukai ';')
         if(SUCCEEDED(retc))
         {
            src_ptr = rest_ptr;
                       
            rest_ptr = strchr(rest_ptr, ';');
            if(rest_ptr) *rest_ptr++ = Nul;
         }
               
// ------- atitinkamas parametras archyve
         KP_ASSERT(rest_arc_ptr, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
         {
            dst_ptr = rest_arc_ptr;
                       
            rest_arc_ptr = strchr(rest_arc_ptr, ';');
            if(rest_arc_ptr) *rest_arc_ptr++ = Nul;
         }

         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(dst_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
// ------------ gaminam paskirties parametrà: {user} --> arc_dir
            if(SUCCEEDED(retc)) strcpy(action_single_arc_expanded, dst_ptr);
            KP_ASSERT(strstr(action_single_arc_expanded, KPST_FNAME_SHORTCUT_USER)  // "{user}" 
               == action_single_arc_expanded, E_INVALIDARG, dst_ptr, True);
         
            if(SUCCEEDED(retc)) retc = KpExpandMacro(action_single_arc_expanded,  
                  KP_MAX_FILE_LIN_LEN, KPST_FNAME_SHORTCUT_USER, arc_dir); 

// ---------------- praneðimas á progress langelá
            if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, src_ptr);
            if(SUCCEEDED(retc))
            { 
               sprintf((char *)str_buf, (const char *)KP_MSG_COPYING_FILE /* STARTSEL_MSG_SAVING_FILE */, fname, ftype); // src_ptr); 
               retc = KpSetProgressTxt(prog_wnd, str_buf);
            }
                  
// ---------------- tikrinam, ar ne katalogas
            if(SUCCEEDED(retc))
            {
               attr = GetFileAttributes((const char *)src_ptr);
               if(attr == INVALID_FILE_ATTRIBUTES)
               {
                  KP_WARNING(KP_E_FERROR, src_ptr);
                  KP_ERROR(KP_E_FERROR, GetLastError());
               }
            }
            if(SUCCEEDED(retc))
            {
               if(attr & FILE_ATTRIBUTE_DIRECTORY) // katalogas
                  retc = KpCopyFolder(src_ptr, action_single_arc_expanded, 
                           prog_wnd, start_time, full_size, &processed_size, &usb_speed, False);
               else // paprastas failas
               {
// ----------------- failo dydis
                  if(SUCCEEDED(retc)) retc = KpGetFileSizeName(src_ptr, &file_size);
                  if(SUCCEEDED(retc))
                  { 
                     file_size /= 1000;
                     if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ;
                  } 

// ----------------- kuriam katalogà
                  if(SUCCEEDED(retc)) retc = CreatePath(action_single_arc_expanded, False);

// ----------------- kopijuojam
                  if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(prog_wnd);
// KpMsgOutF_2("[%s] [%s]", src_ptr, action_single_arc_expanded);
//                if(SUCCEEDED(retc)) if(!CopyFile((const char *)src_ptr, (const char *)action_single_arc_expanded, False))
                  if(SUCCEEDED(retc)) if(!CopyFileEx((const char *)src_ptr, (const char *)action_single_arc_expanded, KpCopyFileCallBack, &prog_wnd, &cancel, 0L))  
                     retc = KP_E_FERROR;

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
                  if(SUCCEEDED(retc))
                  {
                     time(&cur_time);
                     cur_time -= start_time;
                     if(cur_time <= 0) cur_time = 1;
               
                     processed_size += file_size;
               
                     usb_speed = processed_size / cur_time;
                  }   
                  if(SUCCEEDED(retc)) retc = KpSetProgressTime(prog_wnd, Maxint); // (int)(full_size / usb_speed));
//                if(SUCCEEDED(retc)) retc = KpSetProgressPos(prog_wnd, (int)(processed_size * 100 / full_size));   
                  if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, processed_size, full_size);   
               }
            }
            
         } // if(SUCCEEDED(retc)) if(src_ptr[0])
         
      } while(rest_ptr && SUCCEEDED(retc));

      KP_ASSERT(rest_arc_ptr == NULL, KP_E_SYSTEM_ERROR, null, True);

// ------------- nustatom archyvo katalogo einamàjà datà, jei uþraðinëjom ant virðaus
      if(SUCCEEDED(retc))
      {
         GetSystemTime(&cr_time);
         retc = ChFileTimeCrtd(arc_dir, &cr_time);
         if(FAILED(retc)) KP_WARNING(retc, arc_dir);
      }

// gesinam slankiklá
      if(prog_wnd) retc = KillProgressWnd(prog_wnd);
      prog_wnd = NULL;
            
// atstatom kursoriø            
      if(cur_sav!=NULL) SetCursor(cur_sav);
      cur_sav = NULL;

// --------------- iðvedam praneðimà
      if(SUCCEEDED(retc))
      {
static unsigned char str_buf[1000];
         sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_CREATED, arc_dir);              
         KpMsgOut(str_buf, IDI_WARNING, KP_MB_GERAI);
      }
      else if(retc == KP_E_FERROR)
      {
         TvFnameSplit(disk, path, fname, ftype, arc_dir);
//       KpMsgOutF_1(STARTSEL_MSG_LOW_DISK_SPACE, disk);
         sprintf((char *)str_buf, (const char *)STARTSEL_MSG_LOW_DISK_SPACE, disk); 
         KpMsgOut(str_buf, IDI_ERROR, KP_MB_GERAI);
         retc = S_OK;
      }
      else if(retc == KP_E_DIR_ERROR)
      {
//       KpMsgOutF_1(STARTSEL_MSG_DIR_ACCESS_ERROR, arc_dir);
         sprintf((char *)str_buf, (const char *)STARTSEL_MSG_DIR_ACCESS_ERROR, arc_dir); 
         KpMsgOut(str_buf, IDI_ERROR, KP_MB_GERAI);
         retc = S_OK;
      }

      break; // case SaveCopyActionIx:
         
// ==============================
   case RestoreCopyActionIx:
// perspëjam uþdaryt MIKO knygà
      if(SUCCEEDED(retc))
      {
         if(wnd_name[0] != Nul) retc = WaitTilWndCloses(wnd_name, prod_name);
         else KpMsgOut(STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO, IDI_ASTERISK, KP_MB_GERAI, 0, KPW_ALIGN_UP | KPW_ALIGN_CENTER);
      }
                           
// ----- sugeneruojam archyvo vietos katalogo vardà 
      if(SUCCEEDED(retc)) retc = GetArcPath(arc_dir);
            
// ----- tikrinam, ar jau yra iðsaugota  
      if(SUCCEEDED(retc))
      {
         attr = GetFileAttributes((const char *)arc_dir);
         if(attr == INVALID_FILE_ATTRIBUTES)
         {
            retv = GetLastError();
            if((retv == ERROR_FILE_NOT_FOUND) || (retv == ERROR_PATH_NOT_FOUND) || (retv == ERROR_NO_MORE_FILES))
            {
               KpMsgOut(STARTSEL_MSG_NO_ARC, IDI_WARNING, KP_MB_GERAI);
               retc = KP_E_CANCEL;
            }
            else KP_ERROR(KP_E_FERROR, retv);
         }
         else
         {
            if((attr & FILE_ATTRIBUTE_DIRECTORY) == 0) KP_ERROR(KP_E_SYSTEM_ERROR, null)
            else
            {
               retc = KpGetFileCrTime(arc_dir, &cr_time);
               if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK; // turëtø nerasti jau GetFileAttributes()
               else if(SUCCEEDED(retc))
               {
                  switch(iMsgLangOff)
                  {
                  case KpLangEn:       sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_FOUND, cr_time.wMonth, cr_time.wDay, cr_time.wYear); break;
                  case KpLangPl_1250: 
                  case KpLangPl_1257:  
                  case KpLangRu_1251:  
                  case KpLangRu_0:     sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_FOUND, cr_time.wDay, cr_time.wMonth, cr_time.wYear); break;
                  case KpLangLt:
                  default:             sprintf((char *)str_buf, (const char *)STARTSEL_MSG_ARC_FOUND, cr_time.wYear, cr_time.wMonth, cr_time.wDay); break;
                  }
                  retc = KpMsgOut(str_buf, IDI_WARNING, KP_MB_TAIP_NE);
               }
            }
         }
      }
      
#ifndef KPSTSEL_DONT_ASK_MIKO_LIC
      if(SUCCEEDED(retc)) retc = StartSelObj.AskUserPUK();
#endif
// --------------- atsimenam atmintuko PUK ir ser. no.
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniFlashId(&flash_id_sav);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniAdminPwd(puk_sav);
                        
// --------------- pakeièiam kursoriø á laikrodukà
      if(SUCCEEDED(retc))
      {
         cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
         KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
            
// =================================================
// ------------ skaièiuojam failø dydþius
      if(SUCCEEDED(retc)) retc = KpCountFolderFileSizeCnt(arc_dir, &cnt, &file_size);
      if(SUCCEEDED(retc)) full_size = file_size + (cnt + 1) * KPIO_DIR_ACCESS_FILE_SIZE_EQ;

// ------------ slankiklis
      usb_speed = KP_USB2_SPEED;
      if(SUCCEEDED(retc)) retc = KpCreateProgressWnd(&prog_wnd, KP_MSG_COPYING /* STARTSEL_MSG_SAVING */, Maxint /* (int)(full_size / usb_speed) */, full_size);
      KP_ASSERT(prog_wnd, KP_E_SYSTEM_ERROR, null, True);

// =================================================
// ------------ dabar jau vykdom
      if(SUCCEEDED(retc))
      {
         time(&start_time);
         processed_size = 0L;

         retc = KpCopyFolder(arc_dir, theKpStAppPtr->m_lpszFlashDevName, 
                        prog_wnd, start_time, full_size, &processed_size, &usb_speed, False);
      }

// --------------- atstatom PUK ir ser. no.
// ------------ skanuojam parametrus
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;
      }
         
      if(SUCCEEDED(retc)) do
      {          
// ------- analizuojam komandos parametrus (skirtukai ';')
         if(SUCCEEDED(retc))
         {
            src_ptr = rest_ptr;
                       
            rest_ptr = strchr(rest_ptr, ';');
            if(rest_ptr) *rest_ptr++ = Nul;
         }
         
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            KP_ASSERT(strstr(src_ptr, KPST_INI_FILE_TYPE), E_INVALIDARG, src_ptr, True);

// ----------------- iðsaugojam einamàjá .ini failo vardà
//          if(SUCCEEDED(retc)) strcpy(ini_fname_sav, theKpStAppPtr->m_lpszIniFName); // jau iðsaugotas
// ---------------- skaitom src .ini
            KP_ASSERT(strlen(src_ptr) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True); 
            if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, src_ptr); 
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

// ---------------- nustatom PUK ir ser. no.
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniFlashId(flash_id_sav);
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniAdminPwd(puk_sav);

// ---------------- raðom src .ini atgal
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIni();

// ------------ atstatom einamàjá .ini failà // atstatysim vëliau
//          if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, ini_fname_sav);
//          if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

         } // if(SUCCEEDED(retc)) if(src_ptr[0])
            
      } while(rest_ptr && SUCCEEDED(retc));

// gesinam slankiklá
      if(prog_wnd) /* retc = */ KillProgressWnd(prog_wnd);
      prog_wnd = NULL;
            
// atstatom kursoriø            
      if(cur_sav!=NULL) SetCursor(cur_sav);
      cur_sav = NULL;

// --------------- iðvedam praneðimà
      if(SUCCEEDED(retc)) KpMsgOut(STARTSEL_MSG_ARC_RESTORED, IDI_ASTERISK, KP_MB_GERAI); 
      else if(retc == KP_E_FERROR)
      {
         KpMsgOut(STARTSEL_MSG_LOW_FLASH_SPACE, IDI_ERROR, KP_MB_GERAI);
         retc = S_OK;
      }
      else if(retc == KP_E_DIR_ERROR)
      {
         KpMsgOut(STARTSEL_MSG_FLASH_ACCESS_ERROR, IDI_ERROR, KP_MB_GERAI);
         retc = S_OK;
      }
      else if(retc == KP_E_CANCEL) retc = S_OK;

      break;

// ==============================
   case RestoreActionIx:
// perspëjam uþdaryt MIKO knygà
      if(SUCCEEDED(retc))
      {
         if(wnd_name[0] != Nul) retc = WaitTilWndCloses(wnd_name, prod_name);
         else KpMsgOut(STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO, IDI_ASTERISK, KP_MB_GERAI, 0, KPW_ALIGN_UP | KPW_ALIGN_CENTER);
      }

      if(SUCCEEDED(retc)) retc = KpMsgOut(STARTSEL_MSG_SURE_RESTORING, IDI_WARNING, KP_MB_TAIP_NE, 0, KPW_ALIGN_LEFT); // , KP_MB_GERAI_ATSAUKTI);
#ifndef KPSTSEL_DONT_ASK_MIKO_LIC
      if(SUCCEEDED(retc)) retc = StartSelObj.AskUserPUK();
#endif      
      if(SUCCEEDED(retc))
      {
// ---------------- pakeièiam kursoriø á laikrodukà
         cur_sav = SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
         KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
            
// =================================================
// ------------ skaièiuojam failø dydþius
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;
         full_size = 0L;
      }
                        
      if(SUCCEEDED(retc)) do
      {          
// ------- analizuojam komandos parametrø grupes (skirtukai ';')
         src_ptr = rest_ptr;
                       
         rest_ptr = strchr(rest_ptr, ';');
         if(rest_ptr) *rest_ptr++ = Nul;
         
         dst_ptr = strchr(src_ptr, ',');
         if(dst_ptr) *dst_ptr++ = Nul;

         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);
         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            if(dst_ptr || strstr(src_ptr, KPST_INI_FILE_TYPE)) // atskiras failas
            {
               retc = KpGetFileSizeName(src_ptr, &file_size);
               if(SUCCEEDED(retc)) 
               {
                  file_size /= 1000;
                  if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ; 
                  full_size += file_size;
               }
// KpMsgOutF_2("%ld %ld", file_size, full_size);
            }
            else // katalogas iðtrynimui
            {
               retc = KpCountFolderFileSizeCnt(src_ptr, &cnt, NULL); // &file_size);
               full_size += cnt * KPIO_DIR_ACCESS_FILE_SIZE_EQ;
            }                         
         
         } // if(SUCCEEDED(retc)) if(src_ptr[0])
            
      } while(rest_ptr && SUCCEEDED(retc));

// ------------ slankiklis
      if(SUCCEEDED(retc)) usb_speed = KP_USB2_SPEED / 2; // failai kopijuojami ið atmintuko á atmintukà - laikas turëtø dvigubintis
      if(SUCCEEDED(retc)) retc = KpCreateProgressWnd(&prog_wnd, STARTSEL_MSG_RESTORING, Maxint /* (int)(full_size / usb_speed) */, full_size);
      KP_ASSERT(prog_wnd, KP_E_SYSTEM_ERROR, null, True);

// =================================================
// ------------ dabar jau vykdom
      if(SUCCEEDED(retc))
      {
         strcpy(action_buf_tmp, action_buf_exp);
         rest_ptr = action_buf_tmp;
         time(&start_time);
         processed_size = 0L;
      }
         
      if(SUCCEEDED(retc)) do
      {          
// ------------------------ perduodam praneðimus slankiklio langui
         if(SUCCEEDED(retc)) retc = KpProcMsgSimple();

// ------- analizuojam komandos parametrø grupes (skirtukai ';')
         if(SUCCEEDED(retc))
         {
            src_ptr = rest_ptr;
                       
            rest_ptr = strchr(rest_ptr, ';');
            if(rest_ptr) *rest_ptr++ = Nul;
         }
         
         if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(src_ptr);

         if(SUCCEEDED(retc)) if(src_ptr[0])
         {
            dst_ptr = strchr(src_ptr, ',');
            if(dst_ptr)
            {
// ------------- restorinam .pdf
               if(SUCCEEDED(retc)) *dst_ptr++ = Nul;
   
               if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(dst_ptr);

// ------------- progreso langelio praneðimas
               if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, dst_ptr);
               if(SUCCEEDED(retc))
               { 
                  sprintf((char *)str_buf, (const char *)STARTSEL_MSG_RESTORING_FILE, fname, ftype); // dst_ptr); 
                  retc = KpSetProgressTxt(prog_wnd, str_buf);
               }
// KpMsgOutF_2("restore .pdf: %s %s", src_ptr, dst_ptr);

// ----------------- failo dydis
               if(SUCCEEDED(retc)) retc = KpGetFileSizeName(src_ptr, &file_size);
               if(SUCCEEDED(retc))
               {
                  file_size /= 1000;
                  if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ;
               } 

// ---------------- kopijuojam            
               if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(prog_wnd);
// KpMsgOutF_3("%ld %ld %d", file_size, usb_speed, (int)(file_size /* / 1000 */ / usb_speed));
// KpSleep((int)(file_size /* / 1000 */ / usb_speed /* * 1000 */), prog_wnd);
//             KP_ASSERT(CopyFile((const char *)src_ptr, (const char *)dst_ptr, False), KP_E_FERROR, GetLastError(), True);
               KP_ASSERT(CopyFileEx((const char *)src_ptr, (const char *)dst_ptr, KpCopyFileCallBack, &prog_wnd, &cancel, 0L), KP_E_FERROR, GetLastError(), True);  

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
               if(SUCCEEDED(retc))
               {
                  time(&cur_time);
                  cur_time -= start_time;
                  if(cur_time <= 0) cur_time = 1;
               
                  processed_size += file_size;
               
                  usb_speed = processed_size / cur_time;
               }   
// KpMsgOutF_3("%ld %ld %d", full_size, usb_speed, (int)(full_size / usb_speed));
               if(SUCCEEDED(retc)) retc = KpSetProgressTime(prog_wnd, Maxint); // (int)(full_size / usb_speed));
// KpMsgOutF_3("%ld %ld %d", processed_size, full_size, (int)(processed_size * 100 / full_size));
//             if(SUCCEEDED(retc)) retc = KpSetProgressPos(prog_wnd, (int)(processed_size * 100 / full_size));   
               if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, processed_size, full_size);   
                  
            }
            else // if(dst_ptr) 
            {
               if(strstr(src_ptr, KPST_INI_FILE_TYPE))
               {
// ------------- trinam .ini slaptaþodá

// ------------- progreso langelio praneðimas
                  if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, fname, ftype, src_ptr);
                  if(SUCCEEDED(retc))
                  {
                     sprintf((char *)str_buf, (const char *)STARTSEL_MSG_RESTORING_FILE, fname, ftype); // src_ptr); 
                     retc = KpSetProgressTxt(prog_wnd, str_buf);
                  }
// KpMsgOutF_1("clear pwd: %s", src_ptr);

// ----------------- failo dydis
                  if(SUCCEEDED(retc)) retc = KpGetFileSizeName(src_ptr, &file_size);
                  if(SUCCEEDED(retc))
                  { 
                     file_size /= 1000;
                     if(file_size < KPIO_DIR_ACCESS_FILE_SIZE_EQ) file_size = KPIO_DIR_ACCESS_FILE_SIZE_EQ;
                  } 

                  if(SUCCEEDED(retc)) retc = KpSetProgressFileStartPos(prog_wnd);

// KpMsgOutF_3("%ld %ld %d", file_size, usb_speed, (int)(file_size /* / 1000 */ / usb_speed));
// KpSleep((int)(file_size /* / 1000 */ / usb_speed /* * 1000 */), prog_wnd);

// ----------------- iðsaugojam einamàjá .ini failo vardà
//                if(SUCCEEDED(retc)) strcpy(ini_fname_sav, theKpStAppPtr->m_lpszIniFName); // jau iðsaugotas
// --------------- trinam slaptaþodá .ini faile
                  KP_ASSERT(strlen(src_ptr) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True); 
                  if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, src_ptr); 
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserPwd((const unsigned char *)"");
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIni();

// ------------ atstatom einamàjá .ini failà // atstatysim vëliau
//                if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, ini_fname_sav);
//                if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

// ---------------- perskaièiuojam greièius ir slankiklio pozicijas
                  if(SUCCEEDED(retc))
                  {
                     time(&cur_time);
                     cur_time -= start_time;
                     if(cur_time <= 0) cur_time = 1;
            
                     processed_size += file_size;
            
                     usb_speed = processed_size / cur_time;
                  }   
// KpMsgOutF_3("%ld %ld %d", full_size, usb_speed, (int)(full_size / usb_speed));
                  if(SUCCEEDED(retc)) retc = KpSetProgressTime(prog_wnd, Maxint); // (int)(full_size / usb_speed));
// KpMsgOutF_3("%ld %ld %d", processed_size, full_size, (int)(processed_size * 100 / full_size));
//                if(SUCCEEDED(retc)) retc = KpSetProgressPos(prog_wnd, (int)(processed_size * 100 / full_size));   
                  if(SUCCEEDED(retc)) retc = KpSetProgressPosAbs(prog_wnd, processed_size, full_size);   

               }
               else // if(strstr(src_ptr, KPST_INI_FILE_TYPE))
               {
// --------------------- trinam katalogà
                  retc = KpDeleteFolderContents(src_ptr, 
                           prog_wnd, start_time, full_size, &processed_size, &usb_speed);
                  
               } // else // if(strstr(src_ptr, KPST_INI_FILE_TYPE))
                  
            } // else // if(dst_ptr)
                  
         } // if(SUCCEEDED(retc)) if(src_ptr[0])
            
      } while(rest_ptr && SUCCEEDED(retc));

// gesinam slankiklá
      if(prog_wnd) /* retc = */ KillProgressWnd(prog_wnd);
      prog_wnd = NULL;
            
// atstatom kursoriø            
      if(cur_sav!=NULL) SetCursor(cur_sav);
      cur_sav = NULL;

      if(SUCCEEDED(retc)) KpMsgOut(STARTSEL_MSG_RESTORED, IDI_ASTERISK, KP_MB_GERAI);
      if(retc == KP_E_CANCEL) retc = S_OK;

      break; // case RestoreActionIx:
           
   case DiagMsgIx:
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GrpSendDiagMsg(action_buf_exp);
      break; // case DiagMsgId:

   } // if(SUCCEEDED(retc)) switch(StartSelObj.m_iActionTypes[iActNum])   

   if(retc == KP_E_CANCEL) retc = S_OK; // èia nuo progress langelio uþdarymo ir nuo pasitikrinimo langeliø kanceliavimo   

// gesinam slankiklá jeigu kà
   if(prog_wnd) retc = KillProgressWnd(prog_wnd);
   prog_wnd = NULL;
            
// atstatom kursoriø            
   if(cur_sav!=NULL) SetCursor(cur_sav);
   cur_sav = NULL;

// atstatom einamàjá .ini failo vardà ir patá failà
   if(SUCCEEDED(retc)) strcpy(theKpStAppPtr->m_lpszIniFName, ini_fname_sav); // geriau iðkart po panaudojimo // ne - reikia laikino atmintukinio (PUK ir t.t.)
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, True, True); // LoadIni();

return(retc);   
}


// -------------------------------------------------------------
BOOL CALLBACK StartSelDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
BOOL retw = False;
int retp;
bool endfl = False;
bool close_window = False;
// CREATESTRUCT *csp=NULL;
KpBmpData *bgr_bmp_pars = NULL;
KpBmpData *but_bmp_pars = NULL;
KpBmpData *but_hl_bmp_pars = NULL;
KpBmpData *but_sel_bmp_pars = NULL;
int but_x; 
int but_y; 
int but_wdt;
int but_hgt;
int full_but_wdt;
int full_but_hgt;
int prev_but_hgt;
int cur_but_y;
int but_cnt;
int act_num;
MSG msg;
KpStApp *kpstapp_ptr = NULL;
KpStApp *kpstapp_ptr_alloc = NULL;

   retp=LOWORD(wParam);
   endfl=False;   
                 
   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
   
   if(SUCCEEDED(retc)) switch(uMsg) 
   {
   case WM_CREATE:
      KP_ASSERT(/* (StartSelObj.m_iItemsCount >= 0) && */ (StartSelObj.m_iItemsCount < MAX_NUM_START_ITEMS), 
         KP_E_SYSTEM_ERROR, null, True);
   
// background
   
#if FALSE
      if(SUCCEEDED(retc)) csp=(LPCREATESTRUCT)lParam;
      KP_ASSERT(csp, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
      {
         bgr_bmp_pars = (KpBmpData *)csp->lpCreateParams;
         KP_ASSERT(bgr_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
      }
      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(bgr_bmp_pars->m_hBitMap, KP_E_SYSTEM_ERROR, null, True);
#endif

      if(SUCCEEDED(retc))
      {
         bgr_bmp_pars = StartSelObj.m_BackgroundBmpPars;
         KP_ASSERT(bgr_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
      }
      
      if(SUCCEEDED(retc))
         retc = KpCreateBitmap(hKpInstance, hwndDlg, &(bgr_bmp_pars->m_hBitmapCtrl),
                bgr_bmp_pars->m_hBitMap, 0, 0, bgr_bmp_pars->m_iBmpWdt, bgr_bmp_pars->m_iBmpHgt,
                0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);

      if(SUCCEEDED(retc))
      {
// ------------------------- visø mygtukø aukðtis
         full_but_hgt = -StartSelObj.m_iButMargin; // -START_SEL_BUT_MARGIN; // einamasis aukðtis
         full_but_wdt = -StartSelObj.m_iButMargin; // -START_SEL_BUT_MARGIN; // einamasis

         prev_but_hgt = 0;
          
         for(act_num = 0; (act_num < StartSelObj.m_iItemsCount) && SUCCEEDED(retc); act_num++)
         { 
            switch(StartSelObj.m_iItemTypes[act_num])
            {
            case ButtonImageIx:
               if(SUCCEEDED(retc))
               {
                  but_bmp_pars = StartSelObj.m_pButtonBmpPars[act_num];
                  KP_ASSERT(but_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
               }

               if(SUCCEEDED(retc))
               {
                  but_wdt = but_bmp_pars->m_iBmpWdt;
                  but_hgt = but_bmp_pars->m_iBmpHgt;
               }            
         
               break; // case ButtonImageIx:
               
            case ButtonTextIx:

               but_wdt = iaCtrlTextFactors[KPW_CONTROL_STYLE_HEADING_3] * strlen(StartSelObj.m_alpszItems[act_num]) / 10;
               but_cnt = (bgr_bmp_pars->m_iBmpWdt - StartSelObj.m_iHorMargin * 2 + StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */) / but_wdt;
               if(but_cnt == 0) but_cnt = 1;
               but_wdt = ((bgr_bmp_pars->m_iBmpWdt - StartSelObj.m_iHorMargin * 2 + StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */) / but_cnt) - StartSelObj.m_iButMargin; // START_SEL_BUT_MARGIN;
               
               but_hgt = START_SEL_TEXT_BUT_HGT;

               break; // case ButtonTextIx:
               
            } // switch(StartSelObj.m_iItemTypes[act_num])
            
            if(SUCCEEDED(retc))
            {
               if(StartSelObj.m_iHorMargin /* START_SEL_BUT_MARGIN */ + full_but_wdt + 
                  StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */ + but_wdt + 
                  StartSelObj.m_iHorMargin /* START_SEL_BUT_MARGIN */ > bgr_bmp_pars->m_iBmpWdt)
               { 
                  full_but_wdt = but_wdt;
                  full_but_hgt +=  StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */ + prev_but_hgt;            
                  prev_but_hgt = 0;
               }
               else
                  full_but_wdt += StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */ + but_wdt;

               if(prev_but_hgt < but_hgt) prev_but_hgt = but_hgt;
            }

         } // for(act_num = 0; act_num < StartSelObj.m_iItemsCount; act_num++)
      
         if(SUCCEEDED(retc)) full_but_hgt += StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */ + prev_but_hgt;            
            
// ------------------- mygtukai      
         but_x = StartSelObj.m_iHorMargin; // START_SEL_WND_MARGIN; // START_SEL_BUT_MARGIN;
         but_y = bgr_bmp_pars->m_iBmpHgt - StartSelObj.m_iVertMargin /* START_SEL_WND_MARGIN */ - full_but_hgt; 
         
         prev_but_hgt = 0;
          
         for(act_num = 0; (act_num < StartSelObj.m_iItemsCount) && SUCCEEDED(retc); act_num++) 
         {
            switch(StartSelObj.m_iItemTypes[act_num])
            {
            case ButtonImageIx:
               if(SUCCEEDED(retc))
               {
                  but_bmp_pars = StartSelObj.m_pButtonBmpPars[act_num];
                  KP_ASSERT(but_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
               }
         
               if(SUCCEEDED(retc))
               {
                  but_hl_bmp_pars = StartSelObj.m_pButHlBmpPars[act_num];
                  KP_ASSERT(but_hl_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
               }
         
               if(SUCCEEDED(retc))
               {
                  but_sel_bmp_pars = StartSelObj.m_pButSelBmpPars[act_num];
                  KP_ASSERT(but_sel_bmp_pars, KP_E_SYSTEM_ERROR, null, True);
               }
         
               if(SUCCEEDED(retc))
               {
                  but_wdt = but_bmp_pars->m_iBmpWdt;
                  but_hgt = but_bmp_pars->m_iBmpHgt;

                  if(but_x + but_wdt + StartSelObj.m_iHorMargin /* START_SEL_BUT_MARGIN */ > bgr_bmp_pars->m_iBmpWdt)
                  { 
                     but_x = StartSelObj.m_iHorMargin; // START_SEL_BUT_MARGIN;
                     but_y += prev_but_hgt + StartSelObj.m_iButMargin; // START_SEL_BUT_MARGIN;
                     prev_but_hgt = 0;
                  }

                  cur_but_y = but_y;
                  if(but_hgt < prev_but_hgt) cur_but_y = but_y + (prev_but_hgt - but_hgt) / 2;

//                retc = KpCreateButton(hKpInstance, hwndDlg, &(but_bmp_pars->m_hBitmapCtrl), KP_ID_START_SEL + act_num, but_bmp_pars, 
//                   but_x, cur_but_y, 0, BS_FLAT);
               
                  retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(StartSelObj.m_hButtonCtrls[act_num]), KP_ID_START_SEL + act_num, 
                     (const unsigned char *)"", but_bmp_pars->m_hBitMap, but_hl_bmp_pars->m_hBitMap, but_sel_bmp_pars->m_hBitMap,
                     but_x, cur_but_y, but_wdt, but_hgt, KP_WND_UNPROC_BUT|KP_WND_PROC_CURS, 0 /* BS_FLAT */, KpColorSchemeLocal);
               }
               KP_ASSERT(StartSelObj.m_hButtonCtrls[act_num], KP_E_SYSTEM_ERROR, null, False);
               
               if(SUCCEEDED(retc)) but_bmp_pars->m_hBitmapCtrl = StartSelObj.m_hButtonCtrls[act_num];

               break; // case ButtonImageIx:
              
            case ButtonTextIx:
               if(SUCCEEDED(retc))
               {
//                but_wdt = bgr_bmp_pars->m_iBmpWdt - 2 * START_SEL_BUT_MARGIN;
                  but_wdt = iaCtrlTextFactors[KPW_CONTROL_STYLE_HEADING_3] * strlen(StartSelObj.m_alpszItems[act_num]) / 10;
                  but_cnt = (bgr_bmp_pars->m_iBmpWdt - StartSelObj.m_iHorMargin * 2 + StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */) / but_wdt;
                  if(but_cnt == 0) but_cnt = 1;
                  but_wdt = ((bgr_bmp_pars->m_iBmpWdt - StartSelObj.m_iHorMargin * 2 + 
                              StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */) / but_cnt) - 
                              StartSelObj.m_iButMargin; // START_SEL_BUT_MARGIN;

                  but_hgt = START_SEL_TEXT_BUT_HGT;

                  if(but_x + but_wdt + StartSelObj.m_iHorMargin /* START_SEL_BUT_MARGIN */ > bgr_bmp_pars->m_iBmpWdt)
                  { 
                     but_x = StartSelObj.m_iHorMargin; // START_SEL_BUT_MARGIN;
                     but_y += prev_but_hgt + StartSelObj.m_iButMargin; // START_SEL_BUT_MARGIN;
                     prev_but_hgt = 0;
                  }

                  cur_but_y = but_y;
                  if(but_hgt < prev_but_hgt) cur_but_y = but_y + (prev_but_hgt - but_hgt) / 2;

                  retc = UnderlinesToSpaces(StartSelObj.m_alpszItems[act_num]);
               }
               
               if(SUCCEEDED(retc))
               {
//                retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(StartSelObj.m_hButtonCtrls[act_num]), KP_ID_START_SEL + act_num,
//                   StartSelObj.m_alpszItems[act_num], but_x, cur_but_y, but_wdt, but_hgt,
//                   KP_WND_UNPROC_BUT|KP_WND_PROC_CURS, 0, KpColorSchemeLocal);

                  retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(StartSelObj.m_hButtonCtrls[act_num]), KP_ID_START_SEL + act_num, 
                     StartSelObj.m_alpszItems[act_num], 0, 0, 0, but_x, cur_but_y, but_wdt, but_hgt,
                     KP_WND_UNPROC_BUT|KP_WND_PROC_CURS, 0, KpColorSchemeLocal, KPW_CONTROL_STYLE_HEADING_3);

               }
               KP_ASSERT(StartSelObj.m_hButtonCtrls[act_num], KP_E_SYSTEM_ERROR, null, False);

               break; // case ButtonTextIx:
              
            } //  switch(StartSelObj.m_iItemTypes[act_num])
            
            if(prev_but_hgt < but_hgt) prev_but_hgt = but_hgt;

            if(SUCCEEDED(retc)) but_x += StartSelObj.m_iButMargin /* START_SEL_BUT_MARGIN */ + but_wdt;
            
         } // for(act_num = 0; act_num < StartSelObj.m_iItemsCount; act_num++)
         
      } // if(SUCCEEDED(retc))
      
      break;

   case WM_INITDIALOG:
      retw = True;
      break;

   case WM_CLOSE:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      endfl = True;               
      close_window = True;
      break;

   case WM_QUIT:
      switch(retp)
      {
      case IDCANCEL: retc = KP_E_CANCEL; break;
      case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl=True;
      break;

   case WM_COMMAND:            
      switch(LOWORD(wParam))
      {
      case IDOK:
         endfl=True;
         break;

      case IDCANCEL:
         endfl = True;
         close_window=True;
         break;

      case KP_ID_START_SEL + 0:         
      case KP_ID_START_SEL + 1:         
      case KP_ID_START_SEL + 2:         
      case KP_ID_START_SEL + 3:         
      case KP_ID_START_SEL + 4:         
      case KP_ID_START_SEL + 5:         
      case KP_ID_START_SEL + 6:         
      case KP_ID_START_SEL + 7:         
      case KP_ID_START_SEL + 8:         
      case KP_ID_START_SEL + 9:
      case KP_ID_START_SEL + 10:
      case KP_ID_START_SEL + 11:
      case KP_ID_START_SEL + 12:
      case KP_ID_START_SEL + 13:
      case KP_ID_START_SEL + 14:
      case KP_ID_START_SEL + 15:
      case KP_ID_START_SEL + 16:
         
         if(StartSelObj.m_bInProgress) break; // dubliuotas paspaudimas
         StartSelObj.m_bInProgress = True;

         act_num = LOWORD(wParam) - KP_ID_START_SEL;
         KP_ASSERT(act_num < MAX_NUM_START_ITEMS, KP_E_SYSTEM_ERROR, null, True);
      
// iðvalom praneðimø eilæ, kad atðoktø mygtukas
         if(SUCCEEDED(retc)) 
            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
               TranslateMessage(&msg);
               DispatchMessage(&msg);
            }

         if(SUCCEEDED(retc)) StartSelObj.PerformAction(act_num, &endfl, &close_window); 

// iðvalom praneðimø eilæ, kad susivalgytø pakartotiniai paspaudimai
// nepadeda
#if FALSE
         KpSleep(500);
         if(SUCCEEDED(retc)) 
            while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
               TranslateMessage(&msg);
               DispatchMessage(&msg);
               KpSleep(50);
            }
#endif
         StartSelObj.m_bInProgress = False;

         break; // case KP_ID_START_SEL + xxx
               
      } // switch(LOWORD(wParam))

      break; // case WM_COMMAND:

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   
   } // if(SUCCEEDED(retc)) switch(uMsg)

   if(close_window)
   {
      retc0 = S_OK;

//    if(SUCCEEDED(retc)) retc0 = StartSelObj.CloseWindow();

//    if(SUCCEEDED(retc)) retc = retc0;
      
      retc = KP_E_CANCEL;
   }
   
   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);       
   
return(retw);
}


// ----------------------------------
HRESULT StartSel::CloseWindow(void)
{
HRESULT retc=S_OK;

   if(m_hDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hDialogWindow)))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }
       
   if(SUCCEEDED(retc)) ClearMembers();       
       
return(retc);
}

// ----------------------------------------------------
typedef struct
{
HINSTANCE m_hInstance;
unsigned char m_lpszIniFname[KP_MAX_FNAME_LEN + 1];
unsigned char m_lpszCmdLine[KP_MAX_FNAME_LEN + 1];
} StartSelKpStapInitParStruct; 

StartSelKpStapInitParStruct StartSelKpStapInitPars;

DWORD WINAPI StartSelKpStapInit(LPVOID lpParameter)
{
HRESULT retc = S_OK;
StartSelKpStapInitParStruct *par_ptr = (StartSelKpStapInitParStruct *)lpParameter;
   KP_ASSERT(par_ptr, E_POINTER, null, True);

   if(SUCCEEDED(retc)) retc = StartSelObj.InitStApp(par_ptr->m_hInstance, par_ptr->m_lpszIniFname, (LPSTR)par_ptr->m_lpszCmdLine, KpStEditMode); // KpStLicSvrMode);

return(RET_CODE_WIN(retc));
}


// ---------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
MSG msg;
int retp;
bool endfl = False;
static unsigned char full_path[KP_MAX_FNAME_LEN + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char name[KP_MAX_FNAME_LEN + 1];
static unsigned char type[KP_MAX_FTYPE_LEN + 1];

   if(StackTop == NULL) StackTop = &nCmdShow;

// ------------------------------- 
   theKpStAppPtr = static_cast<KpStApp *> (&StartSelObj);

// ------------------------------- 
   if (SUCCEEDED(retc))
   {
      StartSelKpStapInitPars.m_hInstance = hInstance;
      KP_ASSERT(strlen(lpCmdLine) <= KP_MAX_FTYPE_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if (SUCCEEDED(retc)) strcpy(StartSelKpStapInitPars.m_lpszCmdLine, lpCmdLine);
   }

// ================================ atkelta prieð KpStApp::InitStApp(), kad nekabëtø ilgai
   StartSelObj.m_hInstance = hInstance;
   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

// -------------------------------- komandinë eilutë
// TODO: Dabar neveiks – neávykæs StartSelObj.InitStApp()
   endfl = False;
   if(SUCCEEDED(retc)) if(StartSelObj.m_plCmdLineArgs != NULL)
   {
const unsigned char *par_ptr = (const unsigned char *)StartSelObj.m_plCmdLineArgs->GetValue();
      if((par_ptr != null) && SUCCEEDED(retc)) retc = StartSelObj.ParseStartSelCfgLine(par_ptr, null);

      if(SUCCEEDED(retc)) retc = StartSelObj.PerformAction(0, NULL, NULL);

      endfl = True;
   }

   
// -------------------------------- meniu ið .cfg failo
   if(!endfl) // komandinës eilutës parametrø nebuvo
   {
      if(SUCCEEDED(retc)) retc = StartSelObj.ParseStartSelCfg();
#ifdef Debug
      if(SUCCEEDED(retc)) retc = StartSelObj.DumpMembers();
#endif
   
// --------------------------------
      if(SUCCEEDED(retc)) retc = StartSelObj.OpenWindow();

// --------- perspëjimas uþdaryt MIKO knygà
// iðkelta prie kiekvienos funkcijos   
//    if(StartSelObj.m_bMikoPapFun && SUCCEEDED(retc)) 
//       KpMsgOut(STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO, IDI_ASTERISK, KP_MB_GERAI, 0, KPW_ALIGN_UP | KPW_ALIGN_CENTER);                  

   }

// =============================== KpStApp::InitStApp(), nukelta po OpenWindow, kad nekabëtø ilgai
   if(SUCCEEDED(retc)) retc = GetIniFname(StartSelKpStapInitPars.m_lpszIniFname);
   if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, name, type, StartSelKpStapInitPars.m_lpszIniFname);
   if(SUCCEEDED(retc)) if(strlen(disk) + strlen(path) + 1 + strlen(STARTSEL_MNG_DIR) + 1 + strlen(name) + 1 + strlen(type) >= KP_MAX_FNAME_LEN) 
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(StartSelKpStapInitPars.m_lpszIniFname, disk);
      strcat(StartSelKpStapInitPars.m_lpszIniFname, path);
      strcat(StartSelKpStapInitPars.m_lpszIniFname, "\\");
      strcat(StartSelKpStapInitPars.m_lpszIniFname, STARTSEL_MNG_DIR);
      strcat(StartSelKpStapInitPars.m_lpszIniFname, "\\");
      strcat(StartSelKpStapInitPars.m_lpszIniFname, name);
      strcat(StartSelKpStapInitPars.m_lpszIniFname, ".");
      strcat(StartSelKpStapInitPars.m_lpszIniFname, type);
   }
   
   strcpy(StartSelObj.m_lpszIniFName, StartSelKpStapInitPars.m_lpszIniFname);

// if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);
// if(SUCCEEDED(retc)) retc = StartSelObj.InitCommonApp(hInstance, lpCmdLine);

// if(SUCCEEDED(retc)) retc = StartSelObj.InitStApp(hInstance, StartSelKpStapInitPars.m_lpszIniFname, lpCmdLine, KpStEditMode); // KpStLicSvrMode);
// su KpStApp::InitStApp() kaþko kabo 17 sec Win7 atmintukas pirmà kartà
// paleidinëjam atskiram threade, kad patikrintø kpstbls.ini

   KP_ASSERT(CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         StartSelKpStapInit,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         &StartSelKpStapInitPars, // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         NULL                 // LPDWORD lpThreadId                         // pointer to receive thread ID
      ), KP_E_SYSTEM_ERROR, GetLastError(), True);

// -------------------------------------------
// nustatom einamàjá katalogà – reikia paleidimui ið Papildai\*, 
// ið InitCommonApp() iðmestas dël TUX_XFS 
   if(SUCCEEDED(retc)) retc = GetAppPath(full_path, False);
   if(SUCCEEDED(retc)) if(!SetCurrentDirectory((char *)full_path))
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, full_path, False, __FILE__, __LINE__, 0L);
   }


// ================================ message loop
   if(!endfl) // komandinës eilutës parametrø nebuvo
   {
      if(SUCCEEDED(retc)) do
      {
         if(GetMessage(&msg, NULL, 0, 0) < 0)
         {
            retc=KP_E_SYSTEM_ERROR;
            KpErrorProc.OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            retp=LOWORD(msg.wParam);
         }
      
         if(SUCCEEDED(retc)) switch(msg.message)
         {
         case WM_COMMAND:
            switch(retp)
            {
            case IDOK:
               break;
            case IDCANCEL:
//             if(msg.hwnd==m_hDialogWindow) 
                  endfl=True;
               break;
            } // switch(retp)
            break;
      
         case WM_TIMER:
            if((retp == StartSelObj.m_iProcCmdTimer) && SUCCEEDED(retc))
               retc = StartSelObj.CloseAutoPlay();
            break;

         case WM_QUIT:
            switch(retp)
            {
            case IDCANCEL: retc = KP_E_CANCEL; break;
            case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
            }
            endfl=True;
            break;

         case WM_CLOSE:
            endfl=True;
            break;

         }  // if(SUCCEEDED(retc)) switch(msg.message)
   
      } while((!endfl) && SUCCEEDED(retc));

   } // if(!endfl)
   
// ------------------------------------
#ifndef KPSTSEL_NO_KPSTAP
// retc0 = KpFinitWindows();
// retc0 = StartSelObj.CloseCommonApp();
   retc0 = StartSelObj.CloseStApp(retc, KP_My_Documents);
   if(SUCCEEDED(retc)) retc = retc0;
#endif   

return(RET_CODE_WIN(retc));
}
