@echo off
echo ---------------------------------------------
echo tvxmlt.dtd will be deleted - are you sure ???
echo if not - press Ctrl-C !!!
echo ---------------------------------------------
pause
echo on
copy tvxmlt.dtd tvxmltd.sav
del tvxmlt.dtd
ftp -s:xmlt_dtd.get mindux
"C:\Program Files\Microsoft Office\Office\WINWORD.EXE" tvxmlt.dtd
copy tvxmlt.dtd ..\vlz_xmlt
ftp -s:xmlt_dtd.put mindux
