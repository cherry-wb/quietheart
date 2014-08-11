/**
* @page mapmem_drv Page of mapmem drivers.
*/
/**
* Copyright 2011 
* Description:This file is used by mapmemdrv driver.
*/
#ifndef __MAPMEMDRV_H
#define __MAPMEMDRV_H

#if defined(__cplusplus)
extern "C" {
#endif
#include <linux/ioctl.h>

/**
* @defgroup mapmemdrv_group mapmem drivers
*
* Information about mapmem drivers.
*/

/**
* @addtogroup mapmemdrv_group
*
* @{
*/
/**
* @brief Driver major number for static allocation
*/
#define __MAPMEM_MAJOR__ 1025

/**
* @brief If use static allocation
*/
#define __IS_STATIC_MAJOR__ 1

/**
* @brief device node name
*/
#define __DEVICE_NAME__  "mapmemdev0"

/**
* @brief Buffer size
*/
#define __MAPMEM_SIZE__ 0x200000

/**
* @brief Commands for ioctl
*/
#define __MAPMEM_MAGIC__ 'M'
/** Get physical address base of buffer of device*/
#define __MEM_PHY_BASE__ _IOR(__MAPMEM_MAGIC__,0,int)
#define __MEM_SEND_NOTIFY__ _IOR(__MAPMEM_MAGIC__,1,int)
#define __MEM_RECEIVE_NOTIFY__ _IOR(__MAPMEM_MAGIC__,2,int)

/**
* @}
*/

#if defined(__cplusplus)
}
#endif

#endif
