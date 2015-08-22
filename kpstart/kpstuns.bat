mkdir f:\kp\source\kpstart\kpstun.%1
echo xcopy /Y $1 f:\kp\source\kpstart\kpstun.%1 > kpstuns.mcr
kpsgrp kpstuns.mcr @kpstun.mcl > nul
kpsgrp kpstuns.mcr @f:\kp\source\common\kplibw.mcl > nul
