echo on
:: ---------------------------------
:: iskvietimas:
::    call make_creg.bat [Publisher] [ProjID] [Password]

goto cont

:: ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir files
mkdir files
echo copy orig_ikona\%2.ico files
copy orig_ikona\%2.ico files

:: ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2
echo geniss.exe
geniss.exe

if not exist files\sts.exe goto :nodiag
mkdir files_sh\DAT0
copy kpstart_cd.ini files_sh\DAT0\sts.ini
:nodiag

echo copy kpstart_cd.ini F:\kp\source\kpstart\kpstart.ini
copy kpstart_cd.ini F:\kp\source\kpstart\kpstart.ini
echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart
echo call F:\kp\source\kpstart\kpstart_ini.bat
call F:\kp\source\kpstart\kpstart_ini.bat


:: ---------------------------------
call F:\kp\source\kpstart\kpsttrg_creg_mak.bat



:cont 


:: ---------------------------------
echo F:
F:
echo cd \kp\source\kpstart\cert\Launcher\src
cd \kp\source\kpstart\cert\Launcher\src

echo F:\kp\source\kpstart\cert\Launcher\src\bin\Tool.exe Q:\Ebook_DB\%1\%2\%3 %4 F:\kp\source\kpstart\cert\Launcher\src\src\Launcher\cert0.cc
F:\kp\source\kpstart\cert\Launcher\src\bin\Tool.exe Q:\Ebook_DB\%1\%2\%3 %4 F:\kp\source\kpstart\cert\Launcher\src\src\Launcher\cert0.cc

call F:\kp\source\kpstart\cert\Launcher\src\Launcher_mak.bat


:: ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo copy F:\kp\source\kpstart\libkpsttrg.a .
copy F:\kp\source\kpstart\libkpsttrg.a .

echo mkdir Output
mkdir Output

echo mkdir files_sh
mkdir files_sh
echo copy F:\kp\source\kpstart\cert\Launcher\src\bin\Launcher.exe files_sh
copy F:\kp\source\kpstart\cert\Launcher\src\bin\Launcher.exe files_sh

:: ---------------------------------
@echo off

kpsleep.exe 3000

call geniss.bat

kpsleep.exe 3000

call gen_creg.bat noprompt
