/*程序功能：改变gconf的键值。
 * 要求，先把 client_listen程序启动。
 * 一个按钮，一个文本输入框，
 * 如果输入文本点击按钮，那么会把键值设置为文本框内的内容。
 * 如果在文本框内回车，会调用激活文本框的函数，打印一个haha....
 * */

#include <gconf/gconf-client.h>
#include <gtk/gtk.h>
struct My_Data
{
	GConfClient *client;
	GtkWidget *entry;
} gconf_entry;

typedef struct My_Data *Gconf_Entry;
void button_callback(GtkWidget *widget, gpointer data)
{
	GConfClient* client;
	GtkWidget *entry;
	gchar* str;

	client = GCONF_CLIENT(((Gconf_Entry)data)->client);
	entry = GTK_WIDGET(((Gconf_Entry)data)->entry);
	str = gtk_editable_get_chars(GTK_EDITABLE(entry), 0, -1);

	gconf_client_set_string(client, "/extra/test/directory/key",
			str, NULL);

	g_free(str);
}
void
entry_activated_callback(GtkWidget* entry, gpointer user_data)
{
	g_print("haha,entry activated!\n");
}

	int
main(int argc, char** argv)
{
	GtkWidget* window;
	GtkWidget* hbox;
	GtkWidget* entry;
	GtkWidget* button;
	GConfClient* client;
	Gconf_Entry mydata;

	gtk_init(&argc, &argv);
	gconf_init(argc, argv, NULL);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	/*hbox*/
	hbox = gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), hbox);

	/*button*/
	button = gtk_button_new_with_label("button1");
	gtk_box_pack_start(GTK_BOX(hbox), button,
			TRUE, TRUE, 0);

	/*entry*/
	entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), entry,
			TRUE, TRUE, 0);

	/*gconf*/
	//client = gconf_client_new();//这个不行
	client = gconf_client_get_default ();

	gconf_client_add_dir(client,
			"/extra/test/directory",
			GCONF_CLIENT_PRELOAD_NONE,
			NULL);


	gconf_entry.entry = entry;
	gconf_entry.client = client;
	mydata = &gconf_entry;
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(button_callback), mydata);
	g_signal_connect(GTK_OBJECT(entry), "activate",
			G_CALLBACK(entry_activated_callback),
			NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

