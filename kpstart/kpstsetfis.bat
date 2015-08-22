mkdir kpstsetfi.%1
echo xcopy /Y $1 kpstsetfi.%1 > kpstsetfis.mcr
kpsgrp.exe kpstsetfis.mcr @kpstsetfi.mcl > nul
kpsgrp.exe kpstsetfis.mcr @f:\kp\source\common\kplibw.mcl > nul
