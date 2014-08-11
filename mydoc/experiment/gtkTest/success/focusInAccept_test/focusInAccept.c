/*功能：当焦点进入entry的时候entry获得focus-in-event，连接相应的回调函数。
 * 点击按钮将调用**set_accept_focus函数来反复切换是否接受焦点。
 * 现象：如果设置为不接受焦点，如果当前窗口还是焦点窗口的话仍然可以接受
 * focus-in-event并且entry始终有焦点，但是如果切换一下窗口的话就会发现：
 * 那么entry就无法接受focus-in-event了,也无法将焦点放进去，即使grab也不行。
 * 再次点击按钮才可以.
 *
 * */
#include<gtk/gtk.h>
void callback(GtkWidget *widget, gpointer data)
{
	static gboolean accept = FALSE;
	g_print("clicked the button\n");
	accept = !accept;
	if(accept == FALSE)
	{
		g_print("set don't accept focus\n");
		g_print("you should switch to other windows to see the effect\n");
	}
	else
	{
		g_print("set accept focus\n");
	}
	/*设置是否接受焦点,如果设置为false当焦点离开窗口就无法再回来了*/
	gtk_window_set_accept_focus(GTK_WINDOW(data), accept);
//	gtk_widget_grab_focus(GTK_WIDGET(data));
}
gboolean entry_focus_in(GtkWidget *widget, GdkEventFocus *event, gpointer data)
{
	g_print((gchar*)data);
}
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *entry;
	gtk_init(&argc, &argv);
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "focus");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);
	
	/*box*/
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	

	/*entry*/
	entry = gtk_entry_new();
	/*设置当焦点进入事件发生时的回调函数*/
	g_signal_connect(G_OBJECT(entry), "focus-in-event",
			G_CALLBACK(entry_focus_in), "focus-in-event happen\n");
	gtk_box_pack_start(GTK_BOX(vbox), entry,
			TRUE, TRUE, 0);

	/*button*/
	button = gtk_button_new_with_label("focus_accept/not");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), window);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);


	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
