#include <stdlib.h>
main()
{
system("dir > kpn1.txt");

system("echo , > empty.txt");
system("date < empty.txt > cur_date.txt");

system("date 1994.01.01");
system("touch kpn1.txt");
system("date 2001.12.07");

return(0);
}
