/*程序功能：
 * 1)用GtkUIManager,GtkActionGroup快速建立界面建立一个菜单和一个工具条。
 * 2)获取并使用建立的界面中的各个构建。
 * 
 * */

#include "actionUi.h"

void
on_action_window_new_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_tab_new_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_toolbar_bookmarks_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_panels_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_refresh_stop_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_back_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_forward_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void
on_action_home_activate(GtkAction *action, gchar *data)
{
	g_print("%s\n", data);
}

void action_init(GtkActionGroup **actiongroup, GtkUIManager **ui_manager)
{
	*actiongroup = gtk_action_group_new("Browser");

	/*添加动作到动作组，函数原型如下：
	  void gtk_action_group_add_actions(GtkActionGroup *action_group,
	  const GtkActionEntry *entries,
	  guint n_entries,
	  gpointer user_data);
	  意义很明显，
	  action_group是要添加到的组，
	  entries是要添加的动作数组
	  n_entries是待添加的动作中的动作元素数目
	  user_data应该就是给每个动作回调函数传入的参数。
	 * */
	gtk_action_group_add_actions(*actiongroup, menu_entries, menu_entries_n, "hi,in menu");
	gtk_action_group_add_actions(*actiongroup, toolbar_entries, toolbar_entries_n, "hi,in toolbar");

	/*添加动作相关信息到待建立的界面中*/
	*ui_manager = gtk_ui_manager_new();
	gtk_ui_manager_insert_action_group(*ui_manager, *actiongroup, 0);
}

void ui_init(GtkActionGroup **actiongroup, GtkUIManager **ui_manager)
{
	GError* error = NULL;
	GtkAction* action;
	guint i;
	/*添加界面相关信息*/
	if(!gtk_ui_manager_add_ui_from_string(*ui_manager, ui_markup, -1, &error))
	{
		g_message("User interface couldn't be created: %s", error->message);
		g_error_free(error);
	}

	for(i = 0; i < menu_entries_n; i++)
	{
		action = gtk_action_group_get_action(*actiongroup, menu_entries[i].name);

		/*这里设置菜单是否可以激活*/
		gtk_action_set_sensitive(action,
				menu_entries[i].callback || !menu_entries[i].tooltip);
	}

	for(i = 0; i < toolbar_entries_n; i++)
	{
		action = gtk_action_group_get_action(*actiongroup,
				toolbar_entries[i].name);

		/*这里设置菜单是否可以激活*/
		gtk_action_set_sensitive(action,
				toolbar_entries[i].callback || !toolbar_entries[i].tooltip);
	}

}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *menubar;
	GtkWidget *subMenu;
	GtkWidget *menuitem;

	GtkWidget *toolbar;

	GtkActionGroup* actiongroup;
	GtkUIManager* ui_manager;//主界面，包含了待建立的界面和相关的动作

	gtk_init(&argc, &argv);

	/**********初始化主界面$$$$$$$$**********{*/
	/*初始化主界面相关动作信息*/
	action_init(&actiongroup, &ui_manager);
	/*初始华主界面具体界面信息*/
	ui_init(&actiongroup, &ui_manager);
	/**********初始化主界面$$$$$$$$**********}*/

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy"
			, G_CALLBACK(gtk_main_quit), NULL);
	/*添加快捷键*/
	gtk_window_add_accel_group(GTK_WINDOW(window),
			gtk_ui_manager_get_accel_group(ui_manager));

	/*vbox*/
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	/***********使用、设置主界面中的元素$$$$$$******{*/
	/*从主界面获取一个部件的方法,便于添加到窗口中为什么这里有一个警告？*/
	menubar = gtk_ui_manager_get_widget(ui_manager, "/menubar");
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	/*从主界面获取一个菜单项的方法,获取之后设置其属性*/
	menuitem = gtk_ui_manager_get_widget(ui_manager, "/menubar/Menu1/menuitem1.1");
	/*从主界面把本来可以点击的菜单按钮设置为无法点击，非激活状态，工具栏上面仍然可以点*/
	gtk_widget_set_sensitive(GTK_WIDGET(menuitem),
			FALSE);

	/*从主界面获取一个子菜单的方法,获取之后添加一个额外不属于主界面的菜单*/
	subMenu = gtk_menu_item_get_submenu(
			GTK_MENU_ITEM(gtk_ui_manager_get_widget(ui_manager, "/menubar/Menu2")));
	/*可以添加2个额外的分割线*/
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(subMenu), menuitem);
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(subMenu), menuitem);
	menuitem = gtk_menu_item_new_with_label("added out the Ui");
	gtk_menu_shell_append(GTK_MENU_SHELL(subMenu), menuitem);
	gtk_widget_show_all(GTK_WIDGET(subMenu));//此处如果不写，那么即使后面有window的show_all那也没法显示这个菜单.

	/*从主界面获取工具栏的部件*/
	toolbar = gtk_ui_manager_get_widget(ui_manager, "/toolbar_navigation");
	gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar), 0);
	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

	g_object_unref(ui_manager);
	/***********使用、设置主界面中的元素$$$$$$******}*/

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
