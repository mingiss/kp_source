echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpstun_obj
mkdir kpstun_obj
echo del /S/Q kpstun_obj
del /S/Q kpstun_obj

echo del /Q kpstun.exe
del /Q kpstun.exe

echo make -f kpstun.mak
make -f kpstun.mak
