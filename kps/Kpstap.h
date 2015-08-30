// -----------------------------------------
// kpstap.h programos paleidimo apsaugota aplikacija
//

//
// 2013-03-03  mp  m_bMDImaximized – sending Ctrl+Shift+L to Adobe Reader flag – only one time  
// 2015-08-30  mp  atskirtas Kpsttrg bibliotekos kreipiniai KpsInit(), KpsClose() ir KpsTest() (tik patikrinimui be registracijos)
//


#ifndef kpstap_included
#define kpstap_included

// --------------------------------------
// >>>>>> 2013-03-03  mp
// #define KPST_MULTI_DOCS // keli dokumentai vienam Adobe Readerio lange; TODO: kelt á .ini parametrà
// <<<<<< 2013-03-03  mp

// ---------------------------------------
// #define DebugStop // debuginis kpstart.exe --> test.exe, siøsti klientui, kad apsakytø, kur sustojo
// #define CHECK_MAXIMIZE // tikrinam, kodël nemaximizuoja Acrobat lango

// ---------------------------------------
// #define KPST_MOVE_TO_KPHP11 // .INI file inside of emulator only
// #define KPST_USE_CLIPBOARD  // use clipboard for rezults and command processing, throws an error on WinXP
#define KPST_USE_SOCKET  // use IP listening socket for command processing

#define KPST_WINDOWS_INTERFACE // for compid counter file, *.ini file I/O
// #define KPST_UNICODE_FNAMES

// ----------------------------------------- kpstapg.cpp transliavimo parinktys
// #define KPST_PRODGRP_NODOWNLOAD // testuojam tik diegimà, nesiunèiam ir netrinam
#ifdef IBSHT_ENCODED
#define KPST_PRODGRP_CFG_ENCODED // StartGrp.cfg uþkoduotas
#endif
// #define KPST_PRODGRP_NO_SVR_REQUEST // nesikreipia á prodreg.tev.lt, imituoja socketo klaidà – lieka lokalus paskutiná kartà uþkrautas meniu
// #define KPST_PRODGRP_STATIC_CFG  // uþkrauna hardkodiná meniu ið lpszStartGrpCfgDef, uþkloja galimai parsiøstà ið prodreg.tev.lt tuo paèiu ignoruodamas ir oflaininá DAT0/StartGrp.cfg
                                 // galioja ir CheckUpdate()
// #define KPST_PRODGRP_OLD_INTERFACE // uþklausa á prodreg.tev.lt su vien tik lic. id. pagal 2011.08.23 projektà
// #define KPST_PRODGRP_OLD_LOGIN // loginas windowsiniame langelyje, iki 2012.07.17

#define KPST_UPDATE_OLD_INTERFACE   // senas CheckUpdate() interfeisas – skanuoja FDF ir permeta á IE langà
                                       // naujas – per XML, pasiûlo paselektint varneles, parsiunèia fone, sustabdo pagr. programà/dokumentà ir paleidþia atnaujinimø setupus

#define KPST_UPDATE_OLD_LAUNCH      // senas CheckUpdate() paleidimas – per StartCheckUpdateThread();
                                       // naujas – ið StartSockProcess() KpStIpSvrMode kpstisvr.exe;
// ------------------------------
// jei apibrëþtas, ser. no. imam ið "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum" (taip dabar)
// jei ne – ið "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum" (buvo anksèiau)
// buvo problemø su kaþkurio gamintojo atmintukais – UVCView.x86.exe rodydavo kitoká serno, negu nustatydavau að –
// USBSTOR\\Enum ir Disk\\Enum serno skirdavosi, UVCView.x86.exe, atrodo, ima ið Disk\\Enum
// be to, atmintukas.exe ima, atrodo, irgi ið Disk\\Enum (SetupDiGetDeviceInterfaceDetail(..., ..., interfaceDetailData, <...>)
// -------
// Plius78m/klaida_issitryne_8P1-51431-0485 "Disk\\Enum" áraðo neatsiranda
// TODO !!!! reikia perdaryt, kad imtø ið abiejø vietø – jei neranda "Disk\\Enum", tada ieðko "USBSTOR\\Enum"
// TODO !!!! GetFlashVidPid() ima tik ið "USBSTOR\Enum" – kas tada, jei "USBSTOR\Enum" nëra?
// tai kad atsiranda, viskas tvarkoj – bëda buvo dël to, kad atmintukas.exe kitoká ser.no. sugeneravo, dar pasiaiðkint
// -------
#define KPST_FLASH_SERNO_DISK

#define KPST_BITMAP_TO_TOP // ar iðkelti atsklandà virð slaptaþodþio

// --------------------------------
#define KPST_DATA_FILE_CTBL 71

// --------------- koduotu rezultatu lauku parametrai
#define KPST_TXTCD_RADIX_NAME 32
#define KPST_TXTCD_BITS_NAME 5
#define KPST_TXTCD_MASK_NAME 0x1F
#define KPST_TXTCD_CHARS_PER_VAL_NAME 6
#define KPST_TXTCD_BASE_NAME C_At // '@' // C_A // 'A'

#define KPST_TXTCD_RADIX_TID 256
#define KPST_TXTCD_BITS_TID 8
#define KPST_TXTCD_MASK_TID 0xFF
#define KPST_TXTCD_CHARS_PER_VAL_TID 4
#define KPST_TXTCD_BASE_TID C_Spc // ' '

#define KPST_TXTCD_CHARS_PER_VAL_REZ 10 // former KP_TASKS_PER_FIELD
#define KPST_TXTCD_RADIX_REZ 8
#define KPST_TXTCD_BITS_REZ 3
#define KPST_TXTCD_MASK_REZ 0x7

#define KPST_TXTCD_BITS_MIN 6
#define KPST_TXTCD_MASK_MIN 0x3F

#define KPST_TXTCD_BITS_HOUR 5
#define KPST_TXTCD_MASK_HOUR 0x1F

#define KPST_TXTCD_BITS_MONTH 4
#define KPST_TXTCD_MASK_MONTH 0xF

#define KPST_TXTCD_BITS_DAY 5
#define  KPST_TXTCD_MASK_DAY 0x1F

// ---------------------------------------
// flags for theKpStAppPtr->m_Ini.m_iCompIdMode
#define KPST_COMPID_BIOS_DATE    0x0001   // default value, will be applyed even if m_iCompIdMode == 0
#define KPST_COMPID_DISK_ID      0x0002
#define KPST_COMPID_PROC_ID      0x0004
#define KPST_COMPID_MAC          0x0008   // tinklo plokðtës MAC adresas // !!! TODO
#define KPST_COMPID_PROC_NAME    0x0010   // procesoriaus vardas
#define KPST_COMPID_BOLT         0x0020   // programiðkai serveryje ar lokaliai atsitiktinai generuojamas kodas (varþtas)

// ----------------------------------
#define KPST_DAYS_PER_MONTH 30
#define KPST_MINS_PER_DAY KP_MINS_PER_DAY // 2 //
#define KPST_MINS_PER_HOUR KP_MINS_PER_HOUR // 1 //

// ---------------------------------------
#define KPST_INI_FILE_FILTER ((const unsigned char *)"*.ini") // former KPSTEDI_FILE_NAME
#define KPST_REZ_FILE_FILTER ((const unsigned char *)"*.txt")
#define KPST_REZ_FILE_NAME   ((const unsigned char *)"rezultatai.txt")
#define KPST_REZ_LOG_FILE_NAME  ((const unsigned char *)"rezultatai.log")
#define KPST_ACROREAD_FNAME ((const unsigned char *)"AcroRd32.exe")
#define KPST_ACROREAD_FNAME_BIN ((const unsigned char *)"AcroRd32.exe") // èia MIKO knygoms
#define KPST_ACROREAD_FNAME_SHORT ((const unsigned char *)"AcroRd32.") // èia testavimui, kad tiktø ir MIKO knygoms
#define KPST_ACROREAD50_PATHNAME ((const unsigned char *)"AcroRead\\Reader")
#define KPST_ACROREAD60_PATHNAME ((const unsigned char *)"AcroRead602\\Reader") // "AcroRead60"
#define KPST_ACROREAD60_PATHNAME_SHORT ((const unsigned char *)"AR6\\Reader")
#define KPST_ACROREAD70_PATHNAME ((const unsigned char *)"AcroRead709\\Reader") // "AcroRead70" // "Acrobat70")
#define KPST_ACROREAD70_PATHNAME_SHORT ((const unsigned char *)"AR7\\Reader")
#define KPST_ACROREAD80_PATHNAME ((const unsigned char *)"AcroRead813\\Reader") // "AcroRead70" // "Acrobat70")
#define KPST_ACROREAD80_PATHNAME_SHORT ((const unsigned char *)"AR8\\Reader")
#define KPST_ACROREAD90_PATHNAME ((const unsigned char *)"AcroRead90\\Reader") // "AcroRead70" // "Acrobat70")
#define KPST_ACROREAD90_PATHNAME_SHORT ((const unsigned char *)"AR9\\Reader")
// #define KPST_EMA_FNAME ((const unsigned char *)"ema.exe")
#define KPST_EMA_FNAME ((const unsigned char *)"AcroRd32.exe")
#define KPST_EMA_WNAME ((const unsigned char *)"KpstEma")
#define KPST_EMA_OKBUT ((iWindowsVersion<WinNT)?10:11)
#define KPST_ACRO_LOAD_TIME 15 // sec, Acrobatas kraunasi apie 15 sec
#define KPST_ACRO_MAXIMIZE_TIMEOUT  KPST_ACRO_LOAD_TIME // 15 // 30 // kiek sekundþiø bandyti maximizuoti Acrobatà
#define KPST_ACRO_MAXIMIZE_INTERVAL 2000 // 500 // kiek milisekundþiø palaukti, radus maksimizuotinà acrobato langà
#define KPST_SOUND_STOP_TIMEOUT 5

#define KPST_FLASH_REG_FILE_NAME ((const unsigned char *)"atmintukai.txt")

// --------------------------------------- definitions for CopyResults()
// #define JS_SUB_PATH "Adobe\\Acrobat\\JavaScripts\\"
#define JS_SUB_PATH_1 "Adobe\\Acrobat\\"
#define JS_SUB_PATH_2_60 "6.0\\"
#define JS_SUB_PATH_2_70 "7.0\\"
#define JS_SUB_PATH_2_80 "8.0\\"
#define JS_SUB_PATH_2_90 "9.0\\"
#define JS_SUB_PATH_3 "JavaScripts" // "JavaScripts\\"
#define GLOB_JS_FILE_NAME ((const unsigned char *)"glob.js") // former JS_FILE_NAME
#define GLOB_JS_HIST_FILE_NAME ((const unsigned char *)"glob.log") // former JS_HIST_FILE_NAME
#define KPST_INI_FILE_TYPE ((const unsigned char *)".ini")
#define HIST_FILE_TYPE ((const unsigned char *)".log") // former JS_HIST_FILE_TYPE
#define SAV_FILE_TYPE ((const unsigned char *)".sav") // former JS_SAV_FILE_TYPE
#define TEV_SAV_FILE_TYPE ((const unsigned char *)".tvs")
#define KPST_CUR_DIR KP_CUR_DIR
#define KPST_FDF_DATA_FNAME ("data.dat")
#define KPST_FDF_DATA_FTYPE ((const unsigned char *)".dat")
#define KPSTART_UPDATE_DAT ("update.dat")
#define KPSTART_KPSCALC_EXE ("kpscalc.bin") // ("kpscalc.exe")
#define KPSTART_KPSCLC_EXE ("kpsclc.bin") // ("kpsclc.exe")
#define KPSTART_IEXPLORE ((const unsigned char *)"iexplore")
#define TMGrpPrm_FNAME ((const unsigned char *)"TMGrpPrm.sav")
#define KPST_EXT_PLAYERS_INI_FNAME ((const unsigned char *)"\\DAT0\\players.ini")
#define KPST_CHK_BIN_INI_FNAME ((const unsigned char *)"\\DAT0\\kpstbls.ini")
#define KPST_TEV_OBJ_FILE_TYPE ((const unsigned char *)".tev")
#define KPST_PDF_FILE_TYPE ((const unsigned char *)".pdf")
// #define START_SEL_CFG_FNAME ((const unsigned char *)"StartSel.cfg") // former START_SEL_INI_FNAME
#define STARTSEL_MNG_DIR ((const unsigned char *)"DAT0") // "Papildai")
#define START_SEL_CFG_FTYPE ((const unsigned char *)"cfg")

#define JS_SUB_PATH_4 ((const unsigned char *)"\\JavaScripts\\")
#define JS_SVARBIINFO_FLASH ((const unsigned char *)"R__svarbiinfo.js")

// --------------------------------------- .iss file name
#define KPST_ISS_FILE_NAME   (/* (const unsigned char *) */ "gen_iss_cod_lic.pas")


// --------------------------------------- definitions for js contents
#define JS_WAVE_DEVS_PAR_NAME ((const unsigned char *)"wavedevs")
#define JS_TEST_PAR_NAME ((const unsigned char *)"test_par")
#define JS_DATA_READY_PAR_NAME ((const unsigned char *)"duomenys")
#define JS_SRV_ADR_PAR_NAME ((const unsigned char *)"srv_adr")
#define JS_PROD_VER_PAR_NAME ((const unsigned char *)"prod_ver")
#define JS_SRV_PORT_PAR_NAME ((const unsigned char *)"srv_port")
#define JS_FLASH_DEV_PAR_NAME ((const unsigned char *)"flash_disk")
#define JS_PROG_PATH_PAR_NAME ((const unsigned char *)"prog_path")

#define JS_PAR_PREF     ((const unsigned char *)"try{eval((new String(\"")
#define JS_NUM_PAR_PREF_SHORT ((const unsigned char *)"global.%s=(new Number(")
#define JS_BOOL_PAR_PREF_SHORT ((const unsigned char *)"global.%s=(new Boolean(")
#define JS_STR_PAR_PREF_SHORT ((const unsigned char *)"global.%s=(new String(\\\"")
#define JS_STR_PAR_TAIL_SHORT ((const unsigned char *)"\\\"")  // \"))")).valueOf());
#define JS_NUM_PAR_TAIL_SHORT ((const unsigned char *)"")      //   ))")).valueOf());
#define JS_BOOL_PAR_TAIL_SHORT ((const unsigned char *)"")      //   ))")).valueOf());
#define JS_STR_PAR_TAIL_MID ((const unsigned char *)"\\\"))\")).valueOf());")
#define JS_NUM_PAR_TAIL_MID ((const unsigned char *)"))\")).valueOf());")
#define JS_BOOL_PAR_TAIL_MID ((const unsigned char *)"))\")).valueOf());")
#define JS_PAR_TAIL     ((const unsigned char *)"))\")).valueOf());}catch(e){}") // "\n"
#define JS_PAR_TAIL_1   (')') // skaitinis parametras neturi trumpos uodegos - ieskom skliausto
// #define JS_NUM_PAR_PREF ((const unsigned char *)JS_PAR_PREF JS_NUM_PAR_PREF_SHORT)
// #define JS_STR_PAR_PREF ((const unsigned char *)JS_PAR_PREF JS_STR_PAR_PREF_SHORT)
// #define JS_NUM_PAR_TAIL ((const unsigned char *)JS_NUM_PAR_TAIL_SHORT JS_PAR_TAIL)
// #define JS_STR_PAR_TAIL ((const unsigned char *)JS_STR_PAR_TAIL_SHORT JS_PAR_TAIL)

#define JS_VAR_START ((const unsigned char *)"(\'")
#define JS_VAR_TAIL ((const unsigned char *)"\')")

#define JS_AI_VAR_NAME ((const unsigned char *)"global.AI_e=SdS(\'")
#define JS_PRODVAR_NAME ((const unsigned char *)"global.ProdVar=")
#define JS_PRODVAR_SH_NAME ((const unsigned char *)"ProdVar")
#define JS_PRODVER_NAME ((const unsigned char *)"global.ProdVer=")
#define JS_PRODVER_SH_NAME ((const unsigned char *)"ProdVer")

// ---------------------------------------
#define KPST_CLIP_VWR_SUB_PATH "\\System32\\clipbrd.exe"

// ---------------------------------------
#define KPST_CNT_PKG_FMT m_CntPkgFmt
#define KPST_LIC_PKG_FMT m_LicPkgFmt
#define KPST_BOLT_PKG_FMT m_BoltPkgFmt
#define KPST_CNT_REG_KEY_FMT m_CntRegKeyFmt
#define KPST_CNT_REG_PATH_1 m_CntRegPath1
#define KPST_CNT_REG_PATH_11 m_CntRegPath11
#define KPST_CNT_REG_PATH_2 m_CntRegPath2
// #define KPST_CNT_REG_PATH_22 m_CntRegPath22

typedef struct
{
   long m_lRestMinsInit; // ðito saugoti nereikëtø – aktualus ið DiegRakto
   long m_lRestMinutes;
   long m_lCurMins;

} RestTimeStruct;

// ---------------------------------------
#define KPST_ACROREAD_WINDOW_NAME ((const unsigned char *)"Adobe Reader")
// ðiaip tai "Adobe Reader CE", bet maximizuoja tik ilgesnio pavadinimo langus, o kartais
// reikia maksimizuoti bûtent "Adobe Reader CE" langà (pprc)

#define KPST_IE_WINDOW_NAME ((const unsigned char *)"Internet Explorer") // "Windows Internet Explorer" // "Microsoft Internet Explorer"

// --------------------------------------- HTTP queries
// http://www.tev.lt/prodreg.php?instcode=RLL4-8R34-GR52-5U2U
#define KPST_PRODREG_URL_INI ((const unsigned char *)"http://www.tev.lt/prodreg.php") // former KPST_PRODREG_URL // tik geniss.exe, pradinës reikðmës nustatymui, ðiaip konfigûruojamas dinamiðkai
#define KPST_HTTP_REGISTER ((const unsigned char *)"?instcode=")
#define KPST_HTTP_REMOVE   ((const unsigned char *)"?remcode=")
#define KPST_REG_OK        ((const unsigned char *)"KpReg-Ok: ")
#define KPST_REG_OK_short  ((const unsigned char *)"KpReg-Ok")
#define KPST_REG_VOID_short ((const unsigned char *)"KpReg-NoNews")
#define KPST_REG_ERROR     ((const unsigned char *)"KpReg-Error: ")
#define KPST_REG_ERROR_short ((const unsigned char *)"KpReg-Error")
#define KPST_REG_EXPIRED   ((const unsigned char *)"KpReg-Refused: ") // "KpReg-Expired: ") // KPST_REG_REFUSED
#define KPST_REG_EXPIRED_short ((const unsigned char *)"KpReg-Refused") // "KpReg-Expired") // KPST_REG_REFUSED_short
#define KPST_IP_OK         ((const unsigned char *)"KpStart-Ok: ")
#define KPST_IP_ERROR      ((const unsigned char *)"KpStart-Error: ")

// #define KPST_CHK_UPDATE_URL   ((const unsigned char *)"http://127.0.0.1:13006/")
// #define KPST_CHK_UPDATE_FILE ((const unsigned char *)"/")

// PI=73R2-LL54-3UUR-1UJ3  722G-89UU-LLA7-LR8E  0  [dBI+9,+B]:1505+*,=*/,BZ/;)190*+B   0  0  1  33650 RRqlniqQk   ]:1505+*,=*/,  32 0  2  6  0     6000  0&ProdVer=2010&ProdVar=7
#ifdef KPST_UPDATE_OLD_INTERFACE
#define KPST_CHK_UPDATE_URL   ((const unsigned char *)"http://updates.tev.lt/versija.php")
#define KPST_CHK_UPDATE_FILE  ((const unsigned char *)"/versija.php")
#else
#define KPST_CHK_UPDATE_URL   ((const unsigned char *)"http://updates.tev.lt/versija_n.php")
#define KPST_CHK_UPDATE_FILE  ((const unsigned char *)"/versija_n.php")
#endif

// #define KPST_CHK_UPDATE_URL   ((const unsigned char *)"http://updates.tev.lt/test.php")
// #define KPST_CHK_UPDATE_FILE  ((const unsigned char *)"/test.php")

// http://www.tev.lt/prodgrp.php?lic=8R34-GR52-5U2U&ProdVar=1
#define KPST_PRODGRP_URL   ((const unsigned char *)"http://www.tev.lt/prodgrp.php")
#ifdef KPST_PRODGRP_OLD_INTERFACE
#define KPST_PRODGRP_FILE  ((const unsigned char *)"/prodgrp.php")
#define KPST_PRODGRP_FORMAT ("?lic=%s&ProdVar=%d")
#else
// #define KPST_PRODGRP_FILE  ((const unsigned char *)"/prodgrl.php")
#define KPST_PRODGRP_FILE  ((const unsigned char *)"/prodgrp.php")
#define KPST_PRODGRP_FORMAT_1 ("?sesid=%d")
#define KPST_PRODGRP_FORMAT_2 ("?sesid=%d&user=%s&pwd=%s&compid=%d&forced=%d&remid=%ld&fizid=%ld")
#endif
#define KPST_GRP_PWD_CRYPT_CODE 123456L // lokalus statinis kodavimo raktas slaptaþodþio saugojimui registre

#define KPST_USBRAKTAI_URL ((const unsigned char *)"http://www.tev.lt/usbraktai.php")
#define KPST_USBRAKTAI_FILE ((const unsigned char *)"/usbraktai.php")
#define KPST_USBRAKTAI_RAKTAS ((const unsigned char *)"?raktas=")
#define KPST_USBRAKTAI_ID ((const unsigned char *)"&id=")
#define KPST_USBRAKTAI_ID_TAIL ((const unsigned char *)"w0r1UkazZ")
#define KPST_USBRAKTAI_DATA ((const unsigned char *)"&data=")
#define KPST_USBRAKTAI_OK ((const unsigned char *)"ok")
#define KPST_USBRAKTAI_ERR ((const unsigned char *)"err")

// #define KPST_USBPIRK_URL ((const unsigned char *)"http://www.tev.lt/usbpirk.php")
// #define KPST_USBPIRK_URL ((const unsigned char *)"http://siuntiniai.tev.lt/updates/temp/usbpirk.htm")
#define KPST_USBPIRK_URL ((const unsigned char *)"http://siuntiniai.tev.lt")
// #define KPST_USBPIRK_FILE ((const unsigned char *)"/usbpirk.php")
#define KPST_USBPIRK_FILE ((const unsigned char *)"/updates/temp/usbpirk.htm")

#define KPST_BOLT_URL   ((const unsigned char *)"http://www.tev.lt/remid.php")
#define KPST_BOLT_FILE  ((const unsigned char *)"/remid.php")
#define KPST_BOLT_FORMAT ("?fizid=%ld")

#define KPST_ENCODE_FILE_URL   ((const unsigned char *)"http://www.tev.lt/get_file.php") // "http://serveri5.ll/lentyna/get_file.php") // 
#define KPST_ENCODE_FILE_PATTERN ((const unsigned char *)"get_file.php")

#define KPST_GRP_LOGIN_URL   ((const unsigned char *)"http://www.tev.lt/grplogin.php") // "http://serveri5.ll/lentyna/grplogin.htm") // 
#define KPST_GRP_LOGIN_FILE  ((const unsigned char *)"/grplogin.php") // "/lentyna/grplogin.htm") // 

// kpstisvr.exe SockListenProc() komandos
#define KPSTIP_ALIVE_CMD ((const unsigned char *)"CD=")
#define KPSTIP_DISCONNECT_CMD ((const unsigned char *)"RD=")
#define KPSTIP_EXEC_CMD ((const unsigned char *)"EX=")
#define KPSTIP_EXEC_0_CMD ((const unsigned char *)"EX=")
#define KPSTIP_EXEC_EXT_CMD ((const unsigned char *)"EXT=")
#define KPSTIP_EXEC_EXT_0_CMD ((const unsigned char *)"EXT")
// CU=WinLED 5.0&WN=WinLED&PI=R5LG-J135-AJ9A-E8J6	LJ88-23JJ-A2J5-JAU1	0	[dBI+9,+B150:=)7=+BZ/;)190*+B	0	0	1	43627	RRqmnkqQj	150:=)7=+	40	0	2	6	1		7600	0&ProdVer=3012&ProdVar=5
#define KPSTIP_CHK_UPDATE_CMD ((const unsigned char *)"CU=")
#define KPSTIP_CLOSE_WND_CMD ((const unsigned char *)"WN=")
#define KPSTIP_INI_FNAME_CMD ((const unsigned char *)"IF=")

#define KPST_CHK_UPDATE_CMD ((const unsigned char *)"PI=")
// #define KPST_CHK_UPDATE_0_CMD ((const unsigned char *)"PI")
// #define KPST_PROGRAM_ID_VAR_NAME ((const unsigned char *)"PI")
#define KPST_CHK_UPDATE_FORMAT ("&ProdVer=%d&ProdVar=%d")
#define KPST_CHK_UPDATE_PRODVER_CMD ("ProdVer=")

// ----------------------------------
#define KPST_PRODGRP_SVR_REQUEST_ASYN_TIMEOUT 2000 // kiek msec laukti GrpSvrRequest()
#define KPST_PRODGRP_SVR_REQUEST_ASYN_SLEEP 200 // kas kiek msec tikrinti, gal jau pasibaigë GrpSvrRequest()

// makrokomandos parametruose:
//    C: KpStApp::StartCmd() paleidimo komandoje m_lpszCmdStr[]
//    S: StartSel.exe .cfg failo komandos eilutëje
//    E: kpstedb.exe
//    R: KpProcessError() papildomø failø sàraðuose KpDiagMsgAddFiles
//    G: StartGrp.exe
#define KPST_FNAME_SHORTCUT_ATT ((const unsigned char *)"{att}")     // C: nuo .exe failo atkabintos priekabos %TEMP% kataloge failo vardas su prievardþiu ("tv831110.exe", "tv029706.ini")
#define KPST_FNAME_SHORTCUT_PROG ((const unsigned char *)"{prog}")   // C: paleistos programos .exe failo vardas be prievardþio ("MT9", "XFS", ...)
#define KPST_FNAME_SHORTCUT_PAR ((const unsigned char *)"{par}")     // C: pirmas komandinës eilutës m_plCmdLineArgs parametras
#define KPST_FNAME_SHORTCUT_USER ((const unsigned char *)"{user}")   // CS: dvigubo atmintuko flash dalies disko vardas m_lpszFlashDevName be sleðo ("E:"), diegiamiems produktams – vienu þemesnis uþ diegimo katalogà ("C:\Program Files\Tev")
#define KPST_FNAME_SHORTCUT_PROGPATH ((const unsigned char *)"{progpath}") // R: programos paleidimo katalogas ("C:\Program Files\Tev\MaTau5") // kodël ne "{app}"?
#define KPST_FNAME_SHORTCUT_TEMP ((const unsigned char *)"{temp}")   // SRG: %TEMP%
extern const KpChar KpstGrpMacroTemp[];
#define KPST_FNAME_SHORTCUT_TEMP_W (KpstGrpMacroTemp)
#define KPST_FNAME_SHORTCUT_FILE ((const unsigned char *)"{file:")   // E: naudojama kpstedb.exe (paketiniu reþimu) áraðant m_lpszUserData, keièiama nurodyto tekstinio failo paskutinës eilutës turiniu.
                                                                     //    Individualiems atmintukø (MT910SVK) atnaujinimams, make_run_0.bat ("{file:AI\AI_encode.txt}")

// grupiniø downloadø parametro failo / StartGrp.exe paleidimo meniu ðablono makrokomandos
#define KPST_GRP_MACRO_APP       ((const unsigned char *)"{app}")
extern const KpChar KpstGrpMacroApp[];
#define KPST_GRP_MACRO_APP_W        (KpstGrpMacroApp)       // "{app}" // komponento diegimo katalogas // gal tas pats, kaip "{progpath}"?
extern const KpChar KpstGrpMacroAppname[];
#define KPST_GRP_MACRO_APPNAME_W    (KpstGrpMacroAppname)   // "{appname}" // pilnas produkto vardas
extern const KpChar KpstGrpMacroLaunch[];
#define KPST_GRP_MACRO_LAUNCH_W     (KpstGrpMacroLaunch)    // "{launch}" // paleidimo komanda HTML nuorodai
extern const KpChar KpstGrpMacroFile[];
#define KPST_GRP_MACRO_FILE_W       (KpstGrpMacroFile)      // "{file}" // iðorinio failo lokalus vardas (eilinio ið sàraðo)
extern const KpChar KpstGrpMacroMpar[];
#define KPST_GRP_MACRO_MPAR_W       (KpstGrpMacroMpar)      // "{mpar}" // meniu parametro reikðmë (eilinio ið sàraðo)
extern const KpChar KpstGrpMacroSetup[];
#define KPST_GRP_MACRO_SETUP_W      (KpstGrpMacroSetup)     // "{setup}" // diegimo failo URL
extern const KpChar KpstGrpMacroSetupSize[];
#define KPST_GRP_MACRO_SETUPSIZE_W  (KpstGrpMacroSetupSize) // "{setupsize}" // diegimo failo dydis
extern const KpChar KpstGrpMacroLic[];
#define KPST_GRP_MACRO_LIC_W        (KpstGrpMacroLic)       // "{lic}" // produkto licencija
extern const KpChar KpstGrpMacroPrc[];
#define KPST_GRP_MACRO_PRC_W        (KpstGrpMacroPrc)       // "{prc}" // siun2iamo setupo failo progreso indikatoriaus dydis

// ProdVer registro parametrai
#define KPST_PRODVER_REG_KEY_ProdName  ((const unsigned char *)"ProdName")
#define KPST_PRODVER_REG_KEY_Ver       ((const unsigned char *)"Ver")
#define KPST_PRODVER_REG_KEY_ProjID    ((const unsigned char *)"ProjID")
#define KPST_PRODVER_REG_KEY_ExeFName  ((const unsigned char *)"ExeFName")
#define KPST_PRODVER_REG_KEY_ProdFName ((const unsigned char *)"ProdFName")
#define KPST_PRODVER_REG_KEY_ProdGroup ((const unsigned char *)"ProdGroup")
#define KPST_PRODVER_REG_KEY_ProdDir   ((const unsigned char *)"ProdDir")
#define KPST_PRODVER_REG_KEY_Launch    ((const unsigned char *)"Launch")
#define KPST_PRODVER_REG_KEY_Uninst    ((const unsigned char *)"Uninst")
#define KPST_PRODVER_REG_KEY_Installed ((const unsigned char *)"Installed")
#define KPST_PRODVER_REG_KEY_TestUpdates ((const unsigned char *)"TestUpdates")
#define KPST_PRODVER_REG_KEY_LastUser  ((const unsigned char *)"LastUser") // paskutinio StartGrp.exe userio slaptaþodis

// StartGrp.exe meniu xGecko controlo prad=ios koordinatës – kad pranyktø marginai
// TODO: tvarkyti paèiam .htm faile, stumiant bacgroundà:
// <style>
// img#background
// {
//    margin-left: -20px;
//    margin-top: -30px;
// }
#define KPST_GRP_RES_X_COR 0 // (-8)
#define KPST_GRP_RES_Y_COR 0 // (-8)

// StartGrp xGeck controlo pradþios koordinatës
#define KPST_GRP_RES_X KPST_GRP_RES_X_COR
#define KPST_GRP_RES_Y KPST_GRP_RES_Y_COR

// Didinam StartGrp xGecko controlà, kad pasislëptø atsiradæ scrollbarai
// viskas turi bûûti tvarkoma iBshDlg viduj
// #define KPST_GRP_RES_DX_ENL  KPGECKO_SCROLLBAR_WDT
// #define KPST_GRP_RES_DY_ENL  KPGECKO_SCROLLBAR_WDT

// ------------
#define KPST_GRP_PATH_PREFIX ((const unsigned char *)"tux:///KpStart:")
#define KPST_GRP_PATH_PREFIX_W (KpstGrpPathPrefix)

#define KPST_GRP_MENU_FNAME ((const unsigned char *)"DAT0\\StartGrp.htm")
#define KPST_GRP_ALIVE_PRESENT_FILE_NAME ((const unsigned char *)"ProdsAlive.txt")
#define KPST_GRP_FONAS_FNAME ((const unsigned char *)"DAT0\\StartGrp_fonas.gif")
extern long StartGrp_fonas_len; 
extern unsigned char StartGrp_fonas[];

// ------------
#define KPST_USBRAKTAI_FNAME ((const unsigned char *)"RegAtm.htm")

// ------------
#define MD5_RES_WDT 32 // MD5() rezultato (128 bitø hash rakto) ðeðioliktainiø skaitmenø kiekis

// ----------------------------
typedef enum
{
   NoStartSelIx = -1,

   MainBackgroundIx,    // StartSel meniu fono paveikslëlis
   PaletteIx,           // StartSel tekstiniø mygtukø spalvos
   ButtonImageIx,       // StartSel mygtuko paveiksliukas
   ButtonHighlightIx,   // StartSel hoverinamo mygtuko paveiksliukas
   ButtonSelectedIx,    // StartSel paspausto mygtuko paveiksliukas
   ButtonTextIx,        // Tekstinio mygtuko tekstas
   StopRefreshIx,       // StartGrp.exe refresh stabdymas (m_bGrpRefreshFlg = False)
   StartRefreshIx,      // StartGrp.exe refresh paleidimas (m_bGrpRefreshFlg = True)
   StartAndCloseActionIx,  // paleisti programà ir uþdaryti meniu (kad nespaudinëtø kelis kartus)
   StartAdminActionIx,  // paleisti programà admino reþimu (gal tik patikrinant, ar adminas?)
   StartActionIx,       // paleisti programà
   OpenActionIx,        // atidaryti failà
   EditUserDataIx,      // vartotojo duomenø keitimas
   SaveCopyActionIx,    // iðsaugoti MIKO vartotojo failø kopijà
   RestoreCopyActionIx, // atstatyti MIKO vartotojo failø kopijà
   RestoreActionIx,     // atstato MIKO gamyklines nuostatas
   HorMarginIx,         // StartSel apatinë paraðtë pikseliais, nuo jos mygtukai iðdëliojami aukðtyn
   VertMarginIx,        // StartSel kairë paraðtë pikseliais
   ButMarginIx,         // StartSel atstumas tarp mygtukø pikseliais
   DiagMsgIx,           // Siøsti diagnostiná praneðimà
   OptionsIx,           // Paleisti parinkèiø dialogà
   LogoffIx,            // Logoff (StartGrp: Iðregistruoja ir pabaigia programà. Kità kartà paleidþiant, atsivers logino langas.)
   RefreshIx,           // Atnaujinti meniu
   DownLoadIx,          // Pradëti produkto diegimo failo siuntimà, diegimà ir aktyvacijà
   UninstIx,            // Iðmesti produktà
   BrowseIx,            // Iðeiti á iðoriná puslapá, prieð tai iðjungus periodiná meniu atnaujinimà
   ReturnIx,            // Atnaujinti meniu ir ájungti periodiná atnaujinimà
   LoginIx,             // Login (StartGrp: Iðregistruoja ir pereina á logino langà)
   DoLoginIx,           // Logino lango prisijungimo mygtuko paspaudimo vykdymas (StartGrp)
   SetVarIx,            // kintamojo reikðmës iðsaugojimas registre
   GetVarIx,            // iðsaugotos kintamojo reikðmës iðtraukimas

   NumOfStartSelKwdIxs

} StartSelKwdIxs;

#define NumOfStartSelKwdIxs_16 NumOfStartSelKwdIxs // StartActionIx kelt po visø kitø Start...

extern const unsigned char *lpszaStartSelKwds[NumOfStartSelKwdIxs + 1];

// ----------------------------
// R/ID[<42f081e0602ae74b8b6092889b64a869><add62604141cdd499a7c5ab762fe3951>]
#define KPST_RID_LEN 74 // viso R/ID objekto ilgis
#define KPST_RID_PATTERN ((const unsigned char *)"R/ID[<")
#define KPST_RID_ELEM_LEN 32 // vieno elemento reikðmës ilgis (kas tarp <>)

// --------------------------------------- cipboard cmd processor
#define KPST_CLIP_CMD_DELIM ('|')
#define KPST_CLIP_CMD_HAT ("AcroTEV")

// ---------------------------------------
#ifdef Debug
#define KPST_INI_SECS_TO_KILL    (3*KP_SECS_PER_MIN) // 3 min. kabancios licencijos
#else
#define KPST_INI_SECS_TO_KILL    (30*KP_SECS_PER_MIN) // 30 min. kabancios licencijos
#endif
#define KPST_LIC_MANAG_TIMEOUT   (30*KP_MILISECS_PER_SEC) // m_iLicManagTimer
                                       // kas 30 sec. pakartotine registracija prie lokalaus lic. serverio
                                       // taip pat naudojamas ir serveryje - displejaus atnaujinimui
                                       //    ir *.ini pakartotiniam perskaitymui

#define KPST_PROC_CMD_TIMEOUT    500   // kas puse sekundes tikrina komandas clipboarde (vidiniame IP miniserveryje?)

#define KPST_SRV_REFRESH_TIMEOUT  10 // kas 10 sec. atsinaujina lokalaus serverio administravimo busenos puslapiai

#define KPST_CHK_NEW_FLASH_TIMEOUT (1*KP_MILISECS_PER_SEC) // 5000 // 500 // former KPST_CHK_FLASH_TIMEOUT // kas 1 sec. TevAutoRun iesko nauju atmintuku
#define KP_NUM_OF_DISKS ('Z' - 'A' + 1)

#define KPST_CHK_SER_FLASH_TIMEOUT (5*KP_MILISECS_PER_SEC)    // m_iFlashCheckTimer - naudojamas tikrinimui, ar vis dar ikistas atmintukas

#define KPST_SES_PROLONG_TIMEOUT (10*KP_MILISECS_PER_SEC)
#define KPST_SES_RELEASE_TIMEOUT (30*KP_MILISECS_PER_SEC)

#define KPST_REST_MINS_TIMEOUT   (KP_SECS_PER_MIN * KP_MILISECS_PER_SEC) // (10 * KP_MILISECS_PER_SEC) // m_iRestMinsTimer //
#define KPST_REST_DAYS_WARNING   30 // 5 // prieð 5 dienas praneðinëti apie besibaigianèià licencijà

#define KPST_ATM_KOD_NULL ((const unsigned char *)"000-00000-0000") // "000-000000"

#define KPST_STOP_PROCESS_POLLING_TIMER 300 // former KPSTGRP_STOP_PROCESS_POLLING_TIMER

// ---------------------------------------
enum
{
   KpstCloseWindow,  // "CW"
   KpstPutMsg,       // "PM"

   KpstClipCmdCnt
};

extern const unsigned char *lpszaKpstClipCmds[KpstClipCmdCnt+1];

extern unsigned char lpszPostSpChars[]; // vald. simboliai funkcijai EncodePostMsg()

// --------------------------------------- exercise data file definitions
// #define KPST_EXC_HAT ("IP\tUzduotis\tPradzia\tLygis\tPasirinktasRezimas\tPasirinktasUzdSk\tPasirinktasLaikas\n")
#define KPST_EXC_HAT ("IP\tU_duotis\tPrad_ia\tPabaiga\tLygis\tPasirinktas re_imas\tPasirinkta u_duoèiø\tPateikta u_duoèiø\tTeisingai\tNeteisingai\tPasirinktas laikas\n")

typedef class KpstExercDataFileLine_tag
{
public:
   const unsigned char *m_lpszIP;
   const unsigned char *m_lpszUzduotis;
   const unsigned char *m_lpszPradzia;
   const unsigned char *m_lpszPabaiga;
   const unsigned char *m_lpszLygis;
   const unsigned char *m_lpszPasirinktasRezimas;
   const unsigned char *m_lpszPasirinktasUzdSk;
   const unsigned char *m_lpszPateiktasUzdSk;
   const unsigned char *m_lpszTeisingai;
   const unsigned char *m_lpszNeteisingai;
   const unsigned char *m_lpszPasirinktasLaikas;

   KpstExercDataFileLine_tag(void);

} KpstExercDataFileLine;

// --------------------------------------- dialog definitions
#define KPST_SETUP_ICON_X (KPW_WND_MARGIN*3)
#define KPST_SETUP_ICON_Y (KPW_WND_MARGIN*3)
#define KPST_SETUP_ICON_WDT KPW_ICON_WDT
#define KPST_PROMPT_X (KPW_WND_MARGIN*3 /* +100 */)
#define KPST_NUM_OF_KEY_SEGM_CHARS 4
#define KPST_KEY_SEGM_EDIT_DX 45 // 40
#define KPST_NUM_OF_CHSUM_CHARS 1
#define KPST_CHSUM_EDIT_DX 15
#define KPSTLIC_CODE_EDIT_DASH_DX 5
#define KPST_DASH_DX 5
#define KPST_NUM_OF_LIC_CHARS (KPST_NUM_OF_KEY_SEGM_CHARS * 3 + 2)
#define KPST_NUM_OF_KEY_CHARS (KPST_NUM_OF_KEY_SEGM_CHARS * 4 + 3)
// #define KPST_NUM_OF_HIGH_CODE_BITS (KPST_NUM_OF_KEY_SEGM_CHARS * 3) // 12 // dabar kintamas – 12 (LicHigh + ChSum) arba 16 (RestDaysInit + ChSum)

// --------------------------------------- licence input window definitions
#define KPSTLIC_WND_MARGIN 30 // (KPW_WND_MARGIN*3)
#define KPSTLIC_CTRL_MARGIN KPW_WND_MARGIN

#define KPSTLIC_MAX_PROD_NAME_LEN 60

#define KPSTLIC_LINE_X1    0
#define KPSTLIC_LINE_X2    (KPSTLIC_WND_DX - (iWndBorderWdt * 2))
#define KPSTLICREM_LINE_X2 (KPSTLICREM_WND_DX - (iWndBorderWdt * 2))

#define KPSTLIC_HINT_DX 350

#define KPSTLIC_PROMPT_DX 110
#if((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
#define KPSTLIC_PROMPT_X (KPST_PROMPT_X + 40)
#else
#define KPSTLIC_PROMPT_X (KPST_PROMPT_X + 100)
#endif

#define KPSTLIC_HEAD_X (KPST_PROMPT_X+80)
#define KPSTLIC_HEAD_Y               KPSTLIC_WND_MARGIN
#define KPSTLIC_HEAD2_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD])

#define KPSTLIC_SUBHEAD_X (KPST_PROMPT_X+80)
#define KPSTLIC_SUBHEAD_Y           (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)

#define KPSTLIC_LINE1_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2)

#define KPSTLIC_HINT_X KPSTLIC_PROMPT_X
#define KPSTLIC_HINT1_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6)
#define KPSTLIC_HINT2_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)
#define KPSTLIC_HINT21_Y            (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  (iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)

#define KPSTLIC_CODE_PROMPT_X       KPSTLIC_PROMPT_X
#define KPSTLIC_CODE_PROMPT_DX      KPSTLIC_PROMPT_DX

#define KPSTLIC_CODE_CTRL_Y         (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  ((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN))

#define KPSTLIC_CODE1_EDIT_X        (KPSTLIC_PROMPT_X+KPSTLIC_CODE_PROMPT_DX+10)
#define KPSTLIC_CODE_EDIT_DASH1_X   (KPSTLIC_CODE2_EDIT_X-KPST_DASH_DX-KPSTLIC_CTRL_MARGIN)
#define KPSTLIC_CODE2_EDIT_X        (KPSTLIC_PROMPT_X+KPSTLIC_CODE_PROMPT_DX+10+(KPST_KEY_SEGM_EDIT_DX+KPSTLIC_CTRL_MARGIN+KPST_DASH_DX+KPSTLIC_CTRL_MARGIN))
#define KPSTLIC_CODE_EDIT_DASH2_X   (KPSTLIC_CODE3_EDIT_X-KPST_DASH_DX-KPSTLIC_CTRL_MARGIN)
#define KPSTLIC_CODE3_EDIT_X        (KPSTLIC_PROMPT_X+KPSTLIC_CODE_PROMPT_DX+10+(KPST_KEY_SEGM_EDIT_DX+KPSTLIC_CTRL_MARGIN+KPST_DASH_DX+KPSTLIC_CTRL_MARGIN)*2)

#define KPSTLIC_PERSPEJ_X           (KPSTLIC_PROMPT_X - 20) // KPSTLIC_PROMPT_X // (KPST_PROMPT_X+10)
#define KPSTLIC_PERSPEJ_Y           (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  ((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2)

#define KPSTLIC_LINE2_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+/*((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl*/+(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2/*+(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)*persp_fl*/+KPSTLIC_CTRL_MARGIN)

#define KPSTLIC_HINT3_Y             (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  ((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)*persp_fl  +KPSTLIC_CTRL_MARGIN)

#define KPSTLIC_BUT_Y               (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  ((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)*persp_fl  +KPSTLIC_CTRL_MARGIN*4)

// #define KPSTLIC_OK_BUT_X         ((KPSTLIC_WND_DX/2)-(KPW_BUTTON_WDT/2)-KPSTLIC_CTRL_MARGIN-KPW_BUTTON_WDT)
// #define KPSTLIC_OK_BUT_X         ((KPSTLIC_WND_DX/2)-KPSTLIC_CTRL_MARGIN-KPW_BUTTON_WDT)
#define KPSTLIC_OK_BUT_X            ((lic_pars_ptr?lic_pars_ptr->m_iWndWdt:KPSTLIC_WND_DX) - (2 * iWndBorderWdt) - KPSTLIC_WND_MARGIN - KPW_BUTTON_WDT - KPSTLIC_CTRL_MARGIN - KPW_BUTTON_WDT)

// #define KPSTLIC_SKIP_BUT_X       ((KPSTLIC_WND_DX/2)-(KPW_BUTTON_WDT/2))

// #define KPSTLIC_CANCEL_BUT_X     ((KPSTLIC_WND_DX/2)+(KPW_BUTTON_WDT/2)+KPSTLIC_CTRL_MARGIN)
// #define KPSTLIC_CANCEL_BUT_X     ((KPSTLIC_WND_DX/2)+KPSTLIC_CTRL_MARGIN)
#define KPSTLIC_CANCEL_BUT_X        ((lic_pars_ptr?lic_pars_ptr->m_iWndWdt:KPSTLIC_WND_DX) - (2 * iWndBorderWdt) - KPSTLIC_WND_MARGIN - KPW_BUTTON_WDT)

#define KPSTLIC_WND_DX              600 // (((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?600:560) // 560 // 530 // 500 // 450 // 400 // 500
#define KPSTLICREM_WND_DX           670
#define KPSTLIC_WND_DY              ((KPW_WND_BORDER_WDT_INI+KPW_WND_CAPTION_HGT_INI)+\
                                    (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+  ((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2  +(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)*persp_fl  +KPSTLIC_CTRL_MARGIN*4+KPW_BUTTON_HGT+KPSTLIC_CTRL_MARGIN*3)+\
                                    KPW_WND_BORDER_WDT_INI)

#define KPSTLIC_WND_DY_0            ((KPW_WND_BORDER_WDT_INI+KPW_WND_CAPTION_HGT_INI)+\
                                    (KPSTLIC_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*6+/*((iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1) * 2)*hint2_fl*/+(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN)*2/*+(iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTLIC_CTRL_MARGIN)*persp_fl*/+KPSTLIC_CTRL_MARGIN*4+KPW_BUTTON_HGT+KPSTLIC_CTRL_MARGIN*3)+\
                                    KPW_WND_BORDER_WDT_INI)


// --------------------------------------- key input window definitions --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define KPSTKEY_WND_MARGIN 30 // (KPW_WND_MARGIN*3)
#define KPSTKEY_CTRL_MARGIN KPW_WND_MARGIN

#define KPSTKEY_LINE_X1    0
#define KPSTKEY_LINE_X2    (KPSTKEY_WND_DX - (iWndBorderWdt * 2))

#define KPSTKEY_PROMPT_X (KPST_PROMPT_X+100) // KPSTLIC_PROMPT_X // KPST_PROMPT_X
#define KPSTKEY_PROMPT_DX 120 // 110
// #define KPSTKEY_EDIT_X (KPSTKEY_PROMPT_X + KPSTKEY_PROMPT_DX + 100)

#define KPSTKEY_HEAD_X (KPST_PROMPT_X+80)
#define KPSTKEY_HEAD_Y                                          KPSTKEY_WND_MARGIN
#define KPSTKEY_HEAD2_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD])

#define KPSTKEY_SUBHEAD_X (KPST_PROMPT_X+80)
#define KPSTKEY_SUBHEAD_Y                                      (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN)

#define KPSTKEY_LINE1_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2)

#define KPSTKEY_EXPL_X KPSTKEY_PROMPT_X
#define KPSTKEY_EXPL_Y                                         (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6)

#define KPSTKEY_EXPL_1_X KPSTKEY_PROMPT_X
#define KPSTKEY_EXPL_1_Y                                       (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1))

#define KPSTKEY_URL_X KPSTKEY_PROMPT_X
#define KPSTKEY_URL_Y                                          (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2)
#define KPSTKEY_URL_DX (KPSTKEY_WND_DX - KPSTKEY_URL_X - KPW_WND_MARGIN) // (KPSTKEY_WND_DX - 2 * KPSTKEY_URL_X)

#define KPSTKEY_LINE2_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*3)

#define KPSTKEY_HINT_X KPSTKEY_PROMPT_X
#define KPSTKEY_HINT1_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8)
#define KPSTKEY_HINT2_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1))
#define KPSTKEY_HINT3_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2)

#define KPSTKEY_INST_CODE_PROMPT_X KPSTKEY_PROMPT_X
#define KPSTKEY_INST_CODE_PROMPT_DX KPSTKEY_PROMPT_DX
#define KPSTKEY_INST_CODE_CTRL_X KPSTKEY_KEY1_EDIT_X
#define KPSTKEY_INST_CODE_CTRL_DX 160
#define KPSTKEY_INST_CODE_CTRL_Y                               (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2)

#define KPSTKEY_LINE3_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2)

#define KPSTKEY_HINT4_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*5)
#define KPSTKEY_HINT5_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*5+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1))

#define KPSTKEY_KEY_PROMPT_X KPSTKEY_PROMPT_X
#define KPSTKEY_KEY_PROMPT_DX KPSTKEY_PROMPT_DX
#define KPSTKEY_KEY_CTRL_Y                                     (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*5+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2)
#define KPSTKEY_KEY1_EDIT_X      (KPSTKEY_PROMPT_X+KPSTKEY_KEY_PROMPT_DX+10)
#define KPSTKEY_KEY_EDIT_DASH1_X (KPSTKEY_KEY2_EDIT_X-KPST_DASH_DX-KPSTKEY_CTRL_MARGIN)
#define KPSTKEY_KEY2_EDIT_X      (KPSTKEY_PROMPT_X+KPSTKEY_KEY_PROMPT_DX+10+(KPST_KEY_SEGM_EDIT_DX+KPSTKEY_CTRL_MARGIN+KPST_DASH_DX+KPSTKEY_CTRL_MARGIN))
#define KPSTKEY_KEY_EDIT_DASH2_X (KPSTKEY_KEY3_EDIT_X-KPST_DASH_DX-KPSTKEY_CTRL_MARGIN)
#define KPSTKEY_KEY3_EDIT_X      (KPSTKEY_PROMPT_X+KPSTKEY_KEY_PROMPT_DX+10+(KPST_KEY_SEGM_EDIT_DX+KPSTKEY_CTRL_MARGIN+KPST_DASH_DX+KPSTKEY_CTRL_MARGIN)*2)
#define KPSTKEY_KEY_EDIT_DASH3_X (KPSTKEY_KEY4_EDIT_X-KPST_DASH_DX-KPSTKEY_CTRL_MARGIN)
#define KPSTKEY_KEY4_EDIT_X      (KPSTKEY_PROMPT_X+KPSTKEY_KEY_PROMPT_DX+10+(KPST_KEY_SEGM_EDIT_DX+KPSTKEY_CTRL_MARGIN+KPST_DASH_DX+KPSTKEY_CTRL_MARGIN)*3)

#define KPSTKEY_LINE4_Y                                        (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*5+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*3)

#define KPSTKEY_BUT_Y                                          (KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*5+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6)

// #define KPSTKEY_OK_BUT_X (KPSTKEY_WND_DX/2-KPSTKEY_CTRL_MARGIN-KPW_BUTTON_WDT)
// #define KPSTKEY_CANCEL_BUT_X (KPSTKEY_WND_DX/2+KPSTKEY_CTRL_MARGIN)

#define KPSTKEY_OK_BUT_X     (KPSTKEY_WND_DX - (2 * iWndBorderWdt) - KPSTKEY_WND_MARGIN - KPW_BUTTON_WDT - KPSTKEY_CTRL_MARGIN - KPW_BUTTON_WDT)
#define KPSTKEY_CANCEL_BUT_X (KPSTKEY_WND_DX - (2 * iWndBorderWdt) - KPSTKEY_WND_MARGIN - KPW_BUTTON_WDT)

#define KPSTKEY_WND_DX 640 // KPSTLIC_WND_DX // 400 // 500

#define KPSTKEY_WND_DY    (KPW_WND_BORDER_WDT_INI+KPW_WND_CAPTION_HGT_INI+ \
                                                                KPSTKEY_WND_MARGIN  +iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl  +iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPSTKEY_CTRL_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*8+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*2+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*5+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTLIC_CTRL_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPSTKEY_CTRL_MARGIN*6+KPW_BUTTON_HGT+KPSTLIC_CTRL_MARGIN*3+\
                          KPW_WND_BORDER_WDT_INI)


// ---------------------------- unreg key window --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define KPSTREM_WND_MARGIN 30 // (KPW_WND_MARGIN*3)
#define KPSTREM_CTRL_MARGIN KPW_WND_MARGIN

#define KPSTREM_PROMPT_X (KPST_PROMPT_X+100) // KPSTLIC_PROMPT_X // KPST_PROMPT_X
#define KPSTREM_PROMPT_DX 170

#define KPSTREM_LINE_X1    0
#define KPSTREM_LINE_X2    (KPSTREM_WND_DX - (iWndBorderWdt * 2))

#define KPSTREM_HEAD_X (KPST_PROMPT_X+80)
#define KPSTREM_HEAD_Y                                          KPSTKEY_WND_MARGIN
#define KPSTREM_HEAD2_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD])

#define KPSTREM_SUBHEAD_X (KPST_PROMPT_X+80)
#define KPSTREM_SUBHEAD_Y                                      (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN)

#define KPSTREM_LINE1_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*3)

#define KPSTREM_EXPL_X KPSTREM_PROMPT_X
#define KPSTREM_EXPL_Y                                         (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6)

#define KPSTREM_EXPL_1_X KPSTREM_PROMPT_X
#define KPSTREM_EXPL_1_Y                                       (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1))

#define KPSTREM_URL_X KPSTREM_PROMPT_X
#define KPSTREM_URL_Y                                          (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2)
#define KPSTREM_URL_DX (KPSTREM_WND_DX - KPSTREM_URL_X - KPW_WND_MARGIN)

#define KPSTREM_LINE2_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*3)

#define KPSTREM_HINT_X KPSTREM_PROMPT_X
#define KPSTREM_HINT1_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8)
#define KPSTREM_HINT2_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1))
#define KPSTREM_HINT3_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2)

#define KPSTREM_CODE_PROMPT_X KPSTREM_PROMPT_X
#define KPSTREM_CODE_PROMPT_DX KPSTREM_PROMPT_DX
#define KPSTREM_CODE_CTRL_X (KPSTREM_PROMPT_X+KPSTREM_CODE_PROMPT_DX+10)
#define KPSTREM_CODE_CTRL_DX KPSTKEY_INST_CODE_CTRL_DX
#define KPSTREM_CODE_CTRL_Y                                    (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2)

#define KPSTREM_HINT4_X (KPSTREM_PROMPT_X - 20)
#define KPSTREM_HINT4_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN)

#define KPSTREM_LINE3_Y                                        (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*3)

#define KPSTREM_BUT_Y                                          (KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6)

// #define KPSTREM_OK_BUT_X ((KPSTREM_WND_DX-KPW_BUTTON_WDT)/2)
#define KPSTREM_OK_BUT_X (KPSTREM_WND_DX - (2 * iWndBorderWdt) - KPSTREM_WND_MARGIN - KPW_BUTTON_WDT)

#define KPSTREM_WND_DX 680 // KPSTLIC_WND_DX // 400 // 500

#define KPSTREM_WND_DY    (KPW_WND_BORDER_WDT_INI+KPW_WND_CAPTION_HGT_INI+ \
                                                                KPSTKEY_WND_MARGIN+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]*prod_name_2_fl+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*8+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*2+(iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 1)*2+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN+iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+KPW_WND_MARGIN*6+KPW_BUTTON_HGT+KPW_WND_MARGIN*3+ \
                          KPW_WND_BORDER_WDT_INI)

// hHideCloseButtonWnd ismatavimai
#define KPST_HIDE_CLOSE_BUT_WND_DX (3*KPW_ICON_BUTTON_WDT + 10)
#define KPST_HIDE_CLOSE_BUT_WND_DY (KPW_ICON_BUTTON_WDT + 5)


// --------------------- .ini file layout --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
   unsigned char m_lpszCmdStr[KP_MAX_FILE_LIN_WDT+1]; // command to start
      // %1 - priekabos failo kelio ir vardo vieta komandineje eiluteje (be tasko ir pletinio)
   int m_iProlShowTime; // kiek laiko (sec.) rodyti prologa, former iShowTime
   unsigned char m_lpszProlFName[KP_MAX_FNAME_LEN + 1]; // prologo failo vardas
   int m_iBitmapWdt;
   int m_iBitmapHgt;
   unsigned char m_lpszPwdWndName[KP_MAX_FNAME_LEN + 1]; // Password input window name
   unsigned char m_lpszOldPwd[TV_TAG_LEN + 1]; // old password (till 2007.12.11) Acrobato paleidimo slapta_odis
                                                // produktams su sertifikatais – sertifikato failo vardas be prievardþio (*.pfx)
   int m_iPwdEdCtrl; // order number of edit field in Password window
   int m_iPwdOkBut; // order number of OK button in Password window

   unsigned char m_lpszVolName[KP_MAX_FNAME_LEN + 1];
      // turi kelias paskirtis:
      //    kompakto tomo vardas kontrolei;
      //    serverio .exe vardo pradþia;
      //    vartotojo duomenø .fdf failo vardo pradþia (projekte MaTau5m duomenø failo vardas MaTau5e.dat);
      //    atmintuko pririðimo .ini failo vardo pradþia (projekto vardas), naudoja StartSel.exe.

   long m_lSerNo; // kompakto tomo ser. nr. kontrolei?
   unsigned char m_lpszBmpFName[KP_MAX_FNAME_LEN + 1]; // paveiksliuko failo vardas (.bmp)
   unsigned char m_lpszEpilFName[KP_MAX_FNAME_LEN + 1]; // epilogo komanda
   int m_iEpilShowTime; // kiek laiko (sec.) rodyti prologa
   unsigned char m_lpszPresetFName[KP_MAX_FNAME_LEN + 1]; // inicializacinio failo vardas, jo turinys perkeliamas i clipboard, pries paleidziant m_lpszCmdStr, former lpszIniFName
   unsigned char m_lpszRezFName[KP_MAX_FNAME_LEN + 1];
            // rezultatu failo vardas, pasibaigus m_lpszCmdStr,
            // prie jo prijungiamas clipboard turinys,
            // o jei m_lpszRezVar netuscias - tada kintamuju reiksmes is glob.js
   bool m_bCheckCD; // ar tikrinti, kad paleidziama komanda butinai butu CD
   bool m_bBound;   // ar registruotis, pririsant prie kompiuterio
   int m_iProdVer;  // produkto ID (PPP, 1..999) + 1000 * versijos ID (KK, 1..64), KKPPP (desimtaines pozicijos)
   unsigned char m_lpszProdName[KP_MAX_FNAME_LEN + 1]; // produkto versijos pavadinimas
   unsigned char m_lpszPublisher[KP_MAX_FNAME_LEN + 1]; // produkto gamintojo vardas
   unsigned char m_lpszRegURL[KP_MAX_FNAME_LEN + 1]; // i-neto adresas registravimuisi
   unsigned char m_lpszRezVar[KP_MAX_FNAME_LEN + 1]; // rezultatu kintamuju vardu sarasas
   bool m_bKumul; // ar kaupti duomenis i rezultatu faila, False - rasyti ant virsaus
   int m_iShuffCnt; // kiek pirmuju rezultatu lauku maisyti

   long m_lAttOff;  // priekabos failo pradzios adresas
                  // (faktiskai ka tik sutransliuoto kpstart.exe dydis baitais)
                  // ==0 - priekabos nera
   unsigned char m_lpszAttExt[KP_MAX_FTYPE_LEN + 1]; // priekabos failo vardo pletinys be tasko
                                        // (pats vardas generuojamas automatiskai)
   bool m_bCiDirect; // ar starteriui galima skaityti disko ID tiesiogiai
                     // tada i failus raso tik incrementus // ne, dabar raso visa susumuota CompID ir gerai

   long m_lFlashId; // flash ROM Serial number for Flash-dongled applications
   bool m_bCheckFlash; // ar priristi prie flash'o

   int m_iNumOfLics; // number of local server version licenses per seat, 0 - global server version

   unsigned char m_lpszTestCid[KPST_TXTCD_CHARS_PER_VAL_TID+1]; // testo kodas rezultatu identifikavimui

   int m_iIniLicID;  // kpstart.exe: bound license ID, if != 0 - valid only with lic. code specified
                     // kpstreg.exe: predefined license ID, default displayed value

   int m_iCompIdMode; // CompId calculating algorithms, could be combination of several flags,
                      // default value KPST_COMPID_BIOS_DATE

   bool m_bOnTop;    // ar visada maximizuoti, uzdengiant kitu aplikaciju langus
   bool m_bFullScr;  // ar langas pilnam ekrane - tada maximizuojamas kitaip

   bool m_bSubst;    // ar substinti paleidimo katalogà prie virtualaus disko ðaknies - èia seniems projektams

   unsigned char m_lpszPwd[TV_TAG_LEN + 1]; // password Acrobato paleidimo slapta_odis
                                             // produktams su sertifikatais (m_lpszOldPwd <> "") – sertifikato slaptaþodis
   bool m_bEboard;    // ar elektroninë lenta - mygtukai _emai etc.

   int m_iCheckSumOld;  // sum of all bytes in KpStIniData, field is used also for alignment to 4-bytes cluster boundary

   unsigned char m_lpszUserPwd[TV_TAG_LEN + 1]; // kpstart.exe ir kpstedp.exe paleidimo slaptaþodis // buvo vien tik kpstart.exe
   unsigned char m_lpszAdminPwd[TV_TAG_LEN + 1]; // atmintuko licencija (PUK), reikalauja, kai uþmirðti paleidimo slaptaþodá // buvo kpstedp.exe paleidimo slaptaþodis
   unsigned char m_lpszUserData[KP_MAX_FILE_LIN_WDT /* KP_MAX_FILE_LIN_LEN */ + 1]; // vartotojo duomenys – pavardë, ástaigos pavad., adresas, telefonas etc.

   bool m_bClearClipBrd; // ar valyti periodiðkai iðkarpinæ (kad nekopijuotø ir nespausdintø)

   int m_iUpdNum;  // produkto m_iProdVer atnaujinimo numeris, tas pats, kas ProdReg.mdb AddOnNumL, kas Installed registre ir vienetu didesnis uþ ProdVar ið Q_Svarbiinfo.js ir prodreg.tev.lt.

   bool m_bShowIE; // ar paleisti minimizuotà Internet Explorerá (reikia MIMOK projektams)

   bool m_bHideBkmrks;  // former: ar paleidus slëpti bookmarkø tabus kairëje lango pusëje (imituoti pelës dragà) (reikia vadovëliams)
                        // dabar – ar nustatyti registro raktà "Hide bookmarks after use"

   bool m_bSoundMuted; // ar uþgesintas garsas, áraðo (invertuoja) kpstart.exe mygtukas ant bitmapo

   unsigned char m_lpszWndName[KP_MAX_FNAME_LEN + 1]; // lango pavadinimas; pagal já:
                                                      // 1. Atnaujinimo programa kpstisvr.exe (komanda "CU=", KPSTIP_CHK_UPDATE_CMD) uþdaro produkto langà prieð atnaujindama
                                                      // 2. TODO: kpstart.exe maksimizuoja produkto langà
   bool m_bTestUpdates; // ar tikrinti atnaujinimus; lygiagretus poþymis registriniam; èia atmintukams
   bool m_bFindBut; // ar PDF projektas naudoja PDF mygtuk1 Find (XFS-iniai e. vadovëliai, pavyzdþiui) – tada reikia papildomø registro raktø

   bool m_bLicFlash; // ar pririðimas prie flash'o licencijuotas (kaip m_bBound, bet naudojamas ne kompo ID, o atmintuko kodas)

// -------------------------
   int m_iCheckSum;  // sum of all bytes in KpStIniData, field is used also for alignment to 4-bytes cluster boundary

} KpStIniData; // layout of .ini file

#define KPST_SIZEOF_INI_DATA_4 sizeof(KpStIniData)
#define KPST_SIZEOF_INI_DATA_OLD 4288 // sizeof(KpStIniData) prieð kodavimo m_iCheckSum ávedimà - tada reikia nustatyti m_iCheckSumNew = 0

// #ifdef KPST_MOVE_TO_KPHP11
extern KpStIniData IniDataBuf; // used also for offset calculations
// #endif

// initial .ini data for applications without external .ini file
// defined locally in low end application
// if InternalIniData[0]==0 - external .ini, should be loaded from <appname>.ini
extern unsigned char InternalIniData[sizeof(KpStIniData)];

// -------------------------------
#define KPSTAP_NUM_OF_SETS 3
#define KPSTAP_MAX_NUM_OF_FIELDS 50 // max PDF rezultatu kintamuju skaicius m_lpszRezVar
#define KPSTAP_MAX_NUM_OF_SHUFFLED_FIELDS 9 // sumaisymo masyvas issaugojamas long skaiciumi - <=9 skaitmenys
extern unsigned char lpszSupplementToMaxField[KPSTAP_MAX_NUM_OF_FIELDS+1]; // Tab-u eilute
#define WRITE_DATA_FILE_STR_BUF_LEN (KP_MAX_FNAME_LEN*2+100)

//--------------------------------
// IP serveriu duomenys
// http://127.0.0.1:49494/<komanda>
#define KPSTAP_PORT  49494  // portas kliento programos bendravimui su vidiniu TCP/IP miniserveriu duomenu apsikeitimui
#define KPST_IP_CMD_URL  ((const unsigned char *)"http://127.0.0.1:49494/")
// file to send as answer to TCP/IP request
// failas turi buti uzkoduotas su kpsenc.exe
// issiunciamas kaip atsakymas i tuscia HTTP uzklausa (kai nera komandos)
// naudojamas kaip poþymis, ar reikia IP serveriuko kpstisvr.exe paslaugø
// TODO naikinti – praneðimà kelti á kpstisvr.exe vidø, o kaip poþymá naudoti failo kpstisvr.bin existavimà
#define KPSTAP_SVR_DATA_FILE ((const unsigned char *)"kpstdf.bin")

#define KPSTAP_SVR_ANSWER_OK  ((const unsigned char *)"Kpstisvr-Ok:")
#define KPSTAP_SVR_ANSWER_ERROR  ((const unsigned char *)"Kpstisvr-Error:")

// IP komandø serveriuko failo vardas
#define KPSTISVR_EXE_FNAME ((const unsigned char *)"kpstisvr.bin")

// lokalaus rezultatu surinkimo serverio portas
// buvo naudojamas lokalaus licencijø/rezultatø serverio, dabar kaip porta naudojam ProdVer(+10000)
// #define KPSTAP_SPORT 49495

#define KPST_LOG_MSG_LEN (2*KP_MAX_FNAME_LEN + 100)


// ---------------------------------
// GetKpstFdfData() ir decfdf85.exe parametrai:
// source failo tipas:
typedef enum
{
   FdfInputFdf,      // = 0 fdf, galimai ið keliø áraðø, galimai uþkoduotø A85 eilute (kaip buvo decfdf85.exe iki 2007.01.31)
   FdfInputRawA85,   // = 1 pavienë A85 eilutë
   FdfInputRawAscii, // = 2 uþkoduoti ASCII laukai atskirti tabuliacijom

   FdfInputMax       // = 3

} FdfInputMode;

typedef enum
{
   FdfOutputRawAscii,   // = 0 áraðo á ascii eilutæ, laukai atskirti tabuliacijom, duomenu kodavima palieka koks buvo (taip kaip buvo decfdf85.exe iki 2007.01.31)
   FdfOutputAscii,      // = 1 áraðo á ascii, duomenu laukus iðkoduoja
   FdfOutputHead,       // = 2 iðveda tik laukø antraðèiø eilutæ, input failo neskaito
   FdfOutputFdf,        // = 3 fdf, galimai ið keliø laukø, u_koduoja A85

   FdfOutputMax         // = 4

} FdfOutputMode;

#define FIRST_FDF_FIELD 3 // pirmo fdf lauko objekto nr.
// 1 0 obj<</FDF<</Fields[<</T(PI)/V 3 0 R>>]>>>>
// endobj
// 3 0 obj

#define KPSTAP_NUM_OF_ADD_COMP_DATA 16

// --------------------------------
class KpStEdiDlg; // forward definition

// --------------------------------
// KpStdApp <-- KpCommonApp <-- KpStApp

typedef enum
{
   KpstLicFree,
   KpstLicLost,   // prarastas rysys su klientu - bus islaisvinta po
   KpstLicBusy,   // lic. uzimta, rysys su klientu atnaujintas

   KpstMaxOfLicStates
} KpstLicStates;

class LicStatus
{
public:
   KpstLicStates m_iLicState; // former bool m_bBusy;
   IN_ADDR m_Host; // unsigned char m_lpszHost[KP_MAX_FNAME_LEN + 1];
   int m_iSessionID;
   int m_iSecondsToKill; // kiek liko sekundziu iki pamestos licencijos isregistravimo

   LicStatus();
};

typedef enum
{
   KpStarterMode, // program starter kpstart (start.exe, lzdsh.exe...)
   KpStEditMode,  // .ini editor kpstedi (kpstedf.exe, edini.exe), server initialisator kpstlsvi.exe
   KpStRegMode,   // licence (un)registrator
   KpStLicSvrMode,// local LAN licence/result server (kpstlsvr.exe)
   KpStIpSvrMode, // local computer IP command server (kpstisvr.exe)
                  // reikia atskiro, nes Vista uþdraudë porto pakartotiná atidarymà klausymui,
                  // serveriukà reikia paleist vienà kartà visam laikui
   KpStrpdMode,   // kpstrpd.exe – tik (priregistruoto) atmintuko disko raidës suradimas

   KpStNumOfStModes_0

} KpStModes;

#define KpStNumOfStModes_2 KpStNumOfStModes_0 // masyvams


typedef enum
{
   KpStLocalFile, // C:\arkim\rezultatai\bebras_b.dat
   KpStServerFileDirect, // F:\arkim\rezultatai\bebras_b.dat
   KpStServerFilePost, // C:\arkim\rezultatai\sprendimai_bebras_b.dat irasyti per kpstlsvr.exe

   KpStNumOfDatFileTypes

} KpStDataFileTypes;


class KpGrpChk : public KpTextChk
{
public:
// unsigned char m_lpszText[KP_MAX_FILE_LIN_WDT + 1]; // <appname> konvertuotas pagal InnoSetup taisykles (lietuviðki pagal 1257, rusiðki – pagal 1251);  paveldëtas ið KpTextChk

   unsigned char m_lpszDownLoadFName[KP_MAX_FNAME_LEN + 1];
   long m_lDownLoadFSize;
   bool m_bSetupFl; // ar reikia diegti – ne ðiaip failas (meniu paveiksliukas), o komponento diegimas/atnaujinimas
   bool m_bRegFl; // ar reikia registruoti licencijà, licencija lauke m_lpszLicCode;
   unsigned char m_lpszLicCode[KPST_NUM_OF_LIC_CHARS + 1];
// SYSTEMTIME m_time; // lauko nereikia – tikrinam kurdami KpGrpChk áraðà // failo data – palyginimui su turimo keðe failo data, jei ateina ne naujesnis – nesiunèiam

   KpGrpChk(void);
};

#define KPSTGR_DOWNLOAD_PARS_DELIM ('#') // skirtukas StartGrpDownloadThread() parametrø eilutëje
#ifdef DebugStartGrp
#define KPSTGR_REFRESH_TIMEOUT 300 // StartGrp meniu refreðinam kas 0.3 sec
#else
#define KPSTGR_REFRESH_TIMEOUT 5000 // 5 sec. // (10 * 60 * 1000) // kas 10 min.
#endif

typedef union
{
   unsigned long m_lCryptCode;
   unsigned char m_lpszCryptPwd[4 + TV_TAG_LEN + 1];  // pirmi 4 baitai – invertuotas CryptCode, po to 400 baitø koduojamam slaptaþodþiui, gale nulis
                                                      // tarp tø pirmøjø 4 baitø irgi gali atsirasti nulis, jis eilutës pabaigos nereiðkia.
                                                      // po uþkodavimo nuliai gali atsirasti ir bet kur eilutës vidury – slaptaþodþio ilgá reikia atsiminti
                                                      //    prieð uþkodavimà
   int iAlignmentField; // unused field for alignment to 4-bytes cluster boundary
} CryptPwd; 

class KpStApp : public KpCommonApp
{
// public:
// int m_iCompId;    // computer specific ID
                     // or temporary generated session ID for local licence registration
                     // or remote client session ID received through licence registration request, m_iInstCode*
                     // iskeltas i kphp11 KP11_COMPID

// int m_iInstCount; // diegimu skaitilklis

// private:
// int m_iLicCode1;  // iskeltas i kphp11 KP11_LIC_CODE1
// int m_iLicCode2;  // iskeltas i kphp11 KP11_LIC_CODE2
// int m_iLicCode3;  // iskeltas i kphp11 KP11_LIC_CODE3
public:
// int m_iLicID;  // license ID, scanned from m_iLicCode*, entered by user
                  //             or scanned from m_iInstCode*, received from client
                  // iskeltas i kphp11 KP11_LICID

// int m_iLicHigh; // papildomas 12 bitø bibliotekinës licencijos kodas; iðtraukiamas ið ávedamo LicKodo, po to prijungiamas prie formuojamo DiegKodo
                   // buvo saugojamas data.dat kintamajame "LH"
                   // iðkeltas á  kphp11 KP11_LIC_HIGH

// int m_iRestDaysInit; // Gautas atsakymas su DiegRaktu ið prodreg.tev.lt apie licencijos galiojimo dienø skaièiø.
                        // Keièia tik DiegRakto skanavimas, vykdymo metu pastovus, kad DiegRaktas nesikeistø
                        // 0 reiðkia, kad licencija neterminuota
                        // iðkeltas á KP11_REST_DAYS_INIT
// long m_lRestMinutes; // dinamiðkai dekrementuojamas likæs licencijos galiojimo minuèiø skaièius
                        // iðkeltas á KP11_REST_MINS
// bool m_iRestDaysWarningShowed; // praneðimà apie likusias dienas reikia iðvedinëti tik vienà kartà – XFS kpstart inicializacijà kaþkodël iðkvietinëja du kartus // iðkeltas á RestDaysWarningShowed()

   LicStatus *m_pLicArray; // array of registared licences for local licence server
// private:
// diegimo kodas / installation code
// int m_iInstCode1; // iskeltas i kphp11 KP11_INST_CODE1
// int m_iInstCode2; // iskeltas i kphp11 KP11_INST_CODE2
// int m_iInstCode3; // iskeltas i kphp11 KP11_INST_CODE3
// int m_iInstCode4; // iskeltas i kphp11 KP11_INST_CODE4

// public:
// int m_iRemSesID;     // remote session id, scanned from m_iInstCode* or m_iRemCode*, received from the client
                        // used like m_iCompID
                        // iskelta i kphp11 KP11_REM_SESID
// int m_iRemLicID;     // remote licence id, scanned from m_iInstCode* or m_iRemCode*, received from the client
                        // should be Rand(0)
                        // iskelta i kphp11 KP11_REM_LICID
// int m_iRemProdVer;   // remote prodver, scanned from m_iInstCode* or m_iRemCode*, received from the client
                        // iskelta i kphp11 KP11_REM_PRODVER
// private:
// diegimo raktas / installation key
// saved in registry or entered as answer to installation code
// int m_iInstKey1; // iskelta i kphp11 KP11_INST_KEY1
// int m_iInstKey2; // iskelta i kphp11 KP11_INST_KEY2
// int m_iInstKey3; // iskelta i kphp11 KP11_INST_KEY3
// int m_iInstKey4; // iskelta i kphp11 KP11_INST_KEY4

// licencijos ismetimo kodas
// int m_iRemCode1; // iskelta i kphp11 KP11_REM_CODE1
// int m_iRemCode2; // iskelta i kphp11 KP11_REM_CODE2
// int m_iRemCode3; // iskelta i kphp11 KP11_REM_CODE3
// int m_iRemCode4; // iskelta i kphp11 KP11_REM_CODE4

// public:
   int /* KpStModes */ m_iKpStMode; // former bool m_bNormalStart; // False for .ini file editor

   UINT m_iProcCmdTimer;
   UINT m_iLicManagTimer;  // KPST_LIC_MANAG_TIMEOUT
                           // serveris dekrementuoja m_pLicArray[].m_iSecondsToKill,
                           // starterio klientas siuncia pakartotines registracijas
   UINT m_iSesCtrlTimer;   // sesijø kontrolës taimeris – kad neliptø viena ant kitos:
                           //    kpstart.exe siunèia "CD=" praneðimus kpstisvr.exe, praneðdamas, kad dar gyvas. (kas KPST_SES_PROLONG_TIMEOUT)
                           //    kpstisvr.exe, ilgiau negavæs tokio praneðimo (KPST_SES_RELEASE_TIMEOUT), sesijà atlaisvina
   bool m_bIPserver; // naudojamas IP serveris

// UINT m_iPrologTimer; // bitmapø filmuko rodymui

   UINT m_iFlashCheckTimer; // KPST_CHK_SER_FLASH_TIMEOUT - naudojamas tikrinimui, ar vis dar ikistas atmintukas

   unsigned char m_lpszFlashDevName[KP_MAX_FNAME_LEN /* KP_MAX_DEV_LEN */ + 1]; // kpstart.exe paleidimo aplankas be sleðo gale, macrokomandos {user} reikðmë
   unsigned char m_lpszProjDir[KP_MAX_FNAME_LEN + 1]; // Launcher.exe (kpsttrg.lib) paleidimo aplankas be sleðo gale, uþpildomas KpsTestReg(), naudojamas KpsUnReg() – Audrius iðregistravimà numeta vienu aplanku þemiau

   UINT m_iRestMinsTimer; // m_lRestMinutes dekrementavimo taimeris

// --------------------
   unsigned char **m_lpszaExtProcessed;      // StartCmdProcess() procesinamø plëtiniø sàraðas, galas – null
   unsigned char **m_lpszaExtViewers;        // atitinkamo plëtinio failo grotuvas; santykinis kelias nuo aktyvaus kelio arba nuo {m_lpszFlashDevName}\DAT0
   unsigned char *m_lpszaExtViewersBuffer;   // darbinis buferis m_lpszaExtProcessed[] ir m_lpszaExtViewers[] reikðmiø saugojimui
                                             // faktiðkai sukarpytas failo {m_lpszFlashDevName}\DAT0\players.ini turinys
private:
   KpTreeEntry *m_pUserJsList;   // sàraðas failø "%APPDATA%\\Adobe\\Acrobat\\6.0\\JavaScripts\\*.js",
                                 // nukopijuotø ið atmintuko "E:\\Matematika Tau-5E mokytojui\\AcroRead602\\Reader\\Javascripts\\*.js"
                                 // suformuoja CopyUserJscripts(), panaudoja DeleteUserJscripts()

// bool m_bMaximizeAcroWindow;

public:
   unsigned char m_lpszIniFName[KP_MAX_FNAME_LEN + 1]; // ðiaip sutampa su paleidëjo .exe failo vardo pradþia
                                                       // StartSel.exe nustato ið m_Ini.m_lpszVolName
#ifndef KPST_MOVE_TO_KPHP11
   KpStIniData m_Ini;
#endif

private:
   time_t m_lStartTime;

   HBITMAP m_hBitMap;
   HWND m_hBitmapWindow;
// HWND m_hBitmapCtrl;
   int m_iBitmapCnt; // filmuko bitmapø skaièius
// volatile int m_iCurBmp; // dabar rodomas filmuko bitmapas
   unsigned char **m_plpszBmpList; // prologo filmuko bitmapø vardø masyvas
   int *m_iaBmpTimes; // prologo filmuko bitmapø rodymo laikai milisekundëmis

public:
   HWND m_hMuteButton;

private:
   DWORD m_lProlThreadId;
   DWORD m_lEpilThreadId;
   DWORD m_lClipViewerThreadId; // thread ID of C:\Windows\System32\clipbrd.exe
   unsigned char m_lpszClipViewerFName[KP_MAX_FILE_LIN_LEN + 1]; // file name of of C:\Windows\System32\clipbrd.exe
public:
   HANDLE m_hCmdProcess; // process handle of main command
   HANDLE m_hCmdThread; // thread handle of main command
   DWORD m_lCmdThread; // thread ID of main command (tux_dbg)

   unsigned char m_lpszAttFname[KP_MAX_FNAME_LEN + 1]; // full attachment file path and name with extention

private:
// KpStEdiDlg *m_pRezFNameDialog;

   HRESULT m_RetcPr; // prologo/epilogo proceso paleidimo klaidos kodas

   unsigned char m_lpszDrivePath[KP_MAX_FILE_LIN_LEN + 1]; // "Q:" // stored subst'ed drive path for un'subst at the end

   unsigned char m_ClipBuf[KP_MAX_FILE_LIN_LEN + 1];
public:
   unsigned char m_FileDataBuf[KP_MAX_FILE_LIN_LEN + 1];
   unsigned char m_PdfParBuf[KP_MAX_FILE_LIN_LEN + 1];

private:
   HWND m_hLicDialogWindow;

public:
   HWND m_hLicCodeEdit1;
   HWND m_hLicCodeEdit2;
   HWND m_hLicCodeEdit3;

   HWND m_hLicOkButton;
   HWND m_hLicSkipButton;
   HWND m_hLicCancelButton;

private:
   HWND m_hKeyDialogWindow;

public:
   HWND m_hKeyUrlButton;

   HWND m_hInstCodeEdit; // read-only laukas diegimo kodo copy/past-inimui

   HWND m_hInstKey1Edit;
   HWND m_hInstKey2Edit;
   HWND m_hInstKey3Edit;
   HWND m_hInstKey4Edit;

   HWND m_hKeyOkButton;
   HWND m_hKeyCancelButton;

private:
   HWND m_hRemDialogWindow;

public:
   HWND m_hRemCodeEdit; // read-only laukas iðmetimo kodo copy/past-inimui

   HWND m_hRemOkButton;

private:
   HWND m_hHideCloseButtonWnd; // Acrobat-o uzdarymo mygtuku sirma - kad nepaspaustu
   HBITMAP m_hHideCloseButtonBmp;

   int m_iBkmrkFontSize; // Acro bookmarks font size
   bool m_bBookMarksHided; // Acro bookmarks already hidden

   int m_iNumWaveDevs;
   bool m_bSoundPlaying;
   DWORD m_lInitVolume;
   DWORD m_lCurVolume;

   bool m_bShiftFl;

public:
   unsigned char *m_pcListBuf; // buffer of readed data file KPSTAP_SVR_DATA_FILE to be sent over IP
   long m_lListBufLen; // data amount in pcListBuf
   KpSocket *m_pListSocket; // serverio socketas atsakymu i komandas perdavimui (kpstisvr) ir licencijø/rezultatø serverio broadcast socketas serverio adreso suradimui (kpstlsvr)
   KpSocket *m_pLicListSocket; // serverio listen socketas licenciju registravimo / rezultatø perdavimo uzklausoms priimti (kpstlsvr)
   DWORD m_lListThreadId;
   HANDLE m_hListThread;
   bool m_bInstanceLocked; // neleisti tik po vienà kpstart.exe instancijà.
                           // èia kpstisvr.exe kintamasis/semaforas, kpstart.exe pasiklausia POST-indama "CD="
   volatile bool m_bCheckUpdPending; // kpstisvr.exe vyksta update siuntimas – nereaguoti á nusiëmimo timeoutà theKpStAppPtr::m_iSesCtrlTimer

private:
   unsigned char m_CntPkgFmt[KP_MAX_FNAME_LEN + 1];
   unsigned char m_LicPkgFmt[KP_MAX_FNAME_LEN + 1];
   unsigned char m_BoltPkgFmt[KP_MAX_FNAME_LEN + 1];
   unsigned char m_CntRegKeyFmt[KP_MAX_FNAME_LEN + 1];
   unsigned char m_CntRegPath1[KP_MAX_FNAME_LEN + 1];
   unsigned char m_CntRegPath11[KP_MAX_FNAME_LEN + 1];
   unsigned char m_CntRegPath2[KP_MAX_FNAME_LEN + 1];
// unsigned char m_CntRegPath22[KP_MAX_FNAME_LEN + 1];

public:
   int m_iKpstRand0;    // konstanta KpstRand(0), kad nereiktu rekursiskai kviesti kphp11 RC

// produkto parametrai perskaitomi ið objekto RID ir perkeliami á A.js, IoRid()
   unsigned char m_lpszObjFileName[KP_MAX_FNAME_LEN + 1];

   int m_ProdVar; // 0-n, -1 – produktas neádiegtas
   unsigned char m_ProdDate[11]; // "2010.09.17"
   unsigned char m_ProdVersion[10]; // "2.01a"

   long m_lKpStArcStart[2];
   long m_lKpStArcLen[2];

// long m_lRestMinutesMain; // m_lRestMinutes kopija pagrindiniam threadui, atkelta èia, kad nesusektø m_lRestMinutes vietos
                            // panaikintas, nes m_lRestMinutes iðkeltas á KP11_REST_MINS

// --------------- grupiniø/prenumeruojamø leidiniø laukai
   unsigned char *m_lpszGrpCfgBuf; // tekstinis leidiniø grupës XML parametrø bloko pavidalas; UTF-8 koduotë; parsiunèia, sukuria ir uþpildo GrpSvrRequest()
   XmlNode *m_pGrpCfgNode; // leidiniø grupës XML parametrø blokas vidiniam formate, vien tago <pr> turinys
   unsigned char m_lpszGrpCfgFName[KP_MAX_FNAME_LEN + 1]; // leidiniø grupës XML parametrø bloko failo vardas
   KpTreeEntry *m_aGrpDownLoads; // grupinio leidinio komponentø / updeitø listboxo turinys; elementø duomenys – KpGrpChk
// HRESULT m_iGrpSvrRequestRetCode; // GrpSvrRequestThreadProc() gráþimo kodas
   unsigned char *m_lpszGrpMenu; // meniu failo turinys, suformuotas GenStartMenu(); kodavimas UTF-8
   KpPubDlg *m_pGrpKpPubDlg; // meniu (lentynos) dialogo objektas
// KpFileSys *m_pGrpKpFileSys; // meniu HTML failo turinio skaitymo objektas // naudoti m_pGrpKpPubDlg->m_pKpFileSys, kurti fiktyvø m_pGrpKpPubDlg, jeigu kà

   bool m_bSaveTestUpdatesToIni; // ar saugoti TestUpdates á .ini failà

   DWORD m_lGrpRefreshThreadId;                       // periodiðko meniu nusikrovimo threadas ProcessGrpThreadProc()
   volatile bool m_bGrpDownloadListProcessing;        // former m_bGrpDownloadFNameListProcessing;   
                                                      // semaforas – m_bGrpDownLoadThreadList arba m_GrpDownloadFNameList uþimtas
   volatile KpTreeEntry *m_GrpDownLoadThreadList;  // former m_bGrpDownLoadThreadTree; 
                                                      // setupus siunèianèiø StartGrpDownloadThreadProc() ir produktus naikinanèiø StartUninstThreadProc() threadø sàraðas – semaforas meniu atnaujinimo blokavimui
                                                      // jei yra bent vienas áraðas, m_lGrpRefreshThreadId meniu neatnaujina, tik siuntimo threadas StartGrpDownloadThreadProc() atnaujina progreso slankiklá
                                                      // sàraðas naudojamas ir threadø stabdymui iðeinant 
   volatile KpTreeEntry *m_GrpDownloadFNameList;   // ðiuo metu StartGrpDownloadThreadProc() siunèiamø <setup> lokaliø failø vardø sàraðas – semaforas dvigubo paklikinimo blokavimui
                                                      // formuojamas klikinant <mfree> ðablonà
                                                      // jeigu sàraðe toks downloadinamas failas jau yra, naujo nesiunèiam 

// int m_iCompId; // kompiuterio ID StartGrp.exe KpStApp::GrpSvrRequest(), iðkvieèiamam ne ið pagrindinio threado

   volatile bool m_bGrpRefreshFlg; // ar reikia atnaujinti paleidimo meniu (nereikia, kai, pvz., ðiuo metu narðoma iðorëje)
   volatile bool m_bGrpRefreshGlobalFlg; // jei == False, ðita reikðme atstatinëjami trumpam iðjungtas m_bGrpRefreshFlg (jei iðjungimas ávyko m_bGrpRefreshFlg trumpam iðjungus)  

   bool m_bForceGrpCfg; // ar krauti eiliná cfg (StartGrp meniu) forsuotai – nustatomas po tinklo klaidø; taip pat kol kas naudojamas ir kaip off-line indikatorius
   
   bool m_bLogin; // pagrindinis langas logino bûsenoje, ne lentynos darbinëj – kad þinotume, kur gráþt ið iðoriniø narðymø
   
// >>>>>> 2013-03-03  mp
#ifdef KPST_MULTI_DOCS
   bool m_bMDImaximized; // sending Ctrl+Shift+L to Adobe Reader flag – maximize MDI doument – only single time  
#endif
// <<<<<< 2013-03-03  mp
   
// --------------------------------------------------------------------
   KpStApp(void);
   virtual ~KpStApp(void);


   HRESULT InitStApp(HINSTANCE hInstance, const unsigned char *lpszIniFName, LPCSTR /* LPSTR */ lpCmdLine, KpStModes iStMode, // former InitApp
                        bool bCommonAppInitiated = False,   // bCommonAppInitiated = True, jeigu norim InitCommonApp(), tada atidaryt langus, o tik tada InitStApp()
                                                            // (nes ilgai uþtrunka ir langai neatsidaro)
                        bool *pbLicEntered = NULL,          // perduoda á CheckReg()
                        bool bCheckReg = True);              // jei False – netikrina ir neregistruoja licencijos                                               
   HRESULT SetTimers(void);

   HRESULT StartCmd(const unsigned char *lpszCmdLine = null, const unsigned char *lpszPwd = null); // jei lpszCmdLine != null ar lpszPwd != null,
                                                                                                   // ið pradþiø nustatomi KpStIniData::m_lpszCmdStr ir KpStIniData::m_lpszPwd
   HRESULT StartComplete(void);

   HRESULT WatchExec(void);   // klausosi komandu is clipboard; trina clipboard; tikrina TestFlash(); registruojasi á lic. serverá CheckLicSvr()
                              // IP komandø klausymasis iðkeltas á SockListenProc() // former ProcessCmds(), ProcessClipCmds()

   HRESULT CheckClipCmd(void); // tikrina eiline clipboard komanda
// HRESULT CheckSockCmd(void); // tikrina eiline HTTP komanda - iskelta i atskira threada
   HRESULT CreateSockThread(HINSTANCE hInstance); // start HTTP listenning thread SockListenProc()

   HRESULT StartSockProcess(void);  // start HTTP listening process kpstisvr.exe (kpstisvr.bin)
                                    // lokaliai apdorot IP neiðeina, nes Vista uþdraudë portø pakartotiná atidarymà;

   HRESULT SendIPSesAlive(void); // siunèia registravimos praneðimà "CD=" serveriui kpstisvr.exe

   HRESULT StartCmdThread(unsigned char *lpszCmdLine, const unsigned char *lpszPwd, const unsigned char *lpszCurDir, const unsigned char *lpszStartCmdLine);
                        // lpszCmdLine reikalavimai kaip StartCmdProcess()
                        // startuoja komandà atskiram threade; laukia, kol pasibaigs; tada suteikia fokusà AcroRead langui, jei toks yra;
                        // SockListenProc() paprogramë; paleidþia threadà StartCmdThreadProc()
                        // jei lpszPwd ne null, paleidþia mûsø AcroRead KpStapp aplinkoje (surenka slaptaþodá, maximizuoja etc.);
                        //    ðituo atveju naujas threadas nekuriamas (kphp11 nëra multitaskinis), failo uþdarymo nelaukiama
                        //    po iðorinio KpStapp .pdf failo uþdarymo fokuso gràþint kaip ir nereikia –
                        //    jo lygtai ir neturëtø bût galima uþdaryt, galima tik atvert dar kità failà spaudþiant naujà linkà

   HRESULT SetRestMinsTimer(void);  // paleidþia m_iRestMinsTimer – m_lRestMinutes dekrementavimà
                                    // iðkvieèiamas ið InitRestDays_RC() ir ResumeRestDays_RC(), taigi, tik ið HP11 vidaus, todël
                                    // galima naudoti nesaugius algoritmus ir negalima rekursiðkai kreiptis á HP11

   // hRetc - retc pries iskvieciant, kad nesidubliuotu pranesimai;
   // iTxtFileLocation – rezultatai.txt failo aplankas 
   HRESULT CloseStApp(HRESULT hRetc, LocalPaths iTxtFileLocation); 

private:
   void InitKeyFmts(void);

   HRESULT StartClipViewer(void);
   HRESULT CloseClipViewer(void);
public:
   HRESULT StartHp11(HINSTANCE hInstance);
// HRESULT StopHp11(void);

// HRESULT ReadIni(void);  // load text format .ini
// HRESULT WriteIni(void); // save text format .ini
   HRESULT LoadIni(void);  // load binary format .ini from m_lpszIniFName
   HRESULT LoadIniFile(const unsigned char *lpszIniFileName, bool bForceExternal, bool bOutMsg = True);
      // jei failo neranda, klaidos praneðimo neiðveda
      // bForceExternal – skaito iðoriná failà, nepaisydamas, ar yra vidinis hardkodinis (InternalIniData[0] != 0)
      // bOutMsg - ar iðvedinëti praneðimà apie blogà failo formatà KP_E_FILE_FORMAT
   HRESULT SaveIni(void); // save binary format .ini to m_lpszIniFName
   HRESULT SaveIniFile(const unsigned char *lpszIniFileName); // save binary format .ini

   HRESULT IoRid(const unsigned char *lpszObjFileName, bool bWrite);
      // skaito/raðo .tev dokumento objekto R/ID[] ir sinchronizuoja su KpStIniData::m_lpszPwd, KpStIniData::m_iProdVer, uþpildo m_lpszObjFileName
      // bWrite:
      //    False - perskaito KpStIniData::m_lpszPwd, KpStIniData::m_iProdVer
      //    True – áraðo KP11_INST_CODE* ir KP11_INST_KEY*

   HRESULT UnpackObjFiles(void); // iðtraukia failus ið archyvo .tev dokumente m_lpszObjFileName
   HRESULT DeleteObjFiles(void); // iðtrina prieð tai iðtrauktus failus ið archyvo .tev dokumente m_lpszObjFileName

private:
#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
   HRESULT SendIniToHp11(KpStIniData *pBuffer, bool bCheckErrors = False);
#endif
#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
   HRESULT GetIniFromHp11(KpStIniData *pBuffer);
#endif

   HRESULT InitBmpList(void);
   HRESULT PlayPrologue(void);
   HRESULT StopSlider(int *piCurrentIncrement);
   HRESULT ReleaseSlider(int iPreviousIncrement);
   HRESULT StartIE(void); // start minimized internet Explorer

   HRESULT TestCD(void);
   HRESULT SubstToLocal(void); // subst's local path to first free drive letter, when m_Ini.m_lpszCmdStr does not contain drives
   HRESULT Detach(void);
   HRESULT DelAttachment(void);
   HRESULT WaitForWindow(
      const unsigned char *lpszWndName,
      const unsigned char *lpszPwdText,
      int iOkBut, int iPwdEditCtrl,
      HANDLE hCmdProcess,
      HANDLE hCmdThread,
      DWORD lCmdThread,
      HWND hBitmapWindow);
   HRESULT WaitForPwd(void);
   HRESULT WaitForPwdCloses(void);
// HRESULT MaximizeAcroWindowProcess(void);
public:
   HRESULT MaximizeAcroWindowSingle(bool bForceMaximization /* bool bIfMinimizedOnly */);
private:
// HRESULT MinimizeIEWindow(void); // kai su realiu failu atsklanda.htm – jau atsidaro minimizuotas

   bool TestPradInf(void); // tikrina, ar yra langas "Pradinë informacija"; darbinë iðkvieèiama ið HideBookMarks()
   HRESULT DoHideBookMark(void /* int iBarWdt */); // darbinë iðkvieèiama ið HideBookMarks()
   HRESULT HideBookMarks(void); // pastumia bookmarkø tabà, jei m_Ini.m_bHideBkmrks, naudoja m_bBookMarksHided

   HRESULT CloseLaunchPrompt(void); // u_daro Acrobato perspëjimà apie paleid_iamà .exe failà
public:
   HRESULT CloseAutoPlay(void); // u_daro Windows kompakto ar atmintuko AutoPlay pasirinkimo langà
private:
   HRESULT CloseCompatibilityAssistant(void); // u_daro Vistos perspëjimà apie paleid_iamà ne_inomà .exe failà?
// !!!! TODO: HRESULT CloseCredentialManager(void); // u_daro Vistos perspëjimà apie paleid_iamà ne_inomà .exe failà

   HRESULT RenewDll(const unsigned char *lpszDllName, const unsigned char *lpszDest);
   HRESULT RenewDllsAll(void);

   HRESULT InitAcro50(void);
   HRESULT RestoreAcro50(void);

   HRESULT InitAcro(int iVers); // iVers versija * 100 (6.00 --> 600)
   HRESULT RestoreAcro(int iVers);

   HRESULT InitAcro60(void);
// HRESULT ResetAcro60(void);
   HRESULT RestoreAcro60(void);

   HRESULT InitAcro70(void);
   HRESULT RestoreAcro70(void);

   HRESULT InitAcro80(void);
   HRESULT RestoreAcro80(void);

   HRESULT InitAcro90(void);
   HRESULT RestoreAcro90(void);

public:
   HRESULT InitAcroSaveAs(void);
private:
   HRESULT RestoreDll(const unsigned char *lpszDllName, const unsigned char *lpszDest, HMODULE *phLibHandle);
   HRESULT RestoreDllsAll(void);

public:
#ifndef KPST_MOVE_TO_KPHP11
   HRESULT EnctBuf(void *pcBuffer, long lBufLen, int iSeed, bool bCheckErrors = False);
         // encrypts/decrypts buffer,
         // pcBuffer should be allocated in 4-bytes clusters, not shorter than lBufLen
   HRESULT EnctIniData(int iSize, bool bCheckErrors = False);    // encrypts/decrypts .ini file data using EnctBuf()
#endif

   HRESULT TestIniChSum(bool bCheckErrors = False){ return(EmuTv.CallRCCallBackRetC(KP_RC_CBIX_TestIniChSum, bCheckErrors)); }
   HRESULT SetIniChSum(void){ return(EmuTv.CallRCCallBack(KP_RC_CBIX_SetIniChSum)); }

private:
#ifdef KPST_MOVE_TO_KPHP11
   HRESULT GetIniElement(void *pValBuf, long lOffset, int iLen); // gets Ini data element value (from HP11)
#endif
   HRESULT GetIniElementIfNotStopped(void *pValBuf, long lOffset, int iLen); // gets Ini data element value (from HP11) if cMemBank[KP11_BLOCK_PROCESSING/2] == False
#if TRUE // reikia kpstreg.exe // #ifdef KPST_MOVE_TO_KPHP11
public:
   HRESULT SetIniElement(const void *pValBuf, long lOffset, int iLen); // sets Ini data element value (in HP11)
                              // iOffset - data element offset from start of KpStIniData
#endif

public:
   HRESULT GetIniCmdStr(unsigned char *lpszCmdStrBuf); // gets value of m_Ini.m_lpszCmdStr[KP_MAX_FILE_LIN_WDT+1]
   HRESULT GetIniProlShowTime(int *piProlShTim); // gets value of m_Ini.m_iProlShowTime
   HRESULT GetIniProlFName(unsigned char *lpszProlFNameBuf); // gets value of m_Ini.m_lpszProlFName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniBitmapWdt(int *piBmpWdt); // gets value of m_Ini.m_iBitmapWdt
   HRESULT GetIniBitmapHgt(int *piBmpHgt); // gets value of m_Ini.m_iBitmapHgt
   HRESULT GetIniPwdWndName(unsigned char *lpszPwdWndNameBuf); // gets value of m_Ini.m_lpszPwdWndName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniPwd(unsigned char *lpszPwdBuf); // gets value of m_Ini.m_lpszPwd[TV_TAG_LEN + 1];
   HRESULT GetIniOldPwd(unsigned char *lpszOldPwdBuf); // gets value of m_Ini.m_lpszOldPwd[TV_TAG_LEN + 1];
   HRESULT GetIniPwdEdCtrl(int *piPwdEdCtrl); // gets value of m_Ini.m_iPwdEdCtrl;
   HRESULT GetIniPwdOkBut(int *piPwdOkBut); // gets value of m_Ini.m_iPwdOkBut;
   HRESULT GetIniVolName(unsigned char *lpszVolNameBuf); // gets value of m_Ini.m_lpszVolName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniSerNo(long *plSerNo); // gets value of m_Ini.m_lSerNo;
   HRESULT GetIniBmpFName(unsigned char *lpszBmpFNameBuf); // gets value of m_Ini.m_lpszBmpFName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniEpilFName(unsigned char *EpilFNameBuf); // gets value of m_Ini.m_lpszEpilFName[KP_MAX_FNAME_LEN + 1];
   HRESULT GetIniEpilShowTime(int *piEpilShowTime); // gets value of m_Ini.m_iEpilShowTime;
   HRESULT GetIniPresetFName(unsigned char *lpszPresFNameBuf); // gets value of m_Ini.m_lpszPresetFName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniRezFName(unsigned char *lpszRezFNameBuf); // gets value of m_Ini.m_lpszRezFName[KP_MAX_FNAME_LEN + 1];
   HRESULT GetIniCheckCD(bool *pbCheckCD); // gets value of m_Ini.m_bCheckCD
   HRESULT GetIniBound(bool *pbBound); // gets value of m_Ini.m_bBound;
   HRESULT GetIniProdVer(int *piProdVer); // gets value of m_Ini.m_iProdVer
   HRESULT GetIniProdName(unsigned char *lpszProdNameBuf); // gets value of m_Ini.lpszProdName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniProdNameDec(unsigned char *lpszProdNameBuf); // iðtraukia ProdName ir galimai perkoduoja á einamàjà lentelæ (lenkiðkas produkto vardas visada 1257 lentelëje – gali reikëti perkoduoti á 1250)
   HRESULT GetIniWndName(unsigned char *lpszWndNameBuf); // gets value of m_Ini.lpszWndName[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniPublisher(unsigned char *lpszPublisherBuf); // gets value of m_Ini.m_lpszPublisher[KP_MAX_FNAME_LEN + 1]
   HRESULT GetIniRegURL(unsigned char *lpszRegURLBuf); // gets value of m_Ini.m_lpszRegURL[KP_MAX_FNAME_LEN + 1];
   HRESULT GetIniRezVar(unsigned char *lpszRezVarBuf); // gets value of m_Ini.m_lpszRezVar[KP_MAX_FNAME_LEN + 1];
   HRESULT GetIniKumul(bool *pbKumul); // gets value of m_Ini.m_bKumul
   HRESULT GetIniShuffCnt(int *piShuffCnt); // gets value of m_Ini.m_iShuffCnt;
   HRESULT GetIniAttOff(long *plAttOff); // gets value of m_Ini.m_lAttOff;
   HRESULT GetIniAttExt(unsigned char *lpszAttExtBuf); // gets value of m_Ini.m_lpszAttExt[KP_MAX_FTYPE_LEN + 1];
   HRESULT GetIniCiDirect(bool *pbCiDirect); // gets value of m_Ini.m_bCiDirect[KP_MAX_FTYPE_LEN + 1];
   HRESULT GetIniFlashId(long *plFlashId); // gets value of m_Ini.m_lFlashId;
   HRESULT GetIniCheckFlash(bool *pbCheckFlash); // gets value of m_Ini.m_bCheckFlash
   HRESULT GetIniLocalServer(bool *pbLocalServer); // gets value of m_Ini.m_bLocalServer
   HRESULT GetIniNumOfLics(int *piNumOfLics); // gets value of m_Ini.m_iNumOfLics
   HRESULT GetIniTestCid(unsigned char *lpszTestCidBuf); // gets value of m_lpszTestCid[KPST_TXTCD_CHARS_PER_VAL_TID+1]
   HRESULT GetIniIniLicID(int *piIniLicID); // gets value of m_Ini.m_iIniLicID
   HRESULT GetIniCompIdMode(int *piCompIdMode); // gets value of m_Ini.m_iCompIdMode
   HRESULT GetIniOnTop(bool *pbOnTop); // gets value of m_Ini.m_bOnTop
   HRESULT GetIniFullScr(bool *pbFullScr); // gets value of m_Ini.m_bFullScr
   HRESULT GetIniSubst(bool *pbSubst); // gets value of m_Ini.m_bSubst
   HRESULT GetIniEboard(bool *pbEboard); // gets value of m_Ini.m_bEboard
   HRESULT GetIniUserPwd(unsigned char *lpszUserPwdBuf); // gets value of m_Ini.lpszUserPwd[TV_TAG_LEN + 1];
   HRESULT GetIniAdminPwd(unsigned char *lpszAdminPwdBuf); // gets value of m_Ini.lpszAdminPwd[TV_TAG_LEN + 1];
   HRESULT GetIniUserData(unsigned char *lpszUserDataBuf); // gets value of m_Ini.lpszUserData[KP_MAX_FILE_LIN_WDT+1];
   HRESULT GetIniCheckSum(int *piCheckSum); // gets value of m_Ini.m_iCheckSum
   HRESULT GetIniClearClipBrd(bool *pbClearClipBrd); // gets value of m_Ini.m_bClearClipBrd
   HRESULT GetIniUpdNum(int *piUpdNum); // gets value of m_Ini.m_iUpdNum
   HRESULT GetIniShowIE(bool *pbShowIE); // gets value of m_Ini.m_bShowIE
   HRESULT GetIniHideBkmrks(bool *pbHideBkmrks); // gets value of m_Ini.m_bHideBkmrks
   HRESULT GetIniSoundMuted(bool *pbSoundMuted); // gets value of m_Ini.m_bSoundMuted
   HRESULT GetIniTestUpdates(bool *pbTestUpdates); // gets value of m_Ini.m_bTestUpdates
   HRESULT GetIniFindBut(bool *pbFindBut); // gets value of m_Ini.m_bFindBut
   HRESULT GetIniLicFlash(bool *pbLicFlash); // gets value of m_Ini.m_bLicFlash

   HRESULT SetIniCmdStr(const unsigned char *lpszCmdStrVal);
   HRESULT SetIniProlShowTime(int iProlShTim);
   HRESULT SetIniProlFName(const unsigned char *lpszProlFNameVal);
   HRESULT SetIniBitmapWdt(int iBmpWdtVal);
   HRESULT SetIniBitmapHgt(int iBmpHgtVal);
   HRESULT SetIniPwdWndName(const unsigned char *lpszPwdWndNameVal);
   HRESULT SetIniPwd(const unsigned char *lpszPwdVal);
   HRESULT SetIniOldPwd(const unsigned char *lpszOldPwdVal);
   HRESULT SetIniPwdEdCtrl(int iPwdEdCtrlVal);
   HRESULT SetIniPwdOkBut(int iPwdOkButVal);
   HRESULT SetIniVolName(const unsigned char *lpszVolNameVal);
   HRESULT SetIniSerNo(long lSerNoVal);
   HRESULT SetIniBmpFName(const unsigned char *lpszBmpFNameVal);
   HRESULT SetIniEpilFName(const unsigned char *EpilFNameVal);
   HRESULT SetIniEpilShowTime(int iEpilShowTimeVal);
   HRESULT SetIniPresetFName(const unsigned char *lpszPresFNameVal);
   HRESULT SetIniRezFName(const unsigned char *lpszRezFNameVal);
   HRESULT SetIniCheckCD(bool bCheckCDVal);
   HRESULT SetIniBound(bool bBoundVal);
   HRESULT SetIniProdVer(int iProdVerVal);
   HRESULT SetIniProdName(const unsigned char *lpszProdNameVal);
   HRESULT SetIniWndName(const unsigned char *lpszWndNameVal);
   HRESULT SetIniPublisher(const unsigned char *lpszPublisherVal);
   HRESULT SetIniRegURL(const unsigned char *lpszRegURLVal);
   HRESULT SetIniRezVar(const unsigned char *lpszRezVarVal);
   HRESULT SetIniKumul(bool bKumulVal);
   HRESULT SetIniShuffCnt(int iShuffCntVal);
   HRESULT SetIniAttOff(long lAttOffVal);
   HRESULT SetIniAttExt(const unsigned char *lpszAttExtVal);
   HRESULT SetIniCiDirect(bool bCiDirect);
   HRESULT SetIniFlashId(long lFlashId);
   HRESULT SetIniCheckFlash(bool bCheckFlashVal);
   HRESULT SetIniLocalServer(bool bLocalServer);
   HRESULT SetIniNumOfLics(int iNumOfLicsVal);
   HRESULT SetIniTestCid(const unsigned char *lpszTestCidVal);
   HRESULT SetIniIniLicID(int iIniLicIDVal);
   HRESULT SetIniCompIdMode(int iCompIdMode);
   HRESULT SetIniOnTop(bool bOnTopVal);
   HRESULT SetIniFullScr(bool bFullScrVal);
   HRESULT SetIniSubst(bool bSubstVal);
   HRESULT SetIniEboard(bool bEboardVal);
   HRESULT SetIniUserPwd(const unsigned char *lpszUserPwdVal);
   HRESULT SetIniAdminPwd(const unsigned char *lpszUserPwdVal);
   HRESULT SetIniUserData(const unsigned char *lpszUserDataVal);
   HRESULT SetIniCheckSum(int iCheckSum);
   HRESULT SetIniClearClipBrd(bool bClearClipBrdVal);
   HRESULT SetIniUpdNum(int iUpdNumVal);
   HRESULT SetIniShowIE(bool bShowIEVal);
   HRESULT SetIniHideBkmrks(bool bHideBkmrksVal);
   HRESULT SetIniSoundMuted(bool bSoundMutedVal);
   HRESULT SetIniTestUpdates(bool bTestUpdatesVal);
   HRESULT SetIniFindBut(bool bFindButVal);
   HRESULT SetIniLicFlash(bool bLicFlash);

   HRESULT GetIniPwdRC(unsigned char *lpszPwdBuf); // GetIniPwd() is kphp11 atminties, prieð tai turi bûti SendIniToHp11()

// glob.js functions
   HRESULT GetGlobalJsName(unsigned char *lpszGlobJsFNamBuf, unsigned char *lpszJsPathBuf = NULL);
                     // lpszGlobJsFNamBuf[KP_MAX_FNAME_LEN + 1] <-- "%APPDATA%\\Adobe\\Acrobat\\6.0\\JavaScripts\\glob.js"
                     // lpszJsPathBuf[KP_MAX_FNAME_LEN + 1] <-- "%APPDATA%\\Adobe\\Acrobat\\6.0\\JavaScripts"
                     // lpszJsPathBuf gali bûti NULL
private:
   HRESULT SaveGlobalJs(void);
#if FALSE
   HRESULT RestoreGlobalJs(void);
#elif FALSE
   HRESULT DeleteGlobalJs(void);
#else
   HRESULT DeleteGlobalJsVariables(void);
#endif

   HRESULT SetPdfPar(const unsigned char *lpszParName, int iValue); // sets parameter value in glob.js
   HRESULT SetPdfPar(const unsigned char *lpszParName, const unsigned char *lpszValue);  // jei lpszValue == null, parametrà iðtrina
   HRESULT SetPdfPar(const unsigned char *lpszParName, const unsigned char *lpszValue, const unsigned char *lpszPrefix, const unsigned char *lpszTail);
   HRESULT SetPdfPathPar(const unsigned char *lpszParName, const unsigned char *lpszPathValue); // nustato glob.js kintamàjá, '\\' ir ':' keisdamas á '/'

// -------------------
   HRESULT GetTMGrpPrmFName(unsigned char *lpszTMGrpPrmFNamBuf); // lpszTMGrpPrmFNamBuf[KP_MAX_FNAME_LEN + 1] <-- "%APPDATA%\\Adobe\\Acrobat\\7.0\\TMGrpPrm.sav"
   HRESULT UpdateTMGrpPrm(void);
   HRESULT RestoreTMGrpPrm(void);

// -------------------
   unsigned char m_StrBuf[KP_MAX_FILE_LIN_LEN + 1]; // internal buffer for GetPdfPars()
public:
// ið glob.js rezultatø jau nebeskaitom – kad senos ðiukðlës netrukdytø (pas Rolandà buvo kintamasis "klase")
   HRESULT GetPdfPars(unsigned char *lpszBuf, int iBufSize, const unsigned char **plpszaParNames, bool *pbDataReady);
      // analyzes PDF glob.js file
      // returns string, consisting of values of parameters from the list plpszaParNames,
      // delimited by tabs
      // plpszaParNames - NULL-terminated array of pointers to parameter name strings
private:
   HRESULT ScanPdfParValue(const unsigned char *lpszParNam, unsigned char **plpszValBuf);
      // internal procedure to scan single PDF parameter
public:
   HRESULT GetPdfPar(const unsigned char *lpszParName, unsigned char *lpszValue, int iBufSize);

   static HRESULT DecodePostMsg(unsigned char *lpszOutBuf, const unsigned char *lpszInStr, bool bCleanPluses = True);
      // konvertuoja %xx á aðtuonbitá kodà
      // lpszOutBuf can be the same as lpszInStr - buffer is shrinked only and scanned from the left to the right
      // bCleanPluses - ar keisti pliusus á tarpus (kam to iðvis reikia?); StartGrp tai trukdo

   static HRESULT EncodePostMsg(unsigned char *lpszOutBuf, const unsigned char *lpszInStr);
      // konvertuoja vald. simbolius lpszPostSpChars á %xx
      // lpszOutBuf turëtø bûti 3 k. didesnis u_ strlen(lpszInStr)

   HRESULT DecodePdfParText(unsigned char *lpszOutBuf, const unsigned char *lpszInStr); // former EncodePdfParText
      // converts string of PDF pars to 71 ctbl char string
      // lpszOutBuf can be the same as lpszInStr - buffer is shrinked only and scanned from the left to the right

   HRESULT EncodePdfParText(unsigned char *lpszOutBuf, const unsigned char *lpszInStr, int iOutBufLen);
   HRESULT EncodePdfParText(KpString *psOutStr, /* const */ KpString sInStr); // kaþkodël neveikia
      // konvertuoja 71 ctbl char eilutæ á PDF parametrø eilutæ su \\u0000 kodais

   HRESULT DecodePdfPath(unsigned char *lpszPathBuf, const unsigned char *lpszPdfPath);
   HRESULT EncodePdfPath(unsigned char *lpszPdfPathBuf, const unsigned char *lpszPath);

private:
   HRESULT GetClipPars(unsigned char *lpszBuf, int iBufSize, bool *pbDataReady);
      // gets clipboard contents and converts it as PDF pars string

public:
   HRESULT GetFilePars(unsigned char *lpszBuf, int iBufSize, bool *pbDataReady, LocalPaths iTxtFileLocation);
      // gets .txt file from My Documents as result data

   HRESULT GetRezFileName(unsigned char *lpszFNamBuf);
      // prie m_Ini.m_lpszRezFName prideda My Documents kelia, jei tik failo vardas, be kelio
      // lpszFNamBuf[KP_MAX_FNAME_LEN + 1]

   HRESULT FormAddData(unsigned char *lpszAddDataBuf, bool baDataFl[KPSTAP_NUM_OF_SETS], int iNumOfRecs, int iFieldCnt, bool bSrvFl);
      // formuoja kompo duomenu eilute buferyje lpszAddDataBuf[KP_MAX_FILE_LIN_LEN + 1]
      // bSrvFl - ar irasas is kpstlsvr.exe
   HRESULT WriteDataFile(const unsigned char *lpszBuf1, const unsigned char *lpszBuf2, const unsigned char *lpszBuf3, bool bSrvFl, bool bShowErrorMessages);
      // writes two Tab delimited parameter strings to m_Ini.m_lpszRezFName
      // strings - usually m_ClipBuf, m_PdfParBuf and m_FileDataBuf
      // compares whether not identical, tests whether not empty,
      // shuffles, adds additional common parameters before writing
      // bSrvFl - ar irasas is kpstlsvr.exe

   HRESULT WriteExercDataFile(const unsigned char *lpszInMsg); // raso uzduociu sprendimo busenos duomenu eilute i duom. faila

private:
   HRESULT TestSound(void);   // tests whether sound card is present and saves result to glob.js
public:
   HRESULT StopSound(void);
   HRESULT DoMute(void); // greitai nufadina garsà
   HRESULT SwitchMute(void); // invertuoja ir iðsaugoja m_Ini.m_bSoundMuted // negalima iðkvietinëti ið kito threado
private:
   HRESULT FadeSound(int iPerCent);

   HRESULT InitTestPar(void); // setc initial bad value of test_par to glob.js
   HRESULT SetRezSrvData(void);  // nustato rezultatu serverio adresa ir porta (ProdVer) i glob.js

   HRESULT SetAppPathPar(void); // nustato glob.js kintamàjá prog_path, '\\' ir ':' keisdamas á '/'

   HRESULT ResetSystemTime(SYSTEMTIME *p_TtPtr);   // suskaièiuoja senà failø datà, kad galima bûtø nustatyti naujai kuriamiems slaptiems failams
                                                   // anksèiau netgi nustatydavo system datà, po to reikëdavo atstatyti
   HRESULT CreateRegPath(const SYSTEMTIME *p_TtPtr, unsigned char *lpszPath); // sukuria lpszPath ir paskutiniam elementui nustato datà, esanèià *p_TtPtr
                                                                              // nepavykus sukurti, disko raidæ keièia á SystemDrive – tam atvejui, kai kompe nëra disko C:
//-----------------------
   HRESULT CallRCCallBackPtr(KpCommonCallBackIxs iCallBackIx, bool bCheckErrors = False); // iðkvieèia EmuTt::CallRCCallBack() su rc_pars.enc.pCallBackPars = this; – pointeriu á KpStApp::

//-----------------------
public:
   HRESULT CheckReg(HINSTANCE hInst, bool *pbLicEntered = NULL, bool bTestRestDays = False, bool bRunTime = False, bool bVerbose = True);
                              // compares stored installation key with computer ID,
                              //    requests an input of new key if unsuccessfull
                              //    pbLicEntered - returns True, if lic. entering dialog was opened
                              // bRunTime – iðkvietimas ið ProcessRestDays() – iðvedinëti praneðimus apie pasibaigusá lic. galiojimà ir 
                              //    neinicializuoti RestDays kintamøjø – jie dinamiðkai dekrementuojami, o CheckReg() iðkvietimas dar prieð iðsaugojimà
                              // bVerbose – jei False – nieko neklausinëja, neávedinëja licencijø ir neregistruoja, tik gràþina info apie licencijos legalumà   
                              

   HRESULT RemoveReg(HRESULT hRetc, HINSTANCE hInst); // removes installation
                                                      // hRetc - retc pries iskvieciant, kad nesidubliuotu pranesimai

//-----------------------
   HRESULT SaveRegSecData(HKEY hQueryKey, const unsigned char *lpszSubKey, const unsigned char *lpszVariable, long lValue); // slaptos info raðymas á registrà
                                                                                                                      // iðkvieèiama ið SaveRegCompID() ir SaveRegDatRestDaysInit()

   HRESULT GetRegSecData(HKEY hQueryKey, const unsigned char *lpszSubKey, const unsigned char *lpszVariable, long *plValPtr); // slaptos info skaitymas ið registro
                                                                                                                      // iðkvieèiama ið GetRegCompID() ir LoadRegDatRestDaysInit()

//-----------------------
   HRESULT GetPhysCompId(long *plPhysWithoutBolt = NULL);  // reads specific computer ID to m_iCompId,
                                 // (former GetCompId(), butinai po GetSavedCnt() - lic. skaitiklis)
                                 // m_iCompID turi buti jau uzpildytas arba bent 0
                                 // *plPhysWithoutBolt – gràþina FizID (be varþto)
   HRESULT GetTimCompId(void);   // reads random "computer ID" based on system timer for local licence server
   HRESULT GetRegCompID(HKEY hQueryKey, const unsigned char *lpszSubKey, int iProdVer, int *piIdOut); // reads compid from registry, subroutine of GetSavedCompID
private:
   HRESULT GetSavedCompIDFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, int iProdVer, int *p_comp_id); // darbinë GetSavedCompIDprodVer() paprogramë
public:
   HRESULT GetSavedCompIDprodVer(int iProdVer, int *piCompId); // darbinë paprogramë, iðkvieèiama ið GetSavedCompID();
   HRESULT GetSavedCompID(void); // reads stored m_iCompID, (former GetSavedCnt(), readed stored m_iInstCount), jei neranda - m_iCompID=0
                                 // perraso m_iCompID
// HRESULT SaveRegCompID(HKEY hQueryKey, const unsigned char *lpszSubKey, int iProdVer);  // saves compid to the registry, subroutine of SaveCompID
                                                                                          // pakeistas á SaveRegSecData(hQueryKey, lpszSubKey, "EstDispl", (comp_id * 10) ^ prod_ver);
private:
   HRESULT SaveCompIDFileSingle(const unsigned char *lpszPath, const SYSTEMTIME *p_tt, const unsigned char *pkg_name, bool bForceAdmin, int comp_id_calc, int comp_id); // darbinë SaveCompID() paprogramë
public:
   HRESULT SaveCompID(bool bForceAdmin); // saves m_iCompID to hidden registry key and to hidden file,
   HRESULT GetCommonCompID(void){ return(CallRCCallBackPtr(KP_RC_CBIX_GetCommonCompID)); } // common procedure to get and save CompID

private:
   HRESULT IncCompID(void);      // increments installation counter, former IncCount()
                                 // (former SaveCnt(), saved m_iInstCount)
                                 // iskelta i kphp11 KP_RC_INC_COMPID

//----------------------- programinio komp. id RemID funkcijos (varþtas)
   HRESULT GetSavedBoltRegSingle(HKEY hQueryKey, const unsigned char *lpszSubKey, long *plBolt); // skaito RemID ið vieno registro rakto
   HRESULT GetSavedBoltFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, long *plBolt); // skaito RemID ið vieno failo
   HRESULT GetSavedBolt(long *plBolt); // skaito áraðytà slaptuose failuose ir registre RemID, jei neranda – KP_E_KWD_NOT_FOUND 
   HRESULT SaveBoltRegSingle(HKEY hQueryKey, const unsigned char *lpszSubKey, long lBolt);
   HRESULT SaveBoltFileSingle(const unsigned char *lpszPath, const unsigned char *pkg_name, long lBolt, const SYSTEMTIME *p_tt);
   HRESULT SaveBolt(long lBolt); // iðsaugoja RemID slaptuose failuose ir registre 
   HRESULT RetrieveBolt(long *plBolt, long lFizId); // priima RemID ið remid.php
                                       // jei negauna – sugeneruoja atsitiktiná RemID
                                       // jeigu viskas gerai, gautà RemID reikðmæ iðsaugoja kompe
   HRESULT GetBolt(long *plBolt, long lFizId); // RemID perskaito ið slaptø failø (iðsikvieèia GetSavedBolt()), jeigu dar nëra – parsisiunèia ið serverio (RetrieveBolt())
   static long AddBoltFormula(long lFizId, long lRemID); // pati FizID komponavimo su RemID formulë, rezultatas – KompID
   HRESULT AddBolt(long *plCompId); // prikomponuoja RemID prie FizID, gaunamas KompID; iðkvieèia GetBolt() 

//-----------------------
// algoritmas:
//    aktyvacija:
//       CheckReg()
//          InitRestDaysHp11()
//             InitResumeRestDaysHp11(KP_RC_CBIX_InitRestDays)
//                InitRestDays_RC()
//                   InitResumeRestDays_RC( , , False)
//    paleidimas:
//       CheckReg()
//          ResumeRestDaysHp11()
//             InitResumeRestDaysHp11(KP_RC_CBIX_ResumeRestDays)
//                ResumeRestDays_RC()
//                   InitResumeRestDays_RC( , , True)
//                      LoadRegDatRestDaysInit()
//
//    rest days nuresetinimas po expired atsakymo ið serverio
//          ResetRestDaysHp11()
//             InitResumeRestDaysHp11(KP_RC_CBIX_ResetRestDays)
//                ResetRestDays_RC()
//                   InitResumeRestDays_RC( , , False)

   HRESULT SaveDatRestDaysInit(const unsigned char *lpszFileName, const RestTimeStruct *pOutData, bool bForceAdmin); // darbinë SaveRegDatRestDaysInit() paprogramë // former SaveDatRestDays()

   HRESULT LoadDatRestDaysInit(const unsigned char *lpszFileName, RestTimeStruct *pInData);

public:
   HRESULT SaveRegDatRestDaysInit(bool bForceAdmin);  // iðsaugoja KP11_REST_DAYS_INIT, m_lRestMinutes ir dabartiná laikà á visur kur pavyksta // former SaveRegDatRestDays()
                                                      // SaveCompID() analogas
                                                      // iðkvieèiama ið InitRestDaysInit_RC() ir ResumeRestDaysInit_RC() – HP11 callbackø – todël negalima rekursiðkai kviesti HP11 dar kartà

   HRESULT LoadRegDatRestDaysInit(void);  // Bando skaityti KP11_REST_DAYS_INIT, m_lRestMinutes ir áraðo laikà ið abiejø registro raktø ir ið abiejø slaptø failø
                                          // Kai kà nors randa – lygina perskaitytà áraðo laikà su dabartiniu. Jeigu didesnis – gràþina klaidà KP_E_REFUSED apie atsuktà laikrodá.
                                          // Jeigu nedidesnis – ið m_lRestMinutes atima laikø skirtumà
                                          // KP11_REST_DAYS_INIT palyginam su jau esanèiu, perraðom, tik jei naujas maþesnis arba senas buvo 0
                                          // jeigu niekur neranda – gràþina klaidà KP_E_KWD_NOT_FOUND
                                          // jeigu perskaièiuotas m_lRestMinutes <= 0, gràþina KP_E_TIMEOUT
//-----------------------
private:
   HRESULT GetSavedLicences(void); // reads stored m_pLicArray, jei neranda - KP_E_KWD_NOT_FOUND
   HRESULT GetRegLicences(HKEY hQueryKey, const unsigned char *lpszSubKey); // reads m_pLicArray from registry, subroutine of GetSavedLicences()
public:
   HRESULT SaveLicences(bool bForceAdmin); // kartu patikrina, ar adminas - lic. serveris tik adminams
private:
   HRESULT SaveRegLicences(HKEY hQueryKey, const unsigned char *lpszSubKey); // subroutine of SaveLicences()
public:
   HRESULT CountFreeLicences(int *iCnt); // suskaièiuoja laisvas licencijas

//-----------------------
private:
   static HRESULT GetKpstFdfLine(KpString *psOutStr, KpInStream *pInStream); // local function for GetKpstFdfData()
public:
   static HRESULT GetKpstFdfData(KpString *psOutStr, KpInStream *pInStream, FdfInputMode iInpMode, bool bOutMsg); // scans kpstart fdf file (data.dat), single text field, obsolete; perskaito pirmo lauko reikðmæ; data.dat atveju – lauko "PI="
   static HRESULT GetKpstFdfDataRec(XmlTagPars **ppOutDataRec, KpInStream *pInStream, FdfInputMode iInpMode, bool bOutMsg); // scans kpstart fdf file (data.dat, MaTau5e.dat, x7_1.fdf), multiple fields
   static HRESULT GetDataDatParStr(KpString *psDatStr, bool bOutMsg); // ið data.dat iðtraukia pirmo parametro reikðmæ ("PI")
   static HRESULT GetDataDatParStr(unsigned char *lpszDatBuf, bool bOutMsg); // lpszDatBuf[KP_MAX_FILE_LIN_WDT + 1]
   HRESULT GetSavedKeyReg(void); // reads stored installation key from registry to m_iInstKey*
                                 //    does not output any error message,
                                 //    returns KP_E_KWD_NOT_FOUND or KP_E_ILL_CODE in case of failure
                                 // paliktas tik suderinamumui su senais produktais, dabar liko tik per data.dat (SaveKeyDat() ir GetSavedKeyDat())
   HRESULT GetSavedKeyDat(KpString *psRegDatStr); // reads stored installation key form fdf data.dat to m_iInstKey*
                                 //    does not output any error message
                                 //    returns KP_E_KWD_NOT_FOUND or KP_E_ILL_CODE in case of failure
                                 //    *psRegDatStr - iðkoduotos data.dat reikðmës grà_inimui, gali bûti NULL
                                 // !!!! TODO perdaryti su GetDataDatVariable(..., "PI", ...); dabar skaito pirmà parametrà su GetKpstFdfData(), gali bûti ir koks nors kitas

// HRESULT GetLicHigh(void); // perskato data.dat kintamàjá "LH" á m_iLicHigh

   static HRESULT SaveKpstFdfDataRec(const XmlTagPars *pDataRec, KpOutStream *pOutStream, FdfOutputMode iOutMode, bool bOutMsg);
                                 // áraðo fdf failà (data.dat, MaTau5e.dat, x7_1.fdf), multiple fields
                                 // bOutMsg - ar iðvedinëti klaidø praneðimus

   HRESULT EncAtmKod(KpString *sAtmKod, KpString sFileName); // perkoduoja sAtmKod, naudodamas sFileName kaip kaukæ

   HRESULT GetAtmKodTxt(unsigned char *lpszAtmKodBuf);   // iðtraukia tekstiná atmintuko kodà (toká, koks ant birkos)
                                 // lpszAtmKodBuf[TV_TAG_LEN + 1]
                                 // prad_ià ið data.dat failo, galà ið .ini, kuris turi bûti perskaitytas ið atmintuko
                                 // (turi jau bûti iðkviesta TestFlash()); lpszAtmKodBuf[TV_TAG_LEN + 1]

private:
// HRESULT SaveKeyReg(void);     // saves m_iLicCode*, m_iInstKey* to registry
   HRESULT SaveKeyDat(void);     // saves m_iInstCode*, m_iInstKey* to fdf data.dat
                                 // !!!! TODO – jei failas yra, áraðinëti tik kintamàjá SetDataDatVariable(..., "PI", ...), dabar bet kokiu atveju kloja visà failà ant virðaus

   HRESULT DelSavedKey(void);

//-----------------------
   HRESULT CheckPrivileges(const unsigned char *lpszMsg);
                                 // naudojama pries ivedant licencija, tikrina, ar gales irasyti Key
                                 // lpszMsg - neigiamo pranesimo tekstas

// -------------
   HRESULT InitLicId(void);      // m_iLicID=KpstRand(0);
public:
   HRESULT FormatLicCodeFull(unsigned char *lpszLic); // formats textual representation of licence code m_iLicCode*

   HRESULT ScanLic(const unsigned char *lpszLic);  // scans restored or entered license code to m_iLicCode*
                                                   // does not output error messages
                                                   // lpszLic turi bûti jau su nupjautu LicHighChSum

   HRESULT UnpackLic(void);      // tests m_iLicCode* for errors, unpacks it to m_iLicID
                                 // iskeltas i kphp11 KP_RC_UNPACK_LIC
                                 // does not output error messages
                                 // lygina iðtrauktà prodver su m_iProdVer, gràþina klaidà KP_E_ILL_CODE, jei nesutampa

   HRESULT ScanLicTmp(long *piLicID, int *piProdVer, const unsigned char *lpszLicCode);
                                 // iðtraukia LicID ir ProdVer ið LicCode
                                 // m_iProdVer, m_iLicID ir m_iLicCode* nekeièia
                                 // lpszLicCode – su LicHigh
                                 // LicHigh primontuoja prie gràþinamo *piLicID

   HRESULT CalcLicCode(void);    // suskaiciuoja m_iLicCode*; naudoja m_iLicID
                                 // iskeltas i kphp11 KP_RC_CALC_LIC_CODE

   HRESULT ReCalcLicCode(void);  // suskaiciuoja m_iLicID ir m_iLicCode*; naudoja m_iInstCode*
                                 // naudojamas po GetSavedKeyDat()
                                 // m_iCompID ir m_iProdVer neistraukineja, palieka anksciau buvusius
                                 // m_iLicCode* teisingumo netikrina, o gal reiketu???!!!
                                 // iskviecia CalcLicCode()
                                 // iskeltas i kphp11 KP_RC_RECALC_LIC_CODE

// -------------
   HRESULT FormatInstCodeFull(unsigned char *lpszCode); // formats textual representation of installation/remove code m_iInstCode*
                                                        // former FormatCodeFull()
   HRESULT ScanInstCodeFull(const unsigned char *lpszCode); // former ScanCodeFull()
private:
   HRESULT CalcInstCode(void);   // fills m_iInstCode*, uses m_iLicID, m_iCompID, m_iProdVer
                                 // naudojamas po GetSavedKeyReg()
                                 // iskeltas i kphp11 KP_RC_CALC_INST_CODE
public:
   HRESULT UnpackInstCode(void); // server part unpacking of incomming client m_iInstCode*
                                 // converts m_iInstCode* to m_iRemLicID, m_iRemProdVer ir m_iRemSesID;
                                 // skirtingai nuo ReCalcLicCode(), m_iLicCode* neperskaiciuoja
                                 // former ScanInstCode()
                                 // iskeltas i kphp11 KP_RC_UNPACK_INST_CODE
                                 // panasu, kaip kliento puses ReCalcLicCode()

   HRESULT ParseLicCodeHigh(const unsigned char *lpszLicCodeHigh); // iðtraukia LicHigh ir paskanuoja likusá lic. kodà po ávedimo dialogo ar perduodant cmd. line parametru

// -------------
   HRESULT FormatInstKeyFull(unsigned char *lpszKey); // former FormatKeyFull
private:
   HRESULT ScanInstKeyFull(const unsigned char *lpszKey); // scans downloaded/restored installation key to m_iInstKey*
public:
   HRESULT CalcInstKey(void); // naudojamas tik serverio, gerai suskaiciuoja tik jei uzklausa atitiko reikalavimus (CheckRequest())
                              // naudoja m_iInstCode*
                              // iskeltas i kphp11 KP_RC_CALC_INST_KEY
                              // atsizvelgia i KP11_BLOCK_PROCESSING
// -------------
   HRESULT FormatRemCodeFull(unsigned char *lpszRemCode);
public:
   HRESULT ScanRemCodeFull(const unsigned char *lpszCode);
private:
   HRESULT CalcRemoveCode(void); // fills m_iInstCode*
                                 // iskelta i kphp11 KP_RC_CALC_REM_CODE
public:
   HRESULT UnpackRemCode(void);  // server part unpacking of incomming client m_iRemCode*
                                 // converts m_iRemCode* to m_iRemLicID, m_iRemProdVer ir m_iRemSesID;
                                 // iskelta i kphp11 KP_RC_UNPACK_REM_CODE

// -------------
   HRESULT ExtractHigh(unsigned char *lpszCodeBuf, int *piHighCode, int iNumBytes); // iðtraukia á vyresniuosius pirmøjø iNumBytes 32-ainiø skaitmenø bitus ákoduotà reikðmæ --> *piHighCode
                                                                                    // lpszCodeBuf vyr. bitus nuvalo – lieka ðvarus ankstesnio formato hex. kodas
                                                                                    // lpszCodeBuf su brûkðneliais, darbo metu iðmeta, po to vël ástato
                                                                                    // piHighCode gali bûti NULL, tada tik nuvalo vyr. bitus nuo lpszCodeBuf
   HRESULT AddHigh(unsigned char *lpszCodeBuf, int iHighCode, int iNumBytes); // prideda iNumBytes bitø kodà prie lpszCodeBuf pirmøjø iNumBytes skaitmenø
                                                                              // lpszCodeBuf su brûkðneliais, darbo metu iðmeta, po to vël ástato

   HRESULT SaveLicHighHp11(int iLicHighChSum);  // iðkvieèia KP_RC_SAVE_LIC_HIGH_RTN: iðskaido iLicHighChSum á LicHigh ir ChSum, patikrina ChSum, o LicHigh áraðo á KP11_LIC_HIGH
                                                // iLicHighChSum – 8 bitai LicHigh + 4 bitai ChSum

   HRESULT GetLicHighHp11(int *piLicHighChSum); // iðkvieèia KP_RC_GET_LIC_HIGH_RTN: paima LicHigh ið KP11_LIC_HIGH ir prideda ChSum
                                                // gràþina *piLicHighChSum – 8 bitus LicHigh + 4 bitus ChSum

   HRESULT SaveRestDaysInitHp11Common(int iRestDaysInitChSum, int iOpCode);   // iðkvieèia KP_HP11 funkcijà pagal iOpCode: KP_RC_SAVE_REST_DAYS arba KP_RC_SAVE_REST_DAYS_AND_RC
                                                                              // iRestDaysInitChSum - 12 bitø RestDaysInit + 4 bitai ChSum
                                                                              // numeta ChSum nuo iRestDaysInitChSum, jà patikrina, o reikðmæ RestDaysInit áraðo á KP11_REST_DAYS_INIT
                                                                              // ávykdo papildomà callback funkcijà, jei iOpCode == KP_RC_SAVE_REST_DAYS_AND_RC (SaveRestDaysWithRC())
                                                                              // former SaveRestDaysCommon(int iValue, int iOpCode): nustato KP11_REST_DAYS_INIT = iValue ^ KP11_LIC_HIGH
                                                                              // former: KP11_LIC_HIGH jau turi bûti nustatytas
   HRESULT SaveRestDaysInitHp11(int iRestDaysInitChSum) { return(SaveRestDaysInitHp11Common(iRestDaysInitChSum, KP_RC_SAVE_REST_DAYS)); } // former SaveRestDays()

   HRESULT SaveRestDaysInitHp11WithRC(int iRestDaysInitChSum, int iOpCode, int iRCOpCode); // SaveRestDaysInitHp11Common() ir KP_RC_CALLBACK(iRCOpCode) // former SaveRestDaysWithRC()

   HRESULT SaveRestDaysInitHp11AndInit(int iRestDaysInitChSum) // SaveRestDaysInitHp11WithRC() paleidþia naujà galiojimo laiko dekrementà // former SaveRestDaysAndInit()
      { return(SaveRestDaysInitHp11WithRC(iRestDaysInitChSum, KP_RC_SAVE_REST_DAYS_AND_RC, KP_RC_CBIX_InitRestDays)); }
   // { return(SaveRestDaysInitHp11Common(iRestDaysInitChSum, KP_RC_SAVE_REST_DAYS_AND_INIT)); }
   HRESULT SaveRestDaysInitHp11AndResume(int iRestDaysInitChSum) // SaveRestDaysInitHp11WithRC() pratæsia ankstesná galiojimo laiko dekrementà // former SaveRestDaysAndRestore()
      { return(SaveRestDaysInitHp11WithRC(iRestDaysInitChSum, KP_RC_SAVE_REST_DAYS_AND_RC, KP_RC_CBIX_ResumeRestDays)); }
   // { return(SaveRestDaysInitHp11Common(iRestDaysInitChSum, KP_RC_SAVE_REST_DAYS_AND_RESUME)); }

   HRESULT InitResumeRestDaysHp11(KpCommonCallBackIxs iCallBackIx);  // raðo KP11_REST_DAYS_INIT á failà, kalkuliuoja m_lRestMinutes
                                                                     // bendra paprogramë InitRestDaysHp11() (registratoriui) ir ResumeRestDaysHp11() (starteriui)
                                                                     // iCallBackIx gali bûti KP_RC_CBIX_ResumeRestDays arba KP_RC_CBIX_InitRestDays
   HRESULT InitRestDaysHp11(void){ return(InitResumeRestDaysHp11(KP_RC_CBIX_InitRestDays)); }
   HRESULT ResumeRestDaysHp11(void){ return(InitResumeRestDaysHp11(KP_RC_CBIX_ResumeRestDays)); }
   HRESULT ResetRestDaysHp11(void){ return(InitResumeRestDaysHp11(KP_RC_CBIX_ResetRestDays)); }

   HRESULT GetRestDaysInitHp11(int *piRestDaysInitChSum);   // gràþina 12 bitø KP11_REST_DAYS_INIT (RestDaysInit) + 4 bitai ChSum
                                                            // former GetRestDays() // former GetRestDaysMasked(): gràþina KP11_REST_DAYS_INIT ^ KP11_LIC_HIGH

   HRESULT ProcessRestDays(void); // RestDays taimerio procedûra – minuèiø dekrementavimas ir iðsaugojimas
                                  // iðkvieèia ProcessRestDays_RC() per KP_RC_CALLBACK
                                  
   bool RestDaysWarningShowed(void); // gràþina True, jei praneðimas apie pasibaigusá/besibaigiantá lic. galiojimo laikà kà tik iðvestas – iðvedinëti nereikia // former m_iRestDaysWarningShowed
                                  
// -------------
private:
   HRESULT TestKey(void);     // tests whether new entered or previous saved installation key
                              //    m_iInstKey* corresponds to m_iInstCode* (m_iCompId/m_Ini.m_iProdVer/...lic)
                              //    does not output any error message
                              // affects KP11_BLOCK_PROCESSING
                              // iskeltas i kphp11 KP_RC_KEY_CHECK_INTERN
                              // grazina KP_E_ILL_CODE, jei m_iInstKey* neatitinka m_iInstCode*
                              // grazina KP_E_REFUSED, jei nesutampa KpStApp::m_iLicID su KpStApp::m_Ini.m_iIniLicID
                              // jeigu viskas gerai, uþregistruoja sertifikatà
public:
   HRESULT UnRegSert(void); // panaikina sertifikatà

   HRESULT CheckResRequest(void){ return(CallRCCallBackPtr(KP_RC_CBIX_CheckResRequest)); }
                              // lic. rezervavimo uzklausos tikrinimas serveryje - m_iRemLicID==Rand(0), m_iRemProdVer=m_iProdVer
                              // tikrina atejusi m_iRemSesID - ar yra toks uzregistruotas, jei naujas, uzregistruoja laisva licencija, jei dar yra
                              // affects KP11_BLOCK_PROCESSING
   HRESULT CheckRelRequest(void){ return(CallRCCallBackPtr(KP_RC_CBIX_CheckRelRequest)); }
                              // lic. atlaisvinimo uzklausos tikrinimas serveryje - m_iRemLicID==0, m_iRemProdVer=m_iProdVer
                              // Tikrina atejusi m_iRemSesID - ar yra toks uzregistruotas, jei taip - licencija islaisvina
private:
   HRESULT EnterLicence(HINSTANCE hInst, bool bUnReg, bool bEntered);
               // iveda is klaviaturos licenzijos koda
               // bUnReg: False - registravimas, True - isregistravimas
               // bEntered - jei True - ivedineti nereikia, tik patvirtinti
   HRESULT OpenLicWindow(bool bUnReg, bool bEntered);
               // sukuria ir atidaro licenzijos dialogo langa
               // bUnReg: False - registravimas, True - isregistravimas
               // bEntered - jei True - ivedineti nereikia, tik patvirtinti
public:
   HRESULT GetRegUrl(unsigned char *lpszServerBuf, unsigned char *lpszUrlBuf, const unsigned char *lpszHttpQuery);
               // lpszServerBuf[KP_MAX_FNAME_LEN + 1], suformuojamas serverio adresas: http://www.tev.lt/prodreg.php
               // lpszUrlBuf[KP_MAX_FNAME_LEN + 1], suformuojamas pilnas URL: http://www.tev.lt/prodreg.php?instcode=RLL4-8R34-GR52-5U2U
               // abu gali bûti null
private:
   HRESULT SendCodeHttp(HRESULT hRetc, const unsigned char *lpszHttpQuery, bool bRecKey, bool bForcedTestRestDaysMsg = False);
               // uzregistruoja/ismeta registracija per Interneta
               // hRetc - retc pries iskvieciant, kad nesidubliuotu pranesimai
               // lpszHttpQuery – KPST_HTTP_REGISTER ar KPST_HTTP_REMOVE
               // bRecKey – ar priimti diegimo raktà kaip atsakymà
               // bForcedTestRestDaysMsg – iðkvietimas ið ProcessRestDays() iðvedinëti praneðimus apie pasibaigusá lic. galiojimà, 
               //    nekreipiant dëmesio á m_iRestDaysWarningShowed – èia WM_TIMER praneðimas, negerai, jeigu tyliai nusiims  

   HRESULT EnterNewKey(HINSTANCE hInst, const unsigned char *lpszHint1);  // iveda is klaviaturos diegimo rakta
   HRESULT OpenKeyWindow(const unsigned char *lpszHint1);  // sukuria ir atidaro diegimo rakto dialogo langa

   HRESULT OpenRemWindow(const unsigned char *lpszHint1);
   HRESULT RemCodeInfo(HINSTANCE hInst, const unsigned char *lpszHint1);

public:
   HRESULT CheckLicSvr(int iTimerId); // iTimerId - LOWORD(msg.wParam) ið praneðimo WM_TIMER

   HRESULT TestFlashId(long lFlashId, bool *pbFound, int *piNumOfFlashes, unsigned char cDriveLetter); // cDriveLetter - testuojamo flash disko raidë
   HRESULT TestFlash(void);

// ---------------------------
   HRESULT GetProdVerRegVariableStr(unsigned char *lpszValBuf, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName); 
                                                // suranda ProdVer registro parametro reikðmæ
                                                // ið pradþiø ið HKCU, jei neranda – ið HKLM
                                                // lpszValBuf[KP_MAX_FNAME_LEN + 1], nes ten daugiausia katalogai/failø keliai (diegimo, paleidimo, iðmetimo)
                                                // jei neranda, gràþina KP_E_KWD_NOT_FOUND, praneðimo neiðveda
   HRESULT ExtractProdVerRegVariableStr(unsigned char *lpszValBuf, /* const */ XmlNode *pCurNode, const unsigned char *lpszVarName);
                                                // ið *pCurNode iðsitraukia <lic>, ið jo ProdVer, o pagal já registro parametrà
                                                // (iðkvieèia ExtractGrpLicProdVer(), po to GetProdVerRegVariableStr())
                                                // jei neranda, gràþina KP_E_KWD_NOT_FOUND, praneðimo neiðveda
   HRESULT GetProdVerRegVariableDword(DWORD *plVarPtr, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName); // ið pradþiø ið HKCU, jei neranda – ið HKLM
   HRESULT SetProdVerRegVariableStr(const unsigned char *lpszValue, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName); // saugoja tik á HKCU
   HRESULT SetProdVerRegVariableDword(DWORD lValue, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName); // saugoja tik á HKCU
   HRESULT SaveVar(const unsigned char *lpszPars);


   HRESULT GetProdVarReg(void); // suranda m_ProdVar ið registro rakto "Installed" ir dekrementuoja (mano vienetu didesni, negu Tado su Gintaru)
   HRESULT GetProdVarRegTmp(int iProdVer, int *piProdVar); // suranda konkreèios ProdVer diegimo ProdVar, negadina m_iProdVer ir m_ProdVar

   HRESULT StartCheckUpdateThread( // paleidþia threadà CheckUpdateThreadProc() su CheckUpdate(); apibrëþtas kpstapg.cpp
      const unsigned char *lpszChkUpdCmd = null  // komandos "CU=" (KPSTIP_CHK_UPDATE_CMD) tekstas, ið pagrindinës programos atëjusio POST praneðimo turinys
      );                                         // naudojamas kpstisvr.exe IP komandø serveriukyje
#ifndef KPST_UPDATE_OLD_LAUNCH
   HRESULT SendCheckUpdateMsg(void); // IP praneðimà "CU=" siuntimas á kpstisvr.exe
#endif
#ifdef KPST_UPDATE_OLD_INTERFACE
   HRESULT ParseUpdFdf(bool bOutMsg); // parsina m_lpszGrpCfgBuf[] esantá update FDF failà, permeta á atsisiuntimo puslapá, jeigu yra atnaujinimas; CheckUpdate() paprogramë
#endif
   HRESULT CheckUpdate
   (
      const unsigned char *lpszChkUpdCmd, // parametrai, perduoti ið pagrindinës programos per POST praneðimà á StartCheckUpdateThread(); jei null – pasiima ið lokalaus KpStIniData
      bool bForced, // jei bForced == False - tikrina tik jei registre nustatyta TestUpdates = 1L; apibrëþtas kpstapg.cpp
      bool bOutMsg
   );
   HRESULT CheckUpdateSvrRequest(const unsigned char *lpszChkUpdCmd, bool bOutMsg); // kreipiasi á http://updates.tev.lt/versija_n.php, atsakymà gràþina á m_lpszGrpCfgBuf[], CheckUpdate() paprogramë
   HRESULT GetTestUpdates(bool *pbTestUpdates, /* const unsigned char *lpszPublisher = null, */ int iProdVer = 0, const unsigned char *lpszIniFName = null);
                                                                  // iðtraukia ið registro "TestUpdates" - ar reikia automatiðkai tikrinti atnaujinimus
                                                                  // jei iProdVer == 0, ima lokalø KpStIniData::m_iProdVer
                                                                  // lpszIniFName – papildomas poþymis .ini faile KpStIniData::m_bTestUpdates
                                                                  // registro "TestUpdates" ir lpszIniFName KpStIniData::m_bTestUpdates apjungiami su OR (jei bent vienas nustatytas – atnaujinimus tikrinam)
                                                                  // jei lpszIniFName skaitymas sëkmingas, nustatomi m_lpszIniFName[] ir m_bSaveTestUpdatesToIni – SetTestUpdates() iðsaugos ir á .ini
                                                                  // jei lpszIniFName == null, lokalaus KpStIniData::m_bTestUpdates neskaito, bet hardkodinis arba atmintuko tikrinimo metu perskaitytas KpStIniData::m_bTestUpdates lieka galioti
   HRESULT SetTestUpdates(bool bTestUpdates, /* const unsigned char *lpszPublisher = null, */ int iProdVer = 0);   // nustato registro "TestUpdates" - ar reikia automatiðkai tikrinti atnaujinimus
                                                                  // jei iProdVer == 0, ima lokalø KpStIniData::m_iProdVer

   HRESULT GetFlashIniFname(unsigned char *lpszIniFName);   // lpszIniFName[KP_MAX_FNAME_LEN + 1]
                                                            // iðtraukia atmintuke esantá .ini failo vardà
// ---------------------------
   HRESULT GetProdDir(unsigned char *lpszProdDir); // gràþina starterio paleidimo programos katalogo vardà, pvz., "Matematika Tau-5E mokytojui"
                                                   // lpszProdDir[KP_MAX_FNAME_LEN + 1]

// pjaunasi su MT910 SVK uþdaviniø konstruktorium – jis irgi uþdavinius saugoja ..\Mano .fdf failuose
// HRESULT InitUserFileList(void); // formuoja failà <m_lpszVolName>.dat su katalogo ..\Mano .pdf (.fdf) failø sàraðu (fdf formatu)

// HRESULT CopyUpdateDat(void); // kopijuoja update.dat á vartotojo atmintukà/katalogà (m_lpszFlashDevName)
   HRESULT CopyCalcFiles(void); // kopijuoja kpscalc.exe ir KPSCLC.EXE á atmintukà

   HRESULT DelUserJscriptsSingle(const unsigned char *lpszFMask); // darbinë DelAllUserJscripts() paprogramë
   HRESULT DelAllUserJscripts(void); // iðtrina visus "%APPDATA%\\Adobe\\Acrobat\\x.0\\JavaScripts\\*.js" iðskyrus glob.js
                                     // taip pat "...\\*.jss" ir "...\\JSByteCodeWin.bin", kad neliktø jokiø ðiukðliø nuo seniau

   HRESULT CopyUserJscriptsSingle(const unsigned char *lpszUserPath, const unsigned char *lpszFMask); // darbinë funkcija naudojama CopyUserJscripts()
   HRESULT CopyUserJscripts(void); // kopijuoja projekto .js ið ".\AcroRead602\Reader\Javascripts\\*.js"
                                   // á "%APPDATA%\\Adobe\\Acrobat\\6.0\\JavaScripts\\*.js"
                                   // po to uþkloja dar ir dinamiðkai atnaujintus *.js ið atmintuko
                                   // "E:\\Matematika Tau-5E mokytojui\\AcroRead602\Reader\Javascripts\\*.js"

   HRESULT DeleteUserJscripts(void); // iðtrina prieð tai CopyUserJscripts() nukopijuotus *.js pagal kopijavimo metu sudarytà sàraðà
                                     // ið "%APPDATA%\\Adobe\\Acrobat\\6.0\\JavaScripts\\*.js"

// ---------------------------
   static HRESULT GetDataDatVariable(/* const */ KpString *psFileName, const unsigned char *lpszVarName, /* const */ KpString *psVarVal, bool bOutMsg);

   static HRESULT SetDataDatVariable(/* const */ KpString *psFileName, const unsigned char *lpszVarName, /* const */ KpString *psVarVal, bool bOutMsg);
                        // áraðo data.dat struktûros failo laukà vardu lpszVarName[]
                        // bOutMsg - ar iðvedinët klaidø praneðimus

// ---------------------------
   HRESULT SetDataDatUserData(void);   // perraðo m_Ini.lpszUserData[] á data.dat laukà "SI"

// ---------------------------
   HRESULT GetServerPort(int *piPort); // perskaièiuoja rezultatø/licencijø serverio porto numerá ið ProdVer
                                       // ProdVer pasiima pats, perduot nereikia
                                       // broadcast datagramm portas serverio adreso ieðkojimui – *piPort + KP_UDP_PORT_OFFSET

   HRESULT RetrieveLicServerSingle(unsigned char *lpszIpAddrBuf, int iAddrBufSize,  int iPort, const unsigned char *lpszBroadcastAddr);
                                       // darbinë RetrieveLicServer() paprogramë
                                       // lpszIpAddr[] == KP_IPADDR_LOCAL_HOST arba KP_IPADDR_BROADCAST
                                       //    ("127.0.0.1" arba "255.255.255.255", galima ieðkoti arba lokalaus serverio, arba LANe)
                                       // gràþina KP_E_NO_CONN, jei negauna atsakymo
   HRESULT RetrieveLicServer(unsigned char *lpszIpAddrBuf, int iAddrBufSize, int iPort);
                                       // broadcastu apklausia rezultatø/licencijø serverio adresà

// ---------------------------
   HRESULT AskUserPwd(void);
   HRESULT AskUserPUK(const unsigned char *lpszPrompt = null);

// ---------------------------
// tikrina, ar nepaleistas kitas KpStart – jei taip – klaida – vienu metu galima tik vienai sesijai
// nepavyko realizuot, iðkeltas á StartSockProcess() (SendIPSesAlive()), suveikia, tik jei yra KPSTAP_SVR_DATA_FILE (kpstdf.bin) ir KPSTISVR_EXE_FNAME (kpstisvr.bin)
// sesijø dubliavimas negalimas ne vien dël to, kad mygtukai netyèia pasispaudþia du kartus, ar vartotojas nesulaukæs spaudþia dar kartà –
//    IP serveriukas kpstisvr.exe gali vienu metu apdoroti tik vienà projektà – serveris permetamas á to projekto darbiná katalogà
// HRESULT CheckKpStartRunning(void);

// ---------------------------
   HRESULT KpBringToTop(HWND hBitmapWindow, HWND hDlgWnd); // iðkelia langà hBitmapWindow á foregroundà, hDlgWnd - á dugnà

// ---------------------------
   HRESULT InitExtViewers(void); // init m_lpszaExtProcessed[] and m_lpszaExtViewers[] from {m_lpszFlashDevName}\DAT0\players.ini

// ---------------------------
   HRESULT CheckBinaries(void);  // tikrina .bin (.exe) failø ilgius pagal kpstbls.ini (KPST_CHK_BIN_INI_FNAME)
                                 // pats kpstbls.ini turi bûti ðalia kpstart.exe, o failø sàraðas santykinai nuo m_lpszFlashDevName[]

// -------------------------- áraðom uþkoduotà individualaus atmintuko atnaujinimo lic. kodà á R__svarbiinfo.js
   HRESULT CorFlashUpdLicId(unsigned char *lpszUpdUserPars); // sugadina lpszUpdUserPars reikðmæ

// -------------------------- grupiniø leidiniø/prenumeratø apdorojimas, failas kpstapg.cpp
   HRESULT ProcessGrp(bool bMainThread);  // pagrindinis visø grupiniø procedûrø áëjimo taðkas, sutvarko viskà – kreipiasi á prodreg serverá, atnaujina cfg, krauna, diegia, registruoja komponentus
                                          // bMainThread == True: iðvedinëti siunèiamø meniu paveiksliukø termometrus, ið serverio configûracijà krauti per jëgà (GET uþklausos parametras forced=1)
                                          // bMainThread == False: meniu paveiksliukus siøsti tyliai, ið serverio configûracijà krauti tik jei pasikeitë (GET uþklausos parametras forced=0)
                                          // jei ið serverio atëjo atsakymas KpReg-NoNews, gràþina KP_E_CANCEL

   HRESULT StartProcessGrpThread(void);   // ProcessGrp() atskiram threade, iðsaugotà meniu galima rodyt ið karto, po parsiuntimo bus atnaujintas
                                          // periodiðkai iðkvietinëja ProcessGrp(), GenStartMenu() ir nustato m_pGrpKpPubDlg->m_bRefresh = True;
                                          // faktiðkai tas pats, kas periodinis RefreshGrpMenu()
                                          // paleidþia ProcessGrpThreadProc(), m_lGrpRefreshThreadId
   HRESULT StopProcessGrpThread(void);    // stabdo m_lGrpRefreshThreadId

   HRESULT RefreshGrpMenu(bool bReload);  // xGecko nuorodos tux:///KpStart:Refresh procedûra, iðkvieèimas ir ið ProcessGrpThreadProc() bei GrpDownloadSingle()
                                          // iðkvieèia ProcessGrp(), GenStartMenu() ir nustato m_pGrpKpPubDlg->m_bRefresh = True;
                                          // jei bReload == False, uþklausos serveriui nesiunèia, tik atnaujina meniu (GrpDownloadSingle() siuntimo termometrà)

   HRESULT SwitchGrpMenuRefreshing(bool bRefreshFlg); // stabdo/atstato StartGrp() paleidimo meniu periodiná atnaujinimà

   HRESULT GetIniUserPwdEnc(long lCryptCode, unsigned char *lpszCryptPwdOutBuf); // iðtraukia GetIniUserPwd() ir uþkoduoja HTTP uþklausoms ir saugojimui registre, 
                                                      // lpszCryptPwdOutBuf[2 * TV_TAG_LEN + 1] – ðeðioliktainis buferis   

   HRESULT GrpSvrRequest(bool bMainThread, bool bOutMsg);   // kreipiasi á http://www.tev.lt/prodgrp.php?lic=8R34-GR52-5U2U&ProdVar=1
                                                            // atsakymà padeda á m_lpszGrpCfgBuf
                                                            // bOutMsg – ar iðvedinëti klaidø praneðimus
                                                            // bMainThread == True – konfigûracijà krauti per jëgà (forced=1)
// HRESULT GrpSvrRequestAsyn(bool bOutMsg); // paleidþia GrpSvrRequest() atskiram threade, laukia kol pasibaigs threadas ar taimeris

   HRESULT ParseGrpCfgBuf(void); // parsina m_lpszGrpCfgBuf[] esantá UTF-8 XML tekstà á m_pGrpCfgNode

   HRESULT GetGrpCfgItem(XmlNode **pItemPtr, const unsigned char *lpszProdName, XmlNode *pPrpCfgSubNode, bool bInnoSetup);
                                 // suranda konkretaus produkto m_pGrpCfgNode áraðà <item> pagal jo <appname> reikðmæ
                                 // pPrpCfgSubNode – startinis m_pGrpCfgNode elementas, pradedam nuo m_pGrpCfgNode ir eina rekursiðkai gilyn
                                 // nors rekursijos ir nereikia – visi <item>-ai yra tiesioginiai m_pGrpCfgNode vaikai
                                 // *pItemPtr pradþioj turi bûti nustatytas á NULL, ciklinam, kol pasidaro ne NULL
                                 // bInnoSetup == True – lpszProdName koduotas pagal Inno Setup registre áraðomos reikðmës taisykles (rusiðkus á 1051 lentelæ)
                                 // bInnoSetup == False – lpszProdName koduotas, neatpaþintus simbolius (rusiðkus) konvertuojant á lotyniðkus
                                 // TODO: naikint bInnoSetup

   HRESULT CheckGrpResponce(void); //  analizuoja, ar m_pGrpCfgNode tago <resp> reikðmë yra KpReg-Ok
                                   // jei ið serverio atëjo atsakymas KpReg-NoNews, gràþina KP_E_CANCEL

   HRESULT GrpLogoff(void); // nuresetina userio slaptaþodá ir uþkrauna nuliná meniu

   HRESULT InitGrpCfg(void); // m_lpszGrpCfgBuf[] uþpildo nuliniu lpszStartGrpCfgEmpty
   HRESULT SaveGrpCfg(void); // iðsaugoja m_lpszGrpCfgBuf[] á failà DAT0\<prog_vardas>.cfg, prieð tai uþkodavæs
   HRESULT LoadGrpCfg(void); // pakrauna failà DAT0\<prog_vardas>.cfg á m_lpszGrpCfgBuf[], atkoduoja ir suparsina á m_pGrpCfgNode
                             // jei failo neranda, tyliai já inicializuoja nuliniu lpszStartGrpCfgEmpty
   HRESULT CalcGrpCfgFName(void); // uþpildo m_lpszGrpCfgFName[], iðkvieèiamas konstruktoriuj

   HRESULT ExtractGrpDownLoads(/* const */ XmlNode *pPrpCfgSubNode); // m_pGrpCfgNode tagø <appname> reikðmes á --> m_aGrpDownLoads; SelectSetupDownload() paprogramë; parametras – m_pGrpCfgNode, po to rekursiðkai jo vaikai
                                                         // TODO: kelt á XmlNode
                                                         // pPrpCfgSubNode – startinis m_pGrpCfgNode elementas, pradedam nuo m_pGrpCfgNode ir eina rekursiðkai gilyn
                                                         // nors rekursijos ir nereikia – visi <item>-ai yra tiesioginiai m_pGrpCfgNode vaikai
   HRESULT AppendGrpDownLoads(/* const */ XmlNode *pPrpCfgSubNode); // prideda m_pGrpCfgNode tagø <file> nuorodas prie m_aGrpDownLoads; parametras – m_pGrpCfgNode, po to rekursiðkai jo vaikai
                                                         // TODO: kelt á XmlNode
                                                         // tikrina failø datas, prideda tik naujesnius, paþymi m_aGrpDownLoads elementø m_bChecked; iðkvieèiamas po SelectSetupDownload()
   HRESULT SelectSetupDownload(int iProdVer = 0, const unsigned char *lpszProdName = null, bool bUpdFl = False);
                                                         // atidaro parsisiøstinø serialo komponentø sàraðà m_aGrpDownLoads ir leidþia vartotojui suþymëti norimus
                                                         // jei iProdVer == 0, ima lokalø KpStIniData::m_iProdVer
                                                         // jei lpszProdName == null – pasiima ið lokalaus KpStIniData::m_lpszProdName[]
                                                         // bUpdFl – ar updeitas, jei ne – tada serija
// void TraceGrpDownLoads(void /* KpTreeEntry *pCurEntry = m_aGrpDownLoads */);       // iðveda m_aGrpDownLoads turiná á logà

   HRESULT CountFullGrpSize(long *plFullSize);  // suskaièiuoja visø paþymëtø m_aGrpDownLoads failø ilgá
   static HRESULT GetGrpLocalDir(unsigned char *lpszLocalDir); // lpszLocalDir[KP_MAX_FNAME_LEN + 1] – buferis aplankui, á kurá reiks raðyti parsiunèiamus failus
                                                            // StartGrp.exe .\DAT0
                                                            // kpstisvr.exe %TEMP%
                                                            // GetGrpLocalFName paprogramë
   static HRESULT GetGrpLocalFName(unsigned char *lpszLocalFName, unsigned char *lpszProgressMsg, const unsigned char *lpszRemoteFName);
                                                // suformuoja lokalaus parsisiunèiamo failo vardà ir termometro praneðimà
                                                // abu buferiai [KP_MAX_FNAME_LEN + 1], gali bûti null
                                                // lpszRemoteFName – m_aGrpDownLoads elemento KpGrpChk::m_lpszDownLoadFName
                                                // GrpDownLoad() paprogramë
   static HRESULT GetInnoRegPar(unsigned char *lpszParValBuf, const unsigned char *lpszProdName, const unsigned char *lpszParName);
                              // Iðtraukia tekstinio parametro reikðmæ ið Inno Setup registro
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND
                              // GetInnoInstPath() ir GetInnoUnInstCmd() paprogramë
                              // lpszParValBuf[KP_MAX_FNAME_LEN + 1]
   static HRESULT GetInnoInstPath(unsigned char *lpszInstPathBuf, const unsigned char *lpszProdName);
                              // Iðtraukia produkto diegimo katalogà ið Inno Setup registro
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND
                              // GrpDownLoad() paprogramë
                              // lpszInstPathBuf[KP_MAX_FNAME_LEN + 1]
   static HRESULT GetInnoUnInstCmd(unsigned char *lpszUninstPathBuf, const unsigned char *lpszProdName);
                              // Iðtraukia produkto iðmetimo komandinæ eilutæ ið Inno Setup registro
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND
                              // StartUninstThreadProc() paprogramë
                              // lpszUninstPathBuf[KP_MAX_FNAME_LEN + 1]

   HRESULT GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, const unsigned char *lpszAppName, const unsigned char *lpszLicCode);
                              // Iðtraukia produkto diegimo katalogà ið ProdVer registro (per <lic> susiranda ProdVer)
                              // jei neranda – ið Inno Setup registro pagal lpszAppName su GetInnoInstPath()
                              // lpszInstPathBuf[KP_MAX_FNAME_LEN + 1], gali bûti null
                              // *ppiInstPath – sukuriama nauja eilutë, gali bûti NULL, po panaudojimo reikia iðmesti
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND
                              //    *ppiInstPath vis tiek sukuria tuðèià
   HRESULT GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, /* const */ XmlNode *pCurNode);
                              // lpszAppName (<appname>) iðsitraukia su GetAppName()
   HRESULT GetGrpInstPath(unsigned char *lpszInstPathBuf, KpChar **ppiInstPath, const KpGrpChk *GrpDownloadPars);
                              // lpszAppName iðsitraukia ið GrpDownloadPars->m_lpszText

   HRESULT GetGrpUnInstCmd(unsigned char *lpszUnInstPathBuf, const unsigned char *lpszAppName);
                              // Iðtraukia produkto naikinimo komandà ið ProdVer registro (per <lic> susiranda ProdVer)
                              // jei neranda – ið Inno Setup registro pagal <appname> su GetInnoUnInstCmd()
                              // lpszUnInstPathBuf[KP_MAX_FNAME_LEN + 1]
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND

   HRESULT GetGrpLaunch(unsigned char *lpszLaunchBuf, KpChar **ppiLaunch, bool *pbInstalled, const unsigned char *lpszAppName);
   HRESULT GetGrpLaunch(unsigned char *lpszLaunchBuf, KpChar **ppiLaunch, bool *pbInstalled, /* const */ XmlNode *pCurNode);
                              // Iðtraukia produkto paleidimo komandà ið ProdVer registro (per <lic> susiranda ProdVer)
                              // jei neranda – ið <launch> tago
                              // pakeliui su GetGrpInstPath() susiranda {app} ir suparsina
                              // lpszLaunchBuf[KP_MAX_FNAME_LEN + 1], gali bûti null
                              // *ppiLaunch – sukuriama nauja eilutë, gali bûti NULL, po panaudojimo reikia iðmesti
                              // jei neranda, praneðimo neiðveda, o gràþina klaidos kodà KP_E_KWD_NOT_FOUND
                              // pbInstalled – patikrina, ar yra komandoje nurodytas failas, jei pbInstalled == NULL, netikrina

   HRESULT GetGrpItemAppName(unsigned char **plpszAppNameBuf, KpChar **ppiAppName, /* const */ XmlNode *pCurNode, bool bInnoSetup);
                              // pagal <lic> ieðko ProdReg registre rakto "ProdName"
                              // jei neranda, <appname> reikðmæ iðtraukia ið pCurNode ir perkoduoja i 8-bitæ eilutæ
                              //    bInnoSetup == True – pagal Inno Setup registre áraðomos reikðmës taisykles (rusiðkus á 1051 lentelæ)
                              //    bInnoSetup == False – neatpaþintus simbolius (rusiðkus) konvertuojant á lotyniðkus
                              // *plpszAppNameBuf – sukuriama nauja eilutë, gali bûti NULL, po panaudojimo reikia iðmesti
                              // *ppiAppName – sukuriama nauja eilutë, gali bûti NULL, po panaudojimo reikia iðmesti
                              // TODO: naikint bInnoSetup

   HRESULT ExtractGrpLicProdVer(unsigned char **plpszLicCode, long *piLicID, int *piProdVer, /* const */ XmlNode *pCurNode);
                              // iðtraukia tago <item> (XG_Item) licencijà ir ProdVer (ið subtago <lic> XG_Licence)
                              // sukuria plpszLicCode, gali bûti NULL, po panaudojimo reikia iðmesti
                              // piLicID, piProdVer gali bûti NULL
                              // jei neranda <lic> – KP_E_KWD_NOT_FOUND, klaidos praneðimo neiðveda

   HRESULT GrpDownloadSingle(KpGrpChk *GrpDownloadPars, HWND hProgWnd, long *plReceived, long lFullSize, const unsigned char *lpszWndName = null, const unsigned char *lpszProdName = null, bool bOutMsg = True);
                              // siunèia vienà m_aGrpDownLoads elementà, GrpDownLoad() ir StartGrpDownloadThreadProc() paprogramë
                              // hProgWnd - progreso termometro langelis
                              // *plReceived – iðorinis parsiøstos visø failø apimties dalies baitø skaitiklis termometrui
                              // lFullSize – visas parsiøstinø baitø skaièius
                              // lpszWndName – prieð diegiant pareikalauti uþdaryti langà tokiu pavadinimu, jei null – nereikalauti
                              // lpszProdName naudojamas perspëjimo praneðime

   HRESULT GrpDownLoad(bool bMainThread, const unsigned char *lpszWndName = null, const unsigned char *lpszProdName = null);
                              // siunèia m_aGrpDownLoads failus, tik paþymëtus setupinius ir tik naujesnius paprastus <file>;
                              // setupinius èia pat ir tyliai paleidþia, po to iðtrina
                              // bMainThread – ar rodyti siunèiamø failø termometrus
                              // lpszWndName – prieð diegiant pareikalauti uþdaryti langà tokiu pavadinimu, jei null – nereikalauti
                              // lpszProdName naudojamas perspëjimo praneðime

   static HRESULT DecodeAppNameUTF8toStr(unsigned char *lpszAppName, const unsigned char *lpszAppNameUTF8, bool bInnoSetup); // former DecodeAppNameUTF8toWin1257
                              // perkoduoja {appname} ið UTF-8 á 8-bitá
                              //    bInnoSetup == True – pagal Inno Setup registre áraðomos reikðmës taisykles (rusiðkus á 1051 lentelæ)
                              //    bInnoSetup == False – neatpaþintus simbolius (rusiðkus) konvertuojant á lotyniðkus
                              // buferis lpszAppName[KP_MAX_FILE_LIN_WDT + 1]
                              // StartGrpDownloadThread() ir StartUninstThread() paprogramë
                              // TODO: naikint bInnoSetup

   HRESULT AppendGrpDownloadThreadListEntry(DWORD lCurThread); // sukuria naujà m_GrpDownLoadThreadList áraðà
   HRESULT DeleteGrpDownloadThreadListEntry(DWORD lCurThread); // naikina m_GrpDownLoadThreadList áraðà
// HRESULT DumpGrpDownloadThreadList(unsigned char *lpszOutStrBuf, bool bSetSemaphore); 
                              // iðveda m_GrpDownLoadThreadList elementus á lpszOutStrBuf[KP_MAX_FILE_LIN_LEN + 1]
                              // bSetSemaphore – ar stabdyti m_bGrpDownloadListProcessing 

   HRESULT StartGrpDownloadThread(const unsigned char *lpszAppNameUTF8);
                              // paleidþia konkretaus produkto siuntimo threadà StartGrpDownloadThreadProc() StartGrp.exe
                              // lpszAppNameUTF8 – {appname} – produkto vardas, tekstas, einantis po xGecko komandos KpStart:DownLoad:
                              // problemëlë – tas tekstas ið HTML failo per xGecko ateina UTF-8, StartGrpDownloadThread() persikoduoja á Win-1257

   HRESULT KpGrSetProgressPrc(const unsigned char *lpszAppName, int iPrc);
                              // susiranda atitinkamo produkto <item> mazgà m_pGrpCfgNode ir
                              // nustato tagà <prc> termometro prie ikonos iðvedimui
                              // jei iPrc == -1, <prc> tagas sunaikinamas (leidinys parsiøstas ir ádiegtas)

   HRESULT StartUninstThread(const unsigned char *lpszAppNameUTF8);
                              // paleidþia konkretaus produkto iðmetimo threadà StartUninstThreadProc() StartGrp.exe
                              // lpszAppNameUTF8 – {appname} – produkto vardas, tekstas, einantis po xGecko komandos KpStart:DownLoad:
                              // problemëlë – tas tekstas ið HTML failo per xGecko ateina UTF-8, StartGrpDownloadThread() persikoduoja á Win-1257

// ------------------------------------ meniu dël StartGrp.exe
   HRESULT SaveGrpMenu(void); // raðo m_lpszGrpMenu[] á KPST_GRP_MENU_FNAME, prieð tai, gal bût, uþkoduodama
   HRESULT GenStartMenu(bool bLauncher);  // skanuoja m_pGrpCfgNode ir pagamina m_lpszGrpMenu
                                          // jei bLauncher == True, savo <item> áraðà praleidþia
   HRESULT LoadGrpImg(/* const */ XmlNode *pFather, int iTag, KpBmpData *pBmpPars, HBITMAP *pBitmap, XmlNode **pChild = NULL); 
                                          // ieðko iTag tarp pFather vaikø, uþkrauna parsisiøstà failà á *pBitmap; pagalbinë GenStartMenu() paprogramë
                                          // á *pChild gràþina surastà mazgà

   static HRESULT ExtractStartMenuSubsts  // iðtraukia m_pGrpCfgNode subnode tagø reikðmiø sàraðà (<file> arba <mpar>); GenStartMenu() paprogramë
   (                                      // <file> reikðmes keièia á lokalius failø vardus; <mpar> reikðmëse makrokomandas {file} pakeièia atitinkamom pFilesList reikðmëmis
      KpTreeEntry **pElemList,            // iðtrauktas elementø KpChar[] reikðmiø sàraðas
      const XmlNode *pCfgSubNode,         // m_pGrpCfgNode submode – <pr> arba <item>
      KpChar iTag,                        // kuriø tagø reikðmes traukti – XG_File ar XG_MPar
      /* const */ KpTreeEntry *pFilesList = NULL,  // makrokomandø {files} iðskleidimo sàraðas; jei iTag == XG_File, nenaudojamas
      int *piFilesIx = NULL               // naudojamas nuosekliam *pFilesList skanavimui, pradþioj turi bûti nustatytas á 0; jei iTag == XG_File, nenaudojamas
   );                                     // TODO: kelt á XmlNode

   HRESULT OpenShowHtml(void); // inicijuoja meniu objektus; sukuria m_pKpPubDlg
   HRESULT CloseShowHtml(void); // naikina meniu objektus (m_pKpPubDlg)
   HRESULT ProcStartMenu(void); // vykdo meniu

// ------------------------------------ prisiloginimas prie klientø sistemos
   HRESULT GenLoginDlg(void);
   HRESULT Login(void);
   HRESULT ProcDoLogin(const unsigned char *lpszGetPars); // lpszGetPars: "?ButNum=1&user=vardas&pwd=slaptazodis"

// --------------------------
   HRESULT GrpSendDiagMsg(const unsigned char *lpszDiagMsgPars); // diagnostinio praneðimo siuntimas; lpszDiagMsgPars – failø, kuriuos reikia prikabinti prie praneðiomo, vardø sàraðas, atskirtas kabliataðkiais 

// --------------------------
   static HRESULT WaitTilWndCloses(const unsigned char *lpszWndName, const unsigned char *lpszProdName); // tikrina, ar uþdarytas langas

};


// ---------------------
extern DWORD WINAPI CheckUpdateThreadProc(LPVOID /* const unsigned char * */ lpszChkUpdCmd /* lpParameter */); // CheckUpdate() threado procedûra; apibrëþtas kpstapg.cpp
                                                                                                         // lpszChkUpdCmd sukurtas iðkvieèianèio threado, po panaudojimo reikia sunaikint

extern DWORD WINAPI StartGrpDownloadThreadProc(LPVOID lpParameter);
extern DWORD WINAPI StartUninstThreadProc(LPVOID lpParameter);

// ---------------------
class KpStGrpSubster
{
   HRESULT m_hOpenError;

   KpChar *m_iazOutBuf;
   int m_iOutBufLen;
   const KpChar *m_iazTemplate;

/* const */ KpTreeEntry *m_pFilesList; // makrokomandø {files} iðskleidimo sàraðas
   int *m_piFilesIx;                // naudojamas nuosekliam *pFilesList skanavimui, pradþioj turi bûti nustatytas á 0
   int m_iFilesCnt;

/* const */ KpTreeEntry *m_pMParsList; // makrokomandø {mpar} iðskleidimo sàraðas
   int *m_piMParsIx;                // naudojamas nuosekliam *pMParsList skanavimui, pradþioj turi bûti nustatytas á 0
   int m_iMParsCnt;

   const KpChar *m_iazAppName;      // makrokomandos {appname} reikðmë
   const KpChar *m_iazInstPath;     // makrokomandos {app} reikðmë
   const KpChar *m_iazLaunch;       // makrokomandos {launch} reikðmë

   const KpChar *m_iazSetup;        // makrokomandos {setup} reikðmë
   const KpChar *m_iazSetupSize;    // makrokomandos {setupsize} reikðmë
   const KpChar *m_iazLic;          // makrokomandos {lic} reikðmë

   const KpChar *m_iazPrc;          // makrokomandos {prc} reikðmë
   
   KpChar *m_iazTemp;         // makrokomandos {temp} reikðmë

// darbiniai laukai
   const KpChar *m_iazPnts; // m_iazTemplate[] skaitymo rodyklë
   KpChar *m_iazPntd; // m_iazOutBuf[] raðymo rodyklë

public:
   KpStGrpSubster(KpChar *iazOutBuf, int iOutBufLen, const KpChar *iazTemplate,
      /* const */ KpTreeEntry *pFilesList, int *piFilesIx,
      /* const */ KpTreeEntry *pMParsList = NULL, int *piMParsIx = NULL,
      const KpChar *iazAppName = NULL, const KpChar *iazInstPath = NULL, const KpChar *iazLaunch = NULL,
      const KpChar *iazSetup = NULL, const KpChar *iazSetupSize = NULL, const KpChar *iazLic = NULL,
      const KpChar *iazPrc = NULL);

   ~KpStGrpSubster();

private: // darbinës funkcijos
   HRESULT SubstFromList(const KpChar *iazMacroName, /* const */ KpTreeEntry *pSubstList, int *piSubstListIx, int iSubstListSize);
   HRESULT SubstSingle(const KpChar *iazMacroName, const KpChar *iazSubstText);

public:
   HRESULT SubstGrpTpl(void); // iðskleidþia meniu elemento ðablonà, pakeisdama makrokomandas ({file} etc.) atitinkamom reikðmëm; GenStartMenu() paprogramë
};


// ----------------------------------------
extern HRESULT EnctBufSimpl(void *pcBuffer, long lBufLen); // encrypts/decrypts buffer, noncritical algorithm
extern HRESULT EnctBufMed(void *pcBuffer, long lBufLen, int ProdVer, long lEntryId);
            // encrypts/decrypts buffer, noncritical algorithm
            // ProdVer depending, used in lzdencm.exe
extern HRESULT EnctBufInc(void *pcBuffer, long lBufLen, int ProdVer, long lEntryId, bool bEncode);
            // encrypts/decrypts buffer, critical algorithm, bet vis tiek nepaslëptas emuliatoriuje
            // bEncode: uþkoduoti (True) ar iðkoduoti (False)
            // KP_RC_ENCODE_ENTRY gali koduoti tik Maxint*4 ilgio lizdus, be to kaþko lûþta multithreadiniam tux_gecko streamø factory

// ----------------------------------------
// pointer to application instance, casted to KpStApp
// should be initiated in main(), WinMain() or wxApp::OnInit() before of call to KpStApp::InitStApp()
// before use should be checked whether not NULL
extern KpStApp *theKpStAppPtr;


// ----------------------------------------
extern HRESULT GetCommonCompID_RC(void *pKpStAppObjPtr);
extern int NormalizeCompId(long lValue); // sukomponuoja 16 bitu id is ilgo long kodo

typedef struct
{
   KpStApp *m_pThis;
   long m_lFlashId;
   bool *m_pbFound;
   int *m_piNumOfFlashes;
   unsigned char m_cDriveLetter; // tikrinamo flash disko raidë
} TestFlashIdPars_1;
extern HRESULT TestFlashID_RC(void *pTestFlashIdParsPtr);

extern HRESULT GetFlashSerNo(const unsigned char *lpszDevName, long *plSerNo, unsigned char *lpszSerNoTxt, long *plVid, long *plPid, bool bDiskDevNameFormat);
// lpszDevName:
//    jei bDiskDevNameFormat (registro raktas "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum")
//       "USBSTOR\\Disk&Ven_Generic&Prod_USB_Flash_Disk&Rev_0.00\\000000000000A1&0"
//    jei !bDiskDevNameFormat (registro raktas "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum")
//       "USB\\VID_3538&PID_0042\\000000000000A1"
// lpszSerNoTxt[KP_MAX_FNAME_LEN + 1]
// plSerNo normalizuotas á ðeðioliktainá su ForceTextToHex() ið lpszSerNoTxt[] (jei ðiaip tekstas)
// plSerNo, lpszSerNoTxt, plVid ir plPid gali bûti NULL

extern HRESULT GetFlashVidPid(const unsigned char *lpszSerNoTxt, long *plVid, long *plPid);
// iðtraukia ið visø "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum" registro raktø VID ir PID atmintuko, kurio ser.no. yra lpszSerNoTxt
// plVid ir plPid gali bûti NULL

extern HRESULT TestIniChSum_RC(void *pRetC);
extern HRESULT SetIniChSum_RC(void *pVoid);

typedef struct
{
   const unsigned char *m_lpszEnterLicPrompt;
   const unsigned char *m_lpszEnterLicExpl;
   const unsigned char *m_lpszPrompt;
   const unsigned char *m_lpszHint;
   const unsigned char *m_lpszButAkt;
   const unsigned char *m_lpszAtsaukt;
   unsigned char m_lpszLic1[KPST_NUM_OF_KEY_SEGM_CHARS+1];
   unsigned char m_lpszLic2[KPST_NUM_OF_KEY_SEGM_CHARS+1];
   unsigned char m_lpszLic3[KPST_NUM_OF_KEY_SEGM_CHARS+1];
   bool m_bEntered; // ivedineti nereikia, tik patvirtinti
   bool m_bUnReg; // lic. iðregistravimo forma (platesnë)

   int m_iWndWdt;
   int m_iWndHgt;

} KpStLicPars; // parameters to lic. entering window


extern BOOL CALLBACK KpStLicDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK KpStKeyDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK KpStRemDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern DWORD WINAPI SockListenProc(LPVOID lpParameter); // thread procedûra, tikrinanti IP komandas; paleidþiama ið CreateSockThread()

// extern DWORD WINAPI WatchExecProc(LPVOID lpParameter); // thread procedûra WatchExec() vykdymui, naudojama tux_ipa projektuose; apibrëþta kpstrg.cpp

typedef struct // StartCmdThreadProc() parametrai
{
   const unsigned char *m_lpszCmdLine;
   const unsigned char *m_lpszCurDir;
   const unsigned char *m_lpszStartCmdLine;
} StartCmdThreadPars;

extern DWORD WINAPI StartCmdThreadProc(LPVOID lpParameter); // komandos paleidimo threado procedûra; paleidþiama ið StartCmdThread()

// ---------------------------- server kphp11 RC functions
extern HRESULT CheckResRequest_RC(void *pKpStAppObjPtr);
extern HRESULT CheckRelRequest_RC(void *pKpStAppObjPtr);


// ================================================== hardware specific
#define BIOS_DAT_SIZE 10 // 2003.02.11
#define BIOS_DAT_BUF_SIZE 80

#define KPSTA_COMPID_SIGNIF (0x10000/10)

extern HRESULT GetBIOSDate(unsigned char *lpszDatBuf); // lpszDatBuf[BIOS_DAT_SIZE + 1]

extern HRESULT GetProcName(unsigned char *lpszNameBuf); // lpszNameBuf[KP_MAX_FNAME_LEN + 1]

// extern HRESULT GetDiskInfo(int iDiskNo, long *plSerNum, unsigned char *lpszLabel);
// iDiskNo: 0 - default drive, 1 - A:, 2 - B:, 3 - C:, ...
// unsigned char lpszLabel[KP_DOS_FNAME_LEN + 1];
extern HRESULT GetDiskInfo(const unsigned char *lpszVolName, long *plSerNum, unsigned char *lpszLabel);
// lpszVolName - "A:\\", "C:\\", "D:\\", ...
// plSerNum - loginio disko serijinis numeris, ne irenginio
// lpszLabel[KP_MAX_FNAME_LEN + 1]

extern long getHardDriveComputerID(void); // Diskid32.cpp


// ================================================== math
extern int DecKpHexDig(unsigned char cDigit);

extern HRESULT ScanKeyHex(const unsigned char *szKeyBuf, int *piKey);
#if Envir==MSWin32Mfc
extern HRESULT ScanKeyHex(const CString *sKeyBuf, int *piKey); // scans integer security key
#endif

extern unsigned char EncKpHexDig(int iDigit);

extern HRESULT FormatKeyHex(unsigned char *lpszKeyBuf, int iKey);
#if Envir==MSWin32Mfc
extern HRESULT FormatKeyHex(CString *sKeyBuf, int iKey);      // converts integer security key to pseudo-hex string
#endif

extern int KpstRand(int prev); // prev - saved previous value returned by kpst_rand()
extern int KpstXRand(int prev); // atvirkðtinë KpstRand()


// ================================================== flash functions
#define TEV_AUTORUN_INF_FNAME "TevAutorun.inf" // "autorun.inf"

typedef enum
{
   Fl_None = -1,  // nieko nedaryti

   Fl_ToCd,       // rasta irasa isvercia i CD-ROM
   Fl_ToFlash,    // rasta irasa atvercia atgal i normalu USB Flash
   Fl_ToFlashAll, // visu isverstu i cdrom atmintuku irasus atvercia atgal i USB Flash

   Fl_ToHd,       // rasta irasa isvercia i HD, kad butu galima kurti particijas
   Fl_Delete,     // ismeta visus draiveriu irasus, atitinkancius nurodyta ser. nr.
   Fl_CountOnly,  // tik skaiciuoja rastus atmintukus, skaitymo rezimo nekeicia
   Fl_SetRegAccess, // tik nustato priejima prie paskutinio ikisto atmintuko registru

   VT_MaxFlashAction

} FlashActions;

#define VT_MaxFlashAction_1 VT_MaxFlashAction

typedef enum
{
   NoAutoRunIx = -1,

   OpenIx,
   IconIx,
   ActionIx,
   VolTypeIx,
   StartInIx,

   VT_MaxAutoRunKwd

} AutoRunKwdIxs;

#define VT_MaxAutoRunKwd_1 VT_MaxAutoRunKwd

typedef enum
{
   Vt_NoVol = -1,

// kompaktai
   Vt_CDROM,      // neatpazintas DRIVE_CDROM
   Vt_TevCDROM,   // paprastas TEV CD iso su diegimo programom
   Vt_TevLiveCD,  // TEV live CD, nereikia diegti

// USB Flash
   Vt_Removable,  // neatpazintas DRIVE_REMOVABLE
   Vt_FlashUSB,   // pasenes, naudoti Vt_FlashRO
                  // paprastas (NTFS formatuotas) USB Flash, pilnai u_pildytas,
                  // visi failai ReadOnly ir su u_draustom raðymo teisëm;
                  // taip pat Vt_FlashCDROM bendroji dalis su atmintuko kodu
   Vt_TevLocked,  // 8cd USB Flash, 8 MB NTFS particijos projekcija
   Vt_TevUnLocked, // 8cd USB Flash, CD iso image projekcija
   Vt_FlashCDROM, // USB Flash, formatuotas CD iso image formatu, DiskFlash.exe/UFDUtility.exe;
                  // atmintuke dar yra kitas Vt_FlashRO (Vt_FlashUSB) formato loginis diskas su atmintuko kodu
   Vt_FlashRO,    // tas pats, kaip Vt_FlashUSB
   Vt_FlashRW,    // paprastas FAT formatuotas atmintukas atnaujinamiems ar vartotojo kuriamiems (MIKO) projektams; raðyti neu_drausta
   Vt_FlashTUX,   // dviejø daliø atmintukas, FAT formatuota dalis su tux_ipa + paslëpti PDF failai

   VT_MaxVolType

} TvVolTypes;

#define VT_MaxVolType_2 VT_MaxVolType

typedef struct
{
   unsigned char m_lpszOpen[KP_MAX_FNAME_LEN + 1];
   unsigned char m_lpszStartIn[KP_MAX_FNAME_LEN + 1]; // gal geriau tiesiog iðtraukti kelià ið m_lpszOpen?
   unsigned char m_lpszIcon[KP_MAX_FNAME_LEN + 1];
   FlashActions m_iAction;
   TvVolTypes m_iVolType;

} TevAutorunPars;



extern const unsigned char *lpszaAutoRunKwds[VT_MaxAutoRunKwd + 1];
extern const unsigned char *lpszaLockActionKwds[VT_MaxFlashAction + 1];
extern const unsigned char *lpszaVolTypeKwds[VT_MaxVolType + 1];

extern HRESULT LockFlashStr(const unsigned char *lpszLockAction);
extern HRESULT LockFlash(FlashActions iLockAction);
extern HRESULT ParseTevAutorun(const unsigned char *lpszPath, TevAutorunPars *pParBuf, bool bRootDir = True); // parsina TevAutorun.inf
         // lpszPath - drive name without slash "C:"
         // arba path (pvz., ".")
         // bRootDir – TevAutorun.inf ieðkoti ðakniniam kataloge (to paties disko, kuriame yra lpszPath), jei ne – ieðko paèiame lpszPath

extern int ChSum(long lVal);  // skaièiuoja kontrolinës sumos skaitmená mokyklø ir atmintukø kodams -
                              // deðimtainiø skaitmenø sumos su svoriais jauniausias deðimtainis skaitmuo
                              // lengviausias (svoris 1) jauniausias skaitmuo
extern int ChSum(const unsigned char *lpszText);
                              // susumuoja teksto eilutës simboliø kodus su svoriais,
                              // lengviausias (svoris = 1) pirmas baitas
                              // gràþina jauniausià sumos deðimtainá skaitmená

extern HRESULT ForceTextToHex(unsigned char *lpszFlashIdStr); // konvertuoja tekstinæ eilutæ á HEX skaitmenø eilutæ,
                              // tiesiog patrindamas perteklinius bitus
                              // naudojamas tekstiniø FlashId konvertavimui á hex


extern HRESULT KpExpandMacro(unsigned char *lpszCmdBuf, int iBufSize, const unsigned char *lpszMacroName, const unsigned char *lpszReplaceText);
                              // pakeièia makrokomandos tekstà jos iðskleista reikðme (pvz., "{user}")
#endif


// -------------------------------------------------- KP11_REST_DAYS_INIT processing
extern HRESULT InitResumeRestDays_RC(void *pKpStAppObjPtr, bool bForceAdmin, bool bLoadSaved, bool bRestMinsCalculated = False);
                                                // bLoadSaved – ar skaityti iðsaugotas reikðmes – aktyvavimo metu nereikia, tik paleidimo
                                                // bRestMinsCalculated – likusiø minuèiø inicijuot nereikia – nuresetinimo atveju
extern HRESULT InitRestDays_RC(void *pKpStAppObjPtr);
extern HRESULT ResumeRestDays_RC(void *pKpStAppObjPtr);
extern HRESULT ResetRestDays_RC(void *pKpStAppObjPtr);
extern HRESULT ProcessRestDays_RC(void *pKpStAppObjPtr);

// -------------------------------------------------- sertifikato ið/registravimas
extern HRESULT RegSert_RC(void *pKpStAppObjPtr);
extern HRESULT UnRegSert_RC(void *pKpStAppObjPtr);

// --------------------------------------------------
// extern DWORD WINAPI GrpSvrRequestThreadProc(LPVOID lpParameter); // GrpSvrRequest() asinchroninio paleidimo threado procedûra; paleidþiama ið GrpSvrRequestAsyn()
