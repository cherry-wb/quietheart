/*本程序功能：
 * 利用各种颜色在窗口中绘制各种图形：点，线，弧形，连续线(多边形)，矩形等。
 * */
#include <stdio.h>

/*exit, getenv*/
#include <stdlib.h>

#include <X11/Xlib.h>

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
	
	/*用于分配各种颜色的颜色表，这个表的数目是有限的，超限则只能找个类似的颜色*/
	Colormap screen_colormap;     

	/*各种颜色*/
	XColor red, brown, blue, yellow, green;

	/*不同xlib函数的返回值*/
	Status rc;			


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
	
	/******颜色表的创建******/
	screen_colormap = DefaultColormap(display, DefaultScreen(display));


	/******各种颜色的创建******/
	/*根据名称创建颜色。
	 * "red"指定你要设置的颜色名。
	 *第一个&red表示硬件返回的屏幕支持的最接近的颜色值
	 *第二个&red表示精确的颜色值
	 *如果分配了颜色就返回非0，否则返回0。
	 * */
	rc = XAllocNamedColor(display, screen_colormap, "red", &red, &red);
	if (rc == 0)
	{
		fprintf(stderr, "XAllocNamedColor - failed to allocated 'red' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "brown", &brown, &brown);
	if (rc == 0)
	{
		fprintf(stderr, "XAllocNamedColor - failed to allocated 'brown' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue);
	if (rc == 0)
	{
		fprintf(stderr, "XAllocNamedColor - failed to allocated 'blue' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "yellow", &yellow, &yellow);
	if (rc == 0)
	{
		fprintf(stderr, "XAllocNamedColor - failed to allocated 'yellow' color.\n");
		exit(1);
	}

	green.red = 0;
	green.green = 30000;
	green.blue = 0;
	/*根据指定值分配颜色
	 *这是另外一种分配颜色的方法。
	 *&green就是你设置好的颜色。
	 函数返回与你指定的颜色最近到颜色到green中,这里主要是想要获得green的第一个成员，green变量有rgb三个成员，之前还有一个pixel成员表示从颜色表的哪里获得该颜色。
	 *rc表示，如果分配了一个颜色就返回非0，否则返回0。
	 * */
	rc = XAllocColor(display,
			screen_colormap,
			&green);
	if (rc == 0)
	{
		fprintf(stderr,
				"XAllocColor - color failed.\n");
	}

	/******利用前面设置的颜色绘制图形******/
	/*在窗口的每个拐角用红色绘制像素*/
	XSetForeground(display, gc, red.pixel);
	/*下面根据给定坐标绘制每个像素*/
	XDrawPoint(display, win, gc, 5, 5);
	XDrawPoint(display, win, gc, 5, win_height-5);
	XDrawPoint(display, win, gc, win_width-5, 5);
	XDrawPoint(display, win, gc, win_width-5, win_height-5);

	/*利用棕色绘制两个互相垂直的相交直线*/
	XSetForeground(display, gc, brown.pixel);
	/*根据指定的起点终点坐标绘制这两条直线*/
	XDrawLine(display, win, gc, 50, 0, 50, 200);
	XDrawLine(display, win, gc, 0, 100, 200, 100);

	/*利用蓝色绘制一个整弧（圆）
	 *圆心(50,100),参数坐标表示区域矩形左上角，所以参数为50-(30/2)和100-(30/2)
	 *30,30这两个参数表示宽和高(长轴和短轴)。
	 *起点度0( 位于圆心水平右边的位置），终点度（相对于起点的角度）.
	 *注意这里的度是每个单位有64个分格，所以乘以64.
	 * */
	XSetForeground(display, gc, blue.pixel);
	XDrawArc(display, win, gc, 50-(30/2), 100-(30/2), 30, 30, 0, 360*64);

	/*用黄色在窗口的左上角绘制连贯图形（三角型）
	 * XDrawLines的最后一个参数是整数参数int mode,取值可以如下：
	 *CoordModeOrigin表示所有的坐标都是相对原点的。
	 *CoordModePrevious表示第一个点之后所有坐标都是相对前一个点的。
	 * */
	{
		XPoint points[] = {
			{0, 0},
			{15, 15},
			{0, 15},
			{0, 0}
		};
		int npoints = sizeof(points)/sizeof(XPoint);

		XSetForeground(display, gc, yellow.pixel);
		XDrawLines(display, win, gc, points, npoints, CoordModeOrigin);
	}

	/*利用白色绘制一个左上角坐标(120,150)，宽50高60像素的矩形(空心的)*/
	XSetForeground(display, gc, WhitePixel(display, screen_num));
	XDrawRectangle(display, win, gc, 120, 150, 50, 60);

	/*利用绿色在上面矩形左侧绘制一个一样的矩形，不过是实心的矩形*/
	XSetForeground(display, gc, green.pixel);
	XFillRectangle(display, win, gc, 60, 150, 50, 60);

	/*把所有的请求通知给X server*/
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
