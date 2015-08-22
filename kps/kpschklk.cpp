// -------------------------------------------
// kpschklk.cpp
// Check memory leak
// grupuoja ir analizuoja KP_NEW* ir KP_DELETE* logo įrašus
// turi būti nupjauta pradžia iki KpAlloc:, o įrašai ir surikiuoti
//

#include <stdio.h>

int main(void)
{
unsigned char in_buf[1000]; 
	do
	{
		gets((char *)in_buf);
	
	
	
		if(!feof(stdin)) puts((const char *)in_buf);
		
	} while(!feof(stdin));

return(0);
}

