/*本程序功能：
 * 实现各种简单的窗口操作：
 * 隐藏，显示，移动，设置大小，置栈底，置栈顶，图标化，取消图标化（显示）
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>

Window
create_simple_window(Display* display, int width, int height, int x, int y);

int main(int argc, char *argv[])
{
	/*相关定义*/
	Display* display;
	int screen_num;
	Window win;
	unsigned int display_width,
				 display_height;
	unsigned int win_width,
				 win_height;

	/*动态改变的窗口宽度(w),和位置(x)*/
	int w = 300;
	int x = 500;

	/*初始化变量*/
	char *display_name = getenv("DISPLAY"); 
	display = XOpenDisplay(display_name);//打开显示
	if (display == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server '%s'\n",
				argv[0], display_name);
		exit(1);
	}

	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);
	win_width = (display_width / 3);
	win_height = (display_height / 3);

	/*创建窗口*/
	win = create_simple_window(display, win_width, win_height, 0, 0);

	/*不显示,这样任务栏底部的图标按钮也会消失*/
	sleep(2);
	printf("XUnMapWindow:\n");
	XUnmapWindow(display, win);
	XFlush(display);

	/*显示*/
	sleep(2);
	printf("XMapWindow:\n");
	XMapWindow(display, win);
	XFlush(display);

	/*移动1*/
	sleep(2);
	printf("move to 400,100:\n");
	XMoveWindow(display, win, 400, 100);
	XFlush(display);

	/*移动2*/
	sleep(2);
	printf("move to 500,200:\n");
	XMoveWindow(display, win, 500, 200);
	XFlush(display);

	/*移动3*/
	while(x > 400)
	{
		usleep(500000);
		printf("move:\n");
		XMoveWindow(display, win, x, x-300);
		x-=20;
		XFlush(display);
	}

	/*重设大小1*/
	sleep(2);
	printf("resize to 200,300:\n");
	XResizeWindow(display, win, 200, 300);
	XFlush(display);

	/*重设大小2*/
	while(w < 600)
	{
		usleep(500000);
		printf("resize:\n");
		XResizeWindow(display, win, w, 500);
		w+=50;
		XFlush(display);
	}

	/*窗口置栈底*/
	sleep(2);
	printf("Lower:\n");
	XLowerWindow(display, win);
	XFlush(display);
	
	/*窗口置栈顶*/
	sleep(2);
	printf("Raise:\n");
	XRaiseWindow(display, win);
	XFlush(display);

	/*图标化窗口(最小化)*/
	sleep(2);
	printf("Iconify:\n");
	XIconifyWindow(display, win, DefaultScreen(display));
	XFlush(display);

	/*图标化窗口(最小化)*/
	sleep(2);
	printf("Cancel Iconify(XMapWindow):\n");
	XMapWindow(display, win);
	XFlush(display);


	sleep(5);
	XCloseDisplay(display);
	printf("bye!\n");

	return 0;
}
Window
create_simple_window(Display* display, int width, int height, int x, int y)
{
  int screen_num = DefaultScreen(display);
  int win_border_width = 2;
  Window win;
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));
  XSetTransientForHint(display, win, RootWindow(display, screen_num));
  XMapWindow(display, win);
  XFlush(display);
  return win;
}
