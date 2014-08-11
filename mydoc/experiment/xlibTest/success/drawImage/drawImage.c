/*本程序功能：在窗口中动态绘制多个图标,图标必须是bmp格式（非windows的）。
 * 这有两个获取图标方法：1）可以用函数从文件读取图标2）可以包含图标文件到程序中
 * bmp格式实际就是一个数组，和xpm格式又有所不同。
 * */

#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>
/* BitmapOpenFailed, etc. */
#include <X11/Xutil.h>		

/*如果用XCreateBitmapFromData则需要包含这个文件*/
//#include "icon.bmp"

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
	unsigned int bitmap_width, bitmap_height;
	int hotspot_x, hotspot_y;
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
	/*图形上下文环境，提供绘图环境包含前景色背景色线风格等各种属性*/
	gc = create_gc(display, win);

	/*这个函数刷新所有的输出缓存直至所有事件被Xserver收到并处理。
	 *输入参数为False将会不会忽略所有排队事件，
	 如果为True则忽略所有事件包括该函数调用之前的排队事件。
	 * */
	XSync(display, False);

	/******在这里开始绘图******/

	/*使用当前路径的icon.bmp文件，不是windows的bmp，它是个数组,和xpm格式也不同*/
	rc = XReadBitmapFile(display, win,
			"icon.bmp",
			&bitmap_width, &bitmap_height,
			&bitmap,
			&hotspot_x, &hotspot_y);

	/*xpm格式的文件无法读取*/
	/*rc = XReadBitmapFile(display, win,
	  "home.xpm",
	  &bitmap_width, &bitmap_height,
	  &bitmap,
	  &hotspot_x, &hotspot_y);*/
	/*如果读取文件错误的出错处理*/
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

	/*不用上面的方法，用下面的方法获得图片也行，这需要把icon.bmp包含成为头文件
	 * 这里面的icon_bitmap_bits就是这个icon.bmp对应的表示图像的数组
	 * 另外宽度和高度这里设成20，如果不是这个数，那么绘制出来的可能乱了*/
	/*bitmap_width  = 20;
	bitmap_height = 20;
	bitmap = XCreateBitmapFromData(display,
			                       win,
			                       icon_bitmap_bits,
			                       bitmap_width,
			                       bitmap_height);
	if (!bitmap)
	{
		    fprintf(stderr, "XCreateBitmapFromData - error creating pixmap\n");
		    exit(1);
	}
	*/


	/*这里绘制了36个图标*/
	for(i=0; i<6; i++)
	{
		for(j=0; j<6; j++)
		{
			/*这里在指定的window上面绘制图片，各个参数如下：
			 * bitmap指定绘制的源（矩形）
			 * win指定绘制的目标（矩形）
			 * gc图形上下文环境，提供绘图环境包含前景色背景色线风格等各种属性
			 * （0,0）表示相对于源的左上角坐标
			 * (bitmap_width,bitmap_height)表示绘制的大小
			 * (j*bitmap_width,i*bitmap_height)表示相对于目标的左上角坐标
			 * 1和色深位相关，不太清楚。
			 * */
			XCopyPlane(display, bitmap, win, gc,
					0, 0,
					bitmap_width, bitmap_height,
					j*bitmap_width, i*bitmap_height,
					1);
			/*刷新输出缓存直至所有的到X的请求被收到并处理
			 *这里如果传入参数False就不会忽略事件队列中的事件了*/
			XSync(display, False);//如果没有这句话不会动态一个个的绘制
			usleep(100000);
		}
	}


	 /*把所有的请求通知给X server,我尝试过了，不用这一句也行,因为前面有XSync*/
	 /*XFlush函数刷新输出缓存，由于输出缓存通过调用XPending,XNextEvent,XWinEvents
	 *根据需要会被自动刷新，大多数客户程序是不用调用它的。
	 *服务端发起的事件可能被放到库事件队列中的.
	 * */
	XFlush(display);


	/******延迟5秒后释放资源，结束程序******/
	sleep(10);
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
