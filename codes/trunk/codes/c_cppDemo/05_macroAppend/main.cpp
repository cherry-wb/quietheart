/*程序功能：
 * 这里测试预处理命令中的字符串拼接语法部分，对于
 * #define macro(param)
 * 形式定义的宏，如果宏的实现体中有以'##'为前缀的方式引用param,例如：
 * string##param()
 * 那么就实现拼接的功能，例如宏macro(mytest)
 * 会对应"stringmytest"
 * */
#include <iostream>
#include "mymacroappend.h"
using std::cout;
using std::endl;
PLUGIN_FUNC_DECL(myfunc)
int main(int argc, char *argv[])
{
	PLUGIN_FUNC_CALL(myfunc);
}
PLUGIN_FUNC_IMPL(myfunc)
