echo //---------------------------- > %1_ini.cpp
echo // Kpstart %2 .ini data >> %1_ini.cpp
echo // >> %1_ini.cpp
echo #include "envir.h" >> %1_ini.cpp
echo #include "iBshn.h" >> %1_ini.cpp
echo #include "lzdshn.h" >> %1_ini.cpp
echo // >> %1_ini.cpp
echo #include "stdio.h" >> %1_ini.cpp
echo #include "string" >> %1_ini.cpp
echo #include "fstream" >> %1_ini.cpp
echo #include "windows.h" >> %1_ini.cpp
echo #include "commctrl.h" >> %1_ini.cpp
echo #include "richedit.h" >> %1_ini.cpp
echo #include "Richole.h" >> %1_ini.cpp
echo #include "time.h" >> %1_ini.cpp
echo // >> %1_ini.cpp
echo #if CompilerGr == Mingw >> %1_ini.cpp
echo #include "IInputStream.hh" >> %1_ini.cpp
echo #include "IString.hh" >> %1_ini.cpp
echo #include "XApplication.hh" >> %1_ini.cpp
echo #include "XGecko.hh" >> %1_ini.cpp
echo #include "XGeckoDOMEvent.hh" >> %1_ini.cpp
echo #include "XGeckoInit.hh" >> %1_ini.cpp
echo #endif >> %1_ini.cpp
echo // >> %1_ini.cpp
echo #if Compiler != Watcom >> %1_ini.cpp
echo using namespace std; >> %1_ini.cpp
echo #endif >> %1_ini.cpp
echo // >> %1_ini.cpp
echo #include "kpstdlib.h" >> %1_ini.cpp
echo #include "kperrno.h" >> %1_ini.cpp
echo #include "kptt.h" >> %1_ini.cpp
echo #include "kptree.h" >> %1_ini.cpp
echo #include "kpctype.h" >> %1_ini.cpp
echo #include "kpstring.h" >> %1_ini.cpp
echo #include "kpcolors.h" >> %1_ini.cpp
echo #include "kpfonts.h" >> %1_ini.cpp
echo #include "kpstdio.h" >> %1_ini.cpp
echo #include "kpttucf.h" >> %1_ini.cpp
echo #include "res_com.h" >> %1_ini.cpp
echo #include "kpwindow.h" >> %1_ini.cpp
echo #include "kpsock.h" >> %1_ini.cpp
echo #include "kphp11i.h" >> %1_ini.cpp
echo #include "kphp11t.h" >> %1_ini.cpp
echo #include "kpcapp.h" >> %1_ini.cpp
echo #include "tvmain.h" >> %1_ini.cpp
echo #include "tvrtf.h" >> %1_ini.cpp
echo #include "tvrtfo.h" >> %1_ini.cpp
echo #include "tvtex.h" >> %1_ini.cpp
echo #include "tvxml.h" >> %1_ini.cpp
echo #include "xmlp.h" >> %1_ini.cpp
echo #include "xmlh.h" >> %1_ini.cpp
echo #include "xmlf.h" >> %1_ini.cpp
echo #include "xml8.h" >> %1_ini.cpp
echo #include "xmlu.h" >> %1_ini.cpp
echo #include "xmlo1.h" >> %1_ini.cpp
echo #include "xmlt.h" >> %1_ini.cpp
echo #include "xmlis.h" >> %1_ini.cpp
echo #include "xmli.h" >> %1_ini.cpp
echo #include "KpFileSys.h" >> %1_ini.cpp
echo #include "xmln.h" >> %1_ini.cpp
echo #include "xmlg.h" >> %1_ini.cpp
echo #include "KpPubDlg.h" >> %1_ini.cpp
echo #include "kpstap.h" >> %1_ini.cpp
echo // >> %1_ini.cpp
echo unsigned char InternalIniData[ >> %1_ini.cpp
f:\kp\bin\kpsfsz.exe %1.ini >> %1_ini.cpp
echo ]={ >> %1_ini.cpp
f:\kp\bin\kpsdmp2.exe %1.ini 16 n b c >> %1_ini.cpp
echo }; >> %1_ini.cpp
