/*本程序的功能：
 * 检测回调函数的返回值。
 * 检测结果：
 * 1发现如果给一个事件连接多个回调函数，那么会依次调用这些回调函数
 * 2发现如果一个回调函数有布尔返回值且返回TRUE那么之后的回调函数不再被调用
 * 如果返回FALSE那么就会继续调用后面的回调函数。
 * */
#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}
//please notify the class of the parameters.
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occured\n");
	//gtk_main_quit();
	//return TRUE;//
	return FALSE;
}
void destroy(GtkWidget *widget,gpointer data)
{
	g_print("destroy called\n");
	gtk_main_quit();
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//this function set the width of the spacing between the button frame and window frame
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	//if the function return true,then after run all the optionations,the next destroy function will not use.
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	//g_signal_connect(G_OBJECT(window), "clicked",
	//		G_CALLBACK(delete_event), NULL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(destroy),NULL);
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
//to be continuted
