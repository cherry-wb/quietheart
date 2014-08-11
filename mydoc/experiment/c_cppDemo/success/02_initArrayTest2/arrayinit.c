/*测试数组的初始化情况。
结果：
int a[10];这样的定义，导致a中值是随机的。
int b[10] = {1,2};这样的定义，导致b中前两个元素是1,2后面全是0.
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    int a[10];
    int b[10]={1,2};

    for (i = 0; i < 10; ++i)
    {
        printf("a[%d] = %d, ", i, a[i]);
    }

    printf("\n");
    for (i = 0; i < 10; ++i)
    {
        printf("b[%d] = %d, ", i, b[i]);
    }
    printf("\n");

    return 0;
}
