#include <sys/epoll.h>

int main(int argc, char *argv[])
{
    int socket_fd1;
    int socket_fd2;
    int ret;
    int nfds;
    int epollFd;
    struct epoll_event ev, events[2];

    /*返回一个epoll文件描述符号。参数目前不用了，以前用于指示内核如何确定内部结构大小，而非最大存储。*/
    epollFd = epoll_create(2);

    /*对epollFd符号，添加两个事件，它们分别是对文件描述符号socket_fd1,socket_fd2的EPOLLIN事件（即可读）监视。*/
    ev.events = EPOLLIN;
    ev.data.fd = socket_fd1;
    ret = epoll_ctl(epollFd, EPOLL_CTL_ADD, socket_fd1, &ev);

    ev.events = EPOLLIN;
    ev.data.fd = socket_fd2;
    ret = epoll_ctl(epollFd, EPOLL_CTL_ADD, socket_fd2, &ev);

    while (1)
    {
        /*等待epollFd上发生的事件，并返回events供用户处理。2指定最大返回的事件，-1指定等待时间无限。*/
        /*返回准备好的文件描述符号数目。*/
        nfds = epoll_wait(epollFd, events, 2, -1);
        if (0 > nfds)
        {
            if (EINTR == errno)
            {
                continue;
            }
        }

        for (n = 0; n < nfds; n++)
        {
            if (events[n].data.fd == socket_fd1)
            {
                read(socket_fd1);
            }

            if (events[n].data.fd == socket_fd2)
            {
                read(socket_fd2);
            }
        }
    }
    return 0;
}
