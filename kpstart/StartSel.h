// -----------------------------------------
// StartSel.h
// Keli� program� paleidimas i� meniu
// apibr��im� failas
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
STARTSEL_MSG_NOT_ADMIN_IX,                // "�iam veiksmui turite b�ti prisijung�s administratorium.")
STARTSEL_MSG_SURE_RESTORING_IX,           // "Bus panaikinti visi J�s� padaryti pakeitimai, i�trinti visi katalog� �Mano_...� failai ir naudotojo duomenys.\n \nAr sutinkate?")
STARTSEL_MSG_RESTORING_IX,                // "Atstatomas failas...")
STARTSEL_MSG_RESTORING_FILE_IX,           // "Atstatomas failas %s.%s...")
STARTSEL_MSG_RESTORED_IX,                 // "Pradiniai duomenys s�kmingai atstatyti.")
STARTSEL_MSG_ARC_EXIST_IX,                // "Atsargin� kopija, �ra�yta %04d-%02d-%02d, jau yra. Ar norite j� pakeisti?")
STARTSEL_MSG_ARC_CREATED_IX,              // "Naudotojo failai s�kmingai nukopijuoti i� atmintuko � %s.")
STARTSEL_MSG_LOW_DISK_SPACE_IX,           // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s u�tenka vietos.")
STARTSEL_MSG_DIR_ACCESS_ERROR_IX,         // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos %s ra�ymo teis�s.")
STARTSEL_MSG_NO_ARC_IX,                   // "Atmintuko atsargin�s kopijos �iame kompiuteryje n�ra.")
STARTSEL_MSG_ARC_FOUND_IX,                // "Ar norite atstatyti %04d-%02d-%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
STARTSEL_MSG_ARC_RESTORED_IX,             // "Atsargin� kopija s�kmingai atstatyta.")
STARTSEL_MSG_LOW_FLASH_SPACE_IX,          // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke u�tenka vietos.")
STARTSEL_MSG_FLASH_ACCESS_ERROR_IX,       // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos ra�ymo � atmintuk� teis�s.")
STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_IX,   // "U�verkite visus MIKO knygos failus.")

NumOfStartSelMessages
};

#define NumOfStartSelMessages_2 NumOfStartSelMessages
 
extern const unsigned char *lpszaStartSelMessages[NumOfStartSelMessages][KpNumOfLangs];

#define STARTSEL_MSG_NOT_ADMIN                lpszaStartSelMessages[STARTSEL_MSG_NOT_ADMIN_IX             ][iMsgLangOff] // "�iam veiksmui turite b�ti prisijung�s administratorium.")
#define STARTSEL_MSG_SURE_RESTORING           lpszaStartSelMessages[STARTSEL_MSG_SURE_RESTORING_IX        ][iMsgLangOff]  // "Bus panaikinti visi J�s� padaryti pakeitimai, i�trinti visi katalog� �Mano_...� failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING                lpszaStartSelMessages[STARTSEL_MSG_RESTORING_IX             ][iMsgLangOff]  // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE           lpszaStartSelMessages[STARTSEL_MSG_RESTORING_FILE_IX        ][iMsgLangOff]  // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED                 lpszaStartSelMessages[STARTSEL_MSG_RESTORED_IX              ][iMsgLangOff]  // "Pradiniai duomenys s�kmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST                lpszaStartSelMessages[STARTSEL_MSG_ARC_EXIST_IX             ][iMsgLangOff]  // "Atsargin� kopija, �ra�yta %04d-%02d-%02d, jau yra. Ar norite j� pakeisti?")
#define STARTSEL_MSG_ARC_CREATED              lpszaStartSelMessages[STARTSEL_MSG_ARC_CREATED_IX           ][iMsgLangOff]  // "Naudotojo failai s�kmingai nukopijuoti i� atmintuko � %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE           lpszaStartSelMessages[STARTSEL_MSG_LOW_DISK_SPACE_IX        ][iMsgLangOff]  // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s u�tenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR         lpszaStartSelMessages[STARTSEL_MSG_DIR_ACCESS_ERROR_IX      ][iMsgLangOff]  // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos %s ra�ymo teis�s.")
#define STARTSEL_MSG_NO_ARC                   lpszaStartSelMessages[STARTSEL_MSG_NO_ARC_IX                ][iMsgLangOff]  // "Atmintuko atsargin�s kopijos �iame kompiuteryje n�ra.")
#define STARTSEL_MSG_ARC_FOUND                lpszaStartSelMessages[STARTSEL_MSG_ARC_FOUND_IX             ][iMsgLangOff]  // "Ar norite atstatyti %04d-%02d-%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED             lpszaStartSelMessages[STARTSEL_MSG_ARC_RESTORED_IX          ][iMsgLangOff]  // "Atsargin� kopija s�kmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE          lpszaStartSelMessages[STARTSEL_MSG_LOW_FLASH_SPACE_IX       ][iMsgLangOff]  // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke u�tenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR       lpszaStartSelMessages[STARTSEL_MSG_FLASH_ACCESS_ERROR_IX    ][iMsgLangOff]  // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos ra�ymo � atmintuk� teis�s.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO   lpszaStartSelMessages[STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_IX][iMsgLangOff]  // "U�verkite visus MIKO knygos failus.")


#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define STARTSEL_MSG_NOT_ADMIN_EN ((const unsigned char *)"") // "For this function you should be logged as privileged user.")
#define STARTSEL_MSG_SURE_RESTORING_EN ((const unsigned char *)"") // "All your changes will be lost, all files of the folders �Mano_...� and user data will be destroyed.\n \nAre you sure?")
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

#define STARTSEL_MSG_NOT_ADMIN_LT ((const unsigned char *)"") // "�iam veiksmui turite b�ti prisijung�s administratorium.")
#define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"") // "Bus panaikinti visi J�s� padaryti pakeitimai, i�trinti visi aplank� �Mano_...� failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_LT ((const unsigned char *)"") // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_LT ((const unsigned char *)"") // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED_LT ((const unsigned char *)"") // "Pradiniai duomenys s�kmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST_LT ((const unsigned char *)"") // "Atsargin� kopija, �ra�yta %04d-%02d-%02d, jau yra. Ar norite j� pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_LT ((const unsigned char *)"") // "Naudotojo failai s�kmingai nukopijuoti i� atmintuko � %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_LT ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s u�tenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_LT ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos %s ra�ymo teis�s.")
#define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"") // "Atmintuko atsargin�s kopijos �iame kompiuteryje n�ra.")
#define STARTSEL_MSG_ARC_FOUND_LT ((const unsigned char *)"") // "Ar norite atstatyti %04d-%02d-%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_LT ((const unsigned char *)"") // "Atsargin� kopija s�kmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_LT ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke u�tenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_LT ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos ra�ymo � atmintuk� teis�s.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"") // "U�verkite visus MIKO knygos failus.")

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define STARTSEL_MSG_NOT_ADMIN_PL_1250 ((const unsigned char *)"") // "Do wykonania tej czynno�ci musisz zalogowa� si� do systemu jako administrator.")
#define STARTSEL_MSG_SURE_RESTORING_PL_1250 ((const unsigned char *)"") // "Wszystkie dokonane zmiany b�d� usuni�te, wykasowane wszystkie pliki z katalogu "Mano_..." i dane u�ytkownika.\n \nCzy wyra�asz na to zgod�?")
#define STARTSEL_MSG_RESTORING_PL_1250 ((const unsigned char *)"") // "Przywracanie pliku...")
#define STARTSEL_MSG_RESTORING_FILE_PL_1250 ((const unsigned char *)"") // "Przywracanie pliku %s.%s...")
#define STARTSEL_MSG_RESTORED_PL_1250 ((const unsigned char *)"") // "Przywr�cono pierwotne dane.")
#define STARTSEL_MSG_ARC_EXIST_PL_1250 ((const unsigned char *)"") // "Zapasowa kopia, zapisana %02d.%02d.%04d, ju� istnieje. Czy chcesz j� zamieni�?")
#define STARTSEL_MSG_ARC_CREATED_PL_1250 ((const unsigned char *)"") // "Pliki u�ytkownika skopiowano z no�nika USB na %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_PL_1250 ((const unsigned char *)"") // "Nie uda�o si� skopiowa� pliku. Sprawd� czy na dysku %s jest wystarczaj�co miejsca.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1250 ((const unsigned char *)"") // "Nie uda�o si� stworzy� katalogu. Sprawd�, czy plik %s ma prawo zapisywania.")
#define STARTSEL_MSG_NO_ARC_PL_1250 ((const unsigned char *)"") // "Na tym komputerze nie ma zapasowej kopii ksi��ki MIKO.")
#define STARTSEL_MSG_ARC_FOUND_PL_1250 ((const unsigned char *)"") // "Czy chcesz przywr�ci� kopi� stworzon� %02d.%02d.%04d? Wszystkie zmiany dokonane po tej dacie, b�d� usuni�te.")
#define STARTSEL_MSG_ARC_RESTORED_PL_1250 ((const unsigned char *)"") // "Przywr�cono zapasow� kopi�.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_PL_1250 ((const unsigned char *)"") // "Nie uda�o si� skopiowa� pliku. Sprawd� czy na no�niku USB jest wystarczaj�co miejsca na kopi�.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1250 ((const unsigned char *)"") // "Nie uda�o si� stworzy� katalogu. Sprawd�, czy na no�niku USB nie s� zabronione prawa zapisywania.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1250 ((const unsigned char *)"") // "Zamknij wszystkie pliki ksi��ki MIKO.")

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define STARTSEL_MSG_NOT_ADMIN_PL_1257 ((const unsigned char *)"") // "Do wykonania tej czynno�ci musisz zalogowa� si� do systemu jako administrator.")
#define STARTSEL_MSG_SURE_RESTORING_PL_1257 ((const unsigned char *)"") // "Wszystkie dokonane zmiany b�d� usuni�te, wykasowane wszystkie pliki z katalogu �Mano_...� i dane u�ytkownika.\n \nCzy wyra�asz na to zgod�?")
#define STARTSEL_MSG_RESTORING_PL_1257 ((const unsigned char *)"") // "Przywracanie pliku...")
#define STARTSEL_MSG_RESTORING_FILE_PL_1257 ((const unsigned char *)"") // "Przywracanie pliku %s.%s...")
#define STARTSEL_MSG_RESTORED_PL_1257 ((const unsigned char *)"") // "Przywr�cono pierwotne dane.")
#define STARTSEL_MSG_ARC_EXIST_PL_1257 ((const unsigned char *)"") // "Zapasowa kopia, zapisana %02d.%02d.%04d, ju� istnieje. Czy chcesz j� zamieni�?")
#define STARTSEL_MSG_ARC_CREATED_PL_1257 ((const unsigned char *)"") // "Pliki u�ytkownika skopiowano z no�nika USB na %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_PL_1257 ((const unsigned char *)"") // "Nie uda�o si� skopiowa� pliku. Sprawd� czy na dysku %s jest wystarczaj�co miejsca.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1257 ((const unsigned char *)"") // "Nie uda�o si� stworzy� katalogu. Sprawd�, czy plik %s ma prawo zapisywania.")
#define STARTSEL_MSG_NO_ARC_PL_1257 ((const unsigned char *)"") // "Na tym komputerze nie ma zapasowej kopii ksi��ki MIKO.")
#define STARTSEL_MSG_ARC_FOUND_PL_1257 ((const unsigned char *)"") // "Czy chcesz przywr�ci� kopi� stworzon� %02d.%02d.%04d? Wszystkie zmiany dokonane po tej dacie, b�d� usuni�te.")
#define STARTSEL_MSG_ARC_RESTORED_PL_1257 ((const unsigned char *)"") // "Przywr�cono zapasow� kopi�.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_PL_1257 ((const unsigned char *)"") // "Nie uda�o si� skopiowa� pliku. Sprawd� czy na no�niku USB jest wystarczaj�co miejsca na kopi�.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1257 ((const unsigned char *)"") // "Nie uda�o si� stworzy� katalogu. Sprawd�, czy na no�niku USB nie s� zabronione prawa zapisywania.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1257 ((const unsigned char *)"") // "Zamknij wszystkie pliki ksi��ki MIKO.")

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define STARTSEL_MSG_NOT_ADMIN_RU ((const unsigned char *)"") // "�iam veiksmui turite b�ti prisijung�s administratorium.")
#define STARTSEL_MSG_SURE_RESTORING_RU ((const unsigned char *)"") // "Bus panaikinti visi J�s� padaryti pakeitimai, i�trinti visi aplank� �Mano_...� failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_RU ((const unsigned char *)"") // "Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_RU ((const unsigned char *)"") // "Atstatomas failas %s.%s...")
#define STARTSEL_MSG_RESTORED_RU ((const unsigned char *)"") // "Pradiniai duomenys s�kmingai atstatyti.")
#define STARTSEL_MSG_ARC_EXIST_RU ((const unsigned char *)"") // "Atsargin� kopija, �ra�yta %04d-%02d-%02d, jau yra. Ar norite j� pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_RU ((const unsigned char *)"") // "Naudotojo failai s�kmingai nukopijuoti i� atmintuko � %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_RU ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar diske %s u�tenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_RU ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos %s ra�ymo teis�s.")
#define STARTSEL_MSG_NO_ARC_RU ((const unsigned char *)"") // "Atmintuko atsargin�s kopijos �iame kompiuteryje n�ra.")
#define STARTSEL_MSG_ARC_FOUND_RU ((const unsigned char *)"") // "Ar norite atstatyti %04d-%02d-%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_RU ((const unsigned char *)"") // "Atsargin� kopija s�kmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_RU ((const unsigned char *)"") // "Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke u�tenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_RU ((const unsigned char *)"") // "Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos ra�ymo � atmintuk� teis�s.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_RU ((const unsigned char *)"") // "U�verkite visus MIKO knygos failus.")

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
   bool m_bMikoPapFun; // ar MIKO knygos papildom� funkcij� meniu � tada reikia persp�jimo

   KpBmpData *m_BackgroundBmpPars;
   HWND m_hDialogWindow;
   
   unsigned int m_iItemsCount;

   int m_iHorMargin; // atstumas nuo kairiojo kra�to
   int m_iVertMargin; // atstumas nuo apatinio kra�to (mygtukus pradeda formuoti nuo apa�ios
   int m_iButMargin; // atstumas tarp mygtuk�
   
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

   bool m_bInProgress; // semaforas, kad nesidubliuot� mygtuk� paspaudimai
   
private:
   void ClearMembers(void);
public:
   StartSel(void);   
   ~StartSel();
   
   HRESULT ParseStartSelCfg(void); // former ParseStartSelIni()
   HRESULT ParseStartSelCfgLine(const unsigned char *lpszCfgLine, const unsigned char *lpszCfgFname); // skanuoja vien� cfg failo eilut�
   HRESULT DumpMembers(void);

   HRESULT PerformAction(int iActNum, bool *pbEndFl, bool *pbCloseWindow); // vykdo komand� m_iItemTypes[iActNum]

   HRESULT OpenWindow(void);
   HRESULT CloseWindow(void);
};

extern StartSel StartSelObj;

#endif
