rem call dmp8.bat kphp11.bin
rem call dmp8.bat ..\..\kphp11\kphp11.bin.start
rem fc kphp11.bin.txt ..\..\kphp11\kphp11.bin.start.txt > kphp11.dif

call kphp11.dmp.bat
fc kphp11.bin.txt kphp11.bin.txt.sav > kphp11.dif
