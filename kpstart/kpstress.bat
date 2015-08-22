mkdir f:\kp\source\kpstart\kpstresq.%1
echo xcopy /Y $1 f:\kp\source\kpstart\kpstresq.%1 > kpstress.mcr
kpsgrp kpstress.mcr @kpstresq.mcl > nul
kpsgrp kpstress.mcr @f:\kp\source\common\kplibw.mcl > nul
