copy Debug\xmlrcp.exe .
mkdir xmlrcp.%1
echo copy $1 xmlrcp.%1 > xmlrcp_s.mcr
kpsgrp xmlrcp_s.mcr @xmlrcp.mcl > nul
