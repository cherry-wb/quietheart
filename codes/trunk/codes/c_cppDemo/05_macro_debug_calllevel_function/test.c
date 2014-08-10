#include <stdio.h>
#include "levellog.h"

void func111()
{
    module_enter();
    module_leave();
}

void func11()
{
    module_enter();
    module_debug("before call func111.\n");
    func111();
    module_leave();
}

void func12()
{
    module_enter();
    module_leave();
}

void func1()
{
    module_enter();
    module_debug("before call func11.\n");
    func11();
    module_debug("before call func12.\n");
    func12();
    module_leave();
}

int main(int argc, char *argv[])
{
    module_enter();
    module_debug("Hello, this is print in the function:%s\n", "main");
    func1();
    module_leave();
    return 0;
}

