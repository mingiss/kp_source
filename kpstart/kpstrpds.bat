mkdir kpstrpd.%1
echo xcopy /Y $1 kpstrpd.%1 > kpstrpds.mcr
kpsgrp kpstrpds.mcr @kpstrpd.mcl > nul
kpsgrp kpstrpds.mcr @f:\kp\source\common\kplibw.mcl > nul
