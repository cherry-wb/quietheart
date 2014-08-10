/*label的对齐和指定label的大小
 * 主要测试了申请固定大小的label
 * 以及设置label字体的对齐方式
 * 结果：
 * 如果没有任何设置那么对齐方式为：居中方式。
 * 如果设置单行的那么函数
	gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_RIGHT);
	不管用
	应该使用函数
	gtk_misc_set_alignment(GTK_MISC(label1), 0,0);
 * 有待改进和更新
 * */
#include<gtk/gtk.h>
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *alignment1;
	GtkWidget *alignment2;
	GtkWidget *label1;
	GtkWidget *label2;
	//GtkWidget *button2;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	label1 = gtk_label_new("label1");
	/*设置对齐方式，不管用？原因对于单行来说这个函数不管用,官方文档说过的*/
	//gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_RIGHT);
	//gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_FILL);
	/*  void gtk_label_set_justify( GtkLabel         *label,
	 *                              GtkJustification  jtype );
	 *  有以下对齐方式
	 *  GTK_JUSTIFY_LEFT  左对齐
	 *  GTK_JUSTIFY_RIGHT  右对齐
	 *  GTK_JUSTIFY_CENTER  居中对齐(默认)
	 *  GTK_JUSTIFY_FILL  充满
	 * */
	/*指定构件的大小,这个函数管用*/
	//gtk_widget_set_size_request (label1, 300, 50);


	/*设置对齐布局，此处管用,对于单行的来说这个函数才管用，见官方文档*/
	gtk_misc_set_alignment(GTK_MISC(label1), 0,0);
	/*alignment不管用?,可能也是多行才管用吧？*/
	/*alignment1 = gtk_alignment_new(0,0,300,50);
	gtk_widget_set_size_request (alignment1, 300, 50);*/
	gtk_box_pack_start(GTK_BOX(vbox), label1,
			TRUE, TRUE, 0);
	//gtk_container_add(GTK_CONTAINER(alignment1), label1);

	label2 = gtk_label_new("label2, this is very long!");
	/*指定构件的大小*/
	gtk_widget_set_size_request (label2, 300, 50);
	gtk_misc_set_alignment(GTK_MISC(label2), 0,0);
	
	//alignment2 = gtk_alignment_new(0,0,300,50);
	//gtk_widget_set_size_request (alignment2, 300, 50);
	gtk_box_pack_start(GTK_BOX(vbox), label2,
			TRUE, TRUE, 0);
	//gtk_container_add(GTK_CONTAINER(alignment2), label2);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
