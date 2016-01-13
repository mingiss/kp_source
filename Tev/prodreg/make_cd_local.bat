:: @echo off
:: ---------------------------------
:: iskvietimas:
::    call make_cd_local.bat [build'o komentaras]

Q:
cd \Ebook_DB\TEV\MTP5E

echo incbuild.exe %1
:: incbuild.exe %1

if not exist files\sts.exe goto :nodiag
copy startsel.exe files\sts.exe
:nodiag

del make_cd.log
call O:\eknygu_gamyba\make_cd.bat TEV MTP5E  1>> make_cd.log  2>&1
