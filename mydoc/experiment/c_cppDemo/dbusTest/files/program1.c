/*利用Libdbus直接编写程序(远程调用函数)
 * 程序功能:
 * 运行program1,点击按钮启动program2中的一个print(char*)函数，
 * print(char*)函数打印出一个"HelloDbus消息".
 * 补充：应该最好返回一个值？
*/
/*头文件的包含*/
# include <gtk/gtk.h>
# include <dbus/dbus.h> /* Pull in all of D-Bus headers . */
# include <stdio.h>     /* printf , fprintf , stderr */
//# include <stdlib .h>   /* EXIT_FAILURE , EXIT_SUCCESS */
//# include <assert .h>   /* assert */

/*相应的变量定义*/
# define SYSNOTE_NAME  "org.freedesktop.program2"/*公用服务名字*/
# define SYSNOTE_OPATH "/org/freedesktop/program2"/*对象路径*/
# define SYSNOTE_IFACE "org.freedesktop.program2"/*对象接口名字*/
# define SYSNOTE_NOTE  "print"/*（接口下）待调用的函数名字*/

	/*相关代码*/

static int terminateOnError ( const char* msg ,
		const DBusError * error )
{ 
	//assert (msg != NULL);
	//assert (error != NULL);
	if(NULL == msg && NULL == error)
	{
		exit(1);
	}
	if ( dbus_error_is_set (error ))
	{
		fprintf (stderr , msg);
		fprintf (stderr , " DBusError .name: %s\n", error ->name);
		fprintf (stderr , " DBusError . message : %s\n", error -> message );
		exit(1);
	}   
}

gboolean callback(GtkWidget *widget, gpointer data)
{
	g_print("click to send message to program2\n");
	/*****************建立连接*****************/
	/*连接bus的数据结构*/
	DBusConnection * bus = NULL;
	/*调用方法的消息结构*/
	DBusMessage * msg = NULL;
	/*存放D-Bus错误信息的结构，我们在堆栈里分配它，它会自动释放*/
	DBusError error;
	/*将要显示的消息*/
	const char* dispMsg = "hello, function arg sent by the program1\n";
	/*清除错误信息*/
	dbus_error_init (& error);
	/*因为libdbus不使用GLib，所以这里用的是printf*/
	printf (" Connecting to Session D-Bus\n");
	/*获取连接bus,这里尽量共享其他进程的dbus$$$$$$$$$$$$$$$$$*/
	bus = dbus_bus_get ( DBUS_BUS_SESSION , & error );
	/*捕捉错误，如果error非空则终止程序,自己编写的*/
	terminateOnError (" Failed to open Session bus\n", & error );
	//assert (bus != NULL);
	if(NULL == bus)
	{
		exit(1);
	}
	/*一个实用函数，检查是否有进程拥有这个公用的服务名字*/
	if (!dbus_bus_name_has_owner (bus , SYSNOTE_NAME , & error ))
	{
		fprintf (stderr , "Name has no owner on the bus !\n");
		return TRUE ;
	}
	terminateOnError (" Failed to check for name ownership \n", & error );

	/**********建立调用函数的消息*********************/
	/* Construct a DBusMessage that represents a method call.
	   Parameters will be added later . The internal type of the message
	   will be DBUS_MESSAGE_TYPE_METHOD_CALL . */
	//printf (" Creating a message object \n");
	/*建立dbus消息对象,以调用函数,函数的作用是显示对话框*/
	msg = dbus_message_new_method_call ( SYSNOTE_NAME , /* 公用服务名字 */
			SYSNOTE_OPATH , /* 对象路径 */
			SYSNOTE_IFACE , /* 接口名字 */
			SYSNOTE_NOTE ); /* 将要调用的函数 */

	if (msg == NULL)
	{
		fprintf (stderr , "Ran out of memory when creating a message \n");
		exit(1);
	}

	/*为消息添加函数的参数
	  第一个参数：字符串类型的，用来显示对话框的提醒内容
	  第二个参数：整数类型的，用来标志对话框的类型
	  第三个参数：字符串类型的，用来显示确认按钮的内容
	  注意：传递的都是参数值的地址
	  */
	if (! dbus_message_append_args (msg ,
				DBUS_TYPE_STRING , &dispMsg ,
				DBUS_TYPE_INVALID )) {
		fprintf (stderr , "Ran out of memory while constructing args\n");
		exit(1);
	}
	/*消息将要通过marshaling包装之后发送给dbus的deamon然后转发给对应的接收方*/
	/*这里设置dbus deamon确认不给我们发送回应???，这样我们不需要知道消息是否发送到了*/
	dbus_message_set_no_reply (msg , TRUE);
	//printf (" Adding message to client ’s send -queue \n");

	/*这个函数使得如果program2没有启动的则先启动program2*/
	//dbus_message_set_auto_start (msg, TRUE);

	/*************发送消息************/
	/*一般消息建立完毕之后，将会放到一个队列里面，之后会一次性的全部发出，这样可以降低开销*/
	if (! dbus_connection_send (bus , msg , NULL))
	{
		fprintf (stderr , "Ran out of memory while queueing message \n");
		exit(1);
	}
	//printf (" Waiting for send -queue to be sent out\n");
	/*使用这个函数会把队列里的消息立即发送出去,无须排队*/
	dbus_connection_flush (bus);
	//printf ("Queue is now empty \n");

	/* Free up the allocated message . Most D-Bus objects have internal
	   reference count and sharing possibility , so _unref () functions
	   are quite common . */
	dbus_message_unref (msg);
	msg = NULL;

	/*************通讯完毕释放资源***************/
	/*这里因为一般是共享的，所以减少引用*/
	dbus_connection_unref (bus);
	bus = NULL;
	printf (" Quitting ( success )\n");
	return TRUE ;
}
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), NULL);
	gtk_window_set_title(GTK_WINDOW(window), "testDbus_program1");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	
	button = gtk_button_new_with_label("click to send dbus message");
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(callback), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
