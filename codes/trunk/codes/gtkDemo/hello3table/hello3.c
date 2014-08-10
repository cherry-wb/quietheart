#include<gtk/gtk.h>

void callback(GtkWidget *widget, gpointer data)
{
	g_print("hello again \n %s was pressed\n",(gchar*)data);
}
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE;
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	//window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "hello3");
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	//table
	table = gtk_table_new(2,2,TRUE);
	//this set width isn't needed, the last set on window is enough
	//gtk_container_set_border_width(GTK_CONTAINER(table), 10);
	gtk_container_add(GTK_CONTAINER(window), table);

	//button1
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1 clicked");
	gtk_table_attach_defaults(GTK_TABLE(table), button,
			0, 1, 0, 1);
	gtk_widget_show(button);

	//button2
	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2 clicked");
	gtk_table_attach_defaults(GTK_TABLE(table), button,
			1, 2, 0, 1);
	gtk_widget_show(button);

	//button3
	button = gtk_button_new_with_label("quit");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(delete_event), NULL);
	gtk_table_attach_defaults(GTK_TABLE(table), button,
			0, 2, 1, 2);
	gtk_widget_show(button);
	//show all
	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_main();
	return 0;
}
