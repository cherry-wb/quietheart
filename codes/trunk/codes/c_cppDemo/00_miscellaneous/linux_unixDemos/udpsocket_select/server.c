#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <net/if.h>

#include "common.h"

static int InitUdpSocket();
static int DoServe(int sockfd);

int main(int argc, char *argv[])
{
    int ret = 0;
    int sockfd = InitUdpSocket();
    if (sockfd != -1)
    {
        /*server loop*/
        ret = DoServe(sockfd);
    }

    if (sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    return ret;
}

static int InitUdpSocket()
{
    int sockfd = -1;
    struct sockaddr_in localAddr   = { 0 };
    int                isEnable    = 1;
    int flags = 0;

    localAddr.sin_family            = AF_INET;
#if 1
    localAddr.sin_port              = htons(UDP_RECV_PORT);
#else
    /*should we get port in /etc/services?*/
#endif
    localAddr.sin_addr.s_addr       = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sockfd == -1 )
    {
        fprintf(stderr, "Error when create socket with socket.\n");
        goto DEV_FOUND_END;
    }

    flags = fcntl(sockfd,  F_GETFL, 0);
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        fprintf(stderr, "Error when set nonblock flag with fcntl.\n");
        goto DEV_FOUND_END;
    }

    /*?????*/
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&isEnable, sizeof(int)) < 0)
    {
        fprintf(stderr, "Error when set SO_REUSEADDR option with setsockopt.\n");
        goto DEV_FOUND_END;
    }

    if (bind(sockfd, (struct sockaddr *)&localAddr, sizeof(struct sockaddr_in)) == -1 )
    {
        fprintf(stderr, "Error when bind socket with bind.\n");
        goto DEV_FOUND_END;
    }

    return sockfd;

DEV_FOUND_END:
    if (sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    return -1;
}

static int DoServe(int sockfd)
{
    fd_set fds;

    struct sockaddr_in recvAddr = { 0 };
    struct sockaddr_in sendAddr = { 0 };
    int iAddrLen = sizeof(struct sockaddr_in);

    char recvBuf[4096] = {0};
    char sendBuf[4096] = {0};
    UdpHeader *pHeader = NULL;
    UdpData *pData = NULL;

    for(;;)
    {
        struct timeval timeout={3,0};
        int selectRet;
        FD_ZERO(&fds);
        FD_SET(sockfd,&fds);
        selectRet = select(sockfd+1,&fds,NULL,NULL,&timeout);
        if(selectRet > 0 && FD_ISSET(sockfd, &fds))
        {
            fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
            /*receive*/
            if (recvfrom(sockfd, recvBuf, sizeof(recvBuf), MSG_DONTWAIT, (struct sockaddr *)&recvAddr, (socklen_t *)&iAddrLen) <= 0)
            {
                fprintf(stderr, "Error when receive msg by recvfrom.\n");
                return -1;
            }

            /*serve*/
            pHeader = (UdpHeader *)recvBuf;
            switch (pHeader->type)
            {
                case CLIENT_REQ1:
                    {
                        fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
                        printf("receive from client:%s\n", inet_ntoa(recvAddr.sin_addr));
                        pHeader = (UdpHeader *)sendBuf;
                        pHeader->len      = sizeof(UdpHeader) + sizeof(UdpData);
                        pHeader->type = SERVER_RSP;
                        pData = (UdpData *)(sendBuf + sizeof(UdpHeader));
                        pData->param1 = 123;
                        sprintf(pData->msg, "Hello, this is message from server for request1.");
                        break;
                    }
                case CLIENT_REQ2:
                    {
                        fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
                        printf("receive from client:%s\n", inet_ntoa(recvAddr.sin_addr));
                        pHeader = (UdpHeader *)sendBuf;
                        pHeader->len      = sizeof(UdpHeader) + sizeof(UdpData);
                        pHeader->type = SERVER_RSP;
                        pData = (UdpData *)(sendBuf + sizeof(UdpHeader));
                        pData->param1 = 456;
                        sprintf(pData->msg, "Hello, this is message from server for request2.");
                        break;
                    }
                default:
                    break;
            }
            fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);

            /*response*/
            sendAddr.sin_family            = AF_INET;
            sendAddr.sin_port              = recvAddr.sin_port;
            sendAddr.sin_addr.s_addr       = recvAddr.sin_addr.s_addr;
            sendto(sockfd, sendBuf, pHeader->len, 0, (struct sockaddr *)&sendAddr, iAddrLen);
            fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
        }
    }
}
