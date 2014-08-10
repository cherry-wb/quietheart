/*程序功能：实现彩色label字体，可以设置字体颜色大小。
 * 点击按钮可以更换文字但是保持原来的字体风格。
 * 这个程序换颜色比上一个要好，功能应该更强。
 * */
#include<gtk/gtk.h>

void buttonClick(GtkWidget *widget, gpointer data)
{
	static gint textF = 1;
	textF ^= 1;
	gtk_label_set_text(GTK_LABEL(data),textF?"text1":"text2");
}
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "focus");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	label = gtk_label_new("test");

	/******set the attribute*******/
	//set the font size smaller
	PangoAttribute *pa_size = pango_attr_size_new (17000);
	pa_size->start_index = 0;
	pa_size->end_index = -1;
	PangoAttribute *pa_font = pango_attr_family_new ("Sans");
	pa_font->start_index = 0;
	pa_font->end_index = -1;
	PangoAttribute *pa_color = pango_attr_foreground_new(0x0000,0xFFFF,0xFFFF);
	pa_color->start_index = 0;
	pa_color->end_index = -1;
	PangoAttrList *pl = pango_attr_list_new();
	pango_attr_list_insert(pl,pa_size);
	pango_attr_list_insert(pl,pa_font);
	pango_attr_list_insert(pl,pa_color);

	gtk_label_set_attributes ((GtkLabel*)label, pl);
	pango_attr_list_unref (pl);
	/*************/
	gtk_box_pack_start(GTK_BOX(vbox), label,
			TRUE, TRUE, 0);
	button = gtk_button_new_with_label("changeText");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(buttonClick),label);

	gtk_box_pack_start(GTK_BOX(vbox), button,
			TRUE, TRUE, 0);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
