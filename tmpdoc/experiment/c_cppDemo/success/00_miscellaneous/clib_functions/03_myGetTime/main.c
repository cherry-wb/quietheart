/*程序功能：获得当前的系统时间并打印出来
注释：time_t是一个在time.h中定义好的结构体。而tm结构体的原形如下：
struct tm
{
	int tm_sec;//seconds 0-61
	int tm_min;//minutes 1-59
	int tm_hour;//hours 0-23
	int tm_mday;//day of the month 1-31
	int tm_mon;//months since jan 0-11
	int tm_year;//years from 1900
	int tm_wday;//days since Sunday, 0-6
	int tm_yday;//days since Jan 1, 0-365
	int tm_isdst;//Daylight Saving time indicator
};
这里包含了两种方法把时间转换为字符串的格式：
ctime用于time_t*
asctime用于struct tm*
*/
#include <stdio.h>

//time_t,struct tm, asctime
#include <time.h>

int main(int argc, char *argv[])
{
	time_t now;
	struct tm *today;

	//time函数读取现在的时间(国际标准时间非北京时间)，然后传值给now
	//time的返回值也是这个值，不过是time_t
	time(&now);
	//这种方法也行
	//now = time(NULL);

	//把time_t时间转换成字符，通过printf()函数输出
	printf("Local time is %s\n",ctime(&now));
	
	//localtime函数把从time取得的时间now换算成你电脑中的时间(就是你设置的地区)
	today = localtime(&now);

	//上句中asctime函数把tm时间转换成字符，通过printf()函数输出
	printf("Local time is %s\n",asctime(today));
	return 0;
}
