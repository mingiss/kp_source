@echo off
echo ---------------------------------------------
echo kpttu16.txt will be deleted - are you sure ???
echo if not - press Ctrl-C !!!
echo ---------------------------------------------
pause
echo on
del kpttu16.txt
ftp -s:kpttu16.get mindux
"C:\Program Files\Microsoft Office\Office\WINWORD.EXE" kpttu16.txt
ftp -s:kpttu16.put mindux
