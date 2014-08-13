/*程序功能：
 *自定义一个简单的构件，构件包含一个hbox(父亲)，两个button。
 并且建立它自己的属性和信号install property,signal,private。
 * */
#include<gtk/gtk.h>
#include"myComponent.h"

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *my_component;
	GtkButton *button;

	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			gtk_main_quit, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	/*mycomponent*/
	my_component = mycomponent_new();
	gtk_container_add(GTK_CONTAINER(window), my_component);

	/*button3*/
	button = gtk_button_new_with_label("button3 out of mycomponent,add to my component");
	/*不知道为什么编译的时候有警告错误*/
	gtk_box_pack_start(GTK_BOX(my_component), button, TRUE, TRUE, 0);
	//gtk_box_pack_start(MYCOMPONENT(my_component), button, TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
