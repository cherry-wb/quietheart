#include <gtk/gtk.h>


static void on_click(GtkButton *button, gpointer data)
{
	g_print("button clicked!\n");
}

static void hello()
{
	g_print("hi, in func out of symbol, prepare to click!\n");
}

/*这个函数一定不能是static的，它是插件向外提供的函数。*/
GtkWidget * create_button()
{
	hello();
	GtkWidget *button = NULL;
	button = gtk_button_new_with_label("Hello, World!");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(on_click), NULL);
	gtk_widget_show(button);

	return button;
}

