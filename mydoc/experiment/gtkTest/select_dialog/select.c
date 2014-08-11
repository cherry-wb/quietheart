/*一个模板*/
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
void showDlg(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *button;
	gint result = 0;
	/*dialog*/
	dialog = gtk_dialog_new();
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_title(GTK_WINDOW(dialog), "test");
	//gtk_window_set_icon_from_file(GTK_WINDOW(dialog), icon_file, NULL);
	gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);
	gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
	
	/*vbox in dialog*/
	vbox = GTK_DIALOG(dialog)->vbox;

	/*hbox1 in vbox*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);
	
	/*button1 in hbox*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button1");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*button2 in hbox*/
	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "button2");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*hbox2 in vbox*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

	/*button1 in hbox*/
	button = gtk_button_new_with_label("ok");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(delete_event), "button1");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*button2 in hbox*/
	button = gtk_button_new_with_label("cancel");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(delete_event), "button2");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(dialog);
	result = gtk_dialog_run(GTK_DIALOG(dialog));
//	gtk_main();
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);

	/*button in hbox*/
	button = gtk_button_new_with_label("showDlg");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(showDlg), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
