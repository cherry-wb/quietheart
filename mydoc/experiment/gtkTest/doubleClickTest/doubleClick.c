/*本程序功能：
 * 实现鼠标双击和三击按钮的事件函数响应
 *
 * */
#include<gtk/gtk.h>
void click_callback(GtkWidget *button, gpointer data)
{
	g_print("click event\n");
}

void button_press_callback(GtkWidget *button, GdkEventButton *event, gpointer data)
{

	g_print("button_press_event\n");
}

gboolean double_click_callback(GtkWidget *button, GdkEventButton *event, gpointer data)
{//这里处理双击函数，实际也包括了三击
	if (GTK_IS_BUTTON(button) &&
			(event->type==GDK_2BUTTON_PRESS ||
			 event->type==GDK_3BUTTON_PRESS) )
	{
		printf("I feel %s clicked with button %d\n",
				event->type==GDK_2BUTTON_PRESS ? "double" : "triple",
				event->button);
	}

	return FALSE;
}
//please notify the class of the parameters.
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occured\n");
	//gtk_main_quit();
	//return TRUE;//
	return FALSE;
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
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//this function set the width of the spacing between the button frame and window frame
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	//if the function return true,then after run all the optionations,the next destroy function will not use.
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	//g_signal_connect(G_OBJECT(window), "clicked",
	//		G_CALLBACK(delete_event), NULL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(destroy),NULL);
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(click_callback), NULL);
	g_signal_connect(G_OBJECT(button), "button-press-event",
			G_CALLBACK(button_press_callback), NULL);

	/*这里利用button-press-event来连接双击乃至三击的回调函数，也可button-release-event来连接*/
	g_signal_connect(G_CALLBACK(button), "button-press-event",
			G_CALLBACK(double_click_callback), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
//to be continuted
