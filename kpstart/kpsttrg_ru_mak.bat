echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpsttrg_ru_obj
mkdir kpsttrg_ru_obj
echo make -f kpsttrg_ru.mak
make -f kpsttrg_ru.mak

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy libkpsttrg_ru.a tux_XFS\lib\libkpsttrg.a
copy libkpsttrg_ru.a tux_XFS\lib\libkpsttrg.a
