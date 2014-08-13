#include<setjmp.h>
static jmp_buf jmpbuffer;

int main(int argc, char *argv[])
{	
	int longJmpRet = 0;
	if((longJmpRet = setjmp(jmpbuffer)) !=0)
	{/*如果跳转到此处（longjmp被调用则不为0）*/	
	}
	return 0;
}
