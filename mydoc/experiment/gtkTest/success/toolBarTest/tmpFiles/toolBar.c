/*功能：一个简单的模板程序：
 *一个窗口，一个按钮
 *1)如果直接添加按钮或者标签等，那么
 gtk_toolbar_set_show_arrow设置为1的时候如果空间不够了，就不会显示
 需要建立一个ToolItem，把widget用container_add添加到ToolItem上面。
 *2)如果添加的是gtk_tool_button_new创建的按钮等，空间不够会显示下拉箭头来显示
 (当然这要有gtk_toolbar_set_show_arrow设置为1的时候才行。默认就是1).
 * */

#include<gtk/gtk.h>
typedef void (*CallBackFunc)(GtkMenuItem *menuitem, gpointer data);

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

void menuItem_active1(GtkMenuItem *menuitem, gpointer data)
{
	g_print("the menuitem1 %s is activate!\n",(gchar*)data);
}
void menuItem_active2(GtkMenuItem *menuitem, gpointer data)
{
	g_print("the menuitem2 %s is activate!\n",(gchar*)data);
}
void menuItem_active3(GtkMenuItem *menuitem, gpointer data)
{
	g_print("the menuitem3 %s is activate!\n",(gchar*)data);
}

GtkWidget* createMenu2(gchar *menuName, GList *itemNames, GList *itemFunctions)
{
	GtkWidget *menu;
	GtkWidget *menuItem;

	menu = gtk_menu_new();

	while(itemNames && itemFunctions)
	{/*加载menuitem*/
		gchar *itemName = (gchar*)itemNames->data;
		CallBackFunc activeCallBack = (CallBackFunc)itemFunctions->data;

		menuItem = gtk_menu_item_new_with_label(itemName);
		g_signal_connect(G_OBJECT(menuItem), "activate",
				G_CALLBACK(activeCallBack), itemName);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

		itemNames = g_list_next(itemNames);
		itemFunctions = g_list_next(itemFunctions);
	}

	return menu;
}
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

	GtkWidget *button;
	GtkWidget *label;

	//GtkWidget *menuToolbar;
	//GtkWidget *rootMenu;
	GtkWidget *menu;
	GtkWidget *menuItem;

	GtkWidget *menu2;
	GList *menu_items = NULL;
	GList *active_functions = NULL;
	gtk_init(&argc, &argv);

	g_print("hi,the g_get_user_config_dir is:%s\n",g_get_user_config_dir());
	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 500,100);
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	/*vbox*/
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	/*handlebox*/
	handlebox = gtk_handle_box_new();
	gtk_box_pack_start(GTK_BOX(vbox), handlebox,
			TRUE, TRUE, 0);

	/*toolbar*/
	toolbar = gtk_toolbar_new();

	/********设置工具栏的一些属性*/
	/*设置为水平工具栏*/
	gtk_toolbar_set_orientation(GTK_TOOLBAR (toolbar),
			GTK_ORIENTATION_HORIZONTAL);
	/*show_arrow默认参数是1,设置为0则显示所有添加的item了
	 * 不会出现空间不够不能显示的情况，因此窗口空间也不能缩太小*/
	gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar), 0);
	gtk_container_add (GTK_CONTAINER (handlebox), toolbar);


	/*button*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	/*toolItem*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), button);
	/*可以直接添加按钮，但是如果分配的窗口大小不够的话就没有办法显示了*/
	/*如果是0则插到第一个位置，如果是负数则从结尾插入*/
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, -1);

	/*separator*/
	/*创建一个分割线*/
	separator = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, -1);

	/*label*/
	label = gtk_label_new("test1abel");
	/*toolItem*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), label);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, -1);

	/*separator*/
	separator = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, -1);

	/*toolbutton*/
	/*GtkToolItem *gtk_tool_button_new(GtkWidget *icon_widget,
	 *                                 const gchar *label);
	 * */
	tool_button = gtk_tool_button_new(NULL, "toolbutton1");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, -1);

	/*toolbutton根据系统图标创建*/
	tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*toolbutton*/
	tool_button = gtk_tool_button_new(NULL, "toolbutton2");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, -1);

	/*toolbutton*/
	tool_button = gtk_tool_button_new(NULL, "toolbutton3");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*toolbutton*/
	tool_button = gtk_tool_button_new(NULL, "toolbutton4");
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*button*/
	button = gtk_button_new_with_label("hello2");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	/*toolItem*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), button);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, 0);

	/*button*/
	button = gtk_button_new_with_label("hello3");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	/*toolItem*/
	toolItem = gtk_tool_item_new();
	gtk_container_add(GTK_CONTAINER(toolItem), button);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, -1);


	/*void gtk_tool_item_set_proxy_menu_item(GtkToolItem *tool_item,
			                               const gchar *menu_item_id,
										   GtkWidget *menu_item);*/
	/*about Menu*/
	/*the menu "rootmenu1 in menu bar*/
	//menuToolbar = gtk_menu_bar_new();
	//rootMenu = gtk_menu_item_new_with_label("rootmenu1");
	menu = gtk_menu_new();
	menuItem = gtk_menu_item_new_with_label("item11");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item11");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_label("item12");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	
	/*set the submenu for item12*/
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

	//gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootMenu), menu);
	//gtk_menu_shell_append(GTK_MENU_SHELL(menuToolbar),rootMenu);

	/*第1中添加菜单的方法：弹出式菜单*/
	/*toolbutton根据系统图标创建*/
	tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_HOME);
	g_signal_connect(G_OBJECT(tool_button), "clicked",
			G_CALLBACK(pop_menu), menu);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*menu_tool_button,第2种添加菜单的方法,有响应但没有子菜单？难道gtk版本少*/
	/*GtkToolItem * gtk_menu_tool_button_new(GtkWidget *icon_widget,
	 *                                       const gchar *label);
	 * */
	menu_tool_button = gtk_menu_tool_button_new(NULL,"testMenu2");
	//gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(menu_tool_button), rootMenu);//不行，因为是menuitem
	/*能够添加的前提是这个菜单必须之前没有被添加到别的menuitem上面*/
	gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(menu_tool_button), menu);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),menu_tool_button, 0);

	/*toolItem,第3种添加菜单的方法(失败)*/
	//toolItem = gtk_tool_item_new();
	//gtk_tool_item_set_proxy_menu_item(toolItem, "testMenu", menuToolbar);//不行
	//gtk_tool_item_set_proxy_menu_item(toolItem, "testMenu", menu);//不行
	//gtk_tool_item_set_proxy_menu_item(toolItem, "testMenu", rootMenu);
	//添加不管用
	//gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, 0);

	/*toolItem,第4种添加菜单的方法(失败)*/
	//toolItem = gtk_tool_item_new();
	/*添加的前提是不能把rootMenu事先添加到别的构建上面。*/
	//添加之后单击菜单没有反应。
	//gtk_container_add(GTK_CONTAINER(toolItem), rootMenu);
	//gtk_toolbar_insert(GTK_TOOLBAR(toolbar),toolItem, 0);


	/*menu2*/
	/*各个菜单项名称*/
	menu_items = g_list_append(menu_items, "item1");
	menu_items = g_list_append(menu_items, "item2");
	menu_items = g_list_append(menu_items, "item3");
	/*各个回调函数*/
	active_functions = g_list_append(active_functions, menuItem_active1);
	active_functions = g_list_append(active_functions, menuItem_active2);
	active_functions = g_list_append(active_functions, menuItem_active3);
	/*这里真正创建菜单！*/
	menu2 = createMenu2("MenuName", menu_items, active_functions);
	gtk_widget_show_all(menu);

	/*button*/
	button = gtk_button_new_with_label("separator_button");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(pop_menu), menu2);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	g_list_free(menu_items);
	g_list_free(active_functions);
	return 0;
}
