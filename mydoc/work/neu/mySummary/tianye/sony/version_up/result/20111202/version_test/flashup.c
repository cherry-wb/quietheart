/** \mainpage Help page of this program
*	- NAME
*	flashup - test the driver of spi flash with read and write.
*
*	- SYNOPSIS
*	flashup [Option]... [FILE]...
*
*
*	- DESCRIPTION
*	This program used to test the availability of spi flash driver, which will be used for version upgrade in EU11 project.
*
*
*	- EXAMPLES:(Note:now the input length and size is hex)
*	This list the use example of this program.
*		-# (1) write the file:
*		$flashup -w -s 100 -l 200 srcfile desfile
*		or $flashup -s 100 -l 200 srcfile desfile
*		This will write the file "srcfile" to the specified offset of file "desfile". i.e. write the content of "srcfile" to the 100th byte of "desfile", with the content length of 200 bytes.
*
*
*		-# (2) read the file:
*		$flashup -r -s 100 -l 200 srcfile desfile
*		This will read from specified offset of the file "srcfile" to "desfile". i.e. read from the 100th byte of srcfile and write it to desfile, with the length of 200 bytes.
*
*	- TESTS:
*	This shows the way of test the spi flash in avp17 or avp13 board:
*		-#(1) write to spi flash:
*		$flashup -w -s 100 -l 200 inputdatafile /dev/sfmem
*
*		-# (2) read from spi flash:
*		$flashup -r -s 100 -l 200 /dev/sfmem outputdatafile
*
*	- BUGS
*	If there is any bug , please report to: <lv-k@neusoft.com>
*	.
**/

/*Headers*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*Debug flag*/
//#define DEBUG
//#define DEBUG_HEX 0
#if DEBUG_HEX  == 1
#else
#include <string.h>
#endif

#ifdef DEBUG
#define pr_debug(...) do{\
fprintf(stderr,"@@@Function:%s, Line:%d.===>>>: ",__FUNCTION__,__LINE__);\
fprintf(stderr,__VA_ARGS__);\
}while(0)
#else
#define pr_debug(...)
#endif

/*Argument index in argv*/
#define CMD_MODE 1
#define CMD_OFFSET 3
#define CMD_LENGTH 5
#define CMD_INPUT 6
#define CMD_OUTPUT 7

#define CMD_DEF_OFFSET 2
#define CMD_DEF_LENGTH 4
#define CMD_DEF_INPUT 5
#define CMD_DEF_OUTPUT 6

/*File mode*/
#define I_OPENMODE S_IRWXU
#define I_OPENFLAG O_RDONLY
#define O_OPENMODE S_IRWXU
#define O_OPENFLAG O_RDWR | O_CREAT

int   convert16(const char* szHex);
/**
* \brief main
*/
int main(int argc, char *argv[])
{
	if((8 != argc) && (7 != argc))
	{
		printf("Usage:%s [-w|-r]  -s <offset> -l <length> inputfile outputfile\n", argv[0]);
		return 1;
	}
	else
	{
		int offset,length;
		int ifile,ofile;
		char *readbuf;
		/*XXX Check detail arguemnt needs to be done.*/
		if((0 == strcmp(argv[CMD_MODE], "-w")) 
			|| 0 == strcmp(argv[CMD_MODE], "-s") && 7 == argc )
		{/*Default mode is write*/
			pr_debug("write mode.\n");
			if(7 == argc)
			{
				ifile = open(argv[CMD_DEF_INPUT], I_OPENFLAG, I_OPENMODE);
				ofile = open(argv[CMD_DEF_OUTPUT], O_OPENFLAG, O_OPENMODE);
				offset = convert16(argv[CMD_DEF_OFFSET]);
				length = convert16(argv[CMD_DEF_LENGTH]);
			}
			else
			{
				ifile = open(argv[CMD_INPUT], I_OPENFLAG, I_OPENMODE);
				ofile = open(argv[CMD_OUTPUT], O_OPENFLAG, O_OPENMODE);
				offset = convert16(argv[CMD_OFFSET]);
				length = convert16(argv[CMD_LENGTH]);
			}
			pr_debug("offset:%d,length:%d\n",offset, length);

			/*read from inputdatafile*/
			if(NULL == (readbuf = (char*)malloc(length)))
			{
				perror("No Space!\n");
				return 1;
			}
			if(length != read(ifile, readbuf, length))
			{
				if(NULL != readbuf)
				{
					free(readbuf);
					readbuf = NULL;
				}
				perror("Read input error!\n");
				return 1;
			}
			pr_debug("%s\n",readbuf);

			/*write to outputfile*/
			lseek(ofile, offset, SEEK_SET);
			if(length != write(ofile,readbuf,length))
			{
				if(NULL != readbuf)
				{
					free(readbuf);
					readbuf = NULL;
				}
				perror("write output error!\n");
				return 1;
			}

		}
		else if(0 == strcmp(argv[1], "-r"))
		{
			pr_debug("read mode.\n");
			ifile = open(argv[CMD_INPUT], I_OPENFLAG, I_OPENMODE);
			ofile = open(argv[CMD_OUTPUT], O_OPENFLAG, O_OPENMODE);
			offset = convert16(argv[CMD_OFFSET]);
			length = convert16(argv[CMD_LENGTH]);


			pr_debug("offset:%d,length:%d\n",offset, length);

			/*read from inputdatafile*/
			lseek(ifile, offset, SEEK_SET);
			if(NULL == (readbuf = (char*)malloc(length)))
			{
				perror("No Space!\n");
				return 1;
			}
			if(length != read(ifile, readbuf, length))
			{
				if(NULL != readbuf)
				{
					free(readbuf);
					readbuf = NULL;
				}
				perror("Read input error!\n");
				return 1;
			}
			pr_debug("%s\n",readbuf);

			/*write to outputfile*/
			if(length != write(ofile,readbuf,length))
			{
				if(NULL != readbuf)
				{
					free(readbuf);
					readbuf = NULL;
				}
				perror("write output error!\n");
				return 1;
			}
		}
		else
		{
			printf("Unknown arguments \n");
			printf("Usage:%s [-w|-r]  -s <offset> -l <length> inputfile outputfile\n", argv[0]);
			return 1;
		}

		if(NULL != readbuf)
		{
			free(readbuf);
			readbuf = NULL;
		}
		close(ifile);
		close(ofile);

	}
	return 0;
}

int convert16(const char* szHex)
{
	int   sum=0;
#if DEBUG_HEX == 1
	int   index=0;
	int   tmp=0;

	while(szHex[index])
	{
		switch(szHex[index])
		{
			case   'A':
			case   'a':
				tmp=10;
				break;
			case   'B':
			case   'b':
				tmp=11;
				break;
			case   'C':
			case   'c':
				tmp=12;
				break;
			case   'D':
			case   'd':
				tmp=13;
				break;
			case   'E':
			case   'e':
				tmp=14;
				break;
			case   'F':
			case   'f':
				tmp=15;
				break;
			default:
				if( '0' <=szHex[index]   &&   szHex[index] <= '9')
				{
					tmp=szHex[index]- '0';
				}
				else
				{
					tmp=0;
				}
				break;
		}
		index++;
		sum=(sum<<4)+tmp;
	}
#else
	sum = atoi(szHex);
#endif
	return sum;
}
