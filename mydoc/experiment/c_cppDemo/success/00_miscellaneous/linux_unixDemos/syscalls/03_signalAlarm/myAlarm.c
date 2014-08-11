//this program test the alarm system call,it set the second ,in which the process ends.
#include<stdio.h>
#include<unistd.h>
int main(void)
{
unsigned int i;
alarm(1);
for(i = 0; 1; ++i)
{
printf("I=%d\n",i);
}
return 0;
}
