/*程序功能：指定构建的资源文件
 *
 *
 * */

#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}
//please notify the class of the parameters.
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occured\n");
	gtk_main_quit();
	//return TRUE;//
	return FALSE;
}
/*void destroy(GtkWidget *widget,gpointer data)
{
	g_print("destroy called\n");
	gtk_main_quit();
}*/
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*载入指定的资源文件*/
	gtk_rc_parse("myrc");

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	/*给窗口起个名字，这样资源文件中可以通过这个名字找到它*/
	gtk_widget_set_name (window,"myWindow");

	/*button*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_widget_set_name (button,"myButton1");
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
//to be continuted
