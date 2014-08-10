#include <stdio.h>
#include "unixsocket.h"

int main(int argc, char *argv[])
{
    int socket_fd4 = -1;
    char req[] = "hello, from client2";
	char resp[64];
    UnixDomainInit();
    socket_fd4 = UnixDomainCreate(Id4, SIZE_1K);
    UnixDomainSend(socket_fd4, Id2, req, sizeof(req), 1000);
	UnixDomainRecv(socket_fd4, resp, sizeof(resp), 1000);
	printf("In client2, received response '%s' from server.\n", resp);
    return 0;
}
