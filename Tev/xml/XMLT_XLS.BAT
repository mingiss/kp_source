@echo off
echo ---------------------------------------------
echo tvxmlt.xls will be deleted - are you sure ???
echo if not - press Ctrl-C !!!
echo ---------------------------------------------
pause
echo on
copy tvxmlt.xls tvxmltx.sav
del tvxmlt.xls
ftp -s:xmlt_xls.get mindux
"C:\Program Files\Microsoft Office\Office\EXCEL.EXE" tvxmlt.xls
ftp -s:xmlt_xls.put mindux
