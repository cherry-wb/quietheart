/*功能：一个简单的模板程序：
 *一个窗口，一个按钮
 经过实践，相关函数如下：
1)这两个函数:
gtk_widget_size_request(window, &requistion);
gtk_widget_get_child_requisition(window, &requistion);
功能类似，都是获取控件合适的大小(个人觉得不太好用因为值不好控制)
如果不用set_border_width那么requistion的成员都是0

2)这两个函数:
gtk_widget_set_size_request(window, 500, 500);
gtk_widget_get_size_request(window, &width, &height);
前者设置控件最小的大小，这样设置后window无法再缩小了，所以最好调用default_size。
后者获取前者设置的控件的大小,若没调前者(set_size_request)则返回-1.如代码。

3)其他：
gdk_window_get_geometry???
gtk_widget_size_allocate???

 * */

#include<gtk/gtk.h>
void hello(GtkWidget *button, gpointer data)
{
	g_print("hello\n");
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;

	gint width = 0;
	gint height = 0;

	/*GtkRequistion两个成员
	 *gint width:宽度
	 *gint height:高度
	 **/
	GtkRequisition requistion;

	/*GtkAllocation四个成员
	 *gint x:控件相对于它父亲的X坐标
	 *gint y:控件相对于它父亲的Y坐标
	 *gint width:控件被分配的宽度
	 *gint height:控件被分配的高度
	 * */
	GtkAllocation al={10,20,200,200};
	gtk_init(&argc, &argv);

	/*window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/*窗口默认大小*/
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit),NULL);

	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	/*没有这句话，则requistion返回的是0,有则返回100*/
	gtk_container_set_border_width(GTK_CONTAINER(window),50);

	/*获取一个控件比较好的大小，根据这个来组织它的子部件*/
	gtk_widget_size_request(window, &requistion);//requistion之前未初始化之后100
	gtk_widget_get_child_requisition(window, &requistion);//requistion成员都是100

	gtk_widget_get_size_request(window, &width, &height);//先调用返回-1
	/*设置窗口的（最小）大小,topwindow最好用*_default_size用这个不能再缩小了。*/
	gtk_widget_set_size_request(window, 500, 500);
	gtk_widget_get_size_request(window, &width, &height);//返回500
	g_print("request,width:%d\n", width);
	g_print("request,height:%d\n",height);

	/*button*/
	button = gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(hello), NULL);
	/*仅对container的子类有作用*/
	gtk_widget_set_size_request(button, 200, 200);
	//gtk_widget_size_allocate(button, &al);/*没有用？？*/
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
