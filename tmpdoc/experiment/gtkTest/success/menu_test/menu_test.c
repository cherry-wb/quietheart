/*程序功能：
 *演示菜单创建的方法，这里还创建了多级菜单。
 *
 *菜单添加关系：
 menutoolbar
 <--(gtk_menu_shell_append)-menu(一级菜单)
 <--(gtk_menu_shell_append)-menuitem(一级菜单项)
 <--(gtk_menu_item_set_submenu)-menu(二级菜单)
 <--(gtk_menu_shell_append)-menuitem(二级菜单项)
 *...同上更多的级数...
 * */
#include<gtk/gtk.h>
void menuItem_active(GtkMenuItem *menuitem, gpointer data)
{
	g_print("the menu %s is activate!\n",(gchar*)data);
}
void button_clicked(GtkWidget *widget, gpointer data)
{
	g_print("the button clicked \n");
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *menuToolbar;
	GtkWidget *rootMenu;
	GtkWidget *menu;
	GtkWidget *menuItem;
	GtkWidget *vbox;
	GtkWidget *button;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	menuToolbar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(vbox), menuToolbar,
			FALSE, FALSE, 3);

	/*the menu "rootmenu1 in menu bar*/
	rootMenu = gtk_menu_item_new_with_label("rootmenu1");
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

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootMenu), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuToolbar),rootMenu);

	/*the menu "rootmenu2 in menu bar*/
	rootMenu = gtk_menu_item_new_with_label("rootmenu2");
	menu = gtk_menu_new();
	menuItem = gtk_menu_item_new_with_label("item21");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item21");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_label("item22");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item22");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);


	menuItem = gtk_menu_item_new_with_label("item23");
	g_signal_connect(G_OBJECT(menuItem), "activate",
			G_CALLBACK(menuItem_active), "item23");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);
	/*set the submenu for item23*/
	sub2menu = gtk_menu_new();
	subMenuItem = gtk_menu_item_new_with_label("item231");
	g_signal_connect(G_OBJECT(subMenuItem), "activate",
			G_CALLBACK(menuItem_active), "item231");
	gtk_menu_shell_append(GTK_MENU_SHELL(sub2menu),subMenuItem);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), sub2menu);


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootMenu), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuToolbar),rootMenu);


	button = gtk_button_new_with_label("click here");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(button_clicked), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			FALSE, FALSE, 3);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
