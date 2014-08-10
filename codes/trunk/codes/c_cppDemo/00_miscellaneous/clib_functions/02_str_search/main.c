/*程序功能：
	给定一个字符串，查找并返回字符串中第一个指定的子字符串的位置
*/
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	char *test = "first:two:three:four:five";
	int pos1 = strstr(test,":") - test;//第一个冒号的下标位置
	printf("pos1 is:%d\n",pos1);
	int pos2 = strstr(test,"two") - test;//第一个"two"的下标位置
	printf("pos2 is:%d\n",pos2);
}

