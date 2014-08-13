#include<gtk/gtk.h>

void toggle_button_callback(GtkWidget *widget, gpointer data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
	{
		g_print("pressed\n");
	}
	else
	{
		g_print("released\n");
	}
}

void check_button_callback(GtkWidget *widget, gpointer data)
{
	//if(gtk_toggle_button_get_active(GTK_CHECK_BUTTON(widget)))/*wrong*/
	//if(gtk_check_button_get_active(GTK_CHECK_BUTTON(widget)))/*wrong*/
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
	{
		g_print("selected\n");
	}
	else
	{
		g_print("not selected\n");
	}
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *toggle_button;
	GtkWidget *check_button;
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 3);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	toggle_button = gtk_toggle_button_new_with_label("toggle_button");
	g_signal_connect(G_OBJECT(toggle_button), "toggled",
			G_CALLBACK(toggle_button_callback), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), toggle_button, FALSE, FALSE, 3);
	
	check_button = gtk_check_button_new_with_label("check_button");

	g_signal_connect(G_OBJECT(check_button), "toggled",
			G_CALLBACK(check_button_callback), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), check_button, FALSE, FALSE, 3);

	gtk_widget_show(toggle_button);
	gtk_widget_show(check_button);
	gtk_widget_show(vbox);
	gtk_widget_show(window);

	gtk_main();
	return 0;
}
