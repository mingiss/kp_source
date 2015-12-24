echo on
rem ---------------------------------
rem iskvietimas:
rem    call make_XFS_exe.bat [Publisher] [ProjID] [SplashBMP]

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir files
mkdir files
echo copy orig_ikona\%2.ico files
copy orig_ikona\%2.ico files

echo mkdir bin
mkdir bin
echo copy orig_atsklanda\%3 bin
copy orig_atsklanda\%3 bin

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\res
mkdir tux_XFS\res
echo copy orig_ikona\%2.ico tux_XFS\res\%2.ico
copy orig_ikona\%2.ico tux_XFS\res\%2.ico


rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2
echo geniss.exe
geniss.exe

echo xcopy /E/Y tux_XFS F:\kp\source\kpstart\tux_XFS
xcopy /E/Y tux_XFS F:\kp\source\kpstart\tux_XFS

echo touch F:\kp\source\kpstart\tux_XFS\include\tux\fs\XFS.hh
touch F:\kp\source\kpstart\tux_XFS\include\tux\fs\XFS.hh
echo touch F:\kp\source\kpstart\tux_XFS\include\tux\ipa\tux_core.hh
touch F:\kp\source\kpstart\tux_XFS\include\tux\ipa\tux_core.hh
echo touch F:\kp\source\kpstart\tux_XFS\include\tux\ipa\Xipa.hh
touch F:\kp\source\kpstart\tux_XFS\include\tux\ipa\Xipa.hh
echo touch F:\kp\source\kpstart\tux_XFS\src\tux\ipa\XipaResource.rc
touch F:\kp\source\kpstart\tux_XFS\src\tux\ipa\XipaResource.rc

if not exist files\sts.exe goto :nodiag
mkdir files_sh\DAT0
copy kpstart_cd_tux.ini files_sh\DAT0\sts.ini
:nodiag

echo copy kpstart_cd_tux.ini F:\kp\source\kpstart\kpstart.ini
copy kpstart_cd_tux.ini F:\kp\source\kpstart\kpstart.ini
echo copy kpstart_cd.ini F:\kp\source\kpstart\kpstreg.ini
copy kpstart_cd.ini F:\kp\source\kpstart\kpstreg.ini
echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart
echo call F:\kp\source\kpstart\kpstart_ini.bat
call F:\kp\source\kpstart\kpstart_ini.bat


rem ---------------------------------
echo del /S/Q F:\kp\source\kpstart\kpstreg_obj
del /S/Q F:\kp\source\kpstart\kpstreg_obj
call F:\kp\source\kpstart\kpstreg_mak.bat
echo del /S/Q F:\kp\source\kpstart\kpstun_obj
del /S/Q F:\kp\source\kpstart\kpstun_obj
call F:\kp\source\kpstart\kpstun_mak.bat

echo del /S/Q F:\kp\source\kpstart\kpsttrg_obj
del /S/Q F:\kp\source\kpstart\kpsttrg_obj
call F:\kp\source\kpstart\kpsttrg_mak.bat

echo del /S/Q F:\kp\source\kpstart\tux_XFS\tux_obj
del /S/Q F:\kp\source\kpstart\tux_XFS\tux_obj
call F:\kp\source\kpstart\tux_XFS\tux_mak.bat
echo del /S/Q F:\kp\source\kpstart\tux_XFS\XFS_dll_obj
del /S/Q F:\kp\source\kpstart\tux_XFS\XFS_dll_obj
call F:\kp\source\kpstart\tux_XFS\XFS_dll_mak.bat
echo del /S/Q F:\kp\source\kpstart\tux_XFS\XFS_obj
del /S/Q F:\kp\source\kpstart\tux_XFS\XFS_obj
call F:\kp\source\kpstart\tux_XFS\XFS_mak.bat
echo del /S/Q F:\kp\source\kpstart\tux_XFS\xipa_obj
del /S/Q F:\kp\source\kpstart\tux_XFS\xipa_obj
call F:\kp\source\kpstart\tux_XFS\xipa_mak.bat


rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir tux_XFS
mkdir tux_XFS
echo mkdir tux_XFS\lib
mkdir tux_XFS\lib
echo copy F:\kp\source\kpstart\tux_XFS\lib\libkpsttrg.a tux_XFS\lib
copy F:\kp\source\kpstart\tux_XFS\lib\libkpsttrg.a tux_XFS\lib

echo mkdir bin
mkdir bin
echo mkdir Output
mkdir Output
echo mkdir maps
mkdir maps
echo copy F:\kp\source\kpstart\tux_XFS\arch\bin\xipa.bin bin
copy F:\kp\source\kpstart\tux_XFS\arch\bin\xipa.bin bin
echo copy F:\kp\source\kpstart\tux_XFS\xipa.map maps
copy F:\kp\source\kpstart\tux_XFS\xipa.map maps

echo mkdir files_sh
mkdir files_sh
echo copy F:\kp\source\kpstart\tux_XFS\bin\XFS.exe files_sh
copy F:\kp\source\kpstart\tux_XFS\bin\XFS.exe files_sh
echo copy F:\kp\source\kpstart\tux_XFS\XFS.map maps
copy F:\kp\source\kpstart\tux_XFS\XFS.map maps
echo copy F:\kp\source\kpstart\tux_XFS\bin\XFS.dll files_sh
copy F:\kp\source\kpstart\tux_XFS\bin\XFS.dll files_sh
echo copy F:\kp\source\kpstart\tux_XFS\XFS_dll.map maps
copy F:\kp\source\kpstart\tux_XFS\XFS_dll.map maps

echo copy F:\kp\source\kpstart\kpstreg.exe files_sh\registr.exe
copy F:\kp\source\kpstart\kpstreg.exe files_sh\registr.exe
echo copy F:\kp\source\kpstart\kpstreg_mingw.map maps\registr.map
copy F:\kp\source\kpstart\kpstreg_mingw.map maps\registr.map
echo copy F:\kp\source\kpstart\kpstun.exe files_sh\unreg.exe
copy F:\kp\source\kpstart\kpstun.exe files_sh\unreg.exe
echo copy F:\kp\source\kpstart\kpstun_mingw.map maps\unreg.map
copy F:\kp\source\kpstart\kpstun_mingw.map maps\unreg.map

rem ---------------------------------
echo D:
D:
echo cd \Local\XFS
cd \Local\XFS

echo del /S/Q AcroRead709
del /S/Q AcroRead709
echo del /S/Q bin
del /S/Q bin
echo del /S/Q data
del /S/Q data
echo del /S/Q files_cd
del /S/Q files_cd

echo mkdir AcroRead709
mkdir AcroRead709
echo mkdir bin
mkdir bin
echo mkdir data
mkdir data
echo mkdir files_cd
mkdir files_cd

echo xcopy /E/Y Q:\Ebook_DB\%1\%2\AcroRead709 AcroRead709
xcopy /E/Y Q:\Ebook_DB\%1\%2\AcroRead709 AcroRead709
echo xcopy /E/Y Q:\Ebook_DB\%1\%2\bin bin
xcopy /E/Y Q:\Ebook_DB\%1\%2\bin bin
echo xcopy /E/Y Q:\Ebook_DB\%1\%2\data data
xcopy /E/Y Q:\Ebook_DB\%1\%2\data data

rem ---------------------------------
echo java -jar XFSTool2.jar bin
java -jar XFSTool2.jar bin
echo java -jar XFSTool2.jar js
java -jar XFSTool2.jar js
echo java -jar XFSTool2.jar data
java -jar XFSTool2.jar data
		
rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo mkdir files_sh
mkdir files_sh
echo xcopy /E/Y D:\Local\XFS\files_cd files_sh
xcopy /E/Y D:\Local\XFS\files_cd files_sh

rem ---------------------------------
echo D:
D:
echo cd \Local\XFS
cd \Local\XFS

echo del /S/Q files_cd
del /S/Q files_cd
echo del /S/Q AcroRead709
del /S/Q AcroRead709
echo del /S/Q bin
del /S/Q bin
echo del /S/Q data
del /S/Q data

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

rem ---------------------------------
@echo off

kpsleep.exe 3000

call geniss.bat

kpsleep.exe 3000

call gen_cd.bat noprompt
