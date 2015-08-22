mkdir kplibw.%1
echo xcopy /Y $1 kplibw.%1 > kplibws.mcr
kpsgrp kplibws.mcr @kplibw.mcl > nul
