echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart

echo mkdir kpsttrg_pl_obj
mkdir kpsttrg_pl_obj
echo make -f kpsttrg_s_pl.mak
make -f kpsttrg_s_pl.mak

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy libkpsttrg_pl.a tux_XFS\lib\libkpsttrg.a
copy libkpsttrg_pl.a tux_XFS\lib\libkpsttrg.a
