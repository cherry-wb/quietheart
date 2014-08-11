/*本程序功能：
 * 使用比较标准的方法，利用xlib创建一个最简单的窗口
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*创建一个窗口的函数*/
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

	/*根据指定的地址打开显示，简化的可以设置参数display_name为NULL*/
	display = XOpenDisplay(display_name);
	if (display == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server '%s'\n",
				argv[0], display_name);
		exit(1);
	}

	/********************创建一个窗口*****************/
	/*获得我们的display的默认屏幕的大小*/
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);

	/*让我们的窗口占据屏幕1/9的大小*/
	win_width = (display_width / 3);
	win_height = (display_height / 3);

	/*这里根据前面的设置，开始创建窗口!!*/
	win = create_simple_window(display, win_width, win_height, 0, 0);
	/*************************************************/

	/******************这里开始设置窗口的常用属性*****/
	/*这个变量存放窗口的名字属性,实际这是一个X格式的字符串,由c串转换，见后*/
	XTextProperty window_name_property;

	/*这个变量存放窗口的图标名字属性,实际这是一个X格式的字符串,由c串转换，见后*/
    XTextProperty icon_name_property;

	/*关于窗口大小的属性变量*/
    XSizeHints* win_size_hints;

	/*这个变量用于设置窗口的其他杂乱属性*/
    XWMHints* win_hints;

	/*用于存放图标的图像*/
    Pixmap icon_pixmap;

    /*窗口标题和窗口图标标题 */
    char* window_name = "hello, world";//例如窗口的标题
    char* icon_name = "small world";//例如任务栏上面的标题

	/*把窗口标题转换为X格式的字符串，这样才能处理*/
    int rc = XStringListToTextProperty(&window_name,
                                       1,
                                       &window_name_property);
    if (rc == 0)
	{
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }

	/*把窗口图标标题转换为X格式的字符串，这样才能处理*/
    rc = XStringListToTextProperty(&icon_name,
                                   1,
                                   &icon_name_property);
    if (rc == 0)
	{
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }
	/*=======设置窗口标题和图标标题=======*/
	XSetWMName(display, win, &window_name_property);
    XSetWMIconName(display, win, &icon_name_property);

	/*=======设置窗口的大小=======*/
    win_size_hints = XAllocSizeHints();
    if (!win_size_hints)
	{
        fprintf(stderr, "XAllocSizeHints - out of memory\n");
        exit(1);
    }
	/*初始化结构变量，首先指定我们想要填充那种大小标志
	 *在这里，我们填充的是最小大小和初始大小
	 * */
    win_size_hints->flags = PSize | PMinSize;

	/*然后指定限制，
	 *这里，令窗口最小大小是300x200像素，初始大小400x250像素
	 * */
    win_size_hints->min_width = 300;
    win_size_hints->min_height = 200;
    win_size_hints->base_width = 400;
    win_size_hints->base_height = 250;

	/***指定之后设置窗口大小***/
    XSetWMNormalHints(display, win, win_size_hints);

    /*设置完毕可以释放资源*/
    XFree(win_size_hints);

	/*=======设置其他属性，这里省略=======*/
	//win_hints = XAllocWMHints();
	/*...这里应该指定各种属性值...*/
    //XSetWMHints(display, win, win_hints);
    //XFree(win_hints);
	/*************************************************/

	XFlush(display);
	sleep(25);
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

  /*
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
