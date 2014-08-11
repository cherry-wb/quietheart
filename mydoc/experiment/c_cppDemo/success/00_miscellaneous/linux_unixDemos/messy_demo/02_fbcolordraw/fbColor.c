/*程序功能：
 * 一个操作frame的工具,功能是：
 * 在指定的位置绘制指定颜色的点.
 * 结果是全屏幕绘制了颜色。
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
#include "myFbUtil.h"

#define FB_DEV "/dev/fb0"

int main(int argc, char *argv[])
{
	struct MyFb *fbTest = NULL;

	if(NULL == (fbTest = initFb(FB_DEV)))//to be improved
	{//init fail
		printf("Error:initialization failed!\n");
		exit(1);
	}
	printFbInfo(fbTest);

	int i,j;
	int width = fbTest->fb_var.xres;
	int height = fbTest->fb_var.yres;
	for(i = 0; i < width;++i)
	{
        for(j = 0;j<height;++j)
		{
			float r = 0;
			float g = 0;
			float b = 0;
			if(i < width / 3)
			{
				b = (float)j/height;//blue
			}
			else
			{
				b = 1.0;
				if(i < width - width / 3)
				{
					g = (float)j/height;//green
				}
				else
				{
					g = 1.0;
					if(i < width)
					{
						r = (float)j/height;//red
					}
				}
			}
			drawDot(fbTest,i,j,r,g,b);//draw red,green,blue at (i,j) on fbTest.
		}
	}
	releaseFb(fbTest);
}
