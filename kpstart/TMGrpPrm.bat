echo //---------------------------- > TMGrpPrm.cpp
echo // TMGrpPrm.sav file image >> TMGrpPrm.cpp
echo // neredaguoti - failas generuojamas automatiskai >> TMGrpPrm.cpp
echo // >> TMGrpPrm.cpp
echo #define TMGrpPrm_FILE_SIZE \>> TMGrpPrm.cpp
kpsfsz.exe TMGrpPrm.sav >> TMGrpPrm.cpp
echo // >> TMGrpPrm.cpp
echo unsigned char TMGrpPrm[TMGrpPrm_FILE_SIZE]={ >> TMGrpPrm.cpp
kpsdmp2.exe TMGrpPrm.sav 16 n b c >> TMGrpPrm.cpp
echo }; >> TMGrpPrm.cpp
