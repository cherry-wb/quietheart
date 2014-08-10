#ifndef __COMMON_H
#define __COMMON_H

#define TCP_SERV_IPV4 "192.168.1.112"
#define TCP_SERV_IPV6 "fc00::112"
#define TCP_SERV_IPALLV4 "0.0.0.0"
#define TCP_SERV_IPALLV6 "::"
#define TCP_SERV_PORT 10010

/*Our own data*/
typedef struct TcpData
{
    char msg[64];
} TcpData;

#endif
