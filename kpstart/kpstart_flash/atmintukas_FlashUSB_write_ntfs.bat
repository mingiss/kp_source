@echo off

rem -----------------------------------------
rem   atmintuko generavimo scriptas
rem   i�kvie�iamas programos atmintukas.exe
rem   gauna parametrus:
rem      %1 - atmintuko Ser.No. - a�tuoni� skaitmen� �e�ioliktainis skai�ius
rem      %2 - atmintuko u�koduotas Ser.No. atmintuko kodui
rem      %3 - �ios dienos data
rem      %4 - atmintuko disko raid� su dvita�kiu ir sle�u, pvz., E:\
rem


if "%7"=="" goto pabaiga

echo Koreguojamas failas Output_flash\matau5e.ini ...
kpstedb.exe Output_flash\MaTau5e.ini %1

echo Koreguojamas failas ..\atmintukai.txt ...
echo 5M2-%2	000000%1	%3	MaTau-5E_mokytojui_v1.11.2 >> ..\atmintukai.txt
notepad ..\atmintukai.txt

echo Atmintuk� suformatuokite NTFS, tomo vard� �veskite MaTau5m_v1.11.2
pause

echo Aplanko Output_flash turinys kopijuojamas � atmintuk�...
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
echo diegimui pasirinkite atmintuko katalog� %4Matematika Tau-5E mokytojui
MaTau-5E_mokytojui_v1.11.2_diegimas_atmintuke.exe

echo Koreguojamas failas %4Matematika Tau-6E mokytojui\data.dat ...
setatm.exe "%4Matematika Tau-5E mokytojui\data.dat" 5M2-%2

echo Visus atmintuko failus padarykite Read-Only, i�skyrus Matematika Tau-5E mokytojui\cd\cd_turinys.pdf ir katalog� Mano.
echo Visiems min�tiems failams nustatykite Security atributus tik Everyone Read ir Execute.
pause

rem echo Kuriamas %4fl.dat ...
rem genfldat.exe %4

rem echo Read-Only padarykite fail� %4fl.dat.
rem echo Nustatykite failo %4fl.dat security atributus tik Everyone Read ir Execute.
rem pause

:pabaiga
pause
