/*Headers*/
#include "Fr_diabloverup.h"
#include <stdio.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>

/*Debug flag*/
//#define DEBUG
#ifdef DEBUG
#define pr_debug(...) do{\
fprintf(stderr,"@@@Function:%s, Line:%d.===>>>: ",__FUNCTION__,__LINE__);\
fprintf(stderr,__VA_ARGS__);\
}while(0)
#else
#define pr_debug(...)
#endif

/*Device file*/
#ifdef DEBUG
#define DIABLO_SFMEM_DEVICE "./mytest"
#else
#define DIABLO_SFMEM_DEVICE "/dev/sfmem"
#endif

/*File mode*/
#define I_OPENMODE S_IRWXU
#define I_OPENFLAG O_RDONLY
#define O_OPENMODE S_IRWXU
#define O_OPENFLAG O_RDWR | O_CREAT


int SPI_DiabloVerupInit(void)
{
	return 0;
}
int SPI_DiabloVerupStart(unsigned int uiAddr, unsigned int uiSize)
{
	return 0;
}
int SPI_DiabloVerupWrite(unsigned int ulWrAdrs, unsigned char *pucBuf, unsigned long ulRemSize)
{
	unsigned int offset,length;
	int ofile;
	char *readbuf;

	ofile = open(DIABLO_SFMEM_DEVICE, O_OPENFLAG, O_OPENMODE);
	offset = ulWrAdrs;
	length = ulRemSize;
	pr_debug("offset:%d,length:%d\n",offset, length);

	readbuf = pucBuf;
	if(NULL == readbuf)
	{
		perror("No Space!\n");
		close(ofile);
		return -1;
	}

	pr_debug("%s\n",readbuf);

	/*write to outputfile*/
	lseek(ofile, offset, SEEK_SET);
	if(length != write(ofile,readbuf,length))
	{
		perror("write output error!\n");
		close(ofile);
		return 1;
	}
	close(ofile);
	return length;
}

int SPI_DiabloVerupEnd(void)
{
	return 0;
}

void SPI_DiabloReadDataBytes(unsigned int ulRdAdrs,unsigned long ulSize, unsigned char *pucBuf)
{
	unsigned int offset,length;
	int ifile;
	char *readbuf;

	ifile = open(DIABLO_SFMEM_DEVICE, I_OPENFLAG, I_OPENMODE);
	length = ulSize;
	offset = ulRdAdrs;

	pr_debug("length:%d\n",length);

	readbuf = pucBuf;
	/*read from inputdatafile*/
	if(NULL == readbuf)
	{
		perror("No Space!\n");
		close(ifile);
		return ;
	}
	lseek(ifile, offset, SEEK_SET);
	if(length != read(ifile, readbuf, length))
	{
		perror("Read input error!\n");
		close(ifile);
		return;
	}
	pr_debug("%s\n",readbuf);
	close(ifile);
	return ;
}
