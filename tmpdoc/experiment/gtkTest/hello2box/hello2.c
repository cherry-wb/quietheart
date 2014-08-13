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
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);
	
	button = gtk_button_new_with_label("button1");
	//the below is good too
	//g_signal_connect(G_OBJECT(button), "clicked",
	//		GTK_SIGNAL_FUNC(callback), "button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1");
	//don't forget the GTK_BOX
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);
	//don't forget to show here
	gtk_widget_show(button);

	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);
	//show widget don't need to type change
	gtk_widget_show(button);

	gtk_widget_show(hbox);
	gtk_widget_show(window);
	//gtk_window_present(GTK_WINDOW(window));
	gtk_main();
	return 0;
}
