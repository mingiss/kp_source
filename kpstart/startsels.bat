mkdir StartSel.%1
echo xcopy /Y $1 StartSel.%1 > StartSels.mcr
copy StartSels.mcr file.mcr
kpsgrp file.mcr @StartSel.mcl > nul
kpsgrp file.mcr @f:\kp\source\common\kplibw.mcl > nul
