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
   (const unsigned char *)"{progpath}\\DAT0\\StartGrp.cfg",
// (const unsigned char *)"{progpath}\\StartGrp.xml",
   (const unsigned char *)"{progpath}\\DAT0\\StartGrp.htm",
   (const unsigned char *)"{progpath}\\startgrp.ini",
   NULL
};
