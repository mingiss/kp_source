rem copy Debug\xmlext.exe .
mkdir xmlext.%1
echo copy $1 xmlext.%1 > xmlext_s.mcr
kpsgrp xmlext_s.mcr @xmlext.mcl > nul
rem copy f:\wrk\kp\source\tev\vlz\vlz_xmlt\vlz_a.xml xmlext.%1\vlz_a_orig.xml
kpsgrp xmlext_s.mcr @..\..\common\kplibt.mcl > nul
