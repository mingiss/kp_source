echo F:
F:
echo cd \kp\source\common
cd \kp\source\common

echo mkdir kplibwr_obj
mkdir kplibwr_obj
echo del /S/Q kplibwr_obj
del /S/Q kplibwr_obj

rem del /Q libkplibwr.a
del /Q libkplibwr.a

echo make -f kplibwr.mak
make -f kplibwr.mak > kplibwr_mak.log 2>&1

:: echo start /wait C:\PROGRA~1\CodeBlocks\codeblocks.exe kplibwr32.cbp --build --no-batch-window-close
:: start /wait C:\PROGRA~1\CodeBlocks\codeblocks.exe kplibwr32.cbp --build --no-batch-window-close
