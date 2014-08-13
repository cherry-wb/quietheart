/*将定时器设置为一个fd，超时则可读，这样可将定时器用于select等轮询。如果阻塞方式，那么read将阻塞直至定时器超时。*/
/*
CLOCK_REALTIME:受系统时间改变影响，修改系统时间，则超时也会相应受到影响。
CLOCK_MONOTONIC:不受系统时间改变的影响，只表示从过去到超时的绝对时间，及时改变系统时间，也不会影响它。
*/
#include <sys/timerfd.h>
int main(int argc, char *argv[])
{
    struct itimerspec it;
    int fd = -1;
    int ret = 0;

    fd = timerfd_create(CLOCK_MONOTONIC,0);
    if (0 > fd)
    {
        return -1;
    }


    it.it_interval.tv_sec = intervalMs/1000;
    it.it_interval.tv_nsec = (intervalMs%1000) * 1000000;
    it.it_value = it.it_interval;
    ret = timerfd_settime(fd, 0, &it, NULL);
    if (0 != ret)
    {
        close(fd);
        return -1;
    }
    return fd;
}
