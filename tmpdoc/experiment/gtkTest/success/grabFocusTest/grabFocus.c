/*this program is used to set the focus for specific entry when you click corresponding button
 * */
#include<gtk/gtk.h>

void button1_click(GtkWidget *widget, gpointer data)
{
	g_print("click on button 1\n");
	g_print("entry1 text: %s\n",gtk_entry_get_text(GTK_ENTRY(data)));
	if(GTK_WIDGET_CAN_FOCUS(GTK_WIDGET(data)))
	{
		gtk_widget_grab_focus(GTK_WIDGET(data));
	}
}


void button2_click(GtkWidget *widget, gpointer data)
{
	g_print("click on button 2\n");
	g_print("entry2 text: %s\n",gtk_entry_get_text(GTK_ENTRY(data)));
	if(GTK_WIDGET_CAN_FOCUS(GTK_WIDGET(data)))
	{
		gtk_widget_grab_focus(GTK_WIDGET(data));
	}
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *button1;
	GtkWidget *button2;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

/*	gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);*/
	vbox = gtk_vbox_new(TRUE, 3);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 3);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox1 = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox1,
			TRUE, TRUE, 0);

	entry1 = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry1), "entry1");
	gtk_box_pack_start(GTK_BOX(hbox1), entry1,
			TRUE, TRUE, 0);

	entry2 = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry2), "entry2");
	gtk_box_pack_start(GTK_BOX(hbox1), entry2,
			TRUE, TRUE, 0);

	hbox2 = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2,
			TRUE, TRUE, 0);

	button1 = gtk_button_new_with_label("focus for entry1");
	g_signal_connect(G_OBJECT(button1), "clicked",
			G_CALLBACK(button1_click), entry1);
	gtk_box_pack_start(GTK_BOX(hbox2), button1,
			TRUE, TRUE, 0);

	button2 = gtk_button_new_with_label("focus for entry2");
	g_signal_connect(G_OBJECT(button2), "clicked",
			G_CALLBACK(button2_click), entry2);
	gtk_box_pack_start(GTK_BOX(hbox2), button2,
			TRUE, TRUE, 0);


	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
