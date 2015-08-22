echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpsttrg_en_obj
mkdir kpsttrg_en_obj
echo make -f kpsttrg_en.mak
make -f kpsttrg_en.mak

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy libkpsttrg_en.a tux_XFS\lib\libkpsttrg.a
copy libkpsttrg_en.a tux_XFS\lib\libkpsttrg.a
