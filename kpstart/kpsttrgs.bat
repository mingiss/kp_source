mkdir kpsttrg.%1
echo xcopy /Y $1 kpsttrg.%1 > kpsttrgs.mcr
kpsgrp kpsttrgs.mcr @kpsttrg.mcl > nul
kpsgrp kpsttrgs.mcr @f:\kp\source\common\kplibw.mcl > nul
