// ---------------
// kpsttrg.h
// produkto licencijos registracija ir v�lesnis jos tikrinimas
//
// 2015-08-23  mp  atskirtas Kpsttrg bibliotekos kreipiniai KpsInit(), KpsClose() ir KpsTest() (tik patikrinimui be registracijos)
//

#ifndef kpsttrg_included
#define kpsttrg_included


// ---------------
// prane�im� piktogramos
// turi b�ti apibr��tos resurs� faile
#define KP_IDI_SETUP_ICON           301 // setup.ico
#define KP_IDI_OPEN_ICON            324 // open.ico


// ---------------
// Licencijavimo bibliotekos inicializavimas.
// I�kvie�iama vien� kart� programos prad�ioje.
// Neigiamas atsakymas - inicializacija nepavyko.
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsInit();


// ---------------
// Licencijavimo bibliotekos darbo u�baigimas.
// I�kvie�iama vien� kart� programos pabaigoje.
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsClose();


// ---------------
// Licencijos registravimas
// Diegiamiems produktams:
//    Atlieka licencijos registracijos proced�r� pirmo programos paleidimo metu.
//    Gautas atsakymas i� registravimo serverio atsimenamas, o program� paleid�iant kitus kartus,
//    tik tikrinama, ar tie kodai nei�sitryn� ir ar vis dar atitinka kompiuterio parametrus.
//    Neigiamas atsakymas - licencijos registracija nepavyko.
// Atmintukams:
//    Tikrina, ar �ki�tas produkto atmintukas.
//    Neigiamas atsakymas - licencijuotas atmintukas nerastas.
// Naudojimas:
//    if(SUCCEEDED(KpsTestReg())){ ... }
//
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsReg();

inline HRESULT KpsTestReg() { HRESULT retc = KpsInit(); if (SUCCEEDED(retc)) retc = KpsReg(); return retc; }
#define KpsTR KpsTestReg


// ---------------
// Licencijos tikrinimas
// Diegiamiems produktams:
//    Tik patikrina, ar registracijos kodai atitinka kompiuterio parametrus,
//    registracijos proced�ra neatliekama.
// Atmintukams � tas pats, kaip ir KpsReg()
//
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsTest();


// ---------------------------
// Taimerio apdorojimo proced�ra, i�kvie�iama kaip notifikacijos callbackas i� kiekvieno aktyvaus
// lango funkcijos i�kvietimo (pana�iai kaip DefWindowProc()) arba kartu su kiekvienu DispatchMessage()
// pagrindiniame programos prane�im� apdorojimo cikle.
// Pat� taimer� paleid�ia KpsTestReg(), �ita paprogram� tik patikrina, ar perduotas prane�imo parametras n�ra jai skirtas WM_TIMER,
// jei taip � atlieka tikrinimo proced�r�.
// Gr��ina False, jei viskas gerai, True � klaida.
//
// #define KpStaWindowProc KpsWP
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
BOOL CALLBACK KpStaWindowProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);


// ---------------
// Licencijos i�registravimas.
// Tik diegiamiems produktams.
// I�kvie�iamas i� atskiros produkto i�diegimo programos.
// Tik jei pavyko ankstesni produkto �alinimo veiksmai (pvz., PDF certifikato i�registravimas)
//
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsUnReg();

// -----------------
// produkto id
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
int GetProdVer();

#endif // #ifndef kpsttrg_included
