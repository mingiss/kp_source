echo extern unsigned char setup_%1[%4]; >> setup_%1.h

echo extern unsigned char setup_%1[%4]={ >> setup_%1.cpp
kpsdmp2.exe files_flash_upd_ind\%2.exe 16 n b c %3 %4 >> setup_%1.cpp
echo }; >> setup_%1.cpp
