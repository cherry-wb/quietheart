/*本程序实现绿色的label字体
 * */
#include<gtk/gtk.h>

gint main(gint argc, gchar *argv[])
{
	GtkWidget *label;
	GtkWidget *window;
	gchar *label_text = "test1";
	gchar *markup = g_markup_printf_escaped ("<span color=\"#00FF00\">%s</span>", label_text);
	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	label = gtk_label_new(label_text);
	gtk_label_set_markup (GTK_LABEL (label), markup);
	g_free (markup);
	gtk_container_add(GTK_CONTAINER(window), label);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
