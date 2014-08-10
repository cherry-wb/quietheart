/*程序功能：
 * 1)一个gtklist控件中添加单选组.
 * 单选的group用释放吗？
 * 2)清除列表的内容.
 * 
 * 另外：
 * 查看child的位置用如下函数（没有根据位置返回child的?）。
 * gint gtk_list_child_position(GtkList *list,
 *                                GtkWidget *child);
 * */
#include<gtk/gtk.h>
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}

void clear_list(GtkWidget *gtk_list)
{
	g_print("hello, clear!\n");
	/*这里清空列表。
	 *
	 *清除[start,end)范围内的元素,如下：
	 *gtk_list_clear_items(GtkList *list, gint start, gint end);
	 *start表示其实元素(若大于等于end则什么也不做)
	 *end表示终止元素(如果是负数或者是大于元素数则认为是元素数)
	 *假设有三个元素，那么
	 *start = 0的话第一个元素被删除。
	 *start = 1的话第一个元素不被删除掉的。
	 *end = 2的话最后一个元素不被删除。
	 *end = 3则最后一个元素会被删除。
	 *综上，所以第一个应该是1而不是0.
	 * */
	gtk_list_clear_items(GTK_LIST(gtk_list), 0, -1);
}

gboolean my_button(GtkWidget *button, gpointer data)
{
	GtkWidget *gtk_list = GTK_WIDGET(data);
	clear_list(gtk_list);
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button;

	GtkWidget *gtk_list;
	GtkWidget *listitem;
	GtkWidget *elementItem;
	GSList *group;
	GtkWidget *radio;
	gtk_init(&argc, &argv);

	/*这里必须先初始化GList，否则不行*/
	group = NULL;

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello world2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	/*hbox*/
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	/*list*/
	/*给每个listitem添加一个gtkwidget之后在添加到列表中*/
	gtk_list = gtk_list_new();
	listitem = gtk_list_item_new();
	radio = gtk_radio_button_new_with_label(group, "first");
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));//得到链表首
	gtk_container_add(GTK_CONTAINER(listitem), radio);
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);

	listitem = gtk_list_item_new();
	radio = gtk_radio_button_new_with_label(group, "second");
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	gtk_container_add(GTK_CONTAINER(listitem), radio);
	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);

	listitem = gtk_list_item_new();
	radio = gtk_radio_button_new_with_label(group, "third");
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	gtk_container_add(GTK_CONTAINER(listitem), radio);

	gtk_container_add(GTK_CONTAINER(gtk_list), listitem);
	gtk_widget_show_all(gtk_list);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_list,
			TRUE, TRUE, 0);

	button = gtk_button_new_with_label("clear!");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(my_button), gtk_list);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
