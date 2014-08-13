/*本程序实现定时调用功能，
 * 程序有两个按钮，一个启动定时调用函数功能，另一个终止。
 * 如果启动了，那么函数会定时打印信息。
 * */

#include<gtk/gtk.h>

static gint timer = -1;/*定时器号*/
static gint auto_print(gpointer data)
{/*定时调用的函数*/
	g_print("timer printing......\n");
	/*如果该处返回false那么只调用一次(在指定时间过后调用),返回TRUE则定时调用*/
	return TRUE;
}

void callback_start(GtkWidget *widget, gpointer data)
{/*启动定时*/
	g_print("now start the timer...\n");

	if(timer > -1)
	{
		g_print("please stop before start another timer!");
		return;
	}
	/*$$$$$$$关键，定时调用,就是第一下也得等1秒以后再动$$$$$*/
	timer = g_timeout_add(1000, auto_print, NULL);/*函数返回值大于0*/
}
void callback_stop(GtkWidget *widget, gpointer data)
{
	g_print("now stop the timer:%d\n",(gint)data);
	/*$$$$$$$关键，停止定时调用$$$$$*/
	g_source_remove(*(gint*)data);
	*(gint*)data = -1;
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
	GtkWidget *button;
	gtk_init(&argc, &argv);
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "testTimeOut");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	/*hbox*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);
	
	/*button_start*/
	button = gtk_button_new_with_label("start");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback_start), NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*button_stop*/
	button = gtk_button_new_with_label("stop");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback_stop), &timer);
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
