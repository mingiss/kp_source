mkdir kpstw.%1
rem copy Debug\kpstw.exe .\kpstwv.exe
echo xcopy /Y $1 kpstw.%1 > kpstw_s.mcr
kpsgrp kpstw_s.mcr @kpstw.mcl > nul
kpsgrp kpstw_s.mcr @f:\kp\source\common\kplibw.mcl > nul
