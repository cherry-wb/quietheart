/*本程序的功能：设置g_print函数的调用没有响应，不打印g_print的信息.
 *如果点击按钮，会设置g_print为空，这样将不打印。点击5次之后会设置回来可以打印，
 *之后又设置为空....
 *
 * g_print是一个打印消息的函数，可以利用它来打印调试信息，如果
 * 不需要这个函数了，怎么做？
 * 本程序实现定义一个函数，所有的打印信息由这个函数处理，来替代g_printer
 * 设置的语句函数是：GPrintFunc g_set_print_handler(GPrintFunc func);
 * 返回先前设置的函数指针。
 * 关于GPrintFunc定义如下：
 * void (*GPrintFunc)(const gchar *string);
 * 如果设置为，空函数则没有打印信息了。但是参数不能为NULL,这样没有作用,
 * 如果参数设置为NULL那么就又调用g_print了.
 *
 * */
#include<gtk/gtk.h>
void my(const gchar *message)
{/*什么也不打印*/
	;
}
void hello(GtkWidget *button, gpointer data)
{
	static gint count = 0;
	if(count > 3)
	{
		g_set_print_handler(NULL);
		count = 0;
	}
	else
	{
	//	g_set_print_handler(NULL);
		g_set_print_handler(my);
		count++;
	}
	g_print("hello,five times pased set g_print again to null in five clicked.\n");
}
//please notify the class of the parameters.
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occured\n");
	gtk_main_quit();
	//return TRUE;//
	return FALSE;
}
gint main(gint argc, gchar *argv[])
{
	//g_set_print_handler(NULL);
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);

	button = gtk_button_new_with_label("点击设置g_printer");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
//to be continuted
