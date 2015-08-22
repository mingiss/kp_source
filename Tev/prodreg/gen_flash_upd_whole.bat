@echo off


copy "%ProgramFiles%\Inno Setup 5\Languages\Lithuanian_upd_evad.isl" "%ProgramFiles%\Inno Setup 5\Default.isl" > nul


rem "%ProgramFiles%\Microsoft Application Compatibility Toolkit 5\Compatibility Administrator\Compatadmin.exe"


rem call geniss.bat
geniss.exe 1>> geniss.lst  2>&1


rem UVCView.x86.exe
rem kpstedb.exe Output_flash\XFS.ini

if "%1" == "noprompt" goto noprompt_label
gen_flash_upd_whole.iss
goto pabaiga
:noprompt_label
"%ProgramFiles%\Inno Setup 5\Compil32.exe" /cc gen_flash_upd_whole.iss
:pabaiga
