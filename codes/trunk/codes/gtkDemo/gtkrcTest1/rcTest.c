/*程序功能：指定构建的资源文件，以及切换主题
 *
 *
 * */

#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	static int flag = 0;
	g_print("hello,change themes\n");
	//gtk_rc_parse("myrc2");/*暂时还不能用换文件的方式*/
	if(flag == 0)
	{
		gtk_widget_set_name (GTK_WIDGET(data),"myWindow2");/*设置另一个名字*/
	}
	else
	{
		gtk_widget_set_name (GTK_WIDGET(data),"myWindow");/*设置名字*/
	}
	flag ^=1;
	gtk_rc_reparse_all();/*重新载入*/
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
	GtkWidget *vbox;/*以window作为父container*/
	GtkWidget *hbox;/*以vbox作为父widget,vbox中包含两个hbox*/
	GtkWidget *button;/*以hbox作为父widget*/
	GtkWidget *label;/*以hbox作为父widget*/

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

	/*vbox*/
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_set_name (vbox,"myVbox");

	/*hbox1*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox,
			TRUE, TRUE, 20);
//	gtk_container_set_border_width(GTK_CONTAINER(hbox),20);
	gtk_widget_set_name (hbox,"myHbox1");

	/*button1*/
	button = gtk_button_new_with_label("button1");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), window);
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);
	gtk_widget_set_name (button,"myButton1");

	/*label1*/
	label = gtk_label_new("label1");
	gtk_box_pack_start(GTK_BOX(hbox), label,
			TRUE, TRUE, 10);
	gtk_widget_set_name (label,"myLabel1");

	/*hbox2*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox,
			TRUE, TRUE, 20);
//	gtk_container_set_border_width(GTK_CONTAINER(hbox),20);
	gtk_widget_set_name (hbox,"myHbox2");

	/*button2*/
	button = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 10);
	gtk_widget_set_name (button,"myButton2");

	/*label2*/
	label = gtk_label_new("label2");
	gtk_box_pack_start(GTK_BOX(hbox), label,
			TRUE, TRUE, 0);
	gtk_widget_set_name (label,"myLabel2");


	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
//to be continuted
