/*
Poll(wait) for available data , use epoll.
Receive data from clients by unix socket.
*/
#include "unixsocket.h"
#include "epollfd.h"

static char buf1[SIZE_1K] = {0};
static char buf2[SIZE_1K] = {0};

int main(int argc, char *argv[])
{
    int socket_fd1 = -1;
    int socket_fd2 = -1;
	int size1 = sizeof(buf1);
	int size2 = sizeof(buf2);

    UnixDomainInit();

    socket_fd1 = UnixDomainCreate(Id1, SIZE_1K);
    socket_fd2 = UnixDomainCreate(Id2, SIZE_1K);

    /*loop*/
    EPollFd(socket_fd1, buf1, size1, socket_fd2, buf2, size2);

    return 0;
}
