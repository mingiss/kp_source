copy Debug\tvxmlque.exe .
mkdir xmlque.%1
echo copy $1 xmlque.%1 > xmlque_s.mcr
kpsgrp xmlque_s.mcr @xmlque.mcl > nul
