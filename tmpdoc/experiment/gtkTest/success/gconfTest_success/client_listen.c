/*程序功能：一个简单的监听键值变化的程序。
 *主要实现：获取一个键值，添加一个键值目录，连接处理回调函数.
 * */

/*注意需要安装一个libgconf2-dev库。*/
#include <gconf/gconf-client.h>
#include <gtk/gtk.h>

/*回调函数：处理键值发生变化的事件
 *client:发生事件的gconf对象。
 *cnxn_id:gconf_client_notify_add的连接id
 *entry:存放GConf目录的一条记录，是一个key/value对,这里有发生变化的键值 
 *user_data:传到回调函数中的用户数据。
 * */
void
key_changed_callback(GConfClient* client,
		guint cnxn_id,
		GConfEntry *entry,
		gpointer user_data)
{
	GtkWidget* label;
	GConfValue *value;

	/*获得存放键值的对象*/
	value = gconf_entry_get_value(entry);

	label = GTK_WIDGET(user_data);

	if (value == NULL)
	{
		gtk_label_set_text(GTK_LABEL(label), "<unset>");
	}
	else
	{
		if (value->type == GCONF_VALUE_STRING)
		{/*$$$$$$这里获取键值的字符串值，并设置到label$$$$$$$*/
			gtk_label_set_text(GTK_LABEL(label), gconf_value_get_string(value));
		}
		else
		{
			gtk_label_set_text(GTK_LABEL(label), "<wrong type>");
		}
	}
}

int
main(int argc, char** argv)
{
	GtkWidget* window;
	GtkWidget* label;
	GConfClient* client;
	gchar* str;

	gtk_init(&argc, &argv);
	gconf_init(argc, argv, NULL);

	//client = gconf_client_new();//这个不行
	/*首先建立一个gconf对象*/
	client = gconf_client_get_default();

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	/*获取key指定的字符串值，如果出错则返回空,原型如下：
	 *gchar* gconf_client_get_string(GConfClient *client,
	                                 const gchar *key,
							         GError **err);
	 * */
	str = gconf_client_get_string(client, "/extra/test/directory/key",
			NULL);

	label = gtk_label_new(str ? str : "<unset>");

	if (str)
		g_free(str);

	gtk_container_add(GTK_CONTAINER(window), label);

	/*添加一个键值目录：
	 *void gconf_client_add_dir(GConfClient *client,
	                            const gchar *dir,
							    GConfClientPreloadType preload,
							    GError **err);
	 *client:一个gconf对象
	 *dir:将要添加的目录
	 *preload:告诉了如何提前加载它的目录,有三个值：
	 GCONF_CLIENT_PRELOAD_NONE	不预先加载.
	 GCONF_CLIENT_PRELOAD_ONELEVEL	预先加载这个目录的直接孩子.
	 GCONF_CLIENT_PRELOAD_RECURSIVE	递归预先加载这个目录下的所有孩子.
	 *err:出错信息，NULL表示忽略.
	 * gconf_client_remove_dir会移除一个目录，
	 * 这样会导致在这个目录键值上的侦听函数失效。
	 * 如果add了很多次必须要remove同样的次数。
	 *
	 * 注意，实践之后发现，如果用这句话，gconf-editor查看不会多这个目录。
	 * 但用gconftool-2 --type string -s /extra/test/directory/key test
	 * 修改键值，就多了这个目录，并且标签也显示了test,就算没有add用这个命令也会多这个目录。
	 * */
	gconf_client_add_dir(client,
			"/extra/test/directory",
			GCONF_CLIENT_PRELOAD_NONE,
			NULL);

	/* 为键值的变化添加一个回调函数。
	 * guint gconf_client_notify_add(GConfClient *client,
	 *                               const gchar *namespace_section,
	 *                               GConfClientNotifyFunc func,
	 *                               gpointer user_data,
	 *                               GFreeFunc destroy_notify,
	 *                               GError **err);
	 *namespace_section,是侦听的键值。
	 namespace_section键或者它的子键被改变，则调用回调函数，
	 为了让回调函数起作用，必须保证namespace_section在gconf_client_add_dir
	 添加的目录或目录之下。
	 *func,键值发生变化调用的函数。
	 *user_data,传给func回调函数的用户数据。
	 *destroy_notify,如果这个notify被移走或者client被析构则在user_data上调用,如果
	 空则什么都不做。
	 *err,错误信息，如果为NULL则忽略错误。
	 *返回：一个id，用于移除notify.(应该是***_notify_remove)
	 * */
	gconf_client_notify_add(client, "/extra/test/directory/key",
			key_changed_callback,
			label,
			NULL, NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

