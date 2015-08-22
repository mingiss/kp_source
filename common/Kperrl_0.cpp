// ==================================================
// kperrl.cpp
// KpProcessError() papildomø prie DiagMsg prijungiamø failø sàraðas
// prikompiliuojamas prie XFS projekto (prie kpsttrg.lib), skirtingiems projektams gali bûti skirtingi
//

// ======================================= definitions
#include <windows.h>

#include "kperrno.h"

// --------------------------------------------
const unsigned char *KpDiagMsgAddFiles[] = { NULL };
