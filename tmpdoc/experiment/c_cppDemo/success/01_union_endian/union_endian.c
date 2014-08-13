/*程序功能：测试使用联合的方式，以及使用这种方式来查看int类型存放的时候，大端小端对齐的存放方式。
*这里，测试机器为小端方式的，所以结果为：
*4
*3
*2
*1
*也就是说，对于4个字节的int类型，也是按照低地址（就是内存地址较小者）存放低字节（就是数值低位）
*或者说“小”的（即低位）存放在“端”（即内存的起点端，因为内存大小不定所以没有终点端）
*/
#include <stdio.h>
union Test
{
	int data;
	char data2[4];
};

int main(int argc, char *argv[])
{
	union Test t;
	int i = 0;
	t.data=0x01020304;
	for(i = 0; i < 4; ++i)
	{
		printf("char[%d]:%d\n",i,t.data2[i]);
	}
	return 0;
}
