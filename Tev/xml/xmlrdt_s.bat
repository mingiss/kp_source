mkdir xmlrdt.%1
echo copy $1 xmlrdt.%1 > xmlrdt_s.mcr
kpsgrp xmlrdt_s.mcr @xmlrdt.mcl > nul
kpsgrp xmlrdt_s.mcr @..\..\common\kplibt.mcl > nul
