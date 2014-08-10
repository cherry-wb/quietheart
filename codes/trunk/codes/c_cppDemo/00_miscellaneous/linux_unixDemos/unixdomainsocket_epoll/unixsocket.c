#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <dirent.h>

#include "unixsocket.h"

static struct sockaddr_un ma_UnAddr[IdNum];
static char filePath[IdNum][64];

int UnixDomainInit(void)
{/*Create unix domain socket addr.*/
    int len = 0;
    int index = 0;
    struct sockaddr_un *pAddr = NULL;
    DIR *pdir = NULL;
    FILE *pFile = NULL;

    pdir = opendir(DEFAULT_DIR);
    if (pdir == NULL)
    {
        fprintf(stderr, "create dir %d, %s.\n", errno, strerror(errno));
        return -1;
    }
    closedir(pdir);

    memset(ma_UnAddr, 0x00, sizeof(ma_UnAddr));
    for (index = 0; index < IdNum; index++)
    {
        sprintf(filePath[index], "%s.%d", DEFAULT_PATH, index);
        /*
        pFile = fopen(filePath[index], "w+");
        if (pFile == NULL)
        {
            fprintf(stderr, "create file %d, %s.\n", errno, strerror(errno));
            return -1;
        }
        fclose(pFile);
        */
    
        pAddr = &ma_UnAddr[index];
        pAddr->sun_family = AF_LOCAL;
        sprintf(pAddr->sun_path, "%s", filePath[index]);
    }
    
    return 0;
}

int UnixDomainCreate(int localId, unsigned int maxBufSize)
{/*Create socket and bind it to socket addr of local id.*/
    int ret = 0;
    int sockFd = -1;
    int bufSize = 0;
    struct sockaddr_un *pLocalAddr = &ma_UnAddr[localId];


    sockFd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (-1 == sockFd)
    {
        fprintf(stderr, "create socket.%d, %s\n", errno, strerror(errno));
        return -1;
    }

    remove(pLocalAddr->sun_path);

    if (-1 == bind(sockFd, (const struct sockaddr *)pLocalAddr, sizeof(*pLocalAddr)))
    {
        fprintf(stderr, "bind error, index:%d, path:%s\n", localId, pLocalAddr->sun_path);
        fprintf(stderr, "bind error:%d, %s\n", errno, strerror(errno));
        goto err;
    }

    bufSize = (int)maxBufSize;

    ret = setsockopt(sockFd, SOL_SOCKET, SO_SNDBUF, &bufSize, sizeof(bufSize));
    if (0 != ret)
    {
        fprintf(stderr, "setsockopt %d:%d, %s\n", bufSize, errno, strerror(errno));
        goto err;
    }
    
    ret = setsockopt(sockFd, SOL_SOCKET, SO_RCVBUF, &bufSize, sizeof(bufSize));
    if (0 != ret)
    {
        fprintf(stderr, "setsockopt %d:%d, %s\n", bufSize, errno, strerror(errno));
        goto err;
    }

    return sockFd;

err:
    close(sockFd);
    return -1;
}

int UnixDomainRecv(int sockFd, void *pBuf, unsigned int bufSize, int timeout)
{
    int flags = 0;
    ssize_t n = 0;
    socklen_t addrLen = sizeof(struct sockaddr_un);
    struct sockaddr_un remoteAddr;   

    if ((0 > sockFd)
        || (NULL == pBuf)
        || (0 == bufSize))
    {
        return -1;
    }    

    if ((NO_WAIT == timeout)
        || (0 < timeout))
    {
        flags |= MSG_DONTWAIT;
    }
    
    if (0 < timeout)
    {
        fd_set r;
        int sr = 0;
        struct timeval time;
        
        FD_ZERO(&r);
        FD_SET(sockFd, &r);
        
        time.tv_usec = ((timeout%1000)*1000);
        time.tv_sec  = (timeout/1000);

        sr = select(sockFd + 1, &r, NULL, NULL, &time);
        if (0 >= sr)
        {
            return -2;
        }         
    }

    n = recvfrom(sockFd, pBuf, bufSize, flags, (struct sockaddr *)&remoteAddr, &addrLen);
    if (0 > n)
    {
        fprintf(stderr, "sockFd[%d] recvfrom fail:%d, %s", sockFd, errno, strerror(errno));
        return -3;
    }

    return 0;
}

int UnixDomainSend(int sockFd, int remoteId, void *pBuf, unsigned bufSize, int timeout)
{
    int flags = 0;
    ssize_t n = 0;
    struct sockaddr_un *pRemoteAddr = &ma_UnAddr[remoteId];

    if ((0 > sockFd)
        || (NULL == pBuf)
        || (0 == bufSize))
    {
        return -1;
    }

    if (NO_WAIT == timeout)
    {
        flags |= MSG_DONTWAIT;
    }
    
    n = sendto(sockFd, pBuf, bufSize, flags, (const struct sockaddr *)pRemoteAddr, sizeof(*pRemoteAddr));
    if (n != bufSize)
    {
        fprintf(stderr, "sockFd[%d] sendto %d fail:%d, %s", sockFd, remoteId, errno, strerror(errno));
        return -2;
    }

    return 0;
}
