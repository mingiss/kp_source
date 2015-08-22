echo /*  DO NOT CHANGE - GENERATED AUTOMATICALLY */ > Kphp11yd_sp21.cpp 
echo /*----------------------------------------------------------------------------*/ >> Kphp11yd_sp21.cpp 
echo /* FILENAME:         Kphp11yd_sp21.cpp                                        */ >> Kphp11yd_sp21.cpp
echo /* DESCRIPTION:      Kphp11:  Atmintis turinio masyvas                        */ >> Kphp11yd_sp21.cpp
echo /* LANGUAGE:         C++                                                      */ >> Kphp11yd_sp21.cpp
echo /* DESTINATION:      *                                                        */ >> Kphp11yd_sp21.cpp
echo /* SYSTEM_INTERFACE: *                                                        */ >> Kphp11yd_sp21.cpp
echo /* USER_INTERFACE:   *                                                        */ >> Kphp11yd_sp21.cpp
echo /* ARCHIVE_VERSION:  LATEST                                                   */ >> Kphp11yd_sp21.cpp
echo /* ARCHIVE_COMMENT:                                                           */ >> Kphp11yd_sp21.cpp
echo /*----------------------------------------------------------------------------*/ >> Kphp11yd_sp21.cpp
echo /*---------------------------------------------------- gen */ >> Kphp11yd_sp21.cpp
echo // #define Lang 7 /* Cpp */ >> Kphp11yd_sp21.cpp
echo // #define KpInc >> Kphp11yd_sp21.cpp
echo #include "stdafx.h" >> Kphp11yd_sp21.cpp
echo #include "envir.h" >> Kphp11yd_sp21.cpp
echo #include "iBshn.h" >> Kphp11yd_sp21.cpp
echo #include "lzdshn.h" >> Kphp11yd_sp21.cpp
echo #include "stdio.h" >> Kphp11yd_sp21.cpp
echo #include "string" >> Kphp11yd_sp21.cpp
echo // #include "iostream" >> Kphp11yd_sp21.cpp
echo #include "fstream" >> Kphp11yd_sp21.cpp
echo #include "time.h" >> Kphp11yd_sp21.cpp
echo #include "windows.h" >> Kphp11yd_sp21.cpp
echo #include "windowsx.h" >> Kphp11yd_sp21.cpp
echo #include "commctrl.h" >> Kphp11yd_sp21.cpp
echo #include "richedit.h" >> Kphp11yd_sp21.cpp
echo #include "Richole.h" >> Kphp11yd_sp21.cpp
echo #ifdef IBSH_RES_MODE_XGECKO >> Kphp11yd_sp21.cpp
echo #if CompilerGr==Mingw >> Kphp11yd_sp21.cpp
echo #include "IInputStream.hh" >> Kphp11yd_sp21.cpp
echo #include "IString.hh" >> Kphp11yd_sp21.cpp
echo #include "XApplication.hh" >> Kphp11yd_sp21.cpp
echo #include "XGecko.hh" >> Kphp11yd_sp21.cpp
echo #include "XGeckoDOMEvent.hh" >> Kphp11yd_sp21.cpp
echo #include "XGeckoInit.hh" >> Kphp11yd_sp21.cpp
echo #endif >> Kphp11yd_sp21.cpp
echo #endif >> Kphp11yd_sp21.cpp
echo #if (Compiler != Watcom) >> Kphp11yd_sp21.cpp
echo using namespace std; >> Kphp11yd_sp21.cpp
echo #endif >> Kphp11yd_sp21.cpp
echo #include "kpstdlib.h" >> Kphp11yd_sp21.cpp
echo #include "kperrno.h" >> Kphp11yd_sp21.cpp
echo #include "kptt.h" >> Kphp11yd_sp21.cpp
echo #include "kptree.h" >> Kphp11yd_sp21.cpp
echo #include "kpctype.h" >> Kphp11yd_sp21.cpp
echo #include "kpstring.h" >> Kphp11yd_sp21.cpp
echo #include "kpcolors.h" >> Kphp11yd_sp21.cpp
echo #include "kpfonts.h" >> Kphp11yd_sp21.cpp
echo #include "kpstdio.h" >> Kphp11yd_sp21.cpp
echo #include "kpttucf.h" >> Kphp11yd_sp21.cpp
echo #include "res_com.h" >> Kphp11yd_sp21.cpp
echo #include "kpwindow.h" >> Kphp11yd_sp21.cpp
echo #include "kpsock.h" >> Kphp11yd_sp21.cpp
echo #include "kpcapp.h" >> Kphp11yd_sp21.cpp
echo #include "tvmain.h" >> Kphp11yd_sp21.cpp
echo #include "xmlp.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11y.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11w.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11d.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11p.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11s.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11a.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11i.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11t.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11tt.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11rc.h" >> Kphp11yd_sp21.cpp
echo #include "kphp11ry.h" >> Kphp11yd_sp21.cpp
echo #include "tvrtf.h" >> Kphp11yd_sp21.cpp
echo #include "tvrtfo.h" >> Kphp11yd_sp21.cpp
echo #include "tvtex.h" >> Kphp11yd_sp21.cpp
echo #include "tvxml.h" >> Kphp11yd_sp21.cpp
echo #include "xmlp.h" >> Kphp11yd_sp21.cpp
echo #include "xmlh.h" >> Kphp11yd_sp21.cpp
echo #include "xmlf.h" >> Kphp11yd_sp21.cpp
echo #include "xml8.h" >> Kphp11yd_sp21.cpp
echo #include "xmlu.h" >> Kphp11yd_sp21.cpp
echo #include "xmlo1.h" >> Kphp11yd_sp21.cpp
echo #include "xmlt.h" >> Kphp11yd_sp21.cpp
echo #include "xmlis.h" >> Kphp11yd_sp21.cpp
echo #include "xmli.h" >> Kphp11yd_sp21.cpp
echo #include "KpFileSys.h" >> Kphp11yd_sp21.cpp
echo #include "KpPubDlg.h" >> Kphp11yd_sp21.cpp
echo #include "xmln.h" >> Kphp11yd_sp21.cpp
echo #include "kpstap.h" >> Kphp11yd_sp21.cpp
echo /*---------------------------------------------------- var */ >> Kphp11yd_sp21.cpp
echo KpRcPars ParBuf; // fictive buffer for offset calculations only >> Kphp11yd_sp21.cpp
echo long lAlign; >> Kphp11yd_sp21.cpp
echo MemBankType MemBankObj[ >> Kphp11yd_sp21.cpp
f:\kp\bin\kpsfsz.exe kphp11.bin.sp21 >> Kphp11yd_sp21.cpp
echo / 2] >> Kphp11yd_sp21.cpp
echo #ifndef ExternalKphp11 >> Kphp11yd_sp21.cpp
echo // = { .m_sArr >> Kphp11yd_sp21.cpp
echo = { >> Kphp11yd_sp21.cpp
f:\kp\bin\kpsdmp2.exe kphp11.bin.sp21 16 n w c >> Kphp11yd_sp21.cpp
echo } >> Kphp11yd_sp21.cpp
echo #endif >> Kphp11yd_sp21.cpp
echo ; >> Kphp11yd_sp21.cpp
