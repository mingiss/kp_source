// ---------------------------
// kpstreg.cpp
// aplikacijos lic. kodo registravimas
//
// kpstreg.exe kopijuojamas i:
//    registr_tev.exe   - #ifdef KPST_TEV
//   (registr_arkim.exe - #ifdef KPST_ARKIM)
//
// po to pervadinamas i registr.exe
// start.ini faila nukopijuoti i registr.ini ir uzdeti "CID tiesiogiai"
//

#define STAND_ALONE

#include "kpstrg.cpp"

const unsigned char lpszProdName[] = "kpstreg";
