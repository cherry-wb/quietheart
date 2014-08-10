/*利用可变参数，展示vprintf使用。*/
#include <stdio.h>
#include <stdarg.h>
static int myprint(char *fmt, ...);
int main(int argc, char *argv[])
{
    myprint("func:%s, line:%d\n", __func__, __LINE__);
    return 0;
}

int myprint(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}
