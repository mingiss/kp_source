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


echo ----------------------------------
echo %1
echo %2
echo %3
echo %4
echo %5
echo %6
echo %7


echo %2	%1[%6]	%3	GGG11-12	11.2.4 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

pause
