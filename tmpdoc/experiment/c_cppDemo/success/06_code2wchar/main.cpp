/*程序功能：给定一个中文字符的编码，得到相应的中文字符并且打印出来
 * 例如：'人'的编码分别是：
 * 机内码：C8CB
 * 区位码：4043
 * 国标码：484B
 * Unicode码：4EBA
 * 通过实验可以知道，直接将Unicode码转换为wchar_t的话，可以显示.
 * */
#include <iostream>
//#include <cwctype>
//#include <wchar.h>
//#include <stdio.h>
using std::cout;
using std::wcout;
using std::endl;
int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");//方法1

	wchar_t c = wchar_t(0xC8CB);
	wcout<<L"1,"<<c<<endl;//用机内码显示，结果乱码。

	c = wchar_t(0x4043);
	wcout<<L"2,"<<c<<endl;//用区位码显示，结果没有显示。

	c = wchar_t(0x484B);
	wcout<<L"3,"<<c<<endl;//用国标码显示，结果没有显示。

	c = wchar_t(0x4EBA);
	//c = wchar_t(0x6C49);//汉
	wcout<<L"4,"<<c<<endl;//用Unicode码显示，结果显示'人'，正确。

	//printf("5,%C\n", c);//实际这个也行，能显示'人'，但是要把前面的所有wcout去掉。
	return 0;
}
