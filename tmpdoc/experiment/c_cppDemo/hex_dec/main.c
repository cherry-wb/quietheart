/*Trans the 16 base string to int.
*/
#include <stdio.h>
#include   <stdlib.h>
#include <string.h>
int   convert16(const char* szHex);
int main(int argc, char *argv[])
{
	int m = 0;
	m = convert16(argv[1]);

	printf("m dec:%d, m hex:%x\n",m,m);
	return 0;
}

int convert16(const char* szHex)
{
	int   sum=0;
	int   index=0;
	int   tmp=0;

	while(szHex[index])
	{
		switch(szHex[index])
		{
			case   'A':
			case   'a':
				tmp=10;
				break;
			case   'B':
			case   'b':
				tmp=11;
				break;
			case   'C':
			case   'c':
				tmp=12;
				break;
			case   'D':
			case   'd':
				tmp=13;
				break;
			case   'E':
			case   'e':
				tmp=14;
				break;
			case   'F':
			case   'f':
				tmp=15;
				break;
			default:
				if( '0' <=szHex[index]   &&   szHex[index] <= '9')
				{
					tmp=szHex[index]- '0';
				}
				else
				{
					tmp=0;
				}
				break;
		}
		index++;
		sum=(sum<<4)+tmp;
	}
	return sum;
}
