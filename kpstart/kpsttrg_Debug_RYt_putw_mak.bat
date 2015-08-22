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

echo make -f kpsttrg_Debug_RYt_putw.mak
make -f kpsttrg_Debug_RYt_putw.mak

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy libkpsttrg.a tux_XFS\lib
copy libkpsttrg.a tux_XFS\lib
