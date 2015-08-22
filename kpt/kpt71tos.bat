mkdir kpt71tou.%1
echo copy $1 kpt71tou.%1 > kpt71tou.mcr
kpsgrp kpt71tou.mcr @kpt71tou.mcl > nul
kpsgrp kpt71tou.mcr @f:\kp\source\common\kplibt.mcl > nul
