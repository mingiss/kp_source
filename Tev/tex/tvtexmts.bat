copy Debug\tvtexmtt.exe .
mkdir tvtexmtt.%1
echo copy $1 tvtexmtt.%1 > tvtexmts.mcr
kpsgrp tvtexmts.mcr @tvtexmtt.mcl > nul
