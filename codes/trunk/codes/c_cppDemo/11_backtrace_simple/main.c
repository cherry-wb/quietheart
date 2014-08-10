/*Use example of backtrace.*/
#include <stdio.h>
static int func3()
{
    printf("func:%s, line:%d\n", __func__, __LINE__);
    printf("backtrace information:\n");
    #define SIZE 100
    #define STDOUT_FILENO 0
    void *buffer[SIZE];
    int nptrs = 0;
    nptrs = backtrace(buffer, SIZE);
    printf("backtrace() returned %d addresses\r\n", nptrs);
    backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO);
}

static int func2()
{
    printf("func:%s, line:%d\n", __func__, __LINE__);
    func3();
}

static int func1()
{
    printf("func:%s, line:%d\n", __func__, __LINE__);
    func2();
}
int main(int argc, char *argv[])
{
    func1();
    return 0;
}
