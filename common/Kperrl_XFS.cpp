// ==================================================
// kperrl.cpp
// KpProcessError() papildom� prie DiagMsg prijungiam� fail� s�ra�as
// prikompiliuojamas prie XFS projekto (prie kpsttrg.lib), skirtingiems projektams gali b�ti skirtingi
//

// ======================================= definitions
#include <windows.h>

#include "kperrno.h"

// --------------------------------------------
const unsigned char *KpDiagMsgAddFiles[] =
{
// (const unsigned char *)"{temp}\\" KP_XFS_LOG_FNAME,
   (const unsigned char *)"{temp}\\xipa.log",
// (const unsigned char *)"{progpath}\\002.dat", // �ia d�l R__svarbiinfo.js viduj
   NULL
};
