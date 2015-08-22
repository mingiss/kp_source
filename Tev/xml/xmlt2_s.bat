copy Debug\xmlt2.exe .
mkdir xmlt2.%1
echo copy $1 xmlt2.%1 > xmlt2_s.mcr
kpsgrp xmlt2_s.mcr @xmlt2.mcl > nul
