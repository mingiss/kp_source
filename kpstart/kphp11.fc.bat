call dmp8.bat kphp11.bin
call dmp8.bat ..\kphp11\kphp11.bin.start
fc kphp11.bin.txt ..\kphp11\kphp11.bin.start.txt > kphp11.dif
