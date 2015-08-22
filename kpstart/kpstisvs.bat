mkdir kpstisvr.%1
echo xcopy /Y $1 kpstisvr.%1 > kpstisvs.mcr
kpsgrp kpstisvs.mcr @kpstisvr.mcl > nul
kpsgrp kpstisvs.mcr @f:\kp\source\common\kplibw.mcl > nul
