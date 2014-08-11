/*功能：
 *想看看gtk_widget_push_composite_child到底是什么意思。
 * */

#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}
void destroy(GtkWidget *widget,gpointer data)
{
	g_print("destroy called\n");
	gtk_main_quit();
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(destroy),NULL);

	/*button*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);
	//gtk_widget_push_composite_child ();
	//gtk_widget_set_composite_name(button, "button");
	//gtk_widget_pop_composite_child ();

	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
