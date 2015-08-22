dir files_upd_whole /s /b /ON > files_upd_whole.dir
perl files_upd_whole.pl < files_upd_whole.dir > files_upd_whole.txt
