#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
//#include <asm/page.h>
#include <linux/fb.h>
#include "myFbUtil.h"

//can change here for other bits_per_pixel
#define MY_SUPPORT_PIXEL_BIT 16

struct MyFb* initFb(const char *fname)
{
	//open framebuffer file
	struct MyFb *fbTest = malloc(sizeof(struct MyFb));
	if(fbTest == NULL)
	{
		printf("Error:malloc for fbTest failed!\n");
	}
    memset(fbTest, 0, sizeof(struct MyFb));
    fbTest->fb = open(fname, O_RDWR);
    if(fbTest->fb < 0)
    {
        printf("Error opening %s,Check kernel config\n",fname);
        return NULL;
    }

	//get information of frame buffer
    if(-1 == ioctl(fbTest->fb,FBIOGET_VSCREENINFO,&(fbTest->fb_var)))
    {
        printf("Error:ioctl FBIOGET_VSCREENINFO\n");
        return NULL;
    }
    if (-1 == ioctl(fbTest->fb,FBIOGET_FSCREENINFO,&(fbTest->fb_fix)))
    {
        printf("Error:ioctl FBIOGET_FSCREENINFO\n");
        return NULL;
    }

    //map physics address to virtual address
	//fb_fix.smem_start:Start of frame buffer mem
	fbTest->fb_mem_offset=(unsigned long)(fbTest->fb_fix.smem_start)
							&(~(sysconf(_SC_PAGE_SIZE) - 1));
	fbTest->fb_realMapLen = fbTest->fb_fix.smem_len + fbTest->fb_fix.smem_start
							-fbTest->fb_mem_offset;
    fbTest->fb_mem = mmap(NULL, fbTest->fb_realMapLen, PROT_READ | PROT_WRITE, 
						MAP_SHARED, fbTest->fb, 0);
    if (-1L == (long)fbTest->fb_mem)
    {
        printf("mmap error! mem:%ld offset:%x\n",fbTest->fb_mem,fbTest->fb_mem_offset);
        return NULL;
    }
	return fbTest;
}
int printFbInfo(struct MyFb* fbTest)
{
	///////print info
    printf("depth(bits per pixel) = %d\n",fbTest->fb_var.bits_per_pixel);
	//visible resolution,virtual resolution
    printf("xres= %d,yres = %d,xres_virtual = %d,yres_virtual = %d\n",
			fbTest->fb_var.xres,fbTest->fb_var.yres,
			fbTest->fb_var.xres_virtual,fbTest->fb_var.yres_virtual);
	//offset from virtual to visible resolution
	printf(" xoffset = %d, yoffset = %d, grayscale = %d\n",
			fbTest->fb_var.xoffset,fbTest->fb_var.yoffset,fbTest->fb_var.grayscale);
	//height,width of picture in mm
	printf(" height = %d , width = %d ,activate = %d \n",
			fbTest->fb_var.height,fbTest->fb_var.width,fbTest->fb_var.activate);
	//pixel clock in ps (pico seconds)
	printf(" pixclock = %d, l_margin = %d, r_margin = %d, u_margin = %d, d_margin = %d\n",
			fbTest->fb_var.pixclock,fbTest->fb_var.left_margin,fbTest->fb_var.right_margin,
			fbTest->fb_var.upper_margin,fbTest->fb_var.lower_margin);
	//length of horizontal,vertical sync
	printf(" hsync_len = %d, vsync_len = %d , sync = %d, vmode = %d\n",
			fbTest->fb_var.hsync_len,fbTest->fb_var.vsync_len,
			fbTest->fb_var.sync,fbTest->fb_var.vmode);
	//Length of frame buffer mem
	printf("smemlen = %d\n",fbTest->fb_fix.smem_len);
	//length of a line in bytes
    printf("fix_line(in byte) = %d\n",fbTest->fb_fix.line_length);

	//parameters about colors
	printf("red offset:%d\n",fbTest->fb_var.red.offset);
	printf("red len:%d\n",fbTest->fb_var.red.length);
	printf("green offset:%d\n",fbTest->fb_var.green.offset);
	printf("green len:%d\n",fbTest->fb_var.green.length);
	printf("blue offset:%d\n",fbTest->fb_var.blue.offset);
	printf("blue len:%d\n",fbTest->fb_var.blue.length);

	return 0;
}
int drawDot(struct MyFb *fbTest, uint32_t x, uint32_t y, float r, float g, float b)
{
    if (-1L == (long)fbTest->fb_mem)
    {
        printf("mmap error! mem:%x offset:%x\n", fbTest->fb_mem, fbTest->fb_mem_offset);
        return -1;
    }
	if(r > 1.0 || g > 1.0 || b > 1.0)
	{
		printf("Color range error!r,g,b range:[0,1.0]\n");
		return -1;
	}
	if(MY_SUPPORT_PIXEL_BIT == fbTest->fb_var.bits_per_pixel)
	{//only support 16bits per pixel,can change here for other bits_per_pixel
		//关于行和列，
		//由于内存线性排列，第y行的第一个像素是y*fb_fix.line_length
		//由于像素是fb_var.bits_per_pixel>>3字节，所以第x列为...+x*(fb_var.bits_per_pixel>>3)
		unsigned int offset;
		offset = y*fbTest->fb_fix.line_length+x*(fbTest->fb_var.bits_per_pixel>>3);
		uint16_t value = 0;//change the type here for other bits

		//////color values
		//red = ((1<<fbTest->fb_var.red.length)-1) << fbTest->fb_var.red.offset;
		//green = ((1<<fbTest->fb_var.green.length)-1) << fbTest->fb_var.green.offset;
		//blue = ((1<<fbTest->fb_var.bule.length)-1) << fbTest->fb_var.blue.offset;
		value=((uint16_t)(((1<<fbTest->fb_var.red.length)-1)*r))<<fbTest->fb_var.red.offset
			|((uint16_t)(((1<<fbTest->fb_var.green.length)-1)*g))<<fbTest->fb_var.green.offset
			|((uint16_t)(((1<<fbTest->fb_var.blue.length)-1)*b))<<fbTest->fb_var.blue.offset;
		uint16_t *pv = &value;
		memcpy((void*)((unsigned long)fbTest->fb_mem + offset), pv, 2);
	}
	else
	{
        printf("Only %dbits per pixel supported!!!\n",MY_SUPPORT_PIXEL_BIT);
		return -1;
	}
}
int releaseFb(struct MyFb* fbTest)
{
    close(fbTest->fb);
	munmap(fbTest->fb_mem,fbTest->fb_realMapLen);
	free(fbTest);
}
