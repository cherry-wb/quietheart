struct libin_wifi
{
  unsigned char         NET_NUMBER;         /* 搜索到的第几个网络*/
  char *                MAC;	      /* MAC */
  unsigned char         NWID;           /* NWID_libin = 0 代表 NWID:off/any*/
  const char *          Mode;           /* 当为char * Mode_libin 总提示警告信息：警告： 赋值丢弃了指针目标类型的限定 */  
  char *                Protocol_libin;
  char *                ESSID;          /* ESSID_libin = NULL 代表ESSID:off/any/hidden */
  unsigned char         ESSID_NUMBER;   /* ESSID_NUMBER_libin = NULL 代表0 */
  char *                Encryption_key; /*on / off*/
  char *                Bit_Rates;
  char *                Modulations;
  char *                Extra;
  unsigned char         Unknown_Wireless_Token;
  int                   Singal_level;
  int                   Noise_level;
};
struct libin_wifi*  scanning(void);
int iwconfig_eth0_essid(char *dev,char *net);
int iwconfig_eth0_key(char *dev,char *net);
