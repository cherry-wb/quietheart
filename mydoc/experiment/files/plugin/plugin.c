#include <gtk/gtk.h>


void on_click(GtkButton *button, gpointer data)
{
	g_print("button clicked!\n");
}


GtkWidget * create_button()
{
	GtkWidget *button = NULL;
	button = gtk_button_new_with_label("Hello, World!");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(on_click), NULL);
	gtk_widget_show(button);

	return button;
}

