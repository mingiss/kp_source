// -----------------------------------------
// StartSel.h
// Keliø programø paleidimas ið meniu
// apibrëþimø failas
//


#ifndef StartSel_included
#define StartSel_included


// -----------------------------------------
#define MAX_NUM_START_ITEMS 20

#define START_SEL_WND_MARGIN  30 // KPW_CTRL_MARGIN
#define START_SEL_BUT_MARGIN  30 // KPW_WND_MARGIN
#define START_SEL_TEXT_BUT_HGT (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_HEADING_3]) // 30

#define STARTSEL_ARC_LOC ((const unsigned char *)"TEV_arc")


// -------------------------------
enum
{
STARTSEL_MSG_NOT_ADMIN_IX,                // "Ðiam veiksmui turite bûti prisijungæs administratorium.")
STARTSEL_MSG_SURE_RESTORING_IX,           // "Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi katalogø „Mano_...” failai ir naudotojo duomenys.\n \nAr sutinkate?")
STARTSEL_MSG_RESTORING_IX,                // "Atstatomas failas...")
STARTSEL_MSG_RESTORING_FILE_IX,           // "Atstatomas failas %s.%s...")
STARTSEL_MSG_RESTORED_IX,                 // "Pradiniai duomenys sëkmingai atstatyti.")
STARTSEL_MSG_ARC_EXIST_IX,                // "Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
STARTSEL_MSG_ARC_CREATED_IX,              // "Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
STARTSEL_MSG_LOW_DISK_SPACE_IX,           // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
STARTSEL_MSG_DIR_ACCESS_ERROR_IX,         // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
STARTSEL_MSG_NO_ARC_IX,                   // "Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
STARTSEL_MSG_ARC_FOUND_IX,                // "Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
STARTSEL_MSG_ARC_RESTORED_IX,             // "Atsarginë kopija sëkmingai atstatyta.")
STARTSEL_MSG_LOW_FLASH_SPACE_IX,          // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
STARTSEL_MSG_FLASH_ACCESS_ERROR_IX,       // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_IX,   // "Uþverkite visus MIKO knygos failus.")

NumOfStartSelMessages
};

#define NumOfStartSelMessages_2 NumOfStartSelMessages
 
extern const unsigned char *lpszaStartSelMessages[NumOfStartSelMessages][KpNumOfLangs];

#define STARTSEL_MSG_NOT_ADMIN                lpszaStartSelMessages[STARTSEL_MSG_NOT_ADMIN_IX             ][iMsgLangOff] // "Ðiam veiksmui turite bûti prisijungæs administratorium.")
#define STARTSEL_MSG_SURE_RESTORING           lpszaStartSelMessages[STARTSEL_MSG_SURE_RESTORING_IX        ][iMsgLangOff]  // "Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi katalogø „Mano_...” failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING                lpszaStartSelMessages[STARTSEL_MSG_RESTORING_IX             ][iMsgLangOff]  // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE           lpszaStartSelMessages[STARTSEL_MSG_RESTORING_FILE_IX        ][iMsgLangOff]  // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED                 lpszaStartSelMessages[STARTSEL_MSG_RESTORED_IX              ][iMsgLangOff]  // "Pradiniai duomenys sëkmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST                lpszaStartSelMessages[STARTSEL_MSG_ARC_EXIST_IX             ][iMsgLangOff]  // "Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
#define STARTSEL_MSG_ARC_CREATED              lpszaStartSelMessages[STARTSEL_MSG_ARC_CREATED_IX           ][iMsgLangOff]  // "Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE           lpszaStartSelMessages[STARTSEL_MSG_LOW_DISK_SPACE_IX        ][iMsgLangOff]  // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR         lpszaStartSelMessages[STARTSEL_MSG_DIR_ACCESS_ERROR_IX      ][iMsgLangOff]  // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
#define STARTSEL_MSG_NO_ARC                   lpszaStartSelMessages[STARTSEL_MSG_NO_ARC_IX                ][iMsgLangOff]  // "Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
#define STARTSEL_MSG_ARC_FOUND                lpszaStartSelMessages[STARTSEL_MSG_ARC_FOUND_IX             ][iMsgLangOff]  // "Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED             lpszaStartSelMessages[STARTSEL_MSG_ARC_RESTORED_IX          ][iMsgLangOff]  // "Atsarginë kopija sëkmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE          lpszaStartSelMessages[STARTSEL_MSG_LOW_FLASH_SPACE_IX       ][iMsgLangOff]  // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR       lpszaStartSelMessages[STARTSEL_MSG_FLASH_ACCESS_ERROR_IX    ][iMsgLangOff]  // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO   lpszaStartSelMessages[STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_IX][iMsgLangOff]  // "Uþverkite visus MIKO knygos failus.")


#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define STARTSEL_MSG_NOT_ADMIN_EN ((const unsigned char *)"") // "For this function you should be logged as privileged user.")
#define STARTSEL_MSG_SURE_RESTORING_EN ((const unsigned char *)"") // "All your changes will be lost, all files of the folders “Mano_...” and user data will be destroyed.\n \nAre you sure?")
#define STARTSEL_MSG_RESTORING_EN ((const unsigned char *)"") // "Restoring file...")
#define STARTSEL_MSG_RESTORING_FILE_EN ((const unsigned char *)"") // "Restoring file %s.%s...")
#define STARTSEL_MSG_RESTORED_EN ((const unsigned char *)"") // "Initial data successfully restored.")
#define STARTSEL_MSG_ARC_EXIST_EN ((const unsigned char *)"") // "Reserve copy, created %02d.%02d.%04d, already exists. Do you want to overwrite it?")
#define STARTSEL_MSG_ARC_CREATED_EN ((const unsigned char *)"") // "User files successfully copied from USB flash drive to %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_EN ((const unsigned char *)"") // "Unable to copy a file, check free space available on disk %s.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_EN ((const unsigned char *)"") // "Unable to create a folder, check writing access rights to %s.")
#define STARTSEL_MSG_NO_ARC_EN ((const unsigned char *)"") // "Reserve copy of USB flash drive was not found on this computer.")
#define STARTSEL_MSG_ARC_FOUND_EN ((const unsigned char *)"") // "Do you want to restore copy from %02d.%02d.%04d? All later changes to the USB flash drive will be lost.")
#define STARTSEL_MSG_ARC_RESTORED_EN ((const unsigned char *)"") // "Reserve copy successfully restored.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_EN ((const unsigned char *)"") // "Unable to copy a file, check free space available on the USB flash drive.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_EN ((const unsigned char *)"") // "Unable to create a folder, check writing access rights to the USB flash drive.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_EN ((const unsigned char *)"") // "Close all files of the MIKO book.")

#endif // #if ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

#define STARTSEL_MSG_NOT_ADMIN_LT ((const unsigned char *)"") // "Ðiam veiksmui turite bûti prisijungæs administratorium.")
#define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"") // "Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi aplankø „Mano_...” failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_LT ((const unsigned char *)"") // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_LT ((const unsigned char *)"") // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED_LT ((const unsigned char *)"") // "Pradiniai duomenys sëkmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST_LT ((const unsigned char *)"") // "Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_LT ((const unsigned char *)"") // "Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_LT ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_LT ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
#define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"") // "Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
#define STARTSEL_MSG_ARC_FOUND_LT ((const unsigned char *)"") // "Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_LT ((const unsigned char *)"") // "Atsarginë kopija sëkmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_LT ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_LT ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"") // "Uþverkite visus MIKO knygos failus.")

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define STARTSEL_MSG_NOT_ADMIN_PL_1250 ((const unsigned char *)"") // "Do wykonania tej czynnoœci musisz zalogowaæ siê do systemu jako administrator.")
#define STARTSEL_MSG_SURE_RESTORING_PL_1250 ((const unsigned char *)"") // "Wszystkie dokonane zmiany bêd¹ usuniête, wykasowane wszystkie pliki z katalogu "Mano_..." i dane u¿ytkownika.\n \nCzy wyra¿asz na to zgodê?")
#define STARTSEL_MSG_RESTORING_PL_1250 ((const unsigned char *)"") // "Przywracanie pliku...")
#define STARTSEL_MSG_RESTORING_FILE_PL_1250 ((const unsigned char *)"") // "Przywracanie pliku %s.%s...")
#define STARTSEL_MSG_RESTORED_PL_1250 ((const unsigned char *)"") // "Przywrócono pierwotne dane.")
#define STARTSEL_MSG_ARC_EXIST_PL_1250 ((const unsigned char *)"") // "Zapasowa kopia, zapisana %02d.%02d.%04d, ju¿ istnieje. Czy chcesz j¹ zamieniæ?")
#define STARTSEL_MSG_ARC_CREATED_PL_1250 ((const unsigned char *)"") // "Pliki u¿ytkownika skopiowano z noœnika USB na %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_PL_1250 ((const unsigned char *)"") // "Nie uda³o siê skopiowaæ pliku. Sprawd¿ czy na dysku %s jest wystarczaj¹co miejsca.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1250 ((const unsigned char *)"") // "Nie uda³o siê stworzyæ katalogu. SprawdŸ, czy plik %s ma prawo zapisywania.")
#define STARTSEL_MSG_NO_ARC_PL_1250 ((const unsigned char *)"") // "Na tym komputerze nie ma zapasowej kopii ksi¹¿ki MIKO.")
#define STARTSEL_MSG_ARC_FOUND_PL_1250 ((const unsigned char *)"") // "Czy chcesz przywróciæ kopiê stworzon¹ %02d.%02d.%04d? Wszystkie zmiany dokonane po tej dacie, bêd¹ usuniête.")
#define STARTSEL_MSG_ARC_RESTORED_PL_1250 ((const unsigned char *)"") // "Przywrócono zapasow¹ kopiê.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_PL_1250 ((const unsigned char *)"") // "Nie uda³o siê skopiowaæ pliku. SprawdŸ czy na noœniku USB jest wystarczaj¹co miejsca na kopiê.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1250 ((const unsigned char *)"") // "Nie uda³o siê stworzyæ katalogu. SprawdŸ, czy na noœniku USB nie s¹ zabronione prawa zapisywania.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1250 ((const unsigned char *)"") // "Zamknij wszystkie pliki ksi¹¿ki MIKO.")

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define STARTSEL_MSG_NOT_ADMIN_PL_1257 ((const unsigned char *)"") // "Do wykonania tej czynnoúci musisz zalogowaã siæ do systemu jako administrator.")
#define STARTSEL_MSG_SURE_RESTORING_PL_1257 ((const unsigned char *)"") // "Wszystkie dokonane zmiany bædà usuniæte, wykasowane wszystkie pliki z katalogu „Mano_...” i dane uýytkownika.\n \nCzy wyraýasz na to zgodæ?")
#define STARTSEL_MSG_RESTORING_PL_1257 ((const unsigned char *)"") // "Przywracanie pliku...")
#define STARTSEL_MSG_RESTORING_FILE_PL_1257 ((const unsigned char *)"") // "Przywracanie pliku %s.%s...")
#define STARTSEL_MSG_RESTORED_PL_1257 ((const unsigned char *)"") // "Przywrócono pierwotne dane.")
#define STARTSEL_MSG_ARC_EXIST_PL_1257 ((const unsigned char *)"") // "Zapasowa kopia, zapisana %02d.%02d.%04d, juý istnieje. Czy chcesz jà zamieniã?")
#define STARTSEL_MSG_ARC_CREATED_PL_1257 ((const unsigned char *)"") // "Pliki uýytkownika skopiowano z noúnika USB na %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_PL_1257 ((const unsigned char *)"") // "Nie udaùo siæ skopiowaã pliku. Sprawdý czy na dysku %s jest wystarczajàco miejsca.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1257 ((const unsigned char *)"") // "Nie udaùo siæ stworzyã katalogu. Sprawdê, czy plik %s ma prawo zapisywania.")
#define STARTSEL_MSG_NO_ARC_PL_1257 ((const unsigned char *)"") // "Na tym komputerze nie ma zapasowej kopii ksiàýki MIKO.")
#define STARTSEL_MSG_ARC_FOUND_PL_1257 ((const unsigned char *)"") // "Czy chcesz przywróciã kopiæ stworzonà %02d.%02d.%04d? Wszystkie zmiany dokonane po tej dacie, bædà usuniæte.")
#define STARTSEL_MSG_ARC_RESTORED_PL_1257 ((const unsigned char *)"") // "Przywrócono zapasowà kopiæ.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_PL_1257 ((const unsigned char *)"") // "Nie udaùo siæ skopiowaã pliku. Sprawdê czy na noúniku USB jest wystarczajàco miejsca na kopiæ.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1257 ((const unsigned char *)"") // "Nie udaùo siæ stworzyã katalogu. Sprawdê, czy na noúniku USB nie sà zabronione prawa zapisywania.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1257 ((const unsigned char *)"") // "Zamknij wszystkie pliki ksiàýki MIKO.")

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define STARTSEL_MSG_NOT_ADMIN_RU ((const unsigned char *)"") // "Ðiam veiksmui turite bûti prisijungæs administratorium.")
#define STARTSEL_MSG_SURE_RESTORING_RU ((const unsigned char *)"") // "Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi aplankø „Mano_...” failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_RU ((const unsigned char *)"") // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_RU ((const unsigned char *)"") // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED_RU ((const unsigned char *)"") // "Pradiniai duomenys sëkmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST_RU ((const unsigned char *)"") // "Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_RU ((const unsigned char *)"") // "Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_RU ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_RU ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
#define STARTSEL_MSG_NO_ARC_RU ((const unsigned char *)"") // "Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
#define STARTSEL_MSG_ARC_FOUND_RU ((const unsigned char *)"") // "Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_RU ((const unsigned char *)"") // "Atsarginë kopija sëkmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_RU ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_RU ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_RU ((const unsigned char *)"") // "Uþverkite visus MIKO knygos failus.")

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

// -------------------------------------
extern BOOL CALLBACK StartSelDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);

class StartSel : public KpStApp // KpCommonApp
{
// --------------------------- background
private:
   unsigned char m_lpszBackground[KP_MAX_FNAME_LEN+1]; // filename of container .BMP

public:
   bool m_bMikoPapFun; // ar MIKO knygos papildomø funkcijø meniu – tada reikia perspëjimo

   KpBmpData *m_BackgroundBmpPars;
   HWND m_hDialogWindow;
   
   unsigned int m_iItemsCount;

   int m_iHorMargin; // atstumas nuo kairiojo kraðto
   int m_iVertMargin; // atstumas nuo apatinio kraðto (mygtukus pradeda formuoti nuo apaèios
   int m_iButMargin; // atstumas tarp mygtukø
   
// --------------------------- buttons
public:
   StartSelKwdIxs m_iItemTypes[MAX_NUM_START_ITEMS];
   unsigned char m_alpszItems[MAX_NUM_START_ITEMS][KP_MAX_FNAME_LEN+1]; // .BMP file names, text menu item prompts
   unsigned char m_alpszButtonsHighlight[MAX_NUM_START_ITEMS][KP_MAX_FNAME_LEN+1]; // ButtonHilight .BMP file names
   unsigned char m_alpszButtonsSelected[MAX_NUM_START_ITEMS][KP_MAX_FNAME_LEN+1]; // ButtonSelected .BMP file names
   KpBmpData *m_pButtonBmpPars[MAX_NUM_START_ITEMS];
   KpBmpData *m_pButHlBmpPars[MAX_NUM_START_ITEMS];
   KpBmpData *m_pButSelBmpPars[MAX_NUM_START_ITEMS];
   HWND m_hButtonCtrls[MAX_NUM_START_ITEMS];

// --------------------------- actions
   StartSelKwdIxs m_iActionTypes[MAX_NUM_START_ITEMS];
   unsigned char m_alpszActions[MAX_NUM_START_ITEMS][KP_MAX_FILE_LIN_LEN /* KP_MAX_FNAME_LEN */ + 1]; // .exe, restore file names

   bool m_bInProgress; // semaforas, kad nesidubliuotø mygtukø paspaudimai
   
private:
   void ClearMembers(void);
public:
   StartSel(void);   
   ~StartSel();
   
   HRESULT ParseStartSelCfg(void); // former ParseStartSelIni()
   HRESULT ParseStartSelCfgLine(const unsigned char *lpszCfgLine, const unsigned char *lpszCfgFname); // skanuoja vienà cfg failo eilutæ
   HRESULT DumpMembers(void);

   HRESULT PerformAction(int iActNum, bool *pbEndFl, bool *pbCloseWindow); // vykdo komandà m_iItemTypes[iActNum]

   HRESULT OpenWindow(void);
   HRESULT CloseWindow(void);
};

extern StartSel StartSelObj;

#endif
