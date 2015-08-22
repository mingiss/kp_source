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

echo Koreguojamas failas ..\atmintukai.txt ...
echo LGK-%2	%1[%6]	%3	WinLEDg5.05d.20 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Nustatomas atmintuko bendros srities tomo vardas WLEDg505d20 ...
label %5 WLEDg505d20


echo Failas lzdshpf_cla.ini kopijuojamas á atmintukà ...
copy Output_flash\lzdshpf_cla.ini %4

echo Koreguojamas failas %4lzdshpf_cla.ini ...
kpstedb.exe %4lzdshpf_cla.ini %6

echo Nustatomi failo %4lzdshpf_cla.ini atributai ...
attrib %4lzdshpf_cla.ini +r +h


echo Failas lzdshpf_mahd.ini kopijuojamas á atmintukà ...
copy Output_flash\lzdshpf_mahd.ini %4

echo Koreguojamas failas %4lzdshpf_mahd.ini ...
kpstedb.exe %4lzdshpf_mahd.ini %6

echo Nustatomi failo %4lzdshpf_mahd.ini atributai ...
attrib %4lzdshpf_mahd.ini +r +h


echo Failas WinLED.ini kopijuojamas á atmintukà ...
copy Output_flash\WinLED.ini %4

echo Koreguojamas failas %4WinLED.ini ...
kpstedb.exe %4WinLED.ini %6

echo Nustatomi failo %4WinLED.ini atributai ...
attrib %4WinLED.ini +r +h


echo Aplanko Output_flash turinys kopijuojamas á atmintukà ...
mkdir "%4WinLED v5.0"
copy Output_flash\autorun.inf %4
attrib %4autorun.inf +r
copy Output_flash\Pradzia_WinLED.exe %4
attrib %4Pradzia_WinLED.exe +r
copy Output_flash\skaityk.txt %4
attrib %4skaityk.txt +r
copy Output_flash\TevAutoRun.inf %4
attrib %4TevAutoRun.inf +r
copy Output_flash\TevAutoRunSetup.exe %4
attrib %4TevAutoRunSetup.exe +r

echo Diegiamas WinLED_v5.05d.20_diegimas_atmintuke.exe ...
WinLED_v5.05d.20_diegimas_atmintuke.exe /SILENT /DIR="%4WinLED v5.0"

rem echo Koreguojamas failas %4Matematika Tau-6E mokytojui\data.dat ...
rem setatm.exe "%4Matematika Tau-5E mokytojui\data.dat" 5MK-%2

:pabaiga
pause
