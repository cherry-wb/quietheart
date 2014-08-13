/*程序功能：
 *字符串的拷贝：
 *char *strcpy(char *dest, const char *src);
 *拷贝字符串，包括其中的‘\0'结束符号到dest中。

 *char *strncpy(char *dest, const char *src, size_t n);
 *拷贝限定大小的字符串到dest中，
 *如果src长度小于n,那么会把src长度直到n的内容自动填充为'\0',如果src长度大于会将src截断，并且不会将'\0'拷贝到dest中去。
*/
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	char *src = "12345";

	char dst[10];
	strcpy(dst,src);
	printf("%s\n",dst);//12345

	char dst2[10]= {'a',};
	dst2[3]=dst2[4]=dst2[5]='a';
	strncpy(dst2,src,3);
	printf("%s,%c\n",dst2,dst2[3]);//123aaa,a

	char dst3[10] = {'a'};
	strncpy(dst3,src,8);
	printf("%s\n",dst3);//12345
	return 0;
}
