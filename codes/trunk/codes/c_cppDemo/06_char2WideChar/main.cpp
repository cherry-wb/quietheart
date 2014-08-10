/* 程序功能：将字节char*表示的多字节字符转换为一个多字节字符wchar_t
 * #include <stdlib.h>
 * int mbtowc(wchar_t *pwc, const char *s, size_t n);
 * 将s中至多n个字节的字符转换成wchar_t的,返回s中被转换的数目。
 * */
#include <iostream>
//using std::cout;
using std::endl;
using std::wcout;
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");//必须有这个
	wchar_t src1 = L'好';
	char src2[4] = {'\0',};
	wchar_t dest;
	
	//先获得char*表示的wchar_t类型字符
	wctomb(src2, src1);//src2里面是wchar_t类型字符

	//////将char*表示的wchar_t类型字符转换成wchar_t字符
	//此函数不是多线程的,不如mbrtowc好但是mbrtowc多了一个参数
	mbtowc(&dest,src2,sizeof(src2));

	wcout<<dest<<endl;//打印成功
	//printf("%C\n",dest);//没有打印出来,但是注释掉wcout打印的话就可以打印了。
	return 0;
}
