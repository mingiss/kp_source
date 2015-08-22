echo //---------------------------- > iBsh_ini.cpp
echo // iBsh.ini data >> iBsh_ini.cpp
echo // >> iBsh_ini.cpp
echo #include "envir.h" >> iBsh_ini.cpp
echo // >> iBsh_ini.cpp
echo #include "stdio.h" >> iBsh_ini.cpp
echo #include "string" >> iBsh_ini.cpp
echo #include "fstream" >> iBsh_ini.cpp
echo #include "windows.h" >> iBsh_ini.cpp
echo #include "richedit.h" >> iBsh_ini.cpp
echo #include "Richole.h" >> iBsh_ini.cpp
echo #include "time.h" >> iBsh_ini.cpp
echo // >> iBsh_ini.cpp
echo #if Compiler != Watcom >> iBsh_ini.cpp
echo using namespace std; >> iBsh_ini.cpp
echo #endif >> iBsh_ini.cpp
echo // >> iBsh_ini.cpp
echo #include "kpstdlib.h" >> iBsh_ini.cpp
echo #include "kptree.h" >> iBsh_ini.cpp
echo #include "kperrno.h" >> iBsh_ini.cpp
echo #include "kptt.h" >> iBsh_ini.cpp
echo #include "kpstring.h" >> iBsh_ini.cpp
echo #include "kpcolors.h" >> iBsh_ini.cpp
echo #include "kpstdio.h" >> iBsh_ini.cpp
echo #include "kpwindow.h" >> iBsh_ini.cpp
echo #include "kperr.h" >> iBsh_ini.cpp
echo #include "kpsock.h" >> iBsh_ini.cpp
echo #include "kpcapp.h" >> iBsh_ini.cpp
echo #include "tvmain.h" >> iBsh_ini.cpp
echo #include "xmlp.h" >> iBsh_ini.cpp
echo #include "kpstap.h" >> iBsh_ini.cpp
echo // >> iBsh_ini.cpp
echo unsigned char InternalIniData[ >> iBsh_ini.cpp
kpsfsz.exe iBsh.ini >> iBsh_ini.cpp
echo ]={ >> iBsh_ini.cpp
kpsdmp2.exe iBsh.ini 16 n b c >> iBsh_ini.cpp
echo }; >> iBsh_ini.cpp
