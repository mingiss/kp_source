mkdir f:\kp\source\kpstart\kpstest.%1
echo copy $1 f:\kp\source\kpstart\kpstest.%1 > kpstests.mcr
kpsgrp kpstests.mcr @kpstest.mcl > nul
kpsgrp kpstests.mcr @f:\kp\source\common\kplibw.mcl > nul
