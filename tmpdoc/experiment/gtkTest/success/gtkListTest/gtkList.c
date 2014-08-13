/*程序功能：一个gtklist控件的实例
 *gtklist控件现在已经不用了，它被gtktreeview给替代了。
 *1)这个程序用两种方法建立gtklist列表框，
 *2)然后给出为列表框item添加控件的方法
 *3)添加一个分割线标明每个list之间的空档
 */
#include<gtk/gtk.h>
int delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *separator;
	GtkWidget *gtk_list;
	GList *items;
	GList *copy;
	GtkWidget *listitem;
	GtkWidget *elementItem;
	GtkWidget *check;
	gtk_init(&argc, &argv);

	/*这里必须先初始化GList，否则不行*/
	items = NULL;
	copy = NULL;

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	/*vbox*/
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	/*list1*/
	/*第一个添加列表的方法，利用多次container_add*/
	gtk_list = gtk_list_new();
	listitem = gtk_list_item_new_with_label("1first");
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	listitem = gtk_list_item_new_with_label("1second");
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	listitem = gtk_list_item_new_with_label("1third");
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	gtk_widget_show_all(gtk_list);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list,
			TRUE, TRUE, 0);

	/*添加一个分割线标明每个list之间的空档*/
	separator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox), separator,
			TRUE, TRUE, 0);

	/*list2*/
	/*第二个添加列表的方法，利用GList*/
	gtk_list = gtk_list_new();
	listitem = gtk_list_item_new_with_label("2first");
	items = g_list_append(items, listitem);
	listitem = gtk_list_item_new_with_label("2second");
	items = g_list_append(items, listitem);
	listitem = gtk_list_item_new_with_label("2third");
	items = g_list_append(items, listitem);
	/*这里实际不用释放Glist???这里最好利用copy先拷贝一份用拷贝建立列表*/
	copy = g_list_copy(items);
	g_list_free(items);
	items = NULL;
	gtk_list_append_items(GTK_LIST(gtk_list), copy);
	gtk_widget_show_all(gtk_list);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list,
			TRUE, TRUE, 0);

	/*添加一个分割线标明每个list之间的空档*/
	separator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox), separator,
			TRUE, TRUE, 0);

	/*list3*/
	/*给每个listitem添加一个gtkwidget之后在添加到列表中*/
	gtk_list = gtk_list_new();
	listitem = gtk_list_item_new();
	check = gtk_check_button_new_with_label("3first");
	gtk_container_add(GTK_CONTAINER(listitem), check);
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	listitem = gtk_list_item_new();
	check = gtk_check_button_new_with_label("3second");
	gtk_container_add(GTK_CONTAINER(listitem), check);
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	listitem = gtk_list_item_new();
	check = gtk_check_button_new_with_label("3third");
	gtk_container_add(GTK_CONTAINER(listitem), check);
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	gtk_widget_show_all(gtk_list);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
