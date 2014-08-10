/*
1.简介
Linux日志记录由系统日志监控程序和内核日志监控程序组成。
两者都是系统服务守护进程，可通过/etc/init.d找到对应程序，通过service启动关闭和重启。

2.配置
/etc/syslog.conf文件（其他系统有类似的文件,如ubuntu下为/etc/rsyslog.conf）保存日志配置信息。
配置文件的每行语法如下：
[消息类型(规则)]    [处理方案（日志文件）]
两列用一个或多个[TAB]分隔，消息类型格式是“消息来源（facility）.紧急程度(priority)”，其中facility和priority可以用*来通配。
例子：
假设添加如下一行：
cron.err    /var/log/cron
表示：来自cron的级别为err的内容，存放到/var/log/cron文件中。

3.函数
而日志的消息来源（facility）和紧急程度(priority)，是在程序中，登记日志信息的相应接口指定的。如下：
void openlog(const char *ident, int option, int facility);
void syslog(int priority, const char *format, ...);
void closelog(void);
其中openlog和closelog都是可选的。不过，通过调用openlog，我们可以指定ident参数。这样，ident将被加到每条日记记录中。ident一般设成程序的名字。
理解的关键是：openlog函数中的option，facility和syslog函数中的priority参数。具体参见/usr/include/sys/syslog.h文件，大致如下：
syslog支持的option:
#define LOG_PID     0x01    //为每个消息添加进程ID。
#define LOG_CONS            //0x02   如果有error，则打印至控制台。
#define LOG_ODELAY  0x04    //延迟打开日志工具，至syslog()的调用（默认）
#define LOG_NDELAY  0x08    //不延迟打开。
#define LOG_NOWAIT  0x10    //不等待控制台的fork(过时了)。
#define LOG_PERROR  0x20    //同时日志打印到stderr。

syslog支持的faclility：
#define LOG_KERN            (0<<3)    //内核
#define LOG_USER            (1<<3)    
#define LOG_MAIL            (2<<3)    
#define LOG_DAEMON  (3<<3)    
#define LOG_AUTH            (4<<3)    
#define LOG_SYSLOG  (5<<3)    //syslogd产生的消息
#define LOG_LPR     (6<<3)   
#define LOG_NEWS            (7<<3)   
#define LOG_UUCP            (8<<3)  
#define LOG_CRON            (9<<3) 
#define LOG_AUTHPRIV    (10<<3)   
#define LOG_FTP     (11<<3) 
facility的ID（上面对应的数值）与syslog.conf中"消息来源"名字的对应关系如下：
{ "auth", LOG_AUTH },   
{ "authpriv", LOG_AUTHPRIV },   
{ "cron", LOG_CRON },   
{ "daemon", LOG_DAEMON },   
{ "ftp", LOG_FTP },   
{ "kern", LOG_KERN },   
{ "lpr", LOG_LPR },   
{ "mail", LOG_MAIL },   
{ "mark", INTERNAL_MARK },//内部用
{ "news", LOG_NEWS },   
{ "security", LOG_AUTH },//过时了
{ "syslog", LOG_SYSLOG },   
{ "user", LOG_USER },   
{ "uucp", LOG_UUCP },

syslog支持的priority：
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7
priority的ID（上面对应的数值）与名字的对应关系如下：
{ "alert", LOG_ALERT },   
{ "crit", LOG_CRIT },   
{ "debug", LOG_DEBUG },   
{ "emerg", LOG_EMERG },   
{ "err", LOG_ERR },   
{ "error", LOG_ERR },//过时
{ "info", LOG_INFO },   
{ "none", INTERNAL_NOPRI },//内部用
{ "notice", LOG_NOTICE },   
{ "panic", LOG_EMERG },//过时
{ "warn", LOG_WARNING },//过时
{ "warning", LOG_WARNING },  
日志级别由大到小升高。匹配syslog.conf时，会匹配更高的级别。如规则"*.info    /var/log/messages"，将info级以上（notice,warning, err, alert, emerg）（priority表）的所有消息发送到日记文件/var/log/messages。

4.例子
(1)syslog.conf文件添加一行：
user.debug                  /var/log/mydebug

(2)重启syslogd和klogd：
service syslog restart(ubuntu下为/etc/init.d/rsyslog restart)

(3)如下面例子中的代码
这样，将会在/var/log/mydebug中,产生一条格式是"timestamp hostname ident[pid]：log message"的日志,类似如下：
Jul 23 13:37:26 quietheart-ThinkPad-E420 testsyslog[3980]: syslog test message generated in program ./a.out

5.参考：
http://www.cnblogs.com/wangkangluo1/archive/2012/05/30/2526011.html
man手册。

*/
#include <syslog.h>   

int main(int argc, char *argv[])   
{   
    openlog("testsyslog", LOG_CONS | LOG_PID, 0);   
    syslog(LOG_USER | LOG_DEBUG, "syslog test message generated in program %s \n", argv[0]);   
    closelog();   
    return 0;   
}
