/*程序功能：
*这里定义了一些比较常用的用于打印的宏。
*可以通过指定的开关来打印对应级别的宏，或者干脆什么都不打印。
*/
#include "debug_print.h"
int main(int argc, char *argv[])
{
	//Usage of debug functions regard of level(It's best to use these functions to print log.)
	pr_level_debug(1,"Test the %s.\n","debug functions with log level.");//use as "printf",with log level 1.
	pr_level_debug_loc(1);//print the code File,Function,and line position,with log level 1.
	pr_level_debug_var(1,"hello,debug test with level!");//print any type of variable,with log level 1.

	//Usage of debug functions regardless of levels (It's best not use these functions).
	pr_debug("Test the %s.\n","debug functions without log level.");//use as printf.
	pr_debug_loc();//print the code File,Function,and line position.
	char *str = "hello!";
	pr_debug_var(str);//print any type of variable.
	pr_debug_var("hello,debug test!");

	return 0;
}


