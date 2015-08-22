@echo off

rem -----------------------------------------
rem   atmintuko generavimo scriptas
rem   iðkvieèiamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko Ser.No. - aðtuoniø skaitmenø ðeðioliktainis skaièius
rem      %2 - atmintuko uþkoduotas Ser.No. atmintuko kodui
rem      %3 - ðios dienos data
rem      %4 - atmintuko disko raidë su dvitaðkiu ir sleðu, pvz., E:\
rem


if "%7"=="" goto pabaiga

echo Koreguojamas failas Output_flash\matau5e.ini ...
kpstedb.exe Output_flash\MaTau5e.ini %1

echo Koreguojamas failas ..\atmintukai.txt ...
echo 5M2-%2	000000%1	%3	MaTau-5E_mokytojui_v1.11.2 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Atmintukà suformatuokite NTFS, tomo vardà áveskite MaTau5m_v1.11.2
pause

echo Aplanko Output_flash turinys kopijuojamas á atmintukà...
mkdir "%4Mano"
mkdir "%4Matematika Tau-5E mokytojui"
copy Output_flash\diegimas.doc %4
copy Output_flash\MaTau-5E_redaktorius_v1.11.6_diegimas.exe %4
copy Output_flash\MATAU5.ICO %4
copy Output_flash\MaTau5e.ini %4
copy Output_flash\Pradzia_MaTau-5E_mokytojui.exe %4
copy Output_flash\TevAutorun.inf %4
copy Output_flash\TevAutoRun.txt %4
copy Output_flash\TevAutoRunSetup.exe %4

echo Diegiamas MaTau-5E_mokytojui_v1.11.2_diegimas_atmintuke.exe ...
echo diegimui pasirinkite atmintuko katalogà %4Matematika Tau-5E mokytojui
MaTau-5E_mokytojui_v1.11.2_diegimas_atmintuke.exe

echo Koreguojamas failas %4Matematika Tau-6E mokytojui\data.dat ...
setatm.exe "%4Matematika Tau-5E mokytojui\data.dat" 5M2-%2

echo Visus atmintuko failus padarykite Read-Only, iðskyrus Matematika Tau-5E mokytojui\cd\cd_turinys.pdf ir katalogà Mano.
echo Visiems minëtiems failams nustatykite Security atributus tik Everyone Read ir Execute.
pause

rem echo Kuriamas %4fl.dat ...
rem genfldat.exe %4

rem echo Read-Only padarykite failà %4fl.dat.
rem echo Nustatykite failo %4fl.dat security atributus tik Everyone Read ir Execute.
rem pause

:pabaiga
pause
