mkdir kpstart.%1
rem copy Debug\kpstart.exe .\kpstartv.exe
echo xcopy /Y $1 kpstart.%1 > kpstarts.mcr
kpsgrp.exe kpstarts.mcr @kpstart.mcl > nul
kpsgrp.exe kpstarts.mcr @f:\kp\source\common\kplibw.mcl > nul
