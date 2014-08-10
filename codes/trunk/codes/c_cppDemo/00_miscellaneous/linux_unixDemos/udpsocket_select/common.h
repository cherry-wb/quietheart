#ifndef __COMMON_H
#define __COMMON_H

#define UDP_RECV_PORT          50055

#define SERVER_RSP 0x01
#define CLIENT_REQ1 0x02
#define CLIENT_REQ2 0x03

/*Our own header*/
typedef struct UdpHeader
{
    unsigned short type;
    unsigned short len;
} UdpHeader;

/*Our own data*/
typedef struct UdpData
{
    int param1;
    char msg[64];
} UdpData;

#endif
