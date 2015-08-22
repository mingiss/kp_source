dir files_del /s /b /ON > files_del.dir
perl files_del.pl < files_del.dir > files_del.txt
