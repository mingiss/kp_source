mkdir f:\kp\source\kpstart\kpstreg.%1
rem copy Debug\kpstreg.exe .\kpstreg.exe
echo xcopy /Y $1 f:\kp\source\kpstart\kpstreg.%1 > kpstregs.mcr
kpsgrp kpstregs.mcr @kpstreg.mcl > nul
kpsgrp kpstregs.mcr @f:\kp\source\common\kplibw.mcl > nul
