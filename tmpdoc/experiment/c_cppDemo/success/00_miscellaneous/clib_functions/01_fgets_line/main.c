/*程序功能： 
使用fgets读取文件的一行，并且打印出来。
char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets(char *buf);
两者都以行的方式操作流。fgets需要指定缓存的大小，然后读取一行，读取的结果包含new line和一个null结束。如果行长超过了n，那么就读取到n，最后也包含一个null字符（需要仔细调查？）,反正fgets最多读取n-1个字符。gets已经逐渐被淘汰了，因为没有指定缓存大小，不安全，另外它并不把newline存放到buffer中。
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    char chars[256];
    FILE *f = fopen("./test","r");
    while(!feof(f))
    {   
        fgets(chars,256,f);//注意回车也都读取了
        printf("%s",chars,ftell(f));
        //printf("%s:%ld",chars,ftell(f));
    }   
    fclose(f);
	return 0;
}
