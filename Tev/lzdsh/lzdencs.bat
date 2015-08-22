mkdir lzdenc.%1

echo xcopy /Y $1 lzdenc.%1 > lzdencs.mcr
kpsgrp lzdencs.mcr @lzdenc.mcl > nul
kpsgrp lzdencs.mcr @f:\kp\source\common\kplibt.mcl > nul
 