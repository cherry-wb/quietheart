/** @mainpage A simple block driver.*/
/*
#mknod /dev/blktest b 288 0
#insmod simpleblkdrv.ko
#mkfs.ext3 /dev/blktest
#mkdir testmount
#mount -t ext3 /dev/blktest testmount
#cd testmount
#echo hello >test
#cd ..
#umount /dev/blktest
#mount -t ext3 /dev/blktest testmount
#cd testmount
#cat test
#cd ..
#umount /dev/blktest
#rmmod
#insmod simpleblkdrv.ko
#mount -t ext3 /dev/blktest testmount
#cd testmount
#cat test
#cd ..
#umount /dev/blktest
#rmmod

*/
/*
#include <linux/module.h> MODULE_LICENSE(),THIS_MODULE
#include <linux/moduleparam.h> module_param()
#include <linux/init.h> module_init,module_exit
#include <linux/kernel.h> printk(),KERN_NOTICE
#include <linux/slab.h> kmalloc()
#include <linux/fs.h> struct inode,struct file,check_disk_change(),struct block_device_operations,register_blkdev(),unregister_blkdev()
#include <linux/timer.h> struct timer_list,del_timer_sync(),add_timer(),init_timer()
#include <linux/hdreg.h> struct hd_geometry,HDIO_GETGEO,
#include <linux/vmalloc.h> vmalloc(),vfree()
#include <linux/genhd.h> struct gendisk,alloc_disk(),set_capacity(),add_disk(),del_gendisk(),put_disk()
#include <linux/blkdev.h> struct request_queue,request_queue_t,struct request,blk_fs_request(),blk_fs_request(),end_request(),blk_init_queue(),blk_queue_hardsect_size(),blk_cleanup_queue()
*/
#include <linux/module.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/version.h>

/*other files may useful*/
//#include <linux/kernel.h>
//#include <linux/fs.h>
//#include <linux/bio.h>
//#include <linux/mm.h>
//#include <linux/mman.h>
//#include <linux/ioctl.h>
//#include <linux/init.h>
//#include <linux/slab.h>
//#include <linux/fcntl.h>
//#include <linux/hdreg.h>
//#include <asm/uaccess.h>
//#include <asm/io.h>

/*XXX*/
#define MEMBLK_BYTES (1<<22) /*4M*/
#define simpleblkdrv_MAJOR 288
//#define simpleblkdrv_MAJOR 0

#define DRIVER_NAME	"simpleblkdrv"
#define DISK_NAME "memdisk"
#define DRIVER_AUTHOR	"QuietHeart"
#define DRIVER_DESC	"A simple block driver for access memory as disk."

#define USE_REQUEST 0

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("virtual disk for memory");

/*
struct simpleblk_data
{

};
*/

static struct gendisk *simpleblkdrv_disk;
static char blkdev_data[MEMBLK_BYTES];
static struct request_queue *simpleblkdrv_queue;


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)) //XXX not very accurate
static int simpleblk_open(struct inode *inode, struct file *filp)
{
	int ret = 0;
	return ret;
}

static int simpleblk_release(struct inode *inode, struct file *filp)
{
	int ret = 0;
	return ret;
}
#else
static int simpleblk_open(struct block_device *bd, fmode_t mode)
{
	int ret = 0;
	return ret;
}

static int simpleblk_release(struct gendisk *gd, fmode_t mode)
{
	int ret = 0;
	return ret;
}
#endif

static int simpleblk_getgeo(struct block_device *devp, struct hd_geometry *geometry)
{
	int ret = 0;
	return ret;
}

#if USE_REQUEST == 1
static void simpleblkdrv_do_request(struct request_queue *q)
{
	struct request *req;
	while ((req = elv_next_request(q)) != NULL)
	{
		if ((req->sector + req->current_nr_sectors) << 9 > BLK_BYTES)
		{
			printk(KERN_ERR"request error!\n");
			end_request(req, 0);/*transfer fail*/
			continue;
		}

		switch (rq_data_dir(req))
		{
			case READ:
				memcpy(req->buffer, blkdev_data + (req->sector << 9), req->current_nr_sectors << 9);
				end_request(req, 1);/*transfer ok*/
				break;
			case WRITE:
				memcpy(blkdev_data + (req->sector << 9), req->buffer, req->current_nr_sectors << 9);
				end_request(req, 1);/*transfer ok*/
				break;
			default:
				/* No default because rq_data_dir(req) is 1 bit */
				break;
		}
	}
}
#else //Not use request for random device
static int simpleblk_make_request(struct request_queue *q, struct bio *bio)
{
	struct bio_vec *bvec;
	int i;
	void *dsk_mem;
	if ((bio->bi_sector << 9) + bio->bi_size > MEMBLK_BYTES)
	{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)) //XXX not very accurate
		bio_endio(bio, 0, -EIO);
#else
		bio_endio(bio, -EIO);
#endif
		return -EFAULT;
	}
	dsk_mem = blkdev_data + (bio->bi_sector << 9);//in fact the bio->bi_sector is sector offset not real addr.
	switch (bio_rw(bio))
	{
		case READ:
		case READA:
			bio_for_each_segment(bvec, bio, i)
			{
				void *iovec_mem;
				iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(iovec_mem, dsk_mem, bvec->bv_len);
				kunmap(bvec->bv_page);
				dsk_mem += bvec->bv_len;
			}
			break;
		case WRITE:
			bio_for_each_segment(bvec, bio, i)
			{
				void *iovec_mem;
				iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(dsk_mem, iovec_mem, bvec->bv_len);
				kunmap(bvec->bv_page);
				dsk_mem += bvec->bv_len;
			}
			break;
		default:
			printk(KERN_ERR"bad request: unknown value of bio_rw\n");
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)) //XXX not very accurate
		bio_endio(bio, 0, -EIO);
#else
			bio_endio(bio, -EIO);
#endif
			return -EFAULT;
	}
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)) //XXX not very accurate
		bio_endio(bio, 0, -EIO);
#else
		bio_endio(bio, bio->bi_siz, 0);
#endif
	return 0;
}
#endif

static struct block_device_operations simpleblkdrv_fops = { /*this interface differs with kernel version*/
	.owner          = THIS_MODULE,
	.open = simpleblk_open,
	.release        = simpleblk_release,
	.getgeo         = simpleblk_getgeo,
};

static int __init simpleblkdrv_init(void)
{
	int retval;
	/*XXX initial structs*/
	simpleblkdrv_disk = alloc_disk(1);
	if(!simpleblkdrv_disk)
	{
		printk(KERN_ERR"error!\n");
		retval=-ENOMEM;
		goto alloc_disk_fail;
	}

	if(register_blkdev(simpleblkdrv_MAJOR,DISK_NAME))
	{
		printk(KERN_ERR"error!\n");
		retval=-EIO;
		goto register_fail;
	}

#if USE_REQUEST==1
	simpleblkdrv_queue = blk_init_queue(simpleblkdrv_do_request,NULL);/*queue handle*/
#else
	simpleblkdrv_queue = blk_alloc_queue(GFP_KERNEL);
#endif
	if(!simpleblkdrv_queue)
	{
		printk(KERN_ERR"error!\n");
		retval=-ENOMEM;
		goto alloc_queue_fail;
	}
#if USE_REQUEST == 0
	blk_queue_make_request(simpleblkdrv_queue, simpleblk_make_request);
#endif

	/*XXX set disk parameters*/
	strcpy(simpleblkdrv_disk->disk_name, DISK_NAME);/*name (optional)*/
	simpleblkdrv_disk->major = simpleblkdrv_MAJOR;/*major*/
	simpleblkdrv_disk->first_minor = 0;/*minor*/
	simpleblkdrv_disk->fops = &simpleblkdrv_fops;/*operation for disk*/
	simpleblkdrv_disk->queue = simpleblkdrv_queue;/*queue for disk*/
	set_capacity(simpleblkdrv_disk,MEMBLK_BYTES>>9);/*number of sectors*/
	add_disk(simpleblkdrv_disk);

	retval=0;
	return retval;

alloc_queue_fail:
	unregister_blkdev(simpleblkdrv_MAJOR,DISK_NAME);
register_fail:
	put_disk(simpleblkdrv_disk);
alloc_disk_fail:
	;
	return retval;
}
static void __exit simpleblkdrv_cleanup(void)
{
	del_gendisk(simpleblkdrv_disk);
	put_disk(simpleblkdrv_disk);
	blk_cleanup_queue(simpleblkdrv_queue);
	unregister_blkdev(simpleblkdrv_MAJOR,DISK_NAME);
}
//module_init???
