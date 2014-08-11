/*程序功能：
 * 利用fixbox在特定的位置添加控件,尝试给fix添加背景分配按钮大小等等。。
 * 1）如果窗口有背景，添加fixbox之后背景不会被覆盖。fix上面添加背景不起作用。
 * */
#include <gtk/gtk.h>

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
gint my_button1(GtkWidget *button, gpointer data)
{
	g_print("button1 pressed\n");
}

gint my_button2(GtkWidget *button, gpointer data)
{
	g_print("button2 pressed\n");
}

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget 是构件的存储类型 */
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *button;

  /* 初始化 */
  gtk_init (&argc, &argv);
    
  /* 创建一个新窗口 */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Fixed Container");
  update_widget_bg(window, "./bg1.jpg");

  /* 为窗口的 "destroy" 事件设置一个信号处理函数 */ 
  g_signal_connect (G_OBJECT (window), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);
  /* 设置窗口的边框宽度 */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* 创建一个固定容器 */
  fixed = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (window), fixed);
  //update_widget_bg(fixed, "./bg1.jpg");//给fixbox添加背景不管用
 
  /*按钮1*/
  button = gtk_button_new_with_label("button1");
  //gtk_widget_size_request(button, 60,80);
  gtk_fixed_put(GTK_FIXED(fixed), button, 100,200);
  g_signal_connect(G_OBJECT(button), "clicked",
		  G_CALLBACK(my_button1), NULL);

  /*按钮2*/
  button = gtk_button_new_with_label("button2");
  gtk_fixed_put(GTK_FIXED(fixed), button, 400,200);
  g_signal_connect(G_OBJECT(button), "clicked",
		  G_CALLBACK(my_button2), NULL);

  /* 显示窗口 */
  gtk_widget_show_all(window);
    
  /* 进入事件循环 */
  gtk_main ();
    
  return 0;
}
