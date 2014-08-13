/*本程序功能：
 * 使用比较标准的方法，利用xlib创建一个最简单的窗口
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>

Window
create_simple_window(Display* display, int width, int height, int x, int y);

int main(int argc, char *argv[])
{
	/*X display结构的指针*/
	Display* display;

	/*窗口放置的屏幕的编号*/
	int screen_num;

	/*新创建的窗口指针？*/
	Window win;

	/*显示的高度和宽度*/
	unsigned int display_width,
				 display_height;

	/*窗口的高度和宽度*/
	unsigned int win_width,
				 win_height;

	/*X display的显示地址*/
	char *display_name = getenv("DISPLAY"); 

	/*根据指定的地址打开xserver连接，简化的可以设置参数display_name为NULL*/
	display = XOpenDisplay(display_name);
	if (display == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server '%s'\n",
				argv[0], display_name);
		exit(1);
	}

	/*获得我们的display的默认屏幕的大小*/
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);

	/*让我们的窗口占据屏幕1/9的大小*/
	win_width = (display_width / 3);
	win_height = (display_height / 3);

	/*这里根据前面的设置，开始创建窗口!!*/
	win = create_simple_window(display, win_width, win_height, 0, 0);

	sleep(5);
	/*关闭到Xserver的连接*/
	XCloseDisplay(display);
	return 0;
}
Window
create_simple_window(Display* display, int width, int height, int x, int y)
{/*创建一个简单的窗口*/

/*获得屏幕号码*/
  int screen_num = DefaultScreen(display);

/*窗口边缘宽度*/
  int win_border_width = 2;

  Window win;

  /*创建一个简单的窗口作为屏幕上根窗口的直接孩子。参数意义依次如下：
   *所在的显示是哪个
   *该显示号和屏幕号下的根窗口作为父窗口
   *窗口的x坐标
   *窗口的y坐标
   *窗口的宽度
   *窗口的高度
   *窗口的边缘像素宽度
   *窗口的前景色为黑
   *窗口的背景色为白
   * */
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));

  /*如果这样创建那么我们将会看到一个黑色的窗口*/
  /*win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            WhitePixel(display, screen_num),
                            BlackPixel(display, screen_num));*/

  /*没有这个调用也能创建窗口，这个是什么作用？？？
   *设置指定窗口的WM_TRANSIENT_FOR属性为RootWindow(display, screen_num)？？
   *WM_TRANSIENT_FOR属性由程序来设置，用于告诉窗口管理器是一个短暂的top-level窗口
   * */
  XSetTransientForHint(display, win, RootWindow(display, screen_num));

  /* make the window actually appear on the screen. */
  /*这句话使窗口出现在屏幕上*/
  XMapWindow(display, win);

  /* flush all pending requests to the X server. */
  /*把所有的请求提交给X server,如果没有这句话，那么窗口也不会被显示出来的*/
  XFlush(display);

  return win;
}
