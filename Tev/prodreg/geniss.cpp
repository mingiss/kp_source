// ===================================================
// geniss.cpp
// Inno Setup scriptu generatorius
//
// 2012.09.20  mp    individualus XFS archyvø kodavimas
// 2012.09.21  mp    pataisytas Default.iss makrokomandø repleisinimas – anksèiau repleisindavo source failà 
//
// kaþko su mingw neveikia in_file.open("files_cd\\unreg.exe". ...)
//
// Pagamina:
// gen_cd.iss           - licencijuojamai CD versijai
// gen_upd.iss          - licencijuojamos CD versijos nemokamam atnaujinimui
// gen_flash.iss        - atmintuko versijai
// gen_flash_start.iss  - atmintuko (ar kokios kitos "gyvos") versijos paleidejui

// naudoja projekto parametru faila geniss.ini:


// ProdNameRaw =  'Á pagalbà abiturientui. Istorija 2000-2006'             produkto pavadinimas su liet. raidem, figuruojantis setupo ir uninstallo pranesimuose ir registro raktu pavadinimuose
// ProdName =     GetProdNameRaw + '.'                                     produkto pavadinimas su liet. raidem, figuruojantis setupo ir uninstallo pranesimuose ir registro raktu pavadinimuose
//
// ProjID =       ipai                                                     paleidimo failo vardas be pletinio ir apostrofu, grynas tekstas be kreipiniu i funkcijas
//
// ProdVer =      '13014'                                                  prodreg licencijavimo versijos numeris tekstiniam formate, tik skaitmenys
// ProdVerFlash = '18014'                                                  atmintuko versijos ProdVer
// ProdVerNet =   '9012'                                                   tinklinës versijos ProdVer
//
// Ver =          v1.11                                                    versijos numeris tekstiniam formate, gale gali buti raides, be apostrofu (OutputBaseFilename nepriima {code:GetVerStr} ir {code:GetSetupFNameStr}), negali buti funkciju
// PrevVer =      v1.11                                                    ankstesnio atnaujinimo versija, be apostrofu
// FirstVer =     v1.11                                                    pradine produkto versija, be apostrofu
//
// VerName =      GetProdNameRaw + ' ' + GetVer + '.'                      produkto versijos pavadinimas su liet. raidem, figuruojantis setupo pranesimuose
// UpdVerName =   GetProdNameRaw + ' atnaujinimas ' + GetVer + '.'         produkto versijos pavadinimas su liet. raidem, figuruojantis atnaujinimo setupo pranesimuose
// PrevVerName =  GetProdNameRaw + ' atnaujinimas ' + GetPrevVer + '.'     ankstesnio atnaujinimo versijos pavadinimas
// FirstVerName = GetProdNameRaw + ' ' + GetFirstVer + '.'                 pradines produkto versijos pavadinimas (tos, kuriai dar nebuvo atnaujinimo, versijos su UpdNum = 1 pavadinimas VerName
//
// UpdNum =       1                                                        atnaujinimo/versijos numeris, atsimenamas registro rakte HKEY_LOCAL_MACHINE/Software/{ProdVer}; pradines versijos UpdNum = 1; 0 reiskia, kad produktas ismestas arba diegimas buvo nesekmingas
// PrevUpdNum =   0                                                        ankstesnio atnaujinimo numeris, tikrinimui atnaujinimo diegimo metu, HKEY_LOCAL_MACHINE/Software/{ProdVer}/Installed turi buti nemazesnis
// BuildNum =     1                                                        build'o numeris, ðiaip reikalingas chkvol diegimo AppName generavimui - kad skirtingø build'ø tikrinimai diegtøsi á skirtingas vietas
//
// ; ChkVol rezimui tiesiog GetProdName netinka, nes automatas prie ProdName prideda " atmintuke"
// ProdFNameRaw = 'IPA Istorija 2000-2006'                                 produkto pavadinimo variantas lotyniskom raidem (gali bti naudojamas kaip ProdFName ir kaip paskutinis ProdDir ir ProdGroup elementas)
// ProdFName =    GetProdFNameRaw                                          paleidimo piktogramos failo vardas - produkto pavadinimo variantas lotyniskom raidem
// ProdDir =      GetProdFNameRaw                                          diegimo katalogo - produkto pavadinimo variantas lotyniskom raidem, gali buti katalogu medzio fragmentas
// ProdGroup =    GetProdFNameRaw                                          paleidimo meniu skyrelio vardas - produkto pavadinimo variantas lotyniskom raidem, gali buti katalogu medzio fragmentas
//
// ExeFName =     ipai                                                     paleidimo failo vardas be pletinio ir apustrofu, grynas tekstas be kreipiniu i funkcijas
//                                                                         gali bûti GetProjID
// IconFName =    'ipa.ico'                                                .ico ar .exe failo, esancio kataloge {app}, pilnas vardas
// SvrFName =     ipaisvr                                                  serverio paleidimo failo vardas be pletinio ir apustrofu, grynas tekstas be kreipiniu i funkcijas
//
// SplashBMP =    Makroekonomika.bmp
// StartPDF =     Makroekonomika.pdf
// Password =     123456
//
// SetupFName =   IPA_Istorija_2000-2006                                   setup failo ar katalogo vardo pradþia (iki "_diegimas.exe"), be pletinio ir apostrofu
//                                                                         gali bûti GetProjID
//
// AutoRun =      No                                                       ar generuoti nuorodas Start/Programs/StartUp
// RequireAdmin = Yes                                                      ar reikalauti administratoriaus; jei ne - neirasines ir UpdNum i registrus
// PartialInstall = No                                                     Diegimas iðkvieèiamas ið kito diegimo - nereikia jokiø vediklio puslapiø
// PartialDir = No                                                         Silpnesnis uz PartialInstall - produktai atskiri, bet iesko jau idiegto produkto FirstVerName
//                                                                         Tas pats ir to paties produkto papildymams: 
//                                                                         diegimas visada yra "papildymas", reikalauja pries tai idiegtos pagrindines dalies (Bebras, Arkim) 
//                                                                         (ðitas variantas anksèiau buvo PartialInstall, bet tas niekuo nesiskiria nuo PartialDir)  
// ChkUpd = Yes                                                            Ar generuoti atnaujinimø tikrinimo kodà
// ProdType = KMP                                                          Dar reikðmës: EVAD, EBOOK ir PROG – pagal reikðmæ generuoja Inno praneðimø failà
//
// CidMode = 11                                                            KompID skaièiavimo algoritmas: 11 be varþto, 31 – su varþtu
//

// ------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
// #include <iostream.h>
#include <iostream>
// #include <fstream.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
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
#include "kpstmsg.h"
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
#include "geniss.h"
#include "geniss_en.h"
#include "geniss_lt.h"
#include "geniss_pl_1250.h"
#include "geniss_pl_1257.h"
#include "geniss_ru.h"


#if Compiler != Watcom
using namespace std;
#endif


// -----------------------------------------------
const unsigned char *lpszaGenissMessages[NumOfGenissMessages_2][KpNumOfLangs_2] =
{
GENISS_MSG_START_PROG_EN,         GENISS_MSG_START_PROG_LT,         GENISS_MSG_START_PROG_PL_1250,         GENISS_MSG_START_PROG_PL_1257,         GENISS_MSG_START_PROG_RU,         GENISS_MSG_START_PROG_RU,         // "Paleisti programà" 
GENISS_MSG_UNSUCC_START_EN,       GENISS_MSG_UNSUCC_START_LT,       GENISS_MSG_UNSUCC_START_PL_1250,       GENISS_MSG_UNSUCC_START_PL_1257,       GENISS_MSG_UNSUCC_START_RU,       GENISS_MSG_UNSUCC_START_RU,       // "Nepavyko paleisti failo"
GENISS_MSG_PROG_NOT_ISTALLED_EN,  GENISS_MSG_PROG_NOT_ISTALLED_LT,  GENISS_MSG_PROG_NOT_ISTALLED_PL_1250,  GENISS_MSG_PROG_NOT_ISTALLED_PL_1257,  GENISS_MSG_PROG_NOT_ISTALLED_RU,  GENISS_MSG_PROG_NOT_ISTALLED_RU,  // "Programa „\' + GetFirstVerName + \'” dar neádiegta"
GENISS_MSG_UPD_NOT_ISTALLED_EN,   GENISS_MSG_UPD_NOT_ISTALLED_LT,   GENISS_MSG_UPD_NOT_ISTALLED_PL_1250,   GENISS_MSG_UPD_NOT_ISTALLED_PL_1257,   GENISS_MSG_UPD_NOT_ISTALLED_RU,   GENISS_MSG_UPD_NOT_ISTALLED_RU,   // /* atnaujinimas */ "„\' + GetPrevVerName + \'” dar neádiegtas"
                                                                                                                                                                                                                                
GENISS_MSG_RESTART_ADMIN_EN,      GENISS_MSG_RESTART_ADMIN_LT,      GENISS_MSG_RESTART_ADMIN_PL_1250,      GENISS_MSG_RESTART_ADMIN_PL_1257,      GENISS_MSG_RESTART_ADMIN_RU,      GENISS_MSG_RESTART_ADMIN_RU,      // "programà paleiskite ið naujo administratoriaus teisëmis"
GENISS_MSG_INST_ADMIN_EN,         GENISS_MSG_INST_ADMIN_LT,         GENISS_MSG_INST_ADMIN_PL_1250,         GENISS_MSG_INST_ADMIN_PL_1257,         GENISS_MSG_INST_ADMIN_RU,         GENISS_MSG_INST_ADMIN_RU,         // "Diegimui reikalingos administratoriaus teisës"
GENISS_MSG_UNINST_ADMIN_EN,       GENISS_MSG_UNINST_ADMIN_LT,       GENISS_MSG_UNINST_ADMIN_PL_1250,       GENISS_MSG_UNINST_ADMIN_PL_1257,       GENISS_MSG_UNINST_ADMIN_RU,       GENISS_MSG_UNINST_ADMIN_RU,       // "Panaikinimui reikalingos administratoriaus teisës"
                                                                                                                                                                                                                                
GENISS_MSG_FLASH_PLAYER_EN,       GENISS_MSG_FLASH_PLAYER_LT,       GENISS_MSG_FLASH_PLAYER_PL_1250,       GENISS_MSG_FLASH_PLAYER_PL_1257,       GENISS_MSG_FLASH_PLAYER_RU,       GENISS_MSG_FLASH_PLAYER_RU,       // "Dabar bus ádiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."
GENISS_MSG_CABRI_EN,              GENISS_MSG_CABRI_LT,              GENISS_MSG_CABRI_PL_1250,              GENISS_MSG_CABRI_PL_1257,              GENISS_MSG_CABRI_RU,              GENISS_MSG_CABRI_RU,              // "Dabar bus ádiegtas Cabri 3D áskiepis. Vykdykite tolesnius diegimo programos nurodymus."
                                                                                                                                                                                                                                
GENISS_MSG_NAT_LET_EN,            GENISS_MSG_NAT_LET_LT,            GENISS_MSG_NAT_LET_PL_1250,            GENISS_MSG_NAT_LET_PL_1257,            GENISS_MSG_NAT_LET_RU,            GENISS_MSG_NAT_LET_RU,            // "Lietuviðkas raides su diakritiniais þenklais (nosinëmis, paukðèiukais ir kt.) failø varduose galima naudoti tik tuo atveju, jei Jûsø operacinëje sistemoje Windows nustatytos Lietuvos regiono parinktys ir Jûs nesiruoðiate jø keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti failø varduose?"
                                                                                                                                                                                                                                
GENISS_MSG_ATM_KOD_TIT_EN,        GENISS_MSG_ATM_KOD_TIT_LT,        GENISS_MSG_ATM_KOD_TIT_PL_1250,        GENISS_MSG_ATM_KOD_TIT_PL_1257,        GENISS_MSG_ATM_KOD_TIT_RU,        GENISS_MSG_ATM_KOD_TIT_RU,        // "Atmintuko kodas"
GENISS_MSG_ATM_KOD_MAIN_EN,       GENISS_MSG_ATM_KOD_MAIN_LT,       GENISS_MSG_ATM_KOD_MAIN_PL_1250,       GENISS_MSG_ATM_KOD_MAIN_PL_1257,       GENISS_MSG_ATM_KOD_MAIN_RU,       GENISS_MSG_ATM_KOD_MAIN_RU,       // "Áveskite kodà, kuris uþraðytas ant atmintuko."
GENISS_MSG_ATM_KOD_PROMPT_EN,     GENISS_MSG_ATM_KOD_PROMPT_LT,     GENISS_MSG_ATM_KOD_PROMPT_PL_1250,     GENISS_MSG_ATM_KOD_PROMPT_PL_1257,     GENISS_MSG_ATM_KOD_PROMPT_RU,     GENISS_MSG_ATM_KOD_PROMPT_RU,     // GENISS_MSG_ATM_KOD_TIT
                                                                                                                                                                                                                                
GENISS_MSG_CHK_UPD_TIT_EN,        GENISS_MSG_CHK_UPD_TIT_LT,        GENISS_MSG_CHK_UPD_TIT_PL_1250,        GENISS_MSG_CHK_UPD_TIT_PL_1257,        GENISS_MSG_CHK_UPD_TIT_RU,        GENISS_MSG_CHK_UPD_TIT_RU,        // "Automatinis atnaujinimø tikrinimas"
GENISS_MSG_CHK_UPD_MAIN_EN,       GENISS_MSG_CHK_UPD_MAIN_LT,       GENISS_MSG_CHK_UPD_MAIN_PL_1250,       GENISS_MSG_CHK_UPD_MAIN_PL_1257,       GENISS_MSG_CHK_UPD_MAIN_RU,       GENISS_MSG_CHK_UPD_MAIN_RU,       // "Iðvalykite varnelæ, jei nenorite, kad automatiðkai internetu bûtø tikrinama, ar atsirado nauji programos pataisymai ar papildymai."
GENISS_MSG_CHK_UPD_PROMPT_EN,     GENISS_MSG_CHK_UPD_PROMPT_LT,     GENISS_MSG_CHK_UPD_PROMPT_PL_1250,     GENISS_MSG_CHK_UPD_PROMPT_PL_1257,     GENISS_MSG_CHK_UPD_PROMPT_RU,     GENISS_MSG_CHK_UPD_PROMPT_RU,     // "Automatinis atnaujinimø tikrinimas"
                                                                                                                                                                                                                                
GENISS_PROD_FLASH_EN,             GENISS_PROD_FLASH_LT,             GENISS_PROD_FLASH_PL_1250,             GENISS_PROD_FLASH_PL_1257,             GENISS_PROD_FLASH_RU,             GENISS_PROD_FLASH_RU,             // "atmintuke" // atmintukinë produkto versija
GENISS_PROD_LAN_EN,               GENISS_PROD_LAN_LT,               GENISS_PROD_LAN_PL_1250,               GENISS_PROD_LAN_PL_1257,               GENISS_PROD_LAN_RU,               GENISS_PROD_LAN_RU,               // "tinkle" // tinklinë produkto versija
GENISS_PROD_SERVER_EN,            GENISS_PROD_SERVER_LT,            GENISS_PROD_SERVER_PL_1250,            GENISS_PROD_SERVER_PL_1257,            GENISS_PROD_SERVER_RU,            GENISS_PROD_SERVER_RU,            // "serveris" // produkto duomenø/licencijø serveris LAN-e   
                                                                                                                                                                                                                                
GENISS_LINK_OPTIONS_EN,           GENISS_LINK_OPTIONS_LT,           GENISS_LINK_OPTIONS_PL_1250,           GENISS_LINK_OPTIONS_PL_1257,           GENISS_LINK_OPTIONS_RU,           GENISS_LINK_OPTIONS_EN,           // "Parinktys"
GENISS_LINK_REG_EN,               GENISS_LINK_REG_LT,               GENISS_LINK_REG_PL_1250,               GENISS_LINK_REG_PL_1257,               GENISS_LINK_REG_RU,               GENISS_LINK_REG_EN,               // "Registracija"
GENISS_LINK_UNREG_EN,             GENISS_LINK_UNREG_LT,             GENISS_LINK_UNREG_PL_1250,             GENISS_LINK_UNREG_PL_1257,             GENISS_LINK_UNREG_RU,             GENISS_LINK_UNREG_EN,             // "Panaikinimas"
GENISS_LINK_FLASH_EN,             GENISS_LINK_FLASH_LT,             GENISS_LINK_FLASH_PL_1250,             GENISS_LINK_FLASH_PL_1257,             GENISS_LINK_FLASH_RU,             GENISS_LINK_FLASH_EN,             // GENISS_PROD_FLASH
GENISS_LINK_FLASH_CHK_EN,         GENISS_LINK_FLASH_CHK_LT,         GENISS_LINK_FLASH_CHK_PL_1250,         GENISS_LINK_FLASH_CHK_PL_1257,         GENISS_LINK_FLASH_CHK_RU,         GENISS_LINK_FLASH_CHK_EN,         // "atmintuko tikrinimas"
GENISS_LINK_LAN_EN,               GENISS_LINK_LAN_LT,               GENISS_LINK_LAN_PL_1250,               GENISS_LINK_LAN_PL_1257,               GENISS_LINK_LAN_RU,               GENISS_LINK_LAN_EN,               // GENISS_PROD_LAN
GENISS_LINK_SERVER_EN,            GENISS_LINK_SERVER_LT,            GENISS_LINK_SERVER_PL_1250,            GENISS_LINK_SERVER_PL_1257,            GENISS_LINK_SERVER_RU,            GENISS_LINK_SERVER_EN,            // GENISS_PROD_SERVER
GENISS_LINK_SERVER_MANAGEMENT_EN, GENISS_LINK_SERVER_MANAGEMENT_LT, GENISS_LINK_SERVER_MANAGEMENT_PL_1250, GENISS_LINK_SERVER_MANAGEMENT_PL_1257, GENISS_LINK_SERVER_MANAGEMENT_RU, GENISS_LINK_SERVER_MANAGEMENT_EN, // "Serverio valdymas"
GENISS_LINK_CLEAN_NAT_EN,         GENISS_LINK_CLEAN_NAT_LT,         GENISS_LINK_CLEAN_NAT_PL_1250,         GENISS_LINK_CLEAN_NAT_PL_1257,         GENISS_LINK_CLEAN_NAT_RU,         GENISS_LINK_CLEAN_NAT_EN,         // "Senø rezultatø valymas"
GENISS_LINK_CLEAN_LAT_EN,         GENISS_LINK_CLEAN_LAT_LT,         GENISS_LINK_CLEAN_LAT_PL_1250,         GENISS_LINK_CLEAN_LAT_PL_1257,         GENISS_LINK_CLEAN_LAT_RU,         GENISS_LINK_CLEAN_LAT_EN,         // "Senu rezultatu valymas" 
                                                                                                                                                                                                                                
GENISS_INSERT_FLASH_KEY_EN,       GENISS_INSERT_FLASH_KEY_LT,       GENISS_INSERT_FLASH_KEY_PL_1250,       GENISS_INSERT_FLASH_KEY_PL_1257,       GENISS_INSERT_FLASH_KEY_RU,       GENISS_INSERT_FLASH_KEY_RU,       // "Ákiðkite atmintukà su programa "

GENISS_LINK_DIAG_MSG_NAT_EN,      GENISS_LINK_DIAG_MSG_NAT_LT,      GENISS_LINK_DIAG_MSG_NAT_PL_1250,      GENISS_LINK_DIAG_MSG_NAT_PL_1257,      GENISS_LINK_DIAG_MSG_NAT_RU,      GENISS_LINK_DIAG_MSG_NAT_EN,      // "Diagnostinio praneðimo siuntimas"
GENISS_LINK_DIAG_MSG_LAT_EN,      GENISS_LINK_DIAG_MSG_LAT_LT,      GENISS_LINK_DIAG_MSG_LAT_PL_1250,      GENISS_LINK_DIAG_MSG_LAT_PL_1257,      GENISS_LINK_DIAG_MSG_LAT_RU,      GENISS_LINK_DIAG_MSG_LAT_EN,      // "Diagnostinio pranesimo siuntimas"
};


// ------------------------------------
const unsigned char *FnamePref[MaxGenIssType_13] = {
(const unsigned char *)"files",        // GenIssFiles
(const unsigned char *)"files",        // GenIssCd
(const unsigned char *)"files",        // GenIssSh
(const unsigned char *)"files",        // GenIssCert
(const unsigned char *)"files",        // GenIssUpd
(const unsigned char *)"files",        // GenIssUpdWhole
(const unsigned char *)"files",        // GenIssGrp
(const unsigned char *)"files",        // GenIssFlash
(const unsigned char *)"files",        // GenIssFlashUpd
(const unsigned char *)"files",        // GenIssFlashUpdWhole
(const unsigned char *)"files",        // GenIssFlashStart
(const unsigned char *)"files",        // GenIssFlashStartUpd
(const unsigned char *)"files",        // GenIssChkVol
(const unsigned char *)"files",        // GenIssNet
(const unsigned char *)"files",        // GenIssSvr
(const unsigned char *)"files",        // GenIssCli
(const unsigned char *)"files",        // GenIssRez
(const unsigned char *)"fonts",        // GenIssFonts
(const unsigned char *)"files",        // GenIssDel
(const unsigned char *)"files",        // GenIssDelWhole
(const unsigned char *)"files",        // GenIssFinst
};

const unsigned char *FnameSuff[MaxGenIssType_13] = {
(const unsigned char *)"",             // GenIssFiles
(const unsigned char *)"_cd",          // GenIssCd
(const unsigned char *)"_sh",          // GenIssSh
(const unsigned char *)"_creg",        // GenIssCert
(const unsigned char *)"_upd",         // GenIssUpd
(const unsigned char *)"_upd_whole",   // GenIssUpdWhole
(const unsigned char *)"_grp",         // GenIssGrp
(const unsigned char *)"_flash",       // GenIssFlash
(const unsigned char *)"_flash_upd",   // GenIssFlashUpd
(const unsigned char *)"_flash_upd_whole", // GenIssFlashUpdWhole
(const unsigned char *)"_flash_start", // GenIssFlashStart
(const unsigned char *)"_flash_start_upd", // GenIssFlashStartUpd
(const unsigned char *)"_chkvol",      // GenIssChkVol
(const unsigned char *)"_net",         // GenIssNet
(const unsigned char *)"_svr",         // GenIssSvr
(const unsigned char *)"_cli",         // GenIssCli
(const unsigned char *)"_rez",         // GenIssRez
(const unsigned char *)"",             // GenIssFonts
(const unsigned char *)"_del",         // GenIssDel
(const unsigned char *)"_del_whole",   // GenIssDelWhole
(const unsigned char *)"_finst",       // GenIssFinst
};


// ------------------------------------
unsigned char ProdName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdNameRaw[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdFNameRaw[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdFName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdDir[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdGroup[GEN_CSS_STR_PAR_LEN + 1];
unsigned char VerName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char Ver[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdVer[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdVerFlash[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProdVerNet[GEN_CSS_STR_PAR_LEN + 1];
unsigned char UpdVerName[GEN_CSS_STR_PAR_LEN + 1];
int UpdNum;
unsigned char PrevVerName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char PrevVer[GEN_CSS_STR_PAR_LEN + 1];
int PrevUpdNum;
int BuildNum;
unsigned char FirstVerName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char FirstVer[GEN_CSS_STR_PAR_LEN + 1];
unsigned char IconFName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char SetupFName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ExeFName[GEN_CSS_STR_PAR_LEN + 1];
unsigned char SvrFName[GEN_CSS_STR_PAR_LEN + 1];
bool AutoRun;
bool RequireAdmin;
bool PartialInstall;
bool PartialDir;
ProdTypes iProdType;
bool ChkUpd;
unsigned char Publisher[GEN_CSS_STR_PAR_LEN + 1];
unsigned char SplashBMP[GEN_CSS_STR_PAR_LEN + 1];
unsigned char StartPDF[GEN_CSS_STR_PAR_LEN + 1];
unsigned char Password[GEN_CSS_STR_PAR_LEN + 1];
unsigned char ProjID[GEN_CSS_STR_PAR_LEN + 1];
unsigned char Kalba[GEN_CSS_STR_PAR_LEN + 1];
int CidMode = (KPST_COMPID_BIOS_DATE | KPST_COMPID_PROC_NAME);

bool BuildNumInsideVer = False;


const unsigned char *GenIssKwds[NumOfGenKwds_11 + 1] =
{
   (const unsigned char *)"ProdName",
   (const unsigned char *)"ProdNameRaw",
   (const unsigned char *)"ProdDir",
   (const unsigned char *)"ProdGroup",
   (const unsigned char *)"ProdFNameRaw",
   (const unsigned char *)"ProdFName",
   (const unsigned char *)"VerName",
   (const unsigned char *)"Ver",
   (const unsigned char *)"ProdVer",
   (const unsigned char *)"ProdVerFlash",
   (const unsigned char *)"ProdVerNet",
   (const unsigned char *)"UpdVerName",
   (const unsigned char *)"UpdNum",
   (const unsigned char *)"PrevVerName",
   (const unsigned char *)"PrevVer",
   (const unsigned char *)"PrevUpdNum",
   (const unsigned char *)"BuildNum",
   (const unsigned char *)"FirstVerName",
   (const unsigned char *)"FirstVer",
   (const unsigned char *)"IconFName",
   (const unsigned char *)"SetupFName",
   (const unsigned char *)"ExeFName",
   (const unsigned char *)"SvrFName",
   (const unsigned char *)"AutoRun",
   (const unsigned char *)"RequireAdmin",
   (const unsigned char *)"PartialInstall",
   (const unsigned char *)"PartialDir",
   (const unsigned char *)"ProdType",
   (const unsigned char *)"ChkUpd",
   (const unsigned char *)"Publisher",
   (const unsigned char *)"SplashBMP",
   (const unsigned char *)"StartPDF",
   (const unsigned char *)"Password",
   (const unsigned char *)"ProjID",
   (const unsigned char *)"Kalba",
   (const unsigned char *)"CidMode",
   NULL
};


const unsigned char *YesNoKwds[] =
{
   (const unsigned char *)"No",
   (const unsigned char *)"Yes",
   NULL
};


const unsigned char *lpszaProdTypeKwds[ProdTypeCnt_5] =
{
   (const unsigned char *)"PROG",   // KpPROG
   (const unsigned char *)"KMP",    // KpKMP
   (const unsigned char *)"EVAD",   // KpEVAD
   (const unsigned char *)"MIKO",   // KpMIKO
   (const unsigned char *)"UPD",    // KpUPD
   (const unsigned char *)"EBOOK",  // KpEBOOK
   (const unsigned char *)"SALT",  // KpSALT
};


const unsigned char *lpszaIslSufixes[ProdTypeCnt_5] =
{
   (const unsigned char *)"programa",  // KpPROG
   (const unsigned char *)"KMP",       // KpKMP
   (const unsigned char *)"evad",      // KpEVAD
   (const unsigned char *)"MIKO", // "programa",  // "miko", // KpMIKO
   (const unsigned char *)"upd",       // KpUPD
   (const unsigned char *)"ebook",     // KpEBOOK
   (const unsigned char *)"salt",      // KpSALT
};


// -----------------------------------------
#define LangCodesCnt_1 4

const unsigned char *LangCodes[LangCodesCnt_1 + 1] =
{
   (const unsigned char *)"LT",
   (const unsigned char *)"EN",
   (const unsigned char *)"PL",
   (const unsigned char *)"RU",
   null
};

KpLang MsgLangs[LangCodesCnt_1] =
{
   KpLangLt, // "LT"
   KpLangEn, // "EN"
   KpLangPl_1257, // "PL"
   KpLangRu_1251, // KpLangRu_0, // "RU"
};

const unsigned char *SetupFileSuffixes[KpNumOfLangs_2] =
{
   (const unsigned char *)"_setup",       // KpLangEn
   (const unsigned char *)"_diegimas",    // KpLangLt
   (const unsigned char *)"_instalacja",  // KpLangPl_1250
   (const unsigned char *)"_instalacja",  // KpLangPl_1257
   (const unsigned char *)"_setup",       // KpLangRu_1251
   (const unsigned char *)"_setup",       // KpLangRu_0
};

const unsigned char *WholeUpdateSuffix[KpNumOfLangs_2] =
{
   (const unsigned char *)"_whole", // KpLangEn
   (const unsigned char *)"_visas", // KpLangLt
   (const unsigned char *)"_pelna", // "_kompletna", // KpLangPl_1250
   (const unsigned char *)"_pelna", // "_kompletna", // KpLangPl_1257
   (const unsigned char *)"_whole", // KpLangRu_1251
   (const unsigned char *)"_whole", // KpLangRu_0
};

const unsigned char *UpdateSuffix[KpNumOfLangs_2] =
{
   (const unsigned char *)"_update",         // KpLangEn
   (const unsigned char *)"_atnaujinimas",   // KpLangLt
   (const unsigned char *)"_aktualizacja",   // KpLangPl_1250
   (const unsigned char *)"_aktualizacja",   // KpLangPl_1257
   (const unsigned char *)"_update",         // KpLangRu_1251
   (const unsigned char *)"_update",         // KpLangRu_0
};

const unsigned char *PartialUpdateSuffix[KpNumOfLangs_2] =
{
   (const unsigned char *)"_in_parts", // KpLangEn
   (const unsigned char *)"_gabalais", // KpLangLt
   (const unsigned char *)"_sztuczna", // KpLangPl_1250
   (const unsigned char *)"_sztuczna", // KpLangPl_1257
   (const unsigned char *)"_in_parts", // KpLangRu_1251
   (const unsigned char *)"_in_parts", // KpLangRu_0
};

const unsigned char *FlashUpdateSuffix[KpNumOfLangs_2] =
{
   (const unsigned char *)"_flash",       // KpLangEn
   (const unsigned char *)"_atmintuko",   // KpLangLt
   (const unsigned char *)"_nosnika",     // KpLangPl_1250
   (const unsigned char *)"_nosnika",     // KpLangPl_1257
   (const unsigned char *)"_flash",       // KpLangRu_1251
   (const unsigned char *)"_flash",       // KpLangRu_0
};

const unsigned char *SetupFileLangSuffixes[KpNumOfLangs_2] =
{
   (const unsigned char *)"_en", // KpLangEn
   (const unsigned char *)"",    // KpLangLt
   (const unsigned char *)"_pl", // KpLangPl_1250
   (const unsigned char *)"_pl", // KpLangPl_1257
   (const unsigned char *)"_ru", // KpLangRu_1251
   (const unsigned char *)"_ru", // KpLangRu_0
};

const unsigned char *SetupFileLangSuffixesExact[KpNumOfLangs_2] =
{
   (const unsigned char *)"_en", // KpLangEn
   (const unsigned char *)"",    // KpLangLt
   (const unsigned char *)"_pl_1250", // KpLangPl_1250
   (const unsigned char *)"_pl_1257", // KpLangPl_1257
   (const unsigned char *)"_ru_1251", // KpLangRu_1251
   (const unsigned char *)"_ru_0", // KpLangRu_0
};

const unsigned char *InnoSetupMsgFilePref[KpNumOfLangs_2] =
{
   (const unsigned char *)"English",      // KpLangEn
   (const unsigned char *)"Lithuanian",   // KpLangLt
   (const unsigned char *)"Polish",       // KpLangPl_1250
   (const unsigned char *)"Polish_1257",  // KpLangPl_1257
   (const unsigned char *)"Russian",      // KpLangRu_1251
   (const unsigned char *)"Russian",      // KpLangRu_0
};


// --------------------------------------
#define XFSTOOL_CFG_CODE_OFFSET_1 0x00013F
#define XFSTOOL_CFG_CODE_OFFSET_2 0x000186
#define XFSTOOL_CFG_CODE_OFFSET_3 0x0001cb
unsigned char XFSTool_cfg_arr[] = {
/* 000000/ */ 0x00, 0x00, 0x00, 0x06, 0x00, 0x09, 0x6a, 0x73, 0x5f, 0x4b, 0x65, 0x6c, 0x69, 0x61, 0x73, 0x00,
/* 000010/ */ 0x1d, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66, 0x69,
/* 000020/ */ 0x6c, 0x65, 0x73, 0x5f, 0x63, 0x64, 0x5c, 0x30, 0x30, 0x32, 0x2e, 0x64, 0x61, 0x74, 0x44, 0x33,
/* 000030/ */ 0x22, 0x11, 0x44, 0x33, 0x22, 0x11, 0x00, 0x15, 0x23, 0x63, 0x5c, 0x41, 0x63, 0x72, 0x6f, 0x52,
/* 000040/ */ 0x65, 0x61, 0x64, 0x37, 0x30, 0x39, 0x5c, 0x52, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00,
/* 000050/ */ 0x01, 0x00, 0x2b, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c,
/* 000060/ */ 0x41, 0x63, 0x72, 0x6f, 0x52, 0x65, 0x61, 0x64, 0x37, 0x30, 0x39, 0x5c, 0x52, 0x65, 0x61, 0x64,
/* 000070/ */ 0x65, 0x72, 0x5c, 0x4a, 0x61, 0x76, 0x61, 0x53, 0x63, 0x72, 0x69, 0x70, 0x74, 0x73, 0x00, 0x0a,
/* 000080/ */ 0x62, 0x69, 0x6e, 0x5f, 0x4b, 0x65, 0x6c, 0x69, 0x61, 0x73, 0x00, 0x1d, 0x44, 0x3a, 0x5c, 0x4c,
/* 000090/ */ 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x5f, 0x63,
/* 0000a0/ */ 0x64, 0x5c, 0x30, 0x30, 0x31, 0x2e, 0x64, 0x61, 0x74, 0x44, 0x33, 0x22, 0x11, 0x44, 0x33, 0x22,
/* 0000b0/ */ 0x11, 0x00, 0x02, 0x23, 0x63, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x44, 0x3a, 0x5c, 0x4c, 0x6f,
/* 0000c0/ */ 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x62, 0x69, 0x6e, 0x00, 0x0b, 0x64, 0x61, 0x74,
/* 0000d0/ */ 0x61, 0x5f, 0x4b, 0x65, 0x6c, 0x69, 0x61, 0x73, 0x00, 0x1d, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63,
/* 0000e0/ */ 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x5f, 0x63, 0x64, 0x5c,
/* 0000f0/ */ 0x30, 0x30, 0x30, 0x2e, 0x64, 0x61, 0x74, 0x44, 0x33, 0x22, 0x11, 0x44, 0x33, 0x22, 0x11, 0x00,

/* 000100/ */ 0x02, 0x23, 0x63, 0x00, 0x00, 0x00, 0x01, 0x00, 0x11, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61,
/* 000110/ */ 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x64, 0x61, 0x74, 0x61, 0x00, 0x04, 0x64, 0x61, 0x74, 0x61,
/* 000120/ */ 0x00, 0x1d, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66,
/* 000130/ */ 0x69, 0x6c, 0x65, 0x73, 0x5f, 0x63, 0x64, 0x5c, 0x30, 0x30, 0x30, 0x2e, 0x64, 0x61, 0x74, 
/* 00013F/ */                                                                                           0x88,
/* 000140/ */ 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x02, 0x23, 0x63, 0x00, 0x00, 0x00, 0x01, 0x00,
/* 000150/ */ 0x11, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x64, 0x61,
/* 000160/ */ 0x74, 0x61, 0x00, 0x03, 0x62, 0x69, 0x6e, 0x00, 0x1d, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61,
/* 000170/ */ 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66, 0x69, 0x6c, 0x65, 0x73, 0x5f, 0x63, 0x64, 0x5c, 0x30,
/* 000180/ */ 0x30, 0x31, 0x2e, 0x64, 0x61, 0x74, 
/* 000186/ */                                     0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0x02,
/* 000190/ */ 0x23, 0x63, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c,
/* 0001a0/ */ 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x62, 0x69, 0x6e, 0x00, 0x02, 0x6a, 0x73, 0x00, 0x1d, 0x44, 0x3a,
/* 0001b0/ */ 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x66, 0x69, 0x6c, 0x65, 0x73,
/* 0001c0/ */ 0x5f, 0x63, 0x64, 0x5c, 0x30, 0x30, 0x32, 0x2e, 0x64, 0x61, 0x74, 
/* 0001cb/ */                                                                   0x88, 0x77, 0x66, 0x55, 0x44,
/* 0001d0/ */ 0x33, 0x22, 0x11, 0x00, 0x15, 0x23, 0x63, 0x5c, 0x41, 0x63, 0x72, 0x6f, 0x52, 0x65, 0x61, 0x64,
/* 0001e0/ */ 0x37, 0x30, 0x39, 0x5c, 0x52, 0x65, 0x61, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x01, 0x00, 0x2b,
/* 0001f0/ */ 0x44, 0x3a, 0x5c, 0x4c, 0x6f, 0x63, 0x61, 0x6c, 0x5c, 0x58, 0x46, 0x53, 0x5c, 0x41, 0x63, 0x72,

/* 000200/ */ 0x6f, 0x52, 0x65, 0x61, 0x64, 0x37, 0x30, 0x39, 0x5c, 0x52, 0x65, 0x61, 0x64, 0x65, 0x72, 0x5c,
/* 000210/ */ 0x4a, 0x61, 0x76, 0x61, 0x53, 0x63, 0x72, 0x69, 0x70, 0x74, 0x73,     
};

// ------------------------------------
HRESULT InitVars(void)
{
   ProdName[0] = Nul;
   ProdNameRaw[0] = Nul;
   ProdDir[0] = Nul;
   ProdGroup[0] = Nul;
   ProdFNameRaw[0] = Nul;
   ProdFName[0] = Nul;
   VerName[0] = Nul;
   Ver[0] = Nul;
   ProdVer[0] = Nul;
   ProdVerFlash[0] = Nul;
   ProdVerNet[0] = Nul;
   UpdVerName[0] = Nul;
   UpdNum = -1;
   PrevVerName[0] = Nul;
   PrevVer[0] = Nul;
   PrevUpdNum = -1;
   BuildNum = -1;
   FirstVerName[0] = Nul;
   FirstVer[0] = Nul;
   IconFName[0] = Nul;
   SetupFName[0] = Nul;
   ExeFName[0] = Nul;
   SvrFName[0] = Nul;
   AutoRun = False;
   RequireAdmin = False;
   PartialInstall = False;
   PartialDir = False;
   iProdType = KpKMP;
   ChkUpd = False;
   Publisher[0] = Nul;
   SplashBMP[0] = Nul;
   StartPDF[0] = Nul;
   Password[0] = Nul;
   ProjID[0] = Nul;
   Kalba[0] = Nul;
   CidMode = (KPST_COMPID_BIOS_DATE | KPST_COMPID_PROC_NAME); 
   
return(S_OK);
}


// ------------------------------------
HRESULT DelHeadTailApost(unsigned char *lpszString)
{
HRESULT retc = S_OK;
unsigned char *pnts;
unsigned char *pntd;

   KP_ASSERT(lpszString, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = pntd = lpszString;
      
      while(*pnts && SUCCEEDED(retc))
      {
         if((*pnts == '\'') && ((pnts == lpszString) || (*(pnts+1) == Nul))) pnts++;
         else *pntd++ = *pnts++; 
      }
      
      if(SUCCEEDED(retc)) *pntd = Nul;
   }
   
return(retc);
}


// ------------------------------------
HRESULT ReadIniFile(void)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char in_str[GEN_CSS_STR_PAR_LEN+1];
unsigned char *val_ptr = NULL;
int kwd_ix;
int val_ix;
const unsigned char *pnts = null;

      in_file.open(GEN_ISS_INI_FNAME, ios_base::in);
      if(in_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, GEN_ISS_INI_FNAME, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         while(SUCCEEDED(retc))
         {
            in_file.getline((char *)in_str, GEN_CSS_STR_PAR_LEN);
            if(in_file.eof() && SUCCEEDED(retc)) retc = KP_E_EOF;
            else
               if(in_file.fail())
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GEN_ISS_INI_FNAME, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               val_ptr = strchr(in_str, '=');
               if(val_ptr == NULL)
               {
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str);
                  if(SUCCEEDED(retc)) if((in_str[0] != ';') && (in_str[0] != Nul))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, GEN_ISS_INI_FNAME, True, __FILE__, __LINE__, 0L);
               }
               else
               {
                  *val_ptr++ = Nul;
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(in_str); // reikðmë jau atkirsta - galima tvarkytis atskirai
                  if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(val_ptr);

                  if(SUCCEEDED(retc)) if(in_str[0] != ';')
                  {
                     kwd_ix = NoGenIssIx;
                     if(SUCCEEDED(retc))
                     {
                        retc = GetKwrdIndex(&kwd_ix, in_str, GenIssKwds, -1, True, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) switch(kwd_ix)
                     {
                     case ProdNameIx:     strncpy(ProdName    , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdNameRawIx:  strncpy(ProdNameRaw , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdDirIx:      strncpy(ProdDir     , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdGroupIx:    strncpy(ProdGroup   , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdFNameRawIx: strncpy(ProdFNameRaw, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdFNameIx:    strncpy(ProdFName   , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case VerNameIx:      strncpy(VerName     , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case VerIx:          
                        strncpy(Ver         , val_ptr, GEN_CSS_STR_PAR_LEN);
                        pnts = strchr(Ver, '.');
                        if(pnts != null)
                        {
                           pnts = strchr(pnts + 1, '.');
                           if(pnts != null) BuildNumInsideVer = True;
                        } 
                        break;
                     case ProdVerIx:      strncpy(ProdVer     , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdVerFlashIx: strncpy(ProdVerFlash, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProdVerNetIx:   strncpy(ProdVerNet  , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case UpdVerNameIx:   strncpy(UpdVerName  , val_ptr, GEN_CSS_STR_PAR_LEN); break;

                     case UpdNumIx:
                        if(sscanf((const char *)val_ptr, "%d", &UpdNum) != 1)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, val_ptr, True, __FILE__, __LINE__, 0L);
                        break;
                     case PrevVerNameIx:  strncpy(PrevVerName , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case PrevVerIx:      strncpy(PrevVer     , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case PrevUpdNumIx:
                        if(sscanf((const char *)val_ptr, "%d", &PrevUpdNum) != 1)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, val_ptr, True, __FILE__, __LINE__, 0L);
                        break;
                     case BuildNumIx:
                        if(sscanf((const char *)val_ptr, "%d", &BuildNum) != 1)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, val_ptr, True, __FILE__, __LINE__, 0L);
                        break;
                     case FirstVerNameIx: strncpy(FirstVerName, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case FirstVerIx:     strncpy(FirstVer    , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case IconFNameIx:    strncpy(IconFName   , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case SetupFNameIx:   strncpy(SetupFName  , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ExeFNameIx:     strncpy(ExeFName    , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case SvrFNameIx:     strncpy(SvrFName    , val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case AutoRunIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, YesNoKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) AutoRun = val_ix;
                        break;
                     case RequireAdminIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, YesNoKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) RequireAdmin = val_ix;
                        break;
                     case PartialInstallIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, YesNoKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) PartialInstall = val_ix;
                        break;
                     case PartialDirIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, YesNoKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) PartialDir = val_ix;
                        break;
                     case ProdTypeIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, lpszaProdTypeKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        KP_ASSERT((val_ix >= 0) &&  (val_ix < ProdTypeCnt), KP_E_SYSTEM_ERROR, null, True);   
                        if(SUCCEEDED(retc)) iProdType = (ProdTypes)val_ix;
                        break;
                     case ChkUpdIx:
                        retc = GetKwrdIndex(&val_ix, val_ptr, YesNoKwds, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc)) ChkUpd = val_ix;
                        break;
                     case PublisherIx: strncpy(Publisher, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case SplashBMPIx: strncpy(SplashBMP, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case StartPDFIx:  strncpy(StartPDF, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case PasswordIx:  strncpy(Password, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case ProjIDIx:    strncpy(ProjID, val_ptr, GEN_CSS_STR_PAR_LEN); break;
                     case KalbaIx:     
                        strncpy(Kalba, val_ptr, GEN_CSS_STR_PAR_LEN);
                        retc = GetKwrdIndex(&val_ix, val_ptr, LangCodes, -1, False, True);
                        if(retc == KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, in_str, True, __FILE__, __LINE__, 0L);
                        if(SUCCEEDED(retc))
                        {
                           iMsgLangOff = MsgLangs[val_ix];
//                         if(iMsgLangOff == KpLangRu_1251) if(strcmp(ExeFName, "XFS") == 0) iMsgLangOff = KpLangRu_0;
                        }
                        break;
                     case CidModeIx:     
                        sscanf((const char *)val_ptr, "%x", &CidMode);
                        break;
                     }

                  } // if(in_str[0] != ';')

               } // else // if(pnts == NULL)

            } // if(SUCCEEDED(retc))

         } // while(SUCCEEDED(retc))

         if(retc == KP_E_EOF) retc = S_OK;

         in_file.close();

      } // if(SUCCEEDED(retc)) // if(in_file.fail())

   if(SUCCEEDED(retc)) if(strcmp(ExeFName, "GetProjID") == 0) strcpy(ExeFName, ProjID); 
   if(SUCCEEDED(retc)) if(strcmp(SetupFName, "GetProjID") == 0) strcpy(SetupFName, ProjID); 

return(retc);
}


// ------------------------------------
HRESULT OutputFilesPl(GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream out_file;
static unsigned char out_file_name[KP_MAX_FNAME_LEN+1];
static unsigned char cur_path_name[KP_MAX_FNAME_LEN+1];
static unsigned char exp_path_name[2*KP_MAX_FNAME_LEN+1];
const unsigned char *pnts;
unsigned char *pntd;
static unsigned char str_buf[KP_MAX_FNAME_LEN+1];
int ll;

   if(((iGenType < 0) || (iGenType >= MaxGenIssType)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   out_file_name[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strcpy(out_file_name, FnamePref[iGenType]);
      strcat(out_file_name, FnameSuff[iGenType]);
      strcat(out_file_name, ".pl");
   }

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         out_file << "#!/usr/bin/perl -w" << endl;
         out_file << "#" << endl;
         out_file << endl;
         out_file << "while(<STDIN>)" << endl;
         out_file << "{" << endl;
         out_file << "   @file_comps=split /\\./;" << endl;

         if(SUCCEEDED(retc))
         {
            ll = GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)cur_path_name, NULL); 
            if(!ll)
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            else if(ll >= KP_MAX_FNAME_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }
                
         if(SUCCEEDED(retc))
         {
            pnts = cur_path_name;
            pntd = exp_path_name;
            while(*pnts)
            {
               if(*pnts == '\\') *pntd++ = '\\';
               *pntd++ = *pnts++;
            }
            *pntd = Nul;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssFiles:
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssGrp:
         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssNet:
         case GenIssSvr:
         case GenIssChkVol:
         case GenIssCli:
         case GenIssRez:
         case GenIssDel:
         case GenIssDelWhole:
         case GenIssFinst:
            out_file << "   @file_cmap = split /Cmap\\\\/;" << endl;
            out_file << "   @file_cmapp = split /CMap\\\\/;" << endl;
            out_file << "   @file_acro_vers_dir = split /Reader\\\\7.0.0/;" << endl;
            out_file << "   @file_acro_vers_dir_en_US = split /Reader\\\\7.0.0\\\\\en_US/;" << endl;
            out_file << "   @file_xipa_acro_pdf_dll = split /xipa.bin.local/;" << endl;
            out_file << "   @file_tux_ipa_acro_pdf_dll = split /tux_ipa.bin.local/;" << endl;
#if FALSE
out_file << "print(\">>>\");" << endl;
out_file << "print($file_acro_vers_dir[1]);" << endl;
out_file << "print(\"<<<\");" << endl;
out_file << "print(\">>>\");" << endl;
out_file << "print(substr($file_acro_vers_dir[1], 0, 1));" << endl;
out_file << "print(\"<<<\");" << endl;
out_file << "print(\"\\n\");" << endl;
#endif
            out_file << "   if("
                                 "(defined($file_comps[1]) || defined($file_cmap[1]) || defined($file_cmapp[1])) && "
                                 "((!defined($file_acro_vers_dir[1])) || (defined($file_acro_vers_dir[1]) && (substr($file_acro_vers_dir[1], 0, 1) eq \'\\\\\'))) && "
                                 "((!defined($file_acro_vers_dir_en_US[1])) || (defined($file_acro_vers_dir_en_US[1]) && (substr($file_acro_vers_dir_en_US[1], 0, 1) eq \'\\\\\'))) && "
                                 "((!defined($file_xipa_acro_pdf_dll[1])) || (defined($file_xipa_acro_pdf_dll[1]) && (substr($file_xipa_acro_pdf_dll[1], 0, 1) eq \'\\\\\'))) && "
                                 "((!defined($file_tux_ipa_acro_pdf_dll[1])) || (defined($file_tux_ipa_acro_pdf_dll[1]) && (substr($file_tux_ipa_acro_pdf_dll[1], 0, 1) eq \'\\\\\')))"
                             ")" << endl;
            out_file << "   {" << endl;
            out_file << "      @rest=split /" << exp_path_name << "\\\\" << FnamePref[iGenType] << FnameSuff[iGenType] << "/;" << endl;
            out_file << "      $_=$rest[1];" << endl;
            out_file << endl;
            out_file << "      @src_path=split /\\n/;" << endl;
            out_file << "      $_=$src_path[0];" << endl;
            out_file << endl;
            out_file << "      @common_files = split /\\\\CommonFiles/;" << endl;
            out_file << "      if(defined($common_files[1]) && ($common_files[0] eq \"\")) { $_ = $common_files[1]; }" << endl;
            out_file << endl;
            out_file << "      @windows = split /\\\\Windows/;" << endl;
            out_file << "      if(defined($windows[1]) && ($windows[0] eq \"\")) { $_ = $windows[1]; }" << endl;
            out_file << endl;
            out_file << "      @dest_path=split /\\\\/;" << endl;
//          out_file << "      $dest_path[0]="";" << endl;
            out_file << "      pop @dest_path;" << endl;
            out_file << endl;
            break;

         case GenIssFonts:
            out_file << "   @ttf_comps=split /\\.ttf/;" << endl;
            out_file << "   @ttf_up_comps=split /\\.TTF/;" << endl;
            out_file << "   if(defined($file_comps[1]))" << endl;
            out_file << "   {" << endl;
            out_file << "      @rest=split /" << exp_path_name << "\\\\" << FnamePref[iGenType] << FnameSuff[iGenType] << "\\\\/;" << endl;
            out_file << "      $_=$rest[1];" << endl;
            out_file << endl;
            out_file << "      @src_path=split /\\n/;" << endl;
            out_file << "      $_=$src_path[0];" << endl;
            out_file << endl;
            out_file << "      @dest_path=split /\\\\/;" << endl;
//          out_file << "      $dest_path[0]=\"\";" << endl;
            out_file << "      pop @dest_path;" << endl;
            out_file << endl;
            out_file << "      print(\"Source: \\\"" << FnamePref[iGenType] << FnameSuff[iGenType] << "\\\\\");" << endl;
            out_file << "      print($src_path[0]);" << endl;
            out_file << "      print(\"\\\"; DestDir: \\\"{fonts}\\\"; FontInstall: \\\"\");" << endl;
            out_file << "      print(join(\" \", @dest_path));" << endl;
            out_file << "      print(\"\\\"; Flags: onlyifdoesntexist uninsneveruninstall\");" << endl;
            out_file << "      if((!defined($ttf_comps[1])) && (!defined($ttf_up_comps[1])))" << endl;
            out_file << "      {" << endl;
            out_file << "         print(\" fontisnttruetype\");" << endl;
            out_file << "      }" << endl;
//          out_file << "      print(\" deleteafterinstall;\\n\");" << endl;
            out_file << "      print(\";\\n\");" << endl;
            break;
         }


         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssFiles:
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssGrp:
         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssNet:
         case GenIssSvr:
         case GenIssChkVol:
         case GenIssCli:
         case GenIssRez:
         case GenIssFinst:
            out_file << "      print(\"Source: \\\"" << FnamePref[iGenType] << FnameSuff[iGenType] << "\");" << endl;
            out_file << "      print($src_path[0]);" << endl;

            if((iGenType==GenIssRez) && (strchr(ProdDir, ':')))   // ProdDir = 'C:\\arkim'
            {
               DoubleEscape(str_buf, ProdDir);
               if((str_buf[0] != '\\') || (str_buf[1] != '\''))
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  ll = strlen(str_buf);
                  if(ll < 4)
                     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
                  if((str_buf[ll-2] != '\\') || (str_buf[ll-1] != '\''))
                     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  str_buf[ll-2] = Nul;
                  out_file << "      print(\"\\\"; DestDir: \\\"" << str_buf + 2 << "\");" << endl;
               }
            }
            else
            {
               out_file << "      print(\"\\\"; DestDir: \\\"\");" << endl;
               out_file << endl;
               if((iGenType == GenIssFlashStart) || (iGenType == GenIssFlashStartUpd)) out_file << "      print(\"{src}\");" << endl;
               else
               {
                  out_file << "      if(defined($common_files[1]) && ($common_files[0] eq \"\")) { print(\"{cf}\"); }" << endl;
                  out_file << "      else" << endl;
                  out_file << "      {" << endl;
                  out_file << "         if(defined($windows[1]) && ($windows[0] eq \"\")) { print(\"{win}\"); }" << endl;
                  out_file << "         else { print(\"{code:GetAppPathStr}\"); }" << endl;
                  out_file << "      }" << endl;
               }   
            }
            out_file << endl;
            out_file << "      if($#dest_path>=0)" << endl;
            out_file << "      {" << endl;
//          out_file << "         print(\"\\\\\");" << endl;
            out_file << "         print(join(\"\\\\\", @dest_path));" << endl;
            out_file << "      }" << endl;
            out_file << endl;
            out_file << "      print(\"\\\"; Flags: ignoreversion overwritereadonly";
            if(iGenType == GenIssGrp) out_file << " deleteafterinstall"; 
            out_file << ";\\n\");" << endl;
            break;

         case GenIssDel:
         case GenIssDelWhole:
            out_file << "      print(\"      RestartReplace(GetAppPath + \\\'\");" << endl;
            out_file << "      print($src_path[0]);" << endl;
            out_file << "      print(\"\\\', \\\'\\\');\\n\");" << endl;
            break;
         }


         if(SUCCEEDED(retc))
         {
            out_file << "   }" << endl;
            out_file << "}" << endl;
         }

         if((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutputFilesBat(GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream out_file;
static unsigned char out_file_name[KP_MAX_FNAME_LEN+1];

   if(((iGenType < 0) || (iGenType >= MaxGenIssType)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   out_file_name[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strcpy(out_file_name, FnamePref[iGenType]);
      strcat(out_file_name, FnameSuff[iGenType]);
      strcat(out_file_name, ".bat");
   }

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
//       out_file << "Q:" << endl;
//       out_file << "cd \\Ebook_DB\\" << Publisher << "\\" << ProjID << endl;
//       out_file << endl;
         out_file << "dir " << FnamePref[iGenType] << FnameSuff[iGenType] << " /s /b /ON > " << FnamePref[iGenType] << FnameSuff[iGenType] << ".dir" << endl;
         out_file << "perl " << FnamePref[iGenType] << FnameSuff[iGenType] << ".pl < " << FnamePref[iGenType] << FnameSuff[iGenType] << ".dir > " << FnamePref[iGenType] << FnameSuff[iGenType] << ".txt" << endl;

         if((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutputGenBat(GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream out_file;
static unsigned char out_file_name[KP_MAX_FNAME_LEN + 1];
static unsigned char check_fname[KP_MAX_FNAME_LEN+1];
static unsigned char js_dir[KP_MAX_FNAME_LEN + 1];
static unsigned char js_dir_suff[KP_MAX_FNAME_LEN + 1];
static unsigned char files_sub_dir[KP_MAX_FNAME_LEN + 1];
// bool dot_fl = False;
bool js_dir_found = False;
bool upd_js_dir_found = False;
bool upd_whole_js_dir_found = False;
bool flash_js_dir_found = False;
bool flash_upd_js_dir_found = False;
bool flash_upd_whole_js_dir_found = False;
HANDLE test_dir = INVALID_HANDLE_VALUE;
const unsigned char *pnts; 
unsigned char *pntd; 
unsigned char msg_file_name[KP_MAX_FNAME_LEN + 1];
unsigned char msg_in_file_name[KP_MAX_FNAME_LEN + 1];
unsigned char msg_out_file_name[KP_MAX_FNAME_LEN + 1];

   if(((iGenType < 0) || (iGenType >= MaxGenIssType)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   out_file_name[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strcpy(out_file_name, "gen");
      strcat(out_file_name, FnameSuff[iGenType]);
      strcat(out_file_name, ".bat");
   }

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
//       dot_fl = ((strchr(ProdNameRaw, '.')!=NULL) || (strchr(ProdName, '.')!=NULL));

//       out_file << ":: @echo off" << endl;
         out_file << "@echo off" << endl;
         out_file << endl;
         out_file << endl;

//       out_file << "echo ------------------------" << endl;
//       out_file << "Q:" << endl;
//       out_file << "cd \\Ebook_DB\\" << Publisher << "\\" << ProjID << endl;
//       out_file << endl;
//       out_file << endl;

//       out_file << "echo ------------------------" << endl;

         KP_ASSERT(((iProdType >= 0) && (iProdType < ProdTypeCnt)), KP_E_SYSTEM_ERROR, null, True);
         
         if((iMsgLangOff == KpLangRu_1251) || (iMsgLangOff == KpLangRu_0)) out_file << ":: "; // rusiðkiem neveikia Inno unikodizatorius
         out_file << "copy \"%ProgramFiles%";
         
         strcpy(msg_file_name, "\\Inno Setup 5\\Languages\\");         
#if FALSE
#  if(MsgLang == KpLangEn_p)
         strcat(msg_file_name, "English");
#  elif(MsgLang == KpLangPl_1250_p)
         strcat(msg_file_name, "Polish");
#  elif(MsgLang == KpLangPl_1257_p)
         strcat(msg_file_name, "Polish_1257");
#  elif((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
         strcat(msg_file_name, "Russian");
#  else         
         strcat(msg_file_name, "Lithuanian");
#  endif
#else
         strcat(msg_file_name, InnoSetupMsgFilePref[iMsgLangOff]);            
#endif

         if(iMsgLangOff == KpLangLt)
         { 
            strcat(msg_file_name, "_");
// #if(MsgLang == KpLangLt_p) 
            switch(iGenType)
            {
            case GenIssCd:
            case GenIssSh:
            case GenIssCert:
            case GenIssNet:
            case GenIssGrp:
            case GenIssFinst:
               strcat(msg_file_name, lpszaIslSufixes[iProdType]);
//             if(!dot_fl) strcat(msg_file_name, "_dot");
               break;

            case GenIssFlash:
//             strcat(msg_file_name, lpszaIslSufixes[KpPROG]);
//             strcat(msg_file_name, "_flash");
//             break;
            case GenIssUpd:
            case GenIssUpdWhole:
               strcat(msg_file_name, lpszaIslSufixes[KpUPD]);
               strcat(msg_file_name, "_");
               strcat(msg_file_name, lpszaIslSufixes[iProdType]);
//             if(!dot_fl) strcat(msg_file_name, "_dot");
               break;

            case GenIssChkVol:
            case GenIssSvr:
               strcat(msg_file_name, lpszaIslSufixes[KpPROG]);
//             if(!dot_fl) strcat(msg_file_name, "_dot");
               break;

            case GenIssFlashUpd:
            case GenIssFlashUpdWhole:
               strcat(msg_file_name, lpszaIslSufixes[KpUPD]);
               strcat(msg_file_name, "_");
               strcat(msg_file_name, lpszaIslSufixes[iProdType]);
//             strcat(msg_file_name, "_flash");
               break;

            case GenIssFlashStart:
            case GenIssFlashStartUpd: 
               strcat(msg_file_name, lpszaIslSufixes[iProdType]);
               strcat(msg_file_name, "_start");
               break;

            case GenIssCli:
               strcat(msg_file_name, "cli");
               break;
         
            default: KP_ERROR(KP_E_SYSTEM_ERROR, null); break;
            }
// #endif
         }
         strcat(msg_file_name, ".isl");
         out_file << msg_file_name;  
         
         retc = GetLocalPath(msg_in_file_name, KP_Program_Files, False);
      }
      if(SUCCEEDED(retc))
      {
         strcpy(msg_out_file_name, msg_in_file_name);
         
         strcat(msg_in_file_name, msg_file_name);
         
         strcpy(msg_file_name, "\\Inno Setup 5\\Default.isl");
         
         out_file << "\" \"%ProgramFiles%" << msg_file_name << "\" > nul" << endl;

         strcat(msg_out_file_name, msg_file_name);
          
         out_file << endl;
         out_file << endl;
      }
      
// ------------------------------------ skaitom praneðimø failà
      if(SUCCEEDED(retc))
      {
unsigned char *lang_file_ptr = null;
long lang_file_len;

         if(SUCCEEDED(retc)) retc = ReadFileContents(msg_out_file_name, &lang_file_ptr, &lang_file_len, True, False); // perkoduoja nukopijuotà default.isl failà – tam bus iðkvietimas vietoj geniss.bat
         KP_ASSERT(lang_file_ptr != null, KP_E_SYSTEM_ERROR, null, True);
      
// ------------------------------------ keièiam makrokomandas (nesuveikia Inno unicodinimas)
unsigned char *in_buf = null;
unsigned char *out_buf = null;
long in_out_buf_len = lang_file_len * 2; 
      
         KP_NEWA(in_buf, unsigned char, in_out_buf_len + 1);
      
         if(SUCCEEDED(retc)) strcpy(in_buf, lang_file_ptr); 
      
         KP_DELETEA(lang_file_ptr);

unsigned char subst_str[GEN_CSS_STR_PAR_LEN + 1];
// ------------------------------------ keièiam [name] á ProdNameRaw
         strcpy(subst_str, ProdNameRaw); 
         DelHeadTailApost(subst_str);
         if(SUCCEEDED(retc)) retc = ReplaceSubstr(in_buf, (const unsigned char *)"[name]", subst_str, in_out_buf_len);  
         
// ------------------------------------ keièiam [name/ver] á VerName
         strcpy(subst_str, ProdNameRaw); 
         DelHeadTailApost(subst_str);
         strcat(subst_str, " "); 
         strcat(subst_str, Ver); 
         if(SUCCEEDED(retc)) retc = ReplaceSubstr(in_buf, (const unsigned char *)"[name/ver]", subst_str, in_out_buf_len);  
         
// ------------------------------------ keièiam „%1“ á „ProdNameRaw“
         strcpy(subst_str, "„");
         strcpy(subst_str + 1, ProdNameRaw); 
         DelHeadTailApost(subst_str + 1);
         strcat(subst_str, "“");
         if(SUCCEEDED(retc)) retc = ReplaceSubstr(in_buf, (const unsigned char *)"„%1“", subst_str, in_out_buf_len);  
         
// ------------------------------------ keièiam „%1” á „ProdNameRaw”
         strcpy(subst_str, "„");
         strcpy(subst_str + 1, ProdNameRaw); 
         DelHeadTailApost(subst_str + 1);
         strcat(subst_str, "”");
         if(SUCCEEDED(retc)) retc = ReplaceSubstr(in_buf, (const unsigned char *)"„%1”", subst_str, in_out_buf_len);  
         
// ------------------------------------ keièiam «%1» á «ProdNameRaw»
         strcpy(subst_str, "«");
         strcpy(subst_str + 1, ProdNameRaw); 
         DelHeadTailApost(subst_str + 1);
         strcat(subst_str, "»");
         if(SUCCEEDED(retc)) retc = ReplaceSubstr(in_buf, (const unsigned char *)"«%1»", subst_str, in_out_buf_len);  
         
// ------------------------------------ raðom pakeistà praneðimø failà
         if(SUCCEEDED(retc))
         {
fstream lang_out_file;

            lang_out_file.open((const char *)msg_out_file_name, ios_base::out);
            KP_ASSERT(!lang_out_file.fail(), KP_E_DIR_ERROR, msg_out_file_name, True);
      
            if(SUCCEEDED(retc))
            {
               lang_out_file << in_buf;

               KP_ASSERT((!lang_out_file.fail()) && (!lang_out_file.eof()), KP_E_FERROR, msg_out_file_name, True);

               lang_out_file.close();
//             KP_ASSERT(lang_out_file.close() != NULL, KP_E_FILE_ERROR, msg_tmp_file_name, True);
            }
         }
         
// -------------
         retc = S_OK; // ignoruojam praneðimo failo skaitymo klaidas
      }
      
// ------------
      if(SUCCEEDED(retc))
      {
#if FALSE
         switch (iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssNet:
         case GenIssFinst:
//          out_file << "echo ------------------------" << endl;
            out_file << ":: copy " << ExeFName;
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) out_file << FnameSuff[GenIssCd];
            else out_file << FnameSuff[iGenType];
            out_file << ".ini files\\" << ExeFName << ".ini" << endl;
            out_file << ":: del Output\\" << ExeFName << ".ini" << endl;
            out_file << endl;
            out_file << endl;
            break;
         }
#endif
// -------------------
         strcpy(js_dir, "files\\AcroRead602\\Reader\\Javascripts");
         strcpy(js_dir_suff, "\\AcroRead602\\Reader\\Javascripts");
         strcpy(files_sub_dir, "\\");
         pnts = ProdDir;
         if(*pnts == '\'') pnts++;
         strcat(files_sub_dir, pnts);
         pntd = files_sub_dir + strlen(files_sub_dir) - 1;
         if(*pntd == '\'') *pntd = Nul;
         
         js_dir_found = False;
         test_dir = CreateFile("files\\AcroRead602\\Reader\\Javascripts", GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            js_dir_found = True;
            CloseHandle(test_dir);
         }

         upd_js_dir_found = False;
         test_dir = CreateFile("files_upd\\AcroRead602\\Reader\\Javascripts", GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            upd_js_dir_found = True;
            CloseHandle(test_dir);
         }

         upd_whole_js_dir_found = False;
         test_dir = CreateFile("files_upd_whole\\AcroRead602\\Reader\\Javascripts", GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            upd_whole_js_dir_found = True;
            CloseHandle(test_dir);
         }

         flash_js_dir_found = False;
         strcpy(check_fname, "files"); 
         strcat(check_fname, files_sub_dir);
         strcat(check_fname, "\\AR6\\Reader\\Javascripts");
         test_dir = CreateFile((const char *)check_fname, GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            flash_js_dir_found = True;
            strcpy(js_dir, check_fname);
            strcpy(js_dir_suff, files_sub_dir);
            strcat(js_dir_suff, "\\AR6\\Reader\\Javascripts");
            CloseHandle(test_dir);
         }

         flash_upd_js_dir_found = False;
         strcpy(check_fname, "files_flash_upd");
         strcat(check_fname, files_sub_dir);
         strcat(check_fname, "\\AR6\\Reader\\Javascripts");
         test_dir = CreateFile((const char *)check_fname, GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            flash_upd_js_dir_found = True;
            strcpy(js_dir, check_fname);
            strcpy(js_dir_suff, "\\AR6\\Reader\\Javascripts");
            CloseHandle(test_dir);
         }

         flash_upd_whole_js_dir_found = False;
         strcpy(check_fname, "files_flash_upd_whole");
         strcat(check_fname, files_sub_dir);
         strcat(check_fname, "\\AR6\\Reader\\Javascripts");
         test_dir = CreateFile((const char *)check_fname, GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
         if(test_dir != INVALID_HANDLE_VALUE)
         {
            flash_upd_whole_js_dir_found = True;
            strcpy(js_dir, check_fname);
            strcpy(js_dir_suff, "\\AR6\\Reader\\Javascripts");
            CloseHandle(test_dir);
         }

         switch (iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssSvr:
         case GenIssNet:
//          out_file << "echo ------------------------" << endl;
            out_file << ":: \"%ProgramFiles%\\Microsoft Application Compatibility Toolkit 5\\Compatibility Administrator\\Compatadmin.exe\"" << endl;
            out_file << endl;
            out_file << endl;
            break;
         }

         if(
            (
               (
                  (iGenType==GenIssCd) || (iGenType==GenIssSh) || (iGenType==GenIssCert) ||
                  ((iGenType==GenIssUpd) && upd_js_dir_found) ||
                  ((iGenType==GenIssUpdWhole) && upd_whole_js_dir_found) ||
                  (iGenType==GenIssNet)
               ) &&
               js_dir_found
            ) ||
            (((iGenType==GenIssFlash) || (iGenType==GenIssFinst)) && flash_js_dir_found) || 
            ((iGenType==GenIssFlashUpd) && flash_upd_js_dir_found) || 
            ((iGenType==GenIssFlashUpdWhole) && flash_upd_whole_js_dir_found)
           )
         {
//          out_file << "echo ------------------------" << endl;
            out_file << ":: goto skip_butord" << endl;
            out_file << endl;
            out_file << "dir /X " << js_dir << " > files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord0.mcl" << endl;

            out_file << "dir /X files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[GenIssCd];
            else out_file << FnameSuff[iGenType];
            out_file << js_dir_suff << " >> files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord0.mcl" << endl;

            out_file << endl;
            out_file << "echo sutvarkyk faila files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord0.mcl, zr. pvz. butord.mcl" << endl;
            out_file << "pause" << endl;
            out_file << endl;
            out_file << "sort < files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord0.mcl > files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord.mcl" << endl;
            out_file << "del files";
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) out_file << FnameSuff[iGenType];
            if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole) || (iGenType==GenIssFinst)) out_file << files_sub_dir;
            out_file << "\\butord0.mcl" << endl;
            out_file << endl;
            out_file << ":skip_butord" << endl;
            out_file << endl;
            out_file << endl;
         }
//       out_file << "echo ------------------------" << endl;
         /* if(iGenType == GenIssSh) */ out_file << ":: ";
         out_file << "call geniss.bat" << endl;
         out_file << "geniss.exe 1>> geniss.lst  2>&1" << endl; // èia kad parepleisintø lenkiðkus produktø kodus Inno Setup praneðimø faile
         out_file << endl;
         out_file << endl;
//       out_file << "echo ------------------------" << endl;
         if((iGenType==GenIssFlash) || (iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole))
         {
            out_file << ":: UVCView.x86.exe" << endl;
            out_file << ":: kpstedb.exe Output_flash\\" << ExeFName << ".ini" << endl;
            out_file << endl;
         }

         out_file << "if \"%1\" == \"noprompt\" goto noprompt_label" << endl;
         out_file << "gen" << FnameSuff[iGenType] << ".iss" << endl;

         out_file << "goto pabaiga" << endl;
         out_file << ":noprompt_label" << endl;
         out_file << "\"%ProgramFiles%\\Inno Setup 5\\Compil32.exe\" /cc gen" << FnameSuff[iGenType] << ".iss" << endl;
         out_file << ":pabaiga" << endl;

         if((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutputGenLocalBat(const unsigned char *lpszBatName) // lpszBatName be uodegos "_local.bat"
{
HRESULT retc = S_OK;
fstream out_file;
unsigned char out_file_name[KP_MAX_FNAME_LEN + 100];
bool xfs_fl = (strcmp(lpszBatName, (const unsigned char *)"make_XFS_exe") == 0); 
bool cert_fl = (strcmp(lpszBatName, (const unsigned char *)"make_creg") == 0); 

   KP_ASSERT(lpszBatName, E_INVALIDARG, null, True);
   
   if(SUCCEEDED(retc))
   {
      strncpy(out_file_name, lpszBatName, KP_MAX_FNAME_LEN);
      out_file_name[KP_MAX_FNAME_LEN] = Nul;
      strcat(out_file_name, "_local.bat");
   }

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         out_file << ":: @echo off" << endl;
         out_file << ":: ---------------------------------" << endl;
         out_file << ":: iskvietimas:" << endl;
         out_file << "::    call " << out_file_name << " [build\'o komentaras]" << endl;
         out_file << endl;
         
         out_file << "Q:" << endl;
         out_file << "cd \\Ebook_DB\\" << Publisher << "\\" << ProjID << endl;
         out_file << endl;

         out_file << "echo incbuild.exe %1" << endl;
         if (!xfs_fl) out_file << ":: "; out_file << "incbuild.exe %1" << endl;
         out_file << endl;

         out_file << "if not exist files\\sts.exe goto :nodiag" << endl;
         out_file << "copy startsel" << SetupFileLangSuffixes[iMsgLangOff] << ".exe files\\sts.exe" << endl;
         out_file << ":nodiag" << endl;
         out_file << endl;

//       out_file << "del geniss_bat.log" << endl;
//       out_file << "call geniss.bat 1>> geniss_bat.log  2>&1" << endl;

         out_file << "del " << lpszBatName << ".log" << endl;
         out_file << "call O:\\eknygu_gamyba\\" << lpszBatName << SetupFileLangSuffixes[iMsgLangOff] << ".bat " << Publisher << " " << ProjID << " ";
         if (xfs_fl)
         {
             out_file << SplashBMP << " 1>> " << lpszBatName << ".log  2>&1" << endl;

             out_file << "del " << lpszBatName << "_sh.log" << endl;
             out_file << "call O:\\eknygu_gamyba\\" << lpszBatName << "_sh" << SetupFileLangSuffixes[iMsgLangOff] << ".bat " << Publisher << " " << ProjID << " " << SplashBMP << " 1>> " << lpszBatName << "_sh.log  2>&1" << endl;
         }
         else
         {
            if (cert_fl) 
                out_file << ExeFName << ".pfx " << Password;
            out_file << " 1>> " << lpszBatName << ".log  2>&1" << endl;
         }
         
         if ((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutputGenIssBat(void)
{
HRESULT retc = S_OK;
fstream out_file;
const unsigned char *out_file_name = (const unsigned char *)"geniss.bat";

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         out_file << "@echo off" << endl;
         out_file << endl;
//       out_file << "echo ------------------------ > nul" << endl;
//       out_file << "Q:" << endl;
//       out_file << "cd \\Ebook_DB\\" << Publisher << "\\" << ProjID << endl;
//       out_file << endl;
//       out_file << "echo ------------------------ > nul" << endl;
         out_file << "    call files.bat" << endl;
         out_file << endl;
         out_file << "    call files_cd.bat" << endl;
         out_file << "    call files_sh.bat" << endl;
         out_file << "    call files_upd.bat" << endl;
         out_file << "    call files_upd_whole.bat" << endl;
         out_file << "    call files_del.bat" << endl;
         out_file << "    call files_del_whole.bat" << endl;
         out_file << endl;
         out_file << "    call files_grp.bat" << endl;
         out_file << endl;
         out_file << "    call files_flash.bat" << endl;
         out_file << "    call files_flash_upd.bat" << endl;
         out_file << "    call files_flash_upd_whole.bat" << endl;
         out_file << "    call files_flash_start.bat" << endl;
         out_file << "    :: call files_flash_start_upd.bat" << endl;
         out_file << endl;
         out_file << "    call files_net.bat" << endl;
         out_file << "    call files_svr.bat" << endl;
         out_file << "    call files_cli.bat" << endl;
         out_file << "    call files_rez.bat" << endl;
         out_file << endl;
         out_file << "    call files_finst.bat" << endl;
         out_file << endl;
         out_file << "    call files_chkvol.bat" << endl;
         out_file << endl;
         out_file << "    call fonts.bat" << endl;
         out_file << endl;
         out_file << endl;
//       out_file << "echo ------------------------ > nul" << endl;
//       out_file << "geniss.exe > nul" << endl;
//       out_file << "geniss.exe > geniss.lst" << endl;
         out_file << "geniss.exe 1>> geniss.lst  2>&1" << endl;

         if((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutCheckMacroCabri(fstream *pOutFile, GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char check_fname[KP_MAX_FNAME_LEN+1];

   if(((iGenType < 0) || (iGenType >= MaxGenIssType) || (pOutFile == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      strcpy(check_fname, FnamePref[iGenType]);
      if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
      strcat(check_fname, "\\Install Flash Player 7 AX.exe");
      in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
      if(!in_file.fail())
      {
         *pOutFile << "      CheckMacromediaPlayer;" << endl;
         in_file.close();
      }
      
      strcpy(check_fname, FnamePref[iGenType]);
      if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
      strcat(check_fname, "\\install_flash_player_active_x.msi");
      in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
      if(!in_file.fail())
      {
         *pOutFile << "      CheckMacromediaPlayer;" << endl;
         in_file.close();
      }
      
      strcpy(check_fname, FnamePref[iGenType]);
      if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
      strcat(check_fname, "\\Cabri3D_Plugin_200_Win.exe");
      in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
      if(!in_file.fail())
      {
         *pOutFile << "      CheckCabri;" << endl;
         in_file.close();
      }
   }

return(retc);
}


// ------------------------------------
HRESULT OutSbInst(fstream *pOutFile, GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char check_fname[KP_MAX_FNAME_LEN+1];

   if((iGenType != GenIssGrp) && SUCCEEDED(retc))
   {
      if((pOutFile == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         check_fname[0] = Nul; 
         switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
            strcpy(check_fname, FnamePref[iGenType]);
            strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\");
            strcat(check_fname, ExeFName);
            break;
         case GenIssCli:
         case GenIssUpd:
         case GenIssUpdWhole:
            strcpy(check_fname, FnamePref[GenIssCd]);
            strcat(check_fname, FnameSuff[GenIssCd]);
            strcat(check_fname, "\\");
            strcat(check_fname, ExeFName);
            break;
         case GenIssSvr:
            strcpy(check_fname, FnamePref[iGenType]);
            strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\");
            strcat(check_fname, SvrFName);
            break;
         default:
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            break;
         }
         strcat(check_fname, ".sdb"); 
   
         in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
         if(!in_file.fail())
         {
            *pOutFile << endl;
//          *pOutFile << "//    MsgBox(Format('%d', [GetWindowsVersion shr 24]), mbInformation, MB_OK);
            *pOutFile << "      if((GetWindowsVersion shr 24) >= 6) then" << endl;
            *pOutFile << "         if(not Exec(\'sdbinst.exe\', \'-q \"\' + GetAppPath + \'\\\' + ";
            *pOutFile << ((iGenType == GenIssSvr)?"GetSvrFName":"GetExeFName");
            *pOutFile << " + \'.sdb\"\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
            *pOutFile << "            MsgBox(\'";
               *pOutFile << GENISS_MSG_UNSUCC_START;
               *pOutFile << " sdbinst.exe\', mbError, MB_OK);" << endl;
   
            in_file.close();
         }
      
      } // if(SUCCEEDED(retc))
   
   } // if((iGenType != GenIssGrp) && SUCCEEDED(retc))
   
return(retc);
}


// ------------------------------------
HRESULT OutTestUpd(fstream *pOutFile)
{
HRESULT retc = S_OK;

   *pOutFile << endl;
   *pOutFile << "      ll := 1;" << endl;
   *pOutFile << "      if(not TestUpdPage.Values[0]) then ll := 0;" << endl;
   *pOutFile << "      KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'TestUpdates\', ll, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

return(retc);
}


// ------------------------------------
HRESULT AppendIssFile(fstream *pOutFile, const unsigned char *lpszAppFName)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];

   if(((lpszAppFName == NULL) || (pOutFile == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      in_file.open((const char *)lpszAppFName, ios_base::in);
      if(in_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszAppFName, False, __FILE__, __LINE__, 0L);
      else
      {
         while(SUCCEEDED(retc))
         {
            in_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
            if(in_file.eof()) break;
            if(in_file.fail())
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszAppFName, True, __FILE__, __LINE__, 0L);
               break;
            }

            *pOutFile << in_str << endl;
            if(pOutFile->fail() || pOutFile->eof())
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
               break;
            }
         }

         in_file.close();

      } // else // if(in_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------------------------
HRESULT OutputGenIss(GenIssTypes iGenType)
{
HRESULT retc = S_OK;
fstream out_file;
fstream in_file;
static unsigned char out_file_name[KP_MAX_FNAME_LEN+1];
const unsigned char *setup_file_name;
int ver_val = 0;
static unsigned char check_fname[KP_MAX_FNAME_LEN+1];
const unsigned char *icon_file_name = NULL;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char fname[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
static unsigned char fname_lat[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
static unsigned char ftype[KP_MAX_FTYPE_LEN+1];
static unsigned char prname[KP_MAX_FNAME_LEN+1];
static unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];
static unsigned char prod_fname_raw[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
static unsigned char prod_fname[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
static unsigned char prod_dir[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
static unsigned char prod_group[GEN_CSS_STR_PAR_LEN+KP_MAX_FNAME_LEN+1];
bool in_file_open = False;
bool fonts_ready = False;
bool files_flash_start_ready = False;
bool dlls_ready = False;
const unsigned char *pnts = null;
unsigned char *pntd = null;
static unsigned char str_buf[GEN_CSS_STR_PAR_LEN + 1];
static unsigned char setup_fname[GEN_CSS_STR_PAR_LEN + 1];
unsigned char build_str[GEN_CSS_STR_PAR_LEN + 1];
int ll;
bool ask_use_acc_let_flg = False;
bool startsel_exe_exists = False;

   if(((iGenType < 0) || (iGenType >= MaxGenIssType)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   startsel_exe_exists = False;
   strcpy(check_fname, FnamePref[iGenType]);
   if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
   strcat(check_fname, "\\sts.exe");
   in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
   if(!in_file.fail())
   {
      startsel_exe_exists = True;
      in_file.close();
   }

   ask_use_acc_let_flg = False;
   if(
      (
         (
            ((iGenType == GenIssCd) /* || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) */ || (iGenType == GenIssNet) || (iGenType == GenIssCli)) &&
            ((!TvIsLatStr(ProdFNameRaw)) || (!TvIsLatStr(ProdFName)) || (!TvIsLatStr(ProdDir)) || (!TvIsLatStr(ProdGroup)))
         ) ||
         (iGenType == GenIssSvr) ||
         (startsel_exe_exists && (!TvIsLatStr(GENISS_LINK_DIAG_MSG_NAT)) && (iGenType != GenIssSh))
      ) &&
//    (strcmp(ExeFName, "XFS") != 0) &&
      (iMsgLangOff == KpLangLt) 
     )
      ask_use_acc_let_flg = True;
      
   strcpy(prod_fname_raw, ProdFNameRaw);
   strcpy(prod_fname, ProdFName);
   strcpy(prod_dir, ProdDir);
   strcpy(prod_group, ProdGroup);
   if(!ask_use_acc_let_flg)
   {
      TvStrLat(prod_fname_raw, LangToCtbl[iMsgLangOff]);
      TvStrLat(prod_fname, LangToCtbl[iMsgLangOff]);
      TvStrLat(prod_dir, LangToCtbl[iMsgLangOff]);
      TvStrLat(prod_group, LangToCtbl[iMsgLangOff]);
   }

   out_file_name[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strcpy(out_file_name, "gen");
      strcat(out_file_name, FnameSuff[iGenType]);
      strcat(out_file_name, ".iss");
   }

   if(SUCCEEDED(retc))
   {
      build_str[0] = Nul;
      if(!BuildNumInsideVer)
      {
         ll = strlen(Ver);
         if(ll > 0) ll--;
         if(Ver[ll] != '“') sprintf((char *)build_str, ".%d", BuildNum);
      }
   }

// ------------------------------ iðsaugojam senà
   if(SUCCEEDED(retc))
   {
      strcpy(fname, out_file_name);
      strcat(fname, ".sav");
      CopyFile((const char *)out_file_name, (const char *)fname, True);
   }

// ------------------------------
   setup_fname[0] = Nul;
   if(SUCCEEDED(retc))
   {
      strcpy(setup_fname, SetupFName);
      if(iGenType == GenIssGrp)
      {
#if FALSE
#  if(MsgLang == KpLangEn_p)
         strcat(setup_fname, "_en");
#  elif((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p))
         strcat(setup_fname, "_pl");
#  elif((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
         strcat(setup_fname, "_ru");
#  endif
#else
         strcat(setup_fname, SetupFileLangSuffixes[iMsgLangOff]);            
#endif 
      }
      else
      { 
#if FALSE
#  if(MsgLang == KpLangEn_p)
         strcat(setup_fname, "_en");
#  elif(MsgLang == KpLangPl_1250_p)
         strcat(setup_fname, "_pl_1250");
#  elif(MsgLang == KpLangPl_1257_p)
         strcat(setup_fname, "_pl_1257");
#  elif(MsgLang == KpLangRu_1251_p)
         strcat(setup_fname, "_ru_1251");
#  elif(MsgLang == KpLangRu_0_p)
         strcat(setup_fname, "_ru_0");
#  endif 
// #else
         strcat(setup_fname, SetupFileLangSuffixesExact[iMsgLangOff]);            
#endif 
      }
   }

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_file_name, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {

// echo ;------------------------ > gen_cd.iss
//     type gen_iss_top_cd.txt >> gen_cd.iss
// :: type gen_iss_top_flash.txt >> gen_cd.iss
// :: type gen_iss_top_flash_start.txt >> gen_cd.iss


         if(SUCCEEDED(retc))
         {
            out_file << ";------------------------" << endl;
            out_file << "; " << out_file_name << endl;
            out_file << "; Installation script" << endl;
            out_file << "; " << setup_fname << endl;
            out_file << "; " << ProdNameRaw << endl;
            out_file << ";" << endl;
            out_file << endl;
            out_file << endl;
         }
         if(SUCCEEDED(retc))
         {
            out_file << "[Setup]" << endl;
            out_file << "AppPublisher = " << Publisher << endl;
            out_file << "AppPublisherURL = http://www.tev.lt/" << endl;
            out_file << "AppVersion = {code:GetVerStr}" << endl;
            out_file << "VersionInfoCompany = TEV" << endl;
            out_file << endl;
         }

         if(SUCCEEDED(retc))
         {
            out_file << "VersionInfoProductName = {code:GetProdNameStr}" << endl;
            out_file << "VersionInfoProductTextVersion = {code:GetVerNameStr}" << endl;
            out_file << endl;
         }

         if(SUCCEEDED(retc))
         {
            out_file << "AppName = {code:GetProdNameStr}" << endl;
            out_file << "AppVerName = {code:GetVerNameStr}" << endl;
            out_file << endl;
         }
         if(SUCCEEDED(retc))
         {
            out_file << ";ProdVer = {code:GetProdVerStr}" << endl;
            out_file << endl;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssNet:
         case GenIssSvr:
         case GenIssChkVol:
         case GenIssCli:
//          if(strchr(prod_dir, ':'))   // ProdDir = 'C:\\arkim'
               out_file << "DefaultDirName = {code:GetProdDirStr}" << endl;
//          else                       // ProdDir = GetProdFNameRaw
//             out_file << "DefaultDirName = {pf}\\" << Publisher << "\\{code:GetProdDirStr}" << endl;
            break;
         case GenIssFlash:
         case GenIssFinst:
//          out_file << "DefaultDirName = {pf}\\" << Publisher << "\\{code:GetProdDirStr}" << endl;
//          out_file << "DefaultDirName = {pf}\\{code:GetProdDirStr}" << endl;
//          out_file << "DefaultDirName = Output_flash_vol\\{code:GetProdDirStr}" << endl;
//          out_file << "DefaultDirName = Output_flash_iso\\{code:GetProdDirStr}" << endl;
//          out_file << ";DefaultDirName = \\{code:GetProdDirStr}" << endl;
            out_file << "DefaultDirName = {code:GetAppPathStr}\\{code:GetProdDirStr}" << endl;
            out_file << ";DefaultDirName = Output_flash_iso\\{code:GetProdDirStr}" << endl;
            break;
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
//          out_file << "DefaultDirName = \\{code:GetProdDirStr}" << endl;
//          out_file << "DefaultDirName = {code:GetEmptyStr}" << endl;
//          out_file << "DefaultDirName = DAT0" << endl;
            out_file << "DefaultDirName = {code:GetAppPathStr}\\{code:GetProdDirStr}" << endl;
            break;
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssGrp:
//          out_file << "DefaultDirName = {tmp}\\{code:GetProdDirStr}" << endl;
            out_file << "DefaultDirName = {code:GetAppPathStr}" << endl;
            break;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
         case GenIssSvr:
            if((!PartialInstall) && (!PartialDir)) break;
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssCli:
         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFinst:
            out_file << endl;
            if(((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType ==  GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssFinst)) && (!PartialDir)) out_file << ";";
            out_file << "EnableDirDoesntExistWarning = yes" << endl;
            out_file << "DirExistsWarning = no" << endl;
            break;
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssGrp:
            out_file << endl;
            out_file << "DirExistsWarning = no" << endl;
            break;
         }

         if(SUCCEEDED(retc)) out_file << endl;

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssNet:
         case GenIssSvr:
            out_file << "UninstallDisplayIcon = {code:GetAppPathStr}\\{code:GetIconFNameStr}" << endl;
            break;
         case GenIssCli:
         case GenIssGrp:
//          out_file << "UninstallDisplayIcon = {code:GetAppPathStr}\\{code:GetIconFNameStr}" << endl;
            out_file << "Uninstallable = no" << endl; // kad galima bûtø diegti á readonly network drive
            break;
         case GenIssFlash:
         case GenIssFinst:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
//          out_file << ";";
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
            out_file << "UsePreviousAppDir = no" << endl;
            out_file << "Uninstallable = no" << endl;
            break;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
         case GenIssSvr:
         case GenIssChkVol:
         case GenIssCli:
            out_file << endl;
            if(strchr(prod_dir, ':'))   // ProdDir = 'C:\\arkim'
               out_file << "DefaultGroupName = {code:GetProdGroupStr}" << endl;
            else                       // ProdDir = GetProdFNameRaw
            {
//             out_file << "DefaultGroupName = {code:GetProdDirStr}" << endl;
//             out_file << "DefaultGroupName = " << Publisher << "\\{code:GetProdDirStr}" << endl;
//             out_file << "DefaultGroupName = " << Publisher << "\\{code:GetProdGroupStr}" << endl;
               out_file << "DefaultGroupName = {code:GetProdGroupStr}" << endl;
            }
            break;

         case GenIssUpd:
         case GenIssUpdWhole:
            out_file << endl;
            out_file << "DefaultGroupName = {code:GetProdGroupStr}" << endl; // iðtraukiamas ið Inno Setup registro
            break;
         }
         if(SUCCEEDED(retc)) if(iGenType == GenIssCli)
            out_file << "UsePreviousGroup = no" << endl;

//     type gen_iss_top_cd_full.txt >> gen_cd.iss
//  :: type gen_iss_top_cd_upd.txt >> gen_cd.iss
//  :: type gen_iss_top_flash_full.txt >> gen_cd.iss
//  :: type gen_iss_top_flash_start_full.txt >> gen_flash_start.iss

         if(SUCCEEDED(retc)) out_file << endl;
         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
            out_file << ";OutputDir = Output\\setup" << endl;
#if FALSE            
// #  if((MsgLang != KpLangPl_1250_p) && (MsgLang != KpLangPl_1257_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p)) 
#  if((MsgLangOff != KpLangPl_1250) && (MsgLangOff != KpLangPl_1257) && (MsgLangOff != KpLangRu_1251) && (MsgLangOff != KpLangRu_0)) 
            out_file << ";";
#  endif            
            out_file << "OutputDir = files_grp\\setup" << endl;
#endif            

         case GenIssGrp:
#if TRUE // #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
            out_file << ";";
#endif            
            out_file << "OutputDir = ." << endl;
            out_file << endl;
//          out_file << ";OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_diegimas" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_" << Ver << build_str; 
#if FALSE
#  if((MsgLang == KpLangEn_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
            out_file << "_setup" << endl;
#  elif((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
            out_file << "_instalacja" << endl;
#  else
            out_file << "_diegimas" << endl;
#  endif
#else
            out_file << SetupFileSuffixes[iMsgLangOff] << endl;            
#endif

// // #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
// #if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257) || (iMsgLangOff == KpLangRu_1251) || (iMsgLangOff == KpLangRu_0))
//          if(iGenType != GenIssGrp) out_file << ";";
// #endif            
            out_file << "OutputBaseFilename = " << setup_fname;
#if FALSE
#  if((MsgLang == KpLangEn_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
            out_file << "_setup";
#  elif((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
            out_file << "_instalacja";
#  else
            out_file << "_diegimas";
#  endif
#else            
            out_file << SetupFileSuffixes[iMsgLangOff];            
#endif
            if(iGenType == GenIssSh) out_file << "_lentynoje"; 
            out_file << endl;
            
            out_file << ";OutputBaseFilename = " << setup_fname << endl;
            
#if FALSE
            if(iGenType != GenIssGrp)
            {
#  if(MsgLang == KpLangPl_1250_p) 
               out_file << "OutputBaseFilename = setup_pl_1250" << endl;
#  endif            
#  if(MsgLang == KpLangPl_1257_p) 
               out_file << "OutputBaseFilename = setup_pl_1257" << endl;
#  endif            
#  if(MsgLang == KpLangRu_1251_p) 
               out_file << "OutputBaseFilename = setup_ru_1251" << endl;
#  endif            
#  if(MsgLang == KpLangRu_0_p) 
               out_file << "OutputBaseFilename = setup_ru_0" << endl;
#  endif            
            }
#endif            
            out_file << endl;
            break;
         case GenIssUpd:
         case GenIssUpdWhole:
            out_file << "; -----------------------" << endl;
            out_file << "; keliais gabalais:" << endl;
//          out_file << ";OutputDir = {code:GetSetupFNameStr}_{code:GetVerStr}_atnaujinimas_gabalais" << endl;
            out_file << ";OutputDir = " << setup_fname << "_";
            if(iGenType == GenIssUpd) out_file << Ver << build_str;
#if FALSE            
#  if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_pelna";
            out_file << "_aktualizacja_sztuczna" << endl;
            if(iGenType == GenIssUpdWhole) out_file << ";OutputDir = " << setup_fname << "_pelna_aktualizacja_sztuczna" << endl;
#  elif((MsgLang == KpLangEn) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_whole";
            out_file << "_update_in_parts" << endl;
            if(iGenType == GenIssUpdWhole) out_file << ";OutputDir = " << setup_fname << "_whole_update_in_parts" << endl;
#  else // #elif(MsgLang == KpLangLt)
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_visas";
            out_file << "_atnaujinimas_gabalais" << endl;
            if(iGenType == GenIssUpdWhole) out_file << ";OutputDir = " << setup_fname << "_visas_atnaujinimas_gabalais" << endl;
#  endif
#else
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << WholeUpdateSuffix[iMsgLangOff];
            out_file << UpdateSuffix[iMsgLangOff] << PartialUpdateSuffix[iMsgLangOff] << endl;
            if(iGenType == GenIssUpdWhole) out_file << ";OutputDir = " << setup_fname << WholeUpdateSuffix[iMsgLangOff] << UpdateSuffix[iMsgLangOff] << PartialUpdateSuffix[iMsgLangOff] << endl;
#endif
            out_file << endl;
//          out_file << ";OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_";
            if(iGenType == GenIssUpd) out_file << Ver << build_str;
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer;
            out_file << endl;
            if(iGenType == GenIssUpdWhole) out_file << ";OutputBaseFilename = " << setup_fname << endl;
            out_file << endl;
            out_file << ";DiskSpanning = Yes" << endl;
            out_file << ";DiskSliceSize = 5000000" << endl;
            out_file << endl;

            out_file << "; -----------------------" << endl;
            out_file << "; vienu gabalu" << endl;
// #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
// #if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257) || (iMsgLangOff == KpLangRu_1251) || (iMsgLangOff == KpLangRu_0)) 
            out_file << ";";
// #endif            
            out_file << "OutputDir = ." << endl;
// #if((MsgLang != KpLangPl_1250_p) && (MsgLang != KpLangPl_1257_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p)) 
// #if((iMsgLangOff != KpLangPl_1250) && (iMsgLangOff != KpLangPl_1257) && (iMsgLangOff != KpLangRu_1251) && (iMsgLangOff != KpLangRu_0)) 
            out_file << ";";
// #endif            
            out_file << "OutputDir = files_upd_grp\\setup" << endl;
            out_file << endl;
//          out_file << "OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_atnaujinimas_pilnas" << endl;

// #if((MsgLang != KpLangPl_1250_p) && (MsgLang != KpLangPl_1257_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p)) 
// #if((iMsgLangOff != KpLangPl_1250) && (iMsgLangOff != KpLangPl_1257) && (iMsgLangOff != KpLangRu_1251) && (iMsgLangOff != KpLangRu_0)) 
            if(iGenType == GenIssUpdWhole) 
// #endif            
               out_file << ";";
            out_file << "OutputBaseFilename = " << setup_fname << "_";
            if(iGenType == GenIssUpd) out_file << Ver << build_str;
#if FALSE
#  if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_pelna";
            out_file << "_aktualizacja" << endl;
#  elif((MsgLang == KpLangEn) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_whole";
            out_file << "_update" << endl;
#  else // #elif(MsgLang == KpLangLt)
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << "_visas";
            out_file << "_atnaujinimas" << endl;
#  endif
#else
            else /* if(iGenType == GenIssUpdWhole) */ out_file << FirstVer << WholeUpdateSuffix[iMsgLangOff];
            out_file << UpdateSuffix[iMsgLangOff] << endl;
#endif

            if(iGenType == GenIssUpdWhole) out_file << "OutputBaseFilename = " << setup_fname << 
#if FALSE
#  if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
               "_pelna_aktualizacja"
#  elif((MsgLang == KpLangEn) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
               "_whole_update"
#  else // #elif(MsgLang == KpLangLt)
               "_visas_atnaujinimas"
#  endif
#else
               WholeUpdateSuffix[iMsgLangOff] << UpdateSuffix[iMsgLangOff]
#endif
                   << endl;

#if FALSE
#  if(MsgLang == KpLangPl_1250_p) 
            out_file << "OutputBaseFilename = setup_pl_1250" << endl;
#  endif            
#  if(MsgLang == KpLangPl_1257_p) 
            out_file << "OutputBaseFilename = setup_pl_1257" << endl;
#  endif            
#  if(MsgLang == KpLangRu_1251_p) 
            out_file << "OutputBaseFilename = setup_ru_1251" << endl;
#  endif            
#  if(MsgLang == KpLangRu_0_p) 
            out_file << "OutputBaseFilename = setup_ru_0" << endl;
#  endif            
#endif            
            out_file << endl;
            break;
         case GenIssFinst:
            out_file << "OutputDir = " << ProjID << "_atmintukas" << endl;
            out_file << endl;
            break;
         case GenIssFlash:
            out_file << "OutputDir = ." << endl;
            out_file << ";OutputDir = " << setup_fname << "_" << Ver << build_str << "_atmintukas" << endl;
            out_file << endl;
//          out_file << "OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_setup_flash" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_" << Ver << build_str << "_diegimas_atmintuke" << endl;
            out_file << "OutputBaseFilename = " << setup_fname << "_atmintuko_atstatymas" << endl;
            out_file << endl;
            break;
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
// #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
// #if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257) || (iMsgLangOff == KpLangRu_1251) || (iMsgLangOff == KpLangRu_0)) 
//          out_file << ";";
// #endif            
            out_file << "OutputDir = ." << endl;
// #if((MsgLang != KpLangPl_1250_p) && (MsgLang != KpLangPl_1257_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p)) 
// #if((iMsgLangOff != KpLangPl_1250) && (iMsgLangOff != KpLangPl_1257) && (iMsgLangOff != KpLangRu_1251) && (iMsgLangOff != KpLangRu_0)) 
            out_file << ";";
// #endif            
            out_file << "OutputDir = files_flash_upd_grp\\setup" << endl;
            out_file << endl;

// #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
// #if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257) || (iMsgLangOff == KpLangRu_1251) || (iMsgLangOff == KpLangRu_0)) 
//          out_file << ";";
// #endif            
            out_file << "OutputBaseFilename = " << setup_fname << "_";
            if(iGenType == GenIssFlashUpd) out_file << Ver << build_str;
            else /* if(iGenType == GenIssFlashUpdWhole) */ 

#if FALSE
#  if((MsgLang == KpLangEn_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
               out_file << FirstVer << "_whole";
#  elif((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
               out_file << FirstVer << "_kompletna";
#  else
               out_file << FirstVer << "_visas";
#  endif
#else
               out_file << FirstVer << WholeUpdateSuffix[iMsgLangOff];
#endif            

#if FALSE
#  if((MsgLang == KpLangEn_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
            out_file << "_flash_update" << endl;
#  elif((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p)) 
            out_file << "_aktualizacja_nosnika" << endl;
#  else
            out_file << "_atmintuko_atnaujinimas" << endl;
#  endif
#else
// #  if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257)) 
            if((iMsgLangOff == KpLangPl_1250) || (iMsgLangOff == KpLangPl_1257)) 
               out_file << UpdateSuffix[iMsgLangOff] << FlashUpdateSuffix[iMsgLangOff] << endl;
// #  else
            else
               out_file << FlashUpdateSuffix[iMsgLangOff] << UpdateSuffix[iMsgLangOff] << endl;
// #  endif
#endif            

#if FALSE
#  if(MsgLang == KpLangPl_1250_p) 
            out_file << "OutputBaseFilename = update_pl_1250" << endl;
#  endif            
#  if(MsgLang == KpLangPl_1257_p) 
            out_file << "OutputBaseFilename = update_pl_1257" << endl;
#  endif            
#  if(MsgLang == KpLangRu_1251_p) 
            out_file << "OutputBaseFilename = update_ru_1251" << endl;
#  endif            
#  if(MsgLang == KpLangRu_0_p) 
            out_file << "OutputBaseFilename = update_ru_0" << endl;
#  endif            
#endif            
            out_file << endl;
            break;
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
//          out_file << "OutputDir = files" << endl;
            out_file << ";OutputDir = Output_flash" << endl;
//          out_file << "OutputDir = Output_flash_vol" << endl;
//          out_file << ";OutputDir = Output_flash_live" << endl;
            out_file << ";OutputDir = Output_flash_iso" << endl;
            out_file << ";OutputDir = " << setup_fname << "_" << Ver << build_str << "_atmintukas\\Output_flash" << endl;

//          out_file << "OutputDir = Output_flash_iso\\" << prod_dir << endl;
//          out_file << "OutputDir = Output_flash_iso\\" << prod_fname_raw << endl;
//          out_file << "OutputDir = Output_flash_iso\\{code:GetProdDirStr}" << endl;
            strcpy(str_buf, prod_fname_raw);
            pntd = str_buf + strlen(str_buf);
            if(pntd > str_buf) pntd--;
            if(*pntd == '\'') *pntd = Nul;
            pntd = str_buf;
            if(*pntd == '\'') pntd++;
            out_file << "OutputDir = Output_flash_iso\\" << pntd << endl;
            
            out_file << endl;
//          out_file << "OutputBaseFilename = Pradzia_{code:GetSetupFNameStr}" << endl;
            out_file << "OutputBaseFilename = Pradzia_" << setup_fname << endl;
            out_file << endl;
            break;
         case GenIssNet:
            out_file << ";OutputDir = ." << endl;
            out_file << "OutputDir = Output_net" << endl;
            out_file << endl;
//          out_file << ";OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_diegimas_tinkle" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_" << Ver << build_str << "_diegimas_tinkle" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << endl;
            out_file << ";OutputBaseFilename = setup_net" << endl;
            out_file << endl;
            break;
         case GenIssSvr:
            out_file << ";OutputDir = ." << endl;
            out_file << ";OutputDir = ..\\arkim_acrobat\\files" << endl;
            out_file << ";OutputDir = ..\\Acrobat_Beb\\files" << endl;
//          out_file << ";OutputDir = ..\\bebras_b\\files" << endl;
            out_file << ";OutputDir = files" << endl;
            out_file << ";OutputDir = Output_svr" << endl;
            out_file << "OutputDir = Output_net" << endl;
            out_file << endl;
//          out_file << "OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_serverio_diegimas" << endl;
            out_file << "OutputBaseFilename = " << setup_fname << "_" << Ver << build_str << "_serverio_diegimas" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_serveris" << endl;
//          out_file << ";OutputBaseFilename = setup_server" << endl;
            out_file << endl;
            break;
         case GenIssChkVol:
//          out_file << "OutputDir = ." << endl;
//          out_file << "OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_atmintuko_prieziura" << endl;
            out_file << "OutputDir = " /* "OutputBaseFilename=" */ << setup_fname << "_" << Ver << build_str << "_atmintuko_prieziura" << endl;
            out_file << endl;
            break;
         case GenIssCli:
            out_file << ";OutputDir = ." << endl;
            out_file << "OutputDir = Output_net" << endl;
            out_file << endl;
//          out_file << ";OutputBaseFilename = {code:GetSetupFNameStr}_{code:GetVerStr}_mokinys" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_" << Ver << build_str << "_mokinys" << endl;
            out_file << ";OutputBaseFilename = " << setup_fname << "_mokinys" << endl;
            out_file << "OutputBaseFilename = setup_cli" << endl;
            out_file << endl;
            break;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
            if(AutoRun)
            {
               out_file << "RestartIfNeededByRun = yes" << endl;
               out_file << endl;
            }
            break;
         case GenIssSvr:
            out_file << "AlwaysRestart = yes" << endl;
            out_file << "UninstallRestartComputer = yes" << endl;
            out_file << endl;
            break;
         }

         if(SUCCEEDED(retc)) out_file << "UsePreviousLanguage = no" << endl;
         if(SUCCEEDED(retc)) out_file << endl;

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssNet:
         case GenIssSvr:
         case GenIssCli:
         case GenIssGrp:
            if(RequireAdmin) break;
         case GenIssSh:
         case GenIssCert:
            out_file << "AlwaysUsePersonalGroup = yes" << endl;
         case GenIssFlash:
         case GenIssFinst:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
//          out_file << ";";
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
            out_file << "PrivilegesRequired = none" << endl;
            out_file << endl;
            break;
         }

         if(SUCCEEDED(retc))
         {
            strcpy(check_fname, "License.rtf");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << "LicenseFile = " << check_fname << endl;
               out_file << endl;
               in_file.close();
            }
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCert:
            out_file << "InfoBeforeFile = infobefore.rtf" << endl;
            out_file << endl;
            break;
         }

         if(SUCCEEDED(retc)) out_file << endl;

         if(SUCCEEDED(retc)) out_file << "[Files]" << endl;
         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
            if(AutoRun)
            {
//             out_file << "Source: \"files\\{code:GetExeFNameStr}.e_e\"; DestDir: \"{app}\"; DestName: \"{code:GetExeFNameStr}.exe\"; Flags: onlyifdoesntexist;" << endl;
               out_file << "Source: \"files\\" << ExeFName << ".e_e\"; DestDir: \"{code:GetAppPathStr}\"; DestName: \"" << ExeFName << ".exe\"; Flags: onlyifdoesntexist;" << endl;
            }
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssCli:
//          in_file.open("files\\AcroRead602\\Reader\\AcroRd32.exe", ios_base::in | ios_base::binary);

            strcpy(check_fname, FnamePref[iGenType]);
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\AcroRead602\\Reader\\msvcp60.dll");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
// uþkomentuota, kad atmintuko paleidëjams nereikëtø admino, unicows.dll reikia tik Win98, o ten atmintukai ir ðiaip neveikia
               if((!RequireAdmin) || (iGenType==GenIssSh) || (iGenType==GenIssCert) || (iGenType==GenIssFlashStart) || (iGenType==GenIssFlashStartUpd)) out_file << ";";
               out_file << "Source: \"" << check_fname;
//             out_file << FnamePref[iGenType];
//             if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) out_file << FnameSuff[iGenType];    
//             out_file << "\\AcroRead602\\Reader\\msvcp60.dll";
               out_file << "\"; DestDir: \"{sys}\"; Flags: onlyifdoesntexist;" << endl;

               in_file.close();
            }

            strcpy(check_fname, FnamePref[iGenType]);
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\AcroRead602\\Reader\\unicows.dll");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               if((!RequireAdmin) || (iGenType==GenIssSh) || (iGenType==GenIssCert) || (iGenType==GenIssFlashStart) || (iGenType==GenIssFlashStartUpd)) out_file << ";"; // kad atmintuko paleidëjams nereikëtø admino 
               out_file << "Source: \"" << check_fname;
//             out_file << FnamePref[iGenType];
//             if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) out_file << FnameSuff[iGenType];    
//             out_file << "\\AcroRead602\\Reader\\unicows.dll";
               out_file << "\"; DestDir: \"{sys}\"; Flags: onlyifdoesntexist;" << endl;

               in_file.close();
            }
            
// !!! dar reikëtø ...\\AcroRead709\\Reader\\MSVCP71.DLL ir MSVCR71.DLL

// //       out_file << "Source: \"files\\riched.dll\"; DestDir: \"{sys}\"; Flags: onlyifdoesntexist;" << endl;
// //       out_file << "Source: \"files\\riched20.dll\"; DestDir: \"{sys}\"; Flags: onlyifdoesntexist;" << endl;
// WinLED-ui, tik Win98, bet nerekomenduoja
//          out_file << "Source: \"files\\riched32.dll\"; DestDir: \"{sys}\"; Flags: onlyifdoesntexist;" << endl;
            break;
         case GenIssSvr:
//          out_file << "Source: \"files_svr\\{code:GetSvrFNameStr}.e_e\"; DestDir: \"{app}\"; DestName: \"{code:GetSvrFNameStr}.exe\"; Flags: onlyifdoesntexist;" << endl;
            out_file << "Source: \"files_svr\\" << SvrFName << ".e_e\"; DestDir: \"{code:GetAppPathStr}\"; DestName: \"" << SvrFName << ".exe\"; Flags: onlyifdoesntexist;" << endl;

            out_file << "Source: \"files_svr\\Win2K\\srvany.e_e\"; DestDir: \"{code:GetAppPathStr}\\Win2K\"; DestName: \"srvany.exe\"; Flags: onlyifdoesntexist;" << endl;
            out_file << "Source: \"files_svr\\WinNT\\srvany.e_e\"; DestDir: \"{code:GetAppPathStr}\\WinNT\"; DestName: \"srvany.exe\"; Flags: onlyifdoesntexist;" << endl;

            if(AutoRun && (strcmp(ExeFName, SvrFName) != 0))
            {
//             out_file << "Source: \"files_svr\\{code:GetExeFNameStr}.e_e\"; DestDir: \"{code:GetAppPathStr}\"; DestName: \"{code:GetExeFNameStr}.exe\"; Flags: onlyifdoesntexist;" << endl;
               out_file << "Source: \"files_svr\\" << ExeFName << ".e_e\"; DestDir: \"{code:GetAppPathStr}\"; DestName: \"" << ExeFName << ".exe\"; Flags: onlyifdoesntexist;" << endl;
            }
            break;
         }


// echo ------------------------
//     type files.txt >> gen_cd.iss
//  :: type files_upd.txt >> gen_cd.iss

//     type files_cd.txt >> gen_cd.iss
//  :: type files_flash.txt >> gen_cd.iss

//  :: type fonts.txt >> gen_cd.iss


         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_cd.txt");
         case GenIssSh:
         case GenIssCert:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_sh.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_rez.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"fonts.txt");
            break;
         case GenIssUpd:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_upd.txt");
            break;
         case GenIssUpdWhole:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_upd_whole.txt");
            break;
         case GenIssGrp:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_grp.txt");
            break;
         case GenIssFlash:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_flash.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"fonts.txt");
            break;
         case GenIssFlashUpd:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_flash_upd.txt");
            break;
         case GenIssFlashUpdWhole:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_flash_upd_whole.txt");
            break;
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_flash_start.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"fonts.txt");
            break;
         case GenIssNet:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_net.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_rez.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"fonts.txt");
            break;
         case GenIssSvr:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_svr.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_rez.txt");
            break;
         case GenIssChkVol:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_chkvol.txt");
            break;
         case GenIssCli:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_rez.txt");
            break;
         case GenIssFinst:
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"files_finst.txt");
            if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, (const unsigned char *)"fonts.txt");
            break;
         }

// echo ------------------------
//     type gen_iss_ico_cd.txt >> gen_cd.iss

//----------
         if((iGenType != GenIssGrp) && (iGenType != GenIssFinst) && SUCCEEDED(retc))
         {
            icon_file_name = (const unsigned char *)"";
            switch(iGenType)
            {
               case GenIssCd: icon_file_name = (const unsigned char *)"icons_cd.txt"; break;
               case GenIssSh: icon_file_name = (const unsigned char *)"icons_sh.txt"; break;
               case GenIssCert: icon_file_name = (const unsigned char *)"icons_cert.txt"; break;
               case GenIssUpd: icon_file_name = (const unsigned char *)"icons_upd.txt"; break;
               case GenIssUpdWhole: icon_file_name = (const unsigned char *)"icons_upd_whole.txt"; break;
               // case GenIssFlash: icon_file_name = (const unsigned char *)"icons_flash.txt"; break;
               case GenIssFlashUpd: icon_file_name = (const unsigned char *)"icons_flash_upd.txt"; break;
               case GenIssFlashUpdWhole: icon_file_name = (const unsigned char *)"icons_flash_upd_whole.txt"; break;
               case GenIssFlashStart:
               case GenIssFlashStartUpd:
                  icon_file_name = (const unsigned char *)"icons_flash_start.txt"; break;
               case GenIssNet: icon_file_name = (const unsigned char *)"icons_net.txt"; break;
               case GenIssSvr: icon_file_name = (const unsigned char *)"icons_svr.txt"; break;
               case GenIssChkVol: icon_file_name = (const unsigned char *)"icons_chkvol.txt"; break;
               case GenIssCli: icon_file_name = (const unsigned char *)"icons_cli.txt"; break;
            }
            in_file.open((const char *)icon_file_name, ios_base::in);

            if((
                  (iGenType == GenIssCd) || (iGenType == GenIssCert) || 
                  (((iGenType == GenIssSh) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole)) && (!in_file.fail())) || 
                  (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssChkVol) || (iGenType == GenIssCli)
                ) && 
                SUCCEEDED(retc)
               )
            {
               out_file << endl;
               out_file << endl;

               out_file << "[Icons]" << endl;

               if(!in_file.fail())
               {
                  in_file.close();
                  if(SUCCEEDED(retc)) retc = AppendIssFile(&out_file, icon_file_name);
               }
               else
               {
                  if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssChkVol) || (iGenType == GenIssNet) || (iGenType == GenIssCli))
                  {
                     out_file << "Name: \"{group}\\{code:GetProdFNameStr}\"; ";
                        out_file << "Filename: \"{code:GetLaunchStr}\"; "; // "Filename: \"{code:GetAppPathStr}\\{code:GetExeFNameStr}.exe\"; ";
                        out_file << "IconFilename:\"{code:GetAppPathStr}\\{code:GetIconFNameStr}\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }
                  
                  if(iGenType == GenIssSvr)
                  {
                     out_file << "Name: \"{group}\\";
                        out_file << GENISS_LINK_SERVER_MANAGEMENT; 
                        out_file << "\"; Filename: \"{code:GetAppPathStr}\\{code:GetSvrFNameStr}.url\"; IconFilename:\"{code:GetAppPathStr}\\service01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                     out_file << "Name: \"{group}\\{code:GetCleanIconNameStr}\"; Filename: \"{code:GetProdDirStr}\\rezultatai\\trinam_{code:GetSvrFNameStr}.bat\"; IconFilename:\"{code:GetAppPathStr}\\uninst01.ico\"; WorkingDir: \"{code:GetProdDirStr}\\rezultatai\"; Flags: closeonexit;" << endl;
                     out_file << "Name: \"{group}\\";
                        out_file << GENISS_LINK_OPTIONS; 
                        out_file << "\"; Filename: \"{code:GetAppPathStr}\\edini.exe\"; Parameters: \"\"\"{code:GetAppPathStr}\\{code:GetSvrFNameStr}.ini\"\"\"; IconFilename:\"{code:GetAppPathStr}\\setup01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }

                  if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssSvr))
                  {
                     strcpy(check_fname, FnamePref[iGenType]);
                     strcat(check_fname, FnameSuff[GenIssSh]); // FnameSuff[iGenType]);
                     strcat(check_fname, "\\registr.exe"); 
                     in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
                     if(!in_file.fail())
                     {
//                      out_file << "Name: \"{group}\\Registracija\"; Filename: \"{code:GetAppPathStr}\\registr.exe\"; IconFilename:\"{code:GetAppPathStr}\\setup01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                        out_file << ";Name: \"{group}\\";
                           out_file << GENISS_LINK_REG; 
                           out_file << "\"; Filename: \"{code:GetAppPathStr}\\registr.exe\"; IconFilename:\"{code:GetAppPathStr}\\registr.exe\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;

                        in_file.close();
                     }
                  }

                  if(iGenType == GenIssNet)
                  {
                     out_file << "Name: \"{group}\\";
                        out_file << GENISS_LINK_REG;
                        out_file << "\"; Filename: \"{code:GetAppPathStr}\\edini.exe\"; Parameters: \"\"\"{code:GetAppPathStr}\\{code:GetExeFNameStr}.ini\"\"\"; IconFilename:\"{code:GetAppPathStr}\\setup01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }

// in_file.close();
                  strcpy(check_fname, FnamePref[iGenType]);
                  
//                if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole)) strcat(check_fname, FnameSuff[GenIssCd]);
//                else strcat(check_fname, FnameSuff[iGenType]);
                  strcat(check_fname, FnameSuff[GenIssSh]);
                                     
                  strcat(check_fname, "\\unreg.exe"); 
                  in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
//                in_file.open(check_file, fstream::in | fstream::binary);
                  if((!in_file.fail()) && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssSvr)))
                  {
                     out_file << ";Name: \"{group}\\";
                        out_file << GENISS_LINK_UNREG;
                        out_file << "\"; Filename: \"{uninstallexe}\"; IconFilename:\"{code:GetAppPathStr}\\unreg.exe\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }
#if FALSE // Panaikinimo be unreg.exe nebereikia (su unreg.exe irgi)                  
                  else
                  {
// out_file << "------- files_cd\\unreg.exe not found" << endl;
// system("dir files_cd > geniss.lst");

//                   out_file << "Name: \"{group}\\Panaikinimas\"; Filename: \"{code:GetAppPathStr}\\unreg.exe\"; IconFilename:\"{code:GetAppPathStr}\\uninst01.ico\"; WorkingDir: \"{code:GetAppPathStr}\"; Parameters: \"\"\"{uninstallexe}\"\"\";" << endl;
                     out_file << "Name: \"{group}\\";
                        out_file << GENISS_LINK_UNREG;
                        out_file << "\"; Filename: \"{uninstallexe}\"; IconFilename:\"{code:GetAppPathStr}\\uninst01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }
#endif                  
                  if(!in_file.fail()) in_file.close();

// !!!! TODO: palistint visus .exe ið files ir files_cd ir sugeneruot jø .log failø sàraðà
                  if(startsel_exe_exists)
                  {
                     out_file << "Name: \"{group}\\{code:GetSendDiagMsgIconNameStr}\"; Filename: \"{code:GetAppPathStr}\\sts.exe\"; Parameters: \"\"\"DiagMsg = %TEMP%\\";
                     out_file << ExeFName; 
                     out_file << ".log;";
                     if(strcmp(ExeFName, "XFS") == 0) out_file << " %TEMP%\\xipa.log;";
                     out_file << " %TEMP%\\registr.log; {code:GetAppPathStr}\\data.dat\"\"\"; IconFilename:\"{code:GetAppPathStr}\\sts.exe\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }

                  if((!AutoRun) && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssChkVol) || (iGenType == GenIssNet) || (iGenType == GenIssCli)) && SUCCEEDED(retc))
                  {
                     out_file << endl;

//                   out_file << "Name: \"{userdesktop}\\{code:GetProdFNameStr}\"; Filename: \"{app}\\{code:GetExeFNameStr}.exe\"; IconFilename:\"{app}\\{code:GetIconFNameStr}\"; WorkingDir: \"{app}\";" << endl;
                     out_file << "Name: \"";
                     if(RequireAdmin && (iGenType != GenIssSh) && (iGenType != GenIssCert)) out_file << "{commondesktop}";
                     else out_file << "{userdesktop}";
                     out_file << "\\{code:GetProdFNameStr}\"; ";
                        out_file << "Filename: \"{code:GetLaunchStr}\"; "; // "Filename: \"{code:GetAppPathStr}\\{code:GetExeFNameStr}.exe\"; ";
                        out_file << "IconFilename:\"{code:GetAppPathStr}\\{code:GetIconFNameStr}\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }


                  if(iGenType == GenIssSvr)
                  {
                     out_file << endl;

                     out_file << "Name: \"{commondesktop}\\{code:GetProdFNameStr} ";
                        out_file << GENISS_LINK_SERVER;
                        out_file << "\"; Filename: \"{code:GetAppPathStr}\\{code:GetSvrFNameStr}.url\"; IconFilename:\"{code:GetAppPathStr}\\service01.ico\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }

                  if(AutoRun && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssSvr) || (iGenType == GenIssNet)) && SUCCEEDED(retc))
                  {
                     out_file << endl;

                     out_file << "Name: \"{commonstartup}\\{code:GetProdFNameStr}\"; ";
                        out_file << "Filename: \"{code:GetLaunchStr}\"; "; // "Filename: \"{code:GetAppPathStr}\\{code:GetExeFNameStr}.exe\"; ";
                        out_file << "IconFilename:\"{code:GetAppPathStr}\\{code:GetIconFNameStr}\"; WorkingDir: \"{code:GetAppPathStr}\";" << endl;
                  }

               } // else // if(!in_file.fail())

            } // if(((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssSvr) || (iGenType == GenIssChkVol) || (iGenType == GenIssCli)) && SUCCEEDED(retc))

         }  // if(SUCCEEDED(retc))

// --------------
         if(AutoRun && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssNet)) && SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;

            out_file << "[Run]" << endl;
//          out_file << "Filename: \"{app}\\{code:GetExeFNameStr}.exe\"; Flags: postinstall nowait;" << endl;
            out_file << "Filename: \"{code:GetAppPathStr}\\" << ExeFName << ".exe\"; Description: \"";
               out_file << GENISS_MSG_START_PROG;
               out_file << " {code:GetProdFNameStr}.\"; Flags: postinstall nowait;" << endl;
         }


// echo ------------------------
//     type gen_iss_cod.pas >> gen_cd.iss

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;

            out_file << "[Code]" << endl;
            out_file << endl;
            out_file << "var" << endl;
            out_file << "   bFinishedInstall: Boolean;" << endl;
            if(ChkUpd && (iGenType != GenIssFlashStart)) 
               out_file << "   TestUpdPage: TInputOptionWizardPage;" << endl;

            if(ask_use_acc_let_flg)
            {
//             out_file << "   AccLetPage: TInputOptionWizardPage;" << endl;
               out_file << "   AccLetAsked: Boolean;" << endl;
               out_file << "   UseAccLet: Boolean;" << endl;
            }
            if((PartialInstall || PartialDir) && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssNet) || (iGenType == GenIssSvr))) 
               out_file << "   sDefDirName: String;" << endl;
            if(iGenType == GenIssChkVol) out_file << "   FlashIdPage: TInputQueryWizardPage;" << endl;

            if((iGenType == GenIssFlashUpd) || (iGenType == GenIssFlashUpdWhole) || 
                  (iGenType == GenIssFlash) || (iGenType == GenIssFinst))
            { 
               out_file << "   sAppPath: String;" << endl;
               out_file << "   bAppPathCalculated: Boolean;" << endl;
            }

#if FALSE
            out_file << endl;
            out_file << endl;
            out_file << "function GetEmptyStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'\';" << endl;
            out_file << "end;" << endl;
#endif

            if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType == GenIssFinst))
            {
               out_file << endl;
               out_file << endl;
               out_file << "function KpRegSoftWriteDWordValue(const SubKeyName, ValueName: String; const Data: Cardinal; const Message: String): Boolean;" << endl;
               out_file << "var retw: Boolean;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   retw := True;" << endl;
               out_file << endl;
               out_file << "   if(not RegWriteDWordValue(HKEY_LOCAL_MACHINE, \'Software\\\' + SubKeyName, ValueName, Data)) then" << endl;
               out_file << "   begin" << endl;
               if(((!RequireAdmin) || (iGenType == GenIssSh) || (iGenType == GenIssCert)) && (iGenType != GenIssSvr))
               {
//                out_file << "      if(Message = \'" << GENISS_MSG_INST_ADMIN << "\') then" << endl;
                  out_file << "         RegWriteDWordValue(HKEY_CURRENT_USER, \'Software\\\' + SubKeyName, ValueName, Data)" << endl;
//                out_file << "      else" << endl;
//                out_file << "      begin" << endl;
               }
//             if(((RequireAdmin) || (iGenType == GenIssSvr) || (iGenType == GenIssCd) || (iGenType == GenIssNet)) && (iGenType != GenIssSh) && (iGenType != GenIssCert))
               else
               {
                  out_file << "         MsgBox(Message, mbCriticalError, MB_OK);" << endl;
                  out_file << "         retw := False;" << endl;
               }
//             if(((!RequireAdmin) || (iGenType == GenIssSh) || (iGenType == GenIssCert)) && (iGenType != GenIssSvr))
//                out_file << "      end;" << endl;
               out_file << "   end;" << endl;
               out_file << endl;
               out_file << "Result := retw;" << endl;
               out_file << "end;" << endl;
   
               out_file << endl;
               out_file << endl;
               out_file << "function KpRegSoftWriteStringValue(const SubKeyName, ValueName, Data, Message: String): Boolean;" << endl;
               out_file << "var retw: Boolean;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   retw := True;" << endl;
               out_file << endl;
               out_file << "   if(not RegWriteStringValue(HKEY_LOCAL_MACHINE, \'Software\\\' + SubKeyName, ValueName, Data)) then" << endl;
               out_file << "   begin" << endl;
               if(((!RequireAdmin) || (iGenType == GenIssSh) || (iGenType == GenIssCert)) && (iGenType != GenIssSvr))
               {
//                out_file << "      if(Message = \'" << GENISS_MSG_INST_ADMIN << "\') then" << endl;
                  out_file << "         RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\\' + SubKeyName, ValueName, Data)" << endl;
//                out_file << "      else" << endl;
//                out_file << "      begin" << endl;
               }
//             if(((RequireAdmin) || (iGenType == GenIssSvr) || (iGenType == GenIssCd) || (iGenType == GenIssNet)) && (iGenType != GenIssSh) && (iGenType != GenIssCert))
               else
               {
                  out_file << "         MsgBox(Message, mbCriticalError, MB_OK);" << endl;
                  out_file << "         retw := False;" << endl;
               }
//             if(((!RequireAdmin) || (iGenType == GenIssSh) || (iGenType == GenIssCert)) && (iGenType != GenIssSvr))
//                out_file << "      end;" << endl;
               out_file << "   end;" << endl;
               out_file << endl;
               out_file << "Result := retw;" << endl;
               out_file << "end;" << endl;

               out_file << endl;
               out_file << endl;
               out_file << "function KpRegSoftQueryDWordValue(const SubKeyName, ValueName: String; var ResVal: dword): Boolean;" << endl;
               out_file << "var found: Boolean;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   found := False;" << endl;
               out_file << endl;
               out_file << "   if(not found) then found := RegQueryDWordValue(HKEY_CURRENT_USER, \'Software\\\' + SubKeyName, ValueName, ResVal);" << endl;
               out_file << "   if(not found) then found := RegQueryDWordValue(HKEY_CURRENT_USER, \'Software\\Wow6432Node\\\' + SubKeyName, ValueName, ResVal);" << endl;
               out_file << "   if(not found) then found := RegQueryDWordValue(HKEY_LOCAL_MACHINE, \'Software\\\' + SubKeyName, ValueName, ResVal);" << endl;
               out_file << "   if(not found) then found := RegQueryDWordValue(HKEY_LOCAL_MACHINE, \'Software\\Wow6432Node\\\' + SubKeyName, ValueName, ResVal);" << endl;
               out_file << endl;
               out_file << "Result := found;" << endl;
               out_file << "end;" << endl;

               out_file << endl;
               out_file << endl;
               out_file << "function KpRegSoftQueryStringValue(const SubKeyName, ValueName: String; var ResultStr: String): Boolean;" << endl;
               out_file << "var found: Boolean;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   found := False;" << endl;
               out_file << endl;
               out_file << "   if(not found) then found := RegQueryStringValue(HKEY_CURRENT_USER, \'Software\\\' + SubKeyName, ValueName, ResultStr);" << endl;
               out_file << "   if(not found) then found := RegQueryStringValue(HKEY_CURRENT_USER, \'Software\\Wow6432Node\\\' + SubKeyName, ValueName, ResultStr);" << endl;
               out_file << "   if(not found) then found := RegQueryStringValue(HKEY_LOCAL_MACHINE, \'Software\\\' + SubKeyName, ValueName, ResultStr);" << endl;
               out_file << "   if(not found) then found := RegQueryStringValue(HKEY_LOCAL_MACHINE, \'Software\\Wow6432Node\\\' + SubKeyName, ValueName, ResultStr);" << endl;
               out_file << endl;
               out_file << "Result := found;" << endl;
               out_file << "end;" << endl;
            }
            
            out_file << endl;
            out_file << endl;
            out_file << "function GetProdVer: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := ";
            if(SUCCEEDED(retc)) switch(iGenType)
            {
            case GenIssCd:
            case GenIssSh:
            case GenIssCert:
            case GenIssUpd:
            case GenIssUpdWhole:
            case GenIssGrp:
            case GenIssFinst:
               out_file << ProdVer;
               break;
            case GenIssNet:
            case GenIssSvr:
            case GenIssCli:
               out_file << ProdVerNet;
               break;
            case GenIssFlash:
            case GenIssFlashUpd:
            case GenIssFlashUpdWhole:
            case GenIssFlashStart:
            case GenIssFlashStartUpd:
            case GenIssChkVol:
               out_file << ProdVerFlash;
               break;
            }
            out_file << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdVerStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProdVer;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetVer: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'" << Ver << build_str << "\';" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetVerStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetVer;" << endl;
            out_file << "end;" << endl;
         }

// ---------------
//     type gen_iss_cod_cd_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_cd_upd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start_full.pas >> gen_cd.iss


         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssUpd:
         case GenIssUpdWhole:

            out_file << endl;
            out_file << endl;
            out_file << "function GetPrevUpdNum: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << PrevUpdNum << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetPrevVer: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'" << PrevVer << "\';" << endl;
            out_file << "end;" << endl;

         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
//       case GenIssGrp:
         case GenIssNet:
         case GenIssSvr:
         case GenIssCli:
//          if((!PartialInstall) && (!PartialDir) && (iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) break;

         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
//       case GenIssFlashStart:
//       case GenIssFlashStartUpd:
         case GenIssFinst:

            out_file << endl;
            out_file << endl;
            out_file << "function GetFirstVer: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'" << FirstVer << "\';" << endl;
            out_file << "end;" << endl;

            break;
         }

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssCd:
         case GenIssNet:
         case GenIssSvr:

            if((!PartialInstall) && (!PartialDir) && (iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) break;

            if(!PartialInstall)
            {
               out_file << endl;
               out_file << endl;
               out_file << "function ShouldSkipPage(PageID: Integer): Boolean;" << endl;
               out_file << "begin" << endl;
//             if(!PartialInstall)
               {
                  out_file << "   case PageID of" << endl;
                  if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole))
                     out_file << "      wpSelectProgramGroup," << endl;
                  out_file << "      wpSelectDir:" << endl;
               }
//             else
//             {
//                out_file << "   case PageID of" << endl;
//                out_file << "      wpWelcome, wpSelectDir:" << endl;
//             }
               out_file << "         Result := True;" << endl;
//             if(!PartialInstall)
               { 
                  out_file << "      else" << endl;
                  out_file << "         Result := False;" << endl;
                  out_file << "   end;" << endl;
               }
               out_file << "end;" << endl;
   
               break; // case GenIssUpd: // case GenIssCd:
            }

         case GenIssSh:
         case GenIssFlashStart:
         case GenIssGrp:

            out_file << endl;
            out_file << endl;
            out_file << "function ShouldSkipPage(PageID: Integer): Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << "   Result := True;" << endl;
            out_file << "end;" << endl;

            break; // case GenIssFlashStart:

         case GenIssCert:

            out_file << endl;
            out_file << endl;
            out_file << "function ShouldSkipPage(PageID: Integer): Boolean;" << endl;
            out_file << "var retv: Boolean;" << endl;
            out_file << "var launch: String;" << endl;
            out_file << "begin" << endl;
            out_file << "   retv := False;" << endl;
            out_file << "   if(PageID = wpInfoBefore) then" << endl;
            out_file << "   begin" << endl;
            out_file << "      if(RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\AcroRd32.exe', '', launch)) then" << endl;
            out_file << "         retv := True;" << endl;
            out_file << "   end;" << endl;
            out_file << "Result := retv;" << endl;
            out_file << "end;" << endl;
            
            break; // case GenIssCert:

         case GenIssFlashStartUpd:

            out_file << endl;
            out_file << endl;
            out_file << "function ShouldSkipPage(PageID: Integer): Boolean;" << endl;
            out_file << "var retw: Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << "   retw := True;" << endl;
            out_file << "   if(PageID = 100) then retw := False;" << endl;
            out_file << "   Result := retw;" << endl;
            out_file << "end;" << endl;

            break; // case GenIssFlashStartUpd:

         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFlash:
         case GenIssFinst:

            out_file << endl;
            out_file << endl;
            out_file << "function ShouldSkipPage(PageID: Integer): Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << "   case PageID of" << endl;
            out_file << "      wpSelectDir:" << endl;
            out_file << "         Result := True;" << endl;
            out_file << "      else" << endl;
            out_file << "         Result := False;" << endl;
            out_file << "   end;" << endl;
            out_file << "end;" << endl;
   
            break; // GenIssFlashUpd: // case GenIssFlashUpdWhole:
            
         }

// echo ------------------------
//     type gen_iss_cod.pas >> gen_cd.iss

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetProdNameRaw: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << ProdNameRaw << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdName: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := ";
            if(SUCCEEDED(retc)) switch(iGenType)
            {
            case GenIssCd:
            case GenIssSh:
            case GenIssCert:
            case GenIssUpd:
            case GenIssUpdWhole:
            case GenIssGrp:
            case GenIssFlashStart:
            case GenIssFlashStartUpd:
            case GenIssFinst:
               out_file << ProdName;
               break;
            case GenIssCli:
               out_file << ProdName << " + \' ";
                  out_file << GENISS_PROD_LAN;
                  out_file << "\'";
               break;
            case GenIssFlash:
            case GenIssFlashUpd:
            case GenIssFlashUpdWhole:
//          case GenIssFlashStart:
//          case GenIssFlashStartUpd:
//                out_file << "GetProdNameRaw + \' ";
                  out_file << ProdName;
                  if((iProdType != KpMIKO) && (iProdType != KpSALT) && (iGenType != GenIssFlashUpd) && (iGenType != GenIssFlashUpdWhole))  
                  {
                     out_file << " + \' ";
                     out_file << GENISS_PROD_FLASH;
                     out_file << "\'";
                  }
               break;
            case GenIssChkVol:
//             out_file << "GetProdNameRaw + \' \' + GetVer + \'" << build_str << " "
               out_file << "GetProdNameRaw + \' \' + GetVer + \' ";
                  out_file << GENISS_PROD_FLASH;
                  out_file << "\'";
               break;
            case GenIssNet:
//             out_file << "GetProdNameRaw + \' ";
               out_file << ProdName << " + \' ";
                  out_file << GENISS_PROD_LAN;
                  out_file << "\'";
               break;
            case GenIssSvr:
//             out_file << "GetProdNameRaw + \' serveris\'";
               out_file << ProdName << " + \' ";
                  out_file << GENISS_PROD_SERVER;
                  out_file << "\'";
               break;
            }
            out_file << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdNameStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProdName;" << endl;
            out_file << "end;" << endl;
         }


// ---------------
//     type gen_iss_cod_cd_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_cd_upd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start_full.pas >> gen_cd.iss


         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssUpd:
         case GenIssUpdWhole:
            out_file << endl;
            out_file << endl;
            out_file << "function GetPrevVerName: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << PrevVerName << ";" << endl;
            out_file << "end;" << endl;

         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
         case GenIssSvr:
//          if((!PartialInstall) && (!PartialDir) && (iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) break;

            out_file << endl;
            out_file << endl;
            out_file << "function GetFirstVerName: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << FirstVerName << ";" << endl;
            out_file << "end;" << endl;

            break;
         }

//     type gen_iss_cod_cd_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_cd_upd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start_full.pas >> gen_cd.iss

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetVerName: String;" << endl;
            out_file << "begin" << endl;
         }
         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssGrp:
         case GenIssNet:
         case GenIssSvr:
         case GenIssFlash:
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssChkVol:
         case GenIssCli:
         case GenIssFinst:
            out_file << "Result := " << VerName << ";" << endl;
            break;
         case GenIssUpd:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssUpdWhole:
            out_file << "Result := " << UpdVerName << ";" << endl;
            break;
         }
         if(SUCCEEDED(retc))
         {
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetVerNameStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetVerName;" << endl;
            out_file << "end;" << endl;
         }


//     type gen_iss_cod.pas >> gen_cd.iss

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetProdFNameRaw(UseAccLetLoc: Boolean): String;" << endl;
            out_file << "var retv: String;" << endl;
            if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole)) out_file << "// ";
            if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType == GenIssFinst))
               out_file << "var group_name: String;" << endl;

            out_file << "begin" << endl;
            out_file << endl;

            if(ask_use_acc_let_flg)
            {
               out_file << "   if(not AccLetAsked) then" << endl;
               out_file << "   begin" << endl;
               out_file << "      AccLetAsked := True;" << endl;
               out_file << "      UseAccLet := (MsgBox(\'";
                  out_file << GENISS_MSG_NAT_LET; 
                  out_file << "\'," << endl;
               out_file << "         mbConfirmation, MB_YESNO) = IDYES );" << endl;
               out_file << "   end;" << endl;
               out_file << endl;
               
               strcpy(fname, prod_fname_raw);
               TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
               
               out_file << "   if(UseAccLet and UseAccLetLoc) then retv := " << fname /* prod_fname_raw */ << endl;
               out_file << "   else retv := " << TvStrLat(fname, TV_CPP_SOURCE_CTBL) << ";" << endl;
            }
            else
            {
               out_file << "   retv := " << prod_fname_raw << ";" << endl;
            }

            if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli))
            {
               out_file << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole))
                  out_file << "// Padubliuoti ir visiems buvusiems skirtingiems ProdName, ProdDir ir ProdGroup – kai diegiama ant virðaus" << endl;
               else
                  out_file << "// Jeigu keitësi ProdFName, ProdGroup ir diegiami ikonø atnaujinimai – padubliuoti ir visiems buvusiems skirtingiems ProdName, ProdDir ir ProdGroup" << endl;

//             strcpy(fname, ProdNameRaw);
//             DelHeadTailApost(fname);

               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + GetProdName + \'_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
//             out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\" << fname << "_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    \'Inno Setup: Icon Group\', group_name)) then" << endl;

               strcpy(fname, prod_fname_raw); // prod_dir);
               DelHeadTailApost(fname);
               TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);

               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " begin" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    if(group_name = \'" << Publisher << "\\" << fname << "\') then // èia senasis ProdGroup (su paukðèiukais)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "       retv := \'" << fname << "\' // èia senasis ProdFNameRaw (su paukðèiukais)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    else" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "       retv := \'" << TvStrLat(fname, TV_CPP_SOURCE_CTBL) << "\'; // èia senasis ProdFNameRaw (be paukðèiukø)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " end;" << endl;

               out_file << endl;
               strcpy(prname, ProdNameRaw);
               DelHeadTailApost(prname);
               
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\" << prname << "_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    \'Inno Setup: Icon Group\', group_name)) then" << endl;
               
               strcpy(fname, prod_fname_raw); // prod_dir);
               DelHeadTailApost(fname);
               TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);

               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " begin" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    if(group_name = \'" << Publisher << "\\" << fname << "\') then // èia senasis ProdGroup (su paukðèiukais)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "       retv := \'" << fname << "\' // èia senasis ProdFNameRaw (su paukðèiukais)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    else" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "       retv := \'" << TvStrLat(fname, TV_CPP_SOURCE_CTBL) << "\'; // èia senasis ProdFNameRaw (be paukðèiukø)" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " end;" << endl;
            }

            out_file << endl;
            out_file << "Result := retv;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdFName: String;" << endl;

            if(ask_use_acc_let_flg)
            {
               out_file << "var retv, prod_fname: String;" << endl;
               out_file << "begin" << endl;
               out_file << "   prod_fname := GetProdFNameRaw(True);" << endl; // fiktyviai, vien kad nustatytø UseAccLet
               out_file << endl;

               strcpy(fname, prod_fname);
               ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", (const unsigned char *)"GetProdFNameRaw(UseAccLet)", KP_MAX_FNAME_LEN);
               TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
               strcpy(fname_lat, fname);
               TvStrLat(fname_lat, TV_CPP_SOURCE_CTBL);

               out_file << "   if(UseAccLet) then retv := " << fname << endl;
               out_file << "   else retv := " << fname_lat << ";" << endl;
               out_file << endl;
               out_file << "Result := retv";
            }
            else
            {
               out_file << "begin" << endl;
               out_file << "Result := ";
               if(iGenType == GenIssChkVol) out_file << "FlashIdPage.Values[0] + \' \' + ";

               strcpy(fname, prod_fname);
               ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", (const unsigned char *)"GetProdFNameRaw(False)", KP_MAX_FNAME_LEN);

               out_file << fname;
               if(iGenType == GenIssChkVol)
               {
                  out_file << " + \' ";
                     out_file << GENISS_LINK_FLASH_CHK;
                     out_file << "\'";
               }
            }
            out_file << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdFNameStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProdFName;" << endl;
            out_file << "end;" << endl;
         }


// ---------------
//     type gen_iss_cod.pas >> gen_cd.iss


         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetProdDir: String;" << endl;
            if((PartialInstall || PartialDir) && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssNet) || (iGenType == GenIssSvr)))
            {
//             out_file << "var def_dir_name: String;" << endl;
               out_file << "begin" << endl;
//             out_file << "   if(not KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + GetFirstVerName + \'_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
//             out_file << "      \'Inno Setup: App Path\', def_dir_name)) then" << endl;
//             out_file << "   begin" << endl;
//             out_file << "      MsgBox(\'Programa „\' + GetFirstVerName + \'” dar neádiegta\', mbCriticalError, MB_OK);" << endl;
//             out_file << "      def_dir_name := ExpandConstant(\'{pf}\\" << Publisher << "\\\');" << endl;
//             out_file << "      def_dir_name := def_dir_name + " << prod_dir << ";" << endl;
//             out_file << "   end;" << endl;
//             out_file << endl;
//             out_file << "Result := def_dir_name;" << endl;
               out_file << "Result := sDefDirName;" << endl;
               out_file << "end;" << endl;
            }
            else
            {
               out_file << "var retv: String;" << endl;
               if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType==GenIssSvr) || (iGenType==GenIssFinst))
                  out_file << "var dir_name: String;" << endl;

               if(ask_use_acc_let_flg)
               {
                  out_file << "var prod_fname: String;" << endl;
                  out_file << "begin" << endl;
                  out_file << endl;
                  out_file << "   prod_fname := GetProdFNameRaw(True);" << endl; // fiktyviai, vien kad nustatytø UseAccLet
                  out_file << endl;
                  if(strchr(prod_dir, ':')) // ProdDir = 'C:\\arkim'
                     out_file << "   retv := \'\';" << endl;
                  else
                  {   
                     out_file << "   retv := ExpandConstant(\'";
                     if(RequireAdmin && (iGenType != GenIssSh) && (iGenType != GenIssCert)) out_file << "{pf}";
                     else out_file << "{userappdata}"; // "{commonappdata}"; // {localappdata}";
                     out_file << "\\\');" << endl;
                     out_file << endl;
         
                     strcpy(fname, Publisher);
                     TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
                     
                     out_file << "   if(UseAccLet) then retv := retv + \'" << fname /* Publisher */ << "\\\'" << endl;
                     out_file << "   else retv := retv + \'" << TvStrLat(fname, TV_CPP_SOURCE_CTBL) << "\\\';" << endl;
                  }
                  
                  out_file << endl;

                  strcpy(fname, prod_dir);
                  ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", 
                     (const unsigned char *)((strcmp(ExeFName, "XFS") == 0)?"GetProdFNameRaw(False)":"GetProdFNameRaw(UseAccLet)"), KP_MAX_FNAME_LEN);

                  TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
                  strcpy(fname_lat, fname);
                  TvStrLat(fname_lat, TV_CPP_SOURCE_CTBL);

                  out_file << "   if(UseAccLet) then retv := retv + " << fname << endl;
                  out_file << "   else retv := retv + " << fname_lat << ";" << endl;
               }
               else
               {
                  strcpy(fname, prod_dir);
                  ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", (const unsigned char *)"GetProdFNameRaw(False)", KP_MAX_FNAME_LEN);

                  if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole))
                  {
                     out_file << "begin" << endl;
                     out_file << endl;
                     if(strchr(prod_dir, ':')) // ProdDir = 'C:\\arkim'
                        out_file << "   retv := \'\';" << endl;
                     else   
                     {
                        out_file << "   retv := ExpandConstant(\'";
                        if(RequireAdmin && (iGenType != GenIssSh) && (iGenType != GenIssCert)) out_file << "{pf}";
                        else out_file << "{userappdata}"; // "{commonappdata}"; // {localappdata}";
                        out_file << "\\" << Publisher << "\\\');" << endl;
                     }
                     out_file << "   retv := retv + " << fname << ";" << endl;
                  }
                  else
                  {
                     out_file << "begin" << endl;
                     out_file << endl;
                     if(strchr(prod_dir, ':') || // ProdDir = 'C:\\arkim'
                        (iGenType == GenIssFlash) || (iGenType == GenIssFinst) || (iGenType == GenIssFlashUpd) || (iGenType == GenIssFlashUpdWhole) ||
                        (iGenType == GenIssFlashStart) || (iGenType == GenIssFlashStartUpd) || (iGenType == GenIssGrp)) 
                        out_file << "   retv := \'\';" << endl;
                     else   
                     {
                        out_file << "   retv := ExpandConstant(\'";
                        if(RequireAdmin && (iGenType != GenIssSh) && (iGenType != GenIssCert)) out_file << "{pf}";
                        else out_file << "{userappdata}"; // "{commonappdata}"; // {localappdata}";
                        out_file << "\\" << Publisher << "\\\');" << endl;
                     }
                     out_file << "   retv := retv + " << fname << ";" << endl;
                  }
               }

               if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType==GenIssSvr))
               {
                  out_file << endl;
                  if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole))
                     out_file << "// Padubliuoti su visais buvusiais ProdName – kai diegiama ant virðaus" << endl;
                  else
                     out_file << "// Jei keitësi ProdName, padubliuoti ir su visais buvusiais ProdName" << endl;
                  out_file << "   if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + GetProdName + \'_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
                  out_file << "      \'Inno Setup: App Path\', dir_name)) then retv := dir_name;" << endl;

                  out_file << endl;
//                strcpy(prname, ProdNameRaw);
//                DelHeadTailApost(prname);
                  out_file << "   if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\" << prname << "_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
                  out_file << "      \'Inno Setup: App Path\', dir_name)) then retv := dir_name;" << endl;
               }
               
               out_file << endl;
               out_file << "Result := retv";

               if(SUCCEEDED(retc)) switch(iGenType)
               {
               case GenIssCd:
               case GenIssSh:
               case GenIssCert:
               case GenIssFlash:
               case GenIssFlashUpd:
               case GenIssFlashUpdWhole:
               case GenIssFlashStart:
               case GenIssFlashStartUpd:
               case GenIssFinst:
                  break;
//             case GenIssFlash:
//             case GenIssFlashUpd:
//             case GenIssFlashUpdWhole:
//             case GenIssFlashStart:
//             case GenIssFlashStartUpd:
//                out_file << " + \' atmintuke\'";
//                break;
               case GenIssChkVol:
//                out_file << " + \' \' + GetVer + \'" << build_str << " ";
                  out_file << " + \' \' + GetVer + \' ";
                     out_file << GENISS_LINK_FLASH;
                     out_file << "\'";
                  break;
               case GenIssNet:
                  out_file << " + \' " << GENISS_LINK_LAN << "\'";
                  break;
               case GenIssSvr:
                  if(strchr(prod_dir, ':') == NULL)   // ProdDir = 'C:\\arkim'
                  {
                     out_file << " + \' ";
                        out_file << GENISS_LINK_SERVER;
                        out_file << "\'";
                  }
                  break;
               }
               out_file << ";" << endl;
               out_file << "end;" << endl;
            }

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdDirStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProdDir;" << endl;
            out_file << "end;" << endl;
         }

         if((iGenType != GenIssFlash) && (iGenType != GenIssFinst) && (iGenType != GenIssFlashUpd) && (iGenType != GenIssFlashUpdWhole) && 
            (iGenType != GenIssFlashStart) && (iGenType != GenIssFlashStartUpd) && (iGenType != GenIssGrp) &&
            SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetProdGroup: String;" << endl;
            out_file << "var retv: String;" << endl;
            if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole)) out_file << "// ";
            if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType==GenIssSvr) || (iGenType==GenIssFinst))
               out_file << "var group_name: String;" << endl;

            if(ask_use_acc_let_flg)
            {
               out_file << "var prod_fname: String;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   prod_fname := GetProdFNameRaw(True);" << endl; // fiktyviai, vien kad nustatytø UseAccLet
               out_file << endl;

               if(strchr(prod_dir, ':'))   // ProdDir = 'C:\\arkim'
                  out_file << "   retv := \'\';" << endl;
               else                       // ProdDir = GetProdFNameRaw
               {
                  strcpy(fname, Publisher);
                  TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
                  
                  out_file << "   if(UseAccLet) then retv := \'" << fname /* Publisher */ << "\\\'" << endl;
                  out_file << "   else retv := \'" << TvStrLat(fname, TV_CPP_SOURCE_CTBL) << "\\\';" << endl;
               }
               
               out_file << endl;
               
               strcpy(fname, prod_group);
               ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", (const unsigned char *)"GetProdFNameRaw(UseAccLet)", KP_MAX_FNAME_LEN);

               TvStrSpchLat(fname, TV_CPP_SOURCE_CTBL);
               strcpy(fname_lat, fname);
               TvStrLat(fname_lat, TV_CPP_SOURCE_CTBL);

               out_file << "   if(UseAccLet) then retv := retv + " << fname << endl;
               out_file << "   else retv := retv + " << fname_lat << ";" << endl;
            }
            else
            {
               out_file << "begin" << endl;
               out_file << endl;
               if(strchr(prod_dir, ':'))   // ProdDir = 'C:\\arkim'
                  out_file << "   retv := \'\';" << endl;
               else                       // ProdDir = GetProdFNameRaw
                  out_file << "   retv := \'" << Publisher << "\\\';" << endl;
               
               strcpy(fname, prod_group);
               ReplaceSubstr(fname, (const unsigned char *)"GetProdFNameRaw", (const unsigned char *)"GetProdFNameRaw(False)", KP_MAX_FNAME_LEN);

               out_file << "   retv := retv + " << fname << ";" << endl;
            }

            if((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole) || (iGenType == GenIssNet) || (iGenType == GenIssSvr) || (iGenType == GenIssCli) || (iGenType==GenIssSvr))
            {
//             strcpy(fname, ProdNameRaw);
//             DelHeadTailApost(fname);

               out_file << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole))
                  out_file << "// Padubliuoti ir visiems buvusiems skirtingiems ProdName – kai diegiama ant virðaus" << endl;
               else
                  out_file << "// Jeigu keitësi ProdName, ProdGroup ir diegiami ikonø atnaujinimai – padubliuoti ir visiems buvusiems skirtingiems ProdName" << endl;

               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + GetProdName + \'_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
//             if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "//"; else out_file << "  ";
//             out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\" << fname << "_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    \'Inno Setup: Icon Group\', group_name)) then retv := group_name;" << endl;

//             strcpy(prname, ProdNameRaw);
//             DelHeadTailApost(prname);

               out_file << endl;

               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << " if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\" << prname << "_is1\', // èia ávesti senàjá ProdName tekstà" << endl;
               if((iGenType != GenIssUpd) && (iGenType != GenIssUpdWhole)) out_file << "  "; else out_file << "//";
               out_file << "    \'Inno Setup: Icon Group\', group_name)) then retv := group_name;" << endl;
            }

            out_file << endl;
            out_file << "Result := retv";

            if(SUCCEEDED(retc)) switch(iGenType)
            {
            case GenIssCd:
            case GenIssSh:
            case GenIssCert:
            case GenIssFlash:
            case GenIssFlashUpd:
            case GenIssFlashUpdWhole:
            case GenIssFlashStart:
            case GenIssFlashStartUpd:
            case GenIssFinst:
               break;
//          case GenIssFlash:
//          case GenIssFlashUpd:
//          case GenIssFlashUpdWhole:
//          case GenIssFlashStart:
//          case GenIssFlashStartUpd:
//             out_file << " + \' ";
//                out_file << GENISS_LINK_FLASH;
//                out_file << "\'";
//             break;
            case GenIssChkVol:
//             out_file << " + \' \' + GetVer + \'" << build_str << " ";
               out_file << " + \' \' + GetVer + \' ";
                  out_file << GENISS_LINK_FLASH;
                  out_file << "\'";
               break;
            case GenIssNet:
               out_file << " + \' " << GENISS_LINK_LAN << "\'";
               break;
            case GenIssSvr:
               if(strchr(prod_dir, ':') == NULL)   // ProdDir = 'C:\\arkim'
                  out_file << " + \' " << GENISS_LINK_SERVER << "\'";
               break;
            }
            out_file << ";" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProdGroupStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProdGroup;" << endl;
            out_file << "end;" << endl;
         }

         if(SUCCEEDED(retc))
         {
//          if(ask_use_acc_let_flg)
            if(iGenType==GenIssSvr)
            {
               out_file << endl;
               out_file << endl;
               out_file << "function GetCleanIconNameStr(Param: String): String;" << endl;
               out_file << "var retv, prod_fname: String;" << endl;
               out_file << "begin" << endl;
               out_file << "   prod_fname := GetProdFNameRaw;" << endl; // fiktyviai, vien kad nustatytø UseAccLet
               out_file << endl;
               out_file << "   if(UseAccLet) then retv := \'" << GENISS_LINK_CLEAN_NAT << "\'" << endl;
               out_file << "   else retv := \'" << GENISS_LINK_CLEAN_LAT << "\';" << endl;
               out_file << endl;
               out_file << "Result := retv;" << endl;
               out_file << "end;" << endl;
            }

            if(startsel_exe_exists)
            {
               out_file << endl;
               out_file << endl;
               out_file << "function GetSendDiagMsgIconNameStr(Param: String): String;" << endl;
               out_file << "var retv, prod_fname: String;" << endl;
               out_file << "begin" << endl;
               if(ask_use_acc_let_flg)
               {
                  out_file << "   prod_fname := GetProdFNameRaw(True);" << endl; // fiktyviai, vien kad nustatytø UseAccLet
                  out_file << endl;
                  out_file << "   if(UseAccLet) then retv := \'" << GENISS_LINK_DIAG_MSG_NAT << "\'" << endl;
                  out_file << "   else retv := \'" << GENISS_LINK_DIAG_MSG_LAT << "\';" << endl;
               }
               else out_file << "   retv := \'" << GENISS_LINK_DIAG_MSG_LAT << "\';" << endl;
               out_file << endl;
               out_file << "Result := retv;" << endl;
               out_file << "end;" << endl;
            }
            
            out_file << endl;
            out_file << endl;
            out_file << "function GetProjID: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'" << ProjID << "\';" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetProjIDStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetProjID;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetPdfFName: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'" << StartPDF << "\';" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetExeFName: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := \'";
            if(iGenType == GenIssChkVol) out_file << "chkvol";
            else out_file << ExeFName;
            out_file << "\';" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetExeFNameStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetExeFName;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetIconFNameStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << IconFName << ";" << endl;
            out_file << "end;" << endl;

            if(iGenType == GenIssSvr)
            {
               out_file << endl;
               out_file << endl;
               out_file << "function GetSvrFName: String;" << endl;
               out_file << "begin" << endl;
               out_file << "Result := \'" << SvrFName << "\';" << endl;
               out_file << "end;" << endl;

               out_file << endl;
               out_file << endl;
               out_file << "function GetSvrFNameStr(Param: String): String;" << endl;
               out_file << "begin" << endl;
               out_file << "Result := GetSvrFName;" << endl;
               out_file << "end;" << endl;
            }

//          out_file << endl;
//          out_file << endl;
//          out_file << "function GetSetupFNameStr: String;" << endl;
//          out_file << "begin" << endl;
//          out_file << "Result := " << setup_fname << ";" << endl;
//          out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetUpdNum: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := " << UpdNum << ";" << endl;
            out_file << "end;" << endl;
         }



//     type gen_iss_cod_cd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start.pas >> gen_cd.iss

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssCli:
         case GenIssNet:
         case GenIssSvr:
//       case GenIssFlash:
            out_file << endl;
            out_file << endl;
            out_file << "function GetAppPath: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := ExpandConstant(\'{app}\');" << endl;
            out_file << "end;" << endl;
            break;

         case GenIssGrp:
            out_file << endl;
            out_file << endl;
            out_file << "function GetAppPath: String;" << endl;
            out_file << "var retv: String;" << endl;
            out_file << "begin" << endl;
            out_file << "   retv := ExpandConstant(\'{tmp}\');" << endl;
            out_file << "   retv := retv + \'\\\' + GetProdDir;" << endl;
            out_file << "Result := retv;" << endl;
            out_file << "end;" << endl;
            break;

         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFlash:
         case GenIssFinst:
            out_file << endl;
            out_file << endl;
            out_file << "function GetAppPath: String;" << endl;
            out_file << "var path: String;" << endl;
            out_file << "var disk: Integer;" << endl;
            out_file << "var found: Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << endl;
            out_file << "   if(not bAppPathCalculated) then" << endl;
            out_file << "   begin" << endl;
            out_file << "      found := False;" << endl;
            out_file << endl;
            out_file << "      while not found do" << endl;
            out_file << "      begin" << endl;
            out_file << "         for disk := 0 to 25 do" << endl;
            out_file << "         begin" << endl;
            out_file << "            path := Chr(65 + disk) + \':\';" << endl;
            out_file << "            if(FileExists(path + \'\\\' + GetExeFName + \'.ini\')) then" << endl;
            out_file << "            begin" << endl;
            out_file << "               found := True;" << endl;
            out_file << "               sAppPath := path;" << endl;
            out_file << "               bAppPathCalculated := True;" << endl;
            out_file << "               break;" << endl;
            out_file << "            end;" << endl;
            out_file << "         end;" << endl;
            out_file << endl;
            out_file << "         if(not found) then" << endl;
            out_file << "         begin" << endl;
            out_file << "            if(MsgBox(\'" << GENISS_INSERT_FLASH_KEY << "\' + GetProdNameRaw, mbError, MB_OKCANCEL) = IDCANCEL) then Abort;" << endl;
            out_file << "         end;" << endl;
            out_file << "      end;" << endl;
            out_file << endl;
            out_file << "   end;" << endl;
            out_file << endl;
            out_file << "Result := sAppPath;" << endl;
            out_file << "end;" << endl;
            break;

         case GenIssFlashStart:
         case GenIssFlashStartUpd:
            out_file << endl;
            out_file << endl;
            out_file << "function GetAppPath: String;" << endl;
            out_file << "begin" << endl;
//          out_file << "   Result := ExpandConstant(\'{drive:{srcexe}}\\\' + GetProdDir);" << endl;
//          out_file << "   Result := ExpandConstant(\'{drive:{srcexe}}\');" << endl;
//          out_file << "   Result := ExpandConstant(\'.\');" << endl;
            out_file << "// Result := ExpandConstant(\'{src}\\\' + GetProdDir);" << endl;
            out_file << "   Result := ExpandConstant(\'{src}\');" << endl;
            out_file << "end;" << endl;
            break;
         }

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "function GetAppPathStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetAppPath;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetLaunch: String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetAppPath + \'\\\' + ";
                if (iGenType == GenIssCert) out_file << "GetPdfFName;";
                else out_file << "GetExeFName + \'.exe\';";
            out_file << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "function GetLaunchStr(Param: String): String;" << endl;
            out_file << "begin" << endl;
            out_file << "Result := GetLaunch;" << endl;
            out_file << "end;" << endl;
         }

// ---------------
//     type gen_iss_cod.pas >> gen_cd.iss

         if(SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;
            out_file << "procedure CurStepChanged(CurStep: TSetupStep);" << endl;
            out_file << "begin" << endl;
            out_file << "   if(CurStep = ssPostInstall) then" << endl;
            out_file << "      bFinishedInstall := True;" << endl;
            out_file << "end;" << endl;
         }


//     type gen_iss_cod_macromedia.pas >> gen_cd.iss

         setup_file_name = (const unsigned char *)"Install Flash Player 7 AX.exe"; 
         ver_val = 7001400; // 7,0,14,0
         strcpy(check_fname, FnamePref[iGenType]);
         if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
         strcat(check_fname, "\\");
         strcat(check_fname, setup_file_name);
         in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
         if(in_file.fail() && SUCCEEDED(retc))
         {
            setup_file_name = (const unsigned char *)"install_flash_player_active_x.msi"; 
            ver_val = 9011500; // 9.0.115.0 // blogai - suveiks ir 9.1.15.0
            strcpy(check_fname, FnamePref[iGenType]);
            if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\");
            strcat(check_fname, setup_file_name);
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
         }

         if(!in_file.fail() && SUCCEEDED(retc))
         {
            switch(iGenType)
            {
            case GenIssCd:
            case GenIssSh:
            case GenIssCert:
            case GenIssUpd:
            case GenIssUpdWhole:
            case GenIssFlashStart:
            case GenIssFlashStartUpd:
            case GenIssNet:
            case GenIssCli:
               out_file << endl;
               out_file << endl;
               out_file << "procedure CheckMacromediaPlayer;" << endl;
               out_file << "var retv: Integer;" << endl;
               out_file << "var flash_vers: String;" << endl;
               out_file << "var ii: Integer;" << endl;
               out_file << "var st: Integer;" << endl;
               out_file << "var ver: Integer;" << endl;
               out_file << "var win_ver_rec: TWindowsVersion;" << endl;
               out_file << "var win_ver: Integer;" << endl;
               out_file << "begin" << endl;
               out_file << "// -------------------- check flash player version" << endl;
//             out_file << "//     \"6,0,22,0\" - \"Macromedia_Flash_Player_9/Install Flash Player 6 AX.exe\"" << endl;
//             out_file << "// >>> \"7,0,14,0\" - \"Macromedia_Flash_Player_9/Install Flash Player 7 AX.exe\"" << endl;
//             out_file << "//     \"8.0.22.0\" - Macromedia_Flash_Player_9/swflash[1]/GetFlash.exe" << endl;
//             out_file << "//     \"8.0.24.0\" - buvo mano Win98" << endl;
//             out_file << "//     \"9.0.0.0\"  - is AcroReader\'io tiesiai per IE http://www.adobe.com/shockwave/download/download.cgi?P1_Prod_Version=ShockwaveFlash&P5_Language=English" << endl;
               out_file << "   flash_vers := \'0.0.0.0\';" << endl;
               out_file << "   if(not KpRegSoftQueryStringValue(\'Microsoft\\Active Setup\\Installed Components\\{D27CDB6E-AE6D-11CF-96B8-444553540000}\'," << endl;
               out_file << "      \'Version\', flash_vers)) then flash_vers := \'0.0.0.0\';" << endl;
               out_file << endl;
               out_file << "   st := 1;" << endl;
               out_file << "   ver := 0;" << endl;
               out_file << "   for ii := 1 to Length(flash_vers) do" << endl;
               out_file << "   begin" << endl;
               out_file << "      if(flash_vers[ii] = \',\') then flash_vers[ii] := \'.\';" << endl;
               out_file << "      if(flash_vers[ii] = \'.\') then" << endl;
               out_file << "      begin" << endl;
               out_file << "         ver := ver*100 + StrToIntDef(Copy(flash_vers, st, ii-st), 0);" << endl;
               out_file << "         st := ii+1;" << endl;
               out_file << "      end;" << endl;
               out_file << "   end;" << endl;
               out_file << "   ver := ver*100 + StrToIntDef(Copy(flash_vers, st, ii-st), 0);" << endl;
               out_file << "   if(ver > 0) then while ver < 1000000 do ver := ver*100;" << endl;
               out_file << endl;
//             out_file << "   MsgBox(flash_vers, mbInformation, MB_OK);" << endl;
//             out_file << "   MsgBox(IntToStr(ver), mbInformation, MB_OK);" << endl;
               out_file << endl;


// dar tikrint ir failo C:\WINNT\system32\Macromed\Flash\Flash.ocx datà, jei diegiam ver_val = 7001400, o Flash.ocx naujesnis negu 2003.09.04, tada nereikia


               if(ver_val <= 7001400)
               {
                  out_file << "   GetWindowsVersionEx(win_ver_rec);" << endl;
                  out_file << "   win_ver := win_ver_rec.Major * 10000 + win_ver_rec.Minor * 100 + win_ver_rec.ServicePackMajor;" << endl;
                  out_file << endl;
//                out_file << "   MsgBox(Format(\'Major: %d Minor: %d Build: %d ServicePackMajor: %d ServicePackMinor: %d NTPlatform: %d ProductType: %x SuiteMask: %x\', [win_ver_rec.Major, win_ver_rec.Minor, win_ver_rec.Build, win_ver_rec.ServicePackMajor, win_ver_rec.ServicePackMinor, win_ver_rec.NTPlatform, win_ver_rec.ProductType, win_ver_rec.SuiteMask]), mbError, MB_OK);" << endl;
//                out_file << "   MsgBox(Format(\'ProductType: VER_NT_WORKSTATION: %x VER_NT_DOMAIN_CONTROLLER: %x VER_NT_SERVER: %x\', [VER_NT_WORKSTATION, VER_NT_DOMAIN_CONTROLLER, VER_NT_SERVER]), mbError, MB_OK);" << endl;
//                out_file << "   MsgBox(Format(\'SuiteMask: VER_SUITE_BACKOFFICE: %x VER_SUITE_BLADE: %x VER_SUITE_DATACENTER: %x VER_SUITE_ENTERPRISE: %x VER_SUITE_EMBEDDEDNT: %x VER_SUITE_PERSONAL: %x VER_SUITE_SINGLEUSERTS: %x VER_SUITE_SMALLBUSINESS: %x VER_SUITE_SMALLBUSINESS_RESTRICTED: %x VER_SUITE_TERMINAL: %x\', [VER_SUITE_BACKOFFICE, VER_SUITE_BLADE, VER_SUITE_DATACENTER, VER_SUITE_ENTERPRISE, VER_SUITE_EMBEDDEDNT, VER_SUITE_PERSONAL, VER_SUITE_SINGLEUSERTS, VER_SUITE_SMALLBUSINESS, VER_SUITE_SMALLBUSINESS_RESTRICTED, VER_SUITE_TERMINAL]), mbError, MB_OK);" << endl;
//                out_file << endl;
//                out_file << "   if((GetWindowsVersion < 83954216) And (ver < 7001400)) then" << endl; // 83954216 =  $5010A28 =  WinXP v. 5.1.2600
                  out_file << "   if(((not win_ver_rec.NTPlatform) Or (win_ver < 50102)) And (ver < " << ver_val << ")) then" << endl; // 50102 = 5.1 SP2 = WinXP SP2
               }
               else
                  out_file << "   if(ver < " << ver_val << ") then" << endl;
               
               out_file << "   begin" << endl;
               out_file << "      MsgBox(\'" << GENISS_MSG_FLASH_PLAYER << "\', mbInformation, MB_OK);" << endl;

               if(strstr(setup_file_name, ".msi"))               
                  out_file << "      if(not Exec(\'msiexec.exe\', \'/i \"\' + GetAppPath + \'\\" << setup_file_name << "\"\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
               else
                  out_file << "      if(not Exec(GetAppPath + \'\\" << setup_file_name << "\', \'\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
               
               out_file << "      begin" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " " << setup_file_name << ", " << GENISS_MSG_RESTART_ADMIN << "\', mbError, MB_OK);" << endl;
               out_file << "      end;" << endl;
               out_file << "   end;" << endl;
               out_file << "end;" << endl;
               break;
            
            } // switch(iGenType)
            
            in_file.close();
         
         } // if(!in_file.fail() && SUCCEEDED(retc))

//  :: type gen_iss_cod_cabri.pas >> gen_cd.iss

         setup_file_name = (const unsigned char *)"Cabri3D_Plugin_200_Win.exe"; 
         strcpy(check_fname, FnamePref[iGenType]);
         if((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
         strcat(check_fname, "\\");
         strcat(check_fname, setup_file_name);

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssFlashStart:
         case GenIssFlashStartUpd:
         case GenIssNet:
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << endl;
               out_file << endl;
               out_file << "procedure CheckCabri;" << endl;
               out_file << "var cabri_vers: String;" << endl;
               out_file << "begin" << endl;
               out_file << "// -------------------- check Cabri 3D plugin for existence" << endl;
               out_file << "   cabri_vers := \'\';" << endl;
               out_file << "   if(not KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\cabrilog_cabri3d_plugin_20x_is1\'," << endl;
               out_file << "      \'DisplayName\', cabri_vers) then cabri_vers := \'\';" << endl;
               
               out_file << "   if(cabri_vers <> \'Cabri 3D Plug-in 2.0.0\') then" << endl;
               out_file << "   begin" << endl;
               out_file << "      MsgBox(\'" << GENISS_MSG_CABRI << "\', mbInformation, MB_OK);" << endl;
               out_file << "      if(not Exec(GetAppPath + \'\\Cabri3D_Plugin_200_Win.exe\', \'\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "      begin" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " Cabri3D_Plugin_200_Win.exe, " << GENISS_MSG_RESTART_ADMIN << "\', mbError, MB_OK);" << endl;
               out_file << "      end;" << endl;
               out_file << "   end;" << endl;
               out_file << "end;" << endl;

               in_file.close();
            }
            break;
         }


// ------------------
         if(SUCCEEDED(retc)) switch(iGenType)
         {
#if FALSE
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssNet:
         case GenIssSvr:
         case GenIssCli:
            if((!TvIsLatStr(prod_fname_raw)) || (!TvIsLatStr(prod_fname)) || (!TvIsLatStr(prod_dir) || (!TvIsLatStr(prod_group)))
            {
               out_file << endl;
               out_file << endl;
               out_file << "procedure InitializeWizard;" << endl;
               out_file << "begin" << endl;
               out_file << "   AccLetPage := CreateInputOptionPage(wpInfoBefore," << endl;
               out_file << "      \'" << GENISS_MSG_NAT_LET_TIT << "\', \'\'," << endl;
               out_file << "      \'" << GENISS_MSG_NAT_LET_MAIN << "\'," << endl;
               out_file << "      False, False);\'," << endl;
               out_file << "   AccLetPage.Add(\'" << GENISS_MSG_NAT_LET_PROMPT << "\');" << endl;
               out_file << "   AccLetPage.Values[0] := True;" << endl;
               out_file << "end;" << endl;
            }
            break; // case GenIssCd: etc.
#endif
         case GenIssChkVol:
            out_file << endl;
            out_file << endl;
            out_file << "procedure InitializeWizard;" << endl;
            out_file << "begin" << endl;
            out_file << "   FlashIdPage := CreateInputQueryPage(wpInfoBefore," << endl;
            out_file << "      \'" << GENISS_MSG_ATM_KOD_TIT << "\', \'\'," << endl;
            out_file << "      \'" << GENISS_MSG_ATM_KOD_MAIN << "\');" << endl;
            out_file << "   FlashIdPage.Add(\'" << GENISS_MSG_ATM_KOD_PROMPT << ":\', False);" << endl;
            out_file << "end;" << endl;

            break; // case GenIssChkVol:

         }

// ------------------

         if(ChkUpd && ((iGenType == GenIssCd) || (iGenType == GenIssSh) || (iGenType == GenIssCert) || (iGenType == GenIssNet) || (iGenType == GenIssCli) || (iGenType == GenIssFlashStartUpd) || (iGenType == GenIssFinst)) && SUCCEEDED(retc))
         {
            out_file << endl;
            out_file << endl;

            out_file << "procedure InitializeWizard;" << endl;
            if(iGenType == GenIssFlashStartUpd) out_file << "var ll: dword;" << endl;
            out_file << "begin" << endl;
            if(iGenType == GenIssFlashStartUpd)
            {
               out_file << "   ll := 1;" << endl;
               out_file << "   if(not KpRegSoftQueryDWordValue(\'TEV\\\' + GetProdVer, \'TestUpdates\', ll)) then ll := 1;" << endl;
               out_file << endl;
            }
            out_file << "   TestUpdPage := CreateInputOptionPage(wpInfoBefore," << endl;
            out_file << "      \'" << GENISS_MSG_CHK_UPD_TIT << "\', \'\'," << endl;
            out_file << "      \'" << GENISS_MSG_CHK_UPD_MAIN << "\'," << endl;
            out_file << "      False, False);" << endl;
            out_file << "   TestUpdPage.Add(\'" << GENISS_MSG_CHK_UPD_PROMPT << "\');" << endl;
            out_file << "   TestUpdPage.Values[0] := ";
            if(iGenType == GenIssFlashStartUpd) out_file << "(ll <> 0);";
            else out_file << "True;";
            out_file << endl;
            out_file << "end;" << endl;
         }


// ------------------
//     type gen_iss_cod_cd_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_cd_upd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_full.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start_full.pas >> gen_cd.iss

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssNet:
         case GenIssSvr:

            out_file << endl;
            out_file << endl;
            out_file << "function InitializeSetup: Boolean;" << endl;
//          if(PartialInstall || PartialDir) out_file << "var def_dir_name: String;" << endl;
            out_file << "var retw: Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << "   bFinishedInstall := False;" << endl;
            if(ask_use_acc_let_flg)
            {
               out_file << "   AccLetAsked := False;" << endl;
               out_file << "   UseAccLet := True;" << endl;
            }
            if(PartialInstall || PartialDir)
            {
//             out_file << "   def_dir_name := " << prod_dir << ";" << endl;
               out_file << "   sDefDirName := " << prod_dir << ";" << endl;
            }

            out_file << endl;
            out_file << "   retw := True;" << endl;

            out_file << endl;
            out_file << "   if(retw) then retw := KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'";
            if(iGenType == GenIssSvr) out_file << "Srv";
            out_file << KPST_PRODVER_REG_KEY_Installed << "\', 0, \'" << GENISS_MSG_INST_ADMIN << "\');";

            out_file << endl;
            if(PartialInstall || PartialDir)
            {
               out_file << "   if(retw) then" << endl;
               out_file << "      if(not KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + ";
               out_file << (PartialDir?"GetFirstVerName":"GetProdName");
               out_file << " + \'_is1\'," << endl;
//             out_file << "         \'Inno Setup: App Path\', def_dir_name)) then" << endl;
               out_file << "         \'Inno Setup: App Path\', sDefDirName)) then" << endl;
               out_file << "      begin" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_PROG_NOT_ISTALLED << "\', mbCriticalError, MB_OK);" << endl;
               out_file << "         retw := False;" << endl;
               out_file << "      end;" << endl;
               out_file << endl;
            }

            out_file << endl;
            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "procedure DeinitializeSetup;" << endl;
            out_file << "var retv: Integer;" << endl;
            out_file << "var retw: Boolean;" << endl;
            if (ChkUpd && (iGenType != GenIssSvr)) out_file << "var ll: Integer;" << endl;
            if (iGenType == GenIssCert) out_file << "var launch: String;" << endl;
            out_file << "begin" << endl;
            out_file << "   retw := True;" << endl;
            
            out_file << endl;
            out_file << "   if(bFinishedInstall) then" << endl;
            out_file << "   begin" << endl;

            in_file.open("files\\butord.mcl", ios_base::in | ios_base::binary);
            if(!in_file.fail() && (iGenType != GenIssSvr))
            {
               out_file << "      if(not Exec(GetAppPath + \'\\butord.bat\', \'\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " butord.bat\', mbError, MB_OK);" << endl;

               in_file.close();
            }

            if ((iGenType != GenIssSh) && (iGenType != GenIssCert))
            {
               strcpy(check_fname, FnamePref[iGenType]);
               strcat(check_fname, FnameSuff[GenIssSh]);
               strcat(check_fname, "\\registr.exe");
               in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
               if(!in_file.fail())
               {
                  out_file << endl;
                  out_file << "      if(not Exec(GetAppPath + \'\\registr.exe\', \'\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
                  out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " registr.exe\', mbError, MB_OK);" << endl;

                  in_file.close();
               }
            }

            if (iGenType == GenIssCert)
            {
                out_file << endl;
                out_file << "      if(not Exec(GetAppPath + \'\\Launcher.exe\', \'reg\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
                out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " Launcher.exe\', mbError, MB_OK);" << endl;
                out_file << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ProdName\', GetProdName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'Ver\', GetVer, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ProjID\', GetProjID, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ExeFName\', GetExeFName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ProdFName\', GetProdFName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ProdGroup\', ExpandConstant(\'{group}\'), \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'ProdDir\', GetAppPath, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'Launch\', GetLaunch, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'Uninst\', ExpandConstant(\'{uninstallexe}\'), \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << "      if(retw) then retw := KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'Installed\', GetUpdNum, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
                out_file << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cAlwaysTrustedForJavaScript\', \'t20\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cCrossdomain\', \'t15\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cDataInjection\', \'t19\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cExternalStream\', \'t16\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cFileAttachment\', \'t23\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cJavaScript\', \'t17\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cJavaScriptURL\', \'t21\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cMultiMedia\', \'t22\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cScriptInjection\', \'t18\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cSilentPrint\', \'t13\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Adobe\\Acrobat Reader\\9.0\\TrustManager\\cTrustedFolders\\cWeblink\', \'t14\', GetAppPath + \'\\\' + GetPdfFName);" << endl;
                out_file << endl;
                out_file << "      RegWriteStringValue(HKEY_CLASSES_ROOT, \'.tev\', \'\', \'tev_auto_file\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Classes\\.tev\', \'\', \'tev_auto_file\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.tev\\OpenWithList\', \'a\', \'AcroRd32.exe\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.tev\\OpenWithList\', \'MRUList\', \'a\');" << endl;
                out_file << "      RegWriteDWordValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.tev\\OpenWithProgids\', \'tev_auto_file\', 0);" << endl;
                out_file << "      RegWriteDWordValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\ApplicationAssociationToasts\', \'Applications\\AcroRd32.exe_.tev\', 0);" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.tev\\UserChoice\', \'Hash\', \'XpC8g74bfEk=\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.tev\\UserChoice\', \'ProgId\', \'Applications\\AcroRd32.exe\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\Roaming\\OpenWith\\FileExts\\.tev\\UserChoice\', \'Hash\', \'01gD+R2twrQ=\');" << endl;
                out_file << "      RegWriteStringValue(HKEY_CURRENT_USER, \'Software\\Microsoft\\Windows\\Roaming\\OpenWith\\FileExts\\.tev\\UserChoice\', \'ProgId\', \'Applications\\AcroRd32.exe\');" << endl;
                out_file << endl;
                out_file << "      if(RegQueryStringValue(HKEY_LOCAL_MACHINE, \'SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\AcroRd32.exe\', \'\', launch)) then" << endl;
                out_file << "         RegWriteStringValue(HKEY_CLASSES_ROOT, \'tev_auto_file\\Shell\\Open\\Command\', \'\', \'\"\' + launch + \'\" \"%1\"\');" << endl;
            }

//          out_file << endl;
//          out_file << "      if(not Exec(GetAppPath \'\\copy_ini.bat\'), GetAppPath, ExpandConstant(\'{src}\'), SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
//          out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " copy_ini.bat\', mbError, MB_OK);" << endl;

            if((iGenType==GenIssSvr) && SUCCEEDED(retc))
            {
               out_file << endl;
               out_file << "      if(not Exec(GetAppPath + \'\\kpstlsvi.exe\', \'0\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " kpstlsvi.exe\', mbError, MB_OK);" << endl;

               out_file << endl;
               out_file << "      RestartReplace(GetAppPath + \'\\\' + GetSvrFName + \'.e_e\', GetAppPath + \'\\\' + GetSvrFName + \'.exe');" << endl;
               out_file << "      RestartReplace(GetAppPath + \'\\Win2K\\srvany.e_e\', GetAppPath + \'\\Win2K\\srvany.exe\');" << endl;
               out_file << "      RestartReplace(GetAppPath + \'\\WinNT\\srvany.e_e\', GetAppPath + \'\\WinNT\\srvany.exe\');" << endl;
            }

            if(AutoRun && ((iGenType!=GenIssSvr) || (strcmp(ExeFName, SvrFName) != 0)) && SUCCEEDED(retc))
            {
               out_file << endl;
               out_file << "      RestartReplace(GetAppPath + \'\\\' + GetExeFName + \'.e_e\', GetAppPath + \'\\\' + GetExeFName + \'.exe\');" << endl;
            }

            if(SUCCEEDED(retc))
            {
               out_file << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ProdName << "\', GetProdName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_Ver << "\', GetVer, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ProjID << "\', GetProjID, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ExeFName << "\', GetExeFName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ProdFName << "\', GetProdFName, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ProdGroup << "\', ExpandConstant(\'{group}\'), \'"; // GetProdGroup))";
               out_file << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_ProdDir << "\', GetAppPath, \'"; // ExpandConstant(\'{app}\'), \'"; // ExpandConstant(\'{pf}\\\\TEV\\\\{code:GetProdDirStr}\'), \'";
               out_file << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_Launch << "\', GetLaunch, \'";
               out_file << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteStringValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_Uninst << "\', ExpandConstant(\'{uninstallexe}\'), \'";
               out_file << GENISS_MSG_INST_ADMIN << "\');" << endl;

               out_file << "      if(retw) then retw := KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'";
               if(iGenType==GenIssSvr) out_file << "Srv";
               out_file << KPST_PRODVER_REG_KEY_Installed << "\', GetUpdNum, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
            }
            
            if((iGenType != GenIssSvr) && SUCCEEDED(retc))
            {
               out_file << endl;
               retc = OutCheckMacroCabri(&out_file, GenIssFiles);
            }

            if(ChkUpd && (iGenType != GenIssSvr) && SUCCEEDED(retc)) retc = OutTestUpd(&out_file);

            if((iGenType != GenIssFinst) && SUCCEEDED(retc)) retc = OutSbInst(&out_file, iGenType);

            if(SUCCEEDED(retc))
            {
               out_file << "   end;" << endl;
               out_file << "end;" << endl;
            }
            break; // case GenIssCd: case GenIssSvr:

         case GenIssUpd:
         case GenIssUpdWhole:

            out_file << endl;
            out_file << endl;
            out_file << "function InitializeSetup: Boolean;" << endl;
            out_file << "var retw: Boolean;" << endl;
            out_file << "var def_dir_name: String;" << endl;
            out_file << "var upd_num: Integer;" << endl;
            out_file << "var upd_num_ask: Cardinal;" << endl;
            out_file << "begin" << endl;
            out_file << "   bFinishedInstall := False;" << endl;
            out_file << "   retw := True;" << endl;
            out_file << endl;
            out_file << "   upd_num := (-1);" << endl;
            out_file << "   if(KpRegSoftQueryDWordValue(\'TEV\\\' + GetProdVer," << endl;
            out_file << "      \'" << KPST_PRODVER_REG_KEY_Installed << "\', upd_num_ask)) then" << endl;
            out_file << "      begin" << endl;
            out_file << "         upd_num := upd_num_ask;" << endl;
            out_file << "      end" << endl;
            out_file << "      else" << endl;
            out_file << "      begin" << endl;
            out_file << "         upd_num := (-1);" << endl;
            out_file << "      end;" << endl;
            out_file << endl;
            out_file << "   if(upd_num < 0) then" << endl;
            out_file << "      if(KpRegSoftQueryStringValue(\'Microsoft\\Windows\\CurrentVersion\\Uninstall\\\' + GetProdName + \'_is1\'," << endl;
            out_file << "         \'Inno Setup: App Path\', def_dir_name)) then upd_num := 1;" << endl;
            out_file << endl;
            if(iGenType != GenIssUpdWhole) out_file << "   if(upd_num < GetPrevUpdNum) then" << endl;
            if(iGenType != GenIssUpdWhole) out_file << "   begin" << endl;
            if(iGenType != GenIssUpdWhole) out_file << "   ";
            out_file << "   if(upd_num < 1) then" << endl;
            if(iGenType == GenIssUpdWhole) out_file << "   begin" << endl;
            else out_file << "   ";
            out_file << "      MsgBox(\'" << GENISS_MSG_PROG_NOT_ISTALLED << "\', mbCriticalError, MB_OK)" << endl;
            if(iGenType != GenIssUpdWhole) out_file << "      else" << endl;
            if(iGenType != GenIssUpdWhole) out_file << "         MsgBox(\'" << GENISS_MSG_UPD_NOT_ISTALLED << "\', mbCriticalError, MB_OK);" << endl;
            out_file << endl;
            out_file << "      retw := False;" << endl;
            out_file << "   end;" << endl;
            out_file << endl;
            out_file << "   if(retw) then retw := KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'" << KPST_PRODVER_REG_KEY_Installed << "\', upd_num, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
            out_file << endl;
            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "procedure DeinitializeSetup;" << endl;
            out_file << "var retv: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << "   if(bFinishedInstall) then" << endl;
            out_file << "   begin" << endl;

            strcpy(check_fname, "files");
            strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\butord.mcl");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << "      if(not Exec(GetAppPath + \'\\butord.bat\', \'\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " butord.bat\', mbError, MB_OK);" << endl;
               out_file << endl;

               in_file.close();
            }

            out_file_name[0] = Nul;
            if( /* ((iGenType==GenIssUpd) || (iGenType==GenIssUpdWhole)) && */ SUCCEEDED(retc))
            {
               strcpy(out_file_name, FnamePref[iGenType]);
               switch(iGenType)
               {
               case GenIssUpd: strcat(out_file_name, FnameSuff[GenIssDel]); break;
               case GenIssUpdWhole: strcat(out_file_name, FnameSuff[GenIssDelWhole]); break;
               }
               strcat(out_file_name, ".txt");
               retc = AppendIssFile(&out_file, out_file_name);
               out_file << endl;
            }

            if(SUCCEEDED(retc))
            {
               out_file << "      KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'" << KPST_PRODVER_REG_KEY_Installed << "\', GetUpdNum, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
               out_file << endl;
            }

            if(SUCCEEDED(retc)) retc = OutCheckMacroCabri(&out_file, iGenType /* GenIssUpd, GenIssUpdWhole */);

            if(SUCCEEDED(retc)) retc = OutSbInst(&out_file, iGenType);

            if(SUCCEEDED(retc))
            {
               out_file << "   end;" << endl;
               out_file << "end;" << endl;
            }
            break; // case GenIssUpd: case GenIssUpdWhole:

         case GenIssCli:

            strcpy(check_fname, "files");
            strcat(check_fname, FnameSuff[GenIssCd]);
            strcpy(check_fname, "\\");
            strcat(check_fname, ExeFName); 
            strcat(check_fname, ".sdb"); 
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << endl;
               out_file << endl;
               out_file << "procedure DeinitializeSetup;" << endl;
               out_file << "var retv: Integer;" << endl;
               if(ChkUpd) out_file << "var ll: Integer;" << endl;
               out_file << "begin" << endl;
               out_file << "   if(bFinishedInstall) then" << endl;
               out_file << "   begin" << endl;

               if(ChkUpd && SUCCEEDED(retc)) retc = OutTestUpd(&out_file);

               if(SUCCEEDED(retc)) retc = OutCheckMacroCabri(&out_file, iGenType /* GenIssUpd, GenIssUpdWhole */);

               if(SUCCEEDED(retc)) retc = OutSbInst(&out_file, iGenType);

               if(SUCCEEDED(retc))
               {
                  out_file << "   end;" << endl;
                  out_file << "end;" << endl;
               }
            }
            break; // case GenIssCli:

         case GenIssFlash:
         case GenIssFlashUpd:
         case GenIssFlashUpdWhole:
         case GenIssFinst:

            out_file << endl;
            out_file << endl;
            out_file << "function InitializeSetup: Boolean;" << endl;
            out_file << "var retw: Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << "   bFinishedInstall := False;" << endl;
            if((iGenType == GenIssFlashUpd) || (iGenType == GenIssFlashUpdWhole) ||
                     (iGenType == GenIssFlash) || (iGenType == GenIssFinst))
            { 
               out_file << "   sAppPath := \'\';" << endl;
               out_file << "   bAppPathCalculated := False;" << endl;
            }
            out_file << endl;
            out_file << "   retw := True;" << endl;
            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "procedure DeinitializeSetup;" << endl;
            out_file << "var retv: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << "   if(bFinishedInstall) then" << endl;
            out_file << "   begin" << endl;

            strcpy(check_fname, "files");
            if((iGenType==GenIssFlashUpd) || (iGenType==GenIssFlashUpdWhole)) strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, "\\");
            pnts = prod_dir;
            if(*pnts == '\'') pnts++;
            strcat(check_fname, pnts);
            pntd = check_fname + strlen(check_fname) - 1;
            if(*pntd == '\'') *pntd = Nul;
            strcat(check_fname, "\\butord.bat");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << "      if(not Exec(GetAppPath + \'\\\' + GetProdDir + \'\\butord.bat\', \'\', GetAppPath + \'\\\' + GetProdDir, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " butord.bat\', mbError, MB_OK);" << endl;
               out_file << endl;

               in_file.close();
            }

            if (iGenType == GenIssFinst)
            {
               strcpy(check_fname, "files");
               strcat(check_fname, FnameSuff[iGenType]);
               strcat(check_fname, "\\");
               pnts = prod_dir;
               if(*pnts == '\'') pnts++;
               strcat(check_fname, pnts);
               pntd = check_fname + strlen(check_fname) - 1;
               if(*pntd == '\'') *pntd = Nul;
               strcat(check_fname, "\\registr.exe");
               in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
               if(!in_file.fail())
               {
                  out_file << endl;
                  out_file << "      if(not Exec(GetAppPath + \'\\\' + GetProdDir + \'\\registr.exe\', \'\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
                  out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " registr.exe\', mbError, MB_OK);" << endl;

                  in_file.close();
               }
            }

            out_file << "   end;" << endl;
            out_file << "end;" << endl;

            break; // case GenIssFlash:

         case GenIssFlashStart:
         case GenIssFlashStartUpd:

            out_file << endl;
            out_file << endl;
            out_file << "procedure RunExe;" << endl;
            out_file << "var retv: Integer;" << endl;
            out_file << "begin" << endl;

            in_file.open("files_flash\\copy_files.bat", ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               out_file << "   if(not Exec(GetAppPath + \'\\copy_files.bat\', \'\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "   begin" << endl;
               out_file << "      MsgBox(\'" << GENISS_MSG_UNSUCC_START << " copy_files.bat\', mbError, MB_OK);" << endl;
               out_file << "   end;" << endl;
               out_file << endl;

               in_file.close();
            }

            in_file.open("files_flash\\delete_files.bat", ios_base::in | ios_base::binary);

            out_file << "   if(not Exec(GetAppPath + \'\\\' + GetExeFName + \'.exe\', \'\', GetAppPath, SW_SHOW, ";
            if(!in_file.fail()) out_file << "ewWaitUntilTerminated";
            else out_file << "ewNoWait";
            out_file << ", retv)) then" << endl;
            out_file << "   begin" << endl;
            out_file << "      MsgBox(\'" << GENISS_MSG_UNSUCC_START << " \' + GetExeFName + \'.exe\', mbError, MB_OK);" << endl;
            out_file << "   end;" << endl;

            if(!in_file.fail())
            {
               out_file << endl;
               out_file << "   if(not Exec(GetAppPath + \'\\delete_files.bat\', \'\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "   begin" << endl;
               out_file << "      MsgBox(\'" << GENISS_MSG_UNSUCC_START << " delete_files.bat\', mbError, MB_OK);" << endl;
               out_file << "   end;" << endl;

               in_file.close();
            }

            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;

            dlls_ready = False;
            in_file.open("files\\AcroRead602\\Reader\\msvcp60.dll", ios_base::in | ios_base::binary);
            if(!in_file.fail())
            {
               dlls_ready = True;
               in_file.close();
            }

            files_flash_start_ready = False;
            strcpy(check_fname, (const unsigned char *)"files_flash_start.dir");
            in_file.open((const char *)check_fname, ios_base::in);
            if(!in_file.fail())
            {
               in_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
               if(in_file.eof()){}
               else
               {
                  if(in_file.fail())
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, check_fname, True, __FILE__, __LINE__, 0L);
                     break;
                  }
                  else files_flash_start_ready = True;
               }
               in_file.close();
            }

            in_file_open = False;
            fonts_ready = False;
            strcpy(check_fname, (const unsigned char *)"fonts.dir");
            in_file.open((const char *)check_fname, ios_base::in);
            if(!in_file.fail())
            {
               in_file_open = True;

               in_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
               if(in_file.eof()){}
               else
               {
                  if(in_file.fail())
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, check_fname, True, __FILE__, __LINE__, 0L);
                     break;
                  }
                  else fonts_ready = True;
               }
            }

            if(SUCCEEDED(retc))
            {
               out_file << "function InitializeSetup: Boolean;" << endl;
               out_file << "var retv: Integer;" << endl;
               out_file << "var retw: Boolean;" << endl;
               if(ChkUpd && (iGenType == GenIssFlashStartUpd)) out_file << "var ll: dword;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   bFinishedInstall := False;" << endl;
            }

            if(SUCCEEDED(retc)) if(ChkUpd && (iGenType == GenIssFlashStartUpd)) 
            {
               out_file << endl;
               out_file << "   KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'" << KPST_PRODVER_REG_KEY_Installed << "\', GetUpdNum, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;
            }
            
            if((dlls_ready || fonts_ready || files_flash_start_ready || (ChkUpd && (iGenType == GenIssFlashStartUpd))) && SUCCEEDED(retc))
            {
               out_file << endl;
               out_file << "   retw := True; // dll-ø/failø/fontø, tur but, dar nëra - paleisti pilnà paleidimà" << endl;
               out_file << endl;

               out_file << "   if(" << endl;

               if(ChkUpd && (iGenType == GenIssFlashStartUpd))
               {
                  out_file << "      KpRegSoftQueryDWordValue(\'TEV\\\' + GetProdVer, \'TestUpdates\', ll)";
                  if(dlls_ready || files_flash_start_ready || fonts_ready) out_file << " And";
                  out_file << endl;
               }
               
               if(dlls_ready)
               {
            // uþkomentuota, kad atmintuko paleidëjams nereikëtø admino, unicows.dll reikia tik Win98, o ten atmintukai ir ðiaip neveikia
                  out_file << "//    FileExists(ExpandConstant(\'{sys}\\msvcp60.dll\')) And" << endl;  
                  out_file << "//    FileExists(ExpandConstant(\'{sys}\\unicows.dll\')) And" << endl;
                  out_file << "      True";
                  if(files_flash_start_ready || fonts_ready) out_file << " And";
                  out_file << endl;
               }

               if(files_flash_start_ready)
               {
                  out_file << "      False";
                  if(fonts_ready) out_file << " And";
                  out_file << endl;
               }

               if(fonts_ready) while(SUCCEEDED(retc))
               {
                  retc = TvFnameSplit(disk, path, fname, ftype, in_str);

                  if(ftype[0]) out_file << "      FileExists(ExpandConstant(\'{fonts}\\" << fname << "." << ftype << "\'))";

                  in_file.getline((char *)in_str, KP_MAX_FILE_LIN_LEN);
                  if(in_file.eof())
                  {
                     out_file << endl;
                     break;
                  }
                  if(in_file.fail())
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, check_fname, True, __FILE__, __LINE__, 0L);
                     break;
                  }

                  if(ftype[0]) out_file << " And" << endl;
               }

               in_file.close();
               in_file_open = False;

               out_file << "     ) then" << endl;
               out_file << "   begin" << endl;
               out_file << endl;
               out_file << "// dll-ai/fontai jau yra, viskà darom jau èia" << endl;
               out_file << endl;

            } // if(fonts_ready && SUCCEEDED(retc))

            if(SUCCEEDED(retc)) retc = OutCheckMacroCabri(&out_file, GenIssFiles);
            out_file << endl;

            if(SUCCEEDED(retc)) out_file << "      RunExe;" << endl;
            out_file << endl;

            if(SUCCEEDED(retc))
               out_file << "      retw := False; // atsakymas neigiamas, kad nerodytø jokiø tolesniø dialogø, iðkart pasibaigtø" << endl;

            if((dlls_ready || files_flash_start_ready || fonts_ready) && SUCCEEDED(retc))
               out_file << "   end;" << endl;

            out_file << endl;

            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;

            if((dlls_ready || files_flash_start_ready || fonts_ready || (ChkUpd && (iGenType == GenIssFlashStartUpd))) && SUCCEEDED(retc))
            {
               out_file << endl;
               out_file << endl;
               out_file << "procedure DeinitializeSetup();" << endl;
               out_file << "var retv: Integer;" << endl;
               if(ChkUpd && (iGenType == GenIssFlashStartUpd)) out_file << "var ll: dword;" << endl;
               out_file << "begin" << endl;
               out_file << endl;
               out_file << "   if(bFinishedInstall) then" << endl;
               out_file << "   begin" << endl;
               out_file << endl;

               retc = OutCheckMacroCabri(&out_file, GenIssFiles);

               if(SUCCEEDED(retc)) out_file << endl;

               if(ChkUpd && (iGenType == GenIssFlashStartUpd) && SUCCEEDED(retc))
               { 
                  out_file << "      if(not KpRegSoftQueryDWordValue(\'TEV\\\' + GetProdVer, \'TestUpdates\', ll)) then" << endl;
                  out_file << "      begin" << endl;

//                retc = OutTestUpd(&out_file);
                  out_file << "         ll := 1;" << endl;
                  out_file << "         if(not TestUpdPage.Values[0]) then ll := 0;" << endl;
                  out_file << "         KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'TestUpdates\', ll, \'" << GENISS_MSG_INST_ADMIN << "\');" << endl;

                  out_file << "      end;" << endl;
                  out_file << endl;
               }

               if(SUCCEEDED(retc)) out_file << "      RunExe;" << endl;

               if(SUCCEEDED(retc))
               {
                  out_file << endl;
                  out_file << "   end;" << endl;
                  out_file << "end;" << endl;
               }

            } // if(fonts_ready && SUCCEEDED(retc))


            if(in_file_open) in_file.close();
            in_file_open = False;

            break; // case GenIssFlashStart:

         case GenIssGrp:
            out_file << endl;
            out_file << endl;
            out_file << "function InitializeSetup: Boolean;" << endl;
            out_file << "var retw: Boolean;" << endl;
//          out_file << "var retv: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << endl;
            out_file << "   bFinishedInstall := False;" << endl;
            out_file << endl;
#if FALSE            
            out_file << "   if(not Exec(GetAppPath + \'\\setup.exe\', \'\', GetAppPath, SW_SHOW, ewNoWait, retv)) then" << endl;
            out_file << "   begin" << endl;
            out_file << "      MsgBox(\'" << GENISS_MSG_UNSUCC_START << " setup.exe\', mbError, MB_OK);" << endl;
            out_file << "   end;" << endl;
#endif
            out_file << "   retw := True; // False; // atsakymas neigiamas, kad nerodytø jokiø tolesniø dialogø, iðkart pasibaigtø" << endl;
            out_file << endl;

            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;

            out_file << endl;
            out_file << endl;
            out_file << "procedure DeinitializeSetup;" << endl;
            out_file << "var retv: Integer;" << endl;
            out_file << "begin" << endl;
            out_file << "   if(bFinishedInstall) then" << endl;
            out_file << "   begin" << endl;
            out_file << "      if(not Exec(GetAppPath + \'\\setup.exe\', \'\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
            out_file << "      begin" << endl;
            out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " setup.exe\', mbError, MB_OK);" << endl;
            out_file << "      end;" << endl;
            out_file << "   end;" << endl;
            out_file << "end;" << endl;

            break; // case GenIssGrp

         }

// -----------------------------
//     type gen_iss_cod_cd.pas >> gen_cd.iss
//  :: type gen_iss_cod_flash_start.pas >> gen_cd.iss

         if(SUCCEEDED(retc)) switch(iGenType)
         {
         case GenIssCd:
         case GenIssSh:
         case GenIssCert:
         case GenIssUpd:
         case GenIssUpdWhole:
         case GenIssNet:
         case GenIssSvr:
            out_file << endl;
            out_file << endl;
            out_file << "function InitializeUninstall: Boolean;" << endl;

            strcpy(check_fname, FnamePref[iGenType]);
            
//          if((iGenType == GenIssUpd) || (iGenType == GenIssUpdWhole)) strcat(check_fname, FnameSuff[GenIssCd]);
//          else strcat(check_fname, FnameSuff[iGenType]);
            strcat(check_fname, FnameSuff[GenIssSh]);
                               
            strcat(check_fname, "\\unreg.exe");
            in_file.open((const char *)check_fname, ios_base::in | ios_base::binary);
            if((!in_file.fail()) || (iGenType==GenIssCert) || (iGenType==GenIssSvr))
               out_file << "var retv: Integer;" << endl;

            out_file << "var retw: Boolean;" << endl;
            out_file << "begin" << endl;
            out_file << endl;
            out_file << "   retw := True;" << endl;

            out_file << endl;
            out_file << "   if(retw) then retw := KpRegSoftWriteDWordValue(\'TEV\\\' + GetProdVer, \'";
            if(iGenType == GenIssSvr) out_file << "Srv";
            out_file << KPST_PRODVER_REG_KEY_Installed << "\', 0, \'" << GENISS_MSG_UNINST_ADMIN << "\');";

            out_file << endl;
            if(!in_file.fail())
            {
               out_file << endl;
               out_file << "   if(retw) then" << endl;
               out_file << "      if(not Exec(GetAppPath + \'\\unreg.exe\', \'";
               if(iGenType == GenIssSh) out_file << "/SILENT";
               out_file << "\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " unreg.exe\', mbError, MB_OK);" << endl;

               in_file.close();
            }

            if (iGenType==GenIssCert)
            {
               out_file << endl;
               out_file << "// if(retw) then" << endl;
               out_file << "      if(not Exec(GetAppPath + \'\\Launcher.exe\', \'unreg\', GetAppPath, SW_SHOW, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'Nepavyko paleisti failo Launcher.exe\', mbError, MB_OK);" << endl;
            }
            
            if(iGenType==GenIssSvr)
            {
               out_file << endl;
               out_file << "   if(retw) then" << endl;
               out_file << "      if(not Exec(GetAppPath + \'\\kpstlsvu.exe\', \'\', GetAppPath, SW_SHOWMINIMIZED, ewWaitUntilTerminated, retv)) then" << endl;
               out_file << "         MsgBox(\'" << GENISS_MSG_UNSUCC_START << " kpstlsvu.exe\', mbError, MB_OK);" << endl;
            }

            if(iGenType==GenIssSvr)
            {
               out_file << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\\' + GetSvrFName + \'.exe\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\\' + GetSvrFName + \'.url\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\Win2K\\srvany.exe\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\WinNT\\srvany.exe\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\Win2K\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\WinNT\', \'\');" << endl;
               out_file << "   RestartReplace(GetAppPath, \'\');" << endl;
            }

            if(AutoRun && (iGenType!=GenIssUpd) && (iGenType!=GenIssUpdWhole) && ((iGenType!=GenIssSvr) || (strcmp(ExeFName, SvrFName) != 0)))
            {
               out_file << endl;
               out_file << "   RestartReplace(GetAppPath + \'\\\' + GetExeFName + \'.exe\', \'\');" << endl;
            }

            out_file << endl;
            out_file << "Result := retw;" << endl;
            out_file << "end;" << endl;
            break;
         }

         if((out_file.fail() || out_file.eof()) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, out_file_name, True, __FILE__, __LINE__, 0L);

         out_file.close();
//       if(out_file.close() == NULL)
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_ERROR, out_file_name, True, __FILE__, __LINE__, 0L);

      } // if(SUCCEEDED(retc)) // if(!out_file.fail())

   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT OutputKpstartIni(const unsigned char *lpszIniFName)
{
HRESULT retc = S_OK;
static unsigned char str_buf[KP_MAX_FNAME_LEN + GEN_CSS_STR_PAR_LEN + 100];
int prod_ver;

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(lpszIniFName, E_INVALIDARG, null, True);
// KP_ASSERT(KP_MAX_FNAME_LEN >= GEN_CSS_STR_PAR_LEN, KP_E_BUFFER_OVERFLOW, null, True);

// ------------------------------ iðsaugojam senà
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszIniFName);
      strcat(str_buf, ".sav");
      CopyFile((const char *)lpszIniFName, (const char *)str_buf, True);
   }
      
// ----------------------------------------
   strcpy(str_buf, ProdNameRaw);
   DelHeadTailApost(str_buf);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniProdName(str_buf);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPublisher(Publisher);

   str_buf[0] = Nul;
   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_cd")) strcpy(str_buf, ProdVer);   
      else if(strstr(lpszIniFName, "_net")) strcpy(str_buf, ProdVerNet);   
      else strcpy(str_buf, ProdVerFlash);   
   }
   DelHeadTailApost(str_buf);
   sscanf((const char *)str_buf, "%d", &prod_ver);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniProdVer(prod_ver);
   
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniVolName(ExeFName);

   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_tux") == null) // registr.exe reikia naudoti kpstart_cd.ini, ne kpstart_tux_cd.ini – pagal paleidimo komandà jis kurs registro raktus
      {
         str_buf[0] = Nul;
         if ((strstr(lpszIniFName, "_flash") != null) || (strstr(lpszIniFName, "_finst") != null))
            strcat(str_buf, "..\\");

// -------------------------         
unsigned char acro_path[KP_MAX_FNAME_LEN + 1];          
         strcpy(acro_path, "files\\");
         
         if(strstr(lpszIniFName, "_flash") != null)
         {
            strcpy(acro_path, ExeFName);
            strcat(acro_path, "_atmintukas\\Output_flash\\");
         }

const unsigned char *acro_dir = null; 
#define NUM_OF_ACRO_DIR_VARS 4         
const unsigned char *acro_dir_vars[NUM_OF_ACRO_DIR_VARS] = 
{
   (const unsigned char *)"AcroRead602",
   (const unsigned char *)"AR6",
   (const unsigned char *)"AcroRead709",
   (const unsigned char *)"AR7"
};
         
// ----
         for(int ii = 0; (ii < NUM_OF_ACRO_DIR_VARS) && (acro_dir == null); ii++)
         {
unsigned char acro_path_full[KP_MAX_FNAME_LEN + 1];          
            strcpy(acro_path_full, acro_path); 
            strcat(acro_path_full, acro_dir_vars[ii]);
HANDLE test_dir = INVALID_HANDLE_VALUE;
            test_dir = CreateFile((const char *)acro_path_full, GENERIC_READ, FILE_SHARE_READ,
               0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
            if(test_dir != INVALID_HANDLE_VALUE)
            {
               acro_dir = acro_dir_vars[ii];
               CloseHandle(test_dir);
            }
         }

         if(acro_dir == null) acro_dir = acro_dir_vars[0];
         
         strcat(str_buf, acro_dir);
         
         strcat(str_buf, "\\Reader\\AcroRd32.");
         
         if ((strstr(lpszIniFName, "_flash") != null) || (strstr(lpszIniFName, "_finst") != null))
            strcat(str_buf, "bin");
         else 
            strcat(str_buf, "exe");
         
         strcat(str_buf, " /n/h ");
         
         if ((strstr(lpszIniFName, "_flash") != null) || (strstr(lpszIniFName, "_finst") != null))
         {
            strcat(str_buf, "{user}\\");

static unsigned char prname[KP_MAX_FNAME_LEN+1];
            strcpy(prname, ProdFNameRaw);
            DelHeadTailApost(prname);
            strcat(str_buf, prname);

            strcat(str_buf, "\\");
         }
         
         strcat(str_buf, "cd\\");
         KP_ASSERT(strlen(str_buf) + strlen(StartPDF) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc)) strcat(str_buf, StartPDF);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCmdStr(str_buf);
      }
      else retc = theKpStAppPtr->SetIniCmdStr((const unsigned char *)"");
   }

   if(SUCCEEDED(retc))
   { 
      if(strstr(lpszIniFName, "_tux") != null) retc = theKpStAppPtr->SetIniFindBut(True); // XFS-iniuose vadovëliuose yra paieðkos mygtukas
      else retc = theKpStAppPtr->SetIniFindBut(False);
   }

   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_tux") == NULL)
      {
         KP_ASSERT(strlen(Password) <= KP_KWD_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwd(Password);
      }
      else retc = theKpStAppPtr->SetIniPwd((const unsigned char *)"");
   }

   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_tux") == NULL)
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBmpFName(SplashBMP);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBitmapWdt(640);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBitmapHgt(480);
      }
      else
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBmpFName((const unsigned char *)"");
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBitmapWdt(0);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBitmapHgt(0);
      }
   }

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniHideBkmrks(True);

   if(SUCCEEDED(retc)) if(strstr(lpszIniFName, "_flash") != null)
   {
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniEboard(True);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniShowIE(True);
   }

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCiDirect(True);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCompIdMode(CidMode | ((strstr(lpszIniFName, "_sh") != null)?KPST_COMPID_BOLT:0));
   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_cd"))
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBound(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCheckFlash(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniLicFlash(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniRegURL(KPST_PRODREG_URL_INI);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniNumOfLics(0);
      }
      else if(strstr(lpszIniFName, "_flash"))
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBound(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCheckFlash(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniLicFlash(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniRegURL((const unsigned char *)"");
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniNumOfLics(0);
      }
      else if(strstr(lpszIniFName, "_finst"))
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBound(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCheckFlash(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniLicFlash(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniRegURL(KPST_PRODREG_URL_INI);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniNumOfLics(0);
      }
      else if(strstr(lpszIniFName, "_net"))
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniBound(True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniCheckFlash(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniLicFlash(False);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniRegURL((const unsigned char *)"127.0.0.1");
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniNumOfLics(10);
      }
   }

   if(SUCCEEDED(retc))
   {
      if(strstr(lpszIniFName, "_tux") == NULL)
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdWndName((const unsigned char *)"Password");
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdEdCtrl(5);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdOkBut(6);
      }
      else
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdWndName((const unsigned char *)"");
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdEdCtrl(0);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniPwdOkBut(0);
      }
   }

// ----------------------------------------
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(lpszIniFName);

return(retc);
}


// ------------------------------------
HRESULT GenXFS_XFS_hh(void)
{
HRESULT retc = S_OK;
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
fstream out_file;
static unsigned char str_buf[2 * GEN_CSS_STR_PAR_LEN + 1];

   strcpy(out_fname, GENISS_XFS_HH_FNAME);

   if(SUCCEEDED(retc)) retc = CreatePath(out_fname, True);

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_fname, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_fname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      out_file << "#ifndef TUX_FS_XFS_HH" << endl;
      out_file << "#define TUX_FS_XFS_HH" << endl;
      out_file << endl;
      out_file << "/*" << endl;
      out_file << "Changelog:" << endl;
      out_file << "  1.0.18:" << endl;
      out_file << "    * Idetas *.tmp failu kodavimas" << endl;
      out_file << endl;
      out_file << "  1.0.19:" << endl;
      out_file << "    * Idetas XFS_NULL_BINARY, leidziantis pakeisti null.exe pavadinima" << endl;
      out_file << "    * Pakeisti projekto settingai, kad nemestu konsoles" << endl;
      out_file << "    * Ideta galimybe keisti XFS.exe failo varda" << endl;
      out_file << "    * Pridetas \'/A \"scrollbar=0&statusbar=0&navpanes=0\"\' prie acrobato argumentu" << endl;
      out_file << "    * Pakeista lango XIPA lango antraste i XFS_WINDOW_TITLE" << endl;
      out_file << "    * Ideta ikona (XipaResource.rc)" << endl;
      out_file << endl;
      out_file << "  1.0.20:" << endl;
      out_file << "    * Logas perkeltas i %TEMP%\\XFS.log ir uzkoduotas" << endl;
      out_file << endl;
      out_file << "  1.0.21:" << endl;
      out_file << "    * I XPDF idetas setShowScrollbar; atjungtas navigacijos scrollbar\'as PDFams, kurie turi" << endl;
      out_file << "      daugiau negu 1 puslapi." << endl;
      out_file << "    * Idetas XFS_CLIPBOARD_GUARD, kuris jei #define\'intas, tai trins periodiskai kas 0.5 s" << endl;
      out_file << "      clipboarda." << endl;
      out_file << endl;
      out_file << "  1.0.22:" << endl;
      out_file << "    * Istaisytas txCreateFile, kad praleistu visus \"\\Device\" failu atidarymus native rezimu." << endl;
      out_file << "      Tai istaiso update & submitField bugus" << endl;
      out_file << "    * Integruoti TUX_SPLASH_FNAME ir TUX_SHOW_SCROLLBAR" << endl;
      out_file << "    * Idetas XFS_ENCRYPT_LOG, kuris nustato, ar koduoti logus" << endl;
      out_file << endl;
      out_file << "  1.0.23:" << endl;
      out_file << "    * BUGFIX: acrobatas nuluzta, antra karta iskvietus app.activeDocs" << endl;
      out_file << "    * BUGFIX: acrobatas budavo uzkillinamas, todel negaledavo nieko issaugoti i GLOB.JS" << endl;
      out_file << endl;
      out_file << "  1.0.24:" << endl;
      out_file << "    * BUGFIX: mapinami puslapiai roundinami iki 64K vietoj 4K; dabar veiks su win7 64 bit," << endl;
      out_file << "      atitinkamai pakeistas XFSTool, kad generuotu archyvus su 64K alignmentu" << endl;
      out_file << endl;
      out_file << "  1.0.25:" << endl;
      out_file << "    * BUGFIX: nutimas puslapiu roundinimas i 4K txMapViewOfSection funkcijoje" << endl;
      out_file << endl;
      out_file << "  1.0.26:" << endl;
      out_file << "    * Dumpinant stack trace, bus issvestas ir code dump." << endl;
      out_file << endl;
      out_file << "  1.0.27:" << endl;
      out_file << "    * Pakeistas unpatch mechanizmas (is memcpy i asm rep movsb)" << endl;
      out_file << "    * Logas papildytas su base-patch informacija" << endl;
      out_file << "    * Pataisytas code dump offsetas" << endl;
      out_file << endl;
      out_file << "  1.0.28:" << endl;
      out_file << "    * Papildomas thread-safety" << endl;
      out_file << endl;
      out_file << "  1.0.29:" << endl;
      out_file << "    * idetas visiems IcePatch globalus thread-lockas" << endl;
      out_file << endl;
      out_file << "  1.0.30:" << endl;
      out_file << "    * integruoti Mindaugo pakeitimai" << endl;
      out_file << "    * sutvarkytas temporary failu adresavimo mechanizmas" << endl;
      out_file << endl;
      out_file << "  1.0.31:" << endl;
      out_file << "    * idetas automatinis logu perkelimas is TEMP\\XFS.log ir USERPROFILE\\Desktop\\XFS.log" << endl;
      out_file << "    * idetas XFS_CRASH_TEST env kintamasis: jei jo reiksme TRUE (set XFS_CRASH_TEST=TRUE), tuomet" << endl;
      out_file << "      XFS pasileidimo metu nulus" << endl;
      out_file << endl;
      out_file << "  1.0.32:" << endl;
      out_file << "    * AcLayers.DLL ir AppHelp.DLL blokavimas" << endl;
      out_file << "    * sumerginti Mindaugo kalbiniai patchai" << endl;
      out_file << endl;
      out_file << "  1.0.33:" << endl;
      out_file << "    * idetas tinkamas 0x000006ba exceptiono handlinimas" << endl;
      out_file << endl;
      out_file << "  1.0.34:" << endl;
      out_file << "    * comodo firewall fix" << endl;
      out_file << endl;
      out_file << "  1.0.35:" << endl;
      out_file << "    * extra loggingas del image allocation" << endl;
      out_file << "    * praleidziami \\??\\IDE#, \\??\\MountPointManager ir \\??\\Storage# failai" << endl;
      out_file << endl;
      out_file << "  1.0.36:" << endl;
      out_file << "    * blacklistintas Avast snxhk.dll" << endl;
      out_file << endl;
      out_file << "  1.0.37:" << endl;
      out_file << "    * nauji DLL blacklistai" << endl;
      out_file << "    * nauji pass-through" << endl;
      out_file << endl;
      out_file << "  1.0.38:" << endl;
      out_file << "    * dumpinamas kodas ties EIP" << endl;
      out_file << endl;
      out_file << "  1.0.39:" << endl;
      out_file << "    * apsauga nuo parazitinu procesu" << endl;
      out_file << endl;
      out_file << "  1.0.40:" << endl;
      out_file << "    * pafixintas DLL unload kodas" << endl;
      out_file << endl;
      out_file << "  1.0.41:" << endl;
      out_file << "    * failu whitelist" << endl;
#if TRUE // FALSE // 2012.01.03 XFS 1.0.42 nepasileido su TAU51_ru, gráþau prie 1.0.41
      out_file << endl;
      out_file << "  1.0.42:" << endl;
      out_file << "    * pakeistas funkciju hook mechanizmas" << endl;
      out_file << "    * sumazintas handlu wrap skaicius" << endl;
      out_file << endl;
      out_file << "  1.0.43:" << endl;
      out_file << "    * isimti AcLayers.dll ir apphelp.dll is blacklist" << endl;
//    out_file << "    * AcLayers.dll ir AppHelp.dll iðimti ið DLL failø blacklisto" << endl;
      out_file << endl;
      out_file << "  1.0.44:" << endl;
      out_file << "    * i reference counteri idetas mutexas" << endl;
      out_file << endl;
      out_file << "  1.0.45:" << endl;
      out_file << "    * blacklistintas AhJsctNs.dll" << endl;
      out_file << "    * pataisytas stringu lyginimas txSetWindowText hooke" << endl;
      out_file << endl;
      out_file << "  1.0.46:" << endl;
      out_file << "    * langø iðkëlimas á virðø" << endl;
#endif
      out_file << "*/" << endl;
      out_file << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#include <tux/XTux.hh>" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
#if TRUE // FALSE // 2012.01.03 XFS 1.0.42 nepasileido su TAU51_ru, gráþau prie 1.0.41
      out_file << "#define XFS_EXE_VERSION             L\"1.0.46\"" << endl;
      out_file << "#define XFS_DLL_VERSION             L\"1.0.46\"" << endl;
#else
      out_file << "#define XFS_EXE_VERSION             L\"1.0.41\"" << endl;
      out_file << "#define XFS_DLL_VERSION             L\"1.0.41\"" << endl;
#endif
      out_file << "#define XFS_ENCRYPTION_KEY          0x"; 

//    out_file << "1122334455667788";
      strcpy(str_buf, ProdVer);   
      DelHeadTailApost(str_buf);
int mask = 0; 
      sscanf((const char *)str_buf, "%d", &mask);
      out_file.fill('0');
      out_file.setf(ios_base::right | ios_base::hex);
      for(int ii = 0; ii < 4; ii++)
      {
         out_file.width(4);
         out_file  /* << setw(4) */ << mask;
         mask = KpstRand(mask);
      }

      out_file << "LL" << endl;
      
      out_file << "#define XFS_ENCRYPT_LOG" << endl;
      out_file << "//#define XLangEng" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XFS_NULL_BINARY             L\"XFS_null.exe\"" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "//#define XFS_WINDOW_TITLE            L\"XFS \" XFS_EXE_VERSION" << endl;
      out_file << "//#define XFS_WINDOW_TITLE            L\"Matematika Tau. 5 klas\\x0117\"" << endl;

      strcpy(str_buf, ProdFNameRaw);
      DelHeadTailApost(str_buf);
      EncodeWideStr(str_buf, 2 * GEN_CSS_STR_PAR_LEN, LangToCtbl[iMsgLangOff]);
      out_file << "#define XFS_WINDOW_TITLE            L\"" << str_buf << "\"" << endl;
      
      out_file << "#define XFS_CLIPBOARD_GUARD" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XFS_MAX_PATH                4096" << endl;
      out_file << "/************************************************************* TX *************************************************************/" << endl;
      out_file << "/*                                                            XFS                                                             */" << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << endl;
      out_file << "#endif /* TUX_FS_XFS_HH */" << endl;

      out_file.close();
   }

return(retc);
}


HRESULT ScanXFS_XFS_hh(unsigned char *lpszXFSver)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char in_fname[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszXFSver != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(in_fname, GENISS_XFS_HH_FNAME);

      in_file.open((const char *)in_fname, ios_base::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, in_fname, True);
   }
   
   if(SUCCEEDED(retc))
   {
      while((!in_file.eof()) && SUCCEEDED(retc)) 
      {
unsigned char in_line[KP_MAX_FILE_LIN_LEN + 1];      
         in_file.getline(in_line, KP_MAX_FILE_LIN_LEN);
         if(in_file.eof()) break;
         KP_ASSERT(!in_file.fail(), KP_E_FERROR, in_fname, True);
         
         if(SUCCEEDED(retc))
         {
unsigned char *pnts = null;
            pnts = strchr(in_line, '.');
            if(pnts != null) pnts = strchr(pnts, '.');            
            if(pnts != null) pnts = strchr(pnts, ':');            
            if(pnts != null)
            {
               *pnts = Nul;
               CutInitTrailSpcs(in_line);
               strcpy(lpszXFSver, "XFS ");               
int len = strlen(lpszXFSver);
               KP_ASSERT(strlen(in_line) < GEN_CSS_STR_PAR_LEN - len, KP_E_BUFFER_OVERFLOW, null, False);                
               if(SUCCEEDED(retc))
               {
                  strncpy(lpszXFSver + len, in_line, GEN_CSS_STR_PAR_LEN - len);
                  lpszXFSver[GEN_CSS_STR_PAR_LEN] = Nul;
               }               
            }                           
         }
      }
      
      in_file.close();
   }
   
return(retc);
}


// ------------------------------------
HRESULT GenXFS_tux_core_hh(void)
{
HRESULT retc = S_OK;
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
fstream out_file;

   strcpy(out_fname, "tux_XFS\\include\\tux\\ipa\\tux_core.hh");

   if(SUCCEEDED(retc)) retc = CreatePath(out_fname, True);

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_fname, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_fname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      out_file << "#ifndef TUX_CORE_HH" << endl;
      out_file << "#define TUX_CORE_HH" << endl;
      out_file << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define TUX_ACRO							7 // Naudojam Acrobat Reader 7" << endl;
      out_file << "#define TUX_IO_MODE						0 // 1 == Tiesioginis I/O (flash)" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define TUX_PATH            	\"data\"" << endl;
      out_file << "#define TUX_1ST_PAGE        	\"" << StartPDF << "\"" << endl;
      out_file << "#define TUX_SPLASH_FNAME	\"" << SplashBMP << "\"" << endl;
      out_file << "#define TUX_SHOW_SCROLLBAR" << endl;
//    out_file << "#define TUX_SHOW_TOOLBAR" << endl;
      out_file << "#define TUX_FIND" << endl;
      out_file << "#define XIPA_ICON             10" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define TUX_PDF_CLASS       	XIPA_PROJECT \"::pdf\"" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XI_MENU             	100" << endl;
      out_file << "#define XI_MDI_BACKGROUND   	200" << endl;
      out_file << "#define XI_TOOLBAR_BITMAP   	300" << endl;
      out_file << "#define XI_1ST_MDI_CHILD    	10000" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XWM_COMMAND         	(WM_USER + 1)" << endl;
      out_file << "#define XWM_CLOSE       			(WM_USER + 2)" << endl;
      out_file << "#define XWM_CLOSE2       			(WM_USER + 4)" << endl;
      out_file << "#define XWM_PRINT							(WM_USER + 3)" << endl;
      out_file << "#define XCM_PAGALBA						2000" << endl;
      out_file << "#define XCM_APIE							2001" << endl;
      out_file << "#define XCM_NEC								2002" << endl;
      out_file << "#define XCM_VERSIJA						2003" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#if (TUX_IO_MODE == 1)" << endl;
      out_file << "	#define XREG_INTERFACE(x)		true" << endl;
      out_file << "#else" << endl;
      out_file << "	#define XREG_INTERFACE(x)		queryInterface()->x" << endl;
      out_file << "#endif /* (TUX_IO_MODE == 1) */" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << endl;
      out_file << "#ifdef __cplusplus" << endl;
      out_file << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << "typedef bool 									bool_t;" << endl;
      out_file << "typedef const bool 						cbool_t;" << endl;
      out_file << "typedef char 									*str_t;" << endl;
      out_file << "typedef const char 						*cstr_t;" << endl;
      out_file << "/************************************************************* TX *************************************************************/" << endl;
      out_file << "/*                                                        xexception_t                                                        */" << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << endl;
      out_file << "enum xexception_t" << endl;
      out_file << "{" << endl;
      out_file << "  xe_1st_page_not_found         = 0x01," << endl;
      out_file << "  xe_acrobat_init_failed        = 0x02," << endl;
      out_file << "  xe_main_reg_failed            = 0x03," << endl;
      out_file << "  xe_main_wnd_init_failed       = 0x04," << endl;
      out_file << "  xe_mdi_client_init_failed     = 0x05," << endl;
      out_file << "  xe_pdf_ctrl_init_failed       = 0x06," << endl;
      out_file << "  xe_pdf_reg_failed             = 0x07," << endl;
      out_file << "  xe_raise                      = 0xFF" << endl;
      out_file << "};" << endl;
      out_file << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << endl;
      out_file << "#endif /* __cplusplus */" << endl;
      out_file << "#endif /* TUX_CORE_HH */" << endl;

      out_file.close();
   }

return(retc);
}


// ------------------------------------
HRESULT GenXFS_Xipa_hh(void)
{
HRESULT retc = S_OK;
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
fstream out_file;

   strcpy(out_fname, "tux_XFS\\include\\tux\\ipa\\Xipa.hh");

   if(SUCCEEDED(retc)) retc = CreatePath(out_fname, True);

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_fname, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_fname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      out_file << "#ifndef TUX_IPA_XIPA_HH" << endl;
      out_file << "#define TUX_IPA_XIPA_HH" << endl;
      out_file << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#include <tux/XTux.hh>" << endl;
      out_file << "#include <tux/fs/XFS.hh>" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XIPA_PROJECT                L\"" << ProjID << "\"" << endl;
      out_file << "#define XIPA_VERSION                L\"2.0.17\"" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "#define XIPA_MAIN_WINDOW_CLASS      XIPA_PROJECT \".main\"" << endl;
      out_file << "//#define XIPA_WINDOW_TITLE           XIPA_PROJECT \" \" XIPA_VERSION" << endl;
      out_file << "#define XIPA_WINDOW_TITLE           XFS_WINDOW_TITLE" << endl;
      out_file << "#define XIPA_CONTROL_INTERFACE      XIPA_MAIN_WINDOW_CLASS" << endl;
      out_file << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
      out_file << "/************************************************************* TX *************************************************************/" << endl;
      out_file << "/*                                                            Xipa                                                            */" << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << endl;
      out_file << "/******************************************************************************************************************************/" << endl;
      out_file << endl;
      out_file << "#endif /* TUX_IPA_XIPA_HH */" << endl;

      out_file.close();
   }

return(retc);
}


// ------------------------------------
HRESULT GenXFS_XipaResource_rc(void)
{
HRESULT retc = S_OK;
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
fstream out_file;
static unsigned char str_buf[GEN_CSS_STR_PAR_LEN + 100];

   strcpy(out_fname, "tux_XFS\\src\\tux\\ipa\\XipaResource.rc");

   if(SUCCEEDED(retc)) retc = CreatePath(out_fname, True);

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_fname, ios_base::out);
      if(out_file.fail())
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, out_fname, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      out_file << "#include \"res_com.h\"" << endl;
      out_file << endl;   
      out_file << "KP_IDI_SETUP_ICON     ICON    DISCARDABLE     \"res/setup.ico\"" << endl;
      out_file << endl;   

      if(IconFName[0] == '\'')
      {
         strcpy(str_buf, IconFName);
         DelHeadTailApost(str_buf);
      }
      else
      {
         strcpy(str_buf, ProjID);
         strcat(str_buf, ".ico");
      }
      out_file << "10 ICON DISCARDABLE \"res/" << str_buf << "\"" << endl;

      out_file.close();
   }

return(retc);
}


// ------------------------------------
HRESULT GenXFSTool_cfg(void)
{
HRESULT retc = S_OK;
fstream out_file;
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char file_buf[sizeof(XFSTool_cfg_arr) + 1000];

   strcpy(out_fname, "D:\\Local\\XFS\\XFSTool.cfg");

   if(SUCCEEDED(retc)) retc = CreatePath(out_fname, True);

   if(SUCCEEDED(retc))
   {
      out_file.open((const char *)out_fname, ios_base::out | ios_base::binary);
      KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, out_fname, True);
   }

   if(SUCCEEDED(retc))
   {
      memcpy(file_buf, XFSTool_cfg_arr, sizeof(XFSTool_cfg_arr));
      
static unsigned char str_buf[GEN_CSS_STR_PAR_LEN + 100];
      strcpy(str_buf, ProdVer);   
      DelHeadTailApost(str_buf);
int mask = 0; 
      sscanf((const char *)str_buf, "%d", &mask);
      for(int ii = 0; ii < 4; ii++)
      {
         KP_ASSERT(sizeof(short) == 2, KP_E_SYSTEM_ERROR, null, True);

         *(short *)(file_buf + XFSTOOL_CFG_CODE_OFFSET_1 + 2 * (3 - ii)) = mask;
         *(short *)(file_buf + XFSTOOL_CFG_CODE_OFFSET_2 + 2 * (3 - ii)) = mask;
         *(short *)(file_buf + XFSTOOL_CFG_CODE_OFFSET_3 + 2 * (3 - ii)) = mask;

         mask = KpstRand(mask);
      }
      
      out_file.write(file_buf, sizeof(XFSTool_cfg_arr));
      KP_ASSERT(!out_file.fail(), KP_E_FERROR, out_fname, True);
      
      out_file.close();
      KP_ASSERT(!out_file.fail(), KP_E_FERROR, out_fname, True);
   }

return(retc);
}


// ------------------------------------
HRESULT GetGenIssExeDate(unsigned char *lpszCommentsBuf)
{
HRESULT retc = S_OK;

HANDLE hh = CreateFile(GENISS_EXE_FNAME, GENERIC_READ, FILE_SHARE_READ,
               0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   KP_ASSERT(hh != INVALID_HANDLE_VALUE, KP_E_FILE_NOT_FOUND, GetLastError(), True);

   if(SUCCEEDED(retc))
   {
FILETIME ft;
      KP_ASSERT(GetFileTime(hh, NULL, NULL, &ft), KP_E_SYSTEM_ERROR, GetLastError(), True); 
SYSTEMTIME tt;      
      KP_ASSERT(FileTimeToSystemTime(&ft, &tt), KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc)) sprintf((char *)lpszCommentsBuf, "Geniss %04d.%02d.%02d", tt.wYear, tt.wMonth, tt.wDay);
            
      CloseHandle(hh);
   }   

return(retc);
}


// ------------------------------------
HRESULT ScanKpCurDatCpp(unsigned char *lpszCommentsBuf)
{
HRESULT retc = S_OK;
fstream in_file;
static unsigned char in_fname[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszCommentsBuf != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(in_fname, KP_CURDAT_CPP_FNAME);

      in_file.open((const char *)in_fname, ios_base::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, in_fname, True);
   }
   
   if(SUCCEEDED(retc))
   {
      while((!in_file.eof()) && SUCCEEDED(retc)) 
      {
unsigned char in_line[KP_MAX_FILE_LIN_LEN + 1];      
         in_file.getline(in_line, KP_MAX_FILE_LIN_LEN);
         if(in_file.eof()) break;
         KP_ASSERT(!in_file.fail(), KP_E_FERROR, in_fname, True);
         
         if(SUCCEEDED(retc))
         {
            if(strstr(in_line, "lpszProdDate") != null)
            {
unsigned char *pnts = strchr(in_line, '\"');
               KP_ASSERT(pnts != null, KP_E_FILE_FORMAT, in_fname, True);
               if(SUCCEEDED(retc))
               {
                  pnts++;
unsigned char *pntd = strchr(pnts, '\"');
                  if(pntd != null) *pntd = Nul;
                  strcpy(lpszCommentsBuf, "Kpsttrg ");
                  KP_ASSERT(strlen(pnts) < GEN_CSS_STR_PAR_LEN - strlen(lpszCommentsBuf), KP_E_BUFFER_OVERFLOW, null, False);
               }                
               if(SUCCEEDED(retc)) strcat(lpszCommentsBuf, pnts);               
            }                           
         }
      }
      
      in_file.close();
   }
   
return(retc);
}
