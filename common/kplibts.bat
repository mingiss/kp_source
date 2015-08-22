mkdir kplibt.%1
echo xcopy /Y $1 kplibt.%1 > kplibts.mcr
kpsgrp kplibts.mcr @kplibt.mcl > nul
