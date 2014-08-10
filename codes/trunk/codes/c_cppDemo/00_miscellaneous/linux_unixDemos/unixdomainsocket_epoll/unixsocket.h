#ifndef __UNIX_SOCKET_H__
#define __UNIX_SOCKET_H__

#define SIZE_1K (1<<10)
#define NO_WAIT             0
#define WAIT_FOREVER       -1
#define DEFAULT_DIR "./tmp/"
#define DEFAULT_FILE "myunixsocket"
#define DEFAULT_PATH "./tmp/myunixsocket"

enum ProcID{
    Id1=0,/*for server with client1*/
    Id2,/*for server with client2*/
    Id3,/*for client1*/
    Id4,/*for client2*/
    IdNum
};

/*Create socket addr for every ProcID*/
int UnixDomainInit(void);

/*Create an specify socket(for localId) with binded socket addr.*/
int UnixDomainCreate(int localId, unsigned int maxBufSize);

/*Send msg to remoteId, with local created sockFd.*/
int UnixDomainSend(int sockFd, int remoteId, void *pBuf, unsigned bufSize, int timeout);

/*Receive msg from local created sockFd.*/
int UnixDomainRecv(int sockFd, void *pBuf, unsigned int bufSize, int timeout);
#endif
