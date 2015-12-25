echo on
rem ---------------------------------
rem iskvietimas:
rem    call make_KURK.bat [Publisher] [ProjID]

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2
echo geniss.exe
geniss.exe

echo copy kpstart_cd_tux.ini F:\kp\source\kpstart\kpstart.ini
copy kpstart_cd_tux.ini F:\kp\source\kpstart\kpstart.ini
echo F:
F:
echo cd \kp\source\kpstart
cd \kp\source\kpstart
echo call F:\kp\source\kpstart\kpstart_ini.bat
call F:\kp\source\kpstart\kpstart_ini.bat


rem ---------------------------------
echo del /S/Q F:\kp\source\kpstart\kpsttrg_obj
del /S/Q F:\kp\source\kpstart\kpsttrg_obj
call F:\kp\source\kpstart\kpsttrg6432_mak.bat

rem ---------------------------------
echo Q:
Q:
echo cd \Ebook_DB\%1\%2
cd \Ebook_DB\%1\%2

echo copy F:\kp\source\kpstart\tux_XFS\lib\libkpsttrg.a .
copy F:\kp\source\kpstart\tux_XFS\lib\libkpsttrg.a .
