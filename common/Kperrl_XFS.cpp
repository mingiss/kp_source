// ==================================================
// kperrl.cpp
// KpProcessError() papildomø prie DiagMsg prijungiamø failø sàraðas
// prikompiliuojamas prie XFS projekto (prie kpsttrg.lib), skirtingiems projektams gali bûti skirtingi
//

// ======================================= definitions
#include <windows.h>

#include "kperrno.h"

// --------------------------------------------
const unsigned char *KpDiagMsgAddFiles[] =
{
// (const unsigned char *)"{temp}\\" KP_XFS_LOG_FNAME,
   (const unsigned char *)"{temp}\\xipa.log",
// (const unsigned char *)"{progpath}\\002.dat", // èia dël R__svarbiinfo.js viduj
   NULL
};
