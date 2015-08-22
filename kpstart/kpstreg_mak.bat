echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpstreg_obj
mkdir kpstreg_obj
echo del /S/Q kpstreg_obj
del /S/Q kpstreg_obj

echo del /Q kpstreg.exe
del /Q kpstreg.exe
       
echo make -f kpstreg.mak
make -f kpstreg.mak
