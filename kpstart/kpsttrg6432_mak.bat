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

:: echo make -f kpsttrg6432.mak
:: make -f kpsttrg6432.mak

echo start /wait C:\PROGRA~1\CodeBlocks\codeblocks.exe kpsttrg.cbp --build --no-batch-window-close
start /wait C:\PROGRA~1\CodeBlocks\codeblocks.exe kpsttrg.cbp --build --no-batch-window-close

goto galas

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy libkpsttrg.a tux_XFS\lib
copy libkpsttrg.a tux_XFS\lib

echo mkdir tux
mkdir tux
echo mkdir tux\tux_ipa
mkdir tux\tux_ipa
echo mkdir tux\tux_ipa\lib
mkdir tux\tux_ipa\lib
echo copy libkpsttrg.a tux\tux_ipa\lib
copy libkpsttrg.a tux\tux_ipa\lib

:galas