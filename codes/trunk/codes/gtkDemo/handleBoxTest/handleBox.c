/*程序功能：测试handlebox的功能,实现浮动控件
 * handlebox是一个控件，把其他的widget添加到这个控件当中（利用container_add）,
 * 假设把button添加到handlebox中，那么效果就是，我们可以拖动这个按钮，让这个按钮
 * 脱离window而独立起来，类似浮动的功能。同样也可以让这个按钮停靠。
 * 如果handlebox上面没有添加任何widget那么效果就是在handlebox的位置上只有一个
 * 特殊的竖条，没有任何作用。
 * */
#include<gtk/gtk.h>
void callback(GtkWidget *widget, gpointer data)
{
	g_print("hello again\n %s is clicked\n",(gchar*)data);
}
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *hbox;
	GtkWidget *handlebox;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	/*hbox*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);
	
	/*handlebox*/
	handlebox = gtk_handle_box_new();
	gtk_box_pack_start(GTK_BOX(hbox), handlebox,
			TRUE, TRUE, 0);

	/*button1 in handlebox*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1");
	gtk_container_add(GTK_CONTAINER(handlebox), button);

	/*button2*/
	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
