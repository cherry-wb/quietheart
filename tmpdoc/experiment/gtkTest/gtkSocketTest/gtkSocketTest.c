/*本程序功能：
 *实现gtk的Plug和Socket
 Socket是一个程序（假设为a）中的widget,它有一个特定的socketid号。
 Plug是另外一个程序中(假设为b)的widget,需要用一个特定的socketid来初始化，
 如果用a的socketid初始化的话:
 这样，运行a之后，再运行b那么b中所有在Plug中的控件就会显示在程序a中的socket插件中，实现了动态加载。
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
	GtkWidget *button;
	//GtkWidget *button2;
	GtkWidget *socket; 
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
	
	/*button1*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*button2*/
	button = gtk_button_new();
	/*g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2");*/
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	socket = gtk_socket_new ();
	gtk_widget_show (socket);
	gtk_container_add (GTK_CONTAINER (button), socket);
	gtk_widget_show_all(window);
	gtk_widget_realize (socket);/*这句话放在show后面，放在showall前面实践过了之后也行,不用这个好像也行*/
	/* The following call is only necessary if one of
	 *  * the ancestors of the socket is not yet visible.
	 *   */
/*最好不用这样的数字输出，否则这个号码无法在Plug中应用。*/
	/*g_print ("The ID of the sockets window is %x\n",
			gtk_socket_get_id (socket));*/
	g_print ("The ID of the sockets window is %d\n",
			gtk_socket_get_id (socket));
	gtk_main();
	return 0;
}
