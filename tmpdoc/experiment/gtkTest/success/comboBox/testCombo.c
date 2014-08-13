#include<gtk/gtk.h>
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
    GtkWidget		 *combo;	/*StatusBar上面的组合框 */
    GList *options = NULL;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "combobox");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	combo = gtk_combo_new();
    options = g_list_append(options, "Google");
    options = g_list_append(options, "Baidu");
    gtk_combo_set_popdown_strings(GTK_COMBO(combo), options);/*将列表项添加到组合框中*/
    gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(combo)->entry), "");/*如果没有就默认第一个*/
	gtk_editable_set_editable(GTK_EDITABLE(GTK_COMBO(combo)->entry), FALSE);/*默认可以编辑*/
	gtk_container_add(GTK_CONTAINER(window), combo);
	
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
