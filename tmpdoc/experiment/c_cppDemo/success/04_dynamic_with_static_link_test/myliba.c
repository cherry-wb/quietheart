#include <stdio.h>
#include "myliba.h"
void printa(void)
{
#ifdef MYFLAG
	printf("use flag\n");
#endif
	printf("hello in liba\n");
}
