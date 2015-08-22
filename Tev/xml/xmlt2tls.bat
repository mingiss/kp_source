mkdir xmlt2tl.%1
echo xcopy /Y $1 xmlt2tl.%1 > xmlt2tls.mcr
kpsgrp xmlt2tls.mcr @xmlt2tl.mcl > nul
kpsgrp xmlt2tls.mcr @..\..\common\kplibt.mcl > nul
