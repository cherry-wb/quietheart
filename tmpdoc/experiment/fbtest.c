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
#define TRUE 1
#define FALSE 2
#define PAGE_MASK 0XFFFFF000
#define FBIO_AUO_UPDATE_DISPLAY_PARTIAL             _IOW('F', 101, update_area_t *)
typedef struct _update_area_t update_area_t;
struct _update_area_t
{
	int flashbit;       // 1: draw black color; 0: draw white color
	int mode;
	int x;
	int y;
	int w;
	int l;
	unsigned short *buffer;
	unsigned int set_handwriting_area;  // 1: enable handwriting area 0: disable handwriting area
	unsigned int flag_for_ap;   // for application testing
}info;

//a framebuffer device structure;

typedef struct fbdev{
    int fb;
    unsigned long fb_mem_offset;
    unsigned long fb_mem;
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
    char dev[20];
} FBDEV, *PFBDEV;

int fb_open(PFBDEV pFbdev)
{
    pFbdev->fb = open(pFbdev->dev, O_RDWR);
    if(pFbdev->fb < 0)
    {
        printf("Error opening %s: %m. Check kernel config\n", pFbdev->dev);
        return FALSE;
    }
    if (-1 == ioctl(pFbdev->fb,FBIOGET_VSCREENINFO,&(pFbdev->fb_var)))
    {
        printf("ioctl FBIOGET_VSCREENINFO\n");
        return FALSE;
    }
    if (-1 == ioctl(pFbdev->fb,FBIOGET_FSCREENINFO,&(pFbdev->fb_fix)))
    {
        printf("ioctl FBIOGET_FSCREENINFO\n");
        return FALSE;
    }

    //map physics address to virtual address

    pFbdev->fb_mem_offset = (unsigned long)(pFbdev->fb_fix.smem_start) & (~PAGE_MASK);
    pFbdev->fb_mem = (unsigned long int)mmap(NULL, pFbdev->fb_fix.smem_len +
            pFbdev->fb_mem_offset,
            PROT_READ | PROT_WRITE, MAP_SHARED, pFbdev->fb, 0);
    if (-1L == (long) pFbdev->fb_mem)
    {
        printf("mmap error! mem:%ld offset:%ld\n", pFbdev->fb_mem,
                pFbdev->fb_mem_offset);
        return FALSE;
    }

    return TRUE;
}

void fb_close(PFBDEV pFbdev)
{
    close(pFbdev->fb);
    pFbdev->fb=-1;
}

void fb_memset (void *addr, int c, size_t len)
{
    memset(addr, c, len);
}

void draw_dot (PFBDEV pFbdev, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned int offset;
    if (-1L == (long) pFbdev->fb_mem)
    {
        printf("mmap error! mem:%ld offset:%ld\n", pFbdev->fb_mem,
                pFbdev->fb_mem_offset);
        return;
    }
//    offset = y*pFbdev->fb_fix.line_length+4*x;

    offset = y*pFbdev->fb_fix.line_length+2*x;
    fb_memset((void*)(pFbdev->fb_mem + pFbdev->fb_mem_offset + offset), b, 1);
    fb_memset((void*)(pFbdev->fb_mem + pFbdev->fb_mem_offset + offset + 1), g, 1);
//    fb_memset((void*)(pFbdev->fb_mem + pFbdev->fb_mem_offset + offset + 2), r, 1);

//    fb_memset((void*)(pFbdev->fb_mem + pFbdev->fb_mem_offset + offset + 3), 0x00, 1);

}


int main(void)
{
    FBDEV fb;
    memset(&fb, 0, sizeof(FBDEV));
    strcpy(fb.dev, "/dev/fb0");
    if(fb_open(&fb)==FALSE)
    {
        printf("open frame buffer error\n");
        return 0;
    }

    printf("depth(bits per pixel) = %d\n",fb.fb_var.bits_per_pixel);
    printf("xres= %d,yres = %d,xres_virtual = %d,yres_virtual = %d\n",fb.fb_var.xres,fb.fb_var.yres,fb.fb_var.xres_virtual,fb.fb_var.yres_virtual);

	printf(" xoffset = %d, yoffset = %d, grayscale = %d\n",fb.fb_var.xoffset,fb.fb_var.yoffset,fb.fb_var.grayscale);
	printf(" height = %d , width = %d ,activate = %d \n",fb.fb_var.height,fb.fb_var.width,fb.fb_var.activate);
	printf(" pixclock = %d, left_margin = %d, right_margin = %d, upper_margin = %d, lower_margin = %d\n",fb.fb_var.pixclock,fb.fb_var.left_margin,fb.fb_var.right_margin,fb.fb_var.upper_margin,fb.fb_var.lower_margin);
	printf(" hsync_len = %d, vsync_len = %d , sync = %d, vmode = %d\n",fb.fb_var.hsync_len,fb.fb_var.vsync_len,fb.fb_var.sync,fb.fb_var.vmode);

	printf("smemlen = %d\n",fb.fb_fix.smem_len);
    printf("fix_line(in byte) = %d\n",fb.fb_fix.line_length);

    int i,j;
    for(i=0; i<80; ++i)
        for(j = 0;j<80;++j)
        {
            draw_dot(&fb,i,j,0xff,0,0x0);
        }
    for(i=80; i<160; ++i)
        for(j = 0;j<80;++j)
        {
            draw_dot(&fb,i,j,0,0xff,0x0);
        }
    for(i=160; i<240; ++i)
        for(j = 0;j<80;++j)
        {
            draw_dot(&fb,i,j,0,0,0xff);
        }	
/*
//    update_area_t info;
	memset(&info, 0, sizeof(update_area_t));
	info.mode = 0;
	info.x = 0;
	info.y = 0;
	info.w = 480;
	info.l = 480;
	ioctl(&fb, FBIO_AUO_UPDATE_DISPLAY_PARTIAL, &info);
*/

    fb_close(&fb);
    return 0;
}

