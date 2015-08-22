#include <stdio.h>
int main()
{
union REGS in_regs, out_regs;
struct SREGS seg_regs;
char *f_name="c:/tmp/failas.txt"

in_regs.h.ah=0x3d;

int intdosx(union REGS *inregs, union REGS *outregs,
    struct SREGS *segregs);
int86
   printf("kahgfg\n");
return(0);
}
