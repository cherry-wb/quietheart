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
#include "../../driver/mapmemdrv.h"
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
* TODO
*/
unsigned long phys_to_user_virt(unsigned long phys_addr);

/**
* @brief Send signal to notify the receiver.
*
* @param[out] des buffer in the driver to receive data from src.(Is it needed?)
*
* @param[in] src buffer in the user space contains data to be send.
*
* @param[in] length length of data in the src to be send.
*
* @return success if >=0, or some error.
* XXX To be improved.
*/
long int send(void *des, void *src, int length);

/**
* @brief Send signal to notify the sender.
*
* @param[in] src buffer in the driver to receive data from.
*
* @param[out] des buffer in the user space contains data to be send.(Is it needed?)
*
* @param[in] length length of data in the src to be received.
*
* @return success if >=0, or some error.
* XXX To be improved.
* - Note:Current this function has no meaning.
*/
long int receive(void *src, void *des, int length);
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
