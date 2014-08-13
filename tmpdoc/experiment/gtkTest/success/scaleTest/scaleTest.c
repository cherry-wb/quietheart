/*本程序的功能：
 * 实现了范围控件和水平的调节控件，并且为值的变化连接了回调处理函数。
 * */
#include<stdio.h>
#include<gtk/gtk.h>

void valueChanged(GtkAdjustment *adjustment, gpointer user_data)
{
	gdouble tmpValue = 0;
	tmpValue = gtk_adjustment_get_value(adjustment);
	g_print("hello,value changed to %lf!\n", tmpValue);
}

gint main(gint argc, gchar *argv[])
{
	GtkObject *adjust;
	GtkWidget *window;
	GtkWidget *slider;

	gtk_init(&argc, &argv);
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_window_set_default_size(GTK_WINDOW(window), 200,50);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);

	/*adjustment*/
	/*adjustment是个不可见的抽象控件
	 GtkObject* gtk_adjustment_new(gdouble value,这个是初始值
	                               gdouble lower,这个是最小值
								   gdouble upper,这个是最大值
								   gdouble step_increment,这个是步增值
								   gdouble page_increment,这个是页增值
								   gdouble page_size);这个是页大小
	 * */
	adjust = GTK_OBJECT(gtk_adjustment_new(1,1,100,5,20,20));
	g_signal_connect(adjust, "value_changed", G_CALLBACK(valueChanged), NULL);

	/*slider*/
	/*另一个创建slider的函数是
	 GtkWidget* gtk_hscale_new_with_range(gdouble min,
	                                      gdouble max,
								          gdouble step);
	 * */
	slider = gtk_hscale_new(GTK_ADJUSTMENT(adjust));
	/*设置小数点后面的显示位数例如1对应1.0,2对应1.00之类的显示方式*/
	gtk_scale_set_digits(GTK_SCALE(slider), TRUE);
	/*是否显示value值的字符串*/
	gtk_scale_set_draw_value(GTK_SCALE(slider), TRUE);

	gtk_container_add(GTK_CONTAINER(window), slider);
	gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
	return 0;
}
