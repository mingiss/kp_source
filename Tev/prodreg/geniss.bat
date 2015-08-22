@echo off

    call files.bat

    call files_cd.bat
    call files_sh.bat
    call files_upd.bat
    call files_upd_whole.bat
    call files_del.bat
    call files_del_whole.bat

    call files_grp.bat

    call files_flash.bat
    call files_flash_upd.bat
    call files_flash_upd_whole.bat
    call files_flash_start.bat
    rem call files_flash_start_upd.bat

    call files_net.bat
    call files_svr.bat
    call files_cli.bat
    call files_rez.bat

    call files_chkvol.bat

    call fonts.bat


geniss.exe 1>> geniss.lst  2>&1
