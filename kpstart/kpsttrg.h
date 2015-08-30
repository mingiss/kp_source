// ---------------
// kpsttrg.h
// produkto licencijos registracija ir vëlesnis jos tikrinimas
//
// 2015-08-23  mp  atskirtas Kpsttrg bibliotekos kreipiniai KpsInit(), KpsClose() ir KpsTest() (tik patikrinimui be registracijos)
//

#ifndef kpsttrg_included
#define kpsttrg_included


// ---------------
// praneðimø piktogramos
// turi bûti apibrëþtos resursø faile
#define KP_IDI_SETUP_ICON           301 // setup.ico
#define KP_IDI_OPEN_ICON            324 // open.ico


// ---------------
// Licencijavimo bibliotekos inicializavimas.
// Iðkvieèiama vienà kartà programos pradþioje.
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
// Licencijavimo bibliotekos darbo uþbaigimas.
// Iðkvieèiama vienà kartà programos pabaigoje.
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
//    Atlieka licencijos registracijos procedûrà pirmo programos paleidimo metu.
//    Gautas atsakymas ið registravimo serverio atsimenamas, o programà paleidþiant kitus kartus,
//    tik tikrinama, ar tie kodai neiðsitrynë ir ar vis dar atitinka kompiuterio parametrus.
//    Neigiamas atsakymas - licencijos registracija nepavyko.
// Atmintukams:
//    Tikrina, ar ákiðtas produkto atmintukas.
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
//    registracijos procedûra neatliekama.
// Atmintukams – tas pats, kaip ir KpsReg()
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
// Taimerio apdorojimo procedûra, iðkvieèiama kaip notifikacijos callbackas ið kiekvieno aktyvaus
// lango funkcijos iðkvietimo (panaðiai kaip DefWindowProc()) arba kartu su kiekvienu DispatchMessage()
// pagrindiniame programos praneðimø apdorojimo cikle.
// Patá taimerá paleidþia KpsTestReg(), ðita paprogramë tik patikrina, ar perduotas praneðimo parametras nëra jai skirtas WM_TIMER,
// jei taip – atlieka tikrinimo procedûrà.
// Gràþina False, jei viskas gerai, True – klaida.
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
// Licencijos iðregistravimas.
// Tik diegiamiems produktams.
// Iðkvieèiamas ið atskiros produkto iðdiegimo programos.
// Tik jei pavyko ankstesni produkto ðalinimo veiksmai (pvz., PDF certifikato iðregistravimas)
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
