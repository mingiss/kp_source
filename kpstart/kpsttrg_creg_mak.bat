echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpsttrg_obj
mkdir kpsttrg_obj
echo del /S/Q kpsttrg_obj
del /S/Q kpsttrg_obj

rem del /Q libkpsttrg.a
del /Q libkpsttrg.a

echo make -f kpsttrg_creg.mak
make -f kpsttrg_creg.mak

echo mkdir cert
mkdir cert
echo mkdir cert\Launcher
mkdir cert\Launcher
echo mkdir cert\Launcher\src
mkdir cert\Launcher\src
echo mkdir cert\Launcher\src\lib
mkdir cert\Launcher\src\lib
echo copy libkpsttrg.a cert\Launcher\src\lib
copy libkpsttrg.a cert\Launcher\src\lib
