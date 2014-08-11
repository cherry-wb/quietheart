/*只要建立GtkStatusIcon就会自动添加到statusbar中了。*/
#include <gtk/gtk.h>


gboolean tray_button_press_event(GtkWidget *button, GdkEventButton *event, gpointer data)
{
	g_print("hello press event\n");
}
int main(int argc, char *argv[])
{
	GtkWidget *win;
	GtkStatusIcon *icon;
	GtkWidget *event_box;

	gtk_init(&argc, &argv);

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(win), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	icon = gtk_status_icon_new_from_stock(GTK_STOCK_OK);

	/*event_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER (event_box), icon);
	g_signal_connect (G_OBJECT (event_box), "button-press-event",
			          G_CALLBACK (tray_button_press_event), NULL);*/




	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}
