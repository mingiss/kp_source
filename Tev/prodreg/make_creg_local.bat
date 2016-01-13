:: @echo off
:: ---------------------------------
:: iskvietimas:
::    call make_creg_local.bat [build'o komentaras]

Q:
cd \Ebook_DB\TEV\MTP5E

echo incbuild.exe %1
:: incbuild.exe %1

if not exist files\sts.exe goto :nodiag
copy startsel.exe files\sts.exe
:nodiag

del make_creg.log
call O:\eknygu_gamyba\make_creg.bat TEV MTP5E MTP5E.pfx SVQm60q9f2zs 1>> make_creg.log  2>&1
