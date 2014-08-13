#include <stdio.h>
#include "mylibb.h"
void printb(void)
{
#ifdef MYFLAG
	printf("use flag\n");
#endif
	printf("hello in libb\n");
}
