#include<stdio.h> 
int
main(void)
{
	char    name[L_tmpnam], line[1024];
	FILE    *fp;

	printf("%s\n", tmpnam(NULL));       /* first temp name */

	tmpnam(name);                       /* second temp name */
	printf("%s\n", name);

	/*新创建的文件的名字是什么呢？*/
	if ((fp = tmpfile()) == NULL)       /* create temp file */
		perror("tmpfile error");
	fputs("one line of output\n", fp);  /* write to temp file */
	rewind(fp);                         /* then read it back */
	if (fgets(line, sizeof(line), fp) == NULL)
		perror("fgets error");
	fputs(line, stdout);                /* print the line we wrote */

	sleep(20);
	//exit(0);
	return 0;
}
