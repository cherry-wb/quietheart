/*程序功能：
 * 使用framebuffer向屏幕上面绘制颜色块。
 * 具体为：
 * 在屏幕的指定区域，绘制红，绿，蓝三种方形颜色块。
 *目前的问题：
 绘制颜色(ok).
 如何正确的映射内存?
 *
 * 一个例子输出：
 * # ./fbColor 
 * depth(bits per pixel) = 16
 * xres= 1024,yres = 600,xres_virtual = 1024,yres_virtual = 600
 * xoffset = 0, yoffset = 0, grayscale = 0
 * height = 0 , width = 0 ,activate = 0 
 * pixclock = 14800, l_margin = 96, r_margin = 48, u_margin = 16, d_margin = 3
 * hsync_len = 32, vsync_len = 6 , sync = 3, vmode = 0
 * smemlen = 1228800
 * fix_line(in byte) = 2048
 * !!!!!fb mem:40000000,mmstart:0
 * fb_fix.smem_start:e8000000
 * 0,e8000000
 *此程序在arm平台下面测试过。
 * */

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

#define FB_DEV "/dev/fb0"
#define PAGE_MASK 0XFFFFF000//why?
#define TRUE 1
#define FALSE 2
#define MY_DEBUG 1

//color geometry
#define COLOR_WIDTH 80
#define R_START 0
#define G_START ((R_START)+(COLOR_WIDTH))
#define B_START ((G_START)+(COLOR_WIDTH))

//red offset is 11
//green offset is 5
//blue offset is 0
#define PIX_BIT 16
#define RED_OFF 11
#define RED_LEN 5
#define GREEN_OFF 5
#define GREEN_LEN 6
#define BLUE_OFF 0
#define BLUE_LEN 5
#define RED (((1<<RED_LEN)-1) << (RED_OFF))
#define GREEN (((1<<GREEN_LEN)-1) << (GREEN_OFF))
#define BLUE (((1<<BLUE_LEN)-1) << (BLUE_OFF))

//假设一个像素16bit,rgb是565的。
//正常来说：红绿蓝
//0xf800,0x07e0,0x0011
//这里：
//red offset:11,length:5
//green offset:5,length:6
//blue offset:0,length:5

static struct fb_fix_screeninfo fb_fix;
static struct fb_var_screeninfo fb_var;
static unsigned long fb_mem_offset;
static unsigned long fb_mem_offset2;
static void *fb_mem;
static int fb;

void draw_dot(uint32_t x, uint32_t y)
{
    if (-1L == (long)fb_mem)
    {
        printf("mmap error! mem:%x offset:%x\n", fb_mem, fb_mem_offset);
        return;
    }
	//关于行和列，
	//由于内存线性排列，第y行的第一个像素是y*fb_fix.line_length
	//由于像素是fb_var.bits_per_pixel>>3字节，所以第x列为...+x*(fb_var.bits_per_pixel>>3)
    unsigned int offset;
    offset = y*fb_fix.line_length+x*(fb_var.bits_per_pixel>>3);
    //offset = y*fb_fix.line_length+2*x;

	uint16_t value = 0;
	if(x < G_START)
	{
		value = RED;
	}
	else if(x< B_START)
	{
		value = GREEN;
	}
	else
	{
		value = BLUE;
	}
	uint16_t *pv = &value;
    memcpy((void*)((unsigned long)fb_mem + offset), pv, 2);
	
	//wrong
    //memset((void*)((unsigned long)fb_mem + offset), RED, fb_var.bits_per_pixel>>3);
    //memset((void*)((unsigned long)fb_mem + offset), GREEN, fb_var.bits_per_pixel>>3);
    //memset((void*)((unsigned long)fb_mem + offset), BLUE, fb_var.bits_per_pixel>>3);

	//wrong but don't know why?
    //memset((void*)((unsigned long)fb_mem + offset), RED>>2, 1);
    //memset((void*)((unsigned long)fb_mem + offset+1), RED, 1);
}
int main(int argc, char *argv[])
{
	printf("unsigned short len:%d\n",sizeof(unsigned short));
	printf("uint16_t len:%d\n",sizeof(uint16_t));
	//////1)intialize frame buffer
    memset(&fb_fix, 0, sizeof(struct fb_fix_screeninfo));
    memset(&fb_var, 0, sizeof(struct fb_var_screeninfo));
    memset(&fb_var, 0, sizeof(struct fb_var_screeninfo));
	
    fb_mem_offset = 0;
    fb_mem = 0;

	//open frame buffer file
    int fb = open(FB_DEV, O_RDWR);
    if(fb < 0)
    {
        printf("Error opening %s,Check kernel config\n",FB_DEV);
        return FALSE;
    }

	//////2)get information of frame buffer
    if(-1 == ioctl(fb,FBIOGET_VSCREENINFO,&(fb_var)))
    {
        printf("Error:ioctl FBIOGET_VSCREENINFO\n");
        return FALSE;
    }
    if (-1 == ioctl(fb,FBIOGET_FSCREENINFO,&(fb_fix)))
    {
        printf("Error:ioctl FBIOGET_FSCREENINFO\n");
        return FALSE;
    }
	
    //////3)map physics address to virtual address
	//fb_fix.smem_start:Start of frame buffer mem
    fb_mem_offset = (unsigned long)(fb_fix.smem_start) & (~PAGE_MASK);//why?
	//unsigned long fb_realMapLen = fb_fix.smem_len + fb_mem_offset;

	fb_mem_offset2= (unsigned long)(fb_fix.smem_start)&(~(sysconf(_SC_PAGE_SIZE) - 1));
	size_t fb_realMapLen = fb_fix.smem_len+fb_fix.smem_start -  fb_mem_offset2;


    fb_mem = mmap(NULL, fb_realMapLen,
            PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
    if (-1L == (long)fb_mem)
    {
        printf("mmap error! mem:%ld offset:%x\n",fb_mem,
                fb_mem_offset);
        return FALSE;
    }

	///////4)print info
	//每个像素的字节数目
    printf("depth(bits per pixel) = %d\n",fb_var.bits_per_pixel);

	//(两种分辨率)visible resolution,virtual resolution
    printf("xres= %d,yres = %d,xres_virtual = %d,yres_virtual = %d\n",
			fb_var.xres,fb_var.yres,fb_var.xres_virtual,fb_var.yres_virtual);

	//(两种分辨率之间的映射偏移量)offset from virtual to visible resolution
	printf(" xoffset = %d, yoffset = %d, grayscale = %d\n",
			fb_var.xoffset,fb_var.yoffset,fb_var.grayscale);

	//framebuffer的内存大小Length of frame buffer mem
	printf("smemlen = %d\n",fb_fix.smem_len);

	//每"行"的字节数目.length of a line in bytes
    printf("fix_line(in byte) = %d\n",fb_fix.line_length);

	//height,width of picture in mm
	printf(" height = %d , width = %d ,activate = %d \n",
			fb_var.height,fb_var.width,fb_var.activate);

	//pixel clock in ps (pico seconds)
	printf(" pixclock = %d, l_margin = %d, r_margin = %d, u_margin = %d, d_margin = %d\n",
			fb_var.pixclock,fb_var.left_margin,fb_var.right_margin,
			fb_var.upper_margin,fb_var.lower_margin);
	//length of horizontal,vertical sync
	printf(" hsync_len = %d, vsync_len = %d , sync = %d, vmode = %d\n",
			fb_var.hsync_len,fb_var.vsync_len,fb_var.sync,fb_var.vmode);

#if MY_DEBUG == 1
	//////messy test
	//my test
	printf("!!!!!fb mem:%x,mmstart:%x\n",fb_mem,fb_fix.mmio_start);

	//my test for offset
	printf("fb_fix.smem_start:%x\n",fb_fix.smem_start);
	printf("%x,%x\n",fb_mem_offset,fb_mem_offset2);
	printf("red offset:%d\n",fb_var.red.offset);
	printf("red len:%d\n",fb_var.red.length);
	printf("green offset:%d\n",fb_var.green.offset);
	printf("green len:%d\n",fb_var.green.length);
	printf("blue offset:%d\n",fb_var.blue.offset);
	printf("blue len:%d\n",fb_var.blue.length);

	//my test for color
	printf("red:%x\n",RED);
	printf("green:%x\n",GREEN);
	printf("blue:%x\n",BLUE);

#endif

	//////5)draw color
    int i,j;
    for(i=R_START; i<R_START+COLOR_WIDTH; ++i)
	{
        for(j = 0;j<COLOR_WIDTH;++j)
        {
            draw_dot(i,j);//red,at (i,j)
        }
	}

    for(i=G_START; i<G_START+COLOR_WIDTH; ++i)
	{
        for(j = 0;j<COLOR_WIDTH;++j)
        {
            draw_dot(i,j);//green,at (i,j)
        }
	}

    for(i=B_START; i<B_START+COLOR_WIDTH; ++i)
	{
        for(j = 0;j<COLOR_WIDTH;++j)
        {
            draw_dot(i,j);//blue,at (i,j)
        }	
	}
    close(fb);
    fb=-1;
	munmap(fb_mem,fb_realMapLen);
	return 0;
}
