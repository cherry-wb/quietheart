#include<gtk/gtk.h>
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *volumeButton;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	
	volumeButton =gtk_volume_button_new();
	/*g_signal_connect(G_OBJECT(volumeButton), "clicked",
			G_CALLBACK(hello), NULL);*/
	gtk_container_add(GTK_CONTAINER(window), volumeButton);
	gtk_widget_show(volumeButton);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
