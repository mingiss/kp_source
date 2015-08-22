mkdir lzdshe.%1
echo xcopy /Y $1 lzdshe.%1 > lzdshe_s.mcr
kpsgrp lzdshe_s.mcr @lzdshe.mcl > nul
kpsgrp lzdshe_s.mcr @f:\kp\source\common\kplibw.mcl > nul
