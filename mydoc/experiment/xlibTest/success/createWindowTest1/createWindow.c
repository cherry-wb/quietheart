/*本程序功能：
 * 1）利用xlib创建一个最简单的窗口，后面会创建一个稍微复杂的window，
 * 2）3秒钟之后该窗口置底,
 * 3）再过3秒该窗口置顶,
 * 4）再过3秒程序结束。
 * */
#include <stdio.h>

/*exit*/
#include <stdlib.h>

#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
	Display *dpy;
	Window win;
	int win_x = 200;
	int win_y = 100;
	int win_width = 50;
	int win_height = 30;
	int win_border_width = 0;
	int screen_num;

	/*打开到Xserver的连接*/
	if((dpy = XOpenDisplay(NULL)) == NULL)
	{
		/*注意用可以这个函数进行错误输出!!*/
		perror("XOpenDisplay can't connect to X server\n");
		exit(1);
	}

	/*获得默认屏幕号*/
	screen_num = DefaultScreen(dpy);

	/*创建一个窗口*/
//	win = XCreateSimpleWindow(dpy,
//			DefaultRootWindow(dpy),/*父窗口是默认的根窗口*/
//			win_x/*坐标为什么没有作用？*/,
//			win_y,
//			win_width,
//			win_height,
//			win_border_width,/*窗口边缘的像素宽度*/
//			BlackPixel(dpy, screen_num),/*窗口背景像素值?有时候为简化指定为0*/
//			WhitePixel(dpy, screen_num)/*窗口边缘像素值?有时候为简化指定为0*/);

	win = XCreateSimpleWindow(dpy,
			DefaultRootWindow(dpy),/*父窗口是默认的根窗口*/
			0,/*横坐标*/
			0,/*纵坐标*/
			win_width,
			win_height,
			0,/*窗口边缘的像素宽度*/
			0,/*窗口背景像素值*/
			0/*窗口边缘像素值*/);

	/*使窗口出现在屏幕上*/
	XMapWindow(dpy, win);

	/*把所有到Xserver的请求flush,如果没有这句话，那么窗口不会显示出来*/
	XFlush(dpy);

	/*下面对这个窗口进行简单的操作，5秒钟置底，5秒钟又置顶，最后退出*/
	sleep(3);
	XLowerWindow(dpy, win);
	XFlush(dpy);/*没有这句话也无法实现置底*/
	sleep(3);
	XRaiseWindow(dpy, win);
	XFlush(dpy);
	sleep(3);
	XCloseDisplay(display);
	return 0;
}
