/*功能：测试利用g_idle函数来调用另外一个函数。
 *描述：
 *g_idle函数调用的函数和本例中的call_by_idle形式类似。
 *这个函数类似新开了一个线程调用一个函数，但是这个函数只有当没有较高优先的任务
 *的时候才会被执行。返回值？如果不是FALSE那么就会一直调用这个函数。
 *
 *实践结果：
 *1)在回调函数中调用g_idle调用的函数，当回调函数结束的时候才执行。
 *这里回调函数用了sleep,pause都是这样。
 *2)在main中调用g_idle调用的函数，在gtk_main之前就被执行了。
 *g_idle函数执行完才有g_idle调用的函数。
 *3)如果连续点击多次按钮导致多次调用使用g_idle的回调函数，那么
 *所有回调函数执行完了之后才陆续执行g_idle指定的函数。
 * */

#include<gtk/gtk.h>
gboolean call_by_idle(gpointer data)
{
	g_print("go into call_by_idle\n");

	
	g_print("call_by_idle sleep...\n");
	sleep(1);

	g_print("go outof call_by_idle\n");
	return FALSE;
	//return TRUE;
}
void call_back(GtkWidget *button, gpointer data)
{
	g_print("go into call_back!\n");
	g_print("before g_idle!\n");

	g_idle_add(call_by_idle, NULL);

	g_print("after g_idle!\n");
	g_print("call_back sleep...\n");
	sleep(2);
	//pause();
	g_print("go outof call_back!\n");
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);

	g_print("go into main!\n");
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	/*button*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(call_back), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);


	/*test idle*/
	g_print("in main before g_idle!\n");

	g_idle_add(call_by_idle, NULL);

	g_print("in main after g_idle!\n");
	g_print("before gtk_main...\n");
	gtk_main();
	g_print("after gtk_main...\n");
	g_print("go outof main!\n");
	return 0;
}
