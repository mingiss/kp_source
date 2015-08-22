echo extern unsigned char setup_%1[ > setup_%1.h
kpsfsz.exe files_flash_upd_ind\%2.exe >> setup_%1.h
echo ]; >> setup_%1.h

echo extern unsigned char setup_%1[ > setup_%1.cpp
kpsfsz.exe files_flash_upd_ind\%2.exe >> setup_%1.cpp
echo ]={ >> setup_%1.cpp
kpsdmp2.exe files_flash_upd_ind\%2.exe 16 n b c >> setup_%1.cpp
echo }; >> setup_%1.cpp
