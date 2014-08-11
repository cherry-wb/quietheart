/*test:
1)write:
./testapp -w <offset> <size> <intputfile>
2)read:
./testapp -r <offset> <size> <outputfile>
*/
#include "Fr_diabloverup.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*File mode*/
#define I_OPENMODE S_IRWXU
#define I_OPENFLAG O_RDONLY
#define O_OPENMODE S_IRWXU
#define O_OPENFLAG O_RDWR | O_CREAT

int main(int argc, char *argv[])
{
	unsigned int len, off;
	char *buf = NULL;
	if(5 != argc)
	{
		printf("Usage:\n");
		printf("1,write:\n");
		printf("%s -w <offset> <size> <intputfile>\n",argv[0]);
		printf("2,read:\n");
		printf("%s -r <offset> <size> <outputfile>\n",argv[0]);
		return 1;
	}
	off = atoi(argv[2]);
	len = atoi(argv[3]);
	if(NULL == (buf = (char*)malloc(len)))
	{
		perror("No Space!\n");
		return 1;
	}

	if(argv[1] = 'w')
	{
		int ifile = open(argv[4], I_OPENFLAG, I_OPENMODE);
		if(len != read(ifile, buf, len))
		{
			perror("Read input error!\n");
			if(NULL != buf)
			{
				free(buf);
				buf = NULL;
			}
			close(ifile);
			return 1;
		}
		SPI_DiabloVerupWrite(0, buf, len);
	}
	else if(argv[1] = 'r')
	{
		int ofile = open(argv[4], O_OPENFLAG, O_OPENMODE);
		SPI_DiabloReadDataBytes(off, len, buf);
		/*write to outputfile*/
		if(len != write(ofile,buf,len))
		{
			perror("write output error!\n");
			if(NULL != buf)
			{
				free(buf);
				buf = NULL;
			}
			close(ofile);
			return 1;
		}
	}

	if(NULL != buf)
	{
		free(buf);
		buf = NULL;
	}

	return 0;
}
