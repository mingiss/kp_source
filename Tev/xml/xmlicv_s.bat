rem copy Debug\xmlicv.exe .
mkdir xmlicv.%1
echo xcopy /y $1 xmlicv.%1 > xmlicv_s.mcr
kpsgrp xmlicv_s.mcr @xmlicv.mcl > nul
kpsgrp xmlicv_s.mcr @f:\kp\source\common\kplibt.mcl > nul
