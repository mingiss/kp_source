echo on
rem ---------------------------------
rem iskvietimas:
rem    call make_free.bat [Publisher] [ProjID]

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir files
mkdir files
echo copy orig_ikona\%2.ico files
copy orig_ikona\%2.ico files


rem ---------------------------------
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

echo copy kpstart_cd_free.ini F:\kp\source\kpstart\kpstart.ini
copy kpstart_cd_free.ini F:\kp\source\kpstart\kpstart.ini
echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart
echo call F:\kp\source\kpstart\kpstart_ini.bat
call F:\kp\source\kpstart\kpstart_ini.bat


rem ---------------------------------
echo del /S/Q F:\kp\source\kpstart\kpstart_obj
del /S/Q F:\kp\source\kpstart\kpstart_obj
call F:\kp\source\kpstart\kpstart_mak.bat
:: call F:\kp\source\kpstart\kpstart6432_mak.bat


rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir Output
mkdir Output
echo mkdir maps
mkdir maps

echo mkdir files_sh
mkdir files_sh
echo copy F:\kp\source\kpstart\kpstart.exe files_sh\%2.exe
copy F:\kp\source\kpstart\kpstart.exe files_sh\%2.exe
echo copy F:\kp\source\kpstart\kpstart_mingw.map maps
copy F:\kp\source\kpstart\kpstart_mingw.map maps

rem ---------------------------------
@echo off

kpsleep.exe 3000

call geniss.bat

kpsleep.exe 3000

call gen_cd.bat noprompt
