@echo off


copy "%ProgramFiles%\Inno Setup 5\Languages\Lithuanian_KMP.isl" "%ProgramFiles%\Inno Setup 5\Default.isl" > nul


:: "%ProgramFiles%\Microsoft Application Compatibility Toolkit 5\Compatibility Administrator\Compatadmin.exe"


:: call geniss.bat
geniss.exe 1>> geniss.lst  2>&1


if "%1" == "noprompt" goto noprompt_label
gen_net.iss
goto pabaiga
:noprompt_label
"%ProgramFiles%\Inno Setup 5\Compil32.exe" /cc gen_net.iss
:pabaiga
