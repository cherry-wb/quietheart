/*程序的功能：
 * 点击两个按钮，改变相应按钮上面的光标，如果再点击则。。。来回切换.
主要利用函数：gdk_window_set_cursor
 *
 * */
#include<gtk/gtk.h>
void callback1(GtkWidget *widget, gpointer data)
{
	static int flag1 = 0;
	flag1 ^=1;
	g_print("button clicked for cursor1\n");
	if(flag1 == 0)
	{
		gdk_window_set_cursor(widget->window,NULL);
	}
	else
	{
		gdk_window_set_cursor(widget->window, gdk_cursor_new(GDK_X_CURSOR));
	}
}
void callback2(GtkWidget *widget, gpointer data)
{
	static int flag2 = 0;
	flag2 ^=1;
	g_print("button clicked for cursor2\n");
	if(flag2 == 0)
	{
		/*设置为NULL表示使用父窗口的，这也是大多数默认的行为
		 * GDK_BLANK_CURSOR表示光标不可见
		 * */
		gdk_window_set_cursor(widget->window,NULL);
		
	}
	else
	{
		/*设置之后，光标就变成了相应的图案无论离开按钮与否
		 * */
		gdk_window_set_cursor(widget->window, gdk_cursor_new(GDK_BOX_SPIRAL));
	}
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
	GtkWidget *button1;
	GtkWidget *button2;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "cursorChange");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);
	
	button1 = gtk_button_new_with_label("button with cursor1");
	//the below is good too
	//g_signal_connect(G_OBJECT(button), "clicked",
	//		GTK_SIGNAL_FUNC(callback), "button1");
	g_signal_connect(G_OBJECT(button1), "clicked",
			G_CALLBACK(callback1), NULL);
	//don't forget the GTK_BOX
	gtk_box_pack_start(GTK_BOX(hbox), button1,
			TRUE, TRUE, 0);
	//don't forget to show here
	gtk_widget_show(button1);

	button2 = gtk_button_new_with_label("button with cursor2");
	g_signal_connect(G_OBJECT(button2), "clicked",
			G_CALLBACK(callback2), NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button2,
			TRUE, TRUE, 0);
	//show widget don't need to type change
	gtk_widget_show(button2);

	gtk_widget_show(hbox);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
