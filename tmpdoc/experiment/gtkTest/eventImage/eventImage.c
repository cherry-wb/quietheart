/*程序功能：给图片添加事件响应, 有多个图片，并且有背景。
 * 问题，eventbox把它所在的地方的背景给覆盖。
 * */
#include <gtk/gtk.h>
void my_button_press1(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("hello, print1\n");
}

void my_button_press2(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("hello, print2\n");
}

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
int main(int argc,char *argv[ ])
{

	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *event_box;
	GtkWidget *image;

	/*window*/
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	update_widget_bg(window, "./bg1.jpg");
	gtk_window_set_default_size(GTK_WINDOW(window), 300,300);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	/*fixed*/
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (window), fixed);

	/*eventImage1*/
	event_box=gtk_event_box_new();/*创建事件盒构件*/
	g_signal_connect(GTK_OBJECT(event_box),"button_press_event",
			G_CALLBACK(my_button_press1),NULL);/* 为事件盒构件绑定一个事件响应*/
	/*可以给eventbox添加一个背景*/
	//update_widget_bg(event_box, "./bg1.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), event_box, 100,200);
	gtk_widget_show(event_box);
	image = gtk_image_new_from_file("image1.png");
	gtk_container_add(GTK_CONTAINER(event_box),image);
	gtk_widget_show(image);//如果没有这句话，就无法显示image即使后面用show_all

	/*eventImage2*/
	event_box=gtk_event_box_new();/*创建事件盒构件*/
	g_signal_connect(GTK_OBJECT(event_box),"button_press_event",
			G_CALLBACK(my_button_press2),NULL);/* 为事件盒构件绑定一个事件响应*/
	gtk_fixed_put(GTK_FIXED(fixed), event_box, 300,200);
	gtk_widget_show(event_box);
	image = gtk_image_new_from_file("image2.png");
	gtk_container_add(GTK_CONTAINER(event_box),image);
	gtk_widget_show(image);//如果没有这句话，就无法显示image即使后面用show_all

	gtk_widget_show_all(window);
	gtk_main();

}
