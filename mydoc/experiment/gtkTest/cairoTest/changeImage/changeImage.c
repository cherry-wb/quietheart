/*程序功能：
 *利用cairo绘制动态的不同图片，需要注意的是绘制的操作要放在expose中，
 *在定时函数中用gtk_widget_queue_draw(GTK_WIDGET(data))发送expose信号。
 *否则放到定时函数中绘制的话，要么图片很闪，要么无法显示。
 * */
#include <gtk/gtk.h>

#define IMG_BG_FILE "./BG.png"

#define IMG_LOADING_FILE1 "./loadingTest1.png"
#define IMG_LOADING_FILE2 "./loadingTest2.png"
#define IMG_LOADING_FILE3 "./loadingTest3.png"
#define IMG_LOADING_FILE4 "./loadingTest4.png"
#define IMG_LOADING_FILE5 "./loadingTest5.png"
#define IMG_LOADING_FILE6 "./loadingTest6.png"

#define LOAD_IMG_X 100
#define LOAD_IMG_Y 100

/*改变背景*/
static void update_widget_bg(GtkWidget *widget, gchar *img_file);

/*显示图片，每次调用显示不同图片*/
static void showChangeIMG(GtkWidget *widget);

/*定时调用showChangeIMG*/
gboolean changeDraw(gpointer data);

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data);

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

static void showChangeIMG(GtkWidget *widget)
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
	cairo_paint (cr);

	cairo_destroy(cr);
	cairo_surface_destroy (image);
}

gboolean changeDraw(gpointer data)
{
	gtk_widget_queue_draw(GTK_WIDGET(data));
	return TRUE;
}

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data)
{
	showChangeIMG(widget);
	return FALSE;
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

	/*eventbox*/
	event_box=gtk_event_box_new();
	g_signal_connect(event_box, "expose-event",
			G_CALLBACK(on_expose_event), NULL);
	
	update_widget_bg(event_box, IMG_BG_FILE);
	gtk_container_add (GTK_CONTAINER (window), event_box);
	/*没有这句话不能绘图*/
	gtk_widget_set_app_paintable(event_box, TRUE);
	gtk_widget_show(event_box);

	g_timeout_add(500,changeDraw,event_box);

	gtk_widget_show_all(window);

	gtk_main();
}
