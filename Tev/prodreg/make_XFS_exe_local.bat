rem @echo off

Q:
cd \Ebook_DB\TEV\TEST

echo incbuild.exe "%1"
incbuild.exe "%1"

if not exist files\sts.exe goto :nodiag
copy startsel.exe files\sts.exe
:nodiag

del make_XFS_exe.log
call O:\eknygu_gamyba\make_XFS_exe.bat TEV TEST KaroMenoIstorija.bmp 1>> make_XFS_exe.log  2>&1
del make_XFS_exe_sh.log
call O:\eknygu_gamyba\make_XFS_exe_sh.bat TEV TEST KaroMenoIstorija.bmp 1>> make_XFS_exe_sh.log  2>&1
