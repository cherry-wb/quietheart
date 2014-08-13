/*程序功能:一个编码转换的程序
 * 例如：'人'的编码分别是：
 * 机内码：C8CB
 * 区位码：4043
 * 国标码：484B
 * Unicode码：4EBA
 * */
#include <iostream>
#include <iconv.h>
//#include <cwctype>
//#include <wchar.h>
//#include <stdio.h>
using std::cout;
using std::wcout;
using std::endl;

//编码转换函数
//int ConvertEnc( const char *lpszFrom, const char *lpszTo, const char* lpszSrc, int nSrcLen, char* lpszDest, int* lpnDestLen);
int ConvertEnc( const char *lpszFrom, const char *lpszTo, const char* lpszSrc, int nSrcLen, char* lpszDest, int* lpnDestLen);

int main(int argc, char *argv[])
{
	/*
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
*/	
	//////编码转换
	char *from = "GBK";
	char *to = "UTF-8";

	char in[10] = "484B";
	char out[10];
	
	int inLen = 10;
	int outLen = 10;
	ConvertEnc(from, to, in, inLen, out, &outLen);
	cout<<out<<endl;
	return 0;
}

int ConvertEnc( const char *lpszFrom, const char *lpszTo, const char* lpszSrc, int nSrcLen, char* lpszDest, int* lpnDestLen)
{
	iconv_t cv;

	if ((cv = iconv_open(lpszTo, lpszFrom)) == (iconv_t)-1)
	{
		return -1;
	}
	iconv(cv, NULL, NULL, NULL, NULL);

	char* lpszSrc1 = (char*)lpszSrc;
	int ret = iconv(cv, &lpszSrc1, (size_t *)&nSrcLen, &lpszDest, (size_t *)lpnDestLen);
	if (ret == -1)
	{
		iconv_close(cv);
		return -1;
	}
	iconv_close(cv);

	return 0;
}

