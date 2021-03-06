@echo off

rem -----------------------------------------
rem   atmintuko generavimo scenarijus
rem   i�kvie�iamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko tekstinis Ser.No. - a�tuoni� skaitmen� �e�ioliktainis skai�ius
rem      %2 - atmintuko licencijos kodas
rem      %3 - �ios dienos data
rem      %4 - atmintuko disko raid� su dvita�kiu ir sle�u, pvz., E:\
rem      %5 - atmintuko disko raid� su dvita�kiu be sle�o, pvz., E:
rem      %6 - atmintuko Ser.No. - a�tuoni� skaitmen� �e�ioliktainis skai�ius,
rem           toks, koks matosi kpstedf.exe
rem      %7 - atmintuko disko raid� be nieko, pvz., E
rem


if "%7"=="" goto pabaiga

rem DiskFlash.exe

echo Koreguojamas failas ..\atmintukai.txt ...
echo %2	%1[%6]	%3	MIKO_TBK78_v1.10.3 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas TBK78M ...
label %5 TBK78M

echo Trinamas failas %4UFDUtility.exe ...
del %4UFDUtility.exe

echo Aplanko Output_flash turinys kopijuojamas � atmintuk� ...
xcopy /E/Y Output_flash\* %4

echo Koreguojamas failas %4TBK78m.ini ...
kpstedb.exe %4TBK78m.ini -f%6 -p%2

echo Nustatomi fail� atributai ...
copy %4TBK78m.ini %4TBK78m.ini.sav
attrib %4TBK78m.ini +h
attrib %4TBK78m.ini.sav +h

attrib %4autorun.inf +r +h

rem mkdir %4Mano_TBK7-8

echo Koreguojamas failas %4DAK7\data.dat ...
setatm.exe "%4DAK7\data.dat" %2

:pabaiga
pause
