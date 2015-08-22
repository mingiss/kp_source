mkdir xmldep.%1
echo copy $1 xmldep.%1 > xmldeps.mcr
kpsgrp xmldeps.mcr @xmldep.mcl > nul
kpsgrp xmldeps.mcr @..\..\common\kplibt.mcl > nul
