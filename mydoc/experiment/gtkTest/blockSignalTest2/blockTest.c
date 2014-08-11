/*本程序功能：测试回调函数的断开和连接
 * 点击button2(connect/block)，可以实现button1按钮的回调函数的连接和断开
 *
 * */
#include<gtk/gtk.h>
static gulong sig = 0;
void callback1(GtkWidget *widget, gpointer data)
{
	g_print("hello \n %s is clicked\n",(gchar*)data);
}
void callback2(GtkWidget *widget, gpointer data)
{//切换callback1回调函数连接与否
	static int on = 1;
	if(0 == on)
	{
		g_print("connect the callback1 for button1\n");
		//g_signal_handlers_unblock_by_func(GTK_BUTTON(data), callback1, "connect?");//这个方式不管用？
		g_signal_handler_unblock(GTK_BUTTON(data), sig);//取消阻塞信号
		on ^= 1;
	}
	else
	{
		g_print("block the callback1 for button1\n");
//		g_signal_handlers_block_by_func(GTK_BUTTON(data), callback1, "block?");//这个方式不管用？
		g_signal_handler_block(GTK_BUTTON(data), sig);//阻塞信号
		on ^= 1;
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
	gtk_window_set_title(GTK_WINDOW(window), "block signal");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);
	
	button1 = gtk_button_new_with_label("button1");
	//the below is good too
	//g_signal_connect(G_OBJECT(button), "clicked",
	//		GTK_SIGNAL_FUNC(callback), "button1");
	sig = g_signal_connect(G_OBJECT(button1), "clicked",
			G_CALLBACK(callback1), "button1");
	//don't forget the GTK_BOX
	gtk_box_pack_start(GTK_BOX(hbox), button1,
			TRUE, TRUE, 0);
	//don't forget to show here
	gtk_widget_show(button1);

	button2 = gtk_button_new_with_label("block/connect callback1");
	g_signal_connect(G_OBJECT(button2), "clicked",
			G_CALLBACK(callback2), button1);
	gtk_box_pack_start(GTK_BOX(hbox), button2,
			TRUE, TRUE, 0);
	//show widget don't need to type change
	gtk_widget_show(button2);

	gtk_widget_show(hbox);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
