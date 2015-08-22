copy Debug\kpttbp.exe .
mkdir kpttbp.%1
echo copy $1 kpttbp.%1 > kpttbp_s.mcr
kpsgrp kpttbp_s.mcr @kpttbp_s.mcl > nul
