/*程序功能：
 * 测试rename函数，这个函数当对于dir的时候，如果newdir已经存在且空，那么olddir命名为newdir的时候newdir先被删掉；如果newdir非空，那么没有任何动作。
 * */
#include <stdio.h>

int rename(const char *oldname, const char *newname);
int main(int argc, char *argv[])
{
	printf("begin to rename the directory\n");
	rename("./dirold","dirnew");

	printf("end\n");
	return 0;
}
