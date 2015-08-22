mkdir kpstrsvr.%1
echo xcopy /Y $1 kpstrsvr.%1 > kpstrsvs.mcr
kpsgrp kpstrsvs.mcr @kpstrsvr.mcl > nul
kpsgrp kpstrsvs.mcr @f:\kp\source\common\kplibw.mcl > nul
