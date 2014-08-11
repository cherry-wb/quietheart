/*功能：创建自己的工具栏图标而不是系统的。
 * 
 * */

#include<gtk/gtk.h>
#include<unistd.h>
#define MY_BUTTON_ICON "my-button"

/*必须是绝对路径,图片的类型可以是png的*/
#define MY_ICON_PATH "/mnt/myOwn_all/experiment/program/gtkTest/myIconStock/button.png"
#define MY_BUTTON_ICON_FILE "/button.png"

 /*图标项的定义如下：
  typedef struct
  {
	gchar *stock_id; //对应的图标stock id
	gchar *label;
	GdkModifierType modifier;
	guint keyval;
	gchar *translation_domain;
  } GtkStockItem;
  * */
GtkStockItem item = {MY_BUTTON_ICON, NULL, 0, 0, NULL};
/*call back*/
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}

void iconInit()
{/*这里注册自己定义的图标*/

	/*这里路径必须是图标文件的绝对路径，设置的长度不能超过256个字符*/
	char icon_path[256];
	//char *icon_path;
	getcwd(icon_path, 256);
	strcat(icon_path, MY_BUTTON_ICON_FILE);
	g_print("the path get is:%s\n", icon_path);

	/*开始添加一个自己定义的图标$$$$$$$*/
	GtkIconFactory *factory = NULL;
	factory = gtk_icon_factory_new();

	GtkIconSource* iconSource = gtk_icon_source_new();
	gtk_icon_source_set_icon_name(iconSource, MY_BUTTON_ICON);
	//gtk_icon_source_set_filename(iconSource, MY_ICON_PATH);
	gtk_icon_source_set_filename(iconSource, icon_path);//必须是图标的绝对路径

	GtkIconSet* iconSet = gtk_icon_set_new();
	gtk_icon_set_add_source(iconSet, iconSource);
	gtk_icon_source_free(iconSource);
	gtk_icon_factory_add(factory, MY_BUTTON_ICON, iconSet);
	gtk_icon_set_unref(iconSet);

	/*向系统注册自己添加的图标,这里item可以是一个数组$$$$$$$*/
	gtk_stock_add_static(&item,1);
	gtk_icon_factory_add_default(factory);
	g_object_unref(factory);
}

/*main program*/
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *handlebox;
	GtkWidget *toolbar;

	GtkToolItem *toolItem;

	GtkToolItem *tool_button;
	GtkWidget *button;

	gtk_init(&argc, &argv);

	/*这句话可不能放到gtk_init的前面*/
	iconInit();

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

	/*toolbar, to handlebox*/
	toolbar = gtk_toolbar_new();
	/********设置工具栏的一些属性*/
	/*设置为水平工具栏*/
	gtk_toolbar_set_orientation(GTK_TOOLBAR (toolbar),
			GTK_ORIENTATION_HORIZONTAL);
	/*show_arrow默认参数是1,设置为0则显示所有添加的item了
	 * 不会出现空间不够不能显示的情况，因此窗口空间也不能缩太小*/
	gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar), 0);
	gtk_container_add (GTK_CONTAINER (handlebox), toolbar);

	/*toolbutton根据系统图标创建*/
	tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);


	/*toolbutton$$$$$$$$$$$$根据自己定义的图标创建*/
	tool_button = gtk_tool_button_new_from_stock (MY_BUTTON_ICON);
	//tool_button = gtk_tool_button_new_from_stock (GTK_STOCK_HOME);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),tool_button, 0);

	/*button, add to vbox*/
	button = gtk_button_new_with_label("separator_button");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
