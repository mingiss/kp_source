mkdir unlock.%1
rem copy Debug\unlock.exe .\unlock.exe
echo xcopy /Y $1 unlock.%1 > unlocks.mcr
kpsgrp unlocks.mcr @unlock.mcl > nul
kpsgrp unlocks.mcr @f:\kp\source\common\kplibw.mcl > nul
