echo //---------------------------- > geniss_0_ini.cpp
echo // geniss_0.ini data >> geniss_0_ini.cpp
echo // >> geniss_0_ini.cpp
echo #include "envir.h" >> geniss_0_ini.cpp
echo #include "iBshn.h" >> geniss_0_ini.cpp
echo // >> geniss_0_ini.cpp
echo #include "stdio.h" >> geniss_0_ini.cpp
echo #include "string" >> geniss_0_ini.cpp
echo #include "fstream" >> geniss_0_ini.cpp
echo #include "windows.h" >> geniss_0_ini.cpp
echo #include "richedit.h" >> geniss_0_ini.cpp
echo #include "Richole.h" >> geniss_0_ini.cpp
echo #include "time.h" >> geniss_0_ini.cpp
echo // >> geniss_0_ini.cpp
echo #if Compiler != Watcom >> geniss_0_ini.cpp
echo using namespace std; >> geniss_0_ini.cpp
echo #endif >> geniss_0_ini.cpp
echo // >> geniss_0_ini.cpp
echo #include "kpstdlib.h" >> geniss_0_ini.cpp
echo #include "kperrno.h" >> geniss_0_ini.cpp
echo #include "kptt.h" >> geniss_0_ini.cpp
echo #include "kptree.h" >> geniss_0_ini.cpp
echo #include "kpctype.h" >> geniss_0_ini.cpp
echo #include "kpstring.h" >> geniss_0_ini.cpp
echo #include "kpcolors.h" >> geniss_0_ini.cpp
echo #include "kpfonts.h" >> geniss_0_ini.cpp
echo #include "kpstdio.h" >> geniss_0_ini.cpp
echo #include "kpttucf.h" >> geniss_0_ini.cpp
echo #include "res_com.h" >> geniss_0_ini.cpp
echo #include "kpwindow.h" >> geniss_0_ini.cpp
echo #include "kpsock.h" >> geniss_0_ini.cpp
echo #include "kphp11i.h" >> geniss_0_ini.cpp
echo #include "kphp11t.h" >> geniss_0_ini.cpp
echo #include "kpcapp.h" >> geniss_0_ini.cpp
echo #include "tvmain.h" >> geniss_0_ini.cpp
echo #include "tvrtf.h" >> geniss_0_ini.cpp
echo #include "tvrtfo.h" >> geniss_0_ini.cpp
echo #include "tvtex.h" >> geniss_0_ini.cpp
echo #include "tvxml.h" >> geniss_0_ini.cpp
echo #include "xmlp.h" >> geniss_0_ini.cpp
echo #include "xmlh.h" >> geniss_0_ini.cpp
echo #include "xmlf.h" >> geniss_0_ini.cpp
echo #include "xml8.h" >> geniss_0_ini.cpp
echo #include "xmlu.h" >> geniss_0_ini.cpp
echo #include "xmlo1.h" >> geniss_0_ini.cpp
echo #include "xmlt.h" >> geniss_0_ini.cpp
echo #include "xmlis.h" >> geniss_0_ini.cpp
echo #include "xmli.h" >> geniss_0_ini.cpp
echo #include "KpFileSys.h" >> geniss_0_ini.cpp
echo #include "xmln.h" >> geniss_0_ini.cpp
echo #include "xmlg.h" >> geniss_0_ini.cpp
echo #include "kpstap.h" >> geniss_0_ini.cpp
echo // >> geniss_0_ini.cpp
echo unsigned char InternalIniData[ >> geniss_0_ini.cpp
kpsfsz.exe geniss_0.ini >> geniss_0_ini.cpp
echo ]={ >> geniss_0_ini.cpp
kpsdmp2.exe geniss_0.ini 16 n b c >> geniss_0_ini.cpp
echo }; >> geniss_0_ini.cpp
