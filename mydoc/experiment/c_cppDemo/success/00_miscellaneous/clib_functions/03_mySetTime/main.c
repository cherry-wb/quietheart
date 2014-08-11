/*程序功能：获得当前的系统时间并且设置为新的时间
这个程序需要在你的超级用户下面运行，不要轻易尝试
struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};
tm_sec表「秒」数，在[0,61]之间，多出来的两秒是用来处理跳秒问题用的。
tm_min表「分」数，在[0,59]之间。
tm_hour表「时」数，在[0,23]之间。
tm_mday表「本月第几日」，在[1,31]之间。
tm_mon表「本年第几月」，在[0,11]之间。
tm_year要加1900表示那一年。
tm_wday表「本周第几日」，在[0,6]之间。
tm_yday表「本年第几日」，在[0,365]之间，闰年有366日。
tm_isdst表是否为「日光节约时间」。 

*获得当前时间，传回从epoch开始计算起的秒数，如果t是non-null，它将会把时间值填入t中。 
gettimeofday更精确
time_t time(time_t *t); 

1,转成struct tm格式时间函数
1)转换成格林威治时间,有时称为GMT或UTC
struct tm * gmtime(const time_t * t);

2)转换成本地时间
struct tm * localtime(const time_t *t); 

2,转换tm成为time_t格式
1)使用本地时间。
time_t mktime(struct tm *tp);

2)使用UTC时间。 
tme_t timegm(strut tm *tp);

3,其他常用函数：
计算秒差:
double difftime(time_t t2,time_t t1);

以字符串打印时间：
char * asctime(struct tm *tp);

类似sprintf，其格式由fmt来指定:
size_t strftime(char *str,size_t max,char *fmt,struct tm *tp); 

类似scanf一样，解译字串成为tm格式
char * strptime(char *s,char *fmt,struct tm *tp); 

设置时间
int stime(time_t *t);
*/

#include <stdio.h>

//exit
#include <stdlib.h>
//gettimeofday,
//#include <sys/time.h>

//time_t,struct tm, asctime
#include <time.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("usage:%s yy-mm-dd-hh:MM\n", argv[0]);
		printf("for example: %s 2002-09-08-22:02\n", argv[0]);
		printf("the param num is:%d\n", argc);
		printf("the expected num is:%d\n", 2);
		exit(1);
	}
	time_t now;
	struct tm *new;
	int accept = 0;//是否接受新的修改

	//time函数读取现在的时间(国际标准时间非北京时间)，然后传值给now
	time(&now);

	//localtime函数把从time取得的时间now换算成你电脑中的时间(就是你设置的地区)
	new = localtime(&now);

	printf("old time is %s\n",asctime(new));//提示旧时间，防止轻易系统修改时间

	//输入时间
	strptime(argv[1],"%Y-%m-%d-%H:%M",new);//for example,argv[1] is:"2002-09-08-22:02"

	
	//打印新的设置
	//这里年是距1900的年数，所以如果真正打印需要加1900.
	//月份从0开始算，所以打印的时候加1
	printf("new time year: %d\n month :%d\n, date:%d\n, hour:%d\n, minute:%d\n",
			new->tm_year+1900, new->tm_mon+1, new->tm_mday, new->tm_hour, new->tm_min);
	printf("new time to be set is %s\n",asctime(new));
	printf("NOTE:Press \'1\' to accept, \'0\' or else to abort change\n");
	scanf("%d",&accept);

	if(accept == 1)
	{
		//设置时间
		time_t tmp = mktime(new);
		stime(&tmp);
		printf("accepted.\n");
	}
	else
	{
		printf("abort.\n");
		exit(0);
	}
	return 0;
}
