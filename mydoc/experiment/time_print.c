#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
	time_t now;
	time(&now);
	printf("1,%ld",now);
	stime(&now);
	time(&now);
	printf("2,%ld",now);
	return 0;
}
