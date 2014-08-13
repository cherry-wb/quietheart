#include<dbus/dbus-glib-bindings.h>
#include "server-bindings.h"
#include<gtk/gtk.h>
/*标准GObject类结构*/
typedef struct
{
}ServerObject;

typedef struct
{
}ServerObjectClass;
GType
server_obj_get_type (void);
class_init(ServerObjectClass *klass)
{
	/* &dbus_glib__object_info 在server-bindings.h文件里面提供了，
	 * OBJECT_TYPE_SERVER是你的server对象的GType类型。*/
}

init(ServerObject *server)
{
	GError *error = NULL;
	DBusGConnection *connection;
	DBusGProxy *driver_proxy;
	int request_ret;

	connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
	if (connection == NULL)
	{
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}
	/*注册DBUS路径*/
	dbus_g_connection_register_g_object (connection,
			"/org/gnome/ServiceName",
			G_OBJECT (server));

	/*注册service名字，这里定义的常量在dbus-glib-bindings.h里面已经定义了*/
	driver_proxy = dbus_g_proxy_new_for_name (connection,
			DBUS_SERVICE_DBUS,
			DBUS_PATH_DBUS,
			DBUS_INTERFACE_DBUS);

	if(!org_freedesktop_DBus_request_name (driver_proxy,
				"org.gnome.ServiceName",
				0, &request_ret,    
				&error))
	{
		g_warning("Unable to register service: %s", error->message);
		g_error_free (error);
	}
	dbus_g_object_type_install_info (server_obj_get_type(), &dbus_glib_server_object_object_info);
	g_object_unref (driver_proxy);
}
gboolean
server_echo_string (ServerObject *server, gchar *original, gchar **echo, GError **error)
{
	*echo = g_strdup (original);

	/*if (problem)
	{
		//在这里设置错误信息
		g_set_error (error, g_quark_from_static_string ("echo"),
				0xdeadbeef,
				"Some random problem occured, you're screwed");
		return FALSE;
	}*/

	return TRUE;
}

gint main(gint argc, gchar *argv[])
{
	GMainLoop *loop;
	ServerObject *test;
	test = g_object_new(server_obj_get_type(), NULL);
	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);
	return 0;
}
