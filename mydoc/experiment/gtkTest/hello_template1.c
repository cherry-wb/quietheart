/*功能：一个简单的模板程序：
 *一个窗口，一个按钮
 * */

#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	/*button*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
