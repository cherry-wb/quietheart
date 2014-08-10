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

static int InitTcpSocket(const char *ip, const char *service);
static int DoServe(int sockfd);

int main(int argc, char *argv[])
{
    int ret = 0;
    int sockfd;

    if (argc != 1)
    {
        fprintf(stderr, "Usage:%s\n", argv[0]);
        return -1;
    }

    sockfd = InitTcpSocket("192.168.1.112", "mytest");

    if (sockfd != -1)
    {
        /*server loop*/
        ret = DoServe(sockfd);
    }

    if (ret < 0)
    {
        close(sockfd);
    }
    return ret;
}

static int InitTcpSocket(const char *ip, const char *service)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;
    int qlen=10;

    hint.ai_flags = AI_NUMERICHOST;/*numeric host name.*/
    //hint.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV ;/*numeric host name and service name.*/
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(ip, service, &hint, &ailist)) != 0)/*here we should have service name regist in /etc/services.*/
    //if ((err = getaddrinfo(ip, "10010", &hint, &ailist)) != 0)/*numeric port is service name with AI_NUMERICSERV*/
    {
        fprintf(stderr, "Error, getaddrinfo error: %s", gai_strerror(err));
        exit(1);
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next)
    {
#if 1
        char addrP[32] = {0};
        fprintf(stderr, "[serv dbg] AF_INET:%d.\n", AF_INET);
        fprintf(stderr, "[serv dbg] aip->ai_family:%d.\n", aip->ai_family);
        fprintf(stderr, "[serv dbg] aip->ai_protocol:%d.\n", aip->ai_protocol);
        fprintf(stderr, "[serv dbg] aip->ai_addr->sa_family:%d.\n", aip->ai_addr->sa_family);
        inet_ntop(AF_INET, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr, addrP, 32);
        fprintf(stderr, "[serv dbg] aip->ai_addr->sin_addr char:%s.\n", addrP);
        fprintf(stderr, "[serv dbg] aip->ai_addr->sin_port:%d.\n", ntohs(((struct sockaddr_in*)(aip->ai_addr))->sin_port));
#endif

        sockfd = -1;
        if ((sockfd = socket(aip->ai_addr->sa_family, SOCK_STREAM, 0)) < 0)
        {
            fprintf(stderr, "Error, socket.\n");
            continue;
        }

        ((struct sockaddr_in*)(aip->ai_addr))->sin_addr.s_addr = INADDR_ANY;//表示127.0.0.1以及合法的本地ip都可
        //((struct sockaddr_in*)(aip->ai_addr))->sin_port = htons(10010);//htons(0)表示一个临时的端口，如getaddrinfo中service为NULL在这设
        if (bind(sockfd, aip->ai_addr, aip->ai_addrlen) < 0)
        {
            fprintf(stderr, "Error, bind.\n");
            close(sockfd);
            sockfd = -1;
            continue;
        }
        if (listen(sockfd, qlen) < 0) 
        {
            fprintf(stderr, "Error, listen.\n");
            close(sockfd);
            sockfd = -1;
            continue;
        }
        break;
    }
    return sockfd;
}

static int DoServe(int sockfd)
{
    int     clfd;
    FILE    *fp;
    TcpData snd;
    TcpData rcv;

    for (;;)
    {
        clfd = accept(sockfd, NULL, NULL);
        fprintf(stderr, "[serv dbg] \n");
        if (clfd < 0)
        {
            fprintf(stderr, "Error, accept.\n");
            return -1;
        }
        if (recv(clfd, &rcv, sizeof(TcpData), MSG_WAITALL) <= 0)
        {/*Note:the length must be the same as client send or it will not return.*/
            fprintf(stderr, "Error, receivefrom.\n");
            return -1;
        }
        
        fprintf(stderr, "received from client:%s\n", rcv.msg);
        sprintf(snd.msg, "server response.");
        send(clfd, &snd, sizeof(TcpData), 0);
        close(clfd);
    }
    return -1;
}
