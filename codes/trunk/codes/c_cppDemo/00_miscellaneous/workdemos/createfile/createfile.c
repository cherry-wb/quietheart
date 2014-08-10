#include <stdio.h>
#include <string.h>

/*generate file of the following content:
/dev/ttyUSB0 
115200
crtscts
modem
debug
lock
nodetach
usepeerdns
defaultroute
noipdefault
noauth
user "ctnet@mycdma.cn"
password "vnet.mobi"
lcp-echo-failure 5
lcp-echo-interval 30
0.0.0.0:0.0.0.0
connect '/usr/sbin/chat -s -v -f /etc/ppp/cdma2000-connect-chat'
*/
#define CT3G_PPP "/dev/ttyUSB0 \r\n"\
"115200\r\n"\
"crtscts\r\n"\
"modem\r\n"\
"debug\r\n"\
"lock\r\n"\
"nodetach\r\n"\
"usepeerdns\r\n"\
"defaultroute\r\n"\
"noipdefault\r\n"\
"noauth\r\n"\
"user \"%s\"\r\n"\
"password \"%s\"\r\n"\
"lcp-echo-failure 5\r\n"\
"lcp-echo-interval 30\r\n"\
"0.0.0.0:0.0.0.0\r\n"\
"connect '/usr/sbin/chat -s -v -f /etc/ppp/cdma2000-connect-chat'\r\n"

/*generate file of the following content:
TIMEOUT 5
ABORT "DELAYED"
ABORT "BUSY"
ABORT "ERROR"
ABORT "NO DIALTONE"
ABORT "NO CARRIER"
""   AT
"OK-+++\c-OK" ATH0
TIMEOUT 40
""   AT
OK  ATDT#777
CONNECT ""
*/
#define CT3G_CHAT "TIMEOUT 5\r\n"\
"ABORT \"DELAYED\"\r\n"\
"ABORT \"BUSY\"\r\n"\
"ABORT \"ERROR\"\r\n"\
"ABORT \"NO DIALTONE\"\r\n"\
"ABORT \"NO CARRIER\"\r\n"\
"\"\"   AT\r\n"\
"\"OK-+++\\c-OK\" ATH0\r\n"\
"TIMEOUT 40\r\n"\
"\"\"   AT\r\n"\
"OK  ATDT%s\r\n"\
"CONNECT \"\"\r\n"\

int CreateFile(const char *pPath, const char *pBuf, int len)
{
    FILE *pFile = NULL;
    int result = 0;
    if ((pFile = fopen(pPath, "w+")) == NULL)
    {
        result = -1;
        return result;
    }

    if (fwrite(pBuf, len, 1, pFile) <= 0)
    {
        perror("fwrite failed:");
        fclose(pFile);
        result = -1;
        return result;
    }

    fflush(pFile);
    fclose(pFile);
    return 0;
}

int main(int argc, char *argv[])
{
    char buf[1024];
    memset(buf, 0x00, sizeof(buf));
    sprintf(buf, CT3G_PPP, "ctnet@mycdma.cn", "vnet.mobi");
    CreateFile("./pppcfg", buf, strlen(buf));

    memset(buf, 0x00, sizeof(buf));
    sprintf(buf, CT3G_CHAT, "#777");
    CreateFile("./pppchat", buf, strlen(buf));
    return 0;
}
