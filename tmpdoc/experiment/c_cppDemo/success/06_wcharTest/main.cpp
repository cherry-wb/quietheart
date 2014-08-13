/*程序功能：测试宽类型字节的使用,将多字节表示的字符存储在宽字节类型中并打印
 * 功能包括：
 * 1）初始化宽字节字符和字符串
 * 2）使用wcout和wprintf显示宽字节字符和字符串
 * 3）使用swprintf(类似sprintf)将宽字节字符串复制到一个宽字节数组中并打印出来
 *
 * 使用宽字节显示的注意事项：
 * 1）初始化wchar_t的时候，字符前面需要加上一个L.
 * 2）使用wcout显示之前，需要用setlocale设置语言，这里干脆全设置了。
 * 3）或者使用wcout显示之前，用wcout.imbue
 *
 * 实际应该用一般的char类型也能做到多字节的存储与显示但是这里用的是宽字节来实现的
 * 问题：
 * 为什么wcout和cout同时在程序中出现会导致输出错乱呢？
 **/
#include <iostream>
//#include <cwctype>
//#include <wchar.h>
//#include <stdio.h>
using std::cout;
using std::wcout;
using std::endl;
int main(int argc, char *argv[])
{
	//初始化一个宽字节字符
	wchar_t c = L'你';

	//初始化一个宽字节字符串
	wchar_t cstr[] = L"你好";
	//wchar_t *cstr = L"你好";//这种方法尽量不用，应该被摒弃
	
	//cout<<"test"<<endl;//有这句话会无法显示后面的东西
	//设置显示中文之前要先进行设置
	setlocale(LC_ALL,"");//方法1
	//方法2：setlocale(LC_ALL,"Chinese-simplified");但是不知道为什么不行
	//方法3: wcout.imbue(std::locale("chs"));不知道为什么不行
	
	//显示宽字节字符和字符串
	//cout<<"now begin to show wide char:"<<endl;//有这句话会无法显示后面的东西
	wcout<<c<<endl;
	wprintf(L"%C\n",c);//注意这里是大写的C
	wcout<<cstr<<endl;
	wprintf(cstr);
	wcout<<endl;//这里如果用cout<<endl;不行无法回车
	wprintf(L"%S\n",cstr);//注意这里是大写的S
	//cout<<"test"<<endl;//在这里这个输不出来

	//////利用swprintf将宽字节字符复制到wchar_t的var数组中并打印出来
	wchar_t var[100] = L"";
	swprintf(var,100,L"%S",cstr);
	wprintf(L"%S\n",var);//注意这里是大写的S

	return 0;
}
