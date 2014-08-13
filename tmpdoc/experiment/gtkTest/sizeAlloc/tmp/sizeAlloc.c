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
	GtkRequisition requistion;

	/*四个成员
	 *gint x:控件相对于它父亲的X坐标
	 *gint y:控件相对于它父亲的Y坐标
	 *gint width:控件被分配的宽度
	 *gint height:控件被分配的高度
	 * */
	GtkAllocation al={10,20,10,80};
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
	/*仅对container的子类有作用*/
	gtk_widget_size_allocate(button, &al);/*没有用？？*/
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
