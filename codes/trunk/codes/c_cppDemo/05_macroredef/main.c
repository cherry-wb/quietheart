/*测试宏定义的取消重定义
取消(重定义)宏定义，只在当前文件中取消并重定义的后面有效，不影响其它文件。

步骤：
$ make clean
$ make
$ ./main
@ main.c before redefine ok, OK:No change.
@ test.c OK str:No change
@ main.c after redefined ok, OK:Changed.
@ test.c OK str:No change
*/
#include <stdio.h>
#include "test.h"
int main(int argc, char *argv[])
{
    printf("@ %s before redefine ok, OK:%s.\n", __FILE__, OK);
    myprint();
#ifdef OK
#undef OK
#define OK "Changed"
#endif
    printf("@ %s after redefined ok, OK:%s.\n", __FILE__, OK);
    myprint();

}
