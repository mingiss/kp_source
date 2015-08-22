mkdir lzdsh.%1

mkdir lzdsh.%1\lzdshd_setup\files
mkdir lzdsh.%1\lzdshp_setup\files_cd
mkdir lzdsh.%1\lzdshp_setup\files_flash
mkdir lzdsh.%1\lzdshp_setup\files_free

echo xcopy /Y $1 lzdsh.%1 > lzdsh_s.mcr
kpsgrp lzdsh_s.mcr @lzdsh.mcl > nul
kpsgrp lzdsh_s.mcr @f:\kp\source\common\kplibw.mcl > nul

copy lzdshd_setup\files\lzdshd_cla.exe lzdsh.%1\lzdshd_setup\files\lzdshd_cla.exe
copy lzdshd_setup\files\lzdshd_mahd.exe lzdsh.%1\lzdshd_setup\files\lzdshd_mahd.exe
copy lzdshp_setup\files_cd\lzdshp_cla.exe lzdsh.%1\lzdshp_setup\files_cd\lzdshp_cla.exe
copy lzdshp_setup\files_cd\lzdshp_mahd.exe lzdsh.%1\lzdshp_setup\files_cd\lzdshp_mahd.exe
copy lzdshp_setup\files_flash\lzdshp_mahd.exe lzdsh.%1\lzdshp_setup\files_flash\lzdshp_mahd.exe
copy lzdshp_setup\files_flash\lzdshp_cla.exe lzdsh.%1\lzdshp_setup\files_flash\lzdshp_cla.exe
copy lzdshp_setup\files_free\lzdshp_cla.exe lzdsh.%1\lzdshp_setup\files_free\lzdshp_cla.exe
copy lzdshp_setup\files_free\lzdshp_mahd.exe lzdsh.%1\lzdshp_setup\files_free\lzdshp_mahd.exe
