copy Debug\xmlt2h.exe .
mkdir xmlt2h.%1
echo copy $1 xmlt2h.%1 > xmlt2h_s.mcr
kpsgrp xmlt2h_s.mcr @xmlt2h.mcl > nul
