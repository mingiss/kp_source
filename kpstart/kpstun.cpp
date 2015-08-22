// ---------------------------
// kpstun.cpp
// licenzijos panaikinimas
//
// kpstun.exe kopijuojamas i:
//    unreg_tev.exe   - #ifdef KPST_TEV
//    unreg_arkim.exe - #ifdef KPST_ARKIM
//
// po to pervadinamas i unreg.exe
// start.ini faila nukopijuoti i unreg.ini ir uzdeti "CID tiesiogiai"
//

// -----------------------------------------
#define STAND_ALONE

#include "kpstunr.cpp"

const unsigned char lpszProdName[] = "kpstun"; 
