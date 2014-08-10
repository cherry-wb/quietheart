/*本程序功能：
 * 1)右键单击按钮，会在相应的位置上面弹出一个菜单。
 * 2)连接了gdk事件
 * 需要注意的是，弹出菜单，不需要menubar了。
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
GtkWidget* createMenu2(gchar *menuName, GList *itemNames, GList *itemFunctions);

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
gboolean button_pressed(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("the button pressed \n");
	GtkMenu *menu;
	GdkEventButton *button_event;
	menu = GTK_MENU(data);
	if(event->type == GDK_BUTTON_PRESS)
	{
		button_event = (GdkEventButton*)event;
		if(button_event->button == 3)
		{
			/*关键！这里弹出建立好的菜单*/
			/*
			  void gtk_menu_popup(GtkMenu *menu,
			                      GtkWidget *parent_menu_shell,
						          GtkWidget *parent_menu_item,
						          GtkMenuPositionFunc func,
						          gpointer data,
						          guint button,
						          guint32 activate_time);
			 *menu:将要弹出的菜单
			 *parent_menu_shell:包含菜单项的menushell,可以为NULL
			 *parent_menu-item:激发弹出菜单的菜单项,可以为NULL
			 *func:用户指定的给菜单设置位置的位置函数，可以为NULL。
			 *data:func位置函数的参数。
			 *button:激发该事件的button pressed事件，如果不是这种事件如release，keypress，则此处为0
			 *activate_time:事件发生的时间，用户事件的时间戳，如果没有这样的事件可以用gtk_get_current_event_time().

			 func原型：
			 void (*GtkMenuPositionFunc)(GtkMenu *menu,
			                             gint *x,
									     gint *y,
									     gboolean *push_in,
									     gpointer user_data);
			其实只是在这个函数func里面给*x,*y,*push_in赋值就行了。

			 * */
			gtk_menu_popup(menu, NULL, NULL, NULL, NULL,
					button_event->button, button_event->time);
			return TRUE;
		}
	}
	return FALSE;
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *menu;
	
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

	/*创建菜单menu$$$$$$$$$$$$$*/
	/*各个菜单项名称*/
	menu_items = g_list_append(menu_items, "item1");
	menu_items = g_list_append(menu_items, "item2");
	menu_items = g_list_append(menu_items, "item3");
	/*各个回调函数*/
	active_functions = g_list_append(active_functions, menuItem_active1);
	active_functions = g_list_append(active_functions, menuItem_active2);
	active_functions = g_list_append(active_functions, menuItem_active3);
	/*这里真正创建菜单！*/
	menu = createMenu2("MenuName", menu_items, active_functions);
	/*如果没有这句话就无法显示弹出的菜单$$$$$$*/
	gtk_widget_show_all(menu);
	/*gtk_box_pack_start(GTK_BOX(vbox), menu,
			FALSE, FALSE, 3);*/

	/*创建button*/
	button = gtk_button_new_with_label("click here");
	/*连接探出菜单的回调函数*/
	g_signal_connect(G_OBJECT(button), "button_press_event",
			G_CALLBACK(button_pressed), GTK_OBJECT(menu));
	gtk_box_pack_start(GTK_BOX(vbox), button,
			FALSE, FALSE, 3);

	gtk_widget_show_all(window);
	gtk_main();
	g_list_free(menu_items);
	g_list_free(active_functions);
	return 0;
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
