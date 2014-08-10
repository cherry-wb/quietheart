/*程序功能：给一个图片添加事件响应
 *有些构建它们没有X窗口，一般是直接画在它们父窗口的，所有无法接收信号连接函数.
 *这节省了内存，如果需要给它们发消息，则把它们添加到eventBox上面.
 *
 *event_box只是提供一个X窗口，这个窗口什么也不画，但是你不给它添加构件它仍然存
 *在并且也响应事件，如果你把它添加到窗口中，窗口有背景那么窗口的背景被它覆盖
 * */
#include <gtk/gtk.h>
void my_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("hello, print\n");
}
int main(int argc,char *argv[ ])
{

	GtkWidget *window;
	GtkWidget *event_box;
	GtkWidget *image;

	/*window*/
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	/*eventbox*/
	event_box=gtk_event_box_new();/*创建事件盒构件*/
	g_signal_connect(GTK_OBJECT(event_box),"button_press_event",
			G_CALLBACK(my_button_press),NULL);/* 为事件盒构件绑定一个事件响应*/
	gtk_container_add(GTK_CONTAINER(window),event_box);
	gtk_widget_show(event_box);

	/*image*/
	image = gtk_image_new_from_file("image.png");
	gtk_container_add(GTK_CONTAINER(event_box),image);
	gtk_widget_show(image);//如果没有这句话，就无法显示image即使后面用show_all

	gtk_widget_show(window);
	gtk_main();

}
