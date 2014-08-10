#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <net/if.h>

#include "common.h"

static int InitUdpSocket();
static int DoRequest(int sockfd, int requestNo);

int main(int argc, char *argv[])
{
    int ret = 0;
    int sockfd = -1;
    
    if (2 != argc)
    {
        fprintf(stderr, "Usage:\n    %s <requestno>\n", argv[0]);
        fprintf(stderr, "Here, the \"<requestno>\" is 1 or 2\n");
        return -1;
    }
    sockfd = InitUdpSocket();
    if (sockfd != -1)
    {
        ret = DoRequest(sockfd, atoi(argv[1]));
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
    int isEnable = 1;
    int flags = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
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

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&isEnable, sizeof(int)) < 0)
    {
        fprintf(stderr, "Error when set SO_REUSEADDR option with setsockopt.\n");
        goto DEV_FOUND_END;
    }

    /*Set the broadcast.*/
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&isEnable, sizeof(int)) != 0)
    {
        fprintf(stderr, "Error when set SO_BROADCAST option with setsockopt.\n");
        goto DEV_FOUND_END;
    }
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
    return sockfd;

DEV_FOUND_END:
    if (sockfd >= 0)
    {
        close(sockfd);
        sockfd = -1;
    }
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
    return -1;
}

static int DoRequest(int sockfd, int requestNo)
{
    fd_set fds;
    struct timeval timeout={5,0};
    int selectRet = 0;

    struct sockaddr_in recvAddr = { 0 };
    struct sockaddr_in sendAddr = { 0 };
    int iAddrLen = sizeof(struct sockaddr_in);

    char recvBuf[4096] = {0};
    char sendBuf[4096] = {0};
    UdpHeader *pHeader = NULL;
    UdpData *pData = NULL;

    /*broadcast request*/
    sendAddr.sin_family            = AF_INET;
    sendAddr.sin_port              = htons(UDP_RECV_PORT);
    sendAddr.sin_addr.s_addr       = inet_addr("255.255.255.255");
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
    pHeader = (UdpHeader *)sendBuf;
    pHeader->len = sizeof(UdpHeader);/*receive length*/
    switch (requestNo)
    {
        case 1:
            {
                pHeader->type = CLIENT_REQ1;
                break;
            }
        case 2:
            {
                pHeader->type = CLIENT_REQ2;
                break;
            }
        default:
            fprintf(stderr, "Error request number error.\n");
            return -1;
    }
    sendto(sockfd, sendBuf, pHeader->len, 0, (struct sockaddr *)&sendAddr, iAddrLen);
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);

    FD_ZERO(&fds);
    FD_SET(sockfd,&fds);/*Add sockfd to fds*/
    fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
    selectRet = select(sockfd+1,&fds,NULL,NULL,&timeout);/*0 for timeout, -1 for error, >0 is the number of readable file returns*/
    fprintf(stderr, "file:%s, line:%d, ret:%d\n", __FILE__, __LINE__, selectRet);
    while(selectRet > 0 && FD_ISSET(sockfd, &fds))
    {/*if select returns > 0, FD_ISSET(sockfd, &fds) is 1, or it is 0*/
        fprintf(stderr, "file:%s, line:%d\n", __FILE__, __LINE__);
        /*receive*/
        if (recvfrom(sockfd, recvBuf, sizeof(recvBuf), MSG_DONTWAIT, (struct sockaddr *)&recvAddr, (socklen_t *)&iAddrLen) <= 0)
        {
            fprintf(stderr, "Error when receive msg by recvfrom.\n");
            return -1;
        }

        /*process*/
        pHeader = (UdpHeader *)recvBuf;
        switch (pHeader->type)
        {
            case SERVER_RSP:
                {

                    pData = (UdpData *)(recvBuf + sizeof(UdpHeader));
                    printf("receive from server:%s\n", inet_ntoa(recvAddr.sin_addr));
                    printf("data param1:%d, data message:%s\n", pData->param1, pData->msg);
                    break;
                }
            default:
                break;
        }

        /* note: the after select calls has the same effect don't need to clear fdset, the timeout is changed every select.*/
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        selectRet = select(sockfd+1,&fds,NULL,NULL,&timeout);
        //fprintf(stderr, "file:%s, line:%d, ret:%d\n", __FILE__, __LINE__, selectRet);
        //fprintf(stderr, "file:%s, line:%d, isSet:%d\n", __FILE__, __LINE__, FD_ISSET(sockfd,&fds));
    }
    return 0;
}
