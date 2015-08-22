echo extern unsigned char setup_%2_%3[ > setup_%2_%3.h
kpsfsz.exe %1\setup\setup_%2.exe >> setup_%2_%3.h
echo - %4]; >> setup_%2_%3.h

echo extern unsigned char setup_%2_%3[ > setup_%2_%3.cpp
kpsfsz.exe %1\setup\setup_%2.exe >> setup_%2_%3.cpp
echo - %4]={ >> setup_%2_%3.cpp
kpsdmp2.exe %1\setup\setup_%2.exe 16 n b c %4 >> setup_%2_%3.cpp
echo }; >> setup_%2_%3.cpp
