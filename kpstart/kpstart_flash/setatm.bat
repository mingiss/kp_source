rem setatm.exe E:data.dat 000-000000

rem setatm.exe data.dat AI=GG0-65062-1780
rem setatm.exe data.dat AI=GG0-64227-6566

rem setatm.exe data.dat ProdVer=1072
rem setatm.exe data.dat ProdVar=0
rem setatm.exe data.dat ProductVersion=2.11
rem setatm.exe data.dat ProductVersionMin=1.02

rem setatm.exe data.dat AI=ABC-12345-6789

rem setatm.exe data.dat ProductDate="2010.12.31"

rem setatm.exe data.dat AI=GG0-64227-6566 ProdVer=1072 ProdVar=0 ProductVersion=2.11 ProductVersionMin=1.02 ProductDate="2010.12.31"
rem setatm.exe data.dat AI=GG0-64227-6566 ProdVar=0 ProductDate="2010.12.31"

rem setatm.exe ..\data.dat ProdVar=1

rem setatm.exe ..\data.dat ProductDate="2010.12.32"
setatm.exe ..\data.dat ProductDate=@setatm.txt
