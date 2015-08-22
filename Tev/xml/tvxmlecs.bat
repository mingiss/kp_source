mkdir tvxmlecm.%1
echo copy $1 tvxmlecm.%1 > tvxmlecs.mcr
kpsgrp tvxmlecs.mcr @tvxmlecm.mcl > nul
kpsgrp tvxmlecs.mcr @..\..\common\kplibt.mcl > nul
