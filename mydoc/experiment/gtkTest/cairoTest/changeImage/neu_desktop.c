/*程序功能：给图片添加事件响应, 有多个图片，并且有背景。
 *具体：
 *1)只有一个eventbox,在eventbox上面画多个图片，
 *2)根据位置判断事件响应，即不同图片的位置，使用不同事件响应.
 * */
#include <gtk/gtk.h>
#include "aspawn_launch.h"

#ifndef MY_DEBUG_OUTPUT
#define MY_DEBUG_OUTPUT 0
#endif

//#if MY_DEBUG_OUT == 1
#define IMG_DIR "./resource/"
//#else
//#define IMG_DIR "/usr/local/share/neuImage/"
//#endif
//#define IMG_DIR "/usr/local/share/neuImage/resource/"

#define IMG_BG_FILE IMG_DIR"./BG.png"
#define IMG_BG_LOADING_FILE IMG_DIR"./BG_LOADING.png"
//#define IMG_LOADING_FILE IMG_DIR"./loading1.gif"
#define IMG_LOADING_FILE1 IMG_DIR"./loadingTest1.png"
#define IMG_LOADING_FILE2 IMG_DIR"./loadingTest2.png"
#define IMG_LOADING_FILE3 IMG_DIR"./loadingTest3.png"
#define IMG_LOADING_FILE4 IMG_DIR"./loadingTest4.png"
#define IMG_LOADING_FILE5 IMG_DIR"./loadingTest5.png"
#define IMG_LOADING_FILE6 IMG_DIR"./loadingTest6.png"

#define IMG1_NORMAL_FILE IMG_DIR"./btn1_normal.png"
#define IMG2_NORMAL_FILE IMG_DIR"./btn2_normal.png"
#define IMG3_NORMAL_FILE IMG_DIR"./btn3_normal.png"
#define IMG4_NORMAL_FILE IMG_DIR"./btn4_normal.png"

#define IMG1_PRELIGHT_FILE IMG_DIR"./btn1_press.png"
#define IMG2_PRELIGHT_FILE IMG_DIR"./btn2_press.png"
#define IMG3_PRELIGHT_FILE IMG_DIR"./btn3_press.png"
#define IMG4_PRELIGHT_FILE IMG_DIR"./btn4_press.png"

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 128

/*这个宏定义用于调整四个图片整体偏移布局*/
#define X_OFFSET -10
#define Y_OFFSET 90

#define IMAGE1_XPOS (50 + X_OFFSET)
#define IMAGE1_YPOS (200 + Y_OFFSET)

#define IMAGE2_XPOS (220 + X_OFFSET)
#define IMAGE2_YPOS (30 + Y_OFFSET)

#define IMAGE3_XPOS (450 + X_OFFSET)
#define IMAGE3_YPOS (180 + Y_OFFSET)

#define IMAGE4_XPOS (620 + X_OFFSET)
#define IMAGE4_YPOS (-10 + Y_OFFSET)

/*Loading*/
#define LOADING_RECT_X (225 + X_OFFSET)
#define LOADING_RECT_Y (80 + Y_OFFSET)
#define LOADING_RECT_W 400
#define LOADING_RECT_H 160
#define FONT_SIZE (LOADING_RECT_W>>3)
#define FONT_X (LOADING_RECT_X + (FONT_SIZE))
#define FONT_Y (LOADING_RECT_Y + (LOADING_RECT_H>>1))

#define LOAD_IMG_X (225 + X_OFFSET)
#define LOAD_IMG_Y (80 + Y_OFFSET)

#define IS_IN_RANGE(x, low, up) ((x)>(low)?((x)<(up)?1:0):0)
typedef enum
{
	NORMAL,
	PRELIGHT
//	PRESSED
}ButtonState;

static ButtonState btn1state = NORMAL;
static ButtonState btn2state = NORMAL;
static ButtonState btn3state = NORMAL;
static ButtonState btn4state = NORMAL;

static gulong pressSig = 0;
static gulong releaseSig = 0;
static gulong motionSig = 0;
static int winCount = 0;

/**************函数定义**********/
/*判断坐标是否在图片范围内*/
static gboolean in_image1(gint x, gint y);
static gboolean in_image2(gint x, gint y);
static gboolean in_image3(gint x, gint y);
static gboolean in_image4(gint x, gint y);

/*按下*/
static void my_button_press(GtkWidget *widget, GdkEventButton *event,
		gpointer data);

/*松开*/
static void my_button_release(GtkWidget *widget, GdkEventButton *event,
		gpointer data);

/*指针移动*/
static void my_mouse_motion(GtkWidget *widget, GdkEventMotion *event,
		gpointer data);

/*改变背景*/
static void update_widget_bg(GtkWidget *widget, gchar *img_file);

/*绘制图像*/
static void draw_image(GtkWidget *widget, const gchar *file, gint x, gint y);

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data);

/*启动程序*/
/*直接根据命令行来启动，不考虑单实例*/
static int launchApp_simple(char *appCmd);

/*更先进的启动*/
static int startBrowser(GtkWidget *widget);
static int startAudio(GtkWidget *widget);
static int startVideo(GtkWidget *widget);
static int startWifi(GtkWidget *widget);

static gboolean watchCount(gpointer data);

static void showLoading(GtkWidget *widget, const gchar *text);

static void showLoadingIMG(GtkWidget *widget);

/***********函数实现*************/
static void showLoadingIMG(GtkWidget *widget)
{
#if MY_DEBUG_OUTPUT == 1
	g_print("loading");
#endif
	cairo_t *cr;
	cairo_surface_t *image;
	static gint frame = 1;

	cr = gdk_cairo_create(widget->window);
	switch(frame)
	{
		case 1:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE1);
			++frame;
			break;
		case 2:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE2);
			++frame;
			break;
		case 3:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE3);
			++frame;
			break;
		case 4:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE4);
			++frame;
			break;
		case 5:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE5);
			++frame;
			break;
		case 6:
			image = cairo_image_surface_create_from_png(IMG_LOADING_FILE6);
			frame = 1;
			break;
		default:
			frame = 1;
	}
	cairo_set_source_surface (cr, image, LOAD_IMG_X, LOAD_IMG_Y);
	//cairo_scale (cr, 256.0/w, 256.0/h);
	cairo_paint (cr);
	gtk_widget_queue_draw(widget);

	cairo_destroy(cr);
	cairo_surface_destroy (image);
}
static void showLoading(GtkWidget *widget, const gchar *text)
{
#if MY_DEBUG_OUTPUT == 1
	g_print("loading");
#endif
	static int flag = 0;
	cairo_t *cr = gdk_cairo_create(widget->window);
	
	//绘制一个矩形方框
	//cairo_set_rgb_color(cr,0,0,0);
	//cairo_set_source_rgba(cr,0,0,0,1);
	//cairo_rectangle(cr,LOADING_RECT_X, LOADING_RECT_Y,
	//		LOADING_RECT_W, LOADING_RECT_H);
	//cairo_fill(cr);

	if(flag == 0)
	{
		flag ^= 1;
		cairo_set_source_rgba(cr,1,1,0,0.5);
	}
	else
	{
		flag ^=1;
		cairo_set_source_rgba(cr,0,0,1,0.5);
	}
	//cairo_set_font_size (cr, 50.0);
	cairo_set_font_size (cr, FONT_SIZE);
	cairo_move_to(cr, FONT_X, FONT_Y);
	cairo_show_text(cr,text);//画出一个串
	/*cairo_move_to(cr,250,200);
	if(flag == 0)
	{
		cairo_set_rgb_color(cr,0,0.5,0);
	}
	else
	{
		cairo_set_rgb_color(cr,0.5,0.5,0);
	}*/
//	cairo_select_font (cr, "DongWen--Song",
//			CAIRO_FONT_SLANT_NORMAL,
//			CAIRO_FONT_WEIGHT_NORMAL);//为cairo设置一个字体，字体名DongWen--Song，非斜体，非粗体。
	//cairo_scale_font(cr,60);//缩放字体到60倍
	//cairo_show_text(cr,text);//画出一个串
	cairo_destroy(cr);//销毁画笔
}

gboolean watchCount(gpointer data)
{
	//static gint frame = 1;
	gint watcher = winCount;
	gint curCount = getWindowCount();
	GtkWidget *widget = GTK_WIDGET(data);
	if(curCount != watcher)
	{
		//恢复背景颜色
		update_widget_bg(widget, IMG_BG_FILE);
		//恢复信号阻塞
		g_signal_handler_unblock(GTK_WIDGET(widget), pressSig);
		g_signal_handler_unblock(GTK_WIDGET(widget), releaseSig);
		g_signal_handler_unblock(GTK_WIDGET(widget), motionSig);
		//g_signal_handler_unblock_by_func不行么？
		return FALSE;
	}
	//闪烁画出LOADING......
	//showLoading(widget, "Loading......");
	
	//动态绘制图片
	showLoadingIMG(widget);
	/*switch(frame)
	{
		case 1:
			showLoadingIMG(widget, IMG_LOADING_FILE1);
			++frame;
			break;
		case 2:
			showLoadingIMG(widget, IMG_LOADING_FILE2);
			++frame;
			break;
		case 3:
			showLoadingIMG(widget, IMG_LOADING_FILE3);
			++frame;
			break;
		case 4:
			showLoadingIMG(widget, IMG_LOADING_FILE4);
			++frame;
			break;
		case 5:
			showLoadingIMG(widget, IMG_LOADING_FILE5);
			++frame;
			break;
		case 6:
			showLoadingIMG(widget, IMG_LOADING_FILE6);
			frame = 1;
			break;
		default:
			frame = 1;
	}*/
	return TRUE;
}

int startBrowser(GtkWidget *widget)
{
	//改变背景为灰暗
	update_widget_bg(widget, IMG_BG_LOADING_FILE);
	//阻塞点击按扭的事件
	g_signal_handler_block(GTK_WIDGET(widget), pressSig);
	g_signal_handler_block(GTK_WIDGET(widget), releaseSig);
	g_signal_handler_block(GTK_WIDGET(widget), motionSig);
	//g_signal_handlers_block_by_func不行么？

	//获取当前窗口数目
	winCount = getWindowCount();//函数现写
	//g_print("count is %d", winCount);
	g_timeout_add(500,watchCount,widget);
	//启动程序
	launchApp_simple("/usr/bin/midbrowser");
}

int startAudio(GtkWidget *widget)
{
	//改变背景为灰暗
	update_widget_bg(widget, IMG_BG_LOADING_FILE);
	//阻塞点击按扭的事件
	g_signal_handler_block(GTK_WIDGET(widget), pressSig);
	g_signal_handler_block(GTK_WIDGET(widget), releaseSig);
	g_signal_handler_block(GTK_WIDGET(widget), motionSig);
	//g_signal_handlers_block_by_func不行么？

	//获取当前窗口数目
	winCount = getWindowCount();//函数现写
	//g_print("count is %d", winCount);
	g_timeout_add(500,watchCount,widget);
	//启动程序
	//launchApp_simple("StartAudio.sh");
	launchApp_simple("/usr/bin/StartAudio.sh");
}

int startVideo(GtkWidget *widget)
{
	//改变背景为灰暗
	update_widget_bg(widget, IMG_BG_LOADING_FILE);
	//阻塞点击按扭的事件
	g_signal_handler_block(GTK_WIDGET(widget), pressSig);
	g_signal_handler_block(GTK_WIDGET(widget), releaseSig);
	g_signal_handler_block(GTK_WIDGET(widget), motionSig);
	//g_signal_handlers_block_by_func不行么？

	//获取当前窗口数目
	winCount = getWindowCount();//函数现写
	//g_print("count is %d", winCount);
	g_timeout_add(500,watchCount,widget);
	//启动程序
	launchApp_simple("StartVideo.sh");
}

int startWifi(GtkWidget *widget)
{
	//改变背景为灰暗
	update_widget_bg(widget, IMG_BG_LOADING_FILE);
	//阻塞点击按扭的事件
	g_signal_handler_block(GTK_WIDGET(widget), pressSig);
	g_signal_handler_block(GTK_WIDGET(widget), releaseSig);
	g_signal_handler_block(GTK_WIDGET(widget), motionSig);
	//g_signal_handlers_block_by_func不行么？

	//获取当前窗口数目
	winCount = getWindowCount();//函数现写
	//g_print("count is %d", winCount);
	g_timeout_add(500,watchCount,widget);
	//启动程序
	launchApp_simple("StartWifi.sh");
}
static gboolean in_image1(gint x, gint y)
{/*判断位置(x,y)是否在image1图片范围内*/
	if(IS_IN_RANGE(x,IMAGE1_XPOS,IMAGE1_XPOS+IMAGE_WIDTH)
			&& IS_IN_RANGE(y,IMAGE1_YPOS,IMAGE1_YPOS+IMAGE_HEIGHT))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static gboolean in_image2(gint x, gint y)
{/*判断位置(x,y)是否在image2图片范围内*/
	if(IS_IN_RANGE(x,IMAGE2_XPOS,IMAGE2_XPOS+IMAGE_WIDTH)
			&& IS_IN_RANGE(y,IMAGE2_YPOS,IMAGE2_YPOS+IMAGE_HEIGHT))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static gboolean in_image3(gint x, gint y)
{/*判断位置(x,y)是否在image3图片范围内*/
	if(IS_IN_RANGE(x,IMAGE3_XPOS,IMAGE3_XPOS+IMAGE_WIDTH)
			&& IS_IN_RANGE(y,IMAGE3_YPOS,IMAGE3_YPOS+IMAGE_HEIGHT))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static gboolean in_image4(gint x, gint y)
{/*判断位置(x,y)是否在image4图片范围内*/
	if(IS_IN_RANGE(x,IMAGE4_XPOS,IMAGE4_XPOS+IMAGE_WIDTH)
			&& IS_IN_RANGE(y,IMAGE4_YPOS,IMAGE4_YPOS+IMAGE_HEIGHT))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static void my_button_press(GtkWidget *widget, GdkEventButton *event,
		gpointer data)
{
	int x, y;
//	bstate = PRESSED;

	x = event->x;
	y = event->y;

#if MY_DEBUG_OUTPUT == 1
	g_print("hello, x is:%d, y is:%d\n", x, y);
#endif
	if(in_image1(x,y))
	{/*browser*/
#if MY_DEBUG_OUTPUT == 1
		g_print("pressed in the image1\n");
#endif
		//launchApp_simple("/usr/bin/midbrowser");
		startBrowser(widget);
	}
	else if(in_image2(x,y))
	{/*Audio*/
#if MY_DEBUG_OUTPUT == 1
		g_print("pressed in the image2\n");
#endif
		//launchApp_simple("/usr/bin/ls -a");//这里启动程序
		//launchApp_simple("/usr/bin/StartAudio.sh");
		startAudio(widget);
	}
	else if(in_image3(x,y))
	{/*Video*/
#if MY_DEBUG_OUTPUT == 1
		g_print("pressed in the image3\n");
#endif
		//launchApp_simple("/usr/bin/echo good");//这里启动程序
		//launchApp_simple("/usr/bin/StartVideo.sh");
		startVideo(widget);
	}
	else if(in_image4(x,y))
	{/*Wifi*/
#if MY_DEBUG_OUTPUT == 1
		g_print("pressed in the image4\n");
#endif
		//launchApp_simple("/usr/bin/echo 'hello world'");//这里启动程序
		//launchApp_simple("/usr/bin/StartWifi.sh");//这里启动程序
		startWifi(widget);
	}
	else
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("pressed out of all the image!\n");
#endif
	}
}

static void my_button_release(GtkWidget *widget, GdkEventButton *event,
		gpointer data)
{
	int x, y;

	x = event->x;
	y = event->y;

#if MY_DEBUG_OUTPUT == 1
	g_print("hello, x is:%d, y is:%d\n", x, y);
#endif
	if(in_image1(x,y))
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("release in the image1\n");
#endif
		//btn1state = PRELIGHT;
	}
	else if(in_image2(x,y))
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("release in the image2\n");
#endif
	}
	else if(in_image3(x,y))
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("release in the image3\n");
#endif
	}
	else if(in_image4(x,y))
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("release in the image4\n");
#endif
	}
	else
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("release out of all the image!\n");
#endif
	}
}

static void my_mouse_motion(GtkWidget *widget, GdkEventMotion *event,
		gpointer data)
{
	int x, y;
	GdkModifierType state;

#if MY_DEBUG_OUTPUT == 1
	g_print("hello, motion hint out?\n");
#endif
	if(event->is_hint)
	{
#if MY_DEBUG_OUTPUT == 1
		g_print("hello, motion hint in?\n");
#endif
		gdk_window_get_pointer(event->window, &x, &y, &state);
	}
	else
	{
		x = event->x;
		y = event->y;
		state = event->state;
	}
	if(in_image1(x,y))
	{
		btn1state = PRELIGHT;
	}
	else if(in_image2(x,y))
	{
		btn2state = PRELIGHT;
	}
	else if(in_image3(x,y))
	{
		btn3state = PRELIGHT;
	}
	else if(in_image4(x,y))
	{
		btn4state = PRELIGHT;
	}
	else
	{
		btn1state = NORMAL;
		btn2state = NORMAL;
		btn3state = NORMAL;
		btn4state = NORMAL;
	}
	gtk_widget_queue_draw(widget);
}

static void update_widget_bg(GtkWidget *widget, gchar *img_file)
{
	GtkStyle *style;
	GdkPixbuf *pixbuf;
	GdkPixmap *pixmap;

	gint width, height;

	pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);

	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);

	pixmap = gdk_pixmap_new(NULL, width, height, 24);


	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);

	style = gtk_style_copy(GTK_WIDGET (widget)->style);
	if (style->bg_pixmap[GTK_STATE_NORMAL])
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);

	gtk_widget_set_style(GTK_WIDGET (widget), style);//替代了
	//gtk_widget_modify_style(GTK_WIDGET (widget), style);//直接改
	g_object_unref(style);
}

static void draw_image(GtkWidget *widget, const gchar *file, gint x, gint y)
{
	cairo_surface_t *image;
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);

	image = cairo_image_surface_create_from_png(file);
	cairo_set_source_surface(cr, image, x, y);
	cairo_paint(cr);
	cairo_surface_destroy(image);

	cairo_destroy(cr);
}

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data)
{
	if(btn1state == NORMAL)
	{
		draw_image(widget, IMG1_NORMAL_FILE, IMAGE1_XPOS, IMAGE1_YPOS);
	}
	else
	{
		draw_image(widget, IMG1_PRELIGHT_FILE, IMAGE1_XPOS, IMAGE1_YPOS);
	}

	if(btn2state == NORMAL)
	{
		draw_image(widget, IMG2_NORMAL_FILE, IMAGE2_XPOS, IMAGE2_YPOS);
	}
	else
	{
		draw_image(widget, IMG2_PRELIGHT_FILE, IMAGE2_XPOS, IMAGE2_YPOS);
	}

	if(btn3state == NORMAL)
	{
		draw_image(widget, IMG3_NORMAL_FILE, IMAGE3_XPOS, IMAGE3_YPOS);
	}
	else
	{
		draw_image(widget, IMG3_PRELIGHT_FILE, IMAGE3_XPOS, IMAGE3_YPOS);
	}

	if(btn4state == NORMAL)
	{
		draw_image(widget, IMG4_NORMAL_FILE, IMAGE4_XPOS, IMAGE4_YPOS);
	}
	else
	{
		draw_image(widget, IMG4_PRELIGHT_FILE, IMAGE4_XPOS, IMAGE4_YPOS);
	}
	return FALSE;
}

static int launchApp_simple(char *appCmd)
{
#if MY_DEBUG_OUTPUT == 1
	g_print("go into launchApp_portable*****\n");
#endif
	if(appCmd != NULL)
	{/*if input is not NULL*/
		/*parameter number*/
		gint argc;
		/*parameter*/
		gchar **argv = NULL;
		GError *error = NULL;
		GPid child_pid;
		/*****launch the applications here!*****/
		if(g_shell_parse_argv (appCmd, &argc, &argv, &error))
		{
#if MY_DEBUG_OUTPUT == 1
			g_print("the application command is '%s' \n", appCmd);
			g_print("the application path is '%s'\n", argv[0]);
			g_print("the first parameter is '%s'\n", argv[1]);
			g_print("the parameter number is '%d'\n", argc);
#endif
			g_spawn_async(
					/* Child's current working directory,
					   or NULL to inherit parent's */
					NULL,
					/* Child's argument vector. [0] is the path of
					   the program to execute */
					argv,
					/* Child's environment, or NULL to inherit
					   parent's */
					NULL,
					/* Flags from GSpawnFlags */
					0,
					/* Function to run in the child just before
					   exec() */
					NULL,
					/* User data for child_setup */
					NULL,
					/* Return location for child process ID or NULL */
					&child_pid,
					/* Return location for error */
					&error);/*lkcomment异步执行子程序*/

			if (argv)
				g_strfreev (argv);
			return 0;
		}
		if (error)
		{
			g_print("failed to execute!*****\n");

			g_clear_error (&error);
		}
		g_print("spawn failed************\n");
		return 1;

	}
	else
	{
		g_print("appCmd is NULL!!********\n");
		return 1;
	}
#if MY_DEBUG_OUTPUT == 1
	g_print("go outof launchApp_portable*****\n");
#endif
}

int main(int argc,char *argv[ ])
{

	GtkWidget *window;
	GtkWidget *event_box;

	/*window*/
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_default_size(GTK_WINDOW(window), 800,550);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DESKTOP);
	//gtk_container_set_border_width(GTK_CONTAINER(window),10);

	/*eventbox*/
	event_box=gtk_event_box_new();
	
	/*如果没有这个只有单击的时候移动才有响应*/
	gtk_widget_add_events (event_box, GDK_POINTER_MOTION_MASK);
	gtk_widget_add_events (event_box, GDK_POINTER_MOTION_HINT_MASK);
	pressSig = g_signal_connect(GTK_OBJECT(event_box),"button_press_event",
			G_CALLBACK(my_button_press),NULL);
	releaseSig = g_signal_connect(GTK_OBJECT(event_box),"button_release_event",
			G_CALLBACK(my_button_release),NULL);
	motionSig = g_signal_connect(GTK_OBJECT(event_box),"motion_notify_event",
			G_CALLBACK(my_mouse_motion),NULL);
	g_signal_connect(event_box, "expose-event",
			G_CALLBACK(on_expose_event), NULL);
	update_widget_bg(event_box, IMG_BG_FILE);
	gtk_container_add (GTK_CONTAINER (window), event_box);
	/*没有这句话不能绘图*/
	gtk_widget_set_app_paintable(event_box, TRUE);
	gtk_widget_show(event_box);

	gtk_widget_show_all(window);

	gtk_main();
}
