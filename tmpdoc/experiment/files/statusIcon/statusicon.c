/*只要建立GtkStatusIcon就会自动添加到statusbar中了。*/
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *win;
	GtkStatusIcon *icon;

	gtk_init(&argc, &argv);

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(win), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	icon = gtk_status_icon_new_from_stock(GTK_STOCK_OK);
	gtk_widget_show_all(win);

	gtk_main();
	return 0;
}
