rem copy Debug\xmlrpt.exe .
mkdir xmlrpt.%1
echo xcopy /Y $1 xmlrpt.%1 > xmlrpt_s.mcr
kpsgrp xmlrpt_s.mcr @xmlrpt.mcl > nul
kpsgrp xmlrpt_s.mcr @..\..\common\kplibt.mcl > nul
