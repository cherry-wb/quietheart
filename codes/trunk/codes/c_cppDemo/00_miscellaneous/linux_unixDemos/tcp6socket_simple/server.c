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

static void InitTcpSocket(const char *ip, int port);
static int DoServe(int *sock, int sockCount);

int socketFds[2] = {-1, -1}; /*0 for ipv4, 1 for ipv6*/
int main(int argc, char *argv[])
{
    int ret = 0;
    int i;

    if (argc != 1)
    {
        fprintf(stderr, "Usage:%s\n", argv[0]);
        return -1;
    }

    InitTcpSocket(NULL, TCP_SERV_PORT);

    /*server loop*/
    ret = DoServe(socketFds, 2);

    if (ret < 0)
    {
        for (i = 0; i < 2; ++i)
        {
            close(socketFds[i]);
            socketFds[i] = -1;
        }
    }
    return ret;
}

static void InitTcpSocket(const char *ip, int port)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    char portStr[16] = {0};
    int *sockfd = NULL;
    int err;
    int qlen=10;

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
            fprintf(stderr, "[serv dbg] ipv4.\n");
            char addrP[32] = {0};/*a.b.c.d*/
            inet_ntop(AF_INET, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr, addrP, 32);
            fprintf(stderr, "[serv dbg] get aip->ai_addr->sin_addr char:%s.\n", addrP);
            fprintf(stderr, "[serv dbg] get aip->ai_addr->sin_port:%d.\n", ntohs(((struct sockaddr_in*)(aip->ai_addr))->sin_port));

            sockfd = &socketFds[0];
            inet_pton(AF_INET, TCP_SERV_IPV4, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr);

            inet_ntop(AF_INET, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr, addrP, 32);
            fprintf(stderr, "[serv dbg] bind aip->ai_addr->sin_addr char:%s.\n", addrP);
            fprintf(stderr, "[serv dbg] bind aip->ai_addr->sin_port:%d.\n", ntohs(((struct sockaddr_in*)(aip->ai_addr))->sin_port));
        }
        else if (AF_INET6 == aip->ai_family)
        {
            fprintf(stderr, "[serv dbg] ipv6.\n");
            char addrP[64] = {0};/*xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx*/
            inet_ntop(AF_INET6, (void*)&((struct sockaddr_in6*)(aip->ai_addr))->sin6_addr, addrP, 64);
            fprintf(stderr, "[serv dbg] get aip->ai_addr->sin6_addr char:%s.\n", addrP);
            fprintf(stderr, "[serv dbg] get aip->ai_addr->sin6_port:%d.\n", ntohs(((struct sockaddr_in6*)(aip->ai_addr))->sin6_port));

            sockfd = &socketFds[1];
            inet_pton(AF_INET6, TCP_SERV_IPV6, (void*)&((struct sockaddr_in6*)(aip->ai_addr))->sin6_addr);

            fprintf(stderr, "[serv dbg] bind aip->ai_addr->sin6_addr char:%s.\n", addrP);
            fprintf(stderr, "[serv dbg] bind aip->ai_addr->sin6_port:%d.\n", ntohs(((struct sockaddr_in6*)(aip->ai_addr))->sin6_port));
        }
        else
        {
            fprintf(stderr, "[serv dbg] unknown family:%d.\n", aip->ai_family);
        }

        if (-1 == *sockfd)
        {
            if ((*sockfd = socket(aip->ai_addr->sa_family, SOCK_STREAM, 0)) < 0)
            {
                fprintf(stderr, "Error, socket.\n");
                continue;
            }

            if (bind(*sockfd, aip->ai_addr, aip->ai_addrlen) < 0)
            {
                fprintf(stderr, "Error, bind.\n");
                close(*sockfd);
                *sockfd = -1;
                continue;
            }
            if (listen(*sockfd, qlen) < 0) 
            {
                fprintf(stderr, "Error, listen.\n");
                close(*sockfd);
                *sockfd = -1;
                continue;
            }
        }
        else
        {/*XXX already has sockfd?*/
            ;
        }
    }
}

static int DoServe(int *sock, int sockCount)
{
    int     clfd;
    fd_set fds;
    FILE    *fp;
    TcpData snd;
    TcpData rcv;

    for (;;)
    {
        fprintf(stderr, "[serv dbg] server loop %d.\n", __LINE__);
        struct timeval timeout={2,0};
        int selectRet;
        int i;
        int maxFd = -1;
        FD_ZERO(&fds);
        for (i = 0; i < sockCount; ++i)
        {
            fprintf(stderr, "[serv dbg] loop: %d, set fd:%d.\n", __LINE__, sock[i]);
            sock[i] > maxFd?maxFd = sock[i]:maxFd;
            FD_SET(sock[i],&fds);
        }

        selectRet = select(maxFd+1,&fds,NULL,NULL,&timeout);
        fprintf(stderr, "[serv dbg] server loop %d, ret:%d.\n", __LINE__, selectRet);

        for (i = 0; i < sockCount; ++i)
        {
            if(selectRet > 0 && FD_ISSET(sock[i], &fds))
            {
                clfd = accept(sock[i], NULL, NULL);
                fprintf(stderr, "[serv dbg] count:%d\n", sockCount);
                if (clfd < 0)
                {
                    fprintf(stderr, "Error, accept.\n");
                    continue;
                }
                if (recv(clfd, &rcv, sizeof(TcpData), MSG_WAITALL) <= 0)
                {/*Note:the length must be the same as client send or it will not return.*/
                    fprintf(stderr, "Error, receivefrom.\n");
                    continue;
                }

                fprintf(stderr, "received from client:%s\n", rcv.msg);
                sprintf(snd.msg, "server response.");
                send(clfd, &snd, sizeof(TcpData), 0);
                close(clfd);
            }
        }
        fprintf(stderr, "[serv dbg] server loop %d.\n", __LINE__);
    }
    return -1;
}
