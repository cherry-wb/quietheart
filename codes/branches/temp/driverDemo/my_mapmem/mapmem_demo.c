/**
* @mainpage Main page of usage of mapmem demo.
*	- @subpage mapmem_drv About mapmem driver.
*	- @subpage mapmem	About mapmem device api.
*	.
* Description: 
*
* This Shows how to use the mem map driver.
*
* Author: quiet_heart000@126.com
* Copyright 2011
*/
#include "mapmem.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	void *user_vir_addr;

	/*...Malloc the user vir addr from mapmem device...*/

	unsigned long phy_addr = user_virt_to_phys((unsigned long )user_vir_addr);

	printf("The address in user space is:%ld\nThe physical address is:%ld\n",user_vir_addr,phy_addr);

	return 0;
}
