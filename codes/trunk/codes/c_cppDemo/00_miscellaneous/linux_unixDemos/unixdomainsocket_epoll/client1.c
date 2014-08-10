#include <stdio.h>
#include "unixsocket.h"

int main(int argc, char *argv[])
{
    int socket_fd3 = -1;
    char req[] = "hello, from client1";
	char resp[64];
    UnixDomainInit();
    socket_fd3 = UnixDomainCreate(Id3, SIZE_1K);
    UnixDomainSend(socket_fd3, Id1, req, sizeof(req), 1000);
	UnixDomainRecv(socket_fd3, resp, sizeof(resp), 1000);
	printf("In client1, received response '%s' from server.\n", resp);
    return 0;
}
