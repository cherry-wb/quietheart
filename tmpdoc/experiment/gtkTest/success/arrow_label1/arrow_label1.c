/*这个程序实现了修改箭头方向的改变，标签文本的改变，以及字符串的比较操作*/
#include<gtk/gtk.h>

struct myData
{
	GtkArrow *arrow;
	GtkLabel *lLabel;
	GtkLabel *rLabel;
};
struct myData changeData;
void my_click_change(GtkWidget *widget, gpointer data)
{
	g_print("change arrow and label\n");
/*	struct myData *mypointer = (struct myData*)data;*/
/*	mypointer->lLabel;*/
	if(!g_strcmp0(gtk_label_get_text(((struct myData*)data)->lLabel), "clicked here") 
			&& !g_strcmp0(gtk_label_get_text(((struct myData*)data)->rLabel), "none"))
	/*if(gtk_label_get_text(((struct myData*)data)->lLabel)=="clicked here"
			&&gtk_label_get_text(((struct myData*)data)->rLabel)=="none")*/
	{
		gtk_arrow_set(((struct myData*)data)->arrow, GTK_ARROW_RIGHT, GTK_SHADOW_IN);
		gtk_label_set_text(((struct myData*)data)->rLabel, "clicked here");
		gtk_label_set_text(((struct myData*)data)->lLabel, "none");
	}
	else if(!g_strcmp0(gtk_label_get_text(((struct myData*)data)->rLabel), "clicked here") 
			&& !g_strcmp0(gtk_label_get_text(((struct myData*)data)->lLabel), "none"))
	/*else if(gtk_label_get_text(((struct myData*)data)->rLabel) == "clicked here"
			&&gtk_label_get_text(((struct myData*)data)->lLabel=="none"))*/
	{
		gtk_arrow_set(((struct myData*)data)->arrow, GTK_ARROW_LEFT, GTK_SHADOW_IN);
		gtk_label_set_text(((struct myData*)data)->lLabel, "clicked here");
		gtk_label_set_text(((struct myData*)data)->rLabel, "none");
	}
	else
	{
		gtk_label_set_text(((struct myData*)data)->lLabel, "error");
		gtk_label_set_text(((struct myData*)data)->rLabel, "error");
		gtk_arrow_set(((struct myData*)data)->arrow, GTK_ARROW_UP, GTK_SHADOW_OUT);
	}
}

gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *hbox;
	GtkWidget *lLabel;
	GtkWidget *rLabel;
	GtkWidget *button;
	GtkWidget *arrow;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);

	hbox = gtk_hbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(window), hbox);

	lLabel = gtk_label_new("clicked here");
	gtk_box_pack_start(GTK_BOX(hbox), lLabel,
			FALSE, FALSE, 3);

	button = gtk_button_new();
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(my_click_change), &changeData);
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 3);

	arrow = gtk_arrow_new(GTK_ARROW_LEFT, GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(button), arrow);

	rLabel = gtk_label_new("none");
	gtk_box_pack_start(GTK_BOX(hbox), rLabel,
			FALSE, FALSE, 3);

	changeData.arrow = GTK_ARROW(arrow);
	changeData.lLabel = GTK_LABEL(lLabel);
	changeData.rLabel = GTK_LABEL(rLabel);
	
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
