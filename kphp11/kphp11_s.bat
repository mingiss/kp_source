mkdir f:\kp\source\kphp11\kphp11.%1
rem copy Debug\kphp11.exe kphp11v.exe
echo copy $1 f:\kp\source\kphp11\kphp11.%1 > kphp11_s.mcr
kpsgrp kphp11_s.mcr @kphp11.mcl > nul
kpsgrp kphp11_s.mcr @f:\kp\source\common\kplibw.mcl > nul
