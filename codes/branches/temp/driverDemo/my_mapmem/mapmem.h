/**
* @page mapmem Page of mapmem device api.
*/
/**
* Copyright 2011 
* Description:This file describe api for mapmem used in user space.
* Author: quiet_heart000@126.com
*/
#ifndef __MAPMEM_H
#define __MAPMEM_H
#include "mapmemdrv.h"
#if defined(__cplusplus)
extern "C" {
#endif
/**
* @defgroup memmapapi_group mapmem API
*
* Information about api for mapmem devices.
*/

/**
* @addtogroup memmapapi_group
*
* @{
*/


/**
* @name mapmem_public_functions
* Public function declarations. 
*/
/**
* @{
*/
/**
* @brief Map the user space virtual address to physical address.
*
* @param[in] virt_addr user space virtual address.
*
* @return the physical memory address of virt_addr.
*/
unsigned long user_virt_to_phys(unsigned long virt_addr);

/**
* @brief Map the physical address to user space virtual address.
*
* @param[in] phys_addr physical memory address.
*
* @return the user space virtual address of phys_addr.
*
* - Note:Current this function has no meaning because the physical addr may not in user space???
*/
unsigned long phys_to_user_virt(unsigned long phys_addr);
/**
* @}
*/

/**
* @}
*/

#if defined(__cplusplus)
}
#endif

#endif
