/*this program is used to test the grab_point 
 * 程序功能：让一个构建在鼠标离开它的时候仍然能够捕捉指定的鼠标事件
 * 点击到button1上面之后，需要再点击3次才能够释放指针，否则只能响应button1的button-press-event
 * */
#include<gtk/gtk.h>
void my_button1_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	static int grab = 0;
	if(grab < 3)
	{
	//捕捉之后无论点击哪里都只响应button1的button-press-event了，除非button1释放鼠标指针
		g_print("button1 pressed\n");
		gtk_grab_add (GTK_WIDGET(data));/*如果没有这句话的话，即使pointer_grab也不起作用*/
		/*捕捉鼠标事件*/
		gdk_pointer_grab(GTK_WIDGET(data)->window, TRUE,
			(GdkEventMask)(GDK_BUTTON_PRESS_MASK),
			(GdkWindow *)NULL, NULL, GDK_CURRENT_TIME);
		++grab;
		/*
		   GdkGrabStatus  gdk_pointer_grab(GdkWindow *window,
		   gboolean owner_events,
		   GdkEventMask event_mask,
		   GdkWindow *confine_to,
		   GdkCursor *cursor,
		   guint32 time_);
含义理解：（仅供参考）
window :
	捕获鼠标的（构件的）gdk窗口
owner_events :
	如果FALSE那么所有的pointer事件都是关于window的，并且只响应event_mask指定的。
	如果TRUE那么在构件上的pointer事件正常响应，构建外的同false只响应mask指定的。
event_mask :
	结合owner_events指定哪些事件为mask,即被响应。
confine_to :
	If non-NULL, the pointer will be confined to this window during the grab. If the pointer is outside confine_to, it will automatically be moved to the closest edge of confine_to and enter and leave events will be generated as necessary.
	如果非空，那么pointer在grab时将会被限制在指定window,如果超过了这个限制，那么
	pointer将自动移动到window的边缘，发送enter和leave事件。
cursor :
	the cursor to display while the grab is active. If this is NULL then the normal cursors are used for window and its descendants, and the cursor for window is used for all other windows.
	指定grab激活的时候cusor的显示，如果为NULL那么使用正常cursor
time_ :
	导致grab pointer的事件的时间戳，如果不知道就GDK_CURRENT_TIME.

Returns :
	成功则返回GDK_GRAB_SUCCESS
	*/

	}
	else
	{//如果点击的次数超过三次则释放，然后把点击次数置零
		g_print("button1 pressed\n");
		g_print("ungrab the pointer\n");
		gdk_pointer_ungrab(GDK_CURRENT_TIME);
		gtk_grab_remove(GTK_WIDGET(data));
		grab = 0;
	}
}
void button2_click(GtkWidget *widget, gpointer data)
{
	g_print("button2 pressed\n");
}
void my_entry1_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	g_print("to see whether the entry1 response if pointer is grabed by button1\n");
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *button1;
	GtkWidget *button2;
	gint retval;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

/*	gtk_window_set_accept_focus(GTK_WINDOW(window), FALSE);*/
	vbox = gtk_vbox_new(TRUE, 3);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 3);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox1 = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox1,
			TRUE, TRUE, 0);

	/*entry连接回调函数*/
	entry1 = gtk_entry_new();
	g_signal_connect(G_OBJECT(entry1), "button-press-event",
			G_CALLBACK(my_entry1_pressed), NULL);
	gtk_entry_set_text(GTK_ENTRY(entry1), "entry1,press here to see if the grab mask here");
	gtk_box_pack_start(GTK_BOX(hbox1), entry1,
			TRUE, TRUE, 0);

	entry2 = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry2), "entry2");
	gtk_box_pack_start(GTK_BOX(hbox1), entry2,
			TRUE, TRUE, 0);

	hbox2 = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2,
			TRUE, TRUE, 0);

	/*button1连接回调函数*/
	button1 = gtk_button_new_with_label("button1");
	/*在任何时候，即使出了范围，也要捕获button1的鼠标button-press-event事件*/
	g_signal_connect(G_OBJECT(button1), "button-press-event",
			G_CALLBACK(my_button1_pressed), button1);

	gtk_box_pack_start(GTK_BOX(hbox2), button1,
			TRUE, TRUE, 0);

	/*button2连接回调函数*/
	button2 = gtk_button_new_with_label("button2");
	g_signal_connect(G_OBJECT(button2), "clicked",
			G_CALLBACK(button2_click), button2);
	gtk_box_pack_start(GTK_BOX(hbox2), button2,
			TRUE, TRUE, 0);


	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
