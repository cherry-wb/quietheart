/*程序功能：
 * 查看GTK_HPANED这个控件的作用。
 * 这个控件包含两个widget，中间有一个可以拖动的滑块。
 * 添加时，指定添加位置（只有两个位置：左／上，或右／下）,一个位置只能添一个。
 * 这个控件只能添加两个widget如果添加多了就显示不出来了,例如本例中的button2。
 * */
#include<stdio.h>
#include<gtk/gtk.h>

void callback(GtkWidget *widget, gpointer data)
{
	g_print("hello again\n %s is clicked\n",(gchar*)data);
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *hpane;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	frame = gtk_frame_new("following is the hpane");
	gtk_container_add(GTK_CONTAINER(window), frame);


	/*hpane*/
	hpane = gtk_hpaned_new();
	gtk_container_add(GTK_CONTAINER(frame), hpane);
	//gtk_paned_set_position(GTK_PANED(hpane), -1);//设置中间滑块位置

	/*button1*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1");

	/*在上面或者左面的pane添加一个child,原型如下：
	 * (.._pack2是在下面或者右面的panel添加)
	 *void  gtk_paned_pack1(GtkPaned *paned,
	                        GtkWidget *child,
						    gboolean resize,
						    gboolean shrink);
	参数意义：
	paned :
		添加到paned里	
	child :
		将要添加的child
	resize :
		当paned重绘大小的时候这个child是否扩展
	shrink :
		这个child能否比它请求的大小更小 
	这个函数的作用等同于gtk_paned_add1(GTK_PANED(hpane), button)
	 * */
	gtk_paned_pack1(GTK_PANED(hpane), button, FALSE, TRUE);

	/*button2*/
	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2");
	gtk_paned_pack1(GTK_PANED(hpane), button, FALSE, TRUE);

	/*button3*/
	button = gtk_button_new_with_label("button3");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button3");
	gtk_paned_pack2(GTK_PANED(hpane), button, FALSE, TRUE);


	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
