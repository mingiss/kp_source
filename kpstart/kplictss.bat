mkdir kplictst.%1
echo xcopy /Y $1 kplictst.%1 > kplictss.mcr
kpsgrp kplictss.mcr @kplictst.mcl > nul
kpsgrp kplictss.mcr @f:\kp\source\common\kplibw.mcl > nul
