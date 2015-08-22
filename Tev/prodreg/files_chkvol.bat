dir files_chkvol /s /b /ON > files_chkvol.dir
perl files_chkvol.pl < files_chkvol.dir > files_chkvol.txt
