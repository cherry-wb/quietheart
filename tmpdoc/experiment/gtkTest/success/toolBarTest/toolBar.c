/*功能：工具栏上面添加各种功能，如工具栏属性，按钮，标签，工具按钮，菜单等等。
 * 
 *这里代码比较多，关键的部分用"$$$$$$$"字符串标记出来。
 *1)添加到工具栏上面的都是toolitem，所以:
 建立toolitem然后将你的构件container_add到toolitem上面。
 *2)如果直接添加按钮或者标签等，那么:
 gtk_toolbar_set_show_arrow设置为1的时候如果空间不够了，就不会显示
 需要建立一个ToolItem，把widget用container_add添加到ToolItem上面。
 *3)如果添加的是gtk_tool_button_new创建的按钮等，空间不够会显示下拉箭头来显示
 (当然这要有gtk_toolbar_set_show_arrow设置为1的时候才行。默认就是1).
 * */

#include<gtk/gtk.h>

/*call back*/
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}

void pop_menu(GtkWidget *button, gpointer data)
{
	GtkMenu *menu = GTK_MENU(data);
	g_print("pop\n");
	gtk_menu_popup(menu, NULL, NULL, NULL, NULL,
			0, gtk_get_current_event_time());
}
void menuItem_active(GtkMenuItem *menuitem, gpointer data)
{
	g_print("the menu %s is activate!\n",(gchar*)data);
}

/*man program*/
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *handlebox;
	GtkWidget *toolbar;

	GtkToolItem *toolItem;

	GtkToolItem *tool_button;
	GtkToolItem *separator;
	GtkToolItem *menu_tool_button;

	GtkWidget *label;
	GtkWidget *button;

	//GtkWidget *menuToolbar;
	//GtkWidget *rootMenu;
	GtkWidget *menu;
	GtkWidget *menuItem;

	gtk_init(&argc, &argv);

	//g_print("hi,the g_get_user_config_dir is:%s\n",g_get_user_config_dir());
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 500,100);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	/*vbox, to window*/
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	/*handlebox, to vbox*/
	handlebox = gtk_handle_box_new();
	gtk_box_pack_start(GTK_BOX(vbox), handlebox,
			TRUE, TRUE, 0);

	/*toolbar$$$$$$$$$, to handlebox*/
	toolbar = gtk_toolbar_new();
	/********设置工具栏的一些属性*/
	/*设置为水平工具栏*/
	gtk_toolbar_set_orientation(GTK_TOOLBAR (toolbar),
			GTK_ORIENTATION_HORIZONTAL);
	/*show_arrow默认参数是1,设置为0则显示所有添加的item了
	 * 不会出现空间不够不能显示的情况，因此窗口空间也不能缩太小*/
	gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar), 0);
	gtk_container_add (GTK_CONTAINER (handlebox), toolbar);

	/*button, to toolbar*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	/*toolItem$$$$$$$$$*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), button);
	/*可以直接添加按钮，但是如果分配的窗口大小不够的话就没有办法显示了*/
	/*如果是0则插到第一个位置，如果是负数则从结尾插入*/
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, -1);

	/*separator$$$$$$$$$$,to toolbar*/
	/*创建一个分割线*/
	separator = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, -1);

	/*label, to toolbar*/
	label = gtk_label_new("test1abel");
	/*toolItem*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), label);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, -1);

	/*separator,to toolbar*/
	separator = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, -1);

	/*toolbutton$$$$$$$$$$$,to toolbar*/
	/*GtkToolItem *gtk_tool_button_new(GtkWidget *icon_widget,
	 *                                 const gchar *label);
	 * */
	tool_button = gtk_tool_button_new(NULL, "toolbutton1");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, -1);

	/*toolbutton$$$$$$$$$$$$根据系统图标创建*/
	tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	tool_button = gtk_tool_button_new(NULL, "toolbutton2");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, -1);

	/*Menu, to toolbar*/
	//the menu "rootmenu1 in menu bar
	//menuToolbar = gtk_menu_bar_new();
	//rootMenu = gtk_menu_item_new_with_label("rootmenu1");
	menu = gtk_menu_new();
	menuItem = gtk_menu_item_new_with_label("item11");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item11");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_label("item12");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	//set the submenu for item12
	GtkWidget *sub2menu;
	GtkWidget *subMenuItem;
	sub2menu = gtk_menu_new();
	subMenuItem = gtk_menu_item_new_with_label("item121");
	g_signal_connect(G_OBJECT(subMenuItem), "activate",
			G_CALLBACK(menuItem_active), "item121");
	gtk_menu_shell_append(GTK_MENU_SHELL(sub2menu),subMenuItem);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), sub2menu);

	menuItem = gtk_menu_item_new_with_label("item13");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item13");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);
	//如果没有这句话就无法显示弹出的菜单
	gtk_widget_show_all(GTK_WIDGET(menu));

	//gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootMenu), menu);
	//gtk_menu_shell_append(GTK_MENU_SHELL(menuToolbar),rootMenu);

	/*第1种添加菜单的方法：弹出式菜单$$$$$$$*/
	tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_HOME);
	g_signal_connect(G_OBJECT(tool_button), "clicked",
			G_CALLBACK(pop_menu), menu);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*第2种添加菜单的方法:menu_tool_button$$$$$$$$*/
	/*GtkToolItem * gtk_menu_tool_button_new(GtkWidget *icon_widget,
	 *                                       const gchar *label);
	 * */
	menu_tool_button = gtk_menu_tool_button_new(NULL,"testMenu2");
	//gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(menu_tool_button), rootMenu);//不行，因为是menuitem
	//能够添加的前提是这个菜单必须之前没有被添加到别的menuitem上面
	gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(menu_tool_button), menu);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),menu_tool_button, 0);

	/*button, add to vbox*/
	button = gtk_button_new_with_label("separator_button");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(pop_menu), menu);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
