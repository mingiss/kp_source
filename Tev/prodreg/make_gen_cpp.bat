@echo off
rem ----------------------------
rem pagamina gen.cpp is gen.iss
rem velesniam ilinkavimui i kpstrpd.exe, Pradzia_<...>.exe

echo //---------------------------------------- > gen.cpp
echo // gen.cpp                                >> gen.cpp
echo // programos paleidimo diegimo scenarijus >> gen.cpp
echo // prijungimui prie kpstrpd.exe, Pradzia_[...].exe >> gen.cpp
echo //                                        >> gen.cpp
echo #include "envir.h"                        >> gen.cpp
echo //                                        >> gen.cpp
echo #include "stdlib.h"                       >> gen.cpp
echo #include "fstream"                        >> gen.cpp
echo #include "windows.h"                      >> gen.cpp
echo //                                        >> gen.cpp
echo #if Compiler != Watcom                    >> gen.cpp
echo using namespace std;                      >> gen.cpp
echo #endif                                    >> gen.cpp
echo //                                        >> gen.cpp
echo #include "kpstdlib.h"                     >> gen.cpp
echo //                                        >> gen.cpp
echo const unsigned char *GenIssArr[] = {      >> gen.cpp
call perl make_gen_cpp.pl < gen.iss            >> gen.cpp
echo NULL                                      >> gen.cpp
echo };                                        >> gen.cpp
