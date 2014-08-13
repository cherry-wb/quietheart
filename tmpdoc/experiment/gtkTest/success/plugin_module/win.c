/*程序功能：
 *展示利用模块插件的使用方法。
 插件编译成lib*.so的文件，这个程序的插件就是创建一个按钮。
 通过插件，可以扩展应用程序的功能。
 * */
#include <gtk/gtk.h>

//实际没有用到这个也行，但是，最好提供头文件，这才能知道插件提供了哪些函数。
//#include "plugin.h"
typedef GtkWidget *(*modulefunc1)(); 


int main(int argc, char *argv[])
{
	modulefunc1 new_button;
	GModule *module;
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	/*这个函数指定将要使用的模块，第二个参数是加载时的标志，一般就用这个,
	 * 加载正确则返回GModule，否则为空*/
	module = g_module_open("./libplugin.so", G_MODULE_BIND_LAZY);

	/*获取模块module(libplugin.so)中的函数地址，存放到new_button函数指针中
	 * 这里需要注意第3个参数类型。*/
	g_module_symbol(module, "create_button", (gpointer*)&new_button);
	button = new_button();

	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
