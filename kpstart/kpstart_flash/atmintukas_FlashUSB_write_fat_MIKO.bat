@echo off

rem -----------------------------------------
rem   atmintuko generavimo scenarijus
rem   i�kvie�iamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko tekstinis Ser.No. - a�tuoni� skaitmen� �e�ioliktainis skai�ius
rem      %2 - atmintuko u�koduotas Ser.No. atmintuko kodui
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
echo T70-%2	%1[%6]	%3	TBK78m_v1.10.0 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas TBK78M00 ...
label %5 TBK78M00

echo Trinamas brukalas ...
del %4UFDUtility.exe
del %4CarryItEasy.exe
del "%4Password Protection User Manual (CarryItEasy.exe).pdf"

echo Aplanko Output_flash turinys kopijuojamas � atmintuk� ...
xcopy /E Output_flash\* %4

echo Koreguojamas failas %4TBK78m.ini ...
kpstedb.exe %4TBK78m.ini %6

echo Nustatomi fail� atributai ...
copy %4TBK78m.ini %4TBK78m.ini.sav
attrib %4TBK78m.ini +h
attrib %4TBK78m.ini.sav +r +h
attrib %4autorun.inf +r +h

mkdir %4Mano_TBK78m

echo Koreguojamas failas %4TBK78_MIKO\data.dat ...
setatm.exe "%4TBK78_MIKO\data.dat" T70-%2

:pabaiga
pause
