/*程序功能：给定一个wchar_t类型的字符，把它转换成为char并且显示出来
 * */
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::wstring;

//将宽字符转换成窄字符
//参数：一个宽字符wchar_t变量作为输入，一个至少三个元素的char数组作为输出
void w2c(const wchar_t &w_cn, char *c_cn);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");//没有这句话后面的全部显示不正常
	//wchar_t w_cn = L'中';
	wchar_t w_cn = '中';
	//char c_cn[3] = {'\0',};
	char c_cn[5] = {'\0',};
	
	cout<<"size of the wchar_t:"<<sizeof(wchar_t)<<endl;//4
	cout<<"size of the char:"<<sizeof(char)<<endl;//1
	cout<<"size of unsigned short:"<<sizeof(unsigned short)<<endl;//2
	//将wchar_t的w_cn转换为char的c_cn
	w2c(w_cn, c_cn);
	cout<<c_cn<<endl;//无法显示

	string str(c_cn);
	cout<<str<<endl;//无法显示

	cout<<"======================="<<endl;
	wstring s = L"人";
	cout<<s.c_str()<<endl;//打印一串数字
	printf("%S\n",s.c_str());//可以打印

	//wstring s2 = L'人';//初始化失败
	//printf("%S\n", s.c_str());
	return 0;
}

void w2c(const wchar_t &w_cn, char *c_cn)
{
	//c_cn[0] = w_cn>>8;//将w_cn高8位赋值给c_cn[0]
	//c_cn[1] = w_cn;//将w_cn低8位赋值给c_cn[0]
	//c_cn[2] = '\0';
	//4321
	c_cn[0] = w_cn>>24;//4
	c_cn[1] = w_cn>>16;//3
	c_cn[2] = w_cn>>8;//2
	c_cn[3] = w_cn;//1
	c_cn[4] = '\0';
}
