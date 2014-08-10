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

    sockfd = InitTcpSocket(argv[1], "mytest");
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


static int InitTcpSocket(const char *ip, const char *service)
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int             sockfd, err;

    /*get address info*/
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
        /*print address*/
        char addrP[32] = {0};
        fprintf(stderr, "[cli dbg] AF_INET:%d.\n", AF_INET);
        fprintf(stderr, "[cli dbg] aip->ai_family:%d.\n", aip->ai_family);
        fprintf(stderr, "[cli dbg] aip->ai_protocol:%d.\n", aip->ai_protocol);
        fprintf(stderr, "[cli dbg] aip->ai_addr->sa_family:%d.\n", aip->ai_addr->sa_family);
        inet_ntop(AF_INET, (void*)&((struct sockaddr_in*)(aip->ai_addr))->sin_addr, addrP, 32);
        fprintf(stderr, "[cli dbg] aip->ai_addr->sin_addr char:%s.\n", addrP);/*ip address a.b.c.d*/
        fprintf(stderr, "[serv dbg] aip->ai_addr->sin_port:%d.\n", ntohs(((struct sockaddr_in*)(aip->ai_addr))->sin_port));/*port*/
#endif

        /*socket*/
        if ((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
        {
            fprintf(stderr, "Error, socket.\n");
            continue;
        }

        //((struct sockaddr_in*)(aip->ai_addr))->sin_port = htons(10010);//htons(0)表示一个临时的端口，如getaddrinfo中service为NULL在这设
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
