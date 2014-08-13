/*本程序功能：
 * 利用一个接口函数，结合GList方便地创建菜单
 * 这里创建的菜单是单个菜单项并且是单级的。
 * */
#include<gtk/gtk.h>

/*预计的接口
 *单级单项的菜单：menutoolbar->menu->menuitem
 GtkWidget* createMenu(gchar *menuName, glist *itemNames, glist *itemFunctions);
 void addMenu()
 *
 * */
typedef void (*CallBackFunc)(GtkMenuItem *menuitem, gpointer data);

/*创建菜单的接口
 *menuName:菜单项的名称
 *itemNames:菜单项的名称列表
 *itemNames:菜单项的回调函数列表
 * */
GtkWidget* createMenu(gchar *menuName, GList *itemNames, GList *itemFunctions);

/*回调函数*/
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
void button_clicked(GtkWidget *widget, gpointer data)
{
	g_print("the button clicked \n");
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *menuToolbar;
	GtkWidget *vbox;
	GtkWidget *button;
	
	GList *menu_items = NULL;
	GList *active_functions = NULL;

	gtk_init(&argc, &argv);

	/*创建window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	/*创建vbox*/
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	/*创建菜单栏menubar$$$$$$$$$$$$$*/
	/*各个菜单项名称*/
	menu_items = g_list_append(menu_items, "item1");
	menu_items = g_list_append(menu_items, "item2");
	menu_items = g_list_append(menu_items, "item3");
	/*各个回调函数*/
	active_functions = g_list_append(active_functions, menuItem_active1);
	active_functions = g_list_append(active_functions, menuItem_active2);
	active_functions = g_list_append(active_functions, menuItem_active3);
	/*这里真正创建菜单！*/
	menuToolbar = createMenu("MenuName", menu_items, active_functions);
	gtk_box_pack_start(GTK_BOX(vbox), menuToolbar,
			FALSE, FALSE, 3);

	/*创建button*/
	button = gtk_button_new_with_label("click here");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(button_clicked), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			FALSE, FALSE, 3);

	gtk_widget_show_all(window);
	gtk_main();
	g_list_free(menu_items);
	g_list_free(active_functions);
	return 0;
}
GtkWidget* createMenu(gchar *menuName, GList *itemNames, GList *itemFunctions)
{
	GtkWidget *menuToolbar;
	GtkWidget *rootMenu;
	GtkWidget *menu;
	GtkWidget *menuItem;

	menuToolbar = gtk_menu_bar_new();
	rootMenu = gtk_menu_item_new_with_label(menuName);
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

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootMenu), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuToolbar),rootMenu);

	return menuToolbar;
}
