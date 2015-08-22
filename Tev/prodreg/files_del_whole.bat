dir files_del_whole /s /b /ON > files_del_whole.dir
perl files_del_whole.pl < files_del_whole.dir > files_del_whole.txt
