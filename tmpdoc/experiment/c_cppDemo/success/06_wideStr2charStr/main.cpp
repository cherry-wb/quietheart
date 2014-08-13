/*程序功能：将wideChar*的字符串转换成char*的字符串
 * 核心函数:
 * #include <stdlib.h>
 * size_t wcstombs(char *dest, const wchar_t *src, size_t n);
 * 拷贝src至多n个字节到dest，要保证dest有空间。
 * 返回转换的字节数。
 * */
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	//////初始化
	setlocale(LC_ALL,"");
	wchar_t in[] = L"你好吗";
	char out[50];
	for(int i = 0; i < 50; ++i)
	{//去掉可能的结束标记
		out[i] = -1;
	}

	//////转换,将宽字节字符串转换为char*字符串,这里是关键!!
	int cnt = 0;
	cnt = wcstombs(out, in, 50);//不用手动赋值结束标记了

	cout<<out<<endl;//可以打印了

	//检查其余的输出
	cout<<"bytes convert is:"<<cnt<<endl;
	cout<<(int)out[8]<<endl;//-105
	cout<<(int)out[9]<<endl;//0
	cout<<(int)out[10]<<endl;//-1
	cout<<(int)out[11]<<endl;//-1
	//由上面可知返回数目不包括'\0'但是也在最后写入一个空字符,不用手动输入了。
	
	return 0;
}
