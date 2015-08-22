mkdir StartGrp.%1
echo xcopy /Y $1 StartGrp.%1 > StartGrps.mcr
copy StartGrps.mcr file.mcr
kpsgrp file.mcr @StartGrp.mcl > nul
kpsgrp file.mcr @f:\kp\source\common\kplibw.mcl > nul
