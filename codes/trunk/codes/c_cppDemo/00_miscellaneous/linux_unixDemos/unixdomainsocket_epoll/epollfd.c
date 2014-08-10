#include <stdio.h>
#include <errno.h>
#include <sys/epoll.h>
#include "epollfd.h"
#include "unixsocket.h"

void EPollFd(int socket_fd1, char *buf1, int size1, int socket_fd2, char *buf2, int size2)
{
    int n;
    int ret;
    int nfds;
    int epollFd;
    struct epoll_event ev, events[2];
	char respMsg1[] = "Response message1 from server.";
	char respMsg2[] = "Response message2 from server.";

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
                UnixDomainRecv(socket_fd1, buf1, size1, 1000);
                printf("In server, received msg '%s' from client1\n", buf1);
				UnixDomainSend(socket_fd1, Id3, respMsg1, sizeof(respMsg1), 1000);
            }

            if (events[n].data.fd == socket_fd2)
            {
                UnixDomainRecv(socket_fd2, buf2, size2, 1000);
                printf("In server, received msg '%s' from client2\n", buf2);
				UnixDomainSend(socket_fd2, Id4, respMsg2, sizeof(respMsg2), 1000);
            }
        }
    }
}
