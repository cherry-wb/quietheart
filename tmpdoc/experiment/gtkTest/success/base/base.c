/*程序功能：一个最简单的gtk程序*/
#include<gtk/gtk.h>
gint main(gint argc,gchar *argv[])
{
	GtkWidget *window = NULL;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
