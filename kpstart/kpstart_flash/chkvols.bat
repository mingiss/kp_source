mkdir chkvol.%1
echo xcopy /Y $1 chkvol.%1 > chkvols.mcr
kpsgrp chkvols.mcr @chkvol.mcl > nul
kpsgrp chkvols.mcr @f:\kp\source\common\kplibw.mcl > nul
