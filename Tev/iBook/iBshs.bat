mkdir iBsh.%1
echo xcopy /y $1 iBsh.%1 > iBshs.mcr
copy iBshs.mcr file.mcr
copy iBsh.mcl file.mcl
kpsgrp file.mcr @file.mcl > nul
kpsgrp file.mcr @..\..\common\kplibw.mcl > nul
