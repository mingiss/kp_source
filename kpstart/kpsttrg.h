// ---------------
// kpsttrg.h
// produkto licencijos registracija ir v�lesnis jos tikrinimas
//

#ifndef kpsttrg_included
#define kpsttrg_included


// ---------------
// prane�im� piktogramos ID
//
// #define KP_IDI_SETUP_ICON  124


// ---------------
// I�kvie�iama vien� kart� programos prad�ioje, neigiamas atsakymas - registracija nepavyko.
// Diegiamiems produktams:
//    Atlieka licencijos registracijos proced�r� pirmo programos paleidimo metu. 
//    Gautas atsakymas i� registravimo serverio atsimenamas, o program� paleid�iant kitus kartus, tik tikrinama, 
//    ar tie kodai nei�sitryn� ir ar vis dar atitinka kompiuterio parametrus.
//    Jeigu produktas registruojamas atskira programa registr.exe - �ia tik patikrinimas, registracijos proced�ros n�ra,
// Atmintukams:
//    Tikrina, ar �ki�tas produkto atmintukas.
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
HRESULT KpsUnReg(void);

// -----------------
// produkto id
extern int GetProdVer(void);

#endif // #ifndef kpsttrg_included
