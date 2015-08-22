@echo off

rem -----------------------------------------
rem   atmintuko generavimo scenarijus
rem   iðkvieèiamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko tekstinis Ser.No. - aðtuoniø skaitmenø ðeðioliktainis skaièius
rem      %2 - atmintuko uþkoduotas Ser.No. atmintuko kodui
rem      %3 - ðios dienos data
rem      %4 - atmintuko disko raidë su dvitaðkiu ir sleðu, pvz., E:\
rem      %5 - atmintuko disko raidë su dvitaðkiu be sleðo, pvz., E:
rem      %6 - atmintuko Ser.No. - aðtuoniø skaitmenø ðeðioliktainis skaièius,
rem           toks, koks matosi kpstedf.exe
rem      %7 - atmintuko disko raidë be nieko, pvz., E
rem


if "%7"=="" goto pabaiga

rem DiskFlash.exe

echo Koreguojamas failas ..\atmintukai.txt ...
echo T70-%2	%1[%6]	%3	TBK78m_v1.10.0 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas TBK78M00 ...
label %5 TBK78M00

echo Trinamas brukalas ...
del %4UFDUtility.exe
del %4CarryItEasy.exe
del "%4Password Protection User Manual (CarryItEasy.exe).pdf"

echo Aplanko Output_flash turinys kopijuojamas á atmintukà ...
xcopy /E Output_flash\* %4

echo Koreguojamas failas %4TBK78m.ini ...
kpstedb.exe %4TBK78m.ini %6

echo Nustatomi failø atributai ...
copy %4TBK78m.ini %4TBK78m.ini.sav
attrib %4TBK78m.ini +h
attrib %4TBK78m.ini.sav +r +h
attrib %4autorun.inf +r +h

mkdir %4Mano_TBK78m

echo Koreguojamas failas %4TBK78_MIKO\data.dat ...
setatm.exe "%4TBK78_MIKO\data.dat" T70-%2

:pabaiga
pause
