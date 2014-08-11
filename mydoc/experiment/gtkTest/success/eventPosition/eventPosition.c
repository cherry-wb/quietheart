/*程序功能：给图片添加事件响应, 有多个图片，并且有背景。
 *具体：
 *1)只有一个eventbox,在eventbox上面画多个图片，
 *2)根据位置判断事件响应，即不同图片的位置，使用不同事件响应.
 *注意：如果用fixbox那么fixbox并不是可以见到的窗口，它不会覆盖父窗口内容。
 * */
#include <gtk/gtk.h>

#define IMAGE_WIDTH 134
#define IMAGE_HEIGHT 134

#define IMAGE1_XPOS 50
#define IMAGE1_YPOS 150

#define IMAGE2_XPOS 200
#define IMAGE2_YPOS 150

#define IS_IN_RANGE(x, low, up) ((x)>(low)?((x)<(up)?1:0):0)
gboolean in_image1(gint x, gint y)
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

gboolean in_image2(gint x, gint y)
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

void my_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	int x, y;

	x = event->x;
	y = event->y;

	g_print("hello, x is:%d, y is:%d\n", x, y);
	if(in_image1(x,y))
	{
		g_print("pressed in the image1\n");
	}
	else if(in_image2(x,y))
	{
		g_print("pressed in the image2\n");
	}
	else
	{
		g_print("pressed out of all the image!\n");
	}

}

/*改变背景*/
void update_widget_bg(GtkWidget *widget, gchar *img_file)
{
	GtkStyle *style;
	GdkPixbuf *pixbuf;/*缓存文件*/
	GdkPixmap *pixmap;/*表明显示区域*/

	gint width, height;

	pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);/*把文件读到缓存中*/

	width = gdk_pixbuf_get_width(pixbuf);
	height = gdk_pixbuf_get_height(pixbuf);

	pixmap = gdk_pixmap_new(NULL, width, height, 24);/*建立一个显示的区域，以告诉在哪里显示图*/


	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);/*将缓存和显示区域联系*/

	/*设置显示图片构件的相应参数风格*/
	style = gtk_style_copy(GTK_WIDGET (widget)->style);
	if (style->bg_pixmap[GTK_STATE_NORMAL])
		g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);

	style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
	style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);

	gtk_widget_set_style(GTK_WIDGET (widget), style);//替代了
	//gtk_widget_modify_style(GTK_WIDGET (widget), style);//直接改，但是style类型不同了
	g_object_unref(style);
}

static gboolean on_expose_event(GtkWidget *widget,
		GdkEventExpose *event,
		gpointer data)
{
	cairo_surface_t *image;
	cairo_t *cr;
	//g_print("hi,expose_event\n");
	
	/*draw image,必须在show之后才能画,而且要放在这里面画*/
	cr = gdk_cairo_create(widget->window);

	/*image1*/
	image = cairo_image_surface_create_from_png("image1.png");
	cairo_set_source_surface(cr, image, IMAGE1_XPOS, IMAGE1_YPOS);
	cairo_paint(cr);
	cairo_surface_destroy(image);

	/*image2*/
	image = cairo_image_surface_create_from_png("image2.png");
	cairo_set_source_surface(cr, image, IMAGE2_XPOS, IMAGE2_YPOS);
	cairo_paint(cr);
	cairo_surface_destroy(image);

	cairo_destroy(cr);
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
	gtk_window_set_default_size(GTK_WINDOW(window), 300,300);
	//gtk_container_set_border_width(GTK_CONTAINER(window),10);

	/*eventbox*/
	event_box=gtk_event_box_new();
	g_signal_connect(GTK_OBJECT(event_box),"button_press_event",
			G_CALLBACK(my_button_press),NULL);
	g_signal_connect(event_box, "expose-event",
			G_CALLBACK(on_expose_event), NULL);
	update_widget_bg(event_box, "./bg1.jpg");
	gtk_container_add (GTK_CONTAINER (window), event_box);
	/*没有这句话不能绘图*/
	gtk_widget_set_app_paintable(event_box, TRUE);
	gtk_widget_show(event_box);

	gtk_widget_show_all(window);

	gtk_main();
}
