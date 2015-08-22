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
echo %2	%1[%6]	%3	MIKO_TBK56_v2.10.0 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas MIKO knyga ...
label %5 MIKO knyga

echo Trinamas failas %4UFDUtility.exe ...
del %4UFDUtility.exe

echo Aplanko Output_flash turinys kopijuojamas � atmintuk� ...
xcopy /E/Y Output_flash\* %4

echo Koreguojamas failas %4TBK56m.ini ...
kpstedb.exe %4TBK56m.ini -f%6 -p%2

echo Nustatomi fail� atributai ...
copy %4TBK56m.ini %4TBK56m.ini.sav
attrib %4TBK56m.ini +h
attrib %4TBK56m.ini.sav +h

attrib %4autorun.inf +r +h

echo attrib "%4$1" +r +h > ro.mcr
kpsgrp.exe ro.mcr @Output_flash\DAT0\kpstbls.ini

attrib "%4Papildomos funkcijos.exe" +r -h
attrib "%4Pradzia.exe" +r -h

rem mkdir %4Mano_TBK5-6

echo Koreguojamas failas %4DAK5\data.dat ...
setatm.exe "%4DAK5\data.dat" %2

:pabaiga
pause
