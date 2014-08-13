/*本程序功能：弹出一个消息对话框
 * */
#include<gtk/gtk.h>
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
static void
hello_clicked (GtkWidget *widget, gpointer *data)
{
  GtkWidget *dialog;
  /*gtk_message_dialog_new ()函数弹出对话框*/
  dialog = gtk_message_dialog_new (NULL/*临时父窗口*/,
                                   GTK_DIALOG_MODAL |
                                   GTK_DIALOG_DESTROY_WITH_PARENT |
								   GTK_DIALOG_NO_SEPARATOR/*对话框属性*/,
                                   GTK_MESSAGE_INFO/*消息类型，其它类见后*/,
                                   GTK_BUTTONS_OK/*按钮类型,其它类型见后*/,
                                   "Hello world!"/*提示内容，类似printf*/);
  /* 其它消息类型
   * GTK_MESSAGE_INFO,
   * GTK_MESSAGE_WARNING,
   * GTK_MESSAGE_QUESTION,
   * GTK_MESSAGE_ERROR,
   * GTK_MESSAGE_OTHER
   * */

  /*  其它按钮类型
   *  GTK_BUTTONS_NONE,
   *  GTK_BUTTONS_OK,
   *  GTK_BUTTONS_CLOSE,
   *  GTK_BUTTONS_CANCEL,
   *  GTK_BUTTONS_YES_NO,
   *  GTK_BUTTONS_OK_CANCEL
   * */
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}


gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	//GtkWidget *button2;
	gtk_init(&argc, &argv);
	//window = gtk_window_new(GTK_WINDOW_POPUP);/*popup??,can't control by wmctrl*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//don't forget the G_CALLBACK
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "hello dialog");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	button = gtk_button_new_with_label("here");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello_clicked), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);
	
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
