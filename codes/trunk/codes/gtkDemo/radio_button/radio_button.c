#include<gtk/gtk.h>
void radio_callback(GtkToggleButton *button, gpointer data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
	{
		g_print("%s selected\n", (gchar*)data);
	}
}
void close_callback(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *hseparator;
	GtkWidget *vbox1;
	GtkWidget *vbox2;
	GtkWidget *hbox;
	GSList *list;
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "test radio");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox1 = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox1);
	
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox1), hbox, FALSE, FALSE, 0);

	vbox2 = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 0);
	
	button = gtk_radio_button_new_with_label(NULL, "left1");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "left1 radio button");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);
	list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);

	button = gtk_radio_button_new_with_label(list, "left2");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "left2 radio button");
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);
	
	button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button), "left3");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "left3 radio button");
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);

	vbox2 = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox2, FALSE, FALSE, 0);

	button = gtk_radio_button_new_with_label(NULL, "right1");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "right1 radio button");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
	list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);

	button = gtk_radio_button_new_with_label(list, "right2");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "right2 radio button");
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);
	
	button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button), "right3");
	g_signal_connect(G_OBJECT(button), "toggled",
			G_CALLBACK(radio_callback), "right3 radio button");
	gtk_box_pack_start(GTK_BOX(vbox2), button, FALSE, FALSE, 0);

	button = gtk_button_new_with_label("close");
	g_signal_connect(G_OBJECT(button), "clicked",
		G_CALLBACK(close_callback), NULL);
	gtk_box_pack_start(GTK_BOX(vbox1), button, FALSE, FALSE, 0);
	
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
