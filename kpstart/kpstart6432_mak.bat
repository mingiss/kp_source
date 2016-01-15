echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpstart_obj
mkdir kpstart_obj
echo del /S/Q kpstart_obj
del /S/Q kpstart_obj

echo del /Q kpstart.exe
del /Q kpstart.exe
       
echo make -f kpstart6432.mak
make -f kpstart6432.mak
