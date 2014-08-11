/*程序功能：按钮上面有图片，点击按钮，更换图片。
 * */

#include<gtk/gtk.h>

/*make a box with image and text label*/
GtkWidget *img_label_box(gchar *img_filename, gchar *label_text)
{
	GtkWidget *box;
	GtkWidget *img;
	GtkWidget *label;

	box = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 2);

	img = gtk_image_new_from_file(img_filename);
	gtk_box_pack_start(GTK_BOX(box), img, FALSE, FALSE, 3);
	gtk_widget_show(img);

	label = gtk_label_new(label_text);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE,3);
	gtk_widget_show(label);

	return box;
}

void callback(GtkWidget *widget, gpointer data)
{
	g_print("hello %s was pressed\n", (gchar*)data);
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box;
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),3);

	button = gtk_button_new();
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), "img_button");
	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_container_set_border_width(GTK_CONTAINER(button), 3);

	box = img_label_box("icon1.jpg", "icon1");
	gtk_container_add(GTK_CONTAINER(button), box);

	gtk_widget_show(box);
	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();
	return 0;

}

