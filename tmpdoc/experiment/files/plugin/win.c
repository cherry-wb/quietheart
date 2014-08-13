#include <gtk/gtk.h>
#include "plugin.h"

typedef GtkWidget *(*make_button)();

make_button new_button;

GModule *module;

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	module = g_module_open("./libplugin.so", G_MODULE_BIND_LAZY);
	g_module_symbol(module, "create_button", (gpointer *)&new_button);
	button = new_button();

	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
