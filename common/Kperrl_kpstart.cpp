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
   (const unsigned char *)"{progpath}\\AcroRead602\\Reader\\Javascripts\\Q_svarbiinfo.js",
   (const unsigned char *)"{progpath}\\AcroRead709\\Reader\\Javascripts\\Q_svarbiinfo.js",
   (const unsigned char *)"{progpath}\\AR6\\Reader\\Javascripts\\R__svarbiinfo.js",
   (const unsigned char *)"{progpath}\\AR7\\Reader\\Javascripts\\R__svarbiinfo.js",
   (const unsigned char *)"{progpath}\\AR8\\Reader\\Javascripts\\R__svarbiinfo.js",
   NULL
};
