#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *plug;
	GtkWidget *label;

	gtk_init(&argc, &argv);

	// plug = gtk_plug_new_for_display(gdk_display_get_default(), 67108898);
	plug = gtk_plug_new(67108898);
	label = gtk_label_new("HELLO");
	gtk_widget_show(label);

	gtk_container_add(GTK_CONTAINER(plug), label);
	gtk_widget_show_all(plug);

	gtk_main();
	return 0;
}
