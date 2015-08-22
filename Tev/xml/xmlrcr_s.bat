rem copy Debug\tvxmlrcr.exe .
mkdir xmlrcr.%1
echo copy $1 xmlrcr.%1 > xmlrcr_s.mcr
kpsgrp xmlrcr_s.mcr @tvxmlrcr.mcl > nul
kpsgrp xmlrcr_s.mcr @..\..\common\kplibt.mcl > nul
