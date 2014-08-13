/*程序功能：给定一个wchar_t类型的字符，把它转换成为char并且显示出来
 *
 * 核心函数：
 * #include <stdlib.h>
 * int wctomb(char *s, wchar_t wc);
 * 把wc转换为字符串的表示，存放在s中，并返回写入s的个数。
 * 注意要保证s有空间！
 *
 * */
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

//将宽字符转换成窄字符
//参数：一个宽字符wchar_t变量作为输入，一个至少三个元素的char数组作为输出

int main(int argc, char *argv[])
{
	//////初始化
	setlocale(LC_ALL,"");//没有这句话后面的全部显示不正常
	wchar_t w_cn = L'中';
	//wchar_t w_cn = '中';//这样不行
	char c_cn[5] = {'\0',};//至少4个,不过为了保险,虽然显示写了3个但是不要忘记串结束标记
	c_cn[3] = c_cn[4] = -1;//假设没有字符串结束标记
	
	//////测试一下各个类型的大小
	cout<<"size of the wchar_t:"<<sizeof(wchar_t)<<endl;//4
	cout<<"size of the char:"<<sizeof(char)<<endl;//1
	cout<<"size of unsigned short:"<<sizeof(unsigned short)<<endl;//2
	
	//////!!!!!!!将wchar_t的w_cn转换为char的c_cn，关键!!!!!!
	//这里不会自动将最后的结束标记'\0'写入，所以需要自己手动写。
	int cnt = wctomb(c_cn, w_cn);
	c_cn[cnt] = '\0';//字符传结束标记


	//////打印结果
	cout<<c_cn<<endl;//成功打印!!
	printf("%s\n",c_cn);//成功打印!!
	//printf("%C\n",c_cn);//不行
	cout<<"the bytes write to cnt is:"<<cnt<<endl;

	return 0;
}
