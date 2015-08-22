copy Debug\tvtexchy.exe .
mkdir tvtexchy.%1
echo copy $1 tvtexchy.%1 > tvtexchs.mcr
kpsgrp tvtexchs.mcr @tvtexchy.mcl > nul
