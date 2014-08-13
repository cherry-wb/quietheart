/*程序功能：测试使用正常的char类型数据来存储和显示多字节字符的程序
 * 这里wchar_t*向char*的转换成功了。
 * */

#include <iostream>
using std::cout;
using std::endl;
using std::wstring;
int main(int argc, char *argv[])
{
	char first[] = "你好";
	//char first[] = "good";
	//char *first = "你好";//这种方法被摒弃了,最好不要使用
	cout<<first<<endl;//显示正常
	printf("%s\n", first);//显示正常

	setlocale(LC_ALL,"");//没有这句话后面的全部不能显示
	printf("%S\n",first);//无法打印
	cout<<"ok! The length of the first array is:"<<sizeof(first)<<endl;//the length is 5
	//以上结论：直接用多字节常量初始化char*就按照平常对待即可。

	wchar_t tmp[] = L"你好吗";
	char second[20];
	sprintf(second, "%S", tmp);
	cout<<second<<endl;//可以打印
	printf("%S\n",tmp);//可以打印
	printf("%s\n",second);//可以打印
	printf("%S\n",second);//无法打印
	printf(second);//可以打印
	printf("\n");

	wstring str = L"我";
	cout<<str.c_str()<<endl;//只打印了一串0x93c61ec等不固定的数字
	printf("%S\n", str.c_str());//可以显示
	//以上结论：多字节字符串变量使用c标准函数将%s替换为%S，如果转换后为char*则仍旧用%s。
	//即，类型只要是char*就用%s，是wchar_t*就用%S.

	wchar_t tmp2 = L'你';
	char third[20] = {0,};
	sprintf(third, "%C", tmp);
	//printf("%S\n", tmp2);//无法打印,并且程序报错退出了
	printf("%C\n", tmp2);//可以打印
	printf("%c\n", tmp2);//显示乱码
	printf("%C\n", third);//无法打印
	printf("%c\n", third);//只显示一个无法预料的字符每次运行显示不同的结果
	printf("%s\n", third);//无法打印
	printf("%S\n", third);//无法打印
	//以上结论：wchar_t字符在标准c函数中用%C
	//问题：如何将wchar字符转换为char*表示的？

	cout<<"over!"<<endl;

	return 0;
}
