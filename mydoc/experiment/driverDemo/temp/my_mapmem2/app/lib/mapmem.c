/*For mmap*/
#include <sys/mman.h>

/*For file open*/
#include <fcntl.h>

/*For sysconf*/
#include <unistd.h>

/*memcpy*/
#include <string.h>

/*Our api for mapmem*/
#include "mapmem.h"


/*Device path*/
#define __DEVICE_PATH__ "/dev/"__DEVICE_NAME__

/**
* @addtogroup mapmemdrv_group
*
* @{
*/

/**
* @name mapmem_private_functions
* Private function declarations. 
*/
/**
* @{
*/

/*Private function*/
static unsigned long get_user_virt_base(int fd);
/**
* @}
*/

/**
* @}
*/

/*Our implementation for mapmem device api*/
unsigned long user_virt_to_phys(unsigned long virt_addr)
{
	unsigned long phy_base = 0;
	unsigned long user_virt_base = 0;
	unsigned long phys_addr = 0;

	char *filename = __DEVICE_PATH__;
	int fd = open(filename,O_RDONLY);

	/*Get physical address base*/
	ioctl(fd,__MEM_PHY_BASE__, &phy_base);

	/*Get user virtual address base*/
	user_virt_base = get_user_virt_base(fd);

	/*Compute physical address for virt_addr*/
	phys_addr = virt_addr - user_virt_base + phy_base;

	close(fd);
	return phys_addr;
	
}
unsigned long phys_to_user_virt(unsigned long phys_addr)
{
	return 0;
}

long int send(void *des, void *src, int length)
{
	//memcpy(user_vir_addr, "hello!", sizeof("hello!"));
	memcpy(des,src,length);

	char *filename = __DEVICE_PATH__;
	int fd = open(filename,O_RDONLY);
	ioctl(fd, __MEM_SEND_NOTIFY__, &length);
	close(fd);
	return 0;
}

long int receive(void *src, void *des, int length)
{
	memcpy(des,src,length);

	char *filename = __DEVICE_PATH__;
	int fd = open(filename,O_RDONLY);
	ioctl(fd, __MEM_RECEIVE_NOTIFY__, &length);
	close(fd);
	return 0;
}

static unsigned long get_user_virt_base(int fd)
{
	unsigned long usr_vir_base = 0;

	int offset = 0;
	int realOffset = 0 & ~(sysconf(_SC_PAGE_SIZE) - 1);

	int length = __MAPMEM_SIZE__;
	int realLen = length+offset-realOffset;

	/*first argument is NULL???*/
	char *addr = mmap(NULL, realLen,PROT_READ,MAP_PRIVATE,fd,realOffset);
	usr_vir_base = (unsigned long)addr;
	munmap(addr,realLen);

	return usr_vir_base;
}
