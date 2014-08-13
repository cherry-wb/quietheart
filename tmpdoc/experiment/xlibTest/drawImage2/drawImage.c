/*本程序功能：尝试在窗口中绘制多种格式的图片。
 *目前支持的图片格式:
 * */

/*据说：http://www.linuxsir.org/bbs/showthread.php?t=274181
 * 假设有个test.bmp文件，我们可以用convert test.bmp test.xpm把它转换为xpm文件，因为Xlib默认支持的文件格式只有xpm所以我们只能这样做?*/
/*安装imagemagick软件包，其中的convert命令十分强大，可以把任意格式的图片文件转换为xpm文件格式。
 * 假设有个test.bmp文件，我们可以用convert test.bmp test.xpm把它转换为xpm文件，因为Xlib默认支持的文件格式只有xpm所以我们只能这样做。得到的test.xpm实际是个文本文件，定义了的是一个字符串指针数组。
 * 因为Xlib没有提供可以直接存取xpm文件的函数，所以我们还需要安装两个软件包libxpm4以及libxpm-dev。
 * gcc xpmtest1.c -o xpmtest -lX11 -lXpm
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>
/* BitmapOpenFailed, etc. */
#include <X11/Xutil.h>		
#include <X11/xpm.h>

#include "icon.xpm"
/*创建一个窗口*/
Window
create_simple_window(Display* display, int width, int height, int x, int y);

/*创建窗口的图形上下文*/
GC
create_gc(Display* display, Window win);
int main(int argc, char *argv[])
{
	Display* display;
	int screen_num;
	Window win;
	unsigned int display_width,
				 display_height;
	unsigned int win_width,
				 win_height;
	char *display_name = getenv("DISPLAY"); 

	/*用于绘制的图形环境*/
	GC gc;			

	/*不同xlib函数的返回值,应该就是一个整数*/
	/*int rc;*/
	Status rc;			
	Pixmap bitmap;
	XpmAttributes xpmattr;
	unsigned int bitmap_width, bitmap_height;
	//int hotspot_x, hotspot_y;
	int i,j;


	display = XOpenDisplay(display_name);
	if (display == NULL)
	{
		fprintf(stderr, "%s: cannot connect to X server '%s'\n",
				argv[0], display_name);
		exit(1);
	}

	/******窗口的创建******/
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);
	win_width = (display_width / 3);
	win_height = (display_height / 3);
	win = create_simple_window(display, win_width, win_height, 0, 0);

	/******图形上下文的创建******/
	gc = create_gc(display, win);

	/*这个函数刷新所有的输出缓存直至所有事件被Xserver收到并处理。
	 *输入参数为False将会不会忽略所有排队事件，
	 如果为True则忽略所有事件包括该函数调用之前的排队事件。
	 * */
	XSync(display, False);

	/******在这里开始绘图******/

	/*rc = XReadBitmapFile(display, win,
			"icon.bmp",
			&bitmap_width, &bitmap_height,
			&bitmap,
			&hotspot_x, &hotspot_y);*/
	char *s[]={"icon"};

	//rc = XpmCreatePixmapFromData(display, win, s, &bitmap, NULL, &xpmattr);
	rc = XpmCreatePixmapFromData(display, win, icon, &bitmap, NULL, &xpmattr);
	bitmap_width = xpmattr.width;
	bitmap_height = xpmattr.height;
	/*xpm格式的文件无法读取*/
	/*rc = XReadBitmapFile(display, win,
			"home.xpm",
			&bitmap_width, &bitmap_height,
			&bitmap,
			&hotspot_x, &hotspot_y);*/
	switch (rc)
	{
		case BitmapOpenFailed:
			fprintf(stderr, "XReadBitmapFile - could not open file 'icon.bmp'.\n");
			exit(1);
			break;
		case BitmapFileInvalid:
			fprintf(stderr,
					"XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n",
					"icon.bmp");
			exit(1);
			break;
		case BitmapNoMemory:
			fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
			exit(1);
			break;
	}
	XCopyArea(display, bitmap, win, gc, 0, 0, xpmattr.width, xpmattr.height, 0, 0); 

//处理事件
/*	XSelectInput(display, win, ExposureMask | KeyReleaseMask);
	XEvent an_event;
	while(1)
	{
		XNextEvent(display, &an_event);
		switch( an_event.type)
		{
			case Expose:
				if( an_event.xexpose.count > 0)
					break;
				XCopyArea(display, bitmap, win, gc, 0, 0, xpmattr.width, xpmattr.height, 0, 0);
				break;
			case KeyRelease:
				printf("keycode %d\n", an_event.xkey.keycode);
				printf("keystate %d\n",an_event.xkey.state);
				break;				
			default:
				break;
		}
	}	
*/
	{

		for(i=0; i<6; i++)
		{
			for(j=0; j<6; j++)
			{
				/*这里在指定的window上面绘制图片
				 * bitmap指定绘制的源（矩形）
				 * win指定绘制的目标（矩形）
				 * gc
				 * （0,0）表示相对于源的左上角坐标
				 * (bitmap_width,bitmap_height)表示绘制的大小
				 * (j*bitmap_width,i*bitmap_height)表示相对于目标的左上角坐标
				 * 和色深相关，不太清楚。
				 * */
				XCopyPlane(display, bitmap, win, gc,
						0, 0,

						bitmap_width, bitmap_height,
						j*bitmap_width, i*bitmap_height,
						1);
				XSync(display, False);
				usleep(100000);
			}
		}
	}


	/*把所有的请求通知给X server*/
	XFlush(display);


	/******延迟5秒后释放资源，结束程序******/
	sleep(10);
	XFreePixmap(display, bitmap);
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
	 *窗口的前景色为白
	 *窗口的背景色为黑
	 * */
	win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
			x, y, width, height, win_border_width,
			WhitePixel(display, screen_num),
			BlackPixel(display, screen_num));

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

	GC
create_gc(Display* display, Window win)
{/*创建一个窗口的图形上下文*/
	GC gc;				

	/*gc的初始值*/
	XGCValues values;			
	/*代表前面的values中的哪些成员被检测*/
	unsigned long valuemask = 0;		
	/*代表默认屏幕号*/
	int screen_num = DefaultScreen(display);

	/******创建图形对象******/
	/*创建图形上下文并返回,返回的gc可以被具有同样根和深度的指定窗口使用，否则出错。
	 *display代表一个Xserver连接
	 *win代表绘制的窗口
	 *这里是通过valuemask,通过按位或指定设置gc的哪些子部件，即values的哪些成员。
	 例如其值可以为GCLineWidth(一个宏定义，值为(1L<<4))
	 *values指定为valuemask设置的值,例如其成员有int line_width;
	 *
	 * */
	gc = XCreateGC(display, win, valuemask, &values);
	if (gc < 0)
	{
		fprintf(stderr, "XCreateGC: \n");
	}

	/*****设置图形上下文的各种属性*****/
	/*设置前景色和背景色*/
	XSetForeground(display, gc, WhitePixel(display, screen_num));
	XSetBackground(display, gc, BlackPixel(display, screen_num));

	/*设置在gc上面绘制的线的风格*/
	XSetLineAttributes(display, gc,
			2, LineSolid, CapButt, JoinBevel);

	/*设置填充类型为FillSolid*/
	XSetFillStyle(display, gc, FillSolid);

	return gc;
}
