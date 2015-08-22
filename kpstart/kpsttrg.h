// ---------------
// kpsttrg.h
// produkto licencijos registracija ir vëlesnis jos tikrinimas
//

#ifndef kpsttrg_included
#define kpsttrg_included


// ---------------
// praneðimø piktogramos ID
//
// #define KP_IDI_SETUP_ICON  124


// ---------------
// Iðkvieèiama vienà kartà programos pradþioje, neigiamas atsakymas - registracija nepavyko.
// Diegiamiems produktams:
//    Atlieka licencijos registracijos procedûrà pirmo programos paleidimo metu. 
//    Gautas atsakymas ið registravimo serverio atsimenamas, o programà paleidþiant kitus kartus, tik tikrinama, 
//    ar tie kodai neiðsitrynë ir ar vis dar atitinka kompiuterio parametrus.
//    Jeigu produktas registruojamas atskira programa registr.exe - èia tik patikrinimas, registracijos procedûros nëra,
// Atmintukams:
//    Tikrina, ar ákiðtas produkto atmintukas.
// Naudojimas:
//    if(SUCCEEDED(KpsTestReg())){ ... }
//
#define KpsTestReg KpsTR
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpsTestReg(void);


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
HRESULT KpsUnReg(void);

// -----------------
// produkto id
extern int GetProdVer(void);

#endif // #ifndef kpsttrg_included
