@echo off

rem -----------------------------------------
rem   atmintuko generavimo scenarijus
rem   iðkvieèiamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko tekstinis Ser.No. - aðtuoniø skaitmenø ðeðioliktainis skaièius
rem      %2 - atmintuko licencijos kodas
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
echo %2	%1[%6]	%3	IPAB 2000-2009 v2.22.3 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas IPAB22_3 ...
label %5 IPAB22_3

echo Trinamas failas %4UFDUtility.exe ...
del %4UFDUtility.exe

echo Aplanko Output_flash turinys kopijuojamas á atmintukà ...
xcopy /E/Y Output_flash\* %4

echo Koreguojamas failas %4ipab.ini ...
kpstedb.exe %4ipab.ini -f%6 -p%2

echo Nustatomi failø atributai ...
copy %4ipab.ini %4tux_ipa.ini
attrib %4ipab.ini +r +h
attrib %4tux_ipa.ini +r +h

echo attrib "%4$1" +r +h > ro.mcr
kpsgrp.exe ro.mcr @Output_flash\DAT0\kpstbls.ini

attrib "%4Pradzia_IPA_Biologija_2000-2009(b)ipab(d)bin.exe" +r -h

rem echo Koreguojamas failas %4IPA Biologija 2000-2009\data.dat ...
rem setatm.exe "%4IPA Biologija 2000-2009\data.dat" %2

:pabaiga
pause
