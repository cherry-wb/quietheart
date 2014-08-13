#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *win;
	GtkWidget *socket;

	gtk_init(&argc, &argv);

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(win), 100, 100);
	g_signal_connect(G_OBJECT(win), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	socket = gtk_socket_new();
	gtk_widget_show(socket);
	gtk_container_add(GTK_CONTAINER(win), socket);
	gtk_widget_show_all(win);

	gtk_widget_realize(socket);
	g_print("socket id: %d\n", gtk_socket_get_id(GTK_SOCKET(socket)));

	gtk_main();
	return 0;
}
