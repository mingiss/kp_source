echo extern unsigned char setup_%1[ > setup_%1.h
kpsfsz.exe files_grp\setup\setup_%1.exe >> setup_%1.h
echo ]; >> setup_%1.h

echo extern unsigned char setup_%1[ > setup_%1.cpp
kpsfsz.exe files_grp\setup\setup_%1.exe >> setup_%1.cpp
echo ]={ >> setup_%1.cpp
kpsdmp2.exe files_grp\setup\setup_%1.exe 16 n b c >> setup_%1.cpp
echo }; >> setup_%1.cpp
