mkdir kpstlsvr.%1
rem copy Debug\kpstlsvr.exe .\kpstlsvrv.exe
echo xcopy /Y $1 kpstlsvr.%1 > kpstlsvs.mcr
kpsgrp kpstlsvs.mcr @kpstlsvr.mcl > nul
kpsgrp kpstlsvs.mcr @f:\kp\source\common\kplibw.mcl > nul
