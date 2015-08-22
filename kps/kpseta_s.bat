mkdir f:\kp\source\kps\kpseta.%1
echo copy $1 f:\kp\source\kps\kpseta.%1 > kpseta_s.mcr
kpsgrp kpseta_s.mcr @kpseta.mcl > nul
kpsgrp kpseta_s.mcr @f:\kp\source\common\kplibw.mcl > nul
