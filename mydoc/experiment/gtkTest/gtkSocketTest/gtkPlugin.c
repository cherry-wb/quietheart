/*本程序功能：
 *实现gtk的Plug和Socket
 Socket是一个程序（假设为a）中的widget,它有一个特定的socketid号。
 Plug是另外一个程序中(假设为b)的widget,需要用一个特定的socketid来初始化，
 如果用a的socketid初始化的话:
 这样，运行a之后，再运行b那么b中所有在Plug中的控件就会显示在程序a中的socket插件中，实现了动态加载。
 * */
#include<gtk/gtk.h>

gint main(gint argc, gchar *argv[])
{
	GtkWidget *gtkplug;
	GtkWidget *button;

	gtk_init(&argc, &argv);
	gtkplug = gtk_plug_new(67108900);/*这个号是由gtkSocketTest中的程序传过来的，对于编译了一次的程序，可能不变，单最好用通信的方式传递调用*/

	button = gtk_button_new_with_label("buttonInPlug");
	gtk_container_add(GTK_CONTAINER(gtkplug), button);

	gtk_widget_show_all(gtkplug);

	gtk_main();
	return 0;
}
