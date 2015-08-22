mkdir lzdshw.%1
echo xcopy /Y $1 lzdshw.%1 > lzdshw_s.mcr
kpsgrp lzdshw_s.mcr @lzdshw.mcl > nul
kpsgrp lzdshw_s.mcr @f:\kp\source\common\kplibw.mcl > nul
