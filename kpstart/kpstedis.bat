mkdir f:\kp\source\kpstart\kpstedi.%1
rem copy Debug\kpstedi.exe kpstediv.exe
echo xcopy /Y $1 f:\kp\source\kpstart\kpstedi.%1 > kpstedis.mcr
kpsgrp kpstedis.mcr @kpstedi.mcl > nul
kpsgrp kpstedis.mcr @f:\kp\source\common\kplibw.mcl > nul
