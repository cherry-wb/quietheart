#include<gtk/gtk.h>
# include <dbus/dbus.h> 
//#include <dbus/dbus-glib.h>
/*相应的变量定义*/
# define SYSNOTE_NAME  "org.freedesktop.program2"/*公用服务名字*/
# define SYSNOTE_OPATH "/org/freedesktop/program2"/*对象路径*/
# define SYSNOTE_IFACE "org.freedesktop.program2"/*对象接口名字*/

/*程序1远程调用的函数*/
static void print(const gchar *message)
{
	g_print("in function of program2 called by the program1\n");
}

static int terminateOnError ( const char* msg ,
		const DBusError * error )
{/*自定义的处理错误函数*/ 
	if(NULL == msg && NULL == error)
	{
		exit(1);
	}
	if( dbus_error_is_set (error))
	{
		fprintf (stderr , msg);
		fprintf (stderr , " DBusError .name: %s\n", error ->name);
		fprintf (stderr , " DBusError . message : %s\n", error -> message );
		exit(1);
	}   
}

static DBusHandlerResult
signal_filter (DBusConnection *connection, DBusMessage *message, void *user_data)
{/*类似一个侦听函数，收到的消息在message中*/
	GMainLoop *loop = user_data;
	/*一个断开连接的信号*/
	if(dbus_message_is_signal(message, DBUS_INTERFACE_LOCAL, "Disconnected"))
	{
		/*终止循环*/
		g_print("receive quit signal");
		g_main_loop_quit (loop);
		return DBUS_HANDLER_RESULT_HANDLED;
	}
	/*接收到调用print函数的消息*/
	else if (dbus_message_is_method_call(message, "org.freedesktop.program2", "print"))
	{
		DBusError error;
		char *s;
		dbus_error_init (&error);
		/*获得参数*/
		if (dbus_message_get_args 
				(message, &error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
		{
			g_print("received args: %s\n", s);
			/*难道远程调用只能这样调用么？*/
			print(s);
			/*此处如果释放则会出现异常所以暂时就不释放了！*/
			//dbus_free (s);
		}
		else
		{
			g_print("received, but error getting message: %s\n", error.message);
			terminateOnError (" received, but error getting message\n", & error );
			dbus_error_free (&error);
		}
		return DBUS_HANDLER_RESULT_HANDLED;
	}
	return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

static void dbus_related(GMainLoop *loop)
{
	DBusConnection *bus;
	DBusError error;
	dbus_error_init (&error);

	
	bus = dbus_bus_get (DBUS_BUS_SESSION, &error);
	if (!bus)
	{
		g_warning ("Failed to connect to the D-BUS daemon: %s", error.message);
		dbus_error_free (&error);
		return;
	}
	//dbus_bus_register(bus, NULL);
	//dbus_bus_set_unique_name(bus, "org.freedesktop.program2");

	/*注意这句话一定要有，这样才有公共名称！*/
	dbus_bus_request_name(bus, "org.freedesktop.program2", DBUS_NAME_FLAG_ALLOW_REPLACEMENT, NULL);
	dbus_connection_setup_with_g_main (bus, NULL);

	/*添加消息信息*/
	//dbus_bus_add_match (bus, "type='method_call',interface='org.freedesktop.program2',member='print', path='/org/freedesktop/program2',destination='org.freedesktop.program2'", NULL);

	/*添加消息侦听函数*/
	dbus_connection_add_filter (bus, signal_filter, loop, NULL);
	g_main_loop_run (loop);
}

gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_main_loop_quit ((GMainLoop*)data);
	//gtk_main_quit();
	return FALSE; 
}
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *label;
	GMainLoop *loop;
	loop = g_main_loop_new (NULL, FALSE);
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
			G_CALLBACK(delete_event), loop);
	gtk_window_set_title(GTK_WINDOW(window), "testDbus_program2");
	gtk_container_set_border_width(GTK_CONTAINER(window),50);
	
	
	label = gtk_label_new("this is program2 wait for message send by program1");
	gtk_container_add(GTK_CONTAINER(window), label);

	gtk_widget_show_all(window);
	dbus_related(loop);
	//gtk_main();
	return 0;
}
