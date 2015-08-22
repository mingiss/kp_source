mkdir f:\kp\source\kpstart\kpsregu.%1
echo copy $1 f:\kp\source\kpstart\kpsregu.%1 > kpsregus.mcr
kpsgrp kpsregus.mcr @kpsregu.mcl > nul
kpsgrp kpsregus.mcr @f:\kp\source\common\kplibw.mcl > nul
