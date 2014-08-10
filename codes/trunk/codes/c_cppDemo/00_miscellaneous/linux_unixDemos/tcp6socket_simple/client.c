#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <net/if.h>

#include "common.h"

static int InitTcpSocket(const char *ip, int port);
static int DoRequest(int sockfd, char *request);

int main(int argc, char *argv[])
{
    int ret = 0;
    int sockfd = -1;
    
    if (argc != 3)
    {
        fprintf(stderr, "Usage:%s <serverip> <requeststr>\n", argv[0]);
        return -1;
    }

    sockfd = InitTcpSocket(argv[1], TCP_SERV_PORT);
    if (sockfd != -1)
    {
        ret = DoRequest(sockfd, argv[2]);
    }

    if (sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    return ret;
}


static int InitTcpSocket(const char *ip, int port)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    char portStr[16] = {0};
    int             sockfd, err;

    hint.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    sprintf(portStr, "%d", port);

    if ((err = getaddrinfo(ip, portStr, &hint, &ailist)) != 0)
    {
        fprintf(stderr, "Error, getaddrinfo error: %s", gai_strerror(err));
        exit(1);
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next)
    {
        if (AF_INET == aip->ai_family)
        {
            fprintf(stderr, "[cli dbg] ipv4.\n");
            char addrP[32] = {0};/*a.b.c.d*/
            inet_ntop(AF_INET, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr, addrP, 32);
            fprintf(stderr, "[cli dbg] aip->ai_addr->sin_addr char:%s.\n", addrP);
            fprintf(stderr, "[cli dbg] aip->ai_addr->sin_port:%d.\n", ntohs(((struct sockaddr_in*)(aip->ai_addr))->sin_port));
        }
        else if (AF_INET6 == aip->ai_family)
        {
            fprintf(stderr, "[cli dbg] ipv6.\n");
            char addrP[64] = {0};/*xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx*/
            inet_ntop(AF_INET6, (void*)&((struct sockaddr_in6*)(aip->ai_addr))->sin6_addr, addrP, 64);
            fprintf(stderr, "[cli dbg] aip->ai_addr->sin6_addr char:%s.\n", addrP);
            fprintf(stderr, "[cli dbg] aip->ai_addr->sin6_port:%d.\n", ntohs(((struct sockaddr_in6*)(aip->ai_addr))->sin6_port));
        }
        else
        {
            fprintf(stderr, "[cli dbg] unknown family:%d.\n", aip->ai_family);
            continue;
        }

        /*socket*/
        if ((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
        {
            fprintf(stderr, "Error, socket.\n");
            continue;
        }

        if (connect(sockfd, aip->ai_addr, aip->ai_addrlen) < 0)
        {
            perror("\n");
            fprintf(stderr, "Error, connect.\n");
            close(sockfd);
            sockfd = -1;
            continue;
        }
        break;
    }
    return sockfd;
}


static int DoRequest(int sockfd, char *request)
{
    int     n;
    TcpData snd;
    TcpData rcv;

    sprintf(snd.msg, "%s\n", request);
    send(sockfd, &snd, sizeof(TcpData), 0);

    fprintf(stderr, "[cli dbg] \n");
    while ((n = recv(sockfd, &rcv, sizeof(TcpData), 0)) > 0)
    {
        fprintf(stderr, "client receive response from server:%s\n", rcv.msg);
    }
    if (n < 0)
    {
        fprintf(stderr, "Error recv.\n");
        exit(-1);
    }
}
