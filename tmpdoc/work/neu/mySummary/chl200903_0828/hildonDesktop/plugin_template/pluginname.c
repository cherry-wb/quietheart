/*change for new plugin:
 * PluginName -> your PluginName
 * pluginname -> your pluginname
 * plugin_name -> your plugin_name
 * */
#include <libhildondesktop/hildon-status-bar-item.h>
#include <libhildondesktop/libhildondesktop.h>


typedef struct
{
	HildonStatusBarItem *item;
	GtkWidget *button;
}PluginNamePlugin;

static void on_clicked(GtkWidget *button, gpointer data)
{/*lkcomment点击状态栏上面的pluginname按钮相应的映射函数,会弹出菜单*/
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new (NULL,
			GTK_DIALOG_MODAL |
			GTK_DIALOG_DESTROY_WITH_PARENT |
			GTK_DIALOG_NO_SEPARATOR,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"close-app111");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

static void *plugin_name_initialize(HildonStatusBarItem *item, GtkWidget **button)
{
	GtkWidget *image = NULL;
	PluginNamePlugin *my_plugin = g_new0(PluginNamePlugin, 1);
	my_plugin->item = item;
	*button = my_plugin->button = gtk_button_new();
	//image = gtk_image_new_from_icon_name("gnome-window-manager", GTK_ICON_SIZE_MENU);
	image = gtk_image_new_from_file("/usr/local/share/image/pluginname.png");
	gtk_widget_show(image);
	gtk_container_add(GTK_CONTAINER(*button), image);
	g_signal_connect(G_OBJECT(*button), "clicked",
					 G_CALLBACK(on_clicked), NULL);
	gtk_widget_show_all(*button);
	return (void *)my_plugin;
}


static void plugin_name_update(void *data, gint value1, gint value2, const gchar *str)
{
	if (data != NULL)
	{
		PluginNamePlugin *my_plugin = (PluginNamePlugin *) data;
		if (value1 == 0)
			gtk_widget_destroy(GTK_WIDGET(my_plugin->item));
		else
			gtk_widget_show_all(my_plugin->button);
	}
}


static void plugin_name_destroy(void *data)
{
    if(data != NULL)
    {
      g_free(data);
    }
}


void pluginname_entry(HildonStatusBarPluginFn_st *fn) 
{ 
	if(fn != NULL)
	{ 
		fn->initialize = plugin_name_initialize; 
		fn->destroy = plugin_name_destroy; 
		fn->update = plugin_name_update; 
	}
} 

