@echo off

rem -----------------------------------------
rem   atmintuko generavimo scenarijus
rem   iğkvieèiamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko tekstinis Ser.No. - ağtuoniø skaitmenø ğeğioliktainis skaièius
rem      %2 - atmintuko licencijos kodas
rem      %3 - ğios dienos data
rem      %4 - atmintuko disko raidë su dvitağkiu ir sleğu, pvz., E:\
rem      %5 - atmintuko disko raidë su dvitağkiu be sleğo, pvz., E:
rem      %6 - atmintuko Ser.No. - ağtuoniø skaitmenø ğeğioliktainis skaièius,
rem           toks, koks matosi kpstedf.exe
rem      %7 - atmintuko disko raidë be nieko, pvz., E
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
