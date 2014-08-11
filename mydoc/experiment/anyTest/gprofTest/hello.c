#include <stdio.h>
static void my_print (char *);
static void my_print2 (const char *);
int main ()
{
	char my_string[] = "hello world!";
	my_print (my_string);
	my_print2 (my_string);
	my_print (my_string);
}
void count_sum()
{
	int i,sum=0;
	for(i=0; i<10000000; i++)
		sum += i;
}
void my_print (char *string)
{
	count_sum();
	printf  ("The string is %s ", string);
}
void my_print2 (const char *string)
{
	char *string2;
	int size, i,sum =0;
	count_sum();
	size = strlen(string);
	string2 = (char *) malloc (size + 1);
	for (i = 0; i < size; i++) string2[size -1 - i] = string;
	string2[size] = '\0';
	for(i=0; i<50000000; i++)
		sum += i;
	printf  ("The string printed backward is %s ", string2);
}
